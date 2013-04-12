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
 * Module Name : i2capi.h
 * Purpose     : 
 * Author      : Robin Lee
 * Date        :
 * Notes       :
 * $Log: i2capi.h,v $
 * Revision 1.1  2006/04/07 11:38:34  robin6633
 * no message
 *
 *================================================================================
 */
#ifndef I2CAPI_H
#define I2CAPI_H

/* INCLUDE FILE DECLARATIONS */


/* NAMING CONSTANT DECLARATIONS */


/* MACRO DECLARATIONS */


/* TYPE DECLARATIONS */


/* GLOBAL VARIABLES */


/* EXPORTED SUBPROGRAM SPECIFICATIONS */
BOOL	I2C_ByteWrite(U16_T addrOfDev, U16_T addrOfmem, U8_T byteData, U8_T endCond);
BOOL	I2C_PageWrite(U16_T addrOfDev, U16_T addrOfmem, U8_T *ptPageData, U16_T writeLen, U8_T endCond);
BOOL	I2C_RdmRead(U16_T addrOfDev, U16_T addrOfMem ,I2C_BUF *ptRxPkt, U16_T readLen, U8_T endCond);
BOOL	I2C_DummyWrite(U16_T addrOfDev, U16_T addrOfMem, U8_T endCond);


#endif /* End of I2CAPI_H */
