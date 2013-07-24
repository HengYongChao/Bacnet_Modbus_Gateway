/*
 *********************************************************************************
 *     Copyright (c) 2005	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 *********************************************************************************
 */
/*================================================================================
 * Module Name : spiapi.c
 * Purpose     : API functions provide user to send and receive packet.
 *               These API functions invovle SPI driver to accomplish
 *               a packet transfer.
 * Author      : Robin Lee
 * Date        : 2006-01-11
 * Notes       :
 * $Log: spiapi.c,v $
 * Revision 1.1  2006/04/07 11:39:02  robin6633
 * no message
 *
 *================================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include	"reg80390.h"
#include	"types.h"
#include	"spi.h"
#include	"spiapi.h"
#include "delay.h"
#include "printd.h"


/* STATIC VARIABLE DECLARATIONS */


/* LOCAL SUBPROGRAM DECLARATIONS */


/* LOCAL SUBPROGRAM BODIES */


/* EXPORTED SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * BOOL SPI_WriteEnable(void)
 * Purpose : Enable a write process before sending a packet to write.
 * Params  : none
 * Returns : TRUE - successful
 * Note    : Write Enable must be initial when executing all write function.
 *--------------------------------------------------------------------------------
 */
BOOL SPI_WriteEnable(void)
{
	U8_T	xmitByte = 0;
	
	xmitByte = SPI_WREN;
	SPI_FlagEnb(SPI_BUSY);
	SPI_MstXmit(&xmitByte, 8, SPI_NORMAL_LEN|SPI_GO_BSY);

	while (SPI_FlagChk(SPI_BUSY)) {}

	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL SPI_WriteDisable(void)
 * Purpose : Disable a write process.
 * Params  : none
 * Returns : TRUE - successful
 * Note    : After WriteDisable executed, all writing function will be fail.
 *--------------------------------------------------------------------------------
 */
BOOL SPI_WriteDisable(void)
{
	U8_T	xmitByte = 0;
	
	xmitByte = SPI_WRDI;
	SPI_FlagEnb(SPI_BUSY);
	SPI_MstXmit(&xmitByte, 8, SPI_NORMAL_LEN|SPI_GO_BSY);

	while (SPI_FlagChk(SPI_BUSY)) {}

	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL SPI_WriteStatus(U8_T status)
 * Purpose : Change a device status register.
 * Params  : status - changed value.
 * Returns : TRUE - successful.
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL SPI_WriteStatus(U8_T status)
{
	U8_T	writeStatus[2];
	
	writeStatus[1] = SPI_WRSR;
	writeStatus[0] = status;

	if (!SPI_WriteEnable())
		return FALSE;
	SPI_FlagEnb(SPI_BUSY);
	SPI_MstXmit(&writeStatus, 16, SPI_NORMAL_LEN|SPI_GO_BSY);
	while (SPI_FlagChk(SPI_BUSY)) {}
	
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL SPI_ReadStatus(U8_T *status)
 * Purpose : Read a device status register.
 * Params  : *status - a pointer of status value.
 * Returns : TRUE - successful
 * Note    : 
 *--------------------------------------------------------------------------------
 */
BOOL SPI_ReadStatus(U8_T *status)
{
	U8_T	readStatus[2];
	
	readStatus[1] = SPI_RDSR;
	readStatus[0] = 0;
	
	SPI_FlagEnb(SPI_BUSY);
	SPI_MstXmit(&readStatus, 16, SPI_NORMAL_LEN|SPI_GO_BSY);

	while (SPI_FlagChk(SPI_BUSY)) {}
	SPI_GetData(&readStatus);
	*status = readStatus[0];
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL SPI_ByteWrite(U16_T addrOfMem, U8_T byteData)
 * Purpose : Write one byte data into spi devices.
 * Params  : addrOfMem - address of accessing.
 *           byteData - data to be written.
 * Returns : TRUE - successful.
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL SPI_ByteWrite(U16_T addrOfMem, U8_T byteData)
{
	U8_T	byteWrite[4];
	U8_T	status = 0;
	
	byteWrite[3] = SPI_WRITE;
	byteWrite[2] = (U8_T)(addrOfMem >> 8);
	byteWrite[1] = (U8_T)(addrOfMem);
	byteWrite[0] = byteData;

	if (!SPI_WriteEnable())
	{
		return FALSE;
	}
	do
	{
		SPI_ReadStatus(&status);
	} while (status & SPI_WIP);
	SPI_FlagEnb(SPI_BUSY);
	SPI_MstXmit(&byteWrite, 32, SPI_NORMAL_LEN|SPI_GO_BSY);
	while (SPI_FlagChk(SPI_BUSY)) {}
	
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL SPI_PageWrite(U16_T addrOfMem, U8_T *ptByteData, U16_T wrLen)
 * Purpose : Write a data string into spi devices.
 * Params  : addrOfMem - address of accessing.
 *           *ptByteData - pointer of data string to be written.
 *           wrLen - write data length.
 * Returns : TRUE - successful.
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL SPI_PageWrite(U16_T addrOfMem, U8_T *ptByteData, U16_T wrLen)
{
	U8_T		pageWrite[35];
	U8_T		status = 0;
	U16_T		i;
	
	pageWrite[2] = SPI_WRITE;
	pageWrite[1] = (U8_T)(addrOfMem >> 8);
	pageWrite[0] = (U8_T)(addrOfMem);
	for (i=0 ; i<wrLen ; i++)
	{
		pageWrite[3+i] = *(ptByteData+i);
	}

	if (!SPI_WriteEnable())
		return FALSE;
	do
	{
		SPI_ReadStatus(&status);
	}
	while (status & SPI_WIP) ;
	SPI_FlagEnb(SPI_BUSY);
	SPI_MstXmit(&pageWrite[0], 24, SPI_LONG_LEN|SPI_GO_BSY);

	while (SPI_FlagChk(SPI_BUSY)) {}

	for (i=0 ; i<wrLen ; i++)
	{
		SPI_FlagEnb(SPI_BUSY);
		if (i == (wrLen-1))
			SPI_MstXmit(&pageWrite[3+i], 8, SPI_NORMAL_LEN|SPI_GO_BSY);
		else
			SPI_MstXmit(&pageWrite[3+i], 8, SPI_LONG_LEN|SPI_GO_BSY);
		while (SPI_FlagChk(SPI_BUSY)) {}
	}

	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL SPI_ByteRead(U16_T addrOfMem, U8_T *ptByteData)
 * Purpose : Read one byte data from spi devices.
 * Params  : addrOfMem - address of accessing.
 *           *ptByteData - pointer of data which be read.
 * Returns : TRUE - successful.
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL SPI_ByteRead(U16_T addrOfMem, U8_T *ptByteData)
{
	U8_T	byteRead[4];
	U8_T	status = 0;
	
	byteRead[3] = SPI_READ;
	byteRead[2] = (U8_T)(addrOfMem >> 8);
	byteRead[1] = (U8_T)(addrOfMem);
	byteRead[0] = *ptByteData;

	do
	{
		SPI_ReadStatus(&status);
	} while (status & SPI_WIP) ;
	SPI_FlagEnb(SPI_BUSY);
	SPI_MstXmit(&byteRead[0], 32, SPI_NORMAL_LEN|SPI_GO_BSY);
	while (SPI_FlagChk(SPI_BUSY)) {}
	SPI_GetData(&byteRead);
	*ptByteData = byteRead[0];

	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL MCP25C320_PageRead(U16_T addrOfMem, U8_T *ptByteData, U16_T rdLen)
 * Purpose : read a data string from spi devices.
 * Params  : addrOfMem - address of accessing.
 *           *ptByteData - pointer of data string which be read.
 *           rdLen - read data length.
 * Returns : TRUE - successful.
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL SPI_PageRead(U16_T addrOfMem, U8_T *ptByteData, U16_T rdLen)
{
	U8_T	pageRead[4], temp[4];
	U8_T	status = 0;
	U16_T	i;
	
	temp[0] = 0;
	temp[1] = 0;
	temp[2] = 0;
	temp[3] = 0;
	pageRead[3] = 0;
	pageRead[2] = SPI_READ;
	pageRead[1] = (U8_T)(addrOfMem >> 8);
	pageRead[0] = (U8_T)(addrOfMem);

	do
	{
		SPI_ReadStatus(&status);
	}
	while (status & SPI_WIP) ;
	SPI_FlagEnb(SPI_BUSY);
	SPI_MstXmit(&pageRead[0], 24, SPI_LONG_LEN|SPI_GO_BSY);
	
	while (SPI_FlagChk(SPI_BUSY)) {}

	for (i=0 ; i<rdLen ; i++)
	{
		SPI_FlagEnb(SPI_BUSY);
		if (i==rdLen-1)
			SPI_MstXmit(&pageRead[3], 8, SPI_NORMAL_LEN|SPI_GO_BSY);
		else
			SPI_MstXmit(&pageRead[3], 8, SPI_LONG_LEN|SPI_GO_BSY);
		while (SPI_FlagChk(SPI_BUSY)) {}
		SPI_GetData(&temp);
		*(ptByteData + i) = temp[0];
	}
	
	return TRUE;
	
}




 
/* End of spiapi.c */
