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
 * Module Name: dnsc.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: dnsc.c,v $
 * Revision 1.5  2006/05/23 11:04:18  robin6633
 * 1.Add a condition for printd.
 *
 * Revision 1.4  2006/05/23 05:21:53  robin6633
 * 1.Add define condition.
 *
 * Revision 1.3  2006/05/23 01:53:31  robin6633
 * 1.Removed debug information from UART2.
 *
 * Revision 1.2  2006/05/22 13:22:33  robin6633
 * 1.Initial the dns server ip from data base.
 *
 * Revision 1.1  2006/05/22 05:44:27  robin6633
 * no message
 *
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "main.h"

#if (INCLUDE_DNS_CLIENT)
#include "dnsc.h"
#include "dnsctab.h"
#include "tcpip.h"
#include "mstimer.h"
#include "uart.h"
#include "printd.h"

#include <stdio.h>
#include <string.h>

/* NAMING CONSTANT DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static U8_T dnsc_InterAppId;
static U8_T dnsc_State;
static U32_T dnsc_Ip;
static U32_T dnsc_ServerIp = 0xc0a800c8;
static U8_T dnsc_UdpSocket;

/* LOCAL SUBPROGRAM DECLARATIONS */
void dnsc_Send(U8_T InterUdpId, char *pName, U32_T dnsIp);
U8_T dnsc_PrepareQueryPacket(S8_T *pName, U8_T *pBuf);
U32_T dnsc_ParseResponsePacket(U8_T *pBuf, U16_T bufLen);

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSC_Init()
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void DNSC_Init(void)
{
	dnsc_InterAppId = TCPIP_Bind(NULL, DNSC_Event, DNSC_Receive);
	dnsc_State = DNSC_STATE_FREE;
	dnsc_Ip = 0x00000000;
} /* End of DNSC_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSC_Event
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void DNSC_Event(U8_T id, U8_T event)
{
	if (id)
		return;

	if (event == TCPIP_CONNECT_CANCEL)
		dnsc_State = DNSC_STATE_FREE;
	else
	{
#if (UART0_ENABLE)
		PRINTD(DEBUG_MSG,  ("Other event\n\r"));
#endif
	}

} /* End of DNSC_Event() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSC_Receive
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void DNSC_Receive(U8_T XDATA* pData, U16_T length, U8_T id)
{
	if ((dnsc_State != DNSC_STATE_WAIT_RESPONSE) && id)
		return;

	dnsc_Ip = dnsc_ParseResponsePacket(pData, length);
	dnsc_State = DNSC_STATE_RESPONSED;

} /* End of DNSC_Receive() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSC_Query
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T DNSC_Query(S8_T *pName)
{
	if ((dnsc_UdpSocket = TCPIP_UdpNew(dnsc_InterAppId, 0, dnsc_ServerIp, 0,
		DNS_SERVER_PORT)) == TCPIP_NO_NEW_CONN)
	{
#if (UART0_ENABLE)
		PRINTD(DEBUG_MSG,  ("DNSC Allocate Udp Socket fail.\n\r"));
#endif
		return DNSC_STATE_FREE;
	}

	dnsc_Send(dnsc_UdpSocket, pName, dnsc_ServerIp);

	return dnsc_State;

} /* End of DNSC_Query() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSC_GetState
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T DNSC_GetState(void)
{
	return dnsc_State;
} /* End of DNSC_Receive() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSC_GetIp
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T DNSC_GetIp(void)
{
	dnsc_State = DNSC_STATE_FREE;

	return dnsc_Ip;
} /* End of DNSC_Receive() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: dnsc_Send
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void dnsc_Send(U8_T InterUdpId, S8_T *pName, U32_T dnsIp)
{
	U8_T pkt[512];
	U8_T len;
	U8_T i;
	char strIp[16] = {0};

	if(strlen(pName) <= 255)
	{	
		len = dnsc_PrepareQueryPacket(pName, &pkt[0]);
	
		i = sprintf(strIp, "%d.", ((dnsIp >> 24) & 0x000000FF));
		i += sprintf(strIp + i, "%d.", ((dnsIp >> 16) & 0x000000FF));
		i += sprintf(strIp + i, "%d.", ((dnsIp >> 8) & 0x000000FF));
		sprintf(strIp + i, "%d", (dnsIp & 0x000000FF));
	
		TCPIP_UdpSend(InterUdpId, 0, 0, pkt, len);

		dnsc_State = DNSC_STATE_WAIT_RESPONSE;
	}
	else
	{
#if (UART0_ENABLE)
		PRINTD(DEBUG_MSG,  ("Host name length is greater than 255 bytes.\n\r"));
#endif
		dnsc_State = DNSC_STATE_FREE;
	}
} /* End of dnsc_Send() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: dnsc_PrepareQueryPacket
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T dnsc_PrepareQueryPacket(S8_T *pName, U8_T *pBuf)
{
	U8_T len;
	U16_T i, j, k;
	U16_T nameLen = strlen(pName); 
	DnsHeader dnsh;
	DnsQuestion dnsq;

	// Prepare DNS header
	dnsh.id = htons(0xABCD);
	dnsh.q_op4_aa_tc_rd = 0x01;  
	dnsh.ra_z_ad_cd_rc4 = 0x00;
	dnsh.total_questions = htons(0x0001);
	dnsh.total_answers = htons(0x0000);
	dnsh.total_auth_rr = htons(0x0000);
	dnsh.total_extra_rr = htons(0x0000);

	// Prepare Question field
	dnsq.type = htons(DNS_TYPE_A);
	dnsq.class1 = htons(DNS_CLASS_IN);

	memcpy(pBuf, &dnsh, sizeof(dnsh));
	len = sizeof(dnsh);
	
	j = 0;

	for(i = 0; i <= nameLen; i++) 
	{
		if (*(pName + i) == '.' || i == nameLen)
		{
			*(pBuf + len++) = i-j;

			for (k = j; k < i; k++)
				*(pBuf + len++) = *(pName + k);

			j = i+1;
		}
	}

	*(pBuf + len++) = 0;

	memcpy((pBuf + len), &dnsq, sizeof(dnsq));
	len += sizeof(dnsq);

	return len;
} /* End of dnsc_PrepareQueryPacket() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: dnsc_ParseResponsePacket
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T dnsc_ParseResponsePacket(U8_T *pBuf, U16_T bufLen)
{	
	U16_T len;
	U16_T i;
	U32_T ip = 0x00000000;
	DnsHeader dnsh;
	DnsAnswer dnsa;

	if (bufLen < sizeof(dnsh))
	{
#if (UART0_ENABLE)
		PRINTD(DEBUG_MSG,  ("Buffer length is too small.\n\r"));
#endif		
		return ip;
	}

	memcpy(&dnsh, pBuf, sizeof(dnsh));
	len = sizeof(dnsh);
	
	if (((dnsh.ra_z_ad_cd_rc4) & 0x0F) == 0) // No error
	{
		if (dnsh.total_questions > 0)
		{
			for (i = 0; i < dnsh.total_questions; i++)
			{
				// Handle QDCOUNT field at here

				while (*(pBuf + len++) != 0)
				{
					// Handle QNAME field at here
					// ...					
				}
			
				// Handle QTYPE and QCLASS fields at here
				// ...
				len += sizeof(DnsQuestion);
			}
		}

		if (dnsh.total_answers > 0)
		{
			for (i = 0; i < dnsh.total_answers; i++)
			{
				// Handle ANCOUNT field at here

				// Currently only handles first valid answer
				memcpy(&dnsa, (pBuf + len), sizeof(dnsa));

				if ((dnsa.type == DNS_TYPE_A) && (dnsa.class1 == DNS_CLASS_IN))
				{						
					if (dnsa.len == 4)
					{									
						ip = ((((U32_T)dnsa.ip_addr[0] << 16) & 0xFFFF0000) + 
						          ((U32_T)dnsa.ip_addr[1] & 0x0000FFFF));
					}
				}
				else
				{
					// Shift to offset of next answer
					// Header length (Bytes)
					// Name:2  Type:2  Class:2  TTL:4  Data Len:2  Data:variable     
					len += 10; // Length of Name + Type + Class + TTL
					len += ((U16_T)((*(pBuf + len) << 8) & 0xFF00) + (U16_T)*(pBuf + len + 1) + 2);						
				}
			}
		}

		if (dnsh.total_answers > 0)
		{
			// Handle NSCOUNT field at here
			// ...
		}

		if (dnsh.total_answers > 0)
		{
			// Handle ARCOUNT field at here
			// ...
		}
	}
	
	return ip;
} /* End of dnsc_ParseResponsePacket() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSC_Command
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void DNSC_Command(U8_T* pData, U8_T length)
{
	U8_T	state;
	U32_T	ip;

	if (dnsc_State != DNSC_STATE_FREE)
	{
#if (UART0_ENABLE)
		PRINTD(DEBUG_MSG,  ("DNSC Connection is busy.\n\r"));
#endif
		return;
	}

	pData[length] = 0;

	state = DNSCTAB_Query(pData, &ip);	/* include DNS table */
//	state = DNSC_Query(pData);	/* not include DNS table */

} /* End of DNSC_Command */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSC_SetDnsIP
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void DNSC_SetDnsIP(U32_T ip)
{
	dnsc_ServerIp = ip;	
} /* End of DNSC_SetDnsIP() */



#endif /* INCLUDE_DNS_CLIENT */

/* End of dnsc.c */
