/*
 ******************************************************************************
 *     Copyright (c) 2006 	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
/*=============================================================================
 * Module Name: filesys.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: filesys.h,v $
 *=============================================================================
 */

#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

/* INCLUDE FILE DECLARATIONS */
#include "types.h"

/* NAMING CONSTANT DECLARATIONS */
#define FILE_ADVSETTING			1
#define FILE_AXJS0			3
#define FILE_BSCSETTING			4
#define FILE_DDNS			5
#define FILE_INDEX			6
#define FILE_JMPINDEX			7
#define FILE_MSGACCERR			8
#define FILE_MSGADVERR			9
#define FILE_MSGAUTHERR			10
#define FILE_MSGAUTHOK			11
#define FILE_MSGBSCERR			12
#define FILE_MSGREBOOT			13
#define FILE_MSGRESTORE			14
#define FILE_MSGSCTERR			15
#define FILE_MSGUNPWOK			16
#define FILE_MSGUPG			17
#define FILE_SECURITY			18

#define MAX_STORE_FILE_NUM	19
#define MAX_FILE_NAME_LEN	30

#define FILE_TYPE_HTML		0
#define FILE_TYPE_BIN		BIT0
#define FILE_TYPE_JS		BIT1
#define FILE_TYPE_CSS		BIT1|BIT0

#define MAX_POST_RECORDS	28
#define MAX_POST_BUF_SUBMIT	3
#define MAX_POST_BUF_TEXT	8
#define MAX_POST_BUF_TAG	0
#define MAX_POST_BUF_RADIO	0
#define MAX_POST_BUF_SELECT	11
#define MAX_POST_NAME_LEN	15
#define MAX_POST_VALUE_LEN	65
#define NORM_POST_VALUE_LEN	16

#define MAX_SELECT_OPTION_NUM	9
#define MAX_RADIO_OPTION_NUM	0

#define POST_TYPE_SUBMIT	1
#define POST_TYPE_TEXT		2
#define POST_TYPE_RADIO		3
#define POST_TYPE_SELECT	4
#define POST_TYPE_TAG   	5

#define RECORD_TEXT_tftps_ip		0
#define RECORD_TEXT_file_name		1
#define RECORD_SELECT_ipchg		4
#define RECORD_SELECT_pswchg		5
#define RECORD_SELECT_dbr		6
#define RECORD_SELECT_data		7
#define RECORD_SELECT_parity		8
#define RECORD_SELECT_stop		9
#define RECORD_SELECT_flow		10
#define RECORD_SELECT_rs485		11
#define RECORD_SELECT_dhcp		12
#define RECORD_TEXT_static_ip		13
#define RECORD_TEXT_mask		14
#define RECORD_TEXT_gateway_ip		15
#define RECORD_SELECT_select_service		16
#define RECORD_TEXT_ddns_name		17
#define RECORD_TEXT_ddns_psd		18
#define RECORD_TEXT_host_name		19
#define RECORD_SELECT_chk_ddns_frey		20
#define RECORD_TEXT_username		21
#define RECORD_TEXT_password		22
#define RECORD_TEXT_new_usn		24
#define RECORD_TEXT_old_psw		25
#define RECORD_TEXT_new_psw		26
#define RECORD_TEXT_cfm_psw		27

/* TYPE DECLARATIONS */
/*-------------------------------------------------------------*/
typedef struct _FILE_MANAGEMEMT
{
	U8_T			Occupy;
	U8_T			FType;
	U8_T			FName[MAX_FILE_NAME_LEN];
	U16_T			FileSize;
	U8_T			*PBuf;
	U8_T			CgiRef;
	void			*CgiCall;

} FILE_MANAGEMEMT;

/*-------------------------------------------------------------*/
typedef struct _POST_RECORD
{
	U8_T			Occupy;
	U8_T			PostType;
	U8_T			Name[MAX_POST_NAME_LEN];
	U8_T			NameLen;
	U8_T			FileIndex;
	U8_T			UpdateSelf;
	void XDATA*		PValue;

} POST_RECORD;

/*-------------------------------------------------------------*/
typedef struct _BUF_SUBMIT
{
	U8_T			Value[NORM_POST_VALUE_LEN];
	U8_T			DefaultVlaueLen;
	U8_T			IsApply;

} BUF_SUBMIT;

/*-------------------------------------------------------------*/
#if (MAX_POST_BUF_RADIO)
typedef struct _BUF_RADIO
{
	U16_T			Offset[MAX_RADIO_OPTION_NUM];
	U8_T			Value[MAX_RADIO_OPTION_NUM][NORM_POST_VALUE_LEN];
	U8_T			Length[MAX_RADIO_OPTION_NUM];
	U8_T			Count;
	U8_T			DefaultSet;
	U8_T			CurrentSet;
	U8_T			UserSet;

} BUF_RADIO;
#endif

/*-------------------------------------------------------------*/
typedef struct _BUF_TEXT
{
	U16_T			Offset;
	U8_T			*CurrValue;
	U8_T			*UserValue;
	U8_T			DefaultLength;
	U8_T			CurrLength;
	U8_T			UserLength;

} BUF_TEXT;

/*-------------------------------------------------------------*/
typedef struct _BUF_TAG
{
	U16_T			Offset;
	U8_T			CurrValue[NORM_POST_VALUE_LEN];
	U8_T			DefaultLength;
	U8_T			CurrLength;

} BUF_TAG;

/*-------------------------------------------------------------*/
#if (MAX_POST_BUF_SELECT)
typedef struct _BUF_SELECT
{
	U16_T			Offset[MAX_SELECT_OPTION_NUM];
	U8_T			Count;
	U8_T			DefaultSet;
	U8_T			CurrentSet;
	U8_T			UserSet;

} BUF_SELECT;
#endif


/*-------------------------------------------------------------*/
 typedef struct {
	U8_T* name;
	U8_T* val;
} entry;


extern entry entries[20];
extern U8_T num_parms;

/*-------------------------------------------------------------*/

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
#if (MAX_STORE_FILE_NUM)
extern FILE_MANAGEMEMT XDATA FSYS_Manage[MAX_STORE_FILE_NUM];
#endif
#if (MAX_POST_RECORDS)
extern POST_RECORD XDATA POST_Record[MAX_POST_RECORDS];
#endif

void FSYS_Init(void);
U8_T FSYS_FindFile(U8_T XDATA*);
U16_T FSYS_HtmlExpansion(U8_T);

const void *fun_tbl[];

void FUN_TEXT_tftps_ip (void *pWebData);
void FUN_TEXT_file_name (void *pWebData);
void FUN_SELECT_ipchg (void *pWebData);
void FUN_SELECT_pswchg (void *pWebData);
void FUN_SELECT_dbr (void *pWebData);
void FUN_SELECT_data (void *pWebData);
void FUN_SELECT_parity (void *pWebData);
void FUN_SELECT_stop (void *pWebData);
void FUN_SELECT_flow (void *pWebData);
void FUN_SELECT_rs485 (void *pWebData);
void FUN_SELECT_dhcp (void *pWebData);
void FUN_TEXT_static_ip (void *pWebData);
void FUN_TEXT_mask (void *pWebData);
void FUN_TEXT_gateway_ip (void *pWebData);
void FUN_SELECT_select_service (void *pWebData);
void FUN_TEXT_ddns_name (void *pWebData);
void FUN_TEXT_ddns_psd (void *pWebData);
void FUN_TEXT_host_name (void *pWebData);
void FUN_SELECT_chk_ddns_frey (void *pWebData);
void FUN_TEXT_username (void *pWebData);
void FUN_TEXT_password (void *pWebData);
void FUN_TEXT_new_usn (void *pWebData);
void FUN_TEXT_old_psw (void *pWebData);
void FUN_TEXT_new_psw (void *pWebData);
void FUN_TEXT_cfm_psw (void *pWebData);

#endif /* End of __FILE_SYSTEM_H__ */


/* End of filesys.h */