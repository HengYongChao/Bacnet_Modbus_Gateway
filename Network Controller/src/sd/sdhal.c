/****************************************Copyright (c)**************************************************
**                               Guangzhou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			sdhal.c
** Last modified Date:	2005-3-11
** Last Version:		V2.0
** Descriptions:		SD/MMC����дģ��: Ӳ������� ---- SPI��������
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
		
		��дSD����SPI�ӿں���: SPI�ӿ�����,����/�����ֽں���	
	
	**************************************************************/


/*******************************************************************************************************************
** ��������: void SD_HardWareInit()				Name:	  void SD_HardWareInit()
** ��������: ��ʼ������SD����Ӳ������			Function: initialize the hardware condiction that access sd card
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SD_HardWareInit(void)
{ 	

 	SPI_Clk400k();								/* ����SPIƵ��С�ڵ���400kHZ  set frequency of SPI below 400kHZ */  
	SPI_CS_SET();								/* CS�ø�	  				  set CS to high voltage */

}												/* configure SPI interface */


/*******************************************************************************************************************
** ��������: void SPI_Clk400k()					Name:	  void SPI_Clk400k()
** ��������: ����SPI��ʱ��С��400kHZ			Function: set the clock of SPI less than 400kHZ
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
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
** ��������: void SPI_ClkToMax()				Name:	  void SPI_ClkToMax()
** ��������: ����SPI��clock�����ֵ				Function: set the clock of SPI to maximum
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
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
** ��������: void SPI_SendByte()				Name:	  void SPI_SendByte()
** ��������: ͨ��SPI�ӿڷ���һ���ֽ�			Function: send a byte by SPI interface
** �䡡  ��: U8_T byte: ���͵��ֽ�				Input:	  U8_T byte: the byte that will be send
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SPI_SendByte(U8_T byte)
{
	SPI_FlagEnb(SPI_BUSY);
	SPI_MstXmit(&byte, 8, SPI_NORMAL_LEN|SPI_GO_BSY);
	while (SPI_FlagChk(SPI_BUSY)); 
}


/*******************************************************************************************************************
** ��������: U8_T SPI_RecByte()				Name:	  U8_T SPI_RecByte()
** ��������: ��SPI�ӿڽ���һ���ֽ�				Function: receive a byte from SPI interface
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: �յ����ֽ�							Output:	  the byte that be received
********************************************************************************************************************/
U8_T SPI_RecByte(void)
{
	U8_T byteWrite=0xff;
	U8_T byteRead;
	SPI_FlagEnb(SPI_BUSY);
	SPI_MstXmit(&byteWrite, 8, SPI_NORMAL_LEN|SPI_GO_BSY);
	while (SPI_FlagChk(SPI_BUSY)); 
	SPI_GetData(&byteRead);						/* wait for SPIF being set, that is, wait for being received data */
	return(byteRead); 							/* ��ȡ�յ����ֽ� read the byte received */
}


/*******************************************************************************************************************
** ��������: void SPI_CS_Assert()				Name:	  void SPI_CS_Assert()
** ��������: ƬѡSPI�ӻ�						Function: select the SPI slave 
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SPI_CS_Assert(void)
{
	SPI_CS_CLR();			   					/* ƬѡSPI�ӻ�  select the SPI slave */  
}


/*******************************************************************************************************************
** ��������: void SPI_CS_Deassert()				Name:	  void SPI_CS_Deassert()
** ��������: ��ƬѡSPI�ӻ�						Function: not select the SPI slave 
** �䡡  ��: ��									Input:	  NULL
** �� �� ��: ��									Output:	  NULL
********************************************************************************************************************/
void SPI_CS_Deassert(void)
{
	SPI_CS_SET();			    				/* ��ƬѡSPI�ӻ�  not select the SPI slave */
}









