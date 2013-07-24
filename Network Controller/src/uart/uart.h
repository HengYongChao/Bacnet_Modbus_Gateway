 /*
******************************************************************************
 *     Copyright (c) 2005	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
/*================================================================================
 * Module Name : uart.h
 * Purpose     : A header file of uart.c includes UART0 and UART1 module.
 * Author      : Robin Lee
 * Date        : 2006-01-10
 * Notes       :
 * $Log: uart.h,v $
 * Revision 1.1  2006/05/12 14:24:47  robin6633
 * no message
 *
 * Revision 1.3  2006/05/03 02:46:00  robin6633
 * Changed the the function name UART_GetBufCount()
 * to UART_GetRxBufCount() .
 *
 * Revision 1.2  2006/05/02 01:43:45  robin6633
 * Add an expanding function to get the counter value of UART software buffer.
 *
 * Revision 1.1  2006/04/07 11:39:14  robin6633
 * no message
 *
 *================================================================================
 */

#ifndef __UART_H__
#define __UART_H__

/* INCLUDE FILE DECLARATIONS */
#include	"uart_cfg.h"
#include "reg80390.h"

/* NAMING CONSTANT DECLARATIONS */
#if UART0_ENABLE
#define MAX_TX_UART0_BUF_SIZE	512
#define MAX_TX_UART0_MASK		(MAX_TX_UART0_BUF_SIZE - 1)
#define MAX_RX_UART0_BUF_SIZE	512
#define MAX_RX_UART0_MASK		(MAX_RX_UART0_BUF_SIZE - 1)
#endif

#if UART1_ENABLE
#define MAX_TX_UART1_BUF_SIZE	300
#define MAX_TX_UART1_MASK		(MAX_TX_UART1_BUF_SIZE - 1)
#define MAX_RX_UART1_BUF_SIZE	300
#define MAX_RX_UART1_MASK		(MAX_RX_UART1_BUF_SIZE - 1)
#endif

#if 1
	#define read 3
	#define swrite  6
	#define mwrite 16   

sbit Rs485_2_EN = P3^4;
	
typedef struct {
U8_T register_id;
U8_T cmd;
U8_T len;
} uart_frame;				  // LJ 6/8/2012



	/* GLOBAL VARIABLES */
	#if UART0_ENABLE
	extern U16_T  uart0_RxCount;
	extern U16_T  uart0_TxCount;
	extern U8_T   uart0_RxBuf[MAX_RX_UART0_BUF_SIZE]; //lihengning
	extern U8_T	  uart0_TxBuf[MAX_TX_UART0_BUF_SIZE];
	#endif
	
	#if UART1_ENABLE
	extern U16_T  uart1_RxCount;
	extern U16_T  uart1_TxCount;
	extern U8_T   uart1_dealwithTag;
	extern U8_T   uart1_RxBuf[MAX_RX_UART1_BUF_SIZE]; //lihengning
	extern U8_T   uart1_TxBuf[MAX_RX_UART1_BUF_SIZE];

	extern U8_T far uart1_timeout;
	extern U8_T uart1_rec_size;
	#endif
#endif

extern uart_frame rsv_msg;

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void	UART_Init(U8_T port);
S8_T	putchar(S8_T);
S8_T	_getkey(void);
S8_T	NOBLK_getkey(void);
BOOL	UART_ParityChk(S8_T checkbyte);
void	UART0_SetMode(U8_T mode);
void	UART1_SetMode(U8_T mode);
BOOL	UART_SetPort(U8_T portNum);
U16_T	UART_GetRxBufCount(void);
void	PMM_Uart0Init(void);
S8_T	uart0_PutChar(S8_T c);
S8_T 	GetKey(void);


#endif /* End of __UART_H__ */

/* End of uart.h */