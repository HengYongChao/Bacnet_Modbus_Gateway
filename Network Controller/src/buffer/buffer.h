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
 * Module Name : buffer.h
 * Purpose     : 
 * Author      : Robin Lee
 * Date        : 2005-03-31
 * Notes       :
 * $Log: buffer.h,v $
 * Revision 1.3  2005/11/24 12:49:49  robin6633
 * remove unused structure.
 *
 * Revision 1.2  2005/08/01 12:49:10  robin6633
 * Add type definition of buffer.
 *
 * Revision 1.1  2005/06/14 02:05:53  arthur
 * move directory
 *
 * Revision 1.1.1.1  2005/06/06 05:55:57  robin6633
 * no message
 *
 *================================================================================
 */
#ifndef BUFFER_H
#define BUFFER_H

/* INCLUDE FILE DECLARATIONS */


/* NAMING CONSTANT DECLARATIONS */
#define	TOTAL_BUF_NUM	33
/* Buffer Definition */
#define	PAGE_BUF_SIZE	80 // the maximum size can not be over 256

/* MACRO DECLARATIONS */


/* TYPE DECLARATIONS */
typedef struct si_buf_page {
	U8_T 		bufpage[PAGE_BUF_SIZE];
	void		*Next;
} SI_BUF_PAGE;


/* GLOBAL VARIABLES */


/* EXPORTED SUBPROGRAM SPECIFICATIONS */
SI_BUF_PAGE		*GetPktBuf(void);


#endif /* End of BUFFER_H */
