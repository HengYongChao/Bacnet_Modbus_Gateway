
#ifndef	_SCHEDULE_H_

#define	_SCHEDULE_H_


#define MAX_ID					254
#define MAX_WR      			20
#define MAX_AR					16

#define WR_DESCRIPTION_SIZE		31
#define AR_DESCRIPTION_SIZE		29
#define ID_SIZE					3
#define AR_TIME_SIZE			46
#define WR_TIME_SIZE			72
#define SCH_TIME_SIZE			1

#define SCAN_DB_SIZE			5
#define MAX_BACNET				1
#define	BACNET_SIZE				1


#define MAX_DOMAIN_SIZE         32
#define MAX_USERNAME_SIZE       32
#define MAX_PASSWORD_SIZE       32


#define	MAX_INTERVALS_PER_DAY	4
/* the following defintion is for schedule */
#define SCHEDUAL_MODBUS_ADDRESS 200

typedef enum
{
	MODBUS_TIMER_ADDRESS		= SCHEDUAL_MODBUS_ADDRESS, // 200
	
	MODBUS_WR_DESCRIP_FIRST		= MODBUS_TIMER_ADDRESS + 8,
	MODBUS_WR_DESCRIP_LAST		= MODBUS_WR_DESCRIP_FIRST + WR_DESCRIPTION_SIZE * MAX_WR ,	 // 208 + 31*20 = 828
	
	MODBUS_AR_DESCRIP_FIRST		= MODBUS_WR_DESCRIP_LAST ,
	MODBUS_AR_DESCRIP_LAST		= MODBUS_AR_DESCRIP_FIRST +  AR_DESCRIPTION_SIZE * MAX_AR ,	 //828 + 29*16 = 1292
	
	MODBUS_ID_FIRST				= MODBUS_AR_DESCRIP_LAST ,
	MODBUS_ID_LAST				= MODBUS_ID_FIRST + ID_SIZE * MAX_ID ,		  // 1292 + 3*254 = 2054
	
	MODBUS_AR_TIME_FIRST		= MODBUS_ID_LAST ,
	MODBUS_AR_TIME_LAST			= MODBUS_AR_TIME_FIRST + AR_TIME_SIZE * MAX_AR ,    // 2054 + 46*16 = 2790
	
	MODBUS_WR_ONTIME_FIRST		= MODBUS_AR_TIME_LAST ,
	MODBUS_WR_ONTIME_LAST		= MODBUS_WR_ONTIME_FIRST + WR_TIME_SIZE * MAX_WR ,  //2790 + 72*20 = 4230
	
	MODBUS_WR_OFFTIME_FIRST		= MODBUS_WR_ONTIME_LAST ,
	MODBUS_WR_OFFTIME_LAST		= MODBUS_WR_OFFTIME_FIRST + WR_TIME_SIZE * MAX_WR,	//4230 +72*20 = 5670

	MODBUS_SCAN_DB_CTR			= MODBUS_WR_OFFTIME_LAST,
	MODBUS_SCAN_DB_START		= MODBUS_SCAN_DB_CTR + 1,
	MODBUS_SCAN_DB_LAST			= MODBUS_SCAN_DB_START + SCAN_DB_SIZE * MAX_ID,	   //5670 + 5 * 254 = 6940
															/* 1270 */

	MODBUS_GSM_START			= MODBUS_SCAN_DB_LAST,						 // 6941
	MODBUS_GSM_LAST				= MODBUS_GSM_START + 14,					 //lj


	MODBUS_BACNET_START			= MODBUS_GSM_LAST + 62 ,					 // 5956 + 62 = 7014
	MODBUS_BACNET_LAST			= MODBUS_BACNET_START + 1 ,



	// Dyndns	
	MODBUS_DYNDNS_ENABLE,						//7100
	MODBUS_DYNDNS_PROVIDER,						//7101
	MODBUS_DYNDNS_CHECK_IP_EVERY,				//7102
	MODBUS_DYNDNS_FORCE_UPDATE_EVERY,			//7103

	MODBUS_DYNDNS_DOMAIN_NAME_START,													//7135
	MODBUS_DYNDNS_DOMAIN_NAME_END = MODBUS_DYNDNS_DOMAIN_NAME_START + MAX_DOMAIN_SIZE, 	//+32

	MODBUS_DYNDNS_USERNAME_START = MODBUS_DYNDNS_DOMAIN_NAME_END,						//7167
	MODBUS_DYNDNS_USERNAME_END = MODBUS_DYNDNS_USERNAME_START + MAX_USERNAME_SIZE,		//+32
			
	MODBUS_DYNDNS_PASSWORD_START = MODBUS_DYNDNS_USERNAME_END,							//7199
	MODBUS_DYNDNS_PASSWORD_END = MODBUS_DYNDNS_PASSWORD_START + MAX_PASSWORD_SIZE,		//+32

	MODBUS_DYNDNS_LOG_COUNTER = MODBUS_DYNDNS_PASSWORD_END,	//7200
	MODBUS_DYNDNS_LOG_ID,						//7201
	MODBUS_DYNDNS_LOG_CENTURY,					//7202
	MODBUS_DYNDNS_LOG_YEAR,						//7203
	MODBUS_DYNDNS_LOG_MONTH,					//7204
	MODBUS_DYNDNS_LOG_DAY,						//7205
	MODBUS_DYNDNS_LOG_HOUR,						//7206
	MODBUS_DYNDNS_LOG_MIN,						//7207



	MODBUS_TOTAL_PARAMETERS

};

typedef struct //_tagSch_Time
{
	unsigned char centry;
	unsigned char year;
	unsigned char month;
	unsigned char week;
	unsigned char date;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
}Sch_Time;


typedef struct //_tagSTR_WR
{
	union
	{
		unsigned char all[WR_DESCRIPTION_SIZE];
		struct
		{
			unsigned char full_table[20];
			unsigned char lable[8];
			unsigned char holiday1;
			unsigned char holiday2;
			unsigned char flag;	
		/*  flag formate:
			7 		6		5		4		3 		2 		1		0
		  a/m 	value		-		-		-		-		-		-
		*/
		}Desc;
	}UN;
	unsigned char OnTime[WR_TIME_SIZE]; 
	unsigned char OffTime[WR_TIME_SIZE];
}STR_WR; /* weekly routions description */

#define	WR_STRUCT_LENGTH	(WR_DESCRIPTION_SIZE + WR_TIME_SIZE + WR_TIME_SIZE)



typedef struct
{
	union
	{
		unsigned char all[AR_DESCRIPTION_SIZE];
		struct
		{
			unsigned char full_table[20];
			unsigned char lable[8];
			unsigned char flag;
		/*  flag formate:
			7 		6		5		4		3 		2 		1		0
		  a/m 	value		-		-		-		-		-		-
		*/
		}Desc;
	}UN;
	unsigned char Time[AR_TIME_SIZE];
}STR_AR; /* annual roution */

#define	AR_STRUCT_LENGTH	(AR_DESCRIPTION_SIZE + AR_TIME_SIZE)

typedef	union
{
	unsigned char all[ID_SIZE];
	struct
	{
	unsigned char schedule1;
	unsigned char schedule2;
	unsigned char flag;  
	/*  flag formate:
		7 		6		5		4		3 		2 		1		0
	  a/m 	output	state1	state2		-		-		-		-
	*/
	}Str;
}UN_ID; /*config roution */


typedef struct
{
	unsigned char table;
	unsigned char line;
	unsigned char dat[72];
}STR_FLASH;

#define WR_BLOCK_SIZE				1024
#define AR_BLOCK_SIZE				1024
#define ID_BLOCK_SIZE				1536
#define AR_TIME_BLOCK_SIZE			1024
#define INITIALIZE_BLOCK_SIZE		512
 
#define TIME_START_ADDRESS			0X14
#define WR_START_ADDRESS			0X15
#define WR_ON_TIME_START_ADDRESS	0X16
#define WR_OFF_TIME_START_ADDRESS	0X17
#define AR_START_ADDRESS			0X18
#define AR_TIME_START_ADDRESS		0X19
#define ID_START_ADDRESS			0X1a
#define NO_DEFINE_ADDRESS			0xB4DC


extern unsigned char far ar_state_index[2];
extern unsigned char far wr_state_index[3];
extern unsigned char far holiday1_state_index[3];
extern unsigned char far holiday2_state_index[3];

extern unsigned char far output_state_index[32];
extern unsigned char far schedual1_state_index[32];
extern unsigned char far schedual2_state_index[32];
extern bit calibrated_time;

extern STR_FLASH flash;
extern unsigned char bdata REFRESH_STATUS;
extern unsigned char far daylight_enable;
extern unsigned char far daylight_flag;
extern bit BIT_FLAG; // 0 -- run schedule 


extern far STR_WR WR_Roution[MAX_WR];
extern far STR_AR AR_Roution[MAX_AR];
extern far UN_ID ID_Config[MAX_ID];

extern unsigned char far schedule_flag;
extern unsigned char far schedule_id;

void SetBit(unsigned char bit_number, unsigned char *byte);
void ClearBit(unsigned char bit_number, unsigned char *byte);
bit GetBit(unsigned char bit_number, unsigned char *value);
void CheckAnnualRoutines(void);
void CheckWeeklyRoutines(void);
void SendSchedualData(unsigned char id_index, bit output);
void CheckIdRoutines(void);
void CaculateTime(void);

#endif