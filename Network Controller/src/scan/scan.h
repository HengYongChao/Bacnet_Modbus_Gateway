

#ifndef	_SCAN_H_

#define	_SCAN_H_

#include "types.h"

typedef struct _SCAN_DATABASE_
{
	U8_T id;
	U32_T sn;
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