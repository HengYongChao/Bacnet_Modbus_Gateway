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
 * Module Name:main.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: main.h,v $
 *=============================================================================
 */

#ifndef __MAIN_H__
#define __MAIN_H__


/* INCLUDE FILE DECLARATIONS */
#include "types.h"
#include "reg80390.h"

/* NAMING CONSTANT DECLARATIONS */
#define COMMAND_UNKNOW		0
#define COMMAND_HAD_DONE	1

/* Protocol modules - 1:include 0:not include */
#define INCLUDE_DNS_CLIENT  0
#define INCLUDE_DHCP_CLIENT 1
#define INCLUDE_EVENT_DETECT 1

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */ //LHN add
/*-------------------------------------------------------------*/

#define UIP_HEAD  6
#define UIP_CODE_HEAD 3
#define READ_VARIABLES 3
#define WRITE_VARIABLES 6
#define MULTIPLE_WRITE 0x10
#define DEEPSCAN  0x1a


sbit Rs485_EN = P3^6;
sbit DisPlay1 = P2^0;
sbit DisPlay2 = P2^1;
sbit LE = P3^7;

sbit backlight = P1^7;

typedef struct buf_str {
	U16_T Leng;
	U8_T Flag;
	U8_T UdpSocket;
} Time_str;

#define	SERVER_NONE		0
#define	SERVER_TCPIP	1
#define	SERVER_RS232	2
#define	SERVER_USB		3
#define	SERVER_SCHEDULE	4
#define	SERVER_SCAN		5

extern Time_str Time_Server;
extern U8_T	TcpSocket_ME;
extern U8_T	Sever_Order;
extern U8_T	ChangeIP;
extern U8_T	TcpIp_Scan;
extern U8_T far mac_change_enable;


extern BOOL send_out;
extern U8_T rev_cnt;


extern void Uart0_Tx(U8_T *buf,U8_T len);
extern void Uart0_Receive(void);
extern void Uart1_Tx(U8_T *buf,U8_T len);
//extern void Uart1_Receive(U8_T length);
//extern void Uart1_Receive(void);
extern void Uart2_Receive(void);
extern void Tx_To_Tstat(U8_T *buf,U8_T len);

void OSDelay(U8_T x);
#endif /* End of __MAIN_H__ */


/* End of main.h */