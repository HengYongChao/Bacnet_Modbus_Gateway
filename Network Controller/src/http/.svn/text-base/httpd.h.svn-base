/*
 ******************************************************************************
 *     Copyright (c) 2006	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
/*=============================================================================
 * Module Name: httpd.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: httpd.h,v $
 * Revision 1.1.1.1  2006/06/20 05:50:28  borbin
 * no message
 *
 * Revision 1.1.1.1  2006/02/23 00:55:10  borbin
 * no message
 *
 *=============================================================================
 */

#ifndef __HTTPD_H__
#define __HTTPD_H__

/* INCLUDE FILE DECLARATIONS */
#include "types.h"

/* NAMING CONSTANT DECLARATIONS */

#define HTTP_SERVER_PORT	 6001

#define MAX_HTTP_CONNECT		8

#define HTTP_STATE_FREE			0
#define HTTP_STATE_RESERVED		1
#define HTTP_STATE_ACTIVE		2
#define HTTP_STATE_SEND_HEADER	3
#define HTTP_STATE_SEND_DATA	4
#define HTTP_STATE_SEND_FINAL	5
#define HTTP_STATE_SEND_NONE	6

#define HTTP_CMD_UNKNOW			0
#define HTTP_CMD_GET			1
#define HTTP_CMD_POST			2

#define HTTP_POST_SUCCESS		0
#define HTTP_POST_FAILURE		1
#define HTTP_POST_CANCEL		2
#define HTTP_POST_CONTINUE		0xff

#define MAX_POST_COUNT			20

#define MAX_DIVIDE_NUM			25

/* TYPE DECLARATIONS */
typedef struct _FILE_DIVIDE
{
	U8_T	Fragment;
	U8_T	CurIndex;
	U8_T	PadFlag;
	U8_T*	PData;
	U16_T	LeftLen;
	U16_T	Offset[MAX_DIVIDE_NUM];
	U8_T	RecordIndex[MAX_DIVIDE_NUM];
	U8_T	PostType[MAX_DIVIDE_NUM];
	U8_T	SetFlag[MAX_DIVIDE_NUM]; /* for radio and select */

} FILE_DIVIDE;

/*-------------------------------------------------------------*/
typedef struct _HTTP_SERVER_CONN
{
	U32_T	Ip;
	U16_T	Port;
	U8_T	State;
	U8_T	TcpSocket;
	U16_T	Timer;
	U8_T	FileId;

	FILE_DIVIDE	Divide;

} HTTP_SERVER_CONN;

/*-------------------------------------------------------------*/

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void HTTP_Init(void);
U8_T HTTP_NewConn(U32_T XDATA*, U16_T, U8_T);
void HTTP_Event(U8_T, U8_T);
void HTTP_Receive(U8_T XDATA*, U16_T, U8_T);

/* for debug */
void HTTP_Debug(void);


#endif /* End of __HTTPD_H__ */


/* End of httpd.h */
