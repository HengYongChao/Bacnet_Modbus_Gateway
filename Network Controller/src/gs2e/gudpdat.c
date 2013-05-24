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
 * Module Name: gudpdat.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: gudpdat.c,v $
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "adapter.h"
#include "gudpdat.h"
#include "gs2e.h"
#include "gconfig.h"
#include "tcpip.h"
#include "mstimer.h"
#include "stoe.h"
#include "uart.h"
#include "hsuart.h"
#include "printd.h"
#include <string.h>

/* NAMING CONSTANT DECLARATIONS */
#define GUDPDAT_MAX_DATA_LEN		    1472 // maximun UDP payload length
#define GUDPDAT_MAX_CONNS				1 // maximun UDP connections, current version only supports 
                                          // one connection
#define GUDPDAT_NO_NEW_CONN				0xFF

#define GUDPDAT_STATE_FREE				0
#define GUDPDAT_STATE_CONNECTING        1
#define	GUDPDAT_STATE_WAIT				2
#define	GUDPDAT_STATE_CONNECTED			3

#define GUDPDAT_CLOSE_INDICATOR	    	0x30
#define GUDPDAT_CONNECT_INDICATOR   	0x31
#define GUDPDAT_DATA_INDICATOR   		0x32
#define GUDPDAT_FLOW_CONTROL_INDICATOR	0x33
#define GUDPDAT_MAIN_CONNECT_TIME       (3 * 60 * 100)   /* 3 minutes */

/* MACRO DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */
extern U8_T gtcpdat_TxBuf[];
extern U8_T uip_findarptable(U16_T* ipaddr);

/* LOCAL VARIABLES DECLARATIONS */
static GUDPDAT_CONN gudpdat_Conns[GUDPDAT_MAX_CONNS];
static U8_T gudpdat_InterAppId;
static U8_T gudpdat_ConnId;
static U16_T gudpdat_TxDatLen;
static U32_T gudpdat_TxWaitTime;
static U8_T *gudpdat_TxBuf = gtcpdat_TxBuf;
static U16_T gudpdat_Port;
static U16_T gudpdat_EthernetTxTimer;
static U8_T gudpdat_UdpClient;
static U8_T gudpdat_UdpAutoConnect;

#if GS2E_ENABLE_FLOW_CONTROL			
static U8_T gudpdat_FlowControlXonRx;
static U8_T gudpdat_FlowControlModemStatus, gudpdat_FlowControlModemCtrl;
#endif
static U8_T txBuf[6];

/* LOCAL SUBPROGRAM DECLARATIONS */
#if GS2E_ENABLE_FLOW_CONTROL			
static void gudpdat_HandleFlowControlPacket(U8_T XDATA* pData, U16_T length, U8_T id);
#endif
static U8_T gudpdat_CheckAllConnStatusIdle(void);

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPDAT_Task
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GUDPDAT_Task(void) 
{
	U8_T id = gudpdat_ConnId;
    U32_T elapse, time, dip;

	if (((gudpdat_UdpClient == TRUE) && GS2E_GetTaskState() != GS2E_STATE_UDP_DATA_PROCESS) ||  
	      gudpdat_UdpAutoConnect == TRUE
	   )
	{
		U8_T	i;
		U16_T   dport = GCONFIG_GetClientDestPort(); 

        dip = GCONFIG_GetClientDestIP();
        /* get destination ip */
        if (dip == 0)
            return;
        
		if (gudpdat_UdpAutoConnect == TRUE)
	    {
			gudpdat_UdpAutoConnect = FALSE;
			dip = GCONFIG_GetUdpAutoConnectClientIp();
			dport = GCONFIG_GetUdpAutoConnectClientPort();
			
			if (dip == 0) 
				return;
		}

		printd("Make a UDP connection with host ip:%bu %bu %bu %bu port:%u\n\r",
		        (U8_T) ((dip >> 24) & 0x000000FF), (U8_T) ((dip >> 16) & 0x000000FF), 
				(U8_T) ((dip >> 8) & 0x000000FF), (U8_T) (dip & 0x000000FF), (U16_T) dport);
		
		for (i = 0; i < GUDPDAT_MAX_CONNS; i++)
		{
			if (gudpdat_Conns[i].State == GUDPDAT_STATE_FREE)
			{
				gudpdat_ConnId = i;
				gudpdat_Conns[i].State = GUDPDAT_STATE_CONNECTING;
                gudpdat_Conns[i].Timer = SWTIMER_Tick();
                gudpdat_Conns[i].Ip = dip;
                gudpdat_Conns[i].Port = dport;
				gudpdat_Conns[i].UdpSocket = TCPIP_UdpNew(gudpdat_InterAppId,
														  gudpdat_ConnId,	
				                                          dip,
														  GTCPDAT_GetRandomPortNum(),
														  dport);
                /* Send ARP request to build IP/MAC entry in ARP table */
                if ((STOE_GetIPAddr() & STOE_GetSubnetMask()) != (dip & STOE_GetSubnetMask()))
                    dip = STOE_GetGateway();

                ETH_SendArpRequest(dip);
                ETH_SendArpRequest(dip);
                
				GS2E_SetTaskState(GS2E_STATE_UDP_DATA_PROCESS);
				return;
			}
		}
	}
    else if ((gudpdat_UdpClient == TRUE) && (gudpdat_Conns[id].State == GUDPDAT_STATE_CONNECTING))
    {
#if GS2E_ENABLE_FLOW_CONTROL
        dip = gudpdat_Conns[id].Ip;
        if ((STOE_GetIPAddr() & STOE_GetSubnetMask()) != (dip & STOE_GetSubnetMask()))
            dip = STOE_GetGateway();

        if (uip_findarptable((U16_T *)&dip) == 0xFF)
        {
            ETH_SendArpRequest(dip);
            return;
        }
        /* Send connected message */
        txBuf[0] = GUDPDAT_CONNECT_INDICATOR;
        txBuf[1] = 0;
        txBuf[2] = 0;
        TCPIP_UdpSend(gudpdat_Conns[id].UdpSocket, 0, 0, txBuf, 3);
#else
        gudpdat_Conns[id].State = GUDPDAT_STATE_CONNECTED;
#endif
    }
	else
	{
		if (gudpdat_Conns[id].State == GUDPDAT_STATE_CONNECTED)
		{
#if GS2E_ENABLE_FLOW_CONTROL
			
			U8_T  modemStatus, modemCtrl;
			
            /* Flow control header: type    length   payload */
            /*                      ------  -------  ------- */
            /*                      1 byte  2 bytes   any    */
            /* length = length of payload                    */
			modemStatus = HSUR_GetModemStatus(TRUE);
            modemCtrl = (HSUR_GetModemControl() & 0x3);

			if (gudpdat_FlowControlModemStatus != modemStatus || modemCtrl != gudpdat_FlowControlModemCtrl)
			{
				gudpdat_FlowControlModemStatus = modemStatus;
                gudpdat_FlowControlModemCtrl = modemCtrl;
				txBuf[0] = GUDPDAT_FLOW_CONTROL_INDICATOR;
                txBuf[1] = 0;
                txBuf[2] = 3;
				txBuf[3] = MODEM_STATUS_CHANGE;
				txBuf[4] = gudpdat_FlowControlModemStatus;
                txBuf[5] = gudpdat_FlowControlModemCtrl;
				TCPIP_UdpSend(gudpdat_Conns[id].UdpSocket, 0, 0, txBuf, 6);
			}

			if (gudpdat_TxDatLen == 0)
			{
				gudpdat_TxBuf[gudpdat_TxDatLen++] = GUDPDAT_DATA_INDICATOR; // UDP data packet indicator
                gudpdat_TxDatLen += 2;
			}

			if (gudpdat_FlowControlXonRx == TRUE)
			{
#endif
				U8_T dat;

				while (HSUR_GetRxBufCount() > 0)
				{
					if (gudpdat_TxDatLen >= GUDPDAT_MAX_DATA_LEN)
						break;
										
					if (HSUR_GetByteNb(&dat) == TRUE)
                    {
						gudpdat_TxBuf[gudpdat_TxDatLen++] = dat;
                        gudpdat_Conns[id].UrRxBytes++;
                    }
				}

				if (gudpdat_TxDatLen >= GUDPDAT_MAX_DATA_LEN)
				{
#if GS2E_ENABLE_FLOW_CONTROL
                    /* Fill in the length of payload */
                    gudpdat_TxBuf[1] = (U8_T)((GUDPDAT_MAX_DATA_LEN-3) >> 8);
                    gudpdat_TxBuf[2] = (U8_T)((GUDPDAT_MAX_DATA_LEN-3) & 0x00FF);
#endif
					TCPIP_UdpSend(gudpdat_Conns[id].UdpSocket, 0, 0, gudpdat_TxBuf, GUDPDAT_MAX_DATA_LEN);
					
					gudpdat_TxDatLen = 0;				
					gudpdat_TxWaitTime = 0;
				}
#if GS2E_ENABLE_FLOW_CONTROL
				else if (gudpdat_TxDatLen > 3) // both client and server have an indicator
#else
				else if (gudpdat_TxDatLen > 0)
#endif
				{
					time = SWTIMER_Tick();
		
					if (gudpdat_TxWaitTime == 0)
					{
						gudpdat_TxWaitTime = time;
					}
					else
					{
	 					if (time >= gudpdat_TxWaitTime)
							elapse = time - gudpdat_TxWaitTime;
						else
							elapse = (0xFFFFFFFF - gudpdat_TxWaitTime) + time;
	
						if ((elapse * SWTIMER_INTERVAL) >= gudpdat_EthernetTxTimer)
						{
#if GS2E_ENABLE_FLOW_CONTROL
                            /* Fill in the length of payload */
                            gudpdat_TxBuf[1] = (U8_T)((gudpdat_TxDatLen-3) >> 8);
                            gudpdat_TxBuf[2] = (U8_T)((gudpdat_TxDatLen-3) & 0x00FF);
#endif
							TCPIP_UdpSend(gudpdat_Conns[id].UdpSocket, 0, 0, gudpdat_TxBuf, gudpdat_TxDatLen);
							gudpdat_TxDatLen = 0;
							gudpdat_TxWaitTime = 0;	
						}
					}
				}
#if GS2E_ENABLE_FLOW_CONTROL			
		 	}
#endif
            { /* Maintain the connection: send ARP request each GUDPDAT_MAIN_CONNECT_TIME */
                time = SWTIMER_Tick();

                if (time >= gudpdat_Conns[id].Timer)
                    elapse = time - gudpdat_Conns[id].Timer;
                else
                    elapse = (0xFFFFFFFF - gudpdat_Conns[id].Timer) + time;

                if (elapse >= GUDPDAT_MAIN_CONNECT_TIME)
                {
                    if ((STOE_GetIPAddr() & STOE_GetSubnetMask()) != (gudpdat_Conns[id].Ip & STOE_GetSubnetMask()))
                        ETH_SendArpRequest(STOE_GetGateway());
                    else
                        ETH_SendArpRequest(gudpdat_Conns[id].Ip);
                    gudpdat_Conns[id].Timer = time;
                }
            }
		}
	}	
} /* End of GUDPDAT_Task() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPDAT_Init()
 * Purpose: Initialization
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GUDPDAT_Init(U16_T localPort)
{
	U8_T	i;

	gudpdat_UdpClient = FALSE;
	gudpdat_UdpAutoConnect = FALSE;

	for (i = 0; i < GUDPDAT_MAX_CONNS; i++)
    {
		gudpdat_Conns[i].State = GUDPDAT_STATE_FREE;
        gudpdat_Conns[i].UrRxBytes = 0;
        gudpdat_Conns[i].UrTxBytes = 0;
    }

	gudpdat_InterAppId = TCPIP_Bind(GUDPDAT_NewConn, GUDPDAT_Event, GUDPDAT_Receive);
	
	/* unicast packet */
	gudpdat_Port = localPort;

	if ((GCONFIG_GetNetwork() & GCONFIG_NETWORK_CLIENT) != GCONFIG_NETWORK_CLIENT)
	{
		TCPIP_UdpListen(localPort, gudpdat_InterAppId); 		
		printd("UDP data server init ok.\n\r");		
		gudpdat_UdpAutoConnect = GCONFIG_EnableUdpAutoConnectAfterReboot();
	}
	else
	{
		gudpdat_UdpClient = TRUE;	
		printd("UDP data client init ok.\n\r");			
	}

	gudpdat_TxDatLen = 0;
	gudpdat_TxWaitTime = 0;	
	gudpdat_EthernetTxTimer = GCONFIG_GetEthernetTxTimer();

#if GS2E_ENABLE_FLOW_CONTROL			
	gudpdat_FlowControlXonRx = TRUE;
	gudpdat_FlowControlModemStatus = HSUR_GetModemStatus(TRUE);
    gudpdat_FlowControlModemCtrl = (HSUR_GetModemControl() & 0x3);
#endif
} /* End of GUDPDAT_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPDAT_NewConn
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GUDPDAT_NewConn(U32_T XDATA* pip, U16_T remotePort, U8_T socket)
{
	U8_T	i;

	if (GCONFIG_EnableUdpAutoConnectAfterReboot() == TRUE)
	{
		GCONFIG_SetUdpAutoConnectClientIp(*pip);
		GCONFIG_SetUdpAutoConnectClientPort(remotePort);
		GCONFIG_WriteConfigData();
	}

#if (GUDPDAT_MAX_CONNS == 1)
	if (gudpdat_Conns[0].State == GUDPDAT_STATE_CONNECTED)
	{
		gudpdat_Conns[0].State = GUDPDAT_STATE_FREE;
		TCPIP_UdpClose(gudpdat_Conns[0].UdpSocket);
	}
#endif

	for (i = 0; i < GUDPDAT_MAX_CONNS; i++)
	{
		if (gudpdat_Conns[i].State == GUDPDAT_STATE_FREE)
		{
#if GS2E_ENABLE_FLOW_CONTROL
			if (gudpdat_UdpAutoConnect == TRUE)
			{
				gudpdat_UdpAutoConnect = FALSE;
				GS2E_SetTaskState(GS2E_STATE_UDP_DATA_PROCESS);			
				gudpdat_Conns[i].State = GUDPDAT_STATE_CONNECTED;
			}
			else
			{
				gudpdat_Conns[i].State = GUDPDAT_STATE_WAIT;
			}
#else
			GS2E_SetTaskState(GS2E_STATE_UDP_DATA_PROCESS);			
			gudpdat_Conns[i].State = GUDPDAT_STATE_CONNECTED;

			if (gudpdat_UdpAutoConnect == TRUE)
				gudpdat_UdpAutoConnect = FALSE;
#endif
			gudpdat_Conns[i].UdpSocket = socket;
            gudpdat_Conns[i].Timer = SWTIMER_Tick();
            gudpdat_Conns[i].Ip = *pip;
            gudpdat_Conns[i].Port = remotePort;
			gudpdat_ConnId = i;
			printd("New UDP connection: id=%bu, remotePort=%d, socket=%bu\n\r", i, remotePort, socket);

			return i;
		}
	}
	
	return GUDPDAT_NO_NEW_CONN;

} /* End of GUDPDAT_NewConn() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPDAT_Event
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GUDPDAT_Event(U8_T id, U8_T event)
{
	if (event == TCPIP_CONNECT_ACTIVE)
	{
#if GS2E_ENABLE_FLOW_CONTROL
		if (gudpdat_Conns[id].State == GUDPDAT_STATE_WAIT)
		{
			gudpdat_Conns[id].State = GUDPDAT_STATE_CONNECTED;
			GS2E_SetTaskState(GS2E_STATE_UDP_DATA_PROCESS);
		}
#endif
	}
	else if (event == TCPIP_CONNECT_CANCEL)
	{
#if GS2E_ENABLE_FLOW_CONTROL
		if ((GCONFIG_GetNetwork() & GCONFIG_NETWORK_CLIENT) == GCONFIG_NETWORK_CLIENT)
		{
			gudpdat_TxBuf[0] = GUDPDAT_CLOSE_INDICATOR; // close indication
            gudpdat_TxBuf[1] = 0;
            gudpdat_TxBuf[2] = 0;
			TCPIP_UdpSend(gudpdat_Conns[id].UdpSocket, 0, 0, gudpdat_TxBuf, 3);
		}
#endif
		gudpdat_Conns[id].State = GUDPDAT_STATE_FREE;
		GS2E_SetTaskState(GS2E_STATE_IDLE);
		printd("TCPIP_UdpClose(id=%bu, socket=%bu)\n\r", id, gudpdat_Conns[id].UdpSocket);
		TCPIP_UdpClose(gudpdat_Conns[id].UdpSocket);
	}

} /* End of GUDPDAT_Event() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPDAT_Receive
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GUDPDAT_Receive(U8_T XDATA* pData, U16_T length, U8_T id)
{
	U16_T i;

#if GS2E_ENABLE_FLOW_CONTROL
MoreUdpData:
	if (length > 3 && *pData == GUDPDAT_DATA_INDICATOR)
	{
        U16_T dataLen = (*(pData+1) << 8) + *(pData+2) + 3;

		if (gudpdat_Conns[id].State != GUDPDAT_STATE_CONNECTED)
		{
			gudpdat_Conns[id].State = GUDPDAT_STATE_CONNECTED;
			GS2E_SetTaskState(GS2E_STATE_UDP_DATA_PROCESS);
			gudpdat_TxDatLen = 0;
			gudpdat_TxWaitTime = 0;			
		}
        
        if (dataLen > length) 
            dataLen = length;

		for (i = 3; i < dataLen; i++) // 1st byte of data the data indicator 
		{
            gudpdat_Conns[id].UrTxBytes++;
			if (HSUR_PutChar((S8_T) *(pData + i)) == FALSE)
			{
				// UART-2 buffer reachs to high water mark!
				// How to handle this condition is up to the application of upper-layer module.
			}
		}
        length -= dataLen;
        if (length > 0)
        {
            /* point to the next packet header */
            pData += dataLen;
            goto MoreUdpData;
        }
	}
	else if (length <= 6 && *pData == GUDPDAT_FLOW_CONTROL_INDICATOR)
	{
		gudpdat_HandleFlowControlPacket(pData, length, id);
	}
	else if (length == 3)
    {
        if (*pData == GUDPDAT_CONNECT_INDICATOR)
        {
            gudpdat_Conns[id].State = GUDPDAT_STATE_CONNECTED;
            GS2E_SetTaskState(GS2E_STATE_UDP_DATA_PROCESS);
            gudpdat_TxDatLen = 0;
            gudpdat_TxWaitTime = 0;			
        }
        else if (*pData == GUDPDAT_CLOSE_INDICATOR)
        {
            gudpdat_Conns[id].State = GUDPDAT_STATE_FREE;
            GS2E_SetTaskState(GS2E_STATE_IDLE);	
            printd("TCPIP_UdpClose(id=%bu, socket=%bu)\n\r", id, gudpdat_Conns[id].UdpSocket);
            TCPIP_UdpClose(gudpdat_Conns[id].UdpSocket);
        }
    }
#else
	id = id; // to avoid warming message

	for (i = 0; i < length; i++) 
	{
        gudpdat_Conns[id].UrTxBytes++;
		HSUR_PutChar((S8_T) *(pData + i));
	}		
#endif
} /* End of GUDPDAT_Receive() */

#if GS2E_ENABLE_FLOW_CONTROL			
/*
 * ----------------------------------------------------------------------------
 * Function Name: gudpdat_HandleFlowControlPacket
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void gudpdat_HandleFlowControlPacket(U8_T XDATA* pData, U16_T length, U8_T id)
{
	U8_T command = *(pData + 3);
	U8_T dat1;
	U8_T dat2;

	if (length >= 5)
	{
		dat1 = *(pData + 4);

		if (length == 6)
			dat2 = *(pData + 5);
	}

	switch (command)
	{
		case IOCTL_SERIAL_GET_DTRRTS: // 0x01
			txBuf[0] = GUDPDAT_FLOW_CONTROL_INDICATOR;
            txBuf[1] = 0;
            txBuf[2] = 2;
			txBuf[3] = IOCTL_SERIAL_GET_DTRRTS_REPLY; // 0xA1
			txBuf[4] = HSUR_GetModemControl();
			TCPIP_UdpSend(gudpdat_Conns[id].UdpSocket, 0, 0, txBuf, 5);
			break;
		case IOCTL_SERIAL_GET_MODEM_CONTROL: // 0x02
			txBuf[0] = GUDPDAT_FLOW_CONTROL_INDICATOR;
            txBuf[1] = 0;
            txBuf[2] = 2;
			txBuf[3] = IOCTL_SERIAL_GET_MODEM_CONTROL_REPLY; // 0xA2
			txBuf[4] = HSUR_GetModemControl();
			TCPIP_UdpSend(gudpdat_Conns[id].UdpSocket, 0, 0, txBuf, 5);
			break;
		case IOCTL_SERIAL_GET_MODEM_STATUS: // 0x03
			txBuf[0] = GUDPDAT_FLOW_CONTROL_INDICATOR;
            txBuf[1] = 0;
            txBuf[2] = 2;
			txBuf[3] = IOCTL_SERIAL_GET_MODEM_STATUS_REPLY; // 0xA3
			txBuf[4] = HSUR_GetModemStatus(TRUE);
			TCPIP_UdpSend(gudpdat_Conns[id].UdpSocket, 0, 0, txBuf, 5);
			break;
		case IOCTL_SERIAL_CLR_DTR: // 0x11
			HSUR_ClearDTR();
			break;
		case IOCTL_SERIAL_CLR_RTS: // 0x12
			HSUR_ClearRTS();		
			break;
		case IOCTL_SERIAL_SET_DTR: // 0x13
			HSUR_SetDTR();
			break;
		case IOCTL_SERIAL_SET_RTS: // 0x14
			HSUR_SetRTS();
			break;
		case IOCTL_SERIAL_SET_BAUD_RATE: // 0x15			
            HSUR_SetupPort(GCONFIG_GetBaudRate(dat1), dat2);
			break;
		case IOCTL_SERIAL_SET_BREAK_OFF: // 0x16
			dat1 = HSUR_GetLineControl();
			HSUR_SetLineControl(dat1 & 0xBF); // bit 6 - break control bit (1:on, 0:off)
			break;
		case IOCTL_SERIAL_SET_BREAK_ON: // 0x17
			dat1 = HSUR_GetLineControl();
			HSUR_SetLineControl(dat1 | 0x40); // bit 6 - break control bit (1:on, 0:off)
			break;
		case IOCTL_SERIAL_SET_FIFO_CONTROL: // 0x18
			HSUR_SetFifoControl(dat1);
			break;
		case IOCTL_SERIAL_SET_LINE_CONTROL: // 0x19
			HSUR_SetLineControl(dat1);
			break;
		case IOCTL_SERIAL_SET_MODEM_CONTROL: // 0x1A
			HSUR_SetModemControl(dat1);
			break;
		case IOCTL_SERIAL_SET_XOFF: // 0x21
			gudpdat_FlowControlXonRx = FALSE;
			break;
		case IOCTL_SERIAL_SET_XON: // 0x22
			gudpdat_FlowControlXonRx = TRUE;
			break;
        case IOCTL_SERIAL_SET_HANDFLOW:
            switch (dat1)
            {
                case SERIAL_HANDFLOW_NONE:
                    dat1 = UR2_FLOW_CTRL_NO;
                    break;
                case SERIAL_HANDFLOW_HW:
                    dat1 = UR2_FLOW_CTRL_HW;
                    break;
                case SERIAL_HANDFLOW_XON_XOFF:
                    dat1 = UR2_FLOW_CTRL_X;
                    break;
                default:
                    return;
            }
            HSUR_SetFlowControl(dat1);
			break;
		case IOCTL_SERIAL_XOFF_COUNTER: // 0x23
			// Not support
			break;

		default:
			printd("Unknown flow control command!\n\r");
			break;
	}
} /* End of gudpdat_HandleFlowControlPacket() */
#endif

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPDAT_GetTxBytes
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GUDPDAT_GetTxBytes(U8_T id)
{
    if (id < GUDPDAT_MAX_CONNS)
        return gudpdat_Conns[id].UrTxBytes;

    return 0;
} /* End of GUDPDAT_GetTxBytes() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPDAT_GetRxBytes
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GUDPDAT_GetRxBytes(U8_T id)
{
    if (id < GUDPDAT_MAX_CONNS)
        return gudpdat_Conns[id].UrRxBytes;

    return 0;
} /* End of GUDPDAT_GetRxBytes() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: gudpdat_CheckAllConnStatusIdle
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static U8_T gudpdat_CheckAllConnStatusIdle(void)
{
    U8_T id;

    for (id = 0; id < GUDPDAT_MAX_CONNS; id++)
    {
        if (gudpdat_Conns[id].State != GUDPDAT_STATE_FREE)
            return 0;
    }

    return 1;
} /* End of gudpdat_CheckAllConnStatusIdle() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GUDPDAT_ConnClose
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GUDPDAT_ConnClose(U32_T remoteIp, U16_T port)
{
    U8_T id;

    for (id = 0; id < GUDPDAT_MAX_CONNS; id++)
    {
        if (gudpdat_Conns[id].State == GUDPDAT_STATE_CONNECTED)
        {
            if (gudpdat_Conns[id].Ip == remoteIp && gudpdat_Conns[id].Port == port)
            {
                gudpdat_Conns[id].State = GUDPDAT_STATE_FREE;
                TCPIP_UdpClose(gudpdat_Conns[id].UdpSocket);
                if (gudpdat_CheckAllConnStatusIdle())
                    GS2E_SetTaskState(GS2E_STATE_IDLE);
            }
        }
    }

} /* End of GUDPDAT_ConnClose() */

/* End of gudpdat.c */
