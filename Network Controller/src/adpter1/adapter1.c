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
 * Module Name: adapter.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: adapter.c,v $
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "adapter1.h"
#include "reg80390.h"
#include "stoe.h"
#include "dma.h"
#include "tcpip.h"
#include "pppoe.h"
#include "mstimer.h"
#include "dhcpc.h"

/* NAMING CONSTANT DECLARATIONS */
#define ETH_HEADER_LEN		14
#define ETH_NON_TRANSPARENT	0
#define ETH_TRANSPARENT		1
#define ETH_ARP_SEND_INTERVAL_TIME	180

/* GLOBAL VARIABLES DECLARATIONS */
U8_T ETH_IsPppoe = 0;
U8_T ETH_DoDhcp = 0;
U8_T ETH_PppoeHeaderLen = 0;
U8_T ETH_DhcpArpReply = TRUE;

#if (!STOE_TRANSPARENT)
#define ETH_ARP_ENTRY_TIMEOUT		(128 * 4) /* 128 second */

ETH_ARP_TABLE ETH_ArpTable[ETH_ARP_TABLE_COUNTER];
ETH_FROM_GW ETH_IpFromGw[ETH_ARP_TABLE_COUNTER];
U8_T ETH_GatewayMacAddr[MAC_ADDRESS_LEN];
#endif

/* LOCAL VARIABLES DECLARATIONS */
static U8_T eth_EthHeadLen = 0;
static U16_T eth_PayLoadOffset = 0;
#if (!STOE_TRANSPARENT)
static BOOL eth_GatewayArpStaticFlag = FALSE;
#endif
static U32_T eth_ArpSendIntervalTime = 3;
static U32_T eth_ArpSendTime = 0;

/* LOCAL SUBPROGRAM DECLARATIONS */
static void eth_RcvHandle(U8_T XDATA*, U16_T, U8_T);
#if (!STOE_TRANSPARENT)
static BOOL eth_CheckGatewayIp(U8_T XDATA* pBuf);
#endif



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
	EA = 0;
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
* -----------------------------------------------------------------------------
 * Function Name: STOE_DelArpTableByIndex
 * Purpose: delete the assigned index arp entry from arp table
 * Params: 
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_DelArpTableByIndex(U8_T index)
{
	U8_T XDATA	temp;
	U8_T XDATA	value[6] = {0};

	temp = index * 2;
	stoe_WriteReg(STOE_ARP_ADDR_REG, &temp, 1);
	stoe_WriteReg(STOE_ARP_DATA_REG, value, 6);

	temp = ARP_CACHE_CMD_GO;
	stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

	while (temp & ARP_CACHE_CMD_GO)
		stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

} /* End of STOE_DelArpTableByIndex() */

/*
* -----------------------------------------------------------------------------
 * Function Name: stoe_SetNewGatewayInArpTable
 * Purpose: 
 * Params: 
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_SetNewGatewayInArpTable(U8_T XDATA* macAddr, U32_T gateway)
{
	U8_T XDATA	temp, index;
	U8_T XDATA	value[6];
	U8_T XDATA	hash[7];

	index = (U8_T)((U8_T)gateway * 2);
	stoe_WriteReg(STOE_ARP_ADDR_REG, &index, 1);
	value[0] = 0xC0;
	value[1] = 0;
	*(U32_T *)&value[2] = gateway;
	stoe_WriteReg(STOE_ARP_DATA_REG, value, 6);

	temp = ARP_CACHE_CMD_GO;
	stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

	while (temp & ARP_CACHE_CMD_GO)
		stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

	temp = (index + 1);
	stoe_WriteReg(STOE_ARP_ADDR_REG, &temp, 1);

	stoe_WriteReg(STOE_ARP_DATA_REG, macAddr, 6);

	temp = ARP_CACHE_CMD_GO;
	stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

	while (temp & ARP_CACHE_CMD_GO)
		stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

	hash[0] = (U8_T)(((gateway >> 1) & 1) ^ ((gateway >> 9) & 1) ^ ((gateway >> 17) & 1) ^ ((gateway >> 25) & 1));
	hash[1] = (U8_T)(((gateway >> 2) & 1) ^ ((gateway >> 10) & 1) ^ ((gateway >> 18) & 1) ^ ((gateway >> 26) & 1));
	hash[2] = (U8_T)(((gateway >> 3) & 1) ^ ((gateway >> 11) & 1) ^ ((gateway >> 19) & 1) ^ ((gateway >> 27) & 1));
	hash[3] = (U8_T)(((gateway >> 4) & 1) ^ ((gateway >> 12) & 1) ^ ((gateway >> 20) & 1) ^ ((gateway >> 28) & 1));
	hash[4] = (U8_T)(((gateway >> 5) & 1) ^ ((gateway >> 13) & 1) ^ ((gateway >> 21) & 1) ^ ((gateway >> 29) & 1));
	hash[5] = (U8_T)(((gateway >> 6) & 1) ^ ((gateway >> 14) & 1) ^ ((gateway >> 22) & 1) ^ ((gateway >> 30) & 1));
	hash[6] = (U8_T)(((gateway >> 7) & 1) ^ ((gateway >> 15) & 1) ^ ((gateway >> 23) & 1) ^ ((gateway >> 31) & 1));

	index = (hash[0] << 1) + (hash[1] << 2) + (hash[2] << 3) + (hash[3] << 4) + (hash[4] << 5) + (hash[5] << 6) + (hash[6] << 7);
	stoe_WriteReg(STOE_ARP_ADDR_REG, &index, 1);
	value[0] = 0;
	value[1] = 0;
	value[2] = 0;
	value[3] = 0;
	value[4] = 0;
	value[5] = 0;
	stoe_WriteReg(STOE_ARP_DATA_REG, value, 6);

	temp = ARP_CACHE_CMD_GO;
	stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

	while (temp & ARP_CACHE_CMD_GO)
		stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

} /* End of stoe_SetNewGatewayInArpTable() */


/*
* -----------------------------------------------------------------------------
 * Function Name: STOE_FindArpTableMacAddr
 * Purpose: to find the mac address in hw arp table with the assigned ip
 * Params: 
 * Returns:	FALSE: does not find the ip address in hw arp table
 *			TRUE: find arp entry, the mac address is copied to pbuf
 * Note:
 * ----------------------------------------------------------------------------
 */
BOOL STOE_FindArpTableMacAddr(U32_T ip, U8_T XDATA* pbuf)
{
	U8_T XDATA	temp, index;
	U8_T XDATA	value[6];
	U8_T		hash[7];

	/* linear addressing mode */
	temp = ip * 2;
	index = temp;
	stoe_WriteReg(STOE_ARP_ADDR_REG, &temp, 1);
	temp = (ARP_CACHE_CMD_READ | ARP_CACHE_CMD_GO);
	stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

	while (temp & ARP_CACHE_CMD_GO)
		stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

	stoe_ReadReg(STOE_ARP_DATA_REG, value, 6);

	if ((value[0] & BIT7) && (ip == *((U32_T*)&value[2]))) /* find arp entry */
	{
		temp = index + 1;
		stoe_WriteReg(STOE_ARP_ADDR_REG, &temp, 1);
		temp = (ARP_CACHE_CMD_READ | ARP_CACHE_CMD_GO);
		stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

		while (temp & ARP_CACHE_CMD_GO)
			stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

		stoe_ReadReg(STOE_ARP_DATA_REG, value, 6);
		pbuf[0] = value[0];
		pbuf[1] = value[1];
		pbuf[2] = value[2];
		pbuf[3] = value[3];
		pbuf[4] = value[4];
		pbuf[5] = value[5];

		return TRUE;
	}

	/* XOR addressing mode */
	hash[0] = (U8_T)(((ip >> 1) & 1) ^ ((ip >> 9) & 1) ^ ((ip >> 17) & 1) ^ ((ip >> 25) & 1));
	hash[1] = (U8_T)(((ip >> 2) & 1) ^ ((ip >> 10) & 1) ^ ((ip >> 18) & 1) ^ ((ip >> 26) & 1));
	hash[2] = (U8_T)(((ip >> 3) & 1) ^ ((ip >> 11) & 1) ^ ((ip >> 19) & 1) ^ ((ip >> 27) & 1));
	hash[3] = (U8_T)(((ip >> 4) & 1) ^ ((ip >> 12) & 1) ^ ((ip >> 20) & 1) ^ ((ip >> 28) & 1));
	hash[4] = (U8_T)(((ip >> 5) & 1) ^ ((ip >> 13) & 1) ^ ((ip >> 21) & 1) ^ ((ip >> 29) & 1));
	hash[5] = (U8_T)(((ip >> 6) & 1) ^ ((ip >> 14) & 1) ^ ((ip >> 22) & 1) ^ ((ip >> 30) & 1));
	hash[6] = (U8_T)(((ip >> 7) & 1) ^ ((ip >> 15) & 1) ^ ((ip >> 23) & 1) ^ ((ip >> 31) & 1));

	temp = (hash[0] << 1) + (hash[1] << 2) + (hash[2] << 3) + (hash[3] << 4) + (hash[4] << 5) + (hash[5] << 6) + (hash[6] << 7);
	index = temp;
	stoe_WriteReg(STOE_ARP_ADDR_REG, &temp, 1);
	temp = (ARP_CACHE_CMD_READ | ARP_CACHE_CMD_GO);
	stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

	while (temp & ARP_CACHE_CMD_GO)
		stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

	stoe_ReadReg(STOE_ARP_DATA_REG, value, 6);

	if ((value[0] & BIT7) && (ip == *((U32_T*)&value[2])))
	{
		temp = index + 1;
		stoe_WriteReg(STOE_ARP_ADDR_REG, &temp, 1);
		temp = (ARP_CACHE_CMD_READ | ARP_CACHE_CMD_GO);
		stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

		while (temp & ARP_CACHE_CMD_GO)
			stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

		stoe_ReadReg(STOE_ARP_DATA_REG, value, 6);
		pbuf[0] = value[0];
		pbuf[1] = value[1];
		pbuf[2] = value[2];
		pbuf[3] = value[3];
		pbuf[4] = value[4];
		pbuf[5] = value[5];

		return TRUE;
	}

	return FALSE;

} /* End of STOE_FindArpTableMacAddr() */

/*
* -----------------------------------------------------------------------------
 * Function Name: STOE_SetArpTableByIndex
 * Purpose: set arp entry to assigned index
 * Params: 
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void STOE_SetArpTableByIndex(U8_T XDATA* addr, U32_T ip, U8_T index)
{
	U8_T XDATA	temp;
	U8_T XDATA	value[6];

	temp = index * 2;
	stoe_WriteReg(STOE_ARP_ADDR_REG, &temp, 1);
	value[0] = 0xC0;
	value[1] = 0;
	*(U32_T *)&value[2] = ip;
	stoe_WriteReg(STOE_ARP_DATA_REG, value, 6);

	temp = ARP_CACHE_CMD_GO;
	stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

	while (temp & ARP_CACHE_CMD_GO)
		stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

	temp = (index * 2 + 1);
	stoe_WriteReg(STOE_ARP_ADDR_REG, &temp, 1);

	stoe_WriteReg(STOE_ARP_DATA_REG, addr, 6);

	temp = ARP_CACHE_CMD_GO;
	stoe_WriteReg(STOE_ARP_CMD_REG, &temp, 1);

	while (temp & ARP_CACHE_CMD_GO)
		stoe_ReadReg(STOE_ARP_CMD_REG, &temp, 1);

} /* End of STOE_SetArpTableByIndex() */


























/*
 * ----------------------------------------------------------------------------
 * Function Name: ETH_Init
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void ETH_Init(void)
{
	U8_T*		point;
#if (!STOE_TRANSPARENT)
	U8_T		index;
#endif

	/* ethernet initiation */
	STOE_Init(ETH_PHY_SENSE_TYPE);
	STOE_RcvCallback = eth_RcvHandle;

#if (STOE_TRANSPARENT)
	/* Initialise TCP/UDP up-layer interfaces */
	TCPIP_Init(ETH_TRANSPARENT);
	eth_EthHeadLen = ETH_HEADER_LEN;
#else
	TCPIP_Init(ETH_NON_TRANSPARENT);
	eth_EthHeadLen = 0;
#endif
    /* Initialise the ARP cache. */
	point =	MAC_GetMacAddr();
	TCPIP_SetMacAddr(point);

	TCPIP_AssignLowlayerXmitFunc(ETH_Send);

	/* PPPoE initiation */
	PPPOE_Init();

#if (!STOE_TRANSPARENT)
	for (index = 0; index < ETH_ARP_TABLE_COUNTER; index++)
	{
		ETH_ArpTable[index].Valid = 0;
		ETH_IpFromGw[index].Valid = 0;
	}
#endif

} /* End of ETH_Init */

/*
 * ----------------------------------------------------------------------------
 * Function Name: ETH_Start
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void ETH_Start(void)
{
	STOE_Start();

} /* End of ETH_Start */

/*
 * ----------------------------------------------------------------------------
 * Function Name: eth_RcvHandle
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void eth_RcvHandle(U8_T XDATA* pbuf, U16_T length, U8_T protocol)
{
	/* copy packet into uIP buffer */
	DMA_GrantXdata(TCPIP_GetRcvBuffer(), pbuf, length);

	TCPIP_SetRcvLength(length);

#if (STOE_TRANSPARENT == STOE_NON_TRANSPARENT_MODE)
	if (protocol == 0xff)
	{
		if ((*pbuf > 0x44) && (*pbuf < 0x50))
		{
			protocol = *(pbuf + 9);
			PBDP->STOE_RxInform.Protocol = protocol;
		}
	}
#endif

	switch (protocol)
	{
	default:
		break;
	case 1:
	case 2:
	case 6:
	case 17:
#if STOE_TRANSPARENT
		if (ETH_IsPppoe)
		{
			if (!PPPOE_Receive(TCPIP_GetRcvBuffer(), length))
				return;
		}
		else if (ETH_DoDhcp == 0)
			uip_arp_ipin();
#endif
		TCPIP_Receive();
		if(TCPIP_GetXmitLength() > 0)
		{
#if STOE_TRANSPARENT
			if (!ETH_IsPppoe)
				uip_arp_out();
#endif
			ETH_Send(0);
		}
		break;
	case 0xff:
#if STOE_TRANSPARENT
		if (ETH_IsPppoe)
		{
			if (!PPPOE_Receive(TCPIP_GetRcvBuffer(), length))
				return;
		}
		else
		{
			if(pbuf[12] == 0x08 && pbuf[13] == 0x06)
			{
				uip_arp_arpin();
				if ((pbuf[21] == 0x02) && ((*(U32_T *)&pbuf[28]) == STOE_GetIPAddr()))
				{
					if (ETH_CheckDhcpArpReply() == FALSE)
						ETH_SetDhcpArpReplyFlag(TRUE);
				}
				else
				{
	        	    if(TCPIP_GetXmitLength() > 0)
						ETH_Send(0);

					if (TCPIP_GetGwMacAddrFlag())
						eth_ArpSendIntervalTime = ETH_ARP_SEND_INTERVAL_TIME;
				}
			}
		}
#else
		// receive a arp reply packet, check the ip.
		// If this ip is the gateway's ip, update the hardware arp table,
		// and set it static
		if(pbuf[12] == 0x08 && pbuf[13] == 0x06 && pbuf[21] == 0x02)
		{
			if ((*(U32_T *)&pbuf[28]) == STOE_GetIPAddr())
			{
				if (ETH_CheckDhcpArpReply() == FALSE)
					ETH_SetDhcpArpReplyFlag(TRUE);
			}
			else if (eth_CheckGatewayIp(pbuf))
			{
				if (eth_GatewayArpStaticFlag == FALSE)
				{
					U8_T	index, number, j;

					for (index = 0; index < ETH_ARP_TABLE_COUNTER; index++)
					{
						if ((ETH_ArpTable[index].Valid) &&
							(ETH_ArpTable[index].HwTableIndex == (pbuf[31] & 0x7f)))
						{
							/* clrar the old arp entry because gateway is going to
							   create it's arp entry in the same index */
							ETH_ArpTable[index].Valid = 0;
							STOE_DelArpTableByIndex(ETH_ArpTable[index].HwTableIndex);
						}
					}

					number = 0;					
					for (index = ETH_ARP_TABLE_COUNTER; index > 0; index--)
					{
						if (ETH_ArpTable[index -1].Valid)
						{
							if (ETH_ArpTable[index -1].IP == *(U32_T*)&pbuf[28])
							{
								number = index -1;
								ETH_ArpTable[number].Static = 1;
								ETH_ArpTable[number].Timer = 0;
								ETH_ArpTable[number].HwTableIndex = pbuf[31] & 0x7f;/* 0..127 */
								for (j = 0; j < MAC_ADDRESS_LEN; j++)
									ETH_ArpTable[number].MacAddr[j] = pbuf[6 + j];

								break;
							}
						}
						else
						{
							number = index - 1;
						}
					}

					if (index == 0) /* not found in sw arp table */
					{
						ETH_ArpTable[number].Valid = 1;
						ETH_ArpTable[number].Static = 1;
						ETH_ArpTable[number].Timer = 0;
						ETH_ArpTable[number].HwTableIndex = pbuf[31] & 0x7f; /* 0..127 */
						ETH_ArpTable[number].IP = *(U32_T*)&pbuf[28];
						for (j = 0; j < MAC_ADDRESS_LEN; j++)
							ETH_ArpTable[number].MacAddr[j] = pbuf[6 + j];
					}

					for (j = 0; j < MAC_ADDRESS_LEN; j++)
						ETH_GatewayMacAddr[j] = pbuf[6 + j];

					STOE_SetNewGatewayInArpTable(&pbuf[6], *(U32_T *)&pbuf[28]);
					eth_GatewayArpStaticFlag = TRUE;
				}
				eth_ArpSendIntervalTime = ETH_ARP_SEND_INTERVAL_TIME;
			}
			else
			{
				ETH_AddArpTable(&pbuf[6], *(U32_T *)&pbuf[28], ETH_ARP_ENTRY_DYNAMIC);
			}
		} 
#endif
		break;
	}  /* End of switch */

} /* End of eth_RcvHandle */

/*
* -----------------------------------------------------------------------------
 * Function Name: ETH_Send
 * Purpose: Copy Data to Mac ram and send to Ethernet.
 * Params: 
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void ETH_Send(U16_T	payloadOffset)
{
	U16_T	length = TCPIP_GetXmitLength();

	eth_PayLoadOffset = payloadOffset;

#if STOE_TRANSPARENT
	if (ETH_IsPppoe)
	{
	 	length += (eth_EthHeadLen + ETH_PppoeHeaderLen);
		if (!PPPOE_GetState())
			return;

		PPPOE_Send (TCPIP_GetXmitBuffer(), length);
	}
#endif

	ETH_SendPkt(TCPIP_GetXmitBuffer(), length);
		
} /* End of ETH_Send() */

/*
* -----------------------------------------------------------------------------
 * Function Name: ETH_SendPkt
 * Purpose: Copy Data to Mac ram and send to Ethernet.
 * Params: none
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void ETH_SendPkt(U8_T XDATA* psour, U16_T length)
{
	U8_T XDATA* pBuf;
	U8_T XDATA* point;
	U16_T		len;
	U16_T		addr;
	U8_T		isPppoeIp = 0;
	U16_T		totalLen = length;
	U32_T	sourIp = STOE_GetIPAddr();
	U32_T	destIp = *(U32_T*)&psour[16];
	U8_T	mode = 0;

	if (!PBDP->MacInfo.LinkSpeed)
		return;

#if (!STOE_TRANSPARENT)
	while (1)
	{
		U32_T		gatewayIp = STOE_GetGateway();
		U32_T		subnetMask = STOE_GetSubnetMask();
		U8_T XDATA	macAddr[6];
		U8_T		index;

 		/* not ip packet, or ip packet but is broadcast or multicast packet,
		send this packet directly */
		if ((*psour!=0x45)||((*psour==0x45)&&((psour[19]==0xff)||((psour[16]>=0xe0)&&(psour[16]<=0xef)))))
		{
			break;
		}

		if (!eth_GatewayArpStaticFlag) /*has not got gateway ip or mac address*/
		{
			/* different subnet mask, drop this packet */
			if ((sourIp & subnetMask) != (destIp & subnetMask))
			{
				eth_PayLoadOffset = 0; /* clear offset flag */
				return;
			}

			/* same subnet mask */
			if (ETH_FindArpTable(destIp))	/* find ip in sw arp table, */
			{								/*send this packet directly*/
				break;
			}
			/* does not find ip in sw arp table */
			mode = 1; /* send arp request */
			break;
		}

		/* has got gateway ip and mac address */
		if (gatewayIp == destIp) /* send this packet directly */
		{
			break;
		}

		if ((sourIp & subnetMask) != (destIp & subnetMask)) /* different subnet mask */
		{
			break;
		}

		if (ETH_FindArpTable(destIp)) /* find dest ip in sw arp table, send this packet directly */
		{
			break;
		}

		if (ETH_FindIpFromGwTable(destIp)) /* find dest ip in sw from-outside-subnet table */
		{
			mode = 1; /* send arp request frame */
			break;
		}

		/* find the dest ip in hw arp table */
		if (STOE_FindArpTableMacAddr(destIp, macAddr))
		{
			for (index = 0; index < MAC_ADDRESS_LEN; index++)
			{
				/* mac address is different */
				if (ETH_GatewayMacAddr[index] != macAddr[index])
					break;
			}

			/* if the mac address is equal to gateway mac address, add the desp ip to sw from-outside-subnet table */
			if (index == MAC_ADDRESS_LEN)
			{
				ETH_AddIpFromGwTable(destIp);
				mode = 1; /* send arp request frame */
				break;
			}
			else /* the mac address in hardware table is not equal to gateway mac address*/
			{
				ETH_AddArpTable(macAddr, destIp, ETH_ARP_ENTRY_DYNAMIC);
				break; /* send this packet directly */
			}
		}
		else
		{
			mode = 1; /* send arp request frame */
			break;
		}

		break; /* send this packet directly */
	}

	if (mode == 1)
	{
		/* send arp request frame to query mac address */
		*(U32_T *)&psour[38] = destIp;

		point = MAC_GetMacAddr();
		length = 42;
		psour[0] = 0xFF;
		psour[1] = 0xFF;
		psour[2] = 0xFF;
		psour[3] = 0xFF;
		psour[4] = 0xFF;
		psour[5] = 0xFF;
		psour[6] = *(point);
		psour[7] = *(point + 1);
		psour[8] = *(point + 2);
		psour[9] = *(point + 3);
		psour[10] = *(point + 4);
		psour[11] = *(point + 5);
		psour[12] = 0x08; 
		psour[13] = 0x06;
		psour[14] = 0x00;
		psour[15] = 0x01;
		psour[16] = 0x08;
		psour[17] = 0x00;
		psour[18] = 0x06;
		psour[19] = 0x04;
		psour[20] = 0x00;
		psour[21] = 0x01;
		psour[22] = *(point);
		psour[23] = *(point + 1);
		psour[24] = *(point + 2);
		psour[25] = *(point + 3);
		psour[26] = *(point + 4);
		psour[27] = *(point + 5);
		*(U32_T *)&psour[28] = sourIp;

		psour[32] = 0x00;
		psour[33] = 0x00;
		psour[34] = 0x00;
		psour[35] = 0x00;
		psour[36] = 0x00;
		psour[37] = 0x00;

		eth_PayLoadOffset = length;
		totalLen = length;
	}
#endif

	pBuf = STOE_AssignSendBuf(length + MAC_TX_RX_HEADER);
	if (!pBuf)
		return;
	point = pBuf + MAC_TX_RX_HEADER;

#if STOE_TRANSPARENT
	if (ETH_IsPppoe)
	{
		if ((*(psour + 12) == 0x88) && (*(psour + 13) == 0x64) && (*(psour + 20) == 0) && (*(psour + 21) == 0x21))
		{
			isPppoeIp = 1;
			PBDP->STOE_TxInform.Protocol = *(psour + 31);
		}
		else
		{
			eth_PayLoadOffset = length;
			PBDP->STOE_TxInform.Protocol = 0xff;
		}
	}
	else
#endif
	{
#if STOE_TRANSPARENT
		if ((*(psour + 12) == 8) && (*(psour + 13) == 0))
			PBDP->STOE_TxInform.Protocol = *(psour + 23);
		else
			PBDP->STOE_TxInform.Protocol = 0xff;
#else
		if (*psour == 0x45)
			PBDP->STOE_TxInform.Protocol = *(psour + 9);
		else
			PBDP->STOE_TxInform.Protocol = 0xff;
#endif
	}

	if (pBuf)
	{
		if (eth_PayLoadOffset)
			len = eth_PayLoadOffset;
		else
		{
#if STOE_TRANSPARENT
			if (ETH_IsPppoe)
				len = 48 + eth_EthHeadLen;
			else
#endif
				len = 40 + eth_EthHeadLen;
		}

		if (length > len)
		{
			/* Do software DMA */
			DMA_GrantXdata(point, TCPIP_GetXmitBuffer(), len);

			point += len;
			length -= len;

			addr = (U32_T)(TCPIP_GetPayloadBuffer()) >> 8;

			if(addr > 0x8000)	/*if(flag_dataincode)*/
				STOE_CopyCode2TPBR(point, TCPIP_GetPayloadBuffer(), length);
			else if (addr >= 0x200)
				DMA_Grant(point, TCPIP_GetPayloadBuffer(), length);
			else
				DMA_GrantXdata(point, TCPIP_GetPayloadBuffer(), length);
		}
		else
		{
			/* Do software DMA */
			DMA_GrantXdata(point, TCPIP_GetXmitBuffer(), len);

		} /* End of if (length > len) */

#if STOE_TRANSPARENT
		if (isPppoeIp)
			pBuf[5] = 0x80;
		else
#endif
			pBuf[5] = 0;
		STOE_Send(pBuf, totalLen, PBDP->STOE_TxInform.Protocol);
	}

	eth_PayLoadOffset = 0; /* clear offset flag */

} /* End of ETH_SendPkt() */

/*
* -----------------------------------------------------------------------------
 * Function Name: eth_CheckGatewayIp
 * Purpose: Copy Data to Mac ram and send to Ethernet.
 * Params: none
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
BOOL eth_CheckGatewayIp(U8_T XDATA* pBuf)
{
	U32_T	gatewayIp, receiveIp;

	gatewayIp = STOE_GetGateway();
	if (!gatewayIp)
	{
		return FALSE;
	}

	receiveIp = *(U32_T *)&pBuf[28];
	if (gatewayIp != receiveIp)
	{
		return FALSE;
	}

	return TRUE;
}

/*
* -----------------------------------------------------------------------------
 * Function Name: ETH_SendArpToGateway
 * Purpose: send arp request to gateway
 * Params: none
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void ETH_SendArpToGateway(BOOL StopSendAfterRcvReply)
{
	U32_T	gateway, ip, TempTime;
	U8_T	*buf = uip_buf;
	U8_T*	point;

	if (StopSendAfterRcvReply)
	{
#if (STOE_TRANSPARENT)
		if (TCPIP_GetGwMacAddrFlag())
			return;
#else
		if (eth_GatewayArpStaticFlag)
			return;
#endif
	}

	// first check stoe gateway setting
	gateway = STOE_GetGateway();
	if (!gateway)
		return;

	// check stoe source ip setting
	ip = STOE_GetIPAddr();
	if (!ip)
		return;

	// check is it time to send arp request
	TempTime = SWTIMER_Tick();
	if ((TempTime - eth_ArpSendTime) < (eth_ArpSendIntervalTime * SWTIMER_COUNT_SECOND))
		return;

	// update time
	eth_ArpSendTime = TempTime;

#if (STOE_TRANSPARENT)
	if (TCPIP_GetGwMacAddrFlag())
#else
	if (eth_GatewayArpStaticFlag)
#endif
	{
		eth_ArpSendIntervalTime = ETH_ARP_SEND_INTERVAL_TIME;
	}
	else
	{
		eth_ArpSendIntervalTime = 10;
	}

	// send arp request to gateway,
	// in order to get gateway MAC address.
	point = MAC_GetMacAddr();
	uip_len = 42;

	buf[0] = 0xFF;
	buf[1] = 0xFF;
	buf[2] = 0xFF;
	buf[3] = 0xFF;
	buf[4] = 0xFF;
	buf[5] = 0xFF;
	buf[6] = *(point);
	buf[7] = *(point + 1);
	buf[8] = *(point + 2);
	buf[9] = *(point + 3);
	buf[10] = *(point + 4);
	buf[11] = *(point + 5);
	buf[12] = 0x08; 
	buf[13] = 0x06;

	buf[14] = 0x00;
	buf[15] = 0x01;
	buf[16] = 0x08;
	buf[17] = 0x00;
	buf[18] = 0x06;
	buf[19] = 0x04;
	buf[20] = 0x00;
	buf[21] = 0x01;

	buf[22] = *(point);
	buf[23] = *(point + 1);
	buf[24] = *(point + 2);
	buf[25] = *(point + 3);
	buf[26] = *(point + 4);
	buf[27] = *(point + 5);
	*(U32_T *)&buf[28] = STOE_GetIPAddr();
	
	buf[32] = 0x00;
	buf[33] = 0x00;
	buf[34] = 0x00;
	buf[35] = 0x00;
	buf[36] = 0x00;
	buf[37] = 0x00;
	*(U32_T *)&buf[38] = gateway;

	ETH_Send(0);

	return;
}

/*
* -----------------------------------------------------------------------------
 * Function Name: ETH_SendArpRequest
 * Purpose: send arp request to dstIp
 * Params: none
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void ETH_SendArpRequest(U32_T dstIp)
{
	U8_T *buf = uip_buf;
	U8_T *point;

    // in order to get gateway MAC address.
	point = MAC_GetMacAddr();
	uip_len = 42;

	buf[0] = 0xFF;
	buf[1] = 0xFF;
	buf[2] = 0xFF;
	buf[3] = 0xFF;
	buf[4] = 0xFF;
	buf[5] = 0xFF;
	buf[6] = *(point);
	buf[7] = *(point + 1);
	buf[8] = *(point + 2);
	buf[9] = *(point + 3);
	buf[10] = *(point + 4);
	buf[11] = *(point + 5);
	buf[12] = 0x08; 
	buf[13] = 0x06;

	buf[14] = 0x00;
	buf[15] = 0x01;
	buf[16] = 0x08;
	buf[17] = 0x00;
	buf[18] = 0x06;
	buf[19] = 0x04;
	buf[20] = 0x00;
	buf[21] = 0x01;

	buf[22] = *(point);
	buf[23] = *(point + 1);
	buf[24] = *(point + 2);
	buf[25] = *(point + 3);
	buf[26] = *(point + 4);
	buf[27] = *(point + 5);
	*(U32_T *)&buf[28] = STOE_GetIPAddr();
	
	buf[32] = 0x00;
	buf[33] = 0x00;
	buf[34] = 0x00;
	buf[35] = 0x00;
	buf[36] = 0x00;
	buf[37] = 0x00;
	*(U32_T *)&buf[38] = dstIp;

	ETH_Send(0);

	return;
}

/*
* -----------------------------------------------------------------------------
 * Function Name: ETH_RestartSendArpToGateway
 * Purpose: Restart sending arp request to gateway
 * Params: none
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void ETH_RestartSendArpToGateway(void)
{
#if (STOE_TRANSPARENT)
	TCPIP_SetGwMacAddrFlag(FALSE);
#else
	eth_GatewayArpStaticFlag = FALSE;
#endif
	eth_ArpSendIntervalTime = 3;
}

/*
* -----------------------------------------------------------------------------
 * Function Name: ETH_SendDhcpArpRequest
 * Purpose: send arp request to gateway
 * Params: none
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void ETH_SendDhcpArpRequest(void)
{
	U8_T	*buf = uip_buf;
	U8_T*	point;

	eth_ArpSendIntervalTime = 5;

	point = MAC_GetMacAddr();
	uip_len = 42;

	buf[0] = 0xFF;
	buf[1] = 0xFF;
	buf[2] = 0xFF;
	buf[3] = 0xFF;
	buf[4] = 0xFF;
	buf[5] = 0xFF;
	buf[6] = *(point);
	buf[7] = *(point + 1);
	buf[8] = *(point + 2);
	buf[9] = *(point + 3);
	buf[10] = *(point + 4);
	buf[11] = *(point + 5);
	buf[12] = 0x08; 
	buf[13] = 0x06;

	buf[14] = 0x00;
	buf[15] = 0x01;
	buf[16] = 0x08;
	buf[17] = 0x00;
	buf[18] = 0x06;
	buf[19] = 0x04;
	buf[20] = 0x00;
	buf[21] = 0x01;

	buf[22] = *(point);
	buf[23] = *(point + 1);
	buf[24] = *(point + 2);
	buf[25] = *(point + 3);
	buf[26] = *(point + 4);
	buf[27] = *(point + 5);
	*(U32_T *)&buf[28] = STOE_GetIPAddr(); // Source IP address
	
	buf[32] = 0x00;
	buf[33] = 0x00;
	buf[34] = 0x00;
	buf[35] = 0x00;
	buf[36] = 0x00;
	buf[37] = 0x00;
	*(U32_T *)&buf[38] = STOE_GetIPAddr(); // Destination IP address

	ETH_DhcpArpReply = FALSE;

	ETH_Send(0);

	return;
}

#if (!STOE_TRANSPARENT)
/*
* -----------------------------------------------------------------------------
 * Function Name: ETH_AddArpTable
 * Purpose: add a arp entry to hardware and software table
 * Params: none
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void ETH_AddArpTable(U8_T XDATA* addr, U32_T ip, U8_T type)
{
	U8_T	index, number, temp, j;
	U8_T	hash[7];

	number = ETH_ARP_TABLE_COUNTER;
	for (index = ETH_ARP_TABLE_COUNTER; index > 0; index--)
	{
		if (ETH_ArpTable[index -1].Valid)
		{
			if (ETH_ArpTable[index -1].IP == ip)
			{
				return;
			}
		}
		else
		{
			number = index - 1;
		}
	}

	if (index == 0) /* not found */
	{
		if (number == ETH_ARP_TABLE_COUNTER) /* no software resource */
		{
			return;
		}

		index = (U8_T)ip & 0x7f;
		for (j = 0; j < ETH_ARP_TABLE_COUNTER; j++)
		{
			if ((ETH_ArpTable[j].Valid) && (ETH_ArpTable[j].HwTableIndex == index))
				break;
		}

		if (j < ETH_ARP_TABLE_COUNTER) /* the hardware arp entry has been occupy */
		{
			hash[0] = (U8_T)(((ip >> 1) & 1) ^ ((ip >> 9) & 1) ^ ((ip >> 17) & 1) ^ ((ip >> 25) & 1));
			hash[1] = (U8_T)(((ip >> 2) & 1) ^ ((ip >> 10) & 1) ^ ((ip >> 18) & 1) ^ ((ip >> 26) & 1));
			hash[2] = (U8_T)(((ip >> 3) & 1) ^ ((ip >> 11) & 1) ^ ((ip >> 19) & 1) ^ ((ip >> 27) & 1));
			hash[3] = (U8_T)(((ip >> 4) & 1) ^ ((ip >> 12) & 1) ^ ((ip >> 20) & 1) ^ ((ip >> 28) & 1));
			hash[4] = (U8_T)(((ip >> 5) & 1) ^ ((ip >> 13) & 1) ^ ((ip >> 21) & 1) ^ ((ip >> 29) & 1));
			hash[5] = (U8_T)(((ip >> 6) & 1) ^ ((ip >> 14) & 1) ^ ((ip >> 22) & 1) ^ ((ip >> 30) & 1));
			hash[6] = (U8_T)(((ip >> 7) & 1) ^ ((ip >> 15) & 1) ^ ((ip >> 23) & 1) ^ ((ip >> 31) & 1));

			temp = hash[0] + (hash[1] << 1) + (hash[2] << 2) + (hash[3] << 3) + (hash[4] << 4) + (hash[5] << 5) + (hash[6] << 6);
			index = temp;

			for (j = 0; j < ETH_ARP_TABLE_COUNTER; j++)
			{
				/* the hardware arp entry has been occupy */
				if ((ETH_ArpTable[j].Valid) && (ETH_ArpTable[j].HwTableIndex == index))
				{
					return;
				}
			}
		}

		STOE_SetArpTableByIndex(addr, ip, index);

		ETH_ArpTable[number].Valid = 1;
		ETH_ArpTable[number].Static = type;
		ETH_ArpTable[number].Timer = 0;
		ETH_ArpTable[number].HwTableIndex = index; /* 0..127 */
		ETH_ArpTable[number].IP = ip;
		for (j = 0; j < 6; j++)
			ETH_ArpTable[number].MacAddr[j] = addr[j];
	}

} /* End of ETH_AddArpTable() */

/*
* -----------------------------------------------------------------------------
 * Function Name: ETH_FindArpTable
 * Purpose: find arp entry from software table
 * Params: none
 * Returns: TRUE: find the ip addr is in sw arp table
 *			FALSE: not find
 * Note:
 * ----------------------------------------------------------------------------
 */
BOOL ETH_FindArpTable(U32_T ip)
{
	U8_T	index;

	for (index = 0; index < ETH_ARP_TABLE_COUNTER; index++)
	{
		if ((ETH_ArpTable[index].Valid) && (ETH_ArpTable[index].IP == ip))
		{
			ETH_ArpTable[index].Timer = 0;
			return TRUE;
		}
	}
	return FALSE;

} /* End of ETH_FindArpTable() */

/*
* -----------------------------------------------------------------------------
 * Function Name: ETH_AddIpFromGwTable
 * Purpose: add a ip address to Ip-from-Gateway table
 * Params: none
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void ETH_AddIpFromGwTable(U32_T ip)
{
	U8_T	index;
	
	for (index = 0; index < ETH_ARP_TABLE_COUNTER; index++)
	{
		if (!ETH_IpFromGw[index].Valid)
		{
			ETH_IpFromGw[index].Valid = 1;
			ETH_IpFromGw[index].Timer = 0;
			ETH_IpFromGw[index].IP = ip;

			return;
		}
	}
} /* End of ETH_AddIpFromGwTable() */

/*
* -----------------------------------------------------------------------------
 * Function Name: ETH_FindIpFromGwTable
 * Purpose: find an ip address that is in from-outside-subnet table
 * Params: none
 * Returns: TRUE: find the ip addr is in sw from-outside-subnet table
 *			FALSE: not find
 * Note:
 * ----------------------------------------------------------------------------
 */
BOOL ETH_FindIpFromGwTable(U32_T ip)
{
	U8_T	index;

	for (index = 0; index < ETH_ARP_TABLE_COUNTER; index++)
	{
		if ((ETH_IpFromGw[index].Valid) && (ETH_IpFromGw[index].IP == ip))
		{
			ETH_IpFromGw[index].Timer = 0;
			return TRUE;
		}
	}
	return FALSE;

} /* End of ETH_FindIpFromGwTable() */

/*
* -----------------------------------------------------------------------------
 * Function Name: ETH_ArpTableTimer
 * Purpose:	update arp entry timer
 * Params: none
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void ETH_ArpTableTimer(void)
{
	U8_T index;

	for (index = 0; index < ETH_ARP_TABLE_COUNTER; index++)
	{
		if ((ETH_ArpTable[index].Valid) && (!ETH_ArpTable[index].Static))
		{
			ETH_ArpTable[index].Timer++;
			if (ETH_ArpTable[index].Timer > ETH_ARP_ENTRY_TIMEOUT)
			{
				ETH_ArpTable[index].Valid = 0;
				STOE_DelArpTableByIndex(ETH_ArpTable[index].HwTableIndex);
			}
		}

		if (ETH_IpFromGw[index].Valid)
		{
			ETH_IpFromGw[index].Timer++;
			if (ETH_IpFromGw[index].Timer > ETH_ARP_ENTRY_TIMEOUT)
				ETH_IpFromGw[index].Valid = 0;
		}
	}

} /* End of ETH_ArpTableTimer() */
#endif

/* End of adapter.c */