/****************************************Copyright (c)**************************************************
**                               Guangzhou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			sdcmd.h
** Last modified Date:	2005-3-11
** Last Version:		V2.0
** Descriptions:		SD/MMC ��дģ��: ����� ---- SD/MMC ��SPIģʽ֧�ֵ�����(ͷ�ļ�) 
**						Soft Packet of SD/MMC Card : commands that SD/MMC card supported 
**						in spi mode(header file)
**------------------------------------------------------------------------------------------------------
** Created by:			Ming Yuan Zheng
** Created date:		2005-1-6
** Version:				V1.0
** Descriptions:		SD/MMC ��дģ��: ����� ---- SD��SPIģʽ֧�ֵ����� 
**
**------------------------------------------------------------------------------------------------------
** Modified by:			Ming Yuan Zheng
** Modified date:		2005-3-11
** Version:				V2.0
** Descriptions:		�����˶�MMC����֧��,��ʹ�ñ�ģ��ȿ���������ǰ��̨ϵͳ,Ҳ��������uCOS-II��.
**
**------------------------------------------------------------------------------------------------------
** Modified by: 
** Modified date:
** Version:	
** Descriptions: 
**
********************************************************************************************************/

#ifndef __SDCMD_H__
#define __SDCMD_H__

/*
 *******************************************************
	
		SD/MMC ���������������Ӧ�궨��
	
 *******************************************************
*/

/* ������Ӧ���� define command's response */
#define R1 	1
#define R1B 2
#define R2 	3
#define R3 	4

/* R1��R2���ֽڴ����� R1 and upper byte of R2 error code */
#define MSK_IDLE          		  0x01
#define MSK_ERASE_RST     		  0x02
#define MSK_ILL_CMD       		  0x04
#define MSK_CRC_ERR       		  0x08
#define MSK_ERASE_SEQ_ERR 		  0x10
#define MSK_ADDR_ERR      		  0x20
#define MSK_PARAM_ERR     		  0x40

/* R2���ֽڴ����� lower byte of R2 error code */
#define MSK_TOK_ERROR             0x01
#define MSK_TOK_CC_ERROR          0x02
#define MSK_TOK_ECC_FAILED        0x04
#define MSK_TOK_CC_OUTOFRANGE     0x08
#define MSK_TOK_CC_LOCKED         0x10



/* �������� Data Tokens */
#define SD_TOK_READ_STARTBLOCK    0xFE
#define SD_TOK_WRITE_STARTBLOCK   0xFE
#define SD_TOK_READ_STARTBLOCK_M  0xFE
#define SD_TOK_WRITE_STARTBLOCK_M 0xFC
#define SD_TOK_STOP_MULTI         0xFD

/* ������Ӧ���� Data Response Tokens */
#define SD_RESP_DATA_MSK		  0x0F		//������Ӧ����
#define SD_RESP_DATA_ACCETPTED	  0x05		//���ݱ�����
#define SD_RESP_DATA_REJECT_CRC	  0x0B      //����CRC��������ܾ�
#define SD_RESP_DATA_REJECT_WRITE 0x0D		//����д��������ܾ�

/* �ȴ����� Wait Type */
#define SD_WAIT_READ			  0x00		//���ȴ�
#define SD_WAIT_WRITE			  0x01		//д�ȴ�
#define SD_WAIT_ERASE		 	  0x02		//�����ȴ�


/*
*********************************************

     SD��SPIģʽ�����

*********************************************
*/

/******************************** ������� Basic command set **************************/
/* ��λSD �� Reset cards to idle state */
#define CMD0 0
#define CMD0_R R1

/* ��OCR�Ĵ��� Read the OCR (MMC mode, do not use for SD cards) */
#define CMD1 1
#define CMD1_R R1

/* ��CSD�Ĵ��� Card sends the CSD */
#define CMD9 9
#define CMD9_R R1

/* ��CID�Ĵ��� Card sends CID */
#define CMD10 10
#define CMD10_R R1

/* ֹͣ�����ʱ�����ݴ��� Stop a multiple block (stream) read/write operation */
#define CMD12 12
#define CMD12_R R1B

/* �� Card_Status �Ĵ��� Get the addressed card's status register */
#define CMD13 13
#define CMD13_R R2

/***************************** ������ Block read commands **************************/

/* ���ÿ�ĳ��� Set the block length */
#define CMD16 16
#define CMD16_R R1

/* ������ Read a single block */
#define CMD17 17
#define CMD17_R R1

/* �����,ֱ����������CMD12Ϊֹ Read multiple blocks until a CMD12 */
#define CMD18 18
#define CMD18_R R1

/***************************** ��д��� Block write commands *************************/
/* д���� Write a block of the size selected with CMD16 */
#define CMD24 24
#define CMD24_R R1

/* д��� Multiple block write until a CMD12 */
#define CMD25 25
#define CMD25_R R1

/* дCSD�Ĵ��� Program the programmable bits of the CSD */
#define CMD27 27
#define CMD27_R R1

/***************************** д���� Write protection *****************************/
/* Set the write protection bit of the addressed group */
#define CMD28 28
#define CMD28_R R1B

/* Clear the write protection bit of the addressed group */
#define CMD29 29
#define CMD29_R R1B

/* Ask the card for the status of the write protection bits */
#define CMD30 30
#define CMD30_R R1

/***************************** �������� Erase commands *******************************/
/* ���ò��������ʼ��ַ(ֻ����SD��) Set the address of the first write block to be erased(only for SD) */
#define CMD32 32
#define CMD32_R R1

/* ���ò��������ֹ��ַ(ֻ����SD��) Set the address of the last write block to be erased(only for SD) */
#define CMD33 33
#define CMD33_R R1

/* ���ò��������ʼ��ַ(ֻ����MMC��) Set the address of the first write block to be erased(only for MMC) */
#define CMD35 35
#define CMD35_R R1

/* ���ò��������ֹ��ַ(ֻ����MMC��) Set the address of the last write block to be erased(only for MMC) */
#define CMD36 36
#define CMD36_R R1

/* ������ѡ��Ŀ� Erase the selected write blocks */
#define CMD38 38
#define CMD38_R R1B

/***************************** �������� Lock Card commands ***************************/
/* ����/��λ���������/������ Set/reset the password or lock/unlock the card */
#define CMD42 42
#define CMD42_R	R1B
/* Commands from 42 to 54, not defined here */

/***************************** Ӧ������ Application-specific commands ****************/
/* ��ֹ��һ������ΪӦ������  Flag that the next command is application-specific */
#define CMD55 55
#define CMD55_R R1

/* Ӧ�������ͨ��I/O  General purpose I/O for application-specific commands */
#define CMD56 56
#define CMD56_R R1

/* ��OCR�Ĵ���  Read the OCR (SPI mode only) */
#define CMD58 58
#define CMD58_R R3

/* ʹ�ܻ��ֹ CRC Turn CRC on or off */
#define CMD59 59
#define CMD59_R R1

/***************************** Ӧ������ Application-specific commands ***************/
/* ��ȡ SD Status�Ĵ��� Get the SD card's status */
#define ACMD13 13
#define ACMD13_R R2

/* �õ���д�뿨�еĿ�ĸ��� Get the number of written write blocks (Minus errors ) */
#define ACMD22 22
#define ACMD22_R R1

/* ��д֮ǰ,����Ԥ�Ȳ����Ŀ�ĸ��� Set the number of write blocks to be pre-erased before writing */
#define ACMD23 23
#define ACMD23_R R1

/* ��ȡOCR�Ĵ��� Get the card's OCR (SD mode) */
#define ACMD41 41
#define ACMD41_R R1

/* ����/�Ͽ�CD/DATA[3]�����ϵ��������� Connect or disconnect the 50kOhm internal pull-up on CD/DAT[3] */
#define ACMD42 42
#define ACMD42_R R1

/* ��ȡSCR�Ĵ��� Get the SD configuration register */
#define ACMD51 51
#define ACMD51_R R1



extern U8_T SD_SendCmd(U8_T cmd, U8_T *param, U8_T resptype, U8_T *resp);   // һ��SPI����   a SPI command
extern void SD_PackParam(U8_T *parameter, U32_T value);						// ��װ����	  	 pack the parameter
extern U8_T SD_BlockCommand(U8_T cmd, U8_T resptype, U32_T parameter);		// ������ 		 block command 

	
extern U8_T SD_ResetSD(void);												// ��λSD��			reset SD Card

extern U8_T SD_ReadCSD(U8_T csdlen, U8_T *recbuf);							// ��CSD 			read CSD register
extern U8_T SD_ReadCID(U8_T cidlen, U8_T *recbuf);							// ��CID			read CID register
extern U8_T SD_StopTransmission(void);										// ֹͣ����			stop transmission

extern U8_T SD_ReadCard_Status(U8_T *buffer);								// ��Card Status	read Card Status register
extern U8_T SD_SetBlockLen(U32_T length);									// ���ÿ鳤��		set block length

extern U8_T SD_ReadSingleBlock(U32_T blockaddr);							// ������			read a single block
extern U8_T SD_ReadMultipleBlock(U32_T blockaddr);							// �����			read multiple block

extern U8_T SD_WriteSingleBlock(U32_T blockaddr);							// д����			write a single block
extern U8_T SD_WriteMultipleBlock(U32_T blockaddr);							// д��� 			write multiple block


extern U8_T SD_ProgramCSD(U8_T len, U8_T *buff);						// дCSD�Ĵ���  	write CSD register 

extern U8_T SD_EraseStartBlock(U32_T startblock);						// ������ʼ��ַ		erase start address
extern U8_T SD_EraseEndBlock(U32_T endblock);							// ������ֹ��ַ		erase end address
extern U8_T SD_EraseSelectedBlock(void);								// ������ѡ�Ŀ�		erase selected address


extern U8_T SD_ReadOCR(U8_T *recbuf);					// ��OCR			read OCR register
extern U8_T SD_EnableCRC(U8_T bEnable);								// ʹ��CRCУ��		enable CRC


// ����Ӧ������
extern U8_T SD_ReadSD_Status(U8_T sdslen, U8_T *recbuf);				// ��SD_Status		read SD_Status 
extern U8_T SD_GetNumWRBlcoks(U32_T *blocknum);						// �õ���ȷд����� get block numbers that writed well
extern U8_T SD_ReadSCR(U8_T scrlen, U8_T *recbuf);					// ��SCR 			read SCR register


// ����������
extern U8_T SD_ReadRegister(U32_T len, U8_T *recbuf);						// ���Ĵ���  read register 
extern U8_T SD_ReadBlockData(U32_T len, U8_T *recbuf);						// ��������	 read block data 
extern U8_T SD_WriteBlockData(U8_T bmulti, U32_T len, U8_T *sendbuf);		// д������	 write block data

// ��������
extern void SD_StopMultiToken(void);									// ֹͣ���д����	 stop token when write multiple block
extern U8_T SD_WaitBusy(U8_T waittype);								// æ				 busy
extern void SD_SPIDelay(U8_T value);									// ����SPIʱ��		 send SPI clock


#endif













