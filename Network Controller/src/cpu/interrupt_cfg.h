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
 * Module Name : interrupt_cfg.h
 * Purpose     : Configuration setting of interrupt module.
 * Author      : Robin Lee
 * Date        : 2006-01-09
 * Notes       : None.
 * $Log: interrupt_cfg.h,v $
 * Revision 1.2  2006/05/18 05:02:30  Louis
 * no message
 *
 * Revision 1.2  2006/04/20 01:25:49  robin6633
 * 1.Added the power management ISR enable/disable.
 * 2.Added the watchdog ISR enable/disable.
 *
 * Revision 1.1  2006/04/07 11:36:17  robin6633
 * no message
 *
 *================================================================================
 */
#ifndef INTERRUPT_CFG_H
#define INTERRUPT_CFG_H

/* INCLUDE FILE DECLARATIONS */


/* NAMING CONSTANT DECLARATIONS */
#define		AX_LBI_INT_ENABLE				0 // 1:enable Local Bus ISR ; 0:disable Local Bus ISR
#define		AX_ETH_INT_ENABLE				1 // 1:enable Ethernet ISR ; 0:disable Ethernet ISR
#define		AX_I2C_INT_ENABLE				1 // 1:enable I2C ISR ; 0:disable I2C ISR
#define		AX_SPI_INT_ENABLE				0 // 1:enable SPI ISR ; 0:disable SPI ISR
#define		AX_ONEWIRE_INT_ENABLE			0 // 1:enable OneWire ISR ; 0:disable OneWire ISR
#define		AX_CAN_INT_ENABLE				0 // 1:enable CAN ISR ; 0:disable CAN ISR
#define		AX_HSUART_INT_ENABLE			1 // 1:enable High Speed Uart ISR ; 0:disable High Speed Uart ISR
#define		BOOTLDR_ISR						0 // 1:involve the boot loader source code.
#define		AX_POWER_MANAGEMENT_INT_ENABLE	0 // 1:enable power management wake up  ISR ; 0:disable that
#define		AX_WATCHDOG_INT_ENB				0 // 1:enable watchdog ISR ; 0:disable watchdog ISR;


/* MACRO DECLARATIONS */


/* TYPE DECLARATIONS */


/* GLOBAL VARIABLES */


/* EXPORTED SUBPROGRAM SPECIFICATIONS */

#endif /* End of INTERRUPT_CFG_H */
