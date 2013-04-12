#ifndef	E2PROM_H

#define	E2PROM_H

#include 	"../cpu/types.h"
#include	"i2c.h"
#include	"i2capi.h"
#include    <intrins.h>
#include    <string.h>
#include	"../cpu/interrupt.h"


#define ERASE_EVENT	1
#define WRITE_EVENT	2
#define READ_EVENT	3

void E2prom_Initial(void);
U8_T E2prom_Read_Byte(U8_T addr,U8_T *value);
U8_T E2prom_Read_Int(U8_T addr,U16_T *value);
U8_T E2prom_Write_Byte(U8_T addr,U8_T dat);
U8_T E2prom_Write_Int(U8_T addr,U16_T dat);
U8_T E2prom_Erase(void);
U8_T E2prom_Write_Byte_To_Absolute_Address(U8_T addr, U8_T dat);
U8_T E2prom_Read_Byte_From_Absolute_Address(U8_T addr, U8_T *value);

#endif
