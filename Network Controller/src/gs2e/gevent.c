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
 * Module Name: gevent.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: gevent.c,v $
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "gevent.h"
#include "gconfig.h"
#include "stoe.h"
#include "uart.h"
#include "reg80390.h"
#include "printd.h"
#include "ax11000.h"
#include "smtpc.h"
#include "main.h"
#include <string.h>
#include "dnsc.h"
#include "mstimer.h"
#if (INCLUDE_EVENT_DETECT)
/* NAMING CONSTANT DECLARATIONS */

/* MACRO DECLARATIONS */

/* TYPE DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */
U8_T XDATA GEVENT_SmtpBuf[256];
U8_T const FAR GEVENT_SmtpSubject[] = "Warning form R2E.\r\nMIME-Version: 1.0\r\nContent-Type: text/plain\r\nContent-Transfer-Encoding: base64\r\n\r\n";

/* LOCAL VARIABLES DECLARATIONS */
static GEVENT_FLAGS EventFlag;

/* LOCAL SUBPROGRAM DECLARATIONS */
U8_T const FAR warningMessages_coldStart[] = {"Auto Warning: Cold start event"};
U8_T const FAR warningMessages_AuthFail[] = {"Auto Warning: Authentication fail event"};
U8_T const FAR warningMessages_IPchg[] = {"Auto Warning: Local IP changed event"};
U8_T const FAR warningMessages_PWchg[] = {"Auto Warning: Password changed event"};
static U32_T TimerStop = 0, TimerStart = 0, TimerElapse;
	
/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_Timer()
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GEVENT_Timer()
{
    if (!EventFlag.WaitTimer)
        return;

	TimerStop = SWTIMER_Tick();

	if (TimerStop >= TimerStart)
		TimerElapse = TimerStop - TimerStart;
	else
		TimerElapse = TimerStop + (0xFFFFFFFF - TimerStart);
							
	if (TimerElapse > SWTIMER_COUNT_SECOND)
	{
		TimerStart = TimerStop;	
		EventFlag.WaitTimer --;
	}
}  /* End of GEVENT_Timer() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_Task
 * Purpose: Main function
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GEVENT_Task(void)
{
	U8_T FromAddr[36];
	U8_T To1Addr[36];
	U8_T To2Addr[36];
	U8_T To3Addr[36];		
	U32_T QueryIP;
	static U8_T event_status = 0;
	static U8_T QueryFlag = 0;
	
	GEVENT_DetectPSWchgEvent();
	GEVENT_DetectIPchgEvent();
	GEVENT_Timer();
							
	switch (event_status)
	{
	case 0:
		if (GEVENT_GetColdStartEvent())
		{
			event_status = 1;		
		}
		if (GEVENT_GetAuthFailEvent())
		{
			event_status = 1;		
		}
		if (GEVENT_GetIPchgEvent())
		{
			event_status = 1;		
		}
		if (GEVENT_GetPSWchgEvent())
		{
			event_status = 1;		
		}			
		break;
		
	case 1:		
		To1Addr[0] = GCONFIG_GetSMTPDomainName(FromAddr);
		QueryIP = GCONFIG_IpAddr2Ulong(FromAddr, To1Addr[0]);
		event_status = (QueryIP == 0xffffffff) ? 2 : 3;
		QueryFlag = 0;
		break;
		
	case 2:
#if (INCLUDE_DNS_CLIENT)
		if (DNSC_Query(FromAddr, &QueryIP) == DNSC_QUERY_OK)
		{
#if (GEVENT_ENABLE_DEBUG_MSG)
			printd("Event: Query SMTP server %s IP OK! 0x%lx\n\r", FromAddr, QueryIP);		
#endif
				event_status = 3;
		}
		else if (DNSC_Query(FromAddr, &QueryIP) == DNSC_QUERY_FREE)
		{
			if (QueryFlag)
			{
				event_status = 0xff;				
			}
			else
			{
				DNSC_Start(FromAddr);
				QueryFlag = 1;
			}
		}
#else
        event_status = 0;
#endif
		break;
			
	case 3:
		if (SMTPC_GetState() == SMTP_STATE_NONE)
		{
			GCONFIG_GetSMTPFrom(FromAddr);
			GCONFIG_GetSMTPTo1(To1Addr);
			GCONFIG_GetSMTPTo2(To2Addr);
			GCONFIG_GetSMTPTo3(To3Addr);						
			SMTPC_Start(QueryIP, FromAddr, To1Addr, To2Addr, To3Addr);
#if (GEVENT_ENABLE_DEBUG_MSG)
			printd("Send E-mail start...\n\r");			
#endif
	        TimerStart = SWTIMER_Tick();
			EventFlag.WaitTimer = 10;//wait 10 sec
			event_status = 4;
		}
		break;
		
	case 4:
		if (SMTPC_GetState() == SMTP_STATE_WAIT_MESSAGE)
		{
			if (GEVENT_GetColdStartEvent())
				SMTPC_SendMessage(warningMessages_coldStart, sizeof(warningMessages_coldStart));
			else if (GEVENT_GetAuthFailEvent())
				SMTPC_SendMessage(warningMessages_AuthFail, sizeof(warningMessages_AuthFail));
			else if (GEVENT_GetIPchgEvent())
				SMTPC_SendMessage(warningMessages_IPchg, sizeof(warningMessages_IPchg));
			else if (GEVENT_GetPSWchgEvent())
				SMTPC_SendMessage(warningMessages_PWchg, sizeof(warningMessages_PWchg));

			event_status = 5;
		}
		else if ((SMTPC_GetState() == SMTP_STATE_NONE) || (SMTPC_GetState() == SMTP_STATE_QUIT_SENT))
		{
			printd("Send E-mail fail: wait message\n\r");	
			event_status = 0xff;
		}
		else if (EventFlag.WaitTimer == 0)
		{
			printd("Send E-mail fail: wait time out\n\r");
			event_status = 0xff;			
		}
		break;
		
	case 5:
		if (SMTPC_GetState() == SMTP_STATE_QUIT_SENT)
		{
			event_status = 0xff;
#if (GEVENT_ENABLE_DEBUG_MSG)			
			printd("Send E-mail complete\n\r");
#endif
		}
		else if (SMTPC_GetState() == SMTP_STATE_NONE)
		{
#if (GEVENT_ENABLE_DEBUG_MSG)		
			printd("Send E-mail fail: wait quit\n\r");			
#endif			
			event_status = 0xff;
		}
		break;
		
	default:
			GEVENT_SetColdStartEvent(0);
			GEVENT_SetAuthFailEvent(0);
			GEVENT_SetIPchgEvent(0);			
			GEVENT_SetPSWchgEvent(0);
			event_status = 0;
		break;
	}	
	
} /* End of GEVENT_Task() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_Init
 * Purpose: Initialization
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GEVENT_Init(void)
{
	EventFlag.AutoWarning = 0;
	GCONFIG_GetAdmin(EventFlag.USNtemp[0], EventFlag.PSWtemp[0], &(EventFlag.LVLtemp[0]));
	EventFlag.IPtemp[0] = GCONFIG_GetServerStaticIP();	
	EventFlag.WaitTimer = 0;
		
	GEVENT_SetColdStartEvent(1);

	SMTPC_Init(GEVENT_SmtpBuf, GEVENT_SmtpSubject);
} /* End of GEVENT_Init() */

/////////////////////////////////////////////////////////////////////////////////

/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_SetColdStartEvent
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GEVENT_SetColdStartEvent(U8_T Value)
{
	U16_T Temp16;
	
	Temp16 = GCONFIG_GetAutoWarning();
	if (!(Temp16 & GCONFIG_SMTP_EVENT_COLDSTART))
		Value = 0;
				
	if (Value)
		EventFlag.AutoWarning |= GCONFIG_SMTP_EVENT_COLDSTART;
	else
		EventFlag.AutoWarning &= (~GCONFIG_SMTP_EVENT_COLDSTART);
} /* End of GEVENT_SetColdStatrEvent() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_GetColdStartEvent
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GEVENT_GetColdStartEvent(void)
{
	U16_T Temp16;
	
	Temp16 = GCONFIG_GetAutoWarning();
	if ((Temp16 & GCONFIG_SMTP_EVENT_COLDSTART) && (EventFlag.AutoWarning & GCONFIG_SMTP_EVENT_COLDSTART))
		return 1;
		
	return 0;
} /* End of GEVENT_GetColdStartEvent() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_SetAuthFailEvent
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GEVENT_SetAuthFailEvent(U8_T Value)
{
	U16_T Temp16;
	
	Temp16 = GCONFIG_GetAutoWarning();
	if (!(Temp16 & GCONFIG_SMTP_EVENT_AUTH_FAIL))
		Value = 0;
				
	if (Value)
		EventFlag.AutoWarning |= GCONFIG_SMTP_EVENT_AUTH_FAIL;
	else
		EventFlag.AutoWarning &= (~GCONFIG_SMTP_EVENT_AUTH_FAIL);
} /* End of GEVENT_SetAuthFailEvent() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_GetAuthFailEvent
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GEVENT_GetAuthFailEvent(void)
{
	U16_T Temp16;
	
	Temp16 = GCONFIG_GetAutoWarning();
	if ((Temp16 & GCONFIG_SMTP_EVENT_AUTH_FAIL) && (EventFlag.AutoWarning & GCONFIG_SMTP_EVENT_AUTH_FAIL))
		return 1;
		
	return 0;
} /* End of GEVENT_GetAuthFailEvent() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_SetIPchgEvent
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GEVENT_SetIPchgEvent(U8_T Value)
{
	U16_T Temp16;
	
	Temp16 = GCONFIG_GetAutoWarning();
	if (!(Temp16 & GCONFIG_SMTP_EVENT_IP_CHANGED))
		Value = 0;
				
	if (Value)
		EventFlag.AutoWarning |= GCONFIG_SMTP_EVENT_IP_CHANGED;
	else
		EventFlag.AutoWarning &= (~GCONFIG_SMTP_EVENT_IP_CHANGED);
} /* End of GEVENT_SetIPchgEvent() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_GetIPchgEvent
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GEVENT_GetIPchgEvent(void)
{
	U16_T Temp16;
	
	Temp16 = GCONFIG_GetAutoWarning();
	if ((Temp16 & GCONFIG_SMTP_EVENT_IP_CHANGED) && (EventFlag.AutoWarning & GCONFIG_SMTP_EVENT_IP_CHANGED))
		return 1;
		
	return 0;
} /* End of GEVENT_GetIPchgEvent() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_DetectIPchgEvent
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GEVENT_DetectIPchgEvent(void)
{
	if (GCONFIG_GetNetwork() & GCONFIG_NETWORK_DHCP_ENABLE)
		return;
	EventFlag.IPtemp[1] = GCONFIG_GetServerStaticIP();
	
	if (memcmp((U8_T*)&(EventFlag.IPtemp[0]), (U8_T*)&(EventFlag.IPtemp[1]), 4))
	{
		GEVENT_SetIPchgEvent(1);
		memcpy((U8_T*)&(EventFlag.IPtemp[0]), (U8_T*)&(EventFlag.IPtemp[1]), 4);
	}

} /* End of GEVENT_DetectIPchgEvent() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_SetPSWchgEvent
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GEVENT_SetPSWchgEvent(U8_T Value)
{
	U16_T Temp16;
	
	Temp16 = GCONFIG_GetAutoWarning();
	if (!(Temp16 & GCONFIG_SMTP_EVENT_PSW_CHANGED))
		Value = 0;
				
	if (Value)
		EventFlag.AutoWarning |= GCONFIG_SMTP_EVENT_PSW_CHANGED;
	else
		EventFlag.AutoWarning &= (~GCONFIG_SMTP_EVENT_PSW_CHANGED);
} /* End of GEVENT_SetPSWchgEvent() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_GetPSWchgEvent
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GEVENT_GetPSWchgEvent(void)
{
	U16_T Temp16;
	
	Temp16 = GCONFIG_GetAutoWarning();
	if ((Temp16 & GCONFIG_SMTP_EVENT_PSW_CHANGED) && (EventFlag.AutoWarning & GCONFIG_SMTP_EVENT_PSW_CHANGED))
		return 1;
		
	return 0;
} /* End of GEVENT_GetPSWchgEvent() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GEVENT_DetectPSWchgEvent
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GEVENT_DetectPSWchgEvent(void)
{
	GCONFIG_GetAdmin(EventFlag.USNtemp[1], EventFlag.PSWtemp[1], &(EventFlag.LVLtemp[1]));
	
	if (strcmp(EventFlag.PSWtemp[0], EventFlag.PSWtemp[1]))
	{
		GEVENT_SetPSWchgEvent(1);
		strcpy(EventFlag.PSWtemp[0], EventFlag.PSWtemp[1]);
	}

} /* End of GEVENT_DetectPSWchgEvent() */

#endif /* (INCLUDE_EVENT_DETECT) */

/* End of gevent.c */
