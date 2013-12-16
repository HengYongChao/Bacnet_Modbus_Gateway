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
Changes from V1.01

	+ More use of 8bit data types.
	+ Function name prefixes changed where the data type returned has changed.

Changed from V2.0.0

	+ Added the queue locking mechanism and make more use of the scheduler
	  suspension feature to minimise the time interrupts have to be disabled
	  when accessing a queue.

Changed from V2.2.0

	+ Explicit use of 'signed' qualifier on portCHAR types added.
*/

#include <stdlib.h>
#include <string.h>
#include "projdefs.h"
#include "portable.h"
#include "errors.h"
#include "task.h"
#include "list.h"

/*-----------------------------------------------------------
 * PUBLIC LIST API documented in list.h
 *----------------------------------------------------------*/

/* Constants used with the cRxLock and cTxLock structure members. */
#define queueUNLOCKED	( ( signed portCHAR ) -1 )

/*
 * Definition of the queue used by the scheduler.
 * Items are queued by copy, not reference.
 */
typedef struct QueueDefinition
{
	signed portCHAR *pcHead;				/*< Points to the beginning of the queue storage area. */
	signed portCHAR *pcTail;				/*< Points to the byte at the end of the queue storage area.  Once more byte is allocated than necessary to store the queue items, this is used as a marker. */

	signed portCHAR *pcWriteTo;				/*< Points to the free next place in the storage area. */
	signed portCHAR *pcReadFrom;			/*< Points to the last place that a queued item was read from. */

	xList xTasksWaitingToSend;				/*< List of tasks that are blocked waiting to post onto this queue.  Stored in priority order. */
	xList xTasksWaitingToReceive;			/*< List of tasks that are blocked waiting to read from this queue.  Stored in priority order. */

	unsigned portCHAR ucMessagesWaiting;	/*< The number of items currently in the queue. */
	unsigned portCHAR ucLength;				/*< The length of the queue defined as the number of items it will hold, not the number of bytes. */
	unsigned portCHAR ucItemSize;			/*< The size of each items that the queue will hold. */

	signed portCHAR cRxLock;				/*< Stores the number of items received from the queue (removed from the queue) while the queue was locked.  Set to queueUNLOCKED when the queue is not locked. */
	signed portCHAR cTxLock;				/*< Stores the number of items transmitted to the queue (added to the queue) while the queue was locked.  Set to queueUNLOCKED when the queue is not locked. */
} xQUEUE;
/*-----------------------------------------------------------*/

/*
 * Inside this file xQueueHandle is a pointer to a xQUEUE structure.
 * To keep the definition private the API header file defines it as a
 * pointer to void. 
 */
typedef xQUEUE * xQueueHandle;

/*
 * Prototypes for public functions are included here so we don't have to
 * include the API header file (as it defines xQueueHandle differently).  These
 * functions are documented in the API header file. 
 */
xQueueHandle xQueueCreate( unsigned portCHAR ucQueueLength, unsigned portCHAR ucItemSize ) reentrant;
signed portCHAR cQueueSend( xQueueHandle xQueue, const void * pvItemToQueue, portTickType xTicksToWait ) reentrant;
unsigned portCHAR ucQueueMessagesWaiting( xQueueHandle pxQueue ) reentrant;
void vQueueDelete( xQueueHandle xQueue ) reentrant;
signed portCHAR cQueueSendFromISR( xQueueHandle pxQueue, const void *pvItemToQueue, signed portCHAR cTaskPreviouslyWoken ) reentrant;
signed portCHAR cQueueReceive( xQueueHandle pxQueue, void *pcBuffer, portTickType xTicksToWait ) reentrant;
signed portCHAR cQueueReceiveFromISR( xQueueHandle pxQueue, void *pcBuffer, signed portCHAR *pcTaskWoken ) reentrant;

#ifdef KEIL_AX11000
/*
 * Mark a queue as locked.  Locking a queue prevents an ISR from 
 * accessing the queue event lists. 
 */
static void prvLockQueue( xQueueHandle pxQueue ) reentrant;
#endif

/* 
 * Unlocks a queue locked by a call to prvLockQueue.  Locking a queue does not 
 * prevent an ISR from adding or removing items to the queue, but does prevent 
 * an ISR from removing tasks from the queue event lists.  If an ISR finds a 
 * queue is locked it will instead increment the appropriate queue lock count 
 * to indicate that a task may require unblocking.  When the queue in unlocked
 * these lock counts are inspected, and the appropriate action taken.
 */
static signed portCHAR prvUnlockQueue( xQueueHandle pxQueue ) reentrant;

/*
 * Uses a critical section to determine if there is any data in a queue.
 *
 * @return pdTRUE if the queue contains no items, otherwise pdFALSE.
 */
static signed portCHAR prvIsQueueEmpty( const xQueueHandle pxQueue ) reentrant;

/*
 * Uses a critical section to determine if there is any space in a queue.
 *
 * @return pdTRUE if there is no space, otherwise pdFALSE;
 */
static signed portCHAR prvIsQueueFull( const xQueueHandle pxQueue ) reentrant;

/*
 * Macro that copies an item into the queue.  This is done by copying the item
 * byte for byte, not by reference.  Updates the queue state to ensure it's
 * integrity after the copy.
 */
#define prvCopyQueueData( pxQueue, pvItemToQueue )												\
	memcpy( ( void * ) pxQueue->pcWriteTo, pvItemToQueue, ( unsigned ) pxQueue->ucItemSize );	\
	++( pxQueue->ucMessagesWaiting );															\
	pxQueue->pcWriteTo += pxQueue->ucItemSize;													\
	if( pxQueue->pcWriteTo >= pxQueue->pcTail )													\
	{																							\
		pxQueue->pcWriteTo = pxQueue->pcHead;													\
	}																							\

/*-----------------------------------------------------------*/

#ifndef KEIL_AX11000

/*
 * Macro to mark a queue as locked.  Locking a queue prevents an ISR from 
 * accessing the queue event lists. 
 */
#define prvLockQueue( pxQueue )			\
	taskENTER_CRITICAL();				\
		++( pxQueue->cRxLock );			\
		++( pxQueue->cTxLock );			\
	taskEXIT_CRITICAL();				\

/*-----------------------------------------------------------*/
#endif

/*-----------------------------------------------------------
 * PUBLIC QUEUE MANAGEMENT API documented in queue.h
 *----------------------------------------------------------*/

xQueueHandle xQueueCreate( unsigned portCHAR ucQueueLength, unsigned portCHAR ucItemSize ) reentrant
{
xQUEUE *pxNewQueue;
unsigned portSHORT usQueueSizeInBytes;

	/* Allocate the new queue structure. */
	if( ucQueueLength > ( unsigned portCHAR ) 0 )
	{
		pxNewQueue = ( xQUEUE * ) pvPortMalloc( sizeof( xQUEUE ) );
		if( pxNewQueue != NULL )
		{
			/* Create the list of pointers to queue items.  The queue is one byte 
			longer than asked for to make wrap checking easier/faster. */
			usQueueSizeInBytes = ( unsigned portSHORT ) ( ucQueueLength * ucItemSize ) + ( unsigned portSHORT ) 1;

			pxNewQueue->pcHead = ( signed portCHAR * ) pvPortMalloc( usQueueSizeInBytes );
			if( pxNewQueue->pcHead != NULL )
			{
				/* Initialise the queue members as described above where the 
				queue type is defined. */
				pxNewQueue->pcTail = pxNewQueue->pcHead + ( ucQueueLength * ucItemSize );
				pxNewQueue->ucMessagesWaiting = ( unsigned portCHAR ) 0;
				pxNewQueue->pcWriteTo = pxNewQueue->pcHead;
				pxNewQueue->pcReadFrom = pxNewQueue->pcHead + ( ( ucQueueLength - ( unsigned portCHAR ) 1 ) * ucItemSize );
				pxNewQueue->ucLength = ucQueueLength;
				pxNewQueue->ucItemSize = ucItemSize;
				pxNewQueue->cRxLock = queueUNLOCKED;
				pxNewQueue->cTxLock = queueUNLOCKED;

				/* Likewise ensure the event queues start with the correct state. */
				vListInitialise( &( pxNewQueue->xTasksWaitingToSend ) );
				vListInitialise( &( pxNewQueue->xTasksWaitingToReceive ) ); 

				return  pxNewQueue;
			}
			else
			{
				vPortFree( pxNewQueue );
			}
		}
	}

	/* Will only reach here if we could not allocate enough memory or no memory
	was required. */
	return NULL;
}
/*-----------------------------------------------------------*/

signed portCHAR cQueueSend( xQueueHandle pxQueue, const void *pvItemToQueue, portTickType xTicksToWait ) reentrant
{
signed portCHAR cReturn;

	/* Make sure other tasks do not access the queue. */
	vTaskSuspendAll();

	/* It is important that this is the only thread/ISR that modifies the
	ready or delayed lists until cTaskResumeAll() is called.  Places where 
	the ready/delayed lists are modified include:

		+ vTaskDelay() -  Nothing can call vTaskDelay as the scheduler is 
		  suspended, vTaskDelay() cannot be called from an ISR.
		+ vTaskPrioritySet() - Has a critical section around the access.
		+ vTaskSwitchContext() - This will not get executed while the scheduler 
		  is suspended.
		+ prvCheckDelayedTasks() - This will not get executed while the 
		  scheduler is suspended.
		+ sTaskCreate() - Has a critical section around the access.
		+ vTaskResume() - Has a critical section around the access.
		+ cTaskResumeAll() - Has a critical section around the access.
		+ cTaskRemoveFromEventList - Checks to see if the scheduler is 
		  suspended.  If so then the TCB being removed from the event is 
		  removed from the event and added to the xPendingReadyList.
	*/

	/* Make sure interrupts do not access the queue event list. */
	prvLockQueue( pxQueue );

	/* It is important that interrupts to not access the event list of the
	queue being modified here.  Places where the event list is modified
	include:

		+ cQueueSendFromISR().  This checks the lock on the queue to see if
		  it has access.  If the queue is locked then the Tx lock count is 
		  incremented to signify that a task waiting for data can be made ready
		  once the queue lock is removed.  If the queue is not locked then
		  a task can be moved from the event list, but will not be removed
		  from the delayed list or placed in the ready list until the scheduler 
		  is unlocked.  

		+ cQueueReceiveFromISR().  As per cQueueSendFromISR().
	*/
		
	/* If the queue is already full we may have to block. */
	if( prvIsQueueFull( pxQueue ) )
	{
		/* The queue is full - do we want to block or just leave without
		posting? */
		if( xTicksToWait > ( portTickType ) 0 )
		{
			/* We are going to place ourselves on the xTasksWaitingToSend event
			list, and will get woken should the delay expire, or space become
			available on the queue. 
			
			As detailed above we do not require mutual exclusion on the event
			list as nothing else can modify it or the ready lists while we
			have the scheduler suspended and queue locked. 
			
			It is possible that an ISR has removed data from the queue since we
			checked if any was available.  If this is the case then the data
			will have been copied from the queue, and the queue variables 
			updated, but the event list will not yet have been checked to see if
			anything is waiting as the queue is locked. */
			vTaskPlaceOnEventList( &( pxQueue->xTasksWaitingToSend ), xTicksToWait );

			/* Force a context switch now as we are blocked.  We can do
			this from within a critical section as the task we are 
			switching to has its own context.  When we return here (i.e. we
			unblock) we will leave the critical section as normal. 
			
			It is possible that an ISR has caused an event on an unrelated and 
			unlocked queue.  If this was the case then the event list for that 
			queue will have been updated but the ready lists left unchanged -
			instead the readied task will have been added to the pending ready 
			list. */
			taskENTER_CRITICAL();
			{
				/* We can safely unlock the queue and scheduler here as 
				interrupts are disabled.  We must not yield with anything 
				locked, but we can yield from within a critical section.
				
				Tasks that have been placed on the pending ready list cannot
				be tasks that are waiting for events on this queue.  See 
				in comment cTaskRemoveFromEventList(). */
				prvUnlockQueue( pxQueue );

				/* Resuming the scheduler may cause a yield.  If so then there
				is no point yielding again here. */
				if( !cTaskResumeAll() )
				{
					taskYIELD();
				}

				/* Before leaving the critical section we have to ensure
				exclusive access again. */
				vTaskSuspendAll();
				prvLockQueue( pxQueue );				
			}
			taskEXIT_CRITICAL();
		}
	}
		
	/* When we are here it is possible that we unlblocked as space became 
	available on the queue.  It is also possible that an ISR posted to the
	queue since we left the critical section, so it may be that again there
	is no space.  This would only happen if a task and ISR post onto the
	same queue. */
	taskENTER_CRITICAL();
	{
		if( pxQueue->ucMessagesWaiting < pxQueue->ucLength )
		{
			/* There is room in the queue, copy the data into the queue. */			
			prvCopyQueueData( pxQueue, pvItemToQueue );		
			cReturn = ( signed portCHAR ) pdPASS;

			/* Update the TxLock count so prvUnlockQueue knows to check for
			tasks waiting for data to become available in the queue. */
			++( pxQueue->cTxLock );
		}
		else
		{
			cReturn = errQUEUE_FULL;
		}
	}
	taskEXIT_CRITICAL();

	/* We no longer require exclusive access to the queue.  prvUnlockQueue
	will remove any tasks suspended on a receive if either this function 
	or an ISR has posted onto the queue. */
	if( prvUnlockQueue( pxQueue ) )
	{
		/* Resume the scheduler - making ready any tasks that were woken
		by an event while the scheduler was locked.  Resuming the 
		scheduler may cause a yield, in which case there is no point
		yielding again here. */
		if( !cTaskResumeAll() )
		{
			taskYIELD();
		}
	}
	else
	{
		/* Resume the scheduler - making ready any tasks that were woken
		by an event while the scheduler was locked. */
		cTaskResumeAll();
	}

	return cReturn;
}

/*-----------------------------------------------------------*/
//signed portCHAR cQueueSendFromISR( xQueueHandle pxQueue, const void *pvItemToQueue, signed portCHAR cTaskPreviouslyWoken )
signed portCHAR cQueueSendFromISR( xQueueHandle pxQueue, const void *pvItemToQueue, signed portCHAR cTaskPreviouslyWoken ) reentrant
{
	/* Similar to cQueueSend, except we don't block if there is no room in the
	queue.  Also we don't directly wake a task that was blocked on a queue
	read, instead we return a flag to say whether a context switch is required
	or not (i.e. has a task with a higher priority than us been woken by this
	post). */
	if( pxQueue->ucMessagesWaiting < pxQueue->ucLength )
	{
		prvCopyQueueData( pxQueue, pvItemToQueue );

		/* If the queue is locked we do not alter the event list.  This will
		be done when the queue is unlocked later. */
		if( pxQueue->cTxLock == queueUNLOCKED )
		{
			/* We only want to wake one task per ISR, so check that a task has
			not already been woken. */
			if( !cTaskPreviouslyWoken )		
			{
				if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) ) )
				{
					if( cTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToReceive ) ) != ( signed portCHAR ) pdFALSE )
					{
						/* The task waiting has a higher priority so record that a 
						context	switch is required. */
						return pdTRUE;
					}
				}
			}
		}
		else
		{
			/* Increment the lock count so the task that unlocks the queue 
			knows that data was posted while it was locked. */
			++( pxQueue->cTxLock );
		}
	}

	return cTaskPreviouslyWoken;
}
/*-----------------------------------------------------------*/

signed portCHAR cQueueReceive( xQueueHandle pxQueue, void *pcBuffer, portTickType xTicksToWait ) reentrant
{
signed portCHAR cReturn;

	/* This function is very similar to cQueueSend().  See comments within
	cQueueSend() for a more detailed explanation.

	Make sure other tasks do not access the queue. */
	vTaskSuspendAll();

	/* Make sure interrupts do not access the queue. */
	prvLockQueue( pxQueue );

	/* If there are no messages in the queue we may have to block. */
	if( prvIsQueueEmpty( pxQueue ) )
	{
		/* There are no messages in the queue, do we want to block or just
		leave with nothing? */			
		if( xTicksToWait > ( portTickType ) 0 )
		{
			vTaskPlaceOnEventList( &( pxQueue->xTasksWaitingToReceive ), xTicksToWait );
			taskENTER_CRITICAL();
			{
				prvUnlockQueue( pxQueue );
				if( !cTaskResumeAll() )
				{
					taskYIELD();
				}

				vTaskSuspendAll();
				prvLockQueue( pxQueue );			
			}
			taskEXIT_CRITICAL();
		}
	}

	taskENTER_CRITICAL();
	{
		if( pxQueue->ucMessagesWaiting > ( unsigned portCHAR ) 0 )
		{
			pxQueue->pcReadFrom += pxQueue->ucItemSize;
			if( pxQueue->pcReadFrom >= pxQueue->pcTail )
			{
				pxQueue->pcReadFrom = pxQueue->pcHead;
			}
			--( pxQueue->ucMessagesWaiting );
			memcpy( ( void * ) pcBuffer, ( void * ) pxQueue->pcReadFrom, ( unsigned ) pxQueue->ucItemSize );

			/* Increment the lock count so prvUnlockQueue knows to check for
			tasks waiting for space to become available on the queue. */
			++( pxQueue->cRxLock );
			cReturn = ( signed portCHAR ) pdPASS;
		}
		else
		{
			cReturn = ( signed portCHAR ) pdFAIL;
		}
	}
	taskEXIT_CRITICAL();

	/* We no longer require exclusive access to the queue. */
	if( prvUnlockQueue( pxQueue ) )
	{
		if( !cTaskResumeAll() )
		{
			taskYIELD();
		}
	}
	else
	{
		cTaskResumeAll();
	}

	return cReturn;
}
/*-----------------------------------------------------------*/

signed portCHAR cQueueReceiveFromISR( xQueueHandle pxQueue, void *pcBuffer, signed portCHAR *pcTaskWoken ) reentrant
{
signed portCHAR cReturn;

	/* We cannot block from an ISR, so check there is data available. */
	if( pxQueue->ucMessagesWaiting > ( unsigned portCHAR ) 0 )
	{
		/* Copy the data from the queue. */
		pxQueue->pcReadFrom += pxQueue->ucItemSize;
		if( pxQueue->pcReadFrom >= pxQueue->pcTail )
		{
			pxQueue->pcReadFrom = pxQueue->pcHead;
		}
		--( pxQueue->ucMessagesWaiting );
		memcpy( ( void * ) pcBuffer, ( void * ) pxQueue->pcReadFrom, ( unsigned ) pxQueue->ucItemSize );

		/* If the queue is locked we will not modify the event list.  Instead
		we update the lock count so the task that unlocks the queue will know
		that an ISR has removed data while the queue was locked. */
		if( pxQueue->cRxLock == queueUNLOCKED )
		{
			/* We only want to wake one task per ISR, so check that a task has
			not already been woken. */
			if( !( *pcTaskWoken ) )
			{
				if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) ) )
				{
					if( cTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToSend ) ) != ( signed portCHAR ) pdFALSE )
					{
						/* The task waiting has a higher priority than us so
						force a context switch. */
						*pcTaskWoken = ( signed portCHAR ) pdTRUE;
					}
				}
			}
		}
		else
		{
			/* Increment the lock count so the task that unlocks the queue 
			knows that data was removed while it was locked. */
			++( pxQueue->cRxLock );
		}

		cReturn = ( signed portCHAR ) pdPASS;
	}
	else
	{
		cReturn = ( signed portCHAR ) pdFAIL;
	}

	return cReturn;
}
/*-----------------------------------------------------------*/

unsigned portCHAR ucQueueMessagesWaiting( xQueueHandle pxQueue ) reentrant
{
unsigned portCHAR ucReturn;

	taskENTER_CRITICAL();
		ucReturn = pxQueue->ucMessagesWaiting;
	taskEXIT_CRITICAL();

	return ucReturn;
}
/*-----------------------------------------------------------*/

void vQueueDelete( xQueueHandle pxQueue ) reentrant
{
	vPortFree( pxQueue->pcHead );
	vPortFree( pxQueue );
}
/*-----------------------------------------------------------*/

#ifdef KEIL_AX11000
/*
 * Mark a queue as locked.  Locking a queue prevents an ISR from 
 * accessing the queue event lists. 
 */
static void prvLockQueue( xQueueHandle pxQueue ) reentrant
{
	taskENTER_CRITICAL();
	++( pxQueue->cRxLock );
	++( pxQueue->cTxLock );
	taskEXIT_CRITICAL();	
}
#endif
/*-----------------------------------------------------------*/

static signed portCHAR prvUnlockQueue( xQueueHandle pxQueue ) reentrant
{
signed portCHAR cYieldRequired = ( signed portCHAR ) pdFALSE;

	/* THIS FUNCTION MUST BE CALLED WITH THE SCHEDULER SUSPENDED. */

	/* The lock counts contains the number of extra data items placed or 
	removed from the queue while the queue was locked.  When a queue is
	locked items can be added or removed, but the event lists cannot be
	updated. */
	taskENTER_CRITICAL();
	{
		--( pxQueue->cTxLock );

		/* See if data was added to the queue while it was locked. */
		if( pxQueue->cTxLock > queueUNLOCKED )
		{
			pxQueue->cTxLock = queueUNLOCKED;

			/* Data was posted while the queue was locked.  Are any tasks
			blocked waiting for data to become available? */
			if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) ) )
			{
				/* Tasks that are removed from the event list will get added to
				the pending ready list as the scheduler is still suspended. */
				if( cTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToReceive ) ) != ( signed portCHAR ) pdFALSE )
				{
					/* The task waiting has a higher priority so record that a 
					context	switch is required. */
					cYieldRequired = ( signed portCHAR ) pdTRUE;
				}
			}			
		}
	}
	taskEXIT_CRITICAL();

	/* Do the same for the Rx lock. */
	taskENTER_CRITICAL();
	{
		--( pxQueue->cRxLock );

		if( pxQueue->cRxLock > queueUNLOCKED )
		{
			pxQueue->cRxLock = queueUNLOCKED;

			if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) ) )
			{
				if( cTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToSend ) ) != ( signed portCHAR ) pdFALSE )
				{
					cYieldRequired = ( signed portCHAR ) pdTRUE;
				}
			}			
		}
	}
	taskEXIT_CRITICAL();

	return cYieldRequired;
}
/*-----------------------------------------------------------*/

static signed portCHAR prvIsQueueEmpty( const xQueueHandle pxQueue ) reentrant
{
signed portCHAR cReturn;

	taskENTER_CRITICAL();
		cReturn = ( pxQueue->ucMessagesWaiting == ( unsigned portCHAR ) 0 );
	taskEXIT_CRITICAL();

	return cReturn;
}
/*-----------------------------------------------------------*/

static signed portCHAR prvIsQueueFull( const xQueueHandle pxQueue ) reentrant
{
signed portCHAR cReturn;

	taskENTER_CRITICAL();
		cReturn = ( pxQueue->ucMessagesWaiting == pxQueue->ucLength );
	taskEXIT_CRITICAL();

	return cReturn;
}

