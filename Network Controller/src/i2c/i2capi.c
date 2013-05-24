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
 * Module Name : i2capi.c
 * Purpose     : API functions invovle I2C driver functions.
 *               To transmit and to reveive packet by these functions.
 * Author      : Robin Lee
 * Date        : 2006-01-10
 * Notes       :
 * $Log: i2capi.c,v $
 * Revision 1.1  2006/04/07 11:38:34  robin6633
 * no message
 *
 *================================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include	<stdio.h>
#include	"reg80390.h"
#include	"types.h"
#include	"buffer.h"
#include	"i2c.h"
#include	"i2capi.h"


/* STATIC VARIABLE DECLARATIONS */


/* LOCAL SUBPROGRAM DECLARATIONS */


/* LOCAL SUBPROGRAM BODIES */


/* EXPORTED SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * BOOL I2C_ByteWrite(U16_T addrOfDev, U16_T addrOfMem, U8_T byteData, U8_T endCond)
 * Purpose : i2c master send a packet for write one data to a device
 * Params  : addrOfDev : id address of a device
 *           addrOfMem : address for accessing in a device
 *           byteData  : data for writing
 *           endCond   : packet condition after transmitting
 * Returns : TRUE : this accessing is successful
 *           FALSE: this accessing is failed
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL I2C_ByteWrite(U16_T addrOfDev, U16_T addrOfMem, U8_T byteData, U8_T endCond)
{
	I2C_BUF		*ptTxPkt = NULL;
	U8_T		addrMode = 0;

	/* Get buffer of this packet */
	ptTxPkt = (I2C_BUF *)GetPktBuf();
	/* The end condition after transfer complete */
	ptTxPkt->I2cEnd = endCond;
	/* Indicate the packet's direction to master transmit */
	ptTxPkt->I2cDir = I2C_MST_XMIT;
	/* Data length exclude device address */
	ptTxPkt->DataLen = 0x02;

	/* Device Address with 10-bit or 7-bit */
	I2C_Cmd(SI_RD, I2CCTL, &addrMode);
	if (addrMode & I2C_10BIT)
	{
		ptTxPkt->I2cAddr.TenBitAddr = (U16_T)(addrOfDev | ((addrOfMem & 0x0700) >> 8));
	}
	else
	{
		ptTxPkt->I2cAddr.SevenBitAddr = (U8_T)(addrOfDev | ((addrOfMem & 0x0700) >> 8));
	}
	/* Register word Address */
	ptTxPkt->I2cData[0] = (U8_T)(addrOfMem & 0x00FF);
	/* Access Data */
	ptTxPkt->I2cData[1] = byteData;

	/* To send packet and i2c bus will be busy for this transfer */
	I2C_FlagEnb(I2C_BUSY);
	I2C_PktBuf(ptTxPkt);
	/* Waiting for transfer completely */
	while (I2C_FlagChk(I2C_BUSY)) {}
	/* If the packet does not have any ACK echoed, this transfer fail */
	if (I2C_FlagChk(I2C_NACK))
	{
		I2C_FlagClr(I2C_NACK);
		return FALSE;
	}

	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL I2C_PageWrite(U16_T addrOfDev, U16_T addrOfMem, U8_T*ptPageData, U16_T writeLen, U8_T endCond)
 * Purpose : i2c master send a packet for writing more data to a device
 * Params  : addrOfDev : id address of a device
 *           addrOfMem : address for accessing in a device
 *           ptPageData: data string for writing
 *           writeLen  : data length for transmitting include addrOfMem and data string
 *           endCond   : packet condition after transmitting
 * Returns : TRUE : this accessing is successful
 *           FALSE: this accessing is failed
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL I2C_PageWrite(U16_T addrOfDev, U16_T addrOfMem, U8_T *ptPageData, U16_T writeLen, U8_T endCond)
{
	
	I2C_BUF XDATA	*ptTxPkt = NULL;
	U16_T			i;
	U8_T XDATA		addrMode = 0;
	
	/* Get buffer of this packet */
	ptTxPkt = (I2C_BUF *)GetPktBuf();
	/* The end condition after transfer complete */
	ptTxPkt->I2cEnd = endCond;
	/* Indicate the packet's direction to master transmit */
	ptTxPkt->I2cDir = I2C_MST_XMIT;
	/* Data length exclude device address */
	ptTxPkt->DataLen = writeLen + 1;
	/* Device Address with 10-bit or 7-bit */
	I2C_Cmd(SI_RD, I2CCTL, &addrMode);
	if (addrMode & I2C_10BIT)
	{
		ptTxPkt->I2cAddr.TenBitAddr = (U16_T)(addrOfDev | ((addrOfMem & 0x0700) >> 8));
	}
	else
	{
		ptTxPkt->I2cAddr.SevenBitAddr = (U8_T)(addrOfDev | ((addrOfMem & 0x0700) >> 8));
	}
	/* Register word Address */
	ptTxPkt->I2cData[0] = (U8_T)(addrOfMem & 0x00FF);
	/* Access Data */
	for (i = 0 ; i < writeLen ; i ++)
	{
		ptTxPkt->I2cData[i + 1] = *(ptPageData + i);
	}
	/* To send packet and i2c bus will be busy for this transfer */
	I2C_FlagEnb(I2C_BUSY);
	I2C_PktBuf(ptTxPkt);
	/* Waiting for transfer completely */
	while (I2C_FlagChk(I2C_BUSY)) {}
	/* If the packet does not have any ACK echoed, this transfer fail */
	if (I2C_FlagChk(I2C_NACK))
	{
		I2C_FlagClr(I2C_NACK);
		return FALSE;
	}

	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL I2C_RdmRead(U16_T addrOfDev, U16_T addrOfMem ,I2C_BUF *ptPktTemp, U16_T readLen, U8_T endCond)
 * Purpose : i2c master send a packet for reading data from a device
 * Params  : addrOfDev : id address of a device
 *           addrOfMem : address for accessing in a device
 *           ptPktTemp : read data buffer pointer
 *           readLen   : data length for reading
 *           endCond   : packet condition after transfer
 * Returns : TRUE : this accessing is successful
 *           FALSE: this accessing is failed
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL I2C_RdmRead(U16_T addrOfDev, U16_T addrOfMem ,I2C_BUF *ptPktTemp, U16_T readLen, U8_T endCond)
{
	I2C_BUF		*ptRxPkt = NULL;
	U16_T		i;
	U8_T		addrMode = 0;

	/* Get buffer of this packet */
	ptRxPkt = (I2C_BUF *)GetPktBuf();
	/* The end condition after transfer complete */
	ptRxPkt->I2cEnd = I2C_STOP_COND;
	/* Indicate the packet's direction to master receive */
	ptRxPkt->I2cDir = I2C_MST_RCVR;
	/* Data length exclude device address */
	ptRxPkt->DataLen = readLen;
	/* Device Address with 10-bit or 7-bit */
	I2C_Cmd(SI_RD, I2CCTL, &addrMode);
	if (addrMode & I2C_10BIT)
	{
		ptRxPkt->I2cAddr.TenBitAddr = (U16_T)(addrOfDev | ((addrOfMem & 0x0700) >> 8));
	}
	else
	{
		ptRxPkt->I2cAddr.SevenBitAddr = (U8_T)(addrOfDev | ((addrOfMem & 0x0700) >> 8));
	}
	/* Send a dummy packet to indicate the internal address of devices */
	if (endCond & I2C_STOP_COND)
	{
		if (I2C_DummyWrite(addrOfDev, addrOfMem, I2C_STOP_COND))
		{
			/* To send packet and i2c bus will be busy for this transfer */
			I2C_FlagEnb(I2C_BUSY);
			I2C_PktBuf(ptRxPkt);
			/* Waiting for transfer completely */
			while (I2C_FlagChk(I2C_BUSY)) {}
			/* If the packet does not have any ACK echoed, this transfer fail */
			if (I2C_FlagChk(I2C_NACK))
			{
				I2C_FlagClr(I2C_NACK);
				return FALSE;
			}
			/* Get data received in this transfer */
			for (i=0 ; i<=readLen ; i++)
			{
				ptPktTemp->I2cData[i] = ptRxPkt->I2cData[i+1];
			}
			return TRUE;
		}
		else
			return FALSE;
	}
	else
	{
		if (I2C_DummyWrite(addrOfDev, addrOfMem, endCond))
		{
			/* To check the packet has a restart condition for next access */
			while (!I2C_FlagChk(I2C_RESTART)) {}
			/* To send packet and i2c bus will be busy for this transfer */
			I2C_FlagClr(I2C_RESTART);
			I2C_FlagEnb(I2C_BUSY);
			I2C_PktBuf(ptRxPkt);
			/* Waiting for transfer completely */
			while (I2C_FlagChk(I2C_BUSY)) {}
			/* If the packet does not have any ACK echoed, this transfer fail */
			if (I2C_FlagChk(I2C_NACK))
			{
				I2C_FlagClr(I2C_NACK);
				return FALSE;
			}
			/* Get data received in this transfer */
			for (i=0 ; i<=readLen ; i++)
			{
				ptPktTemp->I2cData[i] = ptRxPkt->I2cData[i];
			}
			return TRUE;
		}
		else
			return FALSE;
	}
}

/*
 *--------------------------------------------------------------------------------
 * BOOL I2C_DummyWrite(U16_T addrOfDev, U16_T addrOfMem, U8_T endCond)
 * Purpose : i2c master send a dummy packet for accessing a device
 * Params  : addrOfDev : id address of a device
 *           addrOfMem : address for accessing in a device
 *           endCond   : packet condition after transmitting
 * Returns : TRUE : this accessing is successful
 *           FALSE: this accessing is failed
 * Note    : this function only transmit the address of accessing,
 *           it does not have any data
 *--------------------------------------------------------------------------------
 */
BOOL I2C_DummyWrite(U16_T addrOfDev, U16_T addrOfMem, U8_T endCond)
{
	I2C_BUF		*ptTxPkt = NULL;
	U8_T		addrMode = 0;

	/* Get buffer of this packet */
	ptTxPkt = (I2C_BUF *)GetPktBuf();
	/* The end condition after transfer complete */
	ptTxPkt->I2cEnd = endCond;
	/* Indicate the packet's direction to master transmit */
	ptTxPkt->I2cDir = I2C_MST_XMIT;
	/* Data length exclude device address */
	ptTxPkt->DataLen = 0x01;
	/* Device Address with 10-bit or 7-bit */
	I2C_Cmd(SI_RD, I2CCTL, &addrMode);
	if (addrMode & I2C_10BIT)
	{
		ptTxPkt->I2cAddr.TenBitAddr = (U16_T)(addrOfDev | ((addrOfMem & 0x0700) >> 8));
	}
	else
	{
		ptTxPkt->I2cAddr.SevenBitAddr = (U8_T)(addrOfDev | ((addrOfMem & 0x0700) >> 8));
	}
	/* Register word Address */
	ptTxPkt->I2cData[0] = (U8_T)(addrOfMem & 0x00FF);
	/* No Access Data */
	/* To send packet and i2c bus will be busy for this transfer */
	I2C_FlagEnb(I2C_BUSY);
	I2C_FlagClr(I2C_RESTART);
	I2C_PktBuf(ptTxPkt);
	/* Waiting for transfer completely */
	while (I2C_FlagChk(I2C_BUSY)) {}
	/* If the packet does not have any ACK echoed, this transfer fail */
	if (I2C_FlagChk(I2C_NACK))
	{
		I2C_FlagClr(I2C_NACK);
		return FALSE;
	}

	return TRUE;
}


/* End of i2capi.c */
