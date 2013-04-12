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
 * Module Name : onewire.c
 * Purpose     : This module handles the OneWire serial interface driver.
 * Author      : Robin Lee
 * Date        : 2005-03-31
 * Notes       :
 * $Log: onewire.c,v $
 * Revision 1.6  2005/11/24 12:51:35  robin6633
 * initiate values of use.
 *
 * Revision 1.5  2005/11/01 13:19:08  robin6633
 * fixed OD_MATCH_ROM state changed.
 *
 * Revision 1.4  2005/08/31 02:06:07  robin6633
 * Added the rom code CRC8 cheching and memory data CRC16 checking.
 *
 * Revision 1.3  2005/08/17 06:48:22  robin6633
 * no message
 *
 * Revision 1.2  2005/06/14 02:50:12  arthur
 * changed interrupt.h include
 *
 * Revision 1.1.1.1  2005/06/06 05:55:57  robin6633
 * no message
 *
 *================================================================================
 */

/* INCLUDE FILE DECLARATIONS */
#include	<stdio.h>
#include	"reg80390.h"
#include	"types.h"
//#include	"buffer.h"
#include	"onewire.h"
#include	"delay.h"
#include	<intrins.h>
/* STATIC VARIABLE DECLARATIONS */
static OW_BUF	owpkt;
static U8_T		owromcmd = 0;
static U8_T		owmemcmd = 0;
static U8_T		owrombitarray[64];
static U8_T		rcflag = 0;
static U8_T		odflag = 0;
static U16_T	owtxcnt = 0;
static U16_T	owrxcnt = 0;
static U8_T		owstate = 0;
static U8_T		owrdbyte = 0;
static U8_T		crc8 = 0;
static U16_T	crc16 = 0;
static U8_T		owrdmemdata[144];
static U8_T		intrflag = 0;
static U8_T		intrenbflag = 0;
static U8_T		romcodebuf[MAX_SERIAL_BUF_NUM*8] = 
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

static U16_T	lastdiscrepancy = 0;
static U16_T	lastdeviceflag = 0;
static U16_T	lastfamilydiscrepancy = 0;
static U16_T	searchresult = 0;
static U16_T	serialbufnum = 0;

static U16_T	oddparity[16] = { 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };
static U8_T		crc8table[] = {
	  0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
	157,195, 33,127,252,162, 64, 30, 95,  1,227,189, 62, 96,130,220,
	 35,125,159,193, 66, 28,254,160,225,191, 93,  3,128,222, 60, 98,
	190,224,  2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
	 70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89,  7,
	219,133,103, 57,186,228,  6, 88, 25, 71,165,251,120, 38,196,154,
	101, 59,217,135,  4, 90,184,230,167,249, 27, 69,198,152,122, 36,
	248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91,  5,231,185,
	140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
	 17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
	175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
	 50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
	202,148,118, 40,171,245, 23, 73,  8, 86,180,234,105, 55,213,139,
	 87,  9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
	233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
	116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53
};


/* LOCAL SUBPROGRAM DECLARATIONS */
static void		ONEWIRE_IntrBitsEnb(U8_T bits);
static void		ONEWIRE_IntrBitsDisb(U8_T bits);
//static BOOL		ONEWIRE_ByteXmit(U8_T owbytedata);
//static U8_T		ONEWIRE_ByteRcvr(void);
static void		ONEWIRE_RomFunc(void);
static void		ONEWIRE_RomCodeToBit(void);

#if MEMORY_SECTIONS
static void		ONEWIRE_MemCmdChk(void);
static void		ONEWIRE_MemFunc(void);
#endif


/* LOCAL SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * static void ONEWIRE_IntrBitsEnb(U8_T Bits)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
static void ONEWIRE_IntrBitsEnb(U8_T bits)
{
	U8_T	regval = 0;

	intrenbflag = bits;
	ONEWIRE_Cmd(SI_RD, OWIER, &regval);
	regval = regval | bits;
	ONEWIRE_Cmd(SI_WR, OWIER, &regval);
}

/*
 *--------------------------------------------------------------------------------
 * static void ONEWIRE_IntrBitsDisb(U8_T bits)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
static void ONEWIRE_IntrBitsDisb(U8_T bits)
{
	U8_T	regval = 0;

	ONEWIRE_Cmd(SI_RD, OWIER, &regval);
	regval = regval & (~bits);
	ONEWIRE_Cmd(SI_WR, OWIER, &regval);
}

/*
 *--------------------------------------------------------------------------------
 * static BOOL ONEWIRE_ByteXmit(U8_T owbytedata)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL ONEWIRE_ByteXmit(U8_T owbytedata)
{
	U8_T	temprxbyte = 0;
	U8_T	checkflag = 0;

	ONEWIRE_Cmd(SI_WR, OWTRR, &owbytedata);

	intrflag = 0;
	ONEWIRE_IntrBitsEnb(OW_TSREI_ENB);
	while (1)
	{
		if (intrflag & OW_TSRE)
			break;
	}
	intrflag = 0;

//	SiCmd(SI_WR, OWTRR, &owbytedata);
	
	while (1)
	{
		ONEWIRE_Cmd(SI_RD, OWISR, &checkflag);
		if (checkflag & OW_RBF)
			break;
	}

	ONEWIRE_Cmd(SI_RD, OWTRR, &temprxbyte);

	return (temprxbyte == owbytedata) ? TRUE : FALSE;
}

/*
 *--------------------------------------------------------------------------------
 * static U8_T ONEWIRE_ByteRcvr(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
U8_T ONEWIRE_ByteRcvr(void)
{
	U8_T	temptxbyte = 0;
	U8_T	temprxbyte = 0;
	U8_T	checkflag = 0;

	while (1)
	{
		ONEWIRE_Cmd(SI_RD, OWISR, &checkflag);
		if (checkflag & OW_TSRE)
			break;
	}
	temptxbyte = 0xFF;
	ONEWIRE_Cmd(SI_WR, OWTRR, &temptxbyte);

	ONEWIRE_IntrBitsEnb(OW_RBFI_ENB);
	while (!(intrflag & OW_RBF)) {};
	intrflag = 0;

	ONEWIRE_Cmd(SI_RD, OWTRR, &temprxbyte);

	return temprxbyte;
}

/*
 *--------------------------------------------------------------------------------
 * static void ONEWIRE_MemCmdChk(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
#if MEMORY_SECTIONS
static void ONEWIRE_MemCmdChk(void)
{
	if (owstate & MEM_CMD_STATE)
	{
		if (ONEWIRE_ByteXmit(owmemcmd))
		{
			owstate = MEM_SEQ_STATE;
			owtxcnt = 0;
			owrxcnt = 0;
			crc8 = 0;
			crc16 = 0;
		}
		else
		{
			ONEWIRE_Reset();
		}
	}
}
#endif


/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_RomFunc(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_RomFunc(void)
{
	U8_T	cmdregval = 0;
	U8_T	crc8check = 0;
	U8_T	i;

	if ((owromcmd == SKIP_ROM) || (owromcmd == OD_SKIP_ROM))
	{
	}
	else if (owromcmd == READ_ROM)
	{
		if (owrxcnt < 8)
		{
			owpkt.Romarray[owrxcnt] = ONEWIRE_ByteRcvr();
			owrxcnt ++;
			if (owrxcnt == 8)
			{
				owrxcnt = 0;
				rcflag = 0;
				ONEWIRE_SetCrc8(0);
				for (i=0 ; i<8 ; i++)
				{
					crc8check = ONEWIRE_DoCrc8(owpkt.Romarray[i]);
				}
				if (crc8check == 0)
				{
					if (owmemcmd)
						owstate = MEM_CMD_STATE;
					else
						owstate = IDLE_STATE;
				}
				else
				{
					owstate = IDLE_STATE | CRC_ERR;
				}
			}
		}
	}
#if MULTI_DEVICES
	if ((owromcmd == MATCH_ROM) || (owromcmd == OD_MATCH_ROM))
	{
		if (owtxcnt < 8)
		{
			if (!ONEWIRE_ByteXmit(owpkt.Romarray[owtxcnt]))
			{
				odflag = 0;
				/* Setup OneWire Command mode */
				ONEWIRE_Cmd(SI_RD, OWCMDR, &cmdregval);
				cmdregval = cmdregval & ~OW_OD;
				ONEWIRE_Cmd(SI_WR, OWCMDR, &cmdregval);
				ONEWIRE_Reset();
				return;
			}
			owtxcnt ++;
			if (owtxcnt == 8)
			{
				owtxcnt = 0;
				rcflag = 1;
				
				if (owmemcmd)
					owstate = MEM_CMD_STATE;
				else
					owstate = IDLE_STATE;
			}
		}
	}
#endif
	else if (owromcmd == SEARCH_ROM)
	{
		ONEWIRE_SearchRomFunc();
		owstate = IDLE_STATE;
	}
}

#if MEMORY_SECTIONS
/*
 *--------------------------------------------------------------------------------
 * static void ONEWIRE_MemFunc(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
static void ONEWIRE_MemFunc(void)
{
	U8_T	temprxd = 0;
	U8_T	sysclk = 0;

	if (owstate & MEM_SEQ_STATE)
	{
		if (owmemcmd == WRITE_SCRPAD)
		{
			if (owtxcnt < 11)
			{
				ONEWIRE_ByteXmit(owpkt.Memarray[owtxcnt]);
				owtxcnt ++;
				if (owtxcnt == 2)
				{
					owtxcnt ++;
				}
			}
			else
			{
				owpkt.Memarray[owtxcnt] = ONEWIRE_ByteRcvr();
				owtxcnt ++;
				if (owtxcnt == 13)
				{
					owtxcnt = 0;
					owstate = IDLE_STATE;
				}
			}
		}
		else if (owmemcmd == READ_SCRPAD)
		{
			if (owrxcnt < 3)
			{
				owpkt.Memarray[owrxcnt] = ONEWIRE_ByteRcvr();
				owrxcnt ++;
				if (owrxcnt == 3)
				{
					// ES Byte check
					if (!(owpkt.Memarray[2] & AA_FLAG) && !(owpkt.Memarray[2] & PF_FLAG))
						owrdbyte = (owpkt.Memarray[2] & 0x07) - (owpkt.Memarray[0] & 0x07) + 1;
					else
						owstate = IDLE_STATE;
				}
			}
			else
			{
				owpkt.Memarray[owrxcnt] = ONEWIRE_ByteRcvr();
				owrxcnt ++;
				if (owrxcnt == 13)
				{
					owrxcnt = 0;
					owstate = IDLE_STATE;
				}
			}
		}
		else if (owmemcmd == COPY_SCRPAD)
		{
			if (owtxcnt < 3)
			{
				U32_T	i;

				ONEWIRE_ByteXmit(owpkt.Memarray[owtxcnt]);
				owtxcnt ++;
				if (owtxcnt == 3)
				{
					sysclk = CSREPR & 0xC0;
					switch (sysclk)
					{
						case SCS_100M :
							// Baud rate = 9600 @ 100MHz.
							for (i=0 ; i<4800 ; i++)
							{
							}
							break;
						case SCS_50M :
							// Baud rate = 9600 @ 50MHz.
							for (i=0 ; i<2400 ; i++)
							{
							}
							break;
						case SCS_25M :
							// Baud rate = 9600 @ 25MHz.
							for (i=0 ; i<1200 ; i++)
							{
							}
							break;
					}
				}
			}
			else
			{
				temprxd = ONEWIRE_ByteRcvr();
				if (temprxd == 0xAA)
				{
					owtxcnt = 0;
					owstate = IDLE_STATE;
				}
			}
		}
		else if (owmemcmd == CONVERT_T)
		{
			owstate = IDLE_STATE;
		}
		else if (owmemcmd == READ_MEMORY)
		{
			if (owtxcnt < 2)
			{
				ONEWIRE_ByteXmit(owpkt.Memarray[owtxcnt]);
				owtxcnt ++;
				if (owtxcnt == 2)
				{
					owrxcnt = 0;
				}
			}
			else
			{
				owrdmemdata[owrxcnt] = ONEWIRE_ByteRcvr();
				owrxcnt ++;
				if (owrxcnt == MAX_DATA_LEN)
				{
					owtxcnt = 0;
					owrxcnt = 0;
					owstate = IDLE_STATE;
				}
			}
			
		}
	}
}
#endif

/*
 *--------------------------------------------------------------------------------
 * static void ONEWIRE_RomCodeToBit(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
static void ONEWIRE_RomCodeToBit(void)
{
	U8_T	i, j;

	for (i = 0 ; i < 8 ; i ++)
	{
		for (j = 0 ; j < 8 ; j ++)
		{
			owrombitarray[8 * i + j] = (owpkt.Romarray[i] >> j) & BIT0;
		}
	}
}


/* EXPORTED SUBPROGRAM BODIES */

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_RomCmdChk(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_RomCmdChk(void)
{
	U8_T	cmdregval = 0;

		if (ONEWIRE_ByteXmit(owromcmd))
		{
			switch (owromcmd)
			{
				case READ_ROM :
					rcflag = 0;
					owrxcnt = 0;
					owstate = ROM_SEQ_STATE;
					break;
				#if MULTI_DEVICES
				case MATCH_ROM :
					rcflag = 0;
					owstate = ROM_SEQ_STATE;
					ONEWIRE_RomCodeToBit();
				//	ONEWIRE_SetCmdReg(OW_BIT_CTRL);
					break;
				#endif
				case SEARCH_ROM :
					rcflag = 0;
					owstate = ROM_SEQ_STATE;
				//	ONEWIRE_SetCtrlReg(OW_SRA);
					/* initialize for search */
				//	lastdiscrepancy = 0;
				//	lastdeviceflag = FALSE;
				//	lastfamilydiscrepancy = 0;
					break;
				case SKIP_ROM :
					rcflag = 0;
					owstate = MEM_CMD_STATE;
					break;
				case RESUME_ROM :
					if (rcflag == 1)
					{
						owstate = MEM_CMD_STATE;
					}
					else
					{
						ONEWIRE_Reset();
					}
					break;
				case OD_SKIP_ROM :
					rcflag = 0;
					odflag = 1;
					owstate = MEM_CMD_STATE;
					/* Setup OneWire Command mode */
					ONEWIRE_Cmd(SI_RD, OWCMDR, &cmdregval);
					cmdregval = cmdregval | OW_OD;
					ONEWIRE_Cmd(SI_WR, OWCMDR, &cmdregval);
					break;
				#if MULTI_DEVICES
				case OD_MATCH_ROM :
					rcflag = 0;
					odflag = 1;
					owstate = ROM_SEQ_STATE;
				//	ONEWIRE_SetCmdReg(OW_BIT_CTRL);
					/* Setup OneWire Command mode */
					ONEWIRE_Cmd(SI_RD, OWCMDR, &cmdregval);
					cmdregval = cmdregval | OW_OD;
					ONEWIRE_Cmd(SI_WR, OWCMDR, &cmdregval);
					break;
				#endif
			}
		}

}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_Setup(U8_T ctrlcmd1, U8_T ctrlcmd2, U8_T intrenb, U8_T clkdiv)
 * Purpose : Setup the operation mode of One Wire.
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_Setup(U8_T ctrlcmd1, U8_T ctrlcmd2, U8_T intrenb, U8_T clkdiv)
{
	U16_T	i;

	owpkt.Romcmd = 0;
	owpkt.Memcmd = 0;
	for (i=0 ; i<8 ; i++)
		owpkt.Romarray[i] = 0;
	for (i=0 ;  i<8 ; i++)
		owpkt.Memarray[i] = 0;
	owromcmd = 0;
	owmemcmd = 0;
	rcflag = 0;
	odflag = 0;
	owtxcnt = 0;
	owrxcnt = 0;
	owstate = 0;
	owrdbyte = 0;
	crc8 = 0;
	crc16 = 0;
	intrflag = 0;
	intrenbflag = 0;

	lastdiscrepancy = 0;
	lastdeviceflag = 0;
	lastfamilydiscrepancy = 0;
	searchresult = 0;
	serialbufnum = 0;

	for (i=0 ; i<64 ; i++)
		owrombitarray[i] = 0;
	for (i=0 ; i<144 ; i++)	
		owrdmemdata[i] = 0;

	/* Setup OneWire Control mode */
	ONEWIRE_SetCtrlReg(ctrlcmd1);
	/* Setup OneWire Command mode */
	ONEWIRE_SetCmdReg(ctrlcmd2);	
	/* Enable intertupe flag type of OneWire */
	ONEWIRE_IntrBitsEnb(intrenb);
	/* OneWire clock rate selection */
	ONEWIRE_SetClk(clkdiv);
}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_SetClk(U8_T clkdiv)
 * Purpose : Setup the clock devide of One Wire.
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_SetClk(U8_T clkdiv)
{
	/* OneWire clock rate selection */
	ONEWIRE_Cmd(SI_WR, OWCLKDIV, &clkdiv);
}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_SetCtrlReg(U8_T ctrlreg)
 * Purpose : Setup the control register of One Wire.
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_SetCtrlReg(U8_T ctrlreg)
{
	/* Setup OneWire Control mode */
	ONEWIRE_Cmd(SI_WR, OWCTRLR, &ctrlreg);
}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_SetCmdReg(U8_T cmdreg)
 * Purpose : Setup the command register of One Wire.
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_SetCmdReg(U8_T cmdreg)
{
	U8_T	regval;

	ONEWIRE_Cmd(SI_RD, OWCMDR, &regval);
	regval = regval | cmdreg;
	/* Setup OneWire Command mode */
	ONEWIRE_Cmd(SI_WR, OWCMDR, &regval);
}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_DeSetCmdReg(U8_T cmdReg)
 * Purpose : Setup the command register of One Wire.
 * Params  : cmdReg - command register value.
 * Returns : None.
 * Note    : None.
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_DeSetCmdReg(U8_T cmdReg)
{
	U8_T	regVal;

	ONEWIRE_Cmd(SI_RD, OWCMDR, &regVal);
	regVal &= ~cmdReg;
	/* Setup OneWire Command mode */
	ONEWIRE_Cmd(SI_WR, OWCMDR, &regVal);
}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_Func(void)
 * Purpose : Handling serial interface OneWire interrupt function.
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_Func(void)
{
	U8_T	owstatus;

		/* Disable Transmit Buffer Empty Interrupt of OneWire */
		ONEWIRE_IntrBitsDisb(OW_RBFI_ENB | OW_RSRFI_ENB | OW_TBEI_ENB | OW_TSREI_ENB);
	
		ONEWIRE_Cmd(SI_RD, OWISR, &owstatus);

		if (owstatus & OW_PD)
		{
			owromcmd = owpkt.Romcmd;
			owmemcmd = owpkt.Memcmd;
			owtxcnt  = 0;
			owrxcnt  = 0;
			owstate = ROM_CMD_STATE;
			intrflag = OW_PDR;
		}
		if ((owstatus & OW_RBF) && (intrenbflag & OW_RBFI_ENB))
		{
			intrflag |= OW_RBF;
		}
		if ((owstatus & OW_TSRE) && (intrenbflag & OW_TSREI_ENB))
		{
			intrflag |= OW_TSRE;
		}
}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_SearchRom(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_SearchRomFunc(void)
{
//	U16_T	i;
	U16_T	bitnumber = 1;
	U16_T	lastzero = 0;
	U16_T	rombytenumber = 0;
	U16_T	rombit = 0;
	U16_T	cmprombit = 0;
	U8_T	rombytemask = 1;
	U8_T	searchbit = 0;
	U8_T	lastcrc8 = 0;

	bitnumber = 1;
	lastzero = 0;
	rombytenumber = 0;
	rombytemask = 1;
	searchresult = 0;
	ONEWIRE_SetCrc8(0);
	// if the last search was not the last one
//	if (1)
//	{
		ONEWIRE_SetCmdReg(OW_BIT_CTRL);
		// loop to do the search
		do // loop until through all ROM bytes 0-7
		{
			// read a bit and its complement
			rombit = ONEWIRE_ByteRcvr();
			cmprombit = ONEWIRE_ByteRcvr();
			// check for no devices on 1-wire
			if ((rombit == 1) && (cmprombit == 1))
				ONEWIRE_Reset();
			else
			{
				// all devices coupled have 0 or 1
				if (rombit != cmprombit)
					searchbit = rombit; // bit write value for search
				else
				{
					// if this discrepancy is before the Last Discrepancy
					// on a previous next then pick the same as last time
					if (bitnumber < lastdiscrepancy)
						searchbit = ((owpkt.Romarray[rombytenumber] & rombytemask) > 0);
					else
					// if equal to last pick 1, if not then pick 0
						searchbit = (bitnumber == lastdiscrepancy);
					// if 0 was picked then record its position in LastZero
					if (searchbit == 0)
					{
						lastzero = bitnumber;
						// check for Last discrepancy in family
						if (lastzero < 9)
							lastfamilydiscrepancy = lastzero;
					}
				}
				// set or clear the bit in the ROM byte rom_byte_number
				// with mask rom_byte_mask
				if (searchbit == 1)
					owpkt.Romarray[rombytenumber] |= rombytemask;
				else
					owpkt.Romarray[rombytenumber] &= ~rombytemask;
				// serial number search direction write bit
				if (!ONEWIRE_ByteXmit(searchbit))
					searchresult = FALSE;
				// increment the byte counter id_bit_number
				// and shift the mask rom_byte_mask
				bitnumber ++;
				rombytemask <<= 1;
				// if the mask is 0 then go to new SerialNum byte RomByteNumber and reset mask
				if (rombytemask == 0)
				{
					lastcrc8 = ONEWIRE_DoCrc8(owpkt.Romarray[rombytenumber]); // accumulate the CRC
					rombytenumber ++;
					rombytemask = 1;
				}
			}
		}
		while (rombytenumber < 8) ;
		ONEWIRE_DeSetCmdReg(OW_BIT_CTRL);
		// if the search was successful then
		if ((bitnumber > 64) && (lastcrc8 == 0))
		{
			// search successful so set lastdiscrepancy,lastdeviceflag,search_result
			lastdiscrepancy = lastzero;
			// check for last device
			if (lastdiscrepancy == 0)
			{
				lastdeviceflag = 1;
			}

			searchresult = TRUE;
		}
//	}
}

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_StateChk(U8_T state)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL ONEWIRE_StateChk(U8_T state)
{
	if (owstate & state)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_LastDeviceChk(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL ONEWIRE_LastDeviceChk(void)
{
	if (lastdeviceflag)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_StateFunc(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_StateFunc(void)
{
	if (owstate & ROM_SEQ_STATE)
	{
		ONEWIRE_RomFunc();
	}
	else if (owstate & ROM_CMD_STATE)
	{
		ONEWIRE_RomCmdChk();
	}
#if MEMORY_SECTIONS
	else if (owstate & MEM_SEQ_STATE)
	{
		ONEWIRE_MemFunc();
	}
	else if (owstate & MEM_CMD_STATE)
	{
		ONEWIRE_MemCmdChk();
	}
#endif
}

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_Reset(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL ONEWIRE_Reset(void)
{
	U8_T	resetcmd = 0;

	owstate = ROM_CMD_STATE;
	intrflag = 0;
	resetcmd = OW_RESET;
	ONEWIRE_Cmd(SI_WR, OWCTRLR, &resetcmd);

	while (1)
	{
		if (intrflag & OW_PDR)
			break;
	}

	intrflag = 0;

	ONEWIRE_Cmd(SI_RD, OWISR, &resetcmd);

	return (resetcmd & OW_PDR) ? FALSE : TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_SetCrc8(U8_T setval)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_SetCrc8(U8_T setval)
{
   crc8 = setval;
}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_SetCrc16(U16_T setval)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_SetCrc16(U16_T setval)
{
   crc16 = setval;
}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_StartSearch(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_StartSearch(void)
{
	lastdiscrepancy = 0;
	lastdeviceflag = 0;
	lastfamilydiscrepancy = 0;
	serialbufnum = 0;
}

/*
 *--------------------------------------------------------------------------------
 * U8_T ONEWIRE_DoCrc8(U8_T bytedata)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
U8_T ONEWIRE_DoCrc8(U8_T bytedata)
{
	crc8 = crc8table[crc8 ^ bytedata];
	return crc8;
}

/*
 *--------------------------------------------------------------------------------
 * U16_T DoCrc16(U16_T worddata)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
U16_T ONEWIRE_DoCrc16(U16_T worddata)
{
	worddata = (worddata ^ (crc16 & 0x00FF)) & 0x00FF;
	crc16 >>= 8;

	if (oddparity[worddata & 0x000F] ^ oddparity[worddata >> 4])
		crc16 ^= 0xC001;

	worddata <<= 6;
	crc16 ^= worddata;
	worddata <<= 1;
	crc16 ^= worddata;

	return crc16;
}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_SendPkt(OW_BUF *ptsend)
 * Purpose : 
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_SendPkt(OW_BUF *ptsend)
{
	owpkt = *ptsend;
}

/*
 *--------------------------------------------------------------------------------
 * OW_BUF *ONEWIRE_GetCurBuf(void)
 * Purpose : 
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
OW_BUF *ONEWIRE_GetCurBuf(void)
{
//	for (i=0 ; i<8 ; i++)
//		P0=owpkt.RomArray[i];
	return (&owpkt);
}

#if MEMORY_SECTIONS
/*
 *--------------------------------------------------------------------------------
 * U8_T *ONEWIRE_GetRdMemData(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
U8_T *ONEWIRE_GetRdMemData(void)
{
	return (&owrdmemdata[0]);
}
#endif

/*
 *--------------------------------------------------------------------------------
 * U8_T *ONEWIRE_GetRomCode(void)
 * Purpose :
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
U8_T *ONEWIRE_GetRomCode(void)
{
	return (&romcodebuf[0]);
}

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_Search(U8_T *ptrom)
 * Purpose : Handling serial interface OneWire interrupt function.
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL ONEWIRE_Search(U8_T *ptrom)
{
	U16_T	i, j;
	OW_BUF *ptsearch = NULL;

	for (j=0 ; j<MAX_SERIAL_BUF_NUM ; j++)
	{
		for (i=0 ; i<8 ; i++)
		{
			romcodebuf[i+(j*8)] = 0;
		}
	}
	i=0;
	j=0;
//	ptsearch = (OW_BUF *)GetPktBuf();
	ptsearch = &owpkt;

	ptsearch->Romcmd = SEARCH_ROM;
	for (i=0 ; i<8 ; i++)
		ptsearch->Romarray[i] = 0;
	ptsearch->Memcmd = 0;
	for (i=0 ; i<8 ; i++)
		ptsearch->Memarray[i] = 0;
	ONEWIRE_SendPkt(ptsearch);
	ONEWIRE_StartSearch();

	while (1)
	{
		if (!ONEWIRE_Reset())
			break;
		while (1)
		{
			ONEWIRE_StateFunc();
			if (ONEWIRE_StateChk(IDLE_STATE) == TRUE)
				break;
		}
		ptsearch = ONEWIRE_GetCurBuf();

		for (i=0 ; i<8 ; i++)
		{
			*(ptrom + (i+(j*8))) = ptsearch->Romarray[i];
			romcodebuf[i+(j*8)] = ptsearch->Romarray[i];
		}
		j ++;

		if (j == MAX_SERIAL_BUF_NUM)
			break;
		if (ONEWIRE_LastDeviceChk())
			break;
	}
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_Match(OW_BUF *ptmatch)
 * Purpose : Handling serial interface OneWire interrupt function.
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
#if MULTI_DEVICES
BOOL ONEWIRE_Match(OW_BUF *ptmatch)
{
	ONEWIRE_SendPkt(ptmatch);

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

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_ReadRom(U8_T *ptrom)
 * Purpose : Handling serial interface OneWire interrupt function.
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL ONEWIRE_ReadRom(U8_T *ptrom)
{
	U16_T	i;
	OW_BUF XDATA	*ptreadrom = NULL;

//	ptreadrom = (OW_BUF *)GetPktBuf();
	ptreadrom = &owpkt;

	ptreadrom->Romcmd = READ_ROM;
	for (i=0 ; i<8 ; i++)
		ptreadrom->Romarray[i] = 0;
	ptreadrom->Memcmd = 0;

	ONEWIRE_SendPkt(ptreadrom);

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

	ptreadrom = ONEWIRE_GetCurBuf();
	for (i=0 ; i<8 ; i++)
	{
		*(ptrom + i) = ptreadrom->Romarray[i];
	}

	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * BOOL ONEWIRE_OdSkip(OW_BUF *ptodskip)
 * Purpose : Handling serial interface OneWire interrupt function.
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
BOOL ONEWIRE_OdSkip(OW_BUF *ptodskip)
{
	ONEWIRE_SendPkt(ptodskip);

	if (!ONEWIRE_Reset())
		return FALSE;

	while (1)
	{
		ONEWIRE_StateFunc();
		if (ONEWIRE_StateChk(MEM_CMD_STATE) == TRUE)
			break;
	}
	
	return TRUE;
}

/*
 *--------------------------------------------------------------------------------
 * void ONEWIRE_Cmd(U8_T cmdtype, U8_T owcmdindex, U8_T *owdata)
 * Purpose : Accessing the OneWire interface indirectly through OneWire's SFR.
 * Params  :
 * Returns :
 * Note    :
 *--------------------------------------------------------------------------------
 */
void ONEWIRE_Cmd(U8_T cmdtype, U8_T owcmdindex, U8_T *owdata)
{
	if (cmdtype == SI_WR)
	{
		OWDR = *owdata;
		OWCIR = owcmdindex;
	}
	else if (cmdtype == SI_RD)
	{
		OWCIR = owcmdindex;
		*owdata = OWDR;
	}
}

/* End of onewire.c */
