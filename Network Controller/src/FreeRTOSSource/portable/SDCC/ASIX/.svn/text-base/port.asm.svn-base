;--------------------------------------------------------
; File Created by SDCC : FreeWare ANSI-C Compiler
; Version 2.4.8 #964 (Feb 23 2005)
; This file generated Fri May 20 14:05:28 2005
;--------------------------------------------------------
	.module ______Source_portable_SDCC_ASIX_port
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
_P0	=	0x0080
_SP	=	0x0081
_DPL	=	0x0082
_DPH	=	0x0083
_PCON	=	0x0087
_TCON	=	0x0088
_TMOD	=	0x0089
_TL0	=	0x008a
_TL1	=	0x008b
_TH0	=	0x008c
_TH1	=	0x008d
_P1	=	0x0090
_SCON	=	0x0098
_SBUF	=	0x0099
_P2	=	0x00a0
_IE	=	0x00a8
_P3	=	0x00b0
_IP	=	0x00b8
_PSW	=	0x00d0
_ACC	=	0x00e0
_B	=	0x00f0
_T2CON	=	0x00c8
_RCAP2L	=	0x00ca
_RCAP2H	=	0x00cb
_TL2	=	0x00cc
_TH2	=	0x00cd
;--------------------------------------------------------
; special function bits 
;--------------------------------------------------------
	.area RSEG    (DATA)
_P0_0	=	0x0080
_P0_1	=	0x0081
_P0_2	=	0x0082
_P0_3	=	0x0083
_P0_4	=	0x0084
_P0_5	=	0x0085
_P0_6	=	0x0086
_P0_7	=	0x0087
_IT0	=	0x0088
_IE0	=	0x0089
_IT1	=	0x008a
_IE1	=	0x008b
_TR0	=	0x008c
_TF0	=	0x008d
_TR1	=	0x008e
_TF1	=	0x008f
_P1_0	=	0x0090
_P1_1	=	0x0091
_P1_2	=	0x0092
_P1_3	=	0x0093
_P1_4	=	0x0094
_P1_5	=	0x0095
_P1_6	=	0x0096
_P1_7	=	0x0097
_RI	=	0x0098
_TI	=	0x0099
_RB8	=	0x009a
_TB8	=	0x009b
_REN	=	0x009c
_SM2	=	0x009d
_SM1	=	0x009e
_SM0	=	0x009f
_P2_0	=	0x00a0
_P2_1	=	0x00a1
_P2_2	=	0x00a2
_P2_3	=	0x00a3
_P2_4	=	0x00a4
_P2_5	=	0x00a5
_P2_6	=	0x00a6
_P2_7	=	0x00a7
_EX0	=	0x00a8
_ET0	=	0x00a9
_EX1	=	0x00aa
_ET1	=	0x00ab
_ES	=	0x00ac
_EA	=	0x00af
_P3_0	=	0x00b0
_P3_1	=	0x00b1
_P3_2	=	0x00b2
_P3_3	=	0x00b3
_P3_4	=	0x00b4
_P3_5	=	0x00b5
_P3_6	=	0x00b6
_P3_7	=	0x00b7
_RXD	=	0x00b0
_TXD	=	0x00b1
_INT0	=	0x00b2
_INT1	=	0x00b3
_T0	=	0x00b4
_T1	=	0x00b5
_WR	=	0x00b6
_RD	=	0x00b7
_PX0	=	0x00b8
_PT0	=	0x00b9
_PX1	=	0x00ba
_PT1	=	0x00bb
_PS	=	0x00bc
_P	=	0x00d0
_F1	=	0x00d1
_OV	=	0x00d2
_RS0	=	0x00d3
_RS1	=	0x00d4
_F0	=	0x00d5
_AC	=	0x00d6
_CY	=	0x00d7
_ET2	=	0x00ad
_T2CON_0	=	0x00c8
_T2CON_1	=	0x00c9
_T2CON_2	=	0x00ca
_T2CON_3	=	0x00cb
_T2CON_4	=	0x00cc
_T2CON_5	=	0x00cd
_T2CON_6	=	0x00ce
_T2CON_7	=	0x00cf
_CP_RL2	=	0x00c8
_C_T2	=	0x00c9
_TR2	=	0x00ca
_EXEN2	=	0x00cb
_TCLK	=	0x00cc
_RCLK	=	0x00cd
_EXF2	=	0x00ce
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
_ucStackBytes:
	.ds 1
_pxXRAMStack:
	.ds 2
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
;../../Source/portable/SDCC/ASIX/port.c:221: portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters )
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
;../../Source/portable/SDCC/ASIX/port.c:227: pxStartOfStack = pxTopOfStack;
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
;../../Source/portable/SDCC/ASIX/port.c:228: pxTopOfStack++;
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
;../../Source/portable/SDCC/ASIX/port.c:244: ulAddress = ( unsigned portLONG ) pxCode;
;     genCast
	mov	a,_bp
	add	a,#0xfc
	mov	r0,a
	mov	ar5,@r0
	inc	r0
	mov	ar6,@r0
	mov	r7,#0x00
	mov	r2,#0x00
;../../Source/portable/SDCC/ASIX/port.c:245: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;
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
;../../Source/portable/SDCC/ASIX/port.c:246: ulAddress >>= 8;
;     genRightShift
;     genRightShiftLiteral
;     genrshFour
	mov	ar5,r6
	mov	ar6,r7
	mov	ar7,r2
	mov	r2,#0x00
;../../Source/portable/SDCC/ASIX/port.c:247: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:248: *pxTopOfStack = ( portSTACK_TYPE ) ( ulAddress );
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
;../../Source/portable/SDCC/ASIX/port.c:249: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:252: *pxTopOfStack = 0xaa;	/* acc */
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
;../../Source/portable/SDCC/ASIX/port.c:253: pxTopOfStack++;	
;../../Source/portable/SDCC/ASIX/port.c:256: *pxTopOfStack = portGLOBAL_INTERRUPT_BIT;
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
;../../Source/portable/SDCC/ASIX/port.c:257: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:261: ulAddress = ( unsigned portLONG ) pvParameters;
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
;../../Source/portable/SDCC/ASIX/port.c:262: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;	/* DPL */
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
;../../Source/portable/SDCC/ASIX/port.c:263: ulAddress >>= 8;
;     genRightShift
;     genRightShiftLiteral
;     genrshFour
	mov	ar5,r6
	mov	ar6,r7
	mov	ar7,r2
	mov	r2,#0x00
;../../Source/portable/SDCC/ASIX/port.c:264: *pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:265: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;	/* DPH */
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
;../../Source/portable/SDCC/ASIX/port.c:266: ulAddress >>= 8;
;     genRightShift
;     genRightShiftLiteral
;     genrshFour
	mov	ar5,r6
	mov	ar6,r7
	mov	ar7,r2
	mov	r2,#0x00
;../../Source/portable/SDCC/ASIX/port.c:267: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:268: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;	/* b */
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
;../../Source/portable/SDCC/ASIX/port.c:269: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:272: *pxTopOfStack = 0x02;	/* R2 */
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
;../../Source/portable/SDCC/ASIX/port.c:273: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:274: *pxTopOfStack = 0x03;	/* R3 */
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
;../../Source/portable/SDCC/ASIX/port.c:275: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:276: *pxTopOfStack = 0x04;	/* R4 */
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
;../../Source/portable/SDCC/ASIX/port.c:277: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:278: *pxTopOfStack = 0x05;	/* R5 */
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
;../../Source/portable/SDCC/ASIX/port.c:279: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:280: *pxTopOfStack = 0x06;	/* R6 */
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
;../../Source/portable/SDCC/ASIX/port.c:281: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:282: *pxTopOfStack = 0x07;	/* R7 */
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
;../../Source/portable/SDCC/ASIX/port.c:283: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:284: *pxTopOfStack = 0x00;	/* R0 */
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
;../../Source/portable/SDCC/ASIX/port.c:285: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:286: *pxTopOfStack = 0x01;	/* R1 */
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
;../../Source/portable/SDCC/ASIX/port.c:287: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:288: *pxTopOfStack = 0x00;	/* PSW */
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
;../../Source/portable/SDCC/ASIX/port.c:289: pxTopOfStack++;
;../../Source/portable/SDCC/ASIX/port.c:290: *pxTopOfStack = 0xbb;	/* BP */
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
;../../Source/portable/SDCC/ASIX/port.c:296: *pxStartOfStack = ( portSTACK_TYPE ) ( pxTopOfStack - pxStartOfStack );
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
;../../Source/portable/SDCC/ASIX/port.c:300: return pxStartOfStack;
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
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'sPortStartScheduler'
;------------------------------------------------------------
;sUsePreemption            Allocated to registers 
;------------------------------------------------------------
;../../Source/portable/SDCC/ASIX/port.c:307: portSHORT sPortStartScheduler( portSHORT sUsePreemption )
;	-----------------------------------------
;	 function sPortStartScheduler
;	-----------------------------------------
_sPortStartScheduler:
	push	_bp
	mov	_bp,sp
;../../Source/portable/SDCC/ASIX/port.c:314: prvSetupTimerInterrupt();	
;     genCall
	lcall	_prvSetupTimerInterrupt
;../../Source/portable/SDCC/ASIX/port.c:319: portCOPY_XRAM_TO_STACK();
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
	mov	_pxRAMStack,#0x21
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
;../../Source/portable/SDCC/ASIX/port.c:320: portRESTORE_CONTEXT();
;     genInline
 pop _bp pop PSW pop ar1 pop ar0 pop ar7 pop ar6 pop ar5 pop ar4 pop ar3 pop ar2 pop b pop DPH pop DPL pop ACC JB ACC.7,0098$ CLR IE.7 LJMP 0099$ 0098$:
SETB IE.7 0099$:
	pop ACC reti 
;../../Source/portable/SDCC/ASIX/port.c:323: return pdTRUE;
;     genRet
	mov	dpl,#0x01
	mov	dph,#0x00
00104$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vPortEndScheduler'
;------------------------------------------------------------
;------------------------------------------------------------
;../../Source/portable/SDCC/ASIX/port.c:327: void vPortEndScheduler( void )
;	-----------------------------------------
;	 function vPortEndScheduler
;	-----------------------------------------
_vPortEndScheduler:
	push	_bp
	mov	_bp,sp
;../../Source/portable/SDCC/ASIX/port.c:330: }
00101$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vPortYield'
;------------------------------------------------------------
;------------------------------------------------------------
;../../Source/portable/SDCC/ASIX/port.c:337: void vPortYield( void ) _naked
;	-----------------------------------------
;	 function vPortYield
;	-----------------------------------------
_vPortYield:
;	naked function: no prologue.
;../../Source/portable/SDCC/ASIX/port.c:345: portSAVE_CONTEXT();
;     genInline
	 push ACC push IE clr _EA push DPL push DPH push b push ar2 push ar3 push ar4 push ar5 push ar6 push ar7 push ar0 push ar1 push PSW 
;     genAssign
	mov	_PSW,#0x00
;     genInline
	 push _bp 
;../../Source/portable/SDCC/ASIX/port.c:346: portCOPY_STACK_TO_XRAM();
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
	mov	_pxRAMStack,#0x22
;     genMinus
	mov	a,_SP
	add	a,#0xdf
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
;../../Source/portable/SDCC/ASIX/port.c:349: vTaskSwitchContext();
;     genCall
	lcall	_vTaskSwitchContext
;../../Source/portable/SDCC/ASIX/port.c:353: portCOPY_XRAM_TO_STACK();
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
	mov	_pxRAMStack,#0x21
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
;../../Source/portable/SDCC/ASIX/port.c:354: portRESTORE_CONTEXT();
;     genInline
 pop _bp pop PSW pop ar1 pop ar0 pop ar7 pop ar6 pop ar5 pop ar4 pop ar3 pop ar2 pop b pop DPH pop DPL pop ACC JB ACC.7,0098$ CLR IE.7 LJMP 0099$ 0098$:
SETB IE.7 0099$:
	pop ACC reti 
00107$:
;	naked function: no epilogue.
;------------------------------------------------------------
;Allocation info for local variables in function 'vTimer2ISR'
;------------------------------------------------------------
;------------------------------------------------------------
;../../Source/portable/SDCC/ASIX/port.c:359: void vTimer2ISR( void ) interrupt 5 _naked
;	-----------------------------------------
;	 function vTimer2ISR
;	-----------------------------------------
_vTimer2ISR:
;	naked function: no prologue.
;../../Source/portable/SDCC/ASIX/port.c:365: portSAVE_CONTEXT();
;     genInline
	 push ACC push IE clr _EA push DPL push DPH push b push ar2 push ar3 push ar4 push ar5 push ar6 push ar7 push ar0 push ar1 push PSW 
;     genAssign
	mov	_PSW,#0x00
;     genInline
	 push _bp 
;../../Source/portable/SDCC/ASIX/port.c:366: portCOPY_STACK_TO_XRAM();
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
	mov	_pxRAMStack,#0x22
;     genMinus
	mov	a,_SP
	add	a,#0xdf
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
;../../Source/portable/SDCC/ASIX/port.c:368: vTaskIncrementTick();
;     genCall
	lcall	_vTaskIncrementTick
;../../Source/portable/SDCC/ASIX/port.c:369: vTaskSwitchContext();
;     genCall
	lcall	_vTaskSwitchContext
;../../Source/portable/SDCC/ASIX/port.c:371: portCLEAR_INTERRUPT_FLAG();
;     genAnd
	anl	_T2CON,#0x7F
;../../Source/portable/SDCC/ASIX/port.c:372: portCOPY_XRAM_TO_STACK();
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
	mov	_pxRAMStack,#0x21
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
;../../Source/portable/SDCC/ASIX/port.c:373: portRESTORE_CONTEXT();
;     genInline
 pop _bp pop PSW pop ar1 pop ar0 pop ar7 pop ar6 pop ar5 pop ar4 pop ar3 pop ar2 pop b pop DPH pop DPL pop ACC JB ACC.7,0098$ CLR IE.7 LJMP 0099$ 0098$:
SETB IE.7 0099$:
	pop ACC reti 
00107$:
;	naked function: no epilogue.
;------------------------------------------------------------
;Allocation info for local variables in function 'prvSetupTimerInterrupt'
;------------------------------------------------------------
;ulTicksPerSecond          Allocated to registers 
;ulCaptureTime             Allocated to registers 
;ulCaptureValue            Allocated to registers 
;ucLowCaptureByte          Allocated to registers 
;ucHighCaptureByte         Allocated to registers 
;------------------------------------------------------------
;../../Source/portable/SDCC/ASIX/port.c:387: static void prvSetupTimerInterrupt( void )
;	-----------------------------------------
;	 function prvSetupTimerInterrupt
;	-----------------------------------------
_prvSetupTimerInterrupt:
	push	_bp
	mov	_bp,sp
;../../Source/portable/SDCC/ASIX/port.c:401: RCAP2L = ucLowCaptureByte;
;     genAssign
	mov	_RCAP2L,#0x3D
;../../Source/portable/SDCC/ASIX/port.c:402: RCAP2H = ucHighCaptureByte;
;     genAssign
	mov	_RCAP2H,#0x5D
;../../Source/portable/SDCC/ASIX/port.c:405: TL2 = ucLowCaptureByte;
;     genAssign
	mov	_TL2,#0x3D
;../../Source/portable/SDCC/ASIX/port.c:406: TH2 = ucHighCaptureByte;
;     genAssign
	mov	_TH2,#0x5D
;../../Source/portable/SDCC/ASIX/port.c:409: IE |= portTIMER_2_INTERRUPT_ENABLE;
;     genOr
	orl	_IE,#0x20
;../../Source/portable/SDCC/ASIX/port.c:413: T2CON = portENABLE_TIMER;
;     genAssign
	mov	_T2CON,#0x04
00101$:
	mov	sp,_bp
	pop	_bp
	ret
	.area CSEG    (CODE)
	.area XINIT   (CODE)
