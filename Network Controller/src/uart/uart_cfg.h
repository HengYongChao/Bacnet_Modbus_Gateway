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
 * Module Name : uart_cfg.h
 * Purpose     : Configuration setting of UART0 and UART1 module.
 * Author      : Robin Lee
 * Date        : 2006-01-10
 * Notes       :
 * $Log: uart_cfg.h,v $
 * Revision 1.2  2006/05/18 02:15:57  robin6633
 * 1.Disabled UART1.
 *
 * Revision 1.1  2006/05/12 14:24:47  robin6633
 * no message
 *
 * Revision 1.1  2006/04/07 11:39:14  robin6633
 * no message
 *
 *================================================================================
 */
#ifndef UART_CFG_H
#define UART_CFG_H

/* INCLUDE FILE DECLARATIONS */


/* NAMING CONSTANT DECLARATIONS */
#define	UART0_ENABLE		1	// 1:enable UART0 ; 0:disable UART0
#define	UART1_ENABLE		1	// 1:enable UART1 ; 0:disable UART1 lihengning
#define	HSUR_ENABLE			1	// 1:enable Hihg Speed UART ; 0:disable Hihg Speed UART
#define	UART_PMM_ENABLE		0	// 1:use UART in PMM mode ; 0:disable
#define HSUR_RS485_ENABLE   1   // 1:enable RS485 Driver and Receiver Settings 

/* MACRO DECLARATIONS */


/* TYPE DECLARATIONS */


/* GLOBAL VARIABLES */


/* EXPORTED SUBPROGRAM SPECIFICATIONS */


#endif /* End of UART_CFG_H */
