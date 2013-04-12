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
 * Module Name: phy.c
 * Purpose:  
 * Author:
 * Date:
 * Notes:
 * $Log: phy.c,v $
 * Revision 1.1.1.1  2006/06/20 05:50:28  borbin
 * no message
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "reg80390.h"
#include "phy.h"
#include "stoe.h"
#include "delay.h"
#include <intrins.h>

/* LOCAL VARIABLES DECLARATIONS */
static U16_T XDATA phy_Control = 0;
static U8_T XDATA phy_NetworkType;

/*
* -----------------------------------------------------------------------------
 * Function Name: phy_ReadReg
 * Purpose: Read PHY register.
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void phy_ReadReg(U8_T regaddr, U16_T XDATA* pvalue)
{
	U8_T	temp, isr;

	isr = EA;
	EA = 0;
	_nop_();
	/* abort command */
	EPCR = 0xff;

	EPCR = regaddr;
	EPCR = (PBDP->PhyInfo.PhyAddr + PHY_ACCESS_GO + PHY_READ_REG);

	temp = EPCR;
	temp = EPCR;
	while (temp & PHY_ACCESS_GO)
	{
		DELAY_Us(1);
		temp = EPCR;
		temp = EPCR;

	} /* End of while */

	*pvalue = EPDR;
	temp = EPDR;
	EA = isr;
	*pvalue += ((U16_T)temp << 8);

} /* End of phy_ReadReg */

/*
* -----------------------------------------------------------------------------
 * Function Name: phy_WriteReg
 * Purpose: Set PHY register.
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void phy_WriteReg(U8_T regaddr, U16_T value)
{
	U8_T	temp, isr;

	isr = EA;
	EA = 0;
	_nop_();
	/* abort command */
	EPCR = 0xff;

	EPDR = (U8_T)value;
	EPDR = (U8_T)(value >> 8);
	EPCR = regaddr;
	EPCR = (PBDP->PhyInfo.PhyAddr + PHY_ACCESS_GO);

	temp = EPCR;
	temp = EPCR;
	while (temp & PHY_ACCESS_GO)
	{
		DELAY_Us(1);
		temp = EPCR;
		temp = EPCR;

	} /* End of File */
	EA = isr;

} /* End of phy_WriteReg */

/*
* -----------------------------------------------------------------------------
 * Function Name: PHY_Init
 * Purpose: Initial some registers and variables of PHY.
 * Params: network_type -0: auto- negotiation
 *						-1: fixed 100 full speed.
 *						-2: fixed 100 half speed.
 *						-3: fixed 10 full speed.
 *						-4: fixed 10 half speed.
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PHY_Init(U8_T network_type)
{
	U16_T XDATA	phyctrl, phyanar, tempshort;

	phy_NetworkType = network_type;

	/* use internal phy */
	PBDP->PhyInfo.PhyAddr = PHY_ADDRESS;
	PBDP->PhyInfo.PhyType = PHY_INTERNAL;

	/* software reset */
	phy_WriteReg(MII_PHY_CONTROL, CONTROL_RESET);

	/* read phy reg-2, reg-0 to make sure embedded phy is ready */
	while (1)
	{
		phy_ReadReg(MII_PHY_OUI, &tempshort);
		if (tempshort == 0x003B)
			break;
	}

	while (1)
	{
		phy_ReadReg(MII_PHY_CONTROL, &phyctrl);
		if ((phyctrl == 0x3100) || (phyctrl == 0x3000) || (phyctrl == 0x1100) ||
			(phyctrl == 0x1000))
				break;
	}

	switch (network_type)
	{
	default:
	case AUTO_NEGOTIATION:
		phyctrl |= (CONTROL_100MB | CONTROL_FULL_DUPLEX);
		phyanar = ANAR_SELECTOR_8023 + (ANAR_PAUSE | ANAR_100TXFD | ANAR_100TX |
			ANAR_10TFD | ANAR_10T);
		break;
	case FIXED_100_FULL:
		phyctrl |= (CONTROL_100MB | CONTROL_FULL_DUPLEX);
		phyanar = ANAR_SELECTOR_8023 + (ANAR_PAUSE | ANAR_100TXFD);
		break;
	case FIXED_100_HALF:
		phyctrl |= CONTROL_100MB;
		phyanar = ANAR_SELECTOR_8023 + (ANAR_PAUSE | ANAR_100TX);
		break;
	case FIXED_10_FULL:
		phyctrl |= CONTROL_FULL_DUPLEX;
		phyanar = ANAR_SELECTOR_8023 + (ANAR_PAUSE | ANAR_10TFD);
		break;
	case FIXED_10_HALF:
		phyanar = ANAR_SELECTOR_8023 + (ANAR_PAUSE | ANAR_10T);
		break;
	}

	/* set phy register 0 & 4 to start negotitation*/
	phy_WriteReg(MII_PHY_ANAR, phyanar);
	phyctrl |= (CONTROL_ENABLE_AUTO | CONTROL_START_AUTO);
	phy_WriteReg(MII_PHY_CONTROL, phyctrl);
	phy_Control = phyctrl;

} /* End of PHY_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PHY_CheckMediaType
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T PHY_CheckMediaType(void)
{
	U16_T XDATA	phylinkstatus = 0;
	U16_T XDATA	tempshort;

	while (!phylinkstatus)
	{
		phy_ReadReg(MII_PHY_STATUS, &phylinkstatus);
		phylinkstatus &= BIT5;
	}
	DELAY_Ms(10);

	/* read phy register 0 for internal phy */
	phy_ReadReg(MII_PHY_CONTROL, &tempshort);

	if ((tempshort & CONTROL_100MB) && (tempshort & CONTROL_FULL_DUPLEX))
		phylinkstatus = ANLPAR_100TXFD;
	else if (tempshort & CONTROL_100MB)
		phylinkstatus = ANLPAR_100TX;
	else if (tempshort & CONTROL_FULL_DUPLEX)
		phylinkstatus = ANLPAR_10TFD;
	else
		phylinkstatus = ANLPAR_10T;

	return phylinkstatus;

} /* End of PHY_CheckMediaType() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PHY_Reset
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void phy_Restart(void)
{
	phy_WriteReg(MII_PHY_CONTROL, CONTROL_POWER_DOWN);

	MAC_Init(phy_NetworkType);

} /* End of PHY_Reset() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PHY_PowerUp
 * Purpose: set phy to power up
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PHY_PowerUp(void)
{
	PBDP->PhyInfo.PhyAddr = PHY_ADDRESS;

	phy_WriteReg(MII_PHY_CONTROL, 0);

} /* End of PHY_PowerUp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: PHY_WatchDog
 * Purpose: If ethernet is un-link, restart the phy to make sure it work right
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void PHY_WatchDog(void)
{
	if (!PBDP->MacInfo.LinkSpeed)
		phy_Restart();

} /* End of PHY_WatchDog() */


/* End of phy.c */