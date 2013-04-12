/*
 *********************************************************************************
 *     Copyright (c) 2006	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 *********************************************************************************
 */
/*================================================================================
 * Module Name : flash.c
 * Purpose     : 
 * Author      : 
 * Date        : 
 * Notes       : 
 *
 *================================================================================
 */



#include	<absacc.h>
#include	"reg80390.h"
#include	"types.h"
#include	"ax11000.h"
#include	"flash.h"
#include	"mstimer.h"
#include	<absacc.h>
#include	"reg80390.h"
#include 	"ax11000_cfg.h"
#include	"flash.h"

/* GLOBAL VARIABLE DECLARATIONS */
U8_T IDATA fwAutoUpdated[4] _at_ 0x31;


/* GLOBAL VARIABLE DECLARATIONS */
U8_T CODE* PFlash = 0x6000;


#if (RUNTIME_CODE_START_ADDRESS == RUNTIME_CODE_START_AT_24kH)

typedef S16_T (*pFlashWrite)(U32_T ProgAddr, U8_T * ptWrData/*, U32_T ProgLen, U8_T BootldrSel*/);
typedef S16_T (*pFlashErase)(U32_T EraAddr);

/*
 *--------------------------------------------------------------------------------
 * S16_T IntFlashWrite(U32_T ProgAddr, U8_T *ptWrData,
 *                     U32_T ProgLen, U8_T BootldrSel)
 * Purpose : save prWrtData in Praddr with ProgLen bytes
 * Params  :	ProgAddr - start address
 *				ptWrData - source data array
 *				ProgLen  - no use
 *				BootldrSel  - no use
 * Returns : TRUE or FALSE, whether the routine is done successfully 
 * Note    :
 *-------------------------------------------------------------------------------
 */

S16_T IntFlashWrite(U32_T ProgAddr, U8_T *ptWrData, U32_T ProgLen, U8_T BootldrSel)
{
	U8_T	ret = FALSE;
	pFlashWrite	ptrFlashWrite = (void code*)0x003100;

	ProgLen = ProgLen;
	BootldrSel = BootldrSel;

	EA = 0;
	ret = (*ptrFlashWrite)(ProgAddr, ptWrData);	
	EA = 1;
	if (ret == FALSE)		return FALSE;	
	return TRUE;
}
/*
 *--------------------------------------------------------------------------------
 * S16_T S16_T IntFlashErase(U8_T EraseSel,U32_T EraAddr) 
 * Purpose : Erase a flash block
 * Params  : EraseSel - no use
 *			 EraAddr  - start flash block address you want to erase
 * Returns : TRUE or FALSE, whether the routine is done successfully 
 * Note    :
 *-------------------------------------------------------------------------------
 */
S16_T IntFlashErase(U8_T EraseSel,U32_T EraAddr) //large reentrant
{
	U8_T	ret = FALSE;	
	pFlashErase  ptrFlashErase = (void code*)0x003B00;

	EraseSel = EraseSel;

	EA = 0;
	ret = (*ptrFlashErase)(EraAddr);
	EA = 1;	
	if (ret == FALSE)		return FALSE;
	return TRUE;
}

#else
/*
 *--------------------------------------------------------------------------------
 * S16_T IntFlashWrite(U32_T ProgAddr, U8_T *ptWrData,
 *                     U32_T ProgLen, U8_T BootldrSel)
 * Purpose : save prWrtData in Praddr with ProgLen bytes
 * Params  :	ProgAddr - start address
 *				ptWrData - source data array
 *				ProgLen  - the length of source datas
 *				BootldrSel  - select the boot load way or application way, for my application ,select ERA_RUN
 * Returns : TRUE or FALSE, whether the routine is done successfully 
 * Note    :
 *--------------------------------------------------------------------------------
 */
S16_T IntFlashWrite(U32_T ProgAddr, U8_T *ptWrData, U32_T ProgLen, U8_T BootldrSel) 
{
	U8_T	LastWtst;
//	U32_T	idata i;
//	U8_T	idata PollData;
	U32_T	i;
	U8_T	PollData;

	LastWtst = WTST;
	WTST = 0x07;
	EA = 0;

	if (CSREPR & PMS) // SRAM shadow
	{
		if (BootldrSel & ERA_BLD)
		{
			CSREPR |= FAES | FARM;
			for (i = 0 ; i < 0x4000 ; i++)
			{
				FLASH_WR_ENB;
				FVAR(U8_T, 0x4000 + 0x000555) = 0xAA;
				FVAR(U8_T, 0x4000 + 0x0002AA) = 0x55;
				FVAR(U8_T, 0x4000 + 0x000555) = 0xA0;
				FVAR(U8_T, 0x4000 + i) = *(ptWrData + i);
				FLASH_WR_DISB;
				do
				{
					PollData = FCVAR(U8_T, 0x4000 + i);
				} while (PollData != *(ptWrData + i)) ;
			}
			CSREPR &= ~FARM;

			for (i = 0x4000 ; i < ProgLen ; i++)
			{
				FLASH_WR_ENB;
				CSREPR |= FARM;
				FVAR(U8_T, 0x4000 + 0x000555) = 0xAA;
				FVAR(U8_T, 0x4000 + 0x0002AA) = 0x55;
				FVAR(U8_T, 0x4000 + 0x000555) = 0xA0;
				CSREPR &= ~FARM;
				FVAR(U8_T, i) = *(ptWrData + i);
				FLASH_WR_DISB;
				do
				{
					PollData = FCVAR(U8_T, i);
				} while (PollData != *(ptWrData + i)) ;
			}
			CSREPR &= ~FAES;
		}
		else
		{
			CSREPR |= FAES;
			for (i = 0 ; i < ProgLen ; i++)
			{
				FLASH_WR_ENB;
				CSREPR |= FARM;
				FVAR(U8_T, 0x4000 + 0x000555) = 0xAA;
				FVAR(U8_T, 0x4000 + 0x0002AA) = 0x55;
				FVAR(U8_T, 0x4000 + 0x000555) = 0xA0;
				CSREPR &= ~FARM;
				FVAR(U8_T, ProgAddr + i) = *(ptWrData + i);
				FLASH_WR_DISB;
				do
				{
					PollData = FCVAR(U8_T, ProgAddr + i);
				} while (PollData != *(ptWrData + i)) ;
			}
			CSREPR &= ~FAES;
		}
	}
	else // Flash, No shadow
	{
		CSREPR &= ~FAES;

		if (BootldrSel & ERA_BLD)
		{
			CSREPR |= FARM;
			for (i = 0 ; i < 0x4000 ; i++)
			{
				FLASH_WR_ENB;
				FVAR(U8_T, 0x4000 + 0x000555) = 0xAA;
				FVAR(U8_T, 0x4000 + 0x0002AA) = 0x55;
				FVAR(U8_T, 0x4000 + 0x000555) = 0xA0;
				FVAR(U8_T, 0x4000 + i) = *(ptWrData + i);
				FLASH_WR_DISB;
				do
				{
					PollData = FCVAR(U8_T, 0x4000 + i);
				} while (PollData != *(ptWrData + i)) ;
			}
			CSREPR &= ~FARM;
			for (i = 0x4000 ; i < ProgLen ; i++)
			{
				FLASH_WR_ENB;
				CSREPR |= FARM;
				FVAR(U8_T, 0x4000 + 0x000555) = 0xAA;
				FVAR(U8_T, 0x4000 + 0x0002AA) = 0x55;
				FVAR(U8_T, 0x4000 + 0x000555) = 0xA0;
				CSREPR &= ~FARM;
				FVAR(U8_T, i) = *(ptWrData + i);
				FLASH_WR_DISB;
				do
				{
					PollData = FCVAR(U8_T, i);
				} while (PollData != *(ptWrData + i)) ;
			}
		}
		else
		{
			for (i = 0 ; i < ProgLen ; i++)
			{
				FLASH_WR_ENB;
				CSREPR |= FARM;
				FVAR(U8_T, 0x4000 + 0x000555) = 0xAA;
				FVAR(U8_T, 0x4000 + 0x0002AA) = 0x55;
				FVAR(U8_T, 0x4000 + 0x000555) = 0xA0;
				CSREPR &= ~FARM;
				FVAR(U8_T, ProgAddr + i) = *(ptWrData + i);
				FLASH_WR_DISB;
				do
				{
					PollData = FCVAR(U8_T, ProgAddr + i);
				} while (PollData != *(ptWrData + i)) ;
			}
		}
	}

	WTST = LastWtst;
	EA = 1;

	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * S16_T S16_T IntFlashErase(U8_T EraseSel,U32_T EraAddr) 
 * Purpose : Erase a flash block
 * Params  : EraseSel - select erase block. for my application, EraseSel = ERA_RUN
 *			 EraAddr  - start flash block address you want to erase
 * Returns : TRUE or FALSE, whether the routine is done successfully 
 * Note    : changed by chelsea 13th,Nov
 *--------------------------------------------------------------------------------
 */
S16_T IntFlashErase(U8_T EraseSel,U32_T EraAddr) 
{
//	U8_T	idata PollData, LastWtst;
//	U32_T	idata BaseAddr;
	U8_T	PollData, LastWtst;
	U32_T	BaseAddr;
	U32_T 	temp;
	temp = EraAddr;
	LastWtst = WTST;
	WTST = 0x07;
	EA = 0;
	BaseAddr = 0x4000;
	
	FLASH_WR_ENB;

	if (CSREPR & PMS) // SRAM shadow
		CSREPR |= FAES;
	else
		CSREPR &= ~FAES;
	
	if (EraseSel & ERA_BLD) // Erase  BootLoader
	{
		CSREPR |= FARM;
		
		FVAR(U8_T, BaseAddr + 0x000555) = 0xAA;
		FVAR(U8_T, BaseAddr + 0x0002AA) = 0x55;
		FVAR(U8_T, BaseAddr + 0x000555) = 0x80;
		FVAR(U8_T, BaseAddr + 0x000555) = 0xAA;
		FVAR(U8_T, BaseAddr + 0x0002AA) = 0x55;

		FVAR(U8_T, BaseAddr + 0x000000) = 0x30;
		
		CSREPR &= ~FARM;
	}
	else 
	{
		CSREPR |= FARM;

		FVAR(U8_T, BaseAddr + 0x000555) = 0xAA;
		FVAR(U8_T, BaseAddr + 0x0002AA) = 0x55;
		FVAR(U8_T, BaseAddr + 0x000555) = 0x80;
		FVAR(U8_T, BaseAddr + 0x000555) = 0xAA;
		FVAR(U8_T, BaseAddr + 0x0002AA) = 0x55;

		CSREPR &= ~FARM;
        if(EraseSel & ERA_CFG) // Erase configuration data
        {

			FVAR(U8_T, 0x004000) = 0x30;
        }
		else				   // Erase runtime code
		{
			/*FVAR(U8_T, 0x006000) = 0x30;
			FVAR(U8_T, 0x008000) = 0x30;
			FVAR(U8_T, 0x010000) = 0x30;
			FVAR(U8_T, 0x020000) = 0x30;
			FVAR(U8_T, 0x030000) = 0x30;
			FVAR(U8_T, 0x040000) = 0x30;
			FVAR(U8_T, 0x050000) = 0x30;
			FVAR(U8_T, 0x060000) = 0x30;
			FVAR(U8_T, 0x070000) = 0x30;*/
			FVAR(U8_T, temp) = 0x30;
		}
	}
	FLASH_WR_DISB;
    // check for completition
	if (EraseSel & ERA_BLD)
	{
		CSREPR |= FARM;
		while (1)
		{   
			PollData = FCVAR(U8_T, BaseAddr + 0x000000);
			if (PollData == 0xFF)
			{
				break;
			}
		}
		CSREPR &= ~FARM;
	}
	else
	{
		while (1)
		{
            if(EraseSel & ERA_CFG)
				PollData = FCVAR(U8_T, BaseAddr + 0x000000);
			else
				PollData = FCVAR(U8_T, temp/*BaseAddr + 0x002000*/);

			if (PollData == 0xFF)
			{
				break;
			}
		}
	}

	CSREPR &= ~FAES;

	WTST = LastWtst;
	EA = 1;

	return TRUE;
}
#endif



U8_T IntFlashReadByte(U32_T location, U8_T *value)
{

    *value = FCVAR(U8_T,location);
	
	return TRUE;

}

/*
 *--------------------------------------------------------------------------------
 * U8_T IntFlashWriteInt(U32_T location, U16_T value)
 * Purpose : write a word
 * Params  : location - flash address what you want to write 
 *			 value  - data what you want to write
 * Returns : TRUE or FALSE, whether the routine is done successfully 
 * Note    : 
 *--------------------------------------------------------------------------------
 */
U8_T IntFlashReadInt(U32_T location, U16_T *value)
{
	U8_T temp1,temp2;
	IntFlashReadByte(location + 1,&temp1);
	IntFlashReadByte(location,&temp2);
	*value = temp1 * 256 + temp2;	
	
	return TRUE;

}




U8_T IntFlashWriteByte(U32_T location,U8_T value)
{
	IntFlashWrite(location,&value,1,0);
	return TRUE;
}

U8_T IntFlashWriteInt(U32_T location,U16_T value)
{
	U8_T temp;
	temp = (U8_T)value;
	IntFlashWriteByte(location,temp);
	temp = value >> 8;
	IntFlashWriteByte(location+1,temp);
	return TRUE;
}

#if 1
void MassFlashWrite(U32_T location,U8_T *value,U32_T lenght)
{
	U16_T i;
	/*for(i = 0;i < lenght;i++)
	IntFlashWrite((U32_T)(location + FLASH_BLOCK + i),(value + i),1,0);*/
	/* after add watchdog , must short flash time*/
	for(i = 0;i < lenght;i++)
	IntFlashWrite((U32_T)(location + FLASH_BLOCK + i),(value + i),1,0);
	//IntFlashWrite((U32_T)(location + FLASH_BLOCK),value,lenght,0);
}


void ISPMassFlashWrite(U32_T location,U8_T *value,U32_T lenght)
{
	U16_T i;
	for(i = 0;i < lenght;i++)
	IntFlashWrite((U32_T)(location + FLASH_BLOCK + i),(value + i),1,0);
	/* after add watchdog , must short flash time*/
	//IntFlashWrite((U32_T)(location +0x60000),value,lenght,0);
}

#endif


/* LOCAL SUBPROGRAM BODIES */


/* EXPORTED SUBPROGRAM BODIES */

/*
 * ----------------------------------------------------------------------------
 * void FirmwareUpdate(void)
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void FirmwareUpdate(void)
{
	fwAutoUpdated[0] = 'a';
	fwAutoUpdated[1] = 's';
	fwAutoUpdated[2] = 'i';
	fwAutoUpdated[3] = 'x';
	AX11000_SoftReboot();
}
