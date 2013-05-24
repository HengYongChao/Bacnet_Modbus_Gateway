/*
	FreeRTOS V2.6.0 - Copyright (C) 2003 - 2005 Richard Barry.

	This file is part of the FreeRTOS distribution.

	FreeRTOS is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	FreeRTOS is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FreeRTOS; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	A special exception to the GPL can be applied should you wish to distribute
	a combined work that includes FreeRTOS, without being obliged to provide
	the source code for any proprietary components.  See the licensing section 
	of http://www.FreeRTOS.org for full details of how and when the exception
	can be applied.

	***************************************************************************
	See http://www.FreeRTOS.org for documentation, latest information, license 
	and contact details.  Please ensure to read the configuration and relevant 
	port sections of the online documentation.
	***************************************************************************
*/

/*
Changes from V1.00:
	
	+ Call to portRESTORE_CONTEXT has been removed.  The first context
	  switch is now performed within sPortStartScheduler().

Changes from V1.01:

	+ More use of 8bit data types.
	+ Function name prefixes changed where the data type returned has changed.
	+ USE_TRACE_FACILITY is no longer defined by default.

Changes from V1.2.0

	+ Introduced ucTopReadyPriority.  This tracks the highest priority ready
	  queue that contains a valid TCB and thus makes the context switch 
	  slightly faster.

	+ prvAddTaskToReadyQueue() has been made a macro.

Changes from V1.2.6

	+ Added conditional compilation directives.
	+ Extended API.
	+ Rearranged function order.
	+ Creating a task now causes a context switch if the task being created
	  has a higher priority than the calling task - assuming the kernel is
	  running.
	+ vTaskDelete() now only causes a context switch if the calling task is
	  the task being deleted.

Changes from V2.0.0

	+ Allow the type of the tick count to be 16 or 32 bits.
	+ Introduce xPendingReadyList feature to allow the time interrupts have to
	  be disabled to be minimised.
	+ Remove the #if( INCLUDE_vTaskSuspendAll ) statements.  vTaskSuspendAll()
	  is now always included as it is used by the scheduler itself.

Changes from V2.1.0

	+ Bug fix - pxCurrentTCB is now initialised before the call to 
	  prvInitialiseTaskLists().  Previously pxCurrentTCB could be accessed 
	  while null.

Changed from V2.1.1

	+ Change to where lStackSize is declared within sTaskCreate() to prevent
	  compiler warnings with 8051 port.

Changes from V2.2.0

	+ Explicit use of 'signed' qualifier on portCHAR types added.
	+ Changed odd calculation of initial pxTopOfStack value when 
	  portSTACK_GROWTH < 0.
	+ Removed pcVersionNumber definition.

Changes from V2.5.3

	+ cTaskResumeAll() modified to ensure it can be called prior to the task
	  lists being initialised.

Changes from V2.5.5

	+ Added API function vTaskDelayUntil().
	+ Added INCLUDE_vTaskDelay conditional compilation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "projdefs.h"
#include "portable.h"
#include "task.h"
#include "errors.h"
extern INT8U xdata * data C_XBP;
/*
 * Macro to define the amount of stack available to the idle task.
 */
#define tskIDLE_STACK_SIZE	portMINIMAL_STACK_SIZE

/*
 * Task control block.  A task control block (TCB) is allocated to each task,
 * and stores the context of the task.
 */
typedef struct tskTaskControlBlock
{
	portSTACK_TYPE		*pxTopOfStack;						/*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE STRUCT. */
	portSTACK_TYPE		*pxStack;							/*< Points to the start of the stack. */
	unsigned portSHORT	usStackDepth;						/*< Total depth of the stack (when empty).  This is defined as the number of variables the stack can hold, not the number of bytes. */
	signed portCHAR		pcTaskName[ tskMAX_TASK_NAME_LEN ];	/*< Descriptive name given to the task when created.  Facilitates debugging only. */
	unsigned portCHAR	ucPriority;							/*< The priority of the task where 0 is the lowest priority. */

	xListItem			xGenericListItem;					/*< List item used to place the TCB in ready and blocked queues. */
	xListItem			xEventListItem;						/*< List item used to place the TCB in event lists. */

	unsigned portCHAR	ucTCBNumber;						/*< This is used for tracing the scheduler only. */
} tskTCB;

/*lint -e956 */

volatile tskTCB * volatile pxCurrentTCB = NULL;					

/* Lists for ready and blocked tasks. --------------------*/

 volatile xList pxReadyTasksLists[ portMAX_PRIORITIES ];	/*< Prioratised ready tasks. */
static volatile xList xDelayedTaskList1;						/*< Delayed tasks. */
static volatile xList xDelayedTaskList2;						/*< Delayed tasks (two lists are used - one for delays that have overflowed the current tick count. */
static volatile xList *pxDelayedTaskList;						/*< Points to the delayed task list currently being used. */
static volatile xList *pxOverflowDelayedTaskList;				/*< Points to the delayed task list currently being used to hold tasks that have overflowed the current tick count. */
static volatile xList xPendingReadyList;						/*< Tasks that have been readied while the scheduler was suspended.  They will be moved to the ready queue when the scheduler is resumed. */

#if( INCLUDE_vTaskDelete == 1 )

	static volatile xList xTasksWaitingTermination;				/*< Tasks that have been deleted - but the their memory not yet freed. */

#endif

#if( INCLUDE_vTaskSuspend == 1 )

	static volatile xList xSuspendedTaskList;					/*< Tasks that are currently suspended. */

#endif

/* File private variables. --------------------------------*/
static portSHORT sUsingPreemption = pdFALSE;
static unsigned portSHORT usCurrentNumberOfTasks = ( unsigned portSHORT ) 0;              
volatile portTickType xTickCount = ( portTickType ) 0;				/* Modified by tick ISR. */
static unsigned portCHAR ucTopUsedPriority = tskIDLE_PRIORITY;
static volatile unsigned portCHAR ucTopReadyPriority = tskIDLE_PRIORITY;
static signed portCHAR cSchedulerRunning = pdFALSE;
static volatile unsigned portCHAR ucSchedulerSuspended = pdFALSE;
static volatile unsigned portCHAR ucMissedTicks = ( unsigned portCHAR ) 0;

/* Debugging and trace facilities private variables and macros. ------------*/

/*
 * The value used to fill the stack of a task when the task is created.  This
 * is used purely for checking the high water mark for tasks.
 */
#define tskSTACK_FILL_BYTE	( 0xa5 )

/*
 * Macros used by vListTask to indicate which state a task is in.
 */
#define tskBLOCKED_CHAR		( ( signed portCHAR ) 'B' )
#define tskREADY_CHAR		( ( signed portCHAR ) 'R' )
#define tskDELETED_CHAR		( ( signed portCHAR ) 'D' )
#define tskSUSPENDED_CHAR	( ( signed portCHAR ) 'S' )

/* 
 * Macros and private variables used by the trace facility.
 */
#if( USE_TRACE_FACILITY == 1 )

	#define tskSIZE_OF_EACH_TRACE_LINE			( sizeof( unsigned portLONG ) + sizeof( unsigned portCHAR ) )
	static volatile signed portCHAR * volatile pcTraceBuffer;
	static signed portCHAR *pcTraceBufferStart;
	static signed portCHAR *pcTraceBufferEnd;
	static signed portCHAR cTracing = ( signed portCHAR ) pdFALSE;

#endif

/*
 * Macro that writes a trace of scheduler activity to a buffer.  This trace
 * shows which task is running when and is very useful as a debugging tool.
 * As this macro is called each context switch it is a good idea to undefine
 * it if not using the facility.
 */
#if( USE_TRACE_FACILITY == 1 )

	#define vWriteTraceToBuffer()														\
	{																					\
		if( cTracing )																	\
		{																				\
			static unsigned portCHAR ucPreviousTask = 255;								\
																						\
			if( ucPreviousTask != pxCurrentTCB->ucTCBNumber )							\
			{																			\
				if( ( pcTraceBuffer + tskSIZE_OF_EACH_TRACE_LINE ) < pcTraceBufferEnd )	\
				{																		\
					ucPreviousTask = pxCurrentTCB->ucTCBNumber;							\
					*( unsigned portLONG * ) pcTraceBuffer = ( unsigned portLONG ) xTickCount;	\
					pcTraceBuffer += sizeof( unsigned portLONG );						\
					*( unsigned portCHAR * ) pcTraceBuffer = ucPreviousTask;			\
					pcTraceBuffer += sizeof( unsigned portCHAR );						\
				}																		\
				else																	\
				{																		\
					cTracing = ( signed portCHAR ) pdFALSE;								\
				}																		\
			}																			\
		}																				\
	}

#else

	#define vWriteTraceToBuffer()

#endif


/*
 * Place the task represented by pxTCB into the appropriate ready queue for
 * the task.  It is inserted at the end of the list.  One quirk of this is
 * that if the task being inserted is at the same priority as the currently
 * executing task, then it will only be rescheduled after the currently 
 * executing task has been rescheduled.
 */
#define prvAddTaskToReadyQueue( pxTCB )																			\
{																												\
	listSET_LIST_ITEM_VALUE( &( pxTCB->xGenericListItem ), 0 );													\
	if( pxTCB->ucPriority > ucTopReadyPriority )																\
	{																											\
		ucTopReadyPriority = pxTCB->ucPriority;																	\
	}																											\
	vListInsertEnd( ( xList * ) &( pxReadyTasksLists[ pxTCB->ucPriority ] ), &( pxTCB->xGenericListItem ) );	\
}	


/*
 * Macro that looks at the list of tasks that are currently delayed to see if 
 * any require waking.
 *
 * Tasks are stored in the queue in the order of their wake time - meaning
 * once one tasks has been found whose timer has not expired we need not look
 * any further down the list.
 */
#define prvCheckDelayedTasks()																	\
{																								\
register tskTCB *pxTCB;																			\
																								\
	while( ( pxTCB = ( tskTCB * ) listGET_OWNER_OF_HEAD_ENTRY( pxDelayedTaskList ) ) != NULL )	\
	{																							\
		if( xTickCount < listGET_LIST_ITEM_VALUE( &( pxTCB->xGenericListItem ) ) )				\
		{																						\
			break;																				\
		}																						\
		vListRemove( &( pxTCB->xGenericListItem ) );											\
		/* Is the task waiting on an event also? */												\
		if( pxTCB->xEventListItem.pvContainer )													\
		{																						\
			vListRemove( &( pxTCB->xEventListItem ) );											\
		}																						\
		prvAddTaskToReadyQueue( pxTCB );														\
	}																							\
}																							

/*
 * Several functions take an xTaskHandle parameter that can optionally be NULL,
 * where NULL is used to indicate that the handle of the currently executing 
 * task should be used in place of the parameter.  This macro simply checks to 
 * see if the parameter is NULL and returns a pointer to the appropriate TCB.
 */
#define prvGetTCBFromHandle( pxHandle ) ( ( pxHandle == NULL ) ? ( tskTCB * ) pxCurrentTCB : ( tskTCB * ) pxHandle )


/* File private functions. --------------------------------*/

/*
 * Utility to ready a TCB for a given task.  Mainly just copies the parameters
 * into the TCB structure.
 */
static void prvInitialiseTCBVariables( tskTCB *pxTCB, unsigned portSHORT usStackDepth, const signed portCHAR * const pcName, unsigned portCHAR ucPriority ) reentrant ;

/*
 * Utility to ready all the lists used by the scheduler.  This is called 
 * automatically upon the creation of the first task.
 */
static portSHORT prvInitialiseTaskLists( void ) reentrant;

/*
 * The idle task, which as all tasks is implemented as a never ending loop.
 * The idle task is automatically created and added to the ready lists upon
 * creation of the first user task.
 */
static void prvIdleTask( void *pvParameters ) reentrant;

/*
 * Utility to free all memory allocated by the scheduler to hold a TCB, 
 * including the stack pointed to by the TCB.  
 *
 * This does not free memory allocated by the task itself (i.e. memory 
 * allocated by calls to pvPortMalloc from within the tasks application code).
 */
#if( ( INCLUDE_vTaskDelete == 1 ) || ( INCLUDE_vTaskCleanUpResources == 1 ) )
	static void prvDeleteTCB( tskTCB *pxTCB )reentrant;
#endif

/*
 * Used only by the idle task.  This checks to see if anything has been placed
 * in the list of tasks waiting to be deleted.  If so the task is cleaned up
 * and its TCB deleted.
 */
static void prvCheckTasksWaitingTermination( void )reentrant;

/*
 * Allocates memory from the heap for a TCB and associated stack.  Checks the
 * allocation was successful.
 */
static tskTCB *prvAllocateTCBAndStack( unsigned portSHORT usStackDepth )reentrant;

/*
 * Called from vTaskList.  vListTasks details all the tasks currently under
 * control of the scheduler.  The tasks may be in one of a number of lists.
 * prvListTaskWithinSingleList accepts a list and details the tasks from
 * within just that list.
 *
 * THIS FUNCTION IS INTENDED FOR DEBUGGING ONLY, AND SHOULD NOT BE CALLED FROM
 * NORMAL APPLICATION CODE.
 */
#if( USE_TRACE_FACILITY == 1 )

	static void prvListTaskWithinSingleList( signed portCHAR *pcWriteBuffer, xList *pxList, signed portCHAR cStatus )reentrant;
#endif


/*lint +e956 */





/*-----------------------------------------------------------
 * TASK CREATION API documented in task.h
 *----------------------------------------------------------*/

portSHORT sTaskCreate( pdTASK_CODE pvTaskCode, const signed portCHAR * const pcName, unsigned portSHORT usStackDepth, void *pvParameters, unsigned portCHAR ucPriority, xTaskHandle *pxCreatedTask )reentrant
{
portSHORT sReturn;
tskTCB * pxNewTCB;
static unsigned portCHAR ucTaskNumber = 0; /*lint !e956 Static is deliberate - this is guarded before use. */

	/* Allocate the memory required by the TCB and stack for the new task.  
	checking that the allocation was successful. */
	pxNewTCB = prvAllocateTCBAndStack( usStackDepth );
	if( pxNewTCB != NULL )
	{		
		portSTACK_TYPE *pxTopOfStack;

		/* Setup the newly allocated TCB with the initial state of the task. */
		prvInitialiseTCBVariables( pxNewTCB, usStackDepth, pcName, ucPriority );

		/* Calculate the top of stack address.  This depends on whether the
		stack grows from high memory to low (as per the 80x86) or visa versa. 
		portSTACK_GROWTH is used to make the result positive or negative as
		required by the port. */
		#if portSTACK_GROWTH < 0
		{
			portLONG lStackSize; 

			lStackSize = ( portLONG ) ( pxNewTCB->usStackDepth - ( unsigned portSHORT ) 1 );
			pxTopOfStack = pxNewTCB->pxStack + lStackSize;
		}
		#else
		{
			pxTopOfStack = pxNewTCB->pxStack;	
		}
		#endif

		/* Initialise the TCB stack to look as if the task was already running,
		but had been interrupted by the scheduler.  The return address is set
		to the start of the task function. Once the stack has been initialised
		the	top of stack variable is updated. */
		pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack, pvTaskCode, pvParameters );

		/* We are going to manipulate the task queues to add this task to a
		ready list, so must make sure no interrupts occur. */
		portENTER_CRITICAL();
		{
			usCurrentNumberOfTasks++;
			if( usCurrentNumberOfTasks == ( unsigned portSHORT ) 1 )
			{
				/* As this is the first task it must also be the current task. */
				pxCurrentTCB = ( volatile tskTCB * volatile ) pxNewTCB;

				/* This is the first task to be created so do the preliminary
				initialisation required.  We will not recover if this call 
				fails, but we will report the failure. */
				sReturn = prvInitialiseTaskLists();
			}
			else
			{
				sReturn = pdPASS;

				/* If the scheduler is not already running, make this task the
				current task if it is the highest priority task to be created
				so far. */
				if( cSchedulerRunning == pdFALSE )
				{
					if( pxCurrentTCB->ucPriority <= ucPriority )
					{
						pxCurrentTCB = ( volatile tskTCB * volatile ) pxNewTCB;	
					}
				}
			}				

			/* Remember the top priority to make context switching faster.  Use
			the priority in pxNewTCB as this has been capped to a valid value. */
			if( pxNewTCB->ucPriority > ucTopUsedPriority )
			{
				ucTopUsedPriority = pxNewTCB->ucPriority;
			}

			/* Add a counter into the TCB for tracing only. */
			pxNewTCB->ucTCBNumber = ucTaskNumber;
			ucTaskNumber++;

			prvAddTaskToReadyQueue( pxNewTCB );
		}
		portEXIT_CRITICAL();
	}
	else
	{
		sReturn = errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY;
	}

	if( sReturn == pdPASS )
	{
		if( ( void * ) pxCreatedTask != NULL )
		{
			/* Pass the TCB out - in an anonymous way.  The calling function/
			task can use this as a handle to delete the task later if 
			required.*/
			*pxCreatedTask = ( xTaskHandle ) pxNewTCB;
		}

		if( cSchedulerRunning != pdFALSE )
		{
			/* If the created task is of a higher priority than the current task
			then it should run now. */
			if( pxCurrentTCB->ucPriority < ucPriority )
			{
				taskYIELD();
			}
		}
	}

	return sReturn;
}
/*-----------------------------------------------------------*/

#if( INCLUDE_vTaskDelete == 1 )

	void vTaskDelete( xTaskHandle pxTaskToDelete ) reentrant
	{
	tskTCB *pxTCB;

		taskENTER_CRITICAL();
		{
			/* If null is passed in here then we are deleting ourselves. */
			pxTCB = prvGetTCBFromHandle( pxTaskToDelete );

			/* Remove task from the ready list and place in the	termination list.
			This will stop the task from be scheduled.  The idle task will check
			the termination list and free up any memory allocated by the 
			scheduler for the TCB and stack. */
			vListRemove( &( pxTCB->xGenericListItem ) );

			/* Is the task waiting on an event also? */												
			if( pxTCB->xEventListItem.pvContainer )
			{
				vListRemove( &( pxTCB->xEventListItem ) );
			}

			vListInsertEnd( ( xList * ) &xTasksWaitingTermination, &( pxTCB->xGenericListItem ) );
		}
		taskEXIT_CRITICAL();

		/* Force a reschedule if we have just deleted the current task. */
		if( ( void * ) pxTaskToDelete == NULL )
		{
			taskYIELD();
		}
	}

#endif






/*-----------------------------------------------------------
 * TASK CONTROL API documented in task.h
 *----------------------------------------------------------*/

#if( INCLUDE_vTaskDelayUntil == 1 )
	void vTaskDelayUntil( portTickType *pxPreviousWakeTime, portTickType xTimeIncrement ) reentrant
	{
	portTickType xTimeToWake;
	portCHAR cAlreadyYielded, cShouldDelay = ( portCHAR ) pdFALSE;

		vTaskSuspendAll();
		{
			/* Generate the tick time at which the task wants to wake. */
			xTimeToWake = *pxPreviousWakeTime + xTimeIncrement;

			if( xTickCount < *pxPreviousWakeTime )
			{
				/* The tick count has overflowed since this function was 
				lasted called.  In this case the only time we should ever 
				actually delay is if the wake time has also	overflowed, 
				and the wake time is greater than the tick time.  When this 
				is the case it is as if neither time had overflowed. */
				if( ( xTimeToWake < *pxPreviousWakeTime ) && ( xTimeToWake > xTickCount ) )
				{
					cShouldDelay = ( portCHAR ) pdTRUE;
				}
			}
			else
			{
				/* The tick time has not overflowed.  In this case we will
				delay if either the wake time has overflowed, and/or the
				tick time is less than the wake time. */
				if( ( xTimeToWake < *pxPreviousWakeTime ) || ( xTimeToWake > xTickCount ) )
				{
					cShouldDelay = ( portCHAR ) pdTRUE;
				}
			}

			/* Update the wake time ready for the next call. */
			*pxPreviousWakeTime = xTimeToWake;

			if( cShouldDelay )
			{
				/* We must remove ourselves from the ready list before adding 
				ourselves to the blocked list as the same list item is used for 
				both lists. */
				vListRemove( ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );

				/* The list item will be inserted in wake time order. */
				listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xGenericListItem ), xTimeToWake );

				if( xTimeToWake < xTickCount )
				{
					/* Wake time has overflowed.  Place this item in the 
					overflow list. */
					vListInsert( ( xList * ) pxOverflowDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
				}
				else
				{
					/* The wake time has not overflowed, so we can use the 
					current block list. */
					vListInsert( ( xList * ) pxDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
				}
			}
		}
		cAlreadyYielded = cTaskResumeAll();

		/* Force a reschedule if cTaskResumeAll has not already done so, we may 
		have put ourselves to sleep. */
		if( !cAlreadyYielded )
		{
			taskYIELD(); 
		}
	}
#endif
/*-----------------------------------------------------------*/

#if( INCLUDE_vTaskDelay == 1 )
	void vTaskDelay( portTickType xTicksToDelay ) reentrant
	{
	portTickType xTimeToWake;
	signed portCHAR cAlreadyYielded = pdFALSE;

		/* A delay time of zero just forces a reschedule. */
		if( xTicksToDelay > ( portTickType ) 0 )
		{
			vTaskSuspendAll();
			{
				/* A task that is removed from the event list while the 
				scheduler is suspended will not get placed in the ready 
				list or removed from the blocked list until the scheduler 
				is resumed.  
				
				This task cannot be in an event list as it is the currently 
				executing task. */

				/* Calculate the time to wake - this may overflow but this is 
				not a problem. */
				xTimeToWake = xTickCount + xTicksToDelay;

				/* We must remove ourselves from the ready list before adding 
				ourselves to the blocked list as the same list item is used for 
				both lists. */
				vListRemove( ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );

				/* The list item will be inserted in wake time order. */
				listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xGenericListItem ), xTimeToWake );

				if( xTimeToWake < xTickCount )
				{
					/* Wake time has overflowed.  Place this item in the 
					overflow list. */
					vListInsert( ( xList * ) pxOverflowDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
				}
				else
				{
					/* The wake time has not overflowed, so we can use the 
					current block list. */
					vListInsert( ( xList * ) pxDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
				}
			}
			cAlreadyYielded = cTaskResumeAll();
		}
		
		/* Force a reschedule if cTaskResumeAll has not already done so, we may 
		have put ourselves to sleep. */
		if( !cAlreadyYielded )
		{
			taskYIELD(); 
		}
	}
#endif
/*-----------------------------------------------------------*/

#if( INCLUDE_ucTaskPriorityGet == 1 )

	unsigned portCHAR ucTaskPriorityGet( xTaskHandle pxTask ) reentrant
	{
	tskTCB *pxTCB;
	unsigned portCHAR ucReturn;

		taskENTER_CRITICAL();
		{
			/* If null is passed in here then we are changing the
			priority of the calling function. */
			pxTCB = prvGetTCBFromHandle( pxTask );
			ucReturn = pxTCB->ucPriority;
		}
		taskEXIT_CRITICAL();

		return ucReturn;
	}

#endif
/*-----------------------------------------------------------*/

#if( INCLUDE_vTaskPrioritySet == 1 )

	void vTaskPrioritySet( xTaskHandle pxTask, unsigned portCHAR ucNewPriority ) reentrant
	{
	tskTCB *pxTCB;
	unsigned portCHAR ucCurrentPriority;

		/* Ensure the new priority is valid. */
		if( ucNewPriority >= portMAX_PRIORITIES )
		{
			ucNewPriority = portMAX_PRIORITIES - ( unsigned portCHAR ) 1;
		}

		taskENTER_CRITICAL();
		{
			/* If null is passed in here then we are changing the
			priority of the calling function. */
			pxTCB = prvGetTCBFromHandle( pxTask );
			ucCurrentPriority = pxTCB->ucPriority;

			if( ucCurrentPriority != ucNewPriority )
			{
				pxTCB->ucPriority = ucNewPriority;

				/* If the task is in the blocked or suspended list we need do 
				nothing more than change it's priority variable. However, if 
				the task is in a ready list it needs to be removed and placed 
				in the queue appropriate to its new priority. */
				if( listIS_CONTAINED_WITHIN( &( pxReadyTasksLists[ ucCurrentPriority ] ), &( pxTCB->xGenericListItem ) ) )
				{
					/* The task is currently in its ready list - remove before adding
					it to it's new ready list. */
					vListRemove( &( pxTCB->xGenericListItem ) );
					prvAddTaskToReadyQueue( pxTCB );
				}			
			}
		}
		taskEXIT_CRITICAL();

		/* The priority change may have readied a task of higher
		priority than the calling task. */
		taskYIELD();
	}

#endif
/*-----------------------------------------------------------*/

#if( INCLUDE_vTaskSuspend == 1 )

	void vTaskSuspend( xTaskHandle pxTaskToSuspend ) reentrant
	{
	tskTCB *pxTCB;

		taskENTER_CRITICAL();
		{
			/* If null is passed in here then we are suspending ourselves. */
			pxTCB = prvGetTCBFromHandle( pxTaskToSuspend );

			/* Remove task from the ready/delayed list and place in the	suspended list. */
			vListRemove( &( pxTCB->xGenericListItem ) );

			/* Is the task waiting on an event also? */												
			if( pxTCB->xEventListItem.pvContainer )
			{
				vListRemove( &( pxTCB->xEventListItem ) );
			}

			vListInsertEnd( ( xList * ) &xSuspendedTaskList, &( pxTCB->xGenericListItem ) );
		}
		taskEXIT_CRITICAL();

		/* We may have just suspended the current task. */
		if( ( void * ) pxTaskToSuspend == NULL )
		{
			taskYIELD();
		}
	}

#endif
/*-----------------------------------------------------------*/

#if( INCLUDE_vTaskSuspend == 1 )

	void vTaskResume( xTaskHandle pxTaskToResume )reentrant
	{
	tskTCB *pxTCB;
	portSHORT sYieldRequired;

		/* Remove the task from whichever list it is currently in, and place
		it in the ready list. */
		pxTCB = ( tskTCB * ) pxTaskToResume;

		/* The parameter cannot be NULL as it is impossible to resume the
		currently executing task. */
		if( pxTCB != NULL )
		{
			taskENTER_CRITICAL();
			{
				sYieldRequired = ( pxTCB->ucPriority >= pxCurrentTCB->ucPriority );
				vListRemove( &( pxTCB->xGenericListItem ) );
				prvAddTaskToReadyQueue( pxTCB );
			}
			taskEXIT_CRITICAL();

			/* We may have just resumed a higher priority task. */
			if( sYieldRequired )
			{
				/* This yield may not cause the task just resumed to run, but
				will leave the lists in the correct state for the next yield. */
				taskYIELD();
			}
		}
	}

#endif





/*-----------------------------------------------------------
 * PUBLIC SCHEDULER CONTROL documented in task.h
 *----------------------------------------------------------*/


void vTaskStartScheduler( portSHORT sUsePreemption )reentrant
{
	/* Check a task has been created. */
	if( pxCurrentTCB != NULL )
	{
		sUsingPreemption = sUsePreemption;

		/* Interrupts are turned off here, to ensure a tick does not occur
		before or during the call to sPortStartScheduler().  The stacks of 
		the created tasks contain a status word with interrupts switched on
		so interrupts will automatically get re-enabled when the first task
		starts to run.
		
		STEPPING THROUGH HERE USING A DEBUGGER CAN CAUSE BIG PROBLEMS IF THE
		DEBUGGER ALLOWS INTERRUPTS TO BE PROCESSED. */
		portDISABLE_INTERRUPTS();

		cSchedulerRunning = pdTRUE;
		xTickCount = ( portTickType ) 0;

		/* Setting up the timer tick is hardware specific and thus in the 
		portable interface. */
		if( sPortStartScheduler( sUsePreemption ) )
		{
			/* Should not reach here as if the scheduler is running the
			function will not return. */
		}
		else
		{
			/* Should only reach here if a task calls sTaskEndScheduler(). */
		}
	}
}
/*-----------------------------------------------------------*/

void vTaskEndScheduler( void ) reentrant
{
	/* Stop the scheduler interrupts and call the portable scheduler end 
	routine so the original ISRs can be restored if necessary.  The port
	layer must ensure interrupts enable	bit is left in the correct state. */
	portDISABLE_INTERRUPTS();
	cSchedulerRunning = pdFALSE;
	vPortEndScheduler();
}
/*----------------------------------------------------------*/

void vTaskSuspendAll( void ) reentrant
{
	portENTER_CRITICAL();
		++ucSchedulerSuspended;
	portEXIT_CRITICAL();
}
/*----------------------------------------------------------*/

signed portCHAR cTaskResumeAll( void ) reentrant
{
register tskTCB *pxTCB;
signed portCHAR cAlreadyYielded = ( signed portCHAR ) pdFALSE;

	/* It is possible that an ISR caused a task to be removed from an event
	list while the scheduler was suspended.  If this was the case then the
	removed task will have been added to the xPendingReadyList.  Once the
	scheduler has been resumed it is safe to move all the pending ready
	tasks from this list into their appropriate ready list. */
	portENTER_CRITICAL();
	{
		--ucSchedulerSuspended;

		if( ucSchedulerSuspended == pdFALSE )
		{
			if( usCurrentNumberOfTasks > ( unsigned portSHORT ) 0 )
			{
				/* Move any readied tasks from the pending list into the 
				appropriate ready list. */
				while( ( pxTCB = ( tskTCB * ) listGET_OWNER_OF_HEAD_ENTRY(  ( ( xList * ) &xPendingReadyList ) ) ) != NULL )
				{
					vListRemove( &( pxTCB->xEventListItem ) );
					vListRemove( &( pxTCB->xGenericListItem ) );
					prvAddTaskToReadyQueue( pxTCB );
				}

				/* If any ticks occurred while the scheduler was suspended then
				they should be processed now.  This ensures the tick count does not
				slip, and that any delayed tasks are resumed at the correct time. */
				if( ucMissedTicks > 0 )
				{
					while( ucMissedTicks > 0 )
					{
						vTaskIncrementTick();
						--ucMissedTicks;
					}

					/* As we have processed some ticks it is appropriate to yield
					to ensure the highest priority task that is ready to run is
					the task actually running. */
					cAlreadyYielded = ( signed portCHAR ) pdTRUE;
					taskYIELD();
				}
			}
		}
	}
	portEXIT_CRITICAL();

	return cAlreadyYielded;
}






/*-----------------------------------------------------------
 * PUBLIC TASK UTILITIES documented in task.h
 *----------------------------------------------------------*/



volatile portTickType xTaskGetTickCount( void ) reentrant
{
portTickType xTicks;

	/* Critical section required if running on a 16 bit processor. */
	taskENTER_CRITICAL();
	{
		xTicks = xTickCount;
	}
	taskEXIT_CRITICAL();

	return xTicks;
}
/*-----------------------------------------------------------*/

unsigned portSHORT usTaskGetNumberOfTasks( void ) reentrant
{
unsigned portSHORT usNumberOfTasks;

	taskENTER_CRITICAL();
		usNumberOfTasks = usCurrentNumberOfTasks;
	taskEXIT_CRITICAL();

	return usNumberOfTasks;
}
/*-----------------------------------------------------------*/

#if( ( USE_TRACE_FACILITY == 1 ) && ( INCLUDE_vTaskDelete == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

	void vTaskList( signed portCHAR *pcWriteBuffer ) reentrant
	{
	unsigned portSHORT usQueue;

		/* This is a VERY costly function that should be used for debug only.
		It leaves interrupts disabled for a LONG time. */

		taskENTER_CRITICAL();
		{
			/* Run through all the lists that could potentially contain a TCB and
			report the task name, state and stack high water mark. */

			pcWriteBuffer[ 0 ] = ( signed portCHAR ) 0x00;
			strcat( pcWriteBuffer, ( const signed portCHAR * ) "\r\n" );

			usQueue = ( unsigned portSHORT ) ucTopUsedPriority + ( unsigned portSHORT ) 1;

			do
			{
				usQueue--;

				if( !listLIST_IS_EMPTY( &( pxReadyTasksLists[ usQueue ] ) ) )
				{
					prvListTaskWithinSingleList( pcWriteBuffer, ( xList * ) &( pxReadyTasksLists[ usQueue ] ), tskREADY_CHAR );			
				}
			}while( usQueue > ( unsigned portSHORT ) tskIDLE_PRIORITY );

			if( !listLIST_IS_EMPTY( pxDelayedTaskList ) )
			{
				prvListTaskWithinSingleList( pcWriteBuffer, ( xList * ) pxDelayedTaskList, tskBLOCKED_CHAR );
			}

			if( !listLIST_IS_EMPTY( pxOverflowDelayedTaskList ) )
			{
				prvListTaskWithinSingleList( pcWriteBuffer, ( xList * ) pxOverflowDelayedTaskList, tskBLOCKED_CHAR );
			}

			if( !listLIST_IS_EMPTY( &xTasksWaitingTermination ) )
			{
				prvListTaskWithinSingleList( pcWriteBuffer, ( xList * ) &xTasksWaitingTermination, tskDELETED_CHAR );
			}

			if( !listLIST_IS_EMPTY( &xSuspendedTaskList ) )
			{
				prvListTaskWithinSingleList( pcWriteBuffer, ( xList * ) &xSuspendedTaskList, tskSUSPENDED_CHAR );
			}
		}
		taskEXIT_CRITICAL();
	}

#endif
/*----------------------------------------------------------*/

#if( USE_TRACE_FACILITY == 1 )

	void vTaskStartTrace( signed portCHAR * pcBuffer, unsigned portSHORT usBufferSize ) reentrant
	{
		portENTER_CRITICAL();
		{
			pcTraceBuffer = ( volatile signed portCHAR * volatile )pcBuffer;
			pcTraceBufferStart = pcBuffer;
			pcTraceBufferEnd = pcBuffer + usBufferSize - tskSIZE_OF_EACH_TRACE_LINE;
			cTracing = ( signed portCHAR ) pdTRUE;
		}
		portEXIT_CRITICAL();
	}

#endif
/*----------------------------------------------------------*/

#if( USE_TRACE_FACILITY == 1 )

	unsigned portSHORT usTaskEndTrace( void ) reentrant
	{
	unsigned portSHORT usBufferLength;

		portENTER_CRITICAL();
			cTracing = ( signed portCHAR ) pdFALSE;
		portEXIT_CRITICAL();

		usBufferLength = ( unsigned portSHORT ) ( pcTraceBuffer - pcTraceBufferStart );

		return usBufferLength;
	}

#endif





/*-----------------------------------------------------------
 * SCHEDULER INTERNALS AVAILABLE FOR PORTING PURPOSES
 * documented in task.h
 *----------------------------------------------------------*/


inline void vTaskIncrementTick( void ) reentrant
{
	/* Called by the portable layer each time a tick interrupt occurs.
	Increments the tick then checks to see if the new tick value will cause any
	tasks to be unblocked. */
	if( ucSchedulerSuspended == ( unsigned portCHAR ) pdFALSE )
	{
		++xTickCount;
		if( xTickCount == ( portTickType ) 0 )
		{
			volatile xList *pxTemp;

			/* Tick count has overflowed so we need to swap the delay lists.  If there are
			any items in pxDelayedTaskList here then there is an error! */
			pxTemp = pxDelayedTaskList;
			pxDelayedTaskList = pxOverflowDelayedTaskList;
			pxOverflowDelayedTaskList = pxTemp;
		}

		/* See if this tick has made a timeout expire. */
		prvCheckDelayedTasks();
	}
	else
	{
		++ucMissedTicks;
	}

	#if ( configUSE_TICK_HOOK == 1 )
	{
		extern void vApplicationTickHook( void );

		vApplicationTickHook();
	}
	#endif

}
/*-----------------------------------------------------------*/

#if( ( INCLUDE_vTaskCleanUpResources == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

	void vTaskCleanUpResources( void ) reentrant
	{
	unsigned portSHORT usQueue;
	volatile tskTCB *pxTCB;

		usQueue = ( unsigned portSHORT ) ucTopUsedPriority + ( unsigned portSHORT ) 1;

		/* Remove any TCB's from the ready queues. */
		do
		{
			usQueue--;

			while( !listLIST_IS_EMPTY( &( pxReadyTasksLists[ usQueue ] ) ) )
			{
				listGET_OWNER_OF_NEXT_ENTRY( pxTCB, &( pxReadyTasksLists[ usQueue ] ) )
				vListRemove( ( xListItem * ) &( pxTCB->xGenericListItem ) );

				prvDeleteTCB( ( tskTCB * ) pxTCB );
			}
		}while( usQueue > ( unsigned portSHORT ) tskIDLE_PRIORITY );

		/* Remove any TCB's from the delayed queue. */
		while( !listLIST_IS_EMPTY( &xDelayedTaskList1 ) )
		{
			listGET_OWNER_OF_NEXT_ENTRY( pxTCB, &xDelayedTaskList1 );
			vListRemove( ( xListItem * ) &( pxTCB->xGenericListItem ) );

			prvDeleteTCB( ( tskTCB * ) pxTCB );
		}

		/* Remove any TCB's from the overflow delayed queue. */
		while( !listLIST_IS_EMPTY( &xDelayedTaskList2 ) )
		{
			listGET_OWNER_OF_NEXT_ENTRY( pxTCB, &xDelayedTaskList2 );
			vListRemove( ( xListItem * ) &( pxTCB->xGenericListItem ) );

			prvDeleteTCB( ( tskTCB * ) pxTCB );
		}

		while( !listLIST_IS_EMPTY( &xSuspendedTaskList ) )
		{
			listGET_OWNER_OF_NEXT_ENTRY( pxTCB, &xSuspendedTaskList );
			vListRemove( ( xListItem * ) &( pxTCB->xGenericListItem ) );

			prvDeleteTCB( ( tskTCB * ) pxTCB );
		}		

		while( !listLIST_IS_EMPTY( &xPendingReadyList ) )
		{
			listGET_OWNER_OF_NEXT_ENTRY( pxTCB, &xPendingReadyList );
			vListRemove( ( xListItem * ) &( pxTCB->xGenericListItem ) );

			prvDeleteTCB( ( tskTCB * ) pxTCB );
		}		
	}

#endif
/*-----------------------------------------------------------*/

inline void vTaskSwitchContext( void ) reentrant
{
	if( ucSchedulerSuspended != pdFALSE )
	{
		/* The scheduler is currently suspended - do not allow a context
		switch. */
		return;
	}

	/* Find the highest priority queue that contains ready tasks. */
	while( listLIST_IS_EMPTY( &( pxReadyTasksLists[ ucTopReadyPriority ] ) ) )
	{
		--ucTopReadyPriority;
	}

	/* listGET_OWNER_OF_NEXT_ENTRY walks through the list, so the tasks of the
	same priority get an equal share of the processor time. */
	listGET_OWNER_OF_NEXT_ENTRY( pxCurrentTCB, &( pxReadyTasksLists[ ucTopReadyPriority ] ) );
	vWriteTraceToBuffer();
}
/*-----------------------------------------------------------*/

void vTaskPlaceOnEventList( xList *pxEventList, portTickType xTicksToWait ) reentrant
{
portTickType xTimeToWake;

	/* THIS FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED OR THE
	SCHEDULER SUSPENDED. */

	/* Place the event list item of the TCB in the appropriate event list.
	This is placed in the list in priority order so the highest priority task
	is the first to be woken by the event. */
	vListInsert( ( xList * ) pxEventList, ( xListItem * ) &( pxCurrentTCB->xEventListItem ) );

	/* Calculate the time at which the task should be woken if the event does
	not occur.  This may overflow but this doesn't matter. */
	xTimeToWake = xTickCount + xTicksToWait;

	/* We must remove ourselves from the ready list before adding ourselves
	to the blocked list as the same list item is used for both lists.  We have
	exclusive access to the ready lists as the scheduler is locked. */
	vListRemove( ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );

	listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xGenericListItem ), xTimeToWake );

	if( xTimeToWake < xTickCount )
	{
		/* Wake time has overflowed.  Place this item in the overflow list. */
		vListInsert( ( xList * ) pxOverflowDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
	}
	else
	{
		/* The wake time has not overflowed, so we can use the current block list. */
		vListInsert( ( xList * ) pxDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
	}
}
/*-----------------------------------------------------------*/

signed portCHAR cTaskRemoveFromEventList( const xList *pxEventList ) reentrant
{
tskTCB *pxUnblockedTCB;

	/* THIS FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED OR THE
	SCHEDULER SUSPENDED.  It can also be called from within an ISR. */

	/* The event list is sorted in priority order, so we can remove the 
	first in the list, remove the TCB from the delayed list, and add
	it to the ready list. 
	
	If an event is for a queue that is locked then this function will never
	get called - the lock count on the queue will get modified instead.  This
	means we can always expect exclusive access to the event list here. */
	pxUnblockedTCB = ( tskTCB * ) listGET_OWNER_OF_HEAD_ENTRY( pxEventList );
	vListRemove( &( pxUnblockedTCB->xEventListItem ) );

	if( ucSchedulerSuspended == ( unsigned portCHAR ) pdFALSE )
	{
		vListRemove( &( pxUnblockedTCB->xGenericListItem ) );
		prvAddTaskToReadyQueue( pxUnblockedTCB );
	}
	else
	{
		/* We cannot access the delayed or ready lists, so will hold this
		task pending until the scheduler is resumed. */
		vListInsertEnd( ( xList * ) &( xPendingReadyList ), &( pxUnblockedTCB->xEventListItem ) );
	}

	if( pxUnblockedTCB->ucPriority > pxCurrentTCB->ucPriority )
	{
		/* Return true if the task removed from the event list has
		a higher priority than the calling task.  This allows
		the calling task to know if it should force a context 
		switch now. */
		return ( signed portCHAR ) pdTRUE;
	}
	else
	{
		return ( signed portCHAR ) pdFALSE;
	}
}





/*-----------------------------------------------------------
 * The Idle task.
 *----------------------------------------------------------*/

static void prvIdleTask( void *pvParameters ) reentrant
{
	/* Stop warnings. */
	pvParameters = pvParameters;

	for( ;; )
	{
		/* See if any tasks have been deleted. */
		prvCheckTasksWaitingTermination();

		if( sUsingPreemption == pdFALSE )
		{
			/* If we are not using preemption we keep forcing a task switch to
			see if any other task has become available.  If we are using 
			preemption we don't need to do this as any task becoming available
			will automatically get the processor anyway. */
			taskYIELD();	
		}
	}
} /*lint !e715 pvParameters is not accessed but all task functions require the same prototype. */







/*-----------------------------------------------------------
 * File private functions documented at the top of the file.
 *----------------------------------------------------------*/



static void prvInitialiseTCBVariables( tskTCB *pxTCB, unsigned portSHORT usStackDepth, const signed portCHAR * const pcName, unsigned portCHAR ucPriority ) reentrant
{
	pxTCB->usStackDepth = usStackDepth;

	/* Make sure the name is not too long before copying it into the TCB. */
	if( strlen( pcName ) < ( unsigned portSHORT ) tskMAX_TASK_NAME_LEN )
	{
		portENTER_CRITICAL();
			strcpy( pxTCB->pcTaskName, pcName );
		portEXIT_CRITICAL();
	}
	else
	{
		portENTER_CRITICAL();
			strncpy( pxTCB->pcTaskName, pcName, ( unsigned portSHORT ) tskMAX_TASK_NAME_LEN );
		portEXIT_CRITICAL();
		pxTCB->pcTaskName[ ( unsigned portSHORT ) tskMAX_TASK_NAME_LEN - ( unsigned portSHORT ) 1 ] = '\0';
	}

	/* This is used as an array index so must ensure it's not too large. */
	if( ucPriority >= ( unsigned portCHAR ) portMAX_PRIORITIES )
	{
		ucPriority = ( unsigned portCHAR ) portMAX_PRIORITIES - ( unsigned portCHAR ) 1;
	}
	pxTCB->ucPriority = ucPriority;

	vListInitialiseItem( &( pxTCB->xGenericListItem ) );
	vListInitialiseItem( &( pxTCB->xEventListItem ) );

	/* Set the pxTCB as a link back from the xListItem.  This is so we can get 
	back to	the containing TCB from a generic item in a list. */
	listSET_LIST_ITEM_OWNER( &( pxTCB->xGenericListItem ), pxTCB );

	/* Event lists are always in priority order. */
	listSET_LIST_ITEM_VALUE( &( pxTCB->xEventListItem ), ( portTickType ) ucPriority );
	listSET_LIST_ITEM_OWNER( &( pxTCB->xEventListItem ), pxTCB );
}
/*-----------------------------------------------------------*/

static portSHORT prvInitialiseTaskLists( void ) reentrant
{
register unsigned portCHAR ucPriority;
portSHORT sReturn;

	for( ucPriority = ( unsigned portCHAR) 0; ucPriority < ( unsigned portCHAR ) portMAX_PRIORITIES; ucPriority++ )
	{
		vListInitialise( ( xList * ) &( pxReadyTasksLists[ ucPriority ] ) );
	}

	vListInitialise( ( xList * ) &xDelayedTaskList1 );
	vListInitialise( ( xList * ) &xDelayedTaskList2 );
	vListInitialise( ( xList * ) &xPendingReadyList );

	#if( INCLUDE_vTaskDelete == 1 )
	{
		vListInitialise( ( xList * ) &xTasksWaitingTermination );
	}
	#endif

	#if( INCLUDE_vTaskSuspend == 1 )
	{
		vListInitialise( ( xList * ) &xSuspendedTaskList );
	}
	#endif

	/* Start with pxDelayedTaskList using list1 and the pxOverflowDelayedTaskList 
	using list2. */
	pxDelayedTaskList = &xDelayedTaskList1;
	pxOverflowDelayedTaskList = &xDelayedTaskList2;

	/* Add the idle task at the lowest priority. */
	sReturn = sTaskCreate( prvIdleTask, ( const portCHAR * const ) "IDLE", tskIDLE_STACK_SIZE, ( void * ) NULL, tskIDLE_PRIORITY, ( xTaskHandle * ) NULL );

	return sReturn;
}
/*-----------------------------------------------------------*/

static void prvCheckTasksWaitingTermination( void ) reentrant
{							
	#if( INCLUDE_vTaskDelete == 1 )
	{				
		portSHORT sListIsEmpty;

		vTaskSuspendAll();
			sListIsEmpty = listLIST_IS_EMPTY( &xTasksWaitingTermination );
		cTaskResumeAll();

		if( !sListIsEmpty )
		{
			tskTCB *pxTCB;

			portENTER_CRITICAL();
			{			
				pxTCB = ( tskTCB * ) listGET_OWNER_OF_HEAD_ENTRY( ( ( xList * ) &xTasksWaitingTermination ) );
				vListRemove( &( pxTCB->xGenericListItem ) );
				--usCurrentNumberOfTasks;
			}
			portEXIT_CRITICAL();

			prvDeleteTCB( pxTCB );
		}
	}
	#endif
}
/*-----------------------------------------------------------*/

static tskTCB *prvAllocateTCBAndStack( unsigned portSHORT usStackDepth ) reentrant
{
tskTCB *pxNewTCB;

	/* Allocate space for the TCB.  Where the memory comes from depends on
	the implementation of the port malloc function. */
	pxNewTCB = ( tskTCB * ) pvPortMalloc( sizeof( tskTCB ) );

	if( pxNewTCB != NULL )
	{
		/* Allocate space for the stack used by the task being created.  
		The base of the stack memory stored in the TCB so the task can 
		be deleted later if required. */
		pxNewTCB->pxStack = ( portSTACK_TYPE * ) pvPortMalloc( usStackDepth * sizeof( portSTACK_TYPE ) );

		if( pxNewTCB->pxStack == NULL )
		{
			/* Could not allocate the stack.  Delete the allocated TCB. */
			vPortFree( pxNewTCB );			
			pxNewTCB = NULL;			
		}		
		else
		{
			/* Just to help debugging. */
			memset( pxNewTCB->pxStack, tskSTACK_FILL_BYTE, usStackDepth * sizeof( portSTACK_TYPE ) );
		}
	}

	return pxNewTCB;
}
/*-----------------------------------------------------------*/

#if( USE_TRACE_FACILITY == 1 )

	static void prvListTaskWithinSingleList( signed portCHAR *pcWriteBuffer, xList *pxList, signed portCHAR cStatus )reentrant
	{
	volatile tskTCB *pxNextTCB, *pxFirstTCB;
	static signed portCHAR pcStatusString[ 50 ];
	unsigned portSHORT usStackRemaining;

		/* Write the details of all the TCB's in pxList into the buffer. */
		listGET_OWNER_OF_NEXT_ENTRY( pxFirstTCB, pxList );
		do
		{
			listGET_OWNER_OF_NEXT_ENTRY( pxNextTCB, pxList );
			usStackRemaining = usPortCheckFreeStackSpace( ( unsigned portCHAR * ) pxNextTCB->pxStack, tskSTACK_FILL_BYTE );
			sprintf( pcStatusString, "%s\t\t%c\t%u\t%u\t%d\r\n", pxNextTCB->pcTaskName, cStatus, pxNextTCB->ucPriority, usStackRemaining, pxNextTCB->ucTCBNumber );
			strcat( pcWriteBuffer, pcStatusString );

		} while( pxNextTCB != pxFirstTCB );
	}

#endif
/*-----------------------------------------------------------*/

#if( ( INCLUDE_vTaskDelete == 1 ) || ( INCLUDE_vTaskCleanUpResources == 1 ) )

	static void prvDeleteTCB( tskTCB *pxTCB ) reentrant
	{
		/* Free up the memory allocated by the scheduler for the task.  It is up to
		the task to free any memory allocated at the application level. */
		vPortFree( pxTCB->pxStack );
		vPortFree( pxTCB );
	}

#endif

void prvGetCurrentTCB_XBP() reentrant
{
	pxCurrentTCB->pxTopOfStack = C_XBP;
}


void prvSetCurrentTCB_XBP() reentrant
{
	C_XBP=pxCurrentTCB->pxTopOfStack;
}




