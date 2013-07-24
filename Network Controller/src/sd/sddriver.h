/****************************************Copyright (c)**************************************************
**                               Guangzhou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			sddriver.c
** Last modified Date:	2005-3-10
** Last Version:		V2.0
** Descriptions:		SD/MMC����дģ��: ����� �û�API����(ͷ�ļ�)
**						Soft Packet of SD Card: user API funciton (header file)
**
**------------------------------------------------------------------------------------------------------
** Created by:			Ming Yuan Zheng
** Created date:		2005-1-6
** Version:				V1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			Ming Yuan Zheng
** Modified date:		2005-3-10
** Version:				V2.0
** Descriptions:		�����˶�MMC����֧��,�����˶�UCOS-II��֧��,ʹ��ģ�鲻����������ǰ��̨ϵͳ,��������
**						��UCOS-II��
**------------------------------------------------------------------------------------------------------
** Modified by: 
** Modified date:
** Version:	
** Descriptions: 
**
********************************************************************************************************/

#ifndef __SDDRIVER_H__
#define __SDDRIVER_H__

/* SD����Ϣ�ṹ�嶨�� */ 
/* the information structure variable of SD Card*/
typedef struct SD_STRUCT
{	
	U8_T card_type;
	U32_T block_num;				/* ���п������ */
	U32_T block_len;				/* ���Ŀ鳤��(��λ:�ֽ�) */
	U32_T erase_unit;				/* һ�οɲ����Ŀ���� */
	
	U32_T timeout_read;			/* ���鳬ʱʱ��(��λ: 8 SPI clock) */
	U32_T timeout_write;			/* д�鳬ʱʱ��(��λ: 8 SPI clock) */
	U32_T timeout_erase;			/* ���鳬ʱʱ��(��λ: 8 SPI clock) */
	
}sd_struct;

extern sd_struct sds;				/* SD����Ϣ�ṹ����� */ 

		/*
		*************************************************************

				�û�API����:	��, д, �� SD��  API������������
 			
		*************************************************************
		*/
		
/* ������ error code */
#define   SD_NO_ERR			     	0x00			// ����ִ�гɹ�
#define   SD_ERR_NO_CARD		 	0x01			// ��û����ȫ���뵽������
#define   SD_ERR_USER_PARAM      	0x02			// �û�ʹ��API����ʱ����ڲ����д���
#define   SD_ERR_CARD_PARAM		 	0x03			// ���в����д����뱾ģ�鲻���ݣ�
#define	  SD_ERR_VOL_NOTSUSP        0x04			// ����֧��3.3V����
#define   SD_ERR_OVER_CARDRANGE		0x05			// ����������������Χ
#define   SD_ERR_UNKNOWN_CARD       0x06			// �޷�ʶ����

/* SD������ܷ��صĴ����� */
#define   SD_ERR_CMD_RESPTYPE	 	0x10			// �������ʹ���
#define   SD_ERR_CMD_TIMEOUT     	0x11			// ��������Ӧ��ʱ
#define   SD_ERR_CMD_RESP		 	0x12			// ��������Ӧ����
			
/* ������������ */
#define   SD_ERR_DATA_CRC16      	0x20			// ������CRC16У�鲻ͨ��
#define   SD_ERR_DATA_START_TOK		0x21			// ���������ʱ�����ݿ�ʼ���Ʋ���ȷ
#define	  SD_ERR_DATA_RESP		 	0x22			// д�������ʱ����������Ӧ���Ʋ���ȷ

/* �ȴ������� */
#define   SD_ERR_TIMEOUT_WAIT    	0x30			// д�������ʱ��������ʱ����
#define   SD_ERR_TIMEOUT_READ    	0x31			// ��������ʱ����
#define	  SD_ERR_TIMEOUT_WRITE	 	0x32			// д������ʱ����
#define   SD_ERR_TIMEOUT_ERASE   	0x33			// ����������ʱ����
#define	  SD_ERR_TIMEOUT_WAITIDLE 	0x34			// ��ʼ����ʱ���ȴ����˳�����״̬��ʱ����

/* д�������ܷ��صĴ����� */
#define	  SD_ERR_WRITE_BLK			0x40			// д�����ݴ���
#define	  SD_ERR_WRITE_BLKNUMS      0x41			// д���ʱ����Ҫд��Ŀ�����ȷд��Ŀ�����һ��
#define   SD_ERR_WRITE_PROTECT		0x42			// ����ǵ�д�������ش���д����λ��

/* ʹ��UCOS-IIʱ���ܳ��ֵĴ��� */
#define   SD_ERR_CREATE_SEMSD		0xA0			// ����SD/MMC�������ź���ʧ��



/**************************************************
	
			�����궨��

***************************************************/
#define	  CARDTYPE_SD				0x00			// ����ΪSD  ��
#define   CARDTYPE_MMC				0x01			// ����ΪMMC ��

#define   SD_UCOSII_SMALLWAIT		256				// ������UCOS-IIʱ��С�ȴ�ʱ��
#define   SD_READREG_TIMEOUT		8				// ���Ĵ����ĳ�ʱʱ��
	
		
/* ��ʼ��SD�� initialize sd card */
extern U8_T SD_Initialize(void);	
							
/* ��SD���ж�һ���� read a single block from sd card */
extern U8_T SD_ReadBlock(U32_T blockaddr, U8_T *recbuf);  

/* ��SD���ж������	read multi blocks from sd card */																	
extern U8_T SD_ReadMultiBlock(U32_T blockaddr, U32_T blocknum, U8_T *recbuf); 
 
/* ��SD����д��һ���� write a block to sd card */               
extern U8_T SD_WriteBlock(U32_T blockaddr, U8_T *recbuf);  

/* ��SD����д������ write multi blocks to sd card */  
extern U8_T SD_WriteMultiBlock(U32_T blockaddr, U32_T blocknum, U8_T *recbuf); 

/* ����SD���еĿ� Erase the block of sd card */
extern U8_T SD_EraseBlock(U32_T startaddr, U32_T blocknum); 

/* �õ�SD����Ϣ get information of sd card */
extern U8_T SD_GetCardInfo(void);

/* ��CSD�Ĵ������㳬ʱʱ�� calculate timeout from CSD register */
extern U8_T SD_CalTimeout(U8_T *csdbuf);

/* ����SD���ڲ����г�ʼ������ active sd to initialize process */
extern U8_T SD_ActiveInit(void);

/* ��OS������ʿ����ź��� request semaphore accessed card to OS */
extern void SD_StartSD(void);

/* �����ʿ����ź�������OS return semaphore accessed card to OS */
extern void SD_EndSD(void);


	    /*
	    *************************************************************
	    
	     			����Ϊ������õ�����SD����صĺ궨��
	     	
	    *************************************************************
	    */
	    	    	    
/* Mask off the bits in the OCR corresponding to voltage range 3.2V to
 * 3.4V, OCR bits 20 and 21 */
#define MSK_OCR_33			 	0xC0

/* �����ڳ�ʼ���׶�,�ȴ�SD���˳�����״̬�����Դ��� */
/* Number of tries to wait for the card to go idle during initialization */
#define SD_IDLE_WAIT_MAX     	1000

/* SD�����ʱʱ��(��λ 8clock)*/
/* timeout of command */
#define SD_CMD_TIMEOUT   	 	100
	
/* 100ms �൱��SPIʱ����(��λ unit: 8 clocks) */
/* 100ms correspond to SPI clock(unit: 8 clocks)*/
#define READ_TIMEOUT_100MS      100 * SPI_CLOCK / 1000 / 8

/* 250ms �൱��SPIʱ����(��λ unit: 8 clocks) */
/* 250ms correspond to SPI clock(unit: 8 clocks)*/
#define WRITE_TIMEOUT_250MS		250 * SPI_CLOCK / 1000 / 8    


/* CSD��һЩ����ֽ�λ��(���ֽ���ǰ) */
#define TAAC_POS 			1			//TACC
#define NSAC_POS			2			//NSAC

#define READ_BL_LEN_POS		5			//READ_BL_LEN

#define C_SIZE_POS1			6			//C_SIZE upper  2-bit
#define C_SIZE_POS2			7			//C_SIZE middle 8-bit
#define C_SIZE_POS3			8			//C_SIZE lower	2-bit

#define C_SIZE_MULT_POS1	9			//C_SIZE_MULT upper 2-bit
#define C_SIZE_MULT_POS2	10			//C_SIZE_MULT lower 1-bit	

#define SECTOR_SIZE_POS1	10			//SECTOR_SIZE upper 5-bit
#define SECTOR_SIZE_POS2	11			//SECTOR_SIZE lower 2-bit

#define R2WFACTOR_POS 		12			//R2WFACTOR_POS

/**/
#define ERASE_GRP_SIZE_POS   	10		//MMC�� ERASE_GRP_SIZE 5-bit
#define ERASE_GRP_MULTI_POS1 	10		//MMC�� ERASE_GRP_MULTI 2-bit
#define ERASE_GRP_MULTI_POS2 	11		//MMC�� ERASE_GRP_MULTI 3-bit


//CSD��һЩ�������
#define TAAC_MSK			0x07		//TACC ������
#define NSAC_MSK			0x78		//NSAC ������

#define READ_BL_LEN_MSK		0x0F		//READ_BL_LEN ������

#define C_SIZE_MSK1			0x03		//C_SIZE ��2λ����
#define C_SIZE_MSK3			0xC0		//C_SIZE ��2λ����

#define C_SIZE_MULT_MSK1 	0x03		//C_SIZE_MULT �ĸ�2λ����
#define C_SIZE_MULT_MSK2 	0x80		//C_SIZE_MULT �ĵ�2λ����

#define R2WFACTOR_MSK		0x1C		//R2WFACTOR ����

#define SECTOR_SIZE_MSK1	0x3F		//SECTOR_SIZE �ĸ�5λ
#define SECTOR_SIZE_MSK2	0x80		//SECTOR_SIZE �ĵ�2λ

#define ERASE_GRP_SIZE_MSK 		0x7C		//MMC�� ERASE_GRP_SIZE ����
#define ERASE_GRP_MULTI_MSK1 	0x03		//MMC�� ERASE_GRP_MULTI ��2λ����
#define ERASE_GRP_MULTI_MSK2 	0xE0		//MMC�� ERASE_GRP_NULTI ��3λ����

#endif
                    