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
 * Module Name: httpd.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: httpd.c,v $
 * Revision 1.0  2006/05/30 06:39:38  Francis
 * Revision 3.0.0  2010/09/29 09:51:00  Smile
 * no message
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "reg80390.h"
#include "stoe.h"
#include "main.h"
#include "mstimer.h"
#include "httpd.h"
#include "filesys.h"
#include "adapter.h"
#include "gs2e.h"
#include "gconfig.h"
#include "tcpip.h"
#include "delay.h"
#include "uart.h"
#include "printd.h"
#include <string.h>
#include "ax11000.h"
#include "ctype.h"
#include "lcd.h"
#include "schedule.h"




#if (INCLUDE_EVENT_DETECT)
#include "gevent.h"
#endif
/* NAMING CONSTANT DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */
entry entries[20];
static U8_T test[10];

extern U8_T far dyndns_username[MAX_USERNAME_SIZE];
extern U8_T far dyndns_domain_name[MAX_DOMAIN_SIZE];
extern U8_T far dyndns_password[MAX_PASSWORD_SIZE];


U8_T num_parms;
/* LOCAL VARIABLES DECLARATIONS */
static HTTP_SERVER_CONN XDATA HTTP_Connects[MAX_HTTP_CONNECT];
static U8_T CODE HtmlHeader[] = {"HTTP/1.0 200 OK\r\nCache-control: no-cache\r\nConnection: Keep-Alive\r\nContent-type: text/html\r\n\r\n"};
static U8_T XDATA HtmlHeaderLen = (sizeof(HtmlHeader) - 1);
static U8_T CODE CSSHeader[] = {"HTTP/1.0 200 OK\r\nCache-control: no-cache\r\nConnection: Keep-Alive\r\nContent-type: text/css\r\n\r\n"};
static U8_T XDATA CSSHeaderLen = (sizeof(CSSHeader) - 1);
static U8_T CODE JsHeader[] = {"HTTP/1.0 200 OK\r\nCache-control: no-cache\r\nConnection: Keep-Alive\r\nContent-type: application/javascript\r\n\r\n"};
static U8_T XDATA JsHeaderLen = (sizeof(JsHeader) - 1);
static U8_T XDATA ImageHeader[] = {"HTTP/1.0 200 OK\r\nCache-control: no-cache\r\nConnection: Keep-Alive\r\nContent-Length: xxxxx\r\nContent-type: image/jpeg\r\n\r\n"};
static U8_T XDATA ImageHeaderLen = (sizeof(ImageHeader) - 1);
static U8_T XDATA ImageByteCountOffset = 82;
HTTP_TEMP_BUF XDATA HTTPtemp;

/* LOCAL SUBPROGRAM DECLARATIONS */

static U8_T HTTP_NewConfig(void);
static void HTTP_DivideHtmlFile(HTTP_SERVER_CONN XDATA* pHttpConn, U8_T id);
static U8_T HTTP_CheckPassWord(HTTP_SERVER_CONN XDATA*	pHttpConn);
static void HTTP_LoadSetting(void);
static U8_T HTTP_CheckNewPassword(void);
static U8_T HTTP_CheckNewUsername(void);
/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_Task()
 * Purpose: Main function
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void HTTP_Task(void)
{

} /* End of HTTP_Task() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_Init()
 * Purpose: Initialize HTTP server. 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void HTTP_Init(void)
{
	U8_T	i;

	for (i = 0; i < MAX_HTTP_CONNECT; i++)
	{
		HTTP_Connects[i].State = HTTP_STATE_FREE;
		HTTP_Connects[i].FileId = 0xff;
		HTTP_Connects[i].ContinueFlag = 0;
	}

	HTTPtemp.InterFaceID = TCPIP_Bind(HTTP_NewConn, HTTP_Event, HTTP_Receive);
	TCPIP_TcpListen(HTTP_SERVER_PORT, HTTPtemp.InterFaceID);

	memset((U8_T*)&HTTPtemp, 0 , sizeof(HTTPtemp));
	FSYS_Init();
	HTTP_LoadSetting();
	if (GCONFIG_GetNetwork() & GCONFIG_NETWORK_ACC_IP_ENABLE)
		HTTPtemp.AccessibleIP_EnableFlag = 1;
//	printd("HTTP init ok.\n\r");

} /* End of HTTP_Init() */
 
/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_NewConn()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T HTTP_NewConn(U32_T XDATA* pip, U16_T remotePort, U8_T socket)
{
	U8_T	i;

	for (i = 0; i < MAX_HTTP_CONNECT; i++)
	{
		if (HTTP_Connects[i].State == HTTP_STATE_FREE)
		{
			HTTP_Connects[i].State = HTTP_STATE_ACTIVE;
			HTTP_Connects[i].Timer = (U16_T)SWTIMER_Tick();
			HTTP_Connects[i].Ip = *pip;
			HTTP_Connects[i].Port = remotePort;
			HTTP_Connects[i].TcpSocket = socket;

			return i;
		}
	}
	return TCPIP_NO_NEW_CONN;
} /* End of HTTP_NewConn() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_Event()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void HTTP_Event(U8_T id, U8_T event)
{
	U8_T	fileId = HTTP_Connects[id].FileId;
	
	if (event < TCPIP_CONNECT_XMIT_COMPLETE)
	{
		if (event == TCPIP_CONNECT_CANCEL)
		{
			if(0)
			{
			}
/*====== for msgrestore.htm web page, start ====== */	//Add for redirection web page
			else if (fileId == FILE_MSGRESTORE)
			{
//				printd("Restore and Reboot!!\n\r");
//				GCONFIG_ReadDefaultConfigData();
//				GCONFIG_WriteConfigData();
//				DELAY_Ms(500);
//				AX11000_SoftReboot();

				lcdreset();
				Lcd_Initial();
				Display_reboot();
				AX11000_SoftReboot();

			}
/*====== for msgrestore.htm web page, end ====== */	
/*====== for msgupg.htm web page, start ====== */		
			else if (fileId == FILE_MSGUPG)
			{
//				printd("Upgrade\n\r");
//				GCONFIG_EnableFirmwareUpgrade();
//				GCONFIG_WriteConfigData();		
//				AX11000_SoftReboot();

				lcdreset();
				Lcd_Initial();
				Display_reboot();
				AX11000_SoftReboot();

			}
/*====== for msgupg.htm web page, end ====== */				
/*====== for msgreboot.htm web page, start ====== */	
			else if (fileId == FILE_MSGREBOOT)			
			{
			//	printd("Device Reboot!!\n\r");			
			//	DELAY_Ms(500);
				lcdreset();
				Lcd_Initial();
				Display_reboot();
				AX11000_SoftReboot();
			}
/*====== for msgreboot.htm web page, end ====== */				
/*====== for msgaccerr.htm web page, start ====== */
			else if (fileId == FILE_MSGACCERR)			
			{
				printd ("Unaccessible error !!\n\r");
			}			
/*====== for msgaccerr.htm web page, end ====== */
		HTTP_Connects[id].State = event;
		}
	}
	else if (event == TCPIP_CONNECT_XMIT_COMPLETE)
	{
		U8_T*			pSour;
		static U16_T	dataLen;

		if (HTTP_Connects[id].State == HTTP_STATE_SEND_HEADER)
		{
			{
				if (FSYS_Manage[fileId].FType & FILE_TYPE_BIN)
				{
					HTTP_Connects[id].Divide.Fragment = 0;
				}
				else
				{
					HTTP_DivideHtmlFile(&HTTP_Connects[id], fileId);
				}

			 	pSour = FSYS_Manage[fileId].PBuf;
				dataLen = FSYS_Manage[fileId].FileSize;

				if (HTTP_Connects[id].Divide.Fragment == 0)
				{
					TCPIP_TcpSend(HTTP_Connects[id].TcpSocket, pSour, dataLen, TCPIP_SEND_FINAL);
					HTTP_Connects[id].State = HTTP_STATE_SEND_FINAL;
				}
				else
				{
					HTTP_Connects[id].State = HTTP_STATE_SEND_DATA;
					HTTP_Connects[id].Divide.PData = pSour;
					HTTP_Connects[id].Divide.LeftLen = dataLen;
					HTTP_Connects[id].Divide.CurIndex = 0;
					HTTP_Connects[id].Divide.PadFlag = 0;
					goto SENDHTML;
				}
			}
		}
		else if (HTTP_Connects[id].State == HTTP_STATE_SEND_DATA)
		{
SENDHTML:

//			Uart0_Tx("send.",5);

			{
				BUF_TEXT XDATA		*pText;
//				BUF_TAG XDATA*		pTag;
				U8_T*				pSour = HTTP_Connects[id].Divide.PData;
				static U8_T XDATA	pTrue[] = " checked";
				static U8_T XDATA	pSele[] = " selected";				
				static U16_T		leftLen;
				static U8_T			index;

				leftLen = HTTP_Connects[id].Divide.LeftLen;
				index = HTTP_Connects[id].Divide.CurIndex;
				
				if (!HTTP_Connects[id].Divide.PadFlag)
				{
					
				//	Uart0_Tx("send0",5);
						
					if (index == 0)
						dataLen = HTTP_Connects[id].Divide.Offset[index];
					else if (index == HTTP_Connects[id].Divide.Fragment)
						dataLen = leftLen;
					else
						dataLen = HTTP_Connects[id].Divide.Offset[index] - 
							HTTP_Connects[id].Divide.Offset[index - 1];

					if (index == HTTP_Connects[id].Divide.Fragment)
					{
						TCPIP_TcpSend(HTTP_Connects[id].TcpSocket, pSour, dataLen, TCPIP_SEND_FINAL);
						HTTP_Connects[id].State = HTTP_STATE_SEND_FINAL;

						 Uart0_Tx("s-1",3);
					}
					else
					{
						TCPIP_TcpSend(HTTP_Connects[id].TcpSocket, pSour, dataLen, TCPIP_SEND_NOT_FINAL);
						HTTP_Connects[id].Divide.PData += dataLen;
						HTTP_Connects[id].Divide.LeftLen -= dataLen;
						HTTP_Connects[id].Divide.PadFlag = 1;

						 Uart0_Tx("s-2",3);
					}
				}
				else
				{
				//	Uart0_Tx("send1",5);

					if (HTTP_Connects[id].Divide.PostType[index] == POST_TYPE_RADIO)
					{
						
						Uart0_Tx("radio",5);
						
						if (HTTP_Connects[id].Divide.SetFlag[index] == 1)
							TCPIP_TcpSend(HTTP_Connects[id].TcpSocket, pTrue, 8, TCPIP_SEND_NOT_FINAL);
						else if (HTTP_Connects[id].Divide.SetFlag[index] == 2)
						{
							if (*pSour == ' ')
							{
								HTTP_Connects[id].Divide.PData += 8;
								HTTP_Connects[id].Divide.Offset[index] += 8;
								HTTP_Connects[id].Divide.LeftLen -= 8;
							}
							else
							{
								HTTP_Connects[id].Divide.PData += 7;
								HTTP_Connects[id].Divide.Offset[index] += 7;
								HTTP_Connects[id].Divide.LeftLen -= 7;
							}
							HTTP_Connects[id].Divide.PadFlag = 0;
							HTTP_Connects[id].Divide.CurIndex++;
							goto SENDHTML;
						}
					}
					else if (HTTP_Connects[id].Divide.PostType[index] == POST_TYPE_TEXT)
					{
						
						Uart0_Tx("text.",5);
						
							pText = POST_Record[HTTP_Connects[id].Divide.RecordIndex[index]].PValue;
							leftLen -= pText->DefaultLength;
							if (!leftLen)
							{
								TCPIP_TcpSend(HTTP_Connects[id].TcpSocket, pText->CurrValue, pText->CurrLength, TCPIP_SEND_FINAL);
								HTTP_Connects[id].State = HTTP_STATE_SEND_FINAL;
								return;
							}

							TCPIP_TcpSend(HTTP_Connects[id].TcpSocket, pText->CurrValue, pText->CurrLength, TCPIP_SEND_NOT_FINAL);
							HTTP_Connects[id].Divide.PData += pText->DefaultLength;
							HTTP_Connects[id].Divide.Offset[index] += pText->DefaultLength;
							HTTP_Connects[id].Divide.LeftLen =leftLen;
					}
#if(MAX_POST_BUF_TAG)					
					else if (HTTP_Connects[id].Divide.PostType[index] == POST_TYPE_TAG)
					{
					
						 Uart0_Tx("Tag",3);
					
					
						pTag = POST_Record[HTTP_Connects[id].Divide.RecordIndex[index]].PValue;
						leftLen -= pTag->DefaultLength;
						if(pTag->CurrLength)
						TCPIP_TcpSend(HTTP_Connects[id].TcpSocket, pTag->CurrValue, pTag->CurrLength, TCPIP_SEND_NOT_FINAL);
						HTTP_Connects[id].Divide.PData += pTag->DefaultLength;
						HTTP_Connects[id].Divide.Offset[index] += pTag->DefaultLength;
						HTTP_Connects[id].Divide.LeftLen =leftLen;
						if(!pTag->CurrLength)
						{
							HTTP_Connects[id].Divide.PadFlag = 0;
							HTTP_Connects[id].Divide.CurIndex++;
							goto SENDHTML;
						}
					} 
#endif										
					else if (HTTP_Connects[id].Divide.PostType[index] == POST_TYPE_SELECT)
					{
					  Uart0_Tx("select",6);
					
						if (HTTP_Connects[id].Divide.SetFlag[index] == 1)
						{
							TCPIP_TcpSend(HTTP_Connects[id].TcpSocket, pSele, 9, TCPIP_SEND_NOT_FINAL);
						}
						else if (HTTP_Connects[id].Divide.SetFlag[index] == 2)
						{
							HTTP_Connects[id].Divide.PData += 9;
							HTTP_Connects[id].Divide.Offset[index] += 9;
							HTTP_Connects[id].Divide.LeftLen -= 9;

							HTTP_Connects[id].Divide.PadFlag = 0;
							HTTP_Connects[id].Divide.CurIndex++;
							goto SENDHTML;
						}
					}	
					HTTP_Connects[id].Divide.PadFlag = 0;
					HTTP_Connects[id].Divide.CurIndex++;
				}
			}
		}
		else if	(HTTP_Connects[id].State == HTTP_STATE_SEND_FINAL)
		{
			// HTTP_Connects[id].State = HTTP_STATE_FREE;
		}
	}
} /* End of HTTP_Event() */


/*
 * ----------------------------------------------------------------------------
 * Function Name: StringCompare()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T StringCompare(U8_T XDATA* pData, U8_T XDATA* pStr, U8_T len)
{
	U8_T	index;

	for (index = 0; index < len; index++)
	{
		if (*pData++ != *pStr++) break;
	}
	if (index == len) return 1;
	
	return 0;
} /* End of StringCompare() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GHTTP_GetFile()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GHTTP_GetFile(U8_T XDATA** pData, U8_T XDATA** pFName, U8_T XDATA** pFNameExt, U16_T* length)
{
	U8_T	c, find = 0;
	U8_T	parse_state = 0;

	c = **pData;
	while ((c != ' ') && (c != '\0') && (c != '\r') && (c != '\n'))
	{
		switch(parse_state)
		{
		case 0:
			if (c == '/' || c == '\\')
			{
				parse_state = 1;
				*pFName = *pData + 1;
			}
			break;
		case 1:
			if (c == '?')
			{
				find = 2;
				return find;
			}
			else if (c == '&')
			{
				**pData = '\0';
				return find;
			}
			else
			{
				if ((c == '+') || (c == '=')) return 0;
				/* a path, change it to '_' */
				else if ((c == '/') || (c == '\\')) **pData = '_';
				/* Remember where file extension starts. */
				else if (c == '.')
				{
					*pFNameExt = *pData + 1;
					find = 1;
				}
			}
			break;
		}
		(*pData)++;
		(*length)--;
		c = **pData;
	}

	return find;
} /* End of GHTTP_GetFile() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_LoadSetting()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void HTTP_LoadSetting(void)
{
//	U32_T				temp32;
	U16_T				temp16;
	BUF_TEXT XDATA		*pText;
	BUF_SELECT XDATA	*pSelect;
	
	// Load IP address
	pText = POST_Record[RECORD_TEXT_static_ip].PValue;
	pText->CurrLength = HTTP_Ulong2IpAddr(GCONFIG_GetServerStaticIP(), pText->CurrValue);
	pText->CurrValue[pText->CurrLength ++] = '"';
	
	// Load subnet mask
	pText = POST_Record[RECORD_TEXT_mask].PValue;
	pText->CurrLength = HTTP_Ulong2IpAddr(GCONFIG_GetNetmask(), pText->CurrValue);
	pText->CurrValue[pText->CurrLength ++] = '"';
		
	// Load gateway
	pText = POST_Record[RECORD_TEXT_gateway_ip].PValue;
	pText->CurrLength = HTTP_Ulong2IpAddr(GCONFIG_GetGateway(), pText->CurrValue);
	pText->CurrValue[pText->CurrLength ++] = '"';

//	// Load DNS
//	pText = POST_Record[RECORD_TEXT_dns_ip].PValue;
//	pText->CurrLength = HTTP_Ulong2IpAddr(GCONFIG_GetDNS(), pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';

//	// Load server listen port
//	pText = POST_Record[RECORD_TEXT_s_lstport].PValue;
//	pText->CurrLength = HTTP_Short2Str(GCONFIG_GetServerDataPktListenPort(), pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';

//	// Load transmit timer
//	pText = POST_Record[RECORD_TEXT_txtimer].PValue;
//	pText->CurrLength = HTTP_Short2Str(GCONFIG_GetEthernetTxTimer(), pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';
		
//	// Load destination port
//	pText = POST_Record[RECORD_TEXT_c_desport].PValue;
//	pText->CurrLength = HTTP_Short2Str(GCONFIG_GetClientDestPort(), pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';	

	// Load DHCP/Connection type/Connection mode/Accessiable control
	temp16 = GCONFIG_GetNetwork();
	
	pSelect = POST_Record[RECORD_SELECT_dhcp].PValue;		//Load DHCP control bit.
	pSelect->CurrentSet = (temp16 & GCONFIG_NETWORK_DHCP_ENABLE) ? 1 : 0;//+1 for web display
	

//	// Load ddns username
//	pText = POST_Record[RECORD_TEXT_ddns_name].PValue;
//	pText->CurrLength = HTTP_Short2Str(GCONFIG_GetClientDestPort(), pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';	





//	pSelect = POST_Record[RECORD_SELECT_conntype].PValue;	//Load Connection type option.
//	pSelect->CurrentSet = (temp16 & GCONFIG_NETWORK_PROTO_TCP) ? 0 : 1;	
		
//	pSelect = POST_Record[RECORD_SELECT_cs_mode].PValue;	//Load client/Server mode option.
//	pSelect->CurrentSet = (temp16 & GCONFIG_NETWORK_CLIENT) ? 1 : 0;

//	pSelect = POST_Record[RECORD_SELECT_acc_ipen].PValue;	//Load accessible IP control bit.
//	pSelect->CurrentSet = (temp16 & GCONFIG_NETWORK_ACC_IP_ENABLE) ? 1 : 0;	
//		
//	// Load serial setting
//	temp16 = GCONFIG_GetSerialPort();
//
//	pSelect = POST_Record[RECORD_SELECT_dbr].PValue;
//	pSelect->CurrentSet = ((temp16 & 0xF800) >> 11);
//
//	pSelect = POST_Record[RECORD_SELECT_data].PValue;
//	pSelect->CurrentSet = ((temp16 & 0x0700) >> 8);
//
//	pSelect = POST_Record[RECORD_SELECT_parity].PValue;
//	pSelect->CurrentSet = ((temp16 & 0x00E0) >> 5);
//
//	pSelect = POST_Record[RECORD_SELECT_stop].PValue;
//	pSelect->CurrentSet = ((temp16 & 0x0003));
//
//	pSelect = POST_Record[RECORD_SELECT_flow].PValue;
//	pSelect->CurrentSet = ((temp16 & 0x0001C) >> 2);
//
//	// Load SMTP Domain name
//	pText = POST_Record[RECORD_TEXT_email_addr].PValue;		
//	pText->CurrLength = GCONFIG_GetSMTPDomainName(pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';
//
//	// Load SMTP From addr
//	pText = POST_Record[RECORD_TEXT_email_from].PValue;
//	pText->CurrLength = GCONFIG_GetSMTPFrom(pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';
//		
//	// Load SMTP To1 addr
//	pText = POST_Record[RECORD_TEXT_email_to1].PValue;
//	pText->CurrLength = GCONFIG_GetSMTPTo1(pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';
//	
//	// Load SMTP To2 addr
//	pText = POST_Record[RECORD_TEXT_email_to2].PValue;
//	pText->CurrLength = GCONFIG_GetSMTPTo2(pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';
//	
//	// Load SMTP To3 addr
//	pText = POST_Record[RECORD_TEXT_email_to3].PValue;
//	pText->CurrLength = GCONFIG_GetSMTPTo3(pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';
//
////	// Load Destination host name
////	pText = POST_Record[RECORD_TEXT_c_deshn].PValue;		
////	pText->CurrLength = GCONFIG_GetDestHostName(pText->CurrValue);
////	pText->CurrValue[pText->CurrLength ++] = '"';	
//	
//	// Load FIle Name
//	pText = POST_Record[RECORD_TEXT_file_name].PValue;
//	GCONFIG_GetFilename(pText->CurrValue, 128);
//	pText->CurrLength = strlen(pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';	
//	
//	// Load Auto Warning enable bits
//	temp16 = GCONFIG_GetAutoWarning();
//	
//	pSelect = POST_Record[RECORD_SELECT_coldstart].PValue;	//Load cold start enable bit
//	pSelect->CurrentSet = (temp16 & GCONFIG_SMTP_EVENT_COLDSTART) ? 1 : 0;
//					
//	pSelect = POST_Record[RECORD_SELECT_authfail].PValue;	//Load authentication fail enable bit
//	pSelect->CurrentSet = (temp16 & GCONFIG_SMTP_EVENT_AUTH_FAIL) ? 1 : 0;
//		
//	pSelect = POST_Record[RECORD_SELECT_ipchg].PValue;		//Load IP changed enable bit
//	pSelect->CurrentSet = (temp16 & GCONFIG_SMTP_EVENT_IP_CHANGED) ? 1 : 0;
//		
//	pSelect = POST_Record[RECORD_SELECT_pswchg].PValue;		//Load password changed enable bit
//	pSelect->CurrentSet = (temp16 & GCONFIG_SMTP_EVENT_PSW_CHANGED) ? 1 : 0;
//		
//	// Accessible IP address 0~3
//	pText = POST_Record[RECORD_TEXT_acc_ip1].PValue;
//	GCONFIG_GetAccessibleIP(0,&temp32);
//	pText->CurrLength = HTTP_Ulong2IpAddr(temp32, pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';
//		
//	pText = POST_Record[RECORD_TEXT_acc_ip2].PValue;
//	GCONFIG_GetAccessibleIP(1,&temp32);
//	pText->CurrLength = HTTP_Ulong2IpAddr(temp32, pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';
//		
//	pText = POST_Record[RECORD_TEXT_acc_ip3].PValue;
//	GCONFIG_GetAccessibleIP(2,&temp32);
//	pText->CurrLength = HTTP_Ulong2IpAddr(temp32, pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';
//		
//	pText = POST_Record[RECORD_TEXT_acc_ip4].PValue;
//	GCONFIG_GetAccessibleIP(3,&temp32);
//	pText->CurrLength = HTTP_Ulong2IpAddr(temp32, pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';
//	
//	// Load rs485 control bits
//	pSelect = POST_Record[RECORD_SELECT_rs485].PValue;
//	pSelect->CurrentSet = GCONFIG_GetRs485Mode();
//
//	// Load Tftp Server IP
//	pText = POST_Record[RECORD_TEXT_tftps_ip].PValue;
//	pText->CurrLength = HTTP_Ulong2IpAddr(GCONFIG_GetTftpServerIp(), pText->CurrValue);
//	pText->CurrValue[pText->CurrLength ++] = '"';
					
} /* End of HTTP_LoadSetting() */


/*
 * ----------------------------------------------------------------------------
 * Function Name: GHTTP_UserPost()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T http_UserPost(U8_T XDATA* pData, U16_T length, U8_T fileId, U8_T continueFlag)
{
	BUF_SUBMIT XDATA	*pSubmit;
	BUF_TEXT XDATA		*pText;
#if (MAX_POST_BUF_RADIO)
	BUF_RADIO XDATA*	pRadio;
#endif
#if (MAX_POST_BUF_SELECT)
	BUF_SELECT XDATA*	pSelect;
#endif	
	U16_T				i;
	U8_T				x, y, a, nameLen;
	U8_T				status = 0, final = 0;

	U8_T index;
  	U8_T tempchar;
	
	U8_T IPtemp[4];	

	if (continueFlag)
		goto MAPRECORD;

	if (length < 150)
	{
		//Uart0_Tx("F0",2);
		return HTTP_POST_FAILURE;
	}

	HTTPtemp.PostCnt = 0;
	if (*pData == '?')
	{
		length -= 1;
		pData += 1;
		goto MAPRECORD;
	}

	i = 0;
	while(i < length)
	{
		while (1)
		{
			if ((pData[0]=='\r')&&(pData[1]=='\n')&&(pData[2]=='\r')&&(pData[3]=='\n'))//Find the two empty line.
			{
				pData += 4;
				i += 4;
				if (i == length) return HTTP_POST_CONTINUE;
					
				break;
			}
			else
			{
				pData++;
				i++;
				if ((i + 3) >= length) 
				
			//	Uart0_Tx("F1",2);

				return HTTP_POST_FAILURE;
			}
		}
MAPRECORD:
		for (x = 0; x < MAX_POST_RECORDS; x++)
		{
			if (POST_Record[x].Occupy == 1)
			{
				// check file id
				if (fileId != POST_Record[x].FileIndex)
				{
					if (POST_Record[x].FileIndex != 0xff)
					{
						continue;
					}
				}

				for (y = 0; y < POST_Record[x].NameLen; y++)
				{
					if (POST_Record[x].Name[y] != pData[y]) 
						break;
				}
				if (y == POST_Record[x].NameLen)
				{
					if (pData[y] == '=')
					{
						nameLen = (y + 1);
						pData += nameLen;
						i += nameLen;

						switch (POST_Record[x].PostType)
						{
						case POST_TYPE_SUBMIT:
							pSubmit = POST_Record[x].PValue;
							for (a = 0; a < pSubmit->DefaultVlaueLen; a++)
							{
								if (pSubmit->Value[a] != pData[a]) 
									break;
							}
							if (a == pSubmit->DefaultVlaueLen)
							{
								HTTPtemp.PostTable[HTTPtemp.PostCnt] = x;
								HTTPtemp.PostCnt ++;

							//	Uart0_Tx("SUBMIT",6);
							//	printd ("SUBMIT\n\r");

								if (pSubmit->IsApply)
								{
								//  Uart0_Tx("F2",2);
									return (status ? HTTP_POST_FAILURE : HTTP_POST_SUCCESS);
								}
								else
									return HTTP_POST_CANCEL;
							}
							else
							{
								pData -= nameLen;
								i -= nameLen;

								goto MAPRECORD;
							}
							break;
						case POST_TYPE_TEXT:
							pText = POST_Record[x].PValue;						
							memset(HTTPtemp.Buf[0], 0, sizeof(HTTPtemp.Buf[0]));
    						index=0;
							for (a = 0; a < MAX_POST_VALUE_LEN + 3; a++)
							{
								if (pData[a] == '&')
									break;
								else if (pData[a] == ' ')
								{
									final = 1;
									break;
								}

								HTTPtemp.Buf[0][index] = pData[a];

								if(pData[a] == '%')
								{	
       								 if(isdigit(pData[a+1]))
          								tempchar = (pData[a+1] - '0') << 4;
        							 else
          								tempchar = ((pData[a+1] - 'A') + 10) << 4;
			  
        							 if(isdigit(pData[a+2]))
          								tempchar += (pData[a+2] - '0');
        							else
          								tempchar += ((pData[a+2] - 'A') + 10);

        						    HTTPtemp.Buf[0][index] = tempchar;
        							a+=2;				
      							}
								index++;
							}

							if (pText == NULL)	// username or password
							{
//------------------- Add for chack username & password function start -------------------------------
								if (fileId == FILE_INDEX)//If posted page is Authentication, get the username and password from web page.
								{
									if (RECORD_TEXT_username == x)
									{
										HTTPtemp.UserNameLen = strlen(HTTPtemp.Buf[0]);
										strncpy(HTTPtemp.UserName, HTTPtemp.Buf[0], HTTPtemp.UserNameLen + 1);//Include '\0' char
									}
									else if (RECORD_TEXT_password == x)
									{
										HTTPtemp.PassWordLen = strlen(HTTPtemp.Buf[0]);
										strncpy(HTTPtemp.PassWord, HTTPtemp.Buf[0], HTTPtemp.PassWordLen + 1);									
									}
									else
									{
									
								//	   	Uart0_Tx("F3",2);
										return HTTP_POST_FAILURE;
									}
//------------------- Add for chack username & password function end -------------------------------
//------------------- Add for set new username & password function start -------------------------------
								}			
								else if (fileId == FILE_SECURITY)
								{
									if (RECORD_TEXT_old_psw == x) // original password
									{
										HTTPtemp.OldPassWordLen = strlen(HTTPtemp.Buf[0]);
										strncpy(HTTPtemp.OldPassWord, HTTPtemp.Buf[0], HTTPtemp.OldPassWordLen + 1);//Include '\0' char
									}
									else if (RECORD_TEXT_new_psw == x) // set new password
									{
										HTTPtemp.NewPassWordLen = strlen(HTTPtemp.Buf[0]);
										strncpy(HTTPtemp.NewPassWord, HTTPtemp.Buf[0], HTTPtemp.NewPassWordLen + 1);
									}
									else if (RECORD_TEXT_cfm_psw == x) // set confirm password
									{
										HTTPtemp.CfmPassWordLen = strlen(HTTPtemp.Buf[0]);
										strncpy(HTTPtemp.CfmPassWord, HTTPtemp.Buf[0], HTTPtemp.CfmPassWordLen + 1);

									}
									else if (RECORD_TEXT_new_usn == x) // set new username
									{
										HTTPtemp.NewUserNameLen = strlen(HTTPtemp.Buf[0]);
										strncpy(HTTPtemp.NewUserName, HTTPtemp.Buf[0], HTTPtemp.NewUserNameLen + 1);
									}
									else
									{
									
										//	Uart0_Tx("F4",2);
										return HTTP_POST_FAILURE;
									}
								}
								else									
//------------------- Add for set new username & password function end -------------------------------
								{
								//	Uart0_Tx("F5",2);
								
									return HTTP_POST_FAILURE;
								}
							}
							else
							{
//									Uart0_Tx("F8",2);
									strncpy(pText->UserValue, HTTPtemp.Buf[0], strlen(HTTPtemp.Buf[0]) + 1);//copy post data to user value include '\0' character.
									pText->UserLength = strlen(HTTPtemp.Buf[0]);//set user length not include '\0' character.
/*====== for nrmsetting.htm web page, start ====== */
//									if ((x == RECORD_TEXT_static_ip) ||
//										(x == RECORD_TEXT_tftps_ip) ||									
//										(x == RECORD_TEXT_dns_ip))

									if ((x == RECORD_TEXT_static_ip) ||
										(x == RECORD_TEXT_tftps_ip)) 									
									{
										*(U32_T*)IPtemp = HTTP_IpAddr2Ulong(pText->UserValue, pText->UserLength);
										if (*(U32_T*)IPtemp == 0xffffffff){ 
								//		Uart0_Tx("F17",3);
										return HTTP_POST_FAILURE;	   }
										if ((IPtemp[0] == 0) || (IPtemp[0] > 223) || (IPtemp[3] == 0) || (IPtemp[3] == 255)) 
									//	 Uart0_Tx("F16",3);
										return HTTP_POST_FAILURE;
									}
									else if (x == RECORD_TEXT_mask)
									{
										*(U32_T*)IPtemp = HTTP_IpAddr2Ulong(pText->UserValue, pText->UserLength);
										if (*(U32_T*)IPtemp == 0xffffffff) 
											{
									//		Uart0_Tx("F15",3);
											return HTTP_POST_FAILURE; }
										if (IPtemp[0] != 255) 
										   {
									//	   Uart0_Tx("F14",3);
											return HTTP_POST_FAILURE;
											}
										if (IPtemp[0] >= 128)
										{
											if (IPtemp[1] != 255) 
									//		Uart0_Tx("F13",3);
											return HTTP_POST_FAILURE;
										}
									}
									else if (x == RECORD_TEXT_gateway_ip)
									{
										*(U32_T*)IPtemp = HTTP_IpAddr2Ulong(pText->UserValue, pText->UserLength);									
										if (pText->UserLength)
										{
											if (*(U32_T*)IPtemp == 0xffffffff) 
										//	   	Uart0_Tx("F12",3);
											return HTTP_POST_FAILURE;
// 											if ((IPtemp[3] == 0) || (IPtemp[3] == 255)) return HTTP_POST_FAILURE;
										}
									}
//								   else if	((x == RECORD_TEXT_s_lstport) ||
//											 (x == RECORD_TEXT_c_desport))
//									{
//										Porttemp = HTTP_Str2Short(pText->UserValue, pText->UserLength);
//										if (Porttemp < 1024) return HTTP_POST_FAILURE;
//										
//									}
//									else if ((x == RECORD_TEXT_acc_ip1) ||
//											 (x == RECORD_TEXT_acc_ip2) ||
//											 (x == RECORD_TEXT_acc_ip3) ||
//											 (x == RECORD_TEXT_acc_ip4))
//									{
//										*(U32_T*)IPtemp = HTTP_IpAddr2Ulong(pText->UserValue, pText->UserLength);
//										if (*(U32_T*)IPtemp == 0xffffffff) return HTTP_POST_FAILURE;
////										if ((IPtemp[3] == 255)) return HTTP_POST_FAILURE;									
//								}
							}
/*====== for nrmsetting.htm web page, end ====== */
							if (strlen(HTTPtemp.Buf[0]) == MAX_POST_VALUE_LEN)
							{
								if ((pData[a] != '&') && (pData[a] != ' '))
								{
									printd ("TEXT_FALSE\n\r");
									status = 1;
									pData += a;
									i += a;

									while ((*pData != '&') && (*pData != 0xa) && (*pData != 0xd))
									{
										pData++;
										i++;
									}

									pData++;
									i++;

								   	goto MAPRECORD;
								}
								else if (pData[a] == ' ') final = 1;
							}
							printd ("POST_TEXT: %s\n\r", HTTPtemp.Buf[0]);
							HTTPtemp.PostTable[HTTPtemp.PostCnt] = x;
							HTTPtemp.PostCnt ++;
							if (final == 1)
							{
							//	Uart0_Tx("F6",2);
								return (status ? HTTP_POST_FAILURE : HTTP_POST_SUCCESS);									
							}
							pData += (a + 1);
							i += (a + 1);
							goto MAPRECORD;
							break;
#if (MAX_POST_BUF_RADIO)
						case POST_TYPE_RADIO:
							pRadio = POST_Record[x].PValue;
							for (j = 0; j < pRadio->Count; j++)
							{
									for (a = 0; a < pRadio->Length[j]; a++)
								{
									if (pRadio->Value[j][a] != pData[a]) break;
								}
								if (a == pRadio->Length[j])
								{
									pData += (a + 1);
									i += (a + 1);
									pRadio->UserSet = j;
									HTTPtemp.PostTable[HTTPtemp.PostCnt] = x;
									HTTPtemp.PostCnt ++;

									printd ("Radio item : %bx\n\r", j);

									goto MAPRECORD;
								}
							}
					//		Uart0_Tx("F7",2);
							return HTTP_POST_FAILURE;
							break;
#endif
#if (MAX_POST_BUF_SELECT)
						case POST_TYPE_SELECT:
							pSelect = POST_Record[x].PValue;

							pSelect->UserSet = (*pData) - 0x30;

							if (pSelect->UserSet >= pSelect->Count)
								
						//		Uart0_Tx("F8",2);
								return HTTP_POST_FAILURE;

							pData++;
							i++;

							if (*pData != '&')
							{
								/* support select item > 10 */
								if ((*pData >= '0') && (*pData <= '9'))
								{
									pSelect->UserSet *= 10;
									pSelect->UserSet += ((*pData) - 0x30);
									if (pSelect->UserSet >= pSelect->Count)
										{
								//			Uart0_Tx("F11",3);
										return HTTP_POST_FAILURE;
										}
									pData++;
									i++;
								}

								if (*pData != '&')
								{
									while ((*pData != '&') && (*pData != 0xa) && (*pData != 0xd))
									{
										pData++;
										i++;
									}

									pData++;
									i++;

								   	goto MAPRECORD;
								}
							}

							pData++;
							i++;
							HTTPtemp.PostTable[HTTPtemp.PostCnt] = x;
							HTTPtemp.PostCnt ++;
							printd("POST_SELECT: %bu\n\r", pSelect->UserSet);
							goto MAPRECORD;
							break;
#endif
						default:
							break;
						}
					}
				}
			}
		}
	}
	
	//	Uart0_Tx("F9",2);			
	return HTTP_POST_FAILURE;																				
} /* End of GHTTP_UserPost() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: http_PostVal()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T http_PostVal(U8_T XDATA* pData, U16_T length,U8_T Continue_Flag )
{
  U8_T* pTemp;
  U8_T idx,index;
  U16_T temp;
  U8_T tempchar;
  
  num_parms=0;
  pData[length]=0x0;

  if(!Continue_Flag)
  {
	for(temp=0;temp<length;temp++)
  	{
		if((pData[temp]=='\r') && (pData[temp+1]=='\n') && (pData[temp+2]=='\r') && (pData[temp+3]=='\n')) break;
  	}
  	if(temp==length) 
//	Uart0_Tx("F21",3);
	return HTTP_POST_FAILURE;
	pData+=temp+4;
  }
  
  idx=0;
  while (*pData != 0x0)
  {
    entries[idx].name = pData;
    pTemp = strchr(pData, '=');
    if (!pTemp) break;
    pData=pTemp;
    *pData++ = 0x0;
    entries[idx].val = pData;
		
    while (*pData != 0x0)
    {
      if (*pData == '\r') *pData++= 0x0;
      if (*pData == '&')
      {
        *pData++ = 0x0;    
        if (*pData == 0x0d) pData += 2;  //for \r\n
        break;
      }
      pData++;
    }

    /* convert  '+' to spaces */
    pTemp = entries[idx].val;
    for (; *pTemp != 0x0; pTemp++)
      if (*pTemp == '+') *pTemp = ' '; 
                
    /* convert  '%XX' */
    memset(HTTPtemp.Buf[0], 0, sizeof(HTTPtemp.Buf[0]));
    index=0;
    for (pTemp = entries[idx].val ; *pTemp != 0x0 ; pTemp++)
    {
      HTTPtemp.Buf[0][index] = *pTemp;
      if (*pTemp == '%')
      {	
        if (isdigit(*(pTemp+1)))
          tempchar = (*(pTemp+1) - '0') << 4;
        else
          tempchar = ((*(pTemp+1) - 'A') + 10) << 4;
			  
        if (isdigit(*(pTemp+2)))
          tempchar += (*(pTemp+2) - '0');
        else
          tempchar += ((*(pTemp+2) - 'A') + 10);

        HTTPtemp.Buf[0][index] = tempchar;
        pTemp+=2;				
      }
      index ++;
    }
    strncpy(entries[idx].val, HTTPtemp.Buf[0], strlen(HTTPtemp.Buf[0])+1 );
    idx++;
  }

  if(idx==0) return HTTP_POST_CONTINUE; 
  num_parms=idx;
  return  0;
} /* End of http_PostVal() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_Receive()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void HTTP_Receive(U8_T XDATA* pData, U16_T length, U8_T conn_id)
{
	HTTP_SERVER_CONN XDATA*	pHttpConn = &HTTP_Connects[conn_id];
	U8_T XDATA				str_post[] = {"POST"};
	U8_T					command, status, fileId, index, fileStatus;
	U8_T XDATA*				pFName;
	U8_T XDATA*				pFNameExt;
	U8_T CODE*				pSour;
	U8_T 					*pExpanSour;
	U16_T					data_len;
	U8_T i, j;
    U16_T num_parms=0;
	
	U32_T AccIP;
			
	if (pHttpConn->State < HTTP_STATE_ACTIVE) return;
	
	if (pHttpConn->ContinueFlag)
	{
		fileId = pHttpConn->ContinueFileId;
		goto POST_START;
	}
	
	if (length < 14) return;

	if (StringCompare(pData, str_post, 4))
	{
		command = HTTP_CMD_POST;
		pData += 5;
		length -= 5;
	}
	else
	{
		command = HTTP_CMD_GET;
		pData += 4;
		length -= 4;
	}

	/* skip space */
	while (*pData == ' ')
		pData++;

	fileId = MAX_STORE_FILE_NUM;
	fileStatus = GHTTP_GetFile(&pData, &pFName, &pFNameExt, &length);
	
	if (fileStatus)
		fileId = FSYS_FindFile(pFName);

//	 Uart0_Tx("FileId=.",7);
//	 test[0] = fileStatus;
//	 Uart0_Tx(test,1);

//-----  Add for accessible IP function start ------	
	if ((HTTPtemp.AccessibleIP_EnableFlag != 0) && (FSYS_Manage[fileId].FType == FILE_TYPE_HTML))
	{
		for (i = 0 ; i < GCONFIG_ACCESSIBLE_IP_NUM ; i ++)
		{
			GCONFIG_GetAccessibleIP(i, &AccIP);
			if (pHttpConn->Ip == AccIP) break;
		}

		if (i == GCONFIG_ACCESSIBLE_IP_NUM)
		{
			fileId = FILE_MSGACCERR;
			goto HTTP_TX_HEADER;
		}
	}
//-----  Add for accessible IP function end ------
//--------- Add for user link to not index page directly start ----------------------------------------
//--------- Add for user link to not index page directly end ----------------------------------------	
	if (fileStatus == 2) /* for GET /XXX.XXX?--- mode */
		goto POST_START;

	if (command == HTTP_CMD_POST)
	{
POST_START:

		if (fileId == MAX_STORE_FILE_NUM)		//19
		{
			TCPIP_TcpClose(pHttpConn->TcpSocket); /*RST | ACK*/
			pHttpConn->State = HTTP_STATE_FREE;
			return;
		}
		
		if(FSYS_Manage[fileId].CgiRef==0xff)
		{
			status = http_PostVal(pData, length, pHttpConn->ContinueFlag);

			if (status == HTTP_POST_CONTINUE)
			{
				pHttpConn->ContinueFlag = 1;
				pHttpConn->ContinueFileId = fileId;
				return;
			}

			i=0;
			while(i<num_parms)
			{
				printd("entry[%02bx]=%s,%s\n",i,entries[i].name,entries[i].val);
				i++;
			}  
			pHttpConn->ContinueFlag = 0;

			if (status == HTTP_POST_FAILURE)
			{

				TCPIP_TcpClose(pHttpConn->TcpSocket);/* RST | ACK*/
				pHttpConn->State = HTTP_STATE_FREE;
				return;
			}
		}	
		else
		{								 /* 0 ~ 18*/
			/* look for Referer */
			status = http_UserPost(pData, length, FSYS_Manage[fileId].CgiRef, pHttpConn->ContinueFlag);

				 Uart0_Tx("staus=",6);
				 test[0] = status;
				 Uart0_Tx(test,1);


			if (status == HTTP_POST_SUCCESS)
			{
			
				pHttpConn->ContinueFlag = 0;

/*====== for index.htm web page, start ====== */
				if (fileId == FILE_INDEX)
				{
					status = HTTP_CheckPassWord(pHttpConn);
					if (status == HTTP_POST_FAILURE)
					{
#if (INCLUDE_EVENT_DETECT)
//						GEVENT_SetAuthFailEvent(1);
//						*** Add for authentication fail detect ***					
#endif
						fileId = FILE_MSGAUTHERR;
					}
					else
					{
						fileId = FILE_MSGAUTHOK;
					}
				}
/*====== for index.htm web page, end ====== */
/*====== for security.htm web page, start ====== */
				else if (fileId == FILE_SECURITY)
				{
					if ((HTTPtemp.PostTable[0] == RECORD_TEXT_old_psw) &&
						(HTTPtemp.PostTable[1] == RECORD_TEXT_new_psw) &&
						(HTTPtemp.PostTable[2] == RECORD_TEXT_cfm_psw) && 
						(HTTPtemp.PostCnt == 4))
					{
						status = HTTP_CheckNewPassword();
						fileId = (status == HTTP_POST_FAILURE) ? FILE_MSGSCTERR : FILE_MSGUNPWOK;
					}
					else if ((HTTPtemp.PostTable[0] == RECORD_TEXT_new_usn) &&
							 (HTTPtemp.PostCnt == 2))
					{
						status = HTTP_CheckNewUsername();
						fileId = (status == HTTP_POST_FAILURE) ? FILE_MSGSCTERR : FILE_MSGUNPWOK;
					}
					else
						goto POST_NORM;
				}
/*==================  dyndns ==============================*/
				else if (fileId == FILE_DDNS )
				{

//				 for(i = 0; i < (U8_T)strlen(dyndns_username);i++)
//				 {
//				 	test[0] = dyndns_username[i];
//					Uart0_Tx(test,1);
//				 }

				}
				else
				{
/*====== for security.htm web page, end ====== */				
POST_NORM:
					status = HTTP_NewConfig();
/*====== for msgreboot.htm web page, start ====== */
					if (fileId == FILE_BSCSETTING)
					{
						if (HTTPtemp.SysRebootFlag)
						{
							HTTPtemp.SysRebootFlag = 0;
							fileId = FILE_MSGREBOOT;
						}
					}
/*====== for msgreboot.htm web page, end ====== */
/*====== for advsetting.htm web page, start ====== */
					else if (fileId == FILE_ADVSETTING)
					{
						for (i = 0; i < HTTPtemp.PostCnt ; i ++)
						{
							j = HTTPtemp.PostTable[i];
							if (!strncmp("upgrade", POST_Record[j].Name, POST_Record[j].NameLen))
							{
								fileId = FILE_MSGUPG;
								break;
							}
						}
					}
/*====== for advsetting.htm web page, end ====== */
				}
			}
			else if (status == HTTP_POST_CONTINUE)
			{
							
				Uart0_Tx("POST continue.",14);
			
				pHttpConn->ContinueFlag = 1;
				pHttpConn->ContinueFileId = fileId;
				return;
			}
			else if (status == HTTP_POST_FAILURE)
			{
				pHttpConn->ContinueFlag = 0;				

				Uart0_Tx("POST error data.",16);

				if (fileId == FILE_ADVSETTING)
					fileId = FILE_MSGADVERR;
				else if (fileId == FILE_BSCSETTING)
					fileId = FILE_MSGBSCERR;
				else if (fileId == FILE_SECURITY)
					fileId = FILE_MSGSCTERR;
				else if (fileId == FILE_DDNS)
					fileId = FILE_DDNS;

				else
				{
				TCPIP_TcpClose(pHttpConn->TcpSocket);/* RST | ACK*/
				pHttpConn->State = HTTP_STATE_FREE;
				return;
			}
		}
	}
	}

	if (command == HTTP_CMD_GET)
	{
	//	Uart0_Tx("get the webpage.",16);
		if (fileStatus)
		{
			if (fileId == MAX_STORE_FILE_NUM)
			{
				/* not find file, send reset */
				TCPIP_TcpClose(pHttpConn->TcpSocket);/* RST | ACK*/
				pHttpConn->State = HTTP_STATE_FREE;
				return;
			}
//--------- Add for delete validated IP when user logout start ----------------------------------------			
			else if (fileId == FILE_INDEX)
			{
				for (i = 0; i < 4; i++)
				{
					if (HTTPtemp.AuthenIP[i] == pHttpConn->Ip)
						HTTPtemp.AuthenIP[i] = 0;
				}
			}
//--------- Add for delete validated IP when user logout end ----------------------------------------						
		}
		else
		{
//--------- Add for user link to a web page not specify file name start ----------------------------------------
			fileId = FILE_JMPINDEX;
//--------- Add for user link to a web page not specify file name end ----------------------------------------
		}
	}

//call cgi function
	if(FSYS_Manage[fileId].CgiCall)
	{
		void (*pF)(void);
		pF= FSYS_Manage[fileId].CgiCall;
		pF();
	}	
// update data in some web page
	{
		U8_T i;

		for (i = 0; i < MAX_POST_RECORDS; i++)
		{
			if (fileId == POST_Record[i].FileIndex)
			{
				if ((POST_Record[i].UpdateSelf == TRUE) && (POST_Record[i].PostType == POST_TYPE_TAG))
				{
					void *pValue = POST_Record[i].PValue;
					void (*f)(void *pWebData);
					f = fun_tbl[i];
					f(pValue);
				}
			}
		}
	}
HTTP_TX_HEADER:	
	pHttpConn->FileId = fileId;

	/* begin send html and jpg header */
	if (FSYS_Manage[fileId].FType & FILE_TYPE_BIN)
	{
		data_len = (U32_T)FSYS_Manage[fileId].FileSize;

		index = 5;
		while (index > 0)
		{
			index--;
			ImageHeader[ImageByteCountOffset + index] = (U8_T)((data_len%10) + 0x30);
			data_len /= 10;
		}
		
		if (FSYS_Manage[fileId].FType == FILE_TYPE_CSS)
		{
			data_len = (U32_T)CSSHeaderLen;
			pExpanSour = CSSHeader;
		}
		else
		{ 
			data_len = (U32_T)ImageHeaderLen;
			pExpanSour = ImageHeader;
		}
		TCPIP_TcpSend(pHttpConn->TcpSocket, pExpanSour, data_len, TCPIP_SEND_NOT_FINAL);
	}
	else
	{
		if (FSYS_Manage[fileId].FType == FILE_TYPE_JS)
		{
			data_len = (U32_T)JsHeaderLen;
			pSour = JsHeader;
		}
		else
		{ 
			HTTP_LoadSetting();
			data_len = (U32_T)HtmlHeaderLen;
			pSour = HtmlHeader;
		}
		TCPIP_TcpSend(pHttpConn->TcpSocket, pSour, data_len, TCPIP_SEND_NOT_FINAL);
	}

	pHttpConn->State = HTTP_STATE_SEND_HEADER;

} /* End of HTTP_Receive() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_DivideHtmlFile()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void HTTP_DivideHtmlFile(HTTP_SERVER_CONN XDATA* pHttpConn, U8_T id)
{
#if (MAX_POST_BUF_RADIO)
	BUF_RADIO XDATA		*pRadio;
#endif
	BUF_TEXT XDATA		*pText;
#if (MAX_POST_BUF_SELECT)	
	BUF_SELECT XDATA	*pSelect;
#endif
	BUF_TAG XDATA		*pTag;
	U8_T				tableIndex = 0;
	U8_T				i, k;

	{
		for (i = 0; i < MAX_POST_RECORDS; i++)
		{
			if (id != POST_Record[i].FileIndex)
				continue;
//--------------- Ignore process for non-data structure item start -----------------------
			if ((i == RECORD_TEXT_old_psw) || 
				(i == RECORD_TEXT_new_psw) || 
				(i == RECORD_TEXT_cfm_psw) || 
				(i == RECORD_TEXT_username) ||
				(i == RECORD_TEXT_password) ||
				(i == RECORD_TEXT_new_usn))
				continue;
//--------------- Ignore process for non-data structure item end -------------------------
			if (POST_Record[i].PostType == POST_TYPE_TEXT)
			{
				U8_T	*pData;

					pText = POST_Record[i].PValue;
					if ((!pText) || (pText->DefaultLength == 0) || (pText->CurrLength == 0) ||
						((pText->CurrLength == 1) && (pText->DefaultLength == 1))) continue;

					pData = FSYS_Manage[id].PBuf + pText->Offset;
					if (pText->CurrLength == pText->DefaultLength)
					{
						for (k = 0; k < pText->CurrLength; k++)
						{
							if (pData[k] != pText->CurrValue[k]) break;
						}
						if (k == pText->CurrLength)	continue;
					}
								
					pHttpConn->Divide.Offset[tableIndex] = pText->Offset;
				pHttpConn->Divide.RecordIndex[tableIndex] = i;
				pHttpConn->Divide.PostType[tableIndex] = POST_TYPE_TEXT;

				tableIndex++;
			}
			else if (POST_Record[i].PostType == POST_TYPE_TAG)
			{
				
				pTag = POST_Record[i].PValue;
				if (pTag->DefaultLength == 0)
					continue;
				pHttpConn->Divide.Offset[tableIndex] = pTag->Offset;
				pHttpConn->Divide.RecordIndex[tableIndex] = i;
				pHttpConn->Divide.PostType[tableIndex] = POST_TYPE_TAG;

				tableIndex++;
			}
#if (MAX_POST_BUF_RADIO)	
			else if (POST_Record[i].PostType == POST_TYPE_RADIO)
			{
				pRadio = POST_Record[i].PValue;
				if (pRadio->DefaultSet == pRadio->CurrentSet)
					continue;
			
				for (k = 0; k < pRadio->Count; k++)
				{
					pHttpConn->Divide.Offset[tableIndex] = pRadio->Offset[k];
					pHttpConn->Divide.RecordIndex[tableIndex] = i;
					pHttpConn->Divide.PostType[tableIndex] = POST_TYPE_RADIO;
					if (pRadio->CurrentSet == k)
					{
						pHttpConn->Divide.SetFlag[tableIndex] = 1;
						tableIndex++;
					}
					else if (pRadio->DefaultSet == k)
					{
						pHttpConn->Divide.SetFlag[tableIndex] = 2;
						tableIndex++;
					}
				}
			}
#endif
#if (MAX_POST_BUF_SELECT)
			else if (POST_Record[i].PostType == POST_TYPE_SELECT)
			{
				pSelect = POST_Record[i].PValue;
				if ((pSelect->DefaultSet == pSelect->CurrentSet) ||
						(pSelect->CurrentSet >= pSelect->Count))
				{
					continue;
				}
				for (k = 0; k < pSelect->Count; k++)
				{
					if (pSelect->DefaultSet == k)
					{
						pHttpConn->Divide.Offset[tableIndex] = pSelect->Offset[k];
						pHttpConn->Divide.RecordIndex[tableIndex] = i;
						pHttpConn->Divide.PostType[tableIndex] = POST_TYPE_SELECT;
						pHttpConn->Divide.SetFlag[tableIndex] = 2;
						tableIndex++;	  
					}
					else if (pSelect->CurrentSet == k)
					{
						pHttpConn->Divide.Offset[tableIndex] = pSelect->Offset[k];
						pHttpConn->Divide.RecordIndex[tableIndex] = i;
						pHttpConn->Divide.PostType[tableIndex] = POST_TYPE_SELECT;
						pHttpConn->Divide.SetFlag[tableIndex] = 1;
						tableIndex++;
					}
				}			
			}
#endif			
			else
				continue;
		}
	}
	pHttpConn->Divide.Fragment = tableIndex;	

} /* End of HTTP_DivideHtmlFile() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_NewConfig()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T HTTP_NewConfig(void)
{
#if (MAX_POST_BUF_RADIO)
	BUF_RADIO XDATA		*pRadio;
#endif
	BUF_TEXT XDATA		*pText;
#if (MAX_POST_BUF_SELECT)
	BUF_SELECT XDATA	*pSelect;
#endif	
	U8_T				i;
	U8_T				change;
	void				(*f)(void *pWebData);

	HTTPtemp.SaveCfgFlag = 0;
	HTTPtemp.SysRebootFlag = 0;	


	return HTTP_POST_SUCCESS;


	for (i = 0; i < HTTPtemp.PostCnt; i++)
	{
		if (POST_Record[HTTPtemp.PostTable[i]].PostType == POST_TYPE_TEXT)
		{
			change = 0;
			pText = POST_Record[HTTPtemp.PostTable[i]].PValue;
			
			if (pText == NULL) continue; // it may be password
			{
				if ((pText->CurrLength - 1) == pText->UserLength)
				{
					if (memcmp(pText->CurrValue, pText->UserValue, pText->CurrLength - 1))	change = 1;
				}
				else change = 1;

				if (!change) continue;

				memcpy(pText->CurrValue, pText->UserValue, pText->UserLength);
				pText->CurrValue[pText->UserLength] = '"';
				pText->CurrLength = pText->UserLength + 1;
				pText->UserLength ++;

				f = fun_tbl[HTTPtemp.PostTable[i]];
				f(pText);
			}
		}
#if (MAX_POST_BUF_RADIO)		
		else if (POST_Record[HTTPtemp.PostTable[i]].PostType == POST_TYPE_RADIO)
		{
			change = 0;
			pRadio = POST_Record[HTTPtemp.PostTable[i]].PValue;	
			if (pRadio->UserSet != pRadio->CurrentSet)
			{
				pRadio->CurrentSet = pRadio->UserSet;
				change = 1;
			}

			if (!change) continue;

			f = fun_tbl[HTTPtemp.PostTable[i]];
			f(&pRadio->CurrentSet);
		}
#endif
#if (MAX_POST_BUF_SELECT)
		else if (POST_Record[HTTPtemp.PostTable[i]].PostType == POST_TYPE_SELECT)
		{
			change = 0;
			pSelect = POST_Record[HTTPtemp.PostTable[i]].PValue;
			{
				if (pSelect->UserSet != pSelect->CurrentSet)
				{
					pSelect->CurrentSet = pSelect->UserSet;
					change = 1;
				}
				if (!change) continue;

				f = fun_tbl[HTTPtemp.PostTable[i]];
				f(&pSelect->CurrentSet);
			}
		}
#endif
		else continue;
	}

	if (HTTPtemp.SaveCfgFlag)
	{
		printd("Change Setting\n\r");
		GCONFIG_WriteConfigData();		
	}
	
	return HTTP_POST_SUCCESS;

} /* End of HTTP_NewConfig() */


/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_Ulong2IpAddr()
 * Purpose: Transfer a ulong number to ip address string. exp: 192.168.0.3
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T HTTP_Ulong2IpAddr(U32_T ip, U8_T* pbuf)
{
	U8_T*	point = (U8_T*)&ip;
	U8_T	i = sizeof (U32_T);
	U8_T	temp, value[3];
	U8_T	j, len = 0;

	while (i--)
	{
		temp = *point++;
		if (temp == 0)
		{
			*pbuf++ = 0x30;
			len++;
		}
		else
		{
			j = 3;
			while (j--)
			{
				value[j] = (temp % 10) + 0x30;
				temp /= 10;
			}

			if (value[0] != '0')
			{
				*pbuf++ = value[0];
				*pbuf++ = value[1];
				*pbuf++ = value[2];
				len += 3;
			}
			else if (value[1] != '0')
			{
				*pbuf++ = value[1];
				*pbuf++ = value[2];
				len += 2;
			}
			else
			{
				*pbuf++ = value[2];
				len++;
			}
		}

		if (i)
		{
			*pbuf++ = '.';
			len++;
		}
	}

	return len;
			
} /* End of HTTP_Ulong2IpAddr() */

/*====== for index.htm web page, start ====== */
/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_CheckPassWord()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T HTTP_CheckPassWord(HTTP_SERVER_CONN XDATA*	pHttpConn)
{
	U8_T	Index, LvlTemp;

	return HTTP_POST_SUCCESS;  /* jump */

	if ((HTTPtemp.PostCnt != 3) ||
		(HTTPtemp.PostTable[0] != RECORD_TEXT_username) || 
		(HTTPtemp.PostTable[1] != RECORD_TEXT_password))
	{
		printd ("Login: Lost username or password data!\n\r");	
		
	//	Uart0_Tx("F22",3);
		return HTTP_POST_FAILURE;
	}

	if ((HTTPtemp.UserNameLen == 0) || 
		(HTTPtemp.PassWordLen == 0) || 
		(HTTPtemp.UserNameLen > MAX_AUTH_POST_VALUE_LEN) || 
		(HTTPtemp.PassWordLen > MAX_AUTH_POST_VALUE_LEN))
	{
		printd ("Login: username or password length error!\n\r");
	//	Uart0_Tx("F23",3);
		return HTTP_POST_FAILURE;	
	}
	
	for (Index = 0; Index < MAX_USER_COUNT; Index ++)
	{
		GCONFIG_GetAdmin(HTTPtemp.Buf[0], HTTPtemp.Buf[1], &LvlTemp);	//Get username and password.	
		if ((HTTPtemp.UserNameLen == strlen(HTTPtemp.Buf[0])) && 		//Check length and content, not include '\0' char.
			(HTTPtemp.PassWordLen == strlen(HTTPtemp.Buf[1])) &&		
			(memcmp(HTTPtemp.UserName, HTTPtemp.Buf[0], HTTPtemp.UserNameLen) == 0) &&			
			(memcmp(HTTPtemp.PassWord, HTTPtemp.Buf[1], HTTPtemp.PassWordLen) == 0))
			break;
	}
	
	if (Index == MAX_USER_COUNT)
	{
		printd ("Login: username or password not metch!\n\r");	
 	//	Uart0_Tx("F24",3);
		return HTTP_POST_FAILURE;
	}
	
	for (Index = 0 ; Index < MAX_HTTP_CONNECT ; Index ++)		//Fine a empty space for save authenticationed IP.
	{
		if (HTTPtemp.AuthenIP[Index] == 0)
		{
			HTTPtemp.AuthenIP[Index] = pHttpConn->Ip;
			break;
		}
	}

	if (Index == MAX_HTTP_CONNECT)		//Force this IP to save.
		HTTPtemp.AuthenIP[0] = pHttpConn->Ip;
	
	printd ("Login: username and password check ok!\n\r");	
	return HTTP_POST_SUCCESS;						

} /* End of HTTP_CheckPassWord() */
/*====== for index.htm web page, end ======*/
/*====== for system.htm web page, start ====== */
/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_CheckNewPassword()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T HTTP_CheckNewPassword(void)
{
	U8_T Index, LvlTemp;
	
	  return HTTP_POST_SUCCESS;

	if ((HTTPtemp.PostCnt != 4) ||
		(HTTPtemp.PostTable[0] != RECORD_TEXT_old_psw) || 
		(HTTPtemp.PostTable[1] != RECORD_TEXT_new_psw) || 
		(HTTPtemp.PostTable[2] != RECORD_TEXT_cfm_psw))
	{
		printd ("Change PassWord: Lost password data!\n\r");	
	//	Uart0_Tx("F25",3);
		return HTTP_POST_FAILURE;
	}

	if ((HTTPtemp.NewPassWordLen == 0) || 
		(HTTPtemp.CfmPassWordLen == 0) || 
		(HTTPtemp.NewPassWordLen > MAX_AUTH_POST_VALUE_LEN) || 
		(HTTPtemp.CfmPassWordLen > MAX_AUTH_POST_VALUE_LEN))
	{
		printd ("Change PassWord: New password or confirm password length error!\n\r");
//		Uart0_Tx("F25",3);
		return HTTP_POST_FAILURE;	
	}

	for (Index = 0; Index < MAX_USER_COUNT; Index ++)//Find the Old password.
	{
		GCONFIG_GetAdmin(HTTPtemp.Buf[0], HTTPtemp.Buf[1], &LvlTemp);
		if ((HTTPtemp.OldPassWordLen == strlen(HTTPtemp.Buf[1])) &&
			(memcmp(HTTPtemp.Buf[1], HTTPtemp.OldPassWord, HTTPtemp.OldPassWordLen) == 0))
			break;
	}

	if (Index == MAX_USER_COUNT) 
	{
		printd ("Change PassWord: Old password not found!\n\r");		
	//	Uart0_Tx("F26",3);
		
		return HTTP_POST_FAILURE;
	}

	if (HTTPtemp.NewPassWordLen != HTTPtemp.CfmPassWordLen)
	{
		printd ("Change PassWord: New password and confirm password length not equal!\n\r");	
//		Uart0_Tx("F27",3);
		return HTTP_POST_FAILURE;
	}

	if (memcmp(HTTPtemp.NewPassWord, HTTPtemp.CfmPassWord, HTTPtemp.NewPassWordLen))
	{
		printd ("Change PassWord: Data not equal in %s to %s\n\r",HTTPtemp.OldPassWord , HTTPtemp.NewPassWord);
//		Uart0_Tx("F28",3);
		return HTTP_POST_FAILURE;
	}

//	if (Index == 0)
	{
		GCONFIG_SetAdmin(HTTPtemp.Buf[0], HTTPtemp.NewPassWord);
		printd ("Change PassWord: change ok! from: %s to %s\n\r", HTTPtemp.Buf[1], HTTPtemp.NewPassWord);
        GCONFIG_WriteConfigData();
	}
	return HTTP_POST_SUCCESS;

} /* End of HTTP_CheckNewPassword() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_CheckNewUsername()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T HTTP_CheckNewUsername(void)
{
	U8_T Temp;
	
	return HTTP_POST_SUCCESS;

	if (HTTPtemp.PostCnt != 2) 
//	 Uart0_Tx("F29",3);
	return HTTP_POST_FAILURE;
	
	if ((!HTTPtemp.NewUserNameLen) || (HTTPtemp.NewUserNameLen > MAX_AUTH_POST_VALUE_LEN))
	{
		printd ("Change UserName: New username length error!\n\r");
//		Uart0_Tx("F30",3);
		return HTTP_POST_FAILURE;
	}
	
	GCONFIG_GetAdmin(HTTPtemp.Buf[0], HTTPtemp.Buf[1], &Temp);
	GCONFIG_SetAdmin(HTTPtemp.NewUserName, HTTPtemp.Buf[1]);
	printd ("Change UserName: change ok! from: %s to %s\n\r", HTTPtemp.Buf[0], HTTPtemp.NewUserName);
    GCONFIG_WriteConfigData();		
	
	return HTTP_POST_SUCCESS;
} /* End of HTTP_CheckNewUsername() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_IpAddr2Ulong()
 * Purpose: Transfer a ip address string to ulong number. exp: 0xc0a80003
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T HTTP_IpAddr2Ulong(U8_T* pBuf, U8_T len)
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
} /* End of HTTP_IpAddr2Ulong() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_Str2Short()
 * Purpose: Transfer a string to ushort number.
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T HTTP_Str2Short(U8_T* pBuf, U8_T len)
{
	U32_T	value = 0;

	while (len--)
	{
		value *= 10;
 
		if ((*pBuf < 0x3a) && (*pBuf > 0x2f))
			value += (*pBuf - 0x30);
		else
			return 0xffff;

		pBuf++;
	}
	if (value & 0xFFFF0000) return 0xFFFF;
	return (U16_T)(value & 0xFFFF);

} /* End of HTTP_Str2Short() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: HTTP_Short2Str()
 * Purpose: Transfer a string to ushort number.
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T HTTP_Short2Str(U16_T port, U8_T* pBuf)
{
	U8_T*	point = (U8_T*)&port;
	U8_T	i, j, k, len = 0;
	U16_T	tmp;

	if (port > 9999)
		len = 5;
	else if (port > 999)
		len = 4;
	else if (port > 99)
		len = 3;
	else if (port > 9)
		len = 2;
	else
		len = 1;

	pBuf[len - 1] = (port % 10) + 0x30;
	for (i = 0; i < len - 1 ; i++)
	{
		j = (len - 1) - i;
		tmp = 1;
		for (k = 0; k < j; k++)
		{
			tmp = tmp * 10;
		}
		pBuf[i] = (port / tmp) + 0x30;
		port = port - ((pBuf[i] - 0x30) * tmp);
	}

	return len;

} /* End of HTTP_Short2Str() */
 

/* End of httpd.c */
