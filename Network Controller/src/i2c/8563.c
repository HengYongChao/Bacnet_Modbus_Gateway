#include	<stdio.h>
#include	"reg80390.h"
#include	"types.h"
#include	"buffer.h"
#include	"i2c.h"
#include	"i2capi.h"
#include    "8563.h"

STR_CLK Time;
extern U8_T  far Para[400]; 


U8_T BcdToHex(U8_T byte)  
{
	U8_T i,j;                 
    i = byte >> 4;
	j = byte & 0x0f;     
	return i*10+j;
}


U8_T HexToBcd(U8_T byte)
{
 	U8_T i,j;
	i = byte / 10;
	j = byte % 10;
 	return  (i << 4) + j ;
}


U8_T Set_Clock(U8_T addr,U8_T dat)
{
	U8_T  result;
	U16_T  i;
	result = I2C_ByteWrite(0x51, addr, HexToBcd(dat), I2C_STOP_COND);
	for(i = 0; i < 2500; i++) 	;
	return result;
}




void Initial_Clock(void)
{
	//U16_T i;

	Set_Clock(0,0);
	//for(i=0;i<500;i++);
	Set_Clock(1,0);
	//for(i=0;i<500;i++);
	Set_Clock(2,Time.UN.Setime[7]); //sec
	//for(i=0;i<500;i++);
	Set_Clock(3,Time.UN.Setime[6]);//min
	//for(i=0;i<500;i++);
	Set_Clock(4,Time.UN.Setime[5]);//hour
	//for(i=0;i<300;i++);
	Set_Clock(5,Time.UN.Setime[4]);//day
	//for(i=0;i<300;i++);
	Set_Clock(6,Time.UN.Setime[3]);//which
	//for(i=0;i<300;i++);
	Set_Clock(7,Time.UN.Setime[2]);//month
	//for(i=0;i<300;i++);
	Set_Clock(8,Time.UN.Setime[1]);//year
}

U8_T Read_Clock(U8_T regaddr)
{
	U8_T i, temp[7];
	I2C_BUF Read_Dat;  
	
	I2C_RdmRead(0x51, regaddr, &Read_Dat, 7, I2C_STOP_COND);
	
	for(i = 0; i < 7; i++)
		temp[i] = Read_Dat.I2cData[i];
	
	if(temp[5] & 0x80)
		Time.UN.Current.centary = 19;
	else
		Time.UN.Current.centary = 20;
	
	temp[0] = temp[0] & 0x7f;//sec
	temp[1] = temp[1] & 0x7f;//min
	temp[2] = temp[2] & 0x3f;//hour
	temp[3] = temp[3] & 0x3f;//day
	temp[4] = temp[4] & 0x07;//day of week
	temp[5] = temp[5] & 0x1f; //month
	temp[6] = temp[6] & 0xff; //month
	
	Time.UN.Current.sec = BcdToHex(temp[0]);//  Para[407]= 
	Time.UN.Current.min = BcdToHex(temp[1]);// Para[406]= 
	Time.UN.Current.hour = BcdToHex(temp[2]);// Para[405]= 
	Time.UN.Current.day = BcdToHex(temp[3]);// Para[404]= 
	Time.UN.Current.dayofweek = BcdToHex(temp[4]);// Para[403]= 
	Time.UN.Current.month = BcdToHex(temp[5]);// Para[402]= 
	Time.UN.Current.year = BcdToHex(temp[6]);// Para[401]= 
//	Time.UN.Current.centary   = 20;                // Para[400]= 
	
	return 1;
}