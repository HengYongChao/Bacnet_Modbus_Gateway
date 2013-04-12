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
 * Module Name:dnsctab.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: dnsctab.h,v $
 * Revision 1.1  2006/05/22 05:44:27  robin6633
 * no message
 *
 *
 *=============================================================================
 */

#ifndef __DNSCTAB_C_H__
#define __DNSCTAB_C_H__

/* INCLUDE FILE DECLARATIONS */
#include "types.h"
#include "dnsc.h"

/* NAMING CONSTANT DECLARATIONS */
#define DNSCTAB_MAX_RECORD 4 // Number of records can be kept in the table 

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void DNSCTAB_Init(void);
U8_T DNSCTAB_Query(S8_T*, U32_T*);
U8_T DNSCTAB_GetState(void);
U32_T DNSCTAB_GetIP(void);
void DNSCTAB_SetDnsIP(U32_T);
#endif /* End of __DNSCTAB_C_H__ */

/* End of dnsctab.h */
