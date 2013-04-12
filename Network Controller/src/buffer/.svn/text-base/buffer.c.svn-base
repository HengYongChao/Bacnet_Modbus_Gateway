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
 * Module Name : buffer.c
 * Purpose     : This module handles the buffer memory allocation and release.
 * Author      : Robin Lee
 * Date        : 2005-03-31
 * Notes       :
 * $Log: buffer.c,v $
 * Revision 1.3  2005/11/24 12:48:16  robin6633
 * initiate values of use.
 *
 * Revision 1.2  2005/06/14 02:49:12  arthur
 * changed interrupt.h include
 *
 * Revision 1.1  2005/06/14 02:05:53  arthur
 * move directory
 *
 * Revision 1.1.1.1  2005/06/06 05:55:57  robin6633
 * no message
 *
 *================================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include	"types.h"
#include	"buffer.h"


/* STATIC VARIABLE DECLARATIONS */
static U8_T			bufcount = 0;
static SI_BUF_PAGE	sipagebuf[TOTAL_BUF_NUM];


/* LOCAL SUBPROGRAM DECLARATIONS */


/* LOCAL SUBPROGRAM BODIES */


/* EXPORTED SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * SI_BUF_PAGE *GetPktBuf(void)
 * Purpose : allocate a buffer for serial interface
 * Params  :
 * Returns : ptpktbuf - pointer of buffer allocated
 * Note    : this buffer pool is a ring buffer
 *--------------------------------------------------------------------------------
 */
SI_BUF_PAGE *GetPktBuf(void)
{
	SI_BUF_PAGE	*ptpktbuf = NULL;
	U8_T		i = 0;

	for (i=0 ; i<PAGE_BUF_SIZE ; i++)
	{
		sipagebuf[bufcount].bufpage[i] = 0;
	}
	ptpktbuf = &sipagebuf[bufcount];
	bufcount ++;
	if (bufcount == TOTAL_BUF_NUM)
	{
		bufcount = 0;
	}
	return ptpktbuf;
}


/* End of buffer.c */
