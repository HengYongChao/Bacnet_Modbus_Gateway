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
 * Module Name:adapter_cfg.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: adapter_cfg.h,v $
 *=============================================================================
 */

#ifndef __ADAPTER_CFG_H__
#define __ADAPTER_CFG_H__


/*-------------------------------------------------------------*/
/* NAMING CONSTANT DECLARATIONS */
#define ETH_PHY_AUTO_NEGOTIATION	0
#define ETH_PHY_FIXED_100_FULL		1
#define ETH_PHY_FIXED_100_HALF		2
#define ETH_PHY_FIXED_10_FULL		3
#define ETH_PHY_FIXED_10_HALF		4
#define ETH_PHY_FORCE_EMBEDDED_PHY_10_HALF	5	// Force the embedded Ethernet PHY to operate in 10Mbps half-duplex mode.
												// The EEPROM address 0x01(Flag) BIT-0 must be set to 1.	   

#define ETH_PHY_SENSE_TYPE		(ETH_PHY_AUTO_NEGOTIATION)

/*-------------------------------------------------------------*/


#endif /* End of __ADAPTER_CFG_H__ */


/* End of adapter_cfg.h */