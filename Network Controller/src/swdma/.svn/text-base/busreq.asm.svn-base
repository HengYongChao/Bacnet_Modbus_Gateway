/*
 *********************************************************************************
 *     Copyright (c) 2006   ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 *********************************************************************************
 */
/*================================================================================
 * Module Name : busreq.asm
 * Purpose     : This file handles the bus request interrupt.
 * Author      : Robin Lee
 * Date        : 2005-03-31
 * Notes       :
 * $Log: busreq.asm,v $
 * Revision 1.1  2006/05/12 14:24:19  robin6633
 * no message
 *
 * Revision 1.1.1.1  2006/02/23 00:55:10  borbin
 * no message
 *
 *================================================================================
 */
$NOMOD51

#include <REG80390.H>

NAME	BUSREQ

?PR?BusReqISR?BUSREQ SEGMENT CODE      AT 3000H
	PUBLIC	BusReqISR
	PUBLIC	CheckBusReq
; /***
; BusReqISR : Handle bus request interrupt at INT2
; ***/
CSEG	AT	0003BH
	LJMP	BusReqISR
	RSEG	?PR?BusReqISR?BUSREQ
	USING	0
BusReqISR:
	PUSH     ACC
	/* Grant to release bus */
	ORL  	DBAR,#80H
CheckBusReq:
	/* Polling the BUS_REQ bit */
	MOV	A, DBAR
	JB	0xE0.0, CheckBusReq
	POP	ACC
	RETI

	END

