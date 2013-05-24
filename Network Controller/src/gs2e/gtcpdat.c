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
 * Module Name: gtcpdat.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: gtcpdat.c,v $
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "adapter.h"
#include "gtcpdat.h"
#include "gs2e.h"
#include "gconfig.h"
#include "tcpip.h"
#include "mstimer.h"
#include "stoe.h"
#include "uart.h"
#include "hsuart.h"
#include "string.h"

/* NAMING CONSTANT DECLARATIONS */
#define GTCPDAT_MAX_TCP_DATA_LEN  		1344 //1024
#define GTCPDAT_TX_BUF_SIZE       	(GTCPDAT_MAX_TCP_DATA_LEN * 2)

#define GTCPDAT_MAX_CONNS				1
#define GTCPDAT_NO_NEW_CONN				0xFF

#define GTCPDAT_STATE_FREE				0
#define	GTCPDAT_STATE_WAIT				1
#define	GTCPDAT_STATE_CONNECTED			2

#define GTCPDAT_DATA_INDICATOR   		0x32
#define GTCPDAT_FLOW_CONTROL_INDICATOR	0x33

#define GTCPDAT_MAIN_CONNECT_TIME       (3 * 60 * 100)   /* 3 minutes */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static GTCPDAT_CONN gtcpdat_Conns[GTCPDAT_MAX_CONNS];
static U8_T gtcpdat_InterAppId;
static U8_T gtcpdat_LastTxPktAck; // 1: complete 0: not complete
static U16_T gtcpdat_TxDatLen;
static U16_T gtcpdat_TxSentLen;
static U32_T gtcpdat_TxWaitTime;
U8_T gtcpdat_TxBuf[GTCPDAT_TX_BUF_SIZE];
static U16_T gtcpdat_EthernetTxTimer;
static U8_T gtcpdat_TcpClient;
static U32_T elapse, time;

#if GS2E_ENABLE_FLOW_CONTROL			
static U8_T gtcpdat_FlowControlXonRx;
static U8_T gtcpdat_FlowControlModemStatus, gtcpdat_FlowControlModemCtrl;
static U8_T txBuf[6];
#endif

/* LOCAL SUBPROGRAM DECLARATIONS */
#if GS2E_ENABLE_FLOW_CONTROL			
static void gtcpdat_HandleFlowControlPacket(U8_T XDATA* pData, U16_T length, U8_T id);
#endif

static void gtcpdat_MaintainConnection(U8_T id);
static void gtcpdat_GetDataFromUr(U8_T id);
static void gtcpdat_SendData(U8_T);
static U8_T gtcpdat_CheckAllConnStatusIdle(void);

/*
 * ----------------------------------------------------------------------------
 * Function Name: GTCPDAT_GetRandomPortNum
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U16_T GTCPDAT_GetRandomPortNum(void)
{
    U16_T port;

    port = (U16_T)SWTIMER_Tick();

    if (port < 5000)
        port += 5000;

    return port;
} /* End of GTCPDAT_GetRandomPortNum() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GTCPDAT_Task
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GTCPDAT_Task(void)
{
    U8_T i;

    for (i = 0; i < GTCPDAT_MAX_CONNS; i++)
    {
        switch (gtcpdat_Conns[i].State)
        {
            case GTCPDAT_STATE_FREE:
                if (gtcpdat_TcpClient == 1)
                {
                    gtcpdat_Conns[i].Ip = GCONFIG_GetClientDestIP();
                    /* get destination ip */
                    if (gtcpdat_Conns[i].Ip == 0)
                        break;
                    gtcpdat_Conns[i].State = GTCPDAT_STATE_WAIT;
                    gtcpdat_Conns[i].Timer = SWTIMER_Tick();
                    gtcpdat_Conns[i].Port = GCONFIG_GetClientDestPort();
                    gtcpdat_Conns[i].TcpSocket = TCPIP_TcpNew(gtcpdat_InterAppId,
                                                              i,
                                                              gtcpdat_Conns[i].Ip,
                                                              GTCPDAT_GetRandomPortNum(),
                                                              gtcpdat_Conns[i].Port);

                    TCPIP_TcpConnect(gtcpdat_Conns[i].TcpSocket);
                    GS2E_SetTaskState(GS2E_STATE_TCP_DATA_PROCESS);

                    printd("Make a TCP connection with host ip %bu %bu %bu %bu at port %u\n\r",
                          (U8_T) ((gtcpdat_Conns[i].Ip >> 24) & 0x000000FF), (U8_T) ((gtcpdat_Conns[i].Ip >> 16) & 0x000000FF), 
                          (U8_T) ((gtcpdat_Conns[i].Ip >> 8) & 0x000000FF), (U8_T) (gtcpdat_Conns[i].Ip & 0x000000FF),
                          gtcpdat_Conns[i].Port);
                }
                break;
            case GTCPDAT_STATE_CONNECTED:
                {
#if GS2E_ENABLE_FLOW_CONTROL

                U8_T  modemStatus, modemCtrl;

                /* Flow control header: type    length   payload */
                /*                      ------  -------  ------- */
                /*                      1 byte  2 bytes   any    */
                /* length = length of payload                    */
                if (gtcpdat_LastTxPktAck == 1)
                {
                    modemStatus = HSUR_GetModemStatus(TRUE);
                    modemCtrl = (HSUR_GetModemControl() & 0x3);

                    if (gtcpdat_FlowControlModemStatus != modemStatus || modemCtrl != gtcpdat_FlowControlModemCtrl)
                    { 
                       gtcpdat_FlowControlModemStatus = modemStatus;
                       gtcpdat_FlowControlModemCtrl = modemCtrl;
                       txBuf[0] = GTCPDAT_FLOW_CONTROL_INDICATOR;
                       txBuf[1] = 0;
                       txBuf[2] = 3;
                       txBuf[3] = MODEM_STATUS_CHANGE;
                       txBuf[4] = gtcpdat_FlowControlModemStatus;
                       txBuf[5] = gtcpdat_FlowControlModemCtrl;
                       gtcpdat_LastTxPktAck = 0;
                       TCPIP_TcpSend(gtcpdat_Conns[i].TcpSocket, txBuf, 6, TCPIP_SEND_NOT_FINAL);
                    }
                }

                if (gtcpdat_TxDatLen == 0)
                {
                    gtcpdat_TxBuf[gtcpdat_TxDatLen++] = GTCPDAT_DATA_INDICATOR; // TCP data packet indicator
                    gtcpdat_TxDatLen += 2; /* reserved for length */
                }

                if (gtcpdat_FlowControlXonRx == TRUE)
                {
#endif
	                gtcpdat_GetDataFromUr(i);
                    gtcpdat_SendData(i);
#if GS2E_ENABLE_FLOW_CONTROL
                } // gudpdat_FlowControlXonRx
#endif
                gtcpdat_MaintainConnection(i);
                }
                break;
            default:
                break;
        }
    }
} /* End of GTCPDAT_Task() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: gtcpdat_MaintainConnection()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void gtcpdat_MaintainConnection(U8_T id)
{
    time = SWTIMER_Tick();

    if (time >= gtcpdat_Conns[id].Timer)
        elapse = time - gtcpdat_Conns[id].Timer;
    else
        elapse = (0xFFFFFFFF - gtcpdat_Conns[id].Timer) + time;

    if (elapse >= GTCPDAT_MAIN_CONNECT_TIME)
    {
        if ((STOE_GetIPAddr() & STOE_GetSubnetMask()) != (gtcpdat_Conns[id].Ip & STOE_GetSubnetMask()))
            ETH_SendArpRequest(STOE_GetGateway());
        else
            ETH_SendArpRequest(gtcpdat_Conns[id].Ip);
        gtcpdat_Conns[id].Timer = time;
    }
} /* End of gtcpdat_MaintainConnection() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: gtcpdat_SendData()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void gtcpdat_SendData(U8_T id)
{
#if GS2E_ENABLE_FLOW_CONTROL
    if (gtcpdat_LastTxPktAck == 1 && gtcpdat_TxDatLen > 3)
#else
    if (gtcpdat_LastTxPktAck == 1 && gtcpdat_TxDatLen > 0)
#endif
    {
        if (gtcpdat_TxDatLen >= GTCPDAT_MAX_TCP_DATA_LEN)
        {
            gtcpdat_LastTxPktAck = 0;
#if GS2E_ENABLE_FLOW_CONTROL
            /* Fill in the length of payload */
            gtcpdat_TxBuf[1] = (U8_T)((GTCPDAT_MAX_TCP_DATA_LEN-3) >> 8);
            gtcpdat_TxBuf[2] = (U8_T)((GTCPDAT_MAX_TCP_DATA_LEN-3) & 0x00FF);
            gtcpdat_TxSentLen = GTCPDAT_MAX_TCP_DATA_LEN;
#else
            gtcpdat_TxSentLen = gtcpdat_TxDatLen;
#endif
            TCPIP_TcpSend(gtcpdat_Conns[id].TcpSocket, &gtcpdat_TxBuf[0], gtcpdat_TxSentLen, TCPIP_SEND_NOT_FINAL);   	
            gtcpdat_TxWaitTime = 0;
        }
        else
        {
            time = SWTIMER_Tick();

            if (gtcpdat_TxWaitTime == 0)
            {
                gtcpdat_TxWaitTime = time;
            }
            else
            {
                 if (time >= gtcpdat_TxWaitTime)
                    elapse = time - gtcpdat_TxWaitTime;
                else
                    elapse = (0xFFFFFFFF - gtcpdat_TxWaitTime) + time;

                if (((elapse * SWTIMER_INTERVAL) >= gtcpdat_EthernetTxTimer))
                {
                    gtcpdat_LastTxPktAck = 0;
#if GS2E_ENABLE_FLOW_CONTROL
                     /* Fill in the length of payload */
                    gtcpdat_TxBuf[1] = (U8_T)((gtcpdat_TxDatLen-3) >> 8);
                    gtcpdat_TxBuf[2] = (U8_T)((gtcpdat_TxDatLen-3) & 0x00FF);
#endif
                    TCPIP_TcpSend(gtcpdat_Conns[id].TcpSocket, &gtcpdat_TxBuf[0], gtcpdat_TxDatLen, TCPIP_SEND_NOT_FINAL);	
                    gtcpdat_TxSentLen = gtcpdat_TxDatLen;
                    gtcpdat_TxWaitTime = 0;
                }
            }
        }
    }
} /* End of gtcpdat_SendData() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: gtcpdat_GetDataFromUr()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static void gtcpdat_GetDataFromUr(U8_T id)
{
    U8_T dat;

    while (HSUR_GetRxBufCount() > 0) 
    {
#if GS2E_ENABLE_FLOW_CONTROL
        if (gtcpdat_LastTxPktAck == 1 && gtcpdat_TxDatLen >= GTCPDAT_MAX_TCP_DATA_LEN)
            break;
        else
#endif
        if (gtcpdat_TxDatLen >= GTCPDAT_TX_BUF_SIZE)
            break;

        if (HSUR_GetByteNb(&dat) == TRUE)
        {
            gtcpdat_TxBuf[gtcpdat_TxDatLen++] = dat;
            gtcpdat_Conns[id].UrRxBytes++;
        }
    }
} /* End of gtcpdat_GetDataFromUr() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GTCPDAT_Init()
 * Purpose: Initialization
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GTCPDAT_Init(U16_T localPort)
{
	U8_T	i;

	gtcpdat_TcpClient = 0;

	for (i = 0; i < GTCPDAT_MAX_CONNS; i++)
    {
		gtcpdat_Conns[i].State = GTCPDAT_STATE_FREE;
        gtcpdat_Conns[i].UrRxBytes = 0;
        gtcpdat_Conns[i].UrTxBytes = 0;
    }

	gtcpdat_InterAppId = TCPIP_Bind(GTCPDAT_NewConn, GTCPDAT_Event, GTCPDAT_Receive);
	
	if ((GCONFIG_GetNetwork() & GCONFIG_NETWORK_CLIENT) != GCONFIG_NETWORK_CLIENT)
	{	
		/* unicast packet */
		TCPIP_TcpListen(localPort, gtcpdat_InterAppId);
		
		printd("TCP data server init ok.\n\r");
	}
	else
	{
		gtcpdat_TcpClient = 1;
	
		printd("TCP data client init ok.\n\r");	
	}
	
	gtcpdat_LastTxPktAck = 1;
	gtcpdat_TxDatLen = 0;
    gtcpdat_TxSentLen = 0;
	gtcpdat_TxWaitTime = 0;
	gtcpdat_EthernetTxTimer = GCONFIG_GetEthernetTxTimer();

#if GS2E_ENABLE_FLOW_CONTROL			
	gtcpdat_FlowControlXonRx = TRUE;
	gtcpdat_FlowControlModemStatus = HSUR_GetModemStatus(TRUE);
    gtcpdat_FlowControlModemCtrl = (HSUR_GetModemControl() & 0x3);
#endif
} /* End of GTCPDAT_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GTCPDAT_NewConn
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GTCPDAT_NewConn(U32_T XDATA* pip, U16_T remotePort, U8_T socket)
{
	U8_T	i;

	for (i = 0; i < GTCPDAT_MAX_CONNS; i++)
	{
		if (gtcpdat_Conns[i].State == GTCPDAT_STATE_FREE)
		{
			gtcpdat_Conns[i].State = GTCPDAT_STATE_WAIT;
			gtcpdat_Conns[i].Timer = SWTIMER_Tick();
			gtcpdat_Conns[i].Ip = *pip;
			gtcpdat_Conns[i].Port = remotePort;
			gtcpdat_Conns[i].TcpSocket = socket;
			printd("New TCP connection: id=%bu, remotePort=%d, socket=%bu\n\r", i, remotePort, socket);
			return i;
		}
	}
	
	return GTCPDAT_NO_NEW_CONN;

} /* End of GTCPDAT_NewConn() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GTCPDAT_Event
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GTCPDAT_Event(U8_T id, U8_T event)
{
	if (event == TCPIP_CONNECT_ACTIVE)
	{
		if (gtcpdat_Conns[id].State == GTCPDAT_STATE_WAIT)
		{
			gtcpdat_Conns[id].State = GTCPDAT_STATE_CONNECTED;
			GS2E_SetTaskState(GS2E_STATE_TCP_DATA_PROCESS);
            /* Enable keep-alive */
            TCPIP_TcpKeepAlive(gtcpdat_Conns[id].TcpSocket, TCPIP_KEEPALIVE_ON);
			gtcpdat_LastTxPktAck = 1;
			gtcpdat_TxDatLen = 0;
            gtcpdat_TxSentLen = 0;
			gtcpdat_TxWaitTime = 0;
		}
	}
	else if (event == TCPIP_CONNECT_CANCEL)
	{
		if (gtcpdat_Conns[id].State == GTCPDAT_STATE_CONNECTED ||
            gtcpdat_Conns[id].State == GTCPDAT_STATE_WAIT)
		{
			gtcpdat_Conns[id].State = GTCPDAT_STATE_FREE;
			GS2E_SetTaskState(GS2E_STATE_IDLE);			
		}
	}
	else if (event == TCPIP_CONNECT_XMIT_COMPLETE)
	{
        if (gtcpdat_TxSentLen > 0)
        {
            gtcpdat_TxDatLen -= gtcpdat_TxSentLen;
#if GS2E_ENABLE_FLOW_CONTROL
            if (gtcpdat_TxDatLen > 0)
            {
                gtcpdat_TxBuf[0] = GTCPDAT_DATA_INDICATOR;
                /* reserved the length field */
                memcpy(&gtcpdat_TxBuf[3], &gtcpdat_TxBuf[gtcpdat_TxSentLen], gtcpdat_TxDatLen);
                gtcpdat_TxDatLen += 3;
                gtcpdat_GetDataFromUr(id);
            }
#else
            if (gtcpdat_TxDatLen > 0)
                memcpy(&gtcpdat_TxBuf[0], &gtcpdat_TxBuf[gtcpdat_TxSentLen], gtcpdat_TxDatLen);
            gtcpdat_GetDataFromUr(id);
#endif
            gtcpdat_TxSentLen = 0;
        }
        gtcpdat_LastTxPktAck = 1;
    }
} /* End of GTCPDAT_Event() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GTCPDAT_Receive
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GTCPDAT_Receive(U8_T XDATA* pData, U16_T length, U8_T id)
{
	U16_T i;

	if (gtcpdat_Conns[id].State == GTCPDAT_STATE_CONNECTED)
	{
		if (length <= GTCPDAT_MAX_TCP_DATA_LEN) // Is valid length
		{
#if GS2E_ENABLE_FLOW_CONTROL
MoreTcpData:
			if (length <= 6 && *pData == GTCPDAT_FLOW_CONTROL_INDICATOR)
			{
				gtcpdat_HandleFlowControlPacket(pData, length, id);
			}
			else if (length > 3 && *pData == GTCPDAT_DATA_INDICATOR) 
			{
                U16_T dataLen = (*(pData+1) << 8) + *(pData+2) + 3;

                if (dataLen > length) 
                    dataLen = length;

				for (i = 3; i < dataLen; i++) // 1st byte of data the data indicator 
				{
                    gtcpdat_Conns[id].UrTxBytes++;
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
                    goto MoreTcpData;
                }
			}
#else
			for (i = 0; i < length; i++)
			{
                gtcpdat_Conns[id].UrTxBytes++;
				HSUR_PutChar((S8_T) *(pData + i));
			}
#endif
		}
	}	
} /* End of GTCPDAT_Receive() */

#if GS2E_ENABLE_FLOW_CONTROL			
/*
 * ----------------------------------------------------------------------------
 * Function Name: gtcpdat_HandleFlowControlPacket
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void gtcpdat_HandleFlowControlPacket(U8_T XDATA* pData, U16_T length, U8_T id)
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
		case IOCTL_SERIAL_GET_DTRRTS:
            if (gtcpdat_LastTxPktAck == 1)
            {
                gtcpdat_LastTxPktAck = 0;
                txBuf[0] = GTCPDAT_FLOW_CONTROL_INDICATOR;
                txBuf[1] = 0;
                txBuf[2] = 2;
                txBuf[3] = IOCTL_SERIAL_GET_DTRRTS_REPLY;
                txBuf[4] = HSUR_GetModemControl();
                TCPIP_TcpSend(gtcpdat_Conns[id].TcpSocket, txBuf, 5, TCPIP_SEND_NOT_FINAL);
            }
			break;
		case IOCTL_SERIAL_GET_MODEM_CONTROL:
			if (gtcpdat_LastTxPktAck == 1)
            {
                gtcpdat_LastTxPktAck = 0;
                txBuf[0] = GTCPDAT_FLOW_CONTROL_INDICATOR;
                txBuf[1] = 0;
                txBuf[2] = 2;
                txBuf[3] = IOCTL_SERIAL_GET_MODEM_CONTROL_REPLY;
                txBuf[4] = HSUR_GetModemControl();
                TCPIP_TcpSend(gtcpdat_Conns[id].TcpSocket, txBuf, 5, TCPIP_SEND_NOT_FINAL);
            }
			break;
		case IOCTL_SERIAL_GET_MODEM_STATUS:
			if (gtcpdat_LastTxPktAck == 1)
            {
                gtcpdat_LastTxPktAck = 0;
                txBuf[0] = GTCPDAT_FLOW_CONTROL_INDICATOR;
                txBuf[1] = 0;
                txBuf[2] = 2;
                txBuf[3] = IOCTL_SERIAL_GET_MODEM_STATUS_REPLY;
                txBuf[4] = HSUR_GetModemStatus(TRUE);
                TCPIP_TcpSend(gtcpdat_Conns[id].TcpSocket, txBuf, 5, TCPIP_SEND_NOT_FINAL);
            }
			break;
		case IOCTL_SERIAL_CLR_DTR:
			HSUR_ClearDTR();
			break;
		case IOCTL_SERIAL_CLR_RTS:
			HSUR_ClearRTS();		
			break;
		case IOCTL_SERIAL_SET_DTR:
			HSUR_SetDTR();
			break;
		case IOCTL_SERIAL_SET_RTS:
			HSUR_SetRTS();
			break;
		case IOCTL_SERIAL_SET_BAUD_RATE:			
            HSUR_SetupPort(GCONFIG_GetBaudRate(dat1), dat2);
			break;
		case IOCTL_SERIAL_SET_BREAK_OFF:
			dat1 = HSUR_GetLineControl();
			HSUR_SetLineControl(dat1 & 0xBF); // bit 6 - break control bit (1:on, 0:off)
			break;
		case IOCTL_SERIAL_SET_BREAK_ON:
			dat1 = HSUR_GetLineControl();
			HSUR_SetLineControl(dat1 | 0x40); // bit 6 - break control bit (1:on, 0:off)
			break;
		case IOCTL_SERIAL_SET_FIFO_CONTROL:
			HSUR_SetFifoControl(dat1);
			break;
		case IOCTL_SERIAL_SET_LINE_CONTROL:
			HSUR_SetLineControl(dat1);
			break;
		case IOCTL_SERIAL_SET_MODEM_CONTROL:
			HSUR_SetModemControl(dat1);
			break;
		case IOCTL_SERIAL_SET_XOFF:
			gtcpdat_FlowControlXonRx = FALSE;
			break;
		case IOCTL_SERIAL_SET_XON:
			gtcpdat_FlowControlXonRx = TRUE;
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
		case IOCTL_SERIAL_XOFF_COUNTER:
			//...
			break;

		default:
			printd("Unknown flow control command!\n\r");
			break;
	}
} /* End of gtcpdat_HandleFlowControlPacket() */
#endif

/*
 * ----------------------------------------------------------------------------
 * Function Name: GTCPDAT_GetTxBytes
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GTCPDAT_GetTxBytes(U8_T id)
{
    if (id < GTCPDAT_MAX_CONNS)
        return gtcpdat_Conns[id].UrTxBytes;

    return 0;
} /* End of GTCPDAT_GetTxBytes() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GTCPDAT_GetRxBytes
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T GTCPDAT_GetRxBytes(U8_T id)
{
    if (id < GTCPDAT_MAX_CONNS)
        return gtcpdat_Conns[id].UrRxBytes;

    return 0;
} /* End of GTCPDAT_GetRxBytes() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: gtcpdat_CheckAllConnStatusIdle
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
static U8_T gtcpdat_CheckAllConnStatusIdle(void)
{
    U8_T id;

    for (id = 0; id < GTCPDAT_MAX_CONNS; id++)
    {
        if (gtcpdat_Conns[id].State != GTCPDAT_STATE_FREE)
            return 0;
    }

    return 1;
} /* End of gtcpdat_CheckAllConnStatusIdle() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GTCPDAT_ConnClose
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GTCPDAT_ConnClose(U32_T remoteIp, U16_T port)
{
    U8_T id;

    for (id = 0; id < GTCPDAT_MAX_CONNS; id++)
    {
        if (gtcpdat_Conns[id].State == GTCPDAT_STATE_CONNECTED)
        {
            if (gtcpdat_Conns[id].Ip == remoteIp && gtcpdat_Conns[id].Port == port)
            {
			    gtcpdat_Conns[id].State = GTCPDAT_STATE_FREE;
                TCPIP_TcpClose(gtcpdat_Conns[id].TcpSocket);
                if (gtcpdat_CheckAllConnStatusIdle())
                    GS2E_SetTaskState(GS2E_STATE_IDLE);
            }
        }
    }

} /* End of GTCPDAT_ConnClose() */

/* End of gtcpdat.c */