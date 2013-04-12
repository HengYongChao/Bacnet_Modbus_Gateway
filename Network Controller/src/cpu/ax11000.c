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
 * Module Name : ax11000.c
 * Purpose     : AX11000 initialization and globe values setting.
 * Author      : Robin Lee
 * Date        : 2005-12-27
 * Notes       : In the initial function, all external interrupt are disable in
 *               default. User must enable a specific interrupt in its module.
 *               Several system values are initial in beginning
 * $Log: ax11000.c,v $
 * Revision 1.3  2006/07/20 03:50:52  robin6633
 * 1.Change the header file name "reg80390.h" to "ax110xx.h".
 *
 * Revision 1.2  2006/04/20 01:19:06  robin6633
 * 1.Added watchdog setting.
 * 2.Changed the wait state to fit real chip.
 *
 * Revision 1.1  2006/04/07 11:36:17  robin6633
 * no message
 *
 *================================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include	"ax110xx.h"
#include	"types.h"
#include	"interrupt.h"
#include	"ax11000.h"



/* STATIC VARIABLE DECLARATIONS */
static U8_T 	swResetOn = 0;
static U8_T		globeInt = 0;
static U8_T		cpuSysClk = 0;
static U8_T		memShadow = 0;
static U8_T		progWtst = 0;
static U8_T		dataStretch = 0;


/* LOCAL SUBPROGRAM DECLARATIONS */


/* LOCAL SUBPROGRAM BODIES */


/* EXPORTED SUBPROGRAM BODIES */
extern void test_run(U8_T);
/*
 *--------------------------------------------------------------------------------
 * void AX11000_Init(void)
 * Purpose : Initiation of the AX11000 core.
 * Params  : None
 * Returns : None
 * Note    : None
 *--------------------------------------------------------------------------------
 */
void AX11000_Init(void)
{
	EA = 0; // turn off globe interrupt

	P0 = 0xFF;
	P1 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;

	/* Check program wait-state and data memory wait-state */
	if (CSREPR & PMS)
	{
		memShadow = 1;

		/* for real chip */
		switch (CSREPR & (BIT6|BIT7))
		{
			case SCS_100M :
				cpuSysClk = SCS_100M;
				WTST = 0x01;
				CKCON = 0x01;
				break;
			case SCS_50M :
				cpuSysClk = SCS_50M;
				WTST = 0x00;
				CKCON = 0x01;
				break;
			case SCS_25M :
				cpuSysClk = SCS_25M;
				WTST = 0x00;
				CKCON = 0x01;
				break;
		}
	}
	else
	{
		memShadow = 0;

		/* use this configure while fs = 100Mhz.*/

		/* for real chip */
		switch (CSREPR & (BIT6|BIT7))
		{
			case SCS_100M :
				cpuSysClk = SCS_100M;
				WTST = 0x07;
				CKCON = 0x01;
				break;
			case SCS_50M :
				cpuSysClk = SCS_50M;
				WTST = 0x03;
				CKCON = 0x01;
				break;
			case SCS_25M :
				cpuSysClk = SCS_25M;
				WTST = 0x01;
				CKCON = 0x01;
				break;
		}
	}

	progWtst = WTST & 0x07;
	dataStretch = CKCON & 0x07;

	PCON	&= ~SWB_;	// Turn off switchback function.

	EIF		&= ~INT5F;	// Clear the flag of interrupt 5.
	EIF		&= ~INT6F;	// Clear the flag of interrupt 6.
	if (WTRF)
	{
		CSREPR |= SW_RBT;
		WTRF	= 0;		// Clear Watch Dog Time Out Reset Flag.
	}

	if (swResetOn == TRUE)
	{
		I2CDR = BIT4;
		I2CCIR = 0x04;
		do {
			I2CCIR =0x06;
			swResetOn = I2CDR;
		} while (swResetOn & BIT3);

		swResetOn = 0;
	}







	PINT2	= 1;		// INT2 priority is at high level for DMA request.

	EXTINT0(OFF);		// EINT0 interrupt.						// 7/2/2012 LJ 打开INT0 会导致死掉
	EXTINT1(OFF);		// EINT1 interrupt.
	EXTINT2(OFF);		// EINT2 interrupt for DMA request.
	EXTINT3(OFF);		// EINT3 interrupt for PCA.
	EXTINT4(ON);		// EINT4 interrupt for peripheral device.
	EXTINT5(OFF);		// EINT5 interrupt for software timer.
	EXTINT6(ON);		// EINT6 interrupt for wake-up of power management mode and stop mode.

	if (globeInt & BIT7)
		EA = globeInt & BIT0;
	else
		EA = 1;		// Enable the globe interrupt.



//	IE = 0x00;



}

/*
 *--------------------------------------------------------------------------------
 * U8_T AX11000_GetSysClk(void)
 * Purpose : Get system clock of AX11000 in initial.
 * Params  : None
 * Returns : cpuSysClk - system clock of AX11000
 * Note    : None
 *--------------------------------------------------------------------------------
 */
#if GET_SYS_VALUE
U8_T AX11000_GetSysClk(void)
{
	return cpuSysClk;
}
#endif

/*
 *--------------------------------------------------------------------------------
 * U8_T AX11000_GetMemSdw(void)
 * Purpose : Get system memory shadow setting in initial.
 * Params  : None
 * Returns : memshadow - memory shadow mode
 * Note    : None
 *--------------------------------------------------------------------------------
 */
#if GET_SYS_VALUE
U8_T AX11000_GetMemSdw(void)
{
	return memShadow;
}
#endif

/*
 *--------------------------------------------------------------------------------
 * U8_T AX11000_GetProgWst(void)
 * Purpose : Get system program wait state in initial.
 * Params  : None
 * Returns : progwtst - system program wait state of cpu AX11000
 * Note    : None
 *--------------------------------------------------------------------------------
 */
#if GET_SYS_VALUE
U8_T AX11000_GetProgWst(void)
{
	return progWtst;
}
#endif

/*
 *--------------------------------------------------------------------------------
 * U8_T AX11000_GetDataSth(void)
 * Purpose : Get system data stretch in initial.
 * Params  : None
 * Returns : datastretch - data stretch cycle of cpu AX11000
 * Note    : None
 *--------------------------------------------------------------------------------
 */
#if GET_SYS_VALUE
U8_T AX11000_GetDataSth(void)
{
	return dataStretch;
}
#endif

#if AX_SWRST_ENB
/*
 *--------------------------------------------------------------------------------
 * void AX11000_SoftReset(void)
 * Purpose : Software reset to reset CPU core.
 * Params  : None
 * Returns : None
 * Note    : None
 *--------------------------------------------------------------------------------
 */
void AX11000_SoftReset(void)
{
	if (EA)
		globeInt = BIT0 | BIT7; // BIT0:EA bit record ; BIT7:Software reset record.
	else
		globeInt = BIT7;

	EA = 0;

	swResetOn = TRUE;
	

	CSREPR |= SW_RST;
}
#endif

#if AX_SWRBT_ENB
/*
 *--------------------------------------------------------------------------------
 * void AX11000_SoftReboot(void)
 * Purpose : Software reboot to restart hardware core of all.
 * Params  : None
 * Returns : None
 * Note    : None
 *--------------------------------------------------------------------------------
 */
void AX11000_SoftReboot(void)
{
	
	CSREPR |= SW_RBT;
	
}
#endif

#if AX_WATCHDOG_ENB
/*
 *--------------------------------------------------------------------------------
 * void AX11000_WatchDogSetting(U8_T wdIntrEnb, U8_T wdRstEnb, U8_T wdPrty, U8_T wdTime)
 * Purpose : Enable the Watchdog timer.
 * Params  : None
 * Returns : None
 * Note    : None
 *--------------------------------------------------------------------------------
 */
void AX11000_WatchDogSetting(U8_T wdIntrEnb, U8_T wdRstEnb, U8_T wdPrty, U8_T wdTime)
{
	CKCON |= wdTime;

	if (wdIntrEnb & WD_INTR_ENABLE)
	{
		EWDI = 1;
	}
	else
	{
		EWDI = 0;
	}

	if (wdRstEnb & WD_RESET_ENABLE)
	{
		TA = 0xAA;
		TA = 0x55;
		EWT = 1;
	}
	else
	{
		TA = 0xAA;
		TA = 0x55;
		EWT = 0;
	}

	if (wdPrty & WD_HIGH_PRIORITY)
	{
		PWDI = 1;
	}
	else
	{
		PWDI = 0;
	}
	
	TA = 0xAA;
	TA = 0x55;
	RWT = 1;
	WTRF = 0;
	WDIF = 0;
}
#endif


/* End of ax11000.c */
