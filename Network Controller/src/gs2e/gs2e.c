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
 * Module Name: gs2e.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: gs2e.c,v $
 *
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include "main.h"
#include "adapter.h"
#include "gs2e.h"
#include "gtcpdat.h"
#include "gudpdat.h"
#include "gudpbc.h"
#include "gudpmc.h"
#include "gudpuc.h"
#include "httpd.h"
#include "gconfig.h"
#include "printd.h"
#include "mac.h"
#include "console.h"
#if (INCLUDE_TELNET_SERVER)
#include "telnet.h"
#endif
#if (INCLUDE_EVENT_DETECT)
#include "gevent.h"
#endif
#if (INCLUDE_DNS_CLIENT)
  #include "dnsc.h"
#endif

#include "eeprom.h"
#include "ping.h"
/* NAMING CONSTANT DECLARATIONS */

/* MACRO DECLARATIONS */

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static U8_T XDATA gs2e_State;
static U8_T XDATA gs2e_ConnType;

/* LOCAL SUBPROGRAM DECLARATIONS */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GS2E_Task
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GS2E_Task(void)
{
	GCONFIG_Task();
    if (gs2e_ConnType == GS2E_CONN_UDP)
	    GUDPDAT_Task();
    else if (gs2e_ConnType == GS2E_CONN_TCP)
	    GTCPDAT_Task();
	GUDPMC_Task();
	GUDPBC_Task();
	GUDPUC_Task();
#if (INCLUDE_HTTP_SERVER)
	HTTP_Task();
#endif
    CONSOLE_Task();
#if (INCLUDE_TELNET_SERVER)
    TELNET_Task();
#endif

#if (INCLUDE_EVENT_DETECT)
	GEVENT_Task();
#endif

#if (INCLUDE_DNS_CLIENT)
	DNSC_Task();
#endif	
	PING_Task();

} /* End of GS2E_Task() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GS2E_Init()
 * Purpose: Initialization
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GS2E_Init(void)
{	
	gs2e_State = GS2E_STATE_IDLE; 

	if ((GCONFIG_GetNetwork() & GCONFIG_NETWORK_PROTO_UDP_MCAST) == GCONFIG_NETWORK_PROTO_UDP_MCAST)
		GUDPMC_Init(GCONFIG_UDP_MCAST_SERVER_PORT);

	if ((GCONFIG_GetNetwork() & GCONFIG_NETWORK_PROTO_UDP_BCAST) == GCONFIG_NETWORK_PROTO_UDP_BCAST ||
		(GCONFIG_GetNetwork() & GCONFIG_NETWORK_PROTO_UDP_MCAST) != GCONFIG_NETWORK_PROTO_UDP_MCAST
	   )
	{
		if((GCONFIG_GetNetwork() & GCONFIG_NETWORK_PROTO_UDP_MCAST) != GCONFIG_NETWORK_PROTO_UDP_MCAST)
		{
			MAC_SetRxFilter(MAC_RCV_BROADCAST);
		}
		GUDPBC_Init(GCONFIG_UDP_BCAST_SERVER_PORT);
	}

	GUDPUC_Init(GCONFIG_UDP_UCAST_SERVER_PORT);

#if (INCLUDE_HTTP_SERVER)
	HTTP_Init();
#endif

	if ((GCONFIG_GetNetwork() & GCONFIG_NETWORK_PROTO_UDP) == GCONFIG_NETWORK_PROTO_UDP)
	{
        gs2e_ConnType = GS2E_CONN_UDP;
		GUDPDAT_Init(GCONFIG_GetServerDataPktListenPort());
	}
	else
	{
        gs2e_ConnType = GS2E_CONN_TCP;
		GTCPDAT_Init(GCONFIG_GetServerDataPktListenPort());
	}

    CONSOLE_Init();
#if (INCLUDE_TELNET_SERVER)
    TELNET_Init();
#endif

#if (INCLUDE_EVENT_DETECT)
	GEVENT_Init();
#endif

#if (INCLUDE_DNS_CLIENT)
	DNSC_Init();
#endif	

	EEPROM_Init();
    PING_Init();
} /* End of GS2E_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GS2E_GetTaskState
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GS2E_GetTaskState(void)
{
	return gs2e_State;
} /* End of GS2E_GetTaskState() */
/*
 * ----------------------------------------------------------------------------
 * Function Name: GS2E_SetTaskState
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void GS2E_SetTaskState(U8_T state)
{
	gs2e_State = state;
} /* End of GS2E_SetTaskState() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: GS2E_GetConnType
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T GS2E_GetConnType(void)
{
	return gs2e_ConnType;
} /* End of GS2E_GetConnType() */

/* End of gs2e.c */
