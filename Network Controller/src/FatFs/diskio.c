/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
//#include "usbdisk.h"	/* Example: USB drive control */
//#include "atadrive.h"	/* Example: ATA drive control */
//#include "sdcard.h"		/* Example: MMC/SDC contorl */
#include "types.h"
#include "sddriver.h"
#include "sdhal.h"
#include "sdcmd.h"

/* Definitions of physical drive number for each media */
#define ATA		1
#define MMC		0
#define USB		2


/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber (0..) */
)
{
    U8_T state;
    if(pdrv)
    {
        return STA_NOINIT;  //��֧�ִ���0�Ĳ���
    }
 
    state = SD_Initialize();
    if(state == STA_NODISK)
    {
        return STA_NODISK;
    }
    else if(state != 0)
    {
        return STA_NOINIT;  //��ʼ��ʧ��
    }
    else
    {
        return 0;          //��ʼ���ɹ�
    }
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0..) */
)
{
   if(pdrv)
	{
		return 	STA_NOINIT;
	}

#if 0
    if (SD_ChkCard() != 1)	/* ��鿨�Ƿ���� check weather card is inserted */
    {
    	return 	STA_NOINIT;   
    } 
#endif


	return  0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..128) */
)
{
    U8_T res = 0;
    if (pdrv || !count)
    {   
        return RES_PARERR;  
    }
#if 0
    if(SD_ChkCard() != 1)
    {
        return RES_NOTRDY;  
    }
#endif

    if(count==1)            //1��sector�Ķ�����     
    {                                               
        res = SD_ReadBlock(sector, buff);     
    }                                               
    else                    //���sector�Ķ�����    
    {                                               
        res = SD_ReadMultiBlock(sector,count, buff);
    }                                               
    //������ֵ����SPI_SD_driver.c�ķ���ֵת��ff.c�ķ���ֵ
    if(res == 0x00)
    {
        return RES_OK;
    }
    else
    {
        return RES_ERROR;
    }
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..128) */
)
{
    U8_T res;
 
    if (pdrv || !count)
    {   
        return RES_PARERR;  
    }
#if 0
    if(SD_ChkCard() != 1)
    {
        return RES_NOTRDY; 
    }
#endif 
    // ��д����
    if(count == 1)
    {
        res = SD_WriteBlock(sector, buff);
    }
    else
    {
        res = SD_WriteMultiBlock(sector,count, buff);
    }
    // ����ֵת��
    if(res == 0)
    {
        return RES_OK;
    }
    else
    {
        return RES_ERROR;
    }

}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;

   if (pdrv)
    {   
        return RES_PARERR;  
    }
    //FATFSĿǰ�汾���账��CTRL_SYNC��GET_SECTOR_COUNT��GET_BLOCK_SIZ��������
    switch(cmd)
    {
    case CTRL_SYNC:
        SPI_CS_Assert();

        if(SD_ResetSD() == SD_NO_ERR)
        {
            res = RES_OK;
        }
        else
        {
            res = RES_ERROR;
        }
        SPI_CS_Deassert();
        break;
         
    case GET_BLOCK_SIZE:
        *(WORD*)buff = 512;
        res = RES_OK;
        break;
 
    case GET_SECTOR_COUNT:
        *(DWORD*)buff = SD_GetCardInfo();
        res = RES_OK;
        break;
    default:
        res = RES_PARERR;
        break;
    }
 
    return res;

}
#endif


/*-----------------------------------------------------------------------*/
/* User defined function to give a current time to fatfs module          */
/* 31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                         
/* 15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                               
DWORD get_fattime (void)
{
  return 0;
}



