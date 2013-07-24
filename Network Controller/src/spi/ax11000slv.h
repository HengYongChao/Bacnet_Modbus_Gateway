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
 * Module Name : ax11000slv.h
 * Purpose     : A header file belongs to the slave function of AX11000 module.
 * Author      : Robin Lee
 * Date        : 2006-09-20
 * Notes       : None.
 * $Log$
 *================================================================================
 */
#ifndef AX11000SLV_H
#define AX11000SLV_H

/* INCLUDE FILE DECLARATIONS */


/* NAMING CONSTANT DECLARATIONS */
#define		SFR_P0			0x80 // Port 0
#define		SFR_SP			0x81
#define		SFR_DPL0		0x82 // Data Pointer 0 Low Byte
#define		SFR_DPH0		0x83 // Data Pointer 0 High Byte
#define		SFR_DPL1		0x84 // Data Pointer 1 Low Byte
#define		SFR_DPH1		0x85 // Data Pointer 1 High Byte
#define		SFR_DPS			0x86 // Data Pointers Select Register
#define		SFR_PCON		0x87 // Power Configuration Register
#define		SFR_TCON		0x88 // Timer 0,1 Configuration Register
#define		SFR_TMOD		0x89 // Timer 0,1 Control Mode Register
#define		SFR_TL0			0x8A // Timer 0 Low Byte Counter
#define		SFR_TL1			0x8B
#define		SFR_TH0			0x8C
#define		SFR_TH1			0x8D
#define		SFR_CKCON		0x8E // Clock Control Register
#define		SFR_CSREPR		0x8F // Software Reset and External Program RAM Select Register

#define		SFR_P1			0x90
#define		SFR_EIF			0x91 // Extended Interrupt Flag Register
#define		SFR_WTST		0x92 // Program Wait States Register
#define		SFR_DPX0		0x93 // Data Pointer Extended Register 0
#define		SFR_SDSTSR		0x94
#define		SFR_DPX1		0x95 // Data Pointer Extended Register 1
#define		SFR_I2CCIR		0x96
#define		SFR_I2CDR		0x97
#define		SFR_SCON0		0x98 // UART 0 Configuration Register
#define		SFR_SBUF0		0x99 // UART 0 Buffer Register
#define		SFR_DBAR		0x9A // DMA Bus Arbitration Register
#define		SFR_DCIR		0x9B // DMA Command Index Register
#define		SFR_DDR			0x9C // DMA Data Register
#define		SFR_ACON		0x9D // Address Control Register
#define		SFR_PISSR1		0x9E // Peripheral Interrupt Status Summary Register 1
#define		SFR_PISSR2		0x9F // Peripheral Interrupt Status Summary Register 2

#define		SFR_P2			0xA0 // Port 2
#define		SFR_LMSR_LSAIER	0xA1 // Local Bus Mode Setup Register;Local Bus Slave mode Action and Interrupt Enable Register
#define		SFR_LCR_LSCR	0xA2 // Local Bus Command Register;Local Bus Slave mode Command Register
#define		SFR_LSR_LSSR	0xA3 // Local Bus Status Register;Local Bus Slave mode Status Register
#define		SFR_LDALR_XMWLR	0xA4 // Local Bus Device Address Low Register;External Master Write-read Low Register
#define		SFR_LDAHR_XMWHR	0xA5 // Local Bus Device Address High Register;External Master Write-read High Register
#define		SFR_LDCSR_XMRLR	0xA6 // Local Bus Device Chip Select Register;External Master Read-only Low Register
#define		SFR_XMRHR		0xA7 // External Master Read-only High Register

#define		SFR_IE			0xA8 // Interrupt Enable register
#define		SFR_LDLR		0xA9 // Local Bus Data Low Register
#define		SFR_LDHR		0xAA // Local Bus Data High Register
#define		SFR_LDMLR		0xAB // Local Bus DMA Address Low Register
#define		SFR_LDMMR		0xAC // Local Bus DMA Address Medium Register
#define		SFR_LDMHR		0xAD // Local Bus DMA Address High Register
#define		SFR_TCIR		0xAE // TOE Command Index Register
#define		SFR_TDR			0xAF // TOE Data Register

#define		SFR_P3			0xB0 // Port 3
#define		SFR_CCAPL0		0xB1 // PCA Module 0 Compare/Capture Low Byte Register
#define		SFR_CCAPL1		0xB2 // PCA Module 1 Compare/Capture Low Byte Register
#define		SFR_CCAPL2		0xB3 // PCA Module 2 Compare/Capture Low Byte Register
#define		SFR_CCAPL3		0xB4 // PCA Module 3 Compare/Capture Low Byte Register
#define		SFR_CCAPL4		0xB5 // PCA Module 4 Compare/Capture Low Byte Register
#define		SFR_MCIR		0xB6 // MAC Command Index Register
#define		SFR_MDR			0xB7 // MAC Data Register
#define		SFR_IP			0xB8 // Interrupt Priority Register
#define		SFR_CCAPH0		0xB9 // PCA Module 0 Compare/Capture High Byte Register
#define		SFR_CCAPH1		0xBA // PCA Module 1 Compare/Capture High Byte Register
#define		SFR_CCAPH2		0xBB // PCA Module 2 Compare/Capture High Byte Register
#define		SFR_CCAPH3		0xBC // PCA Module 3 Compare/Capture High Byte Register
#define		SFR_CCAPH4		0xBD // PCA Module 4 Compare/Capture High Byte Register
#define		SFR_EPCR		0xBE // Ethernet PHY Command Index Register
#define		SFR_EPDR		0xBF // Ethernet PHY Data Register

#define		SFR_SCON1		0xC0 // UART 1 Configuration Register
#define		SFR_SBUF1		0xC1 // UART 1 Buffer Register
#define		SFR_CMOD		0xC2 // PCA Timer/Counter Mode Register
#define		SFR_CCON		0xC3 // PCA Timer/Counter Control Register
#define		SFR_CL			0xC4 // PCA Timer/Counter Low
#define		SFR_CH			0xC5 // PCA Timer/Counter High
#define		SFR_T2CON		0xC8 // Timer 2 Configuration Register
#define		SFR_T2IF		0xC9 // Timer 2 Interrupt Flags
#define		SFR_RLDL		0xCA // Timer 2 Reload Low Byte
#define		SFR_RLDH		0xCB // Timer 2 Reload High Byte
#define		SFR_TL2			0xCC // Timer 2 Low Byte Counter
#define		SFR_TH2			0xCD // Timer 2 High Byte Counter
#define		SFR_SPICIR		0xCE // SPI Command Index Register
#define		SFR_SPIDR		0xCF // SPI Data Register

#define		SFR_PSW			0xD0 // Program Status Word
#define		SFR_CCAPM0		0xD1 // PCA Compare/Capture Module Mode Register 0
#define		SFR_CCAPM1		0xD2 // PCA Compare/Capture Module Mode Register 1
#define		SFR_CCAPM2		0xD3 // PCA Compare/Capture Module Mode Register 2
#define		SFR_CCAPM3		0xD4 // PCA Compare/Capture Module Mode Register 3
#define		SFR_CCAPM4		0xD5 // PCA Compare/Capture Module Mode Register 4
#define		SFR_OWCIR		0xD6 // OneWire Command Index Register
#define		SFR_OWDR		0xD7 // OneWire Data Register
#define		SFR_WDCON		0xD8 // Watchdog Configuration
#define		SFR_CANCIR		0xDE // CAN Bus Command Index Register
#define		SFR_CANDR		0xDF // CAN Bus Data Register

#define		SFR_ACC			0xE0 // Accumulator
#define		SFR_UR2_THR_RBR_DLL	0xE1
#define		SFR_UR2_IER_DLH		0xE2
#define		SFR_UR2_IIR_FCR		0xE3
#define		SFR_UR2_LCR			0xE4
#define		SFR_UR2_MCR			0xE5
#define		SFR_UR2_LSR			0xE6
#define		SFR_UR2_MSR			0xE7
#define		SFR_EIE			0xE8 // External Interrupt Enable
#define		SFR_STATUS		0xE9 // Status Register
#define		SFR_MXAX		0xEA // MOVX @Ri Extended Register
#define		SFR_TA			0xEB // Timed Access Protection

#define		SFR_B			0xF0 // B Working Register
#define		SFR_EIP			0xF8 // Extended Interrupt Priority Register
#define		SFR_MD0			0xF9 // MDU Data 0
#define		SFR_MD1			0xFA // MDU Data 1
#define		SFR_MD2			0xFB // MDU Data 2
#define		SFR_MD3			0xFC // MDU Data 3
#define		SFR_MD4			0xFD // MDU Data 4
#define		SFR_MD5			0xFE // MDU Data 5
#define		SFR_ARCON		0xFF // MDU Control Register

#define		SFR_C6			0xC6
#define		SFR_C7			0xC7
#define		SFR_D9			0xD9
#define		SFR_DA			0xDA
#define		SFR_DB			0xDB
#define		SFR_DC			0xDC
#define		SFR_DD			0xDD
#define		SFR_EC			0xEC
#define		SFR_ED			0xED
#define		SFR_EE			0xEE
#define		SFR_EF			0xEF
#define		SFR_F1			0xF1
#define		SFR_F2			0xF2
#define		SFR_F3			0xF3
#define		SFR_F4			0xF4
#define		SFR_F5			0xF5
#define		SFR_F6			0xF6
#define		SFR_F7			0xF7


/* MACRO DECLARATIONS */
sfr		SFRC6 =			0xC6;
sfr		SFRC7 =			0xC7;
sfr		SFRD9 =			0xD9;
sfr		SFRDA =			0xDA;
sfr		SFRDB =			0xDB;
sfr		SFRDC = 		0xDC;
sfr		SFRDD =			0xDD;
sfr		SFREC =			0xEC;
sfr		SFRED =			0xED;
sfr		SFREE =			0xEE;
sfr		SFREF =			0xEF;
sfr		SFRF1 =			0xF1;
sfr		SFRF2 =			0xF2;
sfr		SFRF3 =			0xF3;
sfr		SFRF4 =			0xF4;
sfr		SFRF5 =			0xF5;
sfr		SFRF6 =			0xF6;
sfr		SFRF7 =			0xF7;


/* TYPE DECLARATIONS */


/* GLOBAL VARIABLES */


/* EXPORTED SUBPROGRAM SPECIFICATIONS */
BOOL AX11000SLV_SfrWr(U8_T sfrAddr, U8_T sfrData);
BOOL AX11000SLV_SfrRd(U8_T sfrAddr, U8_T *sfrData);
BOOL AX11000SLV_ExtMemWr(U32_T extMemAddr, U8_T extMemData);
BOOL AX11000SLV_ExtMemRd(U32_T extMemAddr, U8_T *extMemData);
BOOL AX11000SLV_ToeWr(U8_T toeAddr, U8_T *ptToeData, U8_T toeDataLen);
BOOL AX11000SLV_ToeRd(U8_T toeAddr, U8_T *ptToeData, U8_T toeDataLen);
BOOL AX11000SLV_MacWr(U8_T macAddr, U8_T *ptMacData, U8_T macDataLen);
BOOL AX11000SLV_MacRd(U8_T macAddr, U8_T *ptMacData, U8_T macDataLen);
BOOL AX11000SLV_PhyWr(U8_T phyId, U8_T phyAddr, U16_T phyData);
BOOL AX11000SLV_PhyRd(U8_T phyId, U8_T phyAddr, U16_T *phyData);
BOOL AX11000SLV_I2cWr(U8_T addr, U8_T *ptData, U8_T dataLen);
BOOL AX11000SLV_I2cRd(U8_T addr, U8_T *ptData, U8_T dataLen);
BOOL AX11000SLV_SpiWr(U8_T addr, U8_T *ptData, U8_T dataLen);
BOOL AX11000SLV_SpiRd(U8_T addr, U8_T *ptData, U8_T dataLen);
BOOL AX11000SLV_OwWr(U8_T addr, U8_T *ptData, U8_T dataLen);
BOOL AX11000SLV_OwRd(U8_T addr, U8_T *ptData, U8_T dataLen);
BOOL AX11000SLV_CanWr(U8_T addr, U8_T *ptData, U8_T dataLen);
BOOL AX11000SLV_CanRd(U8_T addr, U8_T *ptData, U8_T dataLen);
BOOL AX11000SLV_SwDmaWr(U8_T addr, U8_T *ptData, U8_T dataLen);
BOOL AX11000SLV_SwDmaRd(U8_T addr, U8_T *ptData, U8_T dataLen);


#endif /* End of AX11000SLV_H */
