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
 * Module Name:adapter.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: adapter.h,v $
 *=============================================================================
 */

#ifndef __ADAPTER_H__
#define __ADAPTER_H__


/* INCLUDE FILE DECLARATIONS */
#include "types.h"
#include "adapter_cfg1.h"
#include "stoe_cfg.h"

/* NAMING CONSTANT DECLARATIONS */
#define ETH_STOP_ARP_REQUEST_TO_GATEWAY_AFTER_REPLY			1
#define ETH_CONTINUE_ARP_REQUEST_TO_GATEWAY_AFTER_REPLY		0

#if (!STOE_TRANSPARENT)
#define ETH_ARP_TABLE_COUNTER	16
#define ETH_ARP_ENTRY_STATIC		1
#define ETH_ARP_ENTRY_DYNAMIC		0

typedef struct _ETH_ARP_TABLE
{
	U8_T	Valid;
	U8_T	Static;
	U16_T	Timer;
	U32_T	IP;
	U8_T	MacAddr[6];
	U8_T	HwTableIndex; /* This arp entry is stored in which index of hardware arp table*/

} ETH_ARP_TABLE;

typedef struct _ETH_FROM_OUTSIDE_SUBNET
{
	U8_T	Valid;
	U16_T	Timer;
	U32_T	IP;

} ETH_FROM_GW;

extern ETH_FROM_GW ETH_IpFromGw[];
extern ETH_ARP_TABLE ETH_ArpTable[];
#endif

/* GLOBAL VARIABLES */
extern U8_T ETH_IsPppoe;
extern U8_T ETH_DoDhcp;
extern U8_T ETH_PppoeHeaderLen;
extern U8_T ETH_DhcpArpReply;
#define ETH_GetPppoeFlag() (ETH_IsPppoe)
#define ETH_SetPppoeFlag(a) (ETH_IsPppoe = a)
#define ETH_GetDhcpFlag() (ETH_DoDhcp)
#define ETH_SetDhcpFlag(a) (ETH_DoDhcp = a)
#define ETH_GetPppoeHeaderLen() (ETH_PppoeHeaderLen)
#define ETH_SetPppoeHeaderLen(a) (ETH_PppoeHeaderLen = a)
#define ETH_SetDhcpArpReplyFlag(a) (ETH_DhcpArpReply = a)
#define ETH_CheckDhcpArpReply() (ETH_DhcpArpReply)

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
/*-------------------------------------------------------------*/
void ETH_Init(void);
void ETH_Start(void);
void ETH_Send(U16_T);
void ETH_SendPkt(U8_T XDATA*, U16_T);
void ETH_SendArpToGateway(BOOL);
void ETH_SendArpRequest(U32_T dstIp);
void ETH_RestartSendArpToGateway(void);
void ETH_SendDhcpArpRequest(void);
#if (!STOE_TRANSPARENT)
void ETH_AddArpTable(U8_T XDATA*, U32_T, U8_T);
BOOL ETH_FindArpTable(U32_T);
void ETH_ArpTableTimer(void);
BOOL ETH_FindIpFromGwTable(U32_T);
void ETH_AddIpFromGwTable(U32_T);
#endif


#endif /* End of __ADAPTER_H__ */


/* End of adapter.h */