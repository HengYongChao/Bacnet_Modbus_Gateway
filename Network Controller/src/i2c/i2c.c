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
 * Module Name : i2c.c
 * Purpose     : This module handles the I2C serial interface driver.
 * Author      : Robin Lee
 * Date        : 2005-01-10
 * Notes       :
 * $Log: i2c.c,v $
 * Revision 1.2  2006/04/14 00:56:42  robin6633
 * Fixed the function name error "I2cCmd() -> I2C_Cmd()".
 *
 * Revision 1.1  2006/04/07 11:38:34  robin6633
 * no message
 *
 *================================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include	<stdio.h>
#include	"reg80390.h"
#include	"types.h"
#include	"i2c.h"
#if I2C_SLAVE_ENABLE
#include	"console_debug.h"	
#endif
#include	"printd.h"

/* STATIC VARIABLE DECLARATIONS */
static U8_T		i2cCtrl = 0;
static U8_T		i2cEndCond = 0;
static U8_T		i2cActF = 0;	// indicate the condition of a transfer
static U16_T	i2cDataLen = 0;	// The I2cPktLen includes address and data
static U16_T	i2cDataLenCnt = 0;	// Packet's counter of transferring 
static U8_T		i2cPktDir = 0;	// Packet's direction
static I2C_BUF 	*ptI2cTxBuf = 0;
static I2C_BUF 	*ptI2cRxBuf = 0;
static U8_T		i2cState = 0;	// I2C master state flag
static U8_T		i2cSlvRxPkt[SLV_MAX_PKT_NUM];
static U8_T		i2cSlvTxPkt[SLV_MAX_PKT_NUM];


/* LOCAL SUBPROGRAM DECLARATIONS */
static void i2c_MstStatus(U8_T i2cStatus);
static void i2c_SlvStatus(U8_T i2cStatus);
static void i2c_MasterXmit(U8_T wrData, U8_T mstCmd);
static void i2c_MasterRcvr(U8_T *rdData, U8_T mstCmd);
static void i2c_SlaveXmit(U8_T wrData, U8_T slvCmd);
static void i2c_SlaveRcvr(U8_T *rdData, U8_T slvCmd);

#if I2C_SLAVE_ENABLE
static void i2c_SlvRxProcess(void);
#endif


extern void test_run(U8_T dat);
extern void Uart0_Tx(U8_T *buf,U8_T len); 
extern U8_T test[10] ;
extern void test_port(U8_T);

/* LOCAL SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * static void i2c_MstStatus(U8_T i2cStatus)
 * Purpose : Checks the interrupt status of I2C master mode.
 * Params  : i2cStatus - master status when interrupt occured.
 * Returns : none
 * Note    : none
 *--------------------------------------------------------------------------------
 */
static void i2c_MstStatus(U8_T i2cStatus)
{



	if (i2cPktDir == I2C_MST_XMIT)
	{
		/* Check the current byte ack */
		if ((!(i2cStatus & I2C_NO_ACK)) && (i2cStatus & I2C_INTR_FLAG)
		&& (!(i2cStatus & I2C_TIP)) && (i2cStatus & I2C_BUS_BUSY))
		{
			if (!I2C_FlagChk(I2C_BUSY))
			{
				I2C_FlagEnb(I2C_RESTART);
			}
			else
			{
				if ((i2cCtrl & I2C_10BIT) && (i2cActF & I2C_START_COND))
				{
					
					
					
					i2c_MasterXmit((U8_T)(ptI2cTxBuf->I2cAddr.TenBitAddr & 0x00FF), I2C_MASTER_GO | I2C_CMD_WRITE);
			
					
			
				}
				else
				{
					if (i2cDataLenCnt < (i2cDataLen-1))
					{
						/* transmit the first data byte */
						i2c_MasterXmit(ptI2cTxBuf->I2cData[i2cDataLenCnt], I2C_MASTER_GO | I2C_CMD_WRITE);
						i2cDataLenCnt ++;

						

					}
					else if (i2cDataLenCnt == (i2cDataLen-1))
					{
						/* transmit the last data byte */
						if (i2cEndCond & I2C_STOP_COND)
						{
							i2c_MasterXmit(ptI2cTxBuf->I2cData[i2cDataLenCnt], I2C_MASTER_GO | I2C_CMD_WRITE | I2C_STOP_COND);
							i2cDataLenCnt = 0;

						
						}
						else
						{
							i2c_MasterXmit(ptI2cTxBuf->I2cData[i2cDataLenCnt], I2C_MASTER_GO | I2C_CMD_WRITE);
						
							
							i2cDataLenCnt = 0;
							EA = 0;
							I2C_FlagClr(I2C_BUSY);
							EA = 1;
						}
					}
				}
			}
		/*	if (i2cActF & I2C_STOP_COND)
			{
				i2cDataLenCnt = 0;
				EA = 0;
				I2C_FlagClr(I2C_BUSY);
				EA = 1;
			}*/
		}
		else if (i2cStatus & I2C_NO_ACK)
		{
			i2cDataLenCnt = 0;
			if (i2cActF & I2C_START_COND)
			{
				/* transmit the STOP condition */
				i2c_MasterXmit(0, I2C_MASTER_GO | I2C_STOP_COND);
			
				
			
			
				i2cDataLenCnt = 0;
				EA = 0;
				I2C_FlagClr(I2C_BUSY);
				I2C_FlagEnb(I2C_NACK);
				EA = 1;
			}
			else
			{
				i2cDataLenCnt = 0;
				EA = 0;
				I2C_FlagClr(I2C_BUSY);
				EA = 1;
			}
		}
		else if (i2cStatus & I2C_ARB_LOST)
		{
			i2c_MasterXmit(0, I2C_MASTER_GO | I2C_STOP_COND);
		
			 
		
		
			i2cDataLenCnt = 0;
			EA = 0;
			I2C_FlagClr(I2C_BUSY);
			I2C_FlagEnb(I2C_NACK);
//			printd("I2C arbitration lost\n\r");
			EA = 1;
		}
		else if (i2cStatus & I2C_TIP)
		{
			i2cDataLenCnt = 0;
			if (i2cActF & I2C_START_COND)
			{
				I2C_FlagClr(I2C_BUSY);
				/* transmit the STOP condition */
				i2c_MasterXmit(0, I2C_MASTER_GO | I2C_STOP_COND);


			}
			else
			{
				/* transmit the STOP condition or repeat START condition */
				I2C_PktBuf(ptI2cTxBuf);
			}
		}
		else if ((!(i2cStatus & I2C_NO_ACK)) && (!(i2cStatus & I2C_TIP)) && (!(i2cStatus & I2C_BUS_BUSY)))
		{
			if (i2cActF & I2C_STOP_COND)
			{
				i2cDataLenCnt = 0;
				EA = 0;
				I2C_FlagClr(I2C_BUSY);
				EA = 1;
			}
		}
	}
	else if (i2cPktDir == I2C_MST_RCVR)
	{
		/* Check the current byte ack */
		if ((!(i2cStatus & I2C_NO_ACK)) && (i2cStatus & I2C_INTR_FLAG)
		&& (!(i2cStatus & I2C_TIP)) && (i2cStatus & I2C_BUS_BUSY))
		{
			if (i2cActF & I2C_START_COND)
			{
				if (i2cDataLenCnt == (i2cDataLen - 1))
					i2c_MasterRcvr(&(ptI2cRxBuf->I2cData[0]), I2C_MASTER_GO | I2C_CMD_READ | I2C_STOP_COND);
				else
					i2c_MasterRcvr(&(ptI2cRxBuf->I2cData[0]), I2C_MASTER_GO | I2C_CMD_READ);
			}
			else if (i2cActF & I2C_STOP_COND)
			{
				I2C_FlagClr(I2C_BUSY);
				i2c_MasterRcvr(&(ptI2cRxBuf->I2cData[i2cDataLenCnt]), 0);
			}
			else
			{
				if (i2cDataLenCnt < (i2cDataLen - 1))
				{
					/* reveive the next byte */
					i2c_MasterRcvr(&(ptI2cRxBuf->I2cData[i2cDataLenCnt]), I2C_MASTER_GO | I2C_CMD_READ);
				}
				else if (i2cDataLenCnt == (i2cDataLen - 1))
				{
					/* receive the last byte */
					i2c_MasterRcvr((U8_T *)(&(ptI2cRxBuf->I2cData[i2cDataLenCnt])), I2C_MASTER_GO | I2C_CMD_READ | I2C_STOP_COND);
				}
			}
		}
		else if (i2cStatus & I2C_NO_ACK)
		{
			i2cDataLenCnt = 0;
			if (i2cActF & I2C_START_COND)
			{
				i2c_MasterXmit(0, I2C_MASTER_GO | I2C_STOP_COND);
			
				 
			
				i2cDataLenCnt = 0;
				EA = 0;
				I2C_FlagClr(I2C_BUSY);
				I2C_FlagEnb(I2C_NACK);
				EA = 1;
			}
			else
			{
				i2cDataLenCnt = 0;
				EA = 0;
				I2C_FlagClr(I2C_BUSY);
				EA = 1;
			}
		}
		else
		{
			if (i2cActF & I2C_STOP_COND)
			{
				I2C_FlagClr(I2C_BUSY);
				i2c_MasterRcvr(&(ptI2cRxBuf->I2cData[i2cDataLenCnt]), 0);
			}
		}
	}
}

/*
 *--------------------------------------------------------------------------------
 * static void i2c_SlvStatus(U8_T i2cStatus)
 * Purpose : Handles the interrupt status of I2C slave mode.
 * Params  : none
 * Returns : none
 * Note    : none
 *--------------------------------------------------------------------------------
 */
static void i2c_SlvStatus(U8_T i2cStatus)
{
	U8_T	devAddr;

	if (i2cStatus & I2C_SLV_STOP)
	{
		if (!(i2cStatus & I2C_SLV_START))
		{
			if (i2cPktDir == I2C_SLV_RCVR)
			{
				i2cDataLen = i2cDataLenCnt;
				#if I2C_SLAVE_ENABLE
				i2c_SlvRxProcess();
				#endif
			}
			i2cDataLenCnt = 0;
			i2c_SlaveRcvr(&i2cSlvRxPkt[i2cDataLenCnt], I2C_SLAVE_GO);
		}
	}
	if (i2cStatus & I2C_SLV_NACK)
	{
		i2c_SlaveRcvr(&devAddr, I2C_RLS);
	}
	else
	{
		if (i2cStatus & I2C_SLV_WR)
		{
			if (i2cStatus & I2C_SLV_START)
			{
				i2c_SlaveRcvr(&devAddr, I2C_SLAVE_GO);
				i2cPktDir = I2C_SLV_RCVR;
				i2cDataLenCnt = 0;
			}
			else if (i2cStatus & I2C_SLV_STOP)
			{
				i2c_SlaveRcvr(&i2cSlvRxPkt[i2cDataLenCnt], I2C_SLAVE_GO);
				i2cDataLen = i2cDataLenCnt;
				#if I2C_SLAVE_ENABLE
				i2c_SlvRxProcess();
				#endif
				i2cDataLenCnt = 0;
			}
			else if (i2cStatus & I2C_SLV_RESTART)
			{
				i2c_SlaveRcvr(&devAddr, I2C_SLAVE_GO);
				i2cPktDir = I2C_SLV_RCVR;
				i2cDataLenCnt = 0;
			}
			else
			{
				i2c_SlaveRcvr(&i2cSlvRxPkt[i2cDataLenCnt], I2C_SLAVE_GO);
				i2cDataLenCnt ++;
			}
		}
		else if (i2cStatus & I2C_SLV_RD)
		{
			if (i2cStatus & I2C_SLV_STOP)
			{
				i2c_SlaveRcvr(&devAddr, I2C_SLAVE_GO);
				i2cDataLenCnt = 0;
			}
			else if (i2cStatus & I2C_SLV_START)
			{
				i2cPktDir = I2C_SLV_XMIT;
				i2cDataLenCnt = 0;
				#if I2C_SLAVE_ENABLE
				i2c_SlvRxProcess();
				#endif
				i2c_SlaveXmit(i2cSlvTxPkt[i2cDataLenCnt], I2C_SLAVE_GO);
				i2cDataLenCnt ++;
			}
			else if (i2cStatus & I2C_SLV_RESTART)
			{
				i2cPktDir = I2C_SLV_XMIT;
				i2cDataLenCnt = 0;
				#if I2C_SLAVE_ENABLE
				i2c_SlvRxProcess();
				#endif
				i2c_SlaveXmit(i2cSlvTxPkt[i2cDataLenCnt], I2C_SLAVE_GO);
				i2cDataLenCnt ++;
			}
			else
			{
				if (i2cSlvRxPkt[0] == I2C_SLV_BRDM)
				{
					#if I2C_SLAVE_ENABLE
					i2c_SlvRxProcess();
					#endif
				}
				i2c_SlaveXmit(i2cSlvTxPkt[i2cDataLenCnt], I2C_SLAVE_GO);
				i2cDataLenCnt ++;
			}
		}
	}
}

#if I2C_SLAVE_ENABLE
/*
 *--------------------------------------------------------------------------------
 * static void i2c_SlvRxProcess(void)
 * Purpose : Handling received command functions in I2C slave mode And replying
 *           packets corresponding with the received command.
 * Params  : none
 * Returns : none
 * Note    : none
 *--------------------------------------------------------------------------------
 */
static void i2c_SlvRxProcess(void)
{
	U8_T	slvCmd;
	U8_T	sfrAddr;
	U8_T	cmdIndReg, realReg, realLen;
	U32_T	memAddr, memData;
	U16_T	i;

	slvCmd = i2cSlvRxPkt[0];
	if ((slvCmd & 0xF0) == I2C_SLV_SWSFR)
	{
		realLen = (slvCmd & 0x0F) + 1;
		sfrAddr = i2cSlvRxPkt[1];
		for (i = 0 ; i < realLen ; i ++)
		{
			CLI_SfrWr((U32_T)sfrAddr, (U32_T)i2cSlvRxPkt[i + 2]);
		}
	}
	else if ((slvCmd & 0xF0) == I2C_SLV_SRSFR)
	{
		realLen = (slvCmd & 0x0F) + 1;
		sfrAddr = i2cSlvRxPkt[1];
		for (i = 0 ; i < realLen ; i ++)
		{
			CLI_SfrRd((U32_T)sfrAddr, &memData);
			i2cSlvTxPkt[i] = (U8_T)memData;
		}
	}
	else if ((slvCmd & 0xF0) == I2C_SLV_IWSFR)
	{
		cmdIndReg = i2cSlvRxPkt[1];
		realReg = i2cSlvRxPkt[2];
		realLen = (slvCmd & 0x0F) + 1;
		if (cmdIndReg == SFR_I2CCIR)
		{
			CLI_I2cWr((U32_T)realReg, &i2cSlvRxPkt[3], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_SPICIR)
		{
			CLI_SpiWr((U32_T)realReg, &i2cSlvRxPkt[3], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_OWCIR)
		{
			CLI_OwWr((U32_T)realReg, &i2cSlvRxPkt[3], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_CANCIR)
		{
			CLI_CanWr((U32_T)realReg, &i2cSlvRxPkt[3], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_TCIR)
		{
			CLI_ToeWr((U32_T)realReg, &i2cSlvRxPkt[3], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_MCIR)
		{
			CLI_MacWr((U32_T)realReg, &i2cSlvRxPkt[3], (U8_T)realLen);
		}
	}
	else if ((slvCmd & 0xF0) == I2C_SLV_IRSFR)
	{
		cmdIndReg = i2cSlvRxPkt[1];
		realReg = i2cSlvRxPkt[2];
		realLen = (slvCmd & 0x0F) + 1;
		if (cmdIndReg == SFR_I2CCIR)
		{
			CLI_I2cRd((U32_T)realReg, &i2cSlvTxPkt[i2cDataLenCnt], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_SPICIR)
		{
			CLI_SpiRd((U32_T)realReg, &i2cSlvTxPkt[i2cDataLenCnt], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_OWCIR)
		{
			CLI_OwRd((U32_T)realReg, &i2cSlvTxPkt[i2cDataLenCnt], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_CANCIR)
		{
			CLI_CanRd((U32_T)realReg, &i2cSlvTxPkt[i2cDataLenCnt], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_TCIR)
		{
			CLI_ToeRd((U32_T)realReg, &i2cSlvTxPkt[i2cDataLenCnt], (U8_T)realLen);
		}
		else if (cmdIndReg == SFR_MCIR)
		{
			CLI_MacRd((U32_T)realReg, &i2cSlvTxPkt[i2cDataLenCnt], (U8_T)realLen);
		}
	}
	else if (slvCmd == I2C_SLV_BWDM)
	{
		memAddr = ((U32_T)i2cSlvRxPkt[3] << 16) | ((U32_T)i2cSlvRxPkt[2] << 8) | ((U32_T)i2cSlvRxPkt[1]);
		for (i = 4 ; i < i2cDataLen ; i ++)
		{
			CLI_ExtMemWr((U32_T)memAddr, (U32_T)i2cSlvRxPkt[i]);
			memAddr ++;
		}
	}
	else if (slvCmd == I2C_SLV_BRDM)
	{
		if (i2cDataLenCnt == 0)
		{
			memAddr = ((U32_T)i2cSlvRxPkt[3] << 16) | ((U32_T)i2cSlvRxPkt[2] << 8) | ((U32_T)i2cSlvRxPkt[1]);
		}
		CLI_ExtMemRd((U32_T)memAddr, &memData);
		i2cSlvTxPkt[i2cDataLenCnt] = (U8_T)memData;
		memAddr ++;
	}
}
#endif

/*
 *--------------------------------------------------------------------------------
 * static void i2c_MasterXmit(U8_T wrData, U8_T mstCmd)
 * Purpose : Putting the data into i2c transmitting register and setting the
 *           master's command and condition in I2C master mode.
 * Params  : wrData - one byte data to transmit.
 *           mstCmd - master command of the current byte data.
 * Returns : none
 * Note    : none
 *--------------------------------------------------------------------------------
 */
static void i2c_MasterXmit(U8_T wrData, U8_T mstCmd)
{
	/* Record the globe flag of command condition */
	
	
	
	i2cActF = mstCmd;
	/* First the master flipper sends the slave address to access */
	

	
	I2C_Cmd(SI_WR, I2CTR, &wrData);
	/* Order command to I2CCR */
	

	

	I2C_Cmd(SI_WR, I2CCR, &mstCmd);

	

}

/*
 *--------------------------------------------------------------------------------
 * static void i2c_MasterRcvr(U8_T *rdData, U8_T mstCmd)
 * Purpose : Getting the receiving byte data in I2C master mode.
 * Params  : *rdData - a pointer to store receiving data.
 *           mstCmd - master command of the current byte data.
 * Returns : none
 * Note    : none
 *--------------------------------------------------------------------------------
 */
static void i2c_MasterRcvr(U8_T *rdData, U8_T mstCmd)
{
	/* Record the globe flag of command condition */
	i2cActF = mstCmd;
	/* After ACK, read data from I2CRR */
	I2C_Cmd(SI_RD, I2CRR, rdData);
	/* Then, reply ACK to slave */
	I2C_Cmd(SI_WR, I2CCR, &mstCmd);

	i2cDataLenCnt ++;
}

/*
 *--------------------------------------------------------------------------------
 * static void i2c_SlaveXmit(U8_T wrData, U8_T slvCmd)
 * Purpose : Putting the data into i2c transmitting register and setting the
 *           master's command and condition in I2C slave mode.
 * Params  : wrData - one byte data to transmit.
 *           slvCmd - slave command of the current byte data.
 * Returns : none
 * Note    : none
 *--------------------------------------------------------------------------------
 */
static void i2c_SlaveXmit(U8_T wrData, U8_T slvCmd)
{
	/* Record the globe flag of command condition */
	i2cActF = slvCmd;
	/* transmit the data byte */
	I2C_Cmd(SI_WR, I2CTR, &wrData);
	/* Order command to I2CCR */
	I2C_Cmd(SI_WR, I2CCR, &slvCmd);
}

/*
 *--------------------------------------------------------------------------------
 * static void i2c_SlaveRcvr(U8_T *rdData, U8_T slvCmd)
 * Purpose : Getting the receiving byte data in I2C slave mode.
 * Params  : *rdData - a pointer to store receiving data.
 *           slvCmd - slave command of the current byte data.
 * Returns : none
 * Note    : none
 *--------------------------------------------------------------------------------
 */
static void i2c_SlaveRcvr(U8_T *rdData, U8_T slvCmd)
{
	/* Record the globe flag of command condition */
	i2cActF = slvCmd;
	/* After ACK, read data from I2CRR */
	I2C_Cmd(SI_RD, I2CRR, rdData);
	/* Then, reply ACK to slave */
	I2C_Cmd(SI_WR, I2CCR, &slvCmd);
}


/* EXPORTED SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * void I2C_Setup(U8_T ctrlCmd, U16_T preClk, U16_T axIdAddr)
 * Purpose : This function is used to setup the I2C module and
 *           to initial the globe values in this module.
 * Params  : ctrlCmd - control register value.
 *           preClk - a pre-scale parameter calculates the bus speed.
 *           axIdAddr - a device address of local AX11000 I2C module.
 * Returns : none
 * Note    : none
 *--------------------------------------------------------------------------------
 */
void I2C_Setup(U8_T ctrlCmd, U16_T preClk, U16_T axIdAddr)
{
	U16_T	i;
	/* Values initial */
	i2cCtrl = 0;
	i2cEndCond = 0;
	i2cActF = 0;
	i2cDataLen = 0;
	i2cDataLenCnt = 0;
	i2cPktDir = 0;
	ptI2cTxBuf = NULL;
	ptI2cRxBuf = NULL;
	i2cState = 0;
	for (i=0 ; i<SLV_MAX_PKT_NUM ; i++)
	{
		i2cSlvRxPkt[i] = 0;
		i2cSlvTxPkt[i] = 0;
	}

	/* Pre-scale Clock */
	I2CDR = (U8_T)(0x00FF & preClk);
	I2CDR = (U8_T)((0xFF00 & preClk) >> 8);
	I2CCIR = I2CCPR;		//addr is 0x00



	/* Flipper device address for slave mode */
	I2CDR = (U8_T)(axIdAddr & 0x00FF);
	I2CDR = (U8_T)((axIdAddr & 0xFF00) >> 8);
	I2CCIR = I2CSDAR;



	/* Setup I2C mode */
	I2C_Cmd(SI_WR, I2CCTL, &ctrlCmd);
}

/*
 *--------------------------------------------------------------------------------
 * void I2C_Func(void)
 * Purpose : Handling serial interface I2C interrupt function.
 * Params  : none
 * Returns : none
 * Note    : The I2C_RLE_ING (reloading I2C EEPROM) bit and
 *           the I2C_BL_DONE (Bootloader done) bit must always be checked,
 *           whichever in master mode or slave mode.
 *--------------------------------------------------------------------------------
 */
void I2C_Func(void)
{
	U8_T	i2cStatus;

	I2C_Cmd(SI_RD, I2CCTL, &i2cCtrl);

	if (i2cCtrl & I2C_MASTER_MODE)
	{
		EA = 0;
		I2C_Cmd(SI_RD, I2CMSR, &i2cStatus);
		EA = 1;
		if (!(i2cStatus & I2C_RLE_ING) && (i2cStatus & I2C_BL_DONE))
		{
			if (i2cCtrl & I2C_MST_IE)
			{
				if (i2cStatus & I2C_INTR_FLAG)
				{
					i2c_MstStatus(i2cStatus);
				}
			}
			else
			{
				if (!(i2cStatus & I2C_TIP))
				{
					i2c_MstStatus(i2cStatus);
				}
			}
		}
	}
	else
	{
		EA = 0;
		I2C_Cmd(SI_RD, I2CMSR, &i2cStatus);
		EA = 1;

		if (!(i2cStatus & I2C_RLE_ING) && (i2cStatus & I2C_BL_DONE))
		{
			i2cStatus = 0;
			EA = 0;
			I2C_Cmd(SI_RD, I2CSSR, &i2cStatus);
			EA = 1;
			if (i2cCtrl & I2C_SLV_IE)
			{
				if (i2cStatus & I2C_SLV_TXR_OK)
				{
					i2c_SlvStatus(i2cStatus);
				}
			}
			else
			{
				if (i2cStatus & I2C_SLV_TXR_OK)
				{
					i2c_SlvStatus(i2cStatus);
				}
			}
		}
	}
}

/*
 *--------------------------------------------------------------------------------
 * void I2C_PktBuf(I2C_BUF *ptI2cBuf)
 * Purpose : Packeting a packet and transmitting the first byte
 * Params  : ptI2cBuf - a pointer stores the packet.
 * Returns : none
 * Note    : none
 *--------------------------------------------------------------------------------
 */
void I2C_PktBuf(I2C_BUF *ptI2cBuf)
{
	U8_T	firstAddr;

	I2C_Cmd(SI_RD, I2CCTL, &i2cCtrl); 

	

	if (i2cCtrl & I2C_MASTER_MODE) // I2C Master Mode
	{
		i2cDataLenCnt = 0;
		i2cEndCond = ptI2cBuf->I2cEnd;
		i2cPktDir = ptI2cBuf->I2cDir;
		i2cDataLen = ptI2cBuf->DataLen;
		
				
			if (i2cCtrl & I2C_10BIT)
			{


				firstAddr = ((U8_T)((ptI2cBuf->I2cAddr.TenBitAddr & 0x0300) >> 7) | 0xF0);
				if (i2cPktDir & I2C_XMIT)
				{
					ptI2cTxBuf = ptI2cBuf;
					i2c_MasterXmit(firstAddr & ~BIT0, I2C_MASTER_GO | I2C_CMD_WRITE | I2C_START_COND);
				
				  
				
				}
				else
				{
					ptI2cRxBuf = ptI2cBuf;
					i2c_MasterXmit(firstAddr | BIT0, I2C_MASTER_GO | I2C_CMD_WRITE | I2C_START_COND);
				
				
				
				
				}
			}
			else
			{
				

				firstAddr = ptI2cBuf->I2cAddr.SevenBitAddr << 1;

				if (i2cPktDir & I2C_XMIT)
				{
				

					ptI2cTxBuf = ptI2cBuf;
					
					 
					 
			


				i2c_MasterXmit(firstAddr & ~BIT0, I2C_MASTER_GO | I2C_CMD_WRITE | I2C_START_COND);
					
					
					 
				



				}
				else
				{

					 

					ptI2cRxBuf = ptI2cBuf;
					i2c_MasterXmit(firstAddr | BIT0, I2C_MASTER_GO | I2C_CMD_WRITE | I2C_START_COND);
				
				
				
				}

			   

			}
	}
	else // I2C Slave Mode
	{
	
	 
	
		if (ptI2cBuf->I2cDir & I2C_XMIT)
		{
			/* Get the slave data to transmit */
			//ptI2cTxBuf->ptI2c = ??;
			ptI2cBuf->DataLen = i2cDataLen;
		}
		else
		{
			/* packet the received data to upper layer */
			ptI2cBuf->DataLen = i2cDataLen;
		}
	}
}

/*
 *--------------------------------------------------------------------------------
 * BOOL I2C_FlagChk(U8_T chkBit)
 * Purpose : Checking the current state in I2C driver.
 * Params  : chkBit - the state bit to be checked.
 * Returns : TRUE - the state value meets the chkBit.
 * Note    : none
 *--------------------------------------------------------------------------------
 */
BOOL I2C_FlagChk(U8_T chkBit)
{
	if (i2cState & chkBit)
		return TRUE;
	else
		return FALSE;
}

/*
 *--------------------------------------------------------------------------------
 * void I2C_FlagEnb(U8_T enbBit)
 * Purpose : Setting the current state in I2C driver.
 * Params  : enbBit - the state bit to be set.
 * Returns : none
 * Note    : none
 *--------------------------------------------------------------------------------
 */
void I2C_FlagEnb(U8_T enbBit)
{
	i2cState = i2cState | enbBit;
}

/*
 *--------------------------------------------------------------------------------
 * void I2C_FlagClr(U8_T clrBit)
 * Purpose : Clearing the current state in I2C driver.
 * Params  : clrBit - the state bit to be cleared.
 * Returns : none
 * Note    : none
 *--------------------------------------------------------------------------------
 */
void I2C_FlagClr(U8_T clrBit)
{
	i2cState = i2cState & ~clrBit;
}

/*
 *--------------------------------------------------------------------------------
 * void I2C_Cmd(U8_T cmdType, U8_T i2cCmdIndex, U8_T *i2cData)
 * Purpose : Accessing the I2C interface indirectly through I2C's SFR.
 * Params  : cmdType - command type of writing or reading.
 *           i2cCmdIndex - I2C register address.
 *           *i2cData - a pointer store the data.
 * Returns : none
 * Note    : none
 *--------------------------------------------------------------------------------
 */
void I2C_Cmd(U8_T cmdType, U8_T i2cCmdIndex, U8_T *i2cData)
{
	 
	

	if (cmdType == SI_WR)
	{
		
		
		I2CDR = *i2cData;
		 

		I2CCIR = i2cCmdIndex;
		
		 
	}
	else if (cmdType == SI_RD)
	{
		
		
		I2CCIR = i2cCmdIndex;
		

		*i2cData = I2CDR;
		

	}
}

/*
 *--------------------------------------------------------------------------------
 * void I2C_Post(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void I2C_Post(void)
{
}


/* End of i2c.c */
