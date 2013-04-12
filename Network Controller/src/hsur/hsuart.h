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
 * Module Name : hsuart.h
 * Purpose     : 
 * Author      : Robin Lee
 * Date        : 
 * Notes       :
 * $Log: hsuart.h,v $
 * Revision 1.14  2006/07/25 03:50:22  robin6633
 * 1.Add Xon/Xoff counter for debugging.
 *
 * Revision 1.13  2006/07/19 09:28:59  robin6633
 * 1.Reduce the transmit level to 6 in one transfer.
 *
 * Revision 1.12  2006/07/18 08:04:14  robin6633
 * 1.Fixed Tx flow control in software flow control mode.
 *
 * Revision 1.11  2006/07/13 01:36:08  robin6633
 * 1.Increase transmit size in one transfer.
 *
 * Revision 1.10  2006/06/30 06:17:47  robin6633
 * 1.Add HSUR_CheckTxComplete().
 *
 * Revision 1.9  2006/06/27 10:45:30  robin6633
 * 1.Add flow control for transmitting.
 *
 * Revision 1.8  2006/06/19 14:22:26  robin6633
 * 1.Add a definition of UR2_TX_BUF_LEVEL to
 * force transmitting more data if transmit fifo empty.
 *
 * Revision 1.7  2006/06/11 02:18:54  robin6633
 * 1.Add Xon/Xoff.
 *
 * Revision 1.6  2006/06/05 06:20:21  robin6633
 * 1.Fixed function declaration.
 *    U8_T HSUR_RxBufFlowControl(void) -> void HSUR_RxBufFlowControl(void)
 *
 * Revision 1.5  2006/06/05 01:30:51  robin6633
 * 1.Fixed software flow control and prevented the hardware FIFO overrun.
 *
 * Revision 1.4  2006/05/24 05:39:57  robin6633
 * 1.Add flow control water mark.
 *
 * Revision 1.3  2006/05/22 07:40:08  robin6633
 * 1.Increase tx/rx buffer.
 *
 * Revision 1.2  2006/05/19 03:48:45  robin6633
 * 1.Add Xon/Xoff flow control.
 * 2.Expand an external function HSUR_ChangeBaud(U8_T baud).
 *
 * Revision 1.1  2006/05/15 03:06:52  robin6633
 * no message
 *
 * Revision 1.3  2006/05/03 02:42:36  robin6633
 * Changed the the function name HSUR_GetBufCount()
 * to HSUR_GetRxBufCount() .
 *
 * Revision 1.2  2006/05/02 01:44:13  robin6633
 * Add an expanding function to get the counter value of UART2 software buffer.
 *
 * Revision 1.1  2006/04/07 11:38:18  robin6633
 * no message
 *
 * Revision 1.6  2005/11/07 08:18:56  robin6633
 * Fixed the non-block getkey function
 *
 * Revision 1.5  2005/11/01 13:15:10  robin6633
 * Add non-block getkey function
 *
 * Revision 1.4  2005/10/06 10:18:11  robin6633
 * Added UART2 for console debug.
 *
 * Revision 1.3  2005/09/27 09:16:13  robin6633
 * Add loopback test function.
 *
 * Revision 1.2  2005/09/22 03:06:20  robin6633
 * Add High Speed Uart(UART2) driver for putchar() and getkey().
 *
 * Revision 1.1  2005/08/17 06:48:03  robin6633
 * no message
 *
 *================================================================================
 */
#ifndef HSUART_H
#define HSUART_H

/* INCLUDE FILE DECLARATIONS */
#include	"printd.h"

/* NAMING CONSTANT DECLARATIONS */
#define	UR2_MAX_RX_SIZE				512
#define	UR2_MAX_TX_SIZE				512

#define	UR2_SLEEP					0
#define	UR2_WAKEUP_ENB				BIT4
#define	UR2_HFDPX					BIT6
#define	UR2_SLAVE					BIT7
#define	UR2_MASTER					BIT6|BIT7
#define	ASCII_XON					0x17
#define	ASCII_XOFF					0x19
#define FLOW_SW_CONTINUOUS			0x16
#define	FLOW_SW_WAIT				0x18
#define	FLOW_SW_ERROR				0x14
#define	UR2_FLOW_CTRL_NO			0
#define	UR2_FLOW_CTRL_SW			1
#define	UR2_FLOW_CTRL_HW			2
#define	UR2_FLOW_CTRL_X				3
#define	UR2_FLOW_HI_WATERMARK		(UR2_MAX_RX_SIZE - (UR2_MAX_RX_SIZE / 4))
#define	UR2_FLOW_LO_WATERMARK		(UR2_MAX_RX_SIZE / 4)
#define	UR2_TX_BUF_LEVEL			4
#define	UR2_APP_FLOW_CTRL			1 // flow control between application and UART2 driver.

/* Baud Rate definition */
#define	UR2_BR25_921600				0x0001
#define	UR2_BR25_115200				0x0008
#define	UR2_BR25_57600				0x0010
#define	UR2_BR25_38400				0x0018
#define	UR2_BR25_19200				0x0030
#define	UR2_BR25_9600				0x0060
#define	UR2_BR25_7200				0x0081
#define	UR2_BR25_4800				0x00C1
#define	UR2_BR25_3600				0x0101
#define	UR2_BR25_2400				0x0182
#define	UR2_BR25_1200				0x0304

#define	UR2_BR50_921600				0x0002
#define	UR2_BR50_115200				0x0010
#define	UR2_BR50_57600				0x0020
#define	UR2_BR50_38400				0x0030
#define	UR2_BR50_19200				0x0060
#define	UR2_BR50_9600				0x00C1
#define	UR2_BR50_7200				0x0101
#define	UR2_BR50_4800				0x0182
#define	UR2_BR50_3600				0x0202
#define	UR2_BR50_2400				0x0304
#define	UR2_BR50_1200				0x0607

#define	UR2_BR100_921600			0x0004
#define	UR2_BR100_115200			0x0020
#define	UR2_BR100_57600				0x0040
#define	UR2_BR100_38400				0x0060
#define	UR2_BR100_19200				0x00C1
#define	UR2_BR100_9600				0x0182
#define	UR2_BR100_7200				0x0202
#define	UR2_BR100_4800				0x0304
#define	UR2_BR100_3600				0x0405
#define	UR2_BR100_2400				0x0607
#define	UR2_BR100_1200				0x0C0E


/* MACRO DECLARATIONS */
#define	UART2_TIMEOUT	25
#define	UART1_TIMEOUT	15

/* TYPE DECLARATIONS */


/* GLOBAL VARIABLES */
#if DEBUG_DISPLAY_DIAG
extern U32_T	hsurXonCounter;
extern U32_T	hsurXoffCounter;
#endif

extern U8_T far uart2_timeout;
extern U16_T far hsurRxCount;
extern U8_T far hsurRxBuffer[UR2_MAX_RX_SIZE];

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void	HSUR_Func(void);
void	HSUR_Setup(U16_T divisor, U8_T lCtrl, U8_T intEnb, U8_T fCtrl, U8_T mCtrl);
S8_T	HSUR_GetChar(void);
S8_T	HSUR_PutChar(S8_T ch);
void	HSUR_InitValue(void);
S8_T	HSUR_GetCharNb(void);
U16_T	HSUR_GetRxBufCount(void);
void	HSUR_SetFlowControl(U8_T mode);
void	HSUR_RxBufFlowControl(void);
void	HSUR_TxBufFlowControl(void);
BOOL	HSUR_ChangeBaud(U8_T baud);
BOOL	HSUR_CheckTxComplete(void);
void    HSUR_ErrorRecovery(void);

BOOL	HSUR_SetBaudRate(U16_T divBaudRate);
void	HSUR_SetLineControl(U8_T value);
void	HSUR_SetFifoControl(U8_T value);
void	HSUR_SetModemControl(U8_T value);
void	HSUR_SetRTS(void);
void	HSUR_SetDTR(void);
void	HSUR_ClearRTS(void);
void	HSUR_ClearDTR(void);
U16_T	HSUR_GetBaudRate(void);
U8_T	HSUR_GetLineControl(void);
U8_T	HSUR_GetFifoControl(void);
U8_T	HSUR_GetModemControl(void);
U8_T	HSUR_GetLineStatus(U8_T intrSynth);
U8_T	HSUR_GetModemStatus(U8_T intrSynth);
BOOL	HSUR_XonByApp(void);
BOOL	HSUR_XoffByApp(void);

#endif /* End of HSUART_H */
