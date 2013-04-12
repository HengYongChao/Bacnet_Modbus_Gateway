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
 * Module Name: stoe.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: stoe.h,v $
 * Revision 1.1.1.1  2006/06/20 05:50:28  borbin
 * no message
 *
 *=============================================================================
 */

#ifndef __STOE_H__
#define __STOE_H__


/* INCLUDE FILE DECLARATIONS */
#include "types.h"
#include "stoe_cfg.h"
#include "mac.h"
#include "phy.h"


/* NAMING CONSTANT DECLARATIONS */
#define MAX_ETHERNET_LEN		1514
#define MAC_ADDRESS_LEN			6
#define ETH_HEADER_LEN			14
#define VLAN_HEADER_LEN			4
#define SNAP_LEN				8

#if (STOE_TRANSPARENT)
#define MAX_FRAME_SIZE			(MAX_ETHERNET_LEN + VLAN_HEADER_LEN)
#else
#define MAX_FRAME_SIZE			(MAX_ETHERNET_LEN + VLAN_HEADER_LEN - ETH_HEADER_LEN)
#endif

#define PAGE_SIZE				256

/* STOE header */
#define MAC_TX_RX_HEADER		6

/* calculate BDP start address */
#define STOE_SOCKET_BUFFER_SIZE	((PAGES_OF_XMIT + PAGES_OF_RCV + 1) * PAGE_SIZE)
#define DEFAULT_STACK_BOUNDARY	0x8000	/* 32 K*/
#define STOE_BDP_START_ADDR		(DEFAULT_STACK_BOUNDARY - STOE_SOCKET_BUFFER_SIZE)
#define STOE_RCV_BUF_SIZE		(PAGES_OF_RCV * PAGE_SIZE)
#define STOE_XMIT_BUF_SIZE		(PAGES_OF_XMIT * PAGE_SIZE)

/* STOE register definitions */
#define STOE_L2_CTL_REG			0x00
#define STOE_RX_VLAN_TAG_REG	0x02
#define	STOE_TX_VLAN_TAG_REG	0x04
#define	STOE_ARP_CMD_REG		0x06
#define STOE_ARP_ADDR_REG		0x07
#define STOE_ARP_DATA_REG		0x08
#define STOE_ARP_TIMEOUT_REG	0x0E
#define STOE_IP_ADDR_REG		0x10
#define STOE_SUBNET_MASK_REG	0x14
#define STOE_GATEWAY_IP_REG		0x18
#define STOE_CHKSUM_STATUS_REG	0x1C
#define STOE_L4_CTL_REG			0x20
#define STOE_L4_CMD_REG			0x21
#define STOE_L4_BDP_PNT_REG		0x22
#define STOE_L4_DMA_GAP_REG		0x24
#define STOE_INT_STATUS_REG		0x30
#define STOE_INT_MASK_REG		0x31

/* Bit definitions: STOE_L2_CTL_REG	*/
#define RX_VLAN_ENABLE			BIT0
#define RX_TRANSPARENT			BIT1
#define RX_START_OPERA			BIT3
#define	TX_VLAN_ENABLE			BIT4
#define TX_TRANSPARENT			BIT5
#define	TX_SNAP_ENABLE			BIT6
#define TX_START_OPERA			BIT7

/* Bit definitions: STOE_ARP_CMD_REG */
#define	ARP_CACHE_CMD_READ		BIT0
#define ARP_CACHE_CMD_GO		BIT1

/* Bit definitions: STOE_L4_CTL_REG	*/
#define	DROP_CHKSUMERR_PKT		BIT0
#define ENABLE_XMIT_CHKSUM		BIT1
#define ENABLE_RCV_CROSS		BIT2
#define ENABLE_XMIT_CROSS		BIT3 

/* Bit definitions: STOE_L4_CMD_REG	*/
#define RESUME_PKT_RCV			BIT0
#define XMIT_PACKET				BIT4

/* Bit definitions: STOE_STATUS_REG	*/
/* Bit definitions: STOE_INT_MASK_REG */
#define	ARP_HASH_COLLISION		BIT0
#define RCV_PACKET				BIT1
#define	RCV_BUF_RING_FULL		BIT2
#define	ARP_CACHE_NOT_FIND		BIT4
#define XMIT_EMPTY_BUF			BIT5
#define XMIT_COMPLETE			BIT6
#define STOE_DEFAULT_INT_MASK	(RCV_BUF_RING_FULL | RCV_PACKET)

/* TYPE DECLARATIONS */
//---------------------------------------------------------------
typedef struct _LOCAL_STATION
{
	/* MAC address */
	U8_T	PermStaAddr[MAC_ADDRESS_LEN];
	U8_T	CurrStaAddr[MAC_ADDRESS_LEN];

	/* IP address */
	U32_T	StationIP;
	U32_T	SubnetMask;
	U32_T	Gateway;
	U32_T	DefaultIP;
	U32_T	DefaultMask;
	U32_T	DefaultGateway;

} LOCAL_STATION;

//---------------------------------------------------------------
typedef struct _PACKET_INFORMATION
{
	U8_T XDATA*	PBuf;
	U8_T XDATA*	PIpHeader;
	U8_T XDATA*	PTUIHeader;	/* TCP Header, Udp Header, or ICMP IGMP Header */
	U8_T XDATA*	PData;

	U16_T		TotalLen;
	U16_T		IpTotalLen;
	U16_T		TUITotalLen;
	U16_T		DataLen;
	U8_T		Protocol;
	U8_T		IpHeaderLen;
	U8_T		TcpHeaderLen;
	U8_T		SocketId;
	U8_T		Pages;

} PACKET_INFORMATION;

//---------------------------------------------------------------
typedef struct _BUF_DESC_PAGE
{
#define RX_DESCRIPTOR_SIZE			128
#define RX_DESCRIPTOR_HEADER_SIZE	12
#define RX_RESERVED_BUFFER_SIZE		(RX_DESCRIPTOR_SIZE - RX_DESCRIPTOR_HEADER_SIZE -	\
									sizeof (LOCAL_STATION) - sizeof (PHY_INFO) -		\
									sizeof (MAC_INFO))

	/* hardware RX descriptor header */
	U8_T	BDP_ID;
	U8_T	Pad0;
	U16_T	RSPP;
	U16_T	REPP;
	U16_T	RHPR;
	U16_T	RTPR;
	U8_T	RFP;
	U8_T	Pad1;

	LOCAL_STATION 	NetStation;
	PHY_INFO		PhyInfo;
	MAC_INFO		MacInfo;

	U8_T	RcvReserved[RX_RESERVED_BUFFER_SIZE];

	/* hardware TX descriptor header */
	U16_T	TSPP;
	U16_T	TEPP;
	U16_T	THPR;
	U16_T	TTPR;
	U8_T	TFP;
	U8_T	Pad2;

	U16_T	VSPP;

	U8_T XDATA*	RcvStartAddr;
	U8_T XDATA*	RcvEndAddr;
	U8_T XDATA*	XmtStartAddr;
	U8_T XDATA*	XmtEndAddr;

	PACKET_INFORMATION	STOE_TxInform;
	PACKET_INFORMATION	STOE_RxInform;

} BUF_DESC_PAGE;

//---------------------------------------------------------------
typedef struct _STOE_FRAME_HEADER
{
	U16_T	NPR;
	U16_T	Length;
	U8_T	Protocol;
	U8_T	DataOffset;
	U8_T	Packet;

} STOE_FRAME_HEADER;

/* GLOBAL VARIABLES */
extern LOCAL_STATION XDATA*	PNetStation;
extern BUF_DESC_PAGE XDATA* PBDP;
extern void (*STOE_RcvCallback)(U8_T XDATA*, U16_T, U8_T);

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
//---------------------------------------------------------------
void STOE_Init(U8_T);
void STOE_Start(void);
/* MACRO DECLARATIONS */
#define STOE_GetIPAddr()		(PNetStation->StationIP)
#define STOE_GetSubnetMask()	(PNetStation->SubnetMask)
#define STOE_GetGateway()		(PNetStation->Gateway)

void STOE_SetIPAddr(U32_T);
void STOE_SetSubnetMask(U32_T);
void STOE_SetGateway(U32_T);
void STOE_WaitHwReleaseRcvBuf(void);
#if (STOE_GET_INTSTATUS_MODE == STOE_INTERRUPT_MODE)
  void STOE_SetInterruptFlag(void);
  U8_T STOE_GetInterruptFlag(void);
#endif
void STOE_ProcessInterrupt(void);
void STOE_Send(U8_T XDATA*, U16_T, U8_T);
U8_T XDATA* STOE_AssignSendBuf(U16_T);
U8_T XDATA* STOE_CopyCode2TPBR(U8_T XDATA*, U8_T*, U16_T);
U8_T STOE_CHECK_MAC(U32_T *ip_addr);
#if (!STOE_TRANSPARENT)
void STOE_EnableIpFilter(void);
void STOE_DisableIpFilter(void);
BOOL STOE_AddArpTable(U8_T XDATA*, U32_T, U8_T);
#endif


#endif /* End of __STOE_H__ */


/* End of stoe.h */
