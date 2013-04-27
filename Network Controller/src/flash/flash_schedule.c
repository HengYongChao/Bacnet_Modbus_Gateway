#include "flash.h"
#include "flash_schedule.h"
#include "schedule.h"
#include "../scan/scan.h"
#include "../gsm/gsm.h"
#include <string.h>

STR_FLASH flash;
STR_Flash_POS xdata Flash_Position[18] /*_at_ 0x800*/;

static U8_T far tempbuf[1500] = {0};

U8_T bacnet_id;
extern BOOL  MODBUS_OR_BACNET_FUNCTION_SELECT_ON_UART0;
extern U8_T far Para[400]; 

/* caclulate detailed position for every table */
void Flash_Inital(void)
{
	U8_T loop;
	U16_T baseAddr;
	U16_T len;
	for(loop = 0; loop < T_TOTAL; loop++)
	{
		switch(loop)
		{
			case T_WEEK_DES:	
				baseAddr = 6000;
				len = WR_DESCRIPTION_SIZE * MAX_WR;	// 31*20
				break;
			case T_WEEK_ONTIME:
				baseAddr += len;
				len = WR_TIME_SIZE * MAX_WR;		// 72*20
				break;
			case T_WEEK_OFFTIME:
				baseAddr += len;
				len = WR_TIME_SIZE * MAX_WR;		// 72*20
				break;
			case T_ANNUAL_DES:
				baseAddr += len;
				len = AR_DESCRIPTION_SIZE * MAX_AR;	// 29*16
				break;
			case T_ANNUAL_TIME:
				baseAddr += len;
				len = AR_TIME_SIZE * MAX_AR;		// 46*16
				break;
			case T_ID:
				baseAddr += len;
				len = ID_SIZE * MAX_ID;				// 3*254
				break;
			case T_SCAN:
				baseAddr += len;
				len = SCAN_DB_SIZE * MAX_ID;		// 5*254
				break;	
				
			case T_BACNET:
				baseAddr += len;
				len = MAX_BACNET ;	 				//1*1	
				break;
			case T_GSM:
				baseAddr += len;
				len = PHONE_NUM_SIZE;				// 14	
				
			case T_FEATURE_SEL:
				baseAddr += len;	
				len = CHIOCE_FEATURE_LEN;			  	//1
									
			default:
				break;
		}
		Flash_Position[loop].addr = baseAddr;
		Flash_Position[loop].len = len;
	}	
}

void Flash_Write_Schedule(void)
{
	STR_flag_flash ptr_flash;
	U16_T base_addr;
	U8_T loop;
	U16_T loop1, loop2;

 /* only the first block, erase memory */
	IntFlashErase(ERA_RUN, 0x70000);	
	IntFlashWriteByte(0x70000 + 0xfff0, 0x55);
	MassFlashWrite(0, Para, 400); //LHN add

	ptr_flash.index = 0;

	for(loop = 0; loop < T_TOTAL; loop++)
	{
		ptr_flash.table = loop;	
		
		ptr_flash.len = Flash_Position[loop].len;
		base_addr = Flash_Position[loop].addr;
		
		switch(loop)
		{			
			case T_WEEK_DES:
				for(loop1 = 0; loop1 < MAX_WR; loop1++)
				{
					memcpy(&tempbuf[WR_DESCRIPTION_SIZE * loop1], WR_Roution[loop1].UN.all, WR_DESCRIPTION_SIZE);					
				}
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2, tempbuf[loop2]);	
				break;
			case T_WEEK_ONTIME:
				for(loop1 = 0; loop1 < MAX_WR; loop1++)
				{
					memcpy(&tempbuf[WR_TIME_SIZE * loop1], WR_Roution[loop1].OnTime, WR_TIME_SIZE);					
				}
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2, tempbuf[loop2]);
				break;
			case T_WEEK_OFFTIME:
				for(loop1 = 0;loop1 < MAX_WR;loop1++)
				{
					memcpy(&tempbuf[WR_TIME_SIZE * loop1], WR_Roution[loop1].OffTime, WR_TIME_SIZE);					
				}
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2, tempbuf[loop2]);		
				break;
			case T_ANNUAL_DES:
				for(loop1 = 0; loop1 < MAX_AR; loop1++)
				{
					memcpy(&tempbuf[AR_DESCRIPTION_SIZE * loop1], AR_Roution[loop1].UN.all, AR_DESCRIPTION_SIZE);					
				}
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2, tempbuf[loop2]);		
				break;
			case T_ANNUAL_TIME:
				for(loop1 = 0; loop1 < MAX_AR; loop1++)
				{
					memcpy(&tempbuf[AR_TIME_SIZE * loop1], AR_Roution[loop1].Time, AR_TIME_SIZE);					
				}
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2, tempbuf[loop2]);		
				break;

			case T_ID:
				for(loop1 = 0; loop1 < MAX_ID; loop1++)
				{
					memcpy(&tempbuf[ID_SIZE * loop1], ID_Config[loop1].all, ID_SIZE);					
				}
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2, tempbuf[loop2]);		
				break;
			case T_SCAN:
				for(loop1 = 0; loop1 < MAX_ID; loop1++)
				{
					memcpy(&tempbuf[SCAN_DB_SIZE * loop1], (U8_T *)&scan_db[loop1], SCAN_DB_SIZE);					
				}
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2, tempbuf[loop2]);
				break;
/*******************************************************************************************/
			case T_BACNET:
				for(loop1 = 0; loop1 < MAX_BACNET; loop1++)
				{
					memcpy(&tempbuf[BACNET_SIZE * loop1], (U8_T *)&bacnet_id, BACNET_SIZE);					
				}
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2, tempbuf[loop2]);
				break;
/*=========================================================================================*/
			case T_GSM:
				for(loop1 = 0; loop1 < PHONE_NUM_SIZE; loop1++)
				{
					memcpy(&tempbuf[loop1], &phoneNumber[loop1], 1);
				}
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2, tempbuf[loop2]);
				break;
/*********************************************************************************************/
//			case T_FEATURE_SEL:
//				 for(loop1 = 0; loop1 < CHIOCE_FEATURE_LEN; loop1++)
//				 {
//				   memcpy(&tempbuf[loop1], MODBUS_OR_BACNET_FUNCTION_SELECT_ON_UART0, 1);
//				 }
//				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
//					IntFlashWriteByte(0x70000 + base_addr + loop2, tempbuf[loop2]);
//				break;

 			default:	
				break;
		
		}
	}

}

void Flash_Read_Schedule(void)
{
	STR_flag_flash ptr_flash;
	U16_T base_addr;
	U8_T loop;
	U16_T loop2, loop1;

	ptr_flash.index = 0;
	for(loop = 0; loop < T_TOTAL; loop++)
	{
		ptr_flash.table = loop;	
		
		ptr_flash.len = Flash_Position[loop].len;
		base_addr = Flash_Position[loop].addr;
		switch(loop)
		{			
			case T_WEEK_DES:
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2, &tempbuf[loop2]);
				for(loop1 = 0; loop1 < MAX_WR; loop1++)
				{
					memcpy(WR_Roution[loop1].UN.all, &tempbuf[WR_DESCRIPTION_SIZE * loop1], WR_DESCRIPTION_SIZE);					
				}
				break;
			case T_WEEK_ONTIME:
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2, &tempbuf[loop2]);
				
				for(loop1 = 0; loop1 < MAX_WR; loop1++)
				{
					memcpy(&WR_Roution[loop1].OnTime, &tempbuf[WR_TIME_SIZE * loop1], WR_TIME_SIZE);					
				}
				break;
			case T_WEEK_OFFTIME:
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2, &tempbuf[loop2]);
				for(loop1 = 0; loop1 < MAX_WR; loop1++)
				{
					memcpy(WR_Roution[loop1].OffTime, &tempbuf[WR_TIME_SIZE * loop1], WR_TIME_SIZE);					
				}
				break;
			case T_ANNUAL_DES:
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2, &tempbuf[loop2]);
				for(loop1 = 0; loop1 < MAX_AR; loop1++)
				{
					memcpy(AR_Roution[loop1].UN.all, &tempbuf[AR_DESCRIPTION_SIZE * loop1], AR_DESCRIPTION_SIZE);					
				}
				break;
			case T_ANNUAL_TIME:
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2, &tempbuf[loop2]);
				for(loop1 = 0; loop1 < MAX_AR; loop1++)
				{
					memcpy(AR_Roution[loop1].Time, &tempbuf[AR_TIME_SIZE * loop1], AR_TIME_SIZE);					
				}
				break;
			case T_ID:
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2, &tempbuf[loop2]);
				for(loop1 = 0; loop1 < MAX_ID; loop1++)
				{
					memcpy(ID_Config[loop1].all, &tempbuf[ID_SIZE * loop1], ID_SIZE);					
				}
				break;
			case T_SCAN:
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2, &tempbuf[loop2]);
				for(loop1 = 0; loop1 < MAX_ID; loop1++)
				{
					memcpy((U8_T *)&scan_db[loop1], &tempbuf[SCAN_DB_SIZE * loop1], SCAN_DB_SIZE);					
				}
				break;
/***********************************************************************************************/
			case T_BACNET:
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2, &tempbuf[loop2]);
				for(loop1 = 0; loop1 < MAX_BACNET; loop1++)
				{
					memcpy((U8_T *)&bacnet_id, &tempbuf[BACNET_SIZE * loop1], BACNET_SIZE);					
				}
				break;
/*--------------------------------------------------------------------------------------------*/
			case T_GSM:
				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2, &tempbuf[loop2]);
				for(loop1 = 0; loop1 < PHONE_NUM_SIZE; loop1++)
				{
					memcpy(&phoneNumber[loop1], &tempbuf[ loop1], 1);					
				}
				break;
//		    case T_FEATURE_SEL:
//				for(loop2 = 0; loop2 < ptr_flash.len; loop2++)
//					IntFlashReadByte(0x70000 + base_addr + loop2, &tempbuf[loop2]);
//
//				for(loop1 = 0; loop1 < CHIOCE_FEATURE_LEN; loop1++)
//				{
//					memcpy(MODBUS_OR_BACNET_FUNCTION_SELECT_ON_UART0, &tempbuf[ loop1], 1);					
//				}
//				break;


			default:
				break;
		}
	}
}


