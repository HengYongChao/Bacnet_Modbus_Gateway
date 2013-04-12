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
 * Module Name:dma_cfg.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: dma_cfg.h,v $
 * Revision 1.1  2006/05/12 14:24:19  robin6633
 * no message
 *
 * Revision 1.1.1.1  2006/02/23 00:55:10  borbin
 * no message
 *
 *=============================================================================
 */

#ifndef __DMA_CFG_H__
#define __DMA_CFG_H__


/*-------------------------------------------------------------*/
#define DMA_GAP						2	/* 2 * 64 cycle, don't set '0' */

/*-------------------------------------------------------------*/
/* NAMING CONSTANT DECLARATIONS */
#define DMA_COPY_LESS_THAN_64K		0	/* scope that dma copy, small than 64k */
#define DMA_COPY_LARGE_THAN_64K		1	/* scope that dma copy, large than 64k */

#define DMA_SRAM_RANGE			(DMA_COPY_LARGE_THAN_64K)
										/* if set DMA_COPY_LARGE_THAN_64K, driver
											include DMA_Grant() function.
											Call this function, the source and
											destination address may be in ether XDATA
											or FAR memory. */
/*-------------------------------------------------------------*/
/* NAMING CONSTANT DECLARATIONS */
#define DMA_NO						0
#define DMA_YES						1

#define DMA_INCLUDE_ETHERNET_MODULE	(DMA_YES)
/*-------------------------------------------------------------*/


#endif /* End of __DMA_CFG_H__ */


/* End of dma_cfg.h */