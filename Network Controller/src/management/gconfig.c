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
 * Module Name: gconfig.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: gconfig.c,v $
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "adapter.h"
#include "gconfig.h"

#include "gs2e.h"
#include "tcpip.h"
#include "mstimer.h"
#include "stoe.h"
#include "uart.h"
#include "reg80390.h"
#include "printd.h"
#include "ax11000.h"
#include "hsuart.h"
#include "filesys.h"

#include <absacc.h>
#include <string.h>

#include "main.h"
#if (INCLUDE_DNS_CLIENT)
#include "dnsc.h"
#endif
/* NAMING CONSTANT DECLARATIONS */
#define DEVICE_STATUS_IDLE			0
#define DEVICE_STATUS_CONNECTED		1
#define ENABLE_FIRMWARE_UPGRADE		0x5A

/* MACRO DECLARATIONS */

/* TYPE DECLARATIONS */
typedef U8_T (*pFlashParaData)(U8_T * addr, U16_T len);

/* GLOBAL VARIABLES DECLARATIONS */
GCONFIG_GID XDATA GCONFIG_Gid = {'A','S','I','X','X','I','S','A'};

/* LOCAL VARIABLES DECLARATIONS */
U8_T XDATA gconfig_SysClock;
GCONFIG_CFG_DATA XDATA gconfig_ConfigData;
U8_T IDATA FirmwareUpgradeFlag[4] _at_ 0x36;
static GCONFIG_MAC_ADDR macAddr;

U8_T XDATA gs2e_State;


/* LOCAL SUBPROGRAM DECLARATIONS */
static BOOL	gconfig_ReStoreParameter(U32_T addr, GCONFIG_CFG_DATA *pConfig, U16_T len);
static BOOL gconfig_StoreParameter(GCONFIG_CFG_DATA *pSramBase, U16_T len);
static U16_T gconfig_Checksum(U16_T *pBuf, U32_T length);
static void	gconfig_DisplayConfigData(GCONFIG_CFG_DATA *pConfig);

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_Task
 * Purpose: Main function
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_Task(void)
{

} /* End of GCONFIG_Task() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GS2E_GetTaskState
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GS2E_GetTaskState(void)
{
	return gs2e_State;
} /* End of GS2E_GetTaskState() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GS2E_SetTaskState
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GS2E_SetTaskState(U8_T state)
{
	gs2e_State = state;
} /* End of GS2E_SetTaskState() */



/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_Init
 * Purpose: Initialization
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
//void GCONFIG_Init(void)
//{
//	U16_T portCfg;
//	U16_T baudRateDiv;
//	U8_T  dataStopParityBits = 0;
//	U16_T val;
//	U8_T  flowCtrl, rs485;
//	
//	// Restore last-saved configuration if applicable	
//	GS2E_SetTaskState(GS2E_STATE_IDLE);
//    memcpy((char *)&macAddr, PNetStation->CurrStaAddr, MAC_ADDRESS_LEN);
//	GCONFIG_ReadConfigData();
//
//	// UART 2 parameters setting
//	portCfg = GCONFIG_GetSerialPort();
//	
//	gconfig_SysClock = AX11000_GetSysClk();
//	
//	val = (portCfg >> 11) & 0x001F;
// 
//	baudRateDiv = GCONFIG_GetBaudRate(val);
//
//	val = (portCfg >> 8) & 0x0007; 
//	if (val == 0) 		dataStopParityBits |= UR2_CHAR_5;
//	else if (val == 1) 	dataStopParityBits |= UR2_CHAR_6;
//	else if (val == 2) 	dataStopParityBits |= UR2_CHAR_7;
//	else 				dataStopParityBits |= UR2_CHAR_8;
//
//	val = (portCfg >> 5) & 0x0007; 
//	if (val == 0 || val == 1) dataStopParityBits |= UR2_PARITY_ENB;
//	if (val == 1) 			  dataStopParityBits |= UR2_EVEN_PARITY;
//
//	val = portCfg & 0x0003; 
//	if (val == 0) 	dataStopParityBits |= UR2_STOP_10;
//	else 			dataStopParityBits |= UR2_STOP_15;
//	
//	val = (portCfg >> 2) & 0x0007; 
//	if (val == 0) 		flowCtrl = UR2_FLOW_CTRL_X;
//	else if (val == 1) 	flowCtrl = UR2_FLOW_CTRL_HW;
//	else 				flowCtrl = UR2_FLOW_CTRL_NO;
//
//    rs485 = (UR2_DTR | UR2_RTS);
//    val = GCONFIG_GetRs485Mode();
//
//    if (val == 1)
//        rs485 |= UR2_RS485_RECEIVE;
//    else if (val == 2)
//        rs485 |= UR2_RS485_DRIVE;
//    else if (val == 3)
//        rs485 |= (UR2_RS485_DRIVE | UR2_RS485_RECEIVE);
//
//	HSUR_Setup( baudRateDiv, 
//	            dataStopParityBits, 
//				(UR2_RDI_ENB|UR2_RLSI_ENB|UR2_MSI_ENB),
//				(UR2_FIFO_MODE|UR2_RXFIFO_RST|UR2_TXFIFO_RST|UR2_TRIG_08), 
//				rs485);
// 
//	HSUR_SetFlowControl(flowCtrl);	
//
//} /* End of GCONFIG_Init() */

/////////////////////////////////////////////////////////////////////////////////

void GCONFIG_Init(void)
{
	U16_T portCfg = 0;
	U16_T baudRateDiv = 0;
	U8_T  dataStopParityBits = 0;
	U16_T val = 0;
	U8_T  sysClock = 0; 
	U8_T  flowCtrl = 0;

//	GCONFIG_PRINTD("GCONFIG_Init()...\n\r");

	// Restore last-saved configuration if applicable	
	GCONFIG_ReadConfigData();

//	if (gconfig_ConfigData.FirmwareUpgradeMode == GCONFIG_FW_UPGRADE_ENABLE)
//	{
//		gconfig_ConfigData.FirmwareUpgradeMode = GCONFIG_FW_UPGRADE_DISABLE;
//
//		//GCONFIG_WriteConfigData();
//	}

} /* End of GCONFIG_Init() */


/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetConfigPacket
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetConfigPacket(GCONFIG_CFG_PKT* pCfgPkt)
{
	gconfig_ConfigData.Option = pCfgPkt->Option;
 	gconfig_ConfigData.DevName = pCfgPkt->DevName;
	gconfig_ConfigData.Network = pCfgPkt->Network;
	gconfig_ConfigData.ServerStaticIP = pCfgPkt->ServerStaticIP;
	gconfig_ConfigData.ServerDataPktListenPort = pCfgPkt->ServerDataPktListenPort;
	gconfig_ConfigData.ServerMulticastListenPort = pCfgPkt->ServerMulticastListenPort;
	gconfig_ConfigData.ServerBroadcastListenPort = pCfgPkt->ServerBroadcastListenPort;
	gconfig_ConfigData.ClientDestIP = pCfgPkt->ClientDestIP;
	gconfig_ConfigData.ClientDestPort = pCfgPkt->ClientDestPort; 
	gconfig_ConfigData.Netmask = pCfgPkt->Netmask;
	gconfig_ConfigData.Gateway = pCfgPkt->Gateway;
	gconfig_ConfigData.Dns = pCfgPkt->Dns;
	gconfig_ConfigData.SerialPort = pCfgPkt->SerialPort;		
	gconfig_ConfigData.EthernetTxTimer = pCfgPkt->EthernetTxTimer;

    gconfig_ConfigData.Rs485Mode = pCfgPkt->Rs485Mode;
    memcpy((char *)&gconfig_ConfigData.AccessibleIP[0], (char *)&pCfgPkt->AccessibleIP[0], (GCONFIG_ACCESSIBLE_IP_NUM*4));
    memcpy((char *)&gconfig_ConfigData.Smtp, (char *)&pCfgPkt->Smtp, sizeof(GCONFIG_SMTP_CONFIG));
    memcpy((char *)&gconfig_ConfigData.DestHostName, (char *)&pCfgPkt->DestHostName, 36);
 	
    gconfig_ConfigData.TftpServerIp = pCfgPkt->TftpServerIp;
    memcpy((char *)&gconfig_ConfigData.Filename, (char *)&pCfgPkt->Filename, 128);

	GCONFIG_WriteConfigData();
} /* End of GCONFIG_SetConfigPacket() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetConfigPacket
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_GetConfigPacket(GCONFIG_CFG_PKT* pCfgPkt)
{
    memcpy((char *)&pCfgPkt->Gid, (char *)&GCONFIG_Gid, sizeof(GCONFIG_Gid));
	pCfgPkt->Option = gconfig_ConfigData.Option;
    pCfgPkt->DevName = gconfig_ConfigData.DevName;
    pCfgPkt->MacAddr = macAddr;
	pCfgPkt->Network = gconfig_ConfigData.Network;
    pCfgPkt->ServerDynamicIP = STOE_GetIPAddr();
	pCfgPkt->ServerStaticIP = gconfig_ConfigData.ServerStaticIP;
	pCfgPkt->ServerDataPktListenPort = gconfig_ConfigData.ServerDataPktListenPort;
	pCfgPkt->ServerMulticastListenPort = gconfig_ConfigData.ServerMulticastListenPort;
	pCfgPkt->ServerBroadcastListenPort = gconfig_ConfigData.ServerBroadcastListenPort;
	pCfgPkt->ClientDestIP = gconfig_ConfigData.ClientDestIP;
	pCfgPkt->ClientDestPort = gconfig_ConfigData.ClientDestPort; 
	pCfgPkt->Netmask = gconfig_ConfigData.Netmask;
	pCfgPkt->Gateway = gconfig_ConfigData.Gateway;
	pCfgPkt->Dns = gconfig_ConfigData.Dns;
	pCfgPkt->SerialPort = gconfig_ConfigData.SerialPort;		
	pCfgPkt->EthernetTxTimer = gconfig_ConfigData.EthernetTxTimer;

    pCfgPkt->Rs485Mode = gconfig_ConfigData.Rs485Mode;
    memcpy((char *)&pCfgPkt->AccessibleIP[0], (char *)&gconfig_ConfigData.AccessibleIP[0], (GCONFIG_ACCESSIBLE_IP_NUM*4));
    memcpy((char *)&pCfgPkt->Smtp, (char *)&gconfig_ConfigData.Smtp, sizeof(GCONFIG_SMTP_CONFIG));
    memcpy((char *)&pCfgPkt->DestHostName, (char *)&gconfig_ConfigData.DestHostName, 36);
 	
    pCfgPkt->TftpServerIp = gconfig_ConfigData.TftpServerIp;
    memcpy((char *)&pCfgPkt->Filename[0], (char *)&gconfig_ConfigData.Filename[0], 128);

	if (GS2E_GetTaskState() == GS2E_STATE_IDLE)
		pCfgPkt->DeviceStatus = DEVICE_STATUS_IDLE;
	else
		pCfgPkt->DeviceStatus = DEVICE_STATUS_CONNECTED;

} /* End of GCONFIG_GetConfigPacket() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_ReadConfigData
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_ReadConfigData(void)
{
#ifdef RuntimeCodeAt24KH
	BOOL bRet;

	printd("Read configuration data");
	bRet = gconfig_ReStoreParameter(0, &gconfig_ConfigData, sizeof(gconfig_ConfigData));

	if (bRet == FALSE || (gconfig_ConfigData.ServerStaticIP & 0x000000FF) == 0)
	{
		GCONFIG_ReadDefaultConfigData();
		GCONFIG_WriteConfigData();
		gconfig_DisplayConfigData(&gconfig_ConfigData);
	}

#else
		GCONFIG_ReadDefaultConfigData();
		gconfig_DisplayConfigData(&gconfig_ConfigData);
#endif

} /* End of GCONFIG_ReadConfigData() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_WriteConfigData
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_WriteConfigData(void)
{
#ifdef RuntimeCodeAt24KH
	gconfig_StoreParameter(&gconfig_ConfigData, (U16_T)sizeof(gconfig_ConfigData));
#endif	
} /* End of GCONFIG_WriteConfigData() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_ReadDefaultConfigData
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_ReadDefaultConfigData(void)
{
    U8_T i;

	printd("Read default configuration data. \n\r");

	gconfig_ConfigData.CheckSum = 0x00;
    gconfig_ConfigData.CfgLength = sizeof(gconfig_ConfigData);
	gconfig_ConfigData.UdpAutoConnectClientIp = 0x00000000;
	gconfig_ConfigData.UdpAutoConnectClientPort = 0x0000;

	gconfig_ConfigData.Option = 0;
 	memset(&gconfig_ConfigData.DevName, 0, sizeof(GCONFIG_DEV_NAME));

	gconfig_ConfigData.Network = (GCONFIG_NETWORK_SERVER | 
                                            GCONFIG_NETWORK_DHCP_ENABLE |
                                            GCONFIG_NETWORK_PROTO_TCP |
											GCONFIG_NETWORK_PROTO_UDP_BCAST
										   );

	gconfig_ConfigData.ServerStaticIP = 0xc0a80003;	// 192.168.0.3
	gconfig_ConfigData.ServerDataPktListenPort = GCONFIG_DEFAULT_DATA_PORT;
	gconfig_ConfigData.ServerMulticastListenPort = GCONFIG_UDP_MCAST_SERVER_PORT;
	gconfig_ConfigData.ServerBroadcastListenPort = GCONFIG_UDP_BCAST_SERVER_PORT;
	gconfig_ConfigData.ClientDestIP = 0xc0a80002; 	// 192.168.0.2
	gconfig_ConfigData.ClientDestPort = GCONFIG_DEFAULT_DATA_PORT; 
	gconfig_ConfigData.Netmask = 0xffffff00; 			// 255.255.255.0
	gconfig_ConfigData.Gateway = 0xc0a80001; 			// 192.168.0.1
	gconfig_ConfigData.Dns = 0xa85f0101; 				// 168.95.1.1

	gconfig_ConfigData.SerialPort = (GCONFIG_SPORT_BRATE_115200 |
	                   			   GCONFIG_SPORT_DATABIT_8 |
								   GCONFIG_SPORT_PARITY_NONE |
								   GCONFIG_SPORT_FLOWC_NONE |
								   GCONFIG_SPORT_STOPBIT_1
								  );

	gconfig_ConfigData.EthernetTxTimer = 100; // 100 ms

    strcpy(gconfig_ConfigData.Admin.Username, "admin");
    strcpy(gconfig_ConfigData.Admin.Passwd, "admin");
    gconfig_ConfigData.Admin.Level = 5;

    for (i = 0; i < GCONFIG_ACCESSIBLE_IP_NUM; i++)
    {
        gconfig_ConfigData.AccessibleIP[i] = 0;
    }

    strcpy(gconfig_ConfigData.Smtp.DomainName, "");
    strcpy(gconfig_ConfigData.Smtp.FromAddr, "");
    strcpy(gconfig_ConfigData.Smtp.ToAddr1, "");	
    strcpy(gconfig_ConfigData.Smtp.ToAddr2, "");	
    strcpy(gconfig_ConfigData.Smtp.ToAddr3, "");
	
    gconfig_ConfigData.Smtp.EventEnableBits = 0x0000;

    gconfig_ConfigData.Rs485Mode = 0;

    strcpy(gconfig_ConfigData.DestHostName, "");

    /* the following 5 items will be used for boot loader */
    gconfig_ConfigData.DeviceIp = 0xc0a80003;
    gconfig_ConfigData.DeviceNetmask = 0xFFFFFF00;
    gconfig_ConfigData.DeviceGateway = 0xc0a80001;
    strcpy(gconfig_ConfigData.Filename, "ax.bin");
    gconfig_ConfigData.TftpServerIp = 0xc0a80001;
   
} /* End of GCONFIG_ReadDefaultConfigData */

/////////////////////////////////////////////////////////////////////////////////

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_EnableUdpAutoConnectAfterReboot
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GCONFIG_EnableUdpAutoConnectAfterReboot(void)
{
	if ((gconfig_ConfigData.Option & GCONFIG_OPTION_ENABLE_UDP_AUTO_CONNECT) 
	     == GCONFIG_OPTION_ENABLE_UDP_AUTO_CONNECT)
		return TRUE;
	
	return FALSE;
} /* End of GCONFIG_EnableUdpAutoConnectAfterReboot() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_EnableFirmwareUpgrade
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_EnableFirmwareUpgrade(void)
{
	FirmwareUpgradeFlag[0] = 'a';
	FirmwareUpgradeFlag[1] = 's';
	FirmwareUpgradeFlag[2] = 'i';
	FirmwareUpgradeFlag[3] = 'x';

    /* save the network configuration for boot loader */
    gconfig_ConfigData.DeviceIp = STOE_GetIPAddr();
    gconfig_ConfigData.DeviceNetmask = STOE_GetSubnetMask();
    gconfig_ConfigData.DeviceGateway = STOE_GetGateway();

} /* End of GCONFIG_EnableFirmwareUpgrade() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_IpAddr2Ulong()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GCONFIG_IpAddr2Ulong(U8_T* pBuf, U8_T len)
{
	U32_T	ip = 0;
	U8_T*	point = (U8_T*)&ip;
	U8_T	count = 0;
	U8_T	count2 = 0;

	while (1)
	{
		count2 = 0;
		while ((*pBuf != '.') && len)
		{
			count2++;
			if (count2 > 3) return 0xffffffff;

			*point *= 10;
  
			if ((*pBuf < 0x3a) && (*pBuf > 0x2f))
				*point += (*pBuf - 0x30);
			else
				return 0xffffffff;

			pBuf++;
			len--;
		}
  
		if (len == 0) break;

		pBuf++;
		len--;
		count++;
		point++;

		if (count > 3) return 0xffffffff;
	}

	if (count != 3) return 0xffffffff;

	return ip;
} /* End of GCONFIG_IpAddr2Ulong() */
/////////////////////////////////////////////////////////////////////////////////
// Get Functions

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetDeviceName
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetDeviceName(GCONFIG_DEV_NAME* pDevName)
{
	memcpy(&gconfig_ConfigData.DevName, pDevName, sizeof(GCONFIG_DEV_NAME)); 
} /* End of GCONFIG_GetDeviceName() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetNetwork
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetNetwork(U16_T val)
{
	gconfig_ConfigData.Network = val;	
} /* End of GCONFIG_GetNetwork() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetServerStaticIP
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetServerStaticIP(U32_T ip)
{
	gconfig_ConfigData.ServerStaticIP = ip;	
} /* End of GCONFIG_SetServerStaticIP() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetServerDataPktListenPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetServerDataPktListenPort(U16_T port)
{
	gconfig_ConfigData.ServerDataPktListenPort = port;
} /* End of GCONFIG_SetServerDataPktListenPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetServerMulticastListenPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetServerMulticastListenPort(U16_T port)
{
	gconfig_ConfigData.ServerMulticastListenPort = port;
} /* End of GCONFIG_SetServerMulticastListenPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetServerBroadcastListenPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetServerBroadcastListenPort(U16_T port)
{
	gconfig_ConfigData.ServerBroadcastListenPort = port;
} /* End of GCONFIG_SetServerBroadcastListenPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetClientDestIP
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetClientDestIP(U32_T ip)
{
	gconfig_ConfigData.ClientDestIP = ip;
} /* End of GCONFIG_SetClientDestIP() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetClientDestPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetClientDestPort(U16_T port)
{
	gconfig_ConfigData.ClientDestPort = port;
} /* End of GCONFIG_SetClientDestPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetNetmask
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetNetmask(U32_T netmask)
{
	gconfig_ConfigData.Netmask = netmask;
} /* End of GCONFIG_SetNetmask() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetGateway
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetGateway(U32_T gateway)
{
	gconfig_ConfigData.Gateway = gateway;
} /* End of GCONFIG_SetGateway() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetDNS
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetDNS(U32_T dns)
{
	gconfig_ConfigData.Dns = dns;
} /* End of GCONFIG_SetDNS() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetSerialPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetSerialPort(U16_T sPort)
{
	gconfig_ConfigData.SerialPort = sPort;
} /* End of GCONFIG_SetSerialPort() */


/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetEthernetTxTimer
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetEthernetTxTimer(U16_T timer)
{
	gconfig_ConfigData.EthernetTxTimer = timer;
} /* End of GCONFIG_SetEthernetTxTimer() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetUdpAutoConnectClientIp
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetUdpAutoConnectClientIp(U32_T ip)
{
	gconfig_ConfigData.UdpAutoConnectClientIp = ip;
} /* End of GCONFIG_SetUdpAutoConnectClientIp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetUdpAutoConnectRemotePort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetUdpAutoConnectClientPort(U16_T port)
{
	gconfig_ConfigData.UdpAutoConnectClientPort = port;
} /* End of GCONFIG_SetUdpAutoConnectClientPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetTftpServerIp
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetTftpServerIp(U32_T ip)
{
	gconfig_ConfigData.TftpServerIp = ip;
} /* End of GCONFIG_SetTftpServerIp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetFilename
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GCONFIG_SetFilename(U8_T *filename, U8_T len)
{
	if (len > sizeof(gconfig_ConfigData.Filename) - 1)
		len = sizeof(gconfig_ConfigData.Filename) - 1;

	memcpy(gconfig_ConfigData.Filename, filename, len); 
	gconfig_ConfigData.Filename[len] = '\0'; 	
    return len;
} /* End of GCONFIG_SetFilename() */

/////////////////////////////////////////////////////////////////////////////////
// Get Functions

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetTftpServerIp
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GCONFIG_GetTftpServerIp(void)
{
	return gconfig_ConfigData.TftpServerIp; 
} /* End of GCONFIG_GetTftpServerIp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetFilename
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GCONFIG_GetFilename(U8_T *filename, U8_T len)
{
    if (!filename || len < sizeof(gconfig_ConfigData.Filename))
        return 0;

    memcpy(filename, gconfig_ConfigData.Filename, sizeof(gconfig_ConfigData.Filename)); 

    return sizeof(gconfig_ConfigData.Filename);	
} /* End of GCONFIG_GetFilename() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetDeviceName
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
GCONFIG_DEV_NAME* GCONFIG_GetDeviceName(void)
{
	return &gconfig_ConfigData.DevName;
} /* End of GCONFIG_GetDeviceName() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetMacAddress
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
GCONFIG_MAC_ADDR GCONFIG_GetMacAddress(void)
{
	return macAddr;
} /* End of GCONFIG_GetMacAddress() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetNetwork
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GCONFIG_GetNetwork(void)
{
	return gconfig_ConfigData.Network;
} /* End of GCONFIG_GetNetwork() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetServerStaticIP
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GCONFIG_GetServerStaticIP(void)
{
	return gconfig_ConfigData.ServerStaticIP;
} /* End of GCONFIG_GetServerStaticIP() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetServerDataPktListenPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GCONFIG_GetServerDataPktListenPort(void)
{
	return gconfig_ConfigData.ServerDataPktListenPort;
} /* End of GCONFIG_GetServerDataPktListenPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetServerMulticastListenPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GCONFIG_GetServerMulticastListenPort(void)
{
	return gconfig_ConfigData.ServerMulticastListenPort;
} /* End of GCONFIG_GetServerMulticastListenPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetServerBroadcastListenPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GCONFIG_GetServerBroadcastListenPort(void)
{
	return gconfig_ConfigData.ServerBroadcastListenPort;
} /* End of GCONFIG_GetServerBroadcastListenPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetClientDestIP
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GCONFIG_GetClientDestIP(void)
{
#if (INCLUDE_DNS_CLIENT)
	U32_T	DestIP, DestNameLen;
    teDNSC_STATE state;

	DestNameLen = strlen(gconfig_ConfigData.DestHostName);
	DestIP = GCONFIG_IpAddr2Ulong(gconfig_ConfigData.DestHostName, DestNameLen);
	if (DestIP == 0xffffffff)
	{
		if ((state = DNSC_Query(gconfig_ConfigData.DestHostName, &DestIP)) == DNSC_QUERY_OK)
			return DestIP;
		else if (state == DNSC_QUERY_FREE)
			DNSC_Start(gconfig_ConfigData.DestHostName);
		return 0;		
	}
	return DestIP;
#else
	return gconfig_ConfigData.ClientDestIP;
#endif			
} /* End of GCONFIG_GetClientDestIP() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetClientDestPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GCONFIG_GetClientDestPort(void)
{
	return gconfig_ConfigData.ClientDestPort;
} /* End of GCONFIG_GetClientDestPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetNetmask
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GCONFIG_GetNetmask(void)
{
	return gconfig_ConfigData.Netmask;
} /* End of GCONFIG_GetNetmask() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetGateway
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GCONFIG_GetGateway(void)
{
	return gconfig_ConfigData.Gateway;
} /* End of GCONFIG_GetGateway() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetDNS
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GCONFIG_GetDNS(void)
{
	return gconfig_ConfigData.Dns;
} /* End of GCONFIG_GetDNS() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetSerialPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GCONFIG_GetSerialPort(void)
{
	return gconfig_ConfigData.SerialPort;
} /* End of GCONFIG_GetSerialPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetEthernetTxTimer
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GCONFIG_GetEthernetTxTimer(void)
{
	return gconfig_ConfigData.EthernetTxTimer;
} /* End of GCONFIG_GetEthernetTxTimer() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetUdpAutoConnectClientIp
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GCONFIG_GetUdpAutoConnectClientIp(void)
{
	return gconfig_ConfigData.UdpAutoConnectClientIp;
} /* End of GCONFIG_GetUdpAutoConnectClientIp() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetUdpAutoConnectClientPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GCONFIG_GetUdpAutoConnectClientPort(void)
{
	return gconfig_ConfigData.UdpAutoConnectClientPort;
} /* End of GCONFIG_GetUdpAutoConnectClientPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetBaudRate
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GCONFIG_GetBaudRate(U8_T index)
{
	U16_T baudRate = 0;

	switch(gconfig_SysClock)
	{
		case SCS_25M:
			if 	    (index == 0) baudRate = UR2_BR25_921600;
			else if (index == 1) baudRate = UR2_BR25_115200;
			else if (index == 2) baudRate = UR2_BR25_57600;
			else if (index == 3) baudRate = UR2_BR25_38400;
			else if (index == 4) baudRate = UR2_BR25_19200;
			else if (index == 5) baudRate = UR2_BR25_9600;
			else if (index == 6) baudRate = UR2_BR25_4800;
			else if (index == 7) baudRate = UR2_BR25_2400;
			else if (index == 8) baudRate = UR2_BR25_1200;
			break;
		case SCS_50M:
			if 	    (index == 0) baudRate = UR2_BR50_921600;
			else if (index == 1) baudRate = UR2_BR50_115200;
			else if (index == 2) baudRate = UR2_BR50_57600;
			else if (index == 3) baudRate = UR2_BR50_38400;
			else if (index == 4) baudRate = UR2_BR50_19200;
			else if (index == 5) baudRate = UR2_BR50_9600;
			else if (index == 6) baudRate = UR2_BR50_4800;
			else if (index == 7) baudRate = UR2_BR50_2400;
			else if (index == 8) baudRate = UR2_BR50_1200;
			break;
		case SCS_100M:
			if 	    (index == 0) baudRate = UR2_BR100_921600;
			else if (index == 1) baudRate = UR2_BR100_115200;
			else if (index == 2) baudRate = UR2_BR100_57600;
			else if (index == 3) baudRate = UR2_BR100_38400;
			else if (index == 4) baudRate = UR2_BR100_19200;
			else if (index == 5) baudRate = UR2_BR100_9600;
			else if (index == 6) baudRate = UR2_BR100_4800;
			else if (index == 7) baudRate = UR2_BR100_2400;
			else if (index == 8) baudRate = UR2_BR100_1200;
			break;
		default:
			printd("Unknown system clock rate!\n\r");
			break;
	}
	
	return baudRate;
} /* End of GCONFIG_GetBaudRate() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetAdmin
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
S16_T GCONFIG_GetAdmin(U8_T *username, U8_T *passwd, U8_T *level)
{
    if (!username || !passwd)
        return -1;

    memcpy(username, gconfig_ConfigData.Admin.Username, 16);
    memcpy(passwd, gconfig_ConfigData.Admin.Passwd, 16);
    *level = gconfig_ConfigData.Admin.Level;

    return 1;
} /* End of GCONFIG_GetAdmin() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetAdmin
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
S16_T GCONFIG_SetAdmin(U8_T *username, U8_T *passwd)
{
    if (!username || !passwd)
        return -1;

    memcpy(gconfig_ConfigData.Admin.Username, username, 16);
    memcpy(gconfig_ConfigData.Admin.Passwd, passwd, 16);

    return 1;
} /* End of GCONFIG_SetAdmin() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetAccessibleIP
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
S16_T GCONFIG_GetAccessibleIP(U8_T idx, U32_T *ip)
{
    if (!ip || idx >= GCONFIG_ACCESSIBLE_IP_NUM)
        return -1;

    *ip = gconfig_ConfigData.AccessibleIP[idx];
    return 1;

} /* End of GCONFIG_GetAccessibleIP() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetAccessibleIP
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
S16_T GCONFIG_SetAccessibleIP(U8_T idx, U32_T ip)
{
    if (idx >= GCONFIG_ACCESSIBLE_IP_NUM)
        return -1;

    gconfig_ConfigData.AccessibleIP[idx] = ip;
    return 1;
} /* GCONFIG_SetAccessibleIP() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetSMTPDomainName
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetSMTPDomainName(U8_T *pIn, U8_T len)
{
	if (len > sizeof(gconfig_ConfigData.Smtp.DomainName) - 1)
		len = sizeof(gconfig_ConfigData.Smtp.DomainName) - 1;
	
	memcpy(gconfig_ConfigData.Smtp.DomainName, pIn, len);
	gconfig_ConfigData.Smtp.DomainName[len] = '\0';
} /* GCONFIG_SetSMTPDomainName() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: U8_T GCONFIG_GetSMTPDomainName
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GCONFIG_GetSMTPDomainName(U8_T *pOut)
{
	gconfig_ConfigData.Smtp.DomainName[sizeof(gconfig_ConfigData.Smtp.DomainName) - 1] = '\0';
    strcpy(pOut, gconfig_ConfigData.Smtp.DomainName);

	return strlen(gconfig_ConfigData.Smtp.DomainName);
} /* GCONFIG_GetSMTPDomainName() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetSMTPFrom
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetSMTPFrom(U8_T *pIn, U8_T len)
{
	if (len > sizeof(gconfig_ConfigData.Smtp.FromAddr) - 1)
		len = sizeof(gconfig_ConfigData.Smtp.FromAddr) - 1;
	
	memcpy(gconfig_ConfigData.Smtp.FromAddr, pIn, len);
	gconfig_ConfigData.Smtp.FromAddr[len] = '\0';
} /* GCONFIG_SetSMTPFrom() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: U8_T GCONFIG_GetSMTPFrom()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GCONFIG_GetSMTPFrom(U8_T *pOut)
{
	gconfig_ConfigData.Smtp.FromAddr[sizeof(gconfig_ConfigData.Smtp.FromAddr) - 1] = '\0';
    strcpy(pOut, gconfig_ConfigData.Smtp.FromAddr);

	return strlen(gconfig_ConfigData.Smtp.FromAddr);
} /* GCONFIG_GetSMTPFrom() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetSMTPTo1
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetSMTPTo1(U8_T *pIn, U8_T len)
{
	if (len > sizeof(gconfig_ConfigData.Smtp.ToAddr1) - 1)
		len = sizeof(gconfig_ConfigData.Smtp.ToAddr1) - 1;
	
	memcpy(gconfig_ConfigData.Smtp.ToAddr1, pIn, len);
	gconfig_ConfigData.Smtp.ToAddr1[len] = '\0';
} /* GCONFIG_SetSMTPTo1() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: U8_T GCONFIG_GetSMTPTo1()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GCONFIG_GetSMTPTo1(U8_T *pOut)
{
	gconfig_ConfigData.Smtp.ToAddr1[sizeof(gconfig_ConfigData.Smtp.ToAddr1) - 1] = '\0';
    strcpy(pOut, gconfig_ConfigData.Smtp.ToAddr1);

	return strlen(gconfig_ConfigData.Smtp.ToAddr1);
} /* GCONFIG_GetSMTPTo1() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetSMTPTo2
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetSMTPTo2(U8_T *pIn, U8_T len)
{
	if (len > sizeof(gconfig_ConfigData.Smtp.ToAddr2) - 1)
		len = sizeof(gconfig_ConfigData.Smtp.ToAddr2) - 1;
	
	memcpy(gconfig_ConfigData.Smtp.ToAddr2, pIn, len);
	gconfig_ConfigData.Smtp.ToAddr2[len] = '\0';
} /* GCONFIG_SetSMTPTo2() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: U8_T GCONFIG_GetSMTPTo2()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GCONFIG_GetSMTPTo2(U8_T *pOut)
{
	gconfig_ConfigData.Smtp.ToAddr2[sizeof(gconfig_ConfigData.Smtp.ToAddr2) - 1] = '\0';
    strcpy(pOut, gconfig_ConfigData.Smtp.ToAddr2);

	return strlen(gconfig_ConfigData.Smtp.ToAddr2);
} /* GCONFIG_GetSMTPTo2() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetSMTPTo3
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetSMTPTo3(U8_T *pIn, U8_T len)
{
	if (len > sizeof(gconfig_ConfigData.Smtp.ToAddr3) - 1)
		len = sizeof(gconfig_ConfigData.Smtp.ToAddr3) - 1;
	
	memcpy(gconfig_ConfigData.Smtp.ToAddr3, pIn, len);
	gconfig_ConfigData.Smtp.ToAddr3[len] = '\0';
} /* GCONFIG_SetSMTPTo3() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: U8_T GCONFIG_GetSMTPTo3()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GCONFIG_GetSMTPTo3(U8_T *pOut)
{
	gconfig_ConfigData.Smtp.ToAddr3[sizeof(gconfig_ConfigData.Smtp.ToAddr3) - 1] = '\0';
    strcpy(pOut, gconfig_ConfigData.Smtp.ToAddr3);

	return strlen(gconfig_ConfigData.Smtp.ToAddr3);	
} /* GCONFIG_GetSMTPTo3() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetAutoWarning
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetAutoWarning(U16_T ValueIn)
{
	gconfig_ConfigData.Smtp.EventEnableBits = ValueIn;
} /* GCONFIG_SetAutoWarning() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetAutoWarning
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GCONFIG_GetAutoWarning(void)
{
	return gconfig_ConfigData.Smtp.EventEnableBits;
} /* GCONFIG_GetAutoWarning() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetRs485Mode
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetRs485Mode(U8_T mode)
{
	gconfig_ConfigData.Rs485Mode = mode;
} /* GCONFIG_SetAutoWarning() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetRs485Mode
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GCONFIG_GetRs485Mode(void)
{
	return gconfig_ConfigData.Rs485Mode;
} /* GCONFIG_GetRs485Mode() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetDestHostName
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetDestHostName(U8_T *pIn, U8_T len)
{
    if (len > (sizeof(gconfig_ConfigData.DestHostName)-1))
        len = sizeof(gconfig_ConfigData.DestHostName) - 1;

    memcpy(gconfig_ConfigData.DestHostName, pIn, len);
    gconfig_ConfigData.DestHostName[len] = '\0';

} /* End of GCONFIG_SetDestHostName() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetDestHostName
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GCONFIG_GetDestHostName(U8_T *pOut)
{
    gconfig_ConfigData.DestHostName[sizeof(gconfig_ConfigData.DestHostName) - 1] = '\0';
    strcpy(pOut, gconfig_ConfigData.DestHostName);

	return strlen(gconfig_ConfigData.DestHostName);
} /* End of GCONFIG_GetDestHostName() */
/////////////////////////////////////////////////////////////////////////////////

/*
 * ----------------------------------------------------------------------------
 * Function Name: gconfig_ReStoreParameter
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static BOOL gconfig_ReStoreParameter(U32_T addr, GCONFIG_CFG_DATA *pConfig, U16_T len)
{
	U16_T	i;
	U8_T	*pParaBaseByte;
	U8_T	paraCheckSum = 0;
	U8_T	lastWtst = 0;

	pParaBaseByte = (U8_T *)pConfig;

	lastWtst = WTST;
	WTST = PROG_WTST_7;
	if (CSREPR & PMS) // SRAM shadow
	{
		CSREPR |= FAES;
		for (i = 0 ; i < len ; i++)
		{
			*(pParaBaseByte + i) = FCVAR(U8_T, GCONFIG_CFG_DATA_FLASH_ADDR + addr + i);
		}
		CSREPR &= ~FAES;
	}
	else
	{
		CSREPR &= ~FAES;
		for (i = 0 ; i < len ; i++)
		{
			*(pParaBaseByte + i) = FCVAR(U8_T, GCONFIG_CFG_DATA_FLASH_ADDR + addr + i);
		}
	}
	WTST = lastWtst;

    if (0xffff != gconfig_Checksum((U16_T *)pConfig, len))
    {
        printd(" failed! (wrong checksum)\n\r");
		return FALSE;
    }
    else if (pConfig->CfgLength != len)
    {
        printd(" Invalid configuration data!\n\r");
		return FALSE;
    }
	printd(" ok.\n\r");
	gconfig_DisplayConfigData(pConfig);
	return TRUE;

} /* End of gconfig_ReStoreParameter() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: gconfig_StoreParameter
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static BOOL gconfig_StoreParameter(GCONFIG_CFG_DATA *pConfigData, U16_T len)
{
	U8_T			ret = FALSE;
	pFlashParaData  ptrFlashWrite = (void code*)0x003F00;

    pConfigData->CheckSum = 0;
    pConfigData->CfgLength = len;
    pConfigData->CheckSum = ~gconfig_Checksum((U16_T *)pConfigData, len);
    
	ret = (*ptrFlashWrite)((U8_T *)pConfigData, len);	

	if (ret == FALSE)
		printd("Failed to program Configration Data!!\r\n");

	return ret;
} /* End of gconfig_StoreParameter() */

/*
* -----------------------------------------------------------------------------
 * Function Name: gconfig_Checksum
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static U16_T gconfig_Checksum(U16_T *pBuf, U32_T length)
{
	U32_T	cksum = 0;
	U32_T	i, count;
	U8_T*	inChar = &pBuf;
	U16_T*	point;

	count = length/2;

	for (i = 0; i < count; i++)
	{
		point = pBuf;
		cksum += *pBuf++;
		if (point > pBuf)
			(*inChar) = *inChar + 1;

		if (!(i % 0x8000))
		{
			cksum = (cksum >> 16) + (cksum & 0xffff);
			cksum += (cksum >> 16);
			cksum &= 0xffff;
		}
	}
		
	if (length % 2)
		cksum += (*pBuf & 0xff00);

	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	cksum &= 0xffff;

	return ((U16_T)cksum);
} /* End of gconfig_Checksum() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: gconfig_DisplayConfigData
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void	gconfig_DisplayConfigData(GCONFIG_CFG_DATA *pConfigData)
{
	U8_T i, *pData;
	U8_T dat;
	U16_T val;

	if (GS2E_GetTaskState() == GS2E_STATE_IDLE)
	{
		printd("  Device Name: ");
		for (i = 0; i < 16; i++)
			printd ("%02bx ", pConfigData->DevName.DevName[i]);		

		printd("\n\r");
		printd("  MAC Addr: ");
		for (i = 0; i < 6; i++)
			printd ("%02bx ", macAddr.MacAddr[i]);		
	
		printd("\n\r");
		printd("  Network Setting: ");
		printd ("%04x\r\n", pConfigData->Network);		
	
		val = pConfigData->Network;
		
		if (val & GCONFIG_NETWORK_CLIENT) printd("  SC:Cli ");
		else 					printd("  SC:Ser ");
	
		if (val & GCONFIG_NETWORK_DHCP_ENABLE) printd("DHCP:On ");
		else 					printd("DHCP:Off ");
	
		if (val & GCONFIG_NETWORK_PROTO_UDP) printd("UDP:On ");
		else 					printd("UDP:Off ");
	
		if (val & GCONFIG_NETWORK_PROTO_TCP) printd("TCP:On ");
		else 					printd("TCP:Off ");
	
		if (val & GCONFIG_NETWORK_PROTO_UDP_MCAST) printd("MC:On ");
		else 					printd("MC:Off ");
	
		if (val & GCONFIG_NETWORK_PROTO_UDP_BCAST) printd("BC:On ");
		else 					printd("BC:Off ");
	
		printd("\n\r");
	
		printd("  SIP:");		
        pData = (U8_T *)&pConfigData->ServerStaticIP;
		for (i = 0; i < 4; i++)
			printd ("%bu ", *(pData + i));		

		printd(" Port: DA: %u", pConfigData->ServerDataPktListenPort);
		printd(" MC: %u", pConfigData->ServerMulticastListenPort);
		printd(" BC: %u", pConfigData->ServerBroadcastListenPort);
		printd("\n\r");

		printd("  Dest Host: %s",pConfigData->DestHostName);
		printd(" Dest Port: %u", pConfigData->ClientDestPort);
		printd("\n\r");
		printd("  Netmask:");
        pData = (U8_T *)&pConfigData->Netmask;
		for (i = 0; i < 4; i++)
			printd ("%bu ", *(pData + i));		

		printd(" Gateway:");
        pData = (U8_T *)&pConfigData->Gateway;
		for (i = 0; i < 4; i++)
			printd ("%bu ", *(pData + i));		

		printd(" DNS:");
        pData = (U8_T *)&pConfigData->Dns;
		for (i = 0; i < 4; i++)
			printd ("%bu ", *(pData + i));		

		printd("\n\r");
		printd("  Serial Port Setting: ");
	
		dat = (pConfigData->SerialPort>>8) & 0xFF;
		val = (dat >> 3) & 0x1F; 
		if      (val == 0) printd ("BR:921600 ");
		else if (val == 1) printd ("BR:115200 ");
		else if (val == 2) printd ("BR:57600 ");
		else if (val == 3) printd ("BR:38400 ");
		else if (val == 4) printd ("BR:19200 ");
		else if (val == 5) printd ("BR:9600 ");
		else if (val == 6) printd ("BR:4800 ");
		else if (val == 7) printd ("BR:2400 ");
		else if (val == 8) printd ("BR:1200 ");
	
		val = dat & 0x07; 
		if (val == 0) printd ("DB:5 ");
		else if (val == 1) printd ("DB:6 ");
		else if (val == 2) printd ("DB:7 ");
		else if (val == 3) printd ("DB:8 ");
	
		dat = (pConfigData->SerialPort & 0x00FF);
	
		val = (dat >> 5) & 0x07; 
		if (val == 0) printd ("P:Odd ");
		else if (val == 1) printd ("P:Even ");
		else if (val == 2) printd ("P:None ");
	
		val = (dat >> 2) & 0x07; 
		if (val == 0) printd ("FC:Xon-Xoff ");
		else if (val == 1) printd ("FC:Hardware ");
		else if (val == 2) printd ("FC:None ");
	
		val = dat & 0x03; 
		if (val == 0) printd ("SB:1 ");
		else if (val == 1) printd ("SB:1.5 ");

		printd("\n\r");
		printd("  Tx Time Interval:%u", pConfigData->EthernetTxTimer);
		printd(" Username:%s Password:%s",pConfigData->Admin.Username, pConfigData->Admin.Passwd);
		printd("\n\r");
		
		printd("  E-Mail Server:%s",pConfigData->Smtp.DomainName);		
		printd("\n\r");
				
		printd("  From:%s",pConfigData->Smtp.FromAddr);
		printd("  To1:%s",pConfigData->Smtp.ToAddr1);
		printd("\n\r");
		
		printd("  To2:%s",pConfigData->Smtp.ToAddr2);
		printd("  To3:%s",pConfigData->Smtp.ToAddr3);
		printd("\n\r");
		
		val = pConfigData->Smtp.EventEnableBits;
		printd("  AutoWarning:%x ", val);
		printd("CS:");
		if (val & GCONFIG_SMTP_EVENT_COLDSTART) printd("On ");
		else printd("Off ");
		
		printd("AF:");
		if (val & GCONFIG_SMTP_EVENT_AUTH_FAIL) printd("On ");
		else printd("Off");
		
		printd("IPC:");
		if (val & GCONFIG_SMTP_EVENT_IP_CHANGED) printd("On ");
		else printd("Off ");

		printd("PC:");
		if (val & GCONFIG_SMTP_EVENT_PSW_CHANGED) printd("On ");
		else printd("Off ");
		printd("\n\r\n\r");
	}

} /* End of gconfig_DisplayConfigData() */

/* End of gconfig.c */
