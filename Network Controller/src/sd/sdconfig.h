/****************************************Copyright (c)**************************************************
**                               Guangzhou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			sdconfig.h
** Last modified Date:	2005-3-11
** Last Version:		V2.0
** Descriptions:		SD/MMC ����дģ��: �����ļ�
**						Soft Packet of SD/MMC Card: configuration header file
**
**------------------------------------------------------------------------------------------------------
** Created by:			Ming Yuan Zheng
** Created date:		2005-1-6
** Version:				V1.0
** Descriptions:		��ʼ�汾 The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			Ming Yuan Zheng
** Modified date:		2005-3-11
** Version:				V2.0
** Descriptions:		������LPC22xx��Ӳ������	
**						add LPC22xx hardware configuration
**------------------------------------------------------------------------------------------------------
** Modified by: 
** Modified date:
** Version:	
** Descriptions: 
**
********************************************************************************************************/

#ifndef __SDCONFIG_H__
#define __SDCONFIG_H__


#define SPI_CLOCK				25000000		/* ����ͨ��ʱ,SPIʱ��Ƶ�� frequency (Hz) */

#define SD_BLOCKSIZE 			512			/* SD����ĳ��� */

#define SD_BLOCKSIZE_NBITS		9  

/* ���溯��������,����û�����Ҫ,����Ϊ 0 �ü�ָ������ */

#define SD_ReadMultiBlock_EN    0			/* �Ƿ�ʹ�ܶ���麯�� */

#define SD_WriteMultiBlock_EN   0			/* �Ƿ�ʹ��д��麯�� */

#define SD_EraseBlock_EN		1			/* �Ƿ�ʹ�ܲ������� */

#define SD_ProgramCSD_EN   		0			/* �Ƿ�ʹ��дCSD�Ĵ������� */
	
#define SD_ReadCID_EN	   		0			/* �Ƿ�ʹ�ܶ�CID�Ĵ������� */
	
#define	SD_ReadSD_Status_EN		0			/* �Ƿ�ʹ�ܶ�SD_Status�Ĵ������� */

#define	SD_ReadSCR_EN			0			/* �Ƿ�ʹ�ܶ�SCR�Ĵ������� */

#endif