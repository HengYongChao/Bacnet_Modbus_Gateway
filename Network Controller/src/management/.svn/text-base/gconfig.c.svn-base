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
#include "tcpip.h"
#include "mstimer.h"
#include "stoe.h"
#include "uart.h"
#include "reg80390.h"
#include "printd.h"
#include "ax11000.h"
#include "i2c.h"
#include "i2capi.h"
#include "delay.h"
//#include "hsuart.h"

#include <absacc.h>
#include <string.h>

/* NAMING CONSTANT DECLARATIONS */

/* MACRO DECLARATIONS */
#define GCONFIG_PRINTD(s) printd(s);
#if GCONFIG_EEPROM_CONFIG
#define ADDROFDEV 0x50
#endif
/* TYPE DECLARATIONS */
typedef U8_T (*pFlashParaData)(U8_T * addr, U16_T len);

/* GLOBAL VARIABLES DECLARATIONS */
GCONFIG_GID XDATA GCONFIG_Gid = {'A','S','I','X','X','I','S','A'};
U16_T GCONFIG_CFG_PKT_LEN = sizeof(GCONFIG_CFG_PKT);
/* LOCAL VARIABLES DECLARATIONS */
GCONFIG_CFG_DATA XDATA gconfig_ConfigData;

static gconfig_BaudRateDiv[3][9] =
// br = 921600 115200  57600   38400   19200   9600    4800    2400    1200   
	{ {0x0001, 0x0008, 0x0010, 0x0018, 0x0030, 0x0060, 0x00c1, 0x0182, 0x0304},	// System clock = 25 mhz 
	  {0x0002, 0x0010, 0x0020, 0x0030, 0x0060, 0x00c1, 0x0181, 0x0304, 0x0607}, // System clock = 50 mhz 
	  {0x0004, 0x0020, 0x0040, 0x0060, 0x00c1, 0x0182, 0x0304, 0x0607, 0x0c0e}  // System clock = 100 mhz 
	};

/* LOCAL SUBPROGRAM DECLARATIONS */
static BOOL	gconfig_ReStoreParameter(U32_T addr, U8_T *pBase, U16_T len);
static BOOL gconfig_StoreParameter(U8_T *pSramBase, U16_T len);
static U8_T	gconfig_U8tCheckSum(U8_T *pValue, U16_T len);
void	gconfig_DisplayFlashReadWriteDebuggMsg(U8_T *pBase);

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
 * Function Name: GCONFIG_Init
 * Purpose: Initialization
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_Init(void)
{
	U16_T portCfg = 0;
	U16_T baudRateDiv = 0;
	U8_T  dataStopParityBits = 0;
	U16_T val = 0;
	U8_T  sysClock = 0; 
	U8_T  flowCtrl = 0;

	GCONFIG_PRINTD("GCONFIG_Init()...\n\r");

	// Restore last-saved configuration if applicable	
	GCONFIG_ReadConfigData();

	if (gconfig_ConfigData.FirmwareUpgradeMode == GCONFIG_FW_UPGRADE_ENABLE)
	{
		gconfig_ConfigData.FirmwareUpgradeMode = GCONFIG_FW_UPGRADE_DISABLE;

		//GCONFIG_WriteConfigData();
	}
} /* End of GCONFIG_Init() */

/////////////////////////////////////////////////////////////////////////////////

#if GCONFIG_EEPROM_CONFIG
/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetEpromData
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetEpromData(GCONFIG_CFG_PKT* pCfgPkt)
{
	BOOL rValue;
	U8_T i;
	for (i=0; i<34; i+=8) {
		rValue = I2C_PageWrite(ADDROFDEV, (0x00+i),
			&pCfgPkt->EEPromData.EEPromData[i], 8, I2C_STOP_COND);
		DELAY_Ms(5);
	}
} /* End of GCONFIG_SetConfigPacket() */
#endif

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
	// Store read-only items
	U32_T ip = GCONFIG_GetServerDynamicIP();
	
	// Update whole configuration packet
	memcpy(&gconfig_ConfigData.ConfigPkt, pCfgPkt, GCONFIG_CFG_PKT_LEN);
	
	// Restore read-only items
	GCONFIG_SetServerDynamicIP(ip);
 	
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
//	printd("GCONFIG_GetConfigPacket()...\n\r");
	GCONFIG_ReadConfigData();
	memcpy(pCfgPkt, &gconfig_ConfigData.ConfigPkt, GCONFIG_CFG_PKT_LEN);
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
	BOOL bRet;
#if GCONFIG_EEPROM_CONFIG
	BOOL rValue;
	I2C_BUF dumpdata;
	U8_T i;
#endif
	GCONFIG_MAC_ADDR macAddr;

#if GCONFIG_EEPROM_CONFIG
	dumpdata.I2cEnd = 0;
	dumpdata.I2cDir = 0;
	dumpdata.DataLen = 0;
	dumpdata.I2cAddr.SevenBitAddr = 0;
	dumpdata.I2cAddr.TenBitAddr = 0;
	for (i=0 ; i<MST_MAX_PKT_NUM ; i++)
		dumpdata.I2cData[i] = 0;
#endif

#if (RUNTIME_CODE_START_ADDRESS == RUNTIME_CODE_START_AT_24kH)
	bRet = gconfig_ReStoreParameter(0, (U8_T *)&gconfig_ConfigData, (U16_T)sizeof(gconfig_ConfigData));
#else
	GCONFIG_ReadDefaultConfigData();
#endif

#if GCONFIG_EEPROM_CONFIG
//	GCONFIG_PRINTD("Read EEProm data...\n\r");
	rValue = I2C_RdmRead((U16_T)0x0050, (U16_T)0x00, &dumpdata, (U16_T)34, I2C_STOP_COND);

	if(!rValue) {
	//	GCONFIG_PRINTD("I2C_RdmRead error occurred...\n\r");
	} else {
		memcpy(&gconfig_ConfigData.ConfigPkt.EEPromData.EEPromData[0], dumpdata.I2cData, 34);
	}
#endif

#if GCONFIG_DEBUG_FLASH_RW
	//	printd("GCONFIG_ReadConfigData()...\n\r");
		gconfig_DisplayFlashReadWriteDebuggMsg((U8_T*) &gconfig_ConfigData);
#endif

	if (bRet == FALSE || (gconfig_ConfigData.ConfigPkt.ServerStaticIP & 0x000000FF) == 0)
	{
	//	printd("ConfigData error\n\r");
		GCONFIG_ReadDefaultConfigData();

#if GCONFIG_DEBUG_FLASH_RW
	//	printd("GCONFIG_ReadDefaultConfigData()...\n\r");
		gconfig_DisplayFlashReadWriteDebuggMsg((U8_T*) &gconfig_ConfigData);
#endif

		GCONFIG_WriteConfigData();
	}

	memcpy(&macAddr, PNetStation->CurrStaAddr, MAC_ADDRESS_LEN);
	gconfig_ConfigData.ConfigPkt.MacAddr = macAddr;

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
#if (RUNTIME_CODE_START_ADDRESS == RUNTIME_CODE_START_AT_24kH)
	printd("GCONFIG_WriteConfigData()...\n\r");
	//gconfig_StoreParameter((U8_T *)&gconfig_ConfigData, (U16_T)sizeof(gconfig_ConfigData));	  //LHN
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
	GCONFIG_DEV_NAME devName = {0};

	gconfig_ConfigData.CheckSum = 0x00;
	gconfig_ConfigData.FirmwareUpgradeMode = GCONFIG_FW_UPGRADE_DISABLE;
	gconfig_ConfigData.PowerSaveMode = 0x00;
	gconfig_ConfigData.WatchDogMode = 0x00;
	gconfig_ConfigData.DontFragBit = 0x00;
	gconfig_ConfigData.TcpTimeout = 0x0000;
	gconfig_ConfigData.PingTimeout = 0x0000;

	gconfig_ConfigData.ConfigPkt.Gid = GCONFIG_Gid;
	gconfig_ConfigData.ConfigPkt.Opcode = GCONFIG_OPCODE_NONE;
	gconfig_ConfigData.ConfigPkt.Reserved = 0;
 	gconfig_ConfigData.ConfigPkt.DevName = devName;

	gconfig_ConfigData.ConfigPkt.Network = (//GCONFIG_NETWORK_SERVER		| 
                                            GCONFIG_NETWORK_DHCP_ENABLE |
											GCONFIG_NETWORK_PROTO_UDP	|
                                            GCONFIG_NETWORK_PROTO_TCP	|
											GCONFIG_NETWORK_PROTO_UDP_BCAST );

	gconfig_ConfigData.ConfigPkt.ServerDynamicIP = GCONFIG_GetServerDynamicIP();
	gconfig_ConfigData.ConfigPkt.ServerStaticIP = 0xc0a80003;	// 192.168.0.3
	gconfig_ConfigData.ConfigPkt.ServerUnicastListenPort = 25000;
	gconfig_ConfigData.ConfigPkt.ServerMulticastListenPort = 25100;
	gconfig_ConfigData.ConfigPkt.ServerBroadcastListenPort = 25122;
	gconfig_ConfigData.ConfigPkt.ClientDestIP = 0xc0a80002; 	// 192.168.0.2
	gconfig_ConfigData.ConfigPkt.ClientDestPort = 26000;
	gconfig_ConfigData.ConfigPkt.Netmask = 0xffffff00; 			// 255.255.255.0
//	gconfig_ConfigData.ConfigPkt.Gateway = 0xc0a80001; 			// 192.168.0.1
   	gconfig_ConfigData.ConfigPkt.Gateway = 0xc0a80004;
	gconfig_ConfigData.ConfigPkt.Dns = 0xc0a80001; 				// 192.168.0.1

	gconfig_ConfigData.ConfigPkt.SerialPort = (GCONFIG_SPORT_BRATE_115200 |
	                    					   GCONFIG_SPORT_DATABIT_8 |
											   GCONFIG_SPORT_PARITY_NONE |
											   GCONFIG_SPORT_FLOWC_NONE |
											   GCONFIG_SPORT_STOPBIT_1
											  );

//	printd("default setting %d", gconfig_ConfigData.ConfigPkt.SerialPort);

	gconfig_ConfigData.ConfigPkt.DeviceStatus = 0;	

} /* End of GCONFIG_ReadDefaultConfigData */

/////////////////////////////////////////////////////////////////////////////////
// Set 

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetFirmwareUpgradeMode
 * Purpose: 
 * Params: mode = 1: enable firmware ipgrade after reboot ,  mode = 0: disable
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetFirmwareUpgradeMode(U8_T mode)
{
	gconfig_ConfigData.FirmwareUpgradeMode = mode;
} /* End of GCONFIG_SetFirmwareUpgradeMode() */

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
	memcpy(&gconfig_ConfigData.ConfigPkt.DevName, pDevName, sizeof(GCONFIG_DEV_NAME)); 
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
void GCONFIG_SetMacAddress(GCONFIG_MAC_ADDR* pMacAddr)
{
	memcpy(&gconfig_ConfigData.ConfigPkt.MacAddr, pMacAddr, sizeof(GCONFIG_MAC_ADDR)); 
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
void GCONFIG_SetNetwork(U16_T val)
{
	gconfig_ConfigData.ConfigPkt.Network = val;
} /* End of GCONFIG_GetNetwork() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetServerDynamicIP
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetServerDynamicIP(U32_T ip)
{
	gconfig_ConfigData.ConfigPkt.ServerDynamicIP = ip;

} /* End of GCONFIG_SetServerDynamicIP() */

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
	gconfig_ConfigData.ConfigPkt.ServerStaticIP = ip;	
} /* End of GCONFIG_SetServerStaticIP() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetServerUnicastListenPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetServerUnicastListenPort(U16_T port)
{
	gconfig_ConfigData.ConfigPkt.ServerUnicastListenPort = port;
} /* End of GCONFIG_SetServerUnicastListenPort() */

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
	gconfig_ConfigData.ConfigPkt.ServerMulticastListenPort = port;
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
	gconfig_ConfigData.ConfigPkt.ServerBroadcastListenPort = port;
} /* End of GCONFIG_SetServerBroadcastListenPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetClientDestIP
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetClientDestIP(U32_T ip)
{
	gconfig_ConfigData.ConfigPkt.ClientDestIP = ip;
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
void GCONFIG_SetClientDestPort(U16_T port)
{
	gconfig_ConfigData.ConfigPkt.ClientDestPort = port;
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
void GCONFIG_SetNetmask(U32_T netmask)
{
	gconfig_ConfigData.ConfigPkt.Netmask = netmask;

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
void GCONFIG_SetGateway(U32_T gateway)
{
	gconfig_ConfigData.ConfigPkt.Gateway = gateway;
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
void GCONFIG_SetDNS(U32_T dns)
{
	gconfig_ConfigData.ConfigPkt.Dns = dns;
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
void GCONFIG_SetSerialPort(U16_T sPort)
{
	gconfig_ConfigData.ConfigPkt.SerialPort = sPort;
} /* End of GCONFIG_GetSerialPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_SetDeviceStatus
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_SetDeviceStatus(U16_T status)
{
	gconfig_ConfigData.ConfigPkt.DeviceStatus = status;
} /* End of GCONFIG_SetDeviceStatus() */

/////////////////////////////////////////////////////////////////////////////////
// Get 

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetFirmwareUpgradeMode
 * Purpose: 
 * Params:
 * Returns: 1: enable firmware ipgrade after reboot ,  0: disable
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GCONFIG_GetFirmwareUpgradeMode(void)
{
	return gconfig_ConfigData.FirmwareUpgradeMode;
} /* End of GCONFIG_GetFirmwareUpgradeMode() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetDeviceName
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
GCONFIG_DEV_NAME GCONFIG_GetDeviceName(void)
{
	return gconfig_ConfigData.ConfigPkt.DevName;
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
	return gconfig_ConfigData.ConfigPkt.MacAddr;
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
	return gconfig_ConfigData.ConfigPkt.Network;
} /* End of GCONFIG_GetNetwork() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetServerDynamicIP
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GCONFIG_GetServerDynamicIP(void)
{
	return gconfig_ConfigData.ConfigPkt.ServerDynamicIP;
} /* End of GCONFIG_GetServerDynamicIP() */

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
	return gconfig_ConfigData.ConfigPkt.ServerStaticIP;
} /* End of GCONFIG_GetServerStaticIP() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetServerUnicastListenPort
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GCONFIG_GetServerUnicastListenPort(void)
{
	return gconfig_ConfigData.ConfigPkt.ServerUnicastListenPort;
} /* End of GCONFIG_GetServerUnicastListenPort() */

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
	return gconfig_ConfigData.ConfigPkt.ServerMulticastListenPort;
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
	return gconfig_ConfigData.ConfigPkt.ServerBroadcastListenPort;
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
	return gconfig_ConfigData.ConfigPkt.ClientDestIP;
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
	return gconfig_ConfigData.ConfigPkt.ClientDestPort;
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
	return gconfig_ConfigData.ConfigPkt.Netmask;
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
	return gconfig_ConfigData.ConfigPkt.Gateway;
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
	return gconfig_ConfigData.ConfigPkt.Dns;
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
	return gconfig_ConfigData.ConfigPkt.SerialPort;
} /* End of GCONFIG_GetSerialPort() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_GetDeviceStatus
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GCONFIG_GetDeviceStatus(void)
{
	return gconfig_ConfigData.ConfigPkt.DeviceStatus;
} /* End of GCONFIG_GetDeviceStatus() */


/*
 * ----------------------------------------------------------------------------
 * Function Name: GCONFIG_FirmwareUpgradeReg
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GCONFIG_FirmwareUpgradeReg(void)
{
	GCONFIG_SetFirmwareUpgradeMode(GCONFIG_FW_UPGRADE_ENABLE);
	GCONFIG_WriteConfigData();		
	AX11000_SoftReset();		
} /* End of GCONFIG_FirmwareUpgradeReg() */

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
static BOOL gconfig_ReStoreParameter(U32_T addr, U8_T *pBase, U16_T len)
{
			U16_T	i;
			U8_T	*pParaBaseByte;
			U16_T	paraDataLen = 0;
			U8_T	paraCheckSum = 0;
			U8_T	lastWtst = 0;
		
			pParaBaseByte = pBase;
			paraDataLen = len;
		
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
		
			paraCheckSum = gconfig_U8tCheckSum((pParaBaseByte + 1), (len-1));
		
		#if GCONFIG_DEBUG_FLASH_RW
//			printd("gconfig_ReStoreParameter()...\n\r");
			gconfig_DisplayFlashReadWriteDebuggMsg(pBase);
		#endif
			
			if (paraCheckSum != *(pParaBaseByte))
			{
			//	printd("gconfig_ReStoreParameter() failed! (Wrong checksum)\n\r");
				return FALSE;
			}
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
static BOOL gconfig_StoreParameter(U8_T *pSramBase, U16_T len)
{
	U8_T			ret = FALSE;
	U8_T			paraCheckSum = 0;
	pFlashParaData  ptrFlashWrite = (void code*)0x003F00;

#if GCONFIG_DEBUG_FLASH_RW
//	printd("gconfig_StoreParameter()...\n\r");
	gconfig_DisplayFlashReadWriteDebuggMsg(pSramBase);
#endif

	paraCheckSum = gconfig_U8tCheckSum((pSramBase + 1), (len-1));
	*(pSramBase) = paraCheckSum;

	ret = (*ptrFlashWrite)(pSramBase, len);	

	if (ret == FALSE)
		return FALSE;

	return TRUE;
} /* End of gconfig_StoreParameter() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: gconfig_U8tCheckSum
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static U8_T gconfig_U8tCheckSum(U8_T *pValue, U16_T len)
{
	U16_T	i;
	U8_T	chkSum = 0;

	for (i=0 ; i<len ; i++)
	{
		chkSum = chkSum + pValue[i] ;
	}

	chkSum = ~chkSum;

	return chkSum;
} /* End of gconfig_U8tCheckSum() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: gconfig_DisplayFlashReadWriteDebuggMsg
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void	gconfig_DisplayFlashReadWriteDebuggMsg(U8_T *pBase)
{
//	U8_T i;
//	U8_T dat;
//	U16_T val;
	GCONFIG_CFG_PKT *ptr = (GCONFIG_CFG_PKT *)(pBase+9);
#if 0
//	if (GS2E_GetTaskState() == GS2E_STATE_IDLE)
	{
		printd("   1.Header: ");
		for (i = 0 ; i < 9; i++)
			printd ("%02bx ", *(pBase + i));		
	
		printd("\n\r");
		printd("   2.GID: ");
		for (i = 9 ; i < 17; i++)
			printd ("%02bx ", *(pBase + i));		
		
		printd("\n\r");
		printd("   3.Opcode | Reserved: ");
		for (i = 17 ; i < 19; i++)
			printd ("%02bx ", *(pBase + i));		
	
		printd("\n\r");
		printd("   4.Device Name: ");
		for (i = 19 ; i < 35; i++)
			printd ("%02bx ", *(pBase + i));		
	
		printd("\n\r");
		printd("   5.MAC Addr: ");
		for (i = 35 ; i < 41; i++)
			printd ("%02bx ", *(pBase + i));		
	
		printd("\n\r");
		printd("   6.Network Setting: ");
		for (i = 41 ; i < 43; i++)
			printd ("%02bx ", *(pBase + i));		
	
		dat = *(pBase + 41);
	
	//	printd ("SW:%02bx DHCP:%02bx, U:%02bx T:%02bx B:%02bx M:%02bx", 
	//	         dat & 0x80, dat & 0x40, dat & 0x08, dat & 0x04, dat & 0x02, dat & 0x01 );	
	
		if ((dat & 0x80) == 0x80) printd("SW:Cli ");
		else 					printd("SW:Ser ");
	
		if ((dat & 0x40) == 0x40) printd("DHCP:On ");
		else 					printd("DHCP:Off ");
	
		if ((dat & 0x08) == 0x08) printd("UDP:On ");
		else 					printd("UDP:Off ");
	
		if ((dat & 0x04) == 0x04) printd("TCP:On ");
		else 					printd("TCP:Off ");
	
		if ((dat & 0x02) == 0x02) printd("MC:On ");
		else 					printd("MC:Off ");
	
		if ((dat & 0x01) == 0x01) printd("BC:On ");
		else 					printd("BC:Off ");
	
		printd("\n\r");
		printd("   7.D-IP | S-IP | U-M-B Port: ");
		
		for (i = 43 ; i < 51; i++)
			printd ("%bu ", *(pBase + i));		
	
		for (i = 51 ; i < 57; i+=2)
		{
			val = ((*(pBase + i) << 8) & 0xFF00) + *(pBase + i + 1);	
			printd ("%u ", val);		
		}
	
		printd("\n\r");
		printd("   8.Dest IP | Dest Port: ");
	
		for (i = 57 ; i < 61; i++)
			printd ("%bu ", *(pBase + i));		
	
		for (i = 61 ; i < 53; i+=2)
		{
			val = ((*(pBase + i) << 8) & 0xFF00) + *(pBase + i + 1);	
			printd ("%u ", val);		
		}
	
		printd("\n\r");
		printd("   9.Netmask | Gateway | DNS: ");
		for (i = 63 ; i < 75; i++)
			printd ("%bu ", *(pBase + i));		
	
		printd("\n\r");
		printd("   10.Serial Port Setting: ");
	//	for (i = 75 ; i < 77; i++)
	//		printd ("%02bx ", *(pBase + i));		
	
		dat = *(pBase + 75);
		val = (dat >> 3) & 0x1F; 
		if (val == 0) printd ("BR:115200 ");
		else if (val == 1) printd ("BR:57600 ");
		else if (val == 2) printd ("BR:38400 ");
		else if (val == 3) printd ("BR:19200 ");
		else if (val == 4) printd ("BR:9600 ");
		else if (val == 5) printd ("BR:4800 ");
		else if (val == 6) printd ("BR:2400 ");
		else if (val == 7) printd ("BR:1200 ");
	
		val = dat & 0x07; 
		if (val == 0) printd ("DB:5 ");
		else if (val == 1) printd ("DB:6 ");
		else if (val == 2) printd ("DB:7 ");
		else if (val == 3) printd ("DB:8 ");
	
		dat = *(pBase + 76);
	
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
	//	else if (val == 2) printd ("SB:2 ");
	
		printd("\n\r");
		printd("   11.Status: ");
		for (i = 77 ; i < 79; i++)
			printd ("%02bx ", *(pBase + i));		

#if 0
		printd("\n\r");
		printd("   12.EEPROM DATA: ");
		for (i=0; i<34; i++)
		{
			printd ("%02bx ", ptr->EEPromData.EEPromData[i]);
			if ( (i!=0) && ((i+1)%16 == 0) )
				printd("\n\r                   ");
		}
#endif
	//	printd("\n\r");
	}

 
  #endif

} /* End of gconfig_DisplayFlashReadWriteDebuggMsg() */

/* End of gconfig.c */
