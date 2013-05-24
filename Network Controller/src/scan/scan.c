
#include <stdlib.h>
#include <string.h>
#include "scan.h"
#include "../main/main.h"
#include "../flash/flash.h"
#include "../schedule/schedule.h"

extern void InitCRC16(void);

extern U8_T ChangeFlash;

extern U8_T far CRClo;
extern U8_T far CRChi;
extern void CRC16_Tstat(U8_T ch);
extern U8_T Sever_Order;
extern U8_T far Para[400];

SCAN_DB far scan_db[MAX_ID];
SCAN_DB far current_db;
U8_T db_ctr;

U8_T far scan_state;
U8_T far scan_response_state;

U8_T far online[32] = {0};
U8_T far occupy[32] = {0};

static U8_T nc_id;
static U32_T nc_sn;

static U8_T scan_db_changed = FALSE;

void send_scan_cmd(U8_T max_id, U8_T min_id)
{	
	U8_T i, buf[6];
	
	buf[0] = 0xff;
	buf[1] = 0x19;
	buf[2] = max_id;
	buf[3] = min_id;

	InitCRC16();
	for(i = 0; i < 4; i++)
		CRC16_Tstat(buf[i]);

	buf[4] = CRChi;
	buf[5] = CRClo;

	scan_response_state = NONE_ID;
	Sever_Order = SERVER_SCAN;

	Tx_To_Tstat(buf, 6);
}

#define	DELAY_TICKS		50
U8_T wait_response(void)
{
	U8_T i;
	for(i = 0; i < DELAY_TICKS; i++)
	{
		if(scan_response_state != NONE_ID)
		{
			break;
		}
		else
		{
			OSDelay(2);
		}
	}

	return scan_response_state;
}

void assignment_id_with_sn(U8_T old_id, U8_T new_id, U32_T current_sn)
{
	U8_T i, buf[12];
	
	buf[0] = old_id;
	buf[1] = 0x06;
	buf[2] = 0;
	buf[3] = 0x0a;	//MODBUS_ADDRESS_PLUG_N_PLAY = 10
	buf[4] = 0x55;
	buf[5] = new_id;

	buf[6] = (U8_T)(current_sn >> 24);
	buf[7] = (U8_T)(current_sn >> 16);
	buf[8] = (U8_T)(current_sn >> 8);
	buf[9] = (U8_T)current_sn;

	InitCRC16();
	for(i = 0; i < 10; i++)
		CRC16_Tstat(buf[i]);

	buf[10] = CRChi;
	buf[11] = CRClo;

	scan_state = SCAN_ASSIGN_ID_WITH_SN;
	scan_response_state = NONE_ID;
	Sever_Order = SERVER_SCAN;
	Tx_To_Tstat(buf, 12);
}

U8_T get_idle_id(void)
{
	U8_T i;
	for(i = 1; i <= MAX_ID; i++)
	{
		if(online[(i - 1) / 8] & (1 << ((i - 1) % 8)) == 0)
			return i;
	}
	return 0xff;
}

void check_id_in_database(U8_T id, U32_T sn)
{
	if(online[(id - 1) / 8] & (1 << ((id - 1) % 8))) // in the database
	{
		U8_T i;
		for(i = 0; i < db_ctr; i++)
		{
			if(id == scan_db[i].id) // id already in the database
			{
				if(sn != scan_db[i].sn) // if there exist the same id with defferent sn, push it into the occupy list
				{
					occupy[(id - 1) / 8] |= 1 << ((id - 1) % 8);
				}
				break;
			}
			// if the device is already in the database, return without doing anything
		}
	}
	else
	{
		online[(id - 1) / 8] |= 1 << ((id - 1) % 8);
		scan_db[db_ctr].id = id;
		scan_db[db_ctr].sn = sn;
		db_ctr++;
		scan_db_changed = TRUE;
	}
}



void bin_search(U8_T min_id, U8_T max_id) reentrant
{
	

	if(min_id > max_id)	return;

	scan_state = SCAN_BINSEARCH;
	send_scan_cmd(max_id, min_id);


	switch(wait_response())	// wait for response from tstats scan command
	{
		case UNIQUE_ID:
			// unique id means it is the only id in the range.
			// if the id is already in the database, set it occupy and then change the id with sn in the dealwith_conflict_id routine.
//			Uart0_Tx("\n\rUNIQUE ID!", 12);
			check_id_in_database(current_db.id, current_db.sn);			
			break;
		case MULTIPLE_ID:
			// multiple id means there is more than one id in the range.
			// if the min_id == max_id, there is same id, set the id occupy and return
			// if the min_id != max_id, there is multi id in the range, divide the range and do the sub scan
//			Uart0_Tx("\n\rMULTIPLE ID!", 14);
			if(min_id == max_id)
			{
				occupy[(min_id - 1) / 8] |= 1 << ((min_id - 1) % 8);
			}
			else
			{
				bin_search(min_id, (U8_T)(((U16_T)min_id + (U16_T)max_id) / 2));
				bin_search((U8_T)(((U16_T)min_id + (U16_T)max_id) / 2) + 1, max_id);
			}
			break;
		case UNIQUE_ID_FROM_MULTIPLE:
			// there are multiple ids in the range, but the fisrt reply is good.
//			Uart0_Tx("\n\rUNIQUE_ID_FROM_MULTIPLE!", 26);
			check_id_in_database(current_db.id, current_db.sn);
			if(min_id == max_id)
			{
				occupy[(min_id - 1) / 8] |= 1 << ((min_id - 1) % 8);
			}
			else
			{
				bin_search(min_id, (U8_T)(((U16_T)min_id + (U16_T)max_id) / 2));
				bin_search((U8_T)(((U16_T)min_id + (U16_T)max_id) / 2) + 1, max_id);
			}
			break;
		case NONE_ID:
			// none id means there is not id in the range
//			Uart0_Tx("\n\rNONE ID!", 10);
			break;
	}

	return;
}

void dealwith_conflict_id(void)
{
	U8_T occupy_id = 1;
	U8_T idle_id, i;
	U8_T status;

	while(1)
	{
		if(occupy[(occupy_id - 1) / 8] & (1 << ((occupy_id - 1) % 8)))
		{
			idle_id = get_idle_id();

			scan_state = SCAN_BINSEARCH;
			send_scan_cmd(occupy_id, occupy_id); // get the seperate sn
			status = wait_response();

			if(status == UNIQUE_ID) // if unique, there is not occupied at this id.
			{
				occupy[(occupy_id - 1) / 8] &= ~(1 << ((occupy_id - 1) % 8));
			}
			else if(status == UNIQUE_ID_FROM_MULTIPLE)
			{
				for(i = 0; i < db_ctr; i++)
				{
					if(current_db.id == scan_db[i].id)
					{
						if(current_db.sn != scan_db[i].sn)	// get new device
						{
							assignment_id_with_sn(current_db.id, idle_id, current_db.sn); // assign idle id with sn to this occupy device.
							wait_response();
							if(scan_response_state == ASSIGN_ID)
							{
								online[(idle_id - 1) / 8] |= 1 << ((idle_id - 1) % 8);
								scan_db_changed = TRUE;
							}
						}
						break;
					}
				}
				continue;
			}
			else if(status == MULTIPLE_ID)
			{
				continue;
			}
			else
			{
				continue;
			}
		}
		
		occupy_id++;
		if(occupy_id == 0xff) break;
	}
}

void scan_tstat(void)
{
	U8_T cnt[5];
	
	bin_search(1, 254);
	dealwith_conflict_id();

	cnt[0] =  db_ctr;
//	Uart0_Tx(cnt, 1);


	if(scan_db_changed == TRUE)
	{
		scan_db_changed = FALSE;
		ChangeFlash = 1;
	}
}

// read from flash to get the init online status
void init_scan(void)
{
	U8_T i;
	U8_T is_nc_in_db = FALSE;
	memset(online, 0, 32);
	memset(occupy, 0, 32);
	db_ctr = 0;
	nc_id = Para[13];
	nc_sn = ((U32_T)Para[7] << 24) | ((U32_T)Para[5] << 16) | ((U32_T)Para[3] << 8) | Para[1];

	for(i = 0; i < MAX_ID; i++)
	{
		if((scan_db[i].id != 0x00) && (scan_db[i].id != 0xff))
		{
			online[(scan_db[i].id - 1) / 8] |= (1 << ((scan_db[i].id - 1) % 8));
			db_ctr++;
			if((scan_db[i].id == nc_id) && (scan_db[i].sn == nc_sn))
				is_nc_in_db = TRUE;
		}			
		else
		{
			break;
		}
	}

	if((db_ctr == 0) || (is_nc_in_db == FALSE))
	{
		scan_db[db_ctr].id = nc_id;
		scan_db[db_ctr].sn = nc_sn;
		online[(nc_id - 1) / 8] |= (1 << ((nc_id - 1) % 8));
		db_ctr++;
		ChangeFlash = 1;
	}
}