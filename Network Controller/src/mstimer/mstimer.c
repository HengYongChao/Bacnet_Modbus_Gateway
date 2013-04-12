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
 * Module Name: mstimer.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: mstimer.c,v $
 * Revision 1.2  2006/07/25 05:34:56  borbin
 * no message
 *
 * Revision 1.1.1.1  2006/06/20 05:50:28  borbin
 * no message
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "reg80390.h"
#include "mstimer.h"
#include "interrupt.h"
#include "dma.h"
#include "ax11000_cfg.h"
#include "portmacro.h"



U8_T IDATA ExecuteRuntimeFlag _at_ 0x30;


/*
 * ----------------------------------------------------------------------------
 * Function Name: SWTIMER_Tick
 * Purpose: Get software timer count.
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
extern volatile portTickType xTickCount;
U32_T SWTIMER_Tick(void)
{
	U32_T	timer;
	U8_T	isr;

	isr = EA;
	EA = 0;
	timer = xTickCount;
	EA = isr;
	return timer;

} /* End of SWTIMER_Tick */


/* End of mstmier.c */