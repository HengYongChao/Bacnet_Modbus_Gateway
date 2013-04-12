;--------------------------------------------------------
; File Created by SDCC : FreeWare ANSI-C Compiler
; Version 2.4.8 #964 (Feb 23 2005)
; This file generated Fri May 20 14:05:28 2005
;--------------------------------------------------------
	.module ______Source_queue
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
	.globl _xQueueCreate
	.globl _cQueueSend
	.globl _cQueueSendFromISR
	.globl _cQueueReceive
	.globl _cQueueReceiveFromISR
	.globl _ucQueueMessagesWaiting
	.globl _vQueueDelete
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
;Allocation info for local variables in function 'xQueueCreate'
;------------------------------------------------------------
;ucItemSize                Allocated to stack - offset -3
;ucQueueLength             Allocated to stack - offset 1
;pxNewQueue                Allocated to stack - offset 2
;usQueueSizeInBytes        Allocated to registers r2 r3 
;sloc0                     Allocated to stack - offset 5
;sloc1                     Allocated to stack - offset 8
;------------------------------------------------------------
;../../Source/queue.c:168: xQueueHandle xQueueCreate( unsigned portCHAR ucQueueLength, unsigned portCHAR ucItemSize )
;	-----------------------------------------
;	 function xQueueCreate
;	-----------------------------------------
_xQueueCreate:
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
	mov	a,sp
	add	a,#0x09
	mov	sp,a
;../../Source/queue.c:174: if( ucQueueLength > ( unsigned portCHAR ) 0 )
;     genCmpGt
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
;     genCmp
	clr	c
	mov	a,#0x00
	subb	a,@r0
;     genIfxJump
	jc	00113$
	ljmp	00107$
00113$:
;../../Source/queue.c:176: pxNewQueue = ( xQUEUE * ) pvPortMalloc( sizeof( xQUEUE ) );
;     genCall
	mov	dpl,#0x3D
	mov	dph,#0x00
	lcall	_pvPortMalloc
	mov	r3,dpl
	mov	r4,dph
	mov	r5,b
;     genAssign
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	@r0,ar3
	inc	r0
	mov	@r0,ar4
	inc	r0
	mov	@r0,ar5
;../../Source/queue.c:177: if( pxNewQueue != NULL )
;     genCmpEq
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	cjne	@r0,#0x00,00114$
	inc	r0
	cjne	@r0,#0x00,00114$
	inc	r0
	cjne	@r0,#0x00,00114$
	ljmp	00107$
00114$:
;../../Source/queue.c:181: usQueueSizeInBytes = ( unsigned portSHORT ) ( ucQueueLength * ucItemSize ) + ( unsigned portSHORT ) 1;
;     genMult
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,_bp
	add	a,#0xfd
	mov	r1,a
;     genMultOneByte
	mov	b,@r0
	mov	a,@r1
	mul	ab
	mov	r6,a
	mov	r7,b
;     genPlus
;     genPlusIncr
	mov	a,#0x01
	add	a,ar6
	mov	r2,a
	mov	a,#0x00
	addc	a,ar7
	mov	r3,a
;../../Source/queue.c:183: pxNewQueue->pcHead = ( signed portCHAR * ) pvPortMalloc( usQueueSizeInBytes );
;     genCall
	mov	dpl,r2
	mov	dph,r3
	push	ar6
	push	ar7
	lcall	_pvPortMalloc
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	pop	ar7
	pop	ar6
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r2
	lcall	__gptrput
	inc	dptr
	mov	a,r3
	lcall	__gptrput
	inc	dptr
	mov	a,r4
	lcall	__gptrput
;../../Source/queue.c:184: if( pxNewQueue->pcHead != NULL )
;     genCmpEq
	cjne	r2,#0x00,00115$
	cjne	r3,#0x00,00115$
	cjne	r4,#0x00,00115$
	ljmp	00102$
00115$:
;../../Source/queue.c:188: pxNewQueue->pcTail = pxNewQueue->pcHead + ( ucQueueLength * ucItemSize );
;     genPlus
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	a,_bp
	add	a,#0x05
	mov	r1,a
;     genPlusIncr
	mov	a,#0x03
	add	a,@r0
	mov	@r1,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	inc	r1
	mov	@r1,a
	inc	r0
	inc	r1
	mov	a,@r0
	mov	@r1,a
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r2,a
	inc	dptr
	lcall	__gptrget
	mov	r3,a
;     genPlus
	mov	a,ar6
	add	a,ar5
	mov	r6,a
	mov	a,ar7
	addc	a,ar2
	mov	r7,a
	mov	ar4,r3
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x05
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r6
	lcall	__gptrput
	inc	dptr
	mov	a,r7
	lcall	__gptrput
	inc	dptr
	mov	a,r4
	lcall	__gptrput
;../../Source/queue.c:189: pxNewQueue->ucMessagesWaiting = ( unsigned portCHAR ) 0;
;     genPlus
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	a,#0x38
	add	a,@r0
	mov	r4,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r4
	mov	dph,r6
	mov	b,r7
	mov	a,#0x00
	lcall	__gptrput
;../../Source/queue.c:190: pxNewQueue->pcWriteTo = pxNewQueue->pcHead;
;     genPlus
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	a,#0x06
	add	a,@r0
	mov	r4,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r4
	mov	dph,r6
	mov	b,r7
	mov	a,r5
	lcall	__gptrput
	inc	dptr
	mov	a,r2
	lcall	__gptrput
	inc	dptr
	mov	a,r3
	lcall	__gptrput
;../../Source/queue.c:191: pxNewQueue->pcReadFrom = pxNewQueue->pcHead + ( ( ucQueueLength - ( unsigned portCHAR ) 1 ) * ucItemSize );
;     genPlus
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	a,_bp
	add	a,#0x05
	mov	r1,a
	mov	a,#0x09
	add	a,@r0
	mov	@r1,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	inc	r1
	mov	@r1,a
	inc	r0
	inc	r1
	mov	a,@r0
	mov	@r1,a
;     genCast
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	ar4,@r0
	mov	r6,#0x00
;     genMinus
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
;     genMinusDec
	mov	a,r4
	add	a,#0xff
	mov	@r0,a
	mov	a,r6
	addc	a,#0xff
	inc	r0
	mov	@r0,a
;     genCast
	mov	a,_bp
	add	a,#0xfd
	mov	r0,a
	mov	ar7,@r0
	mov	r4,#0x00
;     genIpush
	push	ar2
	push	ar3
	push	ar5
	push	ar7
	push	ar4
;     genCall
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	lcall	__mulint
	mov	r4,dpl
	mov	r6,dph
	dec	sp
	dec	sp
	pop	ar5
	pop	ar3
	pop	ar2
;     genPlus
	mov	a,ar4
	add	a,ar5
	mov	r5,a
	mov	a,ar6
	addc	a,ar2
	mov	r2,a
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x05
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r5
	lcall	__gptrput
	inc	dptr
	mov	a,r2
	lcall	__gptrput
	inc	dptr
	mov	a,r3
	lcall	__gptrput
;../../Source/queue.c:192: pxNewQueue->ucLength = ucQueueLength;
;     genPlus
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	a,#0x39
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,@r0
	lcall	__gptrput
;../../Source/queue.c:193: pxNewQueue->ucItemSize = ucItemSize;
;     genPlus
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	a,#0x3A
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,_bp
	add	a,#0xfd
	mov	r0,a
	mov	a,@r0
	lcall	__gptrput
;../../Source/queue.c:194: pxNewQueue->cRxLock = queueUNLOCKED;
;     genPlus
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	a,#0x3B
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,#0xFF
	lcall	__gptrput
;../../Source/queue.c:195: pxNewQueue->cTxLock = queueUNLOCKED;
;     genPlus
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	a,#0x3C
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,#0xFF
	lcall	__gptrput
;../../Source/queue.c:198: vListInitialise( &( pxNewQueue->xTasksWaitingToSend ) );
;     genPlus
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	a,#0x0C
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genCall
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	_vListInitialise
;../../Source/queue.c:199: vListInitialise( &( pxNewQueue->xTasksWaitingToReceive ) ); 
;     genPlus
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	a,#0x22
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genCall
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	_vListInitialise
;../../Source/queue.c:201: return  pxNewQueue;
;     genRet
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	ljmp	00108$
00102$:
;../../Source/queue.c:205: vPortFree( pxNewQueue );
;     genCall
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	_vPortFree
00107$:
;../../Source/queue.c:212: return NULL;
;     genRet
	mov	dpl,#0x00
	mov	dph,#0x00
	mov	b,#0x00
00108$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'cQueueSend'
;------------------------------------------------------------
;pvItemToQueue             Allocated to stack - offset -5
;xTicksToWait              Allocated to stack - offset -7
;pxQueue                   Allocated to stack - offset 1
;cReturn                   Allocated to registers r2 
;sloc0                     Allocated to stack - offset 4
;sloc1                     Allocated to stack - offset 5
;sloc2                     Allocated to stack - offset 8
;sloc3                     Allocated to stack - offset 11
;------------------------------------------------------------
;../../Source/queue.c:216: signed portCHAR cQueueSend( xQueueHandle pxQueue, const void *pvItemToQueue, portTickType xTicksToWait )
;	-----------------------------------------
;	 function cQueueSend
;	-----------------------------------------
_cQueueSend:
	push	_bp
	mov	_bp,sp
;     genReceive
	push	dpl
	push	dph
	push	b
	mov	a,sp
	add	a,#0x0c
	mov	sp,a
;../../Source/queue.c:221: vTaskSuspendAll();
;     genCall
	lcall	_vTaskSuspendAll
;../../Source/queue.c:243: prvLockQueue( pxQueue );
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3B
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r2,a
;     genPlus
;     genPlusIncr
	inc	r2
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,r2
	lcall	__gptrput
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3C
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
;     genPlus
;     genPlusIncr
	inc	r5
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/queue.c:261: if( prvIsQueueFull( pxQueue ) )
;     genCall
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	_prvIsQueueFull
	mov	a,dpl
;     genIfx
;     genIfxJump
	jnz	00126$
	ljmp	00106$
00126$:
;../../Source/queue.c:265: if( xTicksToWait > ( portTickType ) 0 )
;     genIfx
	mov	a,_bp
	add	a,#0xf9
	mov	r0,a
	mov	a,@r0
	inc	r0
	orl	a,@r0
;     genIfxJump
	jnz	00127$
	ljmp	00106$
00127$:
;../../Source/queue.c:280: vTaskPlaceOnEventList( &( pxQueue->xTasksWaitingToSend ), xTicksToWait );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x0C
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genIpush
	mov	a,_bp
	add	a,#0xf9
	mov	r0,a
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
;     genCall
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	_vTaskPlaceOnEventList
	dec	sp
	dec	sp
;../../Source/queue.c:292: taskENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/queue.c:301: prvUnlockQueue( pxQueue );
;     genCall
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	_prvUnlockQueue
;../../Source/queue.c:305: if( !cTaskResumeAll() )
;     genCall
	lcall	_cTaskResumeAll
	mov	a,dpl
;     genIfx
;     genIfxJump
	jz	00128$
	ljmp	00102$
00128$:
;../../Source/queue.c:307: taskYIELD();
;     genCall
	lcall	_vPortYield
00102$:
;../../Source/queue.c:312: vTaskSuspendAll();
;     genCall
	lcall	_vTaskSuspendAll
;../../Source/queue.c:313: prvLockQueue( pxQueue );				
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3B
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
;     genPlus
;     genPlusIncr
	inc	r5
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3C
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
;     genPlus
;     genPlusIncr
	inc	r5
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/queue.c:315: taskEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
00106$:
;../../Source/queue.c:324: taskENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/queue.c:326: if( pxQueue->ucMessagesWaiting < pxQueue->ucLength )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x38
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	lcall	__gptrget
	mov	@r0,a
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x39
	add	a,@r0
	mov	r6,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r7,a
	inc	r0
	mov	ar5,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r6
	mov	dph,r7
	mov	b,r5
	lcall	__gptrget
	mov	r6,a
;     genCmpLt
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
;     genCmp
	clr	c
	mov	a,@r0
	subb	a,r6
;     genIfxJump
	jc	00129$
	ljmp	00110$
00129$:
;../../Source/queue.c:329: prvCopyQueueData( pxQueue, pvItemToQueue );		
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,_bp
	add	a,#0x05
	mov	r1,a
	mov	a,#0x3A
	add	a,@r0
	mov	@r1,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	inc	r1
	mov	@r1,a
	inc	r0
	inc	r1
	mov	a,@r0
	mov	@r1,a
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x05
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r5,a
;     genCast
	mov	a,_bp
	add	a,#0x0b
	mov	r0,a
	mov	@r0,ar5
	inc	r0
	mov	@r0,#0x00
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,_bp
	add	a,#0x08
	mov	r1,a
	mov	a,#0x06
	add	a,@r0
	mov	@r1,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	inc	r1
	mov	@r1,a
	inc	r0
	inc	r1
	mov	a,@r0
	mov	@r1,a
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r7,a
	inc	dptr
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
;     genIpush
	push	ar2
	push	ar3
	push	ar4
	mov	a,_bp
	add	a,#0x0b
	mov	r0,a
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
;     genIpush
	mov	a,_bp
	add	a,#0xfb
	mov	r0,a
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
;     genCall
	mov	dpl,r7
	mov	dph,r5
	mov	b,r6
	lcall	_memcpy
	mov	a,sp
	add	a,#0xfb
	mov	sp,a
	pop	ar4
	pop	ar3
	pop	ar2
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
;     genPlus
;     genPlusIncr
	inc	r5
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r2,a
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x05
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r5,a
;     genPlus
	mov	a,ar5
	add	a,ar2
	mov	r2,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r2
	lcall	__gptrput
	inc	dptr
	mov	a,r3
	lcall	__gptrput
	inc	dptr
	mov	a,r4
	lcall	__gptrput
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
;     genPlusIncr
	mov	a,#0x03
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
	inc	dptr
	lcall	__gptrget
	mov	r7,a
;     genCmpLt
;     genCmp
	clr	c
	mov	a,r2
	subb	a,r5
	mov	a,r3
	subb	a,r6
	mov	a,r4
	xrl	a,#0x80
	mov	b,r7
	xrl	b,#0x80
	subb	a,b
;     genIfxJump
	jnc	00130$
	ljmp	00108$
00130$:
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r2,a
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r2
	lcall	__gptrput
	inc	dptr
	mov	a,r3
	lcall	__gptrput
	inc	dptr
	mov	a,r4
	lcall	__gptrput
00108$:
;../../Source/queue.c:330: cReturn = ( signed portCHAR ) pdPASS;
;     genAssign
	mov	r2,#0x01
;../../Source/queue.c:334: ++( pxQueue->cTxLock );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3C
	add	a,@r0
	mov	r3,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r4,a
	inc	r0
	mov	ar5,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	lcall	__gptrget
	mov	r6,a
;     genPlus
;     genPlusIncr
	inc	r6
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	mov	a,r6
	lcall	__gptrput
	ljmp	00111$
00110$:
;../../Source/queue.c:338: cReturn = errQUEUE_FULL;
;     genAssign
	mov	r2,#0xFD
00111$:
;../../Source/queue.c:341: taskEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/queue.c:346: if( prvUnlockQueue( pxQueue ) )
;     genCall
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	push	ar2
	lcall	_prvUnlockQueue
	mov	a,dpl
	pop	ar2
;     genIfx
;     genIfxJump
	jnz	00131$
	ljmp	00115$
00131$:
;../../Source/queue.c:352: if( !cTaskResumeAll() )
;     genCall
	push	ar2
	lcall	_cTaskResumeAll
	mov	a,dpl
	pop	ar2
;     genIfx
;     genIfxJump
	jz	00132$
	ljmp	00116$
00132$:
;../../Source/queue.c:354: taskYIELD();
;     genCall
	lcall	_vPortYield
	ljmp	00116$
00115$:
;../../Source/queue.c:361: cTaskResumeAll();
;     genCall
	push	ar2
	lcall	_cTaskResumeAll
	pop	ar2
00116$:
;../../Source/queue.c:364: return cReturn;
;     genRet
	mov	dpl,r2
00117$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'cQueueSendFromISR'
;------------------------------------------------------------
;pvItemToQueue             Allocated to stack - offset -5
;cTaskPreviouslyWoken      Allocated to stack - offset -6
;pxQueue                   Allocated to stack - offset 1
;sloc0                     Allocated to stack - offset 4
;sloc1                     Allocated to stack - offset 5
;sloc2                     Allocated to stack - offset 8
;sloc3                     Allocated to stack - offset 11
;------------------------------------------------------------
;../../Source/queue.c:368: signed portCHAR cQueueSendFromISR( xQueueHandle pxQueue, const void *pvItemToQueue, signed portCHAR cTaskPreviouslyWoken )
;	-----------------------------------------
;	 function cQueueSendFromISR
;	-----------------------------------------
_cQueueSendFromISR:
	push	_bp
	mov	_bp,sp
;     genReceive
	push	dpl
	push	dph
	push	b
	mov	a,sp
	add	a,#0x0c
	mov	sp,a
;../../Source/queue.c:375: if( pxQueue->ucMessagesWaiting < pxQueue->ucLength )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x38
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	lcall	__gptrget
	mov	@r0,a
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x39
	add	a,@r0
	mov	r3,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r4,a
	inc	r0
	mov	ar2,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r3
	mov	dph,r4
	mov	b,r2
	lcall	__gptrget
	mov	r3,a
;     genCmpLt
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
;     genCmp
	clr	c
	mov	a,@r0
	subb	a,r3
;     genIfxJump
	jc	00122$
	ljmp	00113$
00122$:
;../../Source/queue.c:377: prvCopyQueueData( pxQueue, pvItemToQueue );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,_bp
	add	a,#0x05
	mov	r1,a
	mov	a,#0x3A
	add	a,@r0
	mov	@r1,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	inc	r1
	mov	@r1,a
	inc	r0
	inc	r1
	mov	a,@r0
	mov	@r1,a
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x05
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r2,a
;     genCast
	mov	a,_bp
	add	a,#0x0b
	mov	r0,a
	mov	@r0,ar2
	inc	r0
	mov	@r0,#0x00
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,_bp
	add	a,#0x08
	mov	r1,a
	mov	a,#0x06
	add	a,@r0
	mov	@r1,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	inc	r1
	mov	@r1,a
	inc	r0
	inc	r1
	mov	a,@r0
	mov	@r1,a
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r4,a
	inc	dptr
	lcall	__gptrget
	mov	r2,a
	inc	dptr
	lcall	__gptrget
	mov	r3,a
;     genIpush
	push	ar5
	push	ar6
	push	ar7
	mov	a,_bp
	add	a,#0x0b
	mov	r0,a
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
;     genIpush
	mov	a,_bp
	add	a,#0xfb
	mov	r0,a
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
;     genCall
	mov	dpl,r4
	mov	dph,r2
	mov	b,r3
	lcall	_memcpy
	mov	a,sp
	add	a,#0xfb
	mov	sp,a
	pop	ar7
	pop	ar6
	pop	ar5
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r2,a
;     genPlus
;     genPlusIncr
	inc	r2
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,r2
	lcall	__gptrput
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r2,a
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x05
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r5,a
;     genPlus
	mov	a,ar5
	add	a,ar2
	mov	r2,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r2
	lcall	__gptrput
	inc	dptr
	mov	a,r3
	lcall	__gptrput
	inc	dptr
	mov	a,r4
	lcall	__gptrput
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
;     genPlusIncr
	mov	a,#0x03
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
	inc	dptr
	lcall	__gptrget
	mov	r7,a
;     genCmpLt
;     genCmp
	clr	c
	mov	a,r2
	subb	a,r5
	mov	a,r3
	subb	a,r6
	mov	a,r4
	xrl	a,#0x80
	mov	b,r7
	xrl	b,#0x80
	subb	a,b
;     genIfxJump
	jnc	00123$
	ljmp	00102$
00123$:
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r2,a
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r2
	lcall	__gptrput
	inc	dptr
	mov	a,r3
	lcall	__gptrput
	inc	dptr
	mov	a,r4
	lcall	__gptrput
00102$:
;../../Source/queue.c:381: if( pxQueue->cTxLock == queueUNLOCKED )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3C
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
;     genCmpEq
	cjne	r5,#0xFF,00124$
	sjmp	00125$
00124$:
	ljmp	00110$
00125$:
;../../Source/queue.c:385: if( !cTaskPreviouslyWoken )		
;     genIfx
	mov	a,_bp
	add	a,#0xfa
	mov	r0,a
	mov	a,@r0
;     genIfxJump
	jz	00126$
	ljmp	00113$
00126$:
;../../Source/queue.c:387: if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) ) )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x22
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r6,a
	inc	dptr
	lcall	__gptrget
	mov	r7,a
;     genCmpEq
	cjne	r6,#0x00,00127$
	cjne	r7,#0x00,00127$
	ljmp	00113$
00127$:
;../../Source/queue.c:389: if( cTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToReceive ) ) != ( signed portCHAR ) pdFALSE )
;     genCall
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	_cTaskRemoveFromEventList
	mov	r6,dpl
;     genCmpEq
	cjne	r6,#0x00,00128$
	ljmp	00113$
00128$:
;../../Source/queue.c:393: return pdTRUE;
;     genRet
	mov	dpl,#0x01
	ljmp	00114$
00110$:
;../../Source/queue.c:402: ++( pxQueue->cTxLock );
;     genPlus
;     genPlusIncr
	inc	r5
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
00113$:
;../../Source/queue.c:406: return cTaskPreviouslyWoken;
;     genRet
	mov	a,_bp
	add	a,#0xfa
	mov	r0,a
	mov	dpl,@r0
00114$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'cQueueReceive'
;------------------------------------------------------------
;pcBuffer                  Allocated to stack - offset -5
;xTicksToWait              Allocated to stack - offset -7
;pxQueue                   Allocated to stack - offset 1
;cReturn                   Allocated to registers r2 
;sloc0                     Allocated to stack - offset 4
;sloc1                     Allocated to stack - offset 7
;sloc2                     Allocated to stack - offset 10
;sloc3                     Allocated to stack - offset 11
;------------------------------------------------------------
;../../Source/queue.c:410: signed portCHAR cQueueReceive( xQueueHandle pxQueue, void *pcBuffer, portTickType xTicksToWait )
;	-----------------------------------------
;	 function cQueueReceive
;	-----------------------------------------
_cQueueReceive:
	push	_bp
	mov	_bp,sp
;     genReceive
	push	dpl
	push	dph
	push	b
	mov	a,sp
	add	a,#0x0b
	mov	sp,a
;../../Source/queue.c:418: vTaskSuspendAll();
;     genCall
	lcall	_vTaskSuspendAll
;../../Source/queue.c:421: prvLockQueue( pxQueue );
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3B
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r2,a
;     genPlus
;     genPlusIncr
	inc	r2
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,r2
	lcall	__gptrput
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3C
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
;     genPlus
;     genPlusIncr
	inc	r5
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/queue.c:424: if( prvIsQueueEmpty( pxQueue ) )
;     genCall
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	_prvIsQueueEmpty
	mov	a,dpl
;     genIfx
;     genIfxJump
	jnz	00126$
	ljmp	00106$
00126$:
;../../Source/queue.c:428: if( xTicksToWait > ( portTickType ) 0 )
;     genIfx
	mov	a,_bp
	add	a,#0xf9
	mov	r0,a
	mov	a,@r0
	inc	r0
	orl	a,@r0
;     genIfxJump
	jnz	00127$
	ljmp	00106$
00127$:
;../../Source/queue.c:430: vTaskPlaceOnEventList( &( pxQueue->xTasksWaitingToReceive ), xTicksToWait );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x22
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genIpush
	mov	a,_bp
	add	a,#0xf9
	mov	r0,a
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
;     genCall
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	_vTaskPlaceOnEventList
	dec	sp
	dec	sp
;../../Source/queue.c:431: taskENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/queue.c:433: prvUnlockQueue( pxQueue );
;     genCall
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	_prvUnlockQueue
;../../Source/queue.c:434: if( !cTaskResumeAll() )
;     genCall
	lcall	_cTaskResumeAll
	mov	a,dpl
;     genIfx
;     genIfxJump
	jz	00128$
	ljmp	00102$
00128$:
;../../Source/queue.c:436: taskYIELD();
;     genCall
	lcall	_vPortYield
00102$:
;../../Source/queue.c:439: vTaskSuspendAll();
;     genCall
	lcall	_vTaskSuspendAll
;../../Source/queue.c:440: prvLockQueue( pxQueue );
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3B
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
;     genPlus
;     genPlusIncr
	inc	r5
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3C
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
;     genPlus
;     genPlusIncr
	inc	r5
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/queue.c:442: taskEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
00106$:
;../../Source/queue.c:446: taskENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/queue.c:448: if( pxQueue->ucMessagesWaiting > ( unsigned portCHAR ) 0 )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x38
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,_bp
	add	a,#0x0b
	mov	r0,a
	lcall	__gptrget
	mov	@r0,a
;     genCmpGt
	mov	a,_bp
	add	a,#0x0b
	mov	r0,a
;     genCmp
	clr	c
	mov	a,#0x00
	subb	a,@r0
;     genIfxJump
	jc	00129$
	ljmp	00110$
00129$:
;../../Source/queue.c:450: pxQueue->pcReadFrom += pxQueue->ucItemSize;
;     genIpush
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,_bp
	add	a,#0x04
	mov	r1,a
	mov	a,#0x09
	add	a,@r0
	mov	@r1,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	inc	r1
	mov	@r1,a
	inc	r0
	inc	r1
	mov	a,@r0
	mov	@r1,a
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,_bp
	add	a,#0x07
	mov	r1,a
	lcall	__gptrget
	mov	@r1,a
	inc	dptr
	lcall	__gptrget
	inc	r1
	mov	@r1,a
	inc	dptr
	lcall	__gptrget
	inc	r1
	mov	@r1,a
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3A
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,_bp
	add	a,#0x0a
	mov	r0,a
	lcall	__gptrget
	mov	@r0,a
;     genPlus
	mov	a,_bp
	add	a,#0x07
	mov	r0,a
	mov	a,_bp
	add	a,#0x0a
	mov	r1,a
	mov	a,@r1
	add	a,@r0
	mov	@r0,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	@r0,a
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
	mov	a,_bp
	add	a,#0x07
	mov	r1,a
	mov	a,@r1
	lcall	__gptrput
	inc	dptr
	inc	r1
	mov	a,@r1
	lcall	__gptrput
	inc	dptr
	inc	r1
	mov	a,@r1
	lcall	__gptrput
;../../Source/queue.c:451: if( pxQueue->pcReadFrom >= pxQueue->pcTail )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
;     genPlusIncr
	mov	a,#0x03
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
	inc	dptr
	lcall	__gptrget
	mov	r7,a
;     genCmpLt
	mov	a,_bp
	add	a,#0x07
	mov	r0,a
;     genCmp
	clr	c
	mov	a,@r0
	subb	a,r5
	inc	r0
	mov	a,@r0
	subb	a,r6
	inc	r0
	mov	a,@r0
	xrl	a,#0x80
	mov	b,r7
	xrl	b,#0x80
	subb	a,b
	clr	a
	rlc	a
;     genIpop
;     genIfx
;     genIfxJump
	jz	00130$
	ljmp	00108$
00130$:
;../../Source/queue.c:453: pxQueue->pcReadFrom = pxQueue->pcHead;
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r6,a
	inc	dptr
	lcall	__gptrget
	mov	r7,a
	inc	dptr
	lcall	__gptrget
	mov	r5,a
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
	mov	a,r6
	lcall	__gptrput
	inc	dptr
	mov	a,r7
	lcall	__gptrput
	inc	dptr
	mov	a,r5
	lcall	__gptrput
00108$:
;../../Source/queue.c:455: --( pxQueue->ucMessagesWaiting );
;     genMinus
	mov	a,_bp
	add	a,#0x0b
	mov	r0,a
;     genMinusDec
	mov	a,@r0
	dec	a
	mov	r5,a
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
;../../Source/queue.c:456: memcpy( ( void * ) pcBuffer, ( void * ) pxQueue->pcReadFrom, ( unsigned ) pxQueue->ucItemSize );
;     genCast
	mov	a,_bp
	add	a,#0x0a
	mov	r0,a
	mov	ar2,@r0
	mov	r3,#0x00
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r4,a
	inc	dptr
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
;     genIpush
	push	ar2
	push	ar3
;     genIpush
	push	ar4
	push	ar5
	push	ar6
;     genCall
	mov	a,_bp
	add	a,#0xfb
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	_memcpy
	mov	a,sp
	add	a,#0xfb
	mov	sp,a
;../../Source/queue.c:460: ++( pxQueue->cRxLock );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3B
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
;     genPlus
;     genPlusIncr
	inc	r5
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
;../../Source/queue.c:461: cReturn = ( signed portCHAR ) pdPASS;
;     genAssign
	mov	r2,#0x01
	ljmp	00111$
00110$:
;../../Source/queue.c:465: cReturn = ( signed portCHAR ) pdFAIL;
;     genAssign
	mov	r2,#0x00
00111$:
;../../Source/queue.c:468: taskEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/queue.c:471: if( prvUnlockQueue( pxQueue ) )
;     genCall
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	push	ar2
	lcall	_prvUnlockQueue
	mov	a,dpl
	pop	ar2
;     genIfx
;     genIfxJump
	jnz	00131$
	ljmp	00115$
00131$:
;../../Source/queue.c:473: if( !cTaskResumeAll() )
;     genCall
	push	ar2
	lcall	_cTaskResumeAll
	mov	a,dpl
	pop	ar2
;     genIfx
;     genIfxJump
	jz	00132$
	ljmp	00116$
00132$:
;../../Source/queue.c:475: taskYIELD();
;     genCall
	lcall	_vPortYield
	ljmp	00116$
00115$:
;../../Source/queue.c:480: cTaskResumeAll();
;     genCall
	push	ar2
	lcall	_cTaskResumeAll
	pop	ar2
00116$:
;../../Source/queue.c:483: return cReturn;
;     genRet
	mov	dpl,r2
00117$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'cQueueReceiveFromISR'
;------------------------------------------------------------
;pcBuffer                  Allocated to stack - offset -5
;pcTaskWoken               Allocated to stack - offset -8
;pxQueue                   Allocated to stack - offset 1
;cReturn                   Allocated to registers r2 
;sloc0                     Allocated to stack - offset 4
;sloc1                     Allocated to stack - offset 5
;sloc2                     Allocated to stack - offset 8
;sloc3                     Allocated to stack - offset 9
;------------------------------------------------------------
;../../Source/queue.c:487: signed portCHAR cQueueReceiveFromISR( xQueueHandle pxQueue, void *pcBuffer, signed portCHAR *pcTaskWoken )
;	-----------------------------------------
;	 function cQueueReceiveFromISR
;	-----------------------------------------
_cQueueReceiveFromISR:
	push	_bp
	mov	_bp,sp
;     genReceive
	push	dpl
	push	dph
	push	b
	mov	a,sp
	add	a,#0x0b
	mov	sp,a
;../../Source/queue.c:492: if( pxQueue->ucMessagesWaiting > ( unsigned portCHAR ) 0 )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x38
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	lcall	__gptrget
	mov	@r0,a
;     genCmpGt
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
;     genCmp
	clr	c
	mov	a,#0x00
	subb	a,@r0
;     genIfxJump
	jc	00123$
	ljmp	00113$
00123$:
;../../Source/queue.c:495: pxQueue->pcReadFrom += pxQueue->ucItemSize;
;     genIpush
	push	ar5
	push	ar6
	push	ar7
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,_bp
	add	a,#0x05
	mov	r1,a
	mov	a,#0x09
	add	a,@r0
	mov	@r1,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	inc	r1
	mov	@r1,a
	inc	r0
	inc	r1
	mov	a,@r0
	mov	@r1,a
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x05
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
	inc	dptr
	lcall	__gptrget
	mov	r7,a
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3A
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
	lcall	__gptrget
	mov	@r0,a
;     genPlus
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
	mov	a,@r0
	add	a,ar5
	mov	r5,a
	mov	a,#0x00
	addc	a,ar6
	mov	r6,a
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x05
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r5
	lcall	__gptrput
	inc	dptr
	mov	a,r6
	lcall	__gptrput
	inc	dptr
	mov	a,r7
	lcall	__gptrput
;../../Source/queue.c:496: if( pxQueue->pcReadFrom >= pxQueue->pcTail )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
;     genPlusIncr
	mov	a,#0x03
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r2,a
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
;     genCmpLt
;     genCmp
	clr	c
	mov	a,r5
	subb	a,r2
	mov	a,r6
	subb	a,r3
	mov	a,r7
	xrl	a,#0x80
	mov	b,r4
	xrl	b,#0x80
	subb	a,b
	clr	a
	rlc	a
;     genIpop
	pop	ar7
	pop	ar6
	pop	ar5
;     genIfx
;     genIfxJump
	jz	00124$
	ljmp	00102$
00124$:
;../../Source/queue.c:498: pxQueue->pcReadFrom = pxQueue->pcHead;
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r2,a
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x05
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,r2
	lcall	__gptrput
	inc	dptr
	mov	a,r3
	lcall	__gptrput
	inc	dptr
	mov	a,r4
	lcall	__gptrput
00102$:
;../../Source/queue.c:500: --( pxQueue->ucMessagesWaiting );
;     genMinus
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
;     genMinusDec
	mov	a,@r0
	dec	a
	mov	r2,a
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,r2
	lcall	__gptrput
;../../Source/queue.c:501: memcpy( ( void * ) pcBuffer, ( void * ) pxQueue->pcReadFrom, ( unsigned ) pxQueue->ucItemSize );
;     genCast
	mov	a,_bp
	add	a,#0x08
	mov	r0,a
	mov	ar2,@r0
	mov	r3,#0x00
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x05
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r4,a
	inc	dptr
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
;     genIpush
	push	ar2
	push	ar3
;     genIpush
	push	ar4
	push	ar5
	push	ar6
;     genCall
	mov	a,_bp
	add	a,#0xfb
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	_memcpy
	mov	a,sp
	add	a,#0xfb
	mov	sp,a
;../../Source/queue.c:506: if( pxQueue->cRxLock == queueUNLOCKED )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3B
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
;     genCmpEq
	cjne	r5,#0xFF,00125$
	sjmp	00126$
00125$:
	ljmp	00110$
00126$:
;../../Source/queue.c:510: if( !( *pcTaskWoken ) )
;     genAssign
	mov	a,_bp
	add	a,#0xf8
	mov	r0,a
	mov	ar2,@r0
	inc	r0
	mov	ar3,@r0
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
;     genIfxJump
	jz	00127$
	ljmp	00111$
00127$:
;../../Source/queue.c:512: if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) ) )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,_bp
	add	a,#0x09
	mov	r1,a
	mov	a,#0x0C
	add	a,@r0
	mov	@r1,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	inc	r1
	mov	@r1,a
	inc	r0
	inc	r1
	mov	a,@r0
	mov	@r1,a
;     genPointerGet
;     genGenPointerGet
	mov	a,_bp
	add	a,#0x09
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r6,a
	inc	dptr
	lcall	__gptrget
	mov	r7,a
;     genCmpEq
	cjne	r6,#0x00,00128$
	cjne	r7,#0x00,00128$
	ljmp	00111$
00128$:
;../../Source/queue.c:514: if( cTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToSend ) ) != ( signed portCHAR ) pdFALSE )
;     genCall
	mov	a,_bp
	add	a,#0x09
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	push	ar2
	push	ar3
	push	ar4
	lcall	_cTaskRemoveFromEventList
	mov	r6,dpl
	pop	ar4
	pop	ar3
	pop	ar2
;     genCmpEq
	cjne	r6,#0x00,00129$
	ljmp	00111$
00129$:
;../../Source/queue.c:518: *pcTaskWoken = ( signed portCHAR ) pdTRUE;
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,#0x01
	lcall	__gptrput
	ljmp	00111$
00110$:
;../../Source/queue.c:527: ++( pxQueue->cRxLock );
;     genPlus
;     genPlusIncr
	inc	r5
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
00111$:
;../../Source/queue.c:530: cReturn = ( signed portCHAR ) pdPASS;
;     genAssign
	mov	r2,#0x01
	ljmp	00114$
00113$:
;../../Source/queue.c:534: cReturn = ( signed portCHAR ) pdFAIL;
;     genAssign
	mov	r2,#0x00
00114$:
;../../Source/queue.c:537: return cReturn;
;     genRet
	mov	dpl,r2
00115$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'ucQueueMessagesWaiting'
;------------------------------------------------------------
;pxQueue                   Allocated to registers r2 r3 r4 
;ucReturn                  Allocated to registers r2 
;------------------------------------------------------------
;../../Source/queue.c:541: unsigned portCHAR ucQueueMessagesWaiting( xQueueHandle pxQueue )
;	-----------------------------------------
;	 function ucQueueMessagesWaiting
;	-----------------------------------------
_ucQueueMessagesWaiting:
	push	_bp
	mov	_bp,sp
;     genReceive
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;../../Source/queue.c:545: taskENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/queue.c:546: ucReturn = pxQueue->ucMessagesWaiting;
;     genPlus
	mov	a,#0x38
	add	a,ar2
	mov	r2,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r2,a
;     genAssign
;../../Source/queue.c:547: taskEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/queue.c:549: return ucReturn;
;     genRet
	mov	dpl,r2
00101$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vQueueDelete'
;------------------------------------------------------------
;pxQueue                   Allocated to registers r2 r3 r4 
;------------------------------------------------------------
;../../Source/queue.c:553: void vQueueDelete( xQueueHandle pxQueue )
;	-----------------------------------------
;	 function vQueueDelete
;	-----------------------------------------
_vQueueDelete:
	push	_bp
	mov	_bp,sp
;     genReceive
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;../../Source/queue.c:555: vPortFree( pxQueue->pcHead );
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
	inc	dptr
	lcall	__gptrget
	mov	r7,a
;     genCall
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	push	ar2
	push	ar3
	push	ar4
	lcall	_vPortFree
	pop	ar4
	pop	ar3
	pop	ar2
;../../Source/queue.c:556: vPortFree( pxQueue );
;     genCall
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	_vPortFree
00101$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'prvUnlockQueue'
;------------------------------------------------------------
;pxQueue                   Allocated to stack - offset 1
;cYieldRequired            Allocated to stack - offset 4
;------------------------------------------------------------
;../../Source/queue.c:560: static signed portCHAR prvUnlockQueue( xQueueHandle pxQueue )
;	-----------------------------------------
;	 function prvUnlockQueue
;	-----------------------------------------
_prvUnlockQueue:
	push	_bp
	mov	_bp,sp
;     genReceive
	push	dpl
	push	dph
	push	b
	inc	sp
;../../Source/queue.c:562: signed portCHAR cYieldRequired = ( signed portCHAR ) pdFALSE;
;     genAssign
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	mov	@r0,#0x00
;../../Source/queue.c:570: taskENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/queue.c:572: --( pxQueue->cTxLock );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3C
	add	a,@r0
	mov	r6,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r7,a
	inc	r0
	mov	ar5,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r6
	mov	dph,r7
	mov	b,r5
	lcall	__gptrget
	mov	r2,a
;     genMinus
;     genMinusDec
	dec	r2
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r6
	mov	dph,r7
	mov	b,r5
	mov	a,r2
	lcall	__gptrput
;../../Source/queue.c:575: if( pxQueue->cTxLock > queueUNLOCKED )
;     genCmpGt
;     genCmp
	clr	c
	mov	a,#0xFF
	xrl	a,#0x80
	mov	b,r2
	xrl	b,#0x80
	subb	a,b
;     genIfxJump
	jc	00121$
	ljmp	00106$
00121$:
;../../Source/queue.c:577: pxQueue->cTxLock = queueUNLOCKED;
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r6
	mov	dph,r7
	mov	b,r5
	mov	a,#0xFF
	lcall	__gptrput
;../../Source/queue.c:581: if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) ) )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x22
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
;     genCmpEq
	cjne	r5,#0x00,00122$
	cjne	r6,#0x00,00122$
	ljmp	00106$
00122$:
;../../Source/queue.c:585: if( cTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToReceive ) ) != ( signed portCHAR ) pdFALSE )
;     genCall
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	_cTaskRemoveFromEventList
	mov	r2,dpl
;     genCmpEq
	cjne	r2,#0x00,00123$
	ljmp	00106$
00123$:
;../../Source/queue.c:589: cYieldRequired = ( signed portCHAR ) pdTRUE;
;     genAssign
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	mov	@r0,#0x01
00106$:
;../../Source/queue.c:594: taskEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/queue.c:597: taskENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/queue.c:599: --( pxQueue->cRxLock );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x3B
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
;     genMinus
;     genMinusDec
	dec	r5
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
;../../Source/queue.c:601: if( pxQueue->cRxLock > queueUNLOCKED )
;     genCmpGt
;     genCmp
	clr	c
	mov	a,#0xFF
	xrl	a,#0x80
	mov	b,r5
	xrl	b,#0x80
	subb	a,b
;     genIfxJump
	jc	00124$
	ljmp	00112$
00124$:
;../../Source/queue.c:603: pxQueue->cRxLock = queueUNLOCKED;
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,#0xFF
	lcall	__gptrput
;../../Source/queue.c:605: if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) ) )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x0C
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
;     genCmpEq
	cjne	r5,#0x00,00125$
	cjne	r6,#0x00,00125$
	ljmp	00112$
00125$:
;../../Source/queue.c:607: if( cTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToSend ) ) != ( signed portCHAR ) pdFALSE )
;     genCall
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	_cTaskRemoveFromEventList
	mov	r2,dpl
;     genCmpEq
	cjne	r2,#0x00,00126$
	ljmp	00112$
00126$:
;../../Source/queue.c:609: cYieldRequired = ( signed portCHAR ) pdTRUE;
;     genAssign
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	mov	@r0,#0x01
00112$:
;../../Source/queue.c:614: taskEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/queue.c:616: return cYieldRequired;
;     genRet
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	mov	dpl,@r0
00113$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'prvIsQueueEmpty'
;------------------------------------------------------------
;pxQueue                   Allocated to registers r2 r3 r4 
;cReturn                   Allocated to registers r2 
;------------------------------------------------------------
;../../Source/queue.c:620: static signed portCHAR prvIsQueueEmpty( const xQueueHandle pxQueue )
;	-----------------------------------------
;	 function prvIsQueueEmpty
;	-----------------------------------------
_prvIsQueueEmpty:
	push	_bp
	mov	_bp,sp
;     genReceive
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;../../Source/queue.c:624: taskENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/queue.c:625: cReturn = ( pxQueue->ucMessagesWaiting == ( unsigned portCHAR ) 0 );
;     genPlus
	mov	a,#0x38
	add	a,ar2
	mov	r2,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r2,a
;     genCmpEq
	cjne	r2,#0x00,00103$
	mov	a,#0x01
	sjmp	00104$
00103$:
	clr	a
00104$:
	mov	r2,a
;../../Source/queue.c:626: taskEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/queue.c:628: return cReturn;
;     genRet
	mov	dpl,r2
00101$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'prvIsQueueFull'
;------------------------------------------------------------
;pxQueue                   Allocated to registers r2 r3 r4 
;cReturn                   Allocated to registers r5 
;------------------------------------------------------------
;../../Source/queue.c:632: static signed portCHAR prvIsQueueFull( const xQueueHandle pxQueue )
;	-----------------------------------------
;	 function prvIsQueueFull
;	-----------------------------------------
_prvIsQueueFull:
	push	_bp
	mov	_bp,sp
;     genReceive
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;../../Source/queue.c:636: taskENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/queue.c:637: cReturn = ( pxQueue->ucMessagesWaiting == pxQueue->ucLength );
;     genPlus
	mov	a,#0x38
	add	a,ar2
	mov	r5,a
	mov	a,#0x00
	addc	a,ar3
	mov	r6,a
	mov	ar7,r4
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r5,a
;     genPlus
	mov	a,#0x39
	add	a,ar2
	mov	r2,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r2,a
;     genCmpEq
	mov	a,r5
	cjne	a,ar2,00103$
	mov	a,#0x01
	sjmp	00104$
00103$:
	clr	a
00104$:
	mov	r5,a
;     genAssign
;../../Source/queue.c:638: taskEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/queue.c:640: return cReturn;
;     genRet
	mov	dpl,r5
00101$:
	mov	sp,_bp
	pop	_bp
	ret
	.area CSEG    (CODE)
	.area XINIT   (CODE)
