/*
*********************************************************************************
*     Copyright (c) 2005   ASIX Electronic Corporation      All rights reserved.
*
*     This is unpublished proprietary source code of ASIX Electronic Corporation
*
*     The copyright notice above does not evidence any actual or intended
*     publication of such source code.
*********************************************************************************
*/
/*================================================================================
* Module Name : temperature.c
* Purpose     : 
* Author      : Louis Su
* Date        : 
* Notes       :
* $Log$
*================================================================================
*/

/* INCLUDE FILE DECLARATIONS */

#include	"types.h"
#include	"reg80390.h"
#include	"onewire.h"
#include	"onewireapi.h"
#include	"ax11000.h"
//#include	"buffer.h"
#include	"temperature.h"
#include    <intrins.h>
#include	<stdio.h>
/* STATIC VARIABLE DECLARATIONS */
static	char tr[10];
/* LOCAL SUBPROGRAM DECLARATIONS */

/* LOCAL SUBPROGRAM BODIES */

/* EXPORTED SUBPROGRAM BODIES */

/*
*--------------------------------------------------------------------------------
* int OW_Temprature_GET(void)
* Purpose : test ONEWIRE device
* Params  : 
* Returns : TRUE - successful
* Note    :
*--------------------------------------------------------------------------------
*/

char * OW_Temprature_GET(void)
{

	U8_T 	Read_Data[9];
	U8_T 	i;
	U16_T	temp;
	float	temperature;

	for(i=0; i<9; i++) {
		Read_Data[i] = 0;
	}

	/* CONVERT */
	if (!ONEWIRE_Reset())
		return FALSE;
	i = SKIP_ROM;
	ONEWIRE_ByteXmit(i);
	i = CONVERT_T;
	ONEWIRE_ByteXmit(i);
	/* end of convert */

	/* ReadScratchpad */
	if (!ONEWIRE_Reset())
		return FALSE;
	i = SKIP_ROM;
	ONEWIRE_ByteXmit(i);
	i = READ_SCRPAD;
	ONEWIRE_ByteXmit(i);
	Read_Data[0] = ONEWIRE_ByteRcvr();
	Read_Data[1] = ONEWIRE_ByteRcvr();
	/* end of ReadScratchpad */

	temp = Read_Data[0];
	temp |= Read_Data[1] << 8;

	if(Read_Data[1] & 0xf0) {
		temperature = (~temp + 1) * 0.0625;
		sprintf (tr, "-%.4f", temperature);
	} else {
		temperature = temp * 0.0625;
		sprintf (tr, "%.4f", temperature);
	}
	return tr;
}

void OW_Temprature_init(void)
{
	switch (AX11000_GetSysClk())
	{
		case SCS_100M :
			/* enable presence detect, clock enable,100MHz */
			ONEWIRE_Setup(0, 0, OW_PDI_ENB, OW_CLK_ENB|OW_DIV2|OW_DIV0|OW_PRE0);
			break;
		case SCS_50M :
			/* enable presence detect, clock enable, 50MHz */
			ONEWIRE_Setup(0, 0, OW_PDI_ENB, OW_CLK_ENB|OW_DIV2|OW_PRE0);
			break;
		case SCS_25M :
		default:
			/* enable presence detect, clock enable, 25MHz */
			ONEWIRE_Setup(0, 0, OW_PDI_ENB, OW_CLK_ENB|OW_DIV1|OW_DIV0|OW_PRE0);
			break;
	}
}