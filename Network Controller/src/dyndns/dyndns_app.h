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
 * Module Name:dyndns.h
 * Purpose:
 * Author:
 * Date:
 * Notes:
 *=============================================================================
 */

#ifndef __DYNDNS_APP_H__
#define __DYNDNS_APP_H__

/* INCLUDE FILE DECLARATIONS */
#include "types.h"


#ifndef CONF_DDNS_3322
#define CONF_DDNS_3322		0
#endif

#ifndef CONF_DDNS_DYNDNS
#define CONF_DDNS_DYNDNS	1
#endif

#ifndef CONF_DDNS_NOIP
#define CONF_DDNS_NOIP		2
#endif


#ifndef	MAX_USERNAME_SIZE
#define MAX_USERNAME_SIZE	32
#endif

#ifndef	MAX_PASSWORD_SIZE
#define MAX_PASSWORD_SIZE	32
#endif

#ifndef	MAX_DOMAIN_SIZE
#define MAX_DOMAIN_SIZE		32
#endif

extern U8_T far dyndns_enable;
extern U8_T far dyndns_provider;
extern U8_T far dyndns_domain_name[];
extern U8_T far dyndns_username[];
extern U8_T far dyndns_password[];
extern U8_T far check_ip_every;
extern U8_T far force_update_every;

extern U8_T far update_from_dyndns;
extern U16_T far dyndns_update_counter;
extern U16_T far dyndns_update_period;


typedef struct
{
	U8_T type;
	U32_T ip;
} _STR_DYNDNS_SERVER;

extern _STR_DYNDNS_SERVER const code dyndns_server_array[3];

//extern U8_T far test_dyndns_state;
//extern U8_T far test_dyndns_AppId;
//extern U8_T far test_dyndns_ConnId;
//extern U8_T far test_tcpip_connect_status;
//extern U16_T far test_dyndns_rev_len;
//extern U8_T far test_rev_buf[20];

void init_dyndns(void);
void do_dyndns(void);
void dyndns_reply(void);


#endif /* End of __DYNDNS_H__ */



