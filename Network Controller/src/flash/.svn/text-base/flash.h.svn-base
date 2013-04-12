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
/*================================================================================
 * Module Name : flash.h
 * Purpose     : A header file of flash.c
 * Author      :
 * Date        :
 * Notes       :
 *
 /*********************************************************************************/
// Module Name : flash.h
// Purpose     :
// Author      : Chelsea
// Date        : 2008/11/10
// Revision    : rev0
/*********************************************************************************/
#ifndef __FLASH_H__
#define __FLASH_H__

/* INCLUDE FILE DECLARATIONS */
#include "types.h"

/* NAMING CONSTANT DECLARATIONS */
#define	SOH_128				0x01
#define	SOH_1024			0x02
#define	EOT					0x04
#define	ACK					0x06
#define	NACK				0x15
#define	CAN					0x18
#define	ASCII_C				0x43

#define	X_LEN_128			128
#define	X_LEN_1024			1024
#define	MAX_RETRY			6

#define	STATE_SOH			BIT0
#define	STATE_BLKNUM		BIT1
#define	STATE_BLKNUM_CMP	BIT2
#define	STATE_DATA			BIT3
#define	STATE_ACK			BIT4
#define	STATE_EOT_ACK		BIT5

#define	DUMP_DATA_MEMORY	1
#define	DUMP_FLASH			2
#define	DUMP_SHADOW			3

#define	ERA_BLD				BIT0
#define	ERA_CFG				BIT1
#define	ERA_RUN				BIT2

//  use the last block for store datas and configure file
#define FLASH_BLOCK			0x70000   //  default using the last page

/* GLOBAL VARIABLES */
extern U8_T CODE* PFlash;

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
extern S16_T	IntFlashWrite(U32_T ProgAddr, U8_T *ptWrData, U32_T ProgLen, U8_T BootldrSel);
extern S16_T	IntFlashErase(U8_T EraseSel,U32_T EraAddr);
U8_T 	IntFlashReadByte(U32_T location, U8_T *value);
U8_T    IntFlashReadByte_1(U32_T location, U8_T *value);
U8_T 	IntFlashReadInt(U32_T location, U16_T *value);
U8_T 	IntFlashWriteByte(U32_T location,U8_T value);
U8_T 	IntFlashWriteInt(U32_T location,U16_T value);
void 	MassFlashWrite(U32_T location,U8_T *value,U32_T lenght);
void ISPMassFlashWrite(U32_T location,U8_T *value,U32_T lenght);

#endif /* End of __FLASH_H__ */
