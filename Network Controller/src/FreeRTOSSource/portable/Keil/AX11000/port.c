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

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the Cygnal port.
 *----------------------------------------------------------*/
//#pragma SRC	
/* Standard includes. */
#include <string.h>

/* Scheduler includes. */
#include "projdefs.h"
#include "portable.h"
#include "task.h"
#include "queue.h"
#include "mstimer.h"
#include "interrupt.h"
#include "dma.h"

#include "hsuart.h"
#include "uart.h"
#include "../../../../USB/ch375_com.h"
#include "../../../../gsm/gsm.h"
#include "../include/mstp.h"

U8_T siltime = 0;
//U8_T frame_gap = 0;
BOOL timegasflag = 0;
/* Constants required to setup timer 2 to produce the RTOS tick. */
//#define portCLOCK_DIVISOR				( ( unsigned portLONG ) 12 )
//#define portMAX_TIMER_VALUE				( ( unsigned portLONG ) 0xffff )
//#define portENABLE_TIMER				( ( unsigned portCHAR ) 0x04 )
//#define portTIMER_2_INTERRUPT_ENABLE	( ( unsigned portCHAR ) 0x20 )

/* The value used in the IE register when a task first starts. */
#define portGLOBAL_INTERRUPT_BIT	( ( portSTACK_TYPE ) 0x80 )

/* The value used in the PSW register when a task first starts. */
#define portINITIAL_PSW				( ( portSTACK_TYPE ) 0x00 )

/* Macro to clear the timer 2 interrupt flag. */
#define portCLEAR_INTERRUPT_FLAG()	{					\
										EINT5 = 0;		\
										EIF &= ~INT5F;	\
										EINT5 = 1;		\
									}
											
/* Used during a context switch to store the size of the stack being copied
to or from XRAM. */
//data static unsigned portCHAR ucStackBytes;
//data  unsigned portCHAR ucStackBytes;

/* Used during a context switch to point to the next byte in XRAM from/to which
a RAM byte is to be copied. */
//xdata static portSTACK_TYPE * data pxXRAMStack;
//static portSTACK_TYPE xdata * data pxXRAMStack;

/* Used during a context switch to point to the next byte in RAM from/to which
an XRAM byte is to be copied. */
//data static portSTACK_TYPE * data pxRAMStack;
//static  portSTACK_TYPE data * data pxRAMStack;

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
//typedef void tskTCB;
//extern volatile tskTCB * volatile pxCurrentTCB;

void LoadCtx() reentrant;   /* Save the current working registers to stack, defined in OS_CPU_A.ASM */
extern INT8U xdata * data C_XBP, TICK_INT;


/*
 * Setup the hardware to generate an interrupt off timer 2 at the required 
 * frequency.
 */
static void prvSetupTimerInterrupt( void );


/* 
 * See header file for description. 
 */
portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters ) reentrant
{
    portSTACK_TYPE * stk;

    stk    = (portSTACK_TYPE *) pxTopOfStack;        /* Load stack pointer                                      */

	stk				-= sizeof(void *);		/* Save the pvParameters to external stack */
	*(void**)stk	 = pvParameters;        /*                               */

	stk				-= sizeof(INT16U);      					/* The value should be loaded to PC    */
	*(INT16U*)stk	 = (INT16U) pxCode;       					/* next time when this task is running */

	*--stk	 		 = (portSTACK_TYPE )(((INT32U) pxCode>>16)+0x7F);      /* Third byte of PC for dallas 390 */

/* Following is the registers pushed into hardware stack */
	*--stk			 = 'A';                 /* ACC */
	*--stk			 = 'B';                 /* B   */
	*--stk			 = 'X';                 /* DPX */
	*--stk			 = 'H';                 /* DPH */
	*--stk			 = 'L';                 /* DPL */
//	*--stk			 = 'X';                 /* DPX1 for second DPTR */
//	*--stk			 = 'H';                 /* DPH1 for second DPTR */
//	*--stk			 = 'L';                 /* DPL1 for second DPTR */
//	*--stk			 = DPS;                 /* DPS for second DPTR */
	*--stk			 = PSW;					/* PSW */
	*--stk			 = 0;                   /* R0  */
/*
	*--stk			 = 1;                   // should be R1
	*--stk			 = 2;                   // should be R2
	*--stk			 = 3;                   // should be R3
*/
	stk				-= sizeof(void *);      /* Keil C uses R1,R2,R3 to pass the */
	*(void**)stk	 = pvParameters;                  /* arguments of functions.          */

	*--stk			 = 4;                   /* R4  */
	*--stk			 = 5;                   /* R5  */
	*--stk			 = 6;                   /* R6  */
	*--stk			 = 7;                   /* R7  */
/* Following is the registers pushed into hardware stack manually to support the dallas 390 */
    *--stk           = 0x80;                /* IE, EA is enabled  */

/*
    Next is calculating the hardware stack pointer.
*/
    *--stk			 = (INT8U) portSTACK_START-1      /* Initial value when main was called    */
	                   +1                   /* IE */
	                   +8                   /* R0-R7, eight registers was saved      */
                       +5                   /* ACC, B, DPH, DPL, PSW, five registers */
                       +1                   /* Dallas 390 extra registers DPX1 */
//                       +4                   /* Dallas 390 extra registers for second DPTR - DPL1 DPH1 DPX1 DPS */
                       +sizeof(INT16U)      /* The PC value to be loaded             */
                       +sizeof(INT8U)       /* The third byte of PC value to be loaded for dallas 390  */
					   ;
    return ((void *)stk);

}

/* 
 * See header file for description. 
 */
portSHORT sPortStartScheduler( portSHORT sUsePreemption ) reentrant
{
	/* Stop compiler warnings.  This port uses a constant defined in
	portmacro.h to specify whether or not preemption is used. */
	sUsePreemption = sUsePreemption;

	/* Setup timer 2 to generate the RTOS tick. */
	prvSetupTimerInterrupt();	

    prvSetCurrentTCB_XBP();
	LoadCtx();
										/* Should never get here! */
	return pdTRUE;
}

/*-----------------------------------------------------------*/

void vPortEndScheduler(void) reentrant
{

	/* Not implemented for this port. */
}
/*-----------------------------------------------------------*/


/**********************************************************************************************************
* C_OSCtxSw is the c part of OSCtxSw.
* When control passes to this function, the processor registers have been saved in external stack
***********************************************************************************************************/
void vPortContextSwitch(void) reentrant
{

/*	Save processor registers; DONE in the OSCtxSw part in OS_CPU_ASM.ASM                                  */

/*	Save the current task's stack pointer into the current task's OS_TCB:  
		prvGetCurrentTCB_XBP();
	Call vTaskSwitchContext();                                    
	Get the stack pointer of the task to resume:                           
		prvSetCurrentTCB_XBP;
	Restore all processor registers from the new task's stack;             
	Execute a return from interrupt instruction;                           */
    prvGetCurrentTCB_XBP();
    
	vTaskSwitchContext();

    prvSetCurrentTCB_XBP();
    LoadCtx();

}


INT8U data SaveSP;

void OSIntCtxSw(void) reentrant
{

	EA=0;
    SP=SaveSP;

    prvSetCurrentTCB_XBP();

#pragma ASM
	EXTRN   CODE(_?KCOSCtxSw)
	MOV		A, #BYTE0( _?KCOSCtxSw)
	PUSH	ACC
	MOV		A, #BYTE1(_?KCOSCtxSw)
	PUSH	ACC
	MOV		A, #BYTE2(_?KCOSCtxSw)
	PUSH	ACC
	RETI
#pragma ENDASM

}


void vIntPortContextSwitch(void) reentrant
{

/*	Save processor registers; DONE in the OSCtxSw part in OS_CPU_ASM.ASM                                  */

/*	Save the current task's stack pointer into the current task's OS_TCB:  
		prvGetCurrentTCB_XBP();
	Call vTaskSwitchContext();                                    
	Get the stack pointer of the task to resume:                           
		prvSetCurrentTCB_XBP;
	Restore all processor registers from the new task's stack;             
	Execute a return from interrupt instruction;                           */
    prvGetCurrentTCB_XBP();

	if ( TICK_INT == 1 )
	{
		vTaskIncrementTick();
		TICK_INT = 0;
	}
	vTaskSwitchContext();
		
	portCLEAR_INTERRUPT_FLAG();

    prvSetCurrentTCB_XBP();
    LoadCtx();
	return;

}

/*-----------------------------------------------------------*/

#if portUSE_PREEMPTION == 1

/*-----------------------------------------------------------*/

void vTimer2ISR( void ) interrupt 10
{
	unsigned portCHAR isr;
#pragma ASM
		PUSH IE
#pragma ENDASM						   
		isr = EA;
		EA = 0;
		if(uart2_timeout)
			uart2_timeout--;
		if(uart1_timeout)
			uart1_timeout--;
		if(uart0_timeout)
			uart0_timeout--;
		if(USB_timeout)
			USB_timeout--;
		if(gsm_timeout)
			gsm_timeout--;
	


		siltime++;
		if(siltime >= 1){
		 	siltime = 0;
			SilenceTime += 10;
			}
		

//		SilenceTime++;

//		P1 = ~P1;

		TICK_INT = 1;
		SaveSP=SP;
        prvGetCurrentTCB_XBP();
		EA = isr;

		OSIntCtxSw();
}

#endif

/*-----------------------------------------------------------*/
static void prvSetupTimerInterrupt( void )
{
	/* using MS_TIMER */
	U8_T XDATA	temp[2];

	/* set software timer */
	temp[1] = (U8_T)SWTIMER_INTERVAL;
	temp[0] = (U8_T)(SWTIMER_INTERVAL >> 8) + SWTIMER_START + SWTIMER_INT_ENABLE;
	DMA_WriteReg(SWTIMER_REG, temp, 2);

	EXTINT5(ON);	/* Enable INT5 interrupt for software timer. */

}

#if ( configUSE_TICK_HOOK == 1 )
void vApplicationTickHook( void )
{
}
#endif
