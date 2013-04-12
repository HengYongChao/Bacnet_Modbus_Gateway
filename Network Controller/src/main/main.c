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
 /*============================================================================
 * Module Name: adapter.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: adapter.c,v $
 * Revision 1.8  2006/05/23 05:22:39  robin6633
 * 1.Removed old command input.
 *
 * Revision 1.7  2006/05/23 01:53:55  robin6633
 * 1.Removed debug information from UART2.
 *
 * Revision 1.6  2006/05/22 05:45:23  robin6633
 * 1.Add DNS handle.
 *
 * Revision 1.5  2006/05/18 07:29:32  robin6633
 * 1.Enabled time counter function.
 *
 * Revision 1.4  2006/05/18 02:13:35  robin6633
 * 1.Changed DHCP initial function.
 *
 * Revision 1.3  2006/05/17 08:34:17  robin6633
 * Disabled DHCP function.
 *
 * Revision 1.2  2006/05/16 05:03:09  robin6633
 * no message
 *
 * Revision 1.1  2006/05/12 14:23:38  robin6633
 * no message
 *
 * Revision 1.2  2006/02/24 00:31:47  borbin
 * no message
 *
 * Revision 1.1.1.1  2006/02/23 00:55:10  borbin
 * no message
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "reg80390.h"
#include "main.h"
#include "adapter.h"
#include "mstimer.h"
#include "ax11000.h"
#include "interrupt.h"
#include "stoe.h"
#include "dma.h"
#include "tcpip.h"
#include "hsuart.h"
#include "printd.h"
#include "uart.h"
#include "flash.h"
#include <stdio.h>
#include <Intrins.h>

#include "../i2c/e2prom.h" 

#include "delay.h"  //lihengning

#if STOE_TRANSPARENT
//  #include "uip_arp.h"
#endif
#if (INCLUDE_DHCP_CLIENT)
  #include "dhcpc.h"
#endif
#if (INCLUDE_DNS_CLIENT)
  #include "dnsctab.h"
#endif

#include "gconfig.h"
#include "gudpbc.h"
#include "temperature.h"
#include "httpd.h"
#include "filesys.h"
#include "sntpc.h"

#include <string.h>
#include "projdefs.h"
#include "portable.h"
#include "task.h"
#include "queue.h"
#include "8563.h"

#include "schedule.h"
#include "flash_schedule.h"
#include "../USB/ch375_COM.h"
#include "../scan/scan.h"

#include "../bacnet/gudpmc.h"
#include "../include/mstp.h"
#include "../LCD/LCD.h"
#include <stdlib.h>

#include "../gsm/gsm.h"



/* NAMING CONSTANT DECLARATIONS */
#ifdef DEBUG
#define DBGMSG(A) {A}
#else
#define DBGMSG(A) {}
#endif

#define TIME_OUT_COUNTER	(250/SWTIMER_INTERVAL)  //250
#define Hardware_Rev22       22

typedef struct app_buf {
	U32_T ipaddr;
	U8_T buf[100];
	U16_T uip_len;
	U16_T PayLoadOffset;
	U8_T wait;
}APP_BUF;

APP_BUF	XDATA app_arp_buf;

/* GLOBAL VARIABLES  */
static U16_T ServerBroadcastListenPort;
static U16_T bacnetListenPort;

extern U8_T FlagIsp;
extern U8_T ChangeFlash;
extern U8_T far CRClo;
extern U8_T far CRChi;
extern U8_T data FlagSend0;
extern U8_T far FlagSend1;
extern U8_T far Parame[400]; 
extern U8_T far Para[400]; 
enum ledState LED = None;


U8_T gsm_test_cnt = 0;       // LJ test

#if 1 //lihengning    
extern U8_T  far UartRevNum;  
//extern U16_T far hsurRxCount;
extern U8_T gudpbc_InterAppId;
U8_T TcpSocket_ME;
U8_T Sever_Order = SERVER_NONE;
U8_T Sever_id;
U8_T ChangeIP = 0;
U8_T TcpIp_Scan = 0;
Time_str Time_Server = {0, 0, 0};
U8_T far mac_change_enable = 0;
#endif

#if (INCLUDE_DNS_CLIENT)
U8_T XDATA cmdDnsFlag = 0;
#endif

static U8_T UpIndex = 0;
U8_T  Hardware_Revision;


/* LOCAL SUBPROGRAM DECLARATIONS */
//static void UpdateIpSettings(U32_T);
static void CheckArpTable(void);
extern void InitCRC16(void);
extern void CRC16_Tstat(unsigned char ch);

/* LOCAL VARIABLES DECLARATIONS */
xTaskHandle xHandle1;
xTaskHandle xHandle2;
xTaskHandle xHandle3;
xTaskHandle xHandle4;
xTaskHandle xHandle5;
xTaskHandle xHandle6;
xTaskHandle xHandle7;
xTaskHandle xHandle8;
xTaskHandle xHandle9;   //LHN ADD
xTaskHandle xHandle10;
xTaskHandle xHandle11;
xTaskHandle xHandle12; 
xTaskHandle xHandle13; 	  //bacnet mstp task
xTaskHandle xHandle14; 	  //bacnet mstp task

void test_run(U8_T dat);
U8_T test[10] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};


volatile struct mstp_port_struct_t *mstp_port ;




BOOL  MODBUS_OR_BACNET_FUNCTION_SELECT_ON_UART0 ;

//extern void test_uart0_tx(U8_T buf, U8_T len);


char err485=0;
U8_T data LedSta = 0xff;
//U8_T BeatSta=0;
U8_T  far WebText[6][30]={"time.windows.com","time.stdtime.gov.tw","clock.stdtime.gov.tw ",
                           "watch.stdtime.gov.tw", "pool.ntp.org"};
U32_T far IpServer[6]={0x3b7cc454,0xdc829e48,0xda4b0482,0x7ae2c004,0x3b7cc455};

//U8_T add_mac[6]={1,2,3,4,5,6};
//extern U8_T far UartRev[255];
//extern U8_T far UartSend[255];
//extern unsigned char  auchCRCHi[256];
//extern unsigned char  auchCRCLo[256];
//extern U8_T SerialFlag;
//U16_T StartAdd_Port;
//U16_T RealNum_Port;
//extern U8_T IspFlag;
//extern U8_T far FlagRev;
//extern U8_T  SetimeFlag;
//U16_T Port_Sin_Add=0;
//extern U8_T far buf[255];
//extern U8_T far buf1[255];


void OSDelay(U8_T x)
{
	vTaskDelay(x);
}

U8_T Read_Hardware_Revision(void)
{
    
	return Para[17];

}


/*
 * ----------------------------------------------------------------------------
 * Function Name: UpdateIpSettings
 * Purpose: Update IP address, subnet mak, gateway IP address and DNS IP address 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void UpdateIpSettings(U32_T ip)
{
 	 U32_T gateWay,subnet;

	 if(ip > 0)
	 {
	 	ip = STOE_GetIPAddr();
		subnet = STOE_GetSubnetMask();
		gateWay = STOE_GetGateway();
	
		Para[215]=(U8_T)(ip>>24);
		Para[217]=(U8_T)(ip>>16);
		Para[219]=(U8_T)(ip>>8);
		Para[221]=(U8_T)(ip);
	
		Para[223]=(U8_T)(subnet>>24);
		Para[225]=(U8_T)(subnet>>16);
		Para[227]=(U8_T)(subnet>>8);
		Para[229]=(U8_T)(subnet);
	
		Para[231]=(U8_T)(gateWay>>24);
		Para[233]=(U8_T)(gateWay>>16);
		Para[235]=(U8_T)(gateWay>>8);
		Para[237]=(U8_T)(gateWay);
	}
	else
	{
		ip = (((U32_T)Para[215]) << 24) | ((U32_T)Para[217] << 16) | ((U32_T)Para[219] << 8) | (Para[221]);
		subnet = (((U32_T)Para[223]) << 24) | ((U32_T)Para[225] << 16) | ((U32_T)Para[227] << 8) | (Para[229]);
		gateWay = (((U32_T)Para[231]) << 24) | ((U32_T)Para[233] << 16) | ((U32_T)Para[235] << 8) | (Para[237]);
		
		TCPIP_SetIPAddr(ip); 
		TCPIP_SetSubnetMask(subnet);
		TCPIP_SetGateway(gateWay);
			
		STOE_SetIPAddr(ip); 
	    STOE_SetSubnetMask(subnet);
		STOE_SetGateway(gateWay);
	
	//	GCONFIG_SetServerDynamicIP(ip);						
	//	GCONFIG_WriteConfigData();
	//	GUDPBC_Init(ServerBroadcastListenPort);
	}

}

/*
 * ----------------------------------------------------------------------------
 * Function Name: CheckArpTable
 * Purpose: Update IP address, subnet mak, gateway IP address and DNS IP address 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void CheckArpTable(void)
{
	if (app_arp_buf.wait) 
	{
		U8_T valid = STOE_CHECK_MAC(&app_arp_buf.ipaddr);
		if (valid) 
		{
			DMA_GrantXdata(uip_buf, app_arp_buf.buf, app_arp_buf.uip_len);
			PRINTD(DEBUG_MSG ,("send out the packet from arp buffer\n\r"));
			uip_len = app_arp_buf.uip_len;
			ETH_Send(app_arp_buf.PayLoadOffset);
			uip_len = 0;
			app_arp_buf.wait = 0;
		}
	}
} /* End of CheckArpTable */



void TCPIP_Task(void)reentrant
{
   //U32_T far iP,gateWay,subnet;
//   portTickType xDelayPeriod  = ( portTickType ) 250 / portTICK_RATE_MS;//2 minutes writting flash.
   	

 #if (BOOTLDR_ISR)
	ERROR: BOOTLDR_ISR must set to '0' in non-bootloader driver.
   #endif
   #if (!AX_ETH_INT_ENABLE)
	 ERROR: Must enable ethernet module in this driver.
   #endif
	 U32_T	timeCount,preTimeCount;
   #if (INCLUDE_DHCP_CLIENT)
   	U8_T    cmdDhcpFlag = 0;
	U32_T 	dhcpTimeStart = 0;
	U32_T 	dhcpTimeStop = 0;
#endif
#if STOE_TRANSPARENT
//	U8_T xdata arptimer;
#endif

//   U8_T WhichServer;

	/* Initialize Network adapter */
	ETH_Init();

	DHCP_Init();
	//if (DHCP_Init())
	//	printd("DHCP init ok.\n\r");

#if (INCLUDE_DNS_CLIENT)
	DNSCTAB_Init(); /* include DNS table */
#endif


#if GCONFIG_EEPROM_CONFIG
	I2C_Init();
#endif
	GCONFIG_Init();

//	ServerBroadcastListenPort = GCONFIG_GetServerBroadcastListenPort();
//	printd ("ServerBroadcastListenPort = %d\n\r", ServerBroadcastListenPort);
//	ServerBroadcastListenPort = 25122;
//	GUDPBC_Init(ServerBroadcastListenPort);

#if (INCLUDE_DHCP_CLIENT)	
	if ( (Para[213] == 1) && ((GCONFIG_GetNetwork() & GCONFIG_NETWORK_DHCP_ENABLE) == GCONFIG_NETWORK_DHCP_ENABLE) )
	{
		printd("DHCP request... ");
		DHCP_Start();
#if (!STOE_TRANSPARENT)
		STOE_DisableIpFilter();
#endif
		cmdDhcpFlag = 1;
		dhcpTimeStart = SWTIMER_Tick();
	}
	else
	{
		UpdateIpSettings(0);
	}
#else
	printd("DHCP module is not included. Use static IP address\n\r");
	GCONFIG_SetServerDynamicIP(GCONFIG_GetServerStaticIP());						
	GCONFIG_WriteConfigData();
	GUDPBC_Init(ServerBroadcastListenPort);
#endif

   	ServerBroadcastListenPort = 1234; 
	GUDPBC_Init(ServerBroadcastListenPort);


	bacnetListenPort = 47808;
	GUDPMC_Init(bacnetListenPort);	   		// bacnet port


	HTTP_Init();
	FSYS_Init();

//	SNTPC_Init();
	
	ETH_Start();



//	WhichServer=Para[45]; //customer choose which server fro Sync.
//	SNTPC_Start(800, IpServer[WhichServer]);
//	should add condition if whichserver exceeds 6

	while (1)
	{
//		HSUR_ErrorRecovery(); 
  

#if (!STOE_TRANSPARENT)
		ETH_SendArpToGateway(ETH_CONTINUE_ARP_REQUEST_TO_GATEWAY_AFTER_REPLY);
#endif

		CheckArpTable();

#if (INCLUDE_DHCP_CLIENT)
		if (cmdDhcpFlag == 1)
		{			
			if (DHCP_GetState() > DHCP_IDLE_STATE)
			{
				DHCP_Send();
			}
			else
			{
			 	UpdateIpSettings(STOE_GetIPAddr());
#if (!STOE_TRANSPARENT)
				STOE_EnableIpFilter();
#endif
				cmdDhcpFlag = 0;
			}
		}
#endif

#if (STOE_GET_INTSTATUS_MODE == STOE_INTERRUPT_MODE)	/* interrupt mode */
		if (STOE_GetInterruptFlag())
		{
			STOE_ProcessInterrupt();
		}
#else	/* polling mode */
		STOE_ProcessInterrupt();
#endif

#if (!MAC_GET_INTSTATUS_MODE)
		if (MAC_GetInterruptFlag())
		{
			MAC_ProcessInterrupt();
		}
#else
		MAC_LinkSpeedChk();
#endif

		timeCount = (U16_T)SWTIMER_Tick();
		if ((timeCount- preTimeCount)>= TIME_OUT_COUNTER)
		{
			preTimeCount = timeCount;
			TCPIP_PeriodicCheck();
		}
	//	vTaskDelay(xDelayPeriod);
		
       timeCount = (U16_T)SWTIMER_Tick();
       if(Para[43]==2)
	   {
		  SNTPC_GetState();Para[43]=1;
       }

      //  SNTPC_Debug();

#if (INCLUDE_DNS_CLIENT)
		if (cmdDnsFlag == 1)
		{
			U8_T state = DNSCTAB_GetState();/* include DNS table */

			if (state == DNSC_STATE_FREE)
			{
				cmdDnsFlag = 0;
				printf ("Can not find DNS server.\n\r");
			}
			else if (state == DNSC_STATE_RESPONSED)
			{
				U32_T	ip;

				cmdDnsFlag = 0;

				if ((ip = DNSCTAB_GetIP()) == 0)
				{
					printf ("Can not find remote station via DNS server.\n\r");
				}
				else
				{
					printf ("Get IP address from DNS server : %lx\n\r", ip);
				}
			}
		}
#endif

	}
} /* End of main() */


U8_T BeatSta = 0;
volatile U8_T far LEDS _at_ 0x200000;	//LED Address > 80000, or will compete with SRAM which the range is 0-0x80000!!


void Beat_ON(void)//Set Pin low
{
	U8_T i;

//	if(Hardware_Revision >= Hardware_Rev22)
//	 {	DisPlay1 = 0;
//		DisPlay2 = 1; }
//	else {
//	DisPlay1 = 1;
//	DisPlay2 = 0;  }

 	DisPlay1 = 1;
	DisPlay2 = 0; 


	LE = 0; 
	LedSta = 0xfd;
	for(i = 0; i < 100; i++);                     	   
	LEDS = LedSta;            	                                 
	LE = 1;  
}

void Beat_OFF(void)  //Set Pin high
{
//	if(Hardware_Revision >= Hardware_Rev22)
//	 {	DisPlay1 = 0;
//		DisPlay2 = 1; }
//	else {
//	DisPlay1 = 1;
//	DisPlay2 = 0;  }
	

 	DisPlay1 = 1;
	DisPlay2 = 0; 

	LE = 0;
	LedSta = 0xff;                     	   
	LEDS = LedSta;                               
	LE = 1; 
}

void Led_EthSend(void)//Pin set low
{
//	if(Hardware_Revision >= Hardware_Rev22)
//	 {	DisPlay1 = 0;
//		DisPlay2 = 1; }
//	else {
//	DisPlay1 = 1;
//	DisPlay2 = 0;  }
	
 	DisPlay1 = 1;
	DisPlay2 = 0; 

	
	LE = 0;
	if(BeatSta == 0)
		LedSta = 0xef;
	else
		LedSta = 0xed;       	   
	LEDS = LedSta;                               
	LE = 1;                               
}



void Led_EthRxD(void) //Pin set low 
{
//	if(Hardware_Revision >= Hardware_Rev22)
//	 {	DisPlay1 = 0;
//		DisPlay2 = 1; }
//	else {
//	DisPlay1 = 1;
//	DisPlay2 = 0;  }

 	DisPlay1 = 1;
	DisPlay2 = 0; 

	LE = 0;
	if(BeatSta == 0)
		LedSta = 0xdf;  
	else  
		LedSta = 0xdd;              	   
	LEDS = LedSta; 
	LE = 1;
}

void Led_485RxD(void)//Pin set low 
{    
//	if(Hardware_Revision >= Hardware_Rev22)
//	 {	DisPlay1 = 1;
//		DisPlay2 = 0; }
//	else {
//	DisPlay1 = 0;
//	DisPlay2 = 1;  }
	
	
 	DisPlay1 = 0;
	DisPlay2 = 1; 

	LE = 0;
	LedSta = 0xbf;               	   
	LEDS = LedSta; 
	LE = 1;
}

void Led_485Send(void) //Pin set low 
{      
//	if(Hardware_Revision >= Hardware_Rev22)
//	 {	DisPlay1 = 1;
//		DisPlay2 = 0; }
//	else {
//	DisPlay1 = 0;
//	DisPlay2 = 1;  }
	
	
 	DisPlay1 = 0;
	DisPlay2 = 1; 


	LE = 0;
	LedSta = 0xdf;
	LEDS = LedSta;
	LE = 1;
}

void Led_485ERR(void) //Pin set low 
{   
//	if(Hardware_Revision >= Hardware_Rev22)
//	 {	DisPlay1 = 0;
//		DisPlay2 = 1; }
//	else {
//	DisPlay1 = 1;
//	DisPlay2 = 0;  }


 	DisPlay1 = 1;
	DisPlay2 = 0; 


	LE = 0;
	if(BeatSta == 0)
		LedSta = 0xfb;  
	else
		LedSta = 0xf9;                   	   
	LEDS = LedSta; 
	LE = 1;
}
void Led_ReSet(void)
{
//	if(Hardware_Revision >= Hardware_Rev22)
//	 {	DisPlay1 = 0;
//		DisPlay2 = 1; }
//	else {
//	DisPlay1 = 1;
//	DisPlay2 = 0;  }
	
	
 	DisPlay1 = 1;
	DisPlay2 = 0; 



	LE = 0;
	if(BeatSta == 0)
		LedSta = 0xff;  
	else
		LedSta = 0xfd;                   	   
	LEDS = LedSta; 
	LE = 1;
}



void Led_ispSet(void)
{
//	if(Hardware_Revision >= Hardware_Rev22)
//	 {	DisPlay1 = 0;
//		DisPlay2 = 1; }
//	else {
//	DisPlay1 = 1;
//	DisPlay2 = 0;  }
	
 	DisPlay1 = 1;
	DisPlay2 = 0; 
	
	LE = 0;                     	   
	LEDS = 0xfe;            	                                 
	LE = 1;  
}



/*****************************************/
/*****************************************/
/*****Uart0 routine***********************/
void Uart0_Tx(U8_T *buf,U8_T len)
{     
/*
	U8_T i;
	U16_T j;
	for(i = 0; i < len; i++)
	{ 
		SBUF0 = buf[i];
		for(j = 0; j < 1000; j++);
//		FlagSend0 = 0;
//		while(FlagSend0 == 0);
	}
*/
	U8_T i;
	for(i = 0; i < len; i++)
	{ 
		FlagSend0 = 0;
		SBUF0 = buf[i];
		while(FlagSend0 == 0);
	}

}


void Uart0_Receive(void)
{

	if(uart0_RxCount > 0)
	{

		LED = S485_OK;		
		
		if((uart0_RxBuf[0] == Para[13]) || (uart0_RxBuf[0] == 0xff))//Address of NetControl 
		{ 
			if(uart0_RxBuf[1] == 0x19) //scan Tsnet
			{
				Sever_Order = SERVER_RS232;
				Sever_id = uart0_RxBuf[0]; 
				Tx_To_Tstat(uart0_RxBuf, uart0_RxCount);			   												
			}					
			else if(uart0_RxBuf[1] == 0x1a) //scan NC
			{
				U8_T i; 
				uart0_TxCount = 0;
				uart0_TxBuf[uart0_TxCount++] = uart0_RxBuf[0];
				uart0_TxBuf[uart0_TxCount++] = 0x19;
				uart0_TxBuf[uart0_TxCount++] = Para[13];						 
				uart0_TxBuf[uart0_TxCount++] = Para[1];
				uart0_TxBuf[uart0_TxCount++] = Para[3];
				uart0_TxBuf[uart0_TxCount++] = Para[5];
				uart0_TxBuf[uart0_TxCount++] = Para[7];
				InitCRC16();
				for(i = 0; i < uart0_TxCount; i++)
					CRC16_Tstat(uart0_TxBuf[i]);
				uart0_TxBuf[uart0_TxCount++] = CRChi;
				uart0_TxBuf[uart0_TxCount++] = CRClo;				         
				Uart0_Tx(uart0_TxBuf, uart0_TxCount);	
				uart0_TxCount = 0;
			}
			else if(uart0_RxBuf[1] == read) 
			{	
				U16_T i;
				U8_T far temp_number;
				U8_T far temp_address;
				U8_T far send_buffer;
				U16_T StartAdd = (uart0_RxBuf[2] << 8) | uart0_RxBuf[3];

				uart0_TxBuf[0] = uart0_RxBuf[0];
				uart0_TxBuf[1] = uart0_RxBuf[1];
				uart0_TxBuf[2] = 2 * uart0_RxBuf[5];
				uart0_TxCount = 3 + uart0_TxBuf[2];
				for(i = 0; i < uart0_RxBuf[5]; i++)
				{
					if((StartAdd + i) < MODBUS_TIMER_ADDRESS) //200
					{  
						uart0_TxBuf[3 + 2 * i] = Para[2 * (StartAdd + i)];  
						uart0_TxBuf[4 + 2 * i] = Para[2 * (StartAdd + i) + 1];
					}
					else if(((StartAdd + i) >= MODBUS_TIMER_ADDRESS) && ((StartAdd + i) < (MODBUS_TIMER_ADDRESS + 8))) 
					{
						//  YEAR  MONTH  WEEK DATE  HOUR  MINUTE  SECOND 
						uart0_TxBuf[3 + 2 * i] = 0;
						switch(StartAdd + i - MODBUS_TIMER_ADDRESS)
						{
							case 7:
								uart0_TxBuf[4 + 2 * i] = Time.UN.Current.sec;
								break;	
							case 6:
								uart0_TxBuf[4 + 2 * i] = Time.UN.Current.min;
								break;
							case 5:
								uart0_TxBuf[4 + 2 * i] = Time.UN.Current.hour;
								break;
							case 4:
								uart0_TxBuf[4 + 2 * i] = Time.UN.Current.day;
								break;
							case 3:
								uart0_TxBuf[4 + 2 * i] = Time.UN.Current.dayofweek;
								break;
							case 2:
								uart0_TxBuf[4 + 2 * i] = Time.UN.Current.month;
								break;
							case 1:
								uart0_TxBuf[4 + 2 * i] = Time.UN.Current.year;
								break;
							case 0:
								uart0_TxBuf[4 + 2 * i] = Time.UN.Current.centary;
								break;
						}		
					}
					else if(((StartAdd + i) >= MODBUS_WR_DESCRIP_FIRST) && ((StartAdd + i) < MODBUS_WR_DESCRIP_LAST))
					{
						temp_number = (StartAdd + i - MODBUS_WR_DESCRIP_FIRST) / WR_DESCRIPTION_SIZE;
						temp_address = (StartAdd + i - MODBUS_WR_DESCRIP_FIRST) % WR_DESCRIPTION_SIZE;
						send_buffer = WR_Roution[temp_number].UN.all[temp_address];
					    if((temp_address == (WR_DESCRIPTION_SIZE - 1)) && (send_buffer != 0xff))
						{
							if((send_buffer & 0x80) == 0)
							{
								if(GetBit(temp_number, wr_state_index))
									send_buffer |= 0x40;
								else
									send_buffer &= 0xbf;
							}

							if(GetBit(temp_number, holiday1_state_index))
								send_buffer |= 0x20;
							else
								send_buffer &= 0xdf;

							if(GetBit(temp_number, holiday2_state_index))
								send_buffer |= 0x10;
							else
								send_buffer &= 0xef;
						}
						uart0_TxBuf[3 + 2 * i] = 0;	
						uart0_TxBuf[4 + 2 * i] = send_buffer;	
					}
					else if(((StartAdd + i) >= MODBUS_AR_DESCRIP_FIRST) && ((StartAdd + i) < MODBUS_AR_DESCRIP_LAST))
					{
						temp_number = (StartAdd + i - MODBUS_AR_DESCRIP_FIRST) / AR_DESCRIPTION_SIZE;    // line
						temp_address = (StartAdd + i - MODBUS_AR_DESCRIP_FIRST) % AR_DESCRIPTION_SIZE;
						send_buffer = AR_Roution[temp_number].UN.all[temp_address];

						if(temp_address == (AR_DESCRIPTION_SIZE - 1))
						{
							if((send_buffer & 0x80) == 0)
							{
								if(GetBit(temp_number, ar_state_index))
									send_buffer |= 0x40;
								else
									send_buffer &= 0xbf;
							}
						}
						uart0_TxBuf[3 + 2 * i] = 0;	
						uart0_TxBuf[4 + 2 * i] = send_buffer;	
					}
					else if(((StartAdd + i) >= MODBUS_ID_FIRST) && ((StartAdd + i) < MODBUS_ID_LAST))
					{
						temp_number = (StartAdd + i - MODBUS_ID_FIRST) / ID_SIZE;
						temp_address = (StartAdd + i - MODBUS_ID_FIRST) % ID_SIZE;
						send_buffer = ID_Config[temp_number].all[temp_address];
		
						if((temp_address == (ID_SIZE - 1)) && (send_buffer != 0xff))
						{
							if((send_buffer & 0x80) == 0)
							{
								if(GetBit(temp_number, output_state_index))
									send_buffer |= 0x40;
								else
									send_buffer &= 0xbf;
							}

							if(GetBit(temp_number, schedual1_state_index))
								send_buffer |= 0x20;
							else
								send_buffer &= 0xdf;

							if(GetBit(temp_number, schedual2_state_index))
								send_buffer |= 0x10;
							else
								send_buffer &= 0xef;
						}
						uart0_TxBuf[3 + 2 * i] = 0;	
						uart0_TxBuf[4 + 2 * i] = send_buffer;	
					}
					else if(((StartAdd + i) >= MODBUS_AR_TIME_FIRST) && ((StartAdd + i) < MODBUS_WR_ONTIME_FIRST))
					{
						temp_number = (StartAdd + i - MODBUS_AR_TIME_FIRST) / AR_TIME_SIZE;
						temp_address = (StartAdd + i - MODBUS_AR_TIME_FIRST) % AR_TIME_SIZE;
						send_buffer = AR_Roution[temp_number].Time[temp_address];
		
						uart0_TxBuf[3 + 2 * i] = 0;	
						uart0_TxBuf[4 + 2 * i] = send_buffer;
					}
					else if(((StartAdd + i) >= MODBUS_WR_ONTIME_FIRST) && ((StartAdd + i) < MODBUS_WR_OFFTIME_FIRST))
					{
						temp_number = (StartAdd + i - MODBUS_WR_ONTIME_FIRST) / WR_TIME_SIZE;		
						temp_address = (StartAdd + i - MODBUS_WR_ONTIME_FIRST) % WR_TIME_SIZE;
						send_buffer = WR_Roution[temp_number].OnTime[temp_address];
						uart0_TxBuf[3 + 2 * i] = 0;	
						uart0_TxBuf[4 + 2 * i] = send_buffer;
					}
					else if(((StartAdd + i) >= MODBUS_WR_OFFTIME_FIRST) && ((StartAdd + i) < MODBUS_WR_OFFTIME_LAST))
					{
						temp_number = (StartAdd + i - MODBUS_WR_OFFTIME_FIRST) / WR_TIME_SIZE;
						temp_address = (StartAdd + i - MODBUS_WR_OFFTIME_FIRST) % WR_TIME_SIZE;
						send_buffer = WR_Roution[temp_number].OffTime[temp_address];
						uart0_TxBuf[3 + 2 * i] = 0;	
						uart0_TxBuf[4 + 2 * i] = send_buffer;			
					}
					else if((((StartAdd + i))	>= BACNET_MODBUS_FEATURE_CHOICE_START)&&(StartAdd + i) < BACNET_MODBUS_FEATURE_CHOICE_LAST)
					{


					}

					else
					{
						uart0_TxBuf[3 + 2 * i] = 0;	
						uart0_TxBuf[4 + 2 * i] = 1;
					}						
				} 

				EA = 0;
				InitCRC16();
				for(i = 0; i < uart0_TxCount; i++)
					CRC16_Tstat(uart0_TxBuf[i]);
				uart0_TxBuf[uart0_TxCount++] = CRChi;                        
				uart0_TxBuf[uart0_TxCount++] = CRClo;
				EA = 1;

				Uart0_Tx(uart0_TxBuf, uart0_TxCount);						  					
			}
			else if(uart0_RxBuf[1] == swrite) 
			{
				U16_T StartAdd = (uart0_RxBuf[2] << 8) | uart0_RxBuf[3];
				if(StartAdd < 200)
				{
					if(StartAdd == 15) // clear flash to zero
					{
						if(((uart0_RxBuf[4] << 8) | uart0_RxBuf[5]) == 0x55)
						{
							memset(WR_Roution, 0, MAX_WR * WR_STRUCT_LENGTH);
							memset(AR_Roution, 0, MAX_AR * AR_STRUCT_LENGTH);
							memset(ID_Config, 0, MAX_ID * ID_SIZE);
							Para[30] = 0;
							Para[31] = 0;
							ChangeFlash = 1;
						}
					}
					else if(StartAdd == 106)
					{
//						if((((Para[212] << 8) | Para[213]) == 0) && (((uart0_RxBuf[4] << 8) | uart0_RxBuf[5]) != 0))
						if(((Para[212] << 8) | Para[213]) != ((uart0_RxBuf[4] << 8) | uart0_RxBuf[5]))
						{
							if(((Para[212] << 8) | Para[213]) == 0)
							{
								Para[212] = 0;
								Para[213] = 1;
							
								ChangeIP = 1;
								ChangeFlash = 2;
						
							}
							else if(((uart0_RxBuf[4] << 8) | uart0_RxBuf[5]) == 0)
							{
								Para[212] = 0;
								Para[213] = 0;

								ChangeIP = 1;
								ChangeFlash = 2;

							}
						}
					}
					else if((StartAdd >= 107) && (StartAdd <= 120)) //IP change ,reset cpu
					{
						if(((Para[212] << 8) | Para[213]) == 0)
						{
							Para[2*uart0_RxBuf[3]] = uart0_RxBuf[4]; 		//write to bufffer array high bit
							Para[2*uart0_RxBuf[3] + 1] = uart0_RxBuf[5];	//write to bufffer array low bit
							ChangeFlash = 2;
							ChangeIP = 1;
						}
					}
					else
					{
						Para[2*uart0_RxBuf[3]] = uart0_RxBuf[4]; 		//write to bufffer array high bit
						Para[2*uart0_RxBuf[3] + 1] = uart0_RxBuf[5];	//write to bufffer array low bit
						ChangeFlash = 1;
					}
				}
				else if((StartAdd >= SCHEDUAL_MODBUS_ADDRESS) && (StartAdd < (SCHEDUAL_MODBUS_ADDRESS + 8)))
				{
					switch(StartAdd - SCHEDUAL_MODBUS_ADDRESS)
					{
						case 0: //century
							if(uart0_RxBuf[5] == 19)
							{
								Set_Clock(PCF_MON, Time.UN.Current.month | 0x80);
							}
							else if(uart0_RxBuf[5] == 20)
							{
								Set_Clock(PCF_MON, Time.UN.Current.month & 0x7f);
							}
							break;
						case 1: //year
							Set_Clock(PCF_YEAR, uart0_RxBuf[5]);
							break;
						case 2: //month
							if(Time.UN.Current.centary == 19)
							{
								Set_Clock(PCF_MON, uart0_RxBuf[5] | 0x80);
							}
							else if(Time.UN.Current.centary == 20)
							{
								Set_Clock(PCF_MON, uart0_RxBuf[5] & 0x7f);
							}
							break;
						case 3:
							Set_Clock(PCF_WEEK, uart0_RxBuf[5]);
							break;
						case 4: //date
							Set_Clock(PCF_DAY, uart0_RxBuf[5]);
							break;
						case 5: //hour
							Set_Clock(PCF_HOUR, uart0_RxBuf[5]);
							break;
						case 6: //minute
							Set_Clock(PCF_MIN, uart0_RxBuf[5]);
							break;
						case 7: //second
							Set_Clock(PCF_SEC, uart0_RxBuf[5]);
							break;
					}
				}
				else
				{
					// spare
				}

				Uart0_Tx(uart0_RxBuf, uart0_RxCount);
			}
			else if(uart0_RxBuf[1] == mwrite) //multi_write
			{
				U8_T i;
				U16_T StartAdd = (uart0_RxBuf[2] << 8) | uart0_RxBuf[3];
				ChangeFlash = 1;
				if(StartAdd < SCHEDUAL_MODBUS_ADDRESS)
				{
					if((StartAdd == 100) && (uart0_RxBuf[6] == 12))
					{
						Para[201] = uart0_RxBuf[8];
						Para[203] = uart0_RxBuf[10];
						Para[205] = uart0_RxBuf[12];
						Para[207] = uart0_RxBuf[14];
						Para[209] = uart0_RxBuf[16];
						Para[211] = uart0_RxBuf[18];
		
						mac_change_enable = 1;
						ChangeIP = 1;
					}
				    else
					{
						for(i = 0; i < uart0_RxBuf[6]; i++)
						{
							if(((StartAdd + i / 2) < 100) || ((StartAdd + i / 2) > 105))  
								Para[2 * StartAdd + i] = uart0_RxBuf[7+i];

						} 

					
						if((StartAdd == 107) && (uart0_RxBuf[6] == 8)){
						ChangeIP = 1;
						ChangeFlash = 2;}
						
								
					}
				}
				else if(StartAdd == SCHEDUAL_MODBUS_ADDRESS) //200th register ,write time 
				{
//					if((StartAdd - SCHEDUAL_MODBUS_ADDRESS) % 8 == 0)
//						memcpy(Time.UN.Setime,&uart0_RxBuf[7], 8);
					if(uart0_RxBuf[5] == 8)
					{
						if(uart0_RxBuf[5] == uart0_RxBuf[6])
						{
							Time.UN.Setime[7] = uart0_RxBuf[14];
							Time.UN.Setime[6] = uart0_RxBuf[13];
							Time.UN.Setime[5] = uart0_RxBuf[12];
							Time.UN.Setime[4] = uart0_RxBuf[11];
							Time.UN.Setime[3] = uart0_RxBuf[10];
							if(uart0_RxBuf[7] == 19)
								uart0_RxBuf[9] |= 0x80;
							else
								uart0_RxBuf[9] &= 0x7f;
							Time.UN.Setime[2] = uart0_RxBuf[9];
							Time.UN.Setime[1] = uart0_RxBuf[8];
							Time.UN.Setime[0] = uart0_RxBuf[7];
						}
						else
						{
							Time.UN.Setime[7] = uart0_RxBuf[22];
							Time.UN.Setime[6] = uart0_RxBuf[20];
							Time.UN.Setime[5] = uart0_RxBuf[18];
							Time.UN.Setime[4] = uart0_RxBuf[16];
							Time.UN.Setime[3] = uart0_RxBuf[14];
							if(uart0_RxBuf[8] == 19)
								uart0_RxBuf[12] |= 0x80;
							else
								uart0_RxBuf[12] &= 0x7f;
							Time.UN.Setime[2] = uart0_RxBuf[12];
							Time.UN.Setime[1] = uart0_RxBuf[10];
							Time.UN.Setime[0] = uart0_RxBuf[8];
						}
						Initial_Clock();
					}
				}
				else if ((StartAdd >= MODBUS_WR_DESCRIP_FIRST) && (StartAdd < MODBUS_WR_DESCRIP_LAST)) //weekly
		       	{								
					if((StartAdd - MODBUS_WR_DESCRIP_FIRST) % WR_DESCRIPTION_SIZE == 0)
				 	{
				 		i = (StartAdd - MODBUS_WR_DESCRIP_FIRST) / WR_DESCRIPTION_SIZE;
						memcpy((U8_T *)&WR_Roution[i].UN.all[0], uart0_RxBuf + 7, WR_DESCRIPTION_SIZE);
				 	}
		       	}
		  		else if((StartAdd >= MODBUS_AR_DESCRIP_FIRST) && (StartAdd < MODBUS_AR_DESCRIP_LAST))
				{
					if((StartAdd - MODBUS_AR_DESCRIP_FIRST) % AR_DESCRIPTION_SIZE == 0)
					{
						i = (StartAdd - MODBUS_AR_DESCRIP_FIRST) / AR_DESCRIPTION_SIZE;		 
						memcpy((U8_T *)&AR_Roution[i].UN.all[0], uart0_RxBuf + 7, AR_DESCRIPTION_SIZE);
					}
				}
				else if((StartAdd >= MODBUS_ID_FIRST) && (StartAdd < MODBUS_ID_LAST))
				{
					if((StartAdd - MODBUS_ID_FIRST) % ID_SIZE == 0)
					{
						i = (StartAdd - MODBUS_ID_FIRST) / ID_SIZE;
						memcpy((U8_T *)&ID_Config[i].all[0], uart0_RxBuf + 7, ID_SIZE);
					}
				}
				else if((StartAdd >= MODBUS_AR_TIME_FIRST) && (StartAdd < MODBUS_AR_TIME_LAST))
				{
					if((StartAdd - MODBUS_AR_TIME_FIRST) % AR_TIME_SIZE == 0)
					{
						i = (StartAdd - MODBUS_AR_TIME_FIRST) / AR_TIME_SIZE;			
						memcpy((U8_T *)&AR_Roution[i].Time[0], uart0_RxBuf + 7, AR_TIME_SIZE);
					}
				}
				else if((StartAdd >= MODBUS_WR_ONTIME_FIRST) && (StartAdd < MODBUS_WR_ONTIME_LAST))
				{
					if((StartAdd - MODBUS_WR_ONTIME_FIRST) % WR_TIME_SIZE == 0)
					{
						i = (StartAdd - MODBUS_WR_ONTIME_FIRST) / WR_TIME_SIZE;
						memcpy((U8_T *)&WR_Roution[i].OnTime[0], uart0_RxBuf + 7, WR_TIME_SIZE);
					}
				}
				else if((StartAdd >= MODBUS_WR_OFFTIME_FIRST) && (StartAdd < MODBUS_WR_OFFTIME_LAST))
				{
					if((StartAdd - MODBUS_WR_OFFTIME_FIRST) % WR_TIME_SIZE == 0)
					{
						i = (StartAdd - MODBUS_WR_OFFTIME_FIRST) / WR_TIME_SIZE;					
						memcpy((U8_T *)&WR_Roution[i].OffTime[0], uart0_RxBuf + 7 , WR_TIME_SIZE);
					}
				}

				InitCRC16();
				for(i = 0; i < 6; i++)
				{
					uart0_TxBuf[i] = uart0_RxBuf[i];
					CRC16_Tstat(uart0_TxBuf[i]);
				}
				uart0_TxBuf[6] = CRChi;                        
				uart0_TxBuf[7] = CRClo;

				Uart0_Tx(uart0_TxBuf, 8);
			}
		}
		else
		{
			Sever_Order = SERVER_RS232;
			Sever_id = uart0_RxBuf[0];				  
			Tx_To_Tstat(uart0_RxBuf, uart0_RxCount);								 			          			 
		}

		uart0_RxCount = 0;    
	}
}


/*****************************************/
/*****************************************/
/*****Uart1 routine***********************/
void Uart1_Tx(U8_T *buf,U8_T len)
{     
	U8_T i;
	for(i = 0; i < len; i++)
	{ 
		FlagSend1 = 0;
		SBUF1 = buf[i];
		while(FlagSend1 == 0);
	}
}

U8_T forward_buffer[300];
extern U16_T sessonlen;
extern void Set_transaction_ID(U8_T *str, U16_T reg);

void Uart1_Receive(void)
{
	U16_T uart1_count = 0;

	EA = 0;
	if(uart1_RxCount)
	{
		if(Sever_Order == SERVER_TCPIP)
		{
			Set_transaction_ID(forward_buffer, sessonlen);
			uart1_count = 6;
		}

		memcpy(forward_buffer + uart1_count, uart1_RxBuf, uart1_RxCount);
		uart1_count += uart1_RxCount;
		uart1_RxCount = 0;
		EA = 1;

	//	LED = S485_OK;
	}
	else
	{
		EA = 1;
		return;
	}

	if(uart1_count)
	{
		if(Sever_Order == SERVER_TCPIP)  //Sever Order is from TCPIP
		{
			if(TcpIp_Scan == 1)
			{
				TcpIp_Scan = 0;
				TCPIP_TcpSend(TcpSocket_ME, forward_buffer, uart1_count, TCPIP_SEND_NOT_FINAL);
			}
			else
			{
				TCPIP_TcpSend(TcpSocket_ME, forward_buffer, uart1_count-2, TCPIP_SEND_NOT_FINAL);
			}
		}
		else if(Sever_Order == SERVER_RS232)
		{
			Uart0_Tx(forward_buffer, uart1_count);
		}
		else if(Sever_Order == SERVER_USB)
		{
			memcpy(UpBuf, forward_buffer, uart1_count);
			UpCtr = uart1_count;
			UpIndex = 0;
			ENDP2_NEED_UP_FLAG = 1;
		}
		else if(Sever_Order == SERVER_SCHEDULE)
		{
			if(uart1_count == 8)
			{
				U8_T i;
				InitCRC16();
				for(i = 0; i < 6; i++)
					CRC16_Tstat(forward_buffer[i]);

				if((forward_buffer[6] == CRChi) && (forward_buffer[7] == CRClo))
				{
					schedule_flag = 1;
				}
			}
		}
		else if(Sever_Order == SERVER_SCAN)
		{
			switch(scan_state)
			{
				case SCAN_BINSEARCH:
					scan_response_state = MULTIPLE_ID;
					if(uart1_count >= 9) // right
					{
						U8_T i;
						InitCRC16();
						for(i = 0; i < 7; i++)
							CRC16_Tstat(forward_buffer[i]);
		
						if((forward_buffer[7] == CRChi) && (forward_buffer[8] == CRClo))
						{
							if((forward_buffer[0] == 0xff) && (forward_buffer[1] == 0x19)) // double check it is the response for scan command
							{
								current_db.id = forward_buffer[2];
								current_db.sn = ((U32_T)forward_buffer[6] << 24) | ((U32_T)forward_buffer[5] << 16) | ((U32_T)forward_buffer[4] << 8) | forward_buffer[3];
								if(uart1_count == 9)
								{
									scan_response_state = UNIQUE_ID;
								}
								else
								{
									scan_response_state = UNIQUE_ID_FROM_MULTIPLE;
								}
							}
						}
					}
					// and none tstat in the range will wait timeout in the waitrsponse routine
					break;
				case SCAN_ASSIGN_ID_WITH_SN:
					if(uart1_count == 12) //right
					{
						scan_response_state = ASSIGN_ID;
					}
					break;
			}
		}
		else
		{
			
		}
		Sever_Order = SERVER_NONE;
	}
}


/*****Uart2 routine***********************/
U8_T Uart2_Receive(void)
{
	U16_T uart2_count = 0;

	EA = 0;
	if(hsurRxCount)
	{
		if(Sever_Order == SERVER_TCPIP)
		{
			Set_transaction_ID(forward_buffer, sessonlen);
			uart2_count = 6;
		}

		memcpy(forward_buffer + uart2_count, hsurRxBuffer, hsurRxCount);
		uart2_count += hsurRxCount;
		hsurRxCount = 0;
		EA = 1;

	 //  LED = S485_OK;
	}
	else
	{
		EA = 1;
		return FALSE;
	}

	if(uart2_count)
	{
		
		
		if(Sever_Order == SERVER_TCPIP)  //Sever Order is from TCPIP
		{
			if(TcpIp_Scan == 1)
			{
				TcpIp_Scan = 0;
				TCPIP_TcpSend(TcpSocket_ME, forward_buffer, uart2_count, TCPIP_SEND_NOT_FINAL);
			}
			else
			{
				TCPIP_TcpSend(TcpSocket_ME, forward_buffer, uart2_count-2, TCPIP_SEND_NOT_FINAL);
			}
		}
		else if(Sever_Order == SERVER_RS232)
		{
			Uart0_Tx(forward_buffer, uart2_count);
		}
		else if(Sever_Order == SERVER_USB)
		{
			memcpy(UpBuf, forward_buffer, uart2_count);
			UpCtr = uart2_count;
			UpIndex = 0;
			ENDP2_NEED_UP_FLAG = 1;
		}
		else if(Sever_Order == SERVER_SCHEDULE) // schedule commands
		{
			if(uart2_count == 8)
			{
				U8_T i;
				InitCRC16();
				for(i = 0; i < 6; i++)
					CRC16_Tstat(forward_buffer[i]);

				if((forward_buffer[6] == CRChi) && (forward_buffer[7] == CRClo))
				{
					schedule_flag = 1;
				}
			}	
		}
		else if(Sever_Order == SERVER_SCAN)
		{
			switch(scan_state)
			{
				case SCAN_BINSEARCH:
					scan_response_state = MULTIPLE_ID;
					if(uart2_count >= 9) // right
					{
						U8_T i;
						InitCRC16();
						for(i = 0; i < 7; i++)
							CRC16_Tstat(forward_buffer[i]);
		
						if((forward_buffer[7] == CRChi) && (forward_buffer[8] == CRClo))
						{
							if((forward_buffer[0] == 0xff) && (forward_buffer[1] == 0x19)) // double check it is the response for scan command
							{
								current_db.id = forward_buffer[2];
								current_db.sn = ((U32_T)forward_buffer[6] << 24) | ((U32_T)forward_buffer[5] << 16) | ((U32_T)forward_buffer[4] << 8) | forward_buffer[3];
								if(uart2_count == 9)
								{
									scan_response_state = UNIQUE_ID;
								}
								else
								{
									scan_response_state = UNIQUE_ID_FROM_MULTIPLE;
								}
							}
						}
					}
					// and none tstat in the range will wait timeout in the waitrsponse routine
					break;
				case SCAN_ASSIGN_ID_WITH_SN:
					if(uart2_count == 12) //right
					{
						scan_response_state = ASSIGN_ID;
					}
					break;
			}
		}
		else
		{
			
		}
		Sever_Order = SERVER_NONE;
	}

	return TRUE;
}

/*****transmit order to tstat***********************/
void Tx_To_Tstat(U8_T *buf, U8_T len)
{
	U8_T i;

	Rs485_EN = 1;

	Uart1_Tx(buf, len);

//	DELAY_Ms(1);

	for(i = 0; i < len; i++)  
		HSUR_PutChar(buf[i]);

	if(len < 10)
		DELAY_Ms(1);
	else
		DELAY_Ms((len + 1) / 8);

	Rs485_EN = 0;
}

void LedBeat_task(void) reentrant
{   U16_T i;
  
	portTickType xDelayPeriod = ( portTickType ) 500 / portTICK_RATE_MS;  //2000
    portTickType xDelayPeriod1 = ( portTickType ) 100 / portTICK_RATE_MS;

	for (;;)				
	{  	
		if(err485)
		{
			Led_485ERR();
			for(i = 0; i < 20000;i++);
				err485 = 0;

			vTaskDelay(xDelayPeriod1);
		} 
//		BeatSta=1;
		Beat_ON();
		vTaskDelay(xDelayPeriod);
//		BeatSta=0;
		Beat_OFF() ;
		vTaskDelay(xDelayPeriod);				 
	}
}

void Realtimer_task(void) reentrant
{

	portTickType xDelayPeriod = ( portTickType ) 1000 / portTICK_RATE_MS;//2 minutes writting flash.
   	
	for (;;)
    	{   
		     vTaskDelay(xDelayPeriod);
            /* if(SetimeFlag)
               { SetimeFlag=0;
                 Initial_Clock();
               }*/

			// Uart0_Tx(Data,48);
             Read_Clock(2);
        }

}


void Timer_task(void) reentrant
{
	static U8_T refresh_flash_timer = 0;
	portTickType xDelayPeriod = ( portTickType ) 1000 / portTICK_RATE_MS;//3000
	for (;;)
	{
    	vTaskDelay(xDelayPeriod);				
		
		if(ChangeFlash == 1)
		{  
			ChangeFlash = 0;
			refresh_flash_timer = 30;			
		}

		if(refresh_flash_timer)
		{
			refresh_flash_timer--;
			if(refresh_flash_timer == 0)
			{
				Flash_Write_Schedule();
			}
		}

		if(ChangeIP > 0)  //LHN add
		{
			ChangeIP++;
			if(ChangeIP >= 4)
			{
				ChangeIP = 0;

				if(ChangeFlash == 2)
					Flash_Write_Schedule();
			
				if(mac_change_enable == 1)
				{
					E2prom_Write_Byte_To_Absolute_Address(0x0b, Para[201]);
					E2prom_Write_Byte_To_Absolute_Address(0x0a, Para[203]);
					E2prom_Write_Byte_To_Absolute_Address(0x09, Para[205]);
					E2prom_Write_Byte_To_Absolute_Address(0x08, Para[207]);
					E2prom_Write_Byte_To_Absolute_Address(0x07, Para[209]);
					E2prom_Write_Byte_To_Absolute_Address(0x06, Para[211]);
				
					mac_change_enable = 0;
				}
				
				lcdreset();
				AX11000_SoftReboot();
			
			}
		}

		Read_Clock(2);
	}
}


void Ledflash_task(void) reentrant
{
  
	portTickType xDelayPeriod = ( portTickType ) 100 / portTICK_RATE_MS;//200
	portTickType xDelayPeriod1 = ( portTickType ) 50 / portTICK_RATE_MS;//100
	for (;;)
	{  
		  if(LED==S485_OK){   
		  					  Led_EthSend(); 
							  vTaskDelay(xDelayPeriod1);	/*disable Ethernet LED*/
							  Led_EthRxD(); 
							  vTaskDelay(xDelayPeriod1);
		                
		                  	  Led_485Send();
							  vTaskDelay(xDelayPeriod1);
							  Led_485RxD();
							  vTaskDelay(xDelayPeriod1);
						
				         	  LED=None;Led_ReSet();
					     }

          if(LED==Ethnet_OK){ 
		  						Led_EthSend(); 
		  						vTaskDelay(xDelayPeriod1);
								Led_EthRxD(); 
								vTaskDelay(xDelayPeriod1);
					 		    LED= None;Led_ReSet();
					        }

            
          if(LED==S485_ERR){ Led_485ERR(); vTaskDelay(xDelayPeriod1); vTaskDelay(xDelayPeriod1);
		             
					 LED= None;Led_ReSet();
					 }
          
          
	       vTaskDelay(xDelayPeriod);
	}
}


/*  BACnet Master Node PFM */
void Master_Node_task(void) reentrant
{
	portTickType xDelayPeriod  = ( portTickType ) 20 / portTICK_RATE_MS;//1000
   	
	for (;;)
    {
		vTaskDelay(xDelayPeriod);
		  if(MODBUS_OR_BACNET_FUNCTION_SELECT_ON_UART0){
			 MSTP_Master_Node_FSM(mstp_port);
		  }
    }		

}


void test_task(void) reentrant
{
	portTickType xDelayPeriod  = ( portTickType ) 50 / portTICK_RATE_MS;//1000
	for (;;)
    {
		vTaskDelay(xDelayPeriod);

	   P3 = ~ P3 ;

	   test[0] = 0x21;
	   Uart0_Tx(test,1);

    }		
}




void display_ip(void)
{
	U8_T adr,i;		//num,
	U32_T sn,a,b,c,d;

	a =  Para[7];
	a = a << 24;

	b =  Para[5];
	b = b << 16;

	c =  Para[3];
	c = c << 8;

	d =  Para[1];

	sn = a + b + c + d ;

	Lcd_Show_String(3,1,"ip = ",1,5);
	Lcd_Show_Data(3,6,Para[215],0,1);
	Lcd_Show_String(3,9,".",1,1);
	Lcd_Show_Data(3,10,Para[217],0,1);
	Lcd_Show_String(3,13,".",1,1);
	Lcd_Show_Data(3,14,Para[219],0,1);
	Lcd_Show_String(3,15,".",1,1);
	Lcd_Show_Data(3,16,Para[221],0,1);


	Lcd_Show_String(1,1,"id = ",1,5);
	Lcd_Show_Data(1,6,Para[13],0,1);

	Lcd_Show_String(2,1,"sn = ",1,5);
	Lcd_show_for_32bit(2,6,sn,1);

	
	adr = Para[9] % 10 ;
	i = 1;
	Lcd_Show_String(4,i,"fw:",1,3);
	Lcd_Show_Data(4,i+3,Para[11],0,1);
	Lcd_Show_String(4,i+5,".",1,1);
//	Lcd_Show_Data(4,7,adr,0,1);
 	Lcd_Show_Data(4,i+6,Para[9],0,1);

	Lcd_Show_String(4,i+9,"hw:",1,3);
	Lcd_Show_Data(4,i+12,Para[17],0,1);

	Lcd_Show_String(4,i+15,"bw:",1,3);
	Lcd_Show_Data(4,i+18,Para[29],0,1);


//	Lcd_Show_Data(4,adr,(U16_T)(sn >> 16),0,1);
//	Lcd_Show_Data(4,adr+4,(U16_T)sn,0,1);
	Lcd_Show_String(0,1,"Network Controller",1,12);
}





void Uart0_task(void) reentrant
{
	portTickType xDelayPeriod  = ( portTickType ) 50 / portTICK_RATE_MS;//1000
   	
	for (;;)
    {
		vTaskDelay(xDelayPeriod);
		if(uart0_timeout == 0)
		{
		   if(!MODBUS_OR_BACNET_FUNCTION_SELECT_ON_UART0){		
			 

			Uart0_Receive();
			
			}
		}
    }		
}

void Uart1_task(void) reentrant
{
	portTickType xDelayPeriod = ( portTickType ) 50 / portTICK_RATE_MS;//1500

	for (;;)
    {	
		vTaskDelay(xDelayPeriod);
		if(uart1_timeout == 0)
		{
			Uart1_Receive();
		}

	}
}

void uart2_rescue(void)
{
	U16_T baudRateDiv = 0;

//    HSUR_InitValue();

	switch (CSREPR & (BIT6|BIT7))
		{
	    case SCS_25M:
	 		baudRateDiv = UR2_BR25_19200;
			break;
		case SCS_50M:
			baudRateDiv = UR2_BR50_19200;
			break;
		case SCS_100M:
			baudRateDiv = UR2_BR100_19200;
			break;
		}
	  

	HSUR_Setup(baudRateDiv, (UR2_CHAR_8|UR2_STOP_10), (UR2_RDI_ENB|UR2_RLSI_ENB),
	(UR2_FIFO_MODE|UR2_RXFIFO_RST|UR2_TXFIFO_RST|UR2_TRIG_08), UR2_RTS);


}

void Uart2_task(void) reentrant
{
	U8_T rescue_counter = 0;
	portTickType xDelayPeriod = ( portTickType ) 50 / portTICK_RATE_MS;//1000

	for (;;)
    { 
		vTaskDelay(xDelayPeriod);
		if(uart2_timeout == 0)
		{
			if(Uart2_Receive() == FALSE)
			{
				rescue_counter++;
				if(rescue_counter >= 40)
				{
					rescue_counter = 0;
					uart2_rescue();
				}
			}
		}
	}
}


void Schedule_task(void) reentrant
{
	static U8_T	count = 0;
	portTickType xDelayPeriod = ( portTickType ) 500 / portTICK_RATE_MS;//500
	for (;;)
	{
		vTaskDelay(xDelayPeriod); 
#if 1
/* implement CaculateTime rution  per 500ms */
		CaculateTime();
/* implement CheckWeeklyRoutines rution  per 1s */
		if(count % 2 == 0)  // 1s
		{
			//Para[1]++;
			CheckWeeklyRoutines();
		}
/* implement CheckAnnualRoutines rution  per 3s */
/* implement CheckIdRoutines rution  per 3s */	
		if(count % 6 == 0)  // 3s
		{
			//Para[3]++;
			CheckAnnualRoutines();
			CheckIdRoutines();
		}

#endif		
		if(count < 6)
			count++;
		else
			count = 0;
	}
}

void TimeServer_task(void) reentrant
{
	portTickType xDelayPeriod = ( portTickType ) 1000 / portTICK_RATE_MS;  //2000
    U8_T i;
	U32_T ip;//ntp.fudan.edu.cn=0x3D812A2C; 0xc0a800c7;192.168.0.199 0x4137150f;time.windows.com
	U8_T Data[48]={0xd9,0x00,0x0a,0xfa,0x00,0x00,0x00,0x00,0x00,0x01,0x04}; //{0x65,0,0x0b,0};
	for (;;)
	{ 
		Time_Server.Leng++;
 		if( (Time_Server.Leng == 50000) || (Para[355] == 6))						   		     
		{	
			Para[355] = 0;
			Para[399] = 0;

			ip = ((U32_T)Para[357]) << 24 | ((U32_T)Para[359]) << 16 | ((U32_T)Para[361]) << 8 | (U32_T)Para[363];
			Time_Server.UdpSocket = TCPIP_UdpNew(gudpbc_InterAppId, 0, ip, 1234,123);
			if(Time_Server.UdpSocket != TCPIP_NO_NEW_CONN)
			{
				for(i = 11; i < 40; i++)
					Data[i] = 0;
				Data[40] = 0xd2;Data[41] = 0x3c;Data[42] = 0xde;Data[43] = 0xd6;
				Data[44] = 0xe8;Data[45] = 0;Data[46] = 0;Data[47] = 0;				
			//	Uart0_Tx(Data,48);
			//	DELAY_Ms(5);
				TCPIP_UdpSend(Time_Server.UdpSocket, 0, 0, Data,48);
			}
		}

		if (Time_Server.Leng >= 50110) 
			Time_Server.Leng = 0;
						
		vTaskDelay(xDelayPeriod);
	}
}

void Scan_task(void)
{
	portTickType xDelayPeriod = (portTickType)5000 / portTICK_RATE_MS;
	init_scan();
	while(1)
	{
		vTaskDelay(xDelayPeriod);
		scan_tstat();
	}
}


void USB_task(void)
{
	U8_T len, length;
	U16_T StartAdd;
	portTickType xDelayPeriod = (portTickType)20 / portTICK_RATE_MS;

	CH375_Init();

	while(1)
	{   
		vTaskDelay(xDelayPeriod);
		if(usb_poll() == TRUE)
		{
			mCH375Interrupt();
		}
		else
		{
			if(USB_timeout == 0)
			{
				if(DownCtr > 0)
				{
					if((DownBuf[0] == Para[13]) || (DownBuf[0] == 0xff))	// Address of NetControl 
					{ 
						if(DownBuf[1] == 0x19) 		//scan Tsnet
						{
							Sever_Order = SERVER_USB;		//USB
							Sever_id = DownBuf[0];
							Tx_To_Tstat(DownBuf, DownCtr);			   												
						}					
						else if(DownBuf[1] == 0x1a)	//scan NC
						{ 
							UpCtr = 0;
							UpBuf[UpCtr++] = DownBuf[0];
							UpBuf[UpCtr++] = 0x19;
							UpBuf[UpCtr++] = Para[13];						 
							UpBuf[UpCtr++] = Para[1];
							UpBuf[UpCtr++] = Para[3];
							UpBuf[UpCtr++] = Para[5];
							UpBuf[UpCtr++] = Para[7];
							InitCRC16();
							for(len = 0; len < UpCtr; len++)
								CRC16_Tstat(UpBuf[len]);
							UpBuf[UpCtr++] = CRChi;
							UpBuf[UpCtr++] = CRClo;
							UpIndex = 0;
							ENDP2_NEED_UP_FLAG = 1;				         
						}
						else if(DownBuf[1] == read) 
						{
							UpBuf[0] = DownBuf[0];
							UpBuf[1] = DownBuf[1];
							length = (DownBuf[4] << 8) | DownBuf[5];
							UpBuf[2] = 2 * length;
							UpCtr = 3 + UpBuf[2];
							StartAdd = (DownBuf[2] << 8) | DownBuf[3];						                             
							for(len = 0; len < length; len++)
							{
								if(StartAdd < 200)
								{
									UpBuf[3 + 2 * len] = Para[2 * (StartAdd + len)];  
									UpBuf[4 + 2 * len] = Para[2 * (StartAdd + len) + 1];
								}
								else if(((StartAdd + len) >= MODBUS_TIMER_ADDRESS) && ((StartAdd + len) < (MODBUS_TIMER_ADDRESS + 8))) 
								{
									//  YEAR  MONTH  WEEK DATE  HOUR  MINUTE  SECOND 
									UpBuf[3 + 2 * len] = 0;
									switch(StartAdd + len - MODBUS_TIMER_ADDRESS)
									{
										case 7:
											UpBuf[4 + 2 * len] = Time.UN.Current.sec;
											break;	
										case 6:
											UpBuf[4 + 2 * len] = Time.UN.Current.min;
											break;
										case 5:
											UpBuf[4 + 2 * len] = Time.UN.Current.hour;
											break;
										case 4:
											UpBuf[4 + 2 * len] = Time.UN.Current.day;
											break;
										case 3:
											UpBuf[4 + 2 * len] = Time.UN.Current.dayofweek;
											break;
										case 2:
											UpBuf[4 + 2 * len] = Time.UN.Current.month;
											break;
										case 1:
											UpBuf[4 + 2 * len] = Time.UN.Current.year;
											break;
										case 0:
											UpBuf[4 + 2 * len] = Time.UN.Current.centary;
											break;
									}		
								}
								else if(((StartAdd + len) >= MODBUS_WR_DESCRIP_FIRST) && ((StartAdd + len) < MODBUS_WR_DESCRIP_LAST))
								{
									U8_T temp_number = (StartAdd + len - MODBUS_WR_DESCRIP_FIRST) / WR_DESCRIPTION_SIZE;
									U8_T temp_address = (StartAdd + len - MODBUS_WR_DESCRIP_FIRST) % WR_DESCRIPTION_SIZE;
									U8_T send_buffer = WR_Roution[temp_number].UN.all[temp_address];
								    if((temp_address == (WR_DESCRIPTION_SIZE - 1)) && (send_buffer != 0xff))
									{
										if((send_buffer & 0x80) == 0)
										{
											if(GetBit(temp_number, wr_state_index))
												send_buffer |= 0x40;
											else
												send_buffer &= 0xbf;
										}

										if(GetBit(temp_number, holiday1_state_index))
											send_buffer |= 0x20;
										else
											send_buffer &= 0xdf;

										if(GetBit(temp_number, holiday2_state_index))
											send_buffer |= 0x10;
										else
											send_buffer &= 0xef;
									}
									UpBuf[3 + 2 * len] = 0;	
									UpBuf[4 + 2 * len] = send_buffer;	
								}
								else if(((StartAdd + len) >= MODBUS_AR_DESCRIP_FIRST) && ((StartAdd + len) < MODBUS_AR_DESCRIP_LAST))
								{
									U8_T temp_number = (StartAdd + len - MODBUS_AR_DESCRIP_FIRST) / AR_DESCRIPTION_SIZE;    // line
									U8_T temp_address = (StartAdd + len - MODBUS_AR_DESCRIP_FIRST) % AR_DESCRIPTION_SIZE;
									U8_T send_buffer = AR_Roution[temp_number].UN.all[temp_address];
			
									if(temp_address == (AR_DESCRIPTION_SIZE - 1))
									{
										if((send_buffer & 0x80) == 0)
										{
											if(GetBit(temp_number, ar_state_index))
												send_buffer |= 0x40;
											else
												send_buffer &= 0xbf;
										}
									}
									UpBuf[3 + 2 * len] = 0;	
									UpBuf[4 + 2 * len] = send_buffer;	
								}
								else if(((StartAdd + len) >= MODBUS_ID_FIRST) && ((StartAdd + len) < MODBUS_ID_LAST))
								{
									U8_T temp_number = (StartAdd + len - MODBUS_ID_FIRST) / ID_SIZE;
									U8_T temp_address = (StartAdd + len - MODBUS_ID_FIRST) % ID_SIZE;
									U8_T send_buffer = ID_Config[temp_number].all[temp_address];
					
									if((temp_address == (ID_SIZE - 1)) && (send_buffer != 0xff))
									{
										if((send_buffer & 0x80) == 0)
										{
											if(GetBit(temp_number, output_state_index))
												send_buffer |= 0x40;
											else
												send_buffer &= 0xbf;
										}

										if(GetBit(temp_number, schedual1_state_index))
											send_buffer |= 0x20;
										else
											send_buffer &= 0xdf;

										if(GetBit(temp_number, schedual2_state_index))
											send_buffer |= 0x10;
										else
											send_buffer &= 0xef;
									}
									UpBuf[3 + 2 * len] = 0;	
									UpBuf[4 + 2 * len] = send_buffer;	
								}
								else if(((StartAdd + len) >= MODBUS_AR_TIME_FIRST) && ((StartAdd + len) < MODBUS_WR_ONTIME_FIRST))
								{
									U8_T temp_number = (StartAdd + len - MODBUS_AR_TIME_FIRST) / AR_TIME_SIZE;
									U8_T temp_address = (StartAdd + len - MODBUS_AR_TIME_FIRST) % AR_TIME_SIZE;
									U8_T send_buffer = AR_Roution[temp_number].Time[temp_address];
					
									UpBuf[3 + 2 * len] = 0;	
									UpBuf[4 + 2 * len] = send_buffer;
								}
								else if(((StartAdd + len) >= MODBUS_WR_ONTIME_FIRST) && ((StartAdd + len) < MODBUS_WR_OFFTIME_FIRST))
								{
									U8_T temp_number = (StartAdd + len - MODBUS_WR_ONTIME_FIRST) / WR_TIME_SIZE;		
									U8_T temp_address = (StartAdd + len - MODBUS_WR_ONTIME_FIRST) % WR_TIME_SIZE;
									U8_T send_buffer = WR_Roution[temp_number].OnTime[temp_address];
									UpBuf[3 + 2 * len] = 0;	
									UpBuf[4 + 2 * len] = send_buffer;
								}
								else if(((StartAdd + len) >= MODBUS_WR_OFFTIME_FIRST) && ((StartAdd + len) < MODBUS_WR_OFFTIME_LAST))
								{
									U8_T temp_number = (StartAdd + len - MODBUS_WR_OFFTIME_FIRST) / WR_TIME_SIZE;
									U8_T temp_address = (StartAdd + len - MODBUS_WR_OFFTIME_FIRST) % WR_TIME_SIZE;
									U8_T send_buffer = WR_Roution[temp_number].OffTime[temp_address];
									UpBuf[3 + 2 * len] = 0;	
									UpBuf[4 + 2 * len] = send_buffer;			
								}
								else
								{
									UpBuf[3 + 2 * len] = 0;	
									UpBuf[4 + 2 * len] = 1;
								}						
							} 

							InitCRC16();
							for(len = 0; len < UpCtr; len++)
								CRC16_Tstat(UpBuf[len]);

							UpBuf[UpCtr++] = CRChi;                        
							UpBuf[UpCtr++] = CRClo;

							UpIndex = 0;
							ENDP2_NEED_UP_FLAG = 1;							  					
						}
						else if(DownBuf[1] == swrite) 
						{
							U16_T StartAdd = (DownBuf[2] << 8) | DownBuf[3];
							if(StartAdd < 200)
							{
								if(StartAdd == 15) // clear flash to zero
								{
									if(((DownBuf[4] << 8) | DownBuf[5]) == 0x55)
									{
										memset(WR_Roution, 0, MAX_WR * WR_STRUCT_LENGTH);
										memset(AR_Roution, 0, MAX_AR * AR_STRUCT_LENGTH);
										memset(ID_Config, 0, MAX_ID * ID_SIZE);
										Para[30] = 0;
										Para[31] = 0;
										ChangeFlash = 1;
									}				  
								}
								else if(StartAdd == 106)
								{
									if((((Para[212] << 8) | Para[213]) == 0) && (((DownBuf[4] << 8) | DownBuf[5]) != 0))
									{
										Para[212] = DownBuf[4];
										Para[213] = DownBuf[5];
										ChangeIP = 1;
										ChangeFlash = 2;
									}
								}
								else if((StartAdd >= 107) && (StartAdd <= 120)) //IP change ,reset cpu
								{
									if(((Para[212] << 8) | Para[213]) == 0)
									{
										Para[2*DownBuf[3]] = DownBuf[4];		//write to bufffer array high bit
										Para[2*DownBuf[3] + 1] = DownBuf[5];	//write to bufffer array low bit
										ChangeFlash = 2;
										ChangeIP = 1;
									}
								}
								else
								{
									Para[2*DownBuf[3]] = DownBuf[4]; 			//write to bufffer array high bit
									Para[2*DownBuf[3] + 1] = DownBuf[5];		//write to bufffer array low bit
									ChangeFlash = 1;
								}
							}
							else if((StartAdd >= SCHEDUAL_MODBUS_ADDRESS) && (StartAdd < SCHEDUAL_MODBUS_ADDRESS + 8))
							{
								switch(StartAdd - SCHEDUAL_MODBUS_ADDRESS)
								{
									case 0: //century
										if(DownBuf[5] == 19)
										{
											Set_Clock(PCF_MON, Time.UN.Current.month | 0x80);
										}
										else if(DownBuf[5] == 20)
										{
											Set_Clock(PCF_MON, Time.UN.Current.month & 0x7f);
										}
										break;
									case 1: //year
										Set_Clock(PCF_YEAR, DownBuf[5]);
										break;
									case 2: //month
										if(Time.UN.Current.centary == 19)
										{
											Set_Clock(PCF_MON, DownBuf[5] | 0x80);
										}
										else if(Time.UN.Current.centary == 20)
										{
											Set_Clock(PCF_MON, DownBuf[5] & 0x7f);
										}
										break;
									case 3:
										Set_Clock(PCF_WEEK, DownBuf[5]);
										break;
									case 4: //date
										Set_Clock(PCF_DAY, DownBuf[5]);
										break;
									case 5: //hour
										Set_Clock(PCF_HOUR, DownBuf[5]);
										break;
									case 6: //minute
										Set_Clock(PCF_MIN, DownBuf[5]);
										break;
									case 7: //second
										Set_Clock(PCF_SEC, DownBuf[5]);
										break;
								}
							}
							else
							{
								// spare
							}

							for(len = 0; len < DownCtr; len++)
								UpBuf[len] = DownBuf[len];
	
							UpCtr = len;
							UpIndex = 0;
							ENDP2_NEED_UP_FLAG = 1;
						}
						else if(DownBuf[1] == mwrite) //multi_write
						{
							U8_T i;
							U16_T StartAdd = (DownBuf[2] << 8) | DownBuf[3];
							ChangeFlash = 1;
							if(StartAdd < SCHEDUAL_MODBUS_ADDRESS)
							{
								if((StartAdd == 100) && (DownBuf[6] == 12))
								{
									Para[201] = DownBuf[8];
									Para[203] = DownBuf[10];
									Para[205] = DownBuf[12];
									Para[207] = DownBuf[14];
									Para[209] = DownBuf[16];
									Para[211] = DownBuf[18];
					
									mac_change_enable = 1;
									ChangeIP = 1;
								}
							    else
								{
									for(i = 0; i < DownBuf[6]; i++)
									{
										if(((StartAdd + i / 2) < 100) || ((StartAdd + i / 2) > 105))  
											Para[2 * StartAdd + i] = DownBuf[i];
									}
								}
							}
							else if(StartAdd == SCHEDUAL_MODBUS_ADDRESS) //200th register ,write time 
							{
//								if((StartAdd - SCHEDUAL_MODBUS_ADDRESS) % 8 == 0)
//									memcpy(Time.UN.Setime,&DownBuf[7], 8);
								if(DownBuf[5] == 8)
								{
									if(DownBuf[5] == DownBuf[6])
									{
										Time.UN.Setime[7] = DownBuf[14];
										Time.UN.Setime[6] = DownBuf[13];
										Time.UN.Setime[5] = DownBuf[12];
										Time.UN.Setime[4] = DownBuf[11];
										Time.UN.Setime[3] = DownBuf[10];
										if(DownBuf[7] == 19)
											DownBuf[9] |= 0x80;
										else
											DownBuf[9] &= 0x7f;
										Time.UN.Setime[2] = DownBuf[9];
										Time.UN.Setime[1] = DownBuf[8];
										Time.UN.Setime[0] = DownBuf[7];
									}
									else
									{
										Time.UN.Setime[7] = DownBuf[22];
										Time.UN.Setime[6] = DownBuf[20];
										Time.UN.Setime[5] = DownBuf[18];
										Time.UN.Setime[4] = DownBuf[16];
										Time.UN.Setime[3] = DownBuf[14];
										if(DownBuf[8] == 19)
											DownBuf[12] |= 0x80;
										else
											DownBuf[12] &= 0x7f;
										Time.UN.Setime[2] = DownBuf[12];
										Time.UN.Setime[1] = DownBuf[10];
										Time.UN.Setime[0] = DownBuf[8];
									}
									Initial_Clock();
								}
							}
							else if ((StartAdd >= MODBUS_WR_DESCRIP_FIRST) && (StartAdd < MODBUS_WR_DESCRIP_LAST)) //weekly
					       	{								
								if((StartAdd - MODBUS_WR_DESCRIP_FIRST) % WR_DESCRIPTION_SIZE == 0)
							 	{
							 		i = (StartAdd - MODBUS_WR_DESCRIP_FIRST) / WR_DESCRIPTION_SIZE;
									memcpy(WR_Roution[i].UN.all, DownBuf + 7, WR_DESCRIPTION_SIZE);
							 	}
					       	}
					  		else if((StartAdd >= MODBUS_AR_DESCRIP_FIRST) && (StartAdd < MODBUS_AR_DESCRIP_LAST))
							{
								if((StartAdd - MODBUS_AR_DESCRIP_FIRST) % AR_DESCRIPTION_SIZE == 0)
								{
									i = (StartAdd - MODBUS_AR_DESCRIP_FIRST) / AR_DESCRIPTION_SIZE;		 
									memcpy(AR_Roution[i].UN.all, DownBuf + 7, AR_DESCRIPTION_SIZE);
								}
							}
							else if((StartAdd >= MODBUS_ID_FIRST) && (StartAdd < MODBUS_ID_LAST))
							{
								if((StartAdd - MODBUS_ID_FIRST) % ID_SIZE == 0)
								{
									i = (StartAdd - MODBUS_ID_FIRST) / ID_SIZE;
									memcpy(ID_Config[i].all, DownBuf + 7, ID_SIZE);
								}
							}
							else if((StartAdd >= MODBUS_AR_TIME_FIRST) && (StartAdd < MODBUS_AR_TIME_LAST))
							{
								if((StartAdd - MODBUS_AR_TIME_FIRST) % AR_TIME_SIZE == 0)
								{
									i = (StartAdd - MODBUS_AR_TIME_FIRST) / AR_TIME_SIZE;			
									memcpy(AR_Roution[i].Time, DownBuf + 7, AR_TIME_SIZE);
								}
							}
							else if((StartAdd >= MODBUS_WR_ONTIME_FIRST) && (StartAdd < MODBUS_WR_ONTIME_LAST))
							{
								if((StartAdd - MODBUS_WR_ONTIME_FIRST) % WR_TIME_SIZE == 0)
								{
									i = (StartAdd - MODBUS_WR_ONTIME_FIRST) / WR_TIME_SIZE;
									memcpy(WR_Roution[i].OnTime, DownBuf + 7, WR_TIME_SIZE);
								}
							}
							else if((StartAdd >= MODBUS_WR_OFFTIME_FIRST) && (StartAdd < MODBUS_WR_OFFTIME_LAST))
							{
								if((StartAdd - MODBUS_WR_OFFTIME_FIRST) % WR_TIME_SIZE == 0)
								{
									i = (StartAdd - MODBUS_WR_OFFTIME_FIRST) / WR_TIME_SIZE;					
									memcpy(WR_Roution[i].OffTime, DownBuf + 7 , WR_TIME_SIZE);
								}
							}

							InitCRC16();
							for(i = 0; i < 6; i++)
							{
								UpBuf[len] = DownBuf[len];
								CRC16_Tstat(UpBuf[i]);
							}
							UpBuf[6] = CRChi;                        
							UpBuf[7] = CRClo;
	
							UpCtr = 8;
							UpIndex = 0;
							ENDP2_NEED_UP_FLAG = 1;
						}
					}
					else
					{
						Sever_Order = SERVER_USB;		//USB
						Sever_id = DownBuf[0];				  
						Tx_To_Tstat(DownBuf, DownCtr);								 			          			 
					} 
					
					DownCtr = 0;
				}
			}

			if((ENDP2_NEED_UP_FLAG == 1) && (ENDP2_UP_SUC_FLAG == 1) && UpCtr)
			{
				ENDP2_UP_SUC_FLAG = 0;
				if(UpCtr > BULK_IN_ENDP_MAX_SIZE)
				{
					length = BULK_IN_ENDP_MAX_SIZE;
					UpCtr -= BULK_IN_ENDP_MAX_SIZE;
				}
				else
				{
					length = UpCtr;
					UpCtr = 0;
					ENDP2_NEED_UP_FLAG = 0;
				}

				CH375_WR_CMD_PORT(CMD_WR_USB_DATA7);			// 发出写上传端点2命令
				CH375_WR_DAT_PORT(length);
				for(len = 0; len < length; len++)
					CH375_WR_DAT_PORT(UpBuf[UpIndex++]);
			}
		}
	}
}


BOOL send_out = TRUE;
U8_T test_setpoint[] = { 0xfe, 0x06, 0x01, 0x5b, 0x00, 0x19, 0x2c, 0x20}; 
U8_T rev_cnt = 0;

void gsm_task(void) reentrant						// LJ
{

	char temp_gsm[100];
	portTickType xDelayPeriod = ( portTickType)	1500 / portTICK_RATE_MS;

	gsm_init();                     // LJ
    

	for (;;)
	{
		vTaskDelay(xDelayPeriod);

		switch ( g_state)
		{
			case GSM_INITING:
				gsm_module_init();
				break;
			case GSM_ERROR:
//				gsm_debug( "RETURN ERROR");
				break;
			case GSM_INIT_DONE:
#if 0					   // for test
				if(send_out){
					send_at_cmd( "AT+CMGF=1");
					MicroWait(65000);
					sprintf( temp_gsm, "AT+CMGS=\"%s\"", "15618987525");
					send_at_cmd( temp_gsm);
					MicroWait(65000);
					send_at_cmd( "test first time");
					simulate_write_byte( 0x1a);
//					gsm_debug( "Send phone number");
					send_out = FALSE;
					}
				break;
#endif
				if(0)          // wait for temperature register
				{
					if(send_out)
					{
//						send_at_cmd( "AT+CMGF=1");					   // TEXT 模式
//						MicroWait(65000);
						sprintf( temp_gsm, "AT+CMGS=\"%s\"", &phoneNumber[3]);
						send_at_cmd( temp_gsm);
						MicroWait(65000);
						send_at_cmd( "test first time");
						simulate_write_byte( 0x1a);
						//g_state = SMS_SENDING;
						send_out = FALSE;
					}
				}
				break;				
			case SMS_READY:
				send_at_cmd( "Test GSM module first time");
				simulate_write_byte( 0x1a);
				g_state = GSM_INIT_DONE;
				break;
			case SMS_SEND_SUCCESS:
				g_state = GSM_INIT_DONE;
				break;
			case GET_MSG:
//				gsm_debug( "send cmgr");
				send_at_cmd( "AT+CMGR=1");
//				MicroWait(65000);
				rev_cnt++;
//				g_state = GSM_INIT_DONE;
				if( rev_cnt > 9)
				{
					g_state = GSM_INIT_DONE;
					rev_cnt = 0;
					send_at_cmd( "AT+CMGD=1");			   // 尝试10次后，删除短信
				}
				break;
			case SET_POINT:
				Tx_To_Tstat( test_setpoint, 8);
				g_state = GSM_INIT_DONE;
				break;
			default:
				break;
		}
//		if( gsm_timeout == 0)
		{
//			gsm_debug("UUUUUUUUUUUUUUU");
			if( gsm_RxBuf.size > 1)
			{
//				gsm_debug( gsm_RxBuf.buf);
				gsm_msg_process (gsm_RxBuf.buf); 
//				gsm_RxBuf.size = 0;
//				gsm_debug( "Process	simulate uart message");
			}																																																												 
		}

	}
}

void test_run(U8_T dat)
{
/* TEST CODE */

	while(1){
	 P1_1 = ~ P1_1;

	 P3_7 = ~ P3_7;
	 DELAY_Ms(dat);
	}
}

void test_port(U8_T num)
{

	test[0] = num;
	Uart0_Tx(test,1);

}




/*
 * ----------------------------------------------------------------------------
 * Function Name: main
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------*/
void main(void )
{ 
	U16_T i;
    U8_T FlashFlag=0; //已经烧写过flash 还是没有
    U8_T dat[100];
	U8_T flag_store_schedule;

	mstp_port = calloc(1, sizeof(struct mstp_port_struct_t));

//	LED==S485_OK;

	MODBUS_OR_BACNET_FUNCTION_SELECT_ON_UART0 = 0;			 /* */

	ExecuteRuntimeFlag = 1;


	/* System Initiation */
	AX11000_Init();


	/* UART Interface Initiation */
	UART_Init(0);
	

	UART_Init(1);

   
    /* init mstp port */
    MSTP_Init(mstp_port);


	uart2_rescue();


	Lcd_Initial();


    I2C_Init();


	ETH_Init();



	for(i = 0; i < 100; i++)
    { 
		IntFlashReadByte(0x70000 + i, &dat[i]);
		if(dat[i] == 0xff) FlashFlag++;
    }


   	if(FlashFlag > 90) //if its the time to program
	{   
	 	IntFlashReadByte(0x6FFFF, &Parame[29]);		
		E2prom_Read_Byte_From_Absolute_Address(0x0b, Parame + 201);
		E2prom_Read_Byte_From_Absolute_Address(0x0a, Parame + 203);
		E2prom_Read_Byte_From_Absolute_Address(0x09, Parame + 205);
		E2prom_Read_Byte_From_Absolute_Address(0x08, Parame + 207);
		E2prom_Read_Byte_From_Absolute_Address(0x07, Parame + 209);
		E2prom_Read_Byte_From_Absolute_Address(0x06, Parame + 211);
		MassFlashWrite(0, Parame, 400);   //write datas to address 0,length 400	
	}



	for(i = 0; i < 400; i++)   //read 
		IntFlashReadByte(0x70000 + i, &Para[i]);   //the first para means location,last means array

	E2prom_Read_Byte_From_Absolute_Address(0x0b, Para + 201);
	E2prom_Read_Byte_From_Absolute_Address(0x0a, Para + 203);
	E2prom_Read_Byte_From_Absolute_Address(0x09, Para + 205);
	E2prom_Read_Byte_From_Absolute_Address(0x08, Para + 207);
	E2prom_Read_Byte_From_Absolute_Address(0x07, Para + 209);
	E2prom_Read_Byte_From_Absolute_Address(0x06, Para + 211);

													 

	Flash_Inital();	
	IntFlashReadByte(0x7fff0, &flag_store_schedule);
	if(flag_store_schedule == 0x55)	
	{
		Flash_Read_Schedule(); // read scheduel data from flash
 	}


	if(Para[9] != Parame[9])  //botload is changed,user configure can't erase.so if software revision need to change
	{
		Para[9] = Parame[9];
		Flash_Write_Schedule();	
	}
  	if(Para[33] == 0x1f)//if update is not completed,flashing led shows this statement.
     	FlagIsp = 1; 


	display_ip();
 	Hardware_Revision = Read_Hardware_Revision();


  sTaskCreate(TCPIP_Task, (const signed portCHAR * const)"TCPIP_task",
		portMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, (xTaskHandle *)&xHandle1); //0 2

  sTaskCreate(LedBeat_task, (const signed portCHAR * const)"LedBeat_task",
		portMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, (xTaskHandle *)&xHandle3);  //3

  sTaskCreate(Timer_task, (const signed portCHAR * const)"Timer_task",
		portMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, (xTaskHandle *)&xHandle2);  //3

   sTaskCreate(Ledflash_task, (const signed portCHAR * const)"Ledflash_task",
		portMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 4, (xTaskHandle *)&xHandle4);  //5

   sTaskCreate(Uart0_task, (const signed portCHAR * const)"Uart0_task",
		portMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 7, (xTaskHandle *)&xHandle5); //0

   sTaskCreate(Uart1_task, (const signed portCHAR * const)"Uart1_task",
		portMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 8, (xTaskHandle *)&xHandle6);

   sTaskCreate(Uart2_task, (const signed portCHAR * const)"Uart2_task",
		portMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 9, (xTaskHandle *)&xHandle9);

   sTaskCreate(Schedule_task, (const signed portCHAR * const)"Schedule_task",
		portMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 6, (xTaskHandle *)&xHandle8);


   sTaskCreate(TimeServer_task, (const signed portCHAR * const)"TimeServer_task",
		portMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 5, (xTaskHandle *)&xHandle7);//8

    sTaskCreate(USB_task, (const signed portCHAR * const)"USB_task",
		portMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 10, (xTaskHandle *)&xHandle11);//8

	sTaskCreate(gsm_task, (const signed portCHAR * const)"gsm_task",
		portMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 4, (xTaskHandle *)&xHandle12);		  // LJ


	sTaskCreate(Master_Node_task, (const signed portCHAR * const)"Master_Node_task",
		portMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 9, (xTaskHandle *)&xHandle14);		  // hyc

/* Finally kick off the scheduler.  This function should never return. */
	vTaskStartScheduler( portUSE_PREEMPTION );

}


/* End of adapter.c */