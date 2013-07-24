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
 * Module Name: gudpbc.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: gudpbc.c,v $
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "reg80390.h"
#include "adapter.h"
#include "gudpbc.h"
#include "tcpip.h"
#include "mstimer.h"
#include "stoe.h"
#include "uart.h"
#include "gconfig.h"
#include "ax11000.h"
#include "mac.h"
#include "flash.h"
#include "i2c.h"
#include "i2capi.h"
#include "printd.h"
#include "main.h"
#include <string.h>
#include "8563.h"
#include "../USB/ch375_com.h"
#include "../LCD/LCD.h"

/* NAMING CONSTANT DECLARATIONS */
#define GS2E_ENABLE_STATE_MACHINE	0
#define GUDPBC_EEPROM_CONFIG		(GCONFIG_EEPROM_CONFIG)
#define GUDPBC_ENABLE_DEBUG_MSG		0 // 1: enable 0:disable

#define GUDPBC_MAX_CONNS			4
#define GUDPBC_NO_NEW_CONN			0xFF

#define GUDPBC_STATE_FREE			0
#define	GUDPBC_STATE_WAIT			1
#define	GUDPBC_STATE_CONNECTED		2


/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static GUDPBC_CONN gudpbc_Conns[GUDPBC_MAX_CONNS];
 U8_T gudpbc_InterAppId;
static GCONFIG_CFG_PKT gudpbc_ConfigTxPkt;
static GCONFIG_CFG_PKT gudpbc_ConfigRxPkt;

/* LOCAL SUBPROGRAM DECLARATIONS */
void gudpbc_HandleSearchReq(U8_T XDATA* pData, U8_T id);
void gudpbc_HandleSetReq(U8_T XDATA* pData, U16_T length, U8_T id);
void gudpbc_HandleUpgradeReq(U8_T XDATA* pData, U16_T length, U8_T id);
void gudpbc_HandleResetReq(U8_T XDATA* pData, U16_T length, U8_T id);
void gudpbc_HandleRebootReq(U8_T XDATA* pData, U16_T length, U8_T id);
#if GUDPBC_EEPROM_CONFIG
void gudpbc_HandleEepromReadReq(U8_T XDATA* pData, U16_T length, U8_T id);
void gudpbc_HandleEepromWriteReq(U8_T XDATA* pData, U16_T length, U8_T id);
#endif

U8_T    FlagIsp=0;
//U16_T UdpPort=1234;
extern   U8_T  far  Para[400]; 
U8_T ab[40]={0x65,0,0x0e,0};//0x0b

 U8_T state=1;

 U8_T scanstart=0;

void UdpData(void)
 {

//serial
ab[4]=Para[1];
ab[5]=0;
ab[6]=Para[3];
ab[7]=0;
ab[8]=Para[5];
ab[9]=0;
ab[10]=Para[7];
ab[11]=0;
//nc 
ab[12]=Para[15];
ab[13]=0;
//modbus address
ab[14]=Para[13];
ab[15]=0;
//Ip
ab[16]=Para[215];
ab[17]=0;
ab[18]=Para[217];
ab[19]=0;
ab[20]=Para[219];
ab[21]=0;
ab[22]=Para[221];
ab[23]=0;
//port
//ab[24]=(U8_T)(UdpPort);
//ab[25]=(U8_T)(UdpPort>>8);
ab[24]=Para[241];
ab[25]=Para[240];

ab[26]=Para[9];
ab[27]=0;

ab[28]=Para[11];
ab[29]=0;

ab[30]=Para[17];
ab[31]=0;

}

#if 1  //LHN ADD for time server

#define Bace_s           3439756800   //from 2009.1.1 
#define Bace_Week        3            //2009.1.1 Tuesday
#define Bace_year        2009  
#define Bace_Time_Zone   43200        //Zone -12        
#define Day_s            86400
#define Hour_s           3600
#define Min_s            60
#define year_Day         365


void TimeServer_Deal(U32_T time,U8_T time_zone)
{
	U32_T time_s=0;
	U32_T time_year=0;
	U32_T time_day=0;
	U32_T time_h=0;

	time_s = time - Bace_s + ((U32_T)time_zone) * Hour_s - Bace_Time_Zone;

	if(time_s)
	{
		time_day = time_s / Day_s ;
		time_h = time_s % Day_s;

		Time.UN.Setime[3] = (U8_T)(time_day % 7 + Bace_Week) % 7 + 1;  //Week

		if( (time_day % year_Day)  >= ((time_day / year_Day ) / 4) )
		{
			time_year = time_day / year_Day + Bace_year;   
			time_day = time_day % year_Day - (time_day / year_Day)/4;
		}
		else
		{
			time_year = time_day / year_Day + Bace_year - 1;
   		    if((time_day / year_Day ) / 4)
				time_day = 366 + time_day % year_Day - (time_day / year_Day)/4;	
			else
				time_day = 365 + time_day % year_Day - (time_day / year_Day)/4;	
		}

		Time.UN.Setime[0] = (U8_T)(time_year / 100);           //year high
		Time.UN.Setime[1] = (U8_T)(time_year % 100);           //year low

		if(!(time_year % 4))  //leap year
		{
			if( (time_day >= 0) && (time_day <= 30) ) // january
			{
				Time.UN.Setime[2] = 1;               //month                     
				Time.UN.Setime[4] = time_day + 1;    //day
			}
			else if( (time_day >= 31) && (time_day <= 59) ) // february
			{
				Time.UN.Setime[2] = 2;
				Time.UN.Setime[4] = time_day - 31 + 1;	
			}
			else if( (time_day >= 60) && (time_day <= 90) ) //3
			{
				Time.UN.Setime[2] = 3;
				Time.UN.Setime[4] = time_day - 60 + 1;	
			}
			else if( (time_day >= 91) && (time_day <= 120) )//4
			{
				Time.UN.Setime[2] = 4;
				Time.UN.Setime[4] = time_day - 91 + 1;	
			}
			else if( (time_day >= 121) && (time_day <= 151) ) //5
			{
				Time.UN.Setime[2] = 5;
				Time.UN.Setime[4] = time_day - 121 + 1;	
			}
			else if( (time_day >= 152) && (time_day <= 181) ) //6
			{
				Time.UN.Setime[2] = 6;
				Time.UN.Setime[4] = time_day - 152 + 1;	
			}
			else if( (time_day >= 182) && (time_day <= 212) ) //7
			{
				Time.UN.Setime[2] = 7;
				Time.UN.Setime[4] = time_day - 182 + 1;	
			}
			else if( (time_day >= 213) && (time_day <= 243) ) //8
			{
				Time.UN.Setime[2] = 8;
				Time.UN.Setime[4] = time_day - 213 + 1;	
			}
			else if( (time_day >= 244) && (time_day <= 273) ) //9
			{
				Time.UN.Setime[2] = 9;
				Time.UN.Setime[4] = time_day - 243 + 1;	
			}
			else if( (time_day >= 274) && (time_day <= 304) ) //10
			{
				Time.UN.Setime[2] = 10;
				Time.UN.Setime[4] = time_day - 274 + 1;	
			}
			else if( (time_day >= 305) && (time_day <= 334) ) //11
			{
				Time.UN.Setime[2] = 11;
				Time.UN.Setime[4] = time_day - 304 + 1;	
			}
			else if( (time_day >= 335) && (time_day <= 365) ) //12
			{
				Time.UN.Setime[2] = 12;
				Time.UN.Setime[4] = time_day - 335 + 1;	
			}

		}
		else
		{
			if( (time_day >= 0) && (time_day <= 30) ) // january
			{
				Time.UN.Setime[2] = 1;
				Time.UN.Setime[4] = time_day - 0 + 1;
			}
			else if( (time_day >= 31) && (time_day <= 58) ) // february
			{
				Time.UN.Setime[2] = 2;
				Time.UN.Setime[4] = time_day - 31 + 1;	
			}
			else if( (time_day >= 59) && (time_day <= 89) ) //3
			{
				Time.UN.Setime[2] = 3;
				Time.UN.Setime[4] = time_day - 59 + 1;	
			}
			else if( (time_day >= 90) && (time_day <= 119) )//4
			{
				Time.UN.Setime[2] = 4;
				Time.UN.Setime[4] = time_day - 90 + 1;	
			}
			else if( (time_day >= 120) && (time_day <= 150) ) //5
			{
				Time.UN.Setime[2] = 5;
				Time.UN.Setime[4] = time_day - 120 + 1;	
			}
			else if( (time_day >= 151) && (time_day <= 180) ) //6
			{
				Time.UN.Setime[2] = 6;
				Time.UN.Setime[4] = time_day - 151 + 1;	
			}
			else if( (time_day >= 181) && (time_day <= 211) ) //7
			{
				Time.UN.Setime[2] = 7;
				Time.UN.Setime[4] = time_day - 181 + 1;	
			}
			else if( (time_day >= 212) && (time_day <= 242) ) //8
			{
				Time.UN.Setime[2] = 8;
				Time.UN.Setime[4] = time_day - 212 + 1;	
			}
			else if( (time_day >= 243) && (time_day <= 272) ) //9
			{
				Time.UN.Setime[2] = 9;
				Time.UN.Setime[4] = time_day - 242 + 1;	
			}
			else if( (time_day >= 273) && (time_day <= 303) ) //10
			{
				Time.UN.Setime[2] = 10;
				Time.UN.Setime[4] = time_day - 273 + 1;	
			}
			else if( (time_day >= 304) && (time_day <= 333) ) //11
			{
				Time.UN.Setime[2] = 11;
				Time.UN.Setime[4] = time_day - 303 + 1;	
			}
			else if( (time_day >= 334) && (time_day <= 364) ) //12
			{
				Time.UN.Setime[2] = 12;
				Time.UN.Setime[4] = time_day - 334 + 1;	
			}
	
		}
		Time.UN.Setime[5] = (U8_T)(time_h / Hour_s);  //Hour
		time_h = time_h % Hour_s;
		Time.UN.Setime[6] = (U8_T)(time_h / Min_s);  //minute
		Time.UN.Setime[7] = (U8_T)(time_h % Min_s); //second		
		
		Initial_Clock();
	//	Uart0_Tx(Time.UN.Setime,8);
	}
}

#endif



#if 1
/*
 * ----------------------------------------------------------------------------
 * Function Name: I2C_Init
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void I2C_Init(void)
{
	switch (CSREPR & (BIT6|BIT7))
	{
		case SYS_CLK_100M :
			/* I2C master mode, interrupt enable, fast mode in slave, 7-bits address, 400KHz at 100M */
			I2C_Setup(I2C_ENB|I2C_FAST|I2C_MST_IE|I2C_7BIT|I2C_MASTER_MODE, 0x0031, 0x005A);
			break;
		case SYS_CLK_50M :
			/* I2C master mode, interrupt enable, fast mode in slave, 7-bits address, 400KHz at 50M */
			I2C_Setup(I2C_ENB|I2C_FAST|I2C_MST_IE|I2C_7BIT|I2C_MASTER_MODE, 0x0018, 0x005A);
			break;
		case SYS_CLK_25M :
			/* I2C master mode, interrupt enable, fast mode in slave, 7-bits address, 400KHz at 25M */
			I2C_Setup(I2C_ENB|I2C_FAST|I2C_MST_IE|I2C_7BIT|I2C_MASTER_MODE, 0x000c, 0x005A);
			break;
	}
}
#endif

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPBC_Task
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GUDPBC_Task(void)
{

} /* End of GUDPBC_Task() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPBC_Init()
 * Purpose: Initialization
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GUDPBC_Init(U16_T localPort)
{
	U8_T	i;


	for (i = 0; i < GUDPBC_MAX_CONNS; i++)
		gudpbc_Conns[i].State = GUDPBC_STATE_FREE;

	gudpbc_InterAppId = TCPIP_Bind(GUDPBC_NewConn, GUDPBC_Event, GUDPBC_Receive);
		
	/* unicast packet */
//	TCPIP_UdpListen(123, gudpbc_InterAppId);
	TCPIP_UdpListen(localPort, gudpbc_InterAppId);
	
} /* End of GUDPBC_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPBC_NewConn
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GUDPBC_NewConn(U32_T XDATA* pip, U16_T remotePort, U8_T socket)
{
	U8_T	i;

	pip = pip;
	remotePort = remotePort;

#if GUDPBC_ENABLE_DEBUG_MSG
	printd("GUDPBC_NewConn(remotePort=%d, socket=%d)\n\r",remotePort,socket);
#endif	

	for (i = 0; i < GUDPBC_MAX_CONNS; i++)
	{
		if (gudpbc_Conns[i].State == GUDPBC_STATE_FREE)
		{
			gudpbc_Conns[i].State = GUDPBC_STATE_CONNECTED;
//			gudpbc_Conns[i].Timer = (U16_T)SWTIMER_Tick();
//			gudpbc_Conns[i].Ip = *pip;
//			gudpbc_Conns[i].Port = remotePort;
			gudpbc_Conns[i].UdpSocket = socket;
			return i;
		}
	}
	
	return GUDPBC_NO_NEW_CONN;

} /* End of GUDPBC_NewConn() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPBC_Event
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GUDPBC_Event(U8_T id, U8_T event)
{
	gudpbc_Conns[id].State = event;

} /* End of GUDPBC_Event() */



U8_T udp_receive_reboot(void)
{
	U8_T   socket,id;
	U8_T    *pData;
 //evan move the bootloader jump interface from gudpc.c to http.c 
 // which webpage function have take charge that .c file.

	    if((pData[0] == 0xee) && (pData[1] == 0x10))
	    {   
			gudpbc_HandleSearchReq(pData, id); 
	        IntFlashErase(ERA_RUN, 0x60000);
	        FlagIsp = 1;
			USB_disable();
			lcdreset();
			Lcd_Initial();
			Display_Updating();
	        AX11000_SoftReboot(); 	
		}

   return 	socket;

}



/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPBC_Receive
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GUDPBC_Receive(U8_T XDATA* pData, U16_T length, U8_T id)
{
    U8_T  n=0;
	U32_T time_s=0;
 
	if( (length == 48) )  //(gudpbc_Conns[id].UdpSocket == Time_Server.UdpSocket) && 
	{
		Para[399] = 1;
		time_s = ( ((U32_T)pData[40]) << 24 ) | ( ((U32_T)pData[41]) << 16 ) | ( ((U32_T)pData[42]) << 8 ) |  ((U32_T)pData[43]) ;
		TimeServer_Deal(time_s,Para[23]);
		TCPIP_UdpClose(Time_Server.UdpSocket);
	}
	else
	{
	    if((pData[0] == 100)&&(pData[1] == 0))
	    { 
			scanstart = 1;
	        state = 1;
	    }
	    if(scanstart)
		{  
			for(n = 0; n < (U8_T)length/4; n++)
	        { 
	        	if( (pData[4*n+1] == Para[215])&&(pData[4*n+2] == Para[217])&&(pData[4*n+3] == Para[219])&&(pData[4*n+4] == Para[221]))
	            { 
					scanstart=0;
	                state=0;
	                break;
	            }
	        }

	        if(state)
			{
				U8_T socket = TCPIP_UdpNew(2, 3, 0xffffffff, 0, 4321);
				UdpData();
				TCPIP_UdpSend(socket, 0, 0, ab, 40);
				TCPIP_UdpClose(socket);
			}    	            
	    }
				     
	    if((pData[0] == 0xee) && (pData[1] == 0x10))
	    {   
			gudpbc_HandleSearchReq(pData, id); 
	        IntFlashErase(ERA_RUN, 0x60000);
	        FlagIsp = 1;
			USB_disable();
			lcdreset();
			Lcd_Initial();
			Display_Updating();
	        AX11000_SoftReboot(); 	
	    }
	}
} /* End of GUDPBC_Receive() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: gudpbc_HandleSearchReq
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void gudpbc_HandleSearchReq(U8_T XDATA* pData, U8_T id)
{
	pData = pData;
	UdpData();
	TCPIP_UdpSend(gudpbc_Conns[id].UdpSocket, 0, 0, ab, 40);
}/* End of gudpbc_HandleSearchReq() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: gudpbc_HandleSetReq
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void gudpbc_HandleSetReq(U8_T XDATA* pData, U16_T length, U8_T id)
{
#if GUDPBC_ENABLE_DEBUG_MSG
	printd("gudpbc_HandleSetReq()...\n\r");
#endif

#if GS2E_ENABLE_STATE_MACHINE	
	if (GS2E_GetTaskState() == GS2E_STATE_IDLE)
#else
	if (1)
#endif
	{
		GCONFIG_SetConfigPacket(&gudpbc_ConfigRxPkt);
		*(pData + GCONFIG_OPCODE_OFFSET) = GCONFIG_OPCODE_SET_ACK;
		TCPIP_UdpSend(gudpbc_Conns[id].UdpSocket, 0, 0, pData, length);
   	}
	else
	{
		*(pData + GCONFIG_OPCODE_OFFSET) = GCONFIG_OPCODE_SET_DENY;  	
		TCPIP_UdpSend(gudpbc_Conns[id].UdpSocket, 0, 0, pData, length);		
	}
} /* End of gudpbc_HandleSetReq() */



/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetFirmwareUpgradeMode
 * Purpose: 
 * Params: mode = 1: enable firmware ipgrade after reboot ,  mode = 0: disable
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
//void GCONFIG_SetFirmwareUpgradeMode(U8_T mode)
//{
//	gconfig_ConfigData.FirmwareUpgradeMode = mode;
//} /* End of GCONFIG_SetFirmwareUpgradeMode() */


/*
 * ----------------------------------------------------------------------------
 * Function Name: gudpbc_HandleUpgradeReq
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void gudpbc_HandleUpgradeReq(U8_T XDATA* pData, U16_T length, U8_T id)
{	
#if GUDPBC_ENABLE_DEBUG_MSG
	printd("gudpbc_HandleUpgradeReq()...\n\r");
#endif

#if GS2E_ENABLE_STATE_MACHINE	
	if (GS2E_GetTaskState() == GS2E_STATE_IDLE)
#else
	if (1)
#endif
	{
//		GCONFIG_SetFirmwareUpgradeMode(GCONFIG_FW_UPGRADE_ENABLE);
		GCONFIG_WriteConfigData();
		*(pData + GCONFIG_OPCODE_OFFSET) = GCONFIG_OPCODE_UPGRADE_ACK;
		TCPIP_UdpSend(gudpbc_Conns[id].UdpSocket, 0, 0, pData, length);
	//	FirmwareUpdate();
	}
	else
	{
		*(pData + GCONFIG_OPCODE_OFFSET) = GCONFIG_OPCODE_UPGRADE_DENY;  	
		TCPIP_UdpSend(gudpbc_Conns[id].UdpSocket, 0, 0, pData, length);
	}
} /* End of gudpbc_HandleUpgradeReq() */



/*
 * ----------------------------------------------------------------------------
 * Function Name: gudpbc_HandleResetReq
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void gudpbc_HandleResetReq(U8_T XDATA* pData, U16_T length, U8_T id)
{
#if GUDPBC_ENABLE_DEBUG_MSG
	printd("gudpbc_HandleResetReq()...\n\r");
#endif

#if GS2E_ENABLE_STATE_MACHINE	
	if (GS2E_GetTaskState() == GS2E_STATE_IDLE)
#else
	if (1)
#endif
	{
		GCONFIG_ReadDefaultConfigData();
		GCONFIG_WriteConfigData();
		GCONFIG_GetConfigPacket(&gudpbc_ConfigRxPkt);
	 	gudpbc_ConfigRxPkt.Opcode = GCONFIG_OPCODE_RESET_ACK;
		TCPIP_UdpSend(gudpbc_Conns[id].UdpSocket, 0, 0, (U8_T*) &gudpbc_ConfigRxPkt, GCONFIG_CFG_PKT_LEN);
	}
	else
	{
		*(pData + GCONFIG_OPCODE_OFFSET) = GCONFIG_OPCODE_RESET_DENY;  	
		TCPIP_UdpSend(gudpbc_Conns[id].UdpSocket, 0, 0, pData, length);
	}
} /* End of gudpbc_HandleResetReq() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: gudpbc_HandleRebootReq
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void gudpbc_HandleRebootReq(U8_T XDATA* pData, U16_T length, U8_T id)
{
#if GUDPBC_ENABLE_DEBUG_MSG
	printd("gudpbc_HandleRebootReq()...\n\r");
#endif

#if GS2E_ENABLE_STATE_MACHINE
	if (GS2E_GetTaskState() == GS2E_STATE_IDLE)
#else
	if (1)
#endif
	{
		*(pData + GCONFIG_OPCODE_OFFSET) = GCONFIG_OPCODE_REBOOT_ACK;  	
		TCPIP_UdpSend(gudpbc_Conns[id].UdpSocket, 0, 0, pData, length);
		// May store current status/setting here before restart
		lcdreset();
		Lcd_Initial();
		Display_Updating();
		AX11000_SoftReboot();
	}
	else
	{
		*(pData + GCONFIG_OPCODE_OFFSET) = GCONFIG_OPCODE_RESET_DENY;  	
		TCPIP_UdpSend(gudpbc_Conns[id].UdpSocket, 0, 0, pData, length);
	}
} /* End of gudpbc_HandleRebootReq() */

#if GUDPBC_EEPROM_CONFIG
/*
 * ----------------------------------------------------------------------------
 * Function Name: gudpbc_HandleEepromReadReq
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void gudpbc_HandleEepromReadReq(U8_T XDATA* pData, U16_T length, U8_T id)
{
#if GUDPBC_ENABLE_DEBUG_MSG
	printd("gudpbc_HandleEepromReadReq()...\n\r");
#endif

	GCONFIG_GetConfigPacket(&gudpbc_ConfigRxPkt);
	*(pData + GCONFIG_OPCODE_OFFSET) = GCONFIG_OPCODE_EEPROM_READ_ACK;
	TCPIP_UdpSend(gudpbc_Conns[id].UdpSocket, 0, 0, pData, length);
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: gudpbc_HandleEepromWriteReq
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void gudpbc_HandleEepromWriteReq(U8_T XDATA* pData, U16_T length, U8_T id)
{
#if GUDPBC_ENABLE_DEBUG_MSG
	printd("gudpbc_HandleEepromWriteReq()...\n\r");
#endif

	GCONFIG_SetEpromData(&gudpbc_ConfigRxPkt);
	GCONFIG_SetConfigPacket(&gudpbc_ConfigRxPkt);
	*(pData + GCONFIG_OPCODE_OFFSET) = GCONFIG_OPCODE_EEPROM_WRITE_ACK;
	TCPIP_UdpSend(gudpbc_Conns[id].UdpSocket, 0, 0, pData, length);
}
#endif
/* End of gudpbc.c */
