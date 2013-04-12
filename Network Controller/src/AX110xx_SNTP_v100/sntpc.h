/*
 *********************************************************************************
 *     Copyright (c) 2005	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 *********************************************************************************
 */
 /*============================================================================
 * Module name: sntpc.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: sntpc.h,v $
 * Revision 1.1  2006/08/31 06:52:34  rick
 * no message
 *
 * Revision 1.1.1.1  2006/08/18 05:50:28  eric
 * no message
 *
 *
 *=============================================================================
 */

#ifndef __SNTPC_H__
#define __SNTPC_H__


/* INCLUDE FILE DECLARATIONS */
#include "types.h"

/* NAMING CONSTANT DECLARATIONS */
#define SNTP_SERVER_PORT		123

#define SNTP_MAX_LENGTH			76

/*-------------------------------------------------------------*/
/* NAMING CONSTANT DECLARATIONS */
#define SNTP_STATE_NOTREADY		0
#define SNTP_STATE_INITIAL		1  
#define SNTP_STATE_WAIT			2
#define SNTP_STATE_TIMEOUT		3
#define SNTP_STATE_GET_DONE		4

#define SNTPC_REQUEST_TIMEOUT	(3* SWTIMER_COUNT_SECOND) /* 2 second */
#define SNTPC_MAX_RETRY			6

/* TYPE DECLARATIONS */
typedef struct _sntpheader
{
	U8_T	flags;
	U8_T	stratum;
	U8_T	poll;
	U8_T	precision;
	U32_T	root_delay;
	U32_T	root_dispersion;
	U32_T	reference_ID;
	U32_T	reference_time1;
	U32_T	reference_time2;
	U32_T	originate_time1;
	U32_T	originate_time2;
	U32_T	receive_time1;
	U32_T	receive_time2;
	U32_T	transmit_time1;
	U32_T	transmit_time2;

} SNTPHeader;


typedef struct _timeinfo
{
	SNTPHeader	*sntpcPktPtr;
	U32_T		timestamp;
	U32_T		second_remain;
	U32_T		day_total;
	U16_T		YY;
	U8_T		MM;
	U16_T		DD;
	S16_T		DD_r;
	U8_T		HH;
	U8_T		MI;
	U16_T		MI_r;
	U8_T		SS;
} TimeInfo;

typedef struct _SNTPC_CONN
{
	U8_T	State;
	U8_T	UdpSocket;
	U32_T	ServerIp;

} SNTPC_CONN;

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void SNTPC_Init(void);
void SNTPC_Event(U8_T, U8_T);
void SNTPC_Receive(U8_T XDATA*, U16_T, U8_T);
U8_T* SNTP_GetTime(void);
U8_T SNTPC_Start(S16_T ,U32_T);
void SNTPC_Stop(void);
U8_T SNTPC_GetState(void);


/* for debug */
void SNTPC_Debug(void);

#endif /* __SNTPC_H__ */

