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
 * Module Name : onewireapi.c
 * Purpose     : 
 * Author      : Robin Lee
 * Date        : 2006-01-12
 * Notes       :
 * $Log$
 *================================================================================
 */
/* INCLUDE FILE DECLARATIONS */
#include	"types.h"
#include	"reg80390.h"
//#include	"buffer.h"
#include	"onewire.h"
#include	"onewireapi.h"


/* STATIC VARIABLE DECLARATIONS */


/* LOCAL SUBPROGRAM DECLARATIONS */


/* LOCAL SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_WriteScratchpad(U16_T addrofmem, U8_T *ptbytedata, U16_T devnum)
 * Purpose : write 8 bytes data into scratchpad.
 * Params  : addrofmem - address of accessing.
 *           *ptbytedata - pointer of data string which be writen
 * Returns : TRUE - successful
 * Note    : 
 *--------------------------------------------------------------------------------
 */
BOOL ONEWIRE_WriteScratchpad(U16_T addrofmem, U8_T *ptbytedata, U16_T devnum)
{
	OW_BUF			tempOWbuf;
	OW_BUF XDATA	*ptwrscrpad = NULL;
	U8_T			i;
	U8_T			regval = 0;
	U16_T			calcrc = 0;
	U8_T			*ptromcodes = NULL;

	ONEWIRE_Cmd(SI_RD, OWCMDR, &regval);
	ptwrscrpad = &tempOWbuf;
//	ptwrscrpad = (OW_BUF *)GetPktBuf();
	if (devnum == 0)
	{
		if (regval & OW_OD)
		{
			ptwrscrpad->Romcmd = OD_SKIP_ROM;
		}
		else
		{
			ptwrscrpad->Romcmd = SKIP_ROM;
		}
		for (i=0 ; i<8 ; i++)
			ptwrscrpad->Romarray[i] = 0;
	}
	else
	{
		if (regval & OW_OD)
		{
			ptwrscrpad->Romcmd = OD_MATCH_ROM;
		}
		else
		{
			ptwrscrpad->Romcmd = MATCH_ROM;
		}
		ptromcodes = ONEWIRE_GetRomCode();
		for (i=0 ; i<8 ; i++)
			ptwrscrpad->Romarray[i] = *(ptromcodes + (i + (8*(devnum-1))));
	}
	ONEWIRE_SetCrc16(0);
	ptwrscrpad->Memcmd = WRITE_SCRPAD;
	calcrc = ONEWIRE_DoCrc16(ptwrscrpad->Memcmd);
	// target address low byte
	ptwrscrpad->Memarray[0] = (U8_T)(addrofmem & 0x00FF);
	calcrc = ONEWIRE_DoCrc16(ptwrscrpad->Memarray[0]);
	// target address high byte
	ptwrscrpad->Memarray[1] = (U8_T)((addrofmem & 0xFF00) >> 8);
	calcrc = ONEWIRE_DoCrc16(ptwrscrpad->Memarray[1]);
	// ES byte
	ptwrscrpad->Memarray[2] = 0;
	// 8 data bytes for writing
	for (i=0 ; i<8 ; i++)
	{
		ptwrscrpad->Memarray[3+i] = *(ptbytedata + i);
		calcrc = ONEWIRE_DoCrc16(ptwrscrpad->Memarray[3+i]);
	}
	
	ONEWIRE_SendPkt(ptwrscrpad);
		
	if (!ONEWIRE_Reset())
		return FALSE;
	
	while (1)
	{
		ONEWIRE_StateFunc();
		if (ONEWIRE_StateChk(IDLE_STATE) == TRUE)
			break;
	}
	if (ONEWIRE_StateChk(CRC_ERR) == TRUE)
	{
		return FALSE;
	}
	
	ptwrscrpad = ONEWIRE_GetCurBuf();

	if ((U16_T)(~calcrc) != ((U16_T)(ptwrscrpad->Memarray[11]) | ((U16_T)(ptwrscrpad->Memarray[12]) << 8)))
	{
		return FALSE;
	}

	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_ReadScratchpad(U16_T *addrofmem, U8_T *esbyte, U8_T *ptbytedata, U16_T devnum)
 * Purpose : read 8 bytes data from scratchpad.
 * Params  : *addrofmem - pointer of memory address to be stored for reading.
 *           *esbyte - pointer of ESByte to be stored for reading.
 *           *ptbytedata - pointer of data block to be stored for reading.
 *           devnum - device number
 * Returns : TRUE - successful.
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL ONEWIRE_ReadScratchpad(U16_T *addrofmem, U8_T *esbyte, U8_T *ptbytedata, U16_T devnum)
{
	OW_BUF			tempOWbuf;
	OW_BUF XDATA	*ptrdscrpad = NULL;
	U16_T			i;
	U16_T			calcrc = 0;
	U8_T			regval = 0;
	U8_T			*ptromcodes = NULL;

	ONEWIRE_Cmd(SI_RD, OWCMDR, &regval);
//	ptrdscrpad = (OW_BUF *)GetPktBuf();
	ptrdscrpad = &tempOWbuf;
	if (devnum == 0)
	{
		if (regval & OW_OD)
		{
			ptrdscrpad->Romcmd = OD_SKIP_ROM;
		}
		else
		{
			ptrdscrpad->Romcmd = SKIP_ROM;
		}
		for (i=0 ; i<8 ; i++)
			ptrdscrpad->Romarray[i] = 0;
	}
	else
	{
		if (regval & OW_OD)
		{
			ptrdscrpad->Romcmd = OD_MATCH_ROM;
		}
		else
		{
			ptrdscrpad->Romcmd = MATCH_ROM;
		}
		ptromcodes = ONEWIRE_GetRomCode();
		for (i=0 ; i<8 ; i++)
			ptrdscrpad->Romarray[i] = *(ptromcodes + (i + (8*(devnum-1))));
	}

	ptrdscrpad->Memcmd = READ_SCRPAD;
	
	ONEWIRE_SendPkt(ptrdscrpad);
	
	if (!ONEWIRE_Reset())
		return FALSE;

	while (1)
	{
		ONEWIRE_StateFunc();
		if (ONEWIRE_StateChk(IDLE_STATE) == TRUE)
			break;
	}
	if (ONEWIRE_StateChk(CRC_ERR) == TRUE)
	{
		return FALSE;
	}

	ptrdscrpad = ONEWIRE_GetCurBuf();

	*addrofmem = (U16_T)ptrdscrpad->Memarray[0] | ((U16_T)ptrdscrpad->Memarray[1] << 8);
	*esbyte = ptrdscrpad->Memarray[2];
	for (i=0 ; i<8 ; i++)
	{
		*(ptbytedata+i) = ptrdscrpad->Memarray[3+i];
	}

	if (*esbyte != 0x07)
	{
		return FALSE;
	}

	ONEWIRE_SetCrc16(0);
	calcrc = ONEWIRE_DoCrc16(ptrdscrpad->Memcmd);
	for (i=0 ; i<11 ; i++)
		calcrc = ONEWIRE_DoCrc16(ptrdscrpad->Memarray[i]);
	if ((U16_T)(~calcrc) != ((U16_T)(ptrdscrpad->Memarray[11]) | ((U16_T)(ptrdscrpad->Memarray[12]) << 8)))
	{
		return FALSE;
	}

	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_CopyScratchpad(U16_T addrofmem, U8_T esbyte, U16_T devnum)
 * Purpose : copy 8 bytes data from scratchpad into memory sections.
 * Params  : addrofmem - target address of memory sections.
 *           esbyte - ending address with data status
 * Returns : TRUE - successful
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL ONEWIRE_CopyScratchpad(U16_T addrofmem, U8_T esbyte, U16_T devnum)
{
	OW_BUF			tempOWbuf;
	OW_BUF XDATA	*ptcpscrpad = NULL;
	U16_T			i;
	U8_T			regval = 0;
	U8_T			*ptromcodes = NULL;

	ONEWIRE_Cmd(SI_RD, OWCMDR, &regval);
//	ptcpscrpad = (OW_BUF *)GetPktBuf();
	ptcpscrpad = &tempOWbuf;
	if (devnum == 0)
	{
		if (regval & OW_OD)
		{
			ptcpscrpad->Romcmd = OD_SKIP_ROM;
		}
		else
		{
			ptcpscrpad->Romcmd = SKIP_ROM;
		}
		for (i=0 ; i<8 ; i++)
			ptcpscrpad->Romarray[i] = 0;
	}
	else
	{
		if (regval & OW_OD)
		{
			ptcpscrpad->Romcmd = OD_MATCH_ROM;
		}
		else
		{
			ptcpscrpad->Romcmd = MATCH_ROM;
		}
		ptromcodes = ONEWIRE_GetRomCode();
		for (i=0 ; i<8 ; i++)
			ptcpscrpad->Romarray[i] = *(ptromcodes + (i + (8*(devnum-1))));		
	}
	ptcpscrpad->Memcmd = COPY_SCRPAD;

	// target address low byte
	ptcpscrpad->Memarray[0] = (U8_T)(addrofmem & 0x00FF);
	// target address high byte
	ptcpscrpad->Memarray[1] = (U8_T)((addrofmem & 0xFF00) >> 8);
	// ES byte
	ptcpscrpad->Memarray[2] = esbyte;
	
	for (i=0 ; i<10 ; i++)
	{
		ptcpscrpad->Memarray[3+i] = 0;
	}

	ONEWIRE_SendPkt(ptcpscrpad);
	
	if (!ONEWIRE_Reset())
		return FALSE;
	
	while (1)
	{
		ONEWIRE_StateFunc();
		if (ONEWIRE_StateChk(IDLE_STATE) == TRUE)
			break;
	}
	if (ONEWIRE_StateChk(CRC_ERR) == TRUE)
	{
		return FALSE;
	}
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_ReadMemory(U16_T addrofmem, U16_T devnum)
 * Purpose : read whole data from memory sections.
 * Params  : addrofmem - address of memory sections.
 *           devnum - device number.
 * Returns : TRUE - successful.
 * Note    : read memory always reads starting from the address until end address.
 *--------------------------------------------------------------------------------
 */
#if MEMORY_SECTIONS
BOOL ONEWIRE_ReadMemory(U16_T addrofmem, U16_T devnum)
{
	OW_BUF			tempOWbuf;
	OW_BUF XDATA	*ptrdmem = NULL;
	U16_T			i;
	U8_T			regval = 0;
	U8_T			*ptromcodes = NULL;

	ONEWIRE_Cmd(SI_RD, OWCMDR, &regval);
//	ptrdmem = (OW_BUF *)GetPktBuf();
	ptrdmem = &tempOWbuf;
	if (devnum == 0)
	{
		if (regval & OW_OD)
		{
			ptrdmem->Romcmd = OD_SKIP_ROM;
		}
		else
		{
			ptrdmem->Romcmd = SKIP_ROM;
		}
		for (i=0 ; i<8 ; i++)
			ptrdmem->Romarray[i] = 0;
	}
	else
	{
		if (regval & OW_OD)
		{
			ptrdmem->Romcmd = OD_MATCH_ROM;
		}
		else
		{
			ptrdmem->Romcmd = MATCH_ROM;
		}
		ptromcodes = ONEWIRE_GetRomCode();
		for (i=0 ; i<8 ; i++)
			ptrdmem->Romarray[i] = *(ptromcodes + (i + (8*(devnum-1))));
	}

	ptrdmem->Memcmd = READ_MEMORY;

	// target address low byte
	ptrdmem->Memarray[0] = (U8_T)(addrofmem & 0x00FF);
	// target address high byte
	ptrdmem->Memarray[1] = (U8_T)((addrofmem & 0xFF00) >> 8);
	// ES byte
	ptrdmem->Memarray[2] = 0;
	
	for (i=0 ; i<10 ; i++)
	{
		ptrdmem->Memarray[3+i] = 0;
	}

	ONEWIRE_SendPkt(ptrdmem);

	if (!ONEWIRE_Reset())
		return FALSE;

	while (1)
	{
		ONEWIRE_StateFunc();
		if (ONEWIRE_StateChk(IDLE_STATE) == TRUE)
			break;
	}
	if (ONEWIRE_StateChk(CRC_ERR) == TRUE)
	{
		return FALSE;
	}

	return TRUE;
}
#endif


/* EXPORTED SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_8ByteWrite(U16_T addrofmem, U8_T *ptbytedata, U16_T devnum)
 * Purpose : write 8 bytes data into memory sections.
 * Params  : addrofmem - address of memory sections.
 *           *ptbytedata - pointer of data block to be writen.
 *           devnum - device number.
 * Returns : TRUE - successful.
 * Note    :
 *--------------------------------------------------------------------------------
 */
#if MEMORY_SECTIONS
BOOL ONEWIRE_8ByteWrite(U16_T addrofmem, U8_T *ptbytedata, U16_T devnum)
{
	U16_T	authaddr = 0;
	U8_T	authesbyte = 0;
	U8_T	tempbytes[8] = {0,0,0,0,0,0,0,0};

	if (!ONEWIRE_WriteScratchpad(addrofmem, ptbytedata, devnum))
		return FALSE;
	if (!ONEWIRE_ReadScratchpad(&authaddr, &authesbyte, &tempbytes, devnum))
		return FALSE;
	if (!ONEWIRE_CopyScratchpad(authaddr, authesbyte, devnum))
		return FALSE;

	return TRUE;
}
#endif

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_8ByteRead(U16_T addrofmem, U8_T *ptbytedata, U16_T devnum)
 * Purpose : read 8 bytes data from memory sections.
 * Params  : addrofmem - address of memory sections.
 *           *ptbytedata - pointer of data block to be stored.
 *           devnum - device number.
 * Returns : TRUE - successful.
 * Note    :
 *--------------------------------------------------------------------------------
 */
#if MEMORY_SECTIONS
BOOL ONEWIRE_8ByteRead(U16_T addrofmem, U8_T *ptbytedata, U16_T devnum)
{
	U8_T	i;
	U8_T	*ptread = NULL;

	if (!ONEWIRE_ReadMemory(addrofmem, devnum))
		return FALSE;

	ptread = ONEWIRE_GetRdMemData();
	for (i=0 ; i<8 ; i++)
	{
		*(ptbytedata + i) = *(ptread + i);
	}

	return TRUE;
}
#endif

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_PageRead(U16_T addrofmem, U8_T *ptbytedata, U16_T rdlen, U16_T devnum)
 * Purpose : read data block from memory with a length.
 * Params  : addrofmem - address of memory sections.
 *           *ptbytedata - pointer of data block to be stored.
 *           rdlen - length to be read.
 *           devnum - device number.
 * Returns : TRUE - successful.
 * Note    :
 *--------------------------------------------------------------------------------
 */
#if MEMORY_SECTIONS
BOOL ONEWIRE_PageRead(U16_T addrofmem, U8_T *ptbytedata, U16_T rdlen, U16_T devnum)
{
	U8_T	i;
	U8_T	*ptread = NULL;

	if (!ONEWIRE_ReadMemory(addrofmem, devnum))
		return FALSE;

	ptread = ONEWIRE_GetRdMemData();
	for (i=0 ; i<rdlen ; i++)
	{
		*(ptbytedata + i) = *(ptread + i);
	}

	return TRUE;
}
#endif


/* End of onewireapi.c */
