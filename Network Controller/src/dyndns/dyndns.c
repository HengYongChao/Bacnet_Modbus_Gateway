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
 * Module Name: dyndns.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log:
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "uip.h"
#include "tcpip.h"
#include "dyndns.h"
#include "mstimer.h"
#include <string.h>
#include <stdio.h>

#define CONF_DDNS_3322		0
#define CONF_DDNS_DYNDNS	1
#define CONF_DDNS_NOIP		2

/* NAMING CONSTANT DECLARATIONS */
#define MAX_CMDBUF_SIZE				256
#define MAX_TMP_ENCBUF_SIZE			48
#define MAX_ENCBUF_SIZE				64
#define MAX_USERNAME_SIZE			32
#define MAX_PASSWORD_SIZE			32
#define MAX_DOMAIN_SIZE				32
#define MAX_TIMEOUT_VALUE			50

#define DYNDNS_STATE_IDLE				0
#define DYNDNS_STATE_MAKE_CONNECT		1
#define DYNDNS_STATE_WAIT_CONNECT		2
#define DYNDNS_STATE_SEND_COMMAND		3
#define DYNDNS_STATE_WAIT_RESPONSE		4

/* TYPE DECLARATIONS */

/* MACRO DECLARATIONS */

/* STATIC VARIABLE DECLARATIONS */

/* LOCAL VARIABLE DECLARATIONS */
static S8_T XDATA dyndns_Command[MAX_CMDBUF_SIZE];
static U16_T XDATA dyndns_CmdLen;
static S8_T XDATA dyndns_TmpEncData[MAX_TMP_ENCBUF_SIZE];
static S8_T XDATA dyndns_EncResult[MAX_ENCBUF_SIZE];
static S8_T XDATA dyndns_Base64Table[65] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};
static U8_T XDATA dyndns_IpAddress[4];
static S8_T XDATA dyndns_CheckResult[16];
static U8_T XDATA dyndns_AppId;
static U8_T XDATA dyndns_ConnId;
static U32_T XDATA dyndns_HostIp;
static U16_T XDATA dyndns_HostIpLen;
static U8_T XDATA dyndns_State;
static BOOL XDATA dyndns_bUpdateStart;
static BOOL XDATA dyndns_bUpdateDone;
static U8_T dyndns_Type;
static U8_T dyndns_User[MAX_USERNAME_SIZE] = {0};
static U8_T dyndns_Pass[MAX_PASSWORD_SIZE] = {0};
static U8_T dyndns_Domain[MAX_DOMAIN_SIZE] = {0};
static U32_T dyndns_StartTime;

/* LOCAL SUBPROGRAM DECLARATIONS */
static BOOL dyndns_AssembleCommandPkt(void);
static BOOL dyndns_DoBase64Enc(void);
static void dyndns_Start(void);
static void dyndns_CloseConnection(void);

/*
 * -----------------------------------------------------------------------------
 * Function Name: DynDNS_Init
 * Purpose: To initialize the parameter of this module and to bind a TCPIP connection
 * Params: none
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void DynDNS_Init(void)
{
	// to bind a TCPIP connection
	dyndns_AppId = TCPIP_Bind(NULL, DynDNS_EventHandle, DynDNS_ReceiveHandle);
//	test_dyndns_AppId = dyndns_AppId;
	// to initialize the parameters
	dyndns_State = DYNDNS_STATE_IDLE;
	dyndns_bUpdateStart = TRUE;
	dyndns_bUpdateDone = FALSE;

}

/*
 * -----------------------------------------------------------------------------
 * Function Name: dyndns_CloseConnection
 * Purpose: to close the connection and reset the status
 * Params: none
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void dyndns_CloseConnection(void)
{
	// to close the connection and reset the status
	TCPIP_TcpClose(dyndns_ConnId);
	dyndns_bUpdateDone = TRUE;
	dyndns_State = DYNDNS_STATE_IDLE;
}


/*
 * -----------------------------------------------------------------------------
 * Function Name: DynDNS_GetUpdateState
 * Purpose: To get the state of updating the dynamic dns 
 * Params: none
 * Returns: boolean value. TRUE if the procedure of update has done
 * Note:
 * ----------------------------------------------------------------------------
 */
BOOL DynDNS_GetUpdateState(void)
{
//	test_dyndns_state = dyndns_State;
	if(dyndns_bUpdateDone == TRUE)
	{
		dyndns_bUpdateStart = TRUE;
	}

	return dyndns_bUpdateDone;
}

/*
 * -----------------------------------------------------------------------------
 * Function Name: dyndns_DoBase64Enc
 * Purpose: to encode the username and password in BASE64
 * Params: none
 * Returns: boolean value. TRUE if no error occurs.
 * Note:
 * ----------------------------------------------------------------------------
 */
BOOL dyndns_DoBase64Enc(void)
{
	U16_T i, len;
	U16_T iResult;
	U32_T nValue, nTmpValue;
	U8_T nStart = 0;

	i = 0;
	len = 0;
	while((len < MAX_TMP_ENCBUF_SIZE) && (dyndns_User[i] != 0))
	{
		dyndns_TmpEncData[len] = dyndns_User[i];
		len += 1;
		i += 1;
	}
	
	if(len > (MAX_TMP_ENCBUF_SIZE - 1))
	{
		return FALSE;
	}
	dyndns_TmpEncData[len] = ':';
	len += 1;
	i = 0;
	while((len < MAX_TMP_ENCBUF_SIZE) && (dyndns_Pass[i] != 0))
	{
		dyndns_TmpEncData[len] = dyndns_Pass[i];
		len += 1;
		i += 1;
	}
	
	if(len == MAX_TMP_ENCBUF_SIZE)
	{
		return FALSE;
	}

	dyndns_TmpEncData[len] = 0;

	// begin to encode in BASE64
	// 0x31='1'         0x32='2'         0x33='3'
	// _______________  _______________  _______________
	// 0 0 1 1 0 0 0 1  0 0 1 1 0 0 1 0  0 0 1 1 0 0 1 1
	// ___________ ____________ ____________ ___________
	// 12='M'      19='T'       8='I'        51='z'
	// "123" => "MTIz"
	nValue = 0;
	nStart = 0;
	iResult = 0;
	i = 0;
	while((i < MAX_ENCBUF_SIZE) && (dyndns_TmpEncData[i] != 0))
	{
		nValue <<= 8;
		nValue += dyndns_TmpEncData[i];
		i++;
		nStart++;
		if(nStart == 3)
		{
			nStart = 0;
			nTmpValue = nValue >> 18;
			dyndns_EncResult[iResult++] = dyndns_Base64Table[nTmpValue];
			nTmpValue = (nValue >> 12) & 0x0000003F;
			dyndns_EncResult[iResult++] = dyndns_Base64Table[nTmpValue];
			nTmpValue = (nValue >> 6) & 0x0000003F;
			dyndns_EncResult[iResult++] = dyndns_Base64Table[nTmpValue];
			nTmpValue = nValue & 0x0000003F;
			dyndns_EncResult[iResult++] = dyndns_Base64Table[nTmpValue];
			nValue = 0;
		}
	}
	if(nStart == 2)
	{
		nValue <<= 8;
		nTmpValue = nValue >> 18;
		dyndns_EncResult[iResult++] = dyndns_Base64Table[nTmpValue];
		nTmpValue = (nValue >> 12) & 0x0000003F;
		dyndns_EncResult[iResult++] = dyndns_Base64Table[nTmpValue];
		nTmpValue = (nValue >> 6) & 0x0000003F;
		dyndns_EncResult[iResult++] = dyndns_Base64Table[nTmpValue];
		dyndns_EncResult[iResult++] = '=';
	}else if(nStart == 1)
	{
		nValue <<= 16;
		nTmpValue = nValue >> 18;
		dyndns_EncResult[iResult++] = dyndns_Base64Table[nTmpValue];
		nTmpValue = (nValue >> 12) & 0x0000003F;
		dyndns_EncResult[iResult++] = dyndns_Base64Table[nTmpValue];
		dyndns_EncResult[iResult++] = '=';
		dyndns_EncResult[iResult++] = '=';
	}

	dyndns_EncResult[iResult] = 0;

	return TRUE;

}

/*
 * -----------------------------------------------------------------------------
 * Function Name: dyndns_AssembleCommandPkt
 * Purpose: to assemble the update command
 * Params: none
 * Returns: boolean value. TRUE if no error occurs.
 * Note:
 * ----------------------------------------------------------------------------
 */
BOOL dyndns_AssembleCommandPkt(void)
{
	U16_T nAddr[2];

	// to get the host ip of this device
	uip_gethostaddr(nAddr);
	dyndns_IpAddress[0] = (U8_T)(nAddr[0] / 256);
	dyndns_IpAddress[1] = (U8_T)(nAddr[0] % 256);
	dyndns_IpAddress[2] = (U8_T)(nAddr[1] / 256);
	dyndns_IpAddress[3] = (U8_T)(nAddr[1] % 256);

	if(dyndns_Type == CONF_DDNS_3322)
	{
		// to assemble the update command for the 3322.org
		if(dyndns_DoBase64Enc() == FALSE)
		{
			return FALSE;
		}
		dyndns_CmdLen = sprintf(dyndns_Command, "GET /dyndns/update?system=dyndns&hostname=%s&myip=%bu.%bu.%bu.%bu&wildcard=OFF&mx=NOCHG&backmx=NO&offline=NO HTTP/1.0\r\n",
			dyndns_Domain, dyndns_IpAddress[0], dyndns_IpAddress[1], dyndns_IpAddress[2], dyndns_IpAddress[3], dyndns_EncResult); 
		dyndns_CmdLen += sprintf(dyndns_Command + dyndns_CmdLen, "Host: members.3322.org\r\nAuthorization: Basic %s\r\nUser-Agent: myclient/1.0 me@null.net\r\n\r\n",
			dyndns_EncResult);
	}else if(dyndns_Type == CONF_DDNS_DYNDNS)
	{
		// to assemble the update command for the dyndns.org
		if(dyndns_DoBase64Enc() == FALSE)
		{
			return FALSE;
		}
		dyndns_CmdLen = sprintf(dyndns_Command, "GET /nic/update?system=dyndns&hostname=%s&myip=%bu.%bu.%bu.%bu&wildcard=OFF&mx=NOCHG&backmx=NO&offline=NO HTTP/1.0\r\n",
			dyndns_Domain, dyndns_IpAddress[0], dyndns_IpAddress[1], dyndns_IpAddress[2], dyndns_IpAddress[3], dyndns_EncResult); 
		dyndns_CmdLen += sprintf(dyndns_Command + dyndns_CmdLen, "Host: members.dyndns.org\r\nAuthorization: Basic %s\r\nUser-Agent: myclient/1.0 me@null.net\r\n\r\n",
			dyndns_EncResult);
	}else if(dyndns_Type == CONF_DDNS_NOIP)
	{
		// to assemble the update command for the no-ip.com
		dyndns_CmdLen = sprintf(dyndns_Command, "GET /dns?username=%s&password=%s&hostname=%s&ip=%bu.%bu.%bu.%bu HTTP/1.0\r\n",
			dyndns_User, dyndns_Pass, dyndns_Domain, dyndns_IpAddress[0], dyndns_IpAddress[1], dyndns_IpAddress[2], dyndns_IpAddress[3]); 
		dyndns_CmdLen += sprintf(dyndns_Command + dyndns_CmdLen, "Host: dynupdate.no-ip.com\r\nUser-Agent: myclient/1.0 me@null.net\r\n\r\n",
			dyndns_EncResult);
	}
	dyndns_HostIpLen = sprintf(dyndns_CheckResult, "%bu.%bu.%bu.%bu", dyndns_IpAddress[0], dyndns_IpAddress[1], dyndns_IpAddress[2], dyndns_IpAddress[3]);

	return TRUE;

}

/*
 * -----------------------------------------------------------------------------
 * Function Name: DynDNS_EventHandle
 * Purpose: callback function used by TCPIP module 
 * Params: 
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void DynDNS_EventHandle(U8_T connID, U8_T event)
{
	connID = connID;

//	test_tcpip_connect_status = event;

	if (event == TCPIP_CONNECT_CANCEL)
	{
		// TCPIP connection failed, close the connection and set the flag of done
		dyndns_CloseConnection();
	}
	else if (event == TCPIP_CONNECT_ACTIVE)
	{
		// TCPIP connection established, chagne the state to the send command
		dyndns_State = DYNDNS_STATE_SEND_COMMAND;
	}
	else if (event == TCPIP_CONNECT_XMIT_COMPLETE)
	{
	}
	else /* unknow event */
	{
		dyndns_CloseConnection();
	}

}

/*
 * -----------------------------------------------------------------------------
 * Function Name: DynDNS_ReceiveHandle
 * Purpose: callback function used by TCPIP
 * Params:
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void DynDNS_ReceiveHandle(U8_T XDATA *pData, U16_T length, U8_T connId)
{
//	U8_T i;
	pData = pData;
	length = length;
	connId = connId;

	if(dyndns_State == DYNDNS_STATE_WAIT_RESPONSE)
	{
//		test_dyndns_rev_len = length;
//		for(i = 0; i < length; i++)
//			test_rev_buf[i] = pData[i];
		dyndns_CloseConnection();
	}

}


/*
* -----------------------------------------------------------------------------
 * Function Name: dyndns_Start
 * Purpose: to start the update dynamic DNS procedure
 * Params: none
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void dyndns_Start(void)
{
	U32_T nCurrentTime;

	switch(dyndns_State)
	{
	// query the host ip of the ddns server
	case DYNDNS_STATE_MAKE_CONNECT:
		// to get a TCPIP connection
		dyndns_ConnId = TCPIP_TcpNew(dyndns_AppId, 0, dyndns_HostIp, 0, 80);
//		test_dyndns_ConnId = dyndns_ConnId;

		if (dyndns_ConnId == TCPIP_NO_NEW_CONN)
		{
			dyndns_bUpdateDone = TRUE;
			return;
		}
		TCPIP_TcpConnect(dyndns_ConnId);
		dyndns_State = DYNDNS_STATE_WAIT_CONNECT;
		dyndns_StartTime = SWTIMER_Tick();
		break;
	case DYNDNS_STATE_WAIT_CONNECT:
		// check if the connection is established?
		nCurrentTime = SWTIMER_Tick();
		if((nCurrentTime - dyndns_StartTime) > MAX_TIMEOUT_VALUE)
		{
			// TCPIP connection fail, set the flag of done and return
			dyndns_CloseConnection();
		}
		break;
	case DYNDNS_STATE_SEND_COMMAND:
		// send the update command to the server
		if(dyndns_AssembleCommandPkt() == FALSE)
		{
			// fail to assemble the update command, set the flag of done and return
			dyndns_bUpdateDone = TRUE;
		}else
		{
			// send the update command to the dynamic DNS server
			TCPIP_TcpSend(dyndns_ConnId, dyndns_Command, dyndns_CmdLen, TCPIP_SEND_NOT_FINAL);
			dyndns_State = DYNDNS_STATE_WAIT_RESPONSE;
			dyndns_StartTime = SWTIMER_Tick();
		}
	   	break;
	case DYNDNS_STATE_WAIT_RESPONSE:
		// check if the response from the server is received?
		nCurrentTime = SWTIMER_Tick();
		if((nCurrentTime - dyndns_StartTime) > MAX_TIMEOUT_VALUE)
		{
			// no response from the DDNS server, set the flag of done and return
			dyndns_CloseConnection();
		}
		break;
	default:
		break;
	}

}

/*
 * -----------------------------------------------------------------------------
 * Function Name: DynDNS_DoUpdateDynDns
 * Purpose: to begin to do the update procedure
 * Params:
 *		Type(CONF_DDNS_3322, CONF_DDNS_DYNDNS, CONF_DDNS_NOIP)
 *		HostIp : the server's ip
 *		User : username
 *		Passwd : password
 * Returns: none
 * Note:
 * ----------------------------------------------------------------------------
 */
void DynDNS_DoUpdateDynDns(U8_T Type, U32_T HostIp, U8_T *Domain, U8_T *User, U8_T *Pass)
{
	U16_T i;

	if(dyndns_bUpdateStart == TRUE)
	{
		// to get the string of domain name
		for(i = 0; i < MAX_DOMAIN_SIZE; i++)
		{
			if(Domain[i] == 0)
			{
				break;
			}
			dyndns_Domain[i] = Domain[i];
		}
		// chech if the size of username reach up to the max value?
		if(i == MAX_DOMAIN_SIZE)
		{ 
			dyndns_bUpdateDone = TRUE;
			return;		
		}
		// to get the string of username
		for(i = 0; i < MAX_USERNAME_SIZE; i++)
		{
			if(User[i] == 0)
			{
				break;
			}
			dyndns_User[i] = User[i];
		}
		// chech if the size of username reach up to the max value?
		if(i == MAX_USERNAME_SIZE)
		{ 
			dyndns_bUpdateDone = TRUE;
			return;		
		}
		// to get the string of password
		for(i = 0; i < MAX_PASSWORD_SIZE; i++)
		{
			if(Pass[i] == 0)
			{
				break;
			}
			dyndns_Pass[i] = Pass[i];
		}
		// chech if the size of password reach up to the max value?
		if(i == MAX_PASSWORD_SIZE)
		{
			dyndns_bUpdateDone = TRUE;
			return;		
		}
		// to get the Host IP
		dyndns_HostIp = HostIp;
		// to get the type of server
		dyndns_Type = Type;
		// set the state to query the host ip of the dynamic DNS server
		dyndns_State = DYNDNS_STATE_MAKE_CONNECT;
		// reset the flag of start and done
		dyndns_bUpdateStart = FALSE;
		dyndns_bUpdateDone = FALSE;

		// check if the ddns type is available in this module?
		if((dyndns_Type == 0) || (dyndns_Type > 3))
		{
			// the ddns type is not found, set the flag of done and return;
			dyndns_bUpdateDone = TRUE;
			return;		
		}
	}

	dyndns_Start();
}