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
 * Module Name:dnsc.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: dnsc.h,v $
 * Revision 1.1  2006/05/22 05:44:27  robin6633
 * no message
 *
 *
 *=============================================================================
 */

#ifndef __DNSC_C_H__
#define __DNSC_C_H__

/* INCLUDE FILE DECLARATIONS */
#include "types.h"

/* NAMING CONSTANT DECLARATIONS */
#define DNS_SERVER_PORT		53

/* TFTP HEADER FIELDS */
#define DNS_RESPONSE        0x80 // Query/Response. 1 bit
								 // Opcode. 4 bits
#define DNS_OPCODE_STANDARD 0x00
#define DNS_OPCODE_INVERSE  0x08
#define DNS_OPCODE_STATUS   0x10
#define DNS_AUTHORATIVE     0x04 // Authoritative Answer. 1 bit
#define DNS_TRUNC           0x02 // Truncated. 1 bit
#define DNS_RD              0x01 // Recursion Desired. 1 bit.
#define DNS_RA              0x80 // Recursion Available. 1 bit
							     // Return code. 4 bits.						
#define DNS_ERR_NONE        0x00
#define DNS_ERR_NAME        0x03
#define DNS_ERR_MASK        0x0f
 
#define DNS_TYPE_A			0x0001
#define DNS_CLASS_IN		0x0001

#define DNSC_REQUEST_TIMEOUT	(2 * SWTIMER_COUNT_SECOND) /* 2 second */
#define DNSC_MAX_RETRY			3

/* DNSC connection state */
#define DNSC_STATE_FREE				0
#define	DNSC_STATE_WAIT_RESPONSE	1
#define	DNSC_STATE_RESPONSED		2

/* TYPE DECLARATIONS */
typedef struct 
{
	U16_T id;
	U8_T  q_op4_aa_tc_rd;
	U8_T  ra_z_ad_cd_rc4;
    U16_T total_questions;
    U16_T total_answers;
    U16_T total_auth_rr;
    U16_T total_extra_rr;	
} DnsHeader;

typedef struct
{
	U16_T type;
	U16_T class1;	
} DnsQuestion;

typedef struct
{
	U16_T name_offset;
	U16_T type;
	U16_T class1;
	U16_T ttl[2];
	U16_T len;
	U16_T ip_addr[2];
} DnsAnswer;

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void DNSC_Init(void);
void DNSC_Event(U8_T, U8_T);
void DNSC_Receive(U8_T XDATA*, U16_T, U8_T);
U8_T DNSC_Query(char*);
U8_T DNSC_GetState(void);
U32_T DNSC_GetIp(void);
void DNSC_Command(U8_T*, U8_T);
void DNSC_SetDnsIP(U32_T ip);

#endif /* End of __DNSC_C_H__ */

/* End of dnsc.h */
