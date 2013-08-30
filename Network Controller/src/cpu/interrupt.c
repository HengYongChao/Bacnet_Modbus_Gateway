/*
 *********************************************************************************
 *     Copyright (c) 2005	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 *********************************************************************************
 */
/*================================================================================
 * Module Name : interrupt.c
 * Purpose     : This file include peripheral interrupt service routine and
 *               the wake up interrupt service routine.
 * Author      : Robin Lee
 * Date        : 2006-01-09
 * Notes       :
 * $Log: interrupt.c,v $
 * Revision 1.3  2006/07/20 03:50:59  robin6633
 * 1.Change the header file name "reg80390.h" to "ax110xx.h".
 *
 * Revision 1.2  2006/04/20 01:22:56  robin6633
 * 1.Added watchdog timeout ISR.
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
//#include 	"main.h"


#if AX_LBI_INT_ENABLE
#include	"lbi.h"
#endif

#if AX_ETH_INT_ENABLE
#include	"mac.h"
#endif

#if AX_ETH_INT_ENABLE
#include	"stoe.h"
#endif

#if AX_I2C_INT_ENABLE
#include	"i2c.h"
#endif

#if AX_SPI_INT_ENABLE
#include	"spi.h"
#endif

#if AX_ONEWIRE_INT_ENABLE
#include	"onewire.h"
#endif

#if AX_CAN_INT_ENABLE
#include	"can.h"
#endif

#if AX_HSUART_INT_ENABLE
#include	"hsuart.h"
#endif


/* NAMING CONSTANT DECLARATIONS */


/* STATIC VARIABLE DECLARATIONS */


/* LOCAL SUBPROGRAM DECLARATIONS */
static void	ax11000_PeripherialISR(void);

#if AX_POWER_MANAGEMENT_INT_ENABLE
static void	ax11000_PmmISR(void);
#endif

#if AX_WATCHDOG_INT_ENB
void	ax11000_WatchDogISR(void);
#endif


/* LOCAL SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * static void ax11000_PeripherialISR(void)
 * Purpose : The interrupt service routine of Flipper peripheral devices.
 * Params  : None.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
static void ax11000_PeripherialISR(void) interrupt 9 //use external interrupt 4 (0x4B)
{
	U8_T	intrStt1 = 0;
	U8_T	intrStt2 = 0;

	/* Interrupt type check */
	while (1)
	{
		EA = 0;
		intrStt1 = PISSR1;
		intrStt2 = PISSR2;
		EA = 1;

		if ((intrStt1 == 0) && (intrStt2 == 0))
		{
			break;
		}

#if AX_LBI_INT_ENABLE
		if (intrStt1 & LB_INT_STU)
		{
			LocalBusFunc();
		}
#endif

#if AX_LBI_INT_ENABLE
		if (intrStt1 & LB_EXT_INT_STU)
		{
			LocalBusAccessCompleteFunc();
		}
#endif

#if AX_ETH_INT_ENABLE
#if (MAC_GET_INTSTATUS_MODE == MAC_INTERRUPT_MODE)
		if (intrStt1 & ETH_INT_STU)
		{
			MAC_SetInterruptFlag();

		}
#endif
#endif

#if AX_ETH_INT_ENABLE
#if (STOE_GET_INTSTATUS_MODE == STOE_INTERRUPT_MODE)
		if (intrStt1 & TOE_INT_STU)
		{
			STOE_SetInterruptFlag();

		}
#endif
#endif

#if AX_CAN_INT_ENABLE
		if (intrStt1 & CAN_INT_STU)
		{
			CAN_Func();
		}
#endif

#if AX_I2C_INT_ENABLE
		if (intrStt1 & I2C_INT_STU)
		{
			I2C_Func();
		}
#endif

#if AX_SPI_INT_ENABLE
		if (intrStt1 & SPI_INT_STU)
		{
			SPI_Func();
			
		}
#endif

#if AX_ONEWIRE_INT_ENABLE
		if (intrStt1 & OW_INT_STU)
		{
			ONEWIRE_Func();
		}
#endif

#if AX_HSUART_INT_ENABLE
		if (intrStt2 & UART2_INT_STU)
		{
			HSUR_Func();
		}
#endif

	}
}

#if AX_POWER_MANAGEMENT_INT_ENABLE
/*
 *--------------------------------------------------------------------------------
 * static void ax11000_PmmISR(void)
 * Purpose : The interrupt service routine of the
 *           wake up event in power management mode.
 * Params  : None.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
static void ax11000_PmmISR(void) interrupt 11 //use external interrupt 6 (0x5B)
{
	U8_T	wakeStatus = 0;
	U8_T	mode = 0;
	U8_T	sysClk = 0;
	U8_T	canReg = 0;
	U8_T	intEnb = 0;

	EA = 0;
	EIF &= ~INT6F;	// Clear the flag of interrupt 6.
	EA = 1;

	wakeStatus = PCON;
	if (!(wakeStatus & SWB_))
	{
		PCON &= ~ (PMM_ | STOP_);
	}

#if AX_ETH_INT_ENABLE
	/* Ethernet wake up function */
	/* disable wake up interrupt */
	MDR  = 0;
	MCIR = MAC_STOP_PMM_INT_ENABLE_REG;
	/* clear MAC status register */
	CLI_MacRd((ULONG)MAC_STOP_PMM_INT_STATUS_REG, &WakeStatus, 1);
	STOE_Standby = 0;
#endif

#if AX_CAN_INT_ENABLE
	/* CAN wake up function */
	CAN_WakeUpEvent(0); // 0 for exit power management mode
#endif
}
#endif

#if AX_WATCHDOG_INT_ENB
/*
 *--------------------------------------------------------------------------------
 * void ax11000_WatchDogISR(void)
 * Purpose : The interrupt service routine of the AX11000 Watchdog timeout.
 * Params  : None
 * Returns : None
 * Note    : None
 *--------------------------------------------------------------------------------
 */
void ax11000_WatchDogISR(void) interrupt 12
{
	if (EWDI)
	{
		if (EWT)
		{
			TA = 0xAA;
			TA = 0x55;
			WDIF = 0; // clear WatchDog Interrupt Flag.
			WTRF = 0; // clear the Watchdog Timer Reset Flag.
			RWT = 1; // reset watchdog timer.
		}
		else
		{
			TA = 0xAA;
			TA = 0x55;
			WDIF = 0; //clear WatchDog Interrupt Flag.
			RWT = 1; // reset watchdog timer.
		}
	}
}
#endif


/* EXPORTED SUBPROGRAM BODIES */


/* End of interrupt.c */
