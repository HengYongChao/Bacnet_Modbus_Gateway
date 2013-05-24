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
 * Module Name:gconfig.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: gconfig.h,v $
 *
 *=============================================================================
 */

#ifndef __GCONFIG_H__
#define __GCONFIG_H__

/* INCLUDE FILE DECLARATIONS */
#include "types.h"
#include "i2c.h"

/* NAMING CONSTANT DECLARATIONS */
#define GCONFIG_DEBUG_FLASH_RW			1 // 0: disable, 1: display FLASH read/write debug message  
#define GCONFIG_EEPROM_CONFIG			0 //changed by andy
#define GCONFIG_FW_UPGRADE_ENABLE 		1
#define GCONFIG_FW_UPGRADE_DISABLE 		0

#define GCONFIG_ACCESSIBLE_IP_NUM		4

#define GCONFIG_CFG_DATA_FLASH_ADDR		0x4000



#define GCONFIG_OPCODE_OFFSET				8
#define GCONFIG_OPCODE_SEARCH_REQ			0x00
#define GCONFIG_OPCODE_SEARCH_ACK			0x01
#define GCONFIG_OPCODE_SET_REQ				0x02
#define GCONFIG_OPCODE_SET_ACK				0x03
#define GCONFIG_OPCODE_SET_DENY				0x04
#define GCONFIG_OPCODE_UPGRADE_REQ			0x05
#define GCONFIG_OPCODE_UPGRADE_ACK			0x06
#define GCONFIG_OPCODE_UPGRADE_DENY			0x07
#define GCONFIG_OPCODE_RESET_REQ			0x08
#define GCONFIG_OPCODE_RESET_ACK			0x09
#define GCONFIG_OPCODE_RESET_DENY			0x0A
#define GCONFIG_OPCODE_REBOOT_REQ			0x0B
#define GCONFIG_OPCODE_REBOOT_ACK			0x0C
#define GCONFIG_OPCODE_REBOOT_DENY			0x0D
#define GCONFIG_OPCODE_EEPROM_READ_REQ		0x0E
#define GCONFIG_OPCODE_EEPROM_READ_ACK		0x0F
#define GCONFIG_OPCODE_EEPROM_WRITE_REQ		0x10
#define GCONFIG_OPCODE_EEPROM_WRITE_ACK		0x11
#define GCONFIG_OPCODE_NONE					0xFF

#define GCONFIG_NETWORK_SERVER			0x8000
#define GCONFIG_NETWORK_CLIENT			0x0000
#define GCONFIG_NETWORK_DHCP_ENABLE		0x4000
#define GCONFIG_NETWORK_DHCP_DISABLE	0x0000
#define GCONFIG_NETWORK_PROTO_UDP		0x0800
#define GCONFIG_NETWORK_PROTO_TCP		0x0400
#define GCONFIG_NETWORK_PROTO_UDP_MCAST	0x0200
#define GCONFIG_NETWORK_PROTO_UDP_BCAST	0x0100
#define GCONFIG_NETWORK_TIMEOUT_0_MIN	0x0000
#define GCONFIG_NETWORK_TIMEOUT_10_MIN	0x000A

#define GCONFIG_SPORT_BRATE_115200		0x0000
#define GCONFIG_SPORT_BRATE_38400		0x0800
#define GCONFIG_SPORT_BRATE_19200		0x1000
#define GCONFIG_SPORT_BRATE_9600		0x1800
#define GCONFIG_SPORT_BRATE_4800		0x2000
#define GCONFIG_SPORT_BRATE_2400		0x2800
#define GCONFIG_SPORT_BRATE_1200		0x3000
#define GCONFIG_SPORT_DATABIT_5			0x0000
#define GCONFIG_SPORT_DATABIT_6			0x0100
#define GCONFIG_SPORT_DATABIT_7			0x0200
#define GCONFIG_SPORT_DATABIT_8			0x0300
#define GCONFIG_SPORT_PARITY_ODD		0x0000
#define GCONFIG_SPORT_PARITY_EVEN		0x0020
#define GCONFIG_SPORT_PARITY_NONE		0x0040
#define GCONFIG_SPORT_FLOWC_XON_XOFF	0x0000
#define GCONFIG_SPORT_FLOWC_HARDWARE	0x0004
#define GCONFIG_SPORT_FLOWC_NONE		0x0008
#define GCONFIG_SPORT_STOPBIT_1			0x0000
#define GCONFIG_SPORT_STOPBIT_1P5		0x0001
#define GCONFIG_SPORT_STOPBIT_2			0x0002

/* TYPE DECLARATIONS */
typedef struct _GCONFIG_GID
{
	U8_T id[8]; 
} GCONFIG_GID;

typedef struct _GCONFIG_DEV_NAME
{
	U8_T DevName[16]; 
} GCONFIG_DEV_NAME;

typedef struct _GCONFIG_MAC_ADDR
{
	U8_T MacAddr[6]; 
} GCONFIG_MAC_ADDR;

#if GCONFIG_EEPROM_CONFIG
typedef struct _GCONFIG_EEPROM_DATA
{
	U8_T EEPromData[34]; 
} GCONFIG_EEPROM_DATA;
#endif

typedef struct _GCONFIG_CFG_PKT
{
	GCONFIG_GID 		Gid;
	U8_T				Opcode;
	U8_T				Reserved;
 	GCONFIG_DEV_NAME 	DevName;
	GCONFIG_MAC_ADDR	MacAddr;
	U16_T				Network;
	U32_T				ServerDynamicIP;
	U32_T				ServerStaticIP;
	U16_T				ServerUnicastListenPort;
	U16_T				ServerMulticastListenPort;
	U16_T				ServerBroadcastListenPort;
	U32_T				ClientDestIP;
	U16_T				ClientDestPort;
	U32_T				Netmask;
	U32_T				Gateway;
	U32_T				Dns;
	U16_T				SerialPort;
	U16_T				DeviceStatus;
#if GCONFIG_EEPROM_CONFIG
	GCONFIG_EEPROM_DATA	EEPromData;
#endif
} GCONFIG_CFG_PKT;

typedef struct _GCONFIG_CFG_DATA
{
	U8_T				CheckSum;
	U8_T				FirmwareUpgradeMode;	
	U8_T				PowerSaveMode;
	U8_T				WatchDogMode;
	U8_T				DontFragBit;
	U16_T				TcpTimeout;
	U16_T				PingTimeout;
	GCONFIG_CFG_PKT     ConfigPkt;
} GCONFIG_CFG_DATA;

/*
typedef struct para_base_t
{
	U8_T	CheckSum;
	U16_T	TcpTimeout;
	U16_T	PingTimeout;
	U8_T	SerialBaudrate;
	U8_T	FlowCtrlMode;
	U8_T	PowerSaveMode;
	U8_T	WatchDogMode;
	U8_T	DontFragBit;
	U32_T	IpAddress;
	U32_T	GetwayAddress;
	U32_T	SubNetMask;
	U32_T	DnsServer;
	U8_T	DynamicStaticIp;
}	PARA_BASE_T;
*/
/* GLOBAL VARIABLES */
extern GCONFIG_GID XDATA GCONFIG_Gid;
extern U16_T	GCONFIG_CFG_PKT_LEN;
/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void GCONFIG_Task(void);
void GCONFIG_Init(void);
void GCONFIG_SetConfigPacket(GCONFIG_CFG_PKT*);
void GCONFIG_GetConfigPacket(GCONFIG_CFG_PKT*);
void GCONFIG_ReadConfigData(void);
void GCONFIG_WriteConfigData(void);
void GCONFIG_ReadDefaultConfigData(void);

void GCONFIG_SetEpromData(GCONFIG_CFG_PKT* pCfgPkt);
void GCONFIG_SetFirmwareUpgradeMode(U8_T mode);
void GCONFIG_SetDeviceName(GCONFIG_DEV_NAME*);
void GCONFIG_SetMacAddress(GCONFIG_MAC_ADDR*);
void GCONFIG_SetNetwork(U16_T);
void GCONFIG_SetServerDynamicIP(U32_T);
void GCONFIG_SetServerStaticIP(U32_T);
void GCONFIG_SetServerUnicastListenPort(U16_T);
void GCONFIG_SetServerMulticastListenPort(U16_T);
void GCONFIG_SetServerBroadcastListenPort(U16_T);
void GCONFIG_SetClientDestIP(U32_T);
void GCONFIG_SetClientDestPort(U16_T);
void GCONFIG_SetNetmask(U32_T);
void GCONFIG_SetGateway(U32_T);
void GCONFIG_SetDNS(U32_T);
void GCONFIG_SetSerialPort(U16_T);
void GCONFIG_SetDeviceStatus(U16_T);

U8_T GCONFIG_GetFirmwareUpgradeMode(void);
GCONFIG_DEV_NAME GCONFIG_GetDeviceName(void);
GCONFIG_MAC_ADDR GCONFIG_GetMacAddress(void);
U16_T GCONFIG_GetNetwork(void);
U32_T GCONFIG_GetServerDynamicIP(void);
U32_T GCONFIG_GetServerStaticIP(void);
U16_T GCONFIG_GetServerUnicastListenPort(void);
U16_T GCONFIG_GetServerMulticastListenPort(void);
U16_T GCONFIG_GetServerBroadcastListenPort(void);
U32_T GCONFIG_GetClientDestIP(void);
U16_T GCONFIG_GetClientDestPort(void);
U32_T GCONFIG_GetNetmask(void);
U32_T GCONFIG_GetGateway(void);
U32_T GCONFIG_GetDNS(void);
U16_T GCONFIG_GetSerialPort(void);
U16_T GCONFIG_GetDeviceStatus(void);

void GCONFIG_FirmwareUpgradeReg(void);

#endif /* End of __GCONFIG_H__ */

/* End of gconfig.h */
