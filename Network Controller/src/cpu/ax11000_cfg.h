/*
 *********************************************************************************
 *     Copyright (c) 2005   ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 *********************************************************************************
 */
/*================================================================================
 * Module Name : ax11000_cfg.h
 * Purpose     : Configuration setting of AX11000 module.
 * Author      : Robin Lee
 * Date        : 2006-01-06
 * Notes       : None.
 * $Log: ax11000_cfg.h,v $
 * Revision 1.3  2006/05/19 03:41:49  robin6633
 * 1.Enabled AX_WATCHDOG_ENB.
 *
 * Revision 1.2  2006/05/18 05:02:29  Louis
 * no message
 *
 *================================================================================
 */
#ifndef AX11000_CFG_H
#define AX11000_CFG_H

/* INCLUDE FILE DECLARATIONS */


/* NAMING CONSTANT DECLARATIONS */
#define		GET_SYS_VALUE		1 // 1:get the system globe value information
#define		AX_SWRST_ENB		1 // 1:use software reset function ; 0:not use
#define		AX_SWRBT_ENB		1 // 1:use software reboot function ; 0:not use
#define		STOE_ENABLE			1
#define		AX_WATCHDOG_ENB		1 // 1:involve watchdog function ; 0:not use

/*-------------------------------------------------------------*/
#define		RUNTIME_CODE_START_AT_0H		0	/*	0: runtime code start at 0h */
#define		RUNTIME_CODE_START_AT_24kH		1	/*	1: runtime code start at 24kh. */

#define		RUNTIME_CODE_START_ADDRESS		(RUNTIME_CODE_START_AT_24kH)


/* MACRO DECLARATIONS */
#define		AX_DBG_LED(value)	//{P1 = value;} // debug LED port, default is P1


/* TYPE DECLARATIONS */


/* GLOBAL VARIABLES */


/* EXPORTED SUBPROGRAM SPECIFICATIONS */


#endif /* End of AX11000_CFG_H */
