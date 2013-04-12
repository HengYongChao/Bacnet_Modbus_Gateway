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
 * Module Name: mac.c
 * Purpose:  
 * Author:
 * Date:
 * Notes:
 * $Log: mac.c,v $
 * Revision 1.1.1.1  2006/06/20 05:50:28  borbin
 * no message
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "reg80390.h"
#include "mac.h"
#include "stoe.h"
#include "delay.h"
#include <intrins.h>

/* GLOBAL VARIABLES DECLARATIONS */
static U8_T XDATA mac_InterruptStatus = 0;

/* LOCAL SUBPROGRAM DECLARATIONS */
static void mac_InterruptEnable(void);
static void mac_InterruptDisable(void);
static void mac_StartOperate(void);
static void mac_StopOperate(void);

/*
 * ----------------------------------------------------------------------------
 * Function Name: mac_ReadReg
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void mac_ReadReg(U8_T regaddr, U8_T XDATA* pbuf, U8_T length)
{
	U8_T	isr;

	isr = EA;
	EA = 0;
	_nop_();
	MCIR = regaddr;
	while (length--)
		pbuf[length] = MDR;
	EA = isr;

} /* End of mac_ReadReg */

/*
 * ----------------------------------------------------------------------------
 * Function Name: mac_WriteReg
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void mac_WriteReg(U8_T regaddr, U8_T XDATA* pbuf, U8_T length)
{
	U8_T	isr;

	isr = EA;
	EA = 0;
	while (length--)
		MDR = pbuf[length];
	MCIR = regaddr;
	EA = isr;

} /* End of mac_WriteReg */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MAC_Init
 * Purpose: initial all registers and variables of MAC.
 * Params: network_type -0: auto- negotiation
 *						-1: fixed 100 full speed.
 *						-2: fixed 100 half speed.
 *						-3: fixed 10 full speed.
 *						-4: fixed 10 half speed.
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MAC_Init(U8_T network_type)
{
	U8_T XDATA	temp[3];

	/* read MAC address*/
	mac_ReadReg(MAC_ADDR_REG, PNetStation->CurrStaAddr, MAC_ADDRESS_LEN);

	/* use embedded phy */
	temp[0] = (PHY_SELECT_EMBEDDED | PHY_INTERNAL_PHY_OPERA_STATE | BIT1);
	mac_WriteReg(MAC_PHY_CTL_REG, temp, 1);

	/* phy power up */
	PHY_PowerUp();

	/* reset embedded phy */
	temp[0] = (PHY_SELECT_EMBEDDED | BIT1);
	mac_WriteReg(MAC_PHY_CTL_REG, temp, 1);

	DELAY_Ms(2);

	/* set embedded phy to operating mode */
	temp[0] = (PHY_SELECT_EMBEDDED | PHY_INTERNAL_PHY_OPERA_STATE | BIT1);
	mac_WriteReg(MAC_PHY_CTL_REG, temp, 1);

	/* stop & reset MAC operation */
	mac_StopOperate();

	if (network_type != FORCE_EMBEDDED_PHY_10_HALF)
	{
		/* phy initialize. */
		PHY_Init(network_type);
	}

	PBDP->MacInfo.MediumLinkType = MEDIUM_ENABLE_TX_FLOWCTRL;
	PBDP->MacInfo.FullDuplex = 1;
	switch (network_type)
	{
	default:
	case AUTO_NEGOTIATION:
		PBDP->MacInfo.NetworkType = MAC_AUTO_NEGOTIATION;
		PBDP->MacInfo.MediumLinkType|=(MEDIUM_FULL_DUPLEX_MODE | MEDIUM_MII_100M_MODE |
			MEDIUM_ENABLE_RX_FLOWCTRL);
		break;
	case FIXED_100_FULL:
		PBDP->MacInfo.NetworkType = (MAC_LINK_100M_SPEED | MAC_LINK_FULL_DUPLEX);
		PBDP->MacInfo.MediumLinkType|=(MEDIUM_FULL_DUPLEX_MODE | MEDIUM_MII_100M_MODE |
			MEDIUM_ENABLE_RX_FLOWCTRL);
		break;
	case FIXED_100_HALF:
		PBDP->MacInfo.NetworkType = MAC_LINK_100M_SPEED;
		PBDP->MacInfo.MediumLinkType |= MEDIUM_MII_100M_MODE;
		break;
	case FIXED_10_FULL:
		PBDP->MacInfo.NetworkType = (MAC_LINK_10M_SPEED | MAC_LINK_FULL_DUPLEX);
		PBDP->MacInfo.MediumLinkType |= (MEDIUM_FULL_DUPLEX_MODE |
			MEDIUM_ENABLE_RX_FLOWCTRL);
		break;
	case FIXED_10_HALF:
		PBDP->MacInfo.NetworkType = MAC_LINK_10M_SPEED;
		break;
	case FORCE_EMBEDDED_PHY_10_HALF:
		PBDP->MacInfo.NetworkType = MAC_FORCE_ENBEDDED_PHY_10_HALF;
		PBDP->MacInfo.MediumLinkType = 0;
		break;
	}
	/* set medium status */
	mac_WriteReg(MAC_MEDIUM_STATUS_MODE_REG, &PBDP->MacInfo.MediumLinkType, 1);

	/* set IPG */
	temp[0] = 0x2b;
	temp[1] = 0x16;
	temp[2] = 0x95;
	mac_WriteReg(MAC_IPG_CTL_REG, temp, 3);

	/* set RX filter. */
	temp[0] = BIT6;
	mac_WriteReg(MAC_RX_CTL_REG, temp, 1);
	MAC_SetRxFilter(MAC_RCV_BROADCAST);

	PBDP->MacInfo.LinkSpeed = 0; // Ethernet not linkup.

	/* decide interrupt mask */
#if (MAC_GET_INTSTATUS_MODE == MAC_INTERRUPT_MODE) 
	PBDP->MacInfo.InterruptMask = PRIMARY_LINK_CHANGE_ENABLE;
#endif

} /* End of MAC_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MAC_GetMacAddr
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T* MAC_GetMacAddr(void)
{
	return PNetStation->CurrStaAddr;

} /* End of MAC_GetMacAddr() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MAC_GetMacAddr
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MAC_SetMacAddr(U8_T* addr)
{
	U8_T i;

	for (i = 0; i < MAC_ADDRESS_LEN; i++)
		PNetStation->CurrStaAddr[i] = addr[i];
		
	mac_WriteReg(MAC_ADDR_REG, PNetStation->CurrStaAddr, MAC_ADDRESS_LEN);
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: MAC_Start
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MAC_Start(void)
{
#if (MAC_GET_INTSTATUS_MODE == MAC_INTERRUPT_MODE) 
	/* clear mac interrupt status */
	mac_ReadReg(MAC_WAKEUP_LINK_INT_STATUS_REG, &mac_InterruptStatus, 1);

	/* enable mac interrupt */
	mac_InterruptEnable();
#endif

} /* End of MAC_Start() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: mac_StartOperate
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void mac_StartOperate(void)
{
	U8_T XDATA	temp;

	mac_ReadReg(MAC_RX_CTL_REG, &temp, 1);

	/* set mac register to start receive/transmit packets. */
	temp |= START_OPERATION;
	mac_WriteReg(MAC_RX_CTL_REG, &temp, 1);

} /* End of mac_StartOperate */

/*
 * ----------------------------------------------------------------------------
 * Function Name: mac_StopOperate
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void mac_StopOperate(void)
{
	U8_T XDATA	temp;

	mac_ReadReg(MAC_RX_CTL_REG, &temp, 1);

	temp &= ~START_OPERATION;
	mac_WriteReg(MAC_RX_CTL_REG, &temp, 1);

} /* End of mac_StopOperate */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MAC_SetRxFilter
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MAC_SetRxFilter(U8_T filter)
{
	U8_T XDATA	temp;

	mac_ReadReg(MAC_RX_CTL_REG, &temp, 1);

	/* set rcv filter. */
	temp &= 0xc0;
	if (filter & MAC_RCV_PROMISCUOUS)
		temp |= PACKET_TYPE_PROMISCOUS;
	if (filter & MAC_RCV_ALL_MULTICAST)
		temp |= PACKET_TYPE_ALL_MULTI;
	if (filter & MAC_RCV_BROADCAST)
		temp |= PACKET_TYPE_BROADCAST;
	if (filter & MAC_RCV_MULTICAST)
		temp |= PACKET_TYPE_MULTICAST;

	mac_WriteReg(MAC_RX_CTL_REG, &temp, 1);

} /* End of MAC_SetRxFilter() */

#if (MAC_GET_INTSTATUS_MODE == MAC_INTERRUPT_MODE) 
/*
 * ----------------------------------------------------------------------------
 * Function Name: mac_InterruptEnable
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void mac_InterruptEnable(void)
{
	U8_T XDATA	temp;

	/* set link change interrupt enable */
	temp = PBDP->MacInfo.InterruptMask;
	mac_WriteReg(MAC_LINK_CHANGE_INT_ENABLE_REG, &temp, 1);

} /* End of mac_InterruptEnable */

/*
 * ----------------------------------------------------------------------------
 * Function Name: mac_InterruptDisable
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void mac_InterruptDisable(void)
{
	U8_T XDATA	temp;

	temp = 0;
	mac_WriteReg(MAC_LINK_CHANGE_INT_ENABLE_REG, &temp, 1);

} /* End of mac_InterruptDisable */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MAC_SetInterruptFlag
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MAC_SetInterruptFlag(void)
{
	mac_ReadReg(MAC_WAKEUP_LINK_INT_STATUS_REG, &mac_InterruptStatus, 1);
	if (!(mac_InterruptStatus & STATUS_PRIMARY_LINK_CHANGE))
		mac_InterruptStatus = 0;

} /* End of MAC_SetInterruptFlag() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MAC_GetInterruptFlag
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T MAC_GetInterruptFlag(void)
{
	U8_T flag, isr;

	isr = EA;
	EA = 0;
	flag = mac_InterruptStatus;
	EA = isr;

	return flag;

} /* End of MAC_GetInterruptFlag() */
#endif

/*
 * ----------------------------------------------------------------------------
 * Function Name: mac_GetMediaType
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T mac_GetMediaType(void)
{
	U16_T	phylinkstatus;

	phylinkstatus = PHY_CheckMediaType();

	PBDP->MacInfo.FullDuplex = TRUE;

	PBDP->MacInfo.MediumLinkType = (MEDIUM_ENABLE_TX_FLOWCTRL | MEDIUM_ENABLE_RECEIVE);

	/* Determine if we're linked to 100 full duplex. */
	if (phylinkstatus & ANLPAR_100TXFD)
	{
		PBDP->MacInfo.LinkSpeed = 100;
		PBDP->MacInfo.MediumLinkType |=(MEDIUM_FULL_DUPLEX_MODE |MEDIUM_MII_100M_MODE);
//		printf ("Link to 100 FULL.\n\r");
	}
	/* Determine if we're linked to 100 half duplex. */
	else if (phylinkstatus & ANLPAR_100TX)
	{
		PBDP->MacInfo.LinkSpeed = 100;
		PBDP->MacInfo.MediumLinkType |= MEDIUM_MII_100M_MODE;
		PBDP->MacInfo.FullDuplex = FALSE;
//		printf ("Link to 100 HALF.\n\r");
	} 
	/* Determine if we're linked to 10 full duplex. */
	else if (phylinkstatus & ANLPAR_10TFD)
	{
		PBDP->MacInfo.LinkSpeed = 10;
		PBDP->MacInfo.MediumLinkType |= MEDIUM_FULL_DUPLEX_MODE;
//		printf ("Link to 10 FULL.\n\r");
	}
	/* we're linked to 10 half duplex. */
	else
	{
		PBDP->MacInfo.LinkSpeed = 10;
		PBDP->MacInfo.FullDuplex = FALSE;
//		printf ("Link to 10 HALF.\n\r");
	}

	if (PBDP->MacInfo.FullDuplex)
		PBDP->MacInfo.MediumLinkType |= MEDIUM_ENABLE_RX_FLOWCTRL;
	mac_WriteReg(MAC_MEDIUM_STATUS_MODE_REG, &PBDP->MacInfo.MediumLinkType, 1);

	return PBDP->MacInfo.LinkSpeed;

} /* End of mac_GetMediaType */

#if (MAC_GET_INTSTATUS_MODE == MAC_INTERRUPT_MODE)
/*
 * ----------------------------------------------------------------------------
 * Function Name: mac_LinkSpeedChk
 * Purpose:
 * Params: none
 * Returns:	100: Ethernet is link to 100M
 *			10 : Ethernet is link to 10M
 *			0  : not link
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T mac_LinkSpeedChk(void)
{
	if (mac_InterruptStatus & STATUS_PRIMARY_IS_LINK_UP)
	{
		mac_InterruptStatus = 0;
		if (PBDP->MacInfo.NetworkType != MAC_FORCE_ENBEDDED_PHY_10_HALF)
		{
			mac_GetMediaType();
		}
		else
		{
			PBDP->MacInfo.FullDuplex = 0;
			PBDP->MacInfo.LinkSpeed = 10;

			PBDP->MacInfo.MediumLinkType = MEDIUM_ENABLE_RECEIVE;
			mac_WriteReg(MAC_MEDIUM_STATUS_MODE_REG, &PBDP->MacInfo.MediumLinkType, 1);
		}

		/* start operation */
		mac_StartOperate();
		DELAY_Ms(0x30);
	}
	else
	{
		mac_InterruptStatus = 0;		
		if (PBDP->MacInfo.LinkSpeed)
		{
			PBDP->MacInfo.LinkSpeed = 0;

			/* disable receive */
			PBDP->MacInfo.MediumLinkType &= ~MEDIUM_ENABLE_RECEIVE;
			mac_WriteReg(MAC_MEDIUM_STATUS_MODE_REG, &PBDP->MacInfo.MediumLinkType, 1);

			STOE_WaitHwReleaseRcvBuf();

			/* stop operation and reset Ethernet MAC packet buffer */
			mac_StopOperate();

			if (PBDP->MacInfo.NetworkType != MAC_FORCE_ENBEDDED_PHY_10_HALF)
			{
				PHY_WatchDog();
			}
		}
	}

	return PBDP->MacInfo.LinkSpeed;

} /* End of mac_LinkSpeedChk */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MAC_ProcessInterrupt
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MAC_ProcessInterrupt(void)
{
	mac_InterruptDisable();

	if (mac_InterruptStatus & STATUS_PRIMARY_LINK_CHANGE)
		mac_LinkSpeedChk();

	mac_InterruptEnable();

} /* End of MAC_ProcessInterrupt */
#else
/*
 * ----------------------------------------------------------------------------
 * Function Name: MAC_LinkSpeedChk
 * Purpose:
 * Params: none
 * Returns:	100: Ethernet is link to 100M
 *			10 : Ethernet is link to 10M
 *			0  : not link
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T MAC_LinkSpeedChk(void)
{
	mac_ReadReg(MAC_WAKEUP_LINK_INT_STATUS_REG, &mac_InterruptStatus, 1);
	if (mac_InterruptStatus & STATUS_PRIMARY_IS_LINK_UP)
	{
		if (PBDP->MacInfo.LinkSpeed == 0)
		{
			if (PBDP->MacInfo.NetworkType != MAC_FORCE_ENBEDDED_PHY_10_HALF)
			{
				mac_GetMediaType();
			}
			else
			{
				PBDP->MacInfo.FullDuplex = 0;
				PBDP->MacInfo.LinkSpeed = 10;

				PBDP->MacInfo.MediumLinkType = MEDIUM_ENABLE_RECEIVE;
				mac_WriteReg(MAC_MEDIUM_STATUS_MODE_REG, &PBDP->MacInfo.MediumLinkType, 1);
			}

			/* start operation */
			mac_StartOperate();
			DELAY_Ms(0x30);
		}
	}
	else
	{
		if (PBDP->MacInfo.LinkSpeed)
		{
			PBDP->MacInfo.LinkSpeed = 0;

			/* disable receive */
			PBDP->MacInfo.MediumLinkType &= ~MEDIUM_ENABLE_RECEIVE;
			mac_WriteReg(MAC_MEDIUM_STATUS_MODE_REG, &PBDP->MacInfo.MediumLinkType, 1);

			STOE_WaitHwReleaseRcvBuf();

			/* stop operation and reset Ethernet MAC packet buffer */
			mac_StopOperate();

			if (PBDP->MacInfo.NetworkType != MAC_FORCE_ENBEDDED_PHY_10_HALF)
			{
				PHY_WatchDog();
			}
		}
	}

	return PBDP->MacInfo.LinkSpeed;

} /* End of MAC_LinkSpeedChk */
#endif

#if (MAC_REMOTE_WAKEUP == MAC_SUPPORT)
/*
 * ----------------------------------------------------------------------------
 * Function Name: MAC_WakeupEnable
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MAC_WakeupEnable(U8_T type)
{
	U8_T	temp = 0;

	if (type & MAC_PRIMARY_PHY_LINK_WAKEUP)
		temp |= WAKEUP_BY_PRIMARY_LINK_UP;
	if (type & MAC_MAGIC_PACKET_WAKEUP)
		temp |= WAKEUP_BY_MAGIC_PACKET;
	if (type & MAC_EXTERNAL_PIN_WAKEUP)
		temp |= WAKEUP_BY_EXTER_PIN_TRIG;
	if (type & MAC_MS_FRAME_WAKEUP)
		temp |= WAKEUP_BY_MICROSOFT_FRAME;

	mac_WriteReg(MAC_WAKEUP_INT_ENABLE_REG, &temp, 1);

} /* End of MAC_WakeupEnable() */

/*
* -----------------------------------------------------------------------------
 * Function Name: mac_crc16
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T mac_crc16(U8_T* pbuf, U8_T len)
{
	U16_T	crc, carry;
	U8_T	i, j;
	S8_T	curByte;

	crc = 0xffff;

	for (i = 0; i < len; i++)
	{
		curByte = pbuf[i];
		for (j = 0; j < 8; j++)
		{
			carry = ((crc & 0x8000) ? 1 : 0) ^ (curByte & 0x01);
			crc <<= 1;
			curByte >>= 1;

			if (carry)
			    crc = ((crc ^ 0x8004) | carry);
		}
    }

	return crc;

} /* End of cal_crc16 */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MAC_SetWakeupFrame
 * Purpose: for setting registers about wakeup frame
 * Params:	pWuf : point to MAC_WUF data structure
 * Returns:	0: setting fail.
 *			1: setting success.
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T MAC_SetWakeupFrame(MAC_WUF* pWuf)
{
	U32_T XDATA	mask0, mask1;
	U16_T XDATA crc16;
	U8_T XDATA*	pMask;
	U8_T XDATA	wakeupCmd, offset0, offset1;
	U8_T		mode, i, maskLen, x, y;
	U8_T		frame[64];

	mode = pWuf->Mode;
	offset0 = pWuf->Offset0;
	offset1 = pWuf->Offset1;
	mask0 = pWuf->Mask0;
	mask1 = pWuf->Mask1;

	mac_WriteReg(MAC_WAKEUP_FRAME_OFFSET1, &offset1, 1);
	mac_WriteReg(MAC_WAKEUP_FRAME_OFFSET0, &offset0, 1);
	mac_WriteReg(MAC_WAKEUP_FRAME_MASK1, (U8_T XDATA*)&mask1, 4);
	mac_WriteReg(MAC_WAKEUP_FRAME_MASK0, (U8_T XDATA*)&mask0, 4);

	if (mode < WUF_BOTH_FILTERS) /* single filter */
	{
		if (mode & BIT0)
		{
			wakeupCmd = WAKEUP_FRAME_FILTER1_ENABLE;
			if (mode & BIT1)
				wakeupCmd |= WAKEUP_FRAME_FILTER1_UNI_ENABLE;
		}
		else
		{
			wakeupCmd = WAKEUP_FRAME_FILTER0_ENABLE;
			if (mode & BIT1)
				wakeupCmd |= WAKEUP_FRAME_FILTER0_UNI_ENABLE;
		}
	}
	else if (mode < WUF_CASCADE) /* both filter */
	{
		wakeupCmd = (WAKEUP_FRAME_FILTER1_ENABLE | WAKEUP_FRAME_FILTER0_ENABLE);
		if (mode & BIT1)
			wakeupCmd |= WAKEUP_FRAME_FILTER0_UNI_ENABLE;
	}
	else /* cascade */
	{
		wakeupCmd = (WAKEUP_FRAME_FILTER1_ENABLE | WAKEUP_FRAME_FILTER0_ENABLE |
			WAKEUP_FRAME_CASCADE_ENABLE);
		if (mode & BIT1)
			wakeupCmd |= WAKEUP_FRAME_FILTER0_UNI_ENABLE;
	}

	if ((wakeupCmd & WAKEUP_FRAME_FILTER0_UNI_ENABLE) && (mask0 == 0))
		return 0;

	if ((wakeupCmd & WAKEUP_FRAME_FILTER1_UNI_ENABLE) && (mask1 == 0))
		return 0;

	if ((wakeupCmd & WAKEUP_FRAME_FILTER0_UNI_ENABLE) &&
		!(wakeupCmd & WAKEUP_FRAME_CASCADE_ENABLE))
	{
		maskLen = 0;
		for (i = 0; i < 64; i++) /* clear buffer */
			frame[i] = 0;

		pMask = (U8_T XDATA*)&mask0;
		for (x = 0; x < 4; x++)
		{
			for (y = 0; y < 8; y++)
			{
				if (pMask[3 - x] & (1 << y))
				{
					if ((8*x + y + offset0*2) > pWuf->Length)
						return 0;

					frame[maskLen] = pWuf->Pframe[8*x + y + offset0*2];
					maskLen++;
				}
			}
		}

		crc16 = mac_crc16(frame, maskLen);
		mac_WriteReg(MAC_WAKEUP_FRAME_CRC0, (U8_T XDATA*)&crc16, 2);
		mac_WriteReg(MAC_WAKEUP_FRAME_LAST_BYTE0, &frame[maskLen -1], 1);
	}

	if ((wakeupCmd & WAKEUP_FRAME_FILTER1_UNI_ENABLE) &&
		!(wakeupCmd & WAKEUP_FRAME_CASCADE_ENABLE))
	{
		maskLen = 0;
		for (i = 0; i < 64; i++) /* clear buffer */
			frame[i] = 0;

		pMask = (U8_T XDATA*)&mask1;
		for (x = 0; x < 4; x++)
		{
			for (y = 0; y < 8; y++)
			{
				if (pMask[3 - x] & (1 << y))
				{
					if ((8*x + y + offset1*2) > pWuf->Length)
						return 0;

					frame[maskLen] = pWuf->Pframe[8*x + y + offset1*2];
					maskLen++;
				}
			}
		}

		crc16 = mac_crc16(frame, maskLen);
		mac_WriteReg(MAC_WAKEUP_FRAME_CRC1, (U8_T XDATA*)&crc16, 2);
		mac_WriteReg(MAC_WAKEUP_FRAME_LAST_BYTE1, &frame[maskLen -1], 1);
	}

	if (wakeupCmd & WAKEUP_FRAME_CASCADE_ENABLE)
	{
		maskLen = 0;
		for (i = 0; i < 64; i++) /* clear buffer */
			frame[i] = 0;

		pMask = (U8_T XDATA*)&mask0;
		for (x = 0; x < 4; x++)
		{
			for (y = 0; y < 8; y++)
			{
				if (pMask[3 - x] & (1 << y))
				{
					if ((8*x + y + offset0*2) > pWuf->Length)
						return 0;

					frame[maskLen] = pWuf->Pframe[8*x + y + offset0*2];
					maskLen++;
				}
			}
		}

		pMask = (U8_T XDATA*)&mask1;
		for (x = 0; x < 4; x++)
		{
			for (y = 0; y < 8; y++)
			{
				if (pMask[3 - x] & (1 << y))
				{
					if ((8*x + y + (offset1 + offset0)*2 + 32) > pWuf->Length)
						return 0;

					frame[maskLen] = pWuf->Pframe[8*x + y + (offset1 + offset0)*2 + 32];
					maskLen++;
				}
			}
		}

		crc16 = mac_crc16(frame, maskLen);
		mac_WriteReg(MAC_WAKEUP_FRAME_CRC1, (U8_T XDATA*)&crc16, 2);
		mac_WriteReg(MAC_WAKEUP_FRAME_LAST_BYTE1, &frame[maskLen -1], 1);
	}

	mac_WriteReg(MAC_WAKEUP_FRAME_COMMAND, &wakeupCmd, 1);
	return 1;

} /* End of MAC_SetWakeupFrame() */

/*
* -----------------------------------------------------------------------------
 * Function Name: MAC_SystemSleep
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MAC_SystemSleep(void)
{
	U8_T XDATA	temp;

	/* disable mac receive */
	mac_ReadReg(MAC_MEDIUM_STATUS_MODE_REG, &temp, 1);
	temp &= 0xfb;
	mac_WriteReg(MAC_MEDIUM_STATUS_MODE_REG, &temp, 1);

	DELAY_Ms(500);
	PCON = SWB_;
	PCON |= STOP_;

	DELAY_Ms(500);

	/* enable mac receive */
	mac_ReadReg(MAC_MEDIUM_STATUS_MODE_REG, &temp, 1);
	temp |= 4;
	mac_WriteReg(MAC_MEDIUM_STATUS_MODE_REG, &temp, 1);

} /* End of MAC_SystemSleep() */
#endif

#if (MAC_MULTICAST_FILTER == MAC_SUPPORT)
/*
* -----------------------------------------------------------------------------
 * Function Name: mac_ComputeCrc32
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T mac_ComputeCrc32(U16_T length, U8_T* pbuf)
{
	U32_T	crc32 = 0xffffffff;
	U8_T	curByte, carry, j;
	
	for (; length; length--)
	{
		curByte = *pbuf++;
		for (j=0; j<8; j++)
		{
			carry = curByte & 1;
			if ( crc32 & 0x80000000 )
				carry ^= 1;
			crc32 <<= 1;
			curByte >>= 1;
			if (carry)
				crc32 ^= 0x04c11db7;
		}
	}
	return crc32;

} /* End of mac_ComputeCrc32() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MAC_MultiFilter
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MAC_MultiFilter(U8_T* pbuf, U8_T len)
{
	U8_T	count = len/MAC_ADDRESS_LEN;
	U8_T	index, bitNum;
	U8_T 	filter[8] = {0};

	for (index = 0; index < count; index++)
	{
		if (!(pbuf[0] & 1))
			break;

		bitNum = (U8_T)((mac_ComputeCrc32(MAC_ADDRESS_LEN, pbuf)>>26)&0x3f);
		pbuf += MAC_ADDRESS_LEN;
		filter[7 - (bitNum/8)] |= (1 << (bitNum % 8));
	}

	mac_WriteReg(MAC_MULTICASE_REG, filter, 8);

} /* End of MAC_MultiFilter() */
#endif


/* End of mac.c */