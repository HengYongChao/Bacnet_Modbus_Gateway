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
 * Module Name: dnsctab.c
 * Purpose:
 * Author:
 * Date:
 * Notes:
 * $Log: dnsctab.c,v $
 * Revision 1.2  2006/05/23 01:53:38  robin6633
 * 1.Removed debug information from UART2.
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
#include "adapter.h"
#include "dnsctab.h"
#include "uart.h"
#include "printd.h"

#include <string.h>
#include <stdio.h>

/* NAMING CONSTANT DECLARATIONS */
#define DNSCTAB_MAX_HOST_NAME_LEN 	255

/* GLOBAL VARIABLES DECLARATIONS */

/* LOCAL VARIABLES DECLARATIONS */
static S8_T  XDATA dnsctab_HostNameTable[DNSCTAB_MAX_RECORD][DNSCTAB_MAX_HOST_NAME_LEN + 1];
static U32_T XDATA dnsctab_HostIpTable[DNSCTAB_MAX_RECORD];
static U8_T  XDATA dnsctab_HostName[DNSCTAB_MAX_HOST_NAME_LEN + 1];
static U8_T  XDATA dnsctab_OldestRecord; // Oldest record for overwrite
/* LOCAL SUBPROGRAM DECLARATIONS */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSCTAB_Init()
 * Purpose: Initialization
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void DNSCTAB_Init(void)
{
	U8_T i;

	for (i = 0; i < DNSCTAB_MAX_RECORD; i++)
	{
		dnsctab_HostIpTable[i] = 0;
	}

	dnsctab_OldestRecord = 0;

	DNSC_Init();

} /* End of DNSCTAB_Init() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSCTAB_Query
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T DNSCTAB_Query(S8_T *pName, U32_T *pip)
{
	U8_T	i;

	if(strlen(pName) <= 255)
	{
		for (i = 0; i < DNSCTAB_MAX_RECORD; i++)
		{
			if (dnsctab_HostIpTable[i] == 0)
				continue;
			if (strcmp(pName, dnsctab_HostNameTable[i]) == 0) // Does both host name match?
			{
				*pip = dnsctab_HostIpTable[i]; // Yes, return the host IP

				return DNSC_STATE_RESPONSED; 
			}   	
		}
	
		strcpy(dnsctab_HostName, pName); // Store this new host name
		return DNSC_Query(pName);
	}
	else
	{
#if (UART0_ENABLE)
//		printd ("Host name length is greater than 255 bytes.\n\r");
#endif
	}

	return DNSC_STATE_FREE;

} /* End of DNSCTAB_Query() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSCTAB_GetState
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U8_T DNSCTAB_GetState(void)
{
	return DNSC_GetState();

} /* End of DNSCTAB_Receive() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSCTAB_GetIP
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
U32_T DNSCTAB_GetIP(void)
{
	if (DNSC_GetState() == DNSC_STATE_RESPONSED)
	{
		// Store the new record and overwrite the oldest record if needed)
		if (dnsctab_OldestRecord >= DNSCTAB_MAX_RECORD)
			dnsctab_OldestRecord = 0;
	
		strcpy(dnsctab_HostNameTable[dnsctab_OldestRecord], dnsctab_HostName);
		dnsctab_HostIpTable[dnsctab_OldestRecord] = DNSC_GetIp();

		return dnsctab_HostIpTable[dnsctab_OldestRecord++];
	}
	else
	{
		return 0;
	}
	
} /* End of DNSCTAB_GetIP() */

/*
 * ----------------------------------------------------------------------------
 * Function Name: DNSCTAB_SetDnsIP
 * Purpose: 
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */
void DNSCTAB_SetDnsIP(U32_T ip)
{
	DNSC_SetDnsIP(ip);	
} /* End of DNSCTAB_SetDnsIP() */

#endif /* INCLUDE_DNS_CLIENT */

/* End of dnsctab.c */
