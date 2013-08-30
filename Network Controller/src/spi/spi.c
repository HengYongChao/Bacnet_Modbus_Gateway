/*
 *********************************************************************************
 *     Copyright (c) 2005   ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 *********************************************************************************
 */
/*================================================================================
 * Module Name : spi.c
 * Purpose     : This file handles the SPI serial interface driver.
 *               It includes transmitting and receiving functions of master mode
 *               and slave mode.
 * Author      : Robin Lee
 * Date        : 2006-01-11
 * Notes       :
 * $Log: spi.c,v $
 * Revision 1.1  2006/04/07 11:39:02  robin6633
 * no message
 *
 *================================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include	"reg80390.h"
#include	"types.h"
#include	"spi.h"

#if SPI_SLAVE_ENABLE
 #include	"ax11000slv.h"
#endif


/* STATIC VARIABLE DECLARATIONS */
static U8_T		spiActF = 0;
static U8_T		spiCtrl = 0;
static U8_T		spiPktDir = 0;
static U8_T		spiPktLen = 0;
static U16_T	spiLenCnt = 0;
static U16_T	spiTransLoop = 0;
static U16_T	spiTransLoopCnt = 0;
static U8_T		spiRxBuf[4] = {0,0,0,0};
static U8_T		spiSlvTxBuf[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static U8_T		spiSlvRxBuf[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


/* LOCAL SUBPROGRAM DECLARATIONS */
static void	spi_MstRcvr(void);
static void spi_SlvRcvr(void);

#if SPI_SLAVE_ENABLE
static void spi_SlvProcess(void);
#endif


/* LOCAL SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * static void spi_MstRcvr(void)
 * Purpose : SPI master gets data from receiving register in one transfer.
 * Params  : None.
 * Returns : None.
 * Note    : The receiving register has a size of 4 bytes.
 *--------------------------------------------------------------------------------
 */	
 
static void spi_MstRcvr(void)
{
	U8_T	i;

	SPICIR = SPIRBR;
    for (i = 0 ; i < 4; i++ )
	{
		spiRxBuf[i] = SPIDR;
	}	
}
		  
 /*
static void spi_MRcvr(U8_T *spiRxPkt, U8_T xmitBit)
{
	U8_T	i;

	SPICIR = SPIRBR;
	for (i = 0 ; i <= (xmitBit-1)/8 ; i++ )
	{
		*(spiRxPkt+i) = SPIDR;
	}
}
*/

/*
 *--------------------------------------------------------------------------------
 * static void spi_SlvRcvr(void)
 * Purpose : SPI slave receiving function in one transfer.It will get the packet
 *           from slave buffer register and stores into a software buffer.
 * Params  : None.
 * Returns : None.
 * Note    : The slave buffer register has a size of 16 bytes.
 *--------------------------------------------------------------------------------
 */
#if SPI_SLAVE_ENABLE
static void spi_SlvRcvr(void)
{
	U8_T	i;
	U8_T	rxLen = 0;
	U8_T	slvCmdType = 0;
	U8_T	dataLen = 0;

	SPICIR = SPISB;
	spiSlvRxBuf[0] = SPIDR;
	slvCmdType = spiSlvRxBuf[0] & 0xF0;
	dataLen = (spiSlvRxBuf[0] & 0x0F) + 1;
	if (slvCmdType == SPI_SLV_SRSFR)
	{
		rxLen = 1;
	}
	else if (slvCmdType == SPI_SLV_SWSFR)
	{
		rxLen = dataLen + 1;
	}
	else if (slvCmdType == SPI_SLV_IRSFR)
	{
		rxLen = 2;
	}
	else if (slvCmdType == SPI_SLV_IWSFR)
	{
		rxLen = dataLen + 2;
	}
	else if (slvCmdType == SPI_SLV_BRMEM)
	{
		rxLen = 3;
	}
	else if (slvCmdType == SPI_SLV_BWMEM)
	{
		rxLen = dataLen + 3;
	}
	for (i = 0 ; i < rxLen ; i ++ )
	{
		spiSlvRxBuf[1+i] = SPIDR;
	}
	/* Command abort*/
	SPICIR = 0xFF;
}
#endif

/*
 *--------------------------------------------------------------------------------
 * static void spi_SlvProcess(void)
 * Purpose : SPI slave function which is responsible to transmit and receive
 *           packets. It will call a specific function corresponding with 
 *           received packets.
 * Params  : None.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
#if SPI_SLAVE_ENABLE
static void spi_SlvProcess(void)
{
	U8_T	slvCmdType = 0;
	U8_T	sfrAddr = 0;
	U8_T	cmdIndReg = 0;
	U8_T	realReg = 0;
	U8_T	realLen = 0;
	U32_T	memAddr = 0;
	U8_T	tempData = 0;
	U16_T	i;

	slvCmdType = spiSlvRxBuf[0] & 0xF0;
	if (slvCmdType == SPI_SLV_SRSFR)
	{
		realLen = (spiSlvRxBuf[0] & 0x07) + 1;
		sfrAddr = spiSlvRxBuf[1];
		for (i=0 ; i<realLen ; i++)
		{
			AX11000SLV_SfrRd((U8_T)sfrAddr, &tempData);
			spiSlvTxBuf[i] = (U8_T)tempData;
		}
		SPI_SlvXmit(SPI_SLV_RDY);
	}
	else if (slvCmdType == SPI_SLV_SWSFR)
	{
		realLen = (spiSlvRxBuf[0] & 0x07) + 1;
		sfrAddr = spiSlvRxBuf[1];
		for (i=0 ; i<realLen ; i++)
		{
			tempData = (U32_T)spiSlvRxBuf[2+i];
			AX11000SLV_SfrWr((U8_T)sfrAddr, tempData);
		}
		SPI_SlvXmit(SPI_SLV_RDY);
	}
	else if (slvCmdType  == SPI_SLV_IRSFR)
	{
		cmdIndReg = spiSlvRxBuf[1];
		realReg = spiSlvRxBuf[2];
		realLen = (spiSlvRxBuf[0] & 0x0F) + 1;
		if (cmdIndReg == SFR_SPICIR)
		{
			AX11000SLV_SpiRd((U8_T)realReg, &spiSlvTxBuf[0], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_I2CCIR)
		{
			AX11000SLV_I2cRd((U8_T)realReg, &spiSlvTxBuf[0], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_OWCIR)
		{
			AX11000SLV_OwRd((U8_T)realReg, &spiSlvTxBuf[0], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_CANCIR)
		{
			AX11000SLV_CanRd((U8_T)realReg, &spiSlvTxBuf[0], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_TCIR)
		{
			AX11000SLV_ToeRd((U8_T)realReg, &spiSlvTxBuf[0], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_MCIR)
		{
			AX11000SLV_MacRd((U8_T)realReg, &spiSlvTxBuf[0], (U8_T)realLen);
		}
		SPI_SlvXmit(SPI_SLV_RDY);
	}
	else if (slvCmdType  == SPI_SLV_IWSFR)
	{
		cmdIndReg = spiSlvRxBuf[1];
		realReg = spiSlvRxBuf[2];
		realLen = (spiSlvRxBuf[0] & 0x0F) + 1;
		if (cmdIndReg == SFR_SPICIR)
		{
			AX11000SLV_SpiWr((U8_T)realReg, &spiSlvRxBuf[3], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_I2CCIR)
		{
			AX11000SLV_I2cWr((U8_T)realReg, &spiSlvRxBuf[3], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_OWCIR)
		{
			AX11000SLV_OwWr((U8_T)realReg, &spiSlvRxBuf[3], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_CANCIR)
		{
			AX11000SLV_CanWr((U8_T)realReg, &spiSlvRxBuf[3], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_TCIR)
		{
			AX11000SLV_ToeWr((U8_T)realReg, &spiSlvRxBuf[3], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_MCIR)
		{
			AX11000SLV_MacWr((U8_T)realReg, &spiSlvRxBuf[3], (U8_T)realLen);
		}
		SPI_SlvXmit(SPI_SLV_RDY);
	}
	else if (slvCmdType  == SPI_SLV_BRMEM)
	{
		memAddr = ((U32_T)spiSlvRxBuf[3] << 16) | ((U32_T)spiSlvRxBuf[2] << 8) | ((U32_T)spiSlvRxBuf[1]);
		realLen = (spiSlvRxBuf[0] & 0x0F) + 1;
		for (i = 0 ; i < realLen ; i ++)
		{
			AX11000SLV_ExtMemRd((memAddr + i), &tempData);
			spiSlvTxBuf[i] = (U8_T)tempData;
		}
		SPI_SlvXmit(SPI_SLV_RDY);
	}
	else if (slvCmdType  == SPI_SLV_BWMEM)
	{
#if 0
		realLen = (spiSlvRxBuf[0] & 0x0F) + 1 + 3;
		AUDIO_Rcv((U8_T *)&spiSlvRxBuf[1], (U8_T)realLen);
		SPI_SlvXmit(SPI_SLV_RDY);
#else
	memAddr = ((U32_T)spiSlvRxBuf[3] << 16) | ((U32_T)spiSlvRxBuf[2] << 8) | ((U32_T)spiSlvRxBuf[1]);
		realLen = (spiSlvRxBuf[0] & 0x0F) + 1;
		for (i = 0 ; i < realLen ; i ++)
		{
			tempData = (U32_T)spiSlvRxBuf[4 + i];
			AX11000SLV_ExtMemWr((memAddr + i), tempData);
		}
		SPI_SlvXmit(SPI_SLV_RDY);
#endif
	}
}
#endif

/* EXPORTED SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * void SPI_Setup(U8_T ctrlCmd, U8_T intrEnb, U8_T baudrate, U8_T slvSel)
 * Purpose : Setup the SPI module and initiate SPI function.
 * Params  : ctrlCmd - control register value.
 *           intrEnb - interrupt source enabled bit.
 *           baudrate - a parameterto generate baudrate.
 *           slvSel - slave selection bit.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */


void SPI_CS_SET(void)
{
    U8_T XDATA ss0=0xff;
	P3 = 0xFF;
	SPI_Cmd(SI_WR, SPISSR, &ss0);	

}

void SPI_CS_CLR(void)
{
	 U8_T XDATA ss0=0xfe;
     P3 = 0xFE;
	SPI_Cmd(SI_WR, SPISSR, &ss0);	
}


/* EXPORTED SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * void SPI_Setup(U8_T ctrlCmd, U8_T intrEnb, U8_T baudrate, U8_T slvSel)
 * Purpose : Setup the SPI module and initiate SPI function.
 * Params  : ctrlCmd - control register value.
 *           intrEnb - interrupt source enabled bit.
 *           baudrate - a parameterto generate baudrate.
 *           slvSel - slave selection bit.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
void SPI_Setup(U8_T ctrlCmd, U8_T intrEnb, U8_T baudrate, U8_T slvSel)
{
	U8_T	spiSlvCmd = 0;
	U16_T	i;

	spiActF = 0;
	spiCtrl = 0;
	spiPktDir = 0;
	spiPktLen = 0;
	spiLenCnt = 0;
	spiTransLoop = 0;
	spiTransLoopCnt = 0;
	for (i=0 ; i<4 ; i++) 
		spiRxBuf[i]= 0;	
	for (i=0 ; i<16 ; i++)
	{
		spiSlvTxBuf[i] = 0;
		spiSlvRxBuf[i] = 0;
	}

	/* Record the SPI control mode */
	spiCtrl = intrEnb;
	/* Setup SPI mode */
	SPI_Cmd(SI_WR, SPICTRLR, &ctrlCmd);
	/* Enable intertupe flag type of SPI */
	SPI_Cmd(SI_WR, SPIIER, &intrEnb);
	/* SPI baud rate selection */
	SPI_Cmd(SI_WR, SPIBRR, &baudrate);
	/* SPI slave select */
	SPI_Cmd(SI_WR, SPISSR, &slvSel);
	/* SPI slave is ready to receive */
//	spiSlvCmd = SPI_SLV_RDY;
//	SPI_Cmd(SI_WR, SPISCR, &spiSlvCmd);
}

/*
 *--------------------------------------------------------------------------------
 * void SPI_Func(void)
 * Purpose : Handling SPI interrupt function. It will check interrupt status of
 *           master and slave. And receiving packets first.
 * Params  : None.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
void SPI_Func(void)
{
	U8_T	spiStatus = 0;

	/* Take down the interrupt type */

	EA = 0;
	SPI_Cmd(SI_RD, SPIISR, &spiStatus);
	EA = 1;

	if ((spiCtrl & SPI_STCFIE) || (spiCtrl & SPI_SRCFIE))
	{
		/* Read SPI interrupt status register */
		if (spiStatus & SPI_MCF) // when master complete a transfer
		{
			spi_MstRcvr();
			SPI_FlagClr(SPI_BUSY);
		}

		#if SPI_SLAVE_ENABLE
		else if (spiStatus & SPI_SCF) // when slave complete a transfer
		{
			spi_SlvRcvr();
			spi_SlvProcess();
		}
		#endif
	}
	else
	{
		if (spiStatus & SPI_MCF) // when master complete a transfer
		{
			spi_MstRcvr();
			SPI_FlagClr(SPI_BUSY);
		}
		#if SPI_SLAVE_ENABLE
		else if (spiStatus & SPI_SCF) // when slave complete a transfer
		{
			spi_SlvRcvr();
			spi_SlvProcess();
		}
		#endif
	}
}

/*
 *--------------------------------------------------------------------------------
 * void SPI_MstXmit(U8_T *ptSpiTxPkt, U8_T xmitBit, U8_T cmd)
 * Purpose : SPI master transmit function in one transfer smaller than 32 bits.
 * Params  : ptSpiTxPkt - a pointer of transmitting data.
 *           xmitBit - a number of transmit bit.
 *           cmd - transfer condition in this transfer.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
void SPI_MstXmit(U8_T *ptSpiTxPkt, U8_T xmitBit, U8_T cmd)
{
	U16_T	i;
	U8_T	xmitCmd = 0;
	
	for (i = 0 ; i <= (xmitBit-1)/8 ; i++ )
	{
		SPIDR = *(ptSpiTxPkt + i);
	}
	SPICIR = SPITBR;
	/* order command */
	xmitCmd = ((xmitBit - 1)|cmd);
	SPI_Cmd(SI_WR, SPICMDR, &xmitCmd);	
}

/*
 *--------------------------------------------------------------------------------
 * void SPI_SlvXmit(U8_T spiSlvCmd)
 * Purpose : SPI slave transmit function. It puts data from software TX buffer to
 *           hardware slave buffer register.
 * Params  : spiSlvCmd - ready bit to transmit.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
void SPI_SlvXmit(U8_T spiSlvCmd)
{
	U16_T	i;

	for (i = 0 ; i <16 ; i++ )
	{
		SPIDR = spiSlvTxBuf[i];
	}
	SPICIR = SPISB;
	/* order command */
	SPI_Cmd(SI_WR, SPISCR, &spiSlvCmd);
}

/*
 *--------------------------------------------------------------------------------
 * BOOL SPI_FlagChk(U8_T chkBit)
 * Purpose : Checking the current state in this driver.
 * Params  : chkBit - a state bit to be checked.
 * Returns : TRUE - the current state meets the chkBit. Or FALSE.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
BOOL SPI_FlagChk(U8_T chkBit)
{
	if (spiActF & chkBit)
		return TRUE;
	return FALSE;
}

/*
 *--------------------------------------------------------------------------------
 * void SPI_FlagEnb(U8_T enbBit)
 * Purpose : Setting a state bit in this driver for state machine.
 * Params  : enbBit - a state bit to be turned on.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
void SPI_FlagEnb(U8_T enbBit)
{
	spiActF = spiActF | enbBit;
}

/*
 *--------------------------------------------------------------------------------
 * void SPI_FlagClr(U8_T clrBit)
 * Purpose : Clearing a state bit in this driver for state machine.
 * Params  : clrBit - a state bit to be cleared.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
void SPI_FlagClr(U8_T clrBit)
{
	spiActF = spiActF & ~clrBit;
}

/*
 *--------------------------------------------------------------------------------
 * void SPI_GetData(U8_T *ptBuf)
 * Purpose : Getting data which be stored in software RX buffer.
 * Params  : ptBuf - a pointer to store data.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
void SPI_GetData(U8_T *ptBuf)
{
//	U8_T	i;

	*ptBuf = spiRxBuf[0];
/*
	for (i=0 ; i<4 ; i++)
	{
		*(ptBuf + i) = spiRxBuf[i];
	} */
}

/*
 *--------------------------------------------------------------------------------
 * void SPI_Cmd(U8_T cmdType, U8_T spiCmdIndex, U8_T *spiData)
 * Purpose : Accessing the SPI interface indirectly through SPI's SFR.
 * Params  : cmdType - command type of writing or reading.
 *           spiCmdIndex - SPI register address.
 *           *spiData - a pointer store the data.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
void SPI_Cmd(U8_T cmdType, U8_T spiCmdIndex, U8_T *spiData)
{
	if (cmdType == SI_WR)
	{
		SPIDR = *spiData;
		SPICIR = spiCmdIndex;
	}
	else if (cmdType == SI_RD)
	{
		SPICIR = spiCmdIndex;
		*spiData = SPIDR;
	}
}

/*
 *--------------------------------------------------------------------------------
 * void SPI_Post(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void SPI_Post(void)
{
}


/* End of spi.c */
