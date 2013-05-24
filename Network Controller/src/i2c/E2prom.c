
#include "e2prom.h"
#include "../cpu/ax11000.h"
//  -------------
//  note:	
// 	1. every time use new chip, should initial e2prom using WINDOWS ISP
//	2. make sure the I2C interrupt vector is turned on.
//  -------------

#define  	USER_BASE_ADDR  0x30   // if use 24c02, the usable range is 0x30 - 0xff, 208 bytes

#if 1

I2C_BUF Read_Data;

static U16_T ADDROFDEV = 0x50;
static U16_T delay_count = 2000;

void E2prom_Initial(void)
{
	U16_T 	i2cpreclk = 0;
	U8_T 	sysclk = 0;
	U32_T 	Sysclk;
	sysclk = AX11000_GetSysClk();
	switch (sysclk)
	{
		case SYS_CLK_100M :
			Sysclk = 100000000;
			i2cpreclk = I2C_STD_100M;
			break;
		case SYS_CLK_50M :
			Sysclk = 50000000;
			i2cpreclk = I2C_STD_50M;
			break;
		case SYS_CLK_25M :
			Sysclk = 25000000;
			i2cpreclk = I2C_STD_25M;
			break;
	}
	I2C_Setup(I2C_ENB|I2C_STANDARD|I2C_MST_IE|I2C_7BIT|I2C_MASTER_MODE, i2cpreclk, 0x005A);
	//E2prom_Erase();
}

U8_T E2prom_Read_Byte(U8_T addr, U8_T *value)
{
	I2C_RdmRead(ADDROFDEV, USER_BASE_ADDR + addr, &Read_Data, 1, I2C_STOP_COND);
	*value = Read_Data.I2cData[0];
	return 1;
}

U8_T E2prom_Read_Byte_From_Absolute_Address(U8_T addr, U8_T *value)
{
	I2C_RdmRead(ADDROFDEV, addr, &Read_Data, 1, I2C_STOP_COND);
	*value = Read_Data.I2cData[0];
	return 1;
}


U8_T E2prom_Read_Int(U8_T addr, U16_T *value)
{
	//U8_T temp,temp1;
//	E2prom_Read_Byte(addr,&temp);
//	E2prom_Read_Byte(addr + 1,&temp1);
//	*value = temp + temp1 * 256;
	I2C_RdmRead(ADDROFDEV, USER_BASE_ADDR + addr, &Read_Data, 2, I2C_STOP_COND);
	*value = Read_Data.I2cData[0];
			   
	return 1;
}

U8_T E2prom_Write_Byte(U8_T addr, U8_T dat)
{
	U8_T result;
	U16_T i;
	result = I2C_ByteWrite(ADDROFDEV, USER_BASE_ADDR + addr, dat, I2C_STOP_COND);
	for(i = 0; i < delay_count; i++) 			_nop_ ();
	return result;
}

U8_T E2prom_Write_Byte_To_Absolute_Address(U8_T addr, U8_T dat)
{
	U8_T result;
	U16_T i;
	result = I2C_ByteWrite(ADDROFDEV, addr, dat, I2C_STOP_COND);
	for(i = 0; i < delay_count; i++) 			_nop_ ();
	return result;
}


U8_T E2prom_Write_Int(U8_T addr, U16_T dat)
{	
	U16_T i;
	U8_T temp;
	temp = (U8_T)dat;   // first low byte
	I2C_ByteWrite(ADDROFDEV, USER_BASE_ADDR + addr, temp, I2C_STOP_COND);	
	for(i = 0; i < delay_count; i++) 			_nop_ ();
	temp = dat >> 8;
	I2C_ByteWrite(ADDROFDEV, USER_BASE_ADDR + addr + 1, temp, I2C_STOP_COND);	
	for(i = 0; i < delay_count; i++) 			_nop_ ();
	return 1;
}

// erase e2prom
U8_T E2prom_Erase(void)
{
	U8_T result;
	U16_T j,i;
	for(j = 0; j < 208; j++) 
	{
		result = I2C_ByteWrite(ADDROFDEV, USER_BASE_ADDR + j, 0xFF, I2C_STOP_COND);
		if(!result) 	return result;
		for(i = 0; i < delay_count; i++) 	_nop_ ();
	}


	return result;
}


#endif













