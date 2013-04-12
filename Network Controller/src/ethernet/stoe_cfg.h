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
 * Module Name: stoe_cfg.h
 * Purpose: 
 * Author:
 * Date:
 * Notes:
 * $Log: stoe_cfg.h,v $
 * Revision 1.2  2006/07/25 05:32:12  borbin
 * no message
 *
 * Revision 1.1.1.1  2006/06/20 05:50:28  borbin
 * no message
 *
*=============================================================================
 */

#ifndef __STOE_CFG_H__
#define __STOE_CFG_H__


/* INCLUDE FILE DECLARATIONS */


/* for STOE module */
/* BDP --------------------------------------------------------*/
#define PAGES_OF_XMIT				16	/* pages, 4k */
#define PAGES_OF_RCV				24	/* pages, 6k */

/*-------------------------------------------------------------*/
#define STOE_ARP_TIMEOUT			16	/* hardware arp table timeout is 128 sec. */

/*-------------------------------------------------------------*/
/* NAMING CONSTANT DECLARATIONS */
#define STOE_NON_TRANSPARENT_MODE	0	/* non-transparent mode, hardware remove
											ethernet header and entire ARP packets
											and not being passed up to SW. */
#define STOE_TRANSPARENT_MODE		1	/* transparent mode, hardware allows entire
											frame and ARP packets to be	passed up
											to SW. */
#define STOE_TRANSPARENT		(STOE_NON_TRANSPARENT_MODE)

/*-------------------------------------------------------------*/
/* NAMING CONSTANT DECLARATIONS */
#define STOE_HW_CHECKSUN_DISABLE	0	/*	0: disable stoe checksum offload engine */
#define STOE_HW_CHECKSUN_ENABLE		1	/*	1: enable stoe checksum offload engine. */

#define STOE_CHECKSUM_OFFLOAD	(STOE_HW_CHECKSUN_ENABLE)

/*-------------------------------------------------------------*/
/* NAMING CONSTANT DECLARATIONS */
#define STOE_INTERRUPT_MODE			0	/* driver get stoe-interrupt-status from
											interrupt routine, and this routine will
											set flag when interrupt had be trigged.
											The main function must read the flag to
											decide what events had happened.*/
#define STOE_POLLING_MODE			1	/* deiver get stoe-interrupt-status from
											polling	routine, The main function must
											call function to read STOE register 0x30
											to decide what events had happened.*/

#define STOE_GET_INTSTATUS_MODE	(STOE_POLLING_MODE)

/*-------------------------------------------------------------*/
/* for MAC module */
/* NAMING CONSTANT DECLARATIONS */
#define MAC_INTERRUPT_MODE			0	/* driver get mac-interrupt-status from
											interrupt routine, and this routine will
											set flag when interrupt had be trigged.
											The main function must read the flag to
											decide what events had happened.*/
#define MAC_POLLING_MODE			1	/* deiver get mac-interrupt-status from
											polling	routine, The main function must
											call function to read MAC register 0x28
											to decide what events had happened.*/

#define MAC_GET_INTSTATUS_MODE	(MAC_INTERRUPT_MODE)

/*-------------------------------------------------------------*/
/* NAMING CONSTANT DECLARATIONS */
#define MAC_NOT_SUPPORT				0
#define MAC_SUPPORT					1

#define MAC_REMOTE_WAKEUP		(MAC_NOT_SUPPORT)

/*-------------------------------------------------------------*/
#define MAC_MULTICAST_FILTER	(MAC_SUPPORT)

/*-------------------------------------------------------------*/

#endif	/* End of __STOE_CFG_H__ */


/* End of stoe_cfg.h */
