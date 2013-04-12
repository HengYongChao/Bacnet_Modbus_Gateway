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
 * Module Name:mstimer.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: mstimer.h,v $
 * Revision 1.2  2006/05/18 05:02:43  Louis
 * no message
 *
 * Revision 1.1.1.1  2006/02/23 00:55:10  borbin
 * no message
 *
 *=============================================================================
 */

#ifndef __MSTIMER_H__
#define __MSTIMER_H__

/* INCLUDE FILE DECLARATIONS */
#include "types.h"
#include "mstimer_cfg.h"


/* NAMING CONSTANT DECLARATIONS */
#define SWTIMER_COUNT_SECOND	(1000 / SWTIMER_INTERVAL) /* timer expired count
														per second*/

/* SFR 0x94 definitions*/
#define SWTIMER_EXPIRED			BIT1

/* TIMER register definitions */
#define SWTIMER_REG				0x0C

/* Bit definitions: SW_TIMER_REG */
#define SWTIMER_START			BIT4
#define SWTIMER_RESET			BIT5
#define SWTIMER_INT_ENABLE		BIT7

/* GLOBAL VARIABLES */
extern U8_T IDATA ExecuteRuntimeFlag;

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
//---------------------------------------------------------------

U32_T SWTIMER_Tick(void);

				  
#endif /* End of __MSTIMER_H__ */
