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
 * Very basic block allocation scheme.  This is tailored exactly for the demo
 * application needs and should be tuned or replaced for any other application.
 *----------------------------------------------------------*/

/* Compiler include files. */
#include <stdlib.h>

/* Scheduler include files. */
#include "projdefs.h"
#include "portable.h"

#define heapSMALL_BLOCK_SIZE		( ( unsigned portSHORT ) 45 )
#define heapLARGE_BLOCK_SIZE		portMINIMAL_STACK_SIZE

/* These are the number of blocks required by the demo application. */
#define heapNUM_SMALL_BLOCKS		( 16 )
#define heapNUM_LARGE_BLOCKS		( 10 )

/* Each block contains the data area and a variable that marks the block as
empty or full. */
typedef struct
{
	unsigned portCHAR ucFull;
	unsigned portCHAR ucBlock[ heapSMALL_BLOCK_SIZE ];
} xSmallBlock;

typedef struct
{
	unsigned portCHAR ucFull;
	unsigned portCHAR ucBlock[ heapLARGE_BLOCK_SIZE ];
} xLargeBlock;

static xSmallBlock xSmallBlocks[ heapNUM_SMALL_BLOCKS ];
static xLargeBlock xLargeBlocks[ heapNUM_LARGE_BLOCKS ];

/*-----------------------------------------------------------*/
void *pvPortMalloc( unsigned portSHORT usSize )
{
void *pv = NULL;
unsigned portCHAR ucBlock;

	portENTER_CRITICAL();
	{
		if( usSize <= heapSMALL_BLOCK_SIZE )
		{
			/* Try to find a block in the list of small blocks. */
			for( ucBlock = 0; ucBlock < heapNUM_SMALL_BLOCKS; ucBlock++ )
			{
				if( xSmallBlocks[ ucBlock ].ucFull == pdFALSE )
				{
					xSmallBlocks[ ucBlock ].ucFull = pdTRUE;
					pv = ( void * ) ( xSmallBlocks[ ucBlock ].ucBlock );
					break;
				}
			}
		}

		/* If the block is too large to be obtained from the pool of small
		blocks, or if a small block could not be found, try to find a block
		in the list of large blocks. */
		if( ( usSize <= heapLARGE_BLOCK_SIZE ) && ( pv == NULL ) )
		{		
			for( ucBlock = 0; ucBlock < heapNUM_LARGE_BLOCKS; ucBlock++ )
			{	
				if( xLargeBlocks[ ucBlock ].ucFull == pdFALSE )
				{
					xLargeBlocks[ ucBlock ].ucFull = pdTRUE;
					pv = ( void * ) ( xLargeBlocks[ ucBlock ].ucBlock );
					break;
				}
			}
		}
	}
	portEXIT_CRITICAL();

	if( pv == NULL )
	{
		/* For debugger break points only. */
		pv = NULL;
	}

	return pv;
}
/*-----------------------------------------------------------*/

void vPortFree( void *pv )
{
	/* The AVR demo application does not use any calls to free(). */
	( void ) pv;
}
/*-----------------------------------------------------------*/

