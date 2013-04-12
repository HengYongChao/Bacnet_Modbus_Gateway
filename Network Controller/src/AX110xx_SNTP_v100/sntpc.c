/*
*********************************************************************************
*     Copyright (c) 2006   ASIX Electronic Corporation      All rights reserved.
*
*     This is unpublished proprietary source code of ASIX Electronic Corporation
*
*     The copyright notice above does not evidence any actual or intended
*
*     publication of such source code.
*********************************************************************************


/* INCLUDE FILE DECLARATIONS */
#include "adapter.h"

#if 1
#include "sntpc.h"
#include "tcpip.h"
#include "uart.h"
#include "mstimer.h"
#include "printd.h"
#include <stdio.h>

/* NAMING CONSTANT DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static TimeInfo t;
static SNTPHeader *psntpcpMsg;
static U16_T timetickinfo;
static S16_T GMT;
static U8_T	Month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
static U8_T	AddMonth[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
static SNTPC_CONN sntpc_Conns;
static U8_T sntpc_InterAppId;
static U8_T	sntp_Buf[48];
static U8_T sntp_Retry = 0;

extern U8_T  far Para[400]; 

/* LOCAL SUBPROGRAM DECLARATIONS */


/*
 * ----------------------------------------------------------------------------
 * Function Name: SNTPC_Init
 * Purpose: to initial the SNTP client connection information.
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void SNTPC_Init(void)
{
	sntpc_Conns.State = SNTP_STATE_INITIAL;
	sntpc_InterAppId = TCPIP_Bind(NULL, SNTPC_Event, SNTPC_Receive);
//	printd("sntp init...\n\r");

} /* End of SNTPC_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SNTPC_Event
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void SNTPC_Event(U8_T id, U8_T event)
{
	if (id != 0)
		return;

	if (event == TCPIP_CONNECT_CANCEL)
	{
		TCPIP_UdpClose(sntpc_Conns.UdpSocket);
		sntpc_Conns.State = SNTP_STATE_INITIAL;
	}

} /* End of SNTPC_Event() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SNTPC_Receive
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void SNTPC_Receive(U8_T XDATA* pData, U16_T length, U8_T id)
{
	U8_T	i = 0;
	S8_T	signhour, signmin;
	U8_T	hour, min;

//	printd("UDP received!\n\r");

    

	if (id != 0)
		return;
	length = length;

	signhour = GMT / 100;
	signmin = GMT % 100;

	t.sntpcPktPtr = (SNTPHeader*)pData;
	psntpcpMsg = (SNTPHeader*)t.sntpcPktPtr;
	t.timestamp = psntpcpMsg->receive_time1;

	if (signhour < 0)
	{
		hour = -signhour;
		min = -signmin;
	t.timestamp -= (hour*3600 + min*60);
	}
	else
	{
		hour = signhour;
		min = signmin;
		t.timestamp += (hour*3600 + min*60);
	}

	t.second_remain = t.timestamp % 86400;
	t.day_total = t.timestamp / 86400;
	t.HH = t.second_remain / 3600;
	t.MI_r = t.second_remain % 3600;
	t.MI = t.MI_r / 60;
	t.SS = t.MI_r % 60;
	t.YY = t.day_total / 365.2425;

	if((t.YY % 4) == 0)
	{	
		t.DD_r = t.day_total-(t.YY*365)-(t.YY/4);
		t.DD_r++;
		t.DD_r++;	
		while(t.DD_r>0)
		{
			t.DD = t.DD_r;
			t.DD_r -= AddMonth[i];
			i++;
		}
	}
	else
	{
		t.DD_r = t.day_total-(t.YY*365)-(t.YY/4);
		t.DD_r++;
		if(t.DD_r>365){
			t.DD_r = 1;
			t.YY++;
		}
		while(t.DD_r>0)
		{
			t.DD = t.DD_r;
			t.DD_r -= Month[i];
			i++;
		}
	}
	t.MM = i;
	t.YY += 1900;


	//	printd("\r\n %d/%.2bd/%.2d  %.2bd:%.2bd:%.2bd \r\n",t.YY,t.MM
		//													,t.DD,t.HH
			//												,t.MI,t.SS);
//printd("\r\n %d/%2bd/%2d  %2bd:%2bd:%2bd \r\n",t.YY,t.MM
										//					,t.DD,t.HH
											//				,t.MI,t.SS);
Para[200*2]=t.YY/100;
Para[200*2+1]=t.YY%100;
Para[200*2+2]=t.MM;
Para[200*2+3]=t.DD;
Para[200*2+4]=t.HH;
Para[200*2+5]=t.MI;
Para[200*2+6]=t.SS;

  //  Para[43]=1;
//	TCPIP_UdpClose(sntpc_Conns.UdpSocket);
//	sntpc_Conns.State = SNTP_STATE_GET_DONE;
   // sntpc_Conns.State = SNTP_STATE_WAIT; 

} /* End of SNTPC_Receive() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SNTPC_GetTime
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T* SNTP_GetTime(void)
{
  	if (sntpc_Conns.State != SNTP_STATE_GET_DONE)
		return NULL;

	sntpc_Conns.State = SNTP_STATE_INITIAL;
	sprintf (sntp_Buf, "%d/%.2bd/%.2bd %.2bd:%.2bd:%.2bd",
		t.YY, t.MM, (U8_T)t.DD, t.HH, t.MI, t.SS);
	sntp_Buf[20] = 0;

	return sntp_Buf;

} /* End of SNTP_GetTime() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: sntpc_Send
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void sntpc_Send(U8_T InterUdpId)
{
	U8_T len = 48;
	U8_T i;

	sntp_Buf[0] = 0x0b;
	for (i = 1; i < len; i++)
		sntp_Buf[i] = 0;
	
	TCPIP_UdpSend(InterUdpId, 0, 0, sntp_Buf, len);
//	printd("sntp send...\n\r");

} /* End of sntpc_Send() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SNTPC_Start
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T SNTPC_Start(S16_T gmt, U32_T timesrIP)
{
/*	if (sntpc_Conns.State != SNTP_STATE_INITIAL)
		return SNTP_STATE_NOTREADY;		*/

	sntpc_Conns.ServerIp = timesrIP;
	GMT = gmt;

	/* Create SNTP client port */
	if ((sntpc_Conns.UdpSocket = TCPIP_UdpNew(sntpc_InterAppId, 0, sntpc_Conns.ServerIp,
		0, SNTP_SERVER_PORT)) == TCPIP_NO_NEW_CONN)
	{

//		printd ("Allocate SNTPC socket port fail.\n\r");

		return SNTP_STATE_NOTREADY;
	}

	sntpc_Send(sntpc_Conns.UdpSocket);
	sntpc_Conns.State = SNTP_STATE_WAIT;
	timetickinfo = (U16_T)SWTIMER_Tick();
	sntp_Retry = 0;
//	printd("sntp start...\n\r");
	return SNTP_STATE_WAIT;
} /* End of SNTPC_Start() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SNTPC_Stop
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void SNTPC_Stop(void)
{
	if (sntpc_Conns.State != SNTP_STATE_INITIAL)
	{
		TCPIP_UdpClose(sntpc_Conns.UdpSocket);
		sntpc_Conns.State = SNTP_STATE_INITIAL;
	}

} /* End of SNTPC_Stop() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: SNTPC_GetState
 * Purpose: 
 * Params:SNTPC_Debug(void)
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T SNTPC_GetState(void)
{
	if(sntpc_Conns.State == SNTP_STATE_WAIT)
	{
		U16_T	CurTime = (U16_T)SWTIMER_Tick();
          if(1)
	//	if ((CurTime - timetickinfo) >= SNTPC_REQUEST_TIMEOUT)//SNTPC_REQUEST_TIMEOUT bigger to 5
		{  /** printd ("SNTP >timeout\n\r");
			if (++sntp_Retry >= SNTPC_MAX_RETRY)//SNTPC_MAX_RETRY bigger to 6
			{ printd ("SNTP retry exceed\n\r");
				TCPIP_UdpClose(sntpc_Conns.UdpSocket);
				sntpc_Conns.State = SNTP_STATE_INITIAL;

				return SNTP_STATE_TIMEOUT;
			}***/
           
			sntpc_Send(sntpc_Conns.UdpSocket);
           // printd ("SNTP send in while\n\r");
			timetickinfo = (U16_T)SWTIMER_Tick();
            sntp_Retry=0;
		}
     // else
           // printd ("SNTP <timeout\n\r");
	}
	return sntpc_Conns.State;
}

/* only for debug */
void SNTPC_Debug(void)
{
//	printd ("SNTPC Connection state: %bx\n\r", sntpc_Conns.State);
}


#endif /* #if (INCLUDE_SNTP_CLIENT) */


/* End of sntpc.c */
