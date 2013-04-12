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
 * Module Name : hsuart.c
 * Purpose     : The High Speed UART module driver. It manages the character
 *               buffer and handles the ISR.
 * Author      : Robin Lee
 * Date        : 2006-01-09
 * Notes       : None.
 * $Log: hsuart.c,v $
 * Revision 1.20  2006/07/25 03:41:23  robin6633
 * 1.Add Xon/Xoff counter for debugging.
 *
 * Revision 1.19  2006/07/24 06:40:51  robin6633
 * 1.Fixed the XON/XOFF ASCII is put into hardware transmitting register driectly.
 *
 * Revision 1.18  2006/07/21 11:24:55  robin6633
 * 1.Add flow control check in hsurFlowOn==1.
 *
 * Revision 1.17  2006/07/19 08:51:24  robin6633
 * 1.Fixed Hardware flow control function.
 * 2.Extern a function HSUR_GetLineStatus() to get UR2_LSR.
 *
 * Revision 1.16  2006/07/18 08:03:59  robin6633
 * 1.Fixed Tx flow control in software flow control mode.
 *
 * Revision 1.15  2006/06/30 06:17:01  robin6633
 * 1.Fixed software flow control in first initial.
 *
 * Revision 1.14  2006/06/27 10:45:24  robin6633
 * 1.Add flow control for transmitting.
 *
 * Revision 1.13  2006/06/19 14:20:57  robin6633
 * 1.Protect transmit counter and pointer.
 * 2.Force transmit more data if transmit fifo empty.
 *
 * Revision 1.12  2006/06/11 02:18:49  robin6633
 * 1.Add Xon/Xoff.
 *
 * Revision 1.11  2006/06/05 06:21:43  robin6633
 * 1.Fixed function declaration.
 *    U8_T HSUR_RxBufFlowControl(void) -> void HSUR_RxBufFlowControl(void)
 * 2.Fixed hsur_ReadLsr() & hsur_ReadMsr().
 *
 * Revision 1.10  2006/06/05 01:30:44  robin6633
 * 1.Fixed software flow control and prevented the hardware FIFO overrun.
 *
 * Revision 1.9  2006/05/24 05:40:34  robin6633
 * 1.Add flow control water mark.
 *
 * Revision 1.8  2006/05/23 11:07:51  robin6633
 * 1.Enable flow control code.
 *
 * Revision 1.7  2006/05/22 13:23:42  robin6633
 * 1.Fixed buffer overwrite.
 *
 * Revision 1.6  2006/05/22 07:39:28  robin6633
 * 1.Disable flow control.
 *
 * Revision 1.5  2006/05/19 06:37:13  robin6633
 * 1.Fixed the baudrate setup for default configuration.
 *
 * Revision 1.4  2006/05/19 03:48:37  robin6633
 * 1.Add Xon/Xoff flow control.
 * 2.Expand an external function HSUR_ChangeBaud(U8_T baud).
 *
 * Revision 1.3  2006/05/18 09:57:55  Louis
 * no message
 *
 * Revision 1.2  2006/05/18 02:27:56  robin6633
 * 1.Removed printf in UART2.
 *
 * Revision 1.1  2006/05/15 03:06:52  robin6633
 * no message
 *
 * Revision 1.3  2006/05/03 02:42:30  robin6633
 * Changed the the function name HSUR_GetBufCount()
 * to HSUR_GetRxBufCount() .
 *
 * Revision 1.2  2006/05/02 01:44:07  robin6633
 * Add an expanding function to get the counter value of UART2 software buffer.
 *
 * Revision 1.1  2006/04/07 11:38:18  robin6633
 * no message
 *
 *================================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include	"reg80390.h"
#include	"types.h"
#include	"uart.h"
#include	"mstimer.h"
#include	"hsuart.h"
#include	"string.h"


/* STATIC VARIABLE DECLARATIONS */

U8_T far hsurRxBuffer[UR2_MAX_RX_SIZE];
static U8_T	far 	hsurTxBuffer[UR2_MAX_TX_SIZE];
static U16_T far 	hsurRxBufNum = 0;
static U16_T far 	hsurTxBufNum = 0;
static U8_T	 far 	hsurRxTrigLvl = 0;
U16_T	far hsurRxCount = 0;
static S16_T far 	hsurTxCount = 0;
static U16_T far 	hsurGetPtr = 0;
static U16_T far 	hsurPutPtr = 0;
static U8_T	 far 	hsurFlowCtrl = 0;
static U8_T	 far 	hsurFlowOn = 0;
static U8_T	 far 	hsurTxTransmit = 0;
static U8_T	 far 	hsurTxFlag = 0;
static U8_T	 far 	hsurTxState = 0;
static U16_T far 	hsurErrorCount = 0;
static U32_T far 	hsurErrTimeStart = 0;
static U32_T far 	hsurErrTimeStop = 0;
static U8_T	 far 	hsurErrBlocking = 0;
static U16_T far 	hsurBaudRateDivisor = 0;
static U8_T	 far 	hsurLineStatusValue = 0;
static U8_T	 far 	hsurModemStatusValue = 0;	
static U8_T	 far 	hsurLineControlValue = 0;
static U8_T	 far 	hsurModemControlValue = 0;
static U8_T	 far 	hsurFifoControlValue = 0;
static U8_T	 far 	hsurAppFlowOn = 0;
static U8_T     far  hsurFlowCtrlXoff = FALSE;
static U8_T    far  hsurFlowCtrlXon = FALSE;
static U8_T	 far 	hsurFlowCtrlHwCTSon = FALSE;

U8_T far uart2_timeout = UART2_TIMEOUT;

/* LOCAL SUBPROGRAM DECLARATIONS */
static void		hsur_ReadLsr(void);
static void		hsur_RcvrTrig(void);
static void		hsur_Rcvr(void);
static void		hsur_Xmit(void);
static void		hsur_ReadMsr(void);

extern void 	test_run(U8_T dat);
extern volatile U32_T xTickCount;
/* LOCAL SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * static void hsur_ReadLsr(void)
 * Purpose : Read Line Status Register and display.
 * Params  : None
 * Returns : None
 * Note    : None
 *--------------------------------------------------------------------------------
 */
static void hsur_ReadLsr(void)
{
	hsurLineStatusValue = UR2_LSR;

	if (hsurLineStatusValue & UR2_OE)
	{
		// Overrun Error
		hsurErrorCount ++;
//		P3 = BIT0;
	}
	if (hsurLineStatusValue & UR2_PE)
	{
		// Parity Error
		hsurErrorCount ++;
//		P3 = BIT1;
	}
	if (hsurLineStatusValue & UR2_FE)
	{
		// Framing Error
		hsurErrorCount ++;
//		P3 = BIT2;
	}
	if (hsurLineStatusValue & UR2_BI)
	{
		// Break Interrupt Occured
		hsurErrorCount ++;
//		P3 = BIT3;
	}
	if (hsurLineStatusValue & UR2_FRAME_ERR)
	{
		// Mixing Error
		hsurErrorCount ++;
//		P3 = BIT4;
	}

	if (hsurErrorCount)
	{
		UR2_FCR |= UR2_RXFIFO_RST;

		if (hsurErrorCount >=30)
		{
			hsurErrTimeStop = xTickCount;
			if (((hsurErrTimeStop - hsurErrTimeStart) * SWTIMER_INTERVAL) <= 2000)
			{
				UR2_IER = 0;
				hsurErrBlocking = 1;
			}
			else
			{
				hsurErrBlocking = 0;
				hsurErrTimeStart = 0;
				hsurErrorCount = 0;
			}
		}
		else// if (hsurErrorCount < 30)
		{
			U8_T trash;

			while (UR2_LSR & UR2_DR)
			{
				trash = UR2_RBR;
			}

			if ((hsurErrTimeStart == 0) && (hsurErrorCount < 5))
			{
				hsurErrTimeStart = xTickCount;
			}
			else
			{
				hsurErrTimeStop = xTickCount;
				if (((hsurErrTimeStop - hsurErrTimeStart) * SWTIMER_INTERVAL) > 2000)
				{
					hsurErrBlocking = 0;
					hsurErrTimeStart = 0;
					hsurErrorCount = 0;
				}
			}
		}
	}

	if (hsurFlowCtrl == UR2_FLOW_CTRL_SW)
	{
		UR2_THR = FLOW_SW_ERROR;
	}	
}

/*
 *--------------------------------------------------------------------------------
 * static void hsur_RcvrTrig(void)
 * Purpose : Get data and put into the receiver buffer continuously until trigger bytes
 * Params  : None
 * Returns : None
 * Note    : None
 *--------------------------------------------------------------------------------
 */
static void hsur_RcvrTrig(void)
{
	U8_T	c;
	U16_T	i;

	if (hsurRxCount >= UR2_MAX_RX_SIZE - hsurRxTrigLvl) // buffer full
		return;

	if (hsurFlowCtrl == UR2_FLOW_CTRL_SW)
	{
		for (i=0 ; i<hsurRxTrigLvl ; i++)
		{
			c = UR2_RBR;
			if (hsurTxState == 1)
			{
				EA = 0;
				hsurTxFlag = c;
				hsurTxState = 0;
				EA = 1;
			}
			else
			{
				hsurRxBuffer[hsurRxCount++] = c;
				if (hsurRxCount == UR2_MAX_RX_SIZE)
					hsurRxCount = 0;
			}
	   	}
	}
	else if (hsurFlowCtrl != UR2_FLOW_CTRL_X)
	{
		for (i=0 ; i<hsurRxTrigLvl ; i++)
		{
			hsurRxBuffer[hsurRxCount++] = UR2_RBR;
			if (hsurRxCount == UR2_MAX_RX_SIZE)
				hsurRxCount = 0;	
		}
	}
	else
	{
		for (i=0 ; i<hsurRxTrigLvl ; i++)
		{
			c = UR2_RBR;
			if (c != ASCII_XOFF && c != ASCII_XON)
			{
				hsurRxBuffer[hsurRxCount++] = c;
				if (hsurRxCount == UR2_MAX_RX_SIZE)
					hsurRxCount = 0;
			}
			else
			{
				if (c == ASCII_XOFF)
					hsurFlowCtrlXoff = TRUE;
				else if (c == ASCII_XON)
					hsurFlowCtrlXon = TRUE;
		  	}
		}
	}

	if (hsurFlowCtrl != UR2_FLOW_CTRL_NO)
	{
		HSUR_RxBufFlowControl();

		if (hsurFlowOn == FALSE)
		{
			if (hsurRxCount >= UR2_FLOW_HI_WATERMARK) // check software buffer status
			{
				hsurFlowOn = TRUE;
        	}
        	else if (hsurFlowCtrl == UR2_FLOW_CTRL_SW)
			{
				UR2_THR = FLOW_SW_CONTINUOUS;
			}			
		}	
	}
}

/*
 *--------------------------------------------------------------------------------
 * static void hsur_Rcvr(void)
 * Purpose : Receiving the byte data from hardware register into software buffer.
 * Params  : None
 * Returns : None
 * Note    : None
 *--------------------------------------------------------------------------------
 */
static void hsur_Rcvr(void)
{
	U8_T	far lineStatus = 0;

	if (hsurFlowCtrl == UR2_FLOW_CTRL_SW)
	{
		while (1)
		{
			lineStatus = UR2_LSR;
			hsurLineStatusValue = lineStatus;
	
			if (lineStatus & UR2_DR)
			{
				if (hsurTxState == 1)
				{
					EA = 0;
					hsurTxFlag = UR2_RBR;
					hsurTxState = 0;
					EA = 1;
				}
				else
				{
					hsurRxBuffer[hsurRxCount++] = UR2_RBR;
					if (hsurRxCount == UR2_MAX_RX_SIZE)
					{
						hsurRxCount = 0;
						break;
					}
				}
		 	}
			else
				break;
	  	}
	}
	else if (hsurFlowCtrl != UR2_FLOW_CTRL_X)
	{
		while (1)
		{
			lineStatus = UR2_LSR;
			hsurLineStatusValue = lineStatus;
	
			if (lineStatus & UR2_DR)
			{
				hsurRxBuffer[hsurRxCount++] = UR2_RBR;
				if (hsurRxCount == UR2_MAX_RX_SIZE)
				{
					hsurRxCount = 0;
					break;
				}
		  	}
			else				
				break;
		}		
	}
	else 
	{
		U8_T	c = 0;

		while (1)
		{
			lineStatus = UR2_LSR;
			hsurLineStatusValue = lineStatus;
	
			if (lineStatus & UR2_DR)
			{
				c = UR2_RBR;

				if (c != ASCII_XOFF && c != ASCII_XON)
				{
					hsurRxBuffer[hsurRxCount++] = c;
					if (hsurRxCount == UR2_MAX_RX_SIZE)
					{
						hsurRxCount = 0;
						break;
					}
				}
				else
				{
					if (c == ASCII_XOFF)
						hsurFlowCtrlXoff = TRUE;
					else if (c == ASCII_XON)
						hsurFlowCtrlXon = TRUE;
			  	}
			}
			else
				break;
	   	}
	}

	if (hsurFlowCtrl != UR2_FLOW_CTRL_NO)
		HSUR_RxBufFlowControl();
}

/*
 *--------------------------------------------------------------------------------
 * static void hsur_Xmit(void)
 * Purpose : Transmitting the byte data from software buffer into hardware register.
 * Params  : None
 * Returns : None
 * Note    : None
 *--------------------------------------------------------------------------------
 */
static void hsur_Xmit(void)
{
	U8_T far 	i = 0;

	for (i=0 ; i<UR2_TX_BUF_LEVEL ; i++)
	{
		if (hsurTxCount > 0)
	 	{
			UR2_THR = hsurTxBuffer[hsurTxBufNum];
			hsurTxBufNum ++;
			hsurTxCount --;

			if (hsurTxBufNum == UR2_MAX_TX_SIZE)
				hsurTxBufNum = 0; 

			if ((hsurFlowCtrl == UR2_FLOW_CTRL_HW) || (hsurFlowCtrl == UR2_FLOW_CTRL_X))
			{
				HSUR_TxBufFlowControl();
			}
		
			if (hsurTxCount <= 0)
			{		
				UR2_IER &= ~UR2_THRI_ENB;
				return;
			}
		}
		else
		{
			UR2_IER &= ~UR2_THRI_ENB;
			return;
		}
	}
}

/*
 *--------------------------------------------------------------------------------
 * static void hsur_ReadMsr(void)
 * Purpose : Reading the modem status register.
 * Params  : None
 * Returns : None
 * Note    : None
 *--------------------------------------------------------------------------------
 */
static void hsur_ReadMsr(void)
{
	hsurModemStatusValue = UR2_MSR;

	if (hsurModemStatusValue & UR2_DCTS)
	{
		if (hsurModemStatusValue & UR2_CTS)
		{
			HSUR_SetRTS();
			hsurFlowCtrlHwCTSon = TRUE;
		}
		else
		{
			HSUR_ClearRTS();
			hsurFlowCtrlHwCTSon = FALSE;
		}
	}

	if (hsurModemStatusValue & UR2_DDSR)
	{
		if (hsurModemStatusValue & UR2_DSR)
		{
			HSUR_SetDTR();
		}
		else
		{
			HSUR_ClearDTR();
		}
	}

	if (hsurModemStatusValue & UR2_TERI)
	{
		if (hsurModemStatusValue & UR2_RI)
		{
			UR2_MCR |= UR2_OUT1;
			hsurModemControlValue |= UR2_OUT1;
		}
		else
		{
			UR2_MCR &= ~UR2_OUT1;
			hsurModemControlValue &= ~UR2_OUT1;
		}
	}

	if (hsurModemStatusValue & UR2_DDCD)
	{
		if (hsurModemStatusValue & UR2_DCD)
		{
			UR2_MCR |= UR2_OUT2;
			hsurModemControlValue |= UR2_OUT2;
		}
		else
		{
			UR2_MCR &= ~UR2_OUT2;
			hsurModemControlValue &= ~UR2_OUT2;
		}
	}
}


/* EXPORTED SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * void HSUR_Func(void)
 * Purpose : HSUR interrupt function which checks interrupt status.
 * Params  : None.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
void HSUR_Func(void)  
{
	U8_T far intrStatus = 0;

	intrStatus = UR2_IIR & 0x0F;

	if (intrStatus == UR2_RLS_INTR)
	{
		hsur_ReadLsr();
	}
	else if (intrStatus == UR2_RD_TRIG_INTR)
	{
		UR2_IER &= ~UR2_RDI_ENB;
		hsur_RcvrTrig();
		uart2_timeout = UART2_TIMEOUT;
		UR2_IER |= UR2_RDI_ENB;
	}
	else if (intrStatus == UR2_RD_TI_INTR)
	{
		UR2_IER &= ~UR2_RDI_ENB;
		hsur_Rcvr();
		uart2_timeout = UART2_TIMEOUT;
		UR2_IER |= UR2_RDI_ENB;
	}
	else if (intrStatus == UR2_THRE_INTR)
	{
		if (hsurFlowCtrl != UR2_FLOW_CTRL_SW )
		{
			hsur_Xmit();
		}
		else
		{
			EA = 0;
			hsurTxTransmit = 1;
			hsurTxFlag = 0;
			UR2_IER &= ~UR2_THRI_ENB;
			EA = 1;
		}
	}
	else if (intrStatus == UR2_MS_INTR)
	{
		hsur_ReadMsr();
	}
}

/*
 *--------------------------------------------------------------------------------
 * void HSUR_Setup(U16_T divisor, U8_T lCtrl, U8_T intEnb, U8_T fCtrl, U8_T mCtrl)
 * Purpose : Setup the HSUR mode. Before using the HSUR of AX11000, this function
 *           must be executed to initiate.
 * Params  : divisor - A divisor value used to calculate the baud rate of HSUR.
 *           lCtrl - Line control register value.
 *           intEnb - Interrupt enable register value.
 *           fCtrl - FIFO control register value.
 *           mCtrl - Modem control register value.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
void HSUR_Setup(U16_T divisor, U8_T lCtrl, U8_T intEnb, U8_T fCtrl, U8_T mCtrl)
{
	U16_T	 i;		  /*far*/


	for (i=0 ; i<UR2_MAX_RX_SIZE ; i++)
	{
		hsurRxBuffer[i] = 0;
	}
	for (i=0 ; i<UR2_MAX_TX_SIZE ; i++)
	{
		hsurTxBuffer[i] = 0;
	}


	hsurRxBufNum = 0;
	hsurTxBufNum = 0;
	hsurRxCount = 0;
	hsurTxCount = 0;
	hsurGetPtr = 0;
	hsurPutPtr = 0;

	switch (fCtrl & 0xC0)
	{
		case UR2_TRIG_01 :
			hsurRxTrigLvl = 1;
			break;
		case UR2_TRIG_04 :
			hsurRxTrigLvl = 4;
			break;
		case UR2_TRIG_08 :
			hsurRxTrigLvl = 8;
			break;
		case UR2_TRIG_14 :
			hsurRxTrigLvl = 14;
			break;
	}
	

	UR2_LCR = UR2_DLAB_ENB;
	UR2_DLL = (U8_T)(divisor & 0x00FF);
	UR2_DLH = (U8_T)((divisor & 0xFF00) >> 8);
	UR2_LCR &= ~UR2_DLAB_ENB;
	UR2_LCR = lCtrl;
	UR2_FCR = fCtrl;

	 

#if   HSUR_RS485_ENABLE
	UR2_MCR = (mCtrl | UR2_RS485_RECEIVE);
#else
	UR2_MCR = mCtrl;
#endif


	 

	UR2_IER  =  intEnb;			/* ! */

//	test_run(10);
	

	hsurLineControlValue = lCtrl;
	hsurFifoControlValue = fCtrl;
	hsurModemControlValue = mCtrl;

	

}
/*
 *--------------------------------------------------------------------------------
 * S8_T HSUR_GetChar(void)
 * Purpose : Getting one byte data from the software receiver buffer,
 *           which stores data received from a serial bus.
 * Params  : None.
 * Returns : ch - one byte character in buffer.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
S8_T HSUR_GetChar(void)
{
	U8_T	far ch = 0;
    
	while (hsurRxCount == 0) ;
	
	ch = hsurRxBuffer[hsurGetPtr];
	EA = 0;
	hsurGetPtr ++;
	hsurRxCount --;
	if (hsurGetPtr == UR2_MAX_RX_SIZE)
		hsurGetPtr = 0;
	EA = 1;

	if ((hsurFlowCtrl != UR2_FLOW_CTRL_NO) && (hsurFlowOn))
	{
		if (hsurRxCount <= UR2_FLOW_LO_WATERMARK)
		{
			hsurFlowOn = FALSE;

			if (hsurFlowCtrl == UR2_FLOW_CTRL_SW)
			{
				UR2_THR = FLOW_SW_CONTINUOUS;
			}
			else if (hsurFlowCtrl == UR2_FLOW_CTRL_HW)
			{
				HSUR_SetRTS();
			}
			else if (hsurFlowCtrl == UR2_FLOW_CTRL_X)
			{
				UR2_THR = ASCII_XON;
			}
		}
	}

	return ch;
}

/*
 *--------------------------------------------------------------------------------
 * S8_T HSUR_PutChar(S8_T ch)
 * Purpose : Putting  one byte data into the software transmitter buffer,
 *           which stores data that be sent to a serial bus.
 * Params  : ch - one byte data will be put into buffer.
 * Returns : ch - the same data value will be returned.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
S8_T HSUR_PutChar(S8_T ch)
{
	U16_T	far tIdleStart = 0;
	U16_T	far tIdleStop = 0;

	if (hsurTxCount >= UR2_MAX_TX_SIZE)
	{
//		printd("U2-TX-Full\r\n");
		return FALSE;
	}

	if (hsurFlowCtrl == UR2_FLOW_CTRL_SW)
	{
		UR2_THR = ch;
		hsurTxState = 1;

		if (hsurFlowCtrl == UR2_FLOW_CTRL_SW)
		{
			tIdleStart = xTickCount;
			while (hsurTxTransmit == 0)
			{
				tIdleStop =xTickCount;
				if (((tIdleStop - tIdleStart) / SWTIMER_COUNT_SECOND) >= 3)
				{
//					PRINTD(DEBUG_MSG, ("Can not transmit in UR2_FLOW_CTRL_SW because of no UR2_THRI_INTR\n\r"));
				}
			}
		
			tIdleStart = xTickCount;
			while (hsurTxState == 1)
			{
				tIdleStop = xTickCount;
				if (((tIdleStop - tIdleStart) / SWTIMER_COUNT_SECOND) >= 3)
				{
//					PRINTD(DEBUG_MSG, ("Do not receive any flow control character in UR2_FLOW_CTRL_SW\n\r"));
				}
			}
	
			HSUR_TxBufFlowControl();
			hsurTxTransmit = 0;
		}
	}
	else
	{
		UR2_IER &= ~UR2_THRI_ENB;		
		hsurTxBuffer[hsurPutPtr] = ch;
		hsurPutPtr ++;
		hsurTxCount ++;

		if (hsurPutPtr == UR2_MAX_TX_SIZE)
			hsurPutPtr = 0;
	}

	UR2_IER |= UR2_THRI_ENB;    /* trigger hardware interrupt if hw FIFO empty */

#if UR2_APP_FLOW_CTRL
	if (hsurTxCount >= UR2_FLOW_HI_WATERMARK)
		return FALSE;
	else
		return TRUE;
#else
	return ch;
#endif
}

/*
* -----------------------------------------------------------------------------
 * void HSUR_InitValue(void)
 * Purpose : Initiating all globe value in this driver function.
 * Params  : None.
 * Returns : None.
 * Note    : None.
 * ----------------------------------------------------------------------------
 */
void HSUR_InitValue(void)
{
	U8_T	far sysClk = 0;
	U16_T	far i;

	for (i=0 ; i<UR2_MAX_RX_SIZE ; i++)
	{
		hsurRxBuffer[i] = 0;
	}
	for (i=0 ; i<UR2_MAX_TX_SIZE ; i++)
	{
		hsurTxBuffer[i] = 0;
	}

	hsurRxBufNum = 0;
	hsurTxBufNum = 0;
	hsurRxCount = 0;
	hsurTxCount = 0;
	hsurGetPtr = 0;
	hsurPutPtr = 0;

			 /* what's it? */
	sysClk = CSREPR & 0xC0;
	switch (sysClk)
	{
		case SCS_100M :
//			P3 = 0x10;
			break;
		case SCS_50M :
//			P3 = 0x50;
			break;
		case SCS_25M :
//			P3 = 0x25;
			break;
		default :
//			P3 = 0xAA;
			break;
	}



} /* End of UART_Init */

/*
 *--------------------------------------------------------------------------------
 * S8_T HSUR_GetCharNb(void)
 * Purpose : Getting data from the software receiver buffer, which stores data 
 *           received from a serial bus. This function is similar to HSUR_GetChar,
 *           but this function only check buffer one time.
 * Params  : None.
 * Returns : ch - one byte data in buffer will be returned if having.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
//S16_T HSUR_GetCharNb(void)
S8_T HSUR_GetCharNb(void)
{
	S8_T far ch = 0;

	UR2_IER &= ~UR2_RDI_ENB;
 
	if (hsurRxCount > 0)
	{
		ch = hsurRxBuffer[hsurGetPtr];		
		hsurGetPtr++;
		hsurRxCount --;
		if (hsurGetPtr == UR2_MAX_RX_SIZE)
			hsurGetPtr = 0;

		if ((hsurFlowCtrl != UR2_FLOW_CTRL_NO) && (hsurFlowOn))
		{
			if (hsurRxCount <= UR2_FLOW_LO_WATERMARK)
			{
				hsurFlowOn = FALSE;

				if (hsurFlowCtrl == UR2_FLOW_CTRL_SW)
				{
					UR2_THR = FLOW_SW_CONTINUOUS;
				}
				else if (hsurFlowCtrl == UR2_FLOW_CTRL_HW)
				{
					HSUR_SetRTS();
				}
				else if (hsurFlowCtrl == UR2_FLOW_CTRL_X)
				{
					UR2_THR = ASCII_XON;
				}
			}
		}

		UR2_IER |= UR2_RDI_ENB;
		return ch;
	}
	else
	{
		UR2_IER |= UR2_RDI_ENB;
	
		return -1;
       // return 1000;
	}
}

/*
 * ----------------------------------------------------------------------------
 * U16_T HSUR_GetRxBufCount(void)
 * Purpose : Getting the remain character number in UART2 Rx buffer.
 * Params  : none
 * Returns : hsurRxCount - the number of remain character in UART2 Rx buffer.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
U16_T HSUR_GetRxBufCount(void)
{
	return hsurRxCount;
}

/*
 * ----------------------------------------------------------------------------
 * void HSUR_SetFlowControl(U8_T mode)
 * Purpose : Setting the UART2 flow control mode.
 * Params  : mode - flow control mode.
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void HSUR_SetFlowControl(U8_T mode)
{
	hsurFlowCtrl = mode;

	if (hsurFlowCtrl == UR2_FLOW_CTRL_SW)
	{
		hsurTxTransmit = 0;
		hsurTxFlag = 0;
		hsurFlowOn = 0;
	}
}

/*
 * ----------------------------------------------------------------------------
 * BOOL HSUR_CheckTxComplete(void)
 * Purpose : Check the hardware FIFO empty and software Tx buffer empty
 * Params  : none
 * Returns : TRUE - both empty.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
BOOL HSUR_CheckTxComplete(void)
{
	if ((UR2_LSR & UR2_THRE) && (hsurTxCount == 0))
		return TRUE;
	else
		return FALSE;
}


/*
 * ----------------------------------------------------------------------------
 * void HSUR_RxBufFlowControl(void)
 * Purpose : Check the receiving buffer space and return the flow control character.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void HSUR_RxBufFlowControl(void)
{
	U8_T	far charFlowCtrl = 0;

	if (hsurFlowCtrl == UR2_FLOW_CTRL_SW)
	{
		if (hsurRxCount >= UR2_MAX_RX_SIZE)
		{
			charFlowCtrl = FLOW_SW_ERROR;
		}
		else if (hsurRxCount >= UR2_FLOW_HI_WATERMARK)
		{
			hsurFlowOn = TRUE;
			charFlowCtrl = FLOW_SW_WAIT;
		}
		else if ((hsurFlowOn) && (hsurRxCount > UR2_FLOW_LO_WATERMARK))
		{
			charFlowCtrl = FLOW_SW_WAIT;
		}
		else if ((hsurFlowOn) && (hsurRxCount <= UR2_FLOW_LO_WATERMARK))
		{
			hsurFlowOn = FALSE;
			charFlowCtrl = FLOW_SW_CONTINUOUS;
		}
		else if (hsurFlowOn == FALSE)
		{
			charFlowCtrl = FLOW_SW_CONTINUOUS;
		}
		else
		{
			charFlowCtrl = FLOW_SW_CONTINUOUS;
		}

		UR2_THR = charFlowCtrl;
	}
	else if (hsurFlowCtrl == UR2_FLOW_CTRL_HW)
	{
		if (hsurRxCount >= UR2_FLOW_HI_WATERMARK)
		{
			hsurFlowOn = TRUE;
			UR2_MCR &= ~UR2_RTS;
		}
		else if ((hsurFlowOn) && (hsurRxCount <= UR2_FLOW_LO_WATERMARK))
		{
			hsurFlowOn = FALSE;
			UR2_MCR |= UR2_RTS;
		}
	}
	else if (hsurFlowCtrl == UR2_FLOW_CTRL_X)
	{
		if (hsurRxCount >= UR2_FLOW_HI_WATERMARK)
		{
			hsurFlowOn = TRUE;
			UR2_THR = ASCII_XOFF;
		}
		else if ((hsurFlowOn) && (hsurRxCount <= UR2_FLOW_LO_WATERMARK))
		{
			hsurFlowOn = FALSE;
			UR2_THR = ASCII_XON;
		}
	}
}

/*
 * ----------------------------------------------------------------------------
 * void HSUR_TxBufFlowControl(void)
 * Purpose : Check the transmitting flow control character.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void HSUR_TxBufFlowControl(void)
{
	U8_T	far charFlowCtrl = 0;
	U16_T	far tIdleStart = 0;
	U16_T	far tIdleStop = 0;
	
	if (hsurFlowCtrl == UR2_FLOW_CTRL_HW)
	{
		if (hsurFlowCtrlHwCTSon == TRUE)
		{
			return;
		}

		tIdleStart = xTickCount;
		while (1)
		{
			if (hsurFlowCtrlHwCTSon == TRUE)
			{
				return;
			}
			else
			{
				tIdleStop = xTickCount;

				if (((tIdleStop - tIdleStart) / SWTIMER_COUNT_SECOND) >= 1)
				{
//					PRINTD(DEBUG_MSG, ("Do not match any flow control character in UR2_FLOW_CTRL_HW\n\r"));
				}
			}
		}
	}
	else if (hsurFlowCtrl == UR2_FLOW_CTRL_X)
	{
		if (hsurFlowCtrlXoff == TRUE)
		{
			hsurFlowCtrlXoff = FALSE;
	
			tIdleStart = xTickCount;
			while (1)
			{
				if (hsurFlowCtrlXon == TRUE)
				{
					hsurFlowCtrlXon = FALSE;

					break;
				}
				else
				{
					tIdleStop = xTickCount;
					if (((tIdleStop - tIdleStart) / SWTIMER_COUNT_SECOND) >= 3)
					{
//						PRINTD(DEBUG_MSG, ("Do not match any flow control character in UR2_FLOW_CTRL_X\n\r"));
					}
				}
			}
		}
	}
	else if (hsurFlowCtrl == UR2_FLOW_CTRL_SW)
	{
		tIdleStart = xTickCount;
		while (1)
		{
			charFlowCtrl = hsurTxFlag;
			if (charFlowCtrl == FLOW_SW_CONTINUOUS)
				break;
			else if (charFlowCtrl == FLOW_SW_ERROR)
				UR2_IER &= ~UR2_THRI_ENB;
			else
			{
				tIdleStop =xTickCount;
				if (((tIdleStop - tIdleStart) / SWTIMER_COUNT_SECOND) >= 3)
				{
//					PRINTD(DEBUG_MSG, ("Do not match any flow control character in UR2_FLOW_CTRL_SW\n\r"));
				}
			}
		}
	}
}

/*
 * ----------------------------------------------------------------------------
 * void HSUR_ErrorRecovery(void)
 * Purpose : Checking the HSUR Line Status Register value of errors and
 *           re-enable interrupt of receiving and line status.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void HSUR_ErrorRecovery(void)
{
	if (hsurErrBlocking)
	{
		U8_T	far lsrVal = UR2_LSR;
		U8_T	far trash = 0;

//		printd("hsurErrBlocking = 1\n\r");
		if (lsrVal & UR2_DR)
		{
			trash = UR2_RBR;
		}
		else if (!(lsrVal & UR2_DR) && (hsurErrorCount >= 30))
		{
//			printd("clear hsurErrBlocking = 0\n\r");
			EA = 0;
			UR2_IER |= (UR2_RDI_ENB | UR2_RLSI_ENB | UR2_MSI_ENB);
			hsurErrBlocking = 0;
			hsurErrorCount = 0;
			EA = 1;
		}
	}
}

/*
 * ----------------------------------------------------------------------------
 * BOOL HSUR_SetBaudRate(U16_T divBaudRate)
 * Purpose : Setting the HSUR baudrate.
 * Params  : divBaudRate - divisor of the baudrate.
 * Returns : TRUE - setting complete.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
BOOL HSUR_SetBaudRate(U16_T divBaudRate)
{
	U8_T	far recIntrEnb = UR2_IER;

	UR2_IER = 0;
	UR2_LCR |= UR2_DLAB_ENB;
	UR2_DLL = (U8_T)(divBaudRate & 0x00FF);
	UR2_DLH = (U8_T)((divBaudRate & 0xFF00) >> 8);
	UR2_LCR &= ~UR2_DLAB_ENB;

	hsurBaudRateDivisor = divBaudRate;

	switch (CSREPR & 0xC0)
	{
		case SCS_100M :
//			P3 = 0x10;
			break;
		case SCS_50M :
//			P3 = 0x50;
			break;
		case SCS_25M :
//			P3 = 0x25;
			break;
	}

	UR2_FCR |= UR2_RXFIFO_RST | UR2_TXFIFO_RST;
	UR2_IER = recIntrEnb;

	return TRUE;
}

/*
 * ----------------------------------------------------------------------------
 * void HSUR_SetLineControl(U8_T value)
 * Purpose : Setting the HSUR Line control register with "value".
 * Params  : value - variable to be set.
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void HSUR_SetLineControl(U8_T value)
{
	U8_T	recIntrEnb = UR2_IER;

	UR2_IER = 0;
	UR2_LCR = value;
	hsurLineControlValue = value;
	UR2_IER = recIntrEnb;
}

/*
 * ----------------------------------------------------------------------------
 * void HSUR_SetFifoControl(U8_T value)
 * Purpose : Setting the HSUR FIFO control register with "value".
 * Params  : value - variable to be set.
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void HSUR_SetFifoControl(U8_T value)
{
	U8_T	far recIntrEnb = UR2_IER;

	UR2_IER = 0;
	UR2_FCR = value;
	hsurFifoControlValue = value;
	UR2_IER = recIntrEnb;
}

/*
 * ----------------------------------------------------------------------------
 * void HSUR_SetModemControl(U8_T value)
 * Purpose : Setting the HSUR Modem control register with "value".
 * Params  : value - variable to be set.
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void HSUR_SetModemControl(U8_T value)
{
	U8_T	far recIntrEnb = UR2_IER;

	UR2_IER = 0;
	UR2_MCR = value;
	hsurModemControlValue = value;
	UR2_IER = recIntrEnb;
}

/*
 * ----------------------------------------------------------------------------
 * void HSUR_SetRTS(void)
 * Purpose : Only setting the HSUR RTS bit of Modem control register.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void HSUR_SetRTS(void)
{
	U8_T	far recIntrEnb = UR2_IER;

	UR2_IER = 0;
	UR2_MCR |= UR2_RTS;
	hsurModemControlValue |= UR2_RTS;
	UR2_IER = recIntrEnb;
}

/*
 * ----------------------------------------------------------------------------
 * void HSUR_SetDTR(void)
 * Purpose : Only setting the HSUR DTR bit of Modem control register.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void HSUR_SetDTR(void)
{
	U8_T	far recIntrEnb = UR2_IER;

	UR2_IER = 0;
	UR2_MCR |= UR2_DTR;
	hsurModemControlValue |= UR2_DTR;
	UR2_IER = recIntrEnb;
}

/*
 * ----------------------------------------------------------------------------
 * void HSUR_ClearRTS(void)
 * Purpose : Only clear the HSUR RTS bit of Modem control register.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void HSUR_ClearRTS(void)
{
	UR2_MCR &= ~UR2_RTS;
	hsurModemControlValue &= ~UR2_RTS;
}

/*
 * ----------------------------------------------------------------------------
 * void HSUR_ClearDTR(void)
 * Purpose : Only clear the HSUR DTR bit of Modem control register.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void HSUR_ClearDTR(void)
{
	UR2_MCR &= ~UR2_DTR;
	hsurModemControlValue &= ~UR2_DTR;
}

/*
 * ----------------------------------------------------------------------------
 * U16_T HSUR_GetBaudRate(void)
 * Purpose : Getting the HSUR baudrate divisor.
 * Params  : none
 * Returns : divBaudRate - baudrate divisor.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
U16_T HSUR_GetBaudRate(void)
{
	U16_T	far divBaudRate = 0;

	switch (CSREPR & 0xC0)
	{
		case SCS_100M :
//			P3 = 0x10;
			UR2_LCR |= UR2_DLAB_ENB;
			switch (hsurBaudRateDivisor)
			{
				case UR2_BR100_921600 :
					divBaudRate = UR2_BR100_921600;
					break;
				case UR2_BR100_115200 :
					divBaudRate = UR2_BR100_115200;
					break;
				case UR2_BR100_57600 :
					divBaudRate = UR2_BR100_57600;
					break;
				case UR2_BR100_38400 :
					divBaudRate = UR2_BR100_38400;
					break;
				case UR2_BR100_19200 :
					divBaudRate = UR2_BR100_19200;
					break;
				case UR2_BR100_9600 :
					divBaudRate = UR2_BR100_9600;
					break;
				case UR2_BR100_7200 :
					divBaudRate = UR2_BR100_7200;
					break;
				case UR2_BR100_4800 :
					divBaudRate = UR2_BR100_4800;
					break;
				case UR2_BR100_3600 :
					divBaudRate = UR2_BR100_3600;
					break;
				case UR2_BR100_2400 :
					divBaudRate = UR2_BR100_2400;
					break;
				case UR2_BR100_1200 :
					divBaudRate = UR2_BR100_1200;
					break;
			}
			UR2_LCR &= ~UR2_DLAB_ENB;
			break;
		case SCS_50M :
//			P3 = 0x50;
			UR2_LCR |= UR2_DLAB_ENB;
			switch (hsurBaudRateDivisor)
			{
				case UR2_BR50_921600 :
					divBaudRate = UR2_BR50_921600;
					break;
				case UR2_BR50_115200 :
					divBaudRate = UR2_BR50_115200;
					break;
				case UR2_BR50_57600 :
					divBaudRate = UR2_BR50_57600;
					break;
				case UR2_BR50_38400 :
					divBaudRate = UR2_BR50_38400;
					break;
				case UR2_BR50_19200 :
					divBaudRate = UR2_BR50_19200;
					break;
				case UR2_BR50_9600 :
					divBaudRate = UR2_BR50_9600;
					break;
				case UR2_BR50_7200 :
					divBaudRate = UR2_BR50_7200;
					break;
				case UR2_BR50_4800 :
					divBaudRate = UR2_BR50_4800;
					break;
				case UR2_BR50_3600 :
					divBaudRate = UR2_BR50_3600;
					break;
				case UR2_BR50_2400 :
					divBaudRate = UR2_BR50_2400;
					break;
				case UR2_BR50_1200 :
					divBaudRate = UR2_BR50_1200;
					break;
			}
			UR2_LCR &= ~UR2_DLAB_ENB;
			break;
		case SCS_25M :
//			P3 = 0x25;
			UR2_LCR |= UR2_DLAB_ENB;
			switch (hsurBaudRateDivisor)
			{
				case UR2_BR25_921600 :
					divBaudRate = UR2_BR25_921600;
					break;
				case UR2_BR25_115200 :
					divBaudRate = UR2_BR25_115200;
					break;
				case UR2_BR25_57600 :
					divBaudRate = UR2_BR25_57600;
					break;
				case UR2_BR25_38400 :
					divBaudRate = UR2_BR25_38400;
					break;
				case UR2_BR25_19200 :
					divBaudRate = UR2_BR25_19200;
					break;
				case UR2_BR25_9600 :
					divBaudRate = UR2_BR25_9600;
					break;
				case UR2_BR25_7200 :
					divBaudRate = UR2_BR25_7200;
					break;
				case UR2_BR25_4800 :
					divBaudRate = UR2_BR25_4800;
					break;
				case UR2_BR25_3600 :
					divBaudRate = UR2_BR25_3600;
					break;
				case UR2_BR25_2400 :
					divBaudRate = UR2_BR25_2400;
					break;
				case UR2_BR25_1200 :
					divBaudRate = UR2_BR25_1200;
					break;
			}
			UR2_LCR &= ~UR2_DLAB_ENB;
			break;
	}
	
	return TRUE;
}

/*
 * ----------------------------------------------------------------------------
 * U8_T HSUR_GetLineControl(void)
 * Purpose : Getting the HSUR Line Control register variables.
 * Params  : none
 * Returns : varLineCtrl.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
U8_T HSUR_GetLineControl(void)
{
	U8_T	far varLineCtrl = 0;

	varLineCtrl = UR2_LCR;

	return varLineCtrl;
}

/*
 * ----------------------------------------------------------------------------
 * U8_T HSUR_GetFifoControl(void)
 * Purpose : Getting the HSUR FIFO Control register variables.
 * Params  : none
 * Returns : hsurFifoControlValue.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
U8_T HSUR_GetFifoControl(void)
{
	return hsurFifoControlValue;
}

/*
 * ----------------------------------------------------------------------------
 * U8_T HSUR_GetModemControl(void)
 * Purpose : Getting the HSUR Modem Control register variables.
 * Params  : none
 * Returns : hsurModemControlValue.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
U8_T HSUR_GetModemControl(void)
{
	return hsurModemControlValue;
}

/*
 * ----------------------------------------------------------------------------
 * U8_T HSUR_GetLineStatus(U8_T intrSynth)
 * Purpose : Getting the HSUR Line Status .
 * Params  : intrSynth - 1: Get LSR according to an interrupt trigger.
 *                       0: Get LSR by directly reading the register.
 * Returns : varLineStatus - Line status register variable.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
U8_T HSUR_GetLineStatus(U8_T intrSynth)
{
	U8_T	far varLineStatus = 0;

	if (intrSynth == TRUE)
		varLineStatus = hsurLineStatusValue;
	else if (intrSynth == FALSE)
		varLineStatus = UR2_LSR;

	return varLineStatus;
}

/*
 * ----------------------------------------------------------------------------
 * U8_T HSUR_GetModemStatus(U8_T intrSynth)
 * Purpose : Getting the HSUR Modem Status .
 * Params  : intrSynth - 1: Get MSR according to an interrupt trigger.
 *                       0: Get MSR by directly reading the register.
 * Returns : varModemStatus - Modem status register variable.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
U8_T HSUR_GetModemStatus(U8_T intrSynth)
{
	U8_T	far varModemStatus = 0;

	if (intrSynth == TRUE)
		varModemStatus = hsurModemStatusValue;
	else if (intrSynth == FALSE)
		varModemStatus = UR2_MSR;

	return varModemStatus;
}

/*
 * ----------------------------------------------------------------------------
 * BOOL HSUR_XonByApp(void)
 * Purpose : Application issue flow control characters Xon to driver for
 *           stopping or starting the current transfer.
 * Params  : none
 * Returns : TRUE - driver is already in Xon/Xoff flow control.
 *           FLASE - driver is not in Xon/Xoff flow control.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
BOOL HSUR_XonToApp(void)
{
	if (hsurFlowCtrl != UR2_FLOW_CTRL_X)
	{
		return FALSE;
	}

	hsurAppFlowOn = TRUE;

	return TRUE;
}

/*
 * ----------------------------------------------------------------------------
 * BOOL HSUR_XoffByApp(void)
 * Purpose : Application issue flow control characters Xoff to driver for
 *           stopping or starting the current transfer.
 * Params  : none
 * Returns : TRUE - driver is already in Xon/Xoff flow control.
 *           FLASE - driver is not in Xon/Xoff flow control.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
BOOL HSUR_XoffByApp(void)
{
	if (hsurFlowCtrl != UR2_FLOW_CTRL_X)
	{
		return FALSE;
	}

	hsurAppFlowOn = FALSE;

	return TRUE;
}
/* End of hsuart.c */
