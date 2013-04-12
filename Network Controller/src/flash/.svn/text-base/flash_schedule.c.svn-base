#include "flash.h"
#include "flash_schedule.h"
#include "schedule.h"
#include 	<string.h>

STR_FLASH flash;
STR_Flash_POS xdata Flash_Position[18] /*_at_ 0x800*/;




extern U8_T  far Para[400]; 

/* caclulate detailed position for every table */
void Flash_Inital(void)
{
	U8_T loop;
	U16_T baseAddr;
	
	U16_T  len;
	for(loop = 0;loop < 6;loop++)
	{
		switch(loop)
		{
			case T_WEEK_DES:	
				baseAddr = 6000;
				len = WR_DESCRIPTION_SIZE * MAX_WR; // 31*20
				break;
			case T_WEEK_ONTIME:
				baseAddr += len;
				len = WR_TIME_SIZE * MAX_WR; // 72*20
				break;
			case T_WEEK_OFFTIME:
				baseAddr += len;
				len = WR_TIME_SIZE * MAX_WR; // 72*20
				break;
			case T_ANNUAL_DES:
				baseAddr += len;
				len = AR_DESCRIPTION_SIZE * MAX_AR; // 29*16
				break;
			case T_ANNUAL_TIME:
				baseAddr += len;
				len = AR_TIME_SIZE * MAX_AR;  // 46*16
				break;
			case T_ID:

				baseAddr += len;
				len = ID_SIZE * MAX_ID; // 3*254
				break;			
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
	U16_T loop1,loop2;
//	U16_T i;
	U8_T far tempbuf[500];
 /* only the first block, erase memory */
	IntFlashErase(ERA_RUN, 0x70000);	
	IntFlashWriteByte(0x70000 + 0xfff0,0x55);
	MassFlashWrite(0,Para,400); //LHN add

	ptr_flash.index = 0;

	for(loop = 0;loop < 6 ;loop++)
	{
		ptr_flash.table = loop;	
		
		ptr_flash.len = Flash_Position[loop].len;
		base_addr = Flash_Position[loop].addr;
		
		switch(loop)
		{			
			case T_WEEK_DES:
				for(loop1 = 0;loop1 < MAX_WR;loop1++)
				{
					memcpy(&tempbuf[WR_DESCRIPTION_SIZE * loop1], WR_Roution[loop1].UN.all, WR_DESCRIPTION_SIZE);					
				}
				for(loop2 = 0;loop2 < ptr_flash.len;loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2, tempbuf[loop2]);	
				break;
			case T_WEEK_ONTIME:
				for(loop1 = 0;loop1 < MAX_WR;loop1++)
				{
					memcpy(&tempbuf[WR_TIME_SIZE * loop1], WR_Roution[loop1].OnTime,WR_TIME_SIZE);					
				}
				for(loop2 = 0;loop2 < ptr_flash.len;loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2,tempbuf[loop2]);
				break;
			case T_WEEK_OFFTIME:
				for(loop1 = 0;loop1 < MAX_WR;loop1++)
				{
					memcpy(&tempbuf[WR_TIME_SIZE * loop1],WR_Roution[loop1].OffTime,WR_TIME_SIZE);					
				}
				for(loop2 = 0;loop2 < ptr_flash.len;loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2,tempbuf[loop2]);		
				break;
			case T_ANNUAL_DES:
				for(loop1 = 0;loop1 < MAX_AR;loop1++)
				{
					memcpy(&tempbuf[AR_DESCRIPTION_SIZE * loop1],AR_Roution[loop1].UN.all,AR_DESCRIPTION_SIZE);					
				}
				for(loop2 = 0;loop2 < ptr_flash.len;loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2,tempbuf[loop2]);		
				break;
			case T_ANNUAL_TIME:
				for(loop1 = 0;loop1 < MAX_AR;loop1++)
				{
					memcpy(&tempbuf[AR_TIME_SIZE * loop1],AR_Roution[loop1].Time,AR_TIME_SIZE);					
				}
				for(loop2 = 0;loop2 < ptr_flash.len;loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2,tempbuf[loop2]);		
				break;

			case T_ID:
				for(loop1 = 0;loop1 < MAX_ID;loop1++)
				{
					memcpy(&tempbuf[ID_SIZE * loop1],ID_Config[loop1].all,ID_SIZE);					
				}
				for(loop2 = 0;loop2 < ptr_flash.len;loop2++)
					IntFlashWriteByte(0x70000 + base_addr + loop2,tempbuf[loop2]);		
				break;
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
	U16_T loop2,loop1;
	U8_T far tempbuf[500];

	ptr_flash.index = 0;
	for(loop = 0;loop < 6;loop++)
	{
		ptr_flash.table = loop;	
		
		ptr_flash.len = Flash_Position[loop].len;
		base_addr = Flash_Position[loop].addr;
		switch(loop)
		{			
			case T_WEEK_DES:
				for(loop2 = 0;loop2 < ptr_flash.len;loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2,&tempbuf[loop2]);
				for(loop1 = 0;loop1 < MAX_WR;loop1++)
				{
					memcpy(WR_Roution[loop1].UN.all,&tempbuf[WR_DESCRIPTION_SIZE * loop1],WR_DESCRIPTION_SIZE);					
				}
				break;
			case T_WEEK_ONTIME:
				for(loop2 = 0;loop2 < ptr_flash.len;loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2,&tempbuf[loop2]);
				
				for(loop1 = 0;loop1 < MAX_WR;loop1++)
				{
					memcpy(&WR_Roution[loop1].OnTime,&tempbuf[WR_TIME_SIZE * loop1],WR_TIME_SIZE);					
				}
				break;
			case T_WEEK_OFFTIME:
				for(loop2 = 0;loop2 < ptr_flash.len;loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2,&tempbuf[loop2]);
				for(loop1 = 0;loop1 < MAX_WR;loop1++)
				{
					memcpy(WR_Roution[loop1].OffTime,&tempbuf[WR_TIME_SIZE * loop1],WR_TIME_SIZE);					
				}
				break;
			case T_ANNUAL_DES:
				for(loop2 = 0;loop2 < ptr_flash.len;loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2,&tempbuf[loop2]);
				for(loop1 = 0;loop1 < MAX_AR;loop1++)
				{
					memcpy(AR_Roution[loop1].UN.all,&tempbuf[AR_DESCRIPTION_SIZE * loop1],AR_DESCRIPTION_SIZE);					
				}
				break;
			case T_ANNUAL_TIME:
				for(loop2 = 0;loop2 < ptr_flash.len;loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2,&tempbuf[loop2]);
				for(loop1 = 0;loop1 < MAX_AR;loop1++)
				{
					memcpy(AR_Roution[loop1].Time,&tempbuf[AR_TIME_SIZE * loop1],AR_TIME_SIZE);					
				}
				break;
			case T_ID:
				for(loop2 = 0;loop2 < ptr_flash.len;loop2++)
					IntFlashReadByte(0x70000 + base_addr + loop2,&tempbuf[loop2]);
				for(loop1 = 0;loop1 < MAX_ID;loop1++)
				{
					memcpy(ID_Config[loop1].all,&tempbuf[ID_SIZE * loop1],ID_SIZE);					
				}
				break;
			default:
				break;
		}
	}
}


