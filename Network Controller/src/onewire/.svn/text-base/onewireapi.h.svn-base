/*
 *********************************************************************************
 *     Copyright (c) 2005	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 *********************************************************************************
 */
/*================================================================================
 * Module Name : onewireapi.h
 * Purpose     : 
 * Author      : Robin Lee
 * Date        : 2005-01-12
 * Notes       :
 * $Log$
 *================================================================================
 */
#ifndef ONEWIREAPI_H
#define ONEWIREAPI_H

/* INCLUDE FILE DECLARATIONS */
#include	"onewire_cfg.h"


/* NAMING CONSTANT DECLARATIONS */


/* MACRO DECLARATIONS */


/* TYPE DECLARATIONS */


/* GLOBAL VARIABLES */


/* EXPORTED SUBPROGRAM SPECIFICATIONS */
BOOL	ONEWIRE_WriteScratchpad(U16_T addrofmem, U8_T *ptbytedata, U16_T devnum);
BOOL	ONEWIRE_ReadScratchpad(U16_T *addrofmem, U8_T *esbyte, U8_T *ptbytedata, U16_T devnum);
BOOL	ONEWIRE_CopyScratchpad(U16_T addrofmem, U8_T esByte, U16_T devnum);
#if MEMORY_SECTIONS
BOOL	ONEWIRE_8ByteWrite(U16_T addrofmem, U8_T *ptbytedata, U16_T devnum);
BOOL	ONEWIRE_8ByteRead(U16_T addrofmem, U8_T *ptbytedata, U16_T devnum);
BOOL	ONEWIRE_PageRead(U16_T addrofmem, U8_T *ptbytedata, U16_T rdlen, U16_T devnum);
BOOL	ONEWIRE_ReadMemory(U16_T addrofmem, U16_T devnum);
#endif


#endif /* End of ONEWIREAPI_H */
