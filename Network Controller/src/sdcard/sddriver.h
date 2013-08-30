/****************************************Copyright (c)**************************************************
**                               Guangzhou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			sddriver.c
** Last modified Date:	2005-3-10
** Last Version:		V2.0
** Descriptions:		SD/MMC卡读写模块: 物理层 用户API函数(头文件)
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
** Descriptions:		增加了对MMC卡的支持,增加了对UCOS-II的支持,使该模块不仅能运行于前后台系统,还可运行
**						于UCOS-II上
**------------------------------------------------------------------------------------------------------
** Modified by: 
** Modified date:
** Version:	
** Descriptions: 
**
********************************************************************************************************/

#ifndef __SDDRIVER_H__
#define __SDDRIVER_H__

/* SD卡信息结构体定义 */ 
/* the information structure variable of SD Card*/
typedef struct SD_STRUCT
{	
	U8_T card_type;
	U32_T block_num;				/* 卡中块的数量 */
	U32_T block_len;				/* 卡的块长度(单位:字节) */
	U32_T erase_unit;				/* 一次可擦除的块个数 */
	
	U32_T timeout_read;			/* 读块超时时间(单位: 8 SPI clock) */
	U32_T timeout_write;			/* 写块超时时间(单位: 8 SPI clock) */
	U32_T timeout_erase;			/* 擦块超时时间(单位: 8 SPI clock) */
	
}sd_struct;

extern sd_struct sds;				/* SD卡信息结构体变量 */ 

		/*
		*************************************************************

				用户API函数:	读, 写, 擦 SD卡  API函数及错误码
 			
		*************************************************************
		*/
		
/* 错误码 error code */
#define   SD_NO_ERR			     	0x00			// 函数执行成功
#define   SD_ERR_NO_CARD		 	0x01			// 卡没有完全插入到卡座中
#define   SD_ERR_USER_PARAM      	0x02			// 用户使用API函数时，入口参数有错误
#define   SD_ERR_CARD_PARAM		 	0x03			// 卡中参数有错误（与本模块不兼容）
#define	  SD_ERR_VOL_NOTSUSP        0x04			// 卡不支持3.3V供电
#define   SD_ERR_OVER_CARDRANGE		0x05			// 操作超出卡容量范围
#define   SD_ERR_UNKNOWN_CARD       0x06			// 无法识别卡型

/* SD命令可能返回的错误码 */
#define   SD_ERR_CMD_RESPTYPE	 	0x10			// 命令类型错误
#define   SD_ERR_CMD_TIMEOUT     	0x11			// 卡命令响应超时
#define   SD_ERR_CMD_RESP		 	0x12			// 卡命令响应错误
			
/* 数据流错误码 */
#define   SD_ERR_DATA_CRC16      	0x20			// 数据流CRC16校验不通过
#define   SD_ERR_DATA_START_TOK		0x21			// 读单块或多块时，数据开始令牌不正确
#define	  SD_ERR_DATA_RESP		 	0x22			// 写单块或多块时，卡数据响应令牌不正确

/* 等待错误码 */
#define   SD_ERR_TIMEOUT_WAIT    	0x30			// 写或擦操作时，发生超时错误
#define   SD_ERR_TIMEOUT_READ    	0x31			// 读操作超时错误
#define	  SD_ERR_TIMEOUT_WRITE	 	0x32			// 写操作超时错误
#define   SD_ERR_TIMEOUT_ERASE   	0x33			// 擦除操作超时错误
#define	  SD_ERR_TIMEOUT_WAITIDLE 	0x34			// 初始化卡时，等待卡退出空闲状态超时错误

/* 写操作可能返回的错误码 */
#define	  SD_ERR_WRITE_BLK			0x40			// 写块数据错误
#define	  SD_ERR_WRITE_BLKNUMS      0x41			// 写多块时，想要写入的块与正确写入的块数不一致
#define   SD_ERR_WRITE_PROTECT		0x42			// 卡外壳的写保护开关打在写保护位置

/* 使用UCOS-II时可能出现的错误 */
#define   SD_ERR_CREATE_SEMSD		0xA0			// 创建SD/MMC卡访问信号量失败



/**************************************************
	
			其它宏定义

***************************************************/
#define	  CARDTYPE_SD				0x00			// 卡型为SD  卡
#define   CARDTYPE_MMC				0x01			// 卡型为MMC 卡

#define   SD_UCOSII_SMALLWAIT		256				// 运行于UCOS-II时的小等待时间
#define   SD_READREG_TIMEOUT		8				// 读寄存器的超时时间
	
		
/* 初始化SD卡 initialize sd card */
extern U8_T SD_Initialize(void);	
							
/* 从SD卡中读一个块 read a single block from sd card */
extern U8_T SD_ReadBlock(U32_T blockaddr, U8_T *recbuf);  

/* 从SD卡中读多个块	read multi blocks from sd card */																	
extern U8_T SD_ReadMultiBlock(U32_T blockaddr, U32_T blocknum, U8_T *recbuf); 
 
/* 向SD卡中写入一个块 write a block to sd card */               
extern U8_T SD_WriteBlock(U32_T blockaddr, U8_T *recbuf);  

/* 向SD卡中写入多个块 write multi blocks to sd card */  
extern U8_T SD_WriteMultiBlock(U32_T blockaddr, U32_T blocknum, U8_T *recbuf); 

/* 擦除SD卡中的块 Erase the block of sd card */
extern U8_T SD_EraseBlock(U32_T startaddr, U32_T blocknum); 

/* 得到SD卡信息 get information of sd card */
extern U8_T SD_GetCardInfo(void);

/* 由CSD寄存器计算超时时间 calculate timeout from CSD register */
extern U8_T SD_CalTimeout(U8_T *csdbuf);

/* 激活SD卡内部进行初始化处理 active sd to initialize process */
extern U8_T SD_ActiveInit(void);

/* 向OS申请访问卡的信号量 request semaphore accessed card to OS */
extern void SD_StartSD(void);

/* 将访问卡的信号量还给OS return semaphore accessed card to OS */
extern void SD_EndSD(void);


	    /*
	    *************************************************************
	    
	     			下面为软件包用到的与SD卡相关的宏定义
	     	
	    *************************************************************
	    */
	    	    	    
/* Mask off the bits in the OCR corresponding to voltage range 3.2V to
 * 3.4V, OCR bits 20 and 21 */
#define MSK_OCR_33			 	0xC0

/* 定义在初始化阶段,等待SD卡退出空闲状态的重试次数 */
/* Number of tries to wait for the card to go idle during initialization */
#define SD_IDLE_WAIT_MAX     	1000

/* SD卡命令超时时间(单位 8clock)*/
/* timeout of command */
#define SD_CMD_TIMEOUT   	 	100
	
/* 100ms 相当的SPI时钟数(单位 unit: 8 clocks) */
/* 100ms correspond to SPI clock(unit: 8 clocks)*/
#define READ_TIMEOUT_100MS      100 * SPI_CLOCK / 1000 / 8

/* 250ms 相当的SPI时钟数(单位 unit: 8 clocks) */
/* 250ms correspond to SPI clock(unit: 8 clocks)*/
#define WRITE_TIMEOUT_250MS		250 * SPI_CLOCK / 1000 / 8    


/* CSD中一些域的字节位置(高字节在前) */
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
#define ERASE_GRP_SIZE_POS   	10		//MMC卡 ERASE_GRP_SIZE 5-bit
#define ERASE_GRP_MULTI_POS1 	10		//MMC卡 ERASE_GRP_MULTI 2-bit
#define ERASE_GRP_MULTI_POS2 	11		//MMC卡 ERASE_GRP_MULTI 3-bit


//CSD中一些域的掩码
#define TAAC_MSK			0x07		//TACC 域掩码
#define NSAC_MSK			0x78		//NSAC 域掩码

#define READ_BL_LEN_MSK		0x0F		//READ_BL_LEN 的掩码

#define C_SIZE_MSK1			0x03		//C_SIZE 高2位掩码
#define C_SIZE_MSK3			0xC0		//C_SIZE 低2位掩码

#define C_SIZE_MULT_MSK1 	0x03		//C_SIZE_MULT 的高2位掩码
#define C_SIZE_MULT_MSK2 	0x80		//C_SIZE_MULT 的低2位掩码

#define R2WFACTOR_MSK		0x1C		//R2WFACTOR 掩码

#define SECTOR_SIZE_MSK1	0x3F		//SECTOR_SIZE 的高5位
#define SECTOR_SIZE_MSK2	0x80		//SECTOR_SIZE 的低2位

#define ERASE_GRP_SIZE_MSK 		0x7C		//MMC卡 ERASE_GRP_SIZE 掩码
#define ERASE_GRP_MULTI_MSK1 	0x03		//MMC卡 ERASE_GRP_MULTI 高2位掩码
#define ERASE_GRP_MULTI_MSK2 	0xE0		//MMC卡 ERASE_GRP_NULTI 低3位掩码

#endif
                    