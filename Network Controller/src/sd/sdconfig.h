/****************************************Copyright (c)**************************************************
**                               Guangzhou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			sdconfig.h
** Last modified Date:	2005-3-11
** Last Version:		V2.0
** Descriptions:		SD/MMC 卡读写模块: 配置文件
**						Soft Packet of SD/MMC Card: configuration header file
**
**------------------------------------------------------------------------------------------------------
** Created by:			Ming Yuan Zheng
** Created date:		2005-1-6
** Version:				V1.0
** Descriptions:		初始版本 The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			Ming Yuan Zheng
** Modified date:		2005-3-11
** Version:				V2.0
** Descriptions:		增加了LPC22xx的硬件配置	
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


#define SPI_CLOCK				25000000		/* 正常通信时,SPI时钟频率 frequency (Hz) */

#define SD_BLOCKSIZE 			512			/* SD卡块的长度 */

#define SD_BLOCKSIZE_NBITS		9  

/* 下面函数不常用,如果用户不需要,可置为 0 裁剪指定函数 */

#define SD_ReadMultiBlock_EN    0			/* 是否使能读多块函数 */

#define SD_WriteMultiBlock_EN   0			/* 是否使能写多块函数 */

#define SD_EraseBlock_EN		1			/* 是否使能擦卡函数 */

#define SD_ProgramCSD_EN   		0			/* 是否使能写CSD寄存器函数 */
	
#define SD_ReadCID_EN	   		0			/* 是否使能读CID寄存器函数 */
	
#define	SD_ReadSD_Status_EN		0			/* 是否使能读SD_Status寄存器函数 */

#define	SD_ReadSCR_EN			0			/* 是否使能读SCR寄存器函数 */

#endif