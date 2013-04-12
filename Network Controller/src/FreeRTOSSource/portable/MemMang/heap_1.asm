;--------------------------------------------------------
; File Created by SDCC : FreeWare ANSI-C Compiler
; Version 2.4.8 #964 (Feb 23 2005)
; This file generated Fri May 20 14:05:29 2005
;--------------------------------------------------------
	.module ______Source_portable_MemMang_heap_1
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
	.globl _pvPortMalloc
	.globl _vPortFree
	.globl _vPortInitialiseBlocks
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
_xHeap:
	.ds 6148
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
_usNextFreeByte:
	.ds 2
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
;Allocation info for local variables in function 'pvPortMalloc'
;------------------------------------------------------------
;usWantedSize              Allocated to stack - offset 1
;pvReturn                  Allocated to registers r4 r5 r6 
;sloc0                     Allocated to stack - offset 3
;------------------------------------------------------------
;../../Source/portable/MemMang/heap_1.c:82: void *pvPortMalloc( unsigned portSHORT usWantedSize )
;	-----------------------------------------
;	 function pvPortMalloc
;	-----------------------------------------
_pvPortMalloc:
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
	inc	sp
	inc	sp
;../../Source/portable/MemMang/heap_1.c:84: void *pvReturn = NULL;
;     genAssign
	mov	r4,#0x00
	mov	r5,#0x00
	mov	r6,#0x00
;../../Source/portable/MemMang/heap_1.c:93: vTaskSuspendAll();
;     genIpush
	push	ar4
	push	ar5
	push	ar6
;     genCall
	push	ar4
	push	ar5
	push	ar6
	lcall	_vTaskSuspendAll
	pop	ar6
	pop	ar5
	pop	ar4
;../../Source/portable/MemMang/heap_1.c:96: if( ( usNextFreeByte + usWantedSize ) < portTOTAL_HEAP_SIZE )
;     genAssign
	mov	dptr,#_usNextFreeByte
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	movx	a,@dptr
	mov	@r0,a
	inc	dptr
	movx	a,@dptr
	inc	r0
	mov	@r0,a
;     genPlus
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	a,_bp
	add	a,#0x01
	mov	r1,a
	mov	a,@r1
	add	a,@r0
	mov	r7,a
	inc	r1
	mov	a,@r1
	inc	r0
	addc	a,@r0
	mov	r4,a
;     genCmpLt
;     genCmp
	clr	c
	mov	a,r7
	subb	a,#0x00
	mov	a,r4
	subb	a,#0x18
	clr	a
	rlc	a
;     genIpop
	pop	ar6
	pop	ar5
	pop	ar4
;     genIfx
;     genIfxJump
	jnz	00109$
	ljmp	00104$
00109$:
;../../Source/portable/MemMang/heap_1.c:100: pvReturn = &( xHeap.ucHeap[ usNextFreeByte ] );
;     genPlus
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	a,@r0
	add	a,#(_xHeap + 0x0004)
	mov	r7,a
	inc	r0
	mov	a,@r0
	addc	a,#((_xHeap + 0x0004) >> 8)
	mov	r2,a
;     genCast
	mov	ar4,r7
	mov	ar5,r2
	mov	r6,#0x1
;../../Source/portable/MemMang/heap_1.c:101: usNextFreeByte += usWantedSize;			
;     genPlus
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	a,_bp
	add	a,#0x01
	mov	r1,a
	mov	dptr,#_usNextFreeByte
	mov	a,@r1
	add	a,@r0
	movx	@dptr,a
	inc	r1
	mov	a,@r1
	inc	r0
	addc	a,@r0
	inc	dptr
	movx	@dptr,a
00104$:
;../../Source/portable/MemMang/heap_1.c:104: cTaskResumeAll();
;     genCall
	push	ar4
	push	ar5
	push	ar6
	lcall	_cTaskResumeAll
	pop	ar6
	pop	ar5
	pop	ar4
;../../Source/portable/MemMang/heap_1.c:106: return pvReturn;
;     genRet
	mov	dpl,r4
	mov	dph,r5
	mov	b,r6
00105$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vPortFree'
;------------------------------------------------------------
;pv                        Allocated to registers 
;------------------------------------------------------------
;../../Source/portable/MemMang/heap_1.c:110: void vPortFree( void *pv )
;	-----------------------------------------
;	 function vPortFree
;	-----------------------------------------
_vPortFree:
	push	_bp
	mov	_bp,sp
;../../Source/portable/MemMang/heap_1.c:115: ( void ) pv;
00101$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vPortInitialiseBlocks'
;------------------------------------------------------------
;------------------------------------------------------------
;../../Source/portable/MemMang/heap_1.c:119: void vPortInitialiseBlocks( void )
;	-----------------------------------------
;	 function vPortInitialiseBlocks
;	-----------------------------------------
_vPortInitialiseBlocks:
	push	_bp
	mov	_bp,sp
;../../Source/portable/MemMang/heap_1.c:122: usNextFreeByte = ( unsigned portSHORT ) 0;
;     genAssign
	mov	dptr,#_usNextFreeByte
	clr	a
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
00101$:
	mov	sp,_bp
	pop	_bp
	ret
	.area CSEG    (CODE)
	.area XINIT   (CODE)
__xinit__usNextFreeByte:
	.byte #0x00,#0x00
