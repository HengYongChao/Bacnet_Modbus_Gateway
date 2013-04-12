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

#ifndef PORTMACRO_H
#define PORTMACRO_H

#include <conio.h>

/*-----------------------------------------------------------
 * Port specific definitions for the Flashlite 186 port.
 *----------------------------------------------------------*/

/* These are the only definitions that can be modified!. */

#define portTICK_RATE_HZ		( ( portTickType ) 1000 )
#define portMAX_PRIORITIES		( ( unsigned portSHORT ) 6 )
#define portMINIMAL_STACK_SIZE	( ( unsigned portSHORT ) 128 )
#define portTOTAL_HEAP_SIZE		( ( unsigned portSHORT ) ( 32 * 1024 ) )

/* Set the following definitions to 1 to include the component, or zero
to exclude the component. */

/* Include/exclude the stated API function. */
#define INCLUDE_vTaskPrioritySet		0
#define INCLUDE_ucTaskPriorityGet		0
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1


/* Use/don't use the trace visualisation. */
#define USE_TRACE_FACILITY				0

/* 
 * The tick count (and times defined in tick count units) can be either a 16bit
 * or a 32 bit value.  See documentation on http://www.FreeRTOS.org to decide
 * which to use.
 */
#define USE_16_BIT_TICKS	1

/*-----------------------------------------------------------
 * Do not modify anything below here. 
 *----------------------------------------------------------*/

#define portCHAR		char
#define portFLOAT		float
#define portDOUBLE		long
#define portLONG		long
#define portSHORT		int
#define portSTACK_TYPE	unsigned portSHORT

#if( USE_16_BIT_TICKS == 1 )
	typedef unsigned portSHORT portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffff
#else
	typedef unsigned portLONG portTickType;
	#define portMAX_DELAY ( portTickType ) 0xffffffff
#endif

/*-----------------------------------------------------------*/

#define portENTER_CRITICAL()			__asm{ pushf }  \
										__asm{ cli 	 }	\
/*-----------------------------------------------------------*/

#define portEXIT_CRITICAL()				__asm{ popf }
/*-----------------------------------------------------------*/

#define portDISABLE_INTERRUPTS()		__asm{ cli }
/*-----------------------------------------------------------*/

#define portENABLE_INTERRUPTS()			__asm{ sti }
/*-----------------------------------------------------------*/

#define portSTACK_GROWTH	( -1 )
/*-----------------------------------------------------------*/

#define portSWITCH_INT_NUMBER 	0x80
#define portYIELD()			__asm{ int portSWITCH_INT_NUMBER } 
/*-----------------------------------------------------------*/

#define portINPUT_BYTE( xAddr )				inp( xAddr )
#define portOUTPUT_BYTE( xAddr, ucValue )	outp( xAddr, ucValue )
#define portINPUT_WORD( xAddr )				inpw( xAddr )
#define portOUTPUT_WORD( xAddr, usValue )	outpw( xAddr, usValue )
/*-----------------------------------------------------------*/

#define portTICK_RATE_MS		( ( portTickType ) 1000 / portTICK_RATE_HZ )		
#define portBYTE_ALIGNMENT      2

/*-----------------------------------------------------------*/
#define portINITIAL_SW		( ( portSTACK_TYPE ) 0x0202 )	/* Start the tasks with interrupts enabled. */

#define inline

#endif /* PORTMACRO_H */

