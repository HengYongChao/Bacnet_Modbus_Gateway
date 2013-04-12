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
 * Module Name: delay.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: delay.c,v $
 * Revision 1.2  2006/05/18 05:02:43  Louis
 * no message
 *
 * Revision 1.1.1.1  2006/02/23 00:55:10  borbin
 * no message
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "reg80390.h"
#include "delay.h"
#include "ax11000_cfg.h"
#include "ax11000.h"

/* NAMING CONSTANT DECLARATIONS */
#define CLK_100M	100
#define CLK_50M		50
#define CLK_25M		25

/* LOCAL VARIABLES DECLARATIONS */
static U16_T delay_MsLoop = 1;
static U8_T delay_SysClk = 25;
static U8_T delay_ProgWst = 1;

/*
 * ----------------------------------------------------------------------------
 * Function Name: DELAY_Init
 * Purpose: Get system clock and program wait state to decide delay loop count.
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void DELAY_Init(void)
{
	/* get system clock */
	switch (AX11000_GetSysClk())
	{
		case SCS_100M :
			delay_SysClk = CLK_100M;
			break;
		case SCS_50M :
			delay_SysClk = CLK_50M;
			break;
		case SCS_25M :
			delay_SysClk = CLK_25M;
		default:
			break;
	}

	/* get program wait state */
	delay_ProgWst = AX11000_GetProgWst() + 1;

	/* calculate driver loop count for per ms */
	delay_MsLoop = ((U32_T)delay_SysClk * 1000) / ((U32_T)delay_ProgWst * 11);

} /* End of DELAY_Init */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DELAY_Us
 * Purpose: Delay XXX us.
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void DELAY_Us(U16_T loop)
{	
	U32_T	count;

	count = ((U32_T)delay_SysClk * loop) / ((U32_T)delay_ProgWst * 20);
	if (count > 7)
		count -= 7;
	else
		return;
		
	while (count--);

} /* End of DELAY_Us */

/*
 *--------------------------------------------------------------------------------
 * Function Name: DELAY_Ms
 * Purpose : Delay XXX ms
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void DELAY_Ms(U16_T loop)
{
	U16_T	x, y;

	for (y = 0; y < loop; y++)
	{
		x = delay_MsLoop;
		while (x--);
	}
} /* End of ms_delay*/


/* End of delay.c */