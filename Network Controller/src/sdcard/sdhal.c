/****************************************Copyright (c)**************************************************
**                               Guangzhou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			sdhal.c
** Last modified Date:	2005-3-11
** Last Version:		V2.0
** Descriptions:		SD/MMC卡读写模块: 硬件抽象层 ---- SPI操作函数
**						Soft Packet of SD/MMC Card: hard abstrast layer ---- function of SPI operation
**
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

#include "AX110xx.h"
#include "sdconfig.h"
#include "sdhal.h"
#include "spi.h"

	/**************************************************************
		
		读写SD卡的SPI接口函数: SPI接口设置,发送/接收字节函数	
	
	**************************************************************/


/*******************************************************************************************************************
** 函数名称: void SD_HardWareInit()				Name:	  void SD_HardWareInit()
** 功能描述: 初始化访问SD卡的硬件条件			Function: initialize the hardware condiction that access sd card
** 输　  入: 无									Input:	  NULL
** 输 　 出: 无									Output:	  NULL
********************************************************************************************************************/
void SD_HardWareInit(void)
{ 	

 	SPI_Clk400k();								/* 设置SPI频率小于等于400kHZ  set frequency of SPI below 400kHZ */  
	SPI_CS_SET();								/* CS置高	  				  set CS to high voltage */

}												/* configure SPI interface */


/*******************************************************************************************************************
** 函数名称: void SPI_Clk400k()					Name:	  void SPI_Clk400k()
** 功能描述: 设置SPI的时钟小于400kHZ			Function: set the clock of SPI less than 400kHZ
** 输　  入: 无									Input:	  NULL
** 输 　 出: 无									Output:	  NULL
********************************************************************************************************************/
void SPI_Clk400k(void)
{
	U8_T baudrate;
	switch (CSREPR & (BIT6|BIT7))
		{
			case SCS_100M :
				baudrate=125;
 				break;
			case SCS_50M :
				baudrate=62;
				break;
			case SCS_25M :
                baudrate=31;
				break;
		}

	SPI_Setup(SPI_SSO_ENB|SPI_MST_SEL|SPI_CPOL_LOW|SPI_CPHA_BEG|SPI_ENB, SPI_STCFIE, baudrate, SLAVE_SEL_0); 

	
    SPI_CS_SET();
}


/*******************************************************************************************************************
** 函数名称: void SPI_ClkToMax()				Name:	  void SPI_ClkToMax()
** 功能描述: 设置SPI的clock到最大值				Function: set the clock of SPI to maximum
** 输　  入: 无									Input:	  NULL
** 输 　 出: 无									Output:	  NULL
********************************************************************************************************************/
void SPI_ClkToMax(void)
{   
	U8_T baudrate;
	switch (CSREPR & (BIT6|BIT7))
		{
			case SCS_100M :
				baudrate=1;
 				break;
			case SCS_50M :
				baudrate=1;
				break;
			case SCS_25M :
                baudrate=1;
				break;
		}

	SPI_Cmd(SI_WR, SPIBRR, &baudrate);

}


/*******************************************************************************************************************
** 函数名称: void SPI_SendByte()				Name:	  void SPI_SendByte()
** 功能描述: 通过SPI接口发送一个字节			Function: send a byte by SPI interface
** 输　  入: U8_T byte: 发送的字节				Input:	  U8_T byte: the byte that will be send
** 输 　 出: 无									Output:	  NULL
********************************************************************************************************************/
void SPI_SendByte(U8_T byte)
{
	SPI_FlagEnb(SPI_BUSY);
	SPI_MstXmit(&byte, 8, SPI_NORMAL_LEN|SPI_GO_BSY);
	while (SPI_FlagChk(SPI_BUSY)); 
}


/*******************************************************************************************************************
** 函数名称: U8_T SPI_RecByte()				Name:	  U8_T SPI_RecByte()
** 功能描述: 从SPI接口接收一个字节				Function: receive a byte from SPI interface
** 输　  入: 无									Input:	  NULL
** 输 　 出: 收到的字节							Output:	  the byte that be received
********************************************************************************************************************/
U8_T SPI_RecByte(void)
{
	U8_T byteWrite=0xff;
	U8_T byteRead;
	SPI_FlagEnb(SPI_BUSY);
	SPI_MstXmit(&byteWrite, 8, SPI_NORMAL_LEN|SPI_GO_BSY);
	while (SPI_FlagChk(SPI_BUSY)); 
	SPI_GetData(&byteRead);						/* wait for SPIF being set, that is, wait for being received data */
	return(byteRead); 							/* 读取收到的字节 read the byte received */
}


/*******************************************************************************************************************
** 函数名称: void SPI_CS_Assert()				Name:	  void SPI_CS_Assert()
** 功能描述: 片选SPI从机						Function: select the SPI slave 
** 输　  入: 无									Input:	  NULL
** 输 　 出: 无									Output:	  NULL
********************************************************************************************************************/
void SPI_CS_Assert(void)
{
	SPI_CS_CLR();			   					/* 片选SPI从机  select the SPI slave */  
}


/*******************************************************************************************************************
** 函数名称: void SPI_CS_Deassert()				Name:	  void SPI_CS_Deassert()
** 功能描述: 不片选SPI从机						Function: not select the SPI slave 
** 输　  入: 无									Input:	  NULL
** 输 　 出: 无									Output:	  NULL
********************************************************************************************************************/
void SPI_CS_Deassert(void)
{
	SPI_CS_SET();			    				/* 不片选SPI从机  not select the SPI slave */
}









