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
 * Module Name : ax11000api.c
 * Purpose     : Provide some API functions to access SFR, external data memory
 *               and peripheral registers of AX110xx chip.
 * Author      : Robin Lee
 * Date        : 2006-09-20
 * Notes       : None.
 * $Log$
 *================================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include	"reg80390.h"
#include	"types.h"
#include	"ax11000slv.h"
#include	<stdio.h>
#include	<absacc.h>


/* STATIC VARIABLE DECLARATIONS */


/* LOCAL SUBPROGRAM DECLARATIONS */


/* LOCAL SUBPROGRAM BODIES */


/* EXPORTED SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_SfrWr(U8_T sfrAddr, U8_T sfrData)
 * Purpose : Write one byte data to a SFR address.
 * Params  : sfrAddr - address of SFR
 *           sfrData - one byte data
 * Returns : TRUE - successful
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_SfrWr(U8_T sfrAddr, U8_T sfrData)
{
	switch (sfrAddr)
	{
		case SFR_P0 :
			P0 = (U8_T)sfrData;
			break;
		case SFR_SP :
			SP = (U8_T)sfrData;
			break;
		case SFR_DPL0 :
			DPL0 = (U8_T)sfrData;
			break;
		case SFR_DPH0 :
			DPH0 = (U8_T)sfrData;
			break;
		case SFR_DPL1 :
			DPL1 = (U8_T)sfrData;
			break;
		case SFR_DPH1 :
			DPH1 = (U8_T)sfrData;
			break;
		case SFR_DPS :
			DPS = (U8_T)sfrData;
			break;
		case SFR_PCON :
			PCON = (U8_T)sfrData;
			break;
		case SFR_TCON :
			TCON = (U8_T)sfrData;
			break;
		case SFR_TMOD :
			TMOD = (U8_T)sfrData;
			break;
		case SFR_TL0 :
			TL0 = (U8_T)sfrData;
			break;
		case SFR_TL1 :
			TL1 = (U8_T)sfrData;
			break;
		case SFR_TH0 :
			TH0 = (U8_T)sfrData;
			break;
		case SFR_TH1 :
			TH1 = (U8_T)sfrData;
			break;
		case SFR_CKCON :
			CKCON = (U8_T)sfrData;
			break;
		case SFR_CSREPR :
			CSREPR = (U8_T)sfrData;
			break;
		case SFR_P1 :
			P1 = (U8_T)sfrData;
			break;
		case SFR_EIF :
			EIF = (U8_T)sfrData;
			break;
		case SFR_WTST :
			WTST = (U8_T)sfrData;
			break;
		case SFR_DPX0 :
			DPX0 = (U8_T)sfrData;
			break;
		case SFR_SDSTSR :
			SDSTSR = (U8_T)sfrData;
			break;
		case SFR_DPX1 :
			DPX1 = (U8_T)sfrData;
			break;
		case SFR_I2CCIR :
			I2CCIR = (U8_T)sfrData;
			break;
		case SFR_I2CDR :
			I2CDR = (U8_T)sfrData;
			break;
		case SFR_SCON0 :
			SCON0 = (U8_T)sfrData;
			break;
		case SFR_SBUF0 :
			SBUF0 = (U8_T)sfrData;
			break;
		case SFR_DBAR :
			DBAR = (U8_T)sfrData;
			break;
		case SFR_DCIR :
			DCIR = (U8_T)sfrData;
			break;
		case SFR_DDR :
			DDR = (U8_T)sfrData;
			break;
		case SFR_ACON :
			ACON = (U8_T)sfrData;
			break;
		case SFR_PISSR1 :
			PISSR1 = (U8_T)sfrData;
			break;
		case SFR_PISSR2 :
			PISSR2 = (U8_T)sfrData;
			break;
		case SFR_P2 :
			P2 = (U8_T)sfrData;
			break;
		case SFR_LMSR_LSAIER :
			LMSR = (U8_T)sfrData;
			break;
		case SFR_LCR_LSCR :
			LCR = (U8_T)sfrData;
			break;
		case SFR_LSR_LSSR :
			LSR = (U8_T)sfrData;
			break;
		case SFR_LDALR_XMWLR :
			LDALR = (U8_T)sfrData;
			break;
		case SFR_LDAHR_XMWHR :
			LDAHR = (U8_T)sfrData;
			break;
		case SFR_LDCSR_XMRLR :
			LDCSR = (U8_T)sfrData;
			break;
		case SFR_XMRHR :
			XMRHR = (U8_T)sfrData;
			break;
		case SFR_IE :
			IE = (U8_T)sfrData;
			break;
		case SFR_LDLR :
			LDLR = (U8_T)sfrData;
			break;
		case SFR_LDHR :
			LDHR = (U8_T)sfrData;
			break;
		case SFR_LDMLR :
			DMALR = (U8_T)sfrData;
			break;
		case SFR_LDMMR :
			DMAMR = (U8_T)sfrData;
			break;
		case SFR_LDMHR :
			DMAHR = (U8_T)sfrData;
			break;
		case SFR_TCIR :
			TCIR = (U8_T)sfrData;
			break;
		case SFR_TDR :
			TDR = (U8_T)sfrData;
			break;
		case SFR_P3 :
			P3 = (U8_T)sfrData;
			break;
		case SFR_CCAPL0 :
			CCAPL0 = (U8_T)sfrData;
			break;
		case SFR_CCAPL1 :
			CCAPL1 = (U8_T)sfrData;
			break;
		case SFR_CCAPL2 :
			CCAPL2 = (U8_T)sfrData;
			break;
		case SFR_CCAPL3 :
			CCAPL3 = (U8_T)sfrData;
			break;
		case SFR_CCAPL4 :
			CCAPL4 = (U8_T)sfrData;
			break;
		case SFR_MCIR :
			MCIR = (U8_T)sfrData;
			break;
		case SFR_MDR :
			MDR = (U8_T)sfrData;
			break;
		case SFR_IP :
			IP = (U8_T)sfrData;
			break;
		case SFR_CCAPH0 :
			CCAPH0 = (U8_T)sfrData;
			break;
		case SFR_CCAPH1 :
			CCAPH1 = (U8_T)sfrData;
			break;
		case SFR_CCAPH2 :
			CCAPH2 = (U8_T)sfrData;
			break;
		case SFR_CCAPH3 :
			CCAPH3 = (U8_T)sfrData;
			break;
		case SFR_CCAPH4 :
			CCAPH4 = (U8_T)sfrData;
			break;
		case SFR_EPCR :
			EPCR = (U8_T)sfrData;
			break;
		case SFR_EPDR :
			EPDR = (U8_T)sfrData;
			break;
		case SFR_SCON1 :
			SCON1 = (U8_T)sfrData;
			break;
		case SFR_SBUF1 :
			SBUF1 = (U8_T)sfrData;
			break;
		case SFR_CMOD :
			CMOD = (U8_T)sfrData;
			break;
		case SFR_CCON :
			CCON = (U8_T)sfrData;
			break;
		case SFR_CL :
			CL = (U8_T)sfrData;
			break;
		case SFR_CH :
			CH = (U8_T)sfrData;
			break;
		case SFR_T2CON :
			T2CON = (U8_T)sfrData;
			break;
		case SFR_T2IF :
			T2IF = (U8_T)sfrData;
			break;
		case SFR_RLDL :
			RLDL = (U8_T)sfrData;
			break;
		case SFR_RLDH :
			RLDH = (U8_T)sfrData;
			break;
		case SFR_TL2 :
			TL2 = (U8_T)sfrData;
			break;
		case SFR_TH2 :
			TH2 = (U8_T)sfrData;
			break;
		case SFR_SPICIR :
			SPICIR = (U8_T)sfrData;
			break;
		case SFR_SPIDR :
			SPIDR = (U8_T)sfrData;
			break;
		case SFR_PSW :
			PSW = (U8_T)sfrData;
			break;
		case SFR_CCAPM0 :
			CCAPM0 = (U8_T)sfrData;
			break;
		case SFR_CCAPM1 :
			CCAPM1 = (U8_T)sfrData;
			break;
		case SFR_CCAPM2 :
			CCAPM2 = (U8_T)sfrData;
			break;
		case SFR_CCAPM3 :
			CCAPM3 = (U8_T)sfrData;
			break;
		case SFR_CCAPM4 :
			CCAPM4 = (U8_T)sfrData;
			break;
		case SFR_OWCIR :
			OWCIR = (U8_T)sfrData;
			break;
		case SFR_OWDR :
			OWDR = (U8_T)sfrData;
			break;
		case SFR_WDCON :
			WDCON = (U8_T)sfrData;
			break;
		case SFR_CANCIR :
			CANCIR = (U8_T)sfrData;
			break;
		case SFR_CANDR :
			CANDR = (U8_T)sfrData;
			break;
		case SFR_ACC :
			ACC = (U8_T)sfrData;
			break;
		case SFR_UR2_THR_RBR_DLL :
			UR2_THR = (U8_T)sfrData;
			break;
		case SFR_UR2_IER_DLH :
			UR2_IER = (U8_T)sfrData;
			break;
		case SFR_UR2_IIR_FCR :
			UR2_IIR = (U8_T)sfrData;
			break;
		case SFR_UR2_LCR :
			UR2_LCR = (U8_T)sfrData;
			break;
		case SFR_UR2_MCR :
			UR2_MCR = (U8_T)sfrData;
			break;
		case SFR_UR2_LSR :
			UR2_LSR = (U8_T)sfrData;
			break;
		case SFR_UR2_MSR :
			UR2_MSR = (U8_T)sfrData;
			break;
		case SFR_EIE :
			EIE = (U8_T)sfrData;
			break;
		case SFR_STATUS :
			STATUS = (U8_T)sfrData;
			break;
		case SFR_MXAX :
			MXAX = (U8_T)sfrData;
			break;
		case SFR_TA :
			TA = (U8_T)sfrData;
			break;
		case SFR_B :
			B = (U8_T)sfrData;
			break;
		case SFR_EIP :
			EIP = (U8_T)sfrData;
			break;
		case SFR_MD0 :
			MD0 = (U8_T)sfrData;
			break;
		case SFR_MD1 :
			MD1 = (U8_T)sfrData;
			break;
		case SFR_MD2 :
			MD2 = (U8_T)sfrData;
			break;
		case SFR_MD3 :
			MD3 = (U8_T)sfrData;
			break;
		case SFR_MD4 :
			MD4 = (U8_T)sfrData;
			break;
		case SFR_MD5 :
			MD5 = (U8_T)sfrData;
			break;
		case SFR_ARCON :
			ARCON = (U8_T)sfrData;
			break;
		case SFR_C6 :
			SFRC6 = (U8_T)sfrData;
			break;
		case SFR_C7 :
			SFRC7 = (U8_T)sfrData;
			break;
		case SFR_D9 :
			SFRD9 = (U8_T)sfrData;
			break;
		case SFR_DA :
			SFRDA = (U8_T)sfrData;
			break;
		case SFR_DB :
			SFRDB = (U8_T)sfrData;
			break;
		case SFR_DC :
			SFRDC = (U8_T)sfrData;
			break;
		case SFR_DD :
			SFRDD = (U8_T)sfrData;
			break;
		case SFR_EC :
			SFREC = (U8_T)sfrData;
			break;
		case SFR_ED :
			SFRED = (U8_T)sfrData;
			break;
		case SFR_EE :
			SFREE = (U8_T)sfrData;
			break;
		case SFR_EF :
			SFREF = (U8_T)sfrData;
			break;
		case SFR_F1 :
			SFRF1 = (U8_T)sfrData;
			break;
		case SFR_F2 :
			SFRF2 = (U8_T)sfrData;
			break;
		case SFR_F3 :
			SFRF3 = (U8_T)sfrData;
			break;
		case SFR_F4 :
			SFRF4 = (U8_T)sfrData;
			break;
		case SFR_F5 :
			SFRF5 = (U8_T)sfrData;
			break;
		case SFR_F6 :
			SFRF6 = (U8_T)sfrData;
			break;
		case SFR_F7 :
			SFRF7 = (U8_T)sfrData;
			break;
		default :
			printf("Undefined SFR Address !\n");
	}
	return (TRUE);
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_SfrRd(U8_T sfrAddr, U8_T *sfrData)
 * Purpose : Read one byte data from a SFR address.
 * Params  : sfrAddr - address of SFR
 *           sfrData - one byte data
 * Returns : TRUE - successful
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_SfrRd(U8_T sfrAddr, U8_T *sfrData)
{
	switch (sfrAddr)
	{
		case SFR_P0 :
			*sfrData = (U8_T)P0;
			break;
		case SFR_SP :
			*sfrData = (U8_T)SP;
			break;
		case SFR_DPL0 :
			*sfrData = (U8_T)DPL0;
			break;
		case SFR_DPH0 :
			*sfrData = (U8_T)DPH0;
			break;
		case SFR_DPL1 :
			*sfrData = (U8_T)DPL1;
			break;
		case SFR_DPH1 :
			*sfrData = (U8_T)DPH1;
			break;
		case SFR_DPS :
			*sfrData = (U8_T)DPS;
			break;
		case SFR_PCON :
			*sfrData = (U8_T)PCON;
			break;
		case SFR_TCON :
			*sfrData = (U8_T)TCON;
			break;
		case SFR_TMOD :
			*sfrData = (U8_T)TMOD;
			break;
		case SFR_TL0 :
			*sfrData = (U8_T)TL0;
			break;
		case SFR_TL1 :
			*sfrData = (U8_T)TL1;
			break;
		case SFR_TH0 :
			*sfrData = (U8_T)TH0;
			break;
		case SFR_TH1 :
			*sfrData = (U8_T)TH1;
			break;
		case SFR_CKCON :
			*sfrData = (U8_T)CKCON;
			break;
		case SFR_CSREPR :
			*sfrData = (U8_T)CSREPR;
			break;
		case SFR_P1 :
			*sfrData = (U8_T)P1;
			break;
		case SFR_EIF :
			*sfrData = (U8_T)EIF;
			break;
		case SFR_WTST :
			*sfrData = (U8_T)WTST;
			break;
		case SFR_DPX0 :
			*sfrData = (U8_T)DPX0;
			break;
		case SFR_SDSTSR :
			*sfrData = (U8_T)SDSTSR;
			break;
		case SFR_DPX1 :
			*sfrData = (U8_T)DPX1;
			break;
		case SFR_I2CCIR :
			*sfrData = (U8_T)I2CCIR;
			break;
		case SFR_I2CDR :
			*sfrData = (U8_T)I2CDR;
			break;
		case SFR_SCON0 :
			*sfrData = (U8_T)SCON0;
			break;
		case SFR_SBUF0 :
			*sfrData = (U8_T)SBUF0;
			break;
		case SFR_DBAR :
			*sfrData = (U8_T)DBAR;
			break;
		case SFR_DCIR :
			*sfrData = (U8_T)DCIR;
			break;
		case SFR_DDR :
			*sfrData = (U8_T)DDR;
			break;
		case SFR_ACON :
			*sfrData = (U8_T)ACON;
			break;
		case SFR_PISSR1 :
			*sfrData = (U8_T)PISSR1;
			break;
		case SFR_PISSR2 :
			*sfrData = (U8_T)PISSR2;
			break;
		case SFR_P2 :
			*sfrData = (U8_T)P2;
			break;
		case SFR_LMSR_LSAIER :
			*sfrData = (U8_T)LMSR;
			break;
		case SFR_LCR_LSCR :
			*sfrData = (U8_T)LCR;
			break;
		case SFR_LSR_LSSR :
			*sfrData = (U8_T)LSR;
			break;
		case SFR_LDALR_XMWLR :
			*sfrData = (U8_T)LDALR;
			break;
		case SFR_LDAHR_XMWHR :
			*sfrData = (U8_T)LDAHR;
			break;
		case SFR_LDCSR_XMRLR :
			*sfrData = (U8_T)LDCSR;
			break;
		case SFR_XMRHR :
			*sfrData = (U8_T)XMRHR;
			break;
		case SFR_IE :
			*sfrData = (U8_T)IE;
			break;
		case SFR_LDLR :
			*sfrData = (U8_T)LDLR;
			break;
		case SFR_LDHR :
			*sfrData = (U8_T)LDHR;
			break;
		case SFR_LDMLR :
			*sfrData = (U8_T)DMALR;
			break;
		case SFR_LDMMR :
			*sfrData = (U8_T)DMAMR;
			break;
		case SFR_LDMHR :
			*sfrData = (U8_T)DMAHR;
			break;
		case SFR_TCIR :
			*sfrData = (U8_T)TCIR;
			break;
		case SFR_TDR :
			*sfrData = (U8_T)TDR;
			break;
		case SFR_P3 :
			*sfrData = (U8_T)P3;
			break;
		case SFR_CCAPL0 :
			*sfrData = (U8_T)CCAPL0;
			break;
		case SFR_CCAPL1 :
			*sfrData = (U8_T)CCAPL1;
			break;
		case SFR_CCAPL2 :
			*sfrData = (U8_T)CCAPL2;
			break;
		case SFR_CCAPL3 :
			*sfrData = (U8_T)CCAPL3;
			break;
		case SFR_CCAPL4 :
			*sfrData = (U8_T)CCAPL4;
			break;
		case SFR_MCIR :
			*sfrData = (U8_T)MCIR;
			break;
		case SFR_MDR :
			*sfrData = (U8_T)MDR;
			break;
		case SFR_IP :
			*sfrData = (U8_T)IP;
			break;
		case SFR_CCAPH0 :
			*sfrData = (U8_T)CCAPH0;
			break;
		case SFR_CCAPH1 :
			*sfrData = (U8_T)CCAPH1;
			break;
		case SFR_CCAPH2 :
			*sfrData = (U8_T)CCAPH2;
			break;
		case SFR_CCAPH3 :
			*sfrData = (U8_T)CCAPH3;
			break;
		case SFR_CCAPH4 :
			*sfrData = (U8_T)CCAPH4;
			break;
		case SFR_EPCR :
			*sfrData = (U8_T)EPCR;
			break;
		case SFR_EPDR :
			*sfrData = (U8_T)EPDR;
			break;
		case SFR_SCON1 :
			*sfrData = (U8_T)SCON1;
			break;
		case SFR_SBUF1 :
			*sfrData = (U8_T)SBUF1;
			break;
		case SFR_CMOD :
			*sfrData = (U8_T)CMOD;
			break;
		case SFR_CCON :
			*sfrData = (U8_T)CCON;
			break;
		case SFR_CL :
			*sfrData = (U8_T)CL;
			break;
		case SFR_CH :
			*sfrData = (U8_T)CH;
			break;
		case SFR_T2CON :
			*sfrData = (U8_T)T2CON;
			break;
		case SFR_T2IF :
			*sfrData = (U8_T)T2IF;
			break;
		case SFR_RLDL :
			*sfrData = (U8_T)RLDL;
			break;
		case SFR_RLDH :
			*sfrData = (U8_T)RLDH;
			break;
		case SFR_TL2 :
			*sfrData = (U8_T)TL2;
			break;
		case SFR_TH2 :
			*sfrData = (U8_T)TH2;
			break;
		case SFR_SPICIR :
			*sfrData = (U8_T)SPICIR;
			break;
		case SFR_SPIDR :
			*sfrData = (U8_T)SPIDR;
			break;
		case SFR_PSW :
			*sfrData = (U8_T)PSW;
			break;
		case SFR_CCAPM0 :
			*sfrData = (U8_T)CCAPM0;
			break;
		case SFR_CCAPM1 :
			*sfrData = (U8_T)CCAPM1;
			break;
		case SFR_CCAPM2 :
			*sfrData = (U8_T)CCAPM2;
			break;
		case SFR_CCAPM3 :
			*sfrData = (U8_T)CCAPM3;
			break;
		case SFR_CCAPM4 :
			*sfrData = (U8_T)CCAPM4;
			break;
		case SFR_OWCIR :
			*sfrData = (U8_T)OWCIR;
			break;
		case SFR_OWDR :
			*sfrData = (U8_T)OWDR;
			break;
		case SFR_WDCON :
			*sfrData = (U8_T)WDCON;
			break;
		case SFR_CANCIR :
			*sfrData = (U8_T)CANCIR;
			break;
		case SFR_CANDR :
			*sfrData = (U8_T)CANDR;
			break;
		case SFR_ACC :
			*sfrData = (U8_T)ACC;
			break;
		case SFR_UR2_THR_RBR_DLL :
			*sfrData = (U8_T)UR2_THR;
			break;
		case SFR_UR2_IER_DLH :
			*sfrData = (U8_T)UR2_IER;
			break;
		case SFR_UR2_IIR_FCR :
			*sfrData = (U8_T)UR2_IIR;
			break;
		case SFR_UR2_LCR :
			*sfrData = (U8_T)UR2_LCR;
			break;
		case SFR_UR2_MCR :
			*sfrData = (U8_T)UR2_MCR;
			break;
		case SFR_UR2_LSR :
			*sfrData = (U8_T)UR2_LSR;
			break;
		case SFR_UR2_MSR :
			*sfrData = (U8_T)UR2_MSR;
			break;
		case SFR_EIE :
			*sfrData = (U8_T)EIE;
			break;
		case SFR_STATUS :
			*sfrData = (U8_T)STATUS;
			break;
		case SFR_MXAX :
			*sfrData = (U8_T)MXAX;
			break;
		case SFR_TA :
			*sfrData = (U8_T)TA;
			break;
		case SFR_B :
			*sfrData = (U8_T)B;
			break;
		case SFR_EIP :
			*sfrData = (U8_T)EIP;
			break;
		case SFR_MD0 :
			*sfrData = (U8_T)MD0;
			break;
		case SFR_MD1 :
			*sfrData = (U8_T)MD1;
			break;
		case SFR_MD2 :
			*sfrData = (U8_T)MD2;
			break;
		case SFR_MD3 :
			*sfrData = (U8_T)MD3;
			break;
		case SFR_MD4 :
			*sfrData = (U8_T)MD4;
			break;
		case SFR_MD5 :
			*sfrData = (U8_T)MD5;
			break;
		case SFR_ARCON :
			*sfrData = (U8_T)ARCON;
			break;
		case SFR_C6 :
			*sfrData = (U8_T)SFRC6;
			break;
		case SFR_C7 :
			*sfrData = (U8_T)SFRC7;
			break;
		case SFR_D9 :
			*sfrData = (U8_T)SFRD9;
			break;
		case SFR_DA :
			*sfrData = (U8_T)SFRDA;
			break;
		case SFR_DB :
			*sfrData = (U8_T)SFRDB;
			break;
		case SFR_DC :
			*sfrData = (U8_T)SFRDC;
			break;
		case SFR_DD :
			*sfrData = (U8_T)SFRDD;
			break;
		case SFR_EC :
			*sfrData = (U8_T)SFREC;
			break;
		case SFR_ED :
			*sfrData = (U8_T)SFRED;
			break;
		case SFR_EE :
			*sfrData = (U8_T)SFREE;
			break;
		case SFR_EF :
			*sfrData = (U8_T)SFREF;
			break;
		case SFR_F1 :
			*sfrData = (U8_T)SFRF1;
			break;
		case SFR_F2 :
			*sfrData = (U8_T)SFRF2;
			break;
		case SFR_F3 :
			*sfrData = (U8_T)SFRF3;
			break;
		case SFR_F4 :
			*sfrData = (U8_T)SFRF4;
			break;
		case SFR_F5 :
			*sfrData = (U8_T)SFRF5;
			break;
		case SFR_F6 :
			*sfrData = (U8_T)SFRF6;
			break;
		case SFR_F7 :
			*sfrData = (U8_T)SFRF7;
			break;
		default :
			printf("Undefined SFR Address !\n");
	}
	return (TRUE);
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_ExtMemWr(U32_T extMemAddr, U8_T extMemData)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_ExtMemWr(U32_T extMemAddr, U8_T extMemData)
{
	FVAR(U8_T, extMemAddr) = extMemData;

	return (TRUE);
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_ExtMemRd(U32_T extMemAddr, U8_T *extMemData)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_ExtMemRd(U32_T extMemAddr, U8_T *extMemData)
{
	*extMemData = FVAR(U8_T, extMemAddr);

	return (TRUE);
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_ToeWr(U8_T toeAddr, U8_T *ptToeData, U8_T toeDataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_ToeWr(U8_T toeAddr, U8_T *ptToeData, U8_T toeDataLen)
{
	U8_T	i;

	for (i=0 ; i<toeDataLen ; i++)
	{
		TDR = *(ptToeData + i);
	}
	TCIR = toeAddr;
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_ToeRd(U8_T toeAddr, U8_T *ptToeData, U8_T toeDataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_ToeRd(U8_T toeAddr, U8_T *ptToeData, U8_T toeDataLen)
{
	U8_T	i;

	TCIR = toeAddr;
	for (i=0 ; i<toeDataLen ; i++)
	{
		*(ptToeData + i) = TDR;
	}
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_MacWr(U8_T macAddr, U8_T *ptMacData, U8_T macDataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_MacWr(U8_T macAddr, U8_T *ptMacData, U8_T macDataLen)
{
	U8_T	i;

	for (i=0 ; i<macDataLen ; i++)
	{
		MDR = *(ptMacData + i);
	}
	MCIR = macAddr;
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_MacRd(U8_T macAddr, U8_T *ptMacData, U8_T macDataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_MacRd(U8_T macAddr, U8_T *ptMacData, U8_T macDataLen)
{
	U8_T	i;

	MCIR = macAddr;
	for (i=0 ; i<macDataLen ; i++)
	{
		*(ptMacData + i) = MDR;
	}
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_PhyWr(U8_T phyId, U8_T phyAddr, U16_T phyData)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_PhyWr(U8_T phyId, U8_T phyAddr, U16_T phyData)
{
	U8_T	cmdChk = 0;

	EPCR = 0xFF;
	EPDR = (U8_T)(phyData);
	EPDR = (U8_T)(phyData >> 8);
	EPCR = (U8_T)(phyAddr & 0x000000FF);
	EPCR = (U8_T)(phyId & 0x000000FF) + BIT6;
	while (1)
	{
		cmdChk = EPCR;
		cmdChk = EPCR;
		if (!(cmdChk & BIT6))
			break;
	}
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_PhyRd(U8_T phyId, U8_T phyAddr, U16_T *phyData)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_PhyRd(U8_T phyId, U8_T phyAddr, U16_T *phyData)
{
	U8_T	cmdChk = 0;
	U8_T	temp1 = 0;
	U8_T	temp2 = 0;

	EPCR = 0xFF;
	EPCR = (U8_T)(phyAddr & 0x000000FF);
	EPCR = (U8_T)(phyId & 0x000000FF) + BIT6 + BIT7;
	while (1)
	{
		cmdChk = EPCR;
		cmdChk = EPCR;
		if (!(cmdChk & BIT6))
			break;
	}
	temp1 = EPDR;
	temp2 = EPDR;
	*phyData = (U16_T)temp1 | ((U16_T)temp2 << 8);
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_I2cWr(U8_T addr, U8_T *ptData, U8_T dataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_I2cWr(U8_T addr, U8_T *ptData, U8_T dataLen)
{
	U8_T	i;

	for (i=0 ; i<dataLen ; i++)
	{
		I2CDR = *(ptData + i);
	}
	I2CCIR = addr;
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_I2cRd(U8_T addr, U8_T *ptData, U8_T dataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_I2cRd(U8_T addr, U8_T *ptData, U8_T dataLen)
{
	U8_T	i;

	I2CCIR = addr;
	for (i=0 ; i<dataLen ; i++)
	{
		*(ptData + i) = I2CDR;
	}
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_SpiWr(U8_T addr, U8_T *ptData, U8_T dataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_SpiWr(U8_T addr, U8_T *ptData, U8_T dataLen)
{
	U8_T	i;

	for (i=0 ; i<dataLen ; i++)
	{
		SPIDR = *(ptData + i);
	}
	SPICIR = addr;
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_SpiRd(U8_T addr, U8_T *ptData, U8_T dataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_SpiRd(U8_T addr, U8_T *ptData, U8_T dataLen)
{
	U8_T	i;

	SPICIR = addr;
	for (i=0 ; i<dataLen ; i++)
	{
		*(ptData + i) = SPIDR;
	}
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_OwWr(U8_T addr, U8_T *ptData, U8_T dataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_OwWr(U8_T addr, U8_T *ptData, U8_T dataLen)
{
	U8_T	i;

	for (i=0 ; i<dataLen ; i++)
	{
		OWDR = *(ptData + i);
	}
	OWCIR = addr;
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_OwRd(U8_T addr, U8_T *ptData, U8_T dataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_OwRd(U8_T addr, U8_T *ptData, U8_T dataLen)
{
	U8_T	i;

	OWCIR = addr;
	for (i=0 ; i<dataLen ; i++)
	{
		*(ptData + i) = OWDR;
	}
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_CanWr(U8_T addr, U8_T *ptData, U8_T dataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_CanWr(U8_T addr, U8_T *ptData, U8_T dataLen)
{
	U8_T	i;

	for (i=0 ; i<dataLen ; i++)
	{
		CANDR = *(ptData + i);
	}
	CANCIR = addr;
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_CanRd(U8_T addr, U8_T *ptData, U8_T dataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_CanRd(U8_T addr, U8_T *ptData, U8_T dataLen)
{
	U8_T	i;

	CANCIR = addr;
	for (i=0 ; i<dataLen ; i++)
	{
		*(ptData + i) = CANDR;
	}
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_SwDmaWr(U8_T addr, U8_T *ptData, U8_T dataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_SwDmaWr(U8_T addr, U8_T *ptData, U8_T dataLen)
{
	U8_T	i;

	for (i=0 ; i<dataLen ; i++)
	{
		DDR = *(ptData + i);
	}
	DCIR = addr;
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL AX11000SLV_SwDmaRd(U8_T addr, U8_T *ptData, U8_T dataLen)
 * Purpose:
 * Params:
 * Returns:
 * Note:
 *--------------------------------------------------------------------------------
 */
BOOL AX11000SLV_SwDmaRd(U8_T addr, U8_T *ptData, U8_T dataLen)
{
	U8_T	i;

	DCIR = addr;
	for (i=0 ; i<dataLen ; i++)
	{
		*(ptData + i) = DDR;
	}
	return TRUE;
}


/* End of ax11000slv.c */
