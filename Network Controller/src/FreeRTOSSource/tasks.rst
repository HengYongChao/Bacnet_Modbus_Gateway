                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.4.8 #964 (Feb 23 2005)
                              4 ; This file generated Fri May 20 14:05:27 2005
                              5 ;--------------------------------------------------------
                              6 	.module ______Source_tasks
                              7 	.optsdcc -mmcs51 --model-large
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _TF2
                             13 	.globl _EXF2
                             14 	.globl _RCLK
                             15 	.globl _TCLK
                             16 	.globl _EXEN2
                             17 	.globl _TR2
                             18 	.globl _C_T2
                             19 	.globl _CP_RL2
                             20 	.globl _T2CON_7
                             21 	.globl _T2CON_6
                             22 	.globl _T2CON_5
                             23 	.globl _T2CON_4
                             24 	.globl _T2CON_3
                             25 	.globl _T2CON_2
                             26 	.globl _T2CON_1
                             27 	.globl _T2CON_0
                             28 	.globl _ET2
                             29 	.globl _CY
                             30 	.globl _AC
                             31 	.globl _F0
                             32 	.globl _RS1
                             33 	.globl _RS0
                             34 	.globl _OV
                             35 	.globl _F1
                             36 	.globl _P
                             37 	.globl _PS
                             38 	.globl _PT1
                             39 	.globl _PX1
                             40 	.globl _PT0
                             41 	.globl _PX0
                             42 	.globl _RD
                             43 	.globl _WR
                             44 	.globl _T1
                             45 	.globl _T0
                             46 	.globl _INT1
                             47 	.globl _INT0
                             48 	.globl _TXD
                             49 	.globl _RXD
                             50 	.globl _P3_7
                             51 	.globl _P3_6
                             52 	.globl _P3_5
                             53 	.globl _P3_4
                             54 	.globl _P3_3
                             55 	.globl _P3_2
                             56 	.globl _P3_1
                             57 	.globl _P3_0
                             58 	.globl _EA
                             59 	.globl _ES
                             60 	.globl _ET1
                             61 	.globl _EX1
                             62 	.globl _ET0
                             63 	.globl _EX0
                             64 	.globl _P2_7
                             65 	.globl _P2_6
                             66 	.globl _P2_5
                             67 	.globl _P2_4
                             68 	.globl _P2_3
                             69 	.globl _P2_2
                             70 	.globl _P2_1
                             71 	.globl _P2_0
                             72 	.globl _SM0
                             73 	.globl _SM1
                             74 	.globl _SM2
                             75 	.globl _REN
                             76 	.globl _TB8
                             77 	.globl _RB8
                             78 	.globl _TI
                             79 	.globl _RI
                             80 	.globl _P1_7
                             81 	.globl _P1_6
                             82 	.globl _P1_5
                             83 	.globl _P1_4
                             84 	.globl _P1_3
                             85 	.globl _P1_2
                             86 	.globl _P1_1
                             87 	.globl _P1_0
                             88 	.globl _TF1
                             89 	.globl _TR1
                             90 	.globl _TF0
                             91 	.globl _TR0
                             92 	.globl _IE1
                             93 	.globl _IT1
                             94 	.globl _IE0
                             95 	.globl _IT0
                             96 	.globl _P0_7
                             97 	.globl _P0_6
                             98 	.globl _P0_5
                             99 	.globl _P0_4
                            100 	.globl _P0_3
                            101 	.globl _P0_2
                            102 	.globl _P0_1
                            103 	.globl _P0_0
                            104 	.globl _TH2
                            105 	.globl _TL2
                            106 	.globl _RCAP2H
                            107 	.globl _RCAP2L
                            108 	.globl _T2CON
                            109 	.globl _B
                            110 	.globl _ACC
                            111 	.globl _PSW
                            112 	.globl _IP
                            113 	.globl _P3
                            114 	.globl _IE
                            115 	.globl _P2
                            116 	.globl _SBUF
                            117 	.globl _SCON
                            118 	.globl _P1
                            119 	.globl _TH1
                            120 	.globl _TH0
                            121 	.globl _TL1
                            122 	.globl _TL0
                            123 	.globl _TMOD
                            124 	.globl _TCON
                            125 	.globl _PCON
                            126 	.globl _DPH
                            127 	.globl _DPL
                            128 	.globl _SP
                            129 	.globl _P0
                            130 	.globl _pxCurrentTCB
                            131 	.globl _sTaskCreate
                            132 	.globl _vTaskDelayUntil
                            133 	.globl _vTaskDelay
                            134 	.globl _vTaskStartScheduler
                            135 	.globl _vTaskEndScheduler
                            136 	.globl _vTaskSuspendAll
                            137 	.globl _cTaskResumeAll
                            138 	.globl _xTaskGetTickCount
                            139 	.globl _usTaskGetNumberOfTasks
                            140 	.globl _vTaskIncrementTick
                            141 	.globl _vTaskSwitchContext
                            142 	.globl _vTaskPlaceOnEventList
                            143 	.globl _cTaskRemoveFromEventList
                            144 ;--------------------------------------------------------
                            145 ; special function registers
                            146 ;--------------------------------------------------------
                            147 	.area RSEG    (DATA)
                    0080    148 _P0	=	0x0080
                    0081    149 _SP	=	0x0081
                    0082    150 _DPL	=	0x0082
                    0083    151 _DPH	=	0x0083
                    0087    152 _PCON	=	0x0087
                    0088    153 _TCON	=	0x0088
                    0089    154 _TMOD	=	0x0089
                    008A    155 _TL0	=	0x008a
                    008B    156 _TL1	=	0x008b
                    008C    157 _TH0	=	0x008c
                    008D    158 _TH1	=	0x008d
                    0090    159 _P1	=	0x0090
                    0098    160 _SCON	=	0x0098
                    0099    161 _SBUF	=	0x0099
                    00A0    162 _P2	=	0x00a0
                    00A8    163 _IE	=	0x00a8
                    00B0    164 _P3	=	0x00b0
                    00B8    165 _IP	=	0x00b8
                    00D0    166 _PSW	=	0x00d0
                    00E0    167 _ACC	=	0x00e0
                    00F0    168 _B	=	0x00f0
                    00C8    169 _T2CON	=	0x00c8
                    00CA    170 _RCAP2L	=	0x00ca
                    00CB    171 _RCAP2H	=	0x00cb
                    00CC    172 _TL2	=	0x00cc
                    00CD    173 _TH2	=	0x00cd
                            174 ;--------------------------------------------------------
                            175 ; special function bits 
                            176 ;--------------------------------------------------------
                            177 	.area RSEG    (DATA)
                    0080    178 _P0_0	=	0x0080
                    0081    179 _P0_1	=	0x0081
                    0082    180 _P0_2	=	0x0082
                    0083    181 _P0_3	=	0x0083
                    0084    182 _P0_4	=	0x0084
                    0085    183 _P0_5	=	0x0085
                    0086    184 _P0_6	=	0x0086
                    0087    185 _P0_7	=	0x0087
                    0088    186 _IT0	=	0x0088
                    0089    187 _IE0	=	0x0089
                    008A    188 _IT1	=	0x008a
                    008B    189 _IE1	=	0x008b
                    008C    190 _TR0	=	0x008c
                    008D    191 _TF0	=	0x008d
                    008E    192 _TR1	=	0x008e
                    008F    193 _TF1	=	0x008f
                    0090    194 _P1_0	=	0x0090
                    0091    195 _P1_1	=	0x0091
                    0092    196 _P1_2	=	0x0092
                    0093    197 _P1_3	=	0x0093
                    0094    198 _P1_4	=	0x0094
                    0095    199 _P1_5	=	0x0095
                    0096    200 _P1_6	=	0x0096
                    0097    201 _P1_7	=	0x0097
                    0098    202 _RI	=	0x0098
                    0099    203 _TI	=	0x0099
                    009A    204 _RB8	=	0x009a
                    009B    205 _TB8	=	0x009b
                    009C    206 _REN	=	0x009c
                    009D    207 _SM2	=	0x009d
                    009E    208 _SM1	=	0x009e
                    009F    209 _SM0	=	0x009f
                    00A0    210 _P2_0	=	0x00a0
                    00A1    211 _P2_1	=	0x00a1
                    00A2    212 _P2_2	=	0x00a2
                    00A3    213 _P2_3	=	0x00a3
                    00A4    214 _P2_4	=	0x00a4
                    00A5    215 _P2_5	=	0x00a5
                    00A6    216 _P2_6	=	0x00a6
                    00A7    217 _P2_7	=	0x00a7
                    00A8    218 _EX0	=	0x00a8
                    00A9    219 _ET0	=	0x00a9
                    00AA    220 _EX1	=	0x00aa
                    00AB    221 _ET1	=	0x00ab
                    00AC    222 _ES	=	0x00ac
                    00AF    223 _EA	=	0x00af
                    00B0    224 _P3_0	=	0x00b0
                    00B1    225 _P3_1	=	0x00b1
                    00B2    226 _P3_2	=	0x00b2
                    00B3    227 _P3_3	=	0x00b3
                    00B4    228 _P3_4	=	0x00b4
                    00B5    229 _P3_5	=	0x00b5
                    00B6    230 _P3_6	=	0x00b6
                    00B7    231 _P3_7	=	0x00b7
                    00B0    232 _RXD	=	0x00b0
                    00B1    233 _TXD	=	0x00b1
                    00B2    234 _INT0	=	0x00b2
                    00B3    235 _INT1	=	0x00b3
                    00B4    236 _T0	=	0x00b4
                    00B5    237 _T1	=	0x00b5
                    00B6    238 _WR	=	0x00b6
                    00B7    239 _RD	=	0x00b7
                    00B8    240 _PX0	=	0x00b8
                    00B9    241 _PT0	=	0x00b9
                    00BA    242 _PX1	=	0x00ba
                    00BB    243 _PT1	=	0x00bb
                    00BC    244 _PS	=	0x00bc
                    00D0    245 _P	=	0x00d0
                    00D1    246 _F1	=	0x00d1
                    00D2    247 _OV	=	0x00d2
                    00D3    248 _RS0	=	0x00d3
                    00D4    249 _RS1	=	0x00d4
                    00D5    250 _F0	=	0x00d5
                    00D6    251 _AC	=	0x00d6
                    00D7    252 _CY	=	0x00d7
                    00AD    253 _ET2	=	0x00ad
                    00C8    254 _T2CON_0	=	0x00c8
                    00C9    255 _T2CON_1	=	0x00c9
                    00CA    256 _T2CON_2	=	0x00ca
                    00CB    257 _T2CON_3	=	0x00cb
                    00CC    258 _T2CON_4	=	0x00cc
                    00CD    259 _T2CON_5	=	0x00cd
                    00CE    260 _T2CON_6	=	0x00ce
                    00CF    261 _T2CON_7	=	0x00cf
                    00C8    262 _CP_RL2	=	0x00c8
                    00C9    263 _C_T2	=	0x00c9
                    00CA    264 _TR2	=	0x00ca
                    00CB    265 _EXEN2	=	0x00cb
                    00CC    266 _TCLK	=	0x00cc
                    00CD    267 _RCLK	=	0x00cd
                    00CE    268 _EXF2	=	0x00ce
                    00CF    269 _TF2	=	0x00cf
                            270 ;--------------------------------------------------------
                            271 ; overlayable register banks 
                            272 ;--------------------------------------------------------
                            273 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     274 	.ds 8
                            275 ;--------------------------------------------------------
                            276 ; internal ram data
                            277 ;--------------------------------------------------------
                            278 	.area DSEG    (DATA)
                            279 ;--------------------------------------------------------
                            280 ; overlayable items in internal ram 
                            281 ;--------------------------------------------------------
                            282 	.area OSEG    (OVR,DATA)
                            283 ;--------------------------------------------------------
                            284 ; indirectly addressable internal ram data
                            285 ;--------------------------------------------------------
                            286 	.area ISEG    (DATA)
                            287 ;--------------------------------------------------------
                            288 ; bit data
                            289 ;--------------------------------------------------------
                            290 	.area BSEG    (BIT)
                            291 ;--------------------------------------------------------
                            292 ; paged external ram data
                            293 ;--------------------------------------------------------
                            294 	.area PSEG    (PAG,XDATA)
                            295 ;--------------------------------------------------------
                            296 ; external ram data
                            297 ;--------------------------------------------------------
                            298 	.area XSEG    (XDATA)
   0000                     299 _pxReadyTasksLists:
   0000                     300 	.ds 88
   0058                     301 _xDelayedTaskList1:
   0058                     302 	.ds 22
   006E                     303 _xDelayedTaskList2:
   006E                     304 	.ds 22
   0084                     305 _pxDelayedTaskList:
   0084                     306 	.ds 3
   0087                     307 _pxOverflowDelayedTaskList:
   0087                     308 	.ds 3
   008A                     309 _xPendingReadyList:
   008A                     310 	.ds 22
   00A0                     311 _sTaskCreate_ucTaskNumber_1_1:
   00A0                     312 	.ds 1
                            313 ;--------------------------------------------------------
                            314 ; external initialized ram data
                            315 ;--------------------------------------------------------
                            316 	.area XISEG   (XDATA)
   1D0B                     317 _pxCurrentTCB::
   1D0B                     318 	.ds 3
   1D0E                     319 _sUsingPreemption:
   1D0E                     320 	.ds 2
   1D10                     321 _usCurrentNumberOfTasks:
   1D10                     322 	.ds 2
   1D12                     323 _xTickCount:
   1D12                     324 	.ds 2
   1D14                     325 _ucTopUsedPriority:
   1D14                     326 	.ds 1
   1D15                     327 _ucTopReadyPriority:
   1D15                     328 	.ds 1
   1D16                     329 _cSchedulerRunning:
   1D16                     330 	.ds 1
   1D17                     331 _ucSchedulerSuspended:
   1D17                     332 	.ds 1
   1D18                     333 _ucMissedTicks:
   1D18                     334 	.ds 1
                            335 	.area CSEG    (CODE)
                            336 	.area GSINIT0 (CODE)
                            337 	.area GSINIT1 (CODE)
                            338 	.area GSINIT2 (CODE)
                            339 	.area GSINIT3 (CODE)
                            340 	.area GSINIT4 (CODE)
                            341 	.area GSINIT5 (CODE)
                            342 ;--------------------------------------------------------
                            343 ; global & static initialisations
                            344 ;--------------------------------------------------------
                            345 	.area CSEG    (CODE)
                            346 	.area GSINIT  (CODE)
                            347 	.area GSFINAL (CODE)
                            348 	.area GSINIT  (CODE)
                            349 ;------------------------------------------------------------
                            350 ;Allocation info for local variables in function 'sTaskCreate'
                            351 ;------------------------------------------------------------
                            352 ;pcName                    Allocated to stack - offset -5
                            353 ;usStackDepth              Allocated to stack - offset -7
                            354 ;pvParameters              Allocated to stack - offset -10
                            355 ;ucPriority                Allocated to stack - offset -11
                            356 ;pxCreatedTask             Allocated to stack - offset -14
                            357 ;pvTaskCode                Allocated to stack - offset 1
                            358 ;sReturn                   Allocated to registers r2 r3 
                            359 ;pxNewTCB                  Allocated to stack - offset 3
                            360 ;pxTopOfStack              Allocated to registers r7 r2 r3 
                            361 ;sloc0                     Allocated to stack - offset 11
                            362 ;sloc1                     Allocated to stack - offset 6
                            363 ;ucTaskNumber              Allocated with name '_sTaskCreate_ucTaskNumber_1_1'
                            364 ;------------------------------------------------------------
                            365 ;../../Source/tasks.c:365: static unsigned portCHAR ucTaskNumber = 0; /*lint !e956 Static is deliberate - this is guarded before use. */
                            366 ;     genAssign
   AEFB 90 00 A0            367 	mov	dptr,#_sTaskCreate_ucTaskNumber_1_1
   AEFE 74 00               368 	mov	a,#0x00
   AF00 F0                  369 	movx	@dptr,a
                            370 ;--------------------------------------------------------
                            371 ; Home
                            372 ;--------------------------------------------------------
                            373 	.area HOME    (CODE)
                            374 	.area CSEG    (CODE)
                            375 ;--------------------------------------------------------
                            376 ; code
                            377 ;--------------------------------------------------------
                            378 	.area CSEG    (CODE)
                            379 ;------------------------------------------------------------
                            380 ;Allocation info for local variables in function 'sTaskCreate'
                            381 ;------------------------------------------------------------
                            382 ;pcName                    Allocated to stack - offset -5
                            383 ;usStackDepth              Allocated to stack - offset -7
                            384 ;pvParameters              Allocated to stack - offset -10
                            385 ;ucPriority                Allocated to stack - offset -11
                            386 ;pxCreatedTask             Allocated to stack - offset -14
                            387 ;pvTaskCode                Allocated to stack - offset 1
                            388 ;sReturn                   Allocated to registers r2 r3 
                            389 ;pxNewTCB                  Allocated to stack - offset 3
                            390 ;pxTopOfStack              Allocated to registers r7 r2 r3 
                            391 ;sloc0                     Allocated to stack - offset 11
                            392 ;sloc1                     Allocated to stack - offset 6
                            393 ;ucTaskNumber              Allocated with name '_sTaskCreate_ucTaskNumber_1_1'
                            394 ;------------------------------------------------------------
                            395 ;../../Source/tasks.c:361: portSHORT sTaskCreate( pdTASK_CODE pvTaskCode, const signed portCHAR * const pcName, unsigned portSHORT usStackDepth, void *pvParameters, unsigned portCHAR ucPriority, xTaskHandle *pxCreatedTask )
                            396 ;	-----------------------------------------
                            397 ;	 function sTaskCreate
                            398 ;	-----------------------------------------
   008F                     399 _sTaskCreate:
                    0002    400 	ar2 = 0x02
                    0003    401 	ar3 = 0x03
                    0004    402 	ar4 = 0x04
                    0005    403 	ar5 = 0x05
                    0006    404 	ar6 = 0x06
                    0007    405 	ar7 = 0x07
                    0000    406 	ar0 = 0x00
                    0001    407 	ar1 = 0x01
   008F C0 12               408 	push	_bp
   0091 85 81 12            409 	mov	_bp,sp
                            410 ;     genReceive
   0094 C0 82               411 	push	dpl
   0096 C0 83               412 	push	dph
   0098 E5 81               413 	mov	a,sp
   009A 24 08               414 	add	a,#0x08
   009C F5 81               415 	mov	sp,a
                            416 ;../../Source/tasks.c:369: pxNewTCB = prvAllocateTCBAndStack( usStackDepth );
                            417 ;     genCall
   009E E5 12               418 	mov	a,_bp
   00A0 24 F9               419 	add	a,#0xf9
   00A2 F8                  420 	mov	r0,a
   00A3 86 82               421 	mov	dpl,@r0
   00A5 08                  422 	inc	r0
   00A6 86 83               423 	mov	dph,@r0
   00A8 12 13 22            424 	lcall	_prvAllocateTCBAndStack
   00AB AC 82               425 	mov	r4,dpl
   00AD AD 83               426 	mov	r5,dph
   00AF AE F0               427 	mov	r6,b
                            428 ;     genAssign
   00B1 E5 12               429 	mov	a,_bp
   00B3 24 03               430 	add	a,#0x03
   00B5 F8                  431 	mov	r0,a
   00B6 A6 04               432 	mov	@r0,ar4
   00B8 08                  433 	inc	r0
   00B9 A6 05               434 	mov	@r0,ar5
   00BB 08                  435 	inc	r0
   00BC A6 06               436 	mov	@r0,ar6
                            437 ;../../Source/tasks.c:370: if( pxNewTCB != NULL )
                            438 ;     genCmpEq
   00BE E5 12               439 	mov	a,_bp
   00C0 24 03               440 	add	a,#0x03
   00C2 F8                  441 	mov	r0,a
   00C3 B6 00 0B            442 	cjne	@r0,#0x00,00135$
   00C6 08                  443 	inc	r0
   00C7 B6 00 07            444 	cjne	@r0,#0x00,00135$
   00CA 08                  445 	inc	r0
   00CB B6 00 03            446 	cjne	@r0,#0x00,00135$
   00CE 02 03 0F            447 	ljmp	00113$
   00D1                     448 00135$:
                            449 ;../../Source/tasks.c:375: prvInitialiseTCBVariables( pxNewTCB, usStackDepth, pcName, ucPriority );
                            450 ;     genIpush
   00D1 E5 12               451 	mov	a,_bp
   00D3 24 F5               452 	add	a,#0xf5
   00D5 F8                  453 	mov	r0,a
   00D6 E6                  454 	mov	a,@r0
   00D7 C0 E0               455 	push	acc
                            456 ;     genIpush
   00D9 E5 12               457 	mov	a,_bp
   00DB 24 FB               458 	add	a,#0xfb
   00DD F8                  459 	mov	r0,a
   00DE E6                  460 	mov	a,@r0
   00DF C0 E0               461 	push	acc
   00E1 08                  462 	inc	r0
   00E2 E6                  463 	mov	a,@r0
   00E3 C0 E0               464 	push	acc
   00E5 08                  465 	inc	r0
   00E6 E6                  466 	mov	a,@r0
   00E7 C0 E0               467 	push	acc
                            468 ;     genIpush
   00E9 E5 12               469 	mov	a,_bp
   00EB 24 F9               470 	add	a,#0xf9
   00ED F8                  471 	mov	r0,a
   00EE E6                  472 	mov	a,@r0
   00EF C0 E0               473 	push	acc
   00F1 08                  474 	inc	r0
   00F2 E6                  475 	mov	a,@r0
   00F3 C0 E0               476 	push	acc
                            477 ;     genCall
   00F5 E5 12               478 	mov	a,_bp
   00F7 24 03               479 	add	a,#0x03
   00F9 F8                  480 	mov	r0,a
   00FA 86 82               481 	mov	dpl,@r0
   00FC 08                  482 	inc	r0
   00FD 86 83               483 	mov	dph,@r0
   00FF 08                  484 	inc	r0
   0100 86 F0               485 	mov	b,@r0
   0102 12 10 6A            486 	lcall	_prvInitialiseTCBVariables
   0105 E5 81               487 	mov	a,sp
   0107 24 FA               488 	add	a,#0xfa
   0109 F5 81               489 	mov	sp,a
                            490 ;../../Source/tasks.c:390: pxTopOfStack = pxNewTCB->pxStack;	
                            491 ;     genPlus
   010B E5 12               492 	mov	a,_bp
   010D 24 03               493 	add	a,#0x03
   010F F8                  494 	mov	r0,a
                            495 ;     genPlusIncr
   0110 74 03               496 	mov	a,#0x03
   0112 26                  497 	add	a,@r0
   0113 FF                  498 	mov	r7,a
   0114 74 00               499 	mov	a,#0x00
   0116 08                  500 	inc	r0
   0117 36                  501 	addc	a,@r0
   0118 FA                  502 	mov	r2,a
   0119 08                  503 	inc	r0
   011A 86 03               504 	mov	ar3,@r0
                            505 ;     genPointerGet
                            506 ;     genGenPointerGet
   011C 8F 82               507 	mov	dpl,r7
   011E 8A 83               508 	mov	dph,r2
   0120 8B F0               509 	mov	b,r3
   0122 12 AE 30            510 	lcall	__gptrget
   0125 FF                  511 	mov	r7,a
   0126 A3                  512 	inc	dptr
   0127 12 AE 30            513 	lcall	__gptrget
   012A FA                  514 	mov	r2,a
   012B A3                  515 	inc	dptr
   012C 12 AE 30            516 	lcall	__gptrget
   012F FB                  517 	mov	r3,a
                            518 ;     genAssign
                            519 ;../../Source/tasks.c:398: pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack, pvTaskCode, pvParameters );
                            520 ;     genIpush
   0130 E5 12               521 	mov	a,_bp
   0132 24 F6               522 	add	a,#0xf6
   0134 F8                  523 	mov	r0,a
   0135 E6                  524 	mov	a,@r0
   0136 C0 E0               525 	push	acc
   0138 08                  526 	inc	r0
   0139 E6                  527 	mov	a,@r0
   013A C0 E0               528 	push	acc
   013C 08                  529 	inc	r0
   013D E6                  530 	mov	a,@r0
   013E C0 E0               531 	push	acc
                            532 ;     genIpush
   0140 E5 12               533 	mov	a,_bp
   0142 24 01               534 	add	a,#0x01
   0144 F8                  535 	mov	r0,a
   0145 E6                  536 	mov	a,@r0
   0146 C0 E0               537 	push	acc
   0148 08                  538 	inc	r0
   0149 E6                  539 	mov	a,@r0
   014A C0 E0               540 	push	acc
                            541 ;     genCall
   014C 8F 82               542 	mov	dpl,r7
   014E 8A 83               543 	mov	dph,r2
   0150 8B F0               544 	mov	b,r3
   0152 12 14 1B            545 	lcall	_pxPortInitialiseStack
   0155 AA 82               546 	mov	r2,dpl
   0157 AB 83               547 	mov	r3,dph
   0159 AF F0               548 	mov	r7,b
   015B E5 81               549 	mov	a,sp
   015D 24 FB               550 	add	a,#0xfb
   015F F5 81               551 	mov	sp,a
                            552 ;     genPointerSet
                            553 ;     genGenPointerSet
   0161 E5 12               554 	mov	a,_bp
   0163 24 03               555 	add	a,#0x03
   0165 F8                  556 	mov	r0,a
   0166 86 82               557 	mov	dpl,@r0
   0168 08                  558 	inc	r0
   0169 86 83               559 	mov	dph,@r0
   016B 08                  560 	inc	r0
   016C 86 F0               561 	mov	b,@r0
   016E EA                  562 	mov	a,r2
   016F 12 A3 97            563 	lcall	__gptrput
   0172 A3                  564 	inc	dptr
   0173 EB                  565 	mov	a,r3
   0174 12 A3 97            566 	lcall	__gptrput
   0177 A3                  567 	inc	dptr
   0178 EF                  568 	mov	a,r7
   0179 12 A3 97            569 	lcall	__gptrput
                            570 ;../../Source/tasks.c:402: portENTER_CRITICAL();
                            571 ;     genInline
   017C C0 E0 C0 A8         572 	 push ACC push IE 
                            573 ;     genAssign
   0180 C2 AF               574 	clr	_EA
                            575 ;../../Source/tasks.c:404: usCurrentNumberOfTasks++;
                            576 ;     genAssign
   0182 90 1D 10            577 	mov	dptr,#_usCurrentNumberOfTasks
   0185 E0                  578 	movx	a,@dptr
   0186 FA                  579 	mov	r2,a
   0187 A3                  580 	inc	dptr
   0188 E0                  581 	movx	a,@dptr
   0189 FB                  582 	mov	r3,a
                            583 ;     genPlus
   018A 90 1D 10            584 	mov	dptr,#_usCurrentNumberOfTasks
                            585 ;     genPlusIncr
   018D 74 01               586 	mov	a,#0x01
   018F 25 02               587 	add	a,ar2
   0191 F0                  588 	movx	@dptr,a
   0192 74 00               589 	mov	a,#0x00
   0194 35 03               590 	addc	a,ar3
   0196 A3                  591 	inc	dptr
   0197 F0                  592 	movx	@dptr,a
                            593 ;../../Source/tasks.c:405: if( usCurrentNumberOfTasks == ( unsigned portSHORT ) 1 )
                            594 ;     genAssign
   0198 90 1D 10            595 	mov	dptr,#_usCurrentNumberOfTasks
   019B E0                  596 	movx	a,@dptr
   019C FA                  597 	mov	r2,a
   019D A3                  598 	inc	dptr
   019E E0                  599 	movx	a,@dptr
   019F FB                  600 	mov	r3,a
                            601 ;     genCmpEq
   01A0 BA 01 05            602 	cjne	r2,#0x01,00136$
   01A3 BB 00 02            603 	cjne	r3,#0x00,00136$
   01A6 80 03               604 	sjmp	00137$
   01A8                     605 00136$:
   01A8 02 01 C7            606 	ljmp	00106$
   01AB                     607 00137$:
                            608 ;../../Source/tasks.c:408: pxCurrentTCB = ( volatile tskTCB * volatile ) pxNewTCB;
                            609 ;     genAssign
   01AB E5 12               610 	mov	a,_bp
   01AD 24 03               611 	add	a,#0x03
   01AF F8                  612 	mov	r0,a
   01B0 90 1D 0B            613 	mov	dptr,#_pxCurrentTCB
   01B3 E6                  614 	mov	a,@r0
   01B4 F0                  615 	movx	@dptr,a
   01B5 08                  616 	inc	r0
   01B6 A3                  617 	inc	dptr
   01B7 E6                  618 	mov	a,@r0
   01B8 F0                  619 	movx	@dptr,a
   01B9 08                  620 	inc	r0
   01BA A3                  621 	inc	dptr
   01BB E6                  622 	mov	a,@r0
   01BC F0                  623 	movx	@dptr,a
                            624 ;../../Source/tasks.c:413: sReturn = prvInitialiseTaskLists();
                            625 ;     genCall
   01BD 12 12 5B            626 	lcall	_prvInitialiseTaskLists
   01C0 AA 82               627 	mov	r2,dpl
   01C2 AB 83               628 	mov	r3,dph
                            629 ;     genAssign
   01C4 02 02 20            630 	ljmp	00107$
   01C7                     631 00106$:
                            632 ;../../Source/tasks.c:417: sReturn = pdPASS;
                            633 ;     genAssign
   01C7 7A 01               634 	mov	r2,#0x01
   01C9 7B 00               635 	mov	r3,#0x00
                            636 ;../../Source/tasks.c:422: if( cSchedulerRunning == pdFALSE )
                            637 ;     genAssign
   01CB 90 1D 16            638 	mov	dptr,#_cSchedulerRunning
   01CE E0                  639 	movx	a,@dptr
   01CF FF                  640 	mov	r7,a
                            641 ;     genCmpEq
   01D0 BF 00 02            642 	cjne	r7,#0x00,00138$
   01D3 80 03               643 	sjmp	00139$
   01D5                     644 00138$:
   01D5 02 02 20            645 	ljmp	00107$
   01D8                     646 00139$:
                            647 ;../../Source/tasks.c:424: if( pxCurrentTCB->ucPriority <= ucPriority )
                            648 ;     genIpush
   01D8 C0 02               649 	push	ar2
   01DA C0 03               650 	push	ar3
                            651 ;     genAssign
   01DC 90 1D 0B            652 	mov	dptr,#_pxCurrentTCB
   01DF E0                  653 	movx	a,@dptr
   01E0 FF                  654 	mov	r7,a
   01E1 A3                  655 	inc	dptr
   01E2 E0                  656 	movx	a,@dptr
   01E3 FA                  657 	mov	r2,a
   01E4 A3                  658 	inc	dptr
   01E5 E0                  659 	movx	a,@dptr
   01E6 FB                  660 	mov	r3,a
                            661 ;     genPlus
   01E7 74 18               662 	mov	a,#0x18
   01E9 25 07               663 	add	a,ar7
   01EB FF                  664 	mov	r7,a
   01EC 74 00               665 	mov	a,#0x00
   01EE 35 02               666 	addc	a,ar2
   01F0 FA                  667 	mov	r2,a
                            668 ;     genPointerGet
                            669 ;     genGenPointerGet
   01F1 8F 82               670 	mov	dpl,r7
   01F3 8A 83               671 	mov	dph,r2
   01F5 8B F0               672 	mov	b,r3
   01F7 12 AE 30            673 	lcall	__gptrget
   01FA FF                  674 	mov	r7,a
                            675 ;     genCmpGt
   01FB E5 12               676 	mov	a,_bp
   01FD 24 F5               677 	add	a,#0xf5
   01FF F8                  678 	mov	r0,a
                            679 ;     genCmp
   0200 C3                  680 	clr	c
   0201 E6                  681 	mov	a,@r0
   0202 9F                  682 	subb	a,r7
   0203 E4                  683 	clr	a
   0204 33                  684 	rlc	a
                            685 ;     genIpop
   0205 D0 03               686 	pop	ar3
   0207 D0 02               687 	pop	ar2
                            688 ;     genIfx
                            689 ;     genIfxJump
   0209 60 03               690 	jz	00140$
   020B 02 02 20            691 	ljmp	00107$
   020E                     692 00140$:
                            693 ;../../Source/tasks.c:426: pxCurrentTCB = ( volatile tskTCB * volatile ) pxNewTCB;	
                            694 ;     genAssign
   020E E5 12               695 	mov	a,_bp
   0210 24 03               696 	add	a,#0x03
   0212 F8                  697 	mov	r0,a
   0213 90 1D 0B            698 	mov	dptr,#_pxCurrentTCB
   0216 E6                  699 	mov	a,@r0
   0217 F0                  700 	movx	@dptr,a
   0218 08                  701 	inc	r0
   0219 A3                  702 	inc	dptr
   021A E6                  703 	mov	a,@r0
   021B F0                  704 	movx	@dptr,a
   021C 08                  705 	inc	r0
   021D A3                  706 	inc	dptr
   021E E6                  707 	mov	a,@r0
   021F F0                  708 	movx	@dptr,a
   0220                     709 00107$:
                            710 ;../../Source/tasks.c:433: if( pxNewTCB->ucPriority > ucTopUsedPriority )
                            711 ;     genIpush
   0220 C0 02               712 	push	ar2
   0222 C0 03               713 	push	ar3
                            714 ;     genPlus
   0224 E5 12               715 	mov	a,_bp
   0226 24 03               716 	add	a,#0x03
   0228 F8                  717 	mov	r0,a
   0229 74 18               718 	mov	a,#0x18
   022B 26                  719 	add	a,@r0
   022C FF                  720 	mov	r7,a
   022D 74 00               721 	mov	a,#0x00
   022F 08                  722 	inc	r0
   0230 36                  723 	addc	a,@r0
   0231 FA                  724 	mov	r2,a
   0232 08                  725 	inc	r0
   0233 86 03               726 	mov	ar3,@r0
                            727 ;     genPointerGet
                            728 ;     genGenPointerGet
   0235 8F 82               729 	mov	dpl,r7
   0237 8A 83               730 	mov	dph,r2
   0239 8B F0               731 	mov	b,r3
   023B 12 AE 30            732 	lcall	__gptrget
   023E FD                  733 	mov	r5,a
                            734 ;     genAssign
   023F 90 1D 14            735 	mov	dptr,#_ucTopUsedPriority
   0242 E0                  736 	movx	a,@dptr
   0243 FA                  737 	mov	r2,a
                            738 ;     genCmpGt
                            739 ;     genCmp
   0244 C3                  740 	clr	c
   0245 EA                  741 	mov	a,r2
   0246 9D                  742 	subb	a,r5
   0247 E4                  743 	clr	a
   0248 33                  744 	rlc	a
                            745 ;     genIpop
   0249 D0 03               746 	pop	ar3
   024B D0 02               747 	pop	ar2
                            748 ;     genIfx
                            749 ;     genIfxJump
   024D 70 03               750 	jnz	00141$
   024F 02 02 57            751 	ljmp	00109$
   0252                     752 00141$:
                            753 ;../../Source/tasks.c:435: ucTopUsedPriority = pxNewTCB->ucPriority;
                            754 ;     genAssign
   0252 90 1D 14            755 	mov	dptr,#_ucTopUsedPriority
   0255 ED                  756 	mov	a,r5
   0256 F0                  757 	movx	@dptr,a
   0257                     758 00109$:
                            759 ;../../Source/tasks.c:439: pxNewTCB->ucTCBNumber = ucTaskNumber;
                            760 ;     genIpush
   0257 C0 02               761 	push	ar2
   0259 C0 03               762 	push	ar3
                            763 ;     genPlus
   025B E5 12               764 	mov	a,_bp
   025D 24 03               765 	add	a,#0x03
   025F F8                  766 	mov	r0,a
   0260 74 35               767 	mov	a,#0x35
   0262 26                  768 	add	a,@r0
   0263 FF                  769 	mov	r7,a
   0264 74 00               770 	mov	a,#0x00
   0266 08                  771 	inc	r0
   0267 36                  772 	addc	a,@r0
   0268 FA                  773 	mov	r2,a
   0269 08                  774 	inc	r0
   026A 86 03               775 	mov	ar3,@r0
                            776 ;     genAssign
   026C 90 00 A0            777 	mov	dptr,#_sTaskCreate_ucTaskNumber_1_1
   026F E0                  778 	movx	a,@dptr
   0270 FC                  779 	mov	r4,a
                            780 ;     genPointerSet
                            781 ;     genGenPointerSet
   0271 8F 82               782 	mov	dpl,r7
   0273 8A 83               783 	mov	dph,r2
   0275 8B F0               784 	mov	b,r3
   0277 EC                  785 	mov	a,r4
   0278 12 A3 97            786 	lcall	__gptrput
                            787 ;../../Source/tasks.c:440: ucTaskNumber++;
                            788 ;     genPlus
   027B 90 00 A0            789 	mov	dptr,#_sTaskCreate_ucTaskNumber_1_1
                            790 ;     genPlusIncr
   027E 74 01               791 	mov	a,#0x01
   0280 25 04               792 	add	a,ar4
   0282 F0                  793 	movx	@dptr,a
                            794 ;../../Source/tasks.c:442: prvAddTaskToReadyQueue( pxNewTCB );
                            795 ;     genPlus
   0283 E5 12               796 	mov	a,_bp
   0285 24 03               797 	add	a,#0x03
   0287 F8                  798 	mov	r0,a
   0288 E5 12               799 	mov	a,_bp
   028A 24 06               800 	add	a,#0x06
   028C F9                  801 	mov	r1,a
   028D 74 19               802 	mov	a,#0x19
   028F 26                  803 	add	a,@r0
   0290 F7                  804 	mov	@r1,a
   0291 74 00               805 	mov	a,#0x00
   0293 08                  806 	inc	r0
   0294 36                  807 	addc	a,@r0
   0295 09                  808 	inc	r1
   0296 F7                  809 	mov	@r1,a
   0297 08                  810 	inc	r0
   0298 09                  811 	inc	r1
   0299 E6                  812 	mov	a,@r0
   029A F7                  813 	mov	@r1,a
                            814 ;     genPointerSet
                            815 ;     genGenPointerSet
   029B E5 12               816 	mov	a,_bp
   029D 24 06               817 	add	a,#0x06
   029F F8                  818 	mov	r0,a
   02A0 86 82               819 	mov	dpl,@r0
   02A2 08                  820 	inc	r0
   02A3 86 83               821 	mov	dph,@r0
   02A5 08                  822 	inc	r0
   02A6 86 F0               823 	mov	b,@r0
   02A8 74 00               824 	mov	a,#0x00
   02AA 12 A3 97            825 	lcall	__gptrput
   02AD A3                  826 	inc	dptr
   02AE 74 00               827 	mov	a,#0x00
   02B0 12 A3 97            828 	lcall	__gptrput
                            829 ;     genAssign
   02B3 90 1D 15            830 	mov	dptr,#_ucTopReadyPriority
   02B6 E0                  831 	movx	a,@dptr
   02B7 FA                  832 	mov	r2,a
                            833 ;     genCmpGt
                            834 ;     genCmp
   02B8 C3                  835 	clr	c
   02B9 EA                  836 	mov	a,r2
   02BA 9D                  837 	subb	a,r5
   02BB E4                  838 	clr	a
   02BC 33                  839 	rlc	a
                            840 ;     genIpop
   02BD D0 03               841 	pop	ar3
   02BF D0 02               842 	pop	ar2
                            843 ;     genIfx
                            844 ;     genIfxJump
   02C1 70 03               845 	jnz	00142$
   02C3 02 02 CB            846 	ljmp	00111$
   02C6                     847 00142$:
                            848 ;     genAssign
   02C6 90 1D 15            849 	mov	dptr,#_ucTopReadyPriority
   02C9 ED                  850 	mov	a,r5
   02CA F0                  851 	movx	@dptr,a
   02CB                     852 00111$:
                            853 ;     genMult
                            854 ;     genMultOneByte
   02CB ED                  855 	mov	a,r5
   02CC 75 F0 16            856 	mov	b,#0x16
   02CF A4                  857 	mul	ab
                            858 ;     genPlus
   02D0 24 00               859 	add	a,#_pxReadyTasksLists
   02D2 FC                  860 	mov	r4,a
   02D3 E5 F0               861 	mov	a,b
   02D5 34 00               862 	addc	a,#(_pxReadyTasksLists >> 8)
   02D7 FD                  863 	mov	r5,a
                            864 ;     genCast
   02D8 7E 01               865 	mov	r6,#0x1
                            866 ;     genIpush
   02DA C0 02               867 	push	ar2
   02DC C0 03               868 	push	ar3
   02DE E5 12               869 	mov	a,_bp
   02E0 24 06               870 	add	a,#0x06
   02E2 F8                  871 	mov	r0,a
   02E3 E6                  872 	mov	a,@r0
   02E4 C0 E0               873 	push	acc
   02E6 08                  874 	inc	r0
   02E7 E6                  875 	mov	a,@r0
   02E8 C0 E0               876 	push	acc
   02EA 08                  877 	inc	r0
   02EB E6                  878 	mov	a,@r0
   02EC C0 E0               879 	push	acc
                            880 ;     genCall
   02EE 8C 82               881 	mov	dpl,r4
   02F0 8D 83               882 	mov	dph,r5
   02F2 8E F0               883 	mov	b,r6
   02F4 12 2A F6            884 	lcall	_vListInsertEnd
   02F7 15 81               885 	dec	sp
   02F9 15 81               886 	dec	sp
   02FB 15 81               887 	dec	sp
   02FD D0 03               888 	pop	ar3
   02FF D0 02               889 	pop	ar2
                            890 ;../../Source/tasks.c:444: portEXIT_CRITICAL();
                            891 ;     genInline
   0301 D0 E0               892 	 pop ACC 
                            893 ;     genAnd
   0303 53 E0 80            894 	anl	_ACC,#0x80
                            895 ;     genOr
   0306 E5 E0               896 	mov	a,_ACC
   0308 42 A8               897 	orl	_IE,a
                            898 ;     genInline
   030A D0 E0               899 	 pop ACC 
   030C 02 03 13            900 	ljmp	00114$
   030F                     901 00113$:
                            902 ;../../Source/tasks.c:448: sReturn = errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY;
                            903 ;     genAssign
   030F 7A FF               904 	mov	r2,#0xFF
   0311 7B FF               905 	mov	r3,#0xFF
   0313                     906 00114$:
                            907 ;../../Source/tasks.c:451: if( sReturn == pdPASS )
                            908 ;     genCmpEq
   0313 BA 01 05            909 	cjne	r2,#0x01,00143$
   0316 BB 00 02            910 	cjne	r3,#0x00,00143$
   0319 80 03               911 	sjmp	00144$
   031B                     912 00143$:
   031B 02 03 8C            913 	ljmp	00122$
   031E                     914 00144$:
                            915 ;../../Source/tasks.c:453: if( ( void * ) pxCreatedTask != NULL )
                            916 ;     genAssign
   031E E5 12               917 	mov	a,_bp
   0320 24 F2               918 	add	a,#0xf2
   0322 F8                  919 	mov	r0,a
   0323 86 04               920 	mov	ar4,@r0
   0325 08                  921 	inc	r0
   0326 86 05               922 	mov	ar5,@r0
   0328 08                  923 	inc	r0
   0329 86 06               924 	mov	ar6,@r0
                            925 ;     genCmpEq
   032B BC 00 09            926 	cjne	r4,#0x00,00145$
   032E BD 00 06            927 	cjne	r5,#0x00,00145$
   0331 BE 00 03            928 	cjne	r6,#0x00,00145$
   0334 02 03 52            929 	ljmp	00116$
   0337                     930 00145$:
                            931 ;../../Source/tasks.c:458: *pxCreatedTask = ( xTaskHandle ) pxNewTCB;
                            932 ;     genPointerSet
                            933 ;     genGenPointerSet
   0337 8C 82               934 	mov	dpl,r4
   0339 8D 83               935 	mov	dph,r5
   033B 8E F0               936 	mov	b,r6
   033D E5 12               937 	mov	a,_bp
   033F 24 03               938 	add	a,#0x03
   0341 F8                  939 	mov	r0,a
   0342 E6                  940 	mov	a,@r0
   0343 12 A3 97            941 	lcall	__gptrput
   0346 A3                  942 	inc	dptr
   0347 08                  943 	inc	r0
   0348 E6                  944 	mov	a,@r0
   0349 12 A3 97            945 	lcall	__gptrput
   034C A3                  946 	inc	dptr
   034D 08                  947 	inc	r0
   034E E6                  948 	mov	a,@r0
   034F 12 A3 97            949 	lcall	__gptrput
   0352                     950 00116$:
                            951 ;../../Source/tasks.c:461: if( cSchedulerRunning != pdFALSE )
                            952 ;     genAssign
   0352 90 1D 16            953 	mov	dptr,#_cSchedulerRunning
   0355 E0                  954 	movx	a,@dptr
   0356 FC                  955 	mov	r4,a
                            956 ;     genCmpEq
   0357 BC 00 03            957 	cjne	r4,#0x00,00146$
   035A 02 03 8C            958 	ljmp	00122$
   035D                     959 00146$:
                            960 ;../../Source/tasks.c:465: if( pxCurrentTCB->ucPriority < ucPriority )
                            961 ;     genAssign
   035D 90 1D 0B            962 	mov	dptr,#_pxCurrentTCB
   0360 E0                  963 	movx	a,@dptr
   0361 FC                  964 	mov	r4,a
   0362 A3                  965 	inc	dptr
   0363 E0                  966 	movx	a,@dptr
   0364 FD                  967 	mov	r5,a
   0365 A3                  968 	inc	dptr
   0366 E0                  969 	movx	a,@dptr
   0367 FE                  970 	mov	r6,a
                            971 ;     genPlus
   0368 74 18               972 	mov	a,#0x18
   036A 25 04               973 	add	a,ar4
   036C FC                  974 	mov	r4,a
   036D 74 00               975 	mov	a,#0x00
   036F 35 05               976 	addc	a,ar5
   0371 FD                  977 	mov	r5,a
                            978 ;     genPointerGet
                            979 ;     genGenPointerGet
   0372 8C 82               980 	mov	dpl,r4
   0374 8D 83               981 	mov	dph,r5
   0376 8E F0               982 	mov	b,r6
   0378 12 AE 30            983 	lcall	__gptrget
   037B FC                  984 	mov	r4,a
                            985 ;     genCmpLt
   037C E5 12               986 	mov	a,_bp
   037E 24 F5               987 	add	a,#0xf5
   0380 F8                  988 	mov	r0,a
                            989 ;     genCmp
   0381 C3                  990 	clr	c
   0382 EC                  991 	mov	a,r4
   0383 96                  992 	subb	a,@r0
                            993 ;     genIfxJump
   0384 40 03               994 	jc	00147$
   0386 02 03 8C            995 	ljmp	00122$
   0389                     996 00147$:
                            997 ;../../Source/tasks.c:467: taskYIELD();
                            998 ;     genCall
   0389 12 17 01            999 	lcall	_vPortYield
   038C                    1000 00122$:
                           1001 ;../../Source/tasks.c:472: return sReturn;
                           1002 ;     genRet
   038C 8A 82              1003 	mov	dpl,r2
   038E 8B 83              1004 	mov	dph,r3
   0390                    1005 00123$:
   0390 85 12 81           1006 	mov	sp,_bp
   0393 D0 12              1007 	pop	_bp
   0395 22                 1008 	ret
                           1009 ;------------------------------------------------------------
                           1010 ;Allocation info for local variables in function 'vTaskDelayUntil'
                           1011 ;------------------------------------------------------------
                           1012 ;xTimeIncrement            Allocated to stack - offset -4
                           1013 ;pxPreviousWakeTime        Allocated to stack - offset 1
                           1014 ;xTimeToWake               Allocated to registers r3 r2 
                           1015 ;cAlreadyYielded           Allocated to registers r2 
                           1016 ;cShouldDelay              Allocated to stack - offset 4
                           1017 ;------------------------------------------------------------
                           1018 ;../../Source/tasks.c:522: void vTaskDelayUntil( portTickType *pxPreviousWakeTime, portTickType xTimeIncrement )
                           1019 ;	-----------------------------------------
                           1020 ;	 function vTaskDelayUntil
                           1021 ;	-----------------------------------------
   0396                    1022 _vTaskDelayUntil:
   0396 C0 12              1023 	push	_bp
   0398 85 81 12           1024 	mov	_bp,sp
                           1025 ;     genReceive
   039B C0 82              1026 	push	dpl
   039D C0 83              1027 	push	dph
   039F C0 F0              1028 	push	b
   03A1 05 81              1029 	inc	sp
                           1030 ;../../Source/tasks.c:525: portCHAR cAlreadyYielded, cShouldDelay = ( portCHAR ) pdFALSE;
                           1031 ;     genAssign
   03A3 E5 12              1032 	mov	a,_bp
   03A5 24 04              1033 	add	a,#0x04
   03A7 F8                 1034 	mov	r0,a
   03A8 76 00              1035 	mov	@r0,#0x00
                           1036 ;../../Source/tasks.c:527: vTaskSuspendAll();
                           1037 ;     genCall
   03AA 12 06 94           1038 	lcall	_vTaskSuspendAll
                           1039 ;../../Source/tasks.c:530: xTimeToWake = *pxPreviousWakeTime + xTimeIncrement;
                           1040 ;     genPointerGet
                           1041 ;     genGenPointerGet
   03AD E5 12              1042 	mov	a,_bp
   03AF 24 01              1043 	add	a,#0x01
   03B1 F8                 1044 	mov	r0,a
   03B2 86 82              1045 	mov	dpl,@r0
   03B4 08                 1046 	inc	r0
   03B5 86 83              1047 	mov	dph,@r0
   03B7 08                 1048 	inc	r0
   03B8 86 F0              1049 	mov	b,@r0
   03BA 12 AE 30           1050 	lcall	__gptrget
   03BD FE                 1051 	mov	r6,a
   03BE A3                 1052 	inc	dptr
   03BF 12 AE 30           1053 	lcall	__gptrget
   03C2 FF                 1054 	mov	r7,a
                           1055 ;     genPlus
   03C3 E5 12              1056 	mov	a,_bp
   03C5 24 FC              1057 	add	a,#0xfc
   03C7 F8                 1058 	mov	r0,a
   03C8 E6                 1059 	mov	a,@r0
   03C9 25 06              1060 	add	a,ar6
   03CB FD                 1061 	mov	r5,a
   03CC 08                 1062 	inc	r0
   03CD E6                 1063 	mov	a,@r0
   03CE 35 07              1064 	addc	a,ar7
   03D0 FA                 1065 	mov	r2,a
                           1066 ;     genAssign
   03D1 8D 03              1067 	mov	ar3,r5
                           1068 ;../../Source/tasks.c:532: if( xTickCount < *pxPreviousWakeTime )
                           1069 ;     genAssign
   03D3 90 1D 12           1070 	mov	dptr,#_xTickCount
   03D6 E0                 1071 	movx	a,@dptr
   03D7 FC                 1072 	mov	r4,a
   03D8 A3                 1073 	inc	dptr
   03D9 E0                 1074 	movx	a,@dptr
   03DA FD                 1075 	mov	r5,a
                           1076 ;     genCmpLt
                           1077 ;     genCmp
   03DB C3                 1078 	clr	c
   03DC EC                 1079 	mov	a,r4
   03DD 9E                 1080 	subb	a,r6
   03DE ED                 1081 	mov	a,r5
   03DF 9F                 1082 	subb	a,r7
                           1083 ;     genIfxJump
   03E0 40 03              1084 	jc	00126$
   03E2 02 04 0B           1085 	ljmp	00108$
   03E5                    1086 00126$:
                           1087 ;../../Source/tasks.c:539: if( ( xTimeToWake < *pxPreviousWakeTime ) && ( xTimeToWake > xTickCount ) )
                           1088 ;     genCmpLt
                           1089 ;     genCmp
   03E5 C3                 1090 	clr	c
   03E6 EB                 1091 	mov	a,r3
   03E7 9E                 1092 	subb	a,r6
   03E8 EA                 1093 	mov	a,r2
   03E9 9F                 1094 	subb	a,r7
                           1095 ;     genIfxJump
   03EA 40 03              1096 	jc	00127$
   03EC 02 04 2E           1097 	ljmp	00109$
   03EF                    1098 00127$:
                           1099 ;     genAssign
   03EF 90 1D 12           1100 	mov	dptr,#_xTickCount
   03F2 E0                 1101 	movx	a,@dptr
   03F3 FC                 1102 	mov	r4,a
   03F4 A3                 1103 	inc	dptr
   03F5 E0                 1104 	movx	a,@dptr
   03F6 FD                 1105 	mov	r5,a
                           1106 ;     genCmpGt
                           1107 ;     genCmp
   03F7 C3                 1108 	clr	c
   03F8 EC                 1109 	mov	a,r4
   03F9 9B                 1110 	subb	a,r3
   03FA ED                 1111 	mov	a,r5
   03FB 9A                 1112 	subb	a,r2
                           1113 ;     genIfxJump
   03FC 40 03              1114 	jc	00128$
   03FE 02 04 2E           1115 	ljmp	00109$
   0401                    1116 00128$:
                           1117 ;../../Source/tasks.c:541: cShouldDelay = ( portCHAR ) pdTRUE;
                           1118 ;     genAssign
   0401 E5 12              1119 	mov	a,_bp
   0403 24 04              1120 	add	a,#0x04
   0405 F8                 1121 	mov	r0,a
   0406 76 01              1122 	mov	@r0,#0x01
   0408 02 04 2E           1123 	ljmp	00109$
   040B                    1124 00108$:
                           1125 ;../../Source/tasks.c:549: if( ( xTimeToWake < *pxPreviousWakeTime ) || ( xTimeToWake > xTickCount ) )
                           1126 ;     genCmpLt
                           1127 ;     genCmp
   040B C3                 1128 	clr	c
   040C EB                 1129 	mov	a,r3
   040D 9E                 1130 	subb	a,r6
   040E EA                 1131 	mov	a,r2
   040F 9F                 1132 	subb	a,r7
                           1133 ;     genIfxJump
   0410 50 03              1134 	jnc	00129$
   0412 02 04 27           1135 	ljmp	00104$
   0415                    1136 00129$:
                           1137 ;     genAssign
   0415 90 1D 12           1138 	mov	dptr,#_xTickCount
   0418 E0                 1139 	movx	a,@dptr
   0419 FC                 1140 	mov	r4,a
   041A A3                 1141 	inc	dptr
   041B E0                 1142 	movx	a,@dptr
   041C FD                 1143 	mov	r5,a
                           1144 ;     genCmpGt
                           1145 ;     genCmp
   041D C3                 1146 	clr	c
   041E EC                 1147 	mov	a,r4
   041F 9B                 1148 	subb	a,r3
   0420 ED                 1149 	mov	a,r5
   0421 9A                 1150 	subb	a,r2
                           1151 ;     genIfxJump
   0422 40 03              1152 	jc	00130$
   0424 02 04 2E           1153 	ljmp	00109$
   0427                    1154 00130$:
   0427                    1155 00104$:
                           1156 ;../../Source/tasks.c:551: cShouldDelay = ( portCHAR ) pdTRUE;
                           1157 ;     genAssign
   0427 E5 12              1158 	mov	a,_bp
   0429 24 04              1159 	add	a,#0x04
   042B F8                 1160 	mov	r0,a
   042C 76 01              1161 	mov	@r0,#0x01
   042E                    1162 00109$:
                           1163 ;../../Source/tasks.c:556: *pxPreviousWakeTime = xTimeToWake;
                           1164 ;     genPointerSet
                           1165 ;     genGenPointerSet
   042E E5 12              1166 	mov	a,_bp
   0430 24 01              1167 	add	a,#0x01
   0432 F8                 1168 	mov	r0,a
   0433 86 82              1169 	mov	dpl,@r0
   0435 08                 1170 	inc	r0
   0436 86 83              1171 	mov	dph,@r0
   0438 08                 1172 	inc	r0
   0439 86 F0              1173 	mov	b,@r0
   043B EB                 1174 	mov	a,r3
   043C 12 A3 97           1175 	lcall	__gptrput
   043F A3                 1176 	inc	dptr
   0440 EA                 1177 	mov	a,r2
   0441 12 A3 97           1178 	lcall	__gptrput
                           1179 ;../../Source/tasks.c:558: if( cShouldDelay )
                           1180 ;     genIfx
   0444 E5 12              1181 	mov	a,_bp
   0446 24 04              1182 	add	a,#0x04
   0448 F8                 1183 	mov	r0,a
   0449 E6                 1184 	mov	a,@r0
                           1185 ;     genIfxJump
   044A 70 03              1186 	jnz	00131$
   044C 02 05 18           1187 	ljmp	00114$
   044F                    1188 00131$:
                           1189 ;../../Source/tasks.c:563: vListRemove( ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
                           1190 ;     genAssign
   044F 90 1D 0B           1191 	mov	dptr,#_pxCurrentTCB
   0452 E0                 1192 	movx	a,@dptr
   0453 FC                 1193 	mov	r4,a
   0454 A3                 1194 	inc	dptr
   0455 E0                 1195 	movx	a,@dptr
   0456 FD                 1196 	mov	r5,a
   0457 A3                 1197 	inc	dptr
   0458 E0                 1198 	movx	a,@dptr
   0459 FE                 1199 	mov	r6,a
                           1200 ;     genPlus
   045A 74 19              1201 	mov	a,#0x19
   045C 25 04              1202 	add	a,ar4
   045E FC                 1203 	mov	r4,a
   045F 74 00              1204 	mov	a,#0x00
   0461 35 05              1205 	addc	a,ar5
   0463 FD                 1206 	mov	r5,a
                           1207 ;     genCall
   0464 8C 82              1208 	mov	dpl,r4
   0466 8D 83              1209 	mov	dph,r5
   0468 8E F0              1210 	mov	b,r6
   046A C0 02              1211 	push	ar2
   046C C0 03              1212 	push	ar3
   046E 12 30 07           1213 	lcall	_vListRemove
   0471 D0 03              1214 	pop	ar3
   0473 D0 02              1215 	pop	ar2
                           1216 ;../../Source/tasks.c:566: listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xGenericListItem ), xTimeToWake );
                           1217 ;     genAssign
   0475 90 1D 0B           1218 	mov	dptr,#_pxCurrentTCB
   0478 E0                 1219 	movx	a,@dptr
   0479 FC                 1220 	mov	r4,a
   047A A3                 1221 	inc	dptr
   047B E0                 1222 	movx	a,@dptr
   047C FD                 1223 	mov	r5,a
   047D A3                 1224 	inc	dptr
   047E E0                 1225 	movx	a,@dptr
   047F FE                 1226 	mov	r6,a
                           1227 ;     genPlus
   0480 74 19              1228 	mov	a,#0x19
   0482 25 04              1229 	add	a,ar4
   0484 FC                 1230 	mov	r4,a
   0485 74 00              1231 	mov	a,#0x00
   0487 35 05              1232 	addc	a,ar5
   0489 FD                 1233 	mov	r5,a
                           1234 ;     genPointerSet
                           1235 ;     genGenPointerSet
   048A 8C 82              1236 	mov	dpl,r4
   048C 8D 83              1237 	mov	dph,r5
   048E 8E F0              1238 	mov	b,r6
   0490 EB                 1239 	mov	a,r3
   0491 12 A3 97           1240 	lcall	__gptrput
   0494 A3                 1241 	inc	dptr
   0495 EA                 1242 	mov	a,r2
   0496 12 A3 97           1243 	lcall	__gptrput
                           1244 ;../../Source/tasks.c:568: if( xTimeToWake < xTickCount )
                           1245 ;     genAssign
   0499 90 1D 12           1246 	mov	dptr,#_xTickCount
   049C E0                 1247 	movx	a,@dptr
   049D FC                 1248 	mov	r4,a
   049E A3                 1249 	inc	dptr
   049F E0                 1250 	movx	a,@dptr
   04A0 FD                 1251 	mov	r5,a
                           1252 ;     genCmpLt
                           1253 ;     genCmp
   04A1 C3                 1254 	clr	c
   04A2 EB                 1255 	mov	a,r3
   04A3 9C                 1256 	subb	a,r4
   04A4 EA                 1257 	mov	a,r2
   04A5 9D                 1258 	subb	a,r5
                           1259 ;     genIfxJump
   04A6 40 03              1260 	jc	00132$
   04A8 02 04 E3           1261 	ljmp	00111$
   04AB                    1262 00132$:
                           1263 ;../../Source/tasks.c:572: vListInsert( ( xList * ) pxOverflowDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
                           1264 ;     genAssign
   04AB 90 1D 0B           1265 	mov	dptr,#_pxCurrentTCB
   04AE E0                 1266 	movx	a,@dptr
   04AF FA                 1267 	mov	r2,a
   04B0 A3                 1268 	inc	dptr
   04B1 E0                 1269 	movx	a,@dptr
   04B2 FB                 1270 	mov	r3,a
   04B3 A3                 1271 	inc	dptr
   04B4 E0                 1272 	movx	a,@dptr
   04B5 FC                 1273 	mov	r4,a
                           1274 ;     genPlus
   04B6 74 19              1275 	mov	a,#0x19
   04B8 25 02              1276 	add	a,ar2
   04BA FA                 1277 	mov	r2,a
   04BB 74 00              1278 	mov	a,#0x00
   04BD 35 03              1279 	addc	a,ar3
   04BF FB                 1280 	mov	r3,a
                           1281 ;     genAssign
   04C0 90 00 87           1282 	mov	dptr,#_pxOverflowDelayedTaskList
   04C3 E0                 1283 	movx	a,@dptr
   04C4 FD                 1284 	mov	r5,a
   04C5 A3                 1285 	inc	dptr
   04C6 E0                 1286 	movx	a,@dptr
   04C7 FE                 1287 	mov	r6,a
   04C8 A3                 1288 	inc	dptr
   04C9 E0                 1289 	movx	a,@dptr
   04CA FF                 1290 	mov	r7,a
                           1291 ;     genIpush
   04CB C0 02              1292 	push	ar2
   04CD C0 03              1293 	push	ar3
   04CF C0 04              1294 	push	ar4
                           1295 ;     genCall
   04D1 8D 82              1296 	mov	dpl,r5
   04D3 8E 83              1297 	mov	dph,r6
   04D5 8F F0              1298 	mov	b,r7
   04D7 12 2C E1           1299 	lcall	_vListInsert
   04DA 15 81              1300 	dec	sp
   04DC 15 81              1301 	dec	sp
   04DE 15 81              1302 	dec	sp
   04E0 02 05 18           1303 	ljmp	00114$
   04E3                    1304 00111$:
                           1305 ;../../Source/tasks.c:578: vListInsert( ( xList * ) pxDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
                           1306 ;     genAssign
   04E3 90 1D 0B           1307 	mov	dptr,#_pxCurrentTCB
   04E6 E0                 1308 	movx	a,@dptr
   04E7 FA                 1309 	mov	r2,a
   04E8 A3                 1310 	inc	dptr
   04E9 E0                 1311 	movx	a,@dptr
   04EA FB                 1312 	mov	r3,a
   04EB A3                 1313 	inc	dptr
   04EC E0                 1314 	movx	a,@dptr
   04ED FC                 1315 	mov	r4,a
                           1316 ;     genPlus
   04EE 74 19              1317 	mov	a,#0x19
   04F0 25 02              1318 	add	a,ar2
   04F2 FA                 1319 	mov	r2,a
   04F3 74 00              1320 	mov	a,#0x00
   04F5 35 03              1321 	addc	a,ar3
   04F7 FB                 1322 	mov	r3,a
                           1323 ;     genAssign
   04F8 90 00 84           1324 	mov	dptr,#_pxDelayedTaskList
   04FB E0                 1325 	movx	a,@dptr
   04FC FD                 1326 	mov	r5,a
   04FD A3                 1327 	inc	dptr
   04FE E0                 1328 	movx	a,@dptr
   04FF FE                 1329 	mov	r6,a
   0500 A3                 1330 	inc	dptr
   0501 E0                 1331 	movx	a,@dptr
   0502 FF                 1332 	mov	r7,a
                           1333 ;     genIpush
   0503 C0 02              1334 	push	ar2
   0505 C0 03              1335 	push	ar3
   0507 C0 04              1336 	push	ar4
                           1337 ;     genCall
   0509 8D 82              1338 	mov	dpl,r5
   050B 8E 83              1339 	mov	dph,r6
   050D 8F F0              1340 	mov	b,r7
   050F 12 2C E1           1341 	lcall	_vListInsert
   0512 15 81              1342 	dec	sp
   0514 15 81              1343 	dec	sp
   0516 15 81              1344 	dec	sp
   0518                    1345 00114$:
                           1346 ;../../Source/tasks.c:582: cAlreadyYielded = cTaskResumeAll();
                           1347 ;     genCall
   0518 12 06 B7           1348 	lcall	_cTaskResumeAll
   051B AA 82              1349 	mov	r2,dpl
                           1350 ;     genAssign
                           1351 ;../../Source/tasks.c:586: if( !cAlreadyYielded )
                           1352 ;     genIfx
   051D EA                 1353 	mov	a,r2
                           1354 ;     genIfxJump
   051E 60 03              1355 	jz	00133$
   0520 02 05 26           1356 	ljmp	00117$
   0523                    1357 00133$:
                           1358 ;../../Source/tasks.c:588: taskYIELD(); 
                           1359 ;     genCall
   0523 12 17 01           1360 	lcall	_vPortYield
   0526                    1361 00117$:
   0526 85 12 81           1362 	mov	sp,_bp
   0529 D0 12              1363 	pop	_bp
   052B 22                 1364 	ret
                           1365 ;------------------------------------------------------------
                           1366 ;Allocation info for local variables in function 'vTaskDelay'
                           1367 ;------------------------------------------------------------
                           1368 ;xTicksToDelay             Allocated to registers r2 r3 
                           1369 ;xTimeToWake               Allocated to registers r2 r3 
                           1370 ;cAlreadyYielded           Allocated to registers r4 
                           1371 ;sloc0                     Allocated to stack - offset 6
                           1372 ;------------------------------------------------------------
                           1373 ;../../Source/tasks.c:595: void vTaskDelay( portTickType xTicksToDelay )
                           1374 ;	-----------------------------------------
                           1375 ;	 function vTaskDelay
                           1376 ;	-----------------------------------------
   052C                    1377 _vTaskDelay:
   052C C0 12              1378 	push	_bp
   052E 85 81 12           1379 	mov	_bp,sp
                           1380 ;     genReceive
   0531 AA 82              1381 	mov	r2,dpl
   0533 AB 83              1382 	mov	r3,dph
                           1383 ;../../Source/tasks.c:598: signed portCHAR cAlreadyYielded = pdFALSE;
                           1384 ;     genAssign
   0535 7C 00              1385 	mov	r4,#0x00
                           1386 ;../../Source/tasks.c:601: if( xTicksToDelay > ( portTickType ) 0 )
                           1387 ;     genIfx
   0537 EA                 1388 	mov	a,r2
   0538 4B                 1389 	orl	a,r3
                           1390 ;     genIfxJump
   0539 70 03              1391 	jnz	00113$
   053B 02 06 2B           1392 	ljmp	00105$
   053E                    1393 00113$:
                           1394 ;../../Source/tasks.c:603: vTaskSuspendAll();
                           1395 ;     genCall
   053E C0 02              1396 	push	ar2
   0540 C0 03              1397 	push	ar3
   0542 12 06 94           1398 	lcall	_vTaskSuspendAll
   0545 D0 03              1399 	pop	ar3
   0547 D0 02              1400 	pop	ar2
                           1401 ;../../Source/tasks.c:615: xTimeToWake = xTickCount + xTicksToDelay;
                           1402 ;     genAssign
   0549 90 1D 12           1403 	mov	dptr,#_xTickCount
   054C E0                 1404 	movx	a,@dptr
   054D FD                 1405 	mov	r5,a
   054E A3                 1406 	inc	dptr
   054F E0                 1407 	movx	a,@dptr
   0550 FE                 1408 	mov	r6,a
                           1409 ;     genPlus
   0551 E5 02              1410 	mov	a,ar2
   0553 25 05              1411 	add	a,ar5
   0555 FA                 1412 	mov	r2,a
   0556 E5 03              1413 	mov	a,ar3
   0558 35 06              1414 	addc	a,ar6
   055A FB                 1415 	mov	r3,a
                           1416 ;     genAssign
                           1417 ;../../Source/tasks.c:620: vListRemove( ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
                           1418 ;     genAssign
   055B 90 1D 0B           1419 	mov	dptr,#_pxCurrentTCB
   055E E0                 1420 	movx	a,@dptr
   055F FD                 1421 	mov	r5,a
   0560 A3                 1422 	inc	dptr
   0561 E0                 1423 	movx	a,@dptr
   0562 FE                 1424 	mov	r6,a
   0563 A3                 1425 	inc	dptr
   0564 E0                 1426 	movx	a,@dptr
   0565 FF                 1427 	mov	r7,a
                           1428 ;     genPlus
   0566 74 19              1429 	mov	a,#0x19
   0568 25 05              1430 	add	a,ar5
   056A FD                 1431 	mov	r5,a
   056B 74 00              1432 	mov	a,#0x00
   056D 35 06              1433 	addc	a,ar6
   056F FE                 1434 	mov	r6,a
                           1435 ;     genCall
   0570 8D 82              1436 	mov	dpl,r5
   0572 8E 83              1437 	mov	dph,r6
   0574 8F F0              1438 	mov	b,r7
   0576 C0 02              1439 	push	ar2
   0578 C0 03              1440 	push	ar3
   057A 12 30 07           1441 	lcall	_vListRemove
   057D D0 03              1442 	pop	ar3
   057F D0 02              1443 	pop	ar2
                           1444 ;../../Source/tasks.c:623: listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xGenericListItem ), xTimeToWake );
                           1445 ;     genAssign
   0581 90 1D 0B           1446 	mov	dptr,#_pxCurrentTCB
   0584 E0                 1447 	movx	a,@dptr
   0585 FD                 1448 	mov	r5,a
   0586 A3                 1449 	inc	dptr
   0587 E0                 1450 	movx	a,@dptr
   0588 FE                 1451 	mov	r6,a
   0589 A3                 1452 	inc	dptr
   058A E0                 1453 	movx	a,@dptr
   058B FF                 1454 	mov	r7,a
                           1455 ;     genPlus
   058C 74 19              1456 	mov	a,#0x19
   058E 25 05              1457 	add	a,ar5
   0590 FD                 1458 	mov	r5,a
   0591 74 00              1459 	mov	a,#0x00
   0593 35 06              1460 	addc	a,ar6
   0595 FE                 1461 	mov	r6,a
                           1462 ;     genPointerSet
                           1463 ;     genGenPointerSet
   0596 8D 82              1464 	mov	dpl,r5
   0598 8E 83              1465 	mov	dph,r6
   059A 8F F0              1466 	mov	b,r7
   059C EA                 1467 	mov	a,r2
   059D 12 A3 97           1468 	lcall	__gptrput
   05A0 A3                 1469 	inc	dptr
   05A1 EB                 1470 	mov	a,r3
   05A2 12 A3 97           1471 	lcall	__gptrput
                           1472 ;../../Source/tasks.c:625: if( xTimeToWake < xTickCount )
                           1473 ;     genAssign
   05A5 90 1D 12           1474 	mov	dptr,#_xTickCount
   05A8 E0                 1475 	movx	a,@dptr
   05A9 FD                 1476 	mov	r5,a
   05AA A3                 1477 	inc	dptr
   05AB E0                 1478 	movx	a,@dptr
   05AC FE                 1479 	mov	r6,a
                           1480 ;     genCmpLt
                           1481 ;     genCmp
   05AD C3                 1482 	clr	c
   05AE EA                 1483 	mov	a,r2
   05AF 9D                 1484 	subb	a,r5
   05B0 EB                 1485 	mov	a,r3
   05B1 9E                 1486 	subb	a,r6
                           1487 ;     genIfxJump
   05B2 40 03              1488 	jc	00114$
   05B4 02 05 EF           1489 	ljmp	00102$
   05B7                    1490 00114$:
                           1491 ;../../Source/tasks.c:629: vListInsert( ( xList * ) pxOverflowDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
                           1492 ;     genAssign
   05B7 90 1D 0B           1493 	mov	dptr,#_pxCurrentTCB
   05BA E0                 1494 	movx	a,@dptr
   05BB FA                 1495 	mov	r2,a
   05BC A3                 1496 	inc	dptr
   05BD E0                 1497 	movx	a,@dptr
   05BE FB                 1498 	mov	r3,a
   05BF A3                 1499 	inc	dptr
   05C0 E0                 1500 	movx	a,@dptr
   05C1 FD                 1501 	mov	r5,a
                           1502 ;     genPlus
   05C2 74 19              1503 	mov	a,#0x19
   05C4 25 02              1504 	add	a,ar2
   05C6 FC                 1505 	mov	r4,a
   05C7 74 00              1506 	mov	a,#0x00
   05C9 35 03              1507 	addc	a,ar3
   05CB FB                 1508 	mov	r3,a
                           1509 ;     genAssign
   05CC 90 00 87           1510 	mov	dptr,#_pxOverflowDelayedTaskList
   05CF E0                 1511 	movx	a,@dptr
   05D0 FE                 1512 	mov	r6,a
   05D1 A3                 1513 	inc	dptr
   05D2 E0                 1514 	movx	a,@dptr
   05D3 FF                 1515 	mov	r7,a
   05D4 A3                 1516 	inc	dptr
   05D5 E0                 1517 	movx	a,@dptr
   05D6 FA                 1518 	mov	r2,a
                           1519 ;     genIpush
   05D7 C0 04              1520 	push	ar4
   05D9 C0 03              1521 	push	ar3
   05DB C0 05              1522 	push	ar5
                           1523 ;     genCall
   05DD 8E 82              1524 	mov	dpl,r6
   05DF 8F 83              1525 	mov	dph,r7
   05E1 8A F0              1526 	mov	b,r2
   05E3 12 2C E1           1527 	lcall	_vListInsert
   05E6 15 81              1528 	dec	sp
   05E8 15 81              1529 	dec	sp
   05EA 15 81              1530 	dec	sp
   05EC 02 06 24           1531 	ljmp	00103$
   05EF                    1532 00102$:
                           1533 ;../../Source/tasks.c:635: vListInsert( ( xList * ) pxDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
                           1534 ;     genAssign
   05EF 90 1D 0B           1535 	mov	dptr,#_pxCurrentTCB
   05F2 E0                 1536 	movx	a,@dptr
   05F3 FA                 1537 	mov	r2,a
   05F4 A3                 1538 	inc	dptr
   05F5 E0                 1539 	movx	a,@dptr
   05F6 FB                 1540 	mov	r3,a
   05F7 A3                 1541 	inc	dptr
   05F8 E0                 1542 	movx	a,@dptr
   05F9 FD                 1543 	mov	r5,a
                           1544 ;     genPlus
   05FA 74 19              1545 	mov	a,#0x19
   05FC 25 02              1546 	add	a,ar2
   05FE FC                 1547 	mov	r4,a
   05FF 74 00              1548 	mov	a,#0x00
   0601 35 03              1549 	addc	a,ar3
   0603 FB                 1550 	mov	r3,a
                           1551 ;     genAssign
   0604 90 00 84           1552 	mov	dptr,#_pxDelayedTaskList
   0607 E0                 1553 	movx	a,@dptr
   0608 FE                 1554 	mov	r6,a
   0609 A3                 1555 	inc	dptr
   060A E0                 1556 	movx	a,@dptr
   060B FF                 1557 	mov	r7,a
   060C A3                 1558 	inc	dptr
   060D E0                 1559 	movx	a,@dptr
   060E FA                 1560 	mov	r2,a
                           1561 ;     genIpush
   060F C0 04              1562 	push	ar4
   0611 C0 03              1563 	push	ar3
   0613 C0 05              1564 	push	ar5
                           1565 ;     genCall
   0615 8E 82              1566 	mov	dpl,r6
   0617 8F 83              1567 	mov	dph,r7
   0619 8A F0              1568 	mov	b,r2
   061B 12 2C E1           1569 	lcall	_vListInsert
   061E 15 81              1570 	dec	sp
   0620 15 81              1571 	dec	sp
   0622 15 81              1572 	dec	sp
   0624                    1573 00103$:
                           1574 ;../../Source/tasks.c:638: cAlreadyYielded = cTaskResumeAll();
                           1575 ;     genCall
   0624 12 06 B7           1576 	lcall	_cTaskResumeAll
   0627 AA 82              1577 	mov	r2,dpl
                           1578 ;     genAssign
   0629 8A 04              1579 	mov	ar4,r2
   062B                    1580 00105$:
                           1581 ;../../Source/tasks.c:643: if( !cAlreadyYielded )
                           1582 ;     genIfx
   062B EC                 1583 	mov	a,r4
                           1584 ;     genIfxJump
   062C 60 03              1585 	jz	00115$
   062E 02 06 34           1586 	ljmp	00108$
   0631                    1587 00115$:
                           1588 ;../../Source/tasks.c:645: taskYIELD(); 
                           1589 ;     genCall
   0631 12 17 01           1590 	lcall	_vPortYield
   0634                    1591 00108$:
   0634 85 12 81           1592 	mov	sp,_bp
   0637 D0 12              1593 	pop	_bp
   0639 22                 1594 	ret
                           1595 ;------------------------------------------------------------
                           1596 ;Allocation info for local variables in function 'vTaskStartScheduler'
                           1597 ;------------------------------------------------------------
                           1598 ;sUsePreemption            Allocated to registers r2 r3 
                           1599 ;------------------------------------------------------------
                           1600 ;../../Source/tasks.c:798: void vTaskStartScheduler( portSHORT sUsePreemption )
                           1601 ;	-----------------------------------------
                           1602 ;	 function vTaskStartScheduler
                           1603 ;	-----------------------------------------
   063A                    1604 _vTaskStartScheduler:
   063A C0 12              1605 	push	_bp
   063C 85 81 12           1606 	mov	_bp,sp
                           1607 ;     genReceive
   063F AA 82              1608 	mov	r2,dpl
   0641 AB 83              1609 	mov	r3,dph
                           1610 ;../../Source/tasks.c:801: if( pxCurrentTCB != NULL )
                           1611 ;     genAssign
   0643 90 1D 0B           1612 	mov	dptr,#_pxCurrentTCB
   0646 E0                 1613 	movx	a,@dptr
   0647 FC                 1614 	mov	r4,a
   0648 A3                 1615 	inc	dptr
   0649 E0                 1616 	movx	a,@dptr
   064A FD                 1617 	mov	r5,a
   064B A3                 1618 	inc	dptr
   064C E0                 1619 	movx	a,@dptr
   064D FE                 1620 	mov	r6,a
                           1621 ;     genCmpEq
   064E BC 00 09           1622 	cjne	r4,#0x00,00108$
   0651 BD 00 06           1623 	cjne	r5,#0x00,00108$
   0654 BE 00 03           1624 	cjne	r6,#0x00,00108$
   0657 02 06 78           1625 	ljmp	00105$
   065A                    1626 00108$:
                           1627 ;../../Source/tasks.c:803: sUsingPreemption = sUsePreemption;
                           1628 ;     genAssign
   065A 90 1D 0E           1629 	mov	dptr,#_sUsingPreemption
   065D EA                 1630 	mov	a,r2
   065E F0                 1631 	movx	@dptr,a
   065F A3                 1632 	inc	dptr
   0660 EB                 1633 	mov	a,r3
   0661 F0                 1634 	movx	@dptr,a
                           1635 ;../../Source/tasks.c:813: portDISABLE_INTERRUPTS();
                           1636 ;     genAssign
   0662 C2 AF              1637 	clr	_EA
                           1638 ;../../Source/tasks.c:815: cSchedulerRunning = pdTRUE;
                           1639 ;     genAssign
   0664 90 1D 16           1640 	mov	dptr,#_cSchedulerRunning
   0667 74 01              1641 	mov	a,#0x01
   0669 F0                 1642 	movx	@dptr,a
                           1643 ;../../Source/tasks.c:816: xTickCount = ( portTickType ) 0;
                           1644 ;     genAssign
   066A 90 1D 12           1645 	mov	dptr,#_xTickCount
   066D E4                 1646 	clr	a
   066E F0                 1647 	movx	@dptr,a
   066F A3                 1648 	inc	dptr
   0670 F0                 1649 	movx	@dptr,a
                           1650 ;../../Source/tasks.c:820: if( sPortStartScheduler( sUsePreemption ) )
                           1651 ;     genCall
   0671 8A 82              1652 	mov	dpl,r2
   0673 8B 83              1653 	mov	dph,r3
   0675 12 16 6F           1654 	lcall	_sPortStartScheduler
   0678                    1655 00105$:
   0678 85 12 81           1656 	mov	sp,_bp
   067B D0 12              1657 	pop	_bp
   067D 22                 1658 	ret
                           1659 ;------------------------------------------------------------
                           1660 ;Allocation info for local variables in function 'vTaskEndScheduler'
                           1661 ;------------------------------------------------------------
                           1662 ;------------------------------------------------------------
                           1663 ;../../Source/tasks.c:833: void vTaskEndScheduler( void )
                           1664 ;	-----------------------------------------
                           1665 ;	 function vTaskEndScheduler
                           1666 ;	-----------------------------------------
   067E                    1667 _vTaskEndScheduler:
   067E C0 12              1668 	push	_bp
   0680 85 81 12           1669 	mov	_bp,sp
                           1670 ;../../Source/tasks.c:838: portDISABLE_INTERRUPTS();
                           1671 ;     genAssign
   0683 C2 AF              1672 	clr	_EA
                           1673 ;../../Source/tasks.c:839: cSchedulerRunning = pdFALSE;
                           1674 ;     genAssign
   0685 90 1D 16           1675 	mov	dptr,#_cSchedulerRunning
   0688 74 00              1676 	mov	a,#0x00
   068A F0                 1677 	movx	@dptr,a
                           1678 ;../../Source/tasks.c:840: vPortEndScheduler();
                           1679 ;     genCall
   068B 12 16 F6           1680 	lcall	_vPortEndScheduler
   068E                    1681 00101$:
   068E 85 12 81           1682 	mov	sp,_bp
   0691 D0 12              1683 	pop	_bp
   0693 22                 1684 	ret
                           1685 ;------------------------------------------------------------
                           1686 ;Allocation info for local variables in function 'vTaskSuspendAll'
                           1687 ;------------------------------------------------------------
                           1688 ;------------------------------------------------------------
                           1689 ;../../Source/tasks.c:844: void vTaskSuspendAll( void )
                           1690 ;	-----------------------------------------
                           1691 ;	 function vTaskSuspendAll
                           1692 ;	-----------------------------------------
   0694                    1693 _vTaskSuspendAll:
   0694 C0 12              1694 	push	_bp
   0696 85 81 12           1695 	mov	_bp,sp
                           1696 ;../../Source/tasks.c:846: portENTER_CRITICAL();
                           1697 ;     genInline
   0699 C0 E0 C0 A8        1698 	 push ACC push IE 
                           1699 ;     genAssign
   069D C2 AF              1700 	clr	_EA
                           1701 ;../../Source/tasks.c:847: ++ucSchedulerSuspended;
                           1702 ;     genPlus
   069F 90 1D 17           1703 	mov	dptr,#_ucSchedulerSuspended
   06A2 E0                 1704 	movx	a,@dptr
   06A3 24 01              1705 	add	a,#0x01
   06A5 F0                 1706 	movx	@dptr,a
                           1707 ;../../Source/tasks.c:848: portEXIT_CRITICAL();
                           1708 ;     genInline
   06A6 D0 E0              1709 	 pop ACC 
                           1710 ;     genAnd
   06A8 53 E0 80           1711 	anl	_ACC,#0x80
                           1712 ;     genOr
   06AB E5 E0              1713 	mov	a,_ACC
   06AD 42 A8              1714 	orl	_IE,a
                           1715 ;     genInline
   06AF D0 E0              1716 	 pop ACC 
   06B1                    1717 00101$:
   06B1 85 12 81           1718 	mov	sp,_bp
   06B4 D0 12              1719 	pop	_bp
   06B6 22                 1720 	ret
                           1721 ;------------------------------------------------------------
                           1722 ;Allocation info for local variables in function 'cTaskResumeAll'
                           1723 ;------------------------------------------------------------
                           1724 ;pxTCB                     Allocated to registers r6 r7 r2 
                           1725 ;cAlreadyYielded           Allocated to stack - offset 1
                           1726 ;sloc0                     Allocated to stack - offset 5
                           1727 ;sloc1                     Allocated to stack - offset 2
                           1728 ;------------------------------------------------------------
                           1729 ;../../Source/tasks.c:852: signed portCHAR cTaskResumeAll( void )
                           1730 ;	-----------------------------------------
                           1731 ;	 function cTaskResumeAll
                           1732 ;	-----------------------------------------
   06B7                    1733 _cTaskResumeAll:
   06B7 C0 12              1734 	push	_bp
   06B9 85 81 12           1735 	mov	_bp,sp
   06BC E5 81              1736 	mov	a,sp
   06BE 24 04              1737 	add	a,#0x04
   06C0 F5 81              1738 	mov	sp,a
                           1739 ;../../Source/tasks.c:855: signed portCHAR cAlreadyYielded = ( signed portCHAR ) pdFALSE;
                           1740 ;     genAssign
   06C2 E5 12              1741 	mov	a,_bp
   06C4 24 01              1742 	add	a,#0x01
   06C6 F8                 1743 	mov	r0,a
   06C7 76 00              1744 	mov	@r0,#0x00
                           1745 ;../../Source/tasks.c:862: portENTER_CRITICAL();
                           1746 ;     genInline
   06C9 C0 E0 C0 A8        1747 	 push ACC push IE 
                           1748 ;     genAssign
   06CD C2 AF              1749 	clr	_EA
                           1750 ;../../Source/tasks.c:864: --ucSchedulerSuspended;
                           1751 ;     genMinus
   06CF 90 1D 17           1752 	mov	dptr,#_ucSchedulerSuspended
                           1753 ;     genMinusDec
   06D2 E0                 1754 	movx	a,@dptr
   06D3 14                 1755 	dec	a
                           1756 ;     genAssign
   06D4 90 1D 17           1757 	mov	dptr,#_ucSchedulerSuspended
   06D7 F0                 1758 	movx	@dptr,a
                           1759 ;../../Source/tasks.c:866: if( ucSchedulerSuspended == pdFALSE )
                           1760 ;     genAssign
   06D8 90 1D 17           1761 	mov	dptr,#_ucSchedulerSuspended
   06DB E0                 1762 	movx	a,@dptr
   06DC FB                 1763 	mov	r3,a
                           1764 ;     genCmpEq
   06DD BB 00 02           1765 	cjne	r3,#0x00,00126$
   06E0 80 03              1766 	sjmp	00127$
   06E2                    1767 00126$:
   06E2 02 08 82           1768 	ljmp	00114$
   06E5                    1769 00127$:
                           1770 ;../../Source/tasks.c:868: if( usCurrentNumberOfTasks > ( unsigned portSHORT ) 0 )
                           1771 ;     genAssign
   06E5 90 1D 10           1772 	mov	dptr,#_usCurrentNumberOfTasks
   06E8 E0                 1773 	movx	a,@dptr
   06E9 FB                 1774 	mov	r3,a
   06EA A3                 1775 	inc	dptr
   06EB E0                 1776 	movx	a,@dptr
   06EC FC                 1777 	mov	r4,a
                           1778 ;     genIfx
   06ED EB                 1779 	mov	a,r3
   06EE 4C                 1780 	orl	a,r4
                           1781 ;     genIfxJump
   06EF 70 03              1782 	jnz	00128$
   06F1 02 08 82           1783 	ljmp	00114$
   06F4                    1784 00128$:
                           1785 ;../../Source/tasks.c:872: while( ( pxTCB = ( tskTCB * ) listGET_OWNER_OF_HEAD_ENTRY(  ( ( xList * ) &xPendingReadyList ) ) ) != NULL )
   06F4                    1786 00103$:
                           1787 ;     genPointerGet
                           1788 ;     genFarPointerGet
   06F4 90 00 8A           1789 	mov	dptr,#_xPendingReadyList
   06F7 E0                 1790 	movx	a,@dptr
   06F8 FB                 1791 	mov	r3,a
   06F9 A3                 1792 	inc	dptr
   06FA E0                 1793 	movx	a,@dptr
   06FB FC                 1794 	mov	r4,a
                           1795 ;     genCmpEq
   06FC BB 00 07           1796 	cjne	r3,#0x00,00129$
   06FF BC 00 04           1797 	cjne	r4,#0x00,00129$
   0702 74 01              1798 	mov	a,#0x01
   0704 80 01              1799 	sjmp	00130$
   0706                    1800 00129$:
   0706 E4                 1801 	clr	a
   0707                    1802 00130$:
   0707 FB                 1803 	mov	r3,a
                           1804 ;     genNot
   0708 EB                 1805 	mov	a,r3
   0709 B4 01 00           1806 	cjne	a,#0x01,00131$
   070C                    1807 00131$:
   070C E4                 1808 	clr	a
   070D 33                 1809 	rlc	a
   070E FB                 1810 	mov	r3,a
                           1811 ;     genIfx
   070F EB                 1812 	mov	a,r3
                           1813 ;     genIfxJump
   0710 70 03              1814 	jnz	00132$
   0712 02 07 68           1815 	ljmp	00117$
   0715                    1816 00132$:
                           1817 ;     genPointerGet
                           1818 ;     genGenPointerGet
   0715 90 00 8C           1819 	mov	dptr,#(_xPendingReadyList + 0x0002)
   0718 75 F0 01           1820 	mov	b,#0x01
   071B 12 AE 30           1821 	lcall	__gptrget
   071E FB                 1822 	mov	r3,a
   071F A3                 1823 	inc	dptr
   0720 12 AE 30           1824 	lcall	__gptrget
   0723 FC                 1825 	mov	r4,a
   0724 A3                 1826 	inc	dptr
   0725 12 AE 30           1827 	lcall	__gptrget
   0728 FD                 1828 	mov	r5,a
                           1829 ;     genPlus
                           1830 ;     genPlusIncr
   0729 74 02              1831 	mov	a,#0x02
   072B 25 03              1832 	add	a,ar3
   072D FB                 1833 	mov	r3,a
   072E 74 00              1834 	mov	a,#0x00
   0730 35 04              1835 	addc	a,ar4
   0732 FC                 1836 	mov	r4,a
                           1837 ;     genPointerGet
                           1838 ;     genGenPointerGet
   0733 8B 82              1839 	mov	dpl,r3
   0735 8C 83              1840 	mov	dph,r4
   0737 8D F0              1841 	mov	b,r5
   0739 12 AE 30           1842 	lcall	__gptrget
   073C FB                 1843 	mov	r3,a
   073D A3                 1844 	inc	dptr
   073E 12 AE 30           1845 	lcall	__gptrget
   0741 FC                 1846 	mov	r4,a
   0742 A3                 1847 	inc	dptr
   0743 12 AE 30           1848 	lcall	__gptrget
   0746 FD                 1849 	mov	r5,a
                           1850 ;     genPlus
   0747 74 08              1851 	mov	a,#0x08
   0749 25 03              1852 	add	a,ar3
   074B FB                 1853 	mov	r3,a
   074C 74 00              1854 	mov	a,#0x00
   074E 35 04              1855 	addc	a,ar4
   0750 FC                 1856 	mov	r4,a
                           1857 ;     genPointerGet
                           1858 ;     genGenPointerGet
   0751 8B 82              1859 	mov	dpl,r3
   0753 8C 83              1860 	mov	dph,r4
   0755 8D F0              1861 	mov	b,r5
   0757 12 AE 30           1862 	lcall	__gptrget
   075A FB                 1863 	mov	r3,a
   075B A3                 1864 	inc	dptr
   075C 12 AE 30           1865 	lcall	__gptrget
   075F FC                 1866 	mov	r4,a
   0760 A3                 1867 	inc	dptr
   0761 12 AE 30           1868 	lcall	__gptrget
   0764 FD                 1869 	mov	r5,a
   0765 02 07 6E           1870 	ljmp	00118$
   0768                    1871 00117$:
                           1872 ;     genAssign
   0768 7B 00              1873 	mov	r3,#0x00
   076A 7C 00              1874 	mov	r4,#0x00
   076C 7D 00              1875 	mov	r5,#0x00
   076E                    1876 00118$:
                           1877 ;     genAssign
                           1878 ;     genAssign
   076E 8B 06              1879 	mov	ar6,r3
   0770 8C 07              1880 	mov	ar7,r4
   0772 8D 02              1881 	mov	ar2,r5
                           1882 ;     genCmpEq
   0774 BB 00 09           1883 	cjne	r3,#0x00,00133$
   0777 BC 00 06           1884 	cjne	r4,#0x00,00133$
   077A BD 00 03           1885 	cjne	r5,#0x00,00133$
   077D 02 08 4D           1886 	ljmp	00105$
   0780                    1887 00133$:
                           1888 ;../../Source/tasks.c:874: vListRemove( &( pxTCB->xEventListItem ) );
                           1889 ;     genPlus
   0780 74 27              1890 	mov	a,#0x27
   0782 25 06              1891 	add	a,ar6
   0784 FB                 1892 	mov	r3,a
   0785 74 00              1893 	mov	a,#0x00
   0787 35 07              1894 	addc	a,ar7
   0789 FC                 1895 	mov	r4,a
   078A 8A 05              1896 	mov	ar5,r2
                           1897 ;     genCall
   078C 8B 82              1898 	mov	dpl,r3
   078E 8C 83              1899 	mov	dph,r4
   0790 8D F0              1900 	mov	b,r5
   0792 C0 02              1901 	push	ar2
   0794 C0 06              1902 	push	ar6
   0796 C0 07              1903 	push	ar7
   0798 12 30 07           1904 	lcall	_vListRemove
   079B D0 07              1905 	pop	ar7
   079D D0 06              1906 	pop	ar6
   079F D0 02              1907 	pop	ar2
                           1908 ;../../Source/tasks.c:875: vListRemove( &( pxTCB->xGenericListItem ) );
                           1909 ;     genPlus
   07A1 74 19              1910 	mov	a,#0x19
   07A3 25 06              1911 	add	a,ar6
   07A5 FB                 1912 	mov	r3,a
   07A6 74 00              1913 	mov	a,#0x00
   07A8 35 07              1914 	addc	a,ar7
   07AA FC                 1915 	mov	r4,a
   07AB 8A 05              1916 	mov	ar5,r2
                           1917 ;     genCall
   07AD 8B 82              1918 	mov	dpl,r3
   07AF 8C 83              1919 	mov	dph,r4
   07B1 8D F0              1920 	mov	b,r5
   07B3 C0 02              1921 	push	ar2
   07B5 C0 06              1922 	push	ar6
   07B7 C0 07              1923 	push	ar7
   07B9 12 30 07           1924 	lcall	_vListRemove
   07BC D0 07              1925 	pop	ar7
   07BE D0 06              1926 	pop	ar6
   07C0 D0 02              1927 	pop	ar2
                           1928 ;../../Source/tasks.c:876: prvAddTaskToReadyQueue( pxTCB );
                           1929 ;     genPlus
   07C2 74 19              1930 	mov	a,#0x19
   07C4 25 06              1931 	add	a,ar6
   07C6 FB                 1932 	mov	r3,a
   07C7 74 00              1933 	mov	a,#0x00
   07C9 35 07              1934 	addc	a,ar7
   07CB FC                 1935 	mov	r4,a
   07CC 8A 05              1936 	mov	ar5,r2
                           1937 ;     genPointerSet
                           1938 ;     genGenPointerSet
   07CE 8B 82              1939 	mov	dpl,r3
   07D0 8C 83              1940 	mov	dph,r4
   07D2 8D F0              1941 	mov	b,r5
   07D4 74 00              1942 	mov	a,#0x00
   07D6 12 A3 97           1943 	lcall	__gptrput
   07D9 A3                 1944 	inc	dptr
   07DA 74 00              1945 	mov	a,#0x00
   07DC 12 A3 97           1946 	lcall	__gptrput
                           1947 ;     genPlus
   07DF E5 12              1948 	mov	a,_bp
   07E1 24 02              1949 	add	a,#0x02
   07E3 F8                 1950 	mov	r0,a
   07E4 74 18              1951 	mov	a,#0x18
   07E6 25 06              1952 	add	a,ar6
   07E8 F6                 1953 	mov	@r0,a
   07E9 74 00              1954 	mov	a,#0x00
   07EB 35 07              1955 	addc	a,ar7
   07ED 08                 1956 	inc	r0
   07EE F6                 1957 	mov	@r0,a
   07EF 08                 1958 	inc	r0
   07F0 A6 02              1959 	mov	@r0,ar2
                           1960 ;     genPointerGet
                           1961 ;     genGenPointerGet
   07F2 E5 12              1962 	mov	a,_bp
   07F4 24 02              1963 	add	a,#0x02
   07F6 F8                 1964 	mov	r0,a
   07F7 86 82              1965 	mov	dpl,@r0
   07F9 08                 1966 	inc	r0
   07FA 86 83              1967 	mov	dph,@r0
   07FC 08                 1968 	inc	r0
   07FD 86 F0              1969 	mov	b,@r0
   07FF 12 AE 30           1970 	lcall	__gptrget
   0802 FE                 1971 	mov	r6,a
                           1972 ;     genAssign
   0803 90 1D 15           1973 	mov	dptr,#_ucTopReadyPriority
   0806 E0                 1974 	movx	a,@dptr
   0807 FA                 1975 	mov	r2,a
                           1976 ;     genCmpGt
                           1977 ;     genCmp
   0808 C3                 1978 	clr	c
   0809 EA                 1979 	mov	a,r2
   080A 9E                 1980 	subb	a,r6
                           1981 ;     genIfxJump
   080B 40 03              1982 	jc	00134$
   080D 02 08 15           1983 	ljmp	00102$
   0810                    1984 00134$:
                           1985 ;     genAssign
   0810 90 1D 15           1986 	mov	dptr,#_ucTopReadyPriority
   0813 EE                 1987 	mov	a,r6
   0814 F0                 1988 	movx	@dptr,a
   0815                    1989 00102$:
                           1990 ;     genPointerGet
                           1991 ;     genGenPointerGet
   0815 E5 12              1992 	mov	a,_bp
   0817 24 02              1993 	add	a,#0x02
   0819 F8                 1994 	mov	r0,a
   081A 86 82              1995 	mov	dpl,@r0
   081C 08                 1996 	inc	r0
   081D 86 83              1997 	mov	dph,@r0
   081F 08                 1998 	inc	r0
   0820 86 F0              1999 	mov	b,@r0
   0822 12 AE 30           2000 	lcall	__gptrget
   0825 FA                 2001 	mov	r2,a
                           2002 ;     genMult
                           2003 ;     genMultOneByte
   0826 EA                 2004 	mov	a,r2
   0827 75 F0 16           2005 	mov	b,#0x16
   082A A4                 2006 	mul	ab
                           2007 ;     genPlus
   082B 24 00              2008 	add	a,#_pxReadyTasksLists
   082D FA                 2009 	mov	r2,a
   082E E5 F0              2010 	mov	a,b
   0830 34 00              2011 	addc	a,#(_pxReadyTasksLists >> 8)
   0832 FE                 2012 	mov	r6,a
                           2013 ;     genCast
   0833 7F 01              2014 	mov	r7,#0x1
                           2015 ;     genIpush
   0835 C0 03              2016 	push	ar3
   0837 C0 04              2017 	push	ar4
   0839 C0 05              2018 	push	ar5
                           2019 ;     genCall
   083B 8A 82              2020 	mov	dpl,r2
   083D 8E 83              2021 	mov	dph,r6
   083F 8F F0              2022 	mov	b,r7
   0841 12 2A F6           2023 	lcall	_vListInsertEnd
   0844 15 81              2024 	dec	sp
   0846 15 81              2025 	dec	sp
   0848 15 81              2026 	dec	sp
   084A 02 06 F4           2027 	ljmp	00103$
   084D                    2028 00105$:
                           2029 ;../../Source/tasks.c:882: if( ucMissedTicks > 0 )
                           2030 ;     genAssign
   084D 90 1D 18           2031 	mov	dptr,#_ucMissedTicks
   0850 E0                 2032 	movx	a,@dptr
   0851 FA                 2033 	mov	r2,a
                           2034 ;     genCmpGt
                           2035 ;     genCmp
   0852 C3                 2036 	clr	c
   0853 74 00              2037 	mov	a,#0x00
   0855 9A                 2038 	subb	a,r2
                           2039 ;     genIfxJump
   0856 40 03              2040 	jc	00135$
   0858 02 08 82           2041 	ljmp	00114$
   085B                    2042 00135$:
                           2043 ;../../Source/tasks.c:884: while( ucMissedTicks > 0 )
   085B                    2044 00106$:
                           2045 ;     genAssign
   085B 90 1D 18           2046 	mov	dptr,#_ucMissedTicks
   085E E0                 2047 	movx	a,@dptr
   085F FA                 2048 	mov	r2,a
                           2049 ;     genCmpGt
                           2050 ;     genCmp
   0860 C3                 2051 	clr	c
   0861 74 00              2052 	mov	a,#0x00
   0863 9A                 2053 	subb	a,r2
                           2054 ;     genIfxJump
   0864 40 03              2055 	jc	00136$
   0866 02 08 78           2056 	ljmp	00108$
   0869                    2057 00136$:
                           2058 ;../../Source/tasks.c:886: vTaskIncrementTick();
                           2059 ;     genCall
   0869 12 08 EA           2060 	lcall	_vTaskIncrementTick
                           2061 ;../../Source/tasks.c:887: --ucMissedTicks;
                           2062 ;     genMinus
   086C 90 1D 18           2063 	mov	dptr,#_ucMissedTicks
                           2064 ;     genMinusDec
   086F E0                 2065 	movx	a,@dptr
   0870 14                 2066 	dec	a
                           2067 ;     genAssign
   0871 90 1D 18           2068 	mov	dptr,#_ucMissedTicks
   0874 F0                 2069 	movx	@dptr,a
   0875 02 08 5B           2070 	ljmp	00106$
   0878                    2071 00108$:
                           2072 ;../../Source/tasks.c:893: cAlreadyYielded = ( signed portCHAR ) pdTRUE;
                           2073 ;     genAssign
   0878 E5 12              2074 	mov	a,_bp
   087A 24 01              2075 	add	a,#0x01
   087C F8                 2076 	mov	r0,a
   087D 76 01              2077 	mov	@r0,#0x01
                           2078 ;../../Source/tasks.c:894: taskYIELD();
                           2079 ;     genCall
   087F 12 17 01           2080 	lcall	_vPortYield
   0882                    2081 00114$:
                           2082 ;../../Source/tasks.c:899: portEXIT_CRITICAL();
                           2083 ;     genInline
   0882 D0 E0              2084 	 pop ACC 
                           2085 ;     genAnd
   0884 53 E0 80           2086 	anl	_ACC,#0x80
                           2087 ;     genOr
   0887 E5 E0              2088 	mov	a,_ACC
   0889 42 A8              2089 	orl	_IE,a
                           2090 ;     genInline
   088B D0 E0              2091 	 pop ACC 
                           2092 ;../../Source/tasks.c:901: return cAlreadyYielded;
                           2093 ;     genRet
   088D E5 12              2094 	mov	a,_bp
   088F 24 01              2095 	add	a,#0x01
   0891 F8                 2096 	mov	r0,a
   0892 86 82              2097 	mov	dpl,@r0
   0894                    2098 00115$:
   0894 85 12 81           2099 	mov	sp,_bp
   0897 D0 12              2100 	pop	_bp
   0899 22                 2101 	ret
                           2102 ;------------------------------------------------------------
                           2103 ;Allocation info for local variables in function 'xTaskGetTickCount'
                           2104 ;------------------------------------------------------------
                           2105 ;xTicks                    Allocated to registers r2 r3 
                           2106 ;------------------------------------------------------------
                           2107 ;../../Source/tasks.c:915: volatile portTickType xTaskGetTickCount( void )
                           2108 ;	-----------------------------------------
                           2109 ;	 function xTaskGetTickCount
                           2110 ;	-----------------------------------------
   089A                    2111 _xTaskGetTickCount:
   089A C0 12              2112 	push	_bp
   089C 85 81 12           2113 	mov	_bp,sp
                           2114 ;../../Source/tasks.c:920: taskENTER_CRITICAL();
                           2115 ;     genInline
   089F C0 E0 C0 A8        2116 	 push ACC push IE 
                           2117 ;     genAssign
   08A3 C2 AF              2118 	clr	_EA
                           2119 ;../../Source/tasks.c:922: xTicks = xTickCount;
                           2120 ;     genAssign
   08A5 90 1D 12           2121 	mov	dptr,#_xTickCount
   08A8 E0                 2122 	movx	a,@dptr
   08A9 FA                 2123 	mov	r2,a
   08AA A3                 2124 	inc	dptr
   08AB E0                 2125 	movx	a,@dptr
   08AC FB                 2126 	mov	r3,a
                           2127 ;     genAssign
                           2128 ;../../Source/tasks.c:924: taskEXIT_CRITICAL();
                           2129 ;     genInline
   08AD D0 E0              2130 	 pop ACC 
                           2131 ;     genAnd
   08AF 53 E0 80           2132 	anl	_ACC,#0x80
                           2133 ;     genOr
   08B2 E5 E0              2134 	mov	a,_ACC
   08B4 42 A8              2135 	orl	_IE,a
                           2136 ;     genInline
   08B6 D0 E0              2137 	 pop ACC 
                           2138 ;../../Source/tasks.c:926: return xTicks;
                           2139 ;     genRet
   08B8 8A 82              2140 	mov	dpl,r2
   08BA 8B 83              2141 	mov	dph,r3
   08BC                    2142 00101$:
   08BC 85 12 81           2143 	mov	sp,_bp
   08BF D0 12              2144 	pop	_bp
   08C1 22                 2145 	ret
                           2146 ;------------------------------------------------------------
                           2147 ;Allocation info for local variables in function 'usTaskGetNumberOfTasks'
                           2148 ;------------------------------------------------------------
                           2149 ;usNumberOfTasks           Allocated to registers r2 r3 
                           2150 ;------------------------------------------------------------
                           2151 ;../../Source/tasks.c:930: unsigned portSHORT usTaskGetNumberOfTasks( void )
                           2152 ;	-----------------------------------------
                           2153 ;	 function usTaskGetNumberOfTasks
                           2154 ;	-----------------------------------------
   08C2                    2155 _usTaskGetNumberOfTasks:
   08C2 C0 12              2156 	push	_bp
   08C4 85 81 12           2157 	mov	_bp,sp
                           2158 ;../../Source/tasks.c:934: taskENTER_CRITICAL();
                           2159 ;     genInline
   08C7 C0 E0 C0 A8        2160 	 push ACC push IE 
                           2161 ;     genAssign
   08CB C2 AF              2162 	clr	_EA
                           2163 ;../../Source/tasks.c:935: usNumberOfTasks = usCurrentNumberOfTasks;
                           2164 ;     genAssign
   08CD 90 1D 10           2165 	mov	dptr,#_usCurrentNumberOfTasks
   08D0 E0                 2166 	movx	a,@dptr
   08D1 FA                 2167 	mov	r2,a
   08D2 A3                 2168 	inc	dptr
   08D3 E0                 2169 	movx	a,@dptr
   08D4 FB                 2170 	mov	r3,a
                           2171 ;     genAssign
                           2172 ;../../Source/tasks.c:936: taskEXIT_CRITICAL();
                           2173 ;     genInline
   08D5 D0 E0              2174 	 pop ACC 
                           2175 ;     genAnd
   08D7 53 E0 80           2176 	anl	_ACC,#0x80
                           2177 ;     genOr
   08DA E5 E0              2178 	mov	a,_ACC
   08DC 42 A8              2179 	orl	_IE,a
                           2180 ;     genInline
   08DE D0 E0              2181 	 pop ACC 
                           2182 ;../../Source/tasks.c:938: return usNumberOfTasks;
                           2183 ;     genRet
   08E0 8A 82              2184 	mov	dpl,r2
   08E2 8B 83              2185 	mov	dph,r3
   08E4                    2186 00101$:
   08E4 85 12 81           2187 	mov	sp,_bp
   08E7 D0 12              2188 	pop	_bp
   08E9 22                 2189 	ret
                           2190 ;------------------------------------------------------------
                           2191 ;Allocation info for local variables in function 'vTaskIncrementTick'
                           2192 ;------------------------------------------------------------
                           2193 ;pxTemp                    Allocated to stack - offset 1
                           2194 ;pxTCB                     Allocated to registers r5 r6 r7 
                           2195 ;sloc0                     Allocated to stack - offset 4
                           2196 ;sloc1                     Allocated to stack - offset 6
                           2197 ;------------------------------------------------------------
                           2198 ;../../Source/tasks.c:1043: inline void vTaskIncrementTick( void )
                           2199 ;	-----------------------------------------
                           2200 ;	 function vTaskIncrementTick
                           2201 ;	-----------------------------------------
   08EA                    2202 _vTaskIncrementTick:
   08EA C0 12              2203 	push	_bp
   08EC 85 81 12           2204 	mov	_bp,sp
   08EF E5 81              2205 	mov	a,sp
   08F1 24 08              2206 	add	a,#0x08
   08F3 F5 81              2207 	mov	sp,a
                           2208 ;../../Source/tasks.c:1048: if( ucSchedulerSuspended == ( unsigned portCHAR ) pdFALSE )
                           2209 ;     genAssign
   08F5 90 1D 17           2210 	mov	dptr,#_ucSchedulerSuspended
   08F8 E0                 2211 	movx	a,@dptr
   08F9 FA                 2212 	mov	r2,a
                           2213 ;     genCmpEq
   08FA BA 00 02           2214 	cjne	r2,#0x00,00127$
   08FD 80 03              2215 	sjmp	00128$
   08FF                    2216 00127$:
   08FF 02 0B 75           2217 	ljmp	00113$
   0902                    2218 00128$:
                           2219 ;../../Source/tasks.c:1050: ++xTickCount;
                           2220 ;     genPlus
   0902 90 1D 12           2221 	mov	dptr,#_xTickCount
   0905 E0                 2222 	movx	a,@dptr
   0906 24 01              2223 	add	a,#0x01
   0908 F0                 2224 	movx	@dptr,a
   0909 A3                 2225 	inc	dptr
   090A E0                 2226 	movx	a,@dptr
   090B 34 00              2227 	addc	a,#0x00
   090D F0                 2228 	movx	@dptr,a
                           2229 ;../../Source/tasks.c:1051: if( xTickCount == ( portTickType ) 0 )
                           2230 ;     genAssign
   090E 90 1D 12           2231 	mov	dptr,#_xTickCount
   0911 E0                 2232 	movx	a,@dptr
   0912 FA                 2233 	mov	r2,a
   0913 A3                 2234 	inc	dptr
   0914 E0                 2235 	movx	a,@dptr
   0915 FB                 2236 	mov	r3,a
                           2237 ;     genCmpEq
   0916 BA 00 05           2238 	cjne	r2,#0x00,00129$
   0919 BB 00 02           2239 	cjne	r3,#0x00,00129$
   091C 80 03              2240 	sjmp	00130$
   091E                    2241 00129$:
   091E 02 09 61           2242 	ljmp	00109$
   0921                    2243 00130$:
                           2244 ;../../Source/tasks.c:1057: pxTemp = pxDelayedTaskList;
                           2245 ;     genAssign
   0921 90 00 84           2246 	mov	dptr,#_pxDelayedTaskList
   0924 E0                 2247 	movx	a,@dptr
   0925 FA                 2248 	mov	r2,a
   0926 A3                 2249 	inc	dptr
   0927 E0                 2250 	movx	a,@dptr
   0928 FB                 2251 	mov	r3,a
   0929 A3                 2252 	inc	dptr
   092A E0                 2253 	movx	a,@dptr
   092B FC                 2254 	mov	r4,a
                           2255 ;     genAssign
   092C E5 12              2256 	mov	a,_bp
   092E 24 01              2257 	add	a,#0x01
   0930 F8                 2258 	mov	r0,a
   0931 A6 02              2259 	mov	@r0,ar2
   0933 08                 2260 	inc	r0
   0934 A6 03              2261 	mov	@r0,ar3
   0936 08                 2262 	inc	r0
   0937 A6 04              2263 	mov	@r0,ar4
                           2264 ;../../Source/tasks.c:1058: pxDelayedTaskList = pxOverflowDelayedTaskList;
                           2265 ;     genAssign
   0939 90 00 87           2266 	mov	dptr,#_pxOverflowDelayedTaskList
   093C E0                 2267 	movx	a,@dptr
   093D FA                 2268 	mov	r2,a
   093E A3                 2269 	inc	dptr
   093F E0                 2270 	movx	a,@dptr
   0940 FB                 2271 	mov	r3,a
   0941 A3                 2272 	inc	dptr
   0942 E0                 2273 	movx	a,@dptr
   0943 FC                 2274 	mov	r4,a
                           2275 ;     genAssign
   0944 90 00 84           2276 	mov	dptr,#_pxDelayedTaskList
   0947 EA                 2277 	mov	a,r2
   0948 F0                 2278 	movx	@dptr,a
   0949 A3                 2279 	inc	dptr
   094A EB                 2280 	mov	a,r3
   094B F0                 2281 	movx	@dptr,a
   094C A3                 2282 	inc	dptr
   094D EC                 2283 	mov	a,r4
   094E F0                 2284 	movx	@dptr,a
                           2285 ;../../Source/tasks.c:1059: pxOverflowDelayedTaskList = pxTemp;
                           2286 ;     genAssign
   094F E5 12              2287 	mov	a,_bp
   0951 24 01              2288 	add	a,#0x01
   0953 F8                 2289 	mov	r0,a
   0954 90 00 87           2290 	mov	dptr,#_pxOverflowDelayedTaskList
   0957 E6                 2291 	mov	a,@r0
   0958 F0                 2292 	movx	@dptr,a
   0959 08                 2293 	inc	r0
   095A A3                 2294 	inc	dptr
   095B E6                 2295 	mov	a,@r0
   095C F0                 2296 	movx	@dptr,a
   095D 08                 2297 	inc	r0
   095E A3                 2298 	inc	dptr
   095F E6                 2299 	mov	a,@r0
   0960 F0                 2300 	movx	@dptr,a
                           2301 ;../../Source/tasks.c:1063: prvCheckDelayedTasks();
   0961                    2302 00109$:
                           2303 ;     genAssign
   0961 90 00 84           2304 	mov	dptr,#_pxDelayedTaskList
   0964 E0                 2305 	movx	a,@dptr
   0965 FA                 2306 	mov	r2,a
   0966 A3                 2307 	inc	dptr
   0967 E0                 2308 	movx	a,@dptr
   0968 FB                 2309 	mov	r3,a
   0969 A3                 2310 	inc	dptr
   096A E0                 2311 	movx	a,@dptr
   096B FC                 2312 	mov	r4,a
                           2313 ;     genPointerGet
                           2314 ;     genGenPointerGet
   096C 8A 82              2315 	mov	dpl,r2
   096E 8B 83              2316 	mov	dph,r3
   0970 8C F0              2317 	mov	b,r4
   0972 12 AE 30           2318 	lcall	__gptrget
   0975 FA                 2319 	mov	r2,a
   0976 A3                 2320 	inc	dptr
   0977 12 AE 30           2321 	lcall	__gptrget
   097A FB                 2322 	mov	r3,a
                           2323 ;     genCmpEq
   097B BA 00 07           2324 	cjne	r2,#0x00,00131$
   097E BB 00 04           2325 	cjne	r3,#0x00,00131$
   0981 74 01              2326 	mov	a,#0x01
   0983 80 01              2327 	sjmp	00132$
   0985                    2328 00131$:
   0985 E4                 2329 	clr	a
   0986                    2330 00132$:
   0986 FA                 2331 	mov	r2,a
                           2332 ;     genNot
   0987 EA                 2333 	mov	a,r2
   0988 B4 01 00           2334 	cjne	a,#0x01,00133$
   098B                    2335 00133$:
   098B E4                 2336 	clr	a
   098C 33                 2337 	rlc	a
   098D FA                 2338 	mov	r2,a
                           2339 ;     genIfx
   098E EA                 2340 	mov	a,r2
                           2341 ;     genIfxJump
   098F 70 03              2342 	jnz	00134$
   0991 02 09 FC           2343 	ljmp	00117$
   0994                    2344 00134$:
                           2345 ;     genAssign
   0994 90 00 84           2346 	mov	dptr,#_pxDelayedTaskList
   0997 E0                 2347 	movx	a,@dptr
   0998 FA                 2348 	mov	r2,a
   0999 A3                 2349 	inc	dptr
   099A E0                 2350 	movx	a,@dptr
   099B FB                 2351 	mov	r3,a
   099C A3                 2352 	inc	dptr
   099D E0                 2353 	movx	a,@dptr
   099E FC                 2354 	mov	r4,a
                           2355 ;     genPlus
                           2356 ;     genPlusIncr
   099F 74 02              2357 	mov	a,#0x02
   09A1 25 02              2358 	add	a,ar2
   09A3 FA                 2359 	mov	r2,a
   09A4 74 00              2360 	mov	a,#0x00
   09A6 35 03              2361 	addc	a,ar3
   09A8 FB                 2362 	mov	r3,a
                           2363 ;     genPointerGet
                           2364 ;     genGenPointerGet
   09A9 8A 82              2365 	mov	dpl,r2
   09AB 8B 83              2366 	mov	dph,r3
   09AD 8C F0              2367 	mov	b,r4
   09AF 12 AE 30           2368 	lcall	__gptrget
   09B2 FA                 2369 	mov	r2,a
   09B3 A3                 2370 	inc	dptr
   09B4 12 AE 30           2371 	lcall	__gptrget
   09B7 FB                 2372 	mov	r3,a
   09B8 A3                 2373 	inc	dptr
   09B9 12 AE 30           2374 	lcall	__gptrget
   09BC FC                 2375 	mov	r4,a
                           2376 ;     genPlus
                           2377 ;     genPlusIncr
   09BD 74 02              2378 	mov	a,#0x02
   09BF 25 02              2379 	add	a,ar2
   09C1 FA                 2380 	mov	r2,a
   09C2 74 00              2381 	mov	a,#0x00
   09C4 35 03              2382 	addc	a,ar3
   09C6 FB                 2383 	mov	r3,a
                           2384 ;     genPointerGet
                           2385 ;     genGenPointerGet
   09C7 8A 82              2386 	mov	dpl,r2
   09C9 8B 83              2387 	mov	dph,r3
   09CB 8C F0              2388 	mov	b,r4
   09CD 12 AE 30           2389 	lcall	__gptrget
   09D0 FA                 2390 	mov	r2,a
   09D1 A3                 2391 	inc	dptr
   09D2 12 AE 30           2392 	lcall	__gptrget
   09D5 FB                 2393 	mov	r3,a
   09D6 A3                 2394 	inc	dptr
   09D7 12 AE 30           2395 	lcall	__gptrget
   09DA FC                 2396 	mov	r4,a
                           2397 ;     genPlus
   09DB 74 08              2398 	mov	a,#0x08
   09DD 25 02              2399 	add	a,ar2
   09DF FA                 2400 	mov	r2,a
   09E0 74 00              2401 	mov	a,#0x00
   09E2 35 03              2402 	addc	a,ar3
   09E4 FB                 2403 	mov	r3,a
                           2404 ;     genPointerGet
                           2405 ;     genGenPointerGet
   09E5 8A 82              2406 	mov	dpl,r2
   09E7 8B 83              2407 	mov	dph,r3
   09E9 8C F0              2408 	mov	b,r4
   09EB 12 AE 30           2409 	lcall	__gptrget
   09EE FA                 2410 	mov	r2,a
   09EF A3                 2411 	inc	dptr
   09F0 12 AE 30           2412 	lcall	__gptrget
   09F3 FB                 2413 	mov	r3,a
   09F4 A3                 2414 	inc	dptr
   09F5 12 AE 30           2415 	lcall	__gptrget
   09F8 FC                 2416 	mov	r4,a
   09F9 02 0A 02           2417 	ljmp	00118$
   09FC                    2418 00117$:
                           2419 ;     genAssign
   09FC 7A 00              2420 	mov	r2,#0x00
   09FE 7B 00              2421 	mov	r3,#0x00
   0A00 7C 00              2422 	mov	r4,#0x00
   0A02                    2423 00118$:
                           2424 ;     genAssign
                           2425 ;     genAssign
   0A02 8A 05              2426 	mov	ar5,r2
   0A04 8B 06              2427 	mov	ar6,r3
   0A06 8C 07              2428 	mov	ar7,r4
                           2429 ;     genCmpEq
   0A08 BA 00 09           2430 	cjne	r2,#0x00,00135$
   0A0B BB 00 06           2431 	cjne	r3,#0x00,00135$
   0A0E BC 00 03           2432 	cjne	r4,#0x00,00135$
   0A11 02 0B 7C           2433 	ljmp	00115$
   0A14                    2434 00135$:
                           2435 ;     genPlus
   0A14 74 19              2436 	mov	a,#0x19
   0A16 25 05              2437 	add	a,ar5
   0A18 FA                 2438 	mov	r2,a
   0A19 74 00              2439 	mov	a,#0x00
   0A1B 35 06              2440 	addc	a,ar6
   0A1D FB                 2441 	mov	r3,a
   0A1E 8F 04              2442 	mov	ar4,r7
                           2443 ;     genIpush
   0A20 C0 05              2444 	push	ar5
   0A22 C0 06              2445 	push	ar6
   0A24 C0 07              2446 	push	ar7
                           2447 ;     genPointerGet
                           2448 ;     genGenPointerGet
   0A26 8A 82              2449 	mov	dpl,r2
   0A28 8B 83              2450 	mov	dph,r3
   0A2A 8C F0              2451 	mov	b,r4
   0A2C E5 12              2452 	mov	a,_bp
   0A2E 24 04              2453 	add	a,#0x04
   0A30 F8                 2454 	mov	r0,a
   0A31 12 AE 30           2455 	lcall	__gptrget
   0A34 F6                 2456 	mov	@r0,a
   0A35 A3                 2457 	inc	dptr
   0A36 12 AE 30           2458 	lcall	__gptrget
   0A39 08                 2459 	inc	r0
   0A3A F6                 2460 	mov	@r0,a
                           2461 ;     genAssign
   0A3B 90 1D 12           2462 	mov	dptr,#_xTickCount
   0A3E E0                 2463 	movx	a,@dptr
   0A3F FF                 2464 	mov	r7,a
   0A40 A3                 2465 	inc	dptr
   0A41 E0                 2466 	movx	a,@dptr
   0A42 FD                 2467 	mov	r5,a
                           2468 ;     genCmpLt
   0A43 E5 12              2469 	mov	a,_bp
   0A45 24 04              2470 	add	a,#0x04
   0A47 F8                 2471 	mov	r0,a
                           2472 ;     genCmp
   0A48 C3                 2473 	clr	c
   0A49 EF                 2474 	mov	a,r7
   0A4A 96                 2475 	subb	a,@r0
   0A4B ED                 2476 	mov	a,r5
   0A4C 08                 2477 	inc	r0
   0A4D 96                 2478 	subb	a,@r0
   0A4E E4                 2479 	clr	a
   0A4F 33                 2480 	rlc	a
                           2481 ;     genIpop
   0A50 D0 07              2482 	pop	ar7
   0A52 D0 06              2483 	pop	ar6
   0A54 D0 05              2484 	pop	ar5
                           2485 ;     genIfx
                           2486 ;     genIfxJump
   0A56 60 03              2487 	jz	00136$
   0A58 02 0B 7C           2488 	ljmp	00115$
   0A5B                    2489 00136$:
                           2490 ;     genCall
   0A5B 8A 82              2491 	mov	dpl,r2
   0A5D 8B 83              2492 	mov	dph,r3
   0A5F 8C F0              2493 	mov	b,r4
   0A61 C0 02              2494 	push	ar2
   0A63 C0 03              2495 	push	ar3
   0A65 C0 04              2496 	push	ar4
   0A67 C0 05              2497 	push	ar5
   0A69 C0 06              2498 	push	ar6
   0A6B C0 07              2499 	push	ar7
   0A6D 12 30 07           2500 	lcall	_vListRemove
   0A70 D0 07              2501 	pop	ar7
   0A72 D0 06              2502 	pop	ar6
   0A74 D0 05              2503 	pop	ar5
   0A76 D0 04              2504 	pop	ar4
   0A78 D0 03              2505 	pop	ar3
   0A7A D0 02              2506 	pop	ar2
                           2507 ;     genPlus
   0A7C E5 12              2508 	mov	a,_bp
   0A7E 24 06              2509 	add	a,#0x06
   0A80 F8                 2510 	mov	r0,a
   0A81 74 27              2511 	mov	a,#0x27
   0A83 25 05              2512 	add	a,ar5
   0A85 F6                 2513 	mov	@r0,a
   0A86 74 00              2514 	mov	a,#0x00
   0A88 35 06              2515 	addc	a,ar6
   0A8A 08                 2516 	inc	r0
   0A8B F6                 2517 	mov	@r0,a
   0A8C 08                 2518 	inc	r0
   0A8D A6 07              2519 	mov	@r0,ar7
                           2520 ;     genIpush
   0A8F C0 05              2521 	push	ar5
   0A91 C0 06              2522 	push	ar6
   0A93 C0 07              2523 	push	ar7
                           2524 ;     genPlus
   0A95 E5 12              2525 	mov	a,_bp
   0A97 24 06              2526 	add	a,#0x06
   0A99 F8                 2527 	mov	r0,a
   0A9A 74 0B              2528 	mov	a,#0x0B
   0A9C 26                 2529 	add	a,@r0
   0A9D FD                 2530 	mov	r5,a
   0A9E 74 00              2531 	mov	a,#0x00
   0AA0 08                 2532 	inc	r0
   0AA1 36                 2533 	addc	a,@r0
   0AA2 FE                 2534 	mov	r6,a
   0AA3 08                 2535 	inc	r0
   0AA4 86 07              2536 	mov	ar7,@r0
                           2537 ;     genPointerGet
                           2538 ;     genGenPointerGet
   0AA6 8D 82              2539 	mov	dpl,r5
   0AA8 8E 83              2540 	mov	dph,r6
   0AAA 8F F0              2541 	mov	b,r7
   0AAC 12 AE 30           2542 	lcall	__gptrget
   0AAF FD                 2543 	mov	r5,a
   0AB0 A3                 2544 	inc	dptr
   0AB1 12 AE 30           2545 	lcall	__gptrget
   0AB4 FE                 2546 	mov	r6,a
   0AB5 A3                 2547 	inc	dptr
   0AB6 12 AE 30           2548 	lcall	__gptrget
   0AB9 FF                 2549 	mov	r7,a
                           2550 ;     genIfx
   0ABA ED                 2551 	mov	a,r5
   0ABB 4E                 2552 	orl	a,r6
   0ABC 4F                 2553 	orl	a,r7
                           2554 ;     genIpop
   0ABD D0 07              2555 	pop	ar7
   0ABF D0 06              2556 	pop	ar6
   0AC1 D0 05              2557 	pop	ar5
                           2558 ;     genIfxJump
   0AC3 70 03              2559 	jnz	00137$
   0AC5 02 0A F0           2560 	ljmp	00106$
   0AC8                    2561 00137$:
                           2562 ;     genCall
   0AC8 E5 12              2563 	mov	a,_bp
   0ACA 24 06              2564 	add	a,#0x06
   0ACC F8                 2565 	mov	r0,a
   0ACD 86 82              2566 	mov	dpl,@r0
   0ACF 08                 2567 	inc	r0
   0AD0 86 83              2568 	mov	dph,@r0
   0AD2 08                 2569 	inc	r0
   0AD3 86 F0              2570 	mov	b,@r0
   0AD5 C0 02              2571 	push	ar2
   0AD7 C0 03              2572 	push	ar3
   0AD9 C0 04              2573 	push	ar4
   0ADB C0 05              2574 	push	ar5
   0ADD C0 06              2575 	push	ar6
   0ADF C0 07              2576 	push	ar7
   0AE1 12 30 07           2577 	lcall	_vListRemove
   0AE4 D0 07              2578 	pop	ar7
   0AE6 D0 06              2579 	pop	ar6
   0AE8 D0 05              2580 	pop	ar5
   0AEA D0 04              2581 	pop	ar4
   0AEC D0 03              2582 	pop	ar3
   0AEE D0 02              2583 	pop	ar2
   0AF0                    2584 00106$:
                           2585 ;     genPointerSet
                           2586 ;     genGenPointerSet
   0AF0 8A 82              2587 	mov	dpl,r2
   0AF2 8B 83              2588 	mov	dph,r3
   0AF4 8C F0              2589 	mov	b,r4
   0AF6 74 00              2590 	mov	a,#0x00
   0AF8 12 A3 97           2591 	lcall	__gptrput
   0AFB A3                 2592 	inc	dptr
   0AFC 74 00              2593 	mov	a,#0x00
   0AFE 12 A3 97           2594 	lcall	__gptrput
                           2595 ;     genPlus
   0B01 74 18              2596 	mov	a,#0x18
   0B03 25 05              2597 	add	a,ar5
   0B05 FD                 2598 	mov	r5,a
   0B06 74 00              2599 	mov	a,#0x00
   0B08 35 06              2600 	addc	a,ar6
   0B0A FE                 2601 	mov	r6,a
                           2602 ;     genPointerGet
                           2603 ;     genGenPointerGet
   0B0B 8D 82              2604 	mov	dpl,r5
   0B0D 8E 83              2605 	mov	dph,r6
   0B0F 8F F0              2606 	mov	b,r7
   0B11 E5 12              2607 	mov	a,_bp
   0B13 24 06              2608 	add	a,#0x06
   0B15 F8                 2609 	mov	r0,a
   0B16 12 AE 30           2610 	lcall	__gptrget
   0B19 F6                 2611 	mov	@r0,a
                           2612 ;     genIpush
   0B1A C0 02              2613 	push	ar2
   0B1C C0 03              2614 	push	ar3
   0B1E C0 04              2615 	push	ar4
                           2616 ;     genAssign
   0B20 90 1D 15           2617 	mov	dptr,#_ucTopReadyPriority
   0B23 E0                 2618 	movx	a,@dptr
   0B24 FA                 2619 	mov	r2,a
                           2620 ;     genCmpGt
   0B25 E5 12              2621 	mov	a,_bp
   0B27 24 06              2622 	add	a,#0x06
   0B29 F8                 2623 	mov	r0,a
                           2624 ;     genCmp
   0B2A C3                 2625 	clr	c
   0B2B EA                 2626 	mov	a,r2
   0B2C 96                 2627 	subb	a,@r0
   0B2D E4                 2628 	clr	a
   0B2E 33                 2629 	rlc	a
                           2630 ;     genIpop
   0B2F D0 04              2631 	pop	ar4
   0B31 D0 03              2632 	pop	ar3
   0B33 D0 02              2633 	pop	ar2
                           2634 ;     genIfx
                           2635 ;     genIfxJump
   0B35 70 03              2636 	jnz	00138$
   0B37 02 0B 44           2637 	ljmp	00108$
   0B3A                    2638 00138$:
                           2639 ;     genAssign
   0B3A E5 12              2640 	mov	a,_bp
   0B3C 24 06              2641 	add	a,#0x06
   0B3E F8                 2642 	mov	r0,a
   0B3F 90 1D 15           2643 	mov	dptr,#_ucTopReadyPriority
   0B42 E6                 2644 	mov	a,@r0
   0B43 F0                 2645 	movx	@dptr,a
   0B44                    2646 00108$:
                           2647 ;     genPointerGet
                           2648 ;     genGenPointerGet
   0B44 8D 82              2649 	mov	dpl,r5
   0B46 8E 83              2650 	mov	dph,r6
   0B48 8F F0              2651 	mov	b,r7
   0B4A 12 AE 30           2652 	lcall	__gptrget
   0B4D FD                 2653 	mov	r5,a
                           2654 ;     genMult
                           2655 ;     genMultOneByte
   0B4E ED                 2656 	mov	a,r5
   0B4F 75 F0 16           2657 	mov	b,#0x16
   0B52 A4                 2658 	mul	ab
                           2659 ;     genPlus
   0B53 24 00              2660 	add	a,#_pxReadyTasksLists
   0B55 FD                 2661 	mov	r5,a
   0B56 E5 F0              2662 	mov	a,b
   0B58 34 00              2663 	addc	a,#(_pxReadyTasksLists >> 8)
   0B5A FE                 2664 	mov	r6,a
                           2665 ;     genCast
   0B5B 7F 01              2666 	mov	r7,#0x1
                           2667 ;     genIpush
   0B5D C0 02              2668 	push	ar2
   0B5F C0 03              2669 	push	ar3
   0B61 C0 04              2670 	push	ar4
                           2671 ;     genCall
   0B63 8D 82              2672 	mov	dpl,r5
   0B65 8E 83              2673 	mov	dph,r6
   0B67 8F F0              2674 	mov	b,r7
   0B69 12 2A F6           2675 	lcall	_vListInsertEnd
   0B6C 15 81              2676 	dec	sp
   0B6E 15 81              2677 	dec	sp
   0B70 15 81              2678 	dec	sp
   0B72 02 09 61           2679 	ljmp	00109$
   0B75                    2680 00113$:
                           2681 ;../../Source/tasks.c:1067: ++ucMissedTicks;
                           2682 ;     genPlus
   0B75 90 1D 18           2683 	mov	dptr,#_ucMissedTicks
   0B78 E0                 2684 	movx	a,@dptr
   0B79 24 01              2685 	add	a,#0x01
   0B7B F0                 2686 	movx	@dptr,a
   0B7C                    2687 00115$:
   0B7C 85 12 81           2688 	mov	sp,_bp
   0B7F D0 12              2689 	pop	_bp
   0B81 22                 2690 	ret
                           2691 ;------------------------------------------------------------
                           2692 ;Allocation info for local variables in function 'vTaskSwitchContext'
                           2693 ;------------------------------------------------------------
                           2694 ;------------------------------------------------------------
                           2695 ;../../Source/tasks.c:1133: inline void vTaskSwitchContext( void )
                           2696 ;	-----------------------------------------
                           2697 ;	 function vTaskSwitchContext
                           2698 ;	-----------------------------------------
   0B82                    2699 _vTaskSwitchContext:
   0B82 C0 12              2700 	push	_bp
   0B84 85 81 12           2701 	mov	_bp,sp
                           2702 ;../../Source/tasks.c:1135: if( ucSchedulerSuspended != pdFALSE )
                           2703 ;     genAssign
   0B87 90 1D 17           2704 	mov	dptr,#_ucSchedulerSuspended
   0B8A E0                 2705 	movx	a,@dptr
   0B8B FA                 2706 	mov	r2,a
                           2707 ;     genCmpEq
   0B8C BA 00 03           2708 	cjne	r2,#0x00,00114$
   0B8F 02 0B 95           2709 	ljmp	00103$
   0B92                    2710 00114$:
                           2711 ;../../Source/tasks.c:1139: return;
                           2712 ;     genRet
   0B92 02 0D 49           2713 	ljmp	00108$
                           2714 ;../../Source/tasks.c:1143: while( listLIST_IS_EMPTY( &( pxReadyTasksLists[ ucTopReadyPriority ] ) ) )
   0B95                    2715 00103$:
                           2716 ;     genAssign
   0B95 90 1D 15           2717 	mov	dptr,#_ucTopReadyPriority
   0B98 E0                 2718 	movx	a,@dptr
   0B99 FA                 2719 	mov	r2,a
                           2720 ;     genMult
                           2721 ;     genMultOneByte
   0B9A EA                 2722 	mov	a,r2
   0B9B 75 F0 16           2723 	mov	b,#0x16
   0B9E A4                 2724 	mul	ab
                           2725 ;     genPlus
   0B9F 24 00              2726 	add	a,#_pxReadyTasksLists
   0BA1 F5 82              2727 	mov	dpl,a
   0BA3 E5 F0              2728 	mov	a,b
   0BA5 34 00              2729 	addc	a,#(_pxReadyTasksLists >> 8)
   0BA7 F5 83              2730 	mov	dph,a
                           2731 ;     genPointerGet
                           2732 ;     genFarPointerGet
   0BA9 E0                 2733 	movx	a,@dptr
   0BAA FA                 2734 	mov	r2,a
   0BAB A3                 2735 	inc	dptr
   0BAC E0                 2736 	movx	a,@dptr
   0BAD FB                 2737 	mov	r3,a
                           2738 ;     genCmpEq
   0BAE BA 00 05           2739 	cjne	r2,#0x00,00115$
   0BB1 BB 00 02           2740 	cjne	r3,#0x00,00115$
   0BB4 80 03              2741 	sjmp	00116$
   0BB6                    2742 00115$:
   0BB6 02 0B C5           2743 	ljmp	00105$
   0BB9                    2744 00116$:
                           2745 ;../../Source/tasks.c:1145: --ucTopReadyPriority;
                           2746 ;     genMinus
   0BB9 90 1D 15           2747 	mov	dptr,#_ucTopReadyPriority
                           2748 ;     genMinusDec
   0BBC E0                 2749 	movx	a,@dptr
   0BBD 14                 2750 	dec	a
                           2751 ;     genAssign
   0BBE 90 1D 15           2752 	mov	dptr,#_ucTopReadyPriority
   0BC1 F0                 2753 	movx	@dptr,a
   0BC2 02 0B 95           2754 	ljmp	00103$
   0BC5                    2755 00105$:
                           2756 ;../../Source/tasks.c:1150: listGET_OWNER_OF_NEXT_ENTRY( pxCurrentTCB, &( pxReadyTasksLists[ ucTopReadyPriority ] ) );
                           2757 ;     genAssign
   0BC5 90 1D 15           2758 	mov	dptr,#_ucTopReadyPriority
   0BC8 E0                 2759 	movx	a,@dptr
   0BC9 FA                 2760 	mov	r2,a
                           2761 ;     genMult
                           2762 ;     genMultOneByte
   0BCA EA                 2763 	mov	a,r2
   0BCB 75 F0 16           2764 	mov	b,#0x16
   0BCE A4                 2765 	mul	ab
                           2766 ;     genPlus
   0BCF 24 00              2767 	add	a,#_pxReadyTasksLists
   0BD1 FA                 2768 	mov	r2,a
   0BD2 E5 F0              2769 	mov	a,b
   0BD4 34 00              2770 	addc	a,#(_pxReadyTasksLists >> 8)
   0BD6 FB                 2771 	mov	r3,a
                           2772 ;     genPlus
   0BD7 74 05              2773 	mov	a,#0x05
   0BD9 25 02              2774 	add	a,ar2
   0BDB FA                 2775 	mov	r2,a
   0BDC 74 00              2776 	mov	a,#0x00
   0BDE 35 03              2777 	addc	a,ar3
   0BE0 FB                 2778 	mov	r3,a
                           2779 ;     genAssign
   0BE1 90 1D 15           2780 	mov	dptr,#_ucTopReadyPriority
   0BE4 E0                 2781 	movx	a,@dptr
   0BE5 FC                 2782 	mov	r4,a
                           2783 ;     genMult
                           2784 ;     genMultOneByte
   0BE6 EC                 2785 	mov	a,r4
   0BE7 75 F0 16           2786 	mov	b,#0x16
   0BEA A4                 2787 	mul	ab
                           2788 ;     genPlus
   0BEB 24 00              2789 	add	a,#_pxReadyTasksLists
   0BED FC                 2790 	mov	r4,a
   0BEE E5 F0              2791 	mov	a,b
   0BF0 34 00              2792 	addc	a,#(_pxReadyTasksLists >> 8)
   0BF2 FD                 2793 	mov	r5,a
                           2794 ;     genPlus
   0BF3 74 05              2795 	mov	a,#0x05
   0BF5 25 04              2796 	add	a,ar4
   0BF7 F5 82              2797 	mov	dpl,a
   0BF9 74 00              2798 	mov	a,#0x00
   0BFB 35 05              2799 	addc	a,ar5
   0BFD F5 83              2800 	mov	dph,a
                           2801 ;     genPointerGet
                           2802 ;     genFarPointerGet
   0BFF E0                 2803 	movx	a,@dptr
   0C00 FC                 2804 	mov	r4,a
   0C01 A3                 2805 	inc	dptr
   0C02 E0                 2806 	movx	a,@dptr
   0C03 FD                 2807 	mov	r5,a
   0C04 A3                 2808 	inc	dptr
   0C05 E0                 2809 	movx	a,@dptr
   0C06 FE                 2810 	mov	r6,a
                           2811 ;     genPlus
                           2812 ;     genPlusIncr
   0C07 74 02              2813 	mov	a,#0x02
   0C09 25 04              2814 	add	a,ar4
   0C0B FC                 2815 	mov	r4,a
   0C0C 74 00              2816 	mov	a,#0x00
   0C0E 35 05              2817 	addc	a,ar5
   0C10 FD                 2818 	mov	r5,a
                           2819 ;     genPointerGet
                           2820 ;     genGenPointerGet
   0C11 8C 82              2821 	mov	dpl,r4
   0C13 8D 83              2822 	mov	dph,r5
   0C15 8E F0              2823 	mov	b,r6
   0C17 12 AE 30           2824 	lcall	__gptrget
   0C1A FC                 2825 	mov	r4,a
   0C1B A3                 2826 	inc	dptr
   0C1C 12 AE 30           2827 	lcall	__gptrget
   0C1F FD                 2828 	mov	r5,a
   0C20 A3                 2829 	inc	dptr
   0C21 12 AE 30           2830 	lcall	__gptrget
   0C24 FE                 2831 	mov	r6,a
                           2832 ;     genPointerSet
                           2833 ;     genFarPointerSet
   0C25 8A 82              2834 	mov	dpl,r2
   0C27 8B 83              2835 	mov	dph,r3
   0C29 EC                 2836 	mov	a,r4
   0C2A F0                 2837 	movx	@dptr,a
   0C2B A3                 2838 	inc	dptr
   0C2C ED                 2839 	mov	a,r5
   0C2D F0                 2840 	movx	@dptr,a
   0C2E A3                 2841 	inc	dptr
   0C2F EE                 2842 	mov	a,r6
   0C30 F0                 2843 	movx	@dptr,a
                           2844 ;     genAssign
   0C31 90 1D 15           2845 	mov	dptr,#_ucTopReadyPriority
   0C34 E0                 2846 	movx	a,@dptr
   0C35 FA                 2847 	mov	r2,a
                           2848 ;     genMult
                           2849 ;     genMultOneByte
   0C36 EA                 2850 	mov	a,r2
   0C37 75 F0 16           2851 	mov	b,#0x16
   0C3A A4                 2852 	mul	ab
                           2853 ;     genPlus
   0C3B 24 00              2854 	add	a,#_pxReadyTasksLists
   0C3D FA                 2855 	mov	r2,a
   0C3E E5 F0              2856 	mov	a,b
   0C40 34 00              2857 	addc	a,#(_pxReadyTasksLists >> 8)
   0C42 FB                 2858 	mov	r3,a
                           2859 ;     genPlus
   0C43 74 05              2860 	mov	a,#0x05
   0C45 25 02              2861 	add	a,ar2
   0C47 F5 82              2862 	mov	dpl,a
   0C49 74 00              2863 	mov	a,#0x00
   0C4B 35 03              2864 	addc	a,ar3
   0C4D F5 83              2865 	mov	dph,a
                           2866 ;     genPointerGet
                           2867 ;     genFarPointerGet
   0C4F E0                 2868 	movx	a,@dptr
   0C50 FA                 2869 	mov	r2,a
   0C51 A3                 2870 	inc	dptr
   0C52 E0                 2871 	movx	a,@dptr
   0C53 FB                 2872 	mov	r3,a
   0C54 A3                 2873 	inc	dptr
   0C55 E0                 2874 	movx	a,@dptr
   0C56 FC                 2875 	mov	r4,a
                           2876 ;     genAssign
   0C57 90 1D 15           2877 	mov	dptr,#_ucTopReadyPriority
   0C5A E0                 2878 	movx	a,@dptr
   0C5B FD                 2879 	mov	r5,a
                           2880 ;     genMult
                           2881 ;     genMultOneByte
   0C5C ED                 2882 	mov	a,r5
   0C5D 75 F0 16           2883 	mov	b,#0x16
   0C60 A4                 2884 	mul	ab
                           2885 ;     genPlus
   0C61 24 00              2886 	add	a,#_pxReadyTasksLists
   0C63 FD                 2887 	mov	r5,a
   0C64 E5 F0              2888 	mov	a,b
   0C66 34 00              2889 	addc	a,#(_pxReadyTasksLists >> 8)
   0C68 FE                 2890 	mov	r6,a
                           2891 ;     genPlus
                           2892 ;     genPlusIncr
   0C69 74 02              2893 	mov	a,#0x02
   0C6B 25 05              2894 	add	a,ar5
   0C6D F5 82              2895 	mov	dpl,a
   0C6F 74 00              2896 	mov	a,#0x00
   0C71 35 06              2897 	addc	a,ar6
   0C73 F5 83              2898 	mov	dph,a
                           2899 ;     genPointerGet
                           2900 ;     genFarPointerGet
   0C75 E0                 2901 	movx	a,@dptr
   0C76 FD                 2902 	mov	r5,a
   0C77 A3                 2903 	inc	dptr
   0C78 E0                 2904 	movx	a,@dptr
   0C79 FE                 2905 	mov	r6,a
   0C7A A3                 2906 	inc	dptr
   0C7B E0                 2907 	movx	a,@dptr
   0C7C FF                 2908 	mov	r7,a
                           2909 ;     genCmpEq
   0C7D EA                 2910 	mov	a,r2
   0C7E B5 05 0A           2911 	cjne	a,ar5,00117$
   0C81 EB                 2912 	mov	a,r3
   0C82 B5 06 06           2913 	cjne	a,ar6,00117$
   0C85 EC                 2914 	mov	a,r4
   0C86 B5 07 02           2915 	cjne	a,ar7,00117$
   0C89 80 03              2916 	sjmp	00118$
   0C8B                    2917 00117$:
   0C8B 02 0C FA           2918 	ljmp	00107$
   0C8E                    2919 00118$:
                           2920 ;     genAssign
   0C8E 90 1D 15           2921 	mov	dptr,#_ucTopReadyPriority
   0C91 E0                 2922 	movx	a,@dptr
   0C92 FA                 2923 	mov	r2,a
                           2924 ;     genMult
                           2925 ;     genMultOneByte
   0C93 EA                 2926 	mov	a,r2
   0C94 75 F0 16           2927 	mov	b,#0x16
   0C97 A4                 2928 	mul	ab
                           2929 ;     genPlus
   0C98 24 00              2930 	add	a,#_pxReadyTasksLists
   0C9A FA                 2931 	mov	r2,a
   0C9B E5 F0              2932 	mov	a,b
   0C9D 34 00              2933 	addc	a,#(_pxReadyTasksLists >> 8)
   0C9F FB                 2934 	mov	r3,a
                           2935 ;     genPlus
   0CA0 74 05              2936 	mov	a,#0x05
   0CA2 25 02              2937 	add	a,ar2
   0CA4 FA                 2938 	mov	r2,a
   0CA5 74 00              2939 	mov	a,#0x00
   0CA7 35 03              2940 	addc	a,ar3
   0CA9 FB                 2941 	mov	r3,a
                           2942 ;     genAssign
   0CAA 90 1D 15           2943 	mov	dptr,#_ucTopReadyPriority
   0CAD E0                 2944 	movx	a,@dptr
   0CAE FC                 2945 	mov	r4,a
                           2946 ;     genMult
                           2947 ;     genMultOneByte
   0CAF EC                 2948 	mov	a,r4
   0CB0 75 F0 16           2949 	mov	b,#0x16
   0CB3 A4                 2950 	mul	ab
                           2951 ;     genPlus
   0CB4 24 00              2952 	add	a,#_pxReadyTasksLists
   0CB6 FC                 2953 	mov	r4,a
   0CB7 E5 F0              2954 	mov	a,b
   0CB9 34 00              2955 	addc	a,#(_pxReadyTasksLists >> 8)
   0CBB FD                 2956 	mov	r5,a
                           2957 ;     genPlus
   0CBC 74 05              2958 	mov	a,#0x05
   0CBE 25 04              2959 	add	a,ar4
   0CC0 F5 82              2960 	mov	dpl,a
   0CC2 74 00              2961 	mov	a,#0x00
   0CC4 35 05              2962 	addc	a,ar5
   0CC6 F5 83              2963 	mov	dph,a
                           2964 ;     genPointerGet
                           2965 ;     genFarPointerGet
   0CC8 E0                 2966 	movx	a,@dptr
   0CC9 FC                 2967 	mov	r4,a
   0CCA A3                 2968 	inc	dptr
   0CCB E0                 2969 	movx	a,@dptr
   0CCC FD                 2970 	mov	r5,a
   0CCD A3                 2971 	inc	dptr
   0CCE E0                 2972 	movx	a,@dptr
   0CCF FE                 2973 	mov	r6,a
                           2974 ;     genPlus
                           2975 ;     genPlusIncr
   0CD0 74 02              2976 	mov	a,#0x02
   0CD2 25 04              2977 	add	a,ar4
   0CD4 FC                 2978 	mov	r4,a
   0CD5 74 00              2979 	mov	a,#0x00
   0CD7 35 05              2980 	addc	a,ar5
   0CD9 FD                 2981 	mov	r5,a
                           2982 ;     genPointerGet
                           2983 ;     genGenPointerGet
   0CDA 8C 82              2984 	mov	dpl,r4
   0CDC 8D 83              2985 	mov	dph,r5
   0CDE 8E F0              2986 	mov	b,r6
   0CE0 12 AE 30           2987 	lcall	__gptrget
   0CE3 FC                 2988 	mov	r4,a
   0CE4 A3                 2989 	inc	dptr
   0CE5 12 AE 30           2990 	lcall	__gptrget
   0CE8 FD                 2991 	mov	r5,a
   0CE9 A3                 2992 	inc	dptr
   0CEA 12 AE 30           2993 	lcall	__gptrget
   0CED FE                 2994 	mov	r6,a
                           2995 ;     genPointerSet
                           2996 ;     genFarPointerSet
   0CEE 8A 82              2997 	mov	dpl,r2
   0CF0 8B 83              2998 	mov	dph,r3
   0CF2 EC                 2999 	mov	a,r4
   0CF3 F0                 3000 	movx	@dptr,a
   0CF4 A3                 3001 	inc	dptr
   0CF5 ED                 3002 	mov	a,r5
   0CF6 F0                 3003 	movx	@dptr,a
   0CF7 A3                 3004 	inc	dptr
   0CF8 EE                 3005 	mov	a,r6
   0CF9 F0                 3006 	movx	@dptr,a
   0CFA                    3007 00107$:
                           3008 ;     genAssign
   0CFA 90 1D 15           3009 	mov	dptr,#_ucTopReadyPriority
   0CFD E0                 3010 	movx	a,@dptr
   0CFE FA                 3011 	mov	r2,a
                           3012 ;     genMult
                           3013 ;     genMultOneByte
   0CFF EA                 3014 	mov	a,r2
   0D00 75 F0 16           3015 	mov	b,#0x16
   0D03 A4                 3016 	mul	ab
                           3017 ;     genPlus
   0D04 24 00              3018 	add	a,#_pxReadyTasksLists
   0D06 FA                 3019 	mov	r2,a
   0D07 E5 F0              3020 	mov	a,b
   0D09 34 00              3021 	addc	a,#(_pxReadyTasksLists >> 8)
   0D0B FB                 3022 	mov	r3,a
                           3023 ;     genPlus
   0D0C 74 05              3024 	mov	a,#0x05
   0D0E 25 02              3025 	add	a,ar2
   0D10 F5 82              3026 	mov	dpl,a
   0D12 74 00              3027 	mov	a,#0x00
   0D14 35 03              3028 	addc	a,ar3
   0D16 F5 83              3029 	mov	dph,a
                           3030 ;     genPointerGet
                           3031 ;     genFarPointerGet
   0D18 E0                 3032 	movx	a,@dptr
   0D19 FA                 3033 	mov	r2,a
   0D1A A3                 3034 	inc	dptr
   0D1B E0                 3035 	movx	a,@dptr
   0D1C FB                 3036 	mov	r3,a
   0D1D A3                 3037 	inc	dptr
   0D1E E0                 3038 	movx	a,@dptr
   0D1F FC                 3039 	mov	r4,a
                           3040 ;     genPlus
   0D20 74 08              3041 	mov	a,#0x08
   0D22 25 02              3042 	add	a,ar2
   0D24 FA                 3043 	mov	r2,a
   0D25 74 00              3044 	mov	a,#0x00
   0D27 35 03              3045 	addc	a,ar3
   0D29 FB                 3046 	mov	r3,a
                           3047 ;     genPointerGet
                           3048 ;     genGenPointerGet
   0D2A 8A 82              3049 	mov	dpl,r2
   0D2C 8B 83              3050 	mov	dph,r3
   0D2E 8C F0              3051 	mov	b,r4
   0D30 12 AE 30           3052 	lcall	__gptrget
   0D33 FA                 3053 	mov	r2,a
   0D34 A3                 3054 	inc	dptr
   0D35 12 AE 30           3055 	lcall	__gptrget
   0D38 FB                 3056 	mov	r3,a
   0D39 A3                 3057 	inc	dptr
   0D3A 12 AE 30           3058 	lcall	__gptrget
   0D3D FC                 3059 	mov	r4,a
                           3060 ;     genAssign
   0D3E 90 1D 0B           3061 	mov	dptr,#_pxCurrentTCB
   0D41 EA                 3062 	mov	a,r2
   0D42 F0                 3063 	movx	@dptr,a
   0D43 A3                 3064 	inc	dptr
   0D44 EB                 3065 	mov	a,r3
   0D45 F0                 3066 	movx	@dptr,a
   0D46 A3                 3067 	inc	dptr
   0D47 EC                 3068 	mov	a,r4
   0D48 F0                 3069 	movx	@dptr,a
   0D49                    3070 00108$:
   0D49 85 12 81           3071 	mov	sp,_bp
   0D4C D0 12              3072 	pop	_bp
   0D4E 22                 3073 	ret
                           3074 ;------------------------------------------------------------
                           3075 ;Allocation info for local variables in function 'vTaskPlaceOnEventList'
                           3076 ;------------------------------------------------------------
                           3077 ;xTicksToWait              Allocated to stack - offset -4
                           3078 ;pxEventList               Allocated to registers r2 r3 r4 
                           3079 ;xTimeToWake               Allocated to registers r2 r3 
                           3080 ;------------------------------------------------------------
                           3081 ;../../Source/tasks.c:1155: void vTaskPlaceOnEventList( xList *pxEventList, portTickType xTicksToWait )
                           3082 ;	-----------------------------------------
                           3083 ;	 function vTaskPlaceOnEventList
                           3084 ;	-----------------------------------------
   0D4F                    3085 _vTaskPlaceOnEventList:
   0D4F C0 12              3086 	push	_bp
   0D51 85 81 12           3087 	mov	_bp,sp
                           3088 ;     genReceive
   0D54 AA 82              3089 	mov	r2,dpl
   0D56 AB 83              3090 	mov	r3,dph
   0D58 AC F0              3091 	mov	r4,b
                           3092 ;../../Source/tasks.c:1165: vListInsert( ( xList * ) pxEventList, ( xListItem * ) &( pxCurrentTCB->xEventListItem ) );
                           3093 ;     genAssign
   0D5A 90 1D 0B           3094 	mov	dptr,#_pxCurrentTCB
   0D5D E0                 3095 	movx	a,@dptr
   0D5E FD                 3096 	mov	r5,a
   0D5F A3                 3097 	inc	dptr
   0D60 E0                 3098 	movx	a,@dptr
   0D61 FE                 3099 	mov	r6,a
   0D62 A3                 3100 	inc	dptr
   0D63 E0                 3101 	movx	a,@dptr
   0D64 FF                 3102 	mov	r7,a
                           3103 ;     genPlus
   0D65 74 27              3104 	mov	a,#0x27
   0D67 25 05              3105 	add	a,ar5
   0D69 FD                 3106 	mov	r5,a
   0D6A 74 00              3107 	mov	a,#0x00
   0D6C 35 06              3108 	addc	a,ar6
   0D6E FE                 3109 	mov	r6,a
                           3110 ;     genIpush
   0D6F C0 05              3111 	push	ar5
   0D71 C0 06              3112 	push	ar6
   0D73 C0 07              3113 	push	ar7
                           3114 ;     genCall
   0D75 8A 82              3115 	mov	dpl,r2
   0D77 8B 83              3116 	mov	dph,r3
   0D79 8C F0              3117 	mov	b,r4
   0D7B 12 2C E1           3118 	lcall	_vListInsert
   0D7E 15 81              3119 	dec	sp
   0D80 15 81              3120 	dec	sp
   0D82 15 81              3121 	dec	sp
                           3122 ;../../Source/tasks.c:1169: xTimeToWake = xTickCount + xTicksToWait;
                           3123 ;     genAssign
   0D84 90 1D 12           3124 	mov	dptr,#_xTickCount
   0D87 E0                 3125 	movx	a,@dptr
   0D88 FA                 3126 	mov	r2,a
   0D89 A3                 3127 	inc	dptr
   0D8A E0                 3128 	movx	a,@dptr
   0D8B FB                 3129 	mov	r3,a
                           3130 ;     genPlus
   0D8C E5 12              3131 	mov	a,_bp
   0D8E 24 FC              3132 	add	a,#0xfc
   0D90 F8                 3133 	mov	r0,a
   0D91 E6                 3134 	mov	a,@r0
   0D92 25 02              3135 	add	a,ar2
   0D94 FA                 3136 	mov	r2,a
   0D95 08                 3137 	inc	r0
   0D96 E6                 3138 	mov	a,@r0
   0D97 35 03              3139 	addc	a,ar3
   0D99 FB                 3140 	mov	r3,a
                           3141 ;     genAssign
                           3142 ;../../Source/tasks.c:1174: vListRemove( ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
                           3143 ;     genAssign
   0D9A 90 1D 0B           3144 	mov	dptr,#_pxCurrentTCB
   0D9D E0                 3145 	movx	a,@dptr
   0D9E FC                 3146 	mov	r4,a
   0D9F A3                 3147 	inc	dptr
   0DA0 E0                 3148 	movx	a,@dptr
   0DA1 FD                 3149 	mov	r5,a
   0DA2 A3                 3150 	inc	dptr
   0DA3 E0                 3151 	movx	a,@dptr
   0DA4 FE                 3152 	mov	r6,a
                           3153 ;     genPlus
   0DA5 74 19              3154 	mov	a,#0x19
   0DA7 25 04              3155 	add	a,ar4
   0DA9 FC                 3156 	mov	r4,a
   0DAA 74 00              3157 	mov	a,#0x00
   0DAC 35 05              3158 	addc	a,ar5
   0DAE FD                 3159 	mov	r5,a
                           3160 ;     genCall
   0DAF 8C 82              3161 	mov	dpl,r4
   0DB1 8D 83              3162 	mov	dph,r5
   0DB3 8E F0              3163 	mov	b,r6
   0DB5 C0 02              3164 	push	ar2
   0DB7 C0 03              3165 	push	ar3
   0DB9 12 30 07           3166 	lcall	_vListRemove
   0DBC D0 03              3167 	pop	ar3
   0DBE D0 02              3168 	pop	ar2
                           3169 ;../../Source/tasks.c:1176: listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xGenericListItem ), xTimeToWake );
                           3170 ;     genAssign
   0DC0 90 1D 0B           3171 	mov	dptr,#_pxCurrentTCB
   0DC3 E0                 3172 	movx	a,@dptr
   0DC4 FC                 3173 	mov	r4,a
   0DC5 A3                 3174 	inc	dptr
   0DC6 E0                 3175 	movx	a,@dptr
   0DC7 FD                 3176 	mov	r5,a
   0DC8 A3                 3177 	inc	dptr
   0DC9 E0                 3178 	movx	a,@dptr
   0DCA FE                 3179 	mov	r6,a
                           3180 ;     genPlus
   0DCB 74 19              3181 	mov	a,#0x19
   0DCD 25 04              3182 	add	a,ar4
   0DCF FC                 3183 	mov	r4,a
   0DD0 74 00              3184 	mov	a,#0x00
   0DD2 35 05              3185 	addc	a,ar5
   0DD4 FD                 3186 	mov	r5,a
                           3187 ;     genPointerSet
                           3188 ;     genGenPointerSet
   0DD5 8C 82              3189 	mov	dpl,r4
   0DD7 8D 83              3190 	mov	dph,r5
   0DD9 8E F0              3191 	mov	b,r6
   0DDB EA                 3192 	mov	a,r2
   0DDC 12 A3 97           3193 	lcall	__gptrput
   0DDF A3                 3194 	inc	dptr
   0DE0 EB                 3195 	mov	a,r3
   0DE1 12 A3 97           3196 	lcall	__gptrput
                           3197 ;../../Source/tasks.c:1178: if( xTimeToWake < xTickCount )
                           3198 ;     genAssign
   0DE4 90 1D 12           3199 	mov	dptr,#_xTickCount
   0DE7 E0                 3200 	movx	a,@dptr
   0DE8 FC                 3201 	mov	r4,a
   0DE9 A3                 3202 	inc	dptr
   0DEA E0                 3203 	movx	a,@dptr
   0DEB FD                 3204 	mov	r5,a
                           3205 ;     genCmpLt
                           3206 ;     genCmp
   0DEC C3                 3207 	clr	c
   0DED EA                 3208 	mov	a,r2
   0DEE 9C                 3209 	subb	a,r4
   0DEF EB                 3210 	mov	a,r3
   0DF0 9D                 3211 	subb	a,r5
                           3212 ;     genIfxJump
   0DF1 40 03              3213 	jc	00107$
   0DF3 02 0E 2E           3214 	ljmp	00102$
   0DF6                    3215 00107$:
                           3216 ;../../Source/tasks.c:1181: vListInsert( ( xList * ) pxOverflowDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
                           3217 ;     genAssign
   0DF6 90 1D 0B           3218 	mov	dptr,#_pxCurrentTCB
   0DF9 E0                 3219 	movx	a,@dptr
   0DFA FA                 3220 	mov	r2,a
   0DFB A3                 3221 	inc	dptr
   0DFC E0                 3222 	movx	a,@dptr
   0DFD FB                 3223 	mov	r3,a
   0DFE A3                 3224 	inc	dptr
   0DFF E0                 3225 	movx	a,@dptr
   0E00 FC                 3226 	mov	r4,a
                           3227 ;     genPlus
   0E01 74 19              3228 	mov	a,#0x19
   0E03 25 02              3229 	add	a,ar2
   0E05 FA                 3230 	mov	r2,a
   0E06 74 00              3231 	mov	a,#0x00
   0E08 35 03              3232 	addc	a,ar3
   0E0A FB                 3233 	mov	r3,a
                           3234 ;     genAssign
   0E0B 90 00 87           3235 	mov	dptr,#_pxOverflowDelayedTaskList
   0E0E E0                 3236 	movx	a,@dptr
   0E0F FD                 3237 	mov	r5,a
   0E10 A3                 3238 	inc	dptr
   0E11 E0                 3239 	movx	a,@dptr
   0E12 FE                 3240 	mov	r6,a
   0E13 A3                 3241 	inc	dptr
   0E14 E0                 3242 	movx	a,@dptr
   0E15 FF                 3243 	mov	r7,a
                           3244 ;     genIpush
   0E16 C0 02              3245 	push	ar2
   0E18 C0 03              3246 	push	ar3
   0E1A C0 04              3247 	push	ar4
                           3248 ;     genCall
   0E1C 8D 82              3249 	mov	dpl,r5
   0E1E 8E 83              3250 	mov	dph,r6
   0E20 8F F0              3251 	mov	b,r7
   0E22 12 2C E1           3252 	lcall	_vListInsert
   0E25 15 81              3253 	dec	sp
   0E27 15 81              3254 	dec	sp
   0E29 15 81              3255 	dec	sp
   0E2B 02 0E 63           3256 	ljmp	00104$
   0E2E                    3257 00102$:
                           3258 ;../../Source/tasks.c:1186: vListInsert( ( xList * ) pxDelayedTaskList, ( xListItem * ) &( pxCurrentTCB->xGenericListItem ) );
                           3259 ;     genAssign
   0E2E 90 1D 0B           3260 	mov	dptr,#_pxCurrentTCB
   0E31 E0                 3261 	movx	a,@dptr
   0E32 FA                 3262 	mov	r2,a
   0E33 A3                 3263 	inc	dptr
   0E34 E0                 3264 	movx	a,@dptr
   0E35 FB                 3265 	mov	r3,a
   0E36 A3                 3266 	inc	dptr
   0E37 E0                 3267 	movx	a,@dptr
   0E38 FC                 3268 	mov	r4,a
                           3269 ;     genPlus
   0E39 74 19              3270 	mov	a,#0x19
   0E3B 25 02              3271 	add	a,ar2
   0E3D FA                 3272 	mov	r2,a
   0E3E 74 00              3273 	mov	a,#0x00
   0E40 35 03              3274 	addc	a,ar3
   0E42 FB                 3275 	mov	r3,a
                           3276 ;     genAssign
   0E43 90 00 84           3277 	mov	dptr,#_pxDelayedTaskList
   0E46 E0                 3278 	movx	a,@dptr
   0E47 FD                 3279 	mov	r5,a
   0E48 A3                 3280 	inc	dptr
   0E49 E0                 3281 	movx	a,@dptr
   0E4A FE                 3282 	mov	r6,a
   0E4B A3                 3283 	inc	dptr
   0E4C E0                 3284 	movx	a,@dptr
   0E4D FF                 3285 	mov	r7,a
                           3286 ;     genIpush
   0E4E C0 02              3287 	push	ar2
   0E50 C0 03              3288 	push	ar3
   0E52 C0 04              3289 	push	ar4
                           3290 ;     genCall
   0E54 8D 82              3291 	mov	dpl,r5
   0E56 8E 83              3292 	mov	dph,r6
   0E58 8F F0              3293 	mov	b,r7
   0E5A 12 2C E1           3294 	lcall	_vListInsert
   0E5D 15 81              3295 	dec	sp
   0E5F 15 81              3296 	dec	sp
   0E61 15 81              3297 	dec	sp
   0E63                    3298 00104$:
   0E63 85 12 81           3299 	mov	sp,_bp
   0E66 D0 12              3300 	pop	_bp
   0E68 22                 3301 	ret
                           3302 ;------------------------------------------------------------
                           3303 ;Allocation info for local variables in function 'cTaskRemoveFromEventList'
                           3304 ;------------------------------------------------------------
                           3305 ;pxEventList               Allocated to registers r2 r3 r4 
                           3306 ;pxUnblockedTCB            Allocated to stack - offset 1
                           3307 ;------------------------------------------------------------
                           3308 ;../../Source/tasks.c:1191: signed portCHAR cTaskRemoveFromEventList( const xList *pxEventList )
                           3309 ;	-----------------------------------------
                           3310 ;	 function cTaskRemoveFromEventList
                           3311 ;	-----------------------------------------
   0E69                    3312 _cTaskRemoveFromEventList:
   0E69 C0 12              3313 	push	_bp
   0E6B 85 81 12           3314 	mov	_bp,sp
   0E6E 05 81              3315 	inc	sp
   0E70 05 81              3316 	inc	sp
   0E72 05 81              3317 	inc	sp
                           3318 ;     genReceive
   0E74 AA 82              3319 	mov	r2,dpl
   0E76 AB 83              3320 	mov	r3,dph
   0E78 AC F0              3321 	mov	r4,b
                           3322 ;../../Source/tasks.c:1205: pxUnblockedTCB = ( tskTCB * ) listGET_OWNER_OF_HEAD_ENTRY( pxEventList );
                           3323 ;     genPointerGet
                           3324 ;     genGenPointerGet
   0E7A 8A 82              3325 	mov	dpl,r2
   0E7C 8B 83              3326 	mov	dph,r3
   0E7E 8C F0              3327 	mov	b,r4
   0E80 12 AE 30           3328 	lcall	__gptrget
   0E83 FD                 3329 	mov	r5,a
   0E84 A3                 3330 	inc	dptr
   0E85 12 AE 30           3331 	lcall	__gptrget
   0E88 FE                 3332 	mov	r6,a
                           3333 ;     genCmpEq
   0E89 BD 00 07           3334 	cjne	r5,#0x00,00117$
   0E8C BE 00 04           3335 	cjne	r6,#0x00,00117$
   0E8F 74 01              3336 	mov	a,#0x01
   0E91 80 01              3337 	sjmp	00118$
   0E93                    3338 00117$:
   0E93 E4                 3339 	clr	a
   0E94                    3340 00118$:
   0E94 FD                 3341 	mov	r5,a
                           3342 ;     genNot
   0E95 ED                 3343 	mov	a,r5
   0E96 B4 01 00           3344 	cjne	a,#0x01,00119$
   0E99                    3345 00119$:
   0E99 E4                 3346 	clr	a
   0E9A 33                 3347 	rlc	a
   0E9B FD                 3348 	mov	r5,a
                           3349 ;     genIfx
   0E9C ED                 3350 	mov	a,r5
                           3351 ;     genIfxJump
   0E9D 70 03              3352 	jnz	00120$
   0E9F 02 0E FF           3353 	ljmp	00111$
   0EA2                    3354 00120$:
                           3355 ;     genPlus
                           3356 ;     genPlusIncr
   0EA2 74 02              3357 	mov	a,#0x02
   0EA4 25 02              3358 	add	a,ar2
   0EA6 FA                 3359 	mov	r2,a
   0EA7 74 00              3360 	mov	a,#0x00
   0EA9 35 03              3361 	addc	a,ar3
   0EAB FB                 3362 	mov	r3,a
                           3363 ;     genPointerGet
                           3364 ;     genGenPointerGet
   0EAC 8A 82              3365 	mov	dpl,r2
   0EAE 8B 83              3366 	mov	dph,r3
   0EB0 8C F0              3367 	mov	b,r4
   0EB2 12 AE 30           3368 	lcall	__gptrget
   0EB5 FA                 3369 	mov	r2,a
   0EB6 A3                 3370 	inc	dptr
   0EB7 12 AE 30           3371 	lcall	__gptrget
   0EBA FB                 3372 	mov	r3,a
   0EBB A3                 3373 	inc	dptr
   0EBC 12 AE 30           3374 	lcall	__gptrget
   0EBF FC                 3375 	mov	r4,a
                           3376 ;     genPlus
                           3377 ;     genPlusIncr
   0EC0 74 02              3378 	mov	a,#0x02
   0EC2 25 02              3379 	add	a,ar2
   0EC4 FA                 3380 	mov	r2,a
   0EC5 74 00              3381 	mov	a,#0x00
   0EC7 35 03              3382 	addc	a,ar3
   0EC9 FB                 3383 	mov	r3,a
                           3384 ;     genPointerGet
                           3385 ;     genGenPointerGet
   0ECA 8A 82              3386 	mov	dpl,r2
   0ECC 8B 83              3387 	mov	dph,r3
   0ECE 8C F0              3388 	mov	b,r4
   0ED0 12 AE 30           3389 	lcall	__gptrget
   0ED3 FA                 3390 	mov	r2,a
   0ED4 A3                 3391 	inc	dptr
   0ED5 12 AE 30           3392 	lcall	__gptrget
   0ED8 FB                 3393 	mov	r3,a
   0ED9 A3                 3394 	inc	dptr
   0EDA 12 AE 30           3395 	lcall	__gptrget
   0EDD FC                 3396 	mov	r4,a
                           3397 ;     genPlus
   0EDE 74 08              3398 	mov	a,#0x08
   0EE0 25 02              3399 	add	a,ar2
   0EE2 FA                 3400 	mov	r2,a
   0EE3 74 00              3401 	mov	a,#0x00
   0EE5 35 03              3402 	addc	a,ar3
   0EE7 FB                 3403 	mov	r3,a
                           3404 ;     genPointerGet
                           3405 ;     genGenPointerGet
   0EE8 8A 82              3406 	mov	dpl,r2
   0EEA 8B 83              3407 	mov	dph,r3
   0EEC 8C F0              3408 	mov	b,r4
   0EEE 12 AE 30           3409 	lcall	__gptrget
   0EF1 FA                 3410 	mov	r2,a
   0EF2 A3                 3411 	inc	dptr
   0EF3 12 AE 30           3412 	lcall	__gptrget
   0EF6 FB                 3413 	mov	r3,a
   0EF7 A3                 3414 	inc	dptr
   0EF8 12 AE 30           3415 	lcall	__gptrget
   0EFB FC                 3416 	mov	r4,a
   0EFC 02 0F 05           3417 	ljmp	00112$
   0EFF                    3418 00111$:
                           3419 ;     genAssign
   0EFF 7A 00              3420 	mov	r2,#0x00
   0F01 7B 00              3421 	mov	r3,#0x00
   0F03 7C 00              3422 	mov	r4,#0x00
   0F05                    3423 00112$:
                           3424 ;     genAssign
                           3425 ;     genAssign
   0F05 E5 12              3426 	mov	a,_bp
   0F07 24 01              3427 	add	a,#0x01
   0F09 F8                 3428 	mov	r0,a
   0F0A A6 02              3429 	mov	@r0,ar2
   0F0C 08                 3430 	inc	r0
   0F0D A6 03              3431 	mov	@r0,ar3
   0F0F 08                 3432 	inc	r0
   0F10 A6 04              3433 	mov	@r0,ar4
                           3434 ;../../Source/tasks.c:1206: vListRemove( &( pxUnblockedTCB->xEventListItem ) );
                           3435 ;     genPlus
   0F12 E5 12              3436 	mov	a,_bp
   0F14 24 01              3437 	add	a,#0x01
   0F16 F8                 3438 	mov	r0,a
   0F17 74 27              3439 	mov	a,#0x27
   0F19 26                 3440 	add	a,@r0
   0F1A FD                 3441 	mov	r5,a
   0F1B 74 00              3442 	mov	a,#0x00
   0F1D 08                 3443 	inc	r0
   0F1E 36                 3444 	addc	a,@r0
   0F1F FE                 3445 	mov	r6,a
   0F20 08                 3446 	inc	r0
   0F21 86 07              3447 	mov	ar7,@r0
                           3448 ;     genCall
   0F23 8D 82              3449 	mov	dpl,r5
   0F25 8E 83              3450 	mov	dph,r6
   0F27 8F F0              3451 	mov	b,r7
   0F29 12 30 07           3452 	lcall	_vListRemove
                           3453 ;../../Source/tasks.c:1208: if( ucSchedulerSuspended == ( unsigned portCHAR ) pdFALSE )
                           3454 ;     genAssign
   0F2C 90 1D 17           3455 	mov	dptr,#_ucSchedulerSuspended
   0F2F E0                 3456 	movx	a,@dptr
   0F30 FD                 3457 	mov	r5,a
                           3458 ;     genCmpEq
   0F31 BD 00 02           3459 	cjne	r5,#0x00,00121$
   0F34 80 03              3460 	sjmp	00122$
   0F36                    3461 00121$:
   0F36 02 0F C9           3462 	ljmp	00104$
   0F39                    3463 00122$:
                           3464 ;../../Source/tasks.c:1210: vListRemove( &( pxUnblockedTCB->xGenericListItem ) );
                           3465 ;     genPlus
   0F39 E5 12              3466 	mov	a,_bp
   0F3B 24 01              3467 	add	a,#0x01
   0F3D F8                 3468 	mov	r0,a
   0F3E 74 19              3469 	mov	a,#0x19
   0F40 26                 3470 	add	a,@r0
   0F41 FD                 3471 	mov	r5,a
   0F42 74 00              3472 	mov	a,#0x00
   0F44 08                 3473 	inc	r0
   0F45 36                 3474 	addc	a,@r0
   0F46 FE                 3475 	mov	r6,a
   0F47 08                 3476 	inc	r0
   0F48 86 07              3477 	mov	ar7,@r0
                           3478 ;     genCall
   0F4A 8D 82              3479 	mov	dpl,r5
   0F4C 8E 83              3480 	mov	dph,r6
   0F4E 8F F0              3481 	mov	b,r7
   0F50 12 30 07           3482 	lcall	_vListRemove
                           3483 ;../../Source/tasks.c:1211: prvAddTaskToReadyQueue( pxUnblockedTCB );
                           3484 ;     genPlus
   0F53 E5 12              3485 	mov	a,_bp
   0F55 24 01              3486 	add	a,#0x01
   0F57 F8                 3487 	mov	r0,a
   0F58 74 19              3488 	mov	a,#0x19
   0F5A 26                 3489 	add	a,@r0
   0F5B FD                 3490 	mov	r5,a
   0F5C 74 00              3491 	mov	a,#0x00
   0F5E 08                 3492 	inc	r0
   0F5F 36                 3493 	addc	a,@r0
   0F60 FE                 3494 	mov	r6,a
   0F61 08                 3495 	inc	r0
   0F62 86 07              3496 	mov	ar7,@r0
                           3497 ;     genPointerSet
                           3498 ;     genGenPointerSet
   0F64 8D 82              3499 	mov	dpl,r5
   0F66 8E 83              3500 	mov	dph,r6
   0F68 8F F0              3501 	mov	b,r7
   0F6A 74 00              3502 	mov	a,#0x00
   0F6C 12 A3 97           3503 	lcall	__gptrput
   0F6F A3                 3504 	inc	dptr
   0F70 74 00              3505 	mov	a,#0x00
   0F72 12 A3 97           3506 	lcall	__gptrput
                           3507 ;     genPlus
   0F75 E5 12              3508 	mov	a,_bp
   0F77 24 01              3509 	add	a,#0x01
   0F79 F8                 3510 	mov	r0,a
   0F7A 74 18              3511 	mov	a,#0x18
   0F7C 26                 3512 	add	a,@r0
   0F7D FA                 3513 	mov	r2,a
   0F7E 74 00              3514 	mov	a,#0x00
   0F80 08                 3515 	inc	r0
   0F81 36                 3516 	addc	a,@r0
   0F82 FB                 3517 	mov	r3,a
   0F83 08                 3518 	inc	r0
   0F84 86 04              3519 	mov	ar4,@r0
                           3520 ;     genPointerGet
                           3521 ;     genGenPointerGet
   0F86 8A 82              3522 	mov	dpl,r2
   0F88 8B 83              3523 	mov	dph,r3
   0F8A 8C F0              3524 	mov	b,r4
   0F8C 12 AE 30           3525 	lcall	__gptrget
   0F8F FA                 3526 	mov	r2,a
                           3527 ;     genAssign
   0F90 90 1D 15           3528 	mov	dptr,#_ucTopReadyPriority
   0F93 E0                 3529 	movx	a,@dptr
   0F94 FB                 3530 	mov	r3,a
                           3531 ;     genCmpGt
                           3532 ;     genCmp
   0F95 C3                 3533 	clr	c
   0F96 EB                 3534 	mov	a,r3
   0F97 9A                 3535 	subb	a,r2
                           3536 ;     genIfxJump
   0F98 40 03              3537 	jc	00123$
   0F9A 02 0F A2           3538 	ljmp	00102$
   0F9D                    3539 00123$:
                           3540 ;     genAssign
   0F9D 90 1D 15           3541 	mov	dptr,#_ucTopReadyPriority
   0FA0 EA                 3542 	mov	a,r2
   0FA1 F0                 3543 	movx	@dptr,a
   0FA2                    3544 00102$:
                           3545 ;     genMult
                           3546 ;     genMultOneByte
   0FA2 EA                 3547 	mov	a,r2
   0FA3 75 F0 16           3548 	mov	b,#0x16
   0FA6 A4                 3549 	mul	ab
                           3550 ;     genPlus
   0FA7 24 00              3551 	add	a,#_pxReadyTasksLists
   0FA9 FA                 3552 	mov	r2,a
   0FAA E5 F0              3553 	mov	a,b
   0FAC 34 00              3554 	addc	a,#(_pxReadyTasksLists >> 8)
   0FAE FB                 3555 	mov	r3,a
                           3556 ;     genCast
   0FAF 7C 01              3557 	mov	r4,#0x1
                           3558 ;     genIpush
   0FB1 C0 05              3559 	push	ar5
   0FB3 C0 06              3560 	push	ar6
   0FB5 C0 07              3561 	push	ar7
                           3562 ;     genCall
   0FB7 8A 82              3563 	mov	dpl,r2
   0FB9 8B 83              3564 	mov	dph,r3
   0FBB 8C F0              3565 	mov	b,r4
   0FBD 12 2A F6           3566 	lcall	_vListInsertEnd
   0FC0 15 81              3567 	dec	sp
   0FC2 15 81              3568 	dec	sp
   0FC4 15 81              3569 	dec	sp
   0FC6 02 0F F2           3570 	ljmp	00105$
   0FC9                    3571 00104$:
                           3572 ;../../Source/tasks.c:1217: vListInsertEnd( ( xList * ) &( xPendingReadyList ), &( pxUnblockedTCB->xEventListItem ) );
                           3573 ;     genPlus
   0FC9 E5 12              3574 	mov	a,_bp
   0FCB 24 01              3575 	add	a,#0x01
   0FCD F8                 3576 	mov	r0,a
   0FCE 74 27              3577 	mov	a,#0x27
   0FD0 26                 3578 	add	a,@r0
   0FD1 FA                 3579 	mov	r2,a
   0FD2 74 00              3580 	mov	a,#0x00
   0FD4 08                 3581 	inc	r0
   0FD5 36                 3582 	addc	a,@r0
   0FD6 FB                 3583 	mov	r3,a
   0FD7 08                 3584 	inc	r0
   0FD8 86 04              3585 	mov	ar4,@r0
                           3586 ;     genIpush
   0FDA C0 02              3587 	push	ar2
   0FDC C0 03              3588 	push	ar3
   0FDE C0 04              3589 	push	ar4
                           3590 ;     genCall
   0FE0 75 82 8A           3591 	mov	dpl,#_xPendingReadyList
   0FE3 75 83 00           3592 	mov	dph,#(_xPendingReadyList >> 8)
   0FE6 75 F0 01           3593 	mov	b,#0x01
   0FE9 12 2A F6           3594 	lcall	_vListInsertEnd
   0FEC 15 81              3595 	dec	sp
   0FEE 15 81              3596 	dec	sp
   0FF0 15 81              3597 	dec	sp
   0FF2                    3598 00105$:
                           3599 ;../../Source/tasks.c:1220: if( pxUnblockedTCB->ucPriority > pxCurrentTCB->ucPriority )
                           3600 ;     genPlus
   0FF2 E5 12              3601 	mov	a,_bp
   0FF4 24 01              3602 	add	a,#0x01
   0FF6 F8                 3603 	mov	r0,a
   0FF7 74 18              3604 	mov	a,#0x18
   0FF9 26                 3605 	add	a,@r0
   0FFA FA                 3606 	mov	r2,a
   0FFB 74 00              3607 	mov	a,#0x00
   0FFD 08                 3608 	inc	r0
   0FFE 36                 3609 	addc	a,@r0
   0FFF FB                 3610 	mov	r3,a
   1000 08                 3611 	inc	r0
   1001 86 04              3612 	mov	ar4,@r0
                           3613 ;     genPointerGet
                           3614 ;     genGenPointerGet
   1003 8A 82              3615 	mov	dpl,r2
   1005 8B 83              3616 	mov	dph,r3
   1007 8C F0              3617 	mov	b,r4
   1009 12 AE 30           3618 	lcall	__gptrget
   100C FA                 3619 	mov	r2,a
                           3620 ;     genAssign
   100D 90 1D 0B           3621 	mov	dptr,#_pxCurrentTCB
   1010 E0                 3622 	movx	a,@dptr
   1011 FB                 3623 	mov	r3,a
   1012 A3                 3624 	inc	dptr
   1013 E0                 3625 	movx	a,@dptr
   1014 FC                 3626 	mov	r4,a
   1015 A3                 3627 	inc	dptr
   1016 E0                 3628 	movx	a,@dptr
   1017 FD                 3629 	mov	r5,a
                           3630 ;     genPlus
   1018 74 18              3631 	mov	a,#0x18
   101A 25 03              3632 	add	a,ar3
   101C FB                 3633 	mov	r3,a
   101D 74 00              3634 	mov	a,#0x00
   101F 35 04              3635 	addc	a,ar4
   1021 FC                 3636 	mov	r4,a
                           3637 ;     genPointerGet
                           3638 ;     genGenPointerGet
   1022 8B 82              3639 	mov	dpl,r3
   1024 8C 83              3640 	mov	dph,r4
   1026 8D F0              3641 	mov	b,r5
   1028 12 AE 30           3642 	lcall	__gptrget
   102B FB                 3643 	mov	r3,a
                           3644 ;     genCmpGt
                           3645 ;     genCmp
   102C C3                 3646 	clr	c
   102D EB                 3647 	mov	a,r3
   102E 9A                 3648 	subb	a,r2
                           3649 ;     genIfxJump
   102F 40 03              3650 	jc	00124$
   1031 02 10 3A           3651 	ljmp	00107$
   1034                    3652 00124$:
                           3653 ;../../Source/tasks.c:1226: return ( signed portCHAR ) pdTRUE;
                           3654 ;     genRet
   1034 75 82 01           3655 	mov	dpl,#0x01
   1037 02 10 3D           3656 	ljmp	00109$
   103A                    3657 00107$:
                           3658 ;../../Source/tasks.c:1230: return ( signed portCHAR ) pdFALSE;
                           3659 ;     genRet
   103A 75 82 00           3660 	mov	dpl,#0x00
   103D                    3661 00109$:
   103D 85 12 81           3662 	mov	sp,_bp
   1040 D0 12              3663 	pop	_bp
   1042 22                 3664 	ret
                           3665 ;------------------------------------------------------------
                           3666 ;Allocation info for local variables in function 'prvIdleTask'
                           3667 ;------------------------------------------------------------
                           3668 ;pvParameters              Allocated to registers 
                           3669 ;------------------------------------------------------------
                           3670 ;../../Source/tasks.c:1242: static void prvIdleTask( void *pvParameters )
                           3671 ;	-----------------------------------------
                           3672 ;	 function prvIdleTask
                           3673 ;	-----------------------------------------
   1043                    3674 _prvIdleTask:
   1043 C0 12              3675 	push	_bp
   1045 85 81 12           3676 	mov	_bp,sp
                           3677 ;../../Source/tasks.c:1245: ( void ) pvParameters;
   1048                    3678 00104$:
                           3679 ;../../Source/tasks.c:1250: prvCheckTasksWaitingTermination();
                           3680 ;     genCall
   1048 12 13 17           3681 	lcall	_prvCheckTasksWaitingTermination
                           3682 ;../../Source/tasks.c:1252: if( sUsingPreemption == pdFALSE )
                           3683 ;     genAssign
   104B 90 1D 0E           3684 	mov	dptr,#_sUsingPreemption
   104E E0                 3685 	movx	a,@dptr
   104F FA                 3686 	mov	r2,a
   1050 A3                 3687 	inc	dptr
   1051 E0                 3688 	movx	a,@dptr
   1052 FB                 3689 	mov	r3,a
                           3690 ;     genCmpEq
   1053 BA 00 05           3691 	cjne	r2,#0x00,00110$
   1056 BB 00 02           3692 	cjne	r3,#0x00,00110$
   1059 80 03              3693 	sjmp	00111$
   105B                    3694 00110$:
   105B 02 10 48           3695 	ljmp	00104$
   105E                    3696 00111$:
                           3697 ;../../Source/tasks.c:1258: taskYIELD();	
                           3698 ;     genCall
   105E 12 17 01           3699 	lcall	_vPortYield
   1061 02 10 48           3700 	ljmp	00104$
   1064                    3701 00106$:
   1064 85 12 81           3702 	mov	sp,_bp
   1067 D0 12              3703 	pop	_bp
   1069 22                 3704 	ret
                           3705 ;------------------------------------------------------------
                           3706 ;Allocation info for local variables in function 'prvInitialiseTCBVariables'
                           3707 ;------------------------------------------------------------
                           3708 ;usStackDepth              Allocated to stack - offset -4
                           3709 ;pcName                    Allocated to stack - offset -7
                           3710 ;ucPriority                Allocated to stack - offset -8
                           3711 ;pxTCB                     Allocated to stack - offset 1
                           3712 ;------------------------------------------------------------
                           3713 ;../../Source/tasks.c:1275: static void prvInitialiseTCBVariables( tskTCB *pxTCB, unsigned portSHORT usStackDepth, const signed portCHAR * const pcName, unsigned portCHAR ucPriority )
                           3714 ;	-----------------------------------------
                           3715 ;	 function prvInitialiseTCBVariables
                           3716 ;	-----------------------------------------
   106A                    3717 _prvInitialiseTCBVariables:
   106A C0 12              3718 	push	_bp
   106C 85 81 12           3719 	mov	_bp,sp
                           3720 ;     genReceive
   106F C0 82              3721 	push	dpl
   1071 C0 83              3722 	push	dph
   1073 C0 F0              3723 	push	b
                           3724 ;../../Source/tasks.c:1277: pxTCB->usStackDepth = usStackDepth;
                           3725 ;     genPlus
   1075 E5 12              3726 	mov	a,_bp
   1077 24 01              3727 	add	a,#0x01
   1079 F8                 3728 	mov	r0,a
   107A 74 06              3729 	mov	a,#0x06
   107C 26                 3730 	add	a,@r0
   107D FD                 3731 	mov	r5,a
   107E 74 00              3732 	mov	a,#0x00
   1080 08                 3733 	inc	r0
   1081 36                 3734 	addc	a,@r0
   1082 FE                 3735 	mov	r6,a
   1083 08                 3736 	inc	r0
   1084 86 07              3737 	mov	ar7,@r0
                           3738 ;     genPointerSet
                           3739 ;     genGenPointerSet
   1086 8D 82              3740 	mov	dpl,r5
   1088 8E 83              3741 	mov	dph,r6
   108A 8F F0              3742 	mov	b,r7
   108C E5 12              3743 	mov	a,_bp
   108E 24 FC              3744 	add	a,#0xfc
   1090 F8                 3745 	mov	r0,a
   1091 E6                 3746 	mov	a,@r0
   1092 12 A3 97           3747 	lcall	__gptrput
   1095 A3                 3748 	inc	dptr
   1096 08                 3749 	inc	r0
   1097 E6                 3750 	mov	a,@r0
   1098 12 A3 97           3751 	lcall	__gptrput
                           3752 ;../../Source/tasks.c:1280: if( strlen( pcName ) < ( unsigned portSHORT ) tskMAX_TASK_NAME_LEN )
                           3753 ;     genCall
   109B E5 12              3754 	mov	a,_bp
   109D 24 F9              3755 	add	a,#0xf9
   109F F8                 3756 	mov	r0,a
   10A0 86 82              3757 	mov	dpl,@r0
   10A2 08                 3758 	inc	r0
   10A3 86 83              3759 	mov	dph,@r0
   10A5 08                 3760 	inc	r0
   10A6 86 F0              3761 	mov	b,@r0
   10A8 12 AD FE           3762 	lcall	_strlen
   10AB AD 82              3763 	mov	r5,dpl
   10AD AE 83              3764 	mov	r6,dph
                           3765 ;     genCmpLt
                           3766 ;     genCmp
   10AF C3                 3767 	clr	c
   10B0 ED                 3768 	mov	a,r5
   10B1 94 10              3769 	subb	a,#0x10
   10B3 EE                 3770 	mov	a,r6
   10B4 94 00              3771 	subb	a,#0x00
                           3772 ;     genIfxJump
   10B6 40 03              3773 	jc	00110$
   10B8 02 10 FF           3774 	ljmp	00102$
   10BB                    3775 00110$:
                           3776 ;../../Source/tasks.c:1282: portENTER_CRITICAL();
                           3777 ;     genInline
   10BB C0 E0 C0 A8        3778 	 push ACC push IE 
                           3779 ;     genAssign
   10BF C2 AF              3780 	clr	_EA
                           3781 ;../../Source/tasks.c:1283: strcpy( pxTCB->pcTaskName, pcName );
                           3782 ;     genPlus
   10C1 E5 12              3783 	mov	a,_bp
   10C3 24 01              3784 	add	a,#0x01
   10C5 F8                 3785 	mov	r0,a
   10C6 74 08              3786 	mov	a,#0x08
   10C8 26                 3787 	add	a,@r0
   10C9 FD                 3788 	mov	r5,a
   10CA 74 00              3789 	mov	a,#0x00
   10CC 08                 3790 	inc	r0
   10CD 36                 3791 	addc	a,@r0
   10CE FE                 3792 	mov	r6,a
   10CF 08                 3793 	inc	r0
   10D0 86 07              3794 	mov	ar7,@r0
                           3795 ;     genIpush
   10D2 E5 12              3796 	mov	a,_bp
   10D4 24 F9              3797 	add	a,#0xf9
   10D6 F8                 3798 	mov	r0,a
   10D7 E6                 3799 	mov	a,@r0
   10D8 C0 E0              3800 	push	acc
   10DA 08                 3801 	inc	r0
   10DB E6                 3802 	mov	a,@r0
   10DC C0 E0              3803 	push	acc
   10DE 08                 3804 	inc	r0
   10DF E6                 3805 	mov	a,@r0
   10E0 C0 E0              3806 	push	acc
                           3807 ;     genCall
   10E2 8D 82              3808 	mov	dpl,r5
   10E4 8E 83              3809 	mov	dph,r6
   10E6 8F F0              3810 	mov	b,r7
   10E8 12 A3 2B           3811 	lcall	_strcpy
   10EB 15 81              3812 	dec	sp
   10ED 15 81              3813 	dec	sp
   10EF 15 81              3814 	dec	sp
                           3815 ;../../Source/tasks.c:1284: portEXIT_CRITICAL();
                           3816 ;     genInline
   10F1 D0 E0              3817 	 pop ACC 
                           3818 ;     genAnd
   10F3 53 E0 80           3819 	anl	_ACC,#0x80
                           3820 ;     genOr
   10F6 E5 E0              3821 	mov	a,_ACC
   10F8 42 A8              3822 	orl	_IE,a
                           3823 ;     genInline
   10FA D0 E0              3824 	 pop ACC 
   10FC 02 11 69           3825 	ljmp	00103$
   10FF                    3826 00102$:
                           3827 ;../../Source/tasks.c:1288: portENTER_CRITICAL();
                           3828 ;     genInline
   10FF C0 E0 C0 A8        3829 	 push ACC push IE 
                           3830 ;     genAssign
   1103 C2 AF              3831 	clr	_EA
                           3832 ;../../Source/tasks.c:1289: strncpy( pxTCB->pcTaskName, pcName, ( unsigned portSHORT ) tskMAX_TASK_NAME_LEN );
                           3833 ;     genPlus
   1105 E5 12              3834 	mov	a,_bp
   1107 24 01              3835 	add	a,#0x01
   1109 F8                 3836 	mov	r0,a
   110A 74 08              3837 	mov	a,#0x08
   110C 26                 3838 	add	a,@r0
   110D FD                 3839 	mov	r5,a
   110E 74 00              3840 	mov	a,#0x00
   1110 08                 3841 	inc	r0
   1111 36                 3842 	addc	a,@r0
   1112 FE                 3843 	mov	r6,a
   1113 08                 3844 	inc	r0
   1114 86 07              3845 	mov	ar7,@r0
                           3846 ;     genIpush
   1116 C0 05              3847 	push	ar5
   1118 C0 06              3848 	push	ar6
   111A C0 07              3849 	push	ar7
   111C 74 10              3850 	mov	a,#0x10
   111E C0 E0              3851 	push	acc
   1120 74 00              3852 	mov	a,#0x00
   1122 C0 E0              3853 	push	acc
                           3854 ;     genIpush
   1124 E5 12              3855 	mov	a,_bp
   1126 24 F9              3856 	add	a,#0xf9
   1128 F8                 3857 	mov	r0,a
   1129 E6                 3858 	mov	a,@r0
   112A C0 E0              3859 	push	acc
   112C 08                 3860 	inc	r0
   112D E6                 3861 	mov	a,@r0
   112E C0 E0              3862 	push	acc
   1130 08                 3863 	inc	r0
   1131 E6                 3864 	mov	a,@r0
   1132 C0 E0              3865 	push	acc
                           3866 ;     genCall
   1134 8D 82              3867 	mov	dpl,r5
   1136 8E 83              3868 	mov	dph,r6
   1138 8F F0              3869 	mov	b,r7
   113A 12 AD 67           3870 	lcall	_strncpy
   113D E5 81              3871 	mov	a,sp
   113F 24 FB              3872 	add	a,#0xfb
   1141 F5 81              3873 	mov	sp,a
   1143 D0 07              3874 	pop	ar7
   1145 D0 06              3875 	pop	ar6
   1147 D0 05              3876 	pop	ar5
                           3877 ;../../Source/tasks.c:1290: portEXIT_CRITICAL();
                           3878 ;     genInline
   1149 D0 E0              3879 	 pop ACC 
                           3880 ;     genAnd
   114B 53 E0 80           3881 	anl	_ACC,#0x80
                           3882 ;     genOr
   114E E5 E0              3883 	mov	a,_ACC
   1150 42 A8              3884 	orl	_IE,a
                           3885 ;     genInline
   1152 D0 E0              3886 	 pop ACC 
                           3887 ;../../Source/tasks.c:1291: pxTCB->pcTaskName[ ( unsigned portSHORT ) tskMAX_TASK_NAME_LEN - ( unsigned portSHORT ) 1 ] = '\0';
                           3888 ;     genPlus
   1154 74 0F              3889 	mov	a,#0x0F
   1156 25 05              3890 	add	a,ar5
   1158 FD                 3891 	mov	r5,a
   1159 74 00              3892 	mov	a,#0x00
   115B 35 06              3893 	addc	a,ar6
   115D FE                 3894 	mov	r6,a
                           3895 ;     genPointerSet
                           3896 ;     genGenPointerSet
   115E 8D 82              3897 	mov	dpl,r5
   1160 8E 83              3898 	mov	dph,r6
   1162 8F F0              3899 	mov	b,r7
   1164 74 00              3900 	mov	a,#0x00
   1166 12 A3 97           3901 	lcall	__gptrput
   1169                    3902 00103$:
                           3903 ;../../Source/tasks.c:1295: if( ucPriority >= ( unsigned portCHAR ) portMAX_PRIORITIES )
                           3904 ;     genCmpLt
   1169 E5 12              3905 	mov	a,_bp
   116B 24 F8              3906 	add	a,#0xf8
   116D F8                 3907 	mov	r0,a
                           3908 ;     genCmp
   116E B6 04 00           3909 	cjne	@r0,#0x04,00111$
   1171                    3910 00111$:
                           3911 ;     genIfxJump
   1171 50 03              3912 	jnc	00112$
   1173 02 11 7D           3913 	ljmp	00105$
   1176                    3914 00112$:
                           3915 ;../../Source/tasks.c:1297: ucPriority = ( unsigned portCHAR ) portMAX_PRIORITIES - ( unsigned portCHAR ) 1;
                           3916 ;     genAssign
   1176 E5 12              3917 	mov	a,_bp
   1178 24 F8              3918 	add	a,#0xf8
   117A F8                 3919 	mov	r0,a
   117B 76 03              3920 	mov	@r0,#0x03
   117D                    3921 00105$:
                           3922 ;../../Source/tasks.c:1299: pxTCB->ucPriority = ucPriority;
                           3923 ;     genPlus
   117D E5 12              3924 	mov	a,_bp
   117F 24 01              3925 	add	a,#0x01
   1181 F8                 3926 	mov	r0,a
   1182 74 18              3927 	mov	a,#0x18
   1184 26                 3928 	add	a,@r0
   1185 FD                 3929 	mov	r5,a
   1186 74 00              3930 	mov	a,#0x00
   1188 08                 3931 	inc	r0
   1189 36                 3932 	addc	a,@r0
   118A FE                 3933 	mov	r6,a
   118B 08                 3934 	inc	r0
   118C 86 07              3935 	mov	ar7,@r0
                           3936 ;     genPointerSet
                           3937 ;     genGenPointerSet
   118E 8D 82              3938 	mov	dpl,r5
   1190 8E 83              3939 	mov	dph,r6
   1192 8F F0              3940 	mov	b,r7
   1194 E5 12              3941 	mov	a,_bp
   1196 24 F8              3942 	add	a,#0xf8
   1198 F8                 3943 	mov	r0,a
   1199 E6                 3944 	mov	a,@r0
   119A 12 A3 97           3945 	lcall	__gptrput
                           3946 ;../../Source/tasks.c:1301: vListInitialiseItem( &( pxTCB->xGenericListItem ) );
                           3947 ;     genPlus
   119D E5 12              3948 	mov	a,_bp
   119F 24 01              3949 	add	a,#0x01
   11A1 F8                 3950 	mov	r0,a
   11A2 74 19              3951 	mov	a,#0x19
   11A4 26                 3952 	add	a,@r0
   11A5 FD                 3953 	mov	r5,a
   11A6 74 00              3954 	mov	a,#0x00
   11A8 08                 3955 	inc	r0
   11A9 36                 3956 	addc	a,@r0
   11AA FE                 3957 	mov	r6,a
   11AB 08                 3958 	inc	r0
   11AC 86 07              3959 	mov	ar7,@r0
                           3960 ;     genCall
   11AE 8D 82              3961 	mov	dpl,r5
   11B0 8E 83              3962 	mov	dph,r6
   11B2 8F F0              3963 	mov	b,r7
   11B4 12 2A C4           3964 	lcall	_vListInitialiseItem
                           3965 ;../../Source/tasks.c:1302: vListInitialiseItem( &( pxTCB->xEventListItem ) );
                           3966 ;     genPlus
   11B7 E5 12              3967 	mov	a,_bp
   11B9 24 01              3968 	add	a,#0x01
   11BB F8                 3969 	mov	r0,a
   11BC 74 27              3970 	mov	a,#0x27
   11BE 26                 3971 	add	a,@r0
   11BF FD                 3972 	mov	r5,a
   11C0 74 00              3973 	mov	a,#0x00
   11C2 08                 3974 	inc	r0
   11C3 36                 3975 	addc	a,@r0
   11C4 FE                 3976 	mov	r6,a
   11C5 08                 3977 	inc	r0
   11C6 86 07              3978 	mov	ar7,@r0
                           3979 ;     genCall
   11C8 8D 82              3980 	mov	dpl,r5
   11CA 8E 83              3981 	mov	dph,r6
   11CC 8F F0              3982 	mov	b,r7
   11CE 12 2A C4           3983 	lcall	_vListInitialiseItem
                           3984 ;../../Source/tasks.c:1306: listSET_LIST_ITEM_OWNER( &( pxTCB->xGenericListItem ), pxTCB );
                           3985 ;     genPlus
   11D1 E5 12              3986 	mov	a,_bp
   11D3 24 01              3987 	add	a,#0x01
   11D5 F8                 3988 	mov	r0,a
   11D6 74 19              3989 	mov	a,#0x19
   11D8 26                 3990 	add	a,@r0
   11D9 FD                 3991 	mov	r5,a
   11DA 74 00              3992 	mov	a,#0x00
   11DC 08                 3993 	inc	r0
   11DD 36                 3994 	addc	a,@r0
   11DE FE                 3995 	mov	r6,a
   11DF 08                 3996 	inc	r0
   11E0 86 07              3997 	mov	ar7,@r0
                           3998 ;     genPlus
   11E2 74 08              3999 	mov	a,#0x08
   11E4 25 05              4000 	add	a,ar5
   11E6 FD                 4001 	mov	r5,a
   11E7 74 00              4002 	mov	a,#0x00
   11E9 35 06              4003 	addc	a,ar6
   11EB FE                 4004 	mov	r6,a
                           4005 ;     genPointerSet
                           4006 ;     genGenPointerSet
   11EC 8D 82              4007 	mov	dpl,r5
   11EE 8E 83              4008 	mov	dph,r6
   11F0 8F F0              4009 	mov	b,r7
   11F2 E5 12              4010 	mov	a,_bp
   11F4 24 01              4011 	add	a,#0x01
   11F6 F8                 4012 	mov	r0,a
   11F7 E6                 4013 	mov	a,@r0
   11F8 12 A3 97           4014 	lcall	__gptrput
   11FB A3                 4015 	inc	dptr
   11FC 08                 4016 	inc	r0
   11FD E6                 4017 	mov	a,@r0
   11FE 12 A3 97           4018 	lcall	__gptrput
   1201 A3                 4019 	inc	dptr
   1202 08                 4020 	inc	r0
   1203 E6                 4021 	mov	a,@r0
   1204 12 A3 97           4022 	lcall	__gptrput
                           4023 ;../../Source/tasks.c:1309: listSET_LIST_ITEM_VALUE( &( pxTCB->xEventListItem ), ( portTickType ) ucPriority );
                           4024 ;     genPlus
   1207 E5 12              4025 	mov	a,_bp
   1209 24 01              4026 	add	a,#0x01
   120B F8                 4027 	mov	r0,a
   120C 74 27              4028 	mov	a,#0x27
   120E 26                 4029 	add	a,@r0
   120F FD                 4030 	mov	r5,a
   1210 74 00              4031 	mov	a,#0x00
   1212 08                 4032 	inc	r0
   1213 36                 4033 	addc	a,@r0
   1214 FE                 4034 	mov	r6,a
   1215 08                 4035 	inc	r0
   1216 86 07              4036 	mov	ar7,@r0
                           4037 ;     genCast
   1218 E5 12              4038 	mov	a,_bp
   121A 24 F8              4039 	add	a,#0xf8
   121C F8                 4040 	mov	r0,a
   121D 86 02              4041 	mov	ar2,@r0
   121F 7B 00              4042 	mov	r3,#0x00
                           4043 ;     genPointerSet
                           4044 ;     genGenPointerSet
   1221 8D 82              4045 	mov	dpl,r5
   1223 8E 83              4046 	mov	dph,r6
   1225 8F F0              4047 	mov	b,r7
   1227 EA                 4048 	mov	a,r2
   1228 12 A3 97           4049 	lcall	__gptrput
   122B A3                 4050 	inc	dptr
   122C EB                 4051 	mov	a,r3
   122D 12 A3 97           4052 	lcall	__gptrput
                           4053 ;../../Source/tasks.c:1310: listSET_LIST_ITEM_OWNER( &( pxTCB->xEventListItem ), pxTCB );
                           4054 ;     genPlus
   1230 74 08              4055 	mov	a,#0x08
   1232 25 05              4056 	add	a,ar5
   1234 FD                 4057 	mov	r5,a
   1235 74 00              4058 	mov	a,#0x00
   1237 35 06              4059 	addc	a,ar6
   1239 FE                 4060 	mov	r6,a
                           4061 ;     genPointerSet
                           4062 ;     genGenPointerSet
   123A 8D 82              4063 	mov	dpl,r5
   123C 8E 83              4064 	mov	dph,r6
   123E 8F F0              4065 	mov	b,r7
   1240 E5 12              4066 	mov	a,_bp
   1242 24 01              4067 	add	a,#0x01
   1244 F8                 4068 	mov	r0,a
   1245 E6                 4069 	mov	a,@r0
   1246 12 A3 97           4070 	lcall	__gptrput
   1249 A3                 4071 	inc	dptr
   124A 08                 4072 	inc	r0
   124B E6                 4073 	mov	a,@r0
   124C 12 A3 97           4074 	lcall	__gptrput
   124F A3                 4075 	inc	dptr
   1250 08                 4076 	inc	r0
   1251 E6                 4077 	mov	a,@r0
   1252 12 A3 97           4078 	lcall	__gptrput
   1255                    4079 00106$:
   1255 85 12 81           4080 	mov	sp,_bp
   1258 D0 12              4081 	pop	_bp
   125A 22                 4082 	ret
                           4083 ;------------------------------------------------------------
                           4084 ;Allocation info for local variables in function 'prvInitialiseTaskLists'
                           4085 ;------------------------------------------------------------
                           4086 ;ucPriority                Allocated to registers r2 
                           4087 ;sReturn                   Allocated to registers r2 r3 
                           4088 ;------------------------------------------------------------
                           4089 ;../../Source/tasks.c:1314: static portSHORT prvInitialiseTaskLists( void )
                           4090 ;	-----------------------------------------
                           4091 ;	 function prvInitialiseTaskLists
                           4092 ;	-----------------------------------------
   125B                    4093 _prvInitialiseTaskLists:
   125B C0 12              4094 	push	_bp
   125D 85 81 12           4095 	mov	_bp,sp
                           4096 ;../../Source/tasks.c:1319: for( ucPriority = ( unsigned portCHAR) 0; ucPriority < ( unsigned portCHAR ) portMAX_PRIORITIES; ucPriority++ )
                           4097 ;     genAssign
   1260 7A 00              4098 	mov	r2,#0x00
   1262                    4099 00101$:
                           4100 ;     genCmpLt
                           4101 ;     genCmp
   1262 BA 04 00           4102 	cjne	r2,#0x04,00109$
   1265                    4103 00109$:
                           4104 ;     genIfxJump
   1265 40 03              4105 	jc	00110$
   1267 02 12 8A           4106 	ljmp	00104$
   126A                    4107 00110$:
                           4108 ;../../Source/tasks.c:1321: vListInitialise( ( xList * ) &( pxReadyTasksLists[ ucPriority ] ) );
                           4109 ;     genMult
                           4110 ;     genMultOneByte
   126A EA                 4111 	mov	a,r2
   126B 75 F0 16           4112 	mov	b,#0x16
   126E A4                 4113 	mul	ab
                           4114 ;     genPlus
   126F 24 00              4115 	add	a,#_pxReadyTasksLists
   1271 FB                 4116 	mov	r3,a
   1272 E5 F0              4117 	mov	a,b
   1274 34 00              4118 	addc	a,#(_pxReadyTasksLists >> 8)
   1276 FC                 4119 	mov	r4,a
                           4120 ;     genCast
   1277 7D 01              4121 	mov	r5,#0x1
                           4122 ;     genCall
   1279 8B 82              4123 	mov	dpl,r3
   127B 8C 83              4124 	mov	dph,r4
   127D 8D F0              4125 	mov	b,r5
   127F C0 02              4126 	push	ar2
   1281 12 29 62           4127 	lcall	_vListInitialise
   1284 D0 02              4128 	pop	ar2
                           4129 ;../../Source/tasks.c:1319: for( ucPriority = ( unsigned portCHAR) 0; ucPriority < ( unsigned portCHAR ) portMAX_PRIORITIES; ucPriority++ )
                           4130 ;     genPlus
                           4131 ;     genPlusIncr
   1286 0A                 4132 	inc	r2
   1287 02 12 62           4133 	ljmp	00101$
   128A                    4134 00104$:
                           4135 ;../../Source/tasks.c:1324: vListInitialise( ( xList * ) &xDelayedTaskList1 );
                           4136 ;     genCall
   128A 75 82 58           4137 	mov	dpl,#_xDelayedTaskList1
   128D 75 83 00           4138 	mov	dph,#(_xDelayedTaskList1 >> 8)
   1290 75 F0 01           4139 	mov	b,#0x01
   1293 12 29 62           4140 	lcall	_vListInitialise
                           4141 ;../../Source/tasks.c:1325: vListInitialise( ( xList * ) &xDelayedTaskList2 );
                           4142 ;     genCall
   1296 75 82 6E           4143 	mov	dpl,#_xDelayedTaskList2
   1299 75 83 00           4144 	mov	dph,#(_xDelayedTaskList2 >> 8)
   129C 75 F0 01           4145 	mov	b,#0x01
   129F 12 29 62           4146 	lcall	_vListInitialise
                           4147 ;../../Source/tasks.c:1326: vListInitialise( ( xList * ) &xPendingReadyList );
                           4148 ;     genCall
   12A2 75 82 8A           4149 	mov	dpl,#_xPendingReadyList
   12A5 75 83 00           4150 	mov	dph,#(_xPendingReadyList >> 8)
   12A8 75 F0 01           4151 	mov	b,#0x01
   12AB 12 29 62           4152 	lcall	_vListInitialise
                           4153 ;../../Source/tasks.c:1342: pxDelayedTaskList = &xDelayedTaskList1;
                           4154 ;     genCast
   12AE 90 00 84           4155 	mov	dptr,#_pxDelayedTaskList
   12B1 74 58              4156 	mov	a,#_xDelayedTaskList1
   12B3 F0                 4157 	movx	@dptr,a
   12B4 A3                 4158 	inc	dptr
   12B5 74 00              4159 	mov	a,#(_xDelayedTaskList1 >> 8)
   12B7 F0                 4160 	movx	@dptr,a
   12B8 A3                 4161 	inc	dptr
   12B9 74 01              4162 	mov	a,#0x1
   12BB F0                 4163 	movx	@dptr,a
                           4164 ;../../Source/tasks.c:1343: pxOverflowDelayedTaskList = &xDelayedTaskList2;
                           4165 ;     genCast
   12BC 90 00 87           4166 	mov	dptr,#_pxOverflowDelayedTaskList
   12BF 74 6E              4167 	mov	a,#_xDelayedTaskList2
   12C1 F0                 4168 	movx	@dptr,a
   12C2 A3                 4169 	inc	dptr
   12C3 74 00              4170 	mov	a,#(_xDelayedTaskList2 >> 8)
   12C5 F0                 4171 	movx	@dptr,a
   12C6 A3                 4172 	inc	dptr
   12C7 74 01              4173 	mov	a,#0x1
   12C9 F0                 4174 	movx	@dptr,a
                           4175 ;../../Source/tasks.c:1346: sReturn = sTaskCreate( prvIdleTask, ( const portCHAR * const ) "IDLE", tskIDLE_STACK_SIZE, ( void * ) NULL, tskIDLE_PRIORITY, ( xTaskHandle * ) NULL );
                           4176 ;     genIpush
   12CA 74 00              4177 	mov	a,#0x00
   12CC C0 E0              4178 	push	acc
   12CE 74 00              4179 	mov	a,#0x00
   12D0 C0 E0              4180 	push	acc
   12D2 74 00              4181 	mov	a,#0x00
   12D4 C0 E0              4182 	push	acc
                           4183 ;     genIpush
   12D6 74 00              4184 	mov	a,#0x00
   12D8 C0 E0              4185 	push	acc
                           4186 ;     genIpush
   12DA 74 00              4187 	mov	a,#0x00
   12DC C0 E0              4188 	push	acc
   12DE 74 00              4189 	mov	a,#0x00
   12E0 C0 E0              4190 	push	acc
   12E2 74 00              4191 	mov	a,#0x00
   12E4 C0 E0              4192 	push	acc
                           4193 ;     genIpush
   12E6 74 A6              4194 	mov	a,#0xA6
   12E8 C0 E0              4195 	push	acc
   12EA 74 00              4196 	mov	a,#0x00
   12EC C0 E0              4197 	push	acc
                           4198 ;     genIpush
   12EE 74 16              4199 	mov	a,#__str_0
   12F0 C0 E0              4200 	push	acc
   12F2 74 14              4201 	mov	a,#(__str_0 >> 8)
   12F4 C0 E0              4202 	push	acc
   12F6 74 02              4203 	mov	a,#0x02
   12F8 C0 E0              4204 	push	acc
                           4205 ;     genCall
   12FA 75 82 43           4206 	mov	dpl,#_prvIdleTask
   12FD 75 83 10           4207 	mov	dph,#(_prvIdleTask >> 8)
   1300 12 00 8F           4208 	lcall	_sTaskCreate
   1303 AA 82              4209 	mov	r2,dpl
   1305 AB 83              4210 	mov	r3,dph
   1307 E5 81              4211 	mov	a,sp
   1309 24 F4              4212 	add	a,#0xf4
   130B F5 81              4213 	mov	sp,a
                           4214 ;     genAssign
                           4215 ;../../Source/tasks.c:1348: return sReturn;
                           4216 ;     genRet
   130D 8A 82              4217 	mov	dpl,r2
   130F 8B 83              4218 	mov	dph,r3
   1311                    4219 00105$:
   1311 85 12 81           4220 	mov	sp,_bp
   1314 D0 12              4221 	pop	_bp
   1316 22                 4222 	ret
                           4223 ;------------------------------------------------------------
                           4224 ;Allocation info for local variables in function 'prvCheckTasksWaitingTermination'
                           4225 ;------------------------------------------------------------
                           4226 ;------------------------------------------------------------
                           4227 ;../../Source/tasks.c:1352: static void prvCheckTasksWaitingTermination( void )
                           4228 ;	-----------------------------------------
                           4229 ;	 function prvCheckTasksWaitingTermination
                           4230 ;	-----------------------------------------
   1317                    4231 _prvCheckTasksWaitingTermination:
   1317 C0 12              4232 	push	_bp
   1319 85 81 12           4233 	mov	_bp,sp
                           4234 ;../../Source/tasks.c:1378: }
   131C                    4235 00101$:
   131C 85 12 81           4236 	mov	sp,_bp
   131F D0 12              4237 	pop	_bp
   1321 22                 4238 	ret
                           4239 ;------------------------------------------------------------
                           4240 ;Allocation info for local variables in function 'prvAllocateTCBAndStack'
                           4241 ;------------------------------------------------------------
                           4242 ;usStackDepth              Allocated to stack - offset 1
                           4243 ;pxNewTCB                  Allocated to stack - offset 3
                           4244 ;------------------------------------------------------------
                           4245 ;../../Source/tasks.c:1381: static tskTCB *prvAllocateTCBAndStack( unsigned portSHORT usStackDepth )
                           4246 ;	-----------------------------------------
                           4247 ;	 function prvAllocateTCBAndStack
                           4248 ;	-----------------------------------------
   1322                    4249 _prvAllocateTCBAndStack:
   1322 C0 12              4250 	push	_bp
   1324 85 81 12           4251 	mov	_bp,sp
                           4252 ;     genReceive
   1327 C0 82              4253 	push	dpl
   1329 C0 83              4254 	push	dph
   132B 05 81              4255 	inc	sp
   132D 05 81              4256 	inc	sp
   132F 05 81              4257 	inc	sp
                           4258 ;../../Source/tasks.c:1387: pxNewTCB = ( tskTCB * ) pvPortMalloc( sizeof( tskTCB ) );
                           4259 ;     genCall
   1331 75 82 36           4260 	mov	dpl,#0x36
   1334 75 83 00           4261 	mov	dph,#0x00
   1337 12 31 EC           4262 	lcall	_pvPortMalloc
   133A AC 82              4263 	mov	r4,dpl
   133C AD 83              4264 	mov	r5,dph
   133E AE F0              4265 	mov	r6,b
                           4266 ;     genAssign
   1340 E5 12              4267 	mov	a,_bp
   1342 24 03              4268 	add	a,#0x03
   1344 F8                 4269 	mov	r0,a
   1345 A6 04              4270 	mov	@r0,ar4
   1347 08                 4271 	inc	r0
   1348 A6 05              4272 	mov	@r0,ar5
   134A 08                 4273 	inc	r0
   134B A6 06              4274 	mov	@r0,ar6
                           4275 ;../../Source/tasks.c:1389: if( pxNewTCB != NULL )
                           4276 ;     genCmpEq
   134D E5 12              4277 	mov	a,_bp
   134F 24 03              4278 	add	a,#0x03
   1351 F8                 4279 	mov	r0,a
   1352 B6 00 0B           4280 	cjne	@r0,#0x00,00110$
   1355 08                 4281 	inc	r0
   1356 B6 00 07           4282 	cjne	@r0,#0x00,00110$
   1359 08                 4283 	inc	r0
   135A B6 00 03           4284 	cjne	@r0,#0x00,00110$
   135D 02 14 03           4285 	ljmp	00105$
   1360                    4286 00110$:
                           4287 ;../../Source/tasks.c:1394: pxNewTCB->pxStack = ( portSTACK_TYPE * ) pvPortMalloc( usStackDepth * sizeof( portSTACK_TYPE ) );
                           4288 ;     genPlus
   1360 E5 12              4289 	mov	a,_bp
   1362 24 03              4290 	add	a,#0x03
   1364 F8                 4291 	mov	r0,a
                           4292 ;     genPlusIncr
   1365 74 03              4293 	mov	a,#0x03
   1367 26                 4294 	add	a,@r0
   1368 FF                 4295 	mov	r7,a
   1369 74 00              4296 	mov	a,#0x00
   136B 08                 4297 	inc	r0
   136C 36                 4298 	addc	a,@r0
   136D FA                 4299 	mov	r2,a
   136E 08                 4300 	inc	r0
   136F 86 03              4301 	mov	ar3,@r0
                           4302 ;     genCall
   1371 E5 12              4303 	mov	a,_bp
   1373 24 01              4304 	add	a,#0x01
   1375 F8                 4305 	mov	r0,a
   1376 86 82              4306 	mov	dpl,@r0
   1378 08                 4307 	inc	r0
   1379 86 83              4308 	mov	dph,@r0
   137B C0 02              4309 	push	ar2
   137D C0 03              4310 	push	ar3
   137F C0 07              4311 	push	ar7
   1381 12 31 EC           4312 	lcall	_pvPortMalloc
   1384 AC 82              4313 	mov	r4,dpl
   1386 AD 83              4314 	mov	r5,dph
   1388 AE F0              4315 	mov	r6,b
   138A D0 07              4316 	pop	ar7
   138C D0 03              4317 	pop	ar3
   138E D0 02              4318 	pop	ar2
                           4319 ;     genPointerSet
                           4320 ;     genGenPointerSet
   1390 8F 82              4321 	mov	dpl,r7
   1392 8A 83              4322 	mov	dph,r2
   1394 8B F0              4323 	mov	b,r3
   1396 EC                 4324 	mov	a,r4
   1397 12 A3 97           4325 	lcall	__gptrput
   139A A3                 4326 	inc	dptr
   139B ED                 4327 	mov	a,r5
   139C 12 A3 97           4328 	lcall	__gptrput
   139F A3                 4329 	inc	dptr
   13A0 EE                 4330 	mov	a,r6
   13A1 12 A3 97           4331 	lcall	__gptrput
                           4332 ;../../Source/tasks.c:1396: if( pxNewTCB->pxStack == NULL )
                           4333 ;     genCmpEq
   13A4 BC 00 08           4334 	cjne	r4,#0x00,00111$
   13A7 BD 00 05           4335 	cjne	r5,#0x00,00111$
   13AA BE 00 02           4336 	cjne	r6,#0x00,00111$
   13AD 80 03              4337 	sjmp	00112$
   13AF                    4338 00111$:
   13AF 02 13 D0           4339 	ljmp	00102$
   13B2                    4340 00112$:
                           4341 ;../../Source/tasks.c:1399: vPortFree( pxNewTCB );			
                           4342 ;     genCall
   13B2 E5 12              4343 	mov	a,_bp
   13B4 24 03              4344 	add	a,#0x03
   13B6 F8                 4345 	mov	r0,a
   13B7 86 82              4346 	mov	dpl,@r0
   13B9 08                 4347 	inc	r0
   13BA 86 83              4348 	mov	dph,@r0
   13BC 08                 4349 	inc	r0
   13BD 86 F0              4350 	mov	b,@r0
   13BF 12 32 8D           4351 	lcall	_vPortFree
                           4352 ;../../Source/tasks.c:1400: pxNewTCB = NULL;			
                           4353 ;     genAssign
   13C2 E5 12              4354 	mov	a,_bp
   13C4 24 03              4355 	add	a,#0x03
   13C6 F8                 4356 	mov	r0,a
   13C7 E4                 4357 	clr	a
   13C8 F6                 4358 	mov	@r0,a
   13C9 08                 4359 	inc	r0
   13CA F6                 4360 	mov	@r0,a
   13CB 08                 4361 	inc	r0
   13CC F6                 4362 	mov	@r0,a
   13CD 02 14 03           4363 	ljmp	00105$
   13D0                    4364 00102$:
                           4365 ;../../Source/tasks.c:1405: memset( pxNewTCB->pxStack, tskSTACK_FILL_BYTE, usStackDepth * sizeof( portSTACK_TYPE ) );
                           4366 ;     genPointerGet
                           4367 ;     genGenPointerGet
   13D0 8F 82              4368 	mov	dpl,r7
   13D2 8A 83              4369 	mov	dph,r2
   13D4 8B F0              4370 	mov	b,r3
   13D6 12 AE 30           4371 	lcall	__gptrget
   13D9 FF                 4372 	mov	r7,a
   13DA A3                 4373 	inc	dptr
   13DB 12 AE 30           4374 	lcall	__gptrget
   13DE FA                 4375 	mov	r2,a
   13DF A3                 4376 	inc	dptr
   13E0 12 AE 30           4377 	lcall	__gptrget
   13E3 FB                 4378 	mov	r3,a
                           4379 ;     genIpush
   13E4 E5 12              4380 	mov	a,_bp
   13E6 24 01              4381 	add	a,#0x01
   13E8 F8                 4382 	mov	r0,a
   13E9 E6                 4383 	mov	a,@r0
   13EA C0 E0              4384 	push	acc
   13EC 08                 4385 	inc	r0
   13ED E6                 4386 	mov	a,@r0
   13EE C0 E0              4387 	push	acc
                           4388 ;     genIpush
   13F0 74 A5              4389 	mov	a,#0xA5
   13F2 C0 E0              4390 	push	acc
                           4391 ;     genCall
   13F4 8F 82              4392 	mov	dpl,r7
   13F6 8A 83              4393 	mov	dph,r2
   13F8 8B F0              4394 	mov	b,r3
   13FA 12 AC FC           4395 	lcall	_memset
   13FD 15 81              4396 	dec	sp
   13FF 15 81              4397 	dec	sp
   1401 15 81              4398 	dec	sp
   1403                    4399 00105$:
                           4400 ;../../Source/tasks.c:1409: return pxNewTCB;
                           4401 ;     genRet
   1403 E5 12              4402 	mov	a,_bp
   1405 24 03              4403 	add	a,#0x03
   1407 F8                 4404 	mov	r0,a
   1408 86 82              4405 	mov	dpl,@r0
   140A 08                 4406 	inc	r0
   140B 86 83              4407 	mov	dph,@r0
   140D 08                 4408 	inc	r0
   140E 86 F0              4409 	mov	b,@r0
   1410                    4410 00106$:
   1410 85 12 81           4411 	mov	sp,_bp
   1413 D0 12              4412 	pop	_bp
   1415 22                 4413 	ret
                           4414 	.area CSEG    (CODE)
   1416                    4415 __str_0:
   1416 49 44 4C 45        4416 	.ascii "IDLE"
   141A 00                 4417 	.db 0x00
                           4418 	.area XINIT   (CODE)
   AF07                    4419 __xinit__pxCurrentTCB:
                           4420 ; generic printIvalPtr
   AF07 00 00 00           4421 	.byte #0x00,#0x00,#0x00
   AF0A                    4422 __xinit__sUsingPreemption:
   AF0A 00 00              4423 	.byte #0x00,#0x00
   AF0C                    4424 __xinit__usCurrentNumberOfTasks:
   AF0C 00 00              4425 	.byte #0x00,#0x00
   AF0E                    4426 __xinit__xTickCount:
   AF0E 00 00              4427 	.byte #0x00,#0x00
   AF10                    4428 __xinit__ucTopUsedPriority:
   AF10 00                 4429 	.db #0x00
   AF11                    4430 __xinit__ucTopReadyPriority:
   AF11 00                 4431 	.db #0x00
   AF12                    4432 __xinit__cSchedulerRunning:
   AF12 00                 4433 	.db #0x00
   AF13                    4434 __xinit__ucSchedulerSuspended:
   AF13 00                 4435 	.db #0x00
   AF14                    4436 __xinit__ucMissedTicks:
   AF14 00                 4437 	.db #0x00
