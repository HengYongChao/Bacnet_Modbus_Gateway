;--------------------------------------------------------
; File Created by SDCC : FreeWare ANSI-C Compiler
; Version 2.4.8 #964 (Feb 23 2005)
; This file generated Fri May 20 14:05:27 2005
;--------------------------------------------------------
	.module ______Source_tasks
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
	.globl _pxCurrentTCB
	.globl _sTaskCreate
	.globl _vTaskDelayUntil
	.globl _vTaskDelay
	.globl _vTaskStartScheduler
	.globl _vTaskEndScheduler
	.globl _vTaskSuspendAll
	.globl _cTaskResumeAll
	.globl _xTaskGetTickCount
	.globl _usTaskGetNumberOfTasks
	.globl _vTaskIncrementTick
	.globl _vTaskSwitchContext
	.globl _vTaskPlaceOnEventList
	.globl _cTaskRemoveFromEventList
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
_pxReadyTasksLists:
	.ds 88
_xDelayedTaskList1:
	.ds 22
_xDelayedTaskList2:
	.ds 22
_pxDelayedTaskList:
	.ds 3
_pxOverflowDelayedTaskList:
	.ds 3
_xPendingReadyList:
	.ds 22
_sTaskCreate_ucTaskNumber_1_1:
	.ds 1
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
_pxCurrentTCB::
	.ds 3
_sUsingPreemption:
	.ds 2
_usCurrentNumberOfTasks:
	.ds 2
_xTickCount:
	.ds 2
_ucTopUsedPriority:
	.ds 1
_ucTopReadyPriority:
	.ds 1
_cSchedulerRunning:
	.ds 1
_ucSchedulerSuspended:
	.ds 1
_ucMissedTicks:
	.ds 1
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
;------------------------------------------------------------
;Allocation info for local variables in function 'sTaskCreate'
;------------------------------------------------------------
;pcName                    Allocated to stack - offset -5
;usStackDepth              Allocated to stack - offset -7
;pvParameters              Allocated to stack - offset -10
;ucPriority                Allocated to stack - offset -11
;pxCreatedTask             Allocated to stack - offset -14
;pvTaskCode                Allocated to stack - offset 1
;sReturn                   Allocated to registers r2 r3 
;pxNewTCB                  Allocated to stack - offset 3
;pxTopOfStack              Allocated to registers r7 r2 r3 
;sloc0                     Allocated to stack - offset 11
;sloc1                     Allocated to stack - offset 6
;ucTaskNumber              Allocated with name '_sTaskCreate_ucTaskNumber_1_1'
;------------------------------------------------------------
;../../Source/tasks.c:365: static unsigned portCHAR ucTaskNumber = 0; /*lint !e956 Static is deliberate - this is guarded before use. */
;     genAssign
	mov	dptr,#_sTaskCreate_ucTaskNumber_1_1
	mov	a,#0x00
	movx	@dptr,a
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
;Allocation info for local variables in function 'sTaskCreate'
;------------------------------------------------------------
;pcName                    Allocated to stack - offset -5
;usStackDepth              Allocated to stack - offset -7
;pvParameters              Allocated to stack - offset -10
;ucPriority                Allocated to stack - offset -11
;pxCreatedTask             Allocated to stack - offset -14
;pvTaskCode                Allocated to stack - offset 1
;sReturn                   Allocated to registers r2 r3 
;pxNewTCB                  Allocated to stack - offset 3
;pxTopOfStack              Allocated to registers r7 r2 r3 
;sloc0                     Allocated to stack - offset 11
;sloc1                     Allocated to stack - offset 6
;ucTaskNumber              Allocated with name '_sTaskCreate_ucTaskNumber_1_1'
;------------------------------------------------------------
;../../Source/tasks.c:361: portSHORT sTaskCreate( pdTASK_CODE pvTaskCode, const signed portCHAR * const pcName, unsigned portSHORT usStackDepth, void *pvParameters, unsigned portCHAR ucPriority, xTaskHandle *pxCreatedTask )
;	-----------------------------------------
;	 function sTaskCreate
;	-----------------------------------------
_sTaskCreate:
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
	mov	a,sp
	add	a,#0x08
	mov	sp,a
;../../Source/tasks.c:369: pxNewTCB = prvAllocateTCBAndStack( usStackDepth );
;     genCall
	mov	a,_bp
	add	a,#0xf9
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	lcall	_prvAllocateTCBAndStack
	mov	r4,dpl
	mov	r5,dph
	mov	r6,b
;     genAssign
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	@r0,ar4
	inc	r0
	mov	@r0,ar5
	inc	r0
	mov	@r0,ar6
;../../Source/tasks.c:370: if( pxNewTCB != NULL )
;     genCmpEq
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	cjne	@r0,#0x00,00135$
	inc	r0
	cjne	@r0,#0x00,00135$
	inc	r0
	cjne	@r0,#0x00,00135$
	ljmp	00113$
00135$:
;../../Source/tasks.c:375: prvInitialiseTCBVariables( pxNewTCB, usStackDepth, pcName, ucPriority );
;     genIpush
	mov	a,_bp
	add	a,#0xf5
	mov	r0,a
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
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	_prvInitialiseTCBVariables
	mov	a,sp
	add	a,#0xfa
	mov	sp,a
;../../Source/tasks.c:390: pxTopOfStack = pxNewTCB->pxStack;	
;     genPlus
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
;     genPlusIncr
	mov	a,#0x03
	add	a,@r0
	mov	r7,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r2,a
	inc	r0
	mov	ar3,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r7
	mov	dph,r2
	mov	b,r3
	lcall	__gptrget
	mov	r7,a
	inc	dptr
	lcall	__gptrget
	mov	r2,a
	inc	dptr
	lcall	__gptrget
	mov	r3,a
;     genAssign
;../../Source/tasks.c:398: pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack, pvTaskCode, pvParameters );
;     genIpush
	mov	a,_bp
	add	a,#0xf6
	mov	r0,a
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
;     genIpush
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
;     genCall
	mov	dpl,r7
	mov	dph,r2
	mov	b,r3
	lcall	_pxPortInitialiseStack
	mov	r2,dpl
	mov	r3,dph
	mov	r7,b
	mov	a,sp
	add	a,#0xfb
	mov	sp,a
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x03
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
	mov	a,r7
	lcall	__gptrput
;../../Source/tasks.c:402: portENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/tasks.c:404: usCurrentNumberOfTasks++;
;     genAssign
	mov	dptr,#_usCurrentNumberOfTasks
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
;     genPlus
	mov	dptr,#_usCurrentNumberOfTasks
;     genPlusIncr
	mov	a,#0x01
	add	a,ar2
	movx	@dptr,a
	mov	a,#0x00
	addc	a,ar3
	inc	dptr
	movx	@dptr,a
;../../Source/tasks.c:405: if( usCurrentNumberOfTasks == ( unsigned portSHORT ) 1 )
;     genAssign
	mov	dptr,#_usCurrentNumberOfTasks
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
;     genCmpEq
	cjne	r2,#0x01,00136$
	cjne	r3,#0x00,00136$
	sjmp	00137$
00136$:
	ljmp	00106$
00137$:
;../../Source/tasks.c:408: pxCurrentTCB = ( volatile tskTCB * volatile ) pxNewTCB;
;     genAssign
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	dptr,#_pxCurrentTCB
	mov	a,@r0
	movx	@dptr,a
	inc	r0
	inc	dptr
	mov	a,@r0
	movx	@dptr,a
	inc	r0
	inc	dptr
	mov	a,@r0
	movx	@dptr,a
;../../Source/tasks.c:413: sReturn = prvInitialiseTaskLists();
;     genCall
	lcall	_prvInitialiseTaskLists
	mov	r2,dpl
	mov	r3,dph
;     genAssign
	ljmp	00107$
00106$:
;../../Source/tasks.c:417: sReturn = pdPASS;
;     genAssign
	mov	r2,#0x01
	mov	r3,#0x00
;../../Source/tasks.c:422: if( cSchedulerRunning == pdFALSE )
;     genAssign
	mov	dptr,#_cSchedulerRunning
	movx	a,@dptr
	mov	r7,a
;     genCmpEq
	cjne	r7,#0x00,00138$
	sjmp	00139$
00138$:
	ljmp	00107$
00139$:
;../../Source/tasks.c:424: if( pxCurrentTCB->ucPriority <= ucPriority )
;     genIpush
	push	ar2
	push	ar3
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r7,a
	inc	dptr
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
;     genPlus
	mov	a,#0x18
	add	a,ar7
	mov	r7,a
	mov	a,#0x00
	addc	a,ar2
	mov	r2,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r7
	mov	dph,r2
	mov	b,r3
	lcall	__gptrget
	mov	r7,a
;     genCmpGt
	mov	a,_bp
	add	a,#0xf5
	mov	r0,a
;     genCmp
	clr	c
	mov	a,@r0
	subb	a,r7
	clr	a
	rlc	a
;     genIpop
	pop	ar3
	pop	ar2
;     genIfx
;     genIfxJump
	jz	00140$
	ljmp	00107$
00140$:
;../../Source/tasks.c:426: pxCurrentTCB = ( volatile tskTCB * volatile ) pxNewTCB;	
;     genAssign
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	dptr,#_pxCurrentTCB
	mov	a,@r0
	movx	@dptr,a
	inc	r0
	inc	dptr
	mov	a,@r0
	movx	@dptr,a
	inc	r0
	inc	dptr
	mov	a,@r0
	movx	@dptr,a
00107$:
;../../Source/tasks.c:433: if( pxNewTCB->ucPriority > ucTopUsedPriority )
;     genIpush
	push	ar2
	push	ar3
;     genPlus
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	a,#0x18
	add	a,@r0
	mov	r7,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r2,a
	inc	r0
	mov	ar3,@r0
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r7
	mov	dph,r2
	mov	b,r3
	lcall	__gptrget
	mov	r5,a
;     genAssign
	mov	dptr,#_ucTopUsedPriority
	movx	a,@dptr
	mov	r2,a
;     genCmpGt
;     genCmp
	clr	c
	mov	a,r2
	subb	a,r5
	clr	a
	rlc	a
;     genIpop
	pop	ar3
	pop	ar2
;     genIfx
;     genIfxJump
	jnz	00141$
	ljmp	00109$
00141$:
;../../Source/tasks.c:435: ucTopUsedPriority = pxNewTCB->ucPriority;
;     genAssign
	mov	dptr,#_ucTopUsedPriority
	mov	a,r5
	movx	@dptr,a
00109$:
;../../Source/tasks.c:439: pxNewTCB->ucTCBNumber = ucTaskNumber;
;     genIpush
	push	ar2
	push	ar3
;     genPlus
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	a,#0x35
	add	a,@r0
	mov	r7,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r2,a
	inc	r0
	mov	ar3,@r0
;     genAssign
	mov	dptr,#_sTaskCreate_ucTaskNumber_1_1
	movx	a,@dptr
	mov	r4,a
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r7
	mov	dph,r2
	mov	b,r3
	mov	a,r4
	lcall	__gptrput
;../../Source/tasks.c:440: ucTaskNumber++;
;     genPlus
	mov	dptr,#_sTaskCreate_ucTaskNumber_1_1
;     genPlusIncr
	mov	a,#0x01
	add	a,ar4
	movx	@dptr,a
;../../Source/tasks.c:442: prvAddTaskToReadyQueue( pxNewTCB );
;     genPlus
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	a,_bp
	add	a,#0x06
	mov	r1,a
	mov	a,#0x19
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
;     genPointerSet
;     genGenPointerSet
	mov	a,_bp
	add	a,#0x06
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,#0x00
	lcall	__gptrput
	inc	dptr
	mov	a,#0x00
	lcall	__gptrput
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	a,@dptr
	mov	r2,a
;     genCmpGt
;     genCmp
	clr	c
	mov	a,r2
	subb	a,r5
	clr	a
	rlc	a
;     genIpop
	pop	ar3
	pop	ar2
;     genIfx
;     genIfxJump
	jnz	00142$
	ljmp	00111$
00142$:
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	mov	a,r5
	movx	@dptr,a
00111$:
;     genMult
;     genMultOneByte
	mov	a,r5
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	r4,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	r5,a
;     genCast
	mov	r6,#0x1
;     genIpush
	push	ar2
	push	ar3
	mov	a,_bp
	add	a,#0x06
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
	mov	dph,r5
	mov	b,r6
	lcall	_vListInsertEnd
	dec	sp
	dec	sp
	dec	sp
	pop	ar3
	pop	ar2
;../../Source/tasks.c:444: portEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
	ljmp	00114$
00113$:
;../../Source/tasks.c:448: sReturn = errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY;
;     genAssign
	mov	r2,#0xFF
	mov	r3,#0xFF
00114$:
;../../Source/tasks.c:451: if( sReturn == pdPASS )
;     genCmpEq
	cjne	r2,#0x01,00143$
	cjne	r3,#0x00,00143$
	sjmp	00144$
00143$:
	ljmp	00122$
00144$:
;../../Source/tasks.c:453: if( ( void * ) pxCreatedTask != NULL )
;     genAssign
	mov	a,_bp
	add	a,#0xf2
	mov	r0,a
	mov	ar4,@r0
	inc	r0
	mov	ar5,@r0
	inc	r0
	mov	ar6,@r0
;     genCmpEq
	cjne	r4,#0x00,00145$
	cjne	r5,#0x00,00145$
	cjne	r6,#0x00,00145$
	ljmp	00116$
00145$:
;../../Source/tasks.c:458: *pxCreatedTask = ( xTaskHandle ) pxNewTCB;
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r4
	mov	dph,r5
	mov	b,r6
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	a,@r0
	lcall	__gptrput
	inc	dptr
	inc	r0
	mov	a,@r0
	lcall	__gptrput
	inc	dptr
	inc	r0
	mov	a,@r0
	lcall	__gptrput
00116$:
;../../Source/tasks.c:461: if( cSchedulerRunning != pdFALSE )
;     genAssign
	mov	dptr,#_cSchedulerRunning
	movx	a,@dptr
	mov	r4,a
;     genCmpEq
	cjne	r4,#0x00,00146$
	ljmp	00122$
00146$:
;../../Source/tasks.c:465: if( pxCurrentTCB->ucPriority < ucPriority )
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
;     genPlus
	mov	a,#0x18
	add	a,ar4
	mov	r4,a
	mov	a,#0x00
	addc	a,ar5
	mov	r5,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r4
	mov	dph,r5
	mov	b,r6
	lcall	__gptrget
	mov	r4,a
;     genCmpLt
	mov	a,_bp
	add	a,#0xf5
	mov	r0,a
;     genCmp
	clr	c
	mov	a,r4
	subb	a,@r0
;     genIfxJump
	jc	00147$
	ljmp	00122$
00147$:
;../../Source/tasks.c:467: taskYIELD();
;     genCall
	lcall	_vPortYield
00122$:
;../../Source/tasks.c:472: return sReturn;
;     genRet
	mov	dpl,r2
	mov	dph,r3
00123$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vTaskDelayUntil'
;------------------------------------------------------------
;xTimeIncrement            Allocated to stack - offset -4
;pxPreviousWakeTime        Allocated to stack - offset 1
;xTimeToWake               Allocated to registers r3 r2 
;cAlreadyYielded           Allocated to registers r2 
;cShouldDelay              Allocated to stack - offset 4
;------------------------------------------------------------
;../../Source/tasks.c:522: void vTaskDelayUntil( portTickType *pxPreviousWakeTime, portTickType xTimeIncrement )
;	-----------------------------------------
;	 function vTaskDelayUntil
;	-----------------------------------------
_vTaskDelayUntil:
	push	_bp
	mov	_bp,sp
;     genReceive
	push	dpl
	push	dph
	push	b
	inc	sp
;../../Source/tasks.c:525: portCHAR cAlreadyYielded, cShouldDelay = ( portCHAR ) pdFALSE;
;     genAssign
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	mov	@r0,#0x00
;../../Source/tasks.c:527: vTaskSuspendAll();
;     genCall
	lcall	_vTaskSuspendAll
;../../Source/tasks.c:530: xTimeToWake = *pxPreviousWakeTime + xTimeIncrement;
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
;     genPlus
	mov	a,_bp
	add	a,#0xfc
	mov	r0,a
	mov	a,@r0
	add	a,ar6
	mov	r5,a
	inc	r0
	mov	a,@r0
	addc	a,ar7
	mov	r2,a
;     genAssign
	mov	ar3,r5
;../../Source/tasks.c:532: if( xTickCount < *pxPreviousWakeTime )
;     genAssign
	mov	dptr,#_xTickCount
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
;     genCmpLt
;     genCmp
	clr	c
	mov	a,r4
	subb	a,r6
	mov	a,r5
	subb	a,r7
;     genIfxJump
	jc	00126$
	ljmp	00108$
00126$:
;../../Source/tasks.c:539: if( ( xTimeToWake < *pxPreviousWakeTime ) && ( xTimeToWake > xTickCount ) )
;     genCmpLt
;     genCmp
	clr	c
	mov	a,r3
	subb	a,r6
	mov	a,r2
	subb	a,r7
;     genIfxJump
	jc	00127$
	ljmp	00109$
00127$:
;     genAssign
	mov	dptr,#_xTickCount
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
;     genCmpGt
;     genCmp
	clr	c
	mov	a,r4
	subb	a,r3
	mov	a,r5
	subb	a,r2
;     genIfxJump
	jc	00128$
	ljmp	00109$
00128$:
;../../Source/tasks.c:541: cShouldDelay = ( portCHAR ) pdTRUE;
;     genAssign
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	mov	@r0,#0x01
	ljmp	00109$
00108$:
;../../Source/tasks.c:549: if( ( xTimeToWake < *pxPreviousWakeTime ) || ( xTimeToWake > xTickCount ) )
;     genCmpLt
;     genCmp
	clr	c
	mov	a,r3
	subb	a,r6
	mov	a,r2
	subb	a,r7
;     genIfxJump
	jnc	00129$
	ljmp	00104$
00129$:
;     genAssign
	mov	dptr,#_xTickCount
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
;     genCmpGt
;     genCmp
	clr	c
	mov	a,r4
	subb	a,r3
	mov	a,r5
	subb	a,r2
;     genIfxJump
	jc	00130$
	ljmp	00109$
00130$:
00104$:
;../../Source/tasks.c:551: cShouldDelay = ( portCHAR ) pdTRUE;
;     genAssign
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	mov	@r0,#0x01
00109$:
;../../Source/tasks.c:556: *pxPreviousWakeTime = xTimeToWake;
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
	mov	a,r2
	lcall	__gptrput
;../../Source/tasks.c:558: if( cShouldDelay )
;     genIfx
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
	mov	a,@r0
;     genIfxJump
	jnz	00131$
	ljmp	00114$
00131$:
;../../Source/tasks.c:563: vListRemove( ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
;     genPlus
	mov	a,#0x19
	add	a,ar4
	mov	r4,a
	mov	a,#0x00
	addc	a,ar5
	mov	r5,a
;     genCall
	mov	dpl,r4
	mov	dph,r5
	mov	b,r6
	push	ar2
	push	ar3
	lcall	_vListRemove
	pop	ar3
	pop	ar2
;../../Source/tasks.c:566: listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xGenericListItem ), xTimeToWake );
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
;     genPlus
	mov	a,#0x19
	add	a,ar4
	mov	r4,a
	mov	a,#0x00
	addc	a,ar5
	mov	r5,a
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r4
	mov	dph,r5
	mov	b,r6
	mov	a,r3
	lcall	__gptrput
	inc	dptr
	mov	a,r2
	lcall	__gptrput
;../../Source/tasks.c:568: if( xTimeToWake < xTickCount )
;     genAssign
	mov	dptr,#_xTickCount
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
;     genCmpLt
;     genCmp
	clr	c
	mov	a,r3
	subb	a,r4
	mov	a,r2
	subb	a,r5
;     genIfxJump
	jc	00132$
	ljmp	00111$
00132$:
;../../Source/tasks.c:572: vListInsert( ( xList * ) pxOverflowDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
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
;     genPlus
	mov	a,#0x19
	add	a,ar2
	mov	r2,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genAssign
	mov	dptr,#_pxOverflowDelayedTaskList
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
;     genIpush
	push	ar2
	push	ar3
	push	ar4
;     genCall
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	_vListInsert
	dec	sp
	dec	sp
	dec	sp
	ljmp	00114$
00111$:
;../../Source/tasks.c:578: vListInsert( ( xList * ) pxDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
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
;     genPlus
	mov	a,#0x19
	add	a,ar2
	mov	r2,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genAssign
	mov	dptr,#_pxDelayedTaskList
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
;     genIpush
	push	ar2
	push	ar3
	push	ar4
;     genCall
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	_vListInsert
	dec	sp
	dec	sp
	dec	sp
00114$:
;../../Source/tasks.c:582: cAlreadyYielded = cTaskResumeAll();
;     genCall
	lcall	_cTaskResumeAll
	mov	r2,dpl
;     genAssign
;../../Source/tasks.c:586: if( !cAlreadyYielded )
;     genIfx
	mov	a,r2
;     genIfxJump
	jz	00133$
	ljmp	00117$
00133$:
;../../Source/tasks.c:588: taskYIELD(); 
;     genCall
	lcall	_vPortYield
00117$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vTaskDelay'
;------------------------------------------------------------
;xTicksToDelay             Allocated to registers r2 r3 
;xTimeToWake               Allocated to registers r2 r3 
;cAlreadyYielded           Allocated to registers r4 
;sloc0                     Allocated to stack - offset 6
;------------------------------------------------------------
;../../Source/tasks.c:595: void vTaskDelay( portTickType xTicksToDelay )
;	-----------------------------------------
;	 function vTaskDelay
;	-----------------------------------------
_vTaskDelay:
	push	_bp
	mov	_bp,sp
;     genReceive
	mov	r2,dpl
	mov	r3,dph
;../../Source/tasks.c:598: signed portCHAR cAlreadyYielded = pdFALSE;
;     genAssign
	mov	r4,#0x00
;../../Source/tasks.c:601: if( xTicksToDelay > ( portTickType ) 0 )
;     genIfx
	mov	a,r2
	orl	a,r3
;     genIfxJump
	jnz	00113$
	ljmp	00105$
00113$:
;../../Source/tasks.c:603: vTaskSuspendAll();
;     genCall
	push	ar2
	push	ar3
	lcall	_vTaskSuspendAll
	pop	ar3
	pop	ar2
;../../Source/tasks.c:615: xTimeToWake = xTickCount + xTicksToDelay;
;     genAssign
	mov	dptr,#_xTickCount
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
;     genPlus
	mov	a,ar2
	add	a,ar5
	mov	r2,a
	mov	a,ar3
	addc	a,ar6
	mov	r3,a
;     genAssign
;../../Source/tasks.c:620: vListRemove( ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
;     genPlus
	mov	a,#0x19
	add	a,ar5
	mov	r5,a
	mov	a,#0x00
	addc	a,ar6
	mov	r6,a
;     genCall
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	push	ar2
	push	ar3
	lcall	_vListRemove
	pop	ar3
	pop	ar2
;../../Source/tasks.c:623: listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xGenericListItem ), xTimeToWake );
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
;     genPlus
	mov	a,#0x19
	add	a,ar5
	mov	r5,a
	mov	a,#0x00
	addc	a,ar6
	mov	r6,a
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,r2
	lcall	__gptrput
	inc	dptr
	mov	a,r3
	lcall	__gptrput
;../../Source/tasks.c:625: if( xTimeToWake < xTickCount )
;     genAssign
	mov	dptr,#_xTickCount
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
;     genCmpLt
;     genCmp
	clr	c
	mov	a,r2
	subb	a,r5
	mov	a,r3
	subb	a,r6
;     genIfxJump
	jc	00114$
	ljmp	00102$
00114$:
;../../Source/tasks.c:629: vListInsert( ( xList * ) pxOverflowDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
;     genPlus
	mov	a,#0x19
	add	a,ar2
	mov	r4,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genAssign
	mov	dptr,#_pxOverflowDelayedTaskList
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
	inc	dptr
	movx	a,@dptr
	mov	r2,a
;     genIpush
	push	ar4
	push	ar3
	push	ar5
;     genCall
	mov	dpl,r6
	mov	dph,r7
	mov	b,r2
	lcall	_vListInsert
	dec	sp
	dec	sp
	dec	sp
	ljmp	00103$
00102$:
;../../Source/tasks.c:635: vListInsert( ( xList * ) pxDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
;     genPlus
	mov	a,#0x19
	add	a,ar2
	mov	r4,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genAssign
	mov	dptr,#_pxDelayedTaskList
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
	inc	dptr
	movx	a,@dptr
	mov	r2,a
;     genIpush
	push	ar4
	push	ar3
	push	ar5
;     genCall
	mov	dpl,r6
	mov	dph,r7
	mov	b,r2
	lcall	_vListInsert
	dec	sp
	dec	sp
	dec	sp
00103$:
;../../Source/tasks.c:638: cAlreadyYielded = cTaskResumeAll();
;     genCall
	lcall	_cTaskResumeAll
	mov	r2,dpl
;     genAssign
	mov	ar4,r2
00105$:
;../../Source/tasks.c:643: if( !cAlreadyYielded )
;     genIfx
	mov	a,r4
;     genIfxJump
	jz	00115$
	ljmp	00108$
00115$:
;../../Source/tasks.c:645: taskYIELD(); 
;     genCall
	lcall	_vPortYield
00108$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vTaskStartScheduler'
;------------------------------------------------------------
;sUsePreemption            Allocated to registers r2 r3 
;------------------------------------------------------------
;../../Source/tasks.c:798: void vTaskStartScheduler( portSHORT sUsePreemption )
;	-----------------------------------------
;	 function vTaskStartScheduler
;	-----------------------------------------
_vTaskStartScheduler:
	push	_bp
	mov	_bp,sp
;     genReceive
	mov	r2,dpl
	mov	r3,dph
;../../Source/tasks.c:801: if( pxCurrentTCB != NULL )
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
;     genCmpEq
	cjne	r4,#0x00,00108$
	cjne	r5,#0x00,00108$
	cjne	r6,#0x00,00108$
	ljmp	00105$
00108$:
;../../Source/tasks.c:803: sUsingPreemption = sUsePreemption;
;     genAssign
	mov	dptr,#_sUsingPreemption
	mov	a,r2
	movx	@dptr,a
	inc	dptr
	mov	a,r3
	movx	@dptr,a
;../../Source/tasks.c:813: portDISABLE_INTERRUPTS();
;     genAssign
	clr	_EA
;../../Source/tasks.c:815: cSchedulerRunning = pdTRUE;
;     genAssign
	mov	dptr,#_cSchedulerRunning
	mov	a,#0x01
	movx	@dptr,a
;../../Source/tasks.c:816: xTickCount = ( portTickType ) 0;
;     genAssign
	mov	dptr,#_xTickCount
	clr	a
	movx	@dptr,a
	inc	dptr
	movx	@dptr,a
;../../Source/tasks.c:820: if( sPortStartScheduler( sUsePreemption ) )
;     genCall
	mov	dpl,r2
	mov	dph,r3
	lcall	_sPortStartScheduler
00105$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vTaskEndScheduler'
;------------------------------------------------------------
;------------------------------------------------------------
;../../Source/tasks.c:833: void vTaskEndScheduler( void )
;	-----------------------------------------
;	 function vTaskEndScheduler
;	-----------------------------------------
_vTaskEndScheduler:
	push	_bp
	mov	_bp,sp
;../../Source/tasks.c:838: portDISABLE_INTERRUPTS();
;     genAssign
	clr	_EA
;../../Source/tasks.c:839: cSchedulerRunning = pdFALSE;
;     genAssign
	mov	dptr,#_cSchedulerRunning
	mov	a,#0x00
	movx	@dptr,a
;../../Source/tasks.c:840: vPortEndScheduler();
;     genCall
	lcall	_vPortEndScheduler
00101$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vTaskSuspendAll'
;------------------------------------------------------------
;------------------------------------------------------------
;../../Source/tasks.c:844: void vTaskSuspendAll( void )
;	-----------------------------------------
;	 function vTaskSuspendAll
;	-----------------------------------------
_vTaskSuspendAll:
	push	_bp
	mov	_bp,sp
;../../Source/tasks.c:846: portENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/tasks.c:847: ++ucSchedulerSuspended;
;     genPlus
	mov	dptr,#_ucSchedulerSuspended
	movx	a,@dptr
	add	a,#0x01
	movx	@dptr,a
;../../Source/tasks.c:848: portEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
00101$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'cTaskResumeAll'
;------------------------------------------------------------
;pxTCB                     Allocated to registers r6 r7 r2 
;cAlreadyYielded           Allocated to stack - offset 1
;sloc0                     Allocated to stack - offset 5
;sloc1                     Allocated to stack - offset 2
;------------------------------------------------------------
;../../Source/tasks.c:852: signed portCHAR cTaskResumeAll( void )
;	-----------------------------------------
;	 function cTaskResumeAll
;	-----------------------------------------
_cTaskResumeAll:
	push	_bp
	mov	_bp,sp
	mov	a,sp
	add	a,#0x04
	mov	sp,a
;../../Source/tasks.c:855: signed portCHAR cAlreadyYielded = ( signed portCHAR ) pdFALSE;
;     genAssign
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	@r0,#0x00
;../../Source/tasks.c:862: portENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/tasks.c:864: --ucSchedulerSuspended;
;     genMinus
	mov	dptr,#_ucSchedulerSuspended
;     genMinusDec
	movx	a,@dptr
	dec	a
;     genAssign
	mov	dptr,#_ucSchedulerSuspended
	movx	@dptr,a
;../../Source/tasks.c:866: if( ucSchedulerSuspended == pdFALSE )
;     genAssign
	mov	dptr,#_ucSchedulerSuspended
	movx	a,@dptr
	mov	r3,a
;     genCmpEq
	cjne	r3,#0x00,00126$
	sjmp	00127$
00126$:
	ljmp	00114$
00127$:
;../../Source/tasks.c:868: if( usCurrentNumberOfTasks > ( unsigned portSHORT ) 0 )
;     genAssign
	mov	dptr,#_usCurrentNumberOfTasks
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;     genIfx
	mov	a,r3
	orl	a,r4
;     genIfxJump
	jnz	00128$
	ljmp	00114$
00128$:
;../../Source/tasks.c:872: while( ( pxTCB = ( tskTCB * ) listGET_OWNER_OF_HEAD_ENTRY(  ( ( xList * ) &xPendingReadyList ) ) ) != NULL )
00103$:
;     genPointerGet
;     genFarPointerGet
	mov	dptr,#_xPendingReadyList
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;     genCmpEq
	cjne	r3,#0x00,00129$
	cjne	r4,#0x00,00129$
	mov	a,#0x01
	sjmp	00130$
00129$:
	clr	a
00130$:
	mov	r3,a
;     genNot
	mov	a,r3
	cjne	a,#0x01,00131$
00131$:
	clr	a
	rlc	a
	mov	r3,a
;     genIfx
	mov	a,r3
;     genIfxJump
	jnz	00132$
	ljmp	00117$
00132$:
;     genPointerGet
;     genGenPointerGet
	mov	dptr,#(_xPendingReadyList + 0x0002)
	mov	b,#0x01
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
	inc	dptr
	lcall	__gptrget
	mov	r5,a
;     genPlus
;     genPlusIncr
	mov	a,#0x02
	add	a,ar3
	mov	r3,a
	mov	a,#0x00
	addc	a,ar4
	mov	r4,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
	inc	dptr
	lcall	__gptrget
	mov	r5,a
;     genPlus
	mov	a,#0x08
	add	a,ar3
	mov	r3,a
	mov	a,#0x00
	addc	a,ar4
	mov	r4,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
	inc	dptr
	lcall	__gptrget
	mov	r5,a
	ljmp	00118$
00117$:
;     genAssign
	mov	r3,#0x00
	mov	r4,#0x00
	mov	r5,#0x00
00118$:
;     genAssign
;     genAssign
	mov	ar6,r3
	mov	ar7,r4
	mov	ar2,r5
;     genCmpEq
	cjne	r3,#0x00,00133$
	cjne	r4,#0x00,00133$
	cjne	r5,#0x00,00133$
	ljmp	00105$
00133$:
;../../Source/tasks.c:874: vListRemove( &( pxTCB->xEventListItem ) );
;     genPlus
	mov	a,#0x27
	add	a,ar6
	mov	r3,a
	mov	a,#0x00
	addc	a,ar7
	mov	r4,a
	mov	ar5,r2
;     genCall
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	push	ar2
	push	ar6
	push	ar7
	lcall	_vListRemove
	pop	ar7
	pop	ar6
	pop	ar2
;../../Source/tasks.c:875: vListRemove( &( pxTCB->xGenericListItem ) );
;     genPlus
	mov	a,#0x19
	add	a,ar6
	mov	r3,a
	mov	a,#0x00
	addc	a,ar7
	mov	r4,a
	mov	ar5,r2
;     genCall
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	push	ar2
	push	ar6
	push	ar7
	lcall	_vListRemove
	pop	ar7
	pop	ar6
	pop	ar2
;../../Source/tasks.c:876: prvAddTaskToReadyQueue( pxTCB );
;     genPlus
	mov	a,#0x19
	add	a,ar6
	mov	r3,a
	mov	a,#0x00
	addc	a,ar7
	mov	r4,a
	mov	ar5,r2
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	mov	a,#0x00
	lcall	__gptrput
	inc	dptr
	mov	a,#0x00
	lcall	__gptrput
;     genPlus
	mov	a,_bp
	add	a,#0x02
	mov	r0,a
	mov	a,#0x18
	add	a,ar6
	mov	@r0,a
	mov	a,#0x00
	addc	a,ar7
	inc	r0
	mov	@r0,a
	inc	r0
	mov	@r0,ar2
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
	mov	r6,a
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	a,@dptr
	mov	r2,a
;     genCmpGt
;     genCmp
	clr	c
	mov	a,r2
	subb	a,r6
;     genIfxJump
	jc	00134$
	ljmp	00102$
00134$:
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	mov	a,r6
	movx	@dptr,a
00102$:
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
	mov	r2,a
;     genMult
;     genMultOneByte
	mov	a,r2
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	r2,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	r6,a
;     genCast
	mov	r7,#0x1
;     genIpush
	push	ar3
	push	ar4
	push	ar5
;     genCall
	mov	dpl,r2
	mov	dph,r6
	mov	b,r7
	lcall	_vListInsertEnd
	dec	sp
	dec	sp
	dec	sp
	ljmp	00103$
00105$:
;../../Source/tasks.c:882: if( ucMissedTicks > 0 )
;     genAssign
	mov	dptr,#_ucMissedTicks
	movx	a,@dptr
	mov	r2,a
;     genCmpGt
;     genCmp
	clr	c
	mov	a,#0x00
	subb	a,r2
;     genIfxJump
	jc	00135$
	ljmp	00114$
00135$:
;../../Source/tasks.c:884: while( ucMissedTicks > 0 )
00106$:
;     genAssign
	mov	dptr,#_ucMissedTicks
	movx	a,@dptr
	mov	r2,a
;     genCmpGt
;     genCmp
	clr	c
	mov	a,#0x00
	subb	a,r2
;     genIfxJump
	jc	00136$
	ljmp	00108$
00136$:
;../../Source/tasks.c:886: vTaskIncrementTick();
;     genCall
	lcall	_vTaskIncrementTick
;../../Source/tasks.c:887: --ucMissedTicks;
;     genMinus
	mov	dptr,#_ucMissedTicks
;     genMinusDec
	movx	a,@dptr
	dec	a
;     genAssign
	mov	dptr,#_ucMissedTicks
	movx	@dptr,a
	ljmp	00106$
00108$:
;../../Source/tasks.c:893: cAlreadyYielded = ( signed portCHAR ) pdTRUE;
;     genAssign
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	@r0,#0x01
;../../Source/tasks.c:894: taskYIELD();
;     genCall
	lcall	_vPortYield
00114$:
;../../Source/tasks.c:899: portEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/tasks.c:901: return cAlreadyYielded;
;     genRet
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
00115$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'xTaskGetTickCount'
;------------------------------------------------------------
;xTicks                    Allocated to registers r2 r3 
;------------------------------------------------------------
;../../Source/tasks.c:915: volatile portTickType xTaskGetTickCount( void )
;	-----------------------------------------
;	 function xTaskGetTickCount
;	-----------------------------------------
_xTaskGetTickCount:
	push	_bp
	mov	_bp,sp
;../../Source/tasks.c:920: taskENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/tasks.c:922: xTicks = xTickCount;
;     genAssign
	mov	dptr,#_xTickCount
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
;     genAssign
;../../Source/tasks.c:924: taskEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/tasks.c:926: return xTicks;
;     genRet
	mov	dpl,r2
	mov	dph,r3
00101$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'usTaskGetNumberOfTasks'
;------------------------------------------------------------
;usNumberOfTasks           Allocated to registers r2 r3 
;------------------------------------------------------------
;../../Source/tasks.c:930: unsigned portSHORT usTaskGetNumberOfTasks( void )
;	-----------------------------------------
;	 function usTaskGetNumberOfTasks
;	-----------------------------------------
_usTaskGetNumberOfTasks:
	push	_bp
	mov	_bp,sp
;../../Source/tasks.c:934: taskENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/tasks.c:935: usNumberOfTasks = usCurrentNumberOfTasks;
;     genAssign
	mov	dptr,#_usCurrentNumberOfTasks
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
;     genAssign
;../../Source/tasks.c:936: taskEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/tasks.c:938: return usNumberOfTasks;
;     genRet
	mov	dpl,r2
	mov	dph,r3
00101$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vTaskIncrementTick'
;------------------------------------------------------------
;pxTemp                    Allocated to stack - offset 1
;pxTCB                     Allocated to registers r5 r6 r7 
;sloc0                     Allocated to stack - offset 4
;sloc1                     Allocated to stack - offset 6
;------------------------------------------------------------
;../../Source/tasks.c:1043: inline void vTaskIncrementTick( void )
;	-----------------------------------------
;	 function vTaskIncrementTick
;	-----------------------------------------
_vTaskIncrementTick:
	push	_bp
	mov	_bp,sp
	mov	a,sp
	add	a,#0x08
	mov	sp,a
;../../Source/tasks.c:1048: if( ucSchedulerSuspended == ( unsigned portCHAR ) pdFALSE )
;     genAssign
	mov	dptr,#_ucSchedulerSuspended
	movx	a,@dptr
	mov	r2,a
;     genCmpEq
	cjne	r2,#0x00,00127$
	sjmp	00128$
00127$:
	ljmp	00113$
00128$:
;../../Source/tasks.c:1050: ++xTickCount;
;     genPlus
	mov	dptr,#_xTickCount
	movx	a,@dptr
	add	a,#0x01
	movx	@dptr,a
	inc	dptr
	movx	a,@dptr
	addc	a,#0x00
	movx	@dptr,a
;../../Source/tasks.c:1051: if( xTickCount == ( portTickType ) 0 )
;     genAssign
	mov	dptr,#_xTickCount
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
;     genCmpEq
	cjne	r2,#0x00,00129$
	cjne	r3,#0x00,00129$
	sjmp	00130$
00129$:
	ljmp	00109$
00130$:
;../../Source/tasks.c:1057: pxTemp = pxDelayedTaskList;
;     genAssign
	mov	dptr,#_pxDelayedTaskList
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;     genAssign
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	@r0,ar2
	inc	r0
	mov	@r0,ar3
	inc	r0
	mov	@r0,ar4
;../../Source/tasks.c:1058: pxDelayedTaskList = pxOverflowDelayedTaskList;
;     genAssign
	mov	dptr,#_pxOverflowDelayedTaskList
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;     genAssign
	mov	dptr,#_pxDelayedTaskList
	mov	a,r2
	movx	@dptr,a
	inc	dptr
	mov	a,r3
	movx	@dptr,a
	inc	dptr
	mov	a,r4
	movx	@dptr,a
;../../Source/tasks.c:1059: pxOverflowDelayedTaskList = pxTemp;
;     genAssign
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dptr,#_pxOverflowDelayedTaskList
	mov	a,@r0
	movx	@dptr,a
	inc	r0
	inc	dptr
	mov	a,@r0
	movx	@dptr,a
	inc	r0
	inc	dptr
	mov	a,@r0
	movx	@dptr,a
;../../Source/tasks.c:1063: prvCheckDelayedTasks();
00109$:
;     genAssign
	mov	dptr,#_pxDelayedTaskList
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
	mov	r2,a
	inc	dptr
	lcall	__gptrget
	mov	r3,a
;     genCmpEq
	cjne	r2,#0x00,00131$
	cjne	r3,#0x00,00131$
	mov	a,#0x01
	sjmp	00132$
00131$:
	clr	a
00132$:
	mov	r2,a
;     genNot
	mov	a,r2
	cjne	a,#0x01,00133$
00133$:
	clr	a
	rlc	a
	mov	r2,a
;     genIfx
	mov	a,r2
;     genIfxJump
	jnz	00134$
	ljmp	00117$
00134$:
;     genAssign
	mov	dptr,#_pxDelayedTaskList
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;     genPlus
;     genPlusIncr
	mov	a,#0x02
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
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
;     genPlus
;     genPlusIncr
	mov	a,#0x02
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
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
;     genPlus
	mov	a,#0x08
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
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
	ljmp	00118$
00117$:
;     genAssign
	mov	r2,#0x00
	mov	r3,#0x00
	mov	r4,#0x00
00118$:
;     genAssign
;     genAssign
	mov	ar5,r2
	mov	ar6,r3
	mov	ar7,r4
;     genCmpEq
	cjne	r2,#0x00,00135$
	cjne	r3,#0x00,00135$
	cjne	r4,#0x00,00135$
	ljmp	00115$
00135$:
;     genPlus
	mov	a,#0x19
	add	a,ar5
	mov	r2,a
	mov	a,#0x00
	addc	a,ar6
	mov	r3,a
	mov	ar4,r7
;     genIpush
	push	ar5
	push	ar6
	push	ar7
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
	inc	dptr
	lcall	__gptrget
	inc	r0
	mov	@r0,a
;     genAssign
	mov	dptr,#_xTickCount
	movx	a,@dptr
	mov	r7,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
;     genCmpLt
	mov	a,_bp
	add	a,#0x04
	mov	r0,a
;     genCmp
	clr	c
	mov	a,r7
	subb	a,@r0
	mov	a,r5
	inc	r0
	subb	a,@r0
	clr	a
	rlc	a
;     genIpop
	pop	ar7
	pop	ar6
	pop	ar5
;     genIfx
;     genIfxJump
	jz	00136$
	ljmp	00115$
00136$:
;     genCall
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	push	ar6
	push	ar7
	lcall	_vListRemove
	pop	ar7
	pop	ar6
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
;     genPlus
	mov	a,_bp
	add	a,#0x06
	mov	r0,a
	mov	a,#0x27
	add	a,ar5
	mov	@r0,a
	mov	a,#0x00
	addc	a,ar6
	inc	r0
	mov	@r0,a
	inc	r0
	mov	@r0,ar7
;     genIpush
	push	ar5
	push	ar6
	push	ar7
;     genPlus
	mov	a,_bp
	add	a,#0x06
	mov	r0,a
	mov	a,#0x0B
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
;     genIfx
	mov	a,r5
	orl	a,r6
	orl	a,r7
;     genIpop
	pop	ar7
	pop	ar6
	pop	ar5
;     genIfxJump
	jnz	00137$
	ljmp	00106$
00137$:
;     genCall
	mov	a,_bp
	add	a,#0x06
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	push	ar6
	push	ar7
	lcall	_vListRemove
	pop	ar7
	pop	ar6
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
00106$:
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,#0x00
	lcall	__gptrput
	inc	dptr
	mov	a,#0x00
	lcall	__gptrput
;     genPlus
	mov	a,#0x18
	add	a,ar5
	mov	r5,a
	mov	a,#0x00
	addc	a,ar6
	mov	r6,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,_bp
	add	a,#0x06
	mov	r0,a
	lcall	__gptrget
	mov	@r0,a
;     genIpush
	push	ar2
	push	ar3
	push	ar4
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	a,@dptr
	mov	r2,a
;     genCmpGt
	mov	a,_bp
	add	a,#0x06
	mov	r0,a
;     genCmp
	clr	c
	mov	a,r2
	subb	a,@r0
	clr	a
	rlc	a
;     genIpop
	pop	ar4
	pop	ar3
	pop	ar2
;     genIfx
;     genIfxJump
	jnz	00138$
	ljmp	00108$
00138$:
;     genAssign
	mov	a,_bp
	add	a,#0x06
	mov	r0,a
	mov	dptr,#_ucTopReadyPriority
	mov	a,@r0
	movx	@dptr,a
00108$:
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r5,a
;     genMult
;     genMultOneByte
	mov	a,r5
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	r5,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	r6,a
;     genCast
	mov	r7,#0x1
;     genIpush
	push	ar2
	push	ar3
	push	ar4
;     genCall
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	_vListInsertEnd
	dec	sp
	dec	sp
	dec	sp
	ljmp	00109$
00113$:
;../../Source/tasks.c:1067: ++ucMissedTicks;
;     genPlus
	mov	dptr,#_ucMissedTicks
	movx	a,@dptr
	add	a,#0x01
	movx	@dptr,a
00115$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vTaskSwitchContext'
;------------------------------------------------------------
;------------------------------------------------------------
;../../Source/tasks.c:1133: inline void vTaskSwitchContext( void )
;	-----------------------------------------
;	 function vTaskSwitchContext
;	-----------------------------------------
_vTaskSwitchContext:
	push	_bp
	mov	_bp,sp
;../../Source/tasks.c:1135: if( ucSchedulerSuspended != pdFALSE )
;     genAssign
	mov	dptr,#_ucSchedulerSuspended
	movx	a,@dptr
	mov	r2,a
;     genCmpEq
	cjne	r2,#0x00,00114$
	ljmp	00103$
00114$:
;../../Source/tasks.c:1139: return;
;     genRet
	ljmp	00108$
;../../Source/tasks.c:1143: while( listLIST_IS_EMPTY( &( pxReadyTasksLists[ ucTopReadyPriority ] ) ) )
00103$:
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	a,@dptr
	mov	r2,a
;     genMult
;     genMultOneByte
	mov	a,r2
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	dpl,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	dph,a
;     genPointerGet
;     genFarPointerGet
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
;     genCmpEq
	cjne	r2,#0x00,00115$
	cjne	r3,#0x00,00115$
	sjmp	00116$
00115$:
	ljmp	00105$
00116$:
;../../Source/tasks.c:1145: --ucTopReadyPriority;
;     genMinus
	mov	dptr,#_ucTopReadyPriority
;     genMinusDec
	movx	a,@dptr
	dec	a
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	@dptr,a
	ljmp	00103$
00105$:
;../../Source/tasks.c:1150: listGET_OWNER_OF_NEXT_ENTRY( pxCurrentTCB, &( pxReadyTasksLists[ ucTopReadyPriority ] ) );
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	a,@dptr
	mov	r2,a
;     genMult
;     genMultOneByte
	mov	a,r2
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	r2,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	r3,a
;     genPlus
	mov	a,#0x05
	add	a,ar2
	mov	r2,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	a,@dptr
	mov	r4,a
;     genMult
;     genMultOneByte
	mov	a,r4
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	r4,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	r5,a
;     genPlus
	mov	a,#0x05
	add	a,ar4
	mov	dpl,a
	mov	a,#0x00
	addc	a,ar5
	mov	dph,a
;     genPointerGet
;     genFarPointerGet
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
;     genPlus
;     genPlusIncr
	mov	a,#0x02
	add	a,ar4
	mov	r4,a
	mov	a,#0x00
	addc	a,ar5
	mov	r5,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r4
	mov	dph,r5
	mov	b,r6
	lcall	__gptrget
	mov	r4,a
	inc	dptr
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
;     genPointerSet
;     genFarPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	a,r4
	movx	@dptr,a
	inc	dptr
	mov	a,r5
	movx	@dptr,a
	inc	dptr
	mov	a,r6
	movx	@dptr,a
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	a,@dptr
	mov	r2,a
;     genMult
;     genMultOneByte
	mov	a,r2
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	r2,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	r3,a
;     genPlus
	mov	a,#0x05
	add	a,ar2
	mov	dpl,a
	mov	a,#0x00
	addc	a,ar3
	mov	dph,a
;     genPointerGet
;     genFarPointerGet
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	a,@dptr
	mov	r5,a
;     genMult
;     genMultOneByte
	mov	a,r5
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	r5,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	r6,a
;     genPlus
;     genPlusIncr
	mov	a,#0x02
	add	a,ar5
	mov	dpl,a
	mov	a,#0x00
	addc	a,ar6
	mov	dph,a
;     genPointerGet
;     genFarPointerGet
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
;     genCmpEq
	mov	a,r2
	cjne	a,ar5,00117$
	mov	a,r3
	cjne	a,ar6,00117$
	mov	a,r4
	cjne	a,ar7,00117$
	sjmp	00118$
00117$:
	ljmp	00107$
00118$:
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	a,@dptr
	mov	r2,a
;     genMult
;     genMultOneByte
	mov	a,r2
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	r2,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	r3,a
;     genPlus
	mov	a,#0x05
	add	a,ar2
	mov	r2,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	a,@dptr
	mov	r4,a
;     genMult
;     genMultOneByte
	mov	a,r4
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	r4,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	r5,a
;     genPlus
	mov	a,#0x05
	add	a,ar4
	mov	dpl,a
	mov	a,#0x00
	addc	a,ar5
	mov	dph,a
;     genPointerGet
;     genFarPointerGet
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
;     genPlus
;     genPlusIncr
	mov	a,#0x02
	add	a,ar4
	mov	r4,a
	mov	a,#0x00
	addc	a,ar5
	mov	r5,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r4
	mov	dph,r5
	mov	b,r6
	lcall	__gptrget
	mov	r4,a
	inc	dptr
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
;     genPointerSet
;     genFarPointerSet
	mov	dpl,r2
	mov	dph,r3
	mov	a,r4
	movx	@dptr,a
	inc	dptr
	mov	a,r5
	movx	@dptr,a
	inc	dptr
	mov	a,r6
	movx	@dptr,a
00107$:
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	a,@dptr
	mov	r2,a
;     genMult
;     genMultOneByte
	mov	a,r2
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	r2,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	r3,a
;     genPlus
	mov	a,#0x05
	add	a,ar2
	mov	dpl,a
	mov	a,#0x00
	addc	a,ar3
	mov	dph,a
;     genPointerGet
;     genFarPointerGet
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
;     genPlus
	mov	a,#0x08
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
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
;     genAssign
	mov	dptr,#_pxCurrentTCB
	mov	a,r2
	movx	@dptr,a
	inc	dptr
	mov	a,r3
	movx	@dptr,a
	inc	dptr
	mov	a,r4
	movx	@dptr,a
00108$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'vTaskPlaceOnEventList'
;------------------------------------------------------------
;xTicksToWait              Allocated to stack - offset -4
;pxEventList               Allocated to registers r2 r3 r4 
;xTimeToWake               Allocated to registers r2 r3 
;------------------------------------------------------------
;../../Source/tasks.c:1155: void vTaskPlaceOnEventList( xList *pxEventList, portTickType xTicksToWait )
;	-----------------------------------------
;	 function vTaskPlaceOnEventList
;	-----------------------------------------
_vTaskPlaceOnEventList:
	push	_bp
	mov	_bp,sp
;     genReceive
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;../../Source/tasks.c:1165: vListInsert( ( xList * ) pxEventList, ( xListItem * ) &( pxCurrentTCB->xEventListItem ) );
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
;     genPlus
	mov	a,#0x27
	add	a,ar5
	mov	r5,a
	mov	a,#0x00
	addc	a,ar6
	mov	r6,a
;     genIpush
	push	ar5
	push	ar6
	push	ar7
;     genCall
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	_vListInsert
	dec	sp
	dec	sp
	dec	sp
;../../Source/tasks.c:1169: xTimeToWake = xTickCount + xTicksToWait;
;     genAssign
	mov	dptr,#_xTickCount
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
;     genPlus
	mov	a,_bp
	add	a,#0xfc
	mov	r0,a
	mov	a,@r0
	add	a,ar2
	mov	r2,a
	inc	r0
	mov	a,@r0
	addc	a,ar3
	mov	r3,a
;     genAssign
;../../Source/tasks.c:1174: vListRemove( ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
;     genPlus
	mov	a,#0x19
	add	a,ar4
	mov	r4,a
	mov	a,#0x00
	addc	a,ar5
	mov	r5,a
;     genCall
	mov	dpl,r4
	mov	dph,r5
	mov	b,r6
	push	ar2
	push	ar3
	lcall	_vListRemove
	pop	ar3
	pop	ar2
;../../Source/tasks.c:1176: listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xGenericListItem ), xTimeToWake );
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
;     genPlus
	mov	a,#0x19
	add	a,ar4
	mov	r4,a
	mov	a,#0x00
	addc	a,ar5
	mov	r5,a
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r4
	mov	dph,r5
	mov	b,r6
	mov	a,r2
	lcall	__gptrput
	inc	dptr
	mov	a,r3
	lcall	__gptrput
;../../Source/tasks.c:1178: if( xTimeToWake < xTickCount )
;     genAssign
	mov	dptr,#_xTickCount
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
;     genCmpLt
;     genCmp
	clr	c
	mov	a,r2
	subb	a,r4
	mov	a,r3
	subb	a,r5
;     genIfxJump
	jc	00107$
	ljmp	00102$
00107$:
;../../Source/tasks.c:1181: vListInsert( ( xList * ) pxOverflowDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
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
;     genPlus
	mov	a,#0x19
	add	a,ar2
	mov	r2,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genAssign
	mov	dptr,#_pxOverflowDelayedTaskList
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
;     genIpush
	push	ar2
	push	ar3
	push	ar4
;     genCall
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	_vListInsert
	dec	sp
	dec	sp
	dec	sp
	ljmp	00104$
00102$:
;../../Source/tasks.c:1186: vListInsert( ( xList * ) pxDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
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
;     genPlus
	mov	a,#0x19
	add	a,ar2
	mov	r2,a
	mov	a,#0x00
	addc	a,ar3
	mov	r3,a
;     genAssign
	mov	dptr,#_pxDelayedTaskList
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	movx	a,@dptr
	mov	r6,a
	inc	dptr
	movx	a,@dptr
	mov	r7,a
;     genIpush
	push	ar2
	push	ar3
	push	ar4
;     genCall
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	_vListInsert
	dec	sp
	dec	sp
	dec	sp
00104$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'cTaskRemoveFromEventList'
;------------------------------------------------------------
;pxEventList               Allocated to registers r2 r3 r4 
;pxUnblockedTCB            Allocated to stack - offset 1
;------------------------------------------------------------
;../../Source/tasks.c:1191: signed portCHAR cTaskRemoveFromEventList( const xList *pxEventList )
;	-----------------------------------------
;	 function cTaskRemoveFromEventList
;	-----------------------------------------
_cTaskRemoveFromEventList:
	push	_bp
	mov	_bp,sp
	inc	sp
	inc	sp
	inc	sp
;     genReceive
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;../../Source/tasks.c:1205: pxUnblockedTCB = ( tskTCB * ) listGET_OWNER_OF_HEAD_ENTRY( pxEventList );
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
	cjne	r5,#0x00,00117$
	cjne	r6,#0x00,00117$
	mov	a,#0x01
	sjmp	00118$
00117$:
	clr	a
00118$:
	mov	r5,a
;     genNot
	mov	a,r5
	cjne	a,#0x01,00119$
00119$:
	clr	a
	rlc	a
	mov	r5,a
;     genIfx
	mov	a,r5
;     genIfxJump
	jnz	00120$
	ljmp	00111$
00120$:
;     genPlus
;     genPlusIncr
	mov	a,#0x02
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
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
;     genPlus
;     genPlusIncr
	mov	a,#0x02
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
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
;     genPlus
	mov	a,#0x08
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
	inc	dptr
	lcall	__gptrget
	mov	r3,a
	inc	dptr
	lcall	__gptrget
	mov	r4,a
	ljmp	00112$
00111$:
;     genAssign
	mov	r2,#0x00
	mov	r3,#0x00
	mov	r4,#0x00
00112$:
;     genAssign
;     genAssign
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	@r0,ar2
	inc	r0
	mov	@r0,ar3
	inc	r0
	mov	@r0,ar4
;../../Source/tasks.c:1206: vListRemove( &( pxUnblockedTCB->xEventListItem ) );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x27
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genCall
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	_vListRemove
;../../Source/tasks.c:1208: if( ucSchedulerSuspended == ( unsigned portCHAR ) pdFALSE )
;     genAssign
	mov	dptr,#_ucSchedulerSuspended
	movx	a,@dptr
	mov	r5,a
;     genCmpEq
	cjne	r5,#0x00,00121$
	sjmp	00122$
00121$:
	ljmp	00104$
00122$:
;../../Source/tasks.c:1210: vListRemove( &( pxUnblockedTCB->xGenericListItem ) );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x19
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genCall
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	_vListRemove
;../../Source/tasks.c:1211: prvAddTaskToReadyQueue( pxUnblockedTCB );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x19
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,#0x00
	lcall	__gptrput
	inc	dptr
	mov	a,#0x00
	lcall	__gptrput
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x18
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
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	movx	a,@dptr
	mov	r3,a
;     genCmpGt
;     genCmp
	clr	c
	mov	a,r3
	subb	a,r2
;     genIfxJump
	jc	00123$
	ljmp	00102$
00123$:
;     genAssign
	mov	dptr,#_ucTopReadyPriority
	mov	a,r2
	movx	@dptr,a
00102$:
;     genMult
;     genMultOneByte
	mov	a,r2
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	r2,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	r3,a
;     genCast
	mov	r4,#0x1
;     genIpush
	push	ar5
	push	ar6
	push	ar7
;     genCall
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	_vListInsertEnd
	dec	sp
	dec	sp
	dec	sp
	ljmp	00105$
00104$:
;../../Source/tasks.c:1217: vListInsertEnd( ( xList * ) &( xPendingReadyList ), &( pxUnblockedTCB->xEventListItem ) );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x27
	add	a,@r0
	mov	r2,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
;     genIpush
	push	ar2
	push	ar3
	push	ar4
;     genCall
	mov	dpl,#_xPendingReadyList
	mov	dph,#(_xPendingReadyList >> 8)
	mov	b,#0x01
	lcall	_vListInsertEnd
	dec	sp
	dec	sp
	dec	sp
00105$:
;../../Source/tasks.c:1220: if( pxUnblockedTCB->ucPriority > pxCurrentTCB->ucPriority )
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x18
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
;     genAssign
	mov	dptr,#_pxCurrentTCB
	movx	a,@dptr
	mov	r3,a
	inc	dptr
	movx	a,@dptr
	mov	r4,a
	inc	dptr
	movx	a,@dptr
	mov	r5,a
;     genPlus
	mov	a,#0x18
	add	a,ar3
	mov	r3,a
	mov	a,#0x00
	addc	a,ar4
	mov	r4,a
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	lcall	__gptrget
	mov	r3,a
;     genCmpGt
;     genCmp
	clr	c
	mov	a,r3
	subb	a,r2
;     genIfxJump
	jc	00124$
	ljmp	00107$
00124$:
;../../Source/tasks.c:1226: return ( signed portCHAR ) pdTRUE;
;     genRet
	mov	dpl,#0x01
	ljmp	00109$
00107$:
;../../Source/tasks.c:1230: return ( signed portCHAR ) pdFALSE;
;     genRet
	mov	dpl,#0x00
00109$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'prvIdleTask'
;------------------------------------------------------------
;pvParameters              Allocated to registers 
;------------------------------------------------------------
;../../Source/tasks.c:1242: static void prvIdleTask( void *pvParameters )
;	-----------------------------------------
;	 function prvIdleTask
;	-----------------------------------------
_prvIdleTask:
	push	_bp
	mov	_bp,sp
;../../Source/tasks.c:1245: ( void ) pvParameters;
00104$:
;../../Source/tasks.c:1250: prvCheckTasksWaitingTermination();
;     genCall
	lcall	_prvCheckTasksWaitingTermination
;../../Source/tasks.c:1252: if( sUsingPreemption == pdFALSE )
;     genAssign
	mov	dptr,#_sUsingPreemption
	movx	a,@dptr
	mov	r2,a
	inc	dptr
	movx	a,@dptr
	mov	r3,a
;     genCmpEq
	cjne	r2,#0x00,00110$
	cjne	r3,#0x00,00110$
	sjmp	00111$
00110$:
	ljmp	00104$
00111$:
;../../Source/tasks.c:1258: taskYIELD();	
;     genCall
	lcall	_vPortYield
	ljmp	00104$
00106$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'prvInitialiseTCBVariables'
;------------------------------------------------------------
;usStackDepth              Allocated to stack - offset -4
;pcName                    Allocated to stack - offset -7
;ucPriority                Allocated to stack - offset -8
;pxTCB                     Allocated to stack - offset 1
;------------------------------------------------------------
;../../Source/tasks.c:1275: static void prvInitialiseTCBVariables( tskTCB *pxTCB, unsigned portSHORT usStackDepth, const signed portCHAR * const pcName, unsigned portCHAR ucPriority )
;	-----------------------------------------
;	 function prvInitialiseTCBVariables
;	-----------------------------------------
_prvInitialiseTCBVariables:
	push	_bp
	mov	_bp,sp
;     genReceive
	push	dpl
	push	dph
	push	b
;../../Source/tasks.c:1277: pxTCB->usStackDepth = usStackDepth;
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x06
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,_bp
	add	a,#0xfc
	mov	r0,a
	mov	a,@r0
	lcall	__gptrput
	inc	dptr
	inc	r0
	mov	a,@r0
	lcall	__gptrput
;../../Source/tasks.c:1280: if( strlen( pcName ) < ( unsigned portSHORT ) tskMAX_TASK_NAME_LEN )
;     genCall
	mov	a,_bp
	add	a,#0xf9
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	_strlen
	mov	r5,dpl
	mov	r6,dph
;     genCmpLt
;     genCmp
	clr	c
	mov	a,r5
	subb	a,#0x10
	mov	a,r6
	subb	a,#0x00
;     genIfxJump
	jc	00110$
	ljmp	00102$
00110$:
;../../Source/tasks.c:1282: portENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/tasks.c:1283: strcpy( pxTCB->pcTaskName, pcName );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x08
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genIpush
	mov	a,_bp
	add	a,#0xf9
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
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	_strcpy
	dec	sp
	dec	sp
	dec	sp
;../../Source/tasks.c:1284: portEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
	ljmp	00103$
00102$:
;../../Source/tasks.c:1288: portENTER_CRITICAL();
;     genInline
	 push ACC push IE 
;     genAssign
	clr	_EA
;../../Source/tasks.c:1289: strncpy( pxTCB->pcTaskName, pcName, ( unsigned portSHORT ) tskMAX_TASK_NAME_LEN );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x08
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genIpush
	push	ar5
	push	ar6
	push	ar7
	mov	a,#0x10
	push	acc
	mov	a,#0x00
	push	acc
;     genIpush
	mov	a,_bp
	add	a,#0xf9
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
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	_strncpy
	mov	a,sp
	add	a,#0xfb
	mov	sp,a
	pop	ar7
	pop	ar6
	pop	ar5
;../../Source/tasks.c:1290: portEXIT_CRITICAL();
;     genInline
	 pop ACC 
;     genAnd
	anl	_ACC,#0x80
;     genOr
	mov	a,_ACC
	orl	_IE,a
;     genInline
	 pop ACC 
;../../Source/tasks.c:1291: pxTCB->pcTaskName[ ( unsigned portSHORT ) tskMAX_TASK_NAME_LEN - ( unsigned portSHORT ) 1 ] = '\0';
;     genPlus
	mov	a,#0x0F
	add	a,ar5
	mov	r5,a
	mov	a,#0x00
	addc	a,ar6
	mov	r6,a
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,#0x00
	lcall	__gptrput
00103$:
;../../Source/tasks.c:1295: if( ucPriority >= ( unsigned portCHAR ) portMAX_PRIORITIES )
;     genCmpLt
	mov	a,_bp
	add	a,#0xf8
	mov	r0,a
;     genCmp
	cjne	@r0,#0x04,00111$
00111$:
;     genIfxJump
	jnc	00112$
	ljmp	00105$
00112$:
;../../Source/tasks.c:1297: ucPriority = ( unsigned portCHAR ) portMAX_PRIORITIES - ( unsigned portCHAR ) 1;
;     genAssign
	mov	a,_bp
	add	a,#0xf8
	mov	r0,a
	mov	@r0,#0x03
00105$:
;../../Source/tasks.c:1299: pxTCB->ucPriority = ucPriority;
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x18
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,_bp
	add	a,#0xf8
	mov	r0,a
	mov	a,@r0
	lcall	__gptrput
;../../Source/tasks.c:1301: vListInitialiseItem( &( pxTCB->xGenericListItem ) );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x19
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genCall
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	_vListInitialiseItem
;../../Source/tasks.c:1302: vListInitialiseItem( &( pxTCB->xEventListItem ) );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x27
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genCall
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	_vListInitialiseItem
;../../Source/tasks.c:1306: listSET_LIST_ITEM_OWNER( &( pxTCB->xGenericListItem ), pxTCB );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x19
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genPlus
	mov	a,#0x08
	add	a,ar5
	mov	r5,a
	mov	a,#0x00
	addc	a,ar6
	mov	r6,a
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,@r0
	lcall	__gptrput
	inc	dptr
	inc	r0
	mov	a,@r0
	lcall	__gptrput
	inc	dptr
	inc	r0
	mov	a,@r0
	lcall	__gptrput
;../../Source/tasks.c:1309: listSET_LIST_ITEM_VALUE( &( pxTCB->xEventListItem ), ( portTickType ) ucPriority );
;     genPlus
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,#0x27
	add	a,@r0
	mov	r5,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
;     genCast
	mov	a,_bp
	add	a,#0xf8
	mov	r0,a
	mov	ar2,@r0
	mov	r3,#0x00
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,r2
	lcall	__gptrput
	inc	dptr
	mov	a,r3
	lcall	__gptrput
;../../Source/tasks.c:1310: listSET_LIST_ITEM_OWNER( &( pxTCB->xEventListItem ), pxTCB );
;     genPlus
	mov	a,#0x08
	add	a,ar5
	mov	r5,a
	mov	a,#0x00
	addc	a,ar6
	mov	r6,a
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,@r0
	lcall	__gptrput
	inc	dptr
	inc	r0
	mov	a,@r0
	lcall	__gptrput
	inc	dptr
	inc	r0
	mov	a,@r0
	lcall	__gptrput
00106$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'prvInitialiseTaskLists'
;------------------------------------------------------------
;ucPriority                Allocated to registers r2 
;sReturn                   Allocated to registers r2 r3 
;------------------------------------------------------------
;../../Source/tasks.c:1314: static portSHORT prvInitialiseTaskLists( void )
;	-----------------------------------------
;	 function prvInitialiseTaskLists
;	-----------------------------------------
_prvInitialiseTaskLists:
	push	_bp
	mov	_bp,sp
;../../Source/tasks.c:1319: for( ucPriority = ( unsigned portCHAR) 0; ucPriority < ( unsigned portCHAR ) portMAX_PRIORITIES; ucPriority++ )
;     genAssign
	mov	r2,#0x00
00101$:
;     genCmpLt
;     genCmp
	cjne	r2,#0x04,00109$
00109$:
;     genIfxJump
	jc	00110$
	ljmp	00104$
00110$:
;../../Source/tasks.c:1321: vListInitialise( ( xList * ) &( pxReadyTasksLists[ ucPriority ] ) );
;     genMult
;     genMultOneByte
	mov	a,r2
	mov	b,#0x16
	mul	ab
;     genPlus
	add	a,#_pxReadyTasksLists
	mov	r3,a
	mov	a,b
	addc	a,#(_pxReadyTasksLists >> 8)
	mov	r4,a
;     genCast
	mov	r5,#0x1
;     genCall
	mov	dpl,r3
	mov	dph,r4
	mov	b,r5
	push	ar2
	lcall	_vListInitialise
	pop	ar2
;../../Source/tasks.c:1319: for( ucPriority = ( unsigned portCHAR) 0; ucPriority < ( unsigned portCHAR ) portMAX_PRIORITIES; ucPriority++ )
;     genPlus
;     genPlusIncr
	inc	r2
	ljmp	00101$
00104$:
;../../Source/tasks.c:1324: vListInitialise( ( xList * ) &xDelayedTaskList1 );
;     genCall
	mov	dpl,#_xDelayedTaskList1
	mov	dph,#(_xDelayedTaskList1 >> 8)
	mov	b,#0x01
	lcall	_vListInitialise
;../../Source/tasks.c:1325: vListInitialise( ( xList * ) &xDelayedTaskList2 );
;     genCall
	mov	dpl,#_xDelayedTaskList2
	mov	dph,#(_xDelayedTaskList2 >> 8)
	mov	b,#0x01
	lcall	_vListInitialise
;../../Source/tasks.c:1326: vListInitialise( ( xList * ) &xPendingReadyList );
;     genCall
	mov	dpl,#_xPendingReadyList
	mov	dph,#(_xPendingReadyList >> 8)
	mov	b,#0x01
	lcall	_vListInitialise
;../../Source/tasks.c:1342: pxDelayedTaskList = &xDelayedTaskList1;
;     genCast
	mov	dptr,#_pxDelayedTaskList
	mov	a,#_xDelayedTaskList1
	movx	@dptr,a
	inc	dptr
	mov	a,#(_xDelayedTaskList1 >> 8)
	movx	@dptr,a
	inc	dptr
	mov	a,#0x1
	movx	@dptr,a
;../../Source/tasks.c:1343: pxOverflowDelayedTaskList = &xDelayedTaskList2;
;     genCast
	mov	dptr,#_pxOverflowDelayedTaskList
	mov	a,#_xDelayedTaskList2
	movx	@dptr,a
	inc	dptr
	mov	a,#(_xDelayedTaskList2 >> 8)
	movx	@dptr,a
	inc	dptr
	mov	a,#0x1
	movx	@dptr,a
;../../Source/tasks.c:1346: sReturn = sTaskCreate( prvIdleTask, ( const portCHAR * const ) "IDLE", tskIDLE_STACK_SIZE, ( void * ) NULL, tskIDLE_PRIORITY, ( xTaskHandle * ) NULL );
;     genIpush
	mov	a,#0x00
	push	acc
	mov	a,#0x00
	push	acc
	mov	a,#0x00
	push	acc
;     genIpush
	mov	a,#0x00
	push	acc
;     genIpush
	mov	a,#0x00
	push	acc
	mov	a,#0x00
	push	acc
	mov	a,#0x00
	push	acc
;     genIpush
	mov	a,#0xA6
	push	acc
	mov	a,#0x00
	push	acc
;     genIpush
	mov	a,#__str_0
	push	acc
	mov	a,#(__str_0 >> 8)
	push	acc
	mov	a,#0x02
	push	acc
;     genCall
	mov	dpl,#_prvIdleTask
	mov	dph,#(_prvIdleTask >> 8)
	lcall	_sTaskCreate
	mov	r2,dpl
	mov	r3,dph
	mov	a,sp
	add	a,#0xf4
	mov	sp,a
;     genAssign
;../../Source/tasks.c:1348: return sReturn;
;     genRet
	mov	dpl,r2
	mov	dph,r3
00105$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'prvCheckTasksWaitingTermination'
;------------------------------------------------------------
;------------------------------------------------------------
;../../Source/tasks.c:1352: static void prvCheckTasksWaitingTermination( void )
;	-----------------------------------------
;	 function prvCheckTasksWaitingTermination
;	-----------------------------------------
_prvCheckTasksWaitingTermination:
	push	_bp
	mov	_bp,sp
;../../Source/tasks.c:1378: }
00101$:
	mov	sp,_bp
	pop	_bp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'prvAllocateTCBAndStack'
;------------------------------------------------------------
;usStackDepth              Allocated to stack - offset 1
;pxNewTCB                  Allocated to stack - offset 3
;------------------------------------------------------------
;../../Source/tasks.c:1381: static tskTCB *prvAllocateTCBAndStack( unsigned portSHORT usStackDepth )
;	-----------------------------------------
;	 function prvAllocateTCBAndStack
;	-----------------------------------------
_prvAllocateTCBAndStack:
	push	_bp
	mov	_bp,sp
;     genReceive
	push	dpl
	push	dph
	inc	sp
	inc	sp
	inc	sp
;../../Source/tasks.c:1387: pxNewTCB = ( tskTCB * ) pvPortMalloc( sizeof( tskTCB ) );
;     genCall
	mov	dpl,#0x36
	mov	dph,#0x00
	lcall	_pvPortMalloc
	mov	r4,dpl
	mov	r5,dph
	mov	r6,b
;     genAssign
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	@r0,ar4
	inc	r0
	mov	@r0,ar5
	inc	r0
	mov	@r0,ar6
;../../Source/tasks.c:1389: if( pxNewTCB != NULL )
;     genCmpEq
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	cjne	@r0,#0x00,00110$
	inc	r0
	cjne	@r0,#0x00,00110$
	inc	r0
	cjne	@r0,#0x00,00110$
	ljmp	00105$
00110$:
;../../Source/tasks.c:1394: pxNewTCB->pxStack = ( portSTACK_TYPE * ) pvPortMalloc( usStackDepth * sizeof( portSTACK_TYPE ) );
;     genPlus
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
;     genPlusIncr
	mov	a,#0x03
	add	a,@r0
	mov	r7,a
	mov	a,#0x00
	inc	r0
	addc	a,@r0
	mov	r2,a
	inc	r0
	mov	ar3,@r0
;     genCall
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	push	ar2
	push	ar3
	push	ar7
	lcall	_pvPortMalloc
	mov	r4,dpl
	mov	r5,dph
	mov	r6,b
	pop	ar7
	pop	ar3
	pop	ar2
;     genPointerSet
;     genGenPointerSet
	mov	dpl,r7
	mov	dph,r2
	mov	b,r3
	mov	a,r4
	lcall	__gptrput
	inc	dptr
	mov	a,r5
	lcall	__gptrput
	inc	dptr
	mov	a,r6
	lcall	__gptrput
;../../Source/tasks.c:1396: if( pxNewTCB->pxStack == NULL )
;     genCmpEq
	cjne	r4,#0x00,00111$
	cjne	r5,#0x00,00111$
	cjne	r6,#0x00,00111$
	sjmp	00112$
00111$:
	ljmp	00102$
00112$:
;../../Source/tasks.c:1399: vPortFree( pxNewTCB );			
;     genCall
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	_vPortFree
;../../Source/tasks.c:1400: pxNewTCB = NULL;			
;     genAssign
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	clr	a
	mov	@r0,a
	inc	r0
	mov	@r0,a
	inc	r0
	mov	@r0,a
	ljmp	00105$
00102$:
;../../Source/tasks.c:1405: memset( pxNewTCB->pxStack, tskSTACK_FILL_BYTE, usStackDepth * sizeof( portSTACK_TYPE ) );
;     genPointerGet
;     genGenPointerGet
	mov	dpl,r7
	mov	dph,r2
	mov	b,r3
	lcall	__gptrget
	mov	r7,a
	inc	dptr
	lcall	__gptrget
	mov	r2,a
	inc	dptr
	lcall	__gptrget
	mov	r3,a
;     genIpush
	mov	a,_bp
	add	a,#0x01
	mov	r0,a
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
;     genIpush
	mov	a,#0xA5
	push	acc
;     genCall
	mov	dpl,r7
	mov	dph,r2
	mov	b,r3
	lcall	_memset
	dec	sp
	dec	sp
	dec	sp
00105$:
;../../Source/tasks.c:1409: return pxNewTCB;
;     genRet
	mov	a,_bp
	add	a,#0x03
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
00106$:
	mov	sp,_bp
	pop	_bp
	ret
	.area CSEG    (CODE)
__str_0:
	.ascii "IDLE"
	.db 0x00
	.area XINIT   (CODE)
__xinit__pxCurrentTCB:
; generic printIvalPtr
	.byte #0x00,#0x00,#0x00
__xinit__sUsingPreemption:
	.byte #0x00,#0x00
__xinit__usCurrentNumberOfTasks:
	.byte #0x00,#0x00
__xinit__xTickCount:
	.byte #0x00,#0x00
__xinit__ucTopUsedPriority:
	.db #0x00
__xinit__ucTopReadyPriority:
	.db #0x00
__xinit__cSchedulerRunning:
	.db #0x00
__xinit__ucSchedulerSuspended:
	.db #0x00
__xinit__ucMissedTicks:
	.db #0x00
