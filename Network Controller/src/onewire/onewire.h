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
 * Module Name : onewire.h
 * Purpose     : 
 * Author      : Robin Lee
 * Date        : 2005-03-31
 * Notes       :
 * $Log: onewire.h,v $
 * Revision 1.4  2005/08/31 02:06:14  robin6633
 * Added the rom code CRC8 cheching and memory data CRC16 checking.
 *
 * Revision 1.3  2005/08/17 06:48:22  robin6633
 * no message
 *
 * Revision 1.2  2005/08/11 09:00:06  borbin
 * no message
 *
 * Revision 1.1.1.1  2005/06/06 05:55:57  robin6633
 * no message
 *
 *================================================================================
 */
#ifndef ONEWIRE_H
#define ONEWIRE_H

/* INCLUDE FILE DECLARATIONS */
#include	"onewire_cfg.h"


/* NAMING CONSTANT DECLARATIONS */
/* One Wire Register Map */
#define	OWCTRLR					0x00	// onewire control register
#define	OWTRR					0x01	// onewire transmit and receive buffer register
#define	OWISR					0x02	// onewire interrupt status register
#define	OWIER					0x03	// onewire interrupt enable register
#define	OWCMDR					0x04	// onewire command register
#define	OWCLKDIV				0x05	// onewire clock divide register

/* OWCTRLR */
#define	OW_RESET				BIT0	// onewire reset
#define	OW_SRA					BIT1	// onewire search rom accelerator
#define	OW_FORCE				BIT2	// force onewire bus drived directly

/* OWISR */
#define	OW_PD					BIT0	// presence detect
#define	OW_PDR					BIT1	// presence detect result
#define	OW_TBE					BIT2	// transmit buffer empty
#define	OW_TSRE					BIT3	// transmit shift register empty
#define	OW_RBF					BIT4	// receive buffer full
#define	OW_RSRF					BIT5	// receive shift register full
#define	OW_SHORT				BIT6	// bus is low before sending out the beginning of a reset or a time slot
#define	OW_LOW					BIT7	// bus is low while the master is in idle

/* OWIER */
#define	OW_PDI_ENB				BIT0	// presence detect interrupt enable
#define	OW_TBEI_ENB				BIT2	// transmit buffer empty interrupt enable
#define	OW_TSREI_ENB			BIT3	// transmit shift register empty interrupt enable
#define	OW_RBFI_ENB				BIT4	// receive buffer full interrupt enable
#define	OW_RSRFI_ENB			BIT5	// receive shift register full interrupt enable
#define	OW_OWSHI_ENB			BIT6	// onewire short interrupt enable
#define	OW_OWLI_ENB				BIT7	// onewire low idle interrupt enable

/* OWCMDR */
#define	OW_LLM					BIT0	// long line mode
#define	OW_PPMM					BIT1	// presence pulse masking mode
#define	OW_FORCE_ENB			BIT2	// force onewire enable
#define	OW_STP_ENB				BIT3	// strong pull-up enable
#define	OW_STP_SPLY				BIT4	// strong pull-up supply
#define	OW_BIT_CTRL				BIT5	// bit control
#define	OW_OD					BIT6	// overdrive

/* OWCLKDIV */
#define	OW_PRE0					BIT0
#define	OW_PRE1					BIT1
#define	OW_DIV0					BIT2
#define	OW_DIV1					BIT3
#define	OW_DIV2					BIT4
#define	OW_CLK_ENB				BIT7	// clock enable

/* OneWire Definition */
#define	OW_MST_XMIT				BIT0	// master transmit flag
#define	OW_MST_RCVR				BIT1	// master receive flag
#define	OW_BUSY					BIT0	// onewire busy flag

/* OneWire Command */
#define	READ_ROM				0x33	// read rom command
#define	MATCH_ROM				0x55	// match rom command
#define	SEARCH_ROM				0xF0	// search rom command
#define	SKIP_ROM				0xCC	// skip rom command
#define	RESUME_ROM				0xA5	// resume rom command
#define	OD_SKIP_ROM				0x3C	// overdrive skip rom command
#define	OD_MATCH_ROM			0x69	// overdrive match rom command
#define	WRITE_SCRPAD			0x4E	// write scratchpad command
#define	READ_SCRPAD				0xBE	// read scratchpad command
#define	COPY_SCRPAD				0x48	// copy scratchpad command
#define	READ_MEMORY				0xF0	// read memory command
#define	NO_MEM_CMD				0x00	// command fail
#define	CONVERT_T				0x44


/* OneWire State for OwActF */
#define	ROM_CMD_STATE			BIT0	// processing with rom command
#define	ROM_SEQ_STATE			BIT1	// processing with rom code
#define	MEM_CMD_STATE			BIT2	// processing with memory command
#define	MEM_SEQ_STATE			BIT3	// processing with memory data
#define	CRC_ERR					BIT6	// crc check error
#define	IDLE_STATE				BIT7	// bus idle

#define	AA_FLAG					BIT7	// authorization accepted flag of onewire device register
#define	PF_FLAG					BIT5	// lost power or less byte flag of onewire device register

#define	MAX_DATA_LEN			0x90	// maximum size of memory data
#define	MAX_SERIAL_BUF_NUM		3		// maximum device number


/* MACRO DECLARATIONS */


/* TYPE DECLARATIONS */
typedef struct	ow_rom {
	U8_T		Fmcode;
	U8_T		Sernum[6];
	U8_T		Crc08;
}	OW_ROM;

typedef struct	ow_mem {
	U8_T		Tgaddr1;
	U8_T		Tgaddr2;
	U8_T		Es;
	U8_T		Memdata[8];
	U8_T		Crc16ln;
	U8_T		Crc16hn;
}	OW_MEM;


typedef struct	ow_buf {
	U8_T		Romcmd;
	U8_T		Romarray[8];
	U8_T		Memcmd;
	U8_T		Memarray[13];
}	OW_BUF;


/* GLOBAL VARIABLES */


/* EXPORTED SUBPROGRAM SPECIFICATIONS */
void	ONEWIRE_Setup(U8_T ctrlCmd1, U8_T ctrlCmd2, U8_T intrEnb, U8_T clkDiv);
BOOL	ONEWIRE_Reset(void);
void	ONEWIRE_Func(void);
void	ONEWIRE_Post(void);
void	ONEWIRE_SetClk(U8_T clkDiv);
void	ONEWIRE_SetCtrlReg(U8_T ctrlReg);
void	ONEWIRE_SetCmdReg(U8_T cmdReg);
void	ONEWIRE_DeSetCmdReg(U8_T cmdReg);
void	ONEWIRE_SendPkt(OW_BUF *ptSend);
OW_BUF	*ONEWIRE_GetCurBuf(void);
void	ONEWIRE_SetCrc8(U8_T setVal);
void	ONEWIRE_SetCrc16(U16_T setVal);
void	ONEWIRE_StartSearch(void);
U8_T	ONEWIRE_DoCrc8(U8_T byteData);
U16_T	ONEWIRE_DoCrc16(U16_T wordData);
BOOL	ONEWIRE_StateChk(U8_T state);
void	ONEWIRE_StateFunc(void);
U8_T	*ONEWIRE_GetRomCode(void);
void	ONEWIRE_RomCmdChk(void);
void	ONEWIRE_SearchRomFunc(void);
BOOL	ONEWIRE_LastDeviceChk(void);
void	ONEWIRE_Cmd(U8_T cmdType, U8_T owCmdIndex, U8_T *owData);
BOOL	ONEWIRE_Search(U8_T *ptRom);
extern	BOOL	ONEWIRE_ByteXmit(U8_T owbytedata);
extern	U8_T ONEWIRE_ByteRcvr(void);
BOOL	ONEWIRE_ReadRom(U8_T *ptRom);
BOOL	ONEWIRE_OdSkip(OW_BUF *ptOdSkip);
#if MEMORY_SECTIONS
U8_T	*ONEWIRE_GetRdMemData(void);
#endif
#if MULTI_DEVICES
BOOL	ONEWIRE_Match(OW_BUF *ptMatch);
#endif


#endif /* End of ONEWIRE_H */
