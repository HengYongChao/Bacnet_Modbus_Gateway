/*
 ******************************************************************************
 *     Copyright (c) 2006	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
/*=============================================================================
 * Module Name: MODBUSTCPd.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: MODBUSTCPd.c,v $
 * Revision 1.1.1.1  2006/06/20 05:50:28  borbin
 * no message
 *
 * Revision 1.2  2006/02/24 00:33:06  borbin
 * no message
 *
 * Revision 1.1.1.1  2006/02/23 00:55:10  borbin
 * no message
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "reg80390.h"
#include "modbusTCP.h"
#include "filesys1.h"
#include "adapter.h"
#include "tcpip.h"
#include "mstimer.h"
#include "uart.h"
#if (UART0_ENABLE)
  #include "printd.h"
#endif
#include <string.h>
#include "flash.h"
#include "hsuart.h"
#include  "delay.h"
#include "schedule.h"
#include "8563.h"
#include "../main/main.h"
#include "../i2c/e2prom.h"
#include "scan.h"
#include "../gsm/gsm.h"

/* NAMING CONSTANT DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static MODBUSTCP_SERVER_CONN XDATA MODBUSTCP_Connects[MAX_MODBUSTCP_CONNECT];

/* LOCAL SUBPROGRAM DECLARATIONS */
static U8_T MODBUSTCP_NewConfig(void);
static void	MODBUSTCP_DivideHtmlFile(MODBUSTCP_SERVER_CONN XDATA*, U8_T);
extern void Led_ReSet();


/* LOCAL VARIABLES */
static U8_T XDATA PostTable[MAX_POST_COUNT];
static U8_T XDATA PostCount = 0;
static U8_T MODBUSTCP_InterfaceId = 0;
static U8_T far send_tcp[300]={0};

/* GLOBAL VARIABLES */
U8_T  far Setime[8];
//U8_T  SetimeFlag;
U8_T ChangeFlash=0;

U8_T TsataId ;	  // from modbustcp
U8_T bytesN ;	//Mupitlewrite byte number

unsigned char dbuf[6]={0,0,0,0,0,0};
U8_T  far Para[400]; 
U8_T  far  Parame[400] = {
0, 0x01 , 0 , 1 , 0 , 0x01 , 0, 0,  0, 12 ,	//fireware version :69.11
0, 69 ,0 , 9,0, 0x64 ,0 ,0x1a ,0, 0xFF ,		//hardware	version :26  [bootloader version :14]
0, 0xFF ,0, 20, 0, 0 ,  0, 0xFF, 0 , 0x0e ,
0, 0xFF ,0,0x01, 0, 24, 0, 2,  0, 1, 			//16 register for ISP state
0, 1, 0, 1, 0, 3, 0, 1, 0, 1, 
0, 1, 0, 1 ,0, 1, 0, 1, 0, 1, 
0, 1, 0, 1 ,0, 1, 0 ,1, 0, 1, 
0, 1 ,0, 1, 0, 1 ,0, 1, 0, 1, 
0, 1, 0, 1 ,0, 1, 0, 1, 0, 1, 
0, 1, 0, 1, 0, 1 ,0 ,1, 0, 1 ,
0, 1, 0, 1, 0, 1, 0, 1, 0 ,1 ,
0, 1, 0, 1 ,0, 1, 0, 1, 0, 1 ,
0 ,1, 0, 1, 0, 1, 0, 1 ,0, 1,
0 ,1, 0, 1, 0, 1, 0, 1, 0, 1, 
0 ,1, 0, 1, 0, 1, 0, 1, 0, 1 ,
0 ,1 ,0, 1, 0, 1 ,0, 1, 0, 1, 
0 ,1, 0 ,1, 0, 1, 0, 1, 0, 1 ,
0 ,1 ,0 ,1, 0, 1, 0, 1, 0, 1, 
0 ,0 ,0, 1, 0, 1, 0, 0, 0, 1 ,	//Modified by Evan, for MAC addrss changeable.
0 ,1, 0, 1, 0, 1 ,0, 1, 0, 4 ,    

0, 0, 0 ,1, 0, 0xFF ,0 ,0xFF, 0,0xFF,
0 ,0xFF ,0, 0, 0 ,0xC0, 0, 0xA8, 0, 0, 
0, 0x03, 0, 0xFF ,0,0xFF ,0, 0xFF, 0 ,0, 
0, 0xC0, 0, 0xA8, 0, 0, 0 ,4, 0, 0xFF, 
0x17 ,0x71, 0, 0xFF, 0, 0xFF ,0, 0xFF ,0, 0xFF, 
0xFF, 0xFF ,0xFF, 0xFF, 0xFF, 0xFF ,0, 0xFF, 0xFF,0xFF, 
0 ,0xFF ,0, 0xFF, 0, 0xFF, 0, 0xFF ,0, 0, 
0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 
0 ,0, 0 ,0, 0 ,0 ,0, 1, 0 ,1 ,
0 ,1 ,0, 1, 0, 1, 0, 1 ,0, 1, 
0 ,1, 0, 1, 0, 1, 0, 1, 0, 1, 
0, 1, 0 ,1 ,0, 1 ,0, 1 ,0, 1, 
0, 1, 0, 1, 0, 1, 0, 1 ,0, 1 ,
0, 1, 0, 1, 0 ,1, 0, 1 ,0 ,1 ,
0, 1, 0, 1, 0, 1 ,0 ,1, 0 ,1, 
0, 1, 0, 1, 0 ,0, 
0 ,0x41, 0, 0x37,0, 0x15, 0, 0x0F , //time.windows.com 
0 ,0x3D ,0 ,0x81 ,0, 0x2A ,0 ,0x2C,  //ntp.fudan.edu.cn  
0, 1 ,0 ,1, 0, 1 ,0, 1,
0 ,1 ,0 ,1 ,0 ,1, 0, 1, 0, 1 ,
0, 1 ,0 ,1, 0 ,1, 0, 1, 0, 0,     
} ;  


extern U8_T bacnet_id ;

U16_T sessonid;
U16_T sessonlen;

extern enum ledState LED;
extern U8_T Sever_id;
//sbit En=P3^6;
unsigned char far CRClo;
unsigned char far CRChi;
 /**const code**/
U32_T address=0;
unsigned char   auchCRCHi[256] = {
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,//12
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
} ;	

unsigned char  auchCRCLo[256] = {

0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04,
0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8,
0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10,
0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C,
0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0,
0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C,
0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,//12
0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54,
0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98,
0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40

} ;


//U8_T far *mycode = 0x20000;
//U32_T far codepage = 0;

extern void  Led_485Send();

void assign(U8_T i, U16_T v)
{
	dbuf[i] = (U8_T)(v >> 8);
	dbuf[i+1] = (U8_T)v;
}

void SetTransID(U16_T id)  { assign(0, id);  }
void SetProtoID(U16_T id)  { assign(2, id);  }
void SetLength(U16_T len)  { assign(4, len); }

void Set_transaction_ID(U8_T *str, U16_T len)
{
	U8_T i;

    SetTransID(sessonid) ;
    SetProtoID(0) ;
    SetLength(3 + len);
    for(i = 0; i < 6; i++)
		str[i] = dbuf[i];		
}


void InitCRC16(void)
{
	CRClo = 0xFF;
	CRChi = 0xFF;
}

//-------------------crc16_tstat ---------------------
// calculate crc with one byte
void CRC16_Tstat(unsigned char ch)
{
	unsigned char far uIndex ;
	uIndex = CRChi ^ ch ; // calculate the CRC 
	CRChi = CRClo ^ auchCRCHi[uIndex] ;
	CRClo = auchCRCLo[uIndex] ;
}



// Used to verify the CRC on a received packet.
unsigned int CRC16(unsigned char *puchMsg, unsigned char usDataLen)
{
	unsigned int uchCRCHi = 0xFF ; // high byte of CRC initialized 
	unsigned char uchCRCLo = 0xFF ; // low byte of CRC initialized 
	unsigned char uIndex ; // will index into CRC lookup table 
	while (usDataLen--) // pass through message buffer 
	{
		uIndex = uchCRCHi ^ *puchMsg++ ; // calculate the CRC 
		uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ;
		uchCRCLo = auchCRCLo[uIndex] ;
	}
	return (uchCRCHi << 8 | uchCRCLo);
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: MODBUSTCP_Init
 * Purpose: Initialize MODBUSTCP server. 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MODBUSTCP_Init(void)
{
	U8_T	i;
	U16_T   port;

	for (i = 0; i < MAX_MODBUSTCP_CONNECT; i++)
	{
		MODBUSTCP_Connects[i].State = MODBUSTCP_STATE_FREE;
		MODBUSTCP_Connects[i].FileId = 0xff;
	}

	port=(((U16_T)Para[240]) << 8) | (Para[241]) ;
	MODBUSTCP_InterfaceId = TCPIP_Bind(MODBUSTCP_NewConn, MODBUSTCP_Event, MODBUSTCP_Receive);
	TCPIP_TcpListen(port ,MODBUSTCP_InterfaceId);

//  TCPIP_TcpListen(MODBUSTCP_SERVER_PORT ,MODBUSTCP_InterfaceId);
//	FSYS_Init();

	
//	Uart0_Tx("ModbusTCP init.",15);

}

/*
 * ----------------------------------------------------------------------------
 * Function Name: MODBUSTCP_NewConn
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T MODBUSTCP_NewConn(U32_T XDATA* pip, U16_T remotePort, U8_T socket)
{
	U8_T	i;

	for (i = 0; i < MAX_MODBUSTCP_CONNECT; i++)
	{
		if (MODBUSTCP_Connects[i].State == MODBUSTCP_STATE_FREE)
		{
			MODBUSTCP_Connects[i].State = MODBUSTCP_STATE_ACTIVE;
			MODBUSTCP_Connects[i].Timer = (U16_T)SWTIMER_Tick();
			MODBUSTCP_Connects[i].Ip = *pip;
			MODBUSTCP_Connects[i].Port = remotePort;
			MODBUSTCP_Connects[i].TcpSocket = socket;

			return i;
		}
	}
	return TCPIP_NO_NEW_CONN;
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: MODBUSTCP_Event
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MODBUSTCP_Event(U8_T id, U8_T event)
{
	U8_T	fileId = MODBUSTCP_Connects[id].FileId;


	 MODBUSTCP_Connects[id].State = event;


} /* End of MODBUSTCP_Event() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: MODBUSTCP_Receive
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void MODBUSTCP_Receive(U8_T XDATA* pData, U16_T length, U8_T conn_id)
{
	MODBUSTCP_SERVER_CONN XDATA*	pMODBUSTCPConn = &MODBUSTCP_Connects[conn_id];

	U32_T i;
    U16_T z;
	U8_T NTFlag=0;
    U16_T SeCount; 
    U16_T StartAdd;  
    U8_T RealNum;
    U8_T errFlag = 0;

	U8_T temp;
	U16_T loop;
    U8_T far temp_number;
	U8_T far temp_address;    
	U8_T far send_buffer;

	sessonid = ((U16_T)pData[0] << 8) | pData[1];


  	if((pData[UIP_HEAD] == Para[13]) || (pData[UIP_HEAD] == 0xff))//Address of NetControl 
	{   
		StartAdd = (pData[UIP_HEAD + 2] << 8) + pData[UIP_HEAD + 3]; //起始地址
		if(pData[UIP_HEAD + 1] == READ_VARIABLES)
		{
			RealNum = 2 * pData[UIP_HEAD + 5];//有效字节数目
		}
		else if((pData[UIP_HEAD + 1] == WRITE_VARIABLES) || (pData[UIP_HEAD + 1] == MULTIPLE_WRITE))
		{
			RealNum = 6;
		}

		/*if (pData[UIP_HEAD+1] == DEEPSCAN) //scan
		{    
			send_tcp[UIP_HEAD] = pData[UIP_HEAD];
		  	send_tcp[UIP_HEAD+1] = DEEPSCAN;
			send_tcp[UIP_HEAD+2] = Para[13];
			NTFlag = 5;
		}	
		else*/
	    if(pData[UIP_HEAD + 1] == 0x19) //scan Tsnet
		{
			TcpSocket_ME = pMODBUSTCPConn->TcpSocket;
			LED = S485_OK;

		    Sever_Order = SERVER_TCPIP;
			Sever_id = pData[UIP_HEAD];
			TcpIp_Scan = 1;
		    InitCRC16();				 
			SeCount = length - 6;
			StartAdd = 0;
				 
 			for(z = 0; z < SeCount; z++) 
            { 
		        send_tcp[StartAdd++] = pData[UIP_HEAD+z];									   
                CRC16_Tstat(pData[UIP_HEAD+z]);
            }
			send_tcp[StartAdd++] = CRChi;
		    send_tcp[StartAdd++] = CRClo;

			Tx_To_Tstat(send_tcp, StartAdd);
		}
	    else if(pData[UIP_HEAD+1] == READ_VARIABLES)  //读命令
		{
			NTFlag = 1;   
			send_tcp[UIP_HEAD] = pData[UIP_HEAD];
			send_tcp[UIP_HEAD + 1] = pData[UIP_HEAD + 1];
			send_tcp[UIP_HEAD + 2] = RealNum;	
			for(loop = 0; loop < pData[UIP_HEAD + 5]; loop++)
			{
				if((StartAdd + loop) < MODBUS_TIMER_ADDRESS) //前200个register
				{ 
					send_tcp[UIP_HEAD + 3 + loop * 2] = Para[(StartAdd + loop) * 2] ;
				    send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = Para[(StartAdd + loop) * 2 + 1];//6+3开始
				}//前 200个 1对2 ，以后1对1 
				else if((StartAdd + loop) >= MODBUS_TIMER_ADDRESS) 
				{
					/*	add schedule by chelsea								*/						
					if(StartAdd + loop >= MODBUS_TIMER_ADDRESS && StartAdd + loop < MODBUS_TIMER_ADDRESS + 8)
					{	 
					//  YEAR  MONTH  WEEK DATE  HOUR  MINUTE  SECOND 
						send_tcp[UIP_HEAD + 3 + loop * 2] = 0;
						temp = StartAdd + loop - MODBUS_TIMER_ADDRESS;
						if(temp == 7)	send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = Time.UN.Current.sec;	
						else if(temp == 6)	send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = Time.UN.Current.min;
						else if(temp == 5)	send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = Time.UN.Current.hour;
						else if(temp == 4)	send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = Time.UN.Current.day;
						else if(temp == 3)	send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = Time.UN.Current.dayofweek;
						else if(temp == 2)	send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = Time.UN.Current.month;
						else if(temp == 1)	send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = Time.UN.Current.year;
						else if(temp == 0)	send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = Time.UN.Current.centary;		
					}
					else if( StartAdd + loop >= MODBUS_WR_DESCRIP_FIRST && StartAdd + loop < MODBUS_WR_DESCRIP_LAST)
					{
						temp_number = (StartAdd + loop - MODBUS_WR_DESCRIP_FIRST) / WR_DESCRIPTION_SIZE;
						temp_address = (StartAdd + loop - MODBUS_WR_DESCRIP_FIRST) % WR_DESCRIPTION_SIZE;
		
						send_buffer = WR_Roution[temp_number].UN.all[temp_address];
					    if(temp_address == WR_DESCRIPTION_SIZE - 1 && send_buffer != 0xff)
						{
							if((send_buffer & 0x80) == 0)
							{
								if(GetBit(temp_number,wr_state_index))
									send_buffer |= 0x40;
								else
									send_buffer &= 0xbf;
							}
							if(GetBit(temp_number,holiday1_state_index))
								send_buffer |= 0x20;
							else
								send_buffer &= 0xdf;
							if(GetBit(temp_number,holiday2_state_index))
								send_buffer |= 0x10;
							else
								send_buffer &= 0xef;
						}
						
						send_tcp[UIP_HEAD + 3 + loop * 2] = 0;	
						send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = send_buffer;	
						
					}
					else if( StartAdd + loop >= MODBUS_AR_DESCRIP_FIRST && StartAdd + loop < MODBUS_AR_DESCRIP_LAST)
					{
						temp_number = (StartAdd + loop - MODBUS_AR_DESCRIP_FIRST) / AR_DESCRIPTION_SIZE;    // line
						temp_address = (StartAdd + loop - MODBUS_AR_DESCRIP_FIRST) % AR_DESCRIPTION_SIZE;
													
						send_buffer = AR_Roution[temp_number].UN.all[temp_address];
	
						if(temp_address == AR_DESCRIPTION_SIZE - 1)
						{
							if((send_buffer & 0x80) == 0)
							{
								if(GetBit(temp_number,ar_state_index))
								send_buffer |= 0x40;
								else
								send_buffer &= 0xbf;
							}
						}
						send_tcp[UIP_HEAD + 3 + loop * 2] = 0;	
						send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = send_buffer;	
						
					}
					else if( StartAdd + loop>= MODBUS_ID_FIRST && StartAdd < MODBUS_ID_LAST)
					{
						temp_number = (StartAdd + loop- MODBUS_ID_FIRST) / ID_SIZE;
						temp_address = (StartAdd + loop - MODBUS_ID_FIRST) % ID_SIZE;
						send_buffer = ID_Config[temp_number].all[temp_address];
		
						if(temp_address == ID_SIZE - 1 && send_buffer != 0xff)
						{
							if((send_buffer & 0x80) == 0)
							{
								if(GetBit(temp_number,output_state_index))
								send_buffer |= 0x40;
								else
								send_buffer &= 0xbf;
							}
							if(GetBit(temp_number,schedual1_state_index))
							send_buffer |= 0x20;
							else
							send_buffer &= 0xdf;
							if(GetBit(temp_number,schedual2_state_index))
							send_buffer |= 0x10;
							else
							send_buffer &= 0xef;
						}
		
						send_tcp[UIP_HEAD + 3 + loop * 2] = 0;	
						send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = send_buffer;	
					}
					else if( StartAdd + loop >= MODBUS_AR_TIME_FIRST && StartAdd + loop < MODBUS_WR_ONTIME_FIRST )
					{
						temp_number = (StartAdd + loop - MODBUS_AR_TIME_FIRST) / AR_TIME_SIZE;
						temp_address = (StartAdd + loop - MODBUS_AR_TIME_FIRST) % AR_TIME_SIZE;
		
						send_buffer = AR_Roution[temp_number].Time[temp_address];
		
						send_tcp[UIP_HEAD + 3 + loop * 2] = 0;	
						send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = send_buffer;	
					}
					else if( StartAdd + loop >= MODBUS_WR_ONTIME_FIRST && StartAdd + loop < MODBUS_WR_OFFTIME_FIRST )
					{
						temp_number = 	(StartAdd + loop - MODBUS_WR_ONTIME_FIRST) / WR_TIME_SIZE;		
						temp_address = (StartAdd + loop - MODBUS_WR_ONTIME_FIRST) % WR_TIME_SIZE;
						send_buffer = WR_Roution[temp_number].OnTime[temp_address];
						send_tcp[UIP_HEAD + 3 + loop * 2] = 0;	
						send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = send_buffer;	
					}
					else if( StartAdd + loop >= MODBUS_WR_OFFTIME_FIRST && StartAdd + loop < MODBUS_WR_OFFTIME_LAST )
					{
						// --- send first byte -------------			
						temp_number = (StartAdd + loop - MODBUS_WR_OFFTIME_FIRST) / WR_TIME_SIZE;
						temp_address = (StartAdd + loop - MODBUS_WR_OFFTIME_FIRST) % WR_TIME_SIZE;
		
						send_buffer = WR_Roution[temp_number].OffTime[temp_address];

						send_tcp[UIP_HEAD + 3 + loop * 2] = 0;	
						send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = send_buffer;				
					}
					else if((StartAdd + loop) == MODBUS_SCAN_DB_CTR)			  
					{
						send_tcp[UIP_HEAD + 3 + loop * 2] = 0;	
						send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = db_ctr;		// tsata count
					}
					else if(((StartAdd + loop) >= MODBUS_SCAN_DB_START) && ((StartAdd + loop) < MODBUS_SCAN_DB_LAST))
					{
						temp_number = (StartAdd + loop - MODBUS_SCAN_DB_START) / SCAN_DB_SIZE;
						temp_address = (StartAdd + loop - MODBUS_SCAN_DB_START) % SCAN_DB_SIZE;
						if(temp_address == 0)
						{
							send_buffer = scan_db[temp_number].id;
						}
						else
						{
							send_buffer = (U8_T)(scan_db[temp_number].sn >> (8 * temp_address - 8));
						}
						send_tcp[UIP_HEAD + 3 + loop * 2] = 0;	
						send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = send_buffer;
					}

					else if(((StartAdd + loop) >= MODBUS_GSM_START) && ((StartAdd + loop) < MODBUS_GSM_LAST))
					{
						temp_number = StartAdd + loop - MODBUS_GSM_START;
						send_tcp[UIP_HEAD + 3 + loop * 2] = 0;	
						send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = phoneNumber[temp_number];					 // LJ
					}

//				else if(StartAdd + loop == MODBUS_DYNDNS_ENABLE)
//				{
//					send_tcp[UIP_HEAD + 3 + loop * 2] = 0;
//					send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = dyndns_enable;
//				}
//				else if(StartAdd + loop == MODBUS_DYNDNS_PROVIDER)
//				{
//					send_tcp[UIP_HEAD + 3 + loop * 2] = 0;
//					send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = dyndns_provider;
//				}
//				else if(StartAdd + loop == MODBUS_DYNDNS_CHECK_IP_EVERY)
//				{
//					send_tcp[UIP_HEAD + 3 + loop * 2] = 0;
//					send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = check_ip_every;
//				}
//				else if(StartAdd + loop == MODBUS_DYNDNS_FORCE_UPDATE_EVERY)
//				{
//					send_tcp[UIP_HEAD + 3 + loop * 2] = 0;
//					send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = force_update_every;
//				}
//				else if((StartAdd + loop >= MODBUS_DYNDNS_DOMAIN_NAME_START) && (StartAdd + loop < MODBUS_DYNDNS_DOMAIN_NAME_END))
//				{
//					send_tcp[UIP_HEAD + 3 + loop * 2] = 0;
//					send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = dyndns_domain_name[StartAdd + loop - MODBUS_DYNDNS_DOMAIN_NAME_START];
//				}
//				else if((StartAdd + loop >= MODBUS_DYNDNS_USERNAME_START) && (StartAdd + loop < MODBUS_DYNDNS_USERNAME_END))
//				{
//					send_tcp[UIP_HEAD + 3 + loop * 2] = 0;
//					send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = dyndns_username[StartAdd + loop - MODBUS_DYNDNS_USERNAME_START];
//				}
//				else if((StartAdd + loop >= MODBUS_DYNDNS_PASSWORD_START) && (StartAdd + loop < MODBUS_DYNDNS_PASSWORD_END))
//				{
//					send_tcp[UIP_HEAD + 3 + loop * 2] = 0;
//					send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = dyndns_password[StartAdd + loop - MODBUS_DYNDNS_PASSWORD_START];
//				}

//				else if(StartAdd + loop == MODBUS_PING_START)
//				{
//					send_tcp[UIP_HEAD + 3 + loop * 2] = 0;
//					send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = test_uip_len;//ping_enable;
//				}
//
//				else if((StartAdd + loop >= MODBUS_TEST_PING_BUF_START) && (StartAdd + loop < MODBUS_TEST_PING_BUF_END))
//				{
//					send_tcp[UIP_HEAD + 3 + loop * 2] = 0;
//					send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = test_uip_buf[StartAdd + loop - MODBUS_TEST_PING_BUF_START];//ping_enable;
//				}


/*-------------------------  read select 485 id  ----------------------------------------*/
//					else if(((StartAdd + loop) >= MODBUS_BACNET_START) && ((StartAdd + loop) < MODBUS_BACNET_LAST))
//				    {
//						send_tcp[UIP_HEAD] = pData[UIP_HEAD];
//						send_tcp[UIP_HEAD + 1] = pData[UIP_HEAD + 1];
//						send_tcp[UIP_HEAD + 2] = 0x02;
//						send_tcp[UIP_HEAD + 3] = 0x00;
//						send_tcp[UIP_HEAD + 4] = bacnet_id;
//					}

					else if(StartAdd == 0xee10) //for ISP read address of 0xee10
					{  
						RealNum = 2;
					  	send_tcp[UIP_HEAD] = uip_appdata[UIP_HEAD];//地址
					  	send_tcp[UIP_HEAD+1]= READ_VARIABLES;//命令
					  	send_tcp[UIP_HEAD+2]= RealNum;
					  	send_tcp[UIP_HEAD+3] = send_tcp[UIP_HEAD+4]=0;//有效数据00				
					}
					else
					{
						send_tcp[UIP_HEAD + 3 + loop * 2] = 0;	
						send_tcp[UIP_HEAD + 3 + loop * 2 + 1] = 1;
					}						
				} 
			}
		} 
		else if(pData[UIP_HEAD + 1] == WRITE_VARIABLES) //write: 1.write to flash 2.rite to buffer Para[]1 3.send_tcp
		{			  
			NTFlag = 2;
			if(StartAdd < 200)
			{
				if(StartAdd == 15) // clear flash to zero
				{
					if(((pData[UIP_HEAD + 4] << 8) | pData[UIP_HEAD + 5]) == 0x55)
					{
						memset(WR_Roution, 0, MAX_WR * WR_STRUCT_LENGTH);
						memset(AR_Roution, 0, MAX_AR * AR_STRUCT_LENGTH);
						memset(ID_Config, 0, MAX_ID * ID_SIZE);

						memset(scan_db, 0, SCAN_DB_SIZE * MAX_ID);
						init_scan();

						Para[30] = 0;
						Para[31] = 0;
						ChangeFlash = 2;
					}
				}
				else if(StartAdd == 106)
				{
					if(Para[213] != pData[UIP_HEAD + 5])
					{
						Para[213] = pData[UIP_HEAD + 5];
					}
					ChangeIP = 1;
					ChangeFlash = 2;
				}
				else if((StartAdd >= 107) && (StartAdd <= 120)) //IP change ,reset cpu
				{
					if(Para[213] != 1)//static ip mode
					{
						Para[2*StartAdd] = pData[UIP_HEAD + 4]; 	//write to bufffer array high bit
						Para[2*StartAdd + 1] = pData[UIP_HEAD + 5];	//write to bufffer array low bit
						ChangeFlash = 2;
						ChangeIP = 1;
					}
				}
				else
				{
					Para[2*StartAdd] = pData[UIP_HEAD + 4]; 	//write to bufffer array high bit
					Para[2*StartAdd + 1] = pData[UIP_HEAD + 5];	//write to bufffer array low bit
					ChangeFlash = 2;
				}
			}
			else if((StartAdd >= SCHEDUAL_MODBUS_ADDRESS) && (StartAdd < SCHEDUAL_MODBUS_ADDRESS + 8))
			{
				switch(StartAdd - SCHEDUAL_MODBUS_ADDRESS)
				{
					case 0: //century
						if(pData[UIP_HEAD + 5] == 19)
						{
							Set_Clock(PCF_MON, Time.UN.Current.month | 0x80);
						}
						else if(pData[UIP_HEAD + 5] == 20)
						{
							Set_Clock(PCF_MON, Time.UN.Current.month & 0x7f);
						}
						break;
					case 1: //year
						Set_Clock(PCF_YEAR, pData[UIP_HEAD + 5]);
						break;
					case 2: //month
						if(Time.UN.Current.centary == 19)
						{
							Set_Clock(PCF_MON, pData[UIP_HEAD + 5] | 0x80);
						}
						else if(Time.UN.Current.centary == 20)
						{
							Set_Clock(PCF_MON, pData[UIP_HEAD + 5] & 0x7f);
						}
						break;
					case 3:
						Set_Clock(PCF_WEEK, pData[UIP_HEAD + 5]);
						break;
					case 4: //date
						Set_Clock(PCF_DAY, pData[UIP_HEAD + 5]);
						break;
					case 5: //hour
						Set_Clock(PCF_HOUR, pData[UIP_HEAD + 5]);
						break;
					case 6: //minute
						Set_Clock(PCF_MIN, pData[UIP_HEAD + 5]);
						break;
					case 7: //second
						Set_Clock(PCF_SEC, pData[UIP_HEAD + 5]);
						break;
				}
			}
											
			if(StartAdd != 0x10)//for ISP, not respond if address == 0x10
			{ 
				for (i = 0; i < 6; i++)			
					send_tcp[i + UIP_HEAD] = uip_appdata[i + UIP_HEAD];
			}
			else  //for ISP
			{
				//if(uip_appdata[UIP_HEAD+5] == 0x7f)AX11000_SoftReboot();
			}
		}
		else if(pData[UIP_HEAD+1] == MULTIPLE_WRITE) //multi_write
		{
			ChangeFlash = 1;
			StartAdd = (pData[UIP_HEAD+2] << 8) + pData[UIP_HEAD + 3]; //起始地址
			if((StartAdd == 100) && (pData[UIP_HEAD + 6] == 12))
			{
				Para[201] = pData[UIP_HEAD + 8];
				Para[203] = pData[UIP_HEAD + 10];
				Para[205] = pData[UIP_HEAD + 12];
				Para[207] = pData[UIP_HEAD + 14];
				Para[209] = pData[UIP_HEAD + 16];
				Para[211] = pData[UIP_HEAD + 18];

				mac_change_enable = 1;
				ChangeIP = 1;
			}
		    else if(StartAdd < SCHEDUAL_MODBUS_ADDRESS)
			{
				for(i = 0; i < pData[UIP_HEAD + 6]; i++)
				{
					if((StartAdd < 100) || (StartAdd > 105))  
						Para[2 * StartAdd + i] = pData[UIP_HEAD + i];

					ChangeIP = 1;
				} 
			}
			else if(StartAdd == SCHEDUAL_MODBUS_ADDRESS) //200th register ,write time 
			{
//				if((StartAdd - SCHEDUAL_MODBUS_ADDRESS) % 8 == 0)
//					memcpy(Time.UN.Setime,&pData[UIP_HEAD + 7], 8);
				if(pData[UIP_HEAD + 5] == 8)
				{
					if(pData[UIP_HEAD + 5] == pData[UIP_HEAD + 6])
					{
						Time.UN.Setime[7] = pData[UIP_HEAD + 14];
						Time.UN.Setime[6] = pData[UIP_HEAD + 13];
						Time.UN.Setime[5] = pData[UIP_HEAD + 12];
						Time.UN.Setime[4] = pData[UIP_HEAD + 11];
						Time.UN.Setime[3] = pData[UIP_HEAD + 10];
						if(pData[UIP_HEAD + 7] == 19)
							pData[UIP_HEAD + 9] |= 0x80;
						else
							pData[UIP_HEAD + 9] &= 0x7f;
						Time.UN.Setime[2] = pData[UIP_HEAD + 9];
						Time.UN.Setime[1] = pData[UIP_HEAD + 8];
						Time.UN.Setime[0] = pData[UIP_HEAD + 7];
					}
					else
					{
						Time.UN.Setime[7] = pData[UIP_HEAD + 22];
						Time.UN.Setime[6] = pData[UIP_HEAD + 20];
						Time.UN.Setime[5] = pData[UIP_HEAD + 18];
						Time.UN.Setime[4] = pData[UIP_HEAD + 16];
						Time.UN.Setime[3] = pData[UIP_HEAD + 14];
						if(pData[UIP_HEAD + 8] == 19)
							pData[UIP_HEAD + 12] |= 0x80;
						else
							pData[UIP_HEAD + 12] &= 0x7f;
						Time.UN.Setime[2] = pData[UIP_HEAD + 12];
						Time.UN.Setime[1] = pData[UIP_HEAD + 10];
						Time.UN.Setime[0] = pData[UIP_HEAD + 8];
					}
					Initial_Clock();
				}
			}
	      	else if ((StartAdd >= MODBUS_WR_DESCRIP_FIRST)&&(StartAdd < MODBUS_WR_DESCRIP_LAST)) //weekly
	       	{								
				if((StartAdd - MODBUS_WR_DESCRIP_FIRST) % WR_DESCRIPTION_SIZE == 0)
			 	{
			 		i = (StartAdd - MODBUS_WR_DESCRIP_FIRST) / WR_DESCRIPTION_SIZE;
					memcpy(WR_Roution[i].UN.all,&pData[UIP_HEAD + 7],WR_DESCRIPTION_SIZE);
			 	}
	       	}
	  		else if(StartAdd < MODBUS_AR_DESCRIP_LAST && StartAdd >= MODBUS_AR_DESCRIP_FIRST)
			{
				if((StartAdd - MODBUS_AR_DESCRIP_FIRST) % AR_DESCRIPTION_SIZE == 0)
				{
					i = (StartAdd - MODBUS_AR_DESCRIP_FIRST) / AR_DESCRIPTION_SIZE;		 
					memcpy(AR_Roution[i].UN.all,&pData[UIP_HEAD + 7],AR_DESCRIPTION_SIZE);
				}
			}
			else if(StartAdd < MODBUS_ID_LAST && StartAdd >= MODBUS_ID_FIRST)
			{
				if((StartAdd - MODBUS_ID_FIRST) % ID_SIZE == 0)
				{
					i = (StartAdd - MODBUS_ID_FIRST) / ID_SIZE;
					memcpy(ID_Config[i].all,&pData[UIP_HEAD + 7],ID_SIZE);					
				}
			}
			else if(StartAdd < MODBUS_AR_TIME_LAST && StartAdd >= MODBUS_AR_TIME_FIRST)
			{
				if((StartAdd - MODBUS_AR_TIME_FIRST) % AR_TIME_SIZE == 0)
				{
					i = (StartAdd - MODBUS_AR_TIME_FIRST) / AR_TIME_SIZE;			
					memcpy(AR_Roution[i].Time,&pData[UIP_HEAD + 7],AR_TIME_SIZE);
				}
			}
			else if(StartAdd < MODBUS_WR_ONTIME_LAST && StartAdd >= MODBUS_WR_ONTIME_FIRST)
			{
				if((StartAdd - MODBUS_WR_ONTIME_FIRST) % WR_TIME_SIZE == 0)
				{
					i = (StartAdd - MODBUS_WR_ONTIME_FIRST) / WR_TIME_SIZE;
				
					memcpy(WR_Roution[i].OnTime,&pData[UIP_HEAD + 7],WR_TIME_SIZE);
				}
			}
			else if(StartAdd < MODBUS_WR_OFFTIME_LAST && StartAdd >= MODBUS_WR_OFFTIME_FIRST)
			{
				if((StartAdd-MODBUS_WR_OFFTIME_FIRST) % WR_TIME_SIZE == 0)
				{
					i = (StartAdd - MODBUS_WR_OFFTIME_FIRST) / WR_TIME_SIZE;					
					memcpy(WR_Roution[i].OffTime,&pData[UIP_HEAD + 7],WR_TIME_SIZE);
				}
			}
			else if(StartAdd == MODBUS_GSM_START)
			{
				if(pData[UIP_HEAD + 6] == (PHONE_NUM_SIZE * 2))
				{
					phoneNumber[0] = pData[UIP_HEAD + 8];
					phoneNumber[1] = pData[UIP_HEAD + 10];
					phoneNumber[2] = pData[UIP_HEAD + 12];
					phoneNumber[3] = pData[UIP_HEAD + 14];
					phoneNumber[4] = pData[UIP_HEAD + 16];
					phoneNumber[5] = pData[UIP_HEAD + 18];
					phoneNumber[6] = pData[UIP_HEAD + 20];
					phoneNumber[7] = pData[UIP_HEAD + 22];
					phoneNumber[8] = pData[UIP_HEAD + 24];
					phoneNumber[9] = pData[UIP_HEAD + 26];
					phoneNumber[10] = pData[UIP_HEAD + 28];
					phoneNumber[11] = pData[UIP_HEAD + 30];
					phoneNumber[12] = pData[UIP_HEAD + 32];
					phoneNumber[13] = pData[UIP_HEAD + 34];
				}
				ChangeFlash = 2;
			}

			else
			{i=0;}
			
			for (i=0;i<6;i++)			
			send_tcp[i+UIP_HEAD]=pData[i+UIP_HEAD];
			NTFlag=3;
		}
	
//		sessonid = ((U16_T)pData[0] << 8) | pData[1];
		Set_transaction_ID(send_tcp, RealNum);
    
		if(NTFlag == 1)	//read
		{
			LED = Ethnet_OK;
			TCPIP_TcpSend(pMODBUSTCPConn->TcpSocket, send_tcp, RealNum+UIP_HEAD+UIP_CODE_HEAD, TCPIP_SEND_NOT_FINAL);
		}
		else if(NTFlag == 2)//single_write response byte num=6  ChangeFlash=1;
		{
			LED = Ethnet_OK;
			TCPIP_TcpSend(pMODBUSTCPConn->TcpSocket, send_tcp, RealNum+UIP_HEAD, TCPIP_SEND_NOT_FINAL);
		}
		else if(NTFlag == 3)//multi_write  ChangeFlash=1;
		{
			LED = Ethnet_OK;
			TCPIP_TcpSend(pMODBUSTCPConn->TcpSocket, send_tcp, RealNum+UIP_HEAD, TCPIP_SEND_NOT_FINAL);            
		} 
		else if(NTFlag == 5)
		{
			LED = Ethnet_OK;
			TCPIP_TcpSend(pMODBUSTCPConn->TcpSocket, send_tcp, 6+3, TCPIP_SEND_NOT_FINAL);
		}
		else
		{
			return;
		}
	}
	else
	{
		EA = 0; 

		LED = Ethnet_OK;

		TsataId = pData[UIP_HEAD];

		TcpSocket_ME = pMODBUSTCPConn->TcpSocket;
//		sessonid = ((U16_T)pData[0] << 8) | pData[1];
		if(pData[UIP_HEAD + 1] == READ_VARIABLES)
		{
			sessonlen = 2 * pData[UIP_HEAD + 5];//有效字节数目
		}
		else if((pData[UIP_HEAD + 1] == WRITE_VARIABLES) || (pData[UIP_HEAD + 1] == MULTIPLE_WRITE))
		{
			sessonlen = 6;
		}

	    Sever_Order = SERVER_TCPIP;
		Sever_id = pData[UIP_HEAD];
	
	    InitCRC16();				 
		SeCount = length - 6;
		StartAdd = 0;
			 
		for(z = 0; z < SeCount; z++) 
	    { 
	        send_tcp[StartAdd++] = pData[UIP_HEAD + z];									   
	        CRC16_Tstat(pData[UIP_HEAD + z]);
	    }
		send_tcp[StartAdd++] = CRChi;
	    send_tcp[StartAdd++] = CRClo;
	
		EA = 1;
//		Uart0_Tx(send_tcp, StartAdd);//////////////////
		Tx_To_Tstat(send_tcp, StartAdd);
	#if 0
		DELAY_Ms(40);
		Uart2_Receive();
	#endif
	
	}
} /* End of MODBUSTCP_Receive() */

/* End of MODBUSTCPd.c */
