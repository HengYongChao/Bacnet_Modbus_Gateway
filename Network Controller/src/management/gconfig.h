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


#define GCONFIG_EEPROM_CONFIG 0

/* NAMING CONSTANT DECLARATIONS */
#define GCONFIG_DEFAULT_DATA_PORT		5000  // Default data port for both server and client modes

// Following UDP broadcast, multicast and unicast listening ports are used for communication
// with Device Server Manager program and are not configurable
#define GCONFIG_UDP_BCAST_SERVER_PORT	25122 // UDP broadcast listening ports
#define GCONFIG_UDP_MCAST_SERVER_PORT	25123 // UDP multicast listening ports
#define GCONFIG_UDP_UCAST_SERVER_PORT	25124 // UDP unicast listening ports

#define GCONFIG_CFG_DATA_FLASH_ADDR		0x4000
#define GCONFIG_CFG_PKT_LEN				72

#define GCONFIG_OPCODE_OFFSET			8
#define GCONFIG_OPCODE_SEARCH_REQ		0x00
#define GCONFIG_OPCODE_SEARCH_ACK		0x01
#define GCONFIG_OPCODE_SET_REQ			0x02
#define GCONFIG_OPCODE_SET_ACK			0x03
#define GCONFIG_OPCODE_SET_DENY			0x04
#define GCONFIG_OPCODE_UPGRADE_REQ		0x05
#define GCONFIG_OPCODE_UPGRADE_ACK		0x06
#define GCONFIG_OPCODE_UPGRADE_DENY		0x07
#define GCONFIG_OPCODE_RESET_REQ		0x08
#define GCONFIG_OPCODE_RESET_ACK		0x09
#define GCONFIG_OPCODE_RESET_DENY		0x0A
#define GCONFIG_OPCODE_REBOOT_REQ		0x0B
#define GCONFIG_OPCODE_REBOOT_ACK		0x0C
#define GCONFIG_OPCODE_REBOOT_DENY		0x0D
#define GCONFIG_OPCODE_MONITOR_REQ		0x10
#define GCONFIG_OPCODE_MONITOR_ACK		0x11
#define GCONFIG_OPCODE_CONN_CLOSE		0x12
#define GCONFIG_OPCODE_NONE				0xFF

#define GCONFIG_OPTION_ENABLE_REBOOT			0x01
#define GCONFIG_OPTION_ENABLE_UDP_AUTO_CONNECT	0x02

#define GCONFIG_NETWORK_SERVER			0x0000
#define GCONFIG_NETWORK_CLIENT			0x8000
#define GCONFIG_NETWORK_DHCP_ENABLE		0x4000
#define GCONFIG_NETWORK_DHCP_DISABLE	0x0000
#define GCONFIG_NETWORK_PROTO_UDP		0x0800
#define GCONFIG_NETWORK_PROTO_TCP		0x0400
#define GCONFIG_NETWORK_PROTO_UDP_MCAST	0x0200
#define GCONFIG_NETWORK_PROTO_UDP_BCAST	0x0100
#define GCONFIG_NETWORK_TIMEOUT_0_MIN	0x0000
#define GCONFIG_NETWORK_TIMEOUT_10_MIN	0x000A
#define GCONFIG_NETWORK_ACC_IP_ENABLE	0x1000
#define GCONFIG_NETWORK_ACC_IP_DISABLE	0x0000

#define GCONFIG_SPORT_BRATE_921600		0x0000
#define GCONFIG_SPORT_BRATE_115200		0x0800
#define GCONFIG_SPORT_BRATE_38400		0x1000
#define GCONFIG_SPORT_BRATE_19200		0x1800
#define GCONFIG_SPORT_BRATE_9600		0x2000
#define GCONFIG_SPORT_BRATE_4800		0x2800
#define GCONFIG_SPORT_BRATE_2400		0x3000
#define GCONFIG_SPORT_BRATE_1200		0x3800
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

#define GCONFIG_SMTP_EVENT_COLDSTART    0x0001
#define GCONFIG_SMTP_EVENT_WARMSTART    0x0002
#define GCONFIG_SMTP_EVENT_AUTH_FAIL    0x0004
#define GCONFIG_SMTP_EVENT_IP_CHANGED   0x0008
#define GCONFIG_SMTP_EVENT_PSW_CHANGED  0x0010

#define GCONFIG_ACCESSIBLE_IP_NUM       4
#define GCONFIG_VERSION_STR_LEN         12
#define GCONFIG_VERSION_STRING          "3.1.0"

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

typedef struct _GCONFIG_SMTP_CONFIG
{
    U8_T  DomainName[36];
    U8_T  FromAddr[36];
    U8_T  ToAddr1[36];
    U8_T  ToAddr2[36];
    U8_T  ToAddr3[36];
    U16_T EventEnableBits;
} GCONFIG_SMTP_CONFIG;

typedef struct _GCONFIG_CFG_PKT
{
	GCONFIG_GID 		Gid;
	U8_T				Opcode;
	U8_T				Option;
 	GCONFIG_DEV_NAME 	DevName;
	GCONFIG_MAC_ADDR	MacAddr;
	U16_T				Network;
	U32_T				ServerDynamicIP;
	U32_T				ServerStaticIP;
	U16_T				ServerDataPktListenPort;
	U16_T				ServerMulticastListenPort;
	U16_T				ServerBroadcastListenPort;
	U32_T				ClientDestIP;
	U16_T				ClientDestPort;
	U32_T				Netmask;
	U32_T				Gateway;
	U32_T				Dns;
	U16_T				SerialPort;
	U8_T				Rs485Mode;
	U8_T				DeviceStatus;
	U16_T				EthernetTxTimer;
    U32_T               AccessibleIP[GCONFIG_ACCESSIBLE_IP_NUM];
    GCONFIG_SMTP_CONFIG Smtp;
	U8_T				DestHostName[36];
    U32_T               TftpServerIp;
    U8_T                Filename[128];
} GCONFIG_CFG_PKT;

typedef struct
{
    U8_T Username[16];
    U8_T Passwd[16];
    U8_T Level;
    U8_T Rsvd;
} GCONFIG_ADMIN;

typedef struct _GCONFIG_CFG_DATA
{
	U16_T				CheckSum;
	U16_T				CfgLength;
    /* the following 5 items will be used for boot loader */
    U32_T               DeviceIp;
    U32_T               DeviceNetmask;
    U32_T               DeviceGateway;
    U32_T               TftpServerIp;
    U8_T                Filename[128];

	U32_T				UdpAutoConnectClientIp;
	U16_T				UdpAutoConnectClientPort;
 	GCONFIG_DEV_NAME 	DevName;
	U16_T				Network;
	U32_T				ServerStaticIP;
	U16_T				ServerDataPktListenPort;
	U16_T				ServerMulticastListenPort;
	U16_T				ServerBroadcastListenPort;
	U32_T				ClientDestIP;
	U16_T				ClientDestPort;
	U32_T				Netmask;
	U32_T				Gateway;
	U32_T				Dns;
	U16_T				SerialPort;
	U8_T				Rs485Mode;
	U8_T				Option;
	U16_T				EthernetTxTimer;
    U32_T               AccessibleIP[GCONFIG_ACCESSIBLE_IP_NUM];
    GCONFIG_SMTP_CONFIG Smtp;
	U8_T				DestHostName[36];
    GCONFIG_ADMIN       Admin;
} GCONFIG_CFG_DATA;

typedef struct _GCONFIG_MONITOR_PKT
{
	GCONFIG_GID 		Gid;
	U8_T				Opcode;
    U8_T                ModemStatus;
    U8_T                VerStr[GCONFIG_VERSION_STR_LEN];
	U32_T				TxBytes;
    U32_T               RxBytes;
} GCONFIG_MONITOR_PKT;

typedef struct _GCONFIG_CONN_CLOSE_PKT
{
    GCONFIG_GID 	Gid;
    U8_T		Opcode;
    U8_T		Option;
    U32_T       RemoteIp;
    U16_T       Port;
} GCONFIG_CONN_CLOSE_PKT;

/* GLOBAL VARIABLES */
extern GCONFIG_GID XDATA GCONFIG_Gid;

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void GCONFIG_Task(void);
void GCONFIG_Init(void);
void GCONFIG_SetConfigPacket(GCONFIG_CFG_PKT*);
void GCONFIG_GetConfigPacket(GCONFIG_CFG_PKT*);
void GCONFIG_ReadConfigData(void);
void GCONFIG_WriteConfigData(void);
void GCONFIG_ReadDefaultConfigData(void);
U32_T GCONFIG_IpAddr2Ulong(U8_T*, U8_T);

U8_T GCONFIG_EnableUdpAutoConnectAfterReboot(void);
void GCONFIG_EnableFirmwareUpgrade(void);
void GCONFIG_SetDeviceName(GCONFIG_DEV_NAME*);
void GCONFIG_SetNetwork(U16_T);
void GCONFIG_SetServerStaticIP(U32_T);
void GCONFIG_SetServerDataPktListenPort(U16_T);
void GCONFIG_SetServerMulticastListenPort(U16_T);
void GCONFIG_SetServerBroadcastListenPort(U16_T);
void GCONFIG_SetClientDestIP(U32_T);
void GCONFIG_SetClientDestPort(U16_T);
void GCONFIG_SetNetmask(U32_T);
void GCONFIG_SetGateway(U32_T);
void GCONFIG_SetDNS(U32_T);
void GCONFIG_SetSerialPort(U16_T);
void GCONFIG_SetEthernetTxTimer(U16_T);
void GCONFIG_SetUdpAutoConnectClientIp(U32_T);
void GCONFIG_SetUdpAutoConnectClientPort(U16_T);
void GCONFIG_SetTftpServerIp(U32_T ip);
U8_T GCONFIG_SetFilename(U8_T *filename, U8_T len);

GCONFIG_DEV_NAME* GCONFIG_GetDeviceName(void);
GCONFIG_MAC_ADDR GCONFIG_GetMacAddress(void);
U16_T GCONFIG_GetNetwork(void);
U32_T GCONFIG_GetServerStaticIP(void);
U16_T GCONFIG_GetServerDataPktListenPort(void);
U16_T GCONFIG_GetServerMulticastListenPort(void);
U16_T GCONFIG_GetServerBroadcastListenPort(void);
U32_T GCONFIG_GetClientDestIP(void);
U16_T GCONFIG_GetClientDestPort(void);
U32_T GCONFIG_GetNetmask(void);
U32_T GCONFIG_GetGateway(void);
U32_T GCONFIG_GetDNS(void);
U16_T GCONFIG_GetSerialPort(void);
U16_T GCONFIG_GetEthernetTxTimer(void);
U32_T GCONFIG_GetUdpAutoConnectClientIp(void);
U16_T GCONFIG_GetUdpAutoConnectClientPort(void);
U16_T GCONFIG_GetBaudRate(U8_T index);

S16_T GCONFIG_GetAdmin(U8_T *username, U8_T *passwd, U8_T *level);
S16_T GCONFIG_SetAdmin(U8_T *username, U8_T *passwd);

S16_T GCONFIG_GetAccessibleIP(U8_T idx, U32_T *ip);
S16_T GCONFIG_SetAccessibleIP(U8_T idx, U32_T ip);

void GCONFIG_SetSMTPDomainName(U8_T*, U8_T);
U8_T GCONFIG_GetSMTPDomainName(U8_T*);
void GCONFIG_SetSMTPFrom(U8_T*, U8_T);
U8_T GCONFIG_GetSMTPFrom(U8_T*);
void GCONFIG_SetSMTPTo1(U8_T*, U8_T);
U8_T GCONFIG_GetSMTPTo1(U8_T*);
void GCONFIG_SetSMTPTo2(U8_T*, U8_T);
U8_T GCONFIG_GetSMTPTo2(U8_T*);
void GCONFIG_SetSMTPTo3(U8_T*, U8_T);
U8_T GCONFIG_GetSMTPTo3(U8_T*);
void GCONFIG_SetAutoWarning(U16_T);
U16_T GCONFIG_GetAutoWarning(void);
void GCONFIG_SetRs485Mode(U8_T mode);
U8_T GCONFIG_GetRs485Mode(void);

void GCONFIG_SetDestHostName(U8_T*, U8_T);
U8_T GCONFIG_GetDestHostName(U8_T*);
U32_T GCONFIG_GetTftpServerIp(void);
U8_T GCONFIG_GetFilename(U8_T *filename, U8_T len);

#endif /* End of __GCONFIG_H__ */

/* End of gconfig.h */
