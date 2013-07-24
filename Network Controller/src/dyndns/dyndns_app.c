
#include "dyndns.h"
#include "dyndns_app.h"

//U8_T far test_dyndns_state = 0;
//U8_T far test_dyndns_AppId = 0;
//U8_T far test_dyndns_ConnId = 0xff;
//U8_T far test_tcpip_connect_status = 0;
//U16_T far test_dyndns_rev_len = 0;
//U8_T far test_rev_buf[20] = {0};

U8_T far dyndns_enable = TRUE;
U8_T far dyndns_provider = CONF_DDNS_DYNDNS;
U8_T far dyndns_domain_name[MAX_DOMAIN_SIZE] = "temcocontrols.dyndns.org";
U8_T far dyndns_username[MAX_USERNAME_SIZE] = "temcocontrols";
U8_T far dyndns_password[MAX_PASSWORD_SIZE] = "travel";
U8_T far check_ip_every;
U8_T far force_update_every;

U8_T far update_from_dyndns = TRUE;
U16_T far dyndns_update_counter;
U16_T far dyndns_update_period;

_STR_DYNDNS_SERVER const code dyndns_server_array[3] = 
{
	{
		CONF_DDNS_3322, 	// www.3322.org
		0x3DA0EF19,			// 61.160.239.25
	},
	{
		CONF_DDNS_DYNDNS,	// www.dyndns.com
		0xCC0DF875,			// 204.13.248.117
	},
	{
		CONF_DDNS_NOIP,		// www.no-ip.com
		0x0817E06E,			// 8.23.224.110
	}
//	{
//		CONF_DDNS_ODS,		//update.ods.com
//		0x081E5919,			//8.30.89.19
//	}

};

void init_dyndns(void)
{
	DynDNS_Init();
	update_from_dyndns = TRUE;
}

void do_dyndns(void)
{
	if(dyndns_enable == FALSE)
		return;

	if(update_from_dyndns == TRUE)
	{
		DynDNS_DoUpdateDynDns(dyndns_server_array[dyndns_provider].type,
		 						dyndns_server_array[dyndns_provider].ip, 
								dyndns_domain_name, 
								dyndns_username, 
								dyndns_password);
		
		if(DynDNS_GetUpdateState() == TRUE)
		{
			update_from_dyndns = FALSE;
		}
	}
}

void dyndns_reply(void)
{
	
}