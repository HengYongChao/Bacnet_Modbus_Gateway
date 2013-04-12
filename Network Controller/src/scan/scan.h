

#ifndef	_SCAN_H_

#define	_SCAN_H_

#include "types.h"

typedef struct _SCAN_DATABASE_
{
	U8_T id;
	U32_T sn; 
	
									 		 //Tstat6
//	U8_T product_model;						 //7
//	U8_T cooling_setpoint_value;	 		 //348
//	U8_T setpoint_value;					 //345
//	U8_T heating_setpoint_value;			 //349
//	U8_T rom_temperature;		  		 	 //121 
//	U8_T mode_of_tstat;			  		     //102
//	U8_T output_status;						 //209
//	U8_T night_heating_deaband;				 //352
//	U8_T night_cooling_deaband;				 //353
//	U8_T night_heating_setpoint_value;		 //354
//	U8_T night_cooling_setpoint_value;		 //355
//	U8_T occupied_status;			 		 //109.0
//	U8_T unoccupied_override_timer;	 		 //111


} SCAN_DB;

#define	NONE_ID						0
#define	UNIQUE_ID					1
#define	MULTIPLE_ID					2
#define	UNIQUE_ID_FROM_MULTIPLE		3
#define	ASSIGN_ID					4


#define	SCAN_BINSEARCH			1
#define	SCAN_ASSIGN_ID_WITH_SN	2


extern U8_T far scan_state;
extern U8_T far scan_response_state;
extern SCAN_DB far current_db;
extern SCAN_DB far scan_db[254];
extern U8_T db_ctr;


void init_scan(void);
void scan_tstat(void);
//U8_T check_id_in_database(U8_T id, U32_T sn);

#endif