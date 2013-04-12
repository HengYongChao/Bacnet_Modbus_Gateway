                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.4.8 #964 (Feb 23 2005)
                              4 ; This file generated Fri May 20 14:05:29 2005
                              5 ;--------------------------------------------------------
                              6 	.module ______Source_portable_MemMang_heap_1
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
                            130 	.globl _pvPortMalloc
                            131 	.globl _vPortFree
                            132 	.globl _vPortInitialiseBlocks
                            133 ;--------------------------------------------------------
                            134 ; special function registers
                            135 ;--------------------------------------------------------
                            136 	.area RSEG    (DATA)
                    0080    137 _P0	=	0x0080
                    0081    138 _SP	=	0x0081
                    0082    139 _DPL	=	0x0082
                    0083    140 _DPH	=	0x0083
                    0087    141 _PCON	=	0x0087
                    0088    142 _TCON	=	0x0088
                    0089    143 _TMOD	=	0x0089
                    008A    144 _TL0	=	0x008a
                    008B    145 _TL1	=	0x008b
                    008C    146 _TH0	=	0x008c
                    008D    147 _TH1	=	0x008d
                    0090    148 _P1	=	0x0090
                    0098    149 _SCON	=	0x0098
                    0099    150 _SBUF	=	0x0099
                    00A0    151 _P2	=	0x00a0
                    00A8    152 _IE	=	0x00a8
                    00B0    153 _P3	=	0x00b0
                    00B8    154 _IP	=	0x00b8
                    00D0    155 _PSW	=	0x00d0
                    00E0    156 _ACC	=	0x00e0
                    00F0    157 _B	=	0x00f0
                    00C8    158 _T2CON	=	0x00c8
                    00CA    159 _RCAP2L	=	0x00ca
                    00CB    160 _RCAP2H	=	0x00cb
                    00CC    161 _TL2	=	0x00cc
                    00CD    162 _TH2	=	0x00cd
                            163 ;--------------------------------------------------------
                            164 ; special function bits 
                            165 ;--------------------------------------------------------
                            166 	.area RSEG    (DATA)
                    0080    167 _P0_0	=	0x0080
                    0081    168 _P0_1	=	0x0081
                    0082    169 _P0_2	=	0x0082
                    0083    170 _P0_3	=	0x0083
                    0084    171 _P0_4	=	0x0084
                    0085    172 _P0_5	=	0x0085
                    0086    173 _P0_6	=	0x0086
                    0087    174 _P0_7	=	0x0087
                    0088    175 _IT0	=	0x0088
                    0089    176 _IE0	=	0x0089
                    008A    177 _IT1	=	0x008a
                    008B    178 _IE1	=	0x008b
                    008C    179 _TR0	=	0x008c
                    008D    180 _TF0	=	0x008d
                    008E    181 _TR1	=	0x008e
                    008F    182 _TF1	=	0x008f
                    0090    183 _P1_0	=	0x0090
                    0091    184 _P1_1	=	0x0091
                    0092    185 _P1_2	=	0x0092
                    0093    186 _P1_3	=	0x0093
                    0094    187 _P1_4	=	0x0094
                    0095    188 _P1_5	=	0x0095
                    0096    189 _P1_6	=	0x0096
                    0097    190 _P1_7	=	0x0097
                    0098    191 _RI	=	0x0098
                    0099    192 _TI	=	0x0099
                    009A    193 _RB8	=	0x009a
                    009B    194 _TB8	=	0x009b
                    009C    195 _REN	=	0x009c
                    009D    196 _SM2	=	0x009d
                    009E    197 _SM1	=	0x009e
                    009F    198 _SM0	=	0x009f
                    00A0    199 _P2_0	=	0x00a0
                    00A1    200 _P2_1	=	0x00a1
                    00A2    201 _P2_2	=	0x00a2
                    00A3    202 _P2_3	=	0x00a3
                    00A4    203 _P2_4	=	0x00a4
                    00A5    204 _P2_5	=	0x00a5
                    00A6    205 _P2_6	=	0x00a6
                    00A7    206 _P2_7	=	0x00a7
                    00A8    207 _EX0	=	0x00a8
                    00A9    208 _ET0	=	0x00a9
                    00AA    209 _EX1	=	0x00aa
                    00AB    210 _ET1	=	0x00ab
                    00AC    211 _ES	=	0x00ac
                    00AF    212 _EA	=	0x00af
                    00B0    213 _P3_0	=	0x00b0
                    00B1    214 _P3_1	=	0x00b1
                    00B2    215 _P3_2	=	0x00b2
                    00B3    216 _P3_3	=	0x00b3
                    00B4    217 _P3_4	=	0x00b4
                    00B5    218 _P3_5	=	0x00b5
                    00B6    219 _P3_6	=	0x00b6
                    00B7    220 _P3_7	=	0x00b7
                    00B0    221 _RXD	=	0x00b0
                    00B1    222 _TXD	=	0x00b1
                    00B2    223 _INT0	=	0x00b2
                    00B3    224 _INT1	=	0x00b3
                    00B4    225 _T0	=	0x00b4
                    00B5    226 _T1	=	0x00b5
                    00B6    227 _WR	=	0x00b6
                    00B7    228 _RD	=	0x00b7
                    00B8    229 _PX0	=	0x00b8
                    00B9    230 _PT0	=	0x00b9
                    00BA    231 _PX1	=	0x00ba
                    00BB    232 _PT1	=	0x00bb
                    00BC    233 _PS	=	0x00bc
                    00D0    234 _P	=	0x00d0
                    00D1    235 _F1	=	0x00d1
                    00D2    236 _OV	=	0x00d2
                    00D3    237 _RS0	=	0x00d3
                    00D4    238 _RS1	=	0x00d4
                    00D5    239 _F0	=	0x00d5
                    00D6    240 _AC	=	0x00d6
                    00D7    241 _CY	=	0x00d7
                    00AD    242 _ET2	=	0x00ad
                    00C8    243 _T2CON_0	=	0x00c8
                    00C9    244 _T2CON_1	=	0x00c9
                    00CA    245 _T2CON_2	=	0x00ca
                    00CB    246 _T2CON_3	=	0x00cb
                    00CC    247 _T2CON_4	=	0x00cc
                    00CD    248 _T2CON_5	=	0x00cd
                    00CE    249 _T2CON_6	=	0x00ce
                    00CF    250 _T2CON_7	=	0x00cf
                    00C8    251 _CP_RL2	=	0x00c8
                    00C9    252 _C_T2	=	0x00c9
                    00CA    253 _TR2	=	0x00ca
                    00CB    254 _EXEN2	=	0x00cb
                    00CC    255 _TCLK	=	0x00cc
                    00CD    256 _RCLK	=	0x00cd
                    00CE    257 _EXF2	=	0x00ce
                    00CF    258 _TF2	=	0x00cf
                            259 ;--------------------------------------------------------
                            260 ; overlayable register banks 
                            261 ;--------------------------------------------------------
                            262 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     263 	.ds 8
                            264 ;--------------------------------------------------------
                            265 ; internal ram data
                            266 ;--------------------------------------------------------
                            267 	.area DSEG    (DATA)
                            268 ;--------------------------------------------------------
                            269 ; overlayable items in internal ram 
                            270 ;--------------------------------------------------------
                            271 	.area OSEG    (OVR,DATA)
                            272 ;--------------------------------------------------------
                            273 ; indirectly addressable internal ram data
                            274 ;--------------------------------------------------------
                            275 	.area ISEG    (DATA)
                            276 ;--------------------------------------------------------
                            277 ; bit data
                            278 ;--------------------------------------------------------
                            279 	.area BSEG    (BIT)
                            280 ;--------------------------------------------------------
                            281 ; paged external ram data
                            282 ;--------------------------------------------------------
                            283 	.area PSEG    (PAG,XDATA)
                            284 ;--------------------------------------------------------
                            285 ; external ram data
                            286 ;--------------------------------------------------------
                            287 	.area XSEG    (XDATA)
   00A1                     288 _xHeap:
   00A1                     289 	.ds 6148
                            290 ;--------------------------------------------------------
                            291 ; external initialized ram data
                            292 ;--------------------------------------------------------
                            293 	.area XISEG   (XDATA)
   1D19                     294 _usNextFreeByte:
   1D19                     295 	.ds 2
                            296 	.area CSEG    (CODE)
                            297 	.area GSINIT0 (CODE)
                            298 	.area GSINIT1 (CODE)
                            299 	.area GSINIT2 (CODE)
                            300 	.area GSINIT3 (CODE)
                            301 	.area GSINIT4 (CODE)
                            302 	.area GSINIT5 (CODE)
                            303 ;--------------------------------------------------------
                            304 ; global & static initialisations
                            305 ;--------------------------------------------------------
                            306 	.area CSEG    (CODE)
                            307 	.area GSINIT  (CODE)
                            308 	.area GSFINAL (CODE)
                            309 	.area GSINIT  (CODE)
                            310 ;--------------------------------------------------------
                            311 ; Home
                            312 ;--------------------------------------------------------
                            313 	.area HOME    (CODE)
                            314 	.area CSEG    (CODE)
                            315 ;--------------------------------------------------------
                            316 ; code
                            317 ;--------------------------------------------------------
                            318 	.area CSEG    (CODE)
                            319 ;------------------------------------------------------------
                            320 ;Allocation info for local variables in function 'pvPortMalloc'
                            321 ;------------------------------------------------------------
                            322 ;usWantedSize              Allocated to stack - offset 1
                            323 ;pvReturn                  Allocated to registers r4 r5 r6 
                            324 ;sloc0                     Allocated to stack - offset 3
                            325 ;------------------------------------------------------------
                            326 ;../../Source/portable/MemMang/heap_1.c:82: void *pvPortMalloc( unsigned portSHORT usWantedSize )
                            327 ;	-----------------------------------------
                            328 ;	 function pvPortMalloc
                            329 ;	-----------------------------------------
   31EC                     330 _pvPortMalloc:
                    0002    331 	ar2 = 0x02
                    0003    332 	ar3 = 0x03
                    0004    333 	ar4 = 0x04
                    0005    334 	ar5 = 0x05
                    0006    335 	ar6 = 0x06
                    0007    336 	ar7 = 0x07
                    0000    337 	ar0 = 0x00
                    0001    338 	ar1 = 0x01
   31EC C0 12               339 	push	_bp
   31EE 85 81 12            340 	mov	_bp,sp
                            341 ;     genReceive
   31F1 C0 82               342 	push	dpl
   31F3 C0 83               343 	push	dph
   31F5 05 81               344 	inc	sp
   31F7 05 81               345 	inc	sp
                            346 ;../../Source/portable/MemMang/heap_1.c:84: void *pvReturn = NULL;
                            347 ;     genAssign
   31F9 7C 00               348 	mov	r4,#0x00
   31FB 7D 00               349 	mov	r5,#0x00
   31FD 7E 00               350 	mov	r6,#0x00
                            351 ;../../Source/portable/MemMang/heap_1.c:93: vTaskSuspendAll();
                            352 ;     genIpush
   31FF C0 04               353 	push	ar4
   3201 C0 05               354 	push	ar5
   3203 C0 06               355 	push	ar6
                            356 ;     genCall
   3205 C0 04               357 	push	ar4
   3207 C0 05               358 	push	ar5
   3209 C0 06               359 	push	ar6
   320B 12 06 94            360 	lcall	_vTaskSuspendAll
   320E D0 06               361 	pop	ar6
   3210 D0 05               362 	pop	ar5
   3212 D0 04               363 	pop	ar4
                            364 ;../../Source/portable/MemMang/heap_1.c:96: if( ( usNextFreeByte + usWantedSize ) < portTOTAL_HEAP_SIZE )
                            365 ;     genAssign
   3214 90 1D 19            366 	mov	dptr,#_usNextFreeByte
   3217 E5 12               367 	mov	a,_bp
   3219 24 03               368 	add	a,#0x03
   321B F8                  369 	mov	r0,a
   321C E0                  370 	movx	a,@dptr
   321D F6                  371 	mov	@r0,a
   321E A3                  372 	inc	dptr
   321F E0                  373 	movx	a,@dptr
   3220 08                  374 	inc	r0
   3221 F6                  375 	mov	@r0,a
                            376 ;     genPlus
   3222 E5 12               377 	mov	a,_bp
   3224 24 03               378 	add	a,#0x03
   3226 F8                  379 	mov	r0,a
   3227 E5 12               380 	mov	a,_bp
   3229 24 01               381 	add	a,#0x01
   322B F9                  382 	mov	r1,a
   322C E7                  383 	mov	a,@r1
   322D 26                  384 	add	a,@r0
   322E FF                  385 	mov	r7,a
   322F 09                  386 	inc	r1
   3230 E7                  387 	mov	a,@r1
   3231 08                  388 	inc	r0
   3232 36                  389 	addc	a,@r0
   3233 FC                  390 	mov	r4,a
                            391 ;     genCmpLt
                            392 ;     genCmp
   3234 C3                  393 	clr	c
   3235 EF                  394 	mov	a,r7
   3236 94 00               395 	subb	a,#0x00
   3238 EC                  396 	mov	a,r4
   3239 94 18               397 	subb	a,#0x18
   323B E4                  398 	clr	a
   323C 33                  399 	rlc	a
                            400 ;     genIpop
   323D D0 06               401 	pop	ar6
   323F D0 05               402 	pop	ar5
   3241 D0 04               403 	pop	ar4
                            404 ;     genIfx
                            405 ;     genIfxJump
   3243 70 03               406 	jnz	00109$
   3245 02 32 72            407 	ljmp	00104$
   3248                     408 00109$:
                            409 ;../../Source/portable/MemMang/heap_1.c:100: pvReturn = &( xHeap.ucHeap[ usNextFreeByte ] );
                            410 ;     genPlus
   3248 E5 12               411 	mov	a,_bp
   324A 24 03               412 	add	a,#0x03
   324C F8                  413 	mov	r0,a
   324D E6                  414 	mov	a,@r0
   324E 24 A5               415 	add	a,#(_xHeap + 0x0004)
   3250 FF                  416 	mov	r7,a
   3251 08                  417 	inc	r0
   3252 E6                  418 	mov	a,@r0
   3253 34 00               419 	addc	a,#((_xHeap + 0x0004) >> 8)
   3255 FA                  420 	mov	r2,a
                            421 ;     genCast
   3256 8F 04               422 	mov	ar4,r7
   3258 8A 05               423 	mov	ar5,r2
   325A 7E 01               424 	mov	r6,#0x1
                            425 ;../../Source/portable/MemMang/heap_1.c:101: usNextFreeByte += usWantedSize;			
                            426 ;     genPlus
   325C E5 12               427 	mov	a,_bp
   325E 24 03               428 	add	a,#0x03
   3260 F8                  429 	mov	r0,a
   3261 E5 12               430 	mov	a,_bp
   3263 24 01               431 	add	a,#0x01
   3265 F9                  432 	mov	r1,a
   3266 90 1D 19            433 	mov	dptr,#_usNextFreeByte
   3269 E7                  434 	mov	a,@r1
   326A 26                  435 	add	a,@r0
   326B F0                  436 	movx	@dptr,a
   326C 09                  437 	inc	r1
   326D E7                  438 	mov	a,@r1
   326E 08                  439 	inc	r0
   326F 36                  440 	addc	a,@r0
   3270 A3                  441 	inc	dptr
   3271 F0                  442 	movx	@dptr,a
   3272                     443 00104$:
                            444 ;../../Source/portable/MemMang/heap_1.c:104: cTaskResumeAll();
                            445 ;     genCall
   3272 C0 04               446 	push	ar4
   3274 C0 05               447 	push	ar5
   3276 C0 06               448 	push	ar6
   3278 12 06 B7            449 	lcall	_cTaskResumeAll
   327B D0 06               450 	pop	ar6
   327D D0 05               451 	pop	ar5
   327F D0 04               452 	pop	ar4
                            453 ;../../Source/portable/MemMang/heap_1.c:106: return pvReturn;
                            454 ;     genRet
   3281 8C 82               455 	mov	dpl,r4
   3283 8D 83               456 	mov	dph,r5
   3285 8E F0               457 	mov	b,r6
   3287                     458 00105$:
   3287 85 12 81            459 	mov	sp,_bp
   328A D0 12               460 	pop	_bp
   328C 22                  461 	ret
                            462 ;------------------------------------------------------------
                            463 ;Allocation info for local variables in function 'vPortFree'
                            464 ;------------------------------------------------------------
                            465 ;pv                        Allocated to registers 
                            466 ;------------------------------------------------------------
                            467 ;../../Source/portable/MemMang/heap_1.c:110: void vPortFree( void *pv )
                            468 ;	-----------------------------------------
                            469 ;	 function vPortFree
                            470 ;	-----------------------------------------
   328D                     471 _vPortFree:
   328D C0 12               472 	push	_bp
   328F 85 81 12            473 	mov	_bp,sp
                            474 ;../../Source/portable/MemMang/heap_1.c:115: ( void ) pv;
   3292                     475 00101$:
   3292 85 12 81            476 	mov	sp,_bp
   3295 D0 12               477 	pop	_bp
   3297 22                  478 	ret
                            479 ;------------------------------------------------------------
                            480 ;Allocation info for local variables in function 'vPortInitialiseBlocks'
                            481 ;------------------------------------------------------------
                            482 ;------------------------------------------------------------
                            483 ;../../Source/portable/MemMang/heap_1.c:119: void vPortInitialiseBlocks( void )
                            484 ;	-----------------------------------------
                            485 ;	 function vPortInitialiseBlocks
                            486 ;	-----------------------------------------
   3298                     487 _vPortInitialiseBlocks:
   3298 C0 12               488 	push	_bp
   329A 85 81 12            489 	mov	_bp,sp
                            490 ;../../Source/portable/MemMang/heap_1.c:122: usNextFreeByte = ( unsigned portSHORT ) 0;
                            491 ;     genAssign
   329D 90 1D 19            492 	mov	dptr,#_usNextFreeByte
   32A0 E4                  493 	clr	a
   32A1 F0                  494 	movx	@dptr,a
   32A2 A3                  495 	inc	dptr
   32A3 F0                  496 	movx	@dptr,a
   32A4                     497 00101$:
   32A4 85 12 81            498 	mov	sp,_bp
   32A7 D0 12               499 	pop	_bp
   32A9 22                  500 	ret
                            501 	.area CSEG    (CODE)
                            502 	.area XINIT   (CODE)
   AF15                     503 __xinit__usNextFreeByte:
   AF15 00 00               504 	.byte #0x00,#0x00
