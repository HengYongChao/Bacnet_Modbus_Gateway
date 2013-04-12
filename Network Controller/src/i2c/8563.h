#ifndef _8563_H_
#define _8563_H_



#define  PCF_SEC  0x02
#define  PCF_MIN  0x03
#define  PCF_HOUR  0x04
#define  PCF_DAY  0x05
#define  PCF_WEEK  0x06
#define  PCF_MON  0x07
#define  PCF_YEAR  0x08

typedef struct 
{
	union
	{
		U8_T Setime[8];
		struct
		{
//			U8_T  sec;
//			U8_T  min;
//			U8_T  hour;
//			U8_T  day;
//			U8_T  dayofweek;
//			U8_T  month;
//			U8_T  year;
//			U8_T  centary;
			U8_T  centary;
			U8_T  year; 
			U8_T  month;
			U8_T  dayofweek;
			U8_T  day;
			U8_T  hour;
			U8_T  min;
			U8_T  sec;
		}Current;
	}UN;  
}STR_CLK;


extern STR_CLK Time;

void Initial_Clock(void);
U8_T Read_Clock(U8_T regaddr);
U8_T Set_Clock(U8_T addr,U8_T dat);

#endif

