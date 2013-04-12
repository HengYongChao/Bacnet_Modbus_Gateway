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
 * Module Name:dma.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: dma.h,v $
 * Revision 1.1  2006/05/12 14:24:19  robin6633
 * no message
 *
 * Revision 1.1.1.1  2006/02/23 00:55:10  borbin
 * no message
 *
 *=============================================================================
 */

#ifndef __DMA_H__
#define __DMA_H__


/* INCLUDE FILE DECLARATIONS */
#include "types.h"
#include "dma_cfg.h"

/* NAMING CONSTANT DECLARATIONS */
/* SFR 0x94 definitions*/
#define DMA_COMPLETE			BIT0

/* DMA register definitions */
#define SW_DMA_CMD_REG			0x00
#define SW_DMA_SOUR_ADDR_REG	0x02
#define SW_DMA_TARGET_ADDR_REG	0x06
#define SW_DMA_BYTE_COUNT_REG	0x0A

/* Bit definitions: SW_DMA_CMD_REG */
#define DMA_CMD_GO				BIT0
#define DMA_FORCE_STOP			BIT1
#define DMA_ERROR_BIT			BIT2
#define DMA_ADDR_IN_RPBR		BIT4
#define DMA_ADDR_IN_TPBR		BIT5
#define	DMA_COMPLETE_INT_ENABLE	BIT7

/* for software definition */
#define DMA_NORMAL				0
#define DMA_FROM_RPBR			BIT4
#define DMA_TO_TPBR				BIT5

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
/*-------------------------------------------------------------*/
void DMA_ReadReg(U8_T, U8_T XDATA*, U8_T);
void DMA_WriteReg(U8_T, U8_T XDATA*, U8_T);
void DMA_Init(void);
void DMA_Start(void);
U8_T XDATA* DMA_GrantXdata(U8_T XDATA*, U8_T XDATA*, U16_T);
#if (DMA_SRAM_RANGE == DMA_COPY_LARGE_THAN_64K)
U8_T* DMA_Grant(U8_T*, U8_T*, U16_T);
#endif


#endif /* End of __DMA_H__ */


/* End of dma.h */