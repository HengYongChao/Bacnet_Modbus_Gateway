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
 * Module Name : uart.c
 * Purpose     : The UART module driver. It manages the character
 *               buffer and handles the ISR. This driver includes UART0 and UART1.
 * Author      : Robin Lee
 * Date        : 2006-01-10
 * Notes       : None.
 * $Log: uart.c,v $
 * Revision 1.3  2006/05/18 02:15:34  robin6633
 * 1.Add UART1 disable definition.
 *
 * Revision 1.2  2006/05/17 08:31:32  robin6633
 * 1. Changed the default baudrate to 115200.
 *
 * Revision 1.1  2006/05/12 14:24:47  robin6633
 * no message
 *
 * Revision 1.3  2006/05/03 02:45:55  robin6633
 * Changed the the function name UART_GetBufCount()
 * to UART_GetRxBufCount() .
 *
 * Revision 1.2  2006/05/02 01:43:40  robin6633
 * Add an expanding function to get the counter value of UART software buffer.
 *
 * Revision 1.1  2006/04/07 11:39:14  robin6633
 * no message
 *
 *================================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include	"reg80390.h"
#include	"types.h"
#include	"uart.h"
#include	"ax11000_cfg.h"
#if HSUR_ENABLE
#include	"hsuart.h"
#endif
#include	"adapter_cfg.h"

// #include "Main.h"
// #include <string.h>


uart_frame rsv_msg; 			// LJ 6/11/2012


/* STATIC VARIABLE DECLARATIONS */
#if UART0_ENABLE
 U8_T		uart0_TxBuf[MAX_TX_UART0_BUF_SIZE]; //  lihengning static
static U16_T	uart0_TxHead = 0;
static U16_T	uart0_TxTail = 0;
 U16_T	uart0_TxCount = 0;
static U8_T		uart0_TxFlag = 0;
 U8_T		uart0_RxBuf[MAX_RX_UART0_BUF_SIZE];  
static U16_T	uart0_RxHead = 0;
static U16_T	uart0_RxTail = 0;
static U8_T		uart0_Mode = 0;
U16_T			uart0_RxCount = 0;
#endif

#if UART1_ENABLE
 U8_T		uart1_TxBuf[MAX_TX_UART1_BUF_SIZE]; //  lihengning static
static U16_T	uart1_TxHead = 0;
static U16_T	uart1_TxTail = 0;
 U16_T	uart1_TxCount = 0;
static U8_T		uart1_TxFlag = 0;
 U8_T		uart1_RxBuf[MAX_RX_UART1_BUF_SIZE]; //  lihengning static
static U16_T	uart1_RxHead = 0;
static U16_T	uart1_RxTail = 0;
static U8_T		uart1_Mode = 0;
U16_T uart1_RxCount = 0;
U8_T uart1_rec_size = 8;
U8_T uart1_dealwithTag = 0;
#endif
static U8_T		uartPort = 0;

U8_T far uart1_timeout = UART1_TIMEOUT;
U8_T xdata FlagSend0;

/* LOCAL SUBPROGRAM DECLARATIONS */
#if UART0_ENABLE
static void		uart0_ISR(void);
 void		uart0_Init(void);
static S8_T		uart0_PutChar(S8_T c);
static S8_T		uart0_GetKey(void);
static S8_T		UART0_NoBlockGetkey(void);
#endif
#if UART1_ENABLE
static void		uart1_ISR(void);
 void		uart1_Init(void);  //lihengning static
static S8_T		uart1_PutChar(S8_T c);
static S8_T		uart1_GetKey(void);
static S8_T		uart1_NoBlockGetkey(void);
#endif



U8_T far UartRev[8] ;
extern 	U8_T SYS_FREQUENCY_PERIOD;
extern 	U8_T SYS_FREQUENCY_PERIOD1;


U8_T far UartSend[255];
U8_T far UartRevNum=0;
U8_T far UartSendNum=0;
//U8_T far FlagRev=0;// receive finished flag 0=unfinished 1=read 2= reset
U8_T far FlagSend=0;

U8_T GetNum=0;
U8_T TypeData=0;
U8_T SerialFlag=0;

extern U8_T far Para[400];
extern unsigned char  auchCRCHi[256];
extern unsigned char  auchCRCLo[256];
extern void InitCRC16(void);
extern void CRC16_Tstat(unsigned char ch);
extern  unsigned char far  CRClo;
extern unsigned  char far  CRChi;

extern void Led_485RxD();

U8_T far begin=0;
U8_T far  buf[255]={0};
//U8_T far  buf1[255]={0};



/* LOCAL SUBPROGRAM BODIES */
#if UART0_ENABLE
/*
 * ----------------------------------------------------------------------------
 * static void UART0_ISR(void)
 * Purpose : UART0 interrupt service routine. For sending out, it puts data
 *           from software buffer into hardware serial buffer register (SBUF0).
 *           For receiving, it gets data from hardware serial buffer register
 *           (SBUF0) and stores into software buffer.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */

#if 1
static void UART0_ISR(void) interrupt 4
{
	U8_T i= 0;
	EA = 0;

	if (RI0)
	{

		uart0_RxBuf[uart0_RxCount++] = SBUF0;
		if(uart0_RxCount > MAX_RX_UART0_BUF_SIZE)
			uart0_RxCount = 0;	   
		
	 	RI0 = 0;
	} 

	if (TI0)
	{
		
		FlagSend = 1;// finishing sending flag
		TI0 = 0;


	} /* End of if(TI0) */
	
	EA = 1;
}

#endif 


/*
 * ----------------------------------------------------------------------------
 * static void uart0_Init(void)
 * Purpose : Setting operation mode of UART0 and initiating the global values.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */


static void uart0_Init(void)
{
	U8_T	sysClk = 0;
	U16_T	i;

	uart0_TxHead = 0;
	uart0_TxTail = 0;
	uart0_TxCount = 0;
	uart0_TxFlag = 0;
	uart0_RxHead = 0;
	uart0_RxTail = 0;
	uart0_RxCount = 0;
	for (i=0 ; i<MAX_TX_UART0_BUF_SIZE ; i++)
		uart0_TxBuf[i] = 0;
	for (i=0 ; i<MAX_RX_UART0_BUF_SIZE ; i++)
		uart0_RxBuf[i] = 0;

	// Initialize TIMER1 for standard 8051 UART clock
	PCON  |= 0x80;			// Disable BaudRate doubler.
	SM01  = 1;			// Use serial port 0 in mode 1 with 8-bits data.
	REN0  = 1;			// Enable UART0 receiver.
	TMOD  = 0x20;		// Use timer 1 in mode 2, 8-bit counter with auto-reload.
	uart0_Mode = 1;

	sysClk = CSREPR & 0xC0;
	switch (sysClk)
	{
		case SCS_100M :
		//	AX_DBG_LED(0x10);
			TH1 = 0xE5;		// Baud rate = 9600 @ 100MHz.
			SYS_FREQUENCY_PERIOD1 = 30;
			SYS_FREQUENCY_PERIOD = 100;
			break;
		case SCS_50M :
		//	AX_DBG_LED(0x50);
			TH1 = 0xF2;		// Baud rate = 9600 @ 50MHz.
			break;
		case SCS_25M :
		//	AX_DBG_LED(0x25);
			SYS_FREQUENCY_PERIOD1 =100;
			SYS_FREQUENCY_PERIOD = 200;
			TH1 = 0xF9;		// Baud rate = 9600 @ 25MHz.
			break;
		default :
		//	AX_DBG_LED(0xAA);
			TH1 = 0xF9;		// Baud rate = 9600 @ 25MHz.
			break;
	}

	ES0	= 1;				// Enable serial port Interrupt request
	TR1 = 1;				// Run Timer 1
	TI0 = 0;

	

} /* End of UART_Init */



/*
 * ----------------------------------------------------------------------------
 * static S8_T uart0_PutChar(S8_T c)
 * Purpose : UART0 output function. This function puts one byte data into the
 *           software character buffer.
 * Params  : c - one byte character.
 * Returns : c - one byte character.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
S8_T uart0_PutChar (S8_T c)
{
	U16_T	count = 0;

	if (c == 0xa)
	{
		do
		{
			EA = 0;
			count = uart0_TxCount; 
			EA = 1;
		} while (count == MAX_TX_UART0_BUF_SIZE);
		uart0_TxBuf[uart0_TxHead] = 0xd;
		EA = 0;
		uart0_TxCount++;
		EA = 1;
		uart0_TxHead++;
		uart0_TxHead &= MAX_TX_UART0_MASK;
	}
	do
	{
		EA = 0;
		count = uart0_TxCount; 
		EA = 1;
	} while (count == MAX_TX_UART0_BUF_SIZE);
	uart0_TxBuf[uart0_TxHead] = c;
	EA = 0;
	uart0_TxCount++;
	EA = 1;
	uart0_TxHead++;
	uart0_TxHead &= MAX_TX_UART0_MASK;

	if (!uart0_TxFlag)
	{
		uart0_TxFlag = 1;
		SBUF0 = uart0_TxBuf[uart0_TxTail];
	}

	return c;

}

/*
 * ----------------------------------------------------------------------------
 * static S8_T uart0_GetKey(void)
 * Purpose : UART0 input function. This function replies one byte data from the
 *           software character buffer.
 * Params  : none
 * Returns : c - one byte character.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
static S8_T uart0_GetKey (void)
{
    /* NAMING CONSTANT DECLARATIONS */

    /* LOCAL VARIABLE DECLARATIONS */
    S8_T	c = 0;
    /* BODY */
	while(uart0_RxCount == 0);
	EA = 0;
	uart0_RxCount--;
	EA = 1;
	c = uart0_RxBuf[uart0_RxTail];
	uart0_RxTail++;
	uart0_RxTail &= MAX_RX_UART0_MASK;
	return c;
}

/*
 * ----------------------------------------------------------------------------
 * static S8_T uart0_NoBlockGetkey(void)
 * Purpose : UART0 input function. This function replies one byte data from the
 *           software character buffer. But it only check the buffer one time.
 *           If no data, it will reply a FALSE condition.
 * Params  : none
 * Returns : c - one byte character.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
static S8_T UART0_NoBlockGetkey (void)
{
    char c = 0;

	if (uart0_RxCount !=0 )
	{
		EA = 0;
		uart0_RxCount--;
		EA = 1;
		c = uart0_RxBuf[uart0_RxTail];
		uart0_RxTail++;
		uart0_RxTail &= MAX_RX_UART0_MASK;
		return c;
	}
	else
	{
		return FALSE;
	}
}
#endif


#if UART1_ENABLE
////////////////////////////////////////////////////////////////////////////////
/*
 * ----------------------------------------------------------------------------
 * static void UART1_ISR(void)
 * Purpose : UART1 interrupt service routine. For sending out, it puts data
 *           from software buffer into hardware serial buffer register (SBUF1).
 *           For receiving, it gets data from hardware serial buffer register
 *           (SBUF1) and stores into software buffer.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
#if 1
static void uart1_ISR(void) interrupt 6
{
	EA = 0;


	if(RI1)
	{
		uart1_RxBuf[uart1_RxCount++] = SBUF1;

		if(uart1_RxCount >= MAX_RX_UART1_BUF_SIZE)
			uart1_RxCount = 0;
		

		RI1 = 0;

		uart1_timeout = 5;	 // reveice data  timer = 20		  (3)

	} 
	if (TI1)
	{
		EA = 0;
		FlagSend = 1;// finishing sending flag
		TI1 = 0;
	} /* End of if(TI0) */
   EA = 1;
}  

#endif 

/*
 * ----------------------------------------------------------------------------
 * static void uart1_Init(void)
 * Purpose : Setting operation mode of UART1 and initiating the global values.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
static void uart1_Init(void)
{
	U8_T	sysClk = 0;
	U16_T	i;

	uart1_TxHead = 0;
	uart1_TxTail = 0;
	uart1_TxCount = 0;
	uart1_TxFlag = 0;
	uart1_RxHead = 0;
	uart1_RxTail = 0;
	uart1_RxCount = 0;
	for (i=0 ; i<MAX_TX_UART1_BUF_SIZE ; i++)
		uart1_TxBuf[i] = 0;
	for (i=0 ; i<MAX_RX_UART1_BUF_SIZE ; i++)
		uart1_RxBuf[i] = 0;

	// Initialize TIMER1 for standard 8051 UART clock
	PCON  |= 0x00;			// Disable BaudRate doubler. 	 9600    
	SM10  = 0;
	SM11  = 1;			// Use serial port 1 in mode 1 with 8-bits data.
	REN1  = 1;			// Enable UART1 receiver.
	TMOD  = 0x20;		// Use timer 1 in mode 2, 8-bit counter with auto-reload.
	uart1_Mode = 1;

	sysClk = CSREPR & 0xC0;
	switch (sysClk)
	{							 /* UART1 rate = 57600,only work on 100Mhz*/
		case SCS_100M :
			TH1 = 0xe5;		// Baud rate = 57600 @ 100MHz.	   	 19200=0xE5,57600=0xF7
			break;
		case SCS_50M :
			TH1 = 0xF2;		// Baud rate = 9600 @ 50MHz.
			break;
		case SCS_25M :
			TH1 = 0xF9;		// Baud rate = 9600 @ 25MHz.
			break;
		default :
			TH1 = 0xF9;		// Baud rate = 9600 @ 25MHz.
			break;
	}

	ES1	= 1;				// Enable serial port Interrupt request
	TR1 = 1;				// Run Timer 1
	TI1 = 0;

}

/*
 * ----------------------------------------------------------------------------
 * static S8_T uart1_PutChar(S8_T c)
 * Purpose : UART1 output function. This function puts one byte data into the
 *           software character buffer.
 * Params  : c - one byte character.
 * Returns : c - one byte character.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
static S8_T uart1_PutChar(S8_T c)
{
	U16_T	count = 0;

	if (c == 0xa)
	{
		do
		{
			EA = 0;
			count = uart1_TxCount; 
			EA = 1;
		} while (count == MAX_TX_UART1_BUF_SIZE);
		uart1_TxBuf[uart1_TxHead] = 0xd;
		EA = 0;
		uart1_TxCount++;
		EA = 1;
		uart1_TxHead++;
		uart1_TxHead &= MAX_TX_UART1_MASK;
	}
	do
	{
		EA = 0;
		count = uart1_TxCount; 
		EA = 1;
	} while (count == MAX_TX_UART1_BUF_SIZE);
	uart1_TxBuf[uart1_TxHead] = c;
	EA = 0;
	uart1_TxCount++;
	EA = 1;
	uart1_TxHead++;
	uart1_TxHead &= MAX_TX_UART1_MASK;

	if (!uart1_TxFlag)
	{
		uart1_TxFlag = 1;
		SBUF1 = uart1_TxBuf[uart1_TxTail];
	}
	
	return c;

}

/*
 * ----------------------------------------------------------------------------
 * static S8_T uart1_GetKey(void)
 * Purpose : UART1 input function. This function replies one byte data from the
 *           software character buffer.
 * Params  : none
 * Returns : c - one byte character.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
static S8_T uart1_GetKey (void)
{
    /* NAMING CONSTANT DECLARATIONS */

    /* LOCAL VARIABLE DECLARATIONS */
    S8_T c;
    /* BODY */
	while(uart1_RxCount==0);
	EA = 0;
	uart1_RxCount--;
	EA = 1;
	c = uart1_RxBuf[uart1_RxTail];
	uart1_RxTail++;
	uart1_RxTail &= MAX_RX_UART1_MASK;
	return c;
}

/*
 * ----------------------------------------------------------------------------
 * static S8_T uart1_NoBlockGetkey(void)
 * Purpose : UART1 input function. This function replies one byte data from the
 *           software character buffer. But it only check the buffer one time.
 *           If no data, it will reply a FALSE condition.
 * Params  : none
 * Returns : c - one byte character.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
static S8_T uart1_NoBlockGetkey (void)
{
    char c = 0;

	if (uart1_RxCount !=0 )
	{
		EA = 0;
		uart1_RxCount--;
		EA = 1;
		c = uart1_RxBuf[uart1_RxTail];
		uart1_RxTail++;
		uart1_RxTail &= MAX_RX_UART1_MASK;
		return c;
	}
	else
	{
		return FALSE;
	}
}
#endif


/* EXPORTED SUBPROGRAM BODIES */

/*
 * ----------------------------------------------------------------------------
 * S8_T _getkey (void)
 * Purpose : UART getkey function. This function is the entry of getting
 *           characters from software buffer of system's UART ports,
 *           UART0, UART1 and HSUR. 
 * Params  : none
 * Returns : ch - one byte character.
 * Note    : The default UART port is UART0.
 * ----------------------------------------------------------------------------
 */
S8_T _getkey (void)
{
	S8_T	ch = 0;

	ch = HSUR_GetChar();
	return ch;
}

/*
 * ----------------------------------------------------------------------------
 * S8_T putchar(S8_T c)
 * Purpose : UART putchar function. This function is the entry of putting
 *           characters into software buffer of system's UART ports,
 *           UART0, UART1 and HSUR. 
 * Params  : c - one byte character to be put.
 * Returns : ch - the same character to be replied.
 * Note    : The default UART port is UART0.
 * ----------------------------------------------------------------------------
 */
S8_T putchar(S8_T c)
{
	S8_T	ch = 0;

	ch = HSUR_PutChar(c);
	return ch;
}

/*
 * ----------------------------------------------------------------------------
 * void UART_Init(void)
 * Purpose : UART initial function. It will call a real initial function
 *           corresponding to the used UART port.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void UART_Init(U8_T port)
{
	if (port == 0)
	{
		uart0_Init();
	}
	else if (port == 1)
	{
	 	uart1_Init();
	}
	else if (port == 2)
	{
		HSUR_InitValue();
		HSUR_Setup(0x0010, (UR2_CHAR_8|UR2_STOP_10), (UR2_RDI_ENB|UR2_RLSI_ENB|UR2_MSI_ENB),
		(UR2_FIFO_MODE|UR2_RXFIFO_RST|UR2_TXFIFO_RST|UR2_TRIG_08), UR2_DTR | UR2_RTS);
	}
	
}

/*
 * ----------------------------------------------------------------------------
 * S8_T NOBLK_getkey (void)
 * Purpose : UART no blocking getkey function with one checked. This function
 *           is the entry of getting characters from software buffer of
 *           system's UART ports, UART0, UART1 and HSUR.
 * Params  : none
 * Returns : ch - one byte character.
 * Note    : The default UART port is UART0.
 * ----------------------------------------------------------------------------
 */
S8_T NOBLK_getkey (void)
{
    S8_T	c = 0;

	c = HSUR_GetCharNb();

	return c;
}

/*
 * ----------------------------------------------------------------------------
 * BOOL UART_ParityChk(S8_T checkByte)
 * Purpose : UART parity checked function in one byte transfer.
 * Params  : checkByte - one byte character.
 * Returns : TRUE - odd parity ; FALSE - even parity.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
BOOL UART_ParityChk(S8_T checkByte)
{
	U8_T	oneNum = 0;
	U16_T	i;

	oneNum = 0;
	for (i=0 ; i<=7 ; i++)
	{
		if (checkByte & (BIT0<<i))
		{
			oneNum ++;
		}
	}
	if ((oneNum % 2) == 0)
		return FALSE;		// if '1' number is even, return 0
	else
		return TRUE;		// if '1' number is odd, return 1
}

#if UART0_ENABLE
/*
 * ----------------------------------------------------------------------------
 * void UART0_SetMode(U8_T mode)
 * Purpose : Setting operation mode of UART0.
 * Params  : mode - operation mode (0~3).
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void UART0_SetMode(U8_T mode)
{
	uart0_Mode = mode;
}
#endif

#if UART1_ENABLE
/*
 * ----------------------------------------------------------------------------
 * void UART1_SetMode(U8_T mode)
 * Purpose : Setting operation mode of UART0.
 * Params  : mode - operation mode (0~3).
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
void UART1_SetMode(U8_T mode)
{
	uart1_Mode = mode;
}
#endif

/*
 * ----------------------------------------------------------------------------
 * BOOL UART_SetPort(U8_T portNum)
 * Purpose : Setting which UART port will be used.
 * Params  : portNum - uart port number (0~2).
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
BOOL UART_SetPort(U8_T portNum)
{
	uartPort = portNum & 0x03;
	UART_Init(0);
	UART_Init(1);
	return TRUE;
}

/*
 * ----------------------------------------------------------------------------
 * U16_T UART_GetRxBufCount(void)
 * Purpose : Getting the remain character number in UART Rx buffer.
 * Params  : none
 * Returns : bufCount - the number of remain character in UART software RX buffer.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
U16_T UART_GetRxBufCount(void)
{
	U16_T	bufCount = 0;

	bufCount = HSUR_GetRxBufCount();

	return bufCount;
}

/*
 * ----------------------------------------------------------------------------
 * void PMM_Uart0Init(void)
 * Purpose : Initiating the UART0 to work in power management mode.
 * Params  : none
 * Returns : none
 * Note    : none
 * ----------------------------------------------------------------------------
 */
#if UART_PMM_ENABLE
void PMM_Uart0Init(void)
{
	U16_T	i;

	uart0_TxHead = 0;
	uart0_TxTail = 0;
	uart0_TxCount = 0;
	uart0_TxFlag = 0;
	uart0_RxHead = 0;
	uart0_RxTail = 0;
	uart0_RxCount = 0;
	for (i=0 ; i<MAX_TX_UART0_BUF_SIZE ; i++)
		uart0_TxBuf[i] = 0;
	for (i=0 ; i<MAX_RX_UART0_BUF_SIZE ; i++)
		uart0_RxBuf[i] = 0;

	// Initialize TIMER1 for standard 8051 UART clock
	PCON  = BIT7;		// Enable BaudRate doubler.
	SM01  = 1;			// Use serial port 0 in mode 1 with 8-bits data.
	REN0  = 1;			// Enable UART0 receiver.
	TMOD  = 0x20;		// Use timer 1 in mode 2, 8-bit counter with auto-reload.

	TH1 = 0xFE;			// Baud rate = 1200 @ 25MHz.

	ES0	= 1;				// Enable serial port Interrupt request
	TR1 = 1;				// Run Timer 1
	TI0 = 0;

}
#endif


/*
 * ----------------------------------------------------------------------------
 * S8_T GetKey(void)
 * Purpose : UART0 input function. This function replies one byte data from the
 *           software character buffer.
 * Params  : none
 * Returns : c - one byte character.
 * Note    : none
 * ----------------------------------------------------------------------------
 */
S8_T GetKey(void)
{
    S8_T	ch = 0;
   
   	ch = uart0_GetKey();
	return ch;
}
/* End of uart.c */

/* End of uart.c */
