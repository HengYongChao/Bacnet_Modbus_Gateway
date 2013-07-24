/*#######################################################################################
Connect ARM to MMC/SD 

Copyright (C) 2004 Ulrich Radig

ARM modifications by Ingo Busker 2005
#######################################################################################*/

#ifndef _MMC_H_
 #define _MMC_H_

#include	"reg80390.h"
#include	"types.h"
  





//Prototypes
U8_T mmc_read_byte(void);

void mmc_write_byte(U8_T);

extern void mmc_read_block(U8_T *,U8_T *,U16_T);

extern U8_T mmc_init(void);

extern U8_T mmc_read_sector (U32_T,U8_T *);

extern U8_T mmc_write_sector (U32_T,U8_T *);

extern U8_T mmc_write_command (U8_T *);

extern U8_T mmc_read_csd (U8_T *);

extern U8_T mmc_read_cid (U8_T *);

//set MMC_Chip_Select to high (MMC/SD-Karte Inaktiv)
#define MMC_Disable()   MMC_Chip_Select=1;          //MMC_Write|= (1<<MMC_Chip_Select);

//set MMC_Chip_Select to low (MMC/SD-Karte Aktiv)
#define MMC_Enable()   MMC_Chip_Select=0;          //MMC_Write&=~(1<<MMC_Chip_Select);

//#define nop()  __asm__ __volatile__ ("nop" ::)

#endif //_MMC_H_


