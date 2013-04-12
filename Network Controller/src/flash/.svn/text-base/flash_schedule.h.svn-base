
typedef enum
{
	//T_TIME = 0, 
	T_WEEK_DES = 0,
	T_WEEK_ONTIME,
	T_WEEK_OFFTIME,
	T_ANNUAL_DES,
	T_ANNUAL_TIME,
	T_ID
};

/* MACRO DECLARATIONS */
typedef struct
{
	U16_T addr;
	U16_T len;
}STR_Flash_POS;


typedef struct
{
	U8_T table;
	U16_T index;
	U8_T flag;
	U32_T len;
	U8_T dat[500];
}STR_flag_flash;


void Flash_Inital(void);
void Flash_Write_Schedule(void);
void Flash_Read_Schedule(void);

