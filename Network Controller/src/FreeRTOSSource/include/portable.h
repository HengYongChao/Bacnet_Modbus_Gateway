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
 * Portable layer API.  Each function must be defined for each port.
 *----------------------------------------------------------*/

#ifndef PORTABLE_H
#define PORTABLE_H

#include "projdefs.h"
/* Include the macro file relevant to the port being used. */

#ifdef OPEN_WATCOM_INDUSTRIAL_PC_PORT
	#include "..\..\source\portable\owatcom\16bitdos\pc\portmacro.h"
	typedef void ( __interrupt __far *pxISR )();
#endif

#ifdef OPEN_WATCOM_FLASH_LITE_186_PORT
	#include "..\..\source\portable\owatcom\16bitdos\flsh186\portmacro.h"
	typedef void ( __interrupt __far *pxISR )();
#endif

#ifdef GCC_MEGA_AVR
	#include "../portable/GCC/ATMega323/portmacro.h"
#endif

#ifdef IAR_MEGA_AVR
	#include "../portable/IAR/ATMega323/portmacro.h"
#endif

#ifdef BCC_INDUSTRIAL_PC_PORT
	#include "..\portable\BCC\16BitDOS\PC\prtmacro.h"
    typedef void ( __interrupt __far *pxISR )();
#endif

#ifdef BCC_FLASH_LITE_186_PORT
	#include "..\portable\BCC\16BitDOS\flsh186\prtmacro.h"
    typedef void ( __interrupt __far *pxISR )();
#endif

#ifdef MPLAB_PIC18F_PORT
	#include "..\..\source\portable\MPLAB\PIC18F\portmacro.h"
#endif

#ifdef SDCC_CYGNAL
	#include "../../Source/portable/SDCC/Cygnal/portmacro.h"
#endif

#ifdef SDCC_ASIX
	#include "../../Source/portable/SDCC/ASIX/portmacro.h"
#endif

#ifdef GCC_ARM7
	#include "../../Source/portable/GCC/ARM7/portmacro.h"
#endif

#ifdef GCC_MSP430
	#include "../../Source/portable/GCC/MSP430F449/portmacro.h"
#endif

#ifdef KEIL_ARM7
	#include "..\..\Source\portable\Keil\ARM7\portmacro.h"
#endif

#ifdef KEIL_80390
	#include "..\FREERTOSSource\portable\Keil\390\portmacro.h"
#endif

#ifdef SAM7_IAR
	#include "..\..\Source\portable\IAR\AtmelSAM7S64\portmacro.h"
#endif

#ifdef KEIL_AX11000
	#include "..\FREERTOSSource\portable\Keil\AX11000\portmacro.h"
#endif

/*
 * Setup the stack of a new task so it is ready to be placed under the 
 * scheduler control.  The registers have to be placed on the stack in
 * the order that the port expects to find them.
 */
portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters )reentrant;

/*
 * Map to the memory management routines required for the port. 
 */
void *pvPortMalloc( unsigned portSHORT usSize ) reentrant;
void vPortFree( void *pv ) reentrant;
void vPortInitialiseBlocks( void ) reentrant;

/* 
 * Setup the hardware ready for the scheduler to take control.  This generally
 * sets up a tick interrupt and sets timers for the correct tick frequency.
 */
portSHORT sPortStartScheduler( portSHORT sUsePreemption ) reentrant;

/*
 * Undo any hardware/ISR setup that was performed by sPortStartScheduler() so
 * the hardware is left in its original condition after the scheduler stops
 * executing.
 */
void vPortEndScheduler( void ) reentrant;

/*
 * Finds the high water mark of stack usage.  Returns the smallest amount of 
 * free stack that has been available since the task started.
 *
 * THIS FUNCTION IS INTENDED FOR DEBUGGING ONLY, AND SHOULD NOT BE CALLED FROM
 * NORMAL APPLICATION CODE>
 */
unsigned portSHORT usPortCheckFreeStackSpace( const unsigned portCHAR *pucStackByte, unsigned portCHAR ucStackFillByte ) reentrant;

#endif /* PORTABLE_H */

