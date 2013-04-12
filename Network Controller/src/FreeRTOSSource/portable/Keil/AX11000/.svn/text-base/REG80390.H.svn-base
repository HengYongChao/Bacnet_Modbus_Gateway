/*--------------------------------------------------------------------------
AX110XX.H

Header file for the AX110XX.
Copyright (c) 2001 Keil Software, Inc.  All rights reserved.
--------------------------------------------------------------------------*/

/*------------------------------------------------
Make sure that this file gets included only once.
------------------------------------------------*/
#ifndef AX110XX_HEADER_FILE
#define AX110XX_HEADER_FILE		1

/*------------------------------------------------
Byte Registers
------------------------------------------------*/
sfr	P0			= 0x80;// Port 0
sfr	SP			= 0x81;// Stack Pointer
sfr	DPL0		= 0x82;// Data Pointer 0 Low Byte
sfr	DPH0		= 0x83;// Data Pointer 0 High Byte
sfr	DPL			= 0x82;// Data Pointer 0 Low Byte
sfr	DPH			= 0x83;// Data Pointer 0 High Byte
sfr	DPL1		= 0x84;// Data Pointer 1 Low Byte
sfr	DPH1		= 0x85;// Data Pointer 1 High Byte
sfr	DPS			= 0x86;// Data Pointers Select Register
sfr	PCON		= 0x87;// Power Configuration Register
sfr TCON		= 0x88;// Timer 0,1 Configuration Register
sfr TMOD		= 0x89;// Timer 0,1 Control Mode Register
sfr TL0			= 0x8A;// Timer 0 Low Byte Counter
sfr TL1			= 0x8B;// Timer 1 Low Byte Counter
sfr TH0			= 0x8C;// Timer 0 High Byte Counter
sfr TH1			= 0x8D;// Timer 1 High Byte Counter
sfr CKCON		= 0x8E;// Clock Control Register
sfr CSREPR		= 0x8F;// Software Reset and External Program RAM Select Register

sfr P1			= 0x90;// Port 1
sfr EIF			= 0x91;// Extended Interrupt Flag Register
sfr WTST		= 0x92;// Program Wait States Register
sfr DPX0		= 0x93;// Data Pointer Extended Register 0
sfr DPX			= 0x93;// Data Pointer Extended Register 0
sfr	SDSTSR		= 0x94;// Software Timer and Software DMA complete interrupt status
sfr DPX1		= 0x95;// Data Pointer Extended Register 1
sfr I2CCIR		= 0x96;// I2C Command Index Register
sfr I2CDR		= 0x97;// I2C Data Register
sfr SCON0		= 0x98;// UART 0 Configuration Register
sfr SBUF0		= 0x99;// UART 0 Buffer Register
sfr DBAR		= 0x9A;// DMA Bus Arbitration Register
sfr DCIR		= 0x9B;// DMA Command Index Register
sfr DDR			= 0x9C;// DMA Data Register
sfr ACON		= 0x9D;// Address Control Register
sfr PISSR1		= 0x9E;// Peripheral Interrupt Status Summary Register 1
sfr PISSR2		= 0x9F;// Peripheral Interrupt Status Summary Register 2

sfr P2			= 0xA0;// Port 2
/* Local Bus Master Mode */
sfr LMSR		= 0xA1;// Local Bus Mode Setup Register
sfr LCR			= 0xA2;// Local Bus Command Register
sfr LSR			= 0xA3;// Local Bus Status Register
sfr LDALR		= 0xA4;// Local Bus Device Address Low Register
sfr LDAHR		= 0xA5;// Local Bus Device Address High Register
sfr LDCSR		= 0xA6;// Local Bus Device Chip Select Register
/* Local Bus Slave Mode */
sfr LSAIER		= 0xA1;// Local Bus Slave mode Action and Interrupt Enable Register
sfr LSCR		= 0xA2;// Local Bus Slave mode Command Register
sfr LSSR		= 0xA3;// Local Bus Slave mode Status Register
sfr XMWLR		= 0xA4;// External Master Write-read Low Register
sfr XMWHR		= 0xA5;// External Master Write-read High Register
sfr XMRLR		= 0xA6;// External Master Read-only Low Register
sfr XMRHR		= 0xA7;// External Master Read-only High Register

sfr IE			= 0xA8;// Interrupt Enable register
sfr LDLR		= 0xA9;// Local Bus Data Low Register
sfr LDHR		= 0xAA;// Local Bus Data High Register
sfr DMALR		= 0xAB;// Local Bus DMA Address Low Register
sfr DMAMR		= 0xAC;// Local Bus DMA Address Medium Register
sfr DMAHR		= 0xAD;// Local Bus DMA Address High Register
sfr TCIR		= 0xAE;// TOE Command Index Register
sfr	TDR			= 0xAF;// TOE Data Register

sfr P3			= 0xB0;// Port 3
sfr CCAPL0      = 0xB1;// PCA Module 0 Compare/Capture Low Byte Register
sfr CCAPL1      = 0xB2;// PCA Module 1 Compare/Capture Low Byte Register
sfr CCAPL2      = 0xB3;// PCA Module 2 Compare/Capture Low Byte Register
sfr CCAPL3      = 0xB4;// PCA Module 3 Compare/Capture Low Byte Register
sfr CCAPL4      = 0xB5;// PCA Module 4 Compare/Capture Low Byte Register
sfr MCIR		= 0xB6;// MAC Command Index Register
sfr MDR			= 0xB7;// MAC Data Register
sfr IP			= 0xB8;// Interrupt Priority Register
sfr CCAPH0      = 0xB9;// PCA Module 0 Compare/Capture High Byte Register
sfr CCAPH1      = 0xBA;// PCA Module 1 Compare/Capture High Byte Register
sfr CCAPH2      = 0xBB;// PCA Module 2 Compare/Capture High Byte Register
sfr CCAPH3      = 0xBC;// PCA Module 3 Compare/Capture High Byte Register
sfr CCAPH4      = 0xBD;// PCA Module 4 Compare/Capture High Byte Register
sfr EPCR		= 0xBE;// Ethernet PHY Command Index Register
sfr EPDR		= 0xBF;// Ethernet PHY Data Register

sfr SCON1		= 0xC0;// UART 1 Configuration Register
sfr SBUF1		= 0xC1;// UART 1 Buffer Register
sfr CMOD		= 0xC2;// PCA Timer/Counter Mode Register
sfr CCON		= 0xC3;// PCA Timer/Counter Control Register
sfr CL			= 0xC4;// PCA Timer/Counter Low
sfr CH			= 0xC5;// PCA Timer/Counter High
sfr T2CON		= 0xC8;// Timer 2 Configuration Register
sfr T2IF		= 0xC9;// Timer 2 Interrupt Flags
sfr RLDL		= 0xCA;// Timer 2 Reload Low Byte
sfr RLDH		= 0xCB;// Timer 2 Reload High Byte
sfr TL2			= 0xCC;// Timer 2 Low Byte Counter
sfr TH2			= 0xCD;// Timer 2 High Byte Counter
sfr SPICIR		= 0xCE;// SPI Command Index Register
sfr SPIDR		= 0xCF;// SPI Data Register

sfr PSW			= 0xD0;// Program Status Word
sfr CCAPM0		= 0xD1;// PCA Compare/Capture Module Mode Register 0
sfr CCAPM1		= 0xD2;// PCA Compare/Capture Module Mode Register 1
sfr CCAPM2		= 0xD3;// PCA Compare/Capture Module Mode Register 2
sfr CCAPM3		= 0xD4;// PCA Compare/Capture Module Mode Register 3
sfr CCAPM4		= 0xD5;// PCA Compare/Capture Module Mode Register 4
sfr OWCIR		= 0xD6;// OneWire Command Index Register
sfr OWDR		= 0xD7;// OneWire Data Register
sfr WDCON		= 0xD8;// Watchdog Configuration
sfr CANCIR		= 0xDE;// CAN Bus Command Index Register
sfr CANDR		= 0xDF;// CAN Bus Data Register

sfr ACC			= 0xE0;// Accumulator

/* UART2 registers */
sfr	UR2_DLL		= 0xE1;// High Speed UART2 Divisor Latch Low Register
sfr	UR2_THR		= 0xE1;// High Speed UART2 Transmit Holding Register for Writing
sfr	UR2_RBR		= 0xE1;// High Speed UART2 Receive Buffer Register for Reading
sfr	UR2_DLH		= 0xE2;// High Speed UART2 Divisor Latch High Register
sfr	UR2_IER		= 0xE2;// High Speed UART2 Interrupt Enable Register
sfr	UR2_FCR		= 0xE3;// High Speed UART2 FIFO Control Register for Writing
sfr	UR2_IIR		= 0xE3;// High Speed UART2 Interrupt Identification Register for Reading
sfr	UR2_LCR		= 0xE4;// High Speed UART2 Line Control Register
sfr	UR2_MCR		= 0xE5;// High Speed UART2 Modem Control Register
sfr	UR2_LSR		= 0xE6;// High Speed UART2 Line Status Register
sfr	UR2_MSR		= 0xE7;// High Speed UART2 Modem Status Register

sfr EIE			= 0xE8;// External Interrupt Enable
sfr STATUS		= 0xE9;// Status Register
sfr MXAX		= 0xEA;// MOVX @Ri Extended Register
sfr TA			= 0xEB;// Timed Access Protection

sfr B			= 0xF0;// B Working Register
sfr EIP			= 0xF8;// Extended Interrupt Priority Register
sfr MD0			= 0xF9;// MDU Data 0
sfr MD1			= 0xFA;// MDU Data 1
sfr MD2			= 0xFB;// MDU Data 2
sfr MD3			= 0xFC;// MDU Data 3
sfr MD4			= 0xFD;// MDU Data 4
sfr MD5			= 0xFE;// MDU Data 5
sfr ARCON		= 0xFF;// MDU Control Register


/*------------------------------------------------
P0 (0x80) Bit Registers
------------------------------------------------*/
sbit P0_0		= 0x80;
sbit P0_1		= 0x81;
sbit P0_2		= 0x82;
sbit P0_3		= 0x83;
sbit P0_4		= 0x84;
sbit P0_5		= 0x85;
sbit P0_6		= 0x86;
sbit P0_7		= 0x87;

/*------------------------------------------------
DPS (0x86) Bit Values
------------------------------------------------*/
#define SEL_	0x01
#define TSL_	0x20
#define ID0_	0x40
#define ID1_	0x80

/*------------------------------------------------
PCON (0x87) Bit Values
------------------------------------------------*/
#define PMM_	0x01
#define STOP_	0x02
#define SWB_	0x04
#define PWE_	0x10
#define	SMOD1_	0x40
#define SMOD2_	0x80

/*------------------------------------------------
TCON (0x88) Bit Registers
------------------------------------------------*/
sbit	IT0		= 0x88;
sbit	IE0		= 0x89;
sbit	IT1		= 0x8A;
sbit	IE1		= 0x8B;
sbit	TR0		= 0x8C;
sbit	TF0		= 0x8D;
sbit	TR1		= 0x8E;
sbit	TF1		= 0x8F;

/*------------------------------------------------
TMOD (0x89) Bit Values
------------------------------------------------*/
#define	T0_M0_		0x01
#define	T0_M1_		0x02
#define	T0_CT_		0x04
#define	T0_GATE_	0x08
#define	T1_M0_		0x10
#define	T1_M1_		0x20
#define	T1_CT_		0x40
#define	T1_GATE_	0x80

#define T1_MASK_	0xF0
#define T0_MASK_	0x0F

/*------------------------------------------------
CKCON (0x8E) Bit Values
------------------------------------------------*/
#define MD0_	0x01
#define MD1_	0x02
#define MD2_	0x04
#define	T0M_	0x08
#define	T1M_	0x10
#define	T2M_	0x20
#define WD0_	0x40
#define WD1_	0x80

/*------------------------------------------------
CSREPR (0x8F) Bit Values
------------------------------------------------*/
#define	SW_RST				0x01
#define	SW_RBT				0x02
#define	FARM				0x04
#define	FAES				0x08
#define	PMS					0x10
#define	SCS_100M			0xC0
#define	SCS_75M				0x80
#define	SCS_50M				0x40
#define	SCS_25M				0x00

/*------------------------------------------------
P1 (0x90) Bit Registers
------------------------------------------------*/
sbit P1_0		= 0x90;
sbit P1_1		= 0x91;
sbit P1_2		= 0x92;
sbit P1_3		= 0x93;
sbit P1_4		= 0x94;
sbit P1_5		= 0x95;
sbit P1_6		= 0x96;
sbit P1_7		= 0x97;

/*------------------------------------------------
EIF (0x91) Bit Values
------------------------------------------------*/
#define INT2F		0x01
#define INT3F		0x02
#define INT4F		0x04
#define INT5F		0x08
#define INT6F		0x10

/*------------------------------------------------
SCON0 (0x98) Bit Registers
------------------------------------------------*/
sbit RI0			= 0x98;
sbit TI0			= 0x99;
sbit RB08			= 0x9A;
sbit TB08			= 0x9B;
sbit REN0			= 0x9C;
sbit SM02			= 0x9D;
sbit SM01			= 0x9E;
sbit SM00			= 0x9F;

/*------------------------------------------------
DBAR (0x9A) Bit Values
------------------------------------------------*/
#define	BUS_REQ				0x01
#define	BUS_GRANT			0x80

/*------------------------------------------------
ACON (0x9D) Bit Values
------------------------------------------------*/
#define	FLAT_MODE			0x02
#define	LARGE_MODE			0x00

/*------------------------------------------------
PISSR1 (0x9E) Bit Values
------------------------------------------------*/
#define	LB_INT_STU			0x01
#define	LB_EXT_INT_STU		0x02
#define	ETH_INT_STU			0x04
#define	TOE_INT_STU			0x08
#define	OW_INT_STU			0x10
#define	SPI_INT_STU			0x20
#define	I2C_INT_STU			0x40
#define	CAN_INT_STU			0x80

/*------------------------------------------------
PISSR2 (0x9F) Bit Values
------------------------------------------------*/
#define	UART2_INT_STU		0x01

/*------------------------------------------------
P2 (0xA0) Bit Registers
------------------------------------------------*/
sbit P2_0		= 0xA0;
sbit P2_1		= 0xA1;
sbit P2_2		= 0xA2;
sbit P2_3		= 0xA3;
sbit P2_4		= 0xA4;
sbit P2_5		= 0xA5;
sbit P2_6		= 0xA6;
sbit P2_7		= 0xA7;

/*------------------------------------------------
IE (0xA8) Bit Registers
------------------------------------------------*/
sbit EX0		= 0xA8;       /* 1=Enable External interrupt 0 */
sbit ET0		= 0xA9;       /* 1=Enable Timer 0 interrupt */
sbit EX1		= 0xAA;       /* 1=Enable External interrupt 1 */
sbit ET1		= 0xAB;       /* 1=Enable Timer 1 interrupt */
sbit ES0		= 0xAC;       /* 1=Enable Serial port 0 interrupt */
sbit ET2		= 0xAD;       /* 1=Enable Timer 2 interrupt */
sbit ES1		= 0xAE;       /* 1=Enable Serial port 1 interrupt */
sbit EA			= 0xAF;       /* 0=Disable all interrupts */

/*------------------------------------------------
P3 (0xB0) Bit Registers (Mnemonics & Ports)
------------------------------------------------*/
sbit P3_0		= 0xB0;
sbit P3_1		= 0xB1;
sbit P3_2		= 0xB2;
sbit P3_3		= 0xB3;
sbit P3_4		= 0xB4;
sbit P3_5		= 0xB5;
sbit P3_6		= 0xB6;
sbit P3_7		= 0xB7;

sbit RXD		= 0xB0;       /* Serial data input */
sbit TXD		= 0xB1;       /* Serial data output */
sbit INT0		= 0xB2;       /* External interrupt 0 */
sbit INT1		= 0xB3;       /* External interrupt 1 */
sbit T0			= 0xB4;       /* Timer 0 external input */
sbit T1			= 0xB5;       /* Timer 1 external input */
sbit WR			= 0xB6;       /* External data memory write strobe */
sbit RD			= 0xB7;       /* External data memory read strobe */

/*------------------------------------------------
IP (0xB8) Bit Registers
------------------------------------------------*/
sbit PX0		= 0xB8;
sbit PT0		= 0xB9;
sbit PX1		= 0xBA;
sbit PT1		= 0xBB;
sbit PS0		= 0xBC;
sbit PT2		= 0xBD;
sbit PS1		= 0xBE;

/*------------------------------------------------
SCON1 (0xC0) Bit Registers
------------------------------------------------*/
sbit RI1		= 0xC0;
sbit TI1		= 0xC1;
sbit RB18		= 0xC2;
sbit TB18		= 0xC3;
sbit REN1		= 0xC4;
sbit SM12		= 0xC5;
sbit SM11		= 0xC6;
sbit SM10		= 0xC7;

/*------------------------------------------------
CMOM (0xC2) Bit Values
------------------------------------------------*/
#define PCA_ECF			0x01
#define PCA_T0_OF		0x08
#define	PCA_EXT_CLK		0x0E
#define	PCA_GATE_OFF	0x80

/*------------------------------------------------
CCON (0xC3) Bit Values
------------------------------------------------*/
#define PCA_CCF0		0x01
#define PCA_CCF1		0x02
#define	PCA_CCF2		0x04
#define	PCA_CCF3		0x08
#define	PCA_CCF4		0x10
#define	PCA_CR			0x40
#define	PCA_CF			0x80

/*------------------------------------------------
T2CON (0xC8) Bit Registers
------------------------------------------------*/
sbit CPRL2		= 0xC8;
sbit CT2		= 0xC9;
sbit TR2		= 0xCA;
sbit EXEN2		= 0xCB;
sbit TCLK		= 0xCC;
sbit RCLK		= 0xCD;
sbit EXF2		= 0xCE;
sbit TF2		= 0xCF;

/*------------------------------------------------
PSW (0xD0) Bit Registers
------------------------------------------------*/
sbit P			= 0xD0;
sbit F1			= 0xD1;
sbit OV			= 0xD2;
sbit RS0		= 0xD3;
sbit RS1		= 0xD4;
sbit F0			= 0xD5;
sbit AC			= 0xD6;
sbit CY			= 0xD7;

/*------------------------------------------------
CCAPM0-4 (0xD1-0xD5) Bit Values
------------------------------------------------*/
#define ECCFs		0x01
#define PWMs		0x02
#define	TOGs		0x04
#define	MATs		0x08
#define	CAPNs		0x10
#define	CAPPs		0x20
#define	ECOMs		0x40
#define	CEXs		0x80

/*------------------------------------------------
PSW (0xD8) Bit Registers
------------------------------------------------*/
sbit RWT		= 0xD8;
sbit EWT		= 0xD9;
sbit WTRF		= 0xDA;
sbit WDIF		= 0xDB;

/*------------------------------------------------
Interrupt Vectors:
Interrupt Address = (Number * 8) + 3
------------------------------------------------*/
#define IE0_VECTOR      0  /* 0x03 External Interrupt 0 */
#define TF0_VECTOR      1  /* 0x0B Timer 0 */
#define IE1_VECTOR      2  /* 0x13 External Interrupt 1 */
#define TF1_VECTOR      3  /* 0x1B Timer 1 */
#define SIO_VECTOR      4  /* 0x23 Serial port */

/*------------------------------------------------
UR2_IER (0xE2) Bit Values
------------------------------------------------*/
#define	UR2_RDI_ENB		0x01
#define	UR2_THRI_ENB	0x02
#define	UR2_RLSI_ENB	0x04
#define	UR2_MSI_ENB		0x08

/*------------------------------------------------
UR2_IIR (0xE3) Bit Values
------------------------------------------------*/
#define	UR2_NONE_INTR		0x01
#define	UR2_RLS_INTR		0x06
#define	UR2_RD_TRIG_INTR	0x04
#define	UR2_RD_TI_INTR		0x0C
#define	UR2_THRE_INTR		0x02
#define	UR2_MS_INTR			0x00

/*------------------------------------------------
UR2_FCR (0xE3) Bit Values
------------------------------------------------*/
#define	UR2_FIFO_MODE	0x01
#define	UR2_RXFIFO_RST	0x02
#define	UR2_TXFIFO_RST	0x04
#define	UR2_TRIG_01		0x00
#define	UR2_TRIG_04		0x40
#define	UR2_TRIG_08		0x80
#define	UR2_TRIG_14		0xC0

/*------------------------------------------------
UR2_LCR (0xE4) Bit Values
------------------------------------------------*/
#define	UR2_CHAR_5			0x00
#define	UR2_CHAR_6			0x01
#define	UR2_CHAR_7			0x02
#define	UR2_CHAR_8			0x03
#define	UR2_STOP_10			0x00
#define	UR2_STOP_15			0x04
#define	UR2_PARITY_ENB		0x08
#define	UR2_EVEN_PARITY		0x10
#define	UR2_STICK_PARITY	0x20
#define	UR2_BREAK_ENB		0x40
#define	UR2_DLAB_ENB		0x80

/*------------------------------------------------
UR2_MCR (0xE5) Bit Values
------------------------------------------------*/
#define	UR2_DTR				0x01
#define	UR2_RTS				0x02
#define	UR2_OUT1			0x04
#define	UR2_OUT2			0x08
#define	UR2_LOOPBACK		0x10
#define	UR2_RS485_RECEIVE	0x40
#define	UR2_RS485_DRIVE		0x80

/*------------------------------------------------
UR2_LSR (0xE6) Bit Values
------------------------------------------------*/
#define	UR2_DR				0x01
#define	UR2_OE				0x02
#define	UR2_PE				0x04
#define	UR2_FE				0x08
#define	UR2_BI				0x10
#define	UR2_THRE			0x20
#define	UR2_TEMT			0x40
#define	UR2_FRAME_ERR		0x80

/*------------------------------------------------
UR2_MSR (0xE7) Bit Values
------------------------------------------------*/
#define	UR2_DCTS			0x01
#define	UR2_DDSR			0x02
#define	UR2_TERI			0x04
#define	UR2_DDCD			0x08
#define	UR2_CTS				0x10
#define	UR2_DSR				0x20
#define	UR2_RI				0x40
#define	UR2_DCD				0x80

/*------------------------------------------------
EIE (0xE8) Bit Registers
------------------------------------------------*/
sbit EINT2		= 0xE8;
sbit EINT3		= 0xE9;
sbit EINT4		= 0xEA;
sbit EINT5		= 0xEB;
sbit EINT6		= 0xEC;
sbit EWDI		= 0xED;

/*------------------------------------------------
EIP (0xF8) Bit Registers
------------------------------------------------*/
sbit PINT2		= 0xF8;
sbit PINT3		= 0xF9;
sbit PINT4		= 0xFA;
sbit PINT5		= 0xFB;
sbit PINT6		= 0xFC;
sbit PWDI		= 0xFD;

/*------------------------------------------------
------------------------------------------------*/
#endif