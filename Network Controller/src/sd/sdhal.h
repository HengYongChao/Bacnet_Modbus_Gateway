/****************************************Copyright (c)**************************************************
**                               Guangzhou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			sdhal.h
** Last modified Date:	2005-3-11
** Last Version:		V2.0
** Descriptions:		SD/MMC����дģ�� ---- SPI��������ͷ�ļ�
**						Soft Packet of SD/MMC Card: hard abstrast layer ---- function of SPI operation 
**																			 header file
**------------------------------------------------------------------------------------------------------
** Created by:			Ming Yuan Zheng
** Created date:		2005-1-6
** Version:				V1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			
** Modified date:		
** Version:				
** Descriptions:		
**
**------------------------------------------------------------------------------------------------------
** Modified by: 
** Modified date:
** Version:	
** Descriptions: 
**
********************************************************************************************************/

#ifndef __SDHAL_H__
#define __SDHAL_H__

#include "Types.h"

#if 0
/* ��⿨�Ƿ���ȫ����  check weather card is insert entirely */
extern U8_T SD_ChkCard(void);

/* ��⿨�Ƿ�д����  check weather card is write protect */
extern U8_T SD_ChkCardWP(void);
 #endif
/* ��ʼ������SD����Ӳ����ʼ�� initialize the hardware that access sd card */
extern void SD_HardWareInit(void);

/* ����SPI��ʱ��С��400kHZ set the clock of SPI less than 400kHZ */
extern void SPI_Clk400k(void);

/* ����SPI��clock�����ֵ set the clock of SPI to maximum */
extern void SPI_ClkToMax(void);

/* ͨ��SPI�ӿڷ���һ���ֽ� send a byte by SPI interface */
extern void SPI_SendByte(U8_T byte);

/* ��SPI�ӿڽ���һ���ֽ� receive a byte from SPI interface */
extern U8_T SPI_RecByte(void);

/* ƬѡSPI�ӻ� select the SPI slave */
extern void SPI_CS_Assert(void);

/* ��ƬѡSPI�ӻ� not select the SPI slave */
extern void SPI_CS_Deassert(void);

#endif