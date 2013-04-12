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
 * Module Name : ax11000.h
 * Purpose     : A header file belongs to AX11000 module.
 *               It define all globe parameters in AX11000 module.
 * Author      : Robin Lee
 * Date        : 2006-01-09
 * Notes       : None.
 * $Log: ax11000.h,v $
 * Revision 1.2  2006/05/18 05:02:20  Louis
 * no message
 *
 * Revision 1.2  2006/04/20 01:20:33  robin6633
 * 1.Added software reboot function.
 * 2.Added watchdog setting function.
 *
 * Revision 1.1  2006/04/07 11:36:17  robin6633
 * no message
 *
 *================================================================================
 */
#ifndef AX11000_H
#define AX11000_H

/* INCLUDE FILE DECLARATIONS */
#include	"ax11000_cfg.h"


/* NAMING CONSTANT DECLARATIONS */
#define		PROG_WTST_0			0
#define		PROG_WTST_1			1
#define		PROG_WTST_2			2
#define		PROG_WTST_3			3
#define		PROG_WTST_4			4
#define		PROG_WTST_5			5
#define		PROG_WTST_6			6
#define		PROG_WTST_7			7
#define		DATA_STRETCH_0		0
#define		DATA_STRETCH_1		1
#define		DATA_STRETCH_2		2
#define		DATA_STRETCH_3		3
#define		DATA_STRETCH_4		4
#define		DATA_STRETCH_5		5
#define		DATA_STRETCH_6		6
#define		DATA_STRETCH_7		7

#define		SHADOW_MEM_ENB		0x10
#define		SYS_CLK_100M		0xC0
#define		SYS_CLK_50M			0x40
#define		SYS_CLK_25M			0x00

#define		WD_INTR_ENABLE		1
#define		WD_INTR_DISABLE		0
#define		WD_RESET_ENABLE		1
#define		WD_RESET_DISABLE	0
#define		WD_HIGH_PRIORITY	1
#define		WD_LOW_PRIORITY		0
#define		WD_INTERVAL_131K	0x00
#define		WD_INTERVAL_1M		WD0_
#define		WD_INTERVAL_8M		WD1_
#define		WD_INTERVAL_67M		WD1_|WD0_


/* MACRO DECLARATIONS */


/* TYPE DECLARATIONS */


/* GLOBAL VARIABLES */


/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void	AX11000_Init(void);
U8_T	AX11000_GetSysClk(void);
U8_T	AX11000_GetMemSdw(void);
U8_T	AX11000_GetProgWst(void);
U8_T	AX11000_GetDataSth(void);
#if AX_SWRST_ENB
void	AX11000_SoftReset(void);
#endif
#if AX_SWRBT_ENB
void	AX11000_SoftReboot(void);
#endif
#if AX_WATCHDOG_ENB
void	AX11000_WatchDogSetting(U8_T wdIntrEnb, U8_T wdRstEnb, U8_T wdPrty, U8_T wdTime);
#endif


#endif /* End of AX11000_H */
