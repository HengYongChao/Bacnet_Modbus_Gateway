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
 * Module Name: stoe.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: stoe.c,v $
 * Revision 1.1.1.1  2006/06/20 05:50:28  borbin
 * no message
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "reg80390.h"
#include "stoe.h"
#include "dma.h"
#include "delay.h"
#include "interrupt.h"
#include <intrins.h>

/* GLOBAL VARIABLES DECLARATIONS */
LOCAL_STATION XDATA* PNetStation = {0};
BUF_DESC_PAGE XDATA* PBDP = 0;
void (*STOE_RcvCallback)(U8_T XDATA*, U16_T, U8_T); /* call eth layer rcv process
														function. */

/* LOCAL VARIABLES DECLARATIONS */
static U8_T XDATA stoe_BufferSize[STOE_SOCKET_BUFFER_SIZE] _at_ STOE_BDP_START_ADDR;
static U8_T XDATA stoe_InterruptStatus = 0;

/* LOCAL SUBPROGRAM DECLARATIONS */
static void stoe_BdpInit(void);
#if (STOE_GET_INTSTATUS_MODE == STOE_INTERRUPT_MODE)
  static void stoe_InterruptEnable(void);
#endif
static void stoe_StartOperate(void);
static void stoe_RcvHandle(void);

/*
 * ----------------------------------------------------------------------------
 * Function Name: stoe_ReadReg
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void stoe_ReadReg(U8_T regaddr, U8_T XDATA* pbuf, U8_T length)
{
	U8_T	isr;

	isr = EA;
	EA = 0;
	_nop_();
	TCIR = regaddr;
	while (length--)
		pbuf[length] = TDR;
	EA = isr;

} /* End of stoe_ReadReg */

/*
 * ----------------------------------------------------------------------------
 * Function Name: stoe_WriteReg
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void stoe_WriteReg(U8_T regaddr, U8_T XDATA* pbuf, U8_T length)
{
	U8_T	isr;

	isr = EA;
	EA = 0;
	while (length--)
		TDR = pbuf[length];
	TCIR = regaddr;
	EA = isr;

} /* End of stoe_WriteReg */

/*
 * ----------------------------------------------------------------------------
 * Function Name: STOE_Init
 * Purpose: to initial all registers and variables of STOE. 
 * Params: network_type -0: auto- negotiation
 *						-1: fixed 100 full speed.
 *						-2: fixed 100 half speed.
 *						-3: fixed 10 full speed.
 *						-4: fixed 10 half speed.
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_Init(U8_T network_type)
{
	U8_T XDATA	temp[2];
	U8_T XDATA	value[6] = {0,0,0,0,0,0};
#if (STOE_TRANSPARENT != STOE_TRANSPARENT_MODE)
	U8_T XDATA	result[6];
	U8_T XDATA	index, count;
#endif

	/* set xmit & rcv memory. */
	stoe_BdpInit();

	PNetStation = &PBDP->NetStation;

	/* source IP */
	stoe_ReadReg(STOE_IP_ADDR_REG, (U8_T XDATA*)&PNetStation->DefaultIP, 4);
	PNetStation->StationIP = PNetStation->DefaultIP;

	/* subnet mask */
	stoe_ReadReg(STOE_SUBNET_MASK_REG, (U8_T XDATA*)&PNetStation->DefaultMask, 4);
	PNetStation->SubnetMask = PNetStation->DefaultMask;

	/* gateway */
	stoe_ReadReg(STOE_GATEWAY_IP_REG, (U8_T XDATA*)&PNetStation->DefaultGateway, 4);
	PNetStation->Gateway = PNetStation->DefaultGateway;

	/* set L2 control register */
#if (STOE_TRANSPARENT == STOE_TRANSPARENT_MODE)
	temp[0] = (RX_TRANSPARENT | TX_TRANSPARENT);
#else
	temp[0] = 0;
#endif
//#if (STOE_ADD_SNAP_HEADER)
//	temp[0] |= TX_SNAP_ENABLE;
//#endif
	stoe_WriteReg(STOE_L2_CTL_REG, temp, 1);

	/* set ARP table timeout register */
	temp[0] = STOE_ARP_TIMEOUT;
	stoe_WriteReg(STOE_ARP_TIMEOUT_REG, temp, 1);

	/* set L4 control register */
#if (STOE_CHECKSUM_OFFLOAD)
	temp[0] = (DROP_CHKSUMERR_PKT | ENABLE_XMIT_CHKSUM | ENABLE_XMIT_CROSS);
#else
	temp[0] = ENABLE_XMIT_CROSS;
#endif
	stoe_WriteReg(STOE_L4_CTL_REG, temp, 1);

	/* set BDP point */
	temp[0] = (STOE_BDP_START_ADDR >> 16);
	temp[1] = (STOE_BDP_START_ADDR >> 8);
	stoe_WriteReg(STOE_L4_BDP_PNT_REG, temp, 2);

	/* receive callback function initialize to null point. */
	STOE_RcvCallback = 0;

	DMA_Init();
	DELAY_Init();
	MAC_Init(network_type);

#if (STOE_TRANSPARENT != STOE_TRANSPARENT_MODE)
	/* clear arp table */
	for (index = 0; index < 128 ; index++)
	{
		count = (index * 2);
		stoe_WriteReg(STOE_ARP_ADDR_REG, &count, 1);
		count = (ARP_CACHE_CMD_READ | ARP_CACHE_CMD_GO);
		stoe_WriteReg(STOE_ARP_CMD_REG, &count, 1);

		while (count & ARP_CACHE_CMD_GO)
			stoe_ReadReg(STOE_ARP_CMD_REG, &count, 1);

		stoe_ReadReg(STOE_ARP_DATA_REG, result, 6);

		if (result[0] & BIT7)
		{
			count = (index * 2);
			stoe_WriteReg(STOE_ARP_ADDR_REG, &count, 1);
			stoe_WriteReg(STOE_ARP_DATA_REG, value, 6);
			count = ARP_CACHE_CMD_GO;
			stoe_WriteReg(STOE_ARP_CMD_REG, &count, 1);
			while (count & ARP_CACHE_CMD_GO)
				stoe_ReadReg(STOE_ARP_CMD_REG, &count, 1);
		}
	}
#endif

} /* End of STOE_Init */

/*
* -----------------------------------------------------------------------------
 * Function Name: stoe_BdpInit
 * Purpose: initial Buffer Descriptor Page.
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void stoe_BdpInit(void)
{
	U16_T	page = (STOE_BDP_START_ADDR >> 8);

	PBDP = STOE_BDP_START_ADDR;

	// set BDP number
	PBDP->BDP_ID = 0;

	// set rcv buffer.
	PBDP->RSPP = page + 1;
	PBDP->REPP = page + PAGES_OF_RCV;
	PBDP->RHPR = PBDP->RSPP;
	PBDP->RTPR = PBDP->RSPP;
	PBDP->RFP = PAGES_OF_RCV;

	// set xmit buffer.
	PBDP->TSPP = page + 1 + PAGES_OF_RCV;
	PBDP->TEPP = page + PAGES_OF_RCV + PAGES_OF_XMIT;
	PBDP->THPR = PBDP->TSPP;
	PBDP->TTPR = PBDP->TSPP;
	PBDP->TFP = PAGES_OF_XMIT;

	// set rcv and xmit start/end buffer address.
	PBDP->RcvStartAddr = STOE_BDP_START_ADDR + 256;
	PBDP->XmtStartAddr = PBDP->RcvStartAddr + STOE_RCV_BUF_SIZE;
	PBDP->RcvEndAddr = PBDP->XmtStartAddr - 1;
	PBDP->XmtEndAddr = PBDP->XmtStartAddr + STOE_XMIT_BUF_SIZE - 1;

} /* End of stoe_BdpInit */

//#if (STOE_GET_IPADDR_TYPE == STOE_INITIAL_ASSIGN_IP)
/*
 * ----------------------------------------------------------------------------
 * Function Name: STOE_SetIPAddr
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_SetIPAddr(U32_T ip)
{
	if (ip != PNetStation->StationIP)
	{
		PNetStation->StationIP = ip;
		stoe_WriteReg(STOE_IP_ADDR_REG, (U8_T XDATA*)&PNetStation->StationIP, 4);
	}

} /* End of STOE_SetIPAddr*/

/*
 * ----------------------------------------------------------------------------
 * Function Name: STOE_SetSubnetMask
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_SetSubnetMask(U32_T subnet)
{
	if (subnet != PNetStation->SubnetMask)
	{
		PNetStation->SubnetMask = subnet;
		stoe_WriteReg(STOE_SUBNET_MASK_REG, (U8_T XDATA*)&PNetStation->SubnetMask, 4);
	}

} /* End of STOE_SetSubnetMask */

/*
 * ----------------------------------------------------------------------------
 * Function Name: STOE_Gateway
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_SetGateway(U32_T gateway)
{
	if (gateway != PNetStation->Gateway)
	{
		PNetStation->Gateway = gateway;
		stoe_WriteReg(STOE_GATEWAY_IP_REG, (U8_T XDATA*)&PNetStation->Gateway, 4);
	}

} /* End of STOE_SetGateway */ 
//#endif

/*
 * ----------------------------------------------------------------------------
 * Function Name: STOE_Start
 * Purpose: enable all used interrupts and set some register to start
 *			timer, software-dma and processing received packets.
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_Start(void)
{
	U8_T XDATA	temp;

	/* clear interrupt status */
	stoe_ReadReg(STOE_INT_STATUS_REG, &temp, 1);

#if (STOE_GET_INTSTATUS_MODE == STOE_INTERRUPT_MODE)
	/* enable STOE interrupt */
	stoe_InterruptEnable();
#endif

	/* start STOE L2/L3/L4 engines*/
	stoe_StartOperate();

	/* start DMA module */
	DMA_Start();

	/* start MAC module */
	MAC_Start();

	EXTINT4(1);	/* Enable INT4 interrupt for stoe & mac modules. */

} /* End of STOE_Start */

#if (STOE_GET_INTSTATUS_MODE == STOE_INTERRUPT_MODE)
/*
 * ----------------------------------------------------------------------------
 * Function Name: stoe_InterruptEnable
 * Purpose: enable STOE used interrupt
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void stoe_InterruptEnable(void)
{
	U8_T XDATA	temp;

	temp = STOE_DEFAULT_INT_MASK;
	stoe_WriteReg(STOE_INT_MASK_REG, &temp, 1);

} /* End of stoe_InterruptEnable */

/*
 * ----------------------------------------------------------------------------
 * Function Name: stoe_InterruptDisable
 * Purpose: disable STOE used interrupt
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void stoe_InterruptDisable(void)
{
	U8_T XDATA	temp;

	temp = 0;
	stoe_WriteReg(STOE_INT_MASK_REG, &temp, 1);

} /* End of stoe_InterruptDisable */

/*
 * ----------------------------------------------------------------------------
 * Function Name: STOE_SetInterruptFlag
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_SetInterruptFlag(void)
{
	U8_T XDATA	int_status;

	/* disable stoe interrupt*/
	stoe_InterruptDisable();

	/* read stoe interrupt status */
	stoe_ReadReg(STOE_INT_STATUS_REG, &int_status, 1);

	stoe_InterruptStatus = (int_status & STOE_DEFAULT_INT_MASK);

} /* End of STOE_SetInterruptFlag */

/*
 * ----------------------------------------------------------------------------
 * Function Name: STOE_GetInterruptFlag
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T STOE_GetInterruptFlag(void)
{
	return stoe_InterruptStatus;

} /* End of STOE_SetInterruptFlag */

/*
 * ----------------------------------------------------------------------------
 * Function Name: STOE_ProcessInterrupt
 * Purpose: When STOE interrupt is trigged, programmer can call this function
 *			to process interrupt event. 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_ProcessInterrupt(void)
{
	U8_T XDATA	temp;
	U8_T		isr = EA;

	while (stoe_InterruptStatus)
	{
		EA = isr;

		if (stoe_InterruptStatus & RCV_PACKET)
		{
			while (PBDP->RFP < PAGES_OF_RCV)
				stoe_RcvHandle();
		}
		if (stoe_InterruptStatus & RCV_BUF_RING_FULL)
		{
//			printf ("\rRX Packet Buffer Ring is Full.\n\r");
			temp = RESUME_PKT_RCV;
			stoe_WriteReg(STOE_L4_CMD_REG, &temp, 1);
		}

		isr = EA;
		EA = 0;

		/* read stoe interrupt status */
		stoe_ReadReg(STOE_INT_STATUS_REG, &stoe_InterruptStatus, 1);
		stoe_InterruptStatus &= STOE_DEFAULT_INT_MASK;
	}

	/* ensable stoe interrupt */
	stoe_InterruptEnable();
	EA = isr;

} /* End of STOE_ProcessInterrupt() */
#else
/*
 * ----------------------------------------------------------------------------
 * Function Name: STOE_ProcessInterrupt
 * Purpose: programmer can call this function by polling type to find that
 *			interrupt event had happened.
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_ProcessInterrupt(void)
{
	static U8_T XDATA	int_status;
	U8_T XDATA			temp;

	while (1)
	{
		/* read stoe interrupt status */
		stoe_ReadReg(STOE_INT_STATUS_REG, &int_status, 1);
		int_status &= STOE_DEFAULT_INT_MASK;

		if (!int_status)
			break;

		if (int_status & RCV_PACKET)
		{
			while (PBDP->RFP < PAGES_OF_RCV)
				stoe_RcvHandle();
		}
		if (int_status & RCV_BUF_RING_FULL)
		{
//			printf ("\rRX Packet Buffer Ring is Full.\n\r");
			temp = RESUME_PKT_RCV;
			stoe_WriteReg(STOE_L4_CMD_REG, &temp, 1);
		}
	}
}

#endif

/*
 * ----------------------------------------------------------------------------
 * Function Name: STOE_WaitHwReleaseRcvBuf
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_WaitHwReleaseRcvBuf(void)
{
	U8_T XDATA	temp;
	U8_T		isr;

	isr = EA;
	EA = 0;
	if (PBDP->RFP < PAGES_OF_RCV)
	{
		PBDP->RHPR = PBDP->RTPR;
		PBDP->RFP = PAGES_OF_RCV;
	}
	EA = isr;

	temp = RESUME_PKT_RCV;
	stoe_WriteReg(STOE_L4_CMD_REG, &temp, 1);

	DELAY_Us(1000);

	isr = EA;
	EA = 0;
	while (PBDP->RFP < PAGES_OF_RCV)
	{
		PBDP->RHPR = PBDP->RTPR;
		PBDP->RFP = PAGES_OF_RCV;
		EA = isr;

		DELAY_Us(1000);

		isr = EA;
		EA = 0;
	}
	EA = isr;

} /* End of STOE_WaitHwReleaseRcvBuf() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: stoe_StartOperate
 * Purpose: start L2/L3/L4 engine
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void stoe_StartOperate(void)
{
	U8_T XDATA	temp;

	stoe_ReadReg(STOE_L2_CTL_REG, &temp, 1);

	temp |= (RX_START_OPERA | TX_START_OPERA);
	stoe_WriteReg(STOE_L2_CTL_REG, &temp, 1);

} /* End of stoe_StartOperate */

#if 0
/*
 * ----------------------------------------------------------------------------
 * Function Name: stoe_StopOperate
 * Purpose: stop L2/L3/L4 engine
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void stoe_StopOperate(void)
{
	U8_T XDATA	temp;

	stoe_ReadReg(STOE_L2_CTL_REG, &temp, 1);

	Temp &= ~(RX_START_OPERA | TX_START_OPERA);
	stoe_WriteReg(STOE_L2_CTL_REG, &temp, 1);

} /* End of stoe_StopOperate */
#endif

/*
* -----------------------------------------------------------------------------
 * Function Name: stoe_RcvHandle
 * Purpose: 
 * Params: 
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void stoe_RcvHandle(void)
{
	static STOE_FRAME_HEADER XDATA*	pframe;
	U16_T	length;
	U8_T	pages, isr;

	pframe = ((PBDP->RHPR) << 8);
	length = (pframe->Length & 0xfff);

	PBDP->STOE_RxInform.Protocol = pframe->Protocol;
	PBDP->STOE_RxInform.TotalLen = length;
	PBDP->STOE_RxInform.PBuf = &pframe->Packet; 

	if (length && STOE_RcvCallback)
		STOE_RcvCallback(&pframe->Packet, length, pframe->Protocol);

	if (PBDP->RHPR > pframe->NPR)
		pages = (PBDP->TSPP - PBDP->RHPR) + (pframe->NPR - PBDP->RSPP);
	else
		pages = pframe->NPR - PBDP->RHPR;

	isr = EA;
	EA = 0;
	PBDP->RHPR = pframe->NPR;
	PBDP->RFP += pages;
	EA = isr;

} /* End of stoe_RcvHandle */

/*
* -----------------------------------------------------------------------------
 * Function Name: stoe_XmitHandle
 * Purpose: Set send packet bit to tell hardware transmit one packet to ethernet.
 * Params: 
 * Returns:	
 * Note:
 * ----------------------------------------------------------------------------
 */
void stoe_XmitHandle(void)
{
	U8_T XDATA temp;

	stoe_ReadReg(STOE_L4_CMD_REG, &temp, 1);
	while (temp & XMIT_PACKET)
		stoe_ReadReg(STOE_L4_CMD_REG, &temp, 1);

	temp = XMIT_PACKET;
	stoe_WriteReg(STOE_L4_CMD_REG, &temp, 1);

} /* stoe_XmitHandle */

/*
* -----------------------------------------------------------------------------
 * Function Name: STOE_Send
 * Purpose:	Call this function to set add STOE header.
 * Params:	pbuf : buffer address, must between TSPP and TEPP.
 *			length : packet length.
 *			protocol : if the packet is ip packet, set the ip layer protocol,
 *						if not a ip packet, set value to 0xff.
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_Send(U8_T XDATA* pbuf, U16_T length, U8_T protocol)
{
	STOE_FRAME_HEADER XDATA*	pframe =
									(STOE_FRAME_HEADER XDATA*)pbuf;
	U8_T	occupypages = PBDP->STOE_TxInform.Pages;
	U8_T	isr;

	pframe->Length = length;
	pframe->Protocol = protocol;

	isr = EA;
	EA = 0;
	PBDP->TFP -= occupypages;
	EA = isr;

	PBDP->TTPR += occupypages;
	if (PBDP->TTPR > PBDP->TEPP)
		PBDP->TTPR = PBDP->TSPP + PBDP->TTPR - PBDP->TEPP - 1;

	pframe->NPR = PBDP->TTPR;

	stoe_XmitHandle();

} /* End of STOE_Send() */


/*
* -----------------------------------------------------------------------------
 * Function Name: STOE_AssignSendBuf
 * Purpose: Assign a buffer that adress is between TSPP and TEPP, so STOE engine
 *				cans transmit the packet to MAC SRAM.
 * Params: length : Buffer size that the packet occupied.
 * Returns: Assigned transmit buffer address
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T XDATA* STOE_AssignSendBuf(U16_T length)
{
	U8_T XDATA*	pframe;
	U8_T		occupypages;

	occupypages = ((length + PAGE_SIZE - 1)/PAGE_SIZE);

	if (PBDP->TFP <= occupypages)
		return (U8_T XDATA*)0;

	pframe = ((PBDP->TTPR) << 8);
	PBDP->STOE_TxInform.Pages = occupypages;

	return pframe;

} /* End of STOE_AssignSendBuf */

#if (!BOOTLDR_ISR)
/*
* -----------------------------------------------------------------------------
 * Function Name: STOE_CopyCode2TPBR
 * Purpose: 
 * Params: 
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T XDATA* STOE_CopyCode2TPBR(U8_T XDATA* pdest, U8_T* psour, U16_T length)
{
	U16_T	space, leftlen;

	/* destination address is not in range of TPBR. */
	if ((pdest > PBDP->XmtEndAddr) || (pdest < PBDP->XmtStartAddr))
		return 0;

	space = (U16_T)PBDP->XmtEndAddr - (U16_T)pdest + 1;
	if (space > length)
	{
		while (length--)
			*pdest++ = *psour++;
	}
	else
	{
		leftlen = length - space;

		while (space--)
			*pdest++ = *psour++;

		pdest = PBDP->XmtStartAddr;

		while (leftlen--)
			*pdest++ = *psour++;
	}

	return pdest;

} /* End of STOE_CopyCode2TPBR */
#endif

/*
* -----------------------------------------------------------------------------
 * Function Name: STOE_CHECK_MAC
 * Purpose: 
 * Params: 
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T STOE_CHECK_MAC(U32_T *ip_addr)
{
	U8_T entry_addr, result[6] = {0};
	entry_addr = (U8_T)(*ip_addr & 0x7F) * 2;
// 	PRINTD(DEBUG_MSG, ("STOE_CHECK_MAC :: entry_addr = %bx\n\r", entry_addr));
	stoe_WriteReg(STOE_ARP_ADDR_REG, &entry_addr, 1);

	entry_addr = ARP_CACHE_CMD_READ | ARP_CACHE_CMD_GO;
	stoe_WriteReg(STOE_ARP_CMD_REG, &entry_addr, 1);

	stoe_ReadReg(STOE_ARP_DATA_REG, result, 6);

	if (result[0]& 0x80)
		return 1;
	else
		return 0;

} /* End of STOE_CHECK_MAC() */

#if (!STOE_TRANSPARENT)
/*
* -----------------------------------------------------------------------------
 * Function Name: STOE_EnableIpFilter
 * Purpose: Enable hardware IP filter function, the default is enable. 
 * Params: 
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_EnableIpFilter(void)
{
	U8_T XDATA	temp;

	stoe_ReadReg(STOE_L2_CTL_REG, &temp, 1);

	temp &= ~BIT2;
	stoe_WriteReg(STOE_L2_CTL_REG, &temp, 1);

} /* End of STOE_EnableIpFilter() */

/*
* -----------------------------------------------------------------------------
 * Function Name: STOE_DisableIpFilter
 * Purpose:  Disable hardware IP filter function, the default is enable.
 * Params: 
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_DisableIpFilter(void)
{
	U8_T XDATA	temp;

	stoe_ReadReg(STOE_L2_CTL_REG, &temp, 1);

	temp |= BIT2;
	stoe_WriteReg(STOE_L2_CTL_REG, &temp, 1);

} /* End of STOE_DisableIpFilter() */

/*
* -----------------------------------------------------------------------------
 * Function Name: STOE_AddArpTable
 * Purpose: 
 * Params: 
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
BOOL STOE_AddArpTable(U8_T XDATA* MacAddr, U32_T IpAddr, U8_T Static)
{
	U8_T		temp, index;
	U8_T 		value[6];
	U8_T		hash[7];

	temp = (IpAddr * 2);
	index = temp;
	stoe_WriteReg(STOE_ARP_ADDR_REG, &temp, 1);
	temp = (ARP_CACHE_CMD_READ | ARP_CACHE_CMD_GO);
	stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

	while (temp & ARP_CACHE_CMD_GO)
		stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

	stoe_ReadReg(STOE_ARP_DATA_REG, value, 6);

	if ((value[0] & BIT7) && (IpAddr != *((U32_T*)&value[2])))
	{
		hash[0] = (U8_T)(((IpAddr >> 1) & 1) ^ ((IpAddr >> 9) & 1) ^ ((IpAddr >> 17) & 1) ^ ((IpAddr >> 25) & 1));
		hash[1] = (U8_T)(((IpAddr >> 2) & 1) ^ ((IpAddr >> 10) & 1) ^ ((IpAddr >> 18) & 1) ^ ((IpAddr >> 26) & 1));
		hash[2] = (U8_T)(((IpAddr >> 3) & 1) ^ ((IpAddr >> 11) & 1) ^ ((IpAddr >> 19) & 1) ^ ((IpAddr >> 27) & 1));
		hash[3] = (U8_T)(((IpAddr >> 4) & 1) ^ ((IpAddr >> 12) & 1) ^ ((IpAddr >> 20) & 1) ^ ((IpAddr >> 28) & 1));
		hash[4] = (U8_T)(((IpAddr >> 5) & 1) ^ ((IpAddr >> 13) & 1) ^ ((IpAddr >> 21) & 1) ^ ((IpAddr >> 29) & 1));
		hash[5] = (U8_T)(((IpAddr >> 6) & 1) ^ ((IpAddr >> 14) & 1) ^ ((IpAddr >> 22) & 1) ^ ((IpAddr >> 30) & 1));
		hash[6] = (U8_T)(((IpAddr >> 7) & 1) ^ ((IpAddr >> 15) & 1) ^ ((IpAddr >> 23) & 1) ^ ((IpAddr >> 31) & 1));

		temp = (hash[0] << 1) + (hash[1] << 2) + (hash[2] << 3) + (hash[3] << 4) + (hash[4] << 5) + (hash[5] << 6) + (hash[6] << 7);
		index = temp;
		stoe_WriteReg(STOE_ARP_ADDR_REG, &temp, 1);
		temp = (ARP_CACHE_CMD_READ | ARP_CACHE_CMD_GO);
		stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

		while (temp & ARP_CACHE_CMD_GO)
			stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

		stoe_ReadReg(STOE_ARP_DATA_REG, value, 6);

		if ((value[0] & BIT7) && (IpAddr != *((U32_T*)&value[2])))
		{
			return FALSE;
		}
	}

	stoe_WriteReg(STOE_ARP_ADDR_REG, &index, 1);

	value[0] = 0x80 | ((Static & 0x01) << 6);
	value[1] = 0;
	*(U32_T *)&value[2] = IpAddr;
	stoe_WriteReg(STOE_ARP_DATA_REG, value, 6);

	temp = ARP_CACHE_CMD_GO;
	stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

	while (temp & ARP_CACHE_CMD_GO)
		stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

	temp = (index + 1);
	stoe_WriteReg(STOE_ARP_ADDR_REG, &temp, 1);

	stoe_WriteReg(STOE_ARP_DATA_REG, MacAddr, 6);

	temp = ARP_CACHE_CMD_GO;
	stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

	while (temp & ARP_CACHE_CMD_GO)
		stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

	return TRUE;
}
#endif

/* End of stoe.c */