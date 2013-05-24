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
 /*============================================================================
 * Module Name: httpd.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: httpd.h,v $
 * no message
 *
 *=============================================================================
 */

#ifndef __HTTPD_H__
#define __HTTPD_H__

/* INCLUDE FILE DECLARATIONS */
#include "types.h"
#include "filesys.h"
/* NAMING CONSTANT DECLARATIONS */
#define HTTP_SERVER_PORT		80 

#define MAX_HTTP_CONNECT		4

/* FILE SYS RECORD INDEX */

#define HTTP_STATE_FREE			0
#define HTTP_STATE_RESERVED		1
#define HTTP_STATE_ACTIVE		2
#define HTTP_STATE_SEND_HEADER	3
#define HTTP_STATE_SEND_DATA	4
#define HTTP_STATE_SEND_FINAL	5
//#define HTTP_STATE_SEND_NONE	6

#define HTTP_CMD_UNKNOW			0
#define HTTP_CMD_GET			1
#define HTTP_CMD_POST			2

#define HTTP_POST_SUCCESS		0
#define HTTP_POST_FAILURE		1
#define HTTP_POST_CANCEL		2
#define HTTP_POST_CONTINUE		0xff

#define MAX_POST_COUNT			20

#define MAX_DIVIDE_NUM			25

#define POST_SETTING			0x01

#define MAX_HTML_CMD_LEN		100

#define MAX_USER_COUNT			1

/* uip */
#define UIP_APPSTATE_SIZE		1

#define MAX_AUTH_POST_VALUE_LEN	16

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
	U8_T	SetFlag[MAX_DIVIDE_NUM];

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
	U8_T	ContinueFlag; /* if 1, the POST packet be divided into two frames by http client */
	U8_T	ContinueFileId;
	
	FILE_DIVIDE	Divide;

} HTTP_SERVER_CONN;

/*-------------------------------------------------------------*/
typedef struct _HTTP_USER_PASSWORD
{
	U8_T	UserName[MAX_AUTH_POST_VALUE_LEN];
	U8_T	PassWord[MAX_AUTH_POST_VALUE_LEN];
	U8_T	UserNameLen;
	U8_T	PassWordLen;
	U8_T	IsAdminFlag;

} HTTP_USER_PWORD;
/*-------------------------------------------------------------*/
typedef struct _HTTP_TEMP_BUF
{
	U8_T	InterFaceID;
	U8_T	PostTable[MAX_POST_COUNT];
	U8_T	PostCnt;
	U8_T	SaveCfgFlag;
	U8_T	SysRebootFlag;
	U8_T	Buf[2][MAX_POST_VALUE_LEN];
	U8_T	NewUserName[MAX_AUTH_POST_VALUE_LEN];
	U8_T	NewUserNameLen;
	U8_T	OldPassWord[MAX_AUTH_POST_VALUE_LEN];
	U8_T	OldPassWordLen;
	U8_T	NewPassWord[MAX_AUTH_POST_VALUE_LEN];
	U8_T	NewPassWordLen;	
	U8_T	CfmPassWord[MAX_AUTH_POST_VALUE_LEN];
	U8_T	CfmPassWordLen;
	
	U8_T	UserName[MAX_AUTH_POST_VALUE_LEN];
	U8_T	UserNameLen;
	U8_T	PassWord[MAX_AUTH_POST_VALUE_LEN];
	U8_T	PassWordLen;
	
	U32_T	AuthenIP[MAX_HTTP_CONNECT];
	
	U8_T	AccessibleIP_EnableFlag;
} HTTP_TEMP_BUF;
/*-------------------------------------------------------------*/

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void HTTP_Task(void);
void HTTP_Init(void);
U8_T HTTP_NewConn(U32_T XDATA*, U16_T, U8_T);
void HTTP_Event(U8_T, U8_T);
void HTTP_Receive(U8_T XDATA*, U16_T, U8_T);

U32_T HTTP_IpAddr2Ulong(U8_T*, U8_T);
U16_T HTTP_Str2Short(U8_T*, U8_T);
U8_T  HTTP_Short2Str(U16_T, U8_T*);
U8_T  HTTP_Ulong2IpAddr(U32_T, U8_T*);
extern HTTP_TEMP_BUF HTTPtemp;

#endif /* End of __HTTPD_H__ */


/* End of httpd.h */
