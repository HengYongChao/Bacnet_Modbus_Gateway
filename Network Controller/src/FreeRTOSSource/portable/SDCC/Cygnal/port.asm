;--------------------------------------------------------
; File Created by SDCC : FreeWare ANSI-C Compiler
; Version 2.4.8 #964 (Feb 23 2005)
; This file generated Wed Mar 02 13:24:16 2005
;--------------------------------------------------------
	.module ______Source_portable_SDCC_cygnal_port
	.optsdcc -mmcs51 --model-large
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _TF2
	.globl _EXF2
	.globl _RCLK
	.globl _TCLK
	.globl _EXEN2
	.globl _TR2
	.globl _C_T2
	.globl _CP_RL2
	.globl _T2CON_7
	.globl _T2CON_6
	.globl _T2CON_5
	.globl _T2CON_4
	.globl _T2CON_3
	.globl _T2CON_2
	.globl _T2CON_1
	.globl _T2CON_0
	.globl _ET2
	.globl _CY
	.globl _AC
	.globl _F0
	.globl _RS1
	.globl _RS0
	.globl _OV
	.globl _F1
	.globl _P
	.globl _PS
	.globl _PT1
	.globl _PX1
	.globl _PT0
	.globl _PX0
	.globl _RD
	.globl _WR
	.globl _T1
	.globl _T0
	.globl _INT1
	.globl _INT0
	.globl _TXD
	.globl _RXD
	.globl _P3_7
	.globl _P3_6
	.globl _P3_5
	.globl _P3_4
	.globl _P3_3
	.globl _P3_2
	.globl _P3_1
	.globl _P3_0
	.globl _EA
	.globl _ES
	.globl _ET1
	.globl _EX1
	.globl _ET0
	.globl _EX0
	.globl _P2_7
	.globl _P2_6
	.globl _P2_5
	.globl _P2_4
	.globl _P2_3
	.globl _P2_2
	.globl _P2_1
	.globl _P2_0
	.globl _SM0
	.globl _SM1
	.globl _SM2
	.globl _REN
	.globl _TB8
	.globl _RB8
	.globl _TI
	.globl _RI
	.globl _P1_7
	.globl _P1_6
	.globl _P1_5
	.globl _P1_4
	.globl _P1_3
	.globl _P1_2
	.globl _P1_1
	.globl _P1_0
	.globl _TF1
	.globl _TR1
	.globl _TF0
	.globl _TR0
	.globl _IE1
	.globl _IT1
	.globl _IE0
	.globl _IT0
	.globl _P0_7
	.globl _P0_6
	.globl _P0_5
	.globl _P0_4
	.globl _P0_3
	.globl _P0_2
	.globl _P0_1
	.globl _P0_0
	.globl _TH2
	.globl _TL2
	.globl _RCAP2H
	.globl _RCAP2L
	.globl _T2CON
	.globl _B
	.globl _ACC
	.globl _PSW
	.globl _IP
	.globl _P3
	.globl _IE
	.globl _P2
	.globl _SBUF
	.globl _SCON
	.globl _P1
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _P0
	.globl _pxPortInitialiseStack
	.globl _sPortStartScheduler
	.globl _vPortEndScheduler
	.globl _vPortYield
	.globl _vTimer2ISR
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (DATA)
G$P0$0$0 == 0x0080
_P0	=	0x0080
G$SP$0$0 == 0x0081
_SP	=	0x0081
G$DPL$0$0 == 0x0082
_DPL	=	0x0082
G$DPH$0$0 == 0x0083
_DPH	=	0x0083
G$PCON$0$0 == 0x0087
_PCON	=	0x0087
G$TCON$0$0 == 0x0088
_TCON	=	0x0088
G$TMOD$0$0 == 0x0089
_TMOD	=	0x0089
G$TL0$0$0 == 0x008a
_TL0	=	0x008a
G$TL1$0$0 == 0x008b
_TL1	=	0x008b
G$TH0$0$0 == 0x008c
_TH0	=	0x008c
G$TH1$0$0 == 0x008d
_TH1	=	0x008d
G$P1$0$0 == 0x0090
_P1	=	0x0090
G$SCON$0$0 == 0x0098
_SCON	=	0x0098
G$SBUF$0$0 == 0x0099
_SBUF	=	0x0099
G$P2$0$0 == 0x00a0
_P2	=	0x00a0
G$IE$0$0 == 0x00a8
_IE	=	0x00a8
G$P3$0$0 == 0x00b0
_P3	=	0x00b0
G$IP$0$0 == 0x00b8
_IP	=	0x00b8
G$PSW$0$0 == 0x00d0
_PSW	=	0x00d0
G$ACC$0$0 == 0x00e0
_ACC	=	0x00e0
G$B$0$0 == 0x00f0
_B	=	0x00f0
G$T2CON$0$0 == 0x00c8
_T2CON	=	0x00c8
G$RCAP2L$0$0 == 0x00ca
_RCAP2L	=	0x00ca
G$RCAP2H$0$0 == 0x00cb
_RCAP2H	=	0x00cb
G$TL2$0$0 == 0x00cc
_TL2	=	0x00cc
G$TH2$0$0 == 0x00cd
_TH2	=	0x00cd
;--------------------------------------------------------
; special function bits 
;--------------------------------------------------------
	.area RSEG    (DATA)
G$P0_0$0$0 == 0x0080
_P0_0	=	0x0080
G$P0_1$0$0 == 0x0081
_P0_1	=	0x0081
G$P0_2$0$0 == 0x0082
_P0_2	=	0x0082
G$P0_3$0$0 == 0x0083
_P0_3	=	0x0083
G$P0_4$0$0 == 0x0084
_P0_4	=	0x0084
G$P0_5$0$0 == 0x0085
_P0_5	=	0x0085
G$P0_6$0$0 == 0x0086
_P0_6	=	0x0086
G$P0_7$0$0 == 0x0087
_P0_7	=	0x0087
G$IT0$0$0 == 0x0088
_IT0	=	0x0088
G$IE0$0$0 == 0x0089
_IE0	=	0x0089
G$IT1$0$0 == 0x008a
_IT1	=	0x008a
G$IE1$0$0 == 0x008b
_IE1	=	0x008b
G$TR0$0$0 == 0x008c
_TR0	=	0x008c
G$TF0$0$0 == 0x008d
_TF0	=	0x008d
G$TR1$0$0 == 0x008e
_TR1	=	0x008e
G$TF1$0$0 == 0x008f
_TF1	=	0x008f
G$P1_0$0$0 == 0x0090
_P1_0	=	0x0090
G$P1_1$0$0 == 0x0091
_P1_1	=	0x0091
G$P1_2$0$0 == 0x0092
_P1_2	=	0x0092
G$P1_3$0$0 == 0x0093
_P1_3	=	0x0093
G$P1_4$0$0 == 0x0094
_P1_4	=	0x0094
G$P1_5$0$0 == 0x0095
_P1_5	=	0x0095
G$P1_6$0$0 == 0x0096
_P1_6	=	0x0096
G$P1_7$0$0 == 0x0097
_P1_7	=	0x0097
G$RI$0$0 == 0x0098
_RI	=	0x0098
G$TI$0$0 == 0x0099
_TI	=	0x0099
G$RB8$0$0 == 0x009a
_RB8	=	0x009a
G$TB8$0$0 == 0x009b
_TB8	=	0x009b
G$REN$0$0 == 0x009c
_REN	=	0x009c
G$SM2$0$0 == 0x009d
_SM2	=	0x009d
G$SM1$0$0 == 0x009e
_SM1	=	0x009e
G$SM0$0$0 == 0x009f
_SM0	=	0x009f
G$P2_0$0$0 == 0x00a0
_P2_0	=	0x00a0
G$P2_1$0$0 == 0x00a1
_P2_1	=	0x00a1
G$P2_2$0$0 == 0x00a2
_P2_2	=	0x00a2
G$P2_3$0$0 == 0x00a3
_P2_3	=	0x00a3
G$P2_4$0$0 == 0x00a4
_P2_4	=	0x00a4
G$P2_5$0$0 == 0x00a5
_P2_5	=	0x00a5
G$P2_6$0$0 == 0x00a6
_P2_6	=	0x00a6
G$P2_7$0$0 == 0x00a7
_P2_7	=	0x00a7
G$EX0$0$0 == 0x00a8
_EX0	=	0x00a8
G$ET0$0$0 == 0x00a9
_ET0	=	0x00a9
G$EX1$0$0 == 0x00aa
_EX1	=	0x00aa
G$ET1$0$0 == 0x00ab
_ET1	=	0x00ab
G$ES$0$0 == 0x00ac
_ES	=	0x00ac
G$EA$0$0 == 0x00af
_EA	=	0x00af
G$P3_0$0$0 == 0x00b0
_P3_0	=	0x00b0
G$P3_1$0$0 == 0x00b1
_P3_1	=	0x00b1
G$P3_2$0$0 == 0x00b2
_P3_2	=	0x00b2
G$P3_3$0$0 == 0x00b3
_P3_3	=	0x00b3
G$P3_4$0$0 == 0x00b4
_P3_4	=	0x00b4
G$P3_5$0$0 == 0x00b5
_P3_5	=	0x00b5
G$P3_6$0$0 == 0x00b6
_P3_6	=	0x00b6
G$P3_7$0$0 == 0x00b7
_P3_7	=	0x00b7
G$RXD$0$0 == 0x00b0
_RXD	=	0x00b0
G$TXD$0$0 == 0x00b1
_TXD	=	0x00b1
G$INT0$0$0 == 0x00b2
_INT0	=	0x00b2
G$INT1$0$0 == 0x00b3
_INT1	=	0x00b3
G$T0$0$0 == 0x00b4
_T0	=	0x00b4
G$T1$0$0 == 0x00b5
_T1	=	0x00b5
G$WR$0$0 == 0x00b6
_WR	=	0x00b6
G$RD$0$0 == 0x00b7
_RD	=	0x00b7
G$PX0$0$0 == 0x00b8
_PX0	=	0x00b8
G$PT0$0$0 == 0x00b9
_PT0	=	0x00b9
G$PX1$0$0 == 0x00ba
_PX1	=	0x00ba
G$PT1$0$0 == 0x00bb
_PT1	=	0x00bb
G$PS$0$0 == 0x00bc
_PS	=	0x00bc
G$P$0$0 == 0x00d0
_P	=	0x00d0
G$F1$0$0 == 0x00d1
_F1	=	0x00d1
G$OV$0$0 == 0x00d2
_OV	=	0x00d2
G$RS0$0$0 == 0x00d3
_RS0	=	0x00d3
G$RS1$0$0 == 0x00d4
_RS1	=	0x00d4
G$F0$0$0 == 0x00d5
_F0	=	0x00d5
G$AC$0$0 == 0x00d6
_AC	=	0x00d6
G$CY$0$0 == 0x00d7
_CY	=	0x00d7
G$ET2$0$0 == 0x00ad
_ET2	=	0x00ad
G$T2CON_0$0$0 == 0x00c8
_T2CON_0	=	0x00c8
G$T2CON_1$0$0 == 0x00c9
_T2CON_1	=	0x00c9
G$T2CON_2$0$0 == 0x00ca
_T2CON_2	=	0x00ca
G$T2CON_3$0$0 == 0x00cb
_T2CON_3	=	0x00cb
G$T2CON_4$0$0 == 0x00cc
_T2CON_4	=	0x00cc
G$T2CON_5$0$0 == 0x00cd
_T2CON_5	=	0x00cd
G$T2CON_6$0$0 == 0x00ce
_T2CON_6	=	0x00ce
G$T2CON_7$0$0 == 0x00cf
_T2CON_7	=	0x00cf
G$CP_RL2$0$0 == 0x00c8
_CP_RL2	=	0x00c8
G$C_T2$0$0 == 0x00c9
_C_T2	=	0x00c9
G$TR2$0$0 == 0x00ca
_TR2	=	0x00ca
G$EXEN2$0$0 == 0x00cb
_EXEN2	=	0x00cb
G$TCLK$0$0 == 0x00cc
_TCLK	=	0x00cc
G$RCLK$0$0 == 0x00cd
_RCLK	=	0x00cd
G$EXF2$0$0 == 0x00ce
_EXF2	=	0x00ce
G$TF2$0$0 == 0x00cf
_TF2	=	0x00cf
;--------------------------------------------------------
; overlayable register banks 
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
F______Source_portable_SDCC_cygnal_port$ucStackBytes$0$0==.
_ucStackBytes:
	.ds 1
F______Source_portable_SDCC_cygnal_port$pxXRAMStack$0$0==.
_pxXRAMStack:
	.ds 2
F______Source_portable_SDCC_cygnal_port$pxRAMStack$0$0==.
_pxRAMStack:
	.ds 1
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area OSEG    (OVR,DATA)
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
	.area CSEG    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area CSEG    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'pxPortInitialiseStack'
;------------------------------------------------------------
;pxCode                    Allocated to stack - offset -4
;pvParameters              Allocated to stack - offset -7
;pxTopOfStack              Allocated to stack - offset 1
;ulAddress                 Allocated to registers r5 r6 r7 r2 
;pxStartOfStack            Allocated to stack - offset 4
;------------------------------------------------------------
	G$pxPortInitialiseStack$0$0 ==.
	C$port.c$222$0$0 ==.
;../../Source/portable/SDCC/cygnal/port.c:222: portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters )
;	-----------------------------------------
;	 function pxPortInitialiseStack
;	-----------------------------------------
_pxPortInitialiseStack:
	ar2 = 0x02
	ar3 = 0x03
	ar4 = 0x04
	ar5 = 0x05
	ar6 = 0x06
	ar7 = 0x07
	ar0 = 0x00
	ar1 = 0x01
	push	_bp
	mov	_bp,sp
;     genReceive
	push	dpl
	push	dph
	push	b
	inc	sp
	inc	sp
	inc	sp
	C$port.c$228$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:228: pxStartOfStack = pxTopOfStack;
;     genAssign
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,_bp
	add	a,#0x04
	mov	r1,a
	mov	a,@r0
	mov	@r1,a
	inc	r0
	inc	r1
	mov	a,@r0
	mov	@r1,a
	inc	r0
	inc	r1
	mov	a,@r0
	mov	@r1,a
	C$port.c$229$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:229: pxTopOfStack++;
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
;     genPlusIncr
	mov	a,#0x01
	add	a,@r0
	mov	@r0,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	@r0,a
	C$port.c$245$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:245: ulAddress = ( unsigned portLONG ) pxCode;
;     genCast
	mov	a,_bp
	add	a,#0xfc
	mov	r0,a
	mov	ar5,@r0
	inc	r0
	mov	ar6,@r0
	mov	r7,#0x00
	mov	r2,#0x00
	C$port.c$246$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:246: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;
;     genCast
	mov	ar3,r5
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r3
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$247$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:247: ulAddress >>= 8;
;     genRightShift
;     genRightShiftLiteral
;     genrshFour
	mov	ar5,r6
	mov	ar6,r7
	mov	ar7,r2
	mov	r2,#0x00
	C$port.c$248$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:248: pxTopOfStack++;
	C$port.c$249$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:249: *pxTopOfStack = ( portSTACK_TYPE ) ( ulAddress );
;     genCast
	mov	ar3,r5
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r3
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$250$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:250: pxTopOfStack++;
	C$port.c$253$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:253: *pxTopOfStack = 0xaa;	/* acc */
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0xAA
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$254$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:254: pxTopOfStack++;	
	C$port.c$257$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:257: *pxTopOfStack = portGLOBAL_INTERRUPT_BIT;
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0x80
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$258$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:258: pxTopOfStack++;
	C$port.c$262$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:262: ulAddress = ( unsigned portLONG ) pvParameters;
;     genCast
	mov	a,_bp
	add	a,#0xf9
	mov	r0,a
	mov	ar5,@r0
	inc	r0
	mov	ar6,@r0
	inc	r0
	mov	ar7,@r0
	mov	r2,#0x00
	C$port.c$263$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:263: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;	/* DPL */
;     genCast
	mov	ar3,r5
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r3
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$264$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:264: ulAddress >>= 8;
;     genRightShift
;     genRightShiftLiteral
;     genrshFour
	mov	ar5,r6
	mov	ar6,r7
	mov	ar7,r2
	mov	r2,#0x00
	C$port.c$265$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:265: *pxTopOfStack++;
	C$port.c$266$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:266: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;	/* DPH */
;     genCast
	mov	ar3,r5
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r3
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$267$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:267: ulAddress >>= 8;
;     genRightShift
;     genRightShiftLiteral
;     genrshFour
	mov	ar5,r6
	mov	ar6,r7
	mov	ar7,r2
	mov	r2,#0x00
	C$port.c$268$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:268: pxTopOfStack++;
	C$port.c$269$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:269: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;	/* b */
;     genCast
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r5
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$270$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:270: pxTopOfStack++;
	C$port.c$273$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:273: *pxTopOfStack = 0x02;	/* R2 */
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0x02
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$274$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:274: pxTopOfStack++;
	C$port.c$275$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:275: *pxTopOfStack = 0x03;	/* R3 */
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0x03
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$276$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:276: pxTopOfStack++;
	C$port.c$277$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:277: *pxTopOfStack = 0x04;	/* R4 */
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0x04
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$278$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:278: pxTopOfStack++;
	C$port.c$279$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:279: *pxTopOfStack = 0x05;	/* R5 */
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0x05
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$280$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:280: pxTopOfStack++;
	C$port.c$281$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:281: *pxTopOfStack = 0x06;	/* R6 */
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0x06
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$282$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:282: pxTopOfStack++;
	C$port.c$283$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:283: *pxTopOfStack = 0x07;	/* R7 */
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0x07
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$284$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:284: pxTopOfStack++;
	C$port.c$285$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:285: *pxTopOfStack = 0x00;	/* R0 */
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0x00
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$286$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:286: pxTopOfStack++;
	C$port.c$287$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:287: *pxTopOfStack = 0x01;	/* R1 */
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0x01
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$288$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:288: pxTopOfStack++;
	C$port.c$289$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:289: *pxTopOfStack = 0x00;	/* PSW */
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0x00
	lcall	__gptrput
	inc	dptr
	dec	r0
	dec	r0
	mov	@r0,dpl
	inc	r0
	mov	@r0,dph
	C$port.c$290$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:290: pxTopOfStack++;
	C$port.c$291$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:291: *pxTopOfStack = 0xbb;	/* BP */
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0xBB
	lcall	__gptrput
	C$port.c$297$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:297: *pxStartOfStack = ( portSTACK_TYPE ) ( pxTopOfStack - pxStartOfStack );
;     genMinus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,_bp
	add	a,#0x04
	mov	r1,a
	mov	a,@r0
	clr	c
	subb	a,@r1
	mov	r2,a
	inc	r0
	mov	a,@r0
	inc	r1
	subb	a,@r1
	mov	r3,a
;     genCast
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r2
	lcall	__gptrput
	C$port.c$301$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:301: return pxStartOfStack;
;     genRet
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
00101$:
	mov	sp,_bp
	pop	_bp
	C$port.c$302$1$1 ==.
	XG$pxPortInitialiseStack$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'sPortStartScheduler'
;------------------------------------------------------------
;sUsePreemption            Allocated to registers 
;------------------------------------------------------------
	G$sPortStartScheduler$0$0 ==.
	C$port.c$308$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:308: portSHORT sPortStartScheduler( portSHORT sUsePreemption )
;	-----------------------------------------
;	 function sPortStartScheduler
;	-----------------------------------------
_sPortStartScheduler:
	push	_bp
	mov	_bp,sp
	C$port.c$315$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:315: prvSetupTimerInterrupt();	
;     genCall
	lcall	_prvSetupTimerInterrupt
	C$port.c$323$2$2 ==.
;../../Source/portable/SDCC/cygnal/port.c:323: portCOPY_XRAM_TO_STACK();
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	_pxXRAMStack,a
	inc	dptr
	lcall	__gptrget
	mov	(_pxXRAMStack + 1),a
;     genAssign
	mov	_pxRAMStack,#0x0D
;     genAssign
	mov	dpl,_pxXRAMStack
	mov	dph,(_pxXRAMStack + 1)
;     genPointerGet
;     genFarPointerGet
	movx	a,@dptr
	mov	_ucStackBytes,a
00101$:
;     genPlus
;     genPlusIncr
	inc	_pxXRAMStack
	clr	a
	cjne	a,_pxXRAMStack,00108$
	inc	(_pxXRAMStack + 1)
00108$:
;     genPlus
;     genPlusIncr
	inc	_pxRAMStack
;     genAssign
	mov	r0,_pxRAMStack
;     genAssign
	mov	dpl,_pxXRAMStack
	mov	dph,(_pxXRAMStack + 1)
;     genPointerGet
;     genFarPointerGet
	movx	a,@dptr
	mov	r2,a
;     genPointerSet
;     genNearPointerSet
	mov	@r0,ar2
;     genMinus
;     genMinusDec
	dec	_ucStackBytes
;     genIfx
	mov	a,_ucStackBytes
;     genIfxJump
	jz	00109$
	ljmp	00101$
00109$:
;     genCast
	mov	_SP,_pxRAMStack
	C$port.c$324$2$4 ==.
;../../Source/portable/SDCC/cygnal/port.c:324: portRESTORE_CONTEXT();
;     genInline
 pop _bp pop PSW pop ar1 pop ar0 pop ar7 pop ar6 pop ar5 pop ar4 pop ar3 pop ar2 pop b pop DPH pop DPL pop ACC JB ACC.7,0098$ CLR IE.7 LJMP 0099$ 0098$:
SETB IE.7 0099$:
	pop ACC reti 
	C$port.c$327$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:327: return pdTRUE;
;     genRet
	mov	dpl,#0x01
	mov	dph,#0x00
00104$:
	mov	sp,_bp
	pop	_bp
	C$port.c$328$1$1 ==.
	XG$sPortStartScheduler$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vPortEndScheduler'
;------------------------------------------------------------
;------------------------------------------------------------
	G$vPortEndScheduler$0$0 ==.
	C$port.c$331$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:331: void vPortEndScheduler( void )
;	-----------------------------------------
;	 function vPortEndScheduler
;	-----------------------------------------
_vPortEndScheduler:
	push	_bp
	mov	_bp,sp
	C$port.c$334$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:334: }
00101$:
	mov	sp,_bp
	pop	_bp
	C$port.c$334$1$1 ==.
	XG$vPortEndScheduler$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vPortYield'
;------------------------------------------------------------
;------------------------------------------------------------
	G$vPortYield$0$0 ==.
	C$port.c$341$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:341: void vPortYield( void ) _naked
;	-----------------------------------------
;	 function vPortYield
;	-----------------------------------------
_vPortYield:
;	naked function: no prologue.
	C$port.c$349$2$2 ==.
;../../Source/portable/SDCC/cygnal/port.c:349: portSAVE_CONTEXT();
;     genInline
	 push ACC push IE clr _EA push DPL push DPH push b push ar2 push ar3 push ar4 push ar5 push ar6 push ar7 push ar0 push ar1 push PSW 
;     genAssign
	mov	_PSW,#0x00
;     genInline
	 push _bp 
	C$port.c$350$2$3 ==.
;../../Source/portable/SDCC/cygnal/port.c:350: portCOPY_STACK_TO_XRAM();
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	_pxXRAMStack,a
	inc	dptr
	lcall	__gptrget
	mov	(_pxXRAMStack + 1),a
;     genAssign
	mov	_pxRAMStack,#0x0E
;     genMinus
	mov	a,_SP
	add	a,#0xf3
	mov	_ucStackBytes,a
;     genAssign
	mov	dpl,_pxXRAMStack
	mov	dph,(_pxXRAMStack + 1)
;     genPointerSet
;     genFarPointerSet
	mov	a,_ucStackBytes
	movx	@dptr,a
00101$:
;     genIfx
	mov	a,_ucStackBytes
;     genIfxJump
	jnz	00113$
	ljmp	00103$
00113$:
;     genPlus
;     genPlusIncr
	inc	_pxXRAMStack
	clr	a
	cjne	a,_pxXRAMStack,00114$
	inc	(_pxXRAMStack + 1)
00114$:
;     genAssign
	mov	dpl,_pxXRAMStack
	mov	dph,(_pxXRAMStack + 1)
;     genAssign
	mov	r0,_pxRAMStack
;     genPointerGet
;     genNearPointerGet
	mov	ar2,@r0
;     genPointerSet
;     genFarPointerSet
	mov	a,r2
	movx	@dptr,a
;     genPlus
;     genPlusIncr
	inc	_pxRAMStack
;     genMinus
;     genMinusDec
	dec	_ucStackBytes
	ljmp	00101$
00103$:
	C$port.c$353$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:353: vTaskSwitchContext();
;     genCall
	lcall	_vTaskSwitchContext
	C$port.c$357$2$5 ==.
;../../Source/portable/SDCC/cygnal/port.c:357: portCOPY_XRAM_TO_STACK();
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	_pxXRAMStack,a
	inc	dptr
	lcall	__gptrget
	mov	(_pxXRAMStack + 1),a
;     genAssign
	mov	_pxRAMStack,#0x0D
;     genAssign
	mov	dpl,_pxXRAMStack
	mov	dph,(_pxXRAMStack + 1)
;     genPointerGet
;     genFarPointerGet
	movx	a,@dptr
	mov	_ucStackBytes,a
00104$:
;     genPlus
;     genPlusIncr
	inc	_pxXRAMStack
	clr	a
	cjne	a,_pxXRAMStack,00115$
	inc	(_pxXRAMStack + 1)
00115$:
;     genPlus
;     genPlusIncr
	inc	_pxRAMStack
;     genAssign
	mov	r0,_pxRAMStack
;     genAssign
	mov	dpl,_pxXRAMStack
	mov	dph,(_pxXRAMStack + 1)
;     genPointerGet
;     genFarPointerGet
	movx	a,@dptr
	mov	r2,a
;     genPointerSet
;     genNearPointerSet
	mov	@r0,ar2
;     genMinus
;     genMinusDec
	dec	_ucStackBytes
;     genIfx
	mov	a,_ucStackBytes
;     genIfxJump
	jz	00116$
	ljmp	00104$
00116$:
;     genCast
	mov	_SP,_pxRAMStack
	C$port.c$358$2$7 ==.
;../../Source/portable/SDCC/cygnal/port.c:358: portRESTORE_CONTEXT();
;     genInline
 pop _bp pop PSW pop ar1 pop ar0 pop ar7 pop ar6 pop ar5 pop ar4 pop ar3 pop ar2 pop b pop DPH pop DPL pop ACC JB ACC.7,0098$ CLR IE.7 LJMP 0099$ 0098$:
SETB IE.7 0099$:
	pop ACC reti 
00107$:
;	naked function: no epilogue.
	C$port.c$359$2$7 ==.
	XG$vPortYield$0$0 ==.
;------------------------------------------------------------
;Allocation info for local variables in function 'vTimer2ISR'
;------------------------------------------------------------
;------------------------------------------------------------
	G$vTimer2ISR$0$0 ==.
	C$port.c$363$2$7 ==.
;../../Source/portable/SDCC/cygnal/port.c:363: void vTimer2ISR( void ) interrupt 5 _naked
;	-----------------------------------------
;	 function vTimer2ISR
;	-----------------------------------------
_vTimer2ISR:
;	naked function: no prologue.
	C$port.c$369$2$2 ==.
;../../Source/portable/SDCC/cygnal/port.c:369: portSAVE_CONTEXT();
;     genInline
	 push ACC push IE clr _EA push DPL push DPH push b push ar2 push ar3 push ar4 push ar5 push ar6 push ar7 push ar0 push ar1 push PSW 
;     genAssign
	mov	_PSW,#0x00
;     genInline
	 push _bp 
	C$port.c$370$2$3 ==.
;../../Source/portable/SDCC/cygnal/port.c:370: portCOPY_STACK_TO_XRAM();
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	_pxXRAMStack,a
	inc	dptr
	lcall	__gptrget
	mov	(_pxXRAMStack + 1),a
;     genAssign
	mov	_pxRAMStack,#0x0E
;     genMinus
	mov	a,_SP
	add	a,#0xf3
	mov	_ucStackBytes,a
;     genAssign
	mov	dpl,_pxXRAMStack
	mov	dph,(_pxXRAMStack + 1)
;     genPointerSet
;     genFarPointerSet
	mov	a,_ucStackBytes
	movx	@dptr,a
00101$:
;     genIfx
	mov	a,_ucStackBytes
;     genIfxJump
	jnz	00113$
	ljmp	00103$
00113$:
;     genPlus
;     genPlusIncr
	inc	_pxXRAMStack
	clr	a
	cjne	a,_pxXRAMStack,00114$
	inc	(_pxXRAMStack + 1)
00114$:
;     genAssign
	mov	dpl,_pxXRAMStack
	mov	dph,(_pxXRAMStack + 1)
;     genAssign
	mov	r0,_pxRAMStack
;     genPointerGet
;     genNearPointerGet
	mov	ar2,@r0
;     genPointerSet
;     genFarPointerSet
	mov	a,r2
	movx	@dptr,a
;     genPlus
;     genPlusIncr
	inc	_pxRAMStack
;     genMinus
;     genMinusDec
	dec	_ucStackBytes
	ljmp	00101$
00103$:
	C$port.c$372$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:372: vTaskIncrementTick();
;     genCall
	lcall	_vTaskIncrementTick
	C$port.c$373$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:373: vTaskSwitchContext();
;     genCall
	lcall	_vTaskSwitchContext
	C$port.c$375$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:375: portCLEAR_INTERRUPT_FLAG();
;     genAnd
	anl	_T2CON,#0x7F
	C$port.c$376$2$5 ==.
;../../Source/portable/SDCC/cygnal/port.c:376: portCOPY_XRAM_TO_STACK();
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	_pxXRAMStack,a
	inc	dptr
	lcall	__gptrget
	mov	(_pxXRAMStack + 1),a
;     genAssign
	mov	_pxRAMStack,#0x0D
;     genAssign
	mov	dpl,_pxXRAMStack
	mov	dph,(_pxXRAMStack + 1)
;     genPointerGet
;     genFarPointerGet
	movx	a,@dptr
	mov	_ucStackBytes,a
00104$:
;     genPlus
;     genPlusIncr
	inc	_pxXRAMStack
	clr	a
	cjne	a,_pxXRAMStack,00115$
	inc	(_pxXRAMStack + 1)
00115$:
;     genPlus
;     genPlusIncr
	inc	_pxRAMStack
;     genAssign
	mov	r0,_pxRAMStack
;     genAssign
	mov	dpl,_pxXRAMStack
	mov	dph,(_pxXRAMStack + 1)
;     genPointerGet
;     genFarPointerGet
	movx	a,@dptr
	mov	r2,a
;     genPointerSet
;     genNearPointerSet
	mov	@r0,ar2
;     genMinus
;     genMinusDec
	dec	_ucStackBytes
;     genIfx
	mov	a,_ucStackBytes
;     genIfxJump
	jz	00116$
	ljmp	00104$
00116$:
;     genCast
	mov	_SP,_pxRAMStack
	C$port.c$377$2$7 ==.
;../../Source/portable/SDCC/cygnal/port.c:377: portRESTORE_CONTEXT();
;     genInline
 pop _bp pop PSW pop ar1 pop ar0 pop ar7 pop ar6 pop ar5 pop ar4 pop ar3 pop ar2 pop b pop DPH pop DPL pop ACC JB ACC.7,0098$ CLR IE.7 LJMP 0099$ 0098$:
SETB IE.7 0099$:
	pop ACC reti 
00107$:
;	naked function: no epilogue.
	C$port.c$378$2$7 ==.
	XG$vTimer2ISR$0$0 ==.
;------------------------------------------------------------
;Allocation info for local variables in function 'prvSetupTimerInterrupt'
;------------------------------------------------------------
;ulTicksPerSecond          Allocated to registers 
;ulCaptureTime             Allocated to registers 
;ulCaptureValue            Allocated to registers 
;ucLowCaptureByte          Allocated to registers 
;ucHighCaptureByte         Allocated to registers 
;------------------------------------------------------------
	F______Source_portable_SDCC_cygnal_port$prvSetupTimerInterrupt$0$0 ==.
	C$port.c$391$2$7 ==.
;../../Source/portable/SDCC/cygnal/port.c:391: static void prvSetupTimerInterrupt( void )
;	-----------------------------------------
;	 function prvSetupTimerInterrupt
;	-----------------------------------------
_prvSetupTimerInterrupt:
	push	_bp
	mov	_bp,sp
	C$port.c$413$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:413: RCAP2L = ucLowCaptureByte;
;     genAssign
	mov	_RCAP2L,#0x19
	C$port.c$414$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:414: RCAP2H = ucHighCaptureByte;
;     genAssign
	mov	_RCAP2H,#0xE0
	C$port.c$419$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:419: TL2 = ucLowCaptureByte;
;     genAssign
	mov	_TL2,#0x19
	C$port.c$420$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:420: TH2 = ucHighCaptureByte;
;     genAssign
	mov	_TH2,#0xE0
	C$port.c$423$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:423: IE |= portTIMER_2_INTERRUPT_ENABLE;
;     genOr
	orl	_IE,#0x20
	C$port.c$428$1$1 ==.
;../../Source/portable/SDCC/cygnal/port.c:428: T2CON = portENABLE_TIMER;
;     genAssign
	mov	_T2CON,#0x04
00101$:
	mov	sp,_bp
	pop	_bp
	C$port.c$432$1$1 ==.
	XF______Source_portable_SDCC_cygnal_port$prvSetupTimerInterrupt$0$0 ==.
	ret
	.area CSEG    (CODE)
	.area XINIT   (CODE)
