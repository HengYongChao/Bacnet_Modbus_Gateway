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
#define FILE_DOWN			6
#define FILE_INDEX			7
#define FILE_LED			8
#define FILE_OPTION			9
#define FILE_TEMPERATURE			10
#define FILE_TEXT			11
#define FILE_TOP			12

#define MAX_STORE_FILE_NUM	13
#define MAX_FILE_NAME_LEN	30

#define FILE_TYPE_HTML		0
#define FILE_TYPE_BIN		BIT0

#define MAX_POST_RECORDS	26
#define MAX_POST_BUF_SUBMIT	1
#define MAX_POST_BUF_TEXT	9
#define MAX_POST_BUF_RADIO	8
#define MAX_POST_BUF_SELECT	8
#define MAX_POST_NAME_LEN	15
#define MAX_POST_VALUE_LEN	16

#define MAX_SELECT_OPTION_NUM	2
#define MAX_RADIO_OPTION_NUM	2

#define POST_TYPE_SUBMIT	1
#define POST_TYPE_TEXT		2
#define POST_TYPE_RADIO		3
#define POST_TYPE_SELECT	4

#define RECORD_RADIO_p0		0
#define RECORD_RADIO_p1		1
#define RECORD_RADIO_p2		2
#define RECORD_RADIO_p3		3
#define RECORD_RADIO_p4		4
#define RECORD_RADIO_p5		5
#define RECORD_RADIO_p6		6
#define RECORD_RADIO_p7		7
#define RECORD_SELECT_p0		9
#define RECORD_SELECT_p1		10
#define RECORD_SELECT_p2		11
#define RECORD_SELECT_p3		12
#define RECORD_SELECT_p4		13
#define RECORD_SELECT_p5		14
#define RECORD_SELECT_p6		15
#define RECORD_SELECT_p7		16
#define RECORD_TEXT_temperature		17
#define RECORD_TEXT_p0		18
#define RECORD_TEXT_p1		19
#define RECORD_TEXT_p2		20
#define RECORD_TEXT_p3		21
#define RECORD_TEXT_p4		22
#define RECORD_TEXT_p5		23
#define RECORD_TEXT_p6		24
#define RECORD_TEXT_p7		25

/* TYPE DECLARATIONS */
/*-------------------------------------------------------------*/
typedef struct _FILE_MANAGEMEMT
{
	U8_T			Occupy;
	U8_T			FType;
	U8_T			FName[MAX_FILE_NAME_LEN];
	U16_T			FileSize;
	U8_T			*PBuf;

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
	U8_T			Value[MAX_POST_VALUE_LEN];
	U8_T			DefaultVlaueLen;
	U8_T			IsApply;

} BUF_SUBMIT;

/*-------------------------------------------------------------*/
#if (MAX_POST_BUF_RADIO)
typedef struct _BUF_RADIO
{
	U16_T			Offset[MAX_RADIO_OPTION_NUM];
	U8_T			Value[MAX_RADIO_OPTION_NUM][MAX_POST_VALUE_LEN];
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
	U8_T			CurrValue[MAX_POST_VALUE_LEN];
	U8_T			UserValue[MAX_POST_VALUE_LEN];
	U8_T			DefaultLength;
	U8_T			CurrLength;
	U8_T			UserLength;

} BUF_TEXT;

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

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
#if (MAX_STORE_FILE_NUM)
extern FILE_MANAGEMEMT XDATA FSYS_Manage[MAX_STORE_FILE_NUM];
#endif
#if (MAX_POST_RECORDS)
extern POST_RECORD XDATA POST_Record[MAX_POST_RECORDS];
#endif

#if (MAX_POST_BUF_RADIO)
extern BUF_RADIO XDATA BUF_Radio[MAX_POST_BUF_RADIO];
#endif
#if (MAX_POST_BUF_TEXT)
extern BUF_TEXT XDATA BUF_Text[MAX_POST_BUF_TEXT];
#endif
#if (MAX_POST_BUF_SELECT)
extern BUF_SELECT XDATA BUF_Select[MAX_POST_BUF_SELECT];
#endif

void FSYS_Init(void);
U8_T FSYS_FindFile(U8_T XDATA*);
U16_T FSYS_HtmlExpansion(U8_T);

const void *fun_tbl[];

void FUN_RADIO_p0 (void *pWebData);
void FUN_RADIO_p1 (void *pWebData);
void FUN_RADIO_p2 (void *pWebData);
void FUN_RADIO_p3 (void *pWebData);
void FUN_RADIO_p4 (void *pWebData);
void FUN_RADIO_p5 (void *pWebData);
void FUN_RADIO_p6 (void *pWebData);
void FUN_RADIO_p7 (void *pWebData);
void FUN_SELECT_p0 (void *pWebData);
void FUN_SELECT_p1 (void *pWebData);
void FUN_SELECT_p2 (void *pWebData);
void FUN_SELECT_p3 (void *pWebData);
void FUN_SELECT_p4 (void *pWebData);
void FUN_SELECT_p5 (void *pWebData);
void FUN_SELECT_p6 (void *pWebData);
void FUN_SELECT_p7 (void *pWebData);
void FUN_TEXT_temperature (void *pWebData);
void FUN_TEXT_p0 (void *pWebData);
void FUN_TEXT_p1 (void *pWebData);
void FUN_TEXT_p2 (void *pWebData);
void FUN_TEXT_p3 (void *pWebData);
void FUN_TEXT_p4 (void *pWebData);
void FUN_TEXT_p5 (void *pWebData);
void FUN_TEXT_p6 (void *pWebData);
void FUN_TEXT_p7 (void *pWebData);

#endif /* End of __FILE_SYSTEM_H__ */


/* End of filesys.h */