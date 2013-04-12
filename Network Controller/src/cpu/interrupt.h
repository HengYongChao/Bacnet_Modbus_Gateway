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
 * Module Name : interrupt.h
 * Purpose     : A header file belongs to interrupt module.
 * Author      : Robin Lee
 * Date        : 2005-01-09
 * Notes       : None.
 * $Log: interrupt.h,v $
 * Revision 1.2  2006/05/18 05:02:30  Louis
 * no message
 *
 * Revision 1.2  2006/04/20 01:24:55  robin6633
 * 1.Removed the power management interrupt enable/disable.
 *
 * Revision 1.1  2006/04/07 11:36:17  robin6633
 * no message
 *
 *================================================================================
 */
#ifndef INTERRUPT_H
#define INTERRUPT_H

/* INCLUDE FILE DECLARATIONS */
#include	"interrupt_cfg.h"


/* NAMING CONSTANT DECLARATIONS */
#define		ON		1
#define		OFF		0
#define		EXTINT0(val)	{EX0 = val;}
#define		EXTINT1(val)	{EX1 = val;}
#define		EXTINT2(val)	{EINT2 = val;}
#define		EXTINT3(val)	{EINT3 = val;}
#define		EXTINT4(val)	{EINT4 = val;}
#define		EXTINT5(val)	{EINT5 = val;}
#define		EXTINT6(val)	{EINT6 = val;}


/* MACRO DECLARATIONS */


/* TYPE DECLARATIONS */


/* GLOBAL VARIABLES */


/* EXPORTED SUBPROGRAM SPECIFICATIONS */


#endif /* End of INTERRUPT_H */
