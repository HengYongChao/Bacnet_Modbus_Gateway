/*
 *********************************************************************************
 *     Copyright (c) 2005   ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 *********************************************************************************
 */

#ifndef FLAG_H
#define FLAG_H

typedef xQueueHandle xFlagHandle;


#define FLAG_QUEUE_LENGTH			( ( unsigned portCHAR ) 1 )
#define FLAG_QUEUE_ITEM_LENGTH		( sizeof( unsigned portCHAR ) )

#define	STOEInt		1
#define	MACInt		2
#define	TIMERInt	4

#define vFlagCreate( xFlag )	xFlag = xQueueCreate( ( unsigned portCHAR ) 100, FLAG_QUEUE_ITEM_LENGTH );

unsigned portCHAR cFlagPend( xFlagHandle xFlag , portTickType xBlockTime) reentrant;

void cFlagSendFromISR( xFlagHandle xFlag, unsigned portCHAR xEvent ) reentrant;

#endif