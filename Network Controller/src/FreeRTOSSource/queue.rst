                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.4.8 #964 (Feb 23 2005)
                              4 ; This file generated Fri May 20 14:05:28 2005
                              5 ;--------------------------------------------------------
                              6 	.module ______Source_queue
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
                            130 	.globl _xQueueCreate
                            131 	.globl _cQueueSend
                            132 	.globl _cQueueSendFromISR
                            133 	.globl _cQueueReceive
                            134 	.globl _cQueueReceiveFromISR
                            135 	.globl _ucQueueMessagesWaiting
                            136 	.globl _vQueueDelete
                            137 ;--------------------------------------------------------
                            138 ; special function registers
                            139 ;--------------------------------------------------------
                            140 	.area RSEG    (DATA)
                    0080    141 _P0	=	0x0080
                    0081    142 _SP	=	0x0081
                    0082    143 _DPL	=	0x0082
                    0083    144 _DPH	=	0x0083
                    0087    145 _PCON	=	0x0087
                    0088    146 _TCON	=	0x0088
                    0089    147 _TMOD	=	0x0089
                    008A    148 _TL0	=	0x008a
                    008B    149 _TL1	=	0x008b
                    008C    150 _TH0	=	0x008c
                    008D    151 _TH1	=	0x008d
                    0090    152 _P1	=	0x0090
                    0098    153 _SCON	=	0x0098
                    0099    154 _SBUF	=	0x0099
                    00A0    155 _P2	=	0x00a0
                    00A8    156 _IE	=	0x00a8
                    00B0    157 _P3	=	0x00b0
                    00B8    158 _IP	=	0x00b8
                    00D0    159 _PSW	=	0x00d0
                    00E0    160 _ACC	=	0x00e0
                    00F0    161 _B	=	0x00f0
                    00C8    162 _T2CON	=	0x00c8
                    00CA    163 _RCAP2L	=	0x00ca
                    00CB    164 _RCAP2H	=	0x00cb
                    00CC    165 _TL2	=	0x00cc
                    00CD    166 _TH2	=	0x00cd
                            167 ;--------------------------------------------------------
                            168 ; special function bits 
                            169 ;--------------------------------------------------------
                            170 	.area RSEG    (DATA)
                    0080    171 _P0_0	=	0x0080
                    0081    172 _P0_1	=	0x0081
                    0082    173 _P0_2	=	0x0082
                    0083    174 _P0_3	=	0x0083
                    0084    175 _P0_4	=	0x0084
                    0085    176 _P0_5	=	0x0085
                    0086    177 _P0_6	=	0x0086
                    0087    178 _P0_7	=	0x0087
                    0088    179 _IT0	=	0x0088
                    0089    180 _IE0	=	0x0089
                    008A    181 _IT1	=	0x008a
                    008B    182 _IE1	=	0x008b
                    008C    183 _TR0	=	0x008c
                    008D    184 _TF0	=	0x008d
                    008E    185 _TR1	=	0x008e
                    008F    186 _TF1	=	0x008f
                    0090    187 _P1_0	=	0x0090
                    0091    188 _P1_1	=	0x0091
                    0092    189 _P1_2	=	0x0092
                    0093    190 _P1_3	=	0x0093
                    0094    191 _P1_4	=	0x0094
                    0095    192 _P1_5	=	0x0095
                    0096    193 _P1_6	=	0x0096
                    0097    194 _P1_7	=	0x0097
                    0098    195 _RI	=	0x0098
                    0099    196 _TI	=	0x0099
                    009A    197 _RB8	=	0x009a
                    009B    198 _TB8	=	0x009b
                    009C    199 _REN	=	0x009c
                    009D    200 _SM2	=	0x009d
                    009E    201 _SM1	=	0x009e
                    009F    202 _SM0	=	0x009f
                    00A0    203 _P2_0	=	0x00a0
                    00A1    204 _P2_1	=	0x00a1
                    00A2    205 _P2_2	=	0x00a2
                    00A3    206 _P2_3	=	0x00a3
                    00A4    207 _P2_4	=	0x00a4
                    00A5    208 _P2_5	=	0x00a5
                    00A6    209 _P2_6	=	0x00a6
                    00A7    210 _P2_7	=	0x00a7
                    00A8    211 _EX0	=	0x00a8
                    00A9    212 _ET0	=	0x00a9
                    00AA    213 _EX1	=	0x00aa
                    00AB    214 _ET1	=	0x00ab
                    00AC    215 _ES	=	0x00ac
                    00AF    216 _EA	=	0x00af
                    00B0    217 _P3_0	=	0x00b0
                    00B1    218 _P3_1	=	0x00b1
                    00B2    219 _P3_2	=	0x00b2
                    00B3    220 _P3_3	=	0x00b3
                    00B4    221 _P3_4	=	0x00b4
                    00B5    222 _P3_5	=	0x00b5
                    00B6    223 _P3_6	=	0x00b6
                    00B7    224 _P3_7	=	0x00b7
                    00B0    225 _RXD	=	0x00b0
                    00B1    226 _TXD	=	0x00b1
                    00B2    227 _INT0	=	0x00b2
                    00B3    228 _INT1	=	0x00b3
                    00B4    229 _T0	=	0x00b4
                    00B5    230 _T1	=	0x00b5
                    00B6    231 _WR	=	0x00b6
                    00B7    232 _RD	=	0x00b7
                    00B8    233 _PX0	=	0x00b8
                    00B9    234 _PT0	=	0x00b9
                    00BA    235 _PX1	=	0x00ba
                    00BB    236 _PT1	=	0x00bb
                    00BC    237 _PS	=	0x00bc
                    00D0    238 _P	=	0x00d0
                    00D1    239 _F1	=	0x00d1
                    00D2    240 _OV	=	0x00d2
                    00D3    241 _RS0	=	0x00d3
                    00D4    242 _RS1	=	0x00d4
                    00D5    243 _F0	=	0x00d5
                    00D6    244 _AC	=	0x00d6
                    00D7    245 _CY	=	0x00d7
                    00AD    246 _ET2	=	0x00ad
                    00C8    247 _T2CON_0	=	0x00c8
                    00C9    248 _T2CON_1	=	0x00c9
                    00CA    249 _T2CON_2	=	0x00ca
                    00CB    250 _T2CON_3	=	0x00cb
                    00CC    251 _T2CON_4	=	0x00cc
                    00CD    252 _T2CON_5	=	0x00cd
                    00CE    253 _T2CON_6	=	0x00ce
                    00CF    254 _T2CON_7	=	0x00cf
                    00C8    255 _CP_RL2	=	0x00c8
                    00C9    256 _C_T2	=	0x00c9
                    00CA    257 _TR2	=	0x00ca
                    00CB    258 _EXEN2	=	0x00cb
                    00CC    259 _TCLK	=	0x00cc
                    00CD    260 _RCLK	=	0x00cd
                    00CE    261 _EXF2	=	0x00ce
                    00CF    262 _TF2	=	0x00cf
                            263 ;--------------------------------------------------------
                            264 ; overlayable register banks 
                            265 ;--------------------------------------------------------
                            266 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     267 	.ds 8
                            268 ;--------------------------------------------------------
                            269 ; internal ram data
                            270 ;--------------------------------------------------------
                            271 	.area DSEG    (DATA)
                            272 ;--------------------------------------------------------
                            273 ; overlayable items in internal ram 
                            274 ;--------------------------------------------------------
                            275 	.area OSEG    (OVR,DATA)
                            276 ;--------------------------------------------------------
                            277 ; indirectly addressable internal ram data
                            278 ;--------------------------------------------------------
                            279 	.area ISEG    (DATA)
                            280 ;--------------------------------------------------------
                            281 ; bit data
                            282 ;--------------------------------------------------------
                            283 	.area BSEG    (BIT)
                            284 ;--------------------------------------------------------
                            285 ; paged external ram data
                            286 ;--------------------------------------------------------
                            287 	.area PSEG    (PAG,XDATA)
                            288 ;--------------------------------------------------------
                            289 ; external ram data
                            290 ;--------------------------------------------------------
                            291 	.area XSEG    (XDATA)
                            292 ;--------------------------------------------------------
                            293 ; external initialized ram data
                            294 ;--------------------------------------------------------
                            295 	.area XISEG   (XDATA)
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
                            320 ;Allocation info for local variables in function 'xQueueCreate'
                            321 ;------------------------------------------------------------
                            322 ;ucItemSize                Allocated to stack - offset -3
                            323 ;ucQueueLength             Allocated to stack - offset 1
                            324 ;pxNewQueue                Allocated to stack - offset 2
                            325 ;usQueueSizeInBytes        Allocated to registers r2 r3 
                            326 ;sloc0                     Allocated to stack - offset 5
                            327 ;sloc1                     Allocated to stack - offset 8
                            328 ;------------------------------------------------------------
                            329 ;../../Source/queue.c:168: xQueueHandle xQueueCreate( unsigned portCHAR ucQueueLength, unsigned portCHAR ucItemSize )
                            330 ;	-----------------------------------------
                            331 ;	 function xQueueCreate
                            332 ;	-----------------------------------------
   18F6                     333 _xQueueCreate:
                    0002    334 	ar2 = 0x02
                    0003    335 	ar3 = 0x03
                    0004    336 	ar4 = 0x04
                    0005    337 	ar5 = 0x05
                    0006    338 	ar6 = 0x06
                    0007    339 	ar7 = 0x07
                    0000    340 	ar0 = 0x00
                    0001    341 	ar1 = 0x01
   18F6 C0 12               342 	push	_bp
   18F8 85 81 12            343 	mov	_bp,sp
                            344 ;     genReceive
   18FB C0 82               345 	push	dpl
   18FD E5 81               346 	mov	a,sp
   18FF 24 09               347 	add	a,#0x09
   1901 F5 81               348 	mov	sp,a
                            349 ;../../Source/queue.c:174: if( ucQueueLength > ( unsigned portCHAR ) 0 )
                            350 ;     genCmpGt
   1903 E5 12               351 	mov	a,_bp
   1905 24 01               352 	add	a,#0x01
   1907 F8                  353 	mov	r0,a
                            354 ;     genCmp
   1908 C3                  355 	clr	c
   1909 74 00               356 	mov	a,#0x00
   190B 96                  357 	subb	a,@r0
                            358 ;     genIfxJump
   190C 40 03               359 	jc	00113$
   190E 02 1B 80            360 	ljmp	00107$
   1911                     361 00113$:
                            362 ;../../Source/queue.c:176: pxNewQueue = ( xQUEUE * ) pvPortMalloc( sizeof( xQUEUE ) );
                            363 ;     genCall
   1911 75 82 3D            364 	mov	dpl,#0x3D
   1914 75 83 00            365 	mov	dph,#0x00
   1917 12 31 EC            366 	lcall	_pvPortMalloc
   191A AB 82               367 	mov	r3,dpl
   191C AC 83               368 	mov	r4,dph
   191E AD F0               369 	mov	r5,b
                            370 ;     genAssign
   1920 E5 12               371 	mov	a,_bp
   1922 24 02               372 	add	a,#0x02
   1924 F8                  373 	mov	r0,a
   1925 A6 03               374 	mov	@r0,ar3
   1927 08                  375 	inc	r0
   1928 A6 04               376 	mov	@r0,ar4
   192A 08                  377 	inc	r0
   192B A6 05               378 	mov	@r0,ar5
                            379 ;../../Source/queue.c:177: if( pxNewQueue != NULL )
                            380 ;     genCmpEq
   192D E5 12               381 	mov	a,_bp
   192F 24 02               382 	add	a,#0x02
   1931 F8                  383 	mov	r0,a
   1932 B6 00 0B            384 	cjne	@r0,#0x00,00114$
   1935 08                  385 	inc	r0
   1936 B6 00 07            386 	cjne	@r0,#0x00,00114$
   1939 08                  387 	inc	r0
   193A B6 00 03            388 	cjne	@r0,#0x00,00114$
   193D 02 1B 80            389 	ljmp	00107$
   1940                     390 00114$:
                            391 ;../../Source/queue.c:181: usQueueSizeInBytes = ( unsigned portSHORT ) ( ucQueueLength * ucItemSize ) + ( unsigned portSHORT ) 1;
                            392 ;     genMult
   1940 E5 12               393 	mov	a,_bp
   1942 24 01               394 	add	a,#0x01
   1944 F8                  395 	mov	r0,a
   1945 E5 12               396 	mov	a,_bp
   1947 24 FD               397 	add	a,#0xfd
   1949 F9                  398 	mov	r1,a
                            399 ;     genMultOneByte
   194A 86 F0               400 	mov	b,@r0
   194C E7                  401 	mov	a,@r1
   194D A4                  402 	mul	ab
   194E FE                  403 	mov	r6,a
   194F AF F0               404 	mov	r7,b
                            405 ;     genPlus
                            406 ;     genPlusIncr
   1951 74 01               407 	mov	a,#0x01
   1953 25 06               408 	add	a,ar6
   1955 FA                  409 	mov	r2,a
   1956 74 00               410 	mov	a,#0x00
   1958 35 07               411 	addc	a,ar7
   195A FB                  412 	mov	r3,a
                            413 ;../../Source/queue.c:183: pxNewQueue->pcHead = ( signed portCHAR * ) pvPortMalloc( usQueueSizeInBytes );
                            414 ;     genCall
   195B 8A 82               415 	mov	dpl,r2
   195D 8B 83               416 	mov	dph,r3
   195F C0 06               417 	push	ar6
   1961 C0 07               418 	push	ar7
   1963 12 31 EC            419 	lcall	_pvPortMalloc
   1966 AA 82               420 	mov	r2,dpl
   1968 AB 83               421 	mov	r3,dph
   196A AC F0               422 	mov	r4,b
   196C D0 07               423 	pop	ar7
   196E D0 06               424 	pop	ar6
                            425 ;     genPointerSet
                            426 ;     genGenPointerSet
   1970 E5 12               427 	mov	a,_bp
   1972 24 02               428 	add	a,#0x02
   1974 F8                  429 	mov	r0,a
   1975 86 82               430 	mov	dpl,@r0
   1977 08                  431 	inc	r0
   1978 86 83               432 	mov	dph,@r0
   197A 08                  433 	inc	r0
   197B 86 F0               434 	mov	b,@r0
   197D EA                  435 	mov	a,r2
   197E 12 A3 97            436 	lcall	__gptrput
   1981 A3                  437 	inc	dptr
   1982 EB                  438 	mov	a,r3
   1983 12 A3 97            439 	lcall	__gptrput
   1986 A3                  440 	inc	dptr
   1987 EC                  441 	mov	a,r4
   1988 12 A3 97            442 	lcall	__gptrput
                            443 ;../../Source/queue.c:184: if( pxNewQueue->pcHead != NULL )
                            444 ;     genCmpEq
   198B BA 00 09            445 	cjne	r2,#0x00,00115$
   198E BB 00 06            446 	cjne	r3,#0x00,00115$
   1991 BC 00 03            447 	cjne	r4,#0x00,00115$
   1994 02 1B 70            448 	ljmp	00102$
   1997                     449 00115$:
                            450 ;../../Source/queue.c:188: pxNewQueue->pcTail = pxNewQueue->pcHead + ( ucQueueLength * ucItemSize );
                            451 ;     genPlus
   1997 E5 12               452 	mov	a,_bp
   1999 24 02               453 	add	a,#0x02
   199B F8                  454 	mov	r0,a
   199C E5 12               455 	mov	a,_bp
   199E 24 05               456 	add	a,#0x05
   19A0 F9                  457 	mov	r1,a
                            458 ;     genPlusIncr
   19A1 74 03               459 	mov	a,#0x03
   19A3 26                  460 	add	a,@r0
   19A4 F7                  461 	mov	@r1,a
   19A5 74 00               462 	mov	a,#0x00
   19A7 08                  463 	inc	r0
   19A8 36                  464 	addc	a,@r0
   19A9 09                  465 	inc	r1
   19AA F7                  466 	mov	@r1,a
   19AB 08                  467 	inc	r0
   19AC 09                  468 	inc	r1
   19AD E6                  469 	mov	a,@r0
   19AE F7                  470 	mov	@r1,a
                            471 ;     genPointerGet
                            472 ;     genGenPointerGet
   19AF E5 12               473 	mov	a,_bp
   19B1 24 02               474 	add	a,#0x02
   19B3 F8                  475 	mov	r0,a
   19B4 86 82               476 	mov	dpl,@r0
   19B6 08                  477 	inc	r0
   19B7 86 83               478 	mov	dph,@r0
   19B9 08                  479 	inc	r0
   19BA 86 F0               480 	mov	b,@r0
   19BC 12 AE 30            481 	lcall	__gptrget
   19BF FD                  482 	mov	r5,a
   19C0 A3                  483 	inc	dptr
   19C1 12 AE 30            484 	lcall	__gptrget
   19C4 FA                  485 	mov	r2,a
   19C5 A3                  486 	inc	dptr
   19C6 12 AE 30            487 	lcall	__gptrget
   19C9 FB                  488 	mov	r3,a
                            489 ;     genPlus
   19CA E5 06               490 	mov	a,ar6
   19CC 25 05               491 	add	a,ar5
   19CE FE                  492 	mov	r6,a
   19CF E5 07               493 	mov	a,ar7
   19D1 35 02               494 	addc	a,ar2
   19D3 FF                  495 	mov	r7,a
   19D4 8B 04               496 	mov	ar4,r3
                            497 ;     genPointerSet
                            498 ;     genGenPointerSet
   19D6 E5 12               499 	mov	a,_bp
   19D8 24 05               500 	add	a,#0x05
   19DA F8                  501 	mov	r0,a
   19DB 86 82               502 	mov	dpl,@r0
   19DD 08                  503 	inc	r0
   19DE 86 83               504 	mov	dph,@r0
   19E0 08                  505 	inc	r0
   19E1 86 F0               506 	mov	b,@r0
   19E3 EE                  507 	mov	a,r6
   19E4 12 A3 97            508 	lcall	__gptrput
   19E7 A3                  509 	inc	dptr
   19E8 EF                  510 	mov	a,r7
   19E9 12 A3 97            511 	lcall	__gptrput
   19EC A3                  512 	inc	dptr
   19ED EC                  513 	mov	a,r4
   19EE 12 A3 97            514 	lcall	__gptrput
                            515 ;../../Source/queue.c:189: pxNewQueue->ucMessagesWaiting = ( unsigned portCHAR ) 0;
                            516 ;     genPlus
   19F1 E5 12               517 	mov	a,_bp
   19F3 24 02               518 	add	a,#0x02
   19F5 F8                  519 	mov	r0,a
   19F6 74 38               520 	mov	a,#0x38
   19F8 26                  521 	add	a,@r0
   19F9 FC                  522 	mov	r4,a
   19FA 74 00               523 	mov	a,#0x00
   19FC 08                  524 	inc	r0
   19FD 36                  525 	addc	a,@r0
   19FE FE                  526 	mov	r6,a
   19FF 08                  527 	inc	r0
   1A00 86 07               528 	mov	ar7,@r0
                            529 ;     genPointerSet
                            530 ;     genGenPointerSet
   1A02 8C 82               531 	mov	dpl,r4
   1A04 8E 83               532 	mov	dph,r6
   1A06 8F F0               533 	mov	b,r7
   1A08 74 00               534 	mov	a,#0x00
   1A0A 12 A3 97            535 	lcall	__gptrput
                            536 ;../../Source/queue.c:190: pxNewQueue->pcWriteTo = pxNewQueue->pcHead;
                            537 ;     genPlus
   1A0D E5 12               538 	mov	a,_bp
   1A0F 24 02               539 	add	a,#0x02
   1A11 F8                  540 	mov	r0,a
   1A12 74 06               541 	mov	a,#0x06
   1A14 26                  542 	add	a,@r0
   1A15 FC                  543 	mov	r4,a
   1A16 74 00               544 	mov	a,#0x00
   1A18 08                  545 	inc	r0
   1A19 36                  546 	addc	a,@r0
   1A1A FE                  547 	mov	r6,a
   1A1B 08                  548 	inc	r0
   1A1C 86 07               549 	mov	ar7,@r0
                            550 ;     genPointerSet
                            551 ;     genGenPointerSet
   1A1E 8C 82               552 	mov	dpl,r4
   1A20 8E 83               553 	mov	dph,r6
   1A22 8F F0               554 	mov	b,r7
   1A24 ED                  555 	mov	a,r5
   1A25 12 A3 97            556 	lcall	__gptrput
   1A28 A3                  557 	inc	dptr
   1A29 EA                  558 	mov	a,r2
   1A2A 12 A3 97            559 	lcall	__gptrput
   1A2D A3                  560 	inc	dptr
   1A2E EB                  561 	mov	a,r3
   1A2F 12 A3 97            562 	lcall	__gptrput
                            563 ;../../Source/queue.c:191: pxNewQueue->pcReadFrom = pxNewQueue->pcHead + ( ( ucQueueLength - ( unsigned portCHAR ) 1 ) * ucItemSize );
                            564 ;     genPlus
   1A32 E5 12               565 	mov	a,_bp
   1A34 24 02               566 	add	a,#0x02
   1A36 F8                  567 	mov	r0,a
   1A37 E5 12               568 	mov	a,_bp
   1A39 24 05               569 	add	a,#0x05
   1A3B F9                  570 	mov	r1,a
   1A3C 74 09               571 	mov	a,#0x09
   1A3E 26                  572 	add	a,@r0
   1A3F F7                  573 	mov	@r1,a
   1A40 74 00               574 	mov	a,#0x00
   1A42 08                  575 	inc	r0
   1A43 36                  576 	addc	a,@r0
   1A44 09                  577 	inc	r1
   1A45 F7                  578 	mov	@r1,a
   1A46 08                  579 	inc	r0
   1A47 09                  580 	inc	r1
   1A48 E6                  581 	mov	a,@r0
   1A49 F7                  582 	mov	@r1,a
                            583 ;     genCast
   1A4A E5 12               584 	mov	a,_bp
   1A4C 24 01               585 	add	a,#0x01
   1A4E F8                  586 	mov	r0,a
   1A4F 86 04               587 	mov	ar4,@r0
   1A51 7E 00               588 	mov	r6,#0x00
                            589 ;     genMinus
   1A53 E5 12               590 	mov	a,_bp
   1A55 24 08               591 	add	a,#0x08
   1A57 F8                  592 	mov	r0,a
                            593 ;     genMinusDec
   1A58 EC                  594 	mov	a,r4
   1A59 24 FF               595 	add	a,#0xff
   1A5B F6                  596 	mov	@r0,a
   1A5C EE                  597 	mov	a,r6
   1A5D 34 FF               598 	addc	a,#0xff
   1A5F 08                  599 	inc	r0
   1A60 F6                  600 	mov	@r0,a
                            601 ;     genCast
   1A61 E5 12               602 	mov	a,_bp
   1A63 24 FD               603 	add	a,#0xfd
   1A65 F8                  604 	mov	r0,a
   1A66 86 07               605 	mov	ar7,@r0
   1A68 7C 00               606 	mov	r4,#0x00
                            607 ;     genIpush
   1A6A C0 02               608 	push	ar2
   1A6C C0 03               609 	push	ar3
   1A6E C0 05               610 	push	ar5
   1A70 C0 07               611 	push	ar7
   1A72 C0 04               612 	push	ar4
                            613 ;     genCall
   1A74 E5 12               614 	mov	a,_bp
   1A76 24 08               615 	add	a,#0x08
   1A78 F8                  616 	mov	r0,a
   1A79 86 82               617 	mov	dpl,@r0
   1A7B 08                  618 	inc	r0
   1A7C 86 83               619 	mov	dph,@r0
   1A7E 12 A3 D2            620 	lcall	__mulint
   1A81 AC 82               621 	mov	r4,dpl
   1A83 AE 83               622 	mov	r6,dph
   1A85 15 81               623 	dec	sp
   1A87 15 81               624 	dec	sp
   1A89 D0 05               625 	pop	ar5
   1A8B D0 03               626 	pop	ar3
   1A8D D0 02               627 	pop	ar2
                            628 ;     genPlus
   1A8F E5 04               629 	mov	a,ar4
   1A91 25 05               630 	add	a,ar5
   1A93 FD                  631 	mov	r5,a
   1A94 E5 06               632 	mov	a,ar6
   1A96 35 02               633 	addc	a,ar2
   1A98 FA                  634 	mov	r2,a
                            635 ;     genPointerSet
                            636 ;     genGenPointerSet
   1A99 E5 12               637 	mov	a,_bp
   1A9B 24 05               638 	add	a,#0x05
   1A9D F8                  639 	mov	r0,a
   1A9E 86 82               640 	mov	dpl,@r0
   1AA0 08                  641 	inc	r0
   1AA1 86 83               642 	mov	dph,@r0
   1AA3 08                  643 	inc	r0
   1AA4 86 F0               644 	mov	b,@r0
   1AA6 ED                  645 	mov	a,r5
   1AA7 12 A3 97            646 	lcall	__gptrput
   1AAA A3                  647 	inc	dptr
   1AAB EA                  648 	mov	a,r2
   1AAC 12 A3 97            649 	lcall	__gptrput
   1AAF A3                  650 	inc	dptr
   1AB0 EB                  651 	mov	a,r3
   1AB1 12 A3 97            652 	lcall	__gptrput
                            653 ;../../Source/queue.c:192: pxNewQueue->ucLength = ucQueueLength;
                            654 ;     genPlus
   1AB4 E5 12               655 	mov	a,_bp
   1AB6 24 02               656 	add	a,#0x02
   1AB8 F8                  657 	mov	r0,a
   1AB9 74 39               658 	mov	a,#0x39
   1ABB 26                  659 	add	a,@r0
   1ABC FA                  660 	mov	r2,a
   1ABD 74 00               661 	mov	a,#0x00
   1ABF 08                  662 	inc	r0
   1AC0 36                  663 	addc	a,@r0
   1AC1 FB                  664 	mov	r3,a
   1AC2 08                  665 	inc	r0
   1AC3 86 04               666 	mov	ar4,@r0
                            667 ;     genPointerSet
                            668 ;     genGenPointerSet
   1AC5 8A 82               669 	mov	dpl,r2
   1AC7 8B 83               670 	mov	dph,r3
   1AC9 8C F0               671 	mov	b,r4
   1ACB E5 12               672 	mov	a,_bp
   1ACD 24 01               673 	add	a,#0x01
   1ACF F8                  674 	mov	r0,a
   1AD0 E6                  675 	mov	a,@r0
   1AD1 12 A3 97            676 	lcall	__gptrput
                            677 ;../../Source/queue.c:193: pxNewQueue->ucItemSize = ucItemSize;
                            678 ;     genPlus
   1AD4 E5 12               679 	mov	a,_bp
   1AD6 24 02               680 	add	a,#0x02
   1AD8 F8                  681 	mov	r0,a
   1AD9 74 3A               682 	mov	a,#0x3A
   1ADB 26                  683 	add	a,@r0
   1ADC FA                  684 	mov	r2,a
   1ADD 74 00               685 	mov	a,#0x00
   1ADF 08                  686 	inc	r0
   1AE0 36                  687 	addc	a,@r0
   1AE1 FB                  688 	mov	r3,a
   1AE2 08                  689 	inc	r0
   1AE3 86 04               690 	mov	ar4,@r0
                            691 ;     genPointerSet
                            692 ;     genGenPointerSet
   1AE5 8A 82               693 	mov	dpl,r2
   1AE7 8B 83               694 	mov	dph,r3
   1AE9 8C F0               695 	mov	b,r4
   1AEB E5 12               696 	mov	a,_bp
   1AED 24 FD               697 	add	a,#0xfd
   1AEF F8                  698 	mov	r0,a
   1AF0 E6                  699 	mov	a,@r0
   1AF1 12 A3 97            700 	lcall	__gptrput
                            701 ;../../Source/queue.c:194: pxNewQueue->cRxLock = queueUNLOCKED;
                            702 ;     genPlus
   1AF4 E5 12               703 	mov	a,_bp
   1AF6 24 02               704 	add	a,#0x02
   1AF8 F8                  705 	mov	r0,a
   1AF9 74 3B               706 	mov	a,#0x3B
   1AFB 26                  707 	add	a,@r0
   1AFC FA                  708 	mov	r2,a
   1AFD 74 00               709 	mov	a,#0x00
   1AFF 08                  710 	inc	r0
   1B00 36                  711 	addc	a,@r0
   1B01 FB                  712 	mov	r3,a
   1B02 08                  713 	inc	r0
   1B03 86 04               714 	mov	ar4,@r0
                            715 ;     genPointerSet
                            716 ;     genGenPointerSet
   1B05 8A 82               717 	mov	dpl,r2
   1B07 8B 83               718 	mov	dph,r3
   1B09 8C F0               719 	mov	b,r4
   1B0B 74 FF               720 	mov	a,#0xFF
   1B0D 12 A3 97            721 	lcall	__gptrput
                            722 ;../../Source/queue.c:195: pxNewQueue->cTxLock = queueUNLOCKED;
                            723 ;     genPlus
   1B10 E5 12               724 	mov	a,_bp
   1B12 24 02               725 	add	a,#0x02
   1B14 F8                  726 	mov	r0,a
   1B15 74 3C               727 	mov	a,#0x3C
   1B17 26                  728 	add	a,@r0
   1B18 FA                  729 	mov	r2,a
   1B19 74 00               730 	mov	a,#0x00
   1B1B 08                  731 	inc	r0
   1B1C 36                  732 	addc	a,@r0
   1B1D FB                  733 	mov	r3,a
   1B1E 08                  734 	inc	r0
   1B1F 86 04               735 	mov	ar4,@r0
                            736 ;     genPointerSet
                            737 ;     genGenPointerSet
   1B21 8A 82               738 	mov	dpl,r2
   1B23 8B 83               739 	mov	dph,r3
   1B25 8C F0               740 	mov	b,r4
   1B27 74 FF               741 	mov	a,#0xFF
   1B29 12 A3 97            742 	lcall	__gptrput
                            743 ;../../Source/queue.c:198: vListInitialise( &( pxNewQueue->xTasksWaitingToSend ) );
                            744 ;     genPlus
   1B2C E5 12               745 	mov	a,_bp
   1B2E 24 02               746 	add	a,#0x02
   1B30 F8                  747 	mov	r0,a
   1B31 74 0C               748 	mov	a,#0x0C
   1B33 26                  749 	add	a,@r0
   1B34 FA                  750 	mov	r2,a
   1B35 74 00               751 	mov	a,#0x00
   1B37 08                  752 	inc	r0
   1B38 36                  753 	addc	a,@r0
   1B39 FB                  754 	mov	r3,a
   1B3A 08                  755 	inc	r0
   1B3B 86 04               756 	mov	ar4,@r0
                            757 ;     genCall
   1B3D 8A 82               758 	mov	dpl,r2
   1B3F 8B 83               759 	mov	dph,r3
   1B41 8C F0               760 	mov	b,r4
   1B43 12 29 62            761 	lcall	_vListInitialise
                            762 ;../../Source/queue.c:199: vListInitialise( &( pxNewQueue->xTasksWaitingToReceive ) ); 
                            763 ;     genPlus
   1B46 E5 12               764 	mov	a,_bp
   1B48 24 02               765 	add	a,#0x02
   1B4A F8                  766 	mov	r0,a
   1B4B 74 22               767 	mov	a,#0x22
   1B4D 26                  768 	add	a,@r0
   1B4E FA                  769 	mov	r2,a
   1B4F 74 00               770 	mov	a,#0x00
   1B51 08                  771 	inc	r0
   1B52 36                  772 	addc	a,@r0
   1B53 FB                  773 	mov	r3,a
   1B54 08                  774 	inc	r0
   1B55 86 04               775 	mov	ar4,@r0
                            776 ;     genCall
   1B57 8A 82               777 	mov	dpl,r2
   1B59 8B 83               778 	mov	dph,r3
   1B5B 8C F0               779 	mov	b,r4
   1B5D 12 29 62            780 	lcall	_vListInitialise
                            781 ;../../Source/queue.c:201: return  pxNewQueue;
                            782 ;     genRet
   1B60 E5 12               783 	mov	a,_bp
   1B62 24 02               784 	add	a,#0x02
   1B64 F8                  785 	mov	r0,a
   1B65 86 82               786 	mov	dpl,@r0
   1B67 08                  787 	inc	r0
   1B68 86 83               788 	mov	dph,@r0
   1B6A 08                  789 	inc	r0
   1B6B 86 F0               790 	mov	b,@r0
   1B6D 02 1B 89            791 	ljmp	00108$
   1B70                     792 00102$:
                            793 ;../../Source/queue.c:205: vPortFree( pxNewQueue );
                            794 ;     genCall
   1B70 E5 12               795 	mov	a,_bp
   1B72 24 02               796 	add	a,#0x02
   1B74 F8                  797 	mov	r0,a
   1B75 86 82               798 	mov	dpl,@r0
   1B77 08                  799 	inc	r0
   1B78 86 83               800 	mov	dph,@r0
   1B7A 08                  801 	inc	r0
   1B7B 86 F0               802 	mov	b,@r0
   1B7D 12 32 8D            803 	lcall	_vPortFree
   1B80                     804 00107$:
                            805 ;../../Source/queue.c:212: return NULL;
                            806 ;     genRet
   1B80 75 82 00            807 	mov	dpl,#0x00
   1B83 75 83 00            808 	mov	dph,#0x00
   1B86 75 F0 00            809 	mov	b,#0x00
   1B89                     810 00108$:
   1B89 85 12 81            811 	mov	sp,_bp
   1B8C D0 12               812 	pop	_bp
   1B8E 22                  813 	ret
                            814 ;------------------------------------------------------------
                            815 ;Allocation info for local variables in function 'cQueueSend'
                            816 ;------------------------------------------------------------
                            817 ;pvItemToQueue             Allocated to stack - offset -5
                            818 ;xTicksToWait              Allocated to stack - offset -7
                            819 ;pxQueue                   Allocated to stack - offset 1
                            820 ;cReturn                   Allocated to registers r2 
                            821 ;sloc0                     Allocated to stack - offset 4
                            822 ;sloc1                     Allocated to stack - offset 5
                            823 ;sloc2                     Allocated to stack - offset 8
                            824 ;sloc3                     Allocated to stack - offset 11
                            825 ;------------------------------------------------------------
                            826 ;../../Source/queue.c:216: signed portCHAR cQueueSend( xQueueHandle pxQueue, const void *pvItemToQueue, portTickType xTicksToWait )
                            827 ;	-----------------------------------------
                            828 ;	 function cQueueSend
                            829 ;	-----------------------------------------
   1B8F                     830 _cQueueSend:
   1B8F C0 12               831 	push	_bp
   1B91 85 81 12            832 	mov	_bp,sp
                            833 ;     genReceive
   1B94 C0 82               834 	push	dpl
   1B96 C0 83               835 	push	dph
   1B98 C0 F0               836 	push	b
   1B9A E5 81               837 	mov	a,sp
   1B9C 24 0C               838 	add	a,#0x0c
   1B9E F5 81               839 	mov	sp,a
                            840 ;../../Source/queue.c:221: vTaskSuspendAll();
                            841 ;     genCall
   1BA0 12 06 94            842 	lcall	_vTaskSuspendAll
                            843 ;../../Source/queue.c:243: prvLockQueue( pxQueue );
                            844 ;     genInline
   1BA3 C0 E0 C0 A8         845 	 push ACC push IE 
                            846 ;     genAssign
   1BA7 C2 AF               847 	clr	_EA
                            848 ;     genPlus
   1BA9 E5 12               849 	mov	a,_bp
   1BAB 24 01               850 	add	a,#0x01
   1BAD F8                  851 	mov	r0,a
   1BAE 74 3B               852 	mov	a,#0x3B
   1BB0 26                  853 	add	a,@r0
   1BB1 FD                  854 	mov	r5,a
   1BB2 74 00               855 	mov	a,#0x00
   1BB4 08                  856 	inc	r0
   1BB5 36                  857 	addc	a,@r0
   1BB6 FE                  858 	mov	r6,a
   1BB7 08                  859 	inc	r0
   1BB8 86 07               860 	mov	ar7,@r0
                            861 ;     genPointerGet
                            862 ;     genGenPointerGet
   1BBA 8D 82               863 	mov	dpl,r5
   1BBC 8E 83               864 	mov	dph,r6
   1BBE 8F F0               865 	mov	b,r7
   1BC0 12 AE 30            866 	lcall	__gptrget
   1BC3 FA                  867 	mov	r2,a
                            868 ;     genPlus
                            869 ;     genPlusIncr
   1BC4 0A                  870 	inc	r2
                            871 ;     genPointerSet
                            872 ;     genGenPointerSet
   1BC5 8D 82               873 	mov	dpl,r5
   1BC7 8E 83               874 	mov	dph,r6
   1BC9 8F F0               875 	mov	b,r7
   1BCB EA                  876 	mov	a,r2
   1BCC 12 A3 97            877 	lcall	__gptrput
                            878 ;     genPlus
   1BCF E5 12               879 	mov	a,_bp
   1BD1 24 01               880 	add	a,#0x01
   1BD3 F8                  881 	mov	r0,a
   1BD4 74 3C               882 	mov	a,#0x3C
   1BD6 26                  883 	add	a,@r0
   1BD7 FA                  884 	mov	r2,a
   1BD8 74 00               885 	mov	a,#0x00
   1BDA 08                  886 	inc	r0
   1BDB 36                  887 	addc	a,@r0
   1BDC FB                  888 	mov	r3,a
   1BDD 08                  889 	inc	r0
   1BDE 86 04               890 	mov	ar4,@r0
                            891 ;     genPointerGet
                            892 ;     genGenPointerGet
   1BE0 8A 82               893 	mov	dpl,r2
   1BE2 8B 83               894 	mov	dph,r3
   1BE4 8C F0               895 	mov	b,r4
   1BE6 12 AE 30            896 	lcall	__gptrget
   1BE9 FD                  897 	mov	r5,a
                            898 ;     genPlus
                            899 ;     genPlusIncr
   1BEA 0D                  900 	inc	r5
                            901 ;     genPointerSet
                            902 ;     genGenPointerSet
   1BEB 8A 82               903 	mov	dpl,r2
   1BED 8B 83               904 	mov	dph,r3
   1BEF 8C F0               905 	mov	b,r4
   1BF1 ED                  906 	mov	a,r5
   1BF2 12 A3 97            907 	lcall	__gptrput
                            908 ;     genInline
   1BF5 D0 E0               909 	 pop ACC 
                            910 ;     genAnd
   1BF7 53 E0 80            911 	anl	_ACC,#0x80
                            912 ;     genOr
   1BFA E5 E0               913 	mov	a,_ACC
   1BFC 42 A8               914 	orl	_IE,a
                            915 ;     genInline
   1BFE D0 E0               916 	 pop ACC 
                            917 ;../../Source/queue.c:261: if( prvIsQueueFull( pxQueue ) )
                            918 ;     genCall
   1C00 E5 12               919 	mov	a,_bp
   1C02 24 01               920 	add	a,#0x01
   1C04 F8                  921 	mov	r0,a
   1C05 86 82               922 	mov	dpl,@r0
   1C07 08                  923 	inc	r0
   1C08 86 83               924 	mov	dph,@r0
   1C0A 08                  925 	inc	r0
   1C0B 86 F0               926 	mov	b,@r0
   1C0D 12 29 0A            927 	lcall	_prvIsQueueFull
   1C10 E5 82               928 	mov	a,dpl
                            929 ;     genIfx
                            930 ;     genIfxJump
   1C12 70 03               931 	jnz	00126$
   1C14 02 1C DC            932 	ljmp	00106$
   1C17                     933 00126$:
                            934 ;../../Source/queue.c:265: if( xTicksToWait > ( portTickType ) 0 )
                            935 ;     genIfx
   1C17 E5 12               936 	mov	a,_bp
   1C19 24 F9               937 	add	a,#0xf9
   1C1B F8                  938 	mov	r0,a
   1C1C E6                  939 	mov	a,@r0
   1C1D 08                  940 	inc	r0
   1C1E 46                  941 	orl	a,@r0
                            942 ;     genIfxJump
   1C1F 70 03               943 	jnz	00127$
   1C21 02 1C DC            944 	ljmp	00106$
   1C24                     945 00127$:
                            946 ;../../Source/queue.c:280: vTaskPlaceOnEventList( &( pxQueue->xTasksWaitingToSend ), xTicksToWait );
                            947 ;     genPlus
   1C24 E5 12               948 	mov	a,_bp
   1C26 24 01               949 	add	a,#0x01
   1C28 F8                  950 	mov	r0,a
   1C29 74 0C               951 	mov	a,#0x0C
   1C2B 26                  952 	add	a,@r0
   1C2C FA                  953 	mov	r2,a
   1C2D 74 00               954 	mov	a,#0x00
   1C2F 08                  955 	inc	r0
   1C30 36                  956 	addc	a,@r0
   1C31 FB                  957 	mov	r3,a
   1C32 08                  958 	inc	r0
   1C33 86 04               959 	mov	ar4,@r0
                            960 ;     genIpush
   1C35 E5 12               961 	mov	a,_bp
   1C37 24 F9               962 	add	a,#0xf9
   1C39 F8                  963 	mov	r0,a
   1C3A E6                  964 	mov	a,@r0
   1C3B C0 E0               965 	push	acc
   1C3D 08                  966 	inc	r0
   1C3E E6                  967 	mov	a,@r0
   1C3F C0 E0               968 	push	acc
                            969 ;     genCall
   1C41 8A 82               970 	mov	dpl,r2
   1C43 8B 83               971 	mov	dph,r3
   1C45 8C F0               972 	mov	b,r4
   1C47 12 0D 4F            973 	lcall	_vTaskPlaceOnEventList
   1C4A 15 81               974 	dec	sp
   1C4C 15 81               975 	dec	sp
                            976 ;../../Source/queue.c:292: taskENTER_CRITICAL();
                            977 ;     genInline
   1C4E C0 E0 C0 A8         978 	 push ACC push IE 
                            979 ;     genAssign
   1C52 C2 AF               980 	clr	_EA
                            981 ;../../Source/queue.c:301: prvUnlockQueue( pxQueue );
                            982 ;     genCall
   1C54 E5 12               983 	mov	a,_bp
   1C56 24 01               984 	add	a,#0x01
   1C58 F8                  985 	mov	r0,a
   1C59 86 82               986 	mov	dpl,@r0
   1C5B 08                  987 	inc	r0
   1C5C 86 83               988 	mov	dph,@r0
   1C5E 08                  989 	inc	r0
   1C5F 86 F0               990 	mov	b,@r0
   1C61 12 27 80            991 	lcall	_prvUnlockQueue
                            992 ;../../Source/queue.c:305: if( !cTaskResumeAll() )
                            993 ;     genCall
   1C64 12 06 B7            994 	lcall	_cTaskResumeAll
   1C67 E5 82               995 	mov	a,dpl
                            996 ;     genIfx
                            997 ;     genIfxJump
   1C69 60 03               998 	jz	00128$
   1C6B 02 1C 71            999 	ljmp	00102$
   1C6E                    1000 00128$:
                           1001 ;../../Source/queue.c:307: taskYIELD();
                           1002 ;     genCall
   1C6E 12 17 01           1003 	lcall	_vPortYield
   1C71                    1004 00102$:
                           1005 ;../../Source/queue.c:312: vTaskSuspendAll();
                           1006 ;     genCall
   1C71 12 06 94           1007 	lcall	_vTaskSuspendAll
                           1008 ;../../Source/queue.c:313: prvLockQueue( pxQueue );				
                           1009 ;     genInline
   1C74 C0 E0 C0 A8        1010 	 push ACC push IE 
                           1011 ;     genAssign
   1C78 C2 AF              1012 	clr	_EA
                           1013 ;     genPlus
   1C7A E5 12              1014 	mov	a,_bp
   1C7C 24 01              1015 	add	a,#0x01
   1C7E F8                 1016 	mov	r0,a
   1C7F 74 3B              1017 	mov	a,#0x3B
   1C81 26                 1018 	add	a,@r0
   1C82 FA                 1019 	mov	r2,a
   1C83 74 00              1020 	mov	a,#0x00
   1C85 08                 1021 	inc	r0
   1C86 36                 1022 	addc	a,@r0
   1C87 FB                 1023 	mov	r3,a
   1C88 08                 1024 	inc	r0
   1C89 86 04              1025 	mov	ar4,@r0
                           1026 ;     genPointerGet
                           1027 ;     genGenPointerGet
   1C8B 8A 82              1028 	mov	dpl,r2
   1C8D 8B 83              1029 	mov	dph,r3
   1C8F 8C F0              1030 	mov	b,r4
   1C91 12 AE 30           1031 	lcall	__gptrget
   1C94 FD                 1032 	mov	r5,a
                           1033 ;     genPlus
                           1034 ;     genPlusIncr
   1C95 0D                 1035 	inc	r5
                           1036 ;     genPointerSet
                           1037 ;     genGenPointerSet
   1C96 8A 82              1038 	mov	dpl,r2
   1C98 8B 83              1039 	mov	dph,r3
   1C9A 8C F0              1040 	mov	b,r4
   1C9C ED                 1041 	mov	a,r5
   1C9D 12 A3 97           1042 	lcall	__gptrput
                           1043 ;     genPlus
   1CA0 E5 12              1044 	mov	a,_bp
   1CA2 24 01              1045 	add	a,#0x01
   1CA4 F8                 1046 	mov	r0,a
   1CA5 74 3C              1047 	mov	a,#0x3C
   1CA7 26                 1048 	add	a,@r0
   1CA8 FA                 1049 	mov	r2,a
   1CA9 74 00              1050 	mov	a,#0x00
   1CAB 08                 1051 	inc	r0
   1CAC 36                 1052 	addc	a,@r0
   1CAD FB                 1053 	mov	r3,a
   1CAE 08                 1054 	inc	r0
   1CAF 86 04              1055 	mov	ar4,@r0
                           1056 ;     genPointerGet
                           1057 ;     genGenPointerGet
   1CB1 8A 82              1058 	mov	dpl,r2
   1CB3 8B 83              1059 	mov	dph,r3
   1CB5 8C F0              1060 	mov	b,r4
   1CB7 12 AE 30           1061 	lcall	__gptrget
   1CBA FD                 1062 	mov	r5,a
                           1063 ;     genPlus
                           1064 ;     genPlusIncr
   1CBB 0D                 1065 	inc	r5
                           1066 ;     genPointerSet
                           1067 ;     genGenPointerSet
   1CBC 8A 82              1068 	mov	dpl,r2
   1CBE 8B 83              1069 	mov	dph,r3
   1CC0 8C F0              1070 	mov	b,r4
   1CC2 ED                 1071 	mov	a,r5
   1CC3 12 A3 97           1072 	lcall	__gptrput
                           1073 ;     genInline
   1CC6 D0 E0              1074 	 pop ACC 
                           1075 ;     genAnd
   1CC8 53 E0 80           1076 	anl	_ACC,#0x80
                           1077 ;     genOr
   1CCB E5 E0              1078 	mov	a,_ACC
   1CCD 42 A8              1079 	orl	_IE,a
                           1080 ;     genInline
   1CCF D0 E0              1081 	 pop ACC 
                           1082 ;../../Source/queue.c:315: taskEXIT_CRITICAL();
                           1083 ;     genInline
   1CD1 D0 E0              1084 	 pop ACC 
                           1085 ;     genAnd
   1CD3 53 E0 80           1086 	anl	_ACC,#0x80
                           1087 ;     genOr
   1CD6 E5 E0              1088 	mov	a,_ACC
   1CD8 42 A8              1089 	orl	_IE,a
                           1090 ;     genInline
   1CDA D0 E0              1091 	 pop ACC 
   1CDC                    1092 00106$:
                           1093 ;../../Source/queue.c:324: taskENTER_CRITICAL();
                           1094 ;     genInline
   1CDC C0 E0 C0 A8        1095 	 push ACC push IE 
                           1096 ;     genAssign
   1CE0 C2 AF              1097 	clr	_EA
                           1098 ;../../Source/queue.c:326: if( pxQueue->ucMessagesWaiting < pxQueue->ucLength )
                           1099 ;     genPlus
   1CE2 E5 12              1100 	mov	a,_bp
   1CE4 24 01              1101 	add	a,#0x01
   1CE6 F8                 1102 	mov	r0,a
   1CE7 74 38              1103 	mov	a,#0x38
   1CE9 26                 1104 	add	a,@r0
   1CEA FA                 1105 	mov	r2,a
   1CEB 74 00              1106 	mov	a,#0x00
   1CED 08                 1107 	inc	r0
   1CEE 36                 1108 	addc	a,@r0
   1CEF FB                 1109 	mov	r3,a
   1CF0 08                 1110 	inc	r0
   1CF1 86 04              1111 	mov	ar4,@r0
                           1112 ;     genPointerGet
                           1113 ;     genGenPointerGet
   1CF3 8A 82              1114 	mov	dpl,r2
   1CF5 8B 83              1115 	mov	dph,r3
   1CF7 8C F0              1116 	mov	b,r4
   1CF9 E5 12              1117 	mov	a,_bp
   1CFB 24 04              1118 	add	a,#0x04
   1CFD F8                 1119 	mov	r0,a
   1CFE 12 AE 30           1120 	lcall	__gptrget
   1D01 F6                 1121 	mov	@r0,a
                           1122 ;     genPlus
   1D02 E5 12              1123 	mov	a,_bp
   1D04 24 01              1124 	add	a,#0x01
   1D06 F8                 1125 	mov	r0,a
   1D07 74 39              1126 	mov	a,#0x39
   1D09 26                 1127 	add	a,@r0
   1D0A FE                 1128 	mov	r6,a
   1D0B 74 00              1129 	mov	a,#0x00
   1D0D 08                 1130 	inc	r0
   1D0E 36                 1131 	addc	a,@r0
   1D0F FF                 1132 	mov	r7,a
   1D10 08                 1133 	inc	r0
   1D11 86 05              1134 	mov	ar5,@r0
                           1135 ;     genPointerGet
                           1136 ;     genGenPointerGet
   1D13 8E 82              1137 	mov	dpl,r6
   1D15 8F 83              1138 	mov	dph,r7
   1D17 8D F0              1139 	mov	b,r5
   1D19 12 AE 30           1140 	lcall	__gptrget
   1D1C FE                 1141 	mov	r6,a
                           1142 ;     genCmpLt
   1D1D E5 12              1143 	mov	a,_bp
   1D1F 24 04              1144 	add	a,#0x04
   1D21 F8                 1145 	mov	r0,a
                           1146 ;     genCmp
   1D22 C3                 1147 	clr	c
   1D23 E6                 1148 	mov	a,@r0
   1D24 9E                 1149 	subb	a,r6
                           1150 ;     genIfxJump
   1D25 40 03              1151 	jc	00129$
   1D27 02 1E C7           1152 	ljmp	00110$
   1D2A                    1153 00129$:
                           1154 ;../../Source/queue.c:329: prvCopyQueueData( pxQueue, pvItemToQueue );		
                           1155 ;     genPlus
   1D2A E5 12              1156 	mov	a,_bp
   1D2C 24 01              1157 	add	a,#0x01
   1D2E F8                 1158 	mov	r0,a
   1D2F E5 12              1159 	mov	a,_bp
   1D31 24 05              1160 	add	a,#0x05
   1D33 F9                 1161 	mov	r1,a
   1D34 74 3A              1162 	mov	a,#0x3A
   1D36 26                 1163 	add	a,@r0
   1D37 F7                 1164 	mov	@r1,a
   1D38 74 00              1165 	mov	a,#0x00
   1D3A 08                 1166 	inc	r0
   1D3B 36                 1167 	addc	a,@r0
   1D3C 09                 1168 	inc	r1
   1D3D F7                 1169 	mov	@r1,a
   1D3E 08                 1170 	inc	r0
   1D3F 09                 1171 	inc	r1
   1D40 E6                 1172 	mov	a,@r0
   1D41 F7                 1173 	mov	@r1,a
                           1174 ;     genPointerGet
                           1175 ;     genGenPointerGet
   1D42 E5 12              1176 	mov	a,_bp
   1D44 24 05              1177 	add	a,#0x05
   1D46 F8                 1178 	mov	r0,a
   1D47 86 82              1179 	mov	dpl,@r0
   1D49 08                 1180 	inc	r0
   1D4A 86 83              1181 	mov	dph,@r0
   1D4C 08                 1182 	inc	r0
   1D4D 86 F0              1183 	mov	b,@r0
   1D4F 12 AE 30           1184 	lcall	__gptrget
   1D52 FD                 1185 	mov	r5,a
                           1186 ;     genCast
   1D53 E5 12              1187 	mov	a,_bp
   1D55 24 0B              1188 	add	a,#0x0b
   1D57 F8                 1189 	mov	r0,a
   1D58 A6 05              1190 	mov	@r0,ar5
   1D5A 08                 1191 	inc	r0
   1D5B 76 00              1192 	mov	@r0,#0x00
                           1193 ;     genPlus
   1D5D E5 12              1194 	mov	a,_bp
   1D5F 24 01              1195 	add	a,#0x01
   1D61 F8                 1196 	mov	r0,a
   1D62 E5 12              1197 	mov	a,_bp
   1D64 24 08              1198 	add	a,#0x08
   1D66 F9                 1199 	mov	r1,a
   1D67 74 06              1200 	mov	a,#0x06
   1D69 26                 1201 	add	a,@r0
   1D6A F7                 1202 	mov	@r1,a
   1D6B 74 00              1203 	mov	a,#0x00
   1D6D 08                 1204 	inc	r0
   1D6E 36                 1205 	addc	a,@r0
   1D6F 09                 1206 	inc	r1
   1D70 F7                 1207 	mov	@r1,a
   1D71 08                 1208 	inc	r0
   1D72 09                 1209 	inc	r1
   1D73 E6                 1210 	mov	a,@r0
   1D74 F7                 1211 	mov	@r1,a
                           1212 ;     genPointerGet
                           1213 ;     genGenPointerGet
   1D75 E5 12              1214 	mov	a,_bp
   1D77 24 08              1215 	add	a,#0x08
   1D79 F8                 1216 	mov	r0,a
   1D7A 86 82              1217 	mov	dpl,@r0
   1D7C 08                 1218 	inc	r0
   1D7D 86 83              1219 	mov	dph,@r0
   1D7F 08                 1220 	inc	r0
   1D80 86 F0              1221 	mov	b,@r0
   1D82 12 AE 30           1222 	lcall	__gptrget
   1D85 FF                 1223 	mov	r7,a
   1D86 A3                 1224 	inc	dptr
   1D87 12 AE 30           1225 	lcall	__gptrget
   1D8A FD                 1226 	mov	r5,a
   1D8B A3                 1227 	inc	dptr
   1D8C 12 AE 30           1228 	lcall	__gptrget
   1D8F FE                 1229 	mov	r6,a
                           1230 ;     genIpush
   1D90 C0 02              1231 	push	ar2
   1D92 C0 03              1232 	push	ar3
   1D94 C0 04              1233 	push	ar4
   1D96 E5 12              1234 	mov	a,_bp
   1D98 24 0B              1235 	add	a,#0x0b
   1D9A F8                 1236 	mov	r0,a
   1D9B E6                 1237 	mov	a,@r0
   1D9C C0 E0              1238 	push	acc
   1D9E 08                 1239 	inc	r0
   1D9F E6                 1240 	mov	a,@r0
   1DA0 C0 E0              1241 	push	acc
                           1242 ;     genIpush
   1DA2 E5 12              1243 	mov	a,_bp
   1DA4 24 FB              1244 	add	a,#0xfb
   1DA6 F8                 1245 	mov	r0,a
   1DA7 E6                 1246 	mov	a,@r0
   1DA8 C0 E0              1247 	push	acc
   1DAA 08                 1248 	inc	r0
   1DAB E6                 1249 	mov	a,@r0
   1DAC C0 E0              1250 	push	acc
   1DAE 08                 1251 	inc	r0
   1DAF E6                 1252 	mov	a,@r0
   1DB0 C0 E0              1253 	push	acc
                           1254 ;     genCall
   1DB2 8F 82              1255 	mov	dpl,r7
   1DB4 8D 83              1256 	mov	dph,r5
   1DB6 8E F0              1257 	mov	b,r6
   1DB8 12 AC 5D           1258 	lcall	_memcpy
   1DBB E5 81              1259 	mov	a,sp
   1DBD 24 FB              1260 	add	a,#0xfb
   1DBF F5 81              1261 	mov	sp,a
   1DC1 D0 04              1262 	pop	ar4
   1DC3 D0 03              1263 	pop	ar3
   1DC5 D0 02              1264 	pop	ar2
                           1265 ;     genPointerGet
                           1266 ;     genGenPointerGet
   1DC7 8A 82              1267 	mov	dpl,r2
   1DC9 8B 83              1268 	mov	dph,r3
   1DCB 8C F0              1269 	mov	b,r4
   1DCD 12 AE 30           1270 	lcall	__gptrget
   1DD0 FD                 1271 	mov	r5,a
                           1272 ;     genPlus
                           1273 ;     genPlusIncr
   1DD1 0D                 1274 	inc	r5
                           1275 ;     genPointerSet
                           1276 ;     genGenPointerSet
   1DD2 8A 82              1277 	mov	dpl,r2
   1DD4 8B 83              1278 	mov	dph,r3
   1DD6 8C F0              1279 	mov	b,r4
   1DD8 ED                 1280 	mov	a,r5
   1DD9 12 A3 97           1281 	lcall	__gptrput
                           1282 ;     genPointerGet
                           1283 ;     genGenPointerGet
   1DDC E5 12              1284 	mov	a,_bp
   1DDE 24 08              1285 	add	a,#0x08
   1DE0 F8                 1286 	mov	r0,a
   1DE1 86 82              1287 	mov	dpl,@r0
   1DE3 08                 1288 	inc	r0
   1DE4 86 83              1289 	mov	dph,@r0
   1DE6 08                 1290 	inc	r0
   1DE7 86 F0              1291 	mov	b,@r0
   1DE9 12 AE 30           1292 	lcall	__gptrget
   1DEC FA                 1293 	mov	r2,a
   1DED A3                 1294 	inc	dptr
   1DEE 12 AE 30           1295 	lcall	__gptrget
   1DF1 FB                 1296 	mov	r3,a
   1DF2 A3                 1297 	inc	dptr
   1DF3 12 AE 30           1298 	lcall	__gptrget
   1DF6 FC                 1299 	mov	r4,a
                           1300 ;     genPointerGet
                           1301 ;     genGenPointerGet
   1DF7 E5 12              1302 	mov	a,_bp
   1DF9 24 05              1303 	add	a,#0x05
   1DFB F8                 1304 	mov	r0,a
   1DFC 86 82              1305 	mov	dpl,@r0
   1DFE 08                 1306 	inc	r0
   1DFF 86 83              1307 	mov	dph,@r0
   1E01 08                 1308 	inc	r0
   1E02 86 F0              1309 	mov	b,@r0
   1E04 12 AE 30           1310 	lcall	__gptrget
   1E07 FD                 1311 	mov	r5,a
                           1312 ;     genPlus
   1E08 E5 05              1313 	mov	a,ar5
   1E0A 25 02              1314 	add	a,ar2
   1E0C FA                 1315 	mov	r2,a
   1E0D 74 00              1316 	mov	a,#0x00
   1E0F 35 03              1317 	addc	a,ar3
   1E11 FB                 1318 	mov	r3,a
                           1319 ;     genPointerSet
                           1320 ;     genGenPointerSet
   1E12 E5 12              1321 	mov	a,_bp
   1E14 24 08              1322 	add	a,#0x08
   1E16 F8                 1323 	mov	r0,a
   1E17 86 82              1324 	mov	dpl,@r0
   1E19 08                 1325 	inc	r0
   1E1A 86 83              1326 	mov	dph,@r0
   1E1C 08                 1327 	inc	r0
   1E1D 86 F0              1328 	mov	b,@r0
   1E1F EA                 1329 	mov	a,r2
   1E20 12 A3 97           1330 	lcall	__gptrput
   1E23 A3                 1331 	inc	dptr
   1E24 EB                 1332 	mov	a,r3
   1E25 12 A3 97           1333 	lcall	__gptrput
   1E28 A3                 1334 	inc	dptr
   1E29 EC                 1335 	mov	a,r4
   1E2A 12 A3 97           1336 	lcall	__gptrput
                           1337 ;     genPlus
   1E2D E5 12              1338 	mov	a,_bp
   1E2F 24 01              1339 	add	a,#0x01
   1E31 F8                 1340 	mov	r0,a
                           1341 ;     genPlusIncr
   1E32 74 03              1342 	mov	a,#0x03
   1E34 26                 1343 	add	a,@r0
   1E35 FD                 1344 	mov	r5,a
   1E36 74 00              1345 	mov	a,#0x00
   1E38 08                 1346 	inc	r0
   1E39 36                 1347 	addc	a,@r0
   1E3A FE                 1348 	mov	r6,a
   1E3B 08                 1349 	inc	r0
   1E3C 86 07              1350 	mov	ar7,@r0
                           1351 ;     genPointerGet
                           1352 ;     genGenPointerGet
   1E3E 8D 82              1353 	mov	dpl,r5
   1E40 8E 83              1354 	mov	dph,r6
   1E42 8F F0              1355 	mov	b,r7
   1E44 12 AE 30           1356 	lcall	__gptrget
   1E47 FD                 1357 	mov	r5,a
   1E48 A3                 1358 	inc	dptr
   1E49 12 AE 30           1359 	lcall	__gptrget
   1E4C FE                 1360 	mov	r6,a
   1E4D A3                 1361 	inc	dptr
   1E4E 12 AE 30           1362 	lcall	__gptrget
   1E51 FF                 1363 	mov	r7,a
                           1364 ;     genCmpLt
                           1365 ;     genCmp
   1E52 C3                 1366 	clr	c
   1E53 EA                 1367 	mov	a,r2
   1E54 9D                 1368 	subb	a,r5
   1E55 EB                 1369 	mov	a,r3
   1E56 9E                 1370 	subb	a,r6
   1E57 EC                 1371 	mov	a,r4
   1E58 64 80              1372 	xrl	a,#0x80
   1E5A 8F F0              1373 	mov	b,r7
   1E5C 63 F0 80           1374 	xrl	b,#0x80
   1E5F 95 F0              1375 	subb	a,b
                           1376 ;     genIfxJump
   1E61 50 03              1377 	jnc	00130$
   1E63 02 1E 9C           1378 	ljmp	00108$
   1E66                    1379 00130$:
                           1380 ;     genPointerGet
                           1381 ;     genGenPointerGet
   1E66 E5 12              1382 	mov	a,_bp
   1E68 24 01              1383 	add	a,#0x01
   1E6A F8                 1384 	mov	r0,a
   1E6B 86 82              1385 	mov	dpl,@r0
   1E6D 08                 1386 	inc	r0
   1E6E 86 83              1387 	mov	dph,@r0
   1E70 08                 1388 	inc	r0
   1E71 86 F0              1389 	mov	b,@r0
   1E73 12 AE 30           1390 	lcall	__gptrget
   1E76 FA                 1391 	mov	r2,a
   1E77 A3                 1392 	inc	dptr
   1E78 12 AE 30           1393 	lcall	__gptrget
   1E7B FB                 1394 	mov	r3,a
   1E7C A3                 1395 	inc	dptr
   1E7D 12 AE 30           1396 	lcall	__gptrget
   1E80 FC                 1397 	mov	r4,a
                           1398 ;     genPointerSet
                           1399 ;     genGenPointerSet
   1E81 E5 12              1400 	mov	a,_bp
   1E83 24 08              1401 	add	a,#0x08
   1E85 F8                 1402 	mov	r0,a
   1E86 86 82              1403 	mov	dpl,@r0
   1E88 08                 1404 	inc	r0
   1E89 86 83              1405 	mov	dph,@r0
   1E8B 08                 1406 	inc	r0
   1E8C 86 F0              1407 	mov	b,@r0
   1E8E EA                 1408 	mov	a,r2
   1E8F 12 A3 97           1409 	lcall	__gptrput
   1E92 A3                 1410 	inc	dptr
   1E93 EB                 1411 	mov	a,r3
   1E94 12 A3 97           1412 	lcall	__gptrput
   1E97 A3                 1413 	inc	dptr
   1E98 EC                 1414 	mov	a,r4
   1E99 12 A3 97           1415 	lcall	__gptrput
   1E9C                    1416 00108$:
                           1417 ;../../Source/queue.c:330: cReturn = ( signed portCHAR ) pdPASS;
                           1418 ;     genAssign
   1E9C 7A 01              1419 	mov	r2,#0x01
                           1420 ;../../Source/queue.c:334: ++( pxQueue->cTxLock );
                           1421 ;     genPlus
   1E9E E5 12              1422 	mov	a,_bp
   1EA0 24 01              1423 	add	a,#0x01
   1EA2 F8                 1424 	mov	r0,a
   1EA3 74 3C              1425 	mov	a,#0x3C
   1EA5 26                 1426 	add	a,@r0
   1EA6 FB                 1427 	mov	r3,a
   1EA7 74 00              1428 	mov	a,#0x00
   1EA9 08                 1429 	inc	r0
   1EAA 36                 1430 	addc	a,@r0
   1EAB FC                 1431 	mov	r4,a
   1EAC 08                 1432 	inc	r0
   1EAD 86 05              1433 	mov	ar5,@r0
                           1434 ;     genPointerGet
                           1435 ;     genGenPointerGet
   1EAF 8B 82              1436 	mov	dpl,r3
   1EB1 8C 83              1437 	mov	dph,r4
   1EB3 8D F0              1438 	mov	b,r5
   1EB5 12 AE 30           1439 	lcall	__gptrget
   1EB8 FE                 1440 	mov	r6,a
                           1441 ;     genPlus
                           1442 ;     genPlusIncr
   1EB9 0E                 1443 	inc	r6
                           1444 ;     genPointerSet
                           1445 ;     genGenPointerSet
   1EBA 8B 82              1446 	mov	dpl,r3
   1EBC 8C 83              1447 	mov	dph,r4
   1EBE 8D F0              1448 	mov	b,r5
   1EC0 EE                 1449 	mov	a,r6
   1EC1 12 A3 97           1450 	lcall	__gptrput
   1EC4 02 1E C9           1451 	ljmp	00111$
   1EC7                    1452 00110$:
                           1453 ;../../Source/queue.c:338: cReturn = errQUEUE_FULL;
                           1454 ;     genAssign
   1EC7 7A FD              1455 	mov	r2,#0xFD
   1EC9                    1456 00111$:
                           1457 ;../../Source/queue.c:341: taskEXIT_CRITICAL();
                           1458 ;     genInline
   1EC9 D0 E0              1459 	 pop ACC 
                           1460 ;     genAnd
   1ECB 53 E0 80           1461 	anl	_ACC,#0x80
                           1462 ;     genOr
   1ECE E5 E0              1463 	mov	a,_ACC
   1ED0 42 A8              1464 	orl	_IE,a
                           1465 ;     genInline
   1ED2 D0 E0              1466 	 pop ACC 
                           1467 ;../../Source/queue.c:346: if( prvUnlockQueue( pxQueue ) )
                           1468 ;     genCall
   1ED4 E5 12              1469 	mov	a,_bp
   1ED6 24 01              1470 	add	a,#0x01
   1ED8 F8                 1471 	mov	r0,a
   1ED9 86 82              1472 	mov	dpl,@r0
   1EDB 08                 1473 	inc	r0
   1EDC 86 83              1474 	mov	dph,@r0
   1EDE 08                 1475 	inc	r0
   1EDF 86 F0              1476 	mov	b,@r0
   1EE1 C0 02              1477 	push	ar2
   1EE3 12 27 80           1478 	lcall	_prvUnlockQueue
   1EE6 E5 82              1479 	mov	a,dpl
   1EE8 D0 02              1480 	pop	ar2
                           1481 ;     genIfx
                           1482 ;     genIfxJump
   1EEA 70 03              1483 	jnz	00131$
   1EEC 02 1F 03           1484 	ljmp	00115$
   1EEF                    1485 00131$:
                           1486 ;../../Source/queue.c:352: if( !cTaskResumeAll() )
                           1487 ;     genCall
   1EEF C0 02              1488 	push	ar2
   1EF1 12 06 B7           1489 	lcall	_cTaskResumeAll
   1EF4 E5 82              1490 	mov	a,dpl
   1EF6 D0 02              1491 	pop	ar2
                           1492 ;     genIfx
                           1493 ;     genIfxJump
   1EF8 60 03              1494 	jz	00132$
   1EFA 02 1F 0A           1495 	ljmp	00116$
   1EFD                    1496 00132$:
                           1497 ;../../Source/queue.c:354: taskYIELD();
                           1498 ;     genCall
   1EFD 12 17 01           1499 	lcall	_vPortYield
   1F00 02 1F 0A           1500 	ljmp	00116$
   1F03                    1501 00115$:
                           1502 ;../../Source/queue.c:361: cTaskResumeAll();
                           1503 ;     genCall
   1F03 C0 02              1504 	push	ar2
   1F05 12 06 B7           1505 	lcall	_cTaskResumeAll
   1F08 D0 02              1506 	pop	ar2
   1F0A                    1507 00116$:
                           1508 ;../../Source/queue.c:364: return cReturn;
                           1509 ;     genRet
   1F0A 8A 82              1510 	mov	dpl,r2
   1F0C                    1511 00117$:
   1F0C 85 12 81           1512 	mov	sp,_bp
   1F0F D0 12              1513 	pop	_bp
   1F11 22                 1514 	ret
                           1515 ;------------------------------------------------------------
                           1516 ;Allocation info for local variables in function 'cQueueSendFromISR'
                           1517 ;------------------------------------------------------------
                           1518 ;pvItemToQueue             Allocated to stack - offset -5
                           1519 ;cTaskPreviouslyWoken      Allocated to stack - offset -6
                           1520 ;pxQueue                   Allocated to stack - offset 1
                           1521 ;sloc0                     Allocated to stack - offset 4
                           1522 ;sloc1                     Allocated to stack - offset 5
                           1523 ;sloc2                     Allocated to stack - offset 8
                           1524 ;sloc3                     Allocated to stack - offset 11
                           1525 ;------------------------------------------------------------
                           1526 ;../../Source/queue.c:368: signed portCHAR cQueueSendFromISR( xQueueHandle pxQueue, const void *pvItemToQueue, signed portCHAR cTaskPreviouslyWoken )
                           1527 ;	-----------------------------------------
                           1528 ;	 function cQueueSendFromISR
                           1529 ;	-----------------------------------------
   1F12                    1530 _cQueueSendFromISR:
   1F12 C0 12              1531 	push	_bp
   1F14 85 81 12           1532 	mov	_bp,sp
                           1533 ;     genReceive
   1F17 C0 82              1534 	push	dpl
   1F19 C0 83              1535 	push	dph
   1F1B C0 F0              1536 	push	b
   1F1D E5 81              1537 	mov	a,sp
   1F1F 24 0C              1538 	add	a,#0x0c
   1F21 F5 81              1539 	mov	sp,a
                           1540 ;../../Source/queue.c:375: if( pxQueue->ucMessagesWaiting < pxQueue->ucLength )
                           1541 ;     genPlus
   1F23 E5 12              1542 	mov	a,_bp
   1F25 24 01              1543 	add	a,#0x01
   1F27 F8                 1544 	mov	r0,a
   1F28 74 38              1545 	mov	a,#0x38
   1F2A 26                 1546 	add	a,@r0
   1F2B FD                 1547 	mov	r5,a
   1F2C 74 00              1548 	mov	a,#0x00
   1F2E 08                 1549 	inc	r0
   1F2F 36                 1550 	addc	a,@r0
   1F30 FE                 1551 	mov	r6,a
   1F31 08                 1552 	inc	r0
   1F32 86 07              1553 	mov	ar7,@r0
                           1554 ;     genPointerGet
                           1555 ;     genGenPointerGet
   1F34 8D 82              1556 	mov	dpl,r5
   1F36 8E 83              1557 	mov	dph,r6
   1F38 8F F0              1558 	mov	b,r7
   1F3A E5 12              1559 	mov	a,_bp
   1F3C 24 04              1560 	add	a,#0x04
   1F3E F8                 1561 	mov	r0,a
   1F3F 12 AE 30           1562 	lcall	__gptrget
   1F42 F6                 1563 	mov	@r0,a
                           1564 ;     genPlus
   1F43 E5 12              1565 	mov	a,_bp
   1F45 24 01              1566 	add	a,#0x01
   1F47 F8                 1567 	mov	r0,a
   1F48 74 39              1568 	mov	a,#0x39
   1F4A 26                 1569 	add	a,@r0
   1F4B FB                 1570 	mov	r3,a
   1F4C 74 00              1571 	mov	a,#0x00
   1F4E 08                 1572 	inc	r0
   1F4F 36                 1573 	addc	a,@r0
   1F50 FC                 1574 	mov	r4,a
   1F51 08                 1575 	inc	r0
   1F52 86 02              1576 	mov	ar2,@r0
                           1577 ;     genPointerGet
                           1578 ;     genGenPointerGet
   1F54 8B 82              1579 	mov	dpl,r3
   1F56 8C 83              1580 	mov	dph,r4
   1F58 8A F0              1581 	mov	b,r2
   1F5A 12 AE 30           1582 	lcall	__gptrget
   1F5D FB                 1583 	mov	r3,a
                           1584 ;     genCmpLt
   1F5E E5 12              1585 	mov	a,_bp
   1F60 24 04              1586 	add	a,#0x04
   1F62 F8                 1587 	mov	r0,a
                           1588 ;     genCmp
   1F63 C3                 1589 	clr	c
   1F64 E6                 1590 	mov	a,@r0
   1F65 9B                 1591 	subb	a,r3
                           1592 ;     genIfxJump
   1F66 40 03              1593 	jc	00122$
   1F68 02 21 56           1594 	ljmp	00113$
   1F6B                    1595 00122$:
                           1596 ;../../Source/queue.c:377: prvCopyQueueData( pxQueue, pvItemToQueue );
                           1597 ;     genPlus
   1F6B E5 12              1598 	mov	a,_bp
   1F6D 24 01              1599 	add	a,#0x01
   1F6F F8                 1600 	mov	r0,a
   1F70 E5 12              1601 	mov	a,_bp
   1F72 24 05              1602 	add	a,#0x05
   1F74 F9                 1603 	mov	r1,a
   1F75 74 3A              1604 	mov	a,#0x3A
   1F77 26                 1605 	add	a,@r0
   1F78 F7                 1606 	mov	@r1,a
   1F79 74 00              1607 	mov	a,#0x00
   1F7B 08                 1608 	inc	r0
   1F7C 36                 1609 	addc	a,@r0
   1F7D 09                 1610 	inc	r1
   1F7E F7                 1611 	mov	@r1,a
   1F7F 08                 1612 	inc	r0
   1F80 09                 1613 	inc	r1
   1F81 E6                 1614 	mov	a,@r0
   1F82 F7                 1615 	mov	@r1,a
                           1616 ;     genPointerGet
                           1617 ;     genGenPointerGet
   1F83 E5 12              1618 	mov	a,_bp
   1F85 24 05              1619 	add	a,#0x05
   1F87 F8                 1620 	mov	r0,a
   1F88 86 82              1621 	mov	dpl,@r0
   1F8A 08                 1622 	inc	r0
   1F8B 86 83              1623 	mov	dph,@r0
   1F8D 08                 1624 	inc	r0
   1F8E 86 F0              1625 	mov	b,@r0
   1F90 12 AE 30           1626 	lcall	__gptrget
   1F93 FA                 1627 	mov	r2,a
                           1628 ;     genCast
   1F94 E5 12              1629 	mov	a,_bp
   1F96 24 0B              1630 	add	a,#0x0b
   1F98 F8                 1631 	mov	r0,a
   1F99 A6 02              1632 	mov	@r0,ar2
   1F9B 08                 1633 	inc	r0
   1F9C 76 00              1634 	mov	@r0,#0x00
                           1635 ;     genPlus
   1F9E E5 12              1636 	mov	a,_bp
   1FA0 24 01              1637 	add	a,#0x01
   1FA2 F8                 1638 	mov	r0,a
   1FA3 E5 12              1639 	mov	a,_bp
   1FA5 24 08              1640 	add	a,#0x08
   1FA7 F9                 1641 	mov	r1,a
   1FA8 74 06              1642 	mov	a,#0x06
   1FAA 26                 1643 	add	a,@r0
   1FAB F7                 1644 	mov	@r1,a
   1FAC 74 00              1645 	mov	a,#0x00
   1FAE 08                 1646 	inc	r0
   1FAF 36                 1647 	addc	a,@r0
   1FB0 09                 1648 	inc	r1
   1FB1 F7                 1649 	mov	@r1,a
   1FB2 08                 1650 	inc	r0
   1FB3 09                 1651 	inc	r1
   1FB4 E6                 1652 	mov	a,@r0
   1FB5 F7                 1653 	mov	@r1,a
                           1654 ;     genPointerGet
                           1655 ;     genGenPointerGet
   1FB6 E5 12              1656 	mov	a,_bp
   1FB8 24 08              1657 	add	a,#0x08
   1FBA F8                 1658 	mov	r0,a
   1FBB 86 82              1659 	mov	dpl,@r0
   1FBD 08                 1660 	inc	r0
   1FBE 86 83              1661 	mov	dph,@r0
   1FC0 08                 1662 	inc	r0
   1FC1 86 F0              1663 	mov	b,@r0
   1FC3 12 AE 30           1664 	lcall	__gptrget
   1FC6 FC                 1665 	mov	r4,a
   1FC7 A3                 1666 	inc	dptr
   1FC8 12 AE 30           1667 	lcall	__gptrget
   1FCB FA                 1668 	mov	r2,a
   1FCC A3                 1669 	inc	dptr
   1FCD 12 AE 30           1670 	lcall	__gptrget
   1FD0 FB                 1671 	mov	r3,a
                           1672 ;     genIpush
   1FD1 C0 05              1673 	push	ar5
   1FD3 C0 06              1674 	push	ar6
   1FD5 C0 07              1675 	push	ar7
   1FD7 E5 12              1676 	mov	a,_bp
   1FD9 24 0B              1677 	add	a,#0x0b
   1FDB F8                 1678 	mov	r0,a
   1FDC E6                 1679 	mov	a,@r0
   1FDD C0 E0              1680 	push	acc
   1FDF 08                 1681 	inc	r0
   1FE0 E6                 1682 	mov	a,@r0
   1FE1 C0 E0              1683 	push	acc
                           1684 ;     genIpush
   1FE3 E5 12              1685 	mov	a,_bp
   1FE5 24 FB              1686 	add	a,#0xfb
   1FE7 F8                 1687 	mov	r0,a
   1FE8 E6                 1688 	mov	a,@r0
   1FE9 C0 E0              1689 	push	acc
   1FEB 08                 1690 	inc	r0
   1FEC E6                 1691 	mov	a,@r0
   1FED C0 E0              1692 	push	acc
   1FEF 08                 1693 	inc	r0
   1FF0 E6                 1694 	mov	a,@r0
   1FF1 C0 E0              1695 	push	acc
                           1696 ;     genCall
   1FF3 8C 82              1697 	mov	dpl,r4
   1FF5 8A 83              1698 	mov	dph,r2
   1FF7 8B F0              1699 	mov	b,r3
   1FF9 12 AC 5D           1700 	lcall	_memcpy
   1FFC E5 81              1701 	mov	a,sp
   1FFE 24 FB              1702 	add	a,#0xfb
   2000 F5 81              1703 	mov	sp,a
   2002 D0 07              1704 	pop	ar7
   2004 D0 06              1705 	pop	ar6
   2006 D0 05              1706 	pop	ar5
                           1707 ;     genPointerGet
                           1708 ;     genGenPointerGet
   2008 8D 82              1709 	mov	dpl,r5
   200A 8E 83              1710 	mov	dph,r6
   200C 8F F0              1711 	mov	b,r7
   200E 12 AE 30           1712 	lcall	__gptrget
   2011 FA                 1713 	mov	r2,a
                           1714 ;     genPlus
                           1715 ;     genPlusIncr
   2012 0A                 1716 	inc	r2
                           1717 ;     genPointerSet
                           1718 ;     genGenPointerSet
   2013 8D 82              1719 	mov	dpl,r5
   2015 8E 83              1720 	mov	dph,r6
   2017 8F F0              1721 	mov	b,r7
   2019 EA                 1722 	mov	a,r2
   201A 12 A3 97           1723 	lcall	__gptrput
                           1724 ;     genPointerGet
                           1725 ;     genGenPointerGet
   201D E5 12              1726 	mov	a,_bp
   201F 24 08              1727 	add	a,#0x08
   2021 F8                 1728 	mov	r0,a
   2022 86 82              1729 	mov	dpl,@r0
   2024 08                 1730 	inc	r0
   2025 86 83              1731 	mov	dph,@r0
   2027 08                 1732 	inc	r0
   2028 86 F0              1733 	mov	b,@r0
   202A 12 AE 30           1734 	lcall	__gptrget
   202D FA                 1735 	mov	r2,a
   202E A3                 1736 	inc	dptr
   202F 12 AE 30           1737 	lcall	__gptrget
   2032 FB                 1738 	mov	r3,a
   2033 A3                 1739 	inc	dptr
   2034 12 AE 30           1740 	lcall	__gptrget
   2037 FC                 1741 	mov	r4,a
                           1742 ;     genPointerGet
                           1743 ;     genGenPointerGet
   2038 E5 12              1744 	mov	a,_bp
   203A 24 05              1745 	add	a,#0x05
   203C F8                 1746 	mov	r0,a
   203D 86 82              1747 	mov	dpl,@r0
   203F 08                 1748 	inc	r0
   2040 86 83              1749 	mov	dph,@r0
   2042 08                 1750 	inc	r0
   2043 86 F0              1751 	mov	b,@r0
   2045 12 AE 30           1752 	lcall	__gptrget
   2048 FD                 1753 	mov	r5,a
                           1754 ;     genPlus
   2049 E5 05              1755 	mov	a,ar5
   204B 25 02              1756 	add	a,ar2
   204D FA                 1757 	mov	r2,a
   204E 74 00              1758 	mov	a,#0x00
   2050 35 03              1759 	addc	a,ar3
   2052 FB                 1760 	mov	r3,a
                           1761 ;     genPointerSet
                           1762 ;     genGenPointerSet
   2053 E5 12              1763 	mov	a,_bp
   2055 24 08              1764 	add	a,#0x08
   2057 F8                 1765 	mov	r0,a
   2058 86 82              1766 	mov	dpl,@r0
   205A 08                 1767 	inc	r0
   205B 86 83              1768 	mov	dph,@r0
   205D 08                 1769 	inc	r0
   205E 86 F0              1770 	mov	b,@r0
   2060 EA                 1771 	mov	a,r2
   2061 12 A3 97           1772 	lcall	__gptrput
   2064 A3                 1773 	inc	dptr
   2065 EB                 1774 	mov	a,r3
   2066 12 A3 97           1775 	lcall	__gptrput
   2069 A3                 1776 	inc	dptr
   206A EC                 1777 	mov	a,r4
   206B 12 A3 97           1778 	lcall	__gptrput
                           1779 ;     genPlus
   206E E5 12              1780 	mov	a,_bp
   2070 24 01              1781 	add	a,#0x01
   2072 F8                 1782 	mov	r0,a
                           1783 ;     genPlusIncr
   2073 74 03              1784 	mov	a,#0x03
   2075 26                 1785 	add	a,@r0
   2076 FD                 1786 	mov	r5,a
   2077 74 00              1787 	mov	a,#0x00
   2079 08                 1788 	inc	r0
   207A 36                 1789 	addc	a,@r0
   207B FE                 1790 	mov	r6,a
   207C 08                 1791 	inc	r0
   207D 86 07              1792 	mov	ar7,@r0
                           1793 ;     genPointerGet
                           1794 ;     genGenPointerGet
   207F 8D 82              1795 	mov	dpl,r5
   2081 8E 83              1796 	mov	dph,r6
   2083 8F F0              1797 	mov	b,r7
   2085 12 AE 30           1798 	lcall	__gptrget
   2088 FD                 1799 	mov	r5,a
   2089 A3                 1800 	inc	dptr
   208A 12 AE 30           1801 	lcall	__gptrget
   208D FE                 1802 	mov	r6,a
   208E A3                 1803 	inc	dptr
   208F 12 AE 30           1804 	lcall	__gptrget
   2092 FF                 1805 	mov	r7,a
                           1806 ;     genCmpLt
                           1807 ;     genCmp
   2093 C3                 1808 	clr	c
   2094 EA                 1809 	mov	a,r2
   2095 9D                 1810 	subb	a,r5
   2096 EB                 1811 	mov	a,r3
   2097 9E                 1812 	subb	a,r6
   2098 EC                 1813 	mov	a,r4
   2099 64 80              1814 	xrl	a,#0x80
   209B 8F F0              1815 	mov	b,r7
   209D 63 F0 80           1816 	xrl	b,#0x80
   20A0 95 F0              1817 	subb	a,b
                           1818 ;     genIfxJump
   20A2 50 03              1819 	jnc	00123$
   20A4 02 20 DD           1820 	ljmp	00102$
   20A7                    1821 00123$:
                           1822 ;     genPointerGet
                           1823 ;     genGenPointerGet
   20A7 E5 12              1824 	mov	a,_bp
   20A9 24 01              1825 	add	a,#0x01
   20AB F8                 1826 	mov	r0,a
   20AC 86 82              1827 	mov	dpl,@r0
   20AE 08                 1828 	inc	r0
   20AF 86 83              1829 	mov	dph,@r0
   20B1 08                 1830 	inc	r0
   20B2 86 F0              1831 	mov	b,@r0
   20B4 12 AE 30           1832 	lcall	__gptrget
   20B7 FA                 1833 	mov	r2,a
   20B8 A3                 1834 	inc	dptr
   20B9 12 AE 30           1835 	lcall	__gptrget
   20BC FB                 1836 	mov	r3,a
   20BD A3                 1837 	inc	dptr
   20BE 12 AE 30           1838 	lcall	__gptrget
   20C1 FC                 1839 	mov	r4,a
                           1840 ;     genPointerSet
                           1841 ;     genGenPointerSet
   20C2 E5 12              1842 	mov	a,_bp
   20C4 24 08              1843 	add	a,#0x08
   20C6 F8                 1844 	mov	r0,a
   20C7 86 82              1845 	mov	dpl,@r0
   20C9 08                 1846 	inc	r0
   20CA 86 83              1847 	mov	dph,@r0
   20CC 08                 1848 	inc	r0
   20CD 86 F0              1849 	mov	b,@r0
   20CF EA                 1850 	mov	a,r2
   20D0 12 A3 97           1851 	lcall	__gptrput
   20D3 A3                 1852 	inc	dptr
   20D4 EB                 1853 	mov	a,r3
   20D5 12 A3 97           1854 	lcall	__gptrput
   20D8 A3                 1855 	inc	dptr
   20D9 EC                 1856 	mov	a,r4
   20DA 12 A3 97           1857 	lcall	__gptrput
   20DD                    1858 00102$:
                           1859 ;../../Source/queue.c:381: if( pxQueue->cTxLock == queueUNLOCKED )
                           1860 ;     genPlus
   20DD E5 12              1861 	mov	a,_bp
   20DF 24 01              1862 	add	a,#0x01
   20E1 F8                 1863 	mov	r0,a
   20E2 74 3C              1864 	mov	a,#0x3C
   20E4 26                 1865 	add	a,@r0
   20E5 FA                 1866 	mov	r2,a
   20E6 74 00              1867 	mov	a,#0x00
   20E8 08                 1868 	inc	r0
   20E9 36                 1869 	addc	a,@r0
   20EA FB                 1870 	mov	r3,a
   20EB 08                 1871 	inc	r0
   20EC 86 04              1872 	mov	ar4,@r0
                           1873 ;     genPointerGet
                           1874 ;     genGenPointerGet
   20EE 8A 82              1875 	mov	dpl,r2
   20F0 8B 83              1876 	mov	dph,r3
   20F2 8C F0              1877 	mov	b,r4
   20F4 12 AE 30           1878 	lcall	__gptrget
   20F7 FD                 1879 	mov	r5,a
                           1880 ;     genCmpEq
   20F8 BD FF 02           1881 	cjne	r5,#0xFF,00124$
   20FB 80 03              1882 	sjmp	00125$
   20FD                    1883 00124$:
   20FD 02 21 4B           1884 	ljmp	00110$
   2100                    1885 00125$:
                           1886 ;../../Source/queue.c:385: if( !cTaskPreviouslyWoken )		
                           1887 ;     genIfx
   2100 E5 12              1888 	mov	a,_bp
   2102 24 FA              1889 	add	a,#0xfa
   2104 F8                 1890 	mov	r0,a
   2105 E6                 1891 	mov	a,@r0
                           1892 ;     genIfxJump
   2106 60 03              1893 	jz	00126$
   2108 02 21 56           1894 	ljmp	00113$
   210B                    1895 00126$:
                           1896 ;../../Source/queue.c:387: if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) ) )
                           1897 ;     genPlus
   210B E5 12              1898 	mov	a,_bp
   210D 24 01              1899 	add	a,#0x01
   210F F8                 1900 	mov	r0,a
   2110 74 22              1901 	mov	a,#0x22
   2112 26                 1902 	add	a,@r0
   2113 FA                 1903 	mov	r2,a
   2114 74 00              1904 	mov	a,#0x00
   2116 08                 1905 	inc	r0
   2117 36                 1906 	addc	a,@r0
   2118 FB                 1907 	mov	r3,a
   2119 08                 1908 	inc	r0
   211A 86 04              1909 	mov	ar4,@r0
                           1910 ;     genPointerGet
                           1911 ;     genGenPointerGet
   211C 8A 82              1912 	mov	dpl,r2
   211E 8B 83              1913 	mov	dph,r3
   2120 8C F0              1914 	mov	b,r4
   2122 12 AE 30           1915 	lcall	__gptrget
   2125 FE                 1916 	mov	r6,a
   2126 A3                 1917 	inc	dptr
   2127 12 AE 30           1918 	lcall	__gptrget
   212A FF                 1919 	mov	r7,a
                           1920 ;     genCmpEq
   212B BE 00 06           1921 	cjne	r6,#0x00,00127$
   212E BF 00 03           1922 	cjne	r7,#0x00,00127$
   2131 02 21 56           1923 	ljmp	00113$
   2134                    1924 00127$:
                           1925 ;../../Source/queue.c:389: if( cTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToReceive ) ) != ( signed portCHAR ) pdFALSE )
                           1926 ;     genCall
   2134 8A 82              1927 	mov	dpl,r2
   2136 8B 83              1928 	mov	dph,r3
   2138 8C F0              1929 	mov	b,r4
   213A 12 0E 69           1930 	lcall	_cTaskRemoveFromEventList
   213D AE 82              1931 	mov	r6,dpl
                           1932 ;     genCmpEq
   213F BE 00 03           1933 	cjne	r6,#0x00,00128$
   2142 02 21 56           1934 	ljmp	00113$
   2145                    1935 00128$:
                           1936 ;../../Source/queue.c:393: return pdTRUE;
                           1937 ;     genRet
   2145 75 82 01           1938 	mov	dpl,#0x01
   2148 02 21 5D           1939 	ljmp	00114$
   214B                    1940 00110$:
                           1941 ;../../Source/queue.c:402: ++( pxQueue->cTxLock );
                           1942 ;     genPlus
                           1943 ;     genPlusIncr
   214B 0D                 1944 	inc	r5
                           1945 ;     genPointerSet
                           1946 ;     genGenPointerSet
   214C 8A 82              1947 	mov	dpl,r2
   214E 8B 83              1948 	mov	dph,r3
   2150 8C F0              1949 	mov	b,r4
   2152 ED                 1950 	mov	a,r5
   2153 12 A3 97           1951 	lcall	__gptrput
   2156                    1952 00113$:
                           1953 ;../../Source/queue.c:406: return cTaskPreviouslyWoken;
                           1954 ;     genRet
   2156 E5 12              1955 	mov	a,_bp
   2158 24 FA              1956 	add	a,#0xfa
   215A F8                 1957 	mov	r0,a
   215B 86 82              1958 	mov	dpl,@r0
   215D                    1959 00114$:
   215D 85 12 81           1960 	mov	sp,_bp
   2160 D0 12              1961 	pop	_bp
   2162 22                 1962 	ret
                           1963 ;------------------------------------------------------------
                           1964 ;Allocation info for local variables in function 'cQueueReceive'
                           1965 ;------------------------------------------------------------
                           1966 ;pcBuffer                  Allocated to stack - offset -5
                           1967 ;xTicksToWait              Allocated to stack - offset -7
                           1968 ;pxQueue                   Allocated to stack - offset 1
                           1969 ;cReturn                   Allocated to registers r2 
                           1970 ;sloc0                     Allocated to stack - offset 4
                           1971 ;sloc1                     Allocated to stack - offset 7
                           1972 ;sloc2                     Allocated to stack - offset 10
                           1973 ;sloc3                     Allocated to stack - offset 11
                           1974 ;------------------------------------------------------------
                           1975 ;../../Source/queue.c:410: signed portCHAR cQueueReceive( xQueueHandle pxQueue, void *pcBuffer, portTickType xTicksToWait )
                           1976 ;	-----------------------------------------
                           1977 ;	 function cQueueReceive
                           1978 ;	-----------------------------------------
   2163                    1979 _cQueueReceive:
   2163 C0 12              1980 	push	_bp
   2165 85 81 12           1981 	mov	_bp,sp
                           1982 ;     genReceive
   2168 C0 82              1983 	push	dpl
   216A C0 83              1984 	push	dph
   216C C0 F0              1985 	push	b
   216E E5 81              1986 	mov	a,sp
   2170 24 0B              1987 	add	a,#0x0b
   2172 F5 81              1988 	mov	sp,a
                           1989 ;../../Source/queue.c:418: vTaskSuspendAll();
                           1990 ;     genCall
   2174 12 06 94           1991 	lcall	_vTaskSuspendAll
                           1992 ;../../Source/queue.c:421: prvLockQueue( pxQueue );
                           1993 ;     genInline
   2177 C0 E0 C0 A8        1994 	 push ACC push IE 
                           1995 ;     genAssign
   217B C2 AF              1996 	clr	_EA
                           1997 ;     genPlus
   217D E5 12              1998 	mov	a,_bp
   217F 24 01              1999 	add	a,#0x01
   2181 F8                 2000 	mov	r0,a
   2182 74 3B              2001 	mov	a,#0x3B
   2184 26                 2002 	add	a,@r0
   2185 FD                 2003 	mov	r5,a
   2186 74 00              2004 	mov	a,#0x00
   2188 08                 2005 	inc	r0
   2189 36                 2006 	addc	a,@r0
   218A FE                 2007 	mov	r6,a
   218B 08                 2008 	inc	r0
   218C 86 07              2009 	mov	ar7,@r0
                           2010 ;     genPointerGet
                           2011 ;     genGenPointerGet
   218E 8D 82              2012 	mov	dpl,r5
   2190 8E 83              2013 	mov	dph,r6
   2192 8F F0              2014 	mov	b,r7
   2194 12 AE 30           2015 	lcall	__gptrget
   2197 FA                 2016 	mov	r2,a
                           2017 ;     genPlus
                           2018 ;     genPlusIncr
   2198 0A                 2019 	inc	r2
                           2020 ;     genPointerSet
                           2021 ;     genGenPointerSet
   2199 8D 82              2022 	mov	dpl,r5
   219B 8E 83              2023 	mov	dph,r6
   219D 8F F0              2024 	mov	b,r7
   219F EA                 2025 	mov	a,r2
   21A0 12 A3 97           2026 	lcall	__gptrput
                           2027 ;     genPlus
   21A3 E5 12              2028 	mov	a,_bp
   21A5 24 01              2029 	add	a,#0x01
   21A7 F8                 2030 	mov	r0,a
   21A8 74 3C              2031 	mov	a,#0x3C
   21AA 26                 2032 	add	a,@r0
   21AB FA                 2033 	mov	r2,a
   21AC 74 00              2034 	mov	a,#0x00
   21AE 08                 2035 	inc	r0
   21AF 36                 2036 	addc	a,@r0
   21B0 FB                 2037 	mov	r3,a
   21B1 08                 2038 	inc	r0
   21B2 86 04              2039 	mov	ar4,@r0
                           2040 ;     genPointerGet
                           2041 ;     genGenPointerGet
   21B4 8A 82              2042 	mov	dpl,r2
   21B6 8B 83              2043 	mov	dph,r3
   21B8 8C F0              2044 	mov	b,r4
   21BA 12 AE 30           2045 	lcall	__gptrget
   21BD FD                 2046 	mov	r5,a
                           2047 ;     genPlus
                           2048 ;     genPlusIncr
   21BE 0D                 2049 	inc	r5
                           2050 ;     genPointerSet
                           2051 ;     genGenPointerSet
   21BF 8A 82              2052 	mov	dpl,r2
   21C1 8B 83              2053 	mov	dph,r3
   21C3 8C F0              2054 	mov	b,r4
   21C5 ED                 2055 	mov	a,r5
   21C6 12 A3 97           2056 	lcall	__gptrput
                           2057 ;     genInline
   21C9 D0 E0              2058 	 pop ACC 
                           2059 ;     genAnd
   21CB 53 E0 80           2060 	anl	_ACC,#0x80
                           2061 ;     genOr
   21CE E5 E0              2062 	mov	a,_ACC
   21D0 42 A8              2063 	orl	_IE,a
                           2064 ;     genInline
   21D2 D0 E0              2065 	 pop ACC 
                           2066 ;../../Source/queue.c:424: if( prvIsQueueEmpty( pxQueue ) )
                           2067 ;     genCall
   21D4 E5 12              2068 	mov	a,_bp
   21D6 24 01              2069 	add	a,#0x01
   21D8 F8                 2070 	mov	r0,a
   21D9 86 82              2071 	mov	dpl,@r0
   21DB 08                 2072 	inc	r0
   21DC 86 83              2073 	mov	dph,@r0
   21DE 08                 2074 	inc	r0
   21DF 86 F0              2075 	mov	b,@r0
   21E1 12 28 C9           2076 	lcall	_prvIsQueueEmpty
   21E4 E5 82              2077 	mov	a,dpl
                           2078 ;     genIfx
                           2079 ;     genIfxJump
   21E6 70 03              2080 	jnz	00126$
   21E8 02 22 B0           2081 	ljmp	00106$
   21EB                    2082 00126$:
                           2083 ;../../Source/queue.c:428: if( xTicksToWait > ( portTickType ) 0 )
                           2084 ;     genIfx
   21EB E5 12              2085 	mov	a,_bp
   21ED 24 F9              2086 	add	a,#0xf9
   21EF F8                 2087 	mov	r0,a
   21F0 E6                 2088 	mov	a,@r0
   21F1 08                 2089 	inc	r0
   21F2 46                 2090 	orl	a,@r0
                           2091 ;     genIfxJump
   21F3 70 03              2092 	jnz	00127$
   21F5 02 22 B0           2093 	ljmp	00106$
   21F8                    2094 00127$:
                           2095 ;../../Source/queue.c:430: vTaskPlaceOnEventList( &( pxQueue->xTasksWaitingToReceive ), xTicksToWait );
                           2096 ;     genPlus
   21F8 E5 12              2097 	mov	a,_bp
   21FA 24 01              2098 	add	a,#0x01
   21FC F8                 2099 	mov	r0,a
   21FD 74 22              2100 	mov	a,#0x22
   21FF 26                 2101 	add	a,@r0
   2200 FA                 2102 	mov	r2,a
   2201 74 00              2103 	mov	a,#0x00
   2203 08                 2104 	inc	r0
   2204 36                 2105 	addc	a,@r0
   2205 FB                 2106 	mov	r3,a
   2206 08                 2107 	inc	r0
   2207 86 04              2108 	mov	ar4,@r0
                           2109 ;     genIpush
   2209 E5 12              2110 	mov	a,_bp
   220B 24 F9              2111 	add	a,#0xf9
   220D F8                 2112 	mov	r0,a
   220E E6                 2113 	mov	a,@r0
   220F C0 E0              2114 	push	acc
   2211 08                 2115 	inc	r0
   2212 E6                 2116 	mov	a,@r0
   2213 C0 E0              2117 	push	acc
                           2118 ;     genCall
   2215 8A 82              2119 	mov	dpl,r2
   2217 8B 83              2120 	mov	dph,r3
   2219 8C F0              2121 	mov	b,r4
   221B 12 0D 4F           2122 	lcall	_vTaskPlaceOnEventList
   221E 15 81              2123 	dec	sp
   2220 15 81              2124 	dec	sp
                           2125 ;../../Source/queue.c:431: taskENTER_CRITICAL();
                           2126 ;     genInline
   2222 C0 E0 C0 A8        2127 	 push ACC push IE 
                           2128 ;     genAssign
   2226 C2 AF              2129 	clr	_EA
                           2130 ;../../Source/queue.c:433: prvUnlockQueue( pxQueue );
                           2131 ;     genCall
   2228 E5 12              2132 	mov	a,_bp
   222A 24 01              2133 	add	a,#0x01
   222C F8                 2134 	mov	r0,a
   222D 86 82              2135 	mov	dpl,@r0
   222F 08                 2136 	inc	r0
   2230 86 83              2137 	mov	dph,@r0
   2232 08                 2138 	inc	r0
   2233 86 F0              2139 	mov	b,@r0
   2235 12 27 80           2140 	lcall	_prvUnlockQueue
                           2141 ;../../Source/queue.c:434: if( !cTaskResumeAll() )
                           2142 ;     genCall
   2238 12 06 B7           2143 	lcall	_cTaskResumeAll
   223B E5 82              2144 	mov	a,dpl
                           2145 ;     genIfx
                           2146 ;     genIfxJump
   223D 60 03              2147 	jz	00128$
   223F 02 22 45           2148 	ljmp	00102$
   2242                    2149 00128$:
                           2150 ;../../Source/queue.c:436: taskYIELD();
                           2151 ;     genCall
   2242 12 17 01           2152 	lcall	_vPortYield
   2245                    2153 00102$:
                           2154 ;../../Source/queue.c:439: vTaskSuspendAll();
                           2155 ;     genCall
   2245 12 06 94           2156 	lcall	_vTaskSuspendAll
                           2157 ;../../Source/queue.c:440: prvLockQueue( pxQueue );
                           2158 ;     genInline
   2248 C0 E0 C0 A8        2159 	 push ACC push IE 
                           2160 ;     genAssign
   224C C2 AF              2161 	clr	_EA
                           2162 ;     genPlus
   224E E5 12              2163 	mov	a,_bp
   2250 24 01              2164 	add	a,#0x01
   2252 F8                 2165 	mov	r0,a
   2253 74 3B              2166 	mov	a,#0x3B
   2255 26                 2167 	add	a,@r0
   2256 FA                 2168 	mov	r2,a
   2257 74 00              2169 	mov	a,#0x00
   2259 08                 2170 	inc	r0
   225A 36                 2171 	addc	a,@r0
   225B FB                 2172 	mov	r3,a
   225C 08                 2173 	inc	r0
   225D 86 04              2174 	mov	ar4,@r0
                           2175 ;     genPointerGet
                           2176 ;     genGenPointerGet
   225F 8A 82              2177 	mov	dpl,r2
   2261 8B 83              2178 	mov	dph,r3
   2263 8C F0              2179 	mov	b,r4
   2265 12 AE 30           2180 	lcall	__gptrget
   2268 FD                 2181 	mov	r5,a
                           2182 ;     genPlus
                           2183 ;     genPlusIncr
   2269 0D                 2184 	inc	r5
                           2185 ;     genPointerSet
                           2186 ;     genGenPointerSet
   226A 8A 82              2187 	mov	dpl,r2
   226C 8B 83              2188 	mov	dph,r3
   226E 8C F0              2189 	mov	b,r4
   2270 ED                 2190 	mov	a,r5
   2271 12 A3 97           2191 	lcall	__gptrput
                           2192 ;     genPlus
   2274 E5 12              2193 	mov	a,_bp
   2276 24 01              2194 	add	a,#0x01
   2278 F8                 2195 	mov	r0,a
   2279 74 3C              2196 	mov	a,#0x3C
   227B 26                 2197 	add	a,@r0
   227C FA                 2198 	mov	r2,a
   227D 74 00              2199 	mov	a,#0x00
   227F 08                 2200 	inc	r0
   2280 36                 2201 	addc	a,@r0
   2281 FB                 2202 	mov	r3,a
   2282 08                 2203 	inc	r0
   2283 86 04              2204 	mov	ar4,@r0
                           2205 ;     genPointerGet
                           2206 ;     genGenPointerGet
   2285 8A 82              2207 	mov	dpl,r2
   2287 8B 83              2208 	mov	dph,r3
   2289 8C F0              2209 	mov	b,r4
   228B 12 AE 30           2210 	lcall	__gptrget
   228E FD                 2211 	mov	r5,a
                           2212 ;     genPlus
                           2213 ;     genPlusIncr
   228F 0D                 2214 	inc	r5
                           2215 ;     genPointerSet
                           2216 ;     genGenPointerSet
   2290 8A 82              2217 	mov	dpl,r2
   2292 8B 83              2218 	mov	dph,r3
   2294 8C F0              2219 	mov	b,r4
   2296 ED                 2220 	mov	a,r5
   2297 12 A3 97           2221 	lcall	__gptrput
                           2222 ;     genInline
   229A D0 E0              2223 	 pop ACC 
                           2224 ;     genAnd
   229C 53 E0 80           2225 	anl	_ACC,#0x80
                           2226 ;     genOr
   229F E5 E0              2227 	mov	a,_ACC
   22A1 42 A8              2228 	orl	_IE,a
                           2229 ;     genInline
   22A3 D0 E0              2230 	 pop ACC 
                           2231 ;../../Source/queue.c:442: taskEXIT_CRITICAL();
                           2232 ;     genInline
   22A5 D0 E0              2233 	 pop ACC 
                           2234 ;     genAnd
   22A7 53 E0 80           2235 	anl	_ACC,#0x80
                           2236 ;     genOr
   22AA E5 E0              2237 	mov	a,_ACC
   22AC 42 A8              2238 	orl	_IE,a
                           2239 ;     genInline
   22AE D0 E0              2240 	 pop ACC 
   22B0                    2241 00106$:
                           2242 ;../../Source/queue.c:446: taskENTER_CRITICAL();
                           2243 ;     genInline
   22B0 C0 E0 C0 A8        2244 	 push ACC push IE 
                           2245 ;     genAssign
   22B4 C2 AF              2246 	clr	_EA
                           2247 ;../../Source/queue.c:448: if( pxQueue->ucMessagesWaiting > ( unsigned portCHAR ) 0 )
                           2248 ;     genPlus
   22B6 E5 12              2249 	mov	a,_bp
   22B8 24 01              2250 	add	a,#0x01
   22BA F8                 2251 	mov	r0,a
   22BB 74 38              2252 	mov	a,#0x38
   22BD 26                 2253 	add	a,@r0
   22BE FA                 2254 	mov	r2,a
   22BF 74 00              2255 	mov	a,#0x00
   22C1 08                 2256 	inc	r0
   22C2 36                 2257 	addc	a,@r0
   22C3 FB                 2258 	mov	r3,a
   22C4 08                 2259 	inc	r0
   22C5 86 04              2260 	mov	ar4,@r0
                           2261 ;     genPointerGet
                           2262 ;     genGenPointerGet
   22C7 8A 82              2263 	mov	dpl,r2
   22C9 8B 83              2264 	mov	dph,r3
   22CB 8C F0              2265 	mov	b,r4
   22CD E5 12              2266 	mov	a,_bp
   22CF 24 0B              2267 	add	a,#0x0b
   22D1 F8                 2268 	mov	r0,a
   22D2 12 AE 30           2269 	lcall	__gptrget
   22D5 F6                 2270 	mov	@r0,a
                           2271 ;     genCmpGt
   22D6 E5 12              2272 	mov	a,_bp
   22D8 24 0B              2273 	add	a,#0x0b
   22DA F8                 2274 	mov	r0,a
                           2275 ;     genCmp
   22DB C3                 2276 	clr	c
   22DC 74 00              2277 	mov	a,#0x00
   22DE 96                 2278 	subb	a,@r0
                           2279 ;     genIfxJump
   22DF 40 03              2280 	jc	00129$
   22E1 02 24 6B           2281 	ljmp	00110$
   22E4                    2282 00129$:
                           2283 ;../../Source/queue.c:450: pxQueue->pcReadFrom += pxQueue->ucItemSize;
                           2284 ;     genIpush
                           2285 ;     genPlus
   22E4 E5 12              2286 	mov	a,_bp
   22E6 24 01              2287 	add	a,#0x01
   22E8 F8                 2288 	mov	r0,a
   22E9 E5 12              2289 	mov	a,_bp
   22EB 24 04              2290 	add	a,#0x04
   22ED F9                 2291 	mov	r1,a
   22EE 74 09              2292 	mov	a,#0x09
   22F0 26                 2293 	add	a,@r0
   22F1 F7                 2294 	mov	@r1,a
   22F2 74 00              2295 	mov	a,#0x00
   22F4 08                 2296 	inc	r0
   22F5 36                 2297 	addc	a,@r0
   22F6 09                 2298 	inc	r1
   22F7 F7                 2299 	mov	@r1,a
   22F8 08                 2300 	inc	r0
   22F9 09                 2301 	inc	r1
   22FA E6                 2302 	mov	a,@r0
   22FB F7                 2303 	mov	@r1,a
                           2304 ;     genPointerGet
                           2305 ;     genGenPointerGet
   22FC E5 12              2306 	mov	a,_bp
   22FE 24 04              2307 	add	a,#0x04
   2300 F8                 2308 	mov	r0,a
   2301 86 82              2309 	mov	dpl,@r0
   2303 08                 2310 	inc	r0
   2304 86 83              2311 	mov	dph,@r0
   2306 08                 2312 	inc	r0
   2307 86 F0              2313 	mov	b,@r0
   2309 E5 12              2314 	mov	a,_bp
   230B 24 07              2315 	add	a,#0x07
   230D F9                 2316 	mov	r1,a
   230E 12 AE 30           2317 	lcall	__gptrget
   2311 F7                 2318 	mov	@r1,a
   2312 A3                 2319 	inc	dptr
   2313 12 AE 30           2320 	lcall	__gptrget
   2316 09                 2321 	inc	r1
   2317 F7                 2322 	mov	@r1,a
   2318 A3                 2323 	inc	dptr
   2319 12 AE 30           2324 	lcall	__gptrget
   231C 09                 2325 	inc	r1
   231D F7                 2326 	mov	@r1,a
                           2327 ;     genPlus
   231E E5 12              2328 	mov	a,_bp
   2320 24 01              2329 	add	a,#0x01
   2322 F8                 2330 	mov	r0,a
   2323 74 3A              2331 	mov	a,#0x3A
   2325 26                 2332 	add	a,@r0
   2326 FD                 2333 	mov	r5,a
   2327 74 00              2334 	mov	a,#0x00
   2329 08                 2335 	inc	r0
   232A 36                 2336 	addc	a,@r0
   232B FE                 2337 	mov	r6,a
   232C 08                 2338 	inc	r0
   232D 86 07              2339 	mov	ar7,@r0
                           2340 ;     genPointerGet
                           2341 ;     genGenPointerGet
   232F 8D 82              2342 	mov	dpl,r5
   2331 8E 83              2343 	mov	dph,r6
   2333 8F F0              2344 	mov	b,r7
   2335 E5 12              2345 	mov	a,_bp
   2337 24 0A              2346 	add	a,#0x0a
   2339 F8                 2347 	mov	r0,a
   233A 12 AE 30           2348 	lcall	__gptrget
   233D F6                 2349 	mov	@r0,a
                           2350 ;     genPlus
   233E E5 12              2351 	mov	a,_bp
   2340 24 07              2352 	add	a,#0x07
   2342 F8                 2353 	mov	r0,a
   2343 E5 12              2354 	mov	a,_bp
   2345 24 0A              2355 	add	a,#0x0a
   2347 F9                 2356 	mov	r1,a
   2348 E7                 2357 	mov	a,@r1
   2349 26                 2358 	add	a,@r0
   234A F6                 2359 	mov	@r0,a
   234B 74 00              2360 	mov	a,#0x00
   234D 08                 2361 	inc	r0
   234E 36                 2362 	addc	a,@r0
   234F F6                 2363 	mov	@r0,a
                           2364 ;     genPointerSet
                           2365 ;     genGenPointerSet
   2350 E5 12              2366 	mov	a,_bp
   2352 24 04              2367 	add	a,#0x04
   2354 F8                 2368 	mov	r0,a
   2355 86 82              2369 	mov	dpl,@r0
   2357 08                 2370 	inc	r0
   2358 86 83              2371 	mov	dph,@r0
   235A 08                 2372 	inc	r0
   235B 86 F0              2373 	mov	b,@r0
   235D E5 12              2374 	mov	a,_bp
   235F 24 07              2375 	add	a,#0x07
   2361 F9                 2376 	mov	r1,a
   2362 E7                 2377 	mov	a,@r1
   2363 12 A3 97           2378 	lcall	__gptrput
   2366 A3                 2379 	inc	dptr
   2367 09                 2380 	inc	r1
   2368 E7                 2381 	mov	a,@r1
   2369 12 A3 97           2382 	lcall	__gptrput
   236C A3                 2383 	inc	dptr
   236D 09                 2384 	inc	r1
   236E E7                 2385 	mov	a,@r1
   236F 12 A3 97           2386 	lcall	__gptrput
                           2387 ;../../Source/queue.c:451: if( pxQueue->pcReadFrom >= pxQueue->pcTail )
                           2388 ;     genPlus
   2372 E5 12              2389 	mov	a,_bp
   2374 24 01              2390 	add	a,#0x01
   2376 F8                 2391 	mov	r0,a
                           2392 ;     genPlusIncr
   2377 74 03              2393 	mov	a,#0x03
   2379 26                 2394 	add	a,@r0
   237A FD                 2395 	mov	r5,a
   237B 74 00              2396 	mov	a,#0x00
   237D 08                 2397 	inc	r0
   237E 36                 2398 	addc	a,@r0
   237F FE                 2399 	mov	r6,a
   2380 08                 2400 	inc	r0
   2381 86 07              2401 	mov	ar7,@r0
                           2402 ;     genPointerGet
                           2403 ;     genGenPointerGet
   2383 8D 82              2404 	mov	dpl,r5
   2385 8E 83              2405 	mov	dph,r6
   2387 8F F0              2406 	mov	b,r7
   2389 12 AE 30           2407 	lcall	__gptrget
   238C FD                 2408 	mov	r5,a
   238D A3                 2409 	inc	dptr
   238E 12 AE 30           2410 	lcall	__gptrget
   2391 FE                 2411 	mov	r6,a
   2392 A3                 2412 	inc	dptr
   2393 12 AE 30           2413 	lcall	__gptrget
   2396 FF                 2414 	mov	r7,a
                           2415 ;     genCmpLt
   2397 E5 12              2416 	mov	a,_bp
   2399 24 07              2417 	add	a,#0x07
   239B F8                 2418 	mov	r0,a
                           2419 ;     genCmp
   239C C3                 2420 	clr	c
   239D E6                 2421 	mov	a,@r0
   239E 9D                 2422 	subb	a,r5
   239F 08                 2423 	inc	r0
   23A0 E6                 2424 	mov	a,@r0
   23A1 9E                 2425 	subb	a,r6
   23A2 08                 2426 	inc	r0
   23A3 E6                 2427 	mov	a,@r0
   23A4 64 80              2428 	xrl	a,#0x80
   23A6 8F F0              2429 	mov	b,r7
   23A8 63 F0 80           2430 	xrl	b,#0x80
   23AB 95 F0              2431 	subb	a,b
   23AD E4                 2432 	clr	a
   23AE 33                 2433 	rlc	a
                           2434 ;     genIpop
                           2435 ;     genIfx
                           2436 ;     genIfxJump
   23AF 60 03              2437 	jz	00130$
   23B1 02 23 EA           2438 	ljmp	00108$
   23B4                    2439 00130$:
                           2440 ;../../Source/queue.c:453: pxQueue->pcReadFrom = pxQueue->pcHead;
                           2441 ;     genPointerGet
                           2442 ;     genGenPointerGet
   23B4 E5 12              2443 	mov	a,_bp
   23B6 24 01              2444 	add	a,#0x01
   23B8 F8                 2445 	mov	r0,a
   23B9 86 82              2446 	mov	dpl,@r0
   23BB 08                 2447 	inc	r0
   23BC 86 83              2448 	mov	dph,@r0
   23BE 08                 2449 	inc	r0
   23BF 86 F0              2450 	mov	b,@r0
   23C1 12 AE 30           2451 	lcall	__gptrget
   23C4 FE                 2452 	mov	r6,a
   23C5 A3                 2453 	inc	dptr
   23C6 12 AE 30           2454 	lcall	__gptrget
   23C9 FF                 2455 	mov	r7,a
   23CA A3                 2456 	inc	dptr
   23CB 12 AE 30           2457 	lcall	__gptrget
   23CE FD                 2458 	mov	r5,a
                           2459 ;     genPointerSet
                           2460 ;     genGenPointerSet
   23CF E5 12              2461 	mov	a,_bp
   23D1 24 04              2462 	add	a,#0x04
   23D3 F8                 2463 	mov	r0,a
   23D4 86 82              2464 	mov	dpl,@r0
   23D6 08                 2465 	inc	r0
   23D7 86 83              2466 	mov	dph,@r0
   23D9 08                 2467 	inc	r0
   23DA 86 F0              2468 	mov	b,@r0
   23DC EE                 2469 	mov	a,r6
   23DD 12 A3 97           2470 	lcall	__gptrput
   23E0 A3                 2471 	inc	dptr
   23E1 EF                 2472 	mov	a,r7
   23E2 12 A3 97           2473 	lcall	__gptrput
   23E5 A3                 2474 	inc	dptr
   23E6 ED                 2475 	mov	a,r5
   23E7 12 A3 97           2476 	lcall	__gptrput
   23EA                    2477 00108$:
                           2478 ;../../Source/queue.c:455: --( pxQueue->ucMessagesWaiting );
                           2479 ;     genMinus
   23EA E5 12              2480 	mov	a,_bp
   23EC 24 0B              2481 	add	a,#0x0b
   23EE F8                 2482 	mov	r0,a
                           2483 ;     genMinusDec
   23EF E6                 2484 	mov	a,@r0
   23F0 14                 2485 	dec	a
   23F1 FD                 2486 	mov	r5,a
                           2487 ;     genPointerSet
                           2488 ;     genGenPointerSet
   23F2 8A 82              2489 	mov	dpl,r2
   23F4 8B 83              2490 	mov	dph,r3
   23F6 8C F0              2491 	mov	b,r4
   23F8 ED                 2492 	mov	a,r5
   23F9 12 A3 97           2493 	lcall	__gptrput
                           2494 ;../../Source/queue.c:456: memcpy( ( void * ) pcBuffer, ( void * ) pxQueue->pcReadFrom, ( unsigned ) pxQueue->ucItemSize );
                           2495 ;     genCast
   23FC E5 12              2496 	mov	a,_bp
   23FE 24 0A              2497 	add	a,#0x0a
   2400 F8                 2498 	mov	r0,a
   2401 86 02              2499 	mov	ar2,@r0
   2403 7B 00              2500 	mov	r3,#0x00
                           2501 ;     genPointerGet
                           2502 ;     genGenPointerGet
   2405 E5 12              2503 	mov	a,_bp
   2407 24 04              2504 	add	a,#0x04
   2409 F8                 2505 	mov	r0,a
   240A 86 82              2506 	mov	dpl,@r0
   240C 08                 2507 	inc	r0
   240D 86 83              2508 	mov	dph,@r0
   240F 08                 2509 	inc	r0
   2410 86 F0              2510 	mov	b,@r0
   2412 12 AE 30           2511 	lcall	__gptrget
   2415 FC                 2512 	mov	r4,a
   2416 A3                 2513 	inc	dptr
   2417 12 AE 30           2514 	lcall	__gptrget
   241A FD                 2515 	mov	r5,a
   241B A3                 2516 	inc	dptr
   241C 12 AE 30           2517 	lcall	__gptrget
   241F FE                 2518 	mov	r6,a
                           2519 ;     genIpush
   2420 C0 02              2520 	push	ar2
   2422 C0 03              2521 	push	ar3
                           2522 ;     genIpush
   2424 C0 04              2523 	push	ar4
   2426 C0 05              2524 	push	ar5
   2428 C0 06              2525 	push	ar6
                           2526 ;     genCall
   242A E5 12              2527 	mov	a,_bp
   242C 24 FB              2528 	add	a,#0xfb
   242E F8                 2529 	mov	r0,a
   242F 86 82              2530 	mov	dpl,@r0
   2431 08                 2531 	inc	r0
   2432 86 83              2532 	mov	dph,@r0
   2434 08                 2533 	inc	r0
   2435 86 F0              2534 	mov	b,@r0
   2437 12 AC 5D           2535 	lcall	_memcpy
   243A E5 81              2536 	mov	a,sp
   243C 24 FB              2537 	add	a,#0xfb
   243E F5 81              2538 	mov	sp,a
                           2539 ;../../Source/queue.c:460: ++( pxQueue->cRxLock );
                           2540 ;     genPlus
   2440 E5 12              2541 	mov	a,_bp
   2442 24 01              2542 	add	a,#0x01
   2444 F8                 2543 	mov	r0,a
   2445 74 3B              2544 	mov	a,#0x3B
   2447 26                 2545 	add	a,@r0
   2448 FA                 2546 	mov	r2,a
   2449 74 00              2547 	mov	a,#0x00
   244B 08                 2548 	inc	r0
   244C 36                 2549 	addc	a,@r0
   244D FB                 2550 	mov	r3,a
   244E 08                 2551 	inc	r0
   244F 86 04              2552 	mov	ar4,@r0
                           2553 ;     genPointerGet
                           2554 ;     genGenPointerGet
   2451 8A 82              2555 	mov	dpl,r2
   2453 8B 83              2556 	mov	dph,r3
   2455 8C F0              2557 	mov	b,r4
   2457 12 AE 30           2558 	lcall	__gptrget
   245A FD                 2559 	mov	r5,a
                           2560 ;     genPlus
                           2561 ;     genPlusIncr
   245B 0D                 2562 	inc	r5
                           2563 ;     genPointerSet
                           2564 ;     genGenPointerSet
   245C 8A 82              2565 	mov	dpl,r2
   245E 8B 83              2566 	mov	dph,r3
   2460 8C F0              2567 	mov	b,r4
   2462 ED                 2568 	mov	a,r5
   2463 12 A3 97           2569 	lcall	__gptrput
                           2570 ;../../Source/queue.c:461: cReturn = ( signed portCHAR ) pdPASS;
                           2571 ;     genAssign
   2466 7A 01              2572 	mov	r2,#0x01
   2468 02 24 6D           2573 	ljmp	00111$
   246B                    2574 00110$:
                           2575 ;../../Source/queue.c:465: cReturn = ( signed portCHAR ) pdFAIL;
                           2576 ;     genAssign
   246B 7A 00              2577 	mov	r2,#0x00
   246D                    2578 00111$:
                           2579 ;../../Source/queue.c:468: taskEXIT_CRITICAL();
                           2580 ;     genInline
   246D D0 E0              2581 	 pop ACC 
                           2582 ;     genAnd
   246F 53 E0 80           2583 	anl	_ACC,#0x80
                           2584 ;     genOr
   2472 E5 E0              2585 	mov	a,_ACC
   2474 42 A8              2586 	orl	_IE,a
                           2587 ;     genInline
   2476 D0 E0              2588 	 pop ACC 
                           2589 ;../../Source/queue.c:471: if( prvUnlockQueue( pxQueue ) )
                           2590 ;     genCall
   2478 E5 12              2591 	mov	a,_bp
   247A 24 01              2592 	add	a,#0x01
   247C F8                 2593 	mov	r0,a
   247D 86 82              2594 	mov	dpl,@r0
   247F 08                 2595 	inc	r0
   2480 86 83              2596 	mov	dph,@r0
   2482 08                 2597 	inc	r0
   2483 86 F0              2598 	mov	b,@r0
   2485 C0 02              2599 	push	ar2
   2487 12 27 80           2600 	lcall	_prvUnlockQueue
   248A E5 82              2601 	mov	a,dpl
   248C D0 02              2602 	pop	ar2
                           2603 ;     genIfx
                           2604 ;     genIfxJump
   248E 70 03              2605 	jnz	00131$
   2490 02 24 A7           2606 	ljmp	00115$
   2493                    2607 00131$:
                           2608 ;../../Source/queue.c:473: if( !cTaskResumeAll() )
                           2609 ;     genCall
   2493 C0 02              2610 	push	ar2
   2495 12 06 B7           2611 	lcall	_cTaskResumeAll
   2498 E5 82              2612 	mov	a,dpl
   249A D0 02              2613 	pop	ar2
                           2614 ;     genIfx
                           2615 ;     genIfxJump
   249C 60 03              2616 	jz	00132$
   249E 02 24 AE           2617 	ljmp	00116$
   24A1                    2618 00132$:
                           2619 ;../../Source/queue.c:475: taskYIELD();
                           2620 ;     genCall
   24A1 12 17 01           2621 	lcall	_vPortYield
   24A4 02 24 AE           2622 	ljmp	00116$
   24A7                    2623 00115$:
                           2624 ;../../Source/queue.c:480: cTaskResumeAll();
                           2625 ;     genCall
   24A7 C0 02              2626 	push	ar2
   24A9 12 06 B7           2627 	lcall	_cTaskResumeAll
   24AC D0 02              2628 	pop	ar2
   24AE                    2629 00116$:
                           2630 ;../../Source/queue.c:483: return cReturn;
                           2631 ;     genRet
   24AE 8A 82              2632 	mov	dpl,r2
   24B0                    2633 00117$:
   24B0 85 12 81           2634 	mov	sp,_bp
   24B3 D0 12              2635 	pop	_bp
   24B5 22                 2636 	ret
                           2637 ;------------------------------------------------------------
                           2638 ;Allocation info for local variables in function 'cQueueReceiveFromISR'
                           2639 ;------------------------------------------------------------
                           2640 ;pcBuffer                  Allocated to stack - offset -5
                           2641 ;pcTaskWoken               Allocated to stack - offset -8
                           2642 ;pxQueue                   Allocated to stack - offset 1
                           2643 ;cReturn                   Allocated to registers r2 
                           2644 ;sloc0                     Allocated to stack - offset 4
                           2645 ;sloc1                     Allocated to stack - offset 5
                           2646 ;sloc2                     Allocated to stack - offset 8
                           2647 ;sloc3                     Allocated to stack - offset 9
                           2648 ;------------------------------------------------------------
                           2649 ;../../Source/queue.c:487: signed portCHAR cQueueReceiveFromISR( xQueueHandle pxQueue, void *pcBuffer, signed portCHAR *pcTaskWoken )
                           2650 ;	-----------------------------------------
                           2651 ;	 function cQueueReceiveFromISR
                           2652 ;	-----------------------------------------
   24B6                    2653 _cQueueReceiveFromISR:
   24B6 C0 12              2654 	push	_bp
   24B8 85 81 12           2655 	mov	_bp,sp
                           2656 ;     genReceive
   24BB C0 82              2657 	push	dpl
   24BD C0 83              2658 	push	dph
   24BF C0 F0              2659 	push	b
   24C1 E5 81              2660 	mov	a,sp
   24C3 24 0B              2661 	add	a,#0x0b
   24C5 F5 81              2662 	mov	sp,a
                           2663 ;../../Source/queue.c:492: if( pxQueue->ucMessagesWaiting > ( unsigned portCHAR ) 0 )
                           2664 ;     genPlus
   24C7 E5 12              2665 	mov	a,_bp
   24C9 24 01              2666 	add	a,#0x01
   24CB F8                 2667 	mov	r0,a
   24CC 74 38              2668 	mov	a,#0x38
   24CE 26                 2669 	add	a,@r0
   24CF FD                 2670 	mov	r5,a
   24D0 74 00              2671 	mov	a,#0x00
   24D2 08                 2672 	inc	r0
   24D3 36                 2673 	addc	a,@r0
   24D4 FE                 2674 	mov	r6,a
   24D5 08                 2675 	inc	r0
   24D6 86 07              2676 	mov	ar7,@r0
                           2677 ;     genPointerGet
                           2678 ;     genGenPointerGet
   24D8 8D 82              2679 	mov	dpl,r5
   24DA 8E 83              2680 	mov	dph,r6
   24DC 8F F0              2681 	mov	b,r7
   24DE E5 12              2682 	mov	a,_bp
   24E0 24 04              2683 	add	a,#0x04
   24E2 F8                 2684 	mov	r0,a
   24E3 12 AE 30           2685 	lcall	__gptrget
   24E6 F6                 2686 	mov	@r0,a
                           2687 ;     genCmpGt
   24E7 E5 12              2688 	mov	a,_bp
   24E9 24 04              2689 	add	a,#0x04
   24EB F8                 2690 	mov	r0,a
                           2691 ;     genCmp
   24EC C3                 2692 	clr	c
   24ED 74 00              2693 	mov	a,#0x00
   24EF 96                 2694 	subb	a,@r0
                           2695 ;     genIfxJump
   24F0 40 03              2696 	jc	00123$
   24F2 02 26 FB           2697 	ljmp	00113$
   24F5                    2698 00123$:
                           2699 ;../../Source/queue.c:495: pxQueue->pcReadFrom += pxQueue->ucItemSize;
                           2700 ;     genIpush
   24F5 C0 05              2701 	push	ar5
   24F7 C0 06              2702 	push	ar6
   24F9 C0 07              2703 	push	ar7
                           2704 ;     genPlus
   24FB E5 12              2705 	mov	a,_bp
   24FD 24 01              2706 	add	a,#0x01
   24FF F8                 2707 	mov	r0,a
   2500 E5 12              2708 	mov	a,_bp
   2502 24 05              2709 	add	a,#0x05
   2504 F9                 2710 	mov	r1,a
   2505 74 09              2711 	mov	a,#0x09
   2507 26                 2712 	add	a,@r0
   2508 F7                 2713 	mov	@r1,a
   2509 74 00              2714 	mov	a,#0x00
   250B 08                 2715 	inc	r0
   250C 36                 2716 	addc	a,@r0
   250D 09                 2717 	inc	r1
   250E F7                 2718 	mov	@r1,a
   250F 08                 2719 	inc	r0
   2510 09                 2720 	inc	r1
   2511 E6                 2721 	mov	a,@r0
   2512 F7                 2722 	mov	@r1,a
                           2723 ;     genPointerGet
                           2724 ;     genGenPointerGet
   2513 E5 12              2725 	mov	a,_bp
   2515 24 05              2726 	add	a,#0x05
   2517 F8                 2727 	mov	r0,a
   2518 86 82              2728 	mov	dpl,@r0
   251A 08                 2729 	inc	r0
   251B 86 83              2730 	mov	dph,@r0
   251D 08                 2731 	inc	r0
   251E 86 F0              2732 	mov	b,@r0
   2520 12 AE 30           2733 	lcall	__gptrget
   2523 FD                 2734 	mov	r5,a
   2524 A3                 2735 	inc	dptr
   2525 12 AE 30           2736 	lcall	__gptrget
   2528 FE                 2737 	mov	r6,a
   2529 A3                 2738 	inc	dptr
   252A 12 AE 30           2739 	lcall	__gptrget
   252D FF                 2740 	mov	r7,a
                           2741 ;     genPlus
   252E E5 12              2742 	mov	a,_bp
   2530 24 01              2743 	add	a,#0x01
   2532 F8                 2744 	mov	r0,a
   2533 74 3A              2745 	mov	a,#0x3A
   2535 26                 2746 	add	a,@r0
   2536 FA                 2747 	mov	r2,a
   2537 74 00              2748 	mov	a,#0x00
   2539 08                 2749 	inc	r0
   253A 36                 2750 	addc	a,@r0
   253B FB                 2751 	mov	r3,a
   253C 08                 2752 	inc	r0
   253D 86 04              2753 	mov	ar4,@r0
                           2754 ;     genPointerGet
                           2755 ;     genGenPointerGet
   253F 8A 82              2756 	mov	dpl,r2
   2541 8B 83              2757 	mov	dph,r3
   2543 8C F0              2758 	mov	b,r4
   2545 E5 12              2759 	mov	a,_bp
   2547 24 08              2760 	add	a,#0x08
   2549 F8                 2761 	mov	r0,a
   254A 12 AE 30           2762 	lcall	__gptrget
   254D F6                 2763 	mov	@r0,a
                           2764 ;     genPlus
   254E E5 12              2765 	mov	a,_bp
   2550 24 08              2766 	add	a,#0x08
   2552 F8                 2767 	mov	r0,a
   2553 E6                 2768 	mov	a,@r0
   2554 25 05              2769 	add	a,ar5
   2556 FD                 2770 	mov	r5,a
   2557 74 00              2771 	mov	a,#0x00
   2559 35 06              2772 	addc	a,ar6
   255B FE                 2773 	mov	r6,a
                           2774 ;     genPointerSet
                           2775 ;     genGenPointerSet
   255C E5 12              2776 	mov	a,_bp
   255E 24 05              2777 	add	a,#0x05
   2560 F8                 2778 	mov	r0,a
   2561 86 82              2779 	mov	dpl,@r0
   2563 08                 2780 	inc	r0
   2564 86 83              2781 	mov	dph,@r0
   2566 08                 2782 	inc	r0
   2567 86 F0              2783 	mov	b,@r0
   2569 ED                 2784 	mov	a,r5
   256A 12 A3 97           2785 	lcall	__gptrput
   256D A3                 2786 	inc	dptr
   256E EE                 2787 	mov	a,r6
   256F 12 A3 97           2788 	lcall	__gptrput
   2572 A3                 2789 	inc	dptr
   2573 EF                 2790 	mov	a,r7
   2574 12 A3 97           2791 	lcall	__gptrput
                           2792 ;../../Source/queue.c:496: if( pxQueue->pcReadFrom >= pxQueue->pcTail )
                           2793 ;     genPlus
   2577 E5 12              2794 	mov	a,_bp
   2579 24 01              2795 	add	a,#0x01
   257B F8                 2796 	mov	r0,a
                           2797 ;     genPlusIncr
   257C 74 03              2798 	mov	a,#0x03
   257E 26                 2799 	add	a,@r0
   257F FA                 2800 	mov	r2,a
   2580 74 00              2801 	mov	a,#0x00
   2582 08                 2802 	inc	r0
   2583 36                 2803 	addc	a,@r0
   2584 FB                 2804 	mov	r3,a
   2585 08                 2805 	inc	r0
   2586 86 04              2806 	mov	ar4,@r0
                           2807 ;     genPointerGet
                           2808 ;     genGenPointerGet
   2588 8A 82              2809 	mov	dpl,r2
   258A 8B 83              2810 	mov	dph,r3
   258C 8C F0              2811 	mov	b,r4
   258E 12 AE 30           2812 	lcall	__gptrget
   2591 FA                 2813 	mov	r2,a
   2592 A3                 2814 	inc	dptr
   2593 12 AE 30           2815 	lcall	__gptrget
   2596 FB                 2816 	mov	r3,a
   2597 A3                 2817 	inc	dptr
   2598 12 AE 30           2818 	lcall	__gptrget
   259B FC                 2819 	mov	r4,a
                           2820 ;     genCmpLt
                           2821 ;     genCmp
   259C C3                 2822 	clr	c
   259D ED                 2823 	mov	a,r5
   259E 9A                 2824 	subb	a,r2
   259F EE                 2825 	mov	a,r6
   25A0 9B                 2826 	subb	a,r3
   25A1 EF                 2827 	mov	a,r7
   25A2 64 80              2828 	xrl	a,#0x80
   25A4 8C F0              2829 	mov	b,r4
   25A6 63 F0 80           2830 	xrl	b,#0x80
   25A9 95 F0              2831 	subb	a,b
   25AB E4                 2832 	clr	a
   25AC 33                 2833 	rlc	a
                           2834 ;     genIpop
   25AD D0 07              2835 	pop	ar7
   25AF D0 06              2836 	pop	ar6
   25B1 D0 05              2837 	pop	ar5
                           2838 ;     genIfx
                           2839 ;     genIfxJump
   25B3 60 03              2840 	jz	00124$
   25B5 02 25 EE           2841 	ljmp	00102$
   25B8                    2842 00124$:
                           2843 ;../../Source/queue.c:498: pxQueue->pcReadFrom = pxQueue->pcHead;
                           2844 ;     genPointerGet
                           2845 ;     genGenPointerGet
   25B8 E5 12              2846 	mov	a,_bp
   25BA 24 01              2847 	add	a,#0x01
   25BC F8                 2848 	mov	r0,a
   25BD 86 82              2849 	mov	dpl,@r0
   25BF 08                 2850 	inc	r0
   25C0 86 83              2851 	mov	dph,@r0
   25C2 08                 2852 	inc	r0
   25C3 86 F0              2853 	mov	b,@r0
   25C5 12 AE 30           2854 	lcall	__gptrget
   25C8 FA                 2855 	mov	r2,a
   25C9 A3                 2856 	inc	dptr
   25CA 12 AE 30           2857 	lcall	__gptrget
   25CD FB                 2858 	mov	r3,a
   25CE A3                 2859 	inc	dptr
   25CF 12 AE 30           2860 	lcall	__gptrget
   25D2 FC                 2861 	mov	r4,a
                           2862 ;     genPointerSet
                           2863 ;     genGenPointerSet
   25D3 E5 12              2864 	mov	a,_bp
   25D5 24 05              2865 	add	a,#0x05
   25D7 F8                 2866 	mov	r0,a
   25D8 86 82              2867 	mov	dpl,@r0
   25DA 08                 2868 	inc	r0
   25DB 86 83              2869 	mov	dph,@r0
   25DD 08                 2870 	inc	r0
   25DE 86 F0              2871 	mov	b,@r0
   25E0 EA                 2872 	mov	a,r2
   25E1 12 A3 97           2873 	lcall	__gptrput
   25E4 A3                 2874 	inc	dptr
   25E5 EB                 2875 	mov	a,r3
   25E6 12 A3 97           2876 	lcall	__gptrput
   25E9 A3                 2877 	inc	dptr
   25EA EC                 2878 	mov	a,r4
   25EB 12 A3 97           2879 	lcall	__gptrput
   25EE                    2880 00102$:
                           2881 ;../../Source/queue.c:500: --( pxQueue->ucMessagesWaiting );
                           2882 ;     genMinus
   25EE E5 12              2883 	mov	a,_bp
   25F0 24 04              2884 	add	a,#0x04
   25F2 F8                 2885 	mov	r0,a
                           2886 ;     genMinusDec
   25F3 E6                 2887 	mov	a,@r0
   25F4 14                 2888 	dec	a
   25F5 FA                 2889 	mov	r2,a
                           2890 ;     genPointerSet
                           2891 ;     genGenPointerSet
   25F6 8D 82              2892 	mov	dpl,r5
   25F8 8E 83              2893 	mov	dph,r6
   25FA 8F F0              2894 	mov	b,r7
   25FC EA                 2895 	mov	a,r2
   25FD 12 A3 97           2896 	lcall	__gptrput
                           2897 ;../../Source/queue.c:501: memcpy( ( void * ) pcBuffer, ( void * ) pxQueue->pcReadFrom, ( unsigned ) pxQueue->ucItemSize );
                           2898 ;     genCast
   2600 E5 12              2899 	mov	a,_bp
   2602 24 08              2900 	add	a,#0x08
   2604 F8                 2901 	mov	r0,a
   2605 86 02              2902 	mov	ar2,@r0
   2607 7B 00              2903 	mov	r3,#0x00
                           2904 ;     genPointerGet
                           2905 ;     genGenPointerGet
   2609 E5 12              2906 	mov	a,_bp
   260B 24 05              2907 	add	a,#0x05
   260D F8                 2908 	mov	r0,a
   260E 86 82              2909 	mov	dpl,@r0
   2610 08                 2910 	inc	r0
   2611 86 83              2911 	mov	dph,@r0
   2613 08                 2912 	inc	r0
   2614 86 F0              2913 	mov	b,@r0
   2616 12 AE 30           2914 	lcall	__gptrget
   2619 FC                 2915 	mov	r4,a
   261A A3                 2916 	inc	dptr
   261B 12 AE 30           2917 	lcall	__gptrget
   261E FD                 2918 	mov	r5,a
   261F A3                 2919 	inc	dptr
   2620 12 AE 30           2920 	lcall	__gptrget
   2623 FE                 2921 	mov	r6,a
                           2922 ;     genIpush
   2624 C0 02              2923 	push	ar2
   2626 C0 03              2924 	push	ar3
                           2925 ;     genIpush
   2628 C0 04              2926 	push	ar4
   262A C0 05              2927 	push	ar5
   262C C0 06              2928 	push	ar6
                           2929 ;     genCall
   262E E5 12              2930 	mov	a,_bp
   2630 24 FB              2931 	add	a,#0xfb
   2632 F8                 2932 	mov	r0,a
   2633 86 82              2933 	mov	dpl,@r0
   2635 08                 2934 	inc	r0
   2636 86 83              2935 	mov	dph,@r0
   2638 08                 2936 	inc	r0
   2639 86 F0              2937 	mov	b,@r0
   263B 12 AC 5D           2938 	lcall	_memcpy
   263E E5 81              2939 	mov	a,sp
   2640 24 FB              2940 	add	a,#0xfb
   2642 F5 81              2941 	mov	sp,a
                           2942 ;../../Source/queue.c:506: if( pxQueue->cRxLock == queueUNLOCKED )
                           2943 ;     genPlus
   2644 E5 12              2944 	mov	a,_bp
   2646 24 01              2945 	add	a,#0x01
   2648 F8                 2946 	mov	r0,a
   2649 74 3B              2947 	mov	a,#0x3B
   264B 26                 2948 	add	a,@r0
   264C FA                 2949 	mov	r2,a
   264D 74 00              2950 	mov	a,#0x00
   264F 08                 2951 	inc	r0
   2650 36                 2952 	addc	a,@r0
   2651 FB                 2953 	mov	r3,a
   2652 08                 2954 	inc	r0
   2653 86 04              2955 	mov	ar4,@r0
                           2956 ;     genPointerGet
                           2957 ;     genGenPointerGet
   2655 8A 82              2958 	mov	dpl,r2
   2657 8B 83              2959 	mov	dph,r3
   2659 8C F0              2960 	mov	b,r4
   265B 12 AE 30           2961 	lcall	__gptrget
   265E FD                 2962 	mov	r5,a
                           2963 ;     genCmpEq
   265F BD FF 02           2964 	cjne	r5,#0xFF,00125$
   2662 80 03              2965 	sjmp	00126$
   2664                    2966 00125$:
   2664 02 26 EB           2967 	ljmp	00110$
   2667                    2968 00126$:
                           2969 ;../../Source/queue.c:510: if( !( *pcTaskWoken ) )
                           2970 ;     genAssign
   2667 E5 12              2971 	mov	a,_bp
   2669 24 F8              2972 	add	a,#0xf8
   266B F8                 2973 	mov	r0,a
   266C 86 02              2974 	mov	ar2,@r0
   266E 08                 2975 	inc	r0
   266F 86 03              2976 	mov	ar3,@r0
   2671 08                 2977 	inc	r0
   2672 86 04              2978 	mov	ar4,@r0
                           2979 ;     genPointerGet
                           2980 ;     genGenPointerGet
   2674 8A 82              2981 	mov	dpl,r2
   2676 8B 83              2982 	mov	dph,r3
   2678 8C F0              2983 	mov	b,r4
   267A 12 AE 30           2984 	lcall	__gptrget
                           2985 ;     genIfxJump
   267D 60 03              2986 	jz	00127$
   267F 02 26 F6           2987 	ljmp	00111$
   2682                    2988 00127$:
                           2989 ;../../Source/queue.c:512: if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) ) )
                           2990 ;     genPlus
   2682 E5 12              2991 	mov	a,_bp
   2684 24 01              2992 	add	a,#0x01
   2686 F8                 2993 	mov	r0,a
   2687 E5 12              2994 	mov	a,_bp
   2689 24 09              2995 	add	a,#0x09
   268B F9                 2996 	mov	r1,a
   268C 74 0C              2997 	mov	a,#0x0C
   268E 26                 2998 	add	a,@r0
   268F F7                 2999 	mov	@r1,a
   2690 74 00              3000 	mov	a,#0x00
   2692 08                 3001 	inc	r0
   2693 36                 3002 	addc	a,@r0
   2694 09                 3003 	inc	r1
   2695 F7                 3004 	mov	@r1,a
   2696 08                 3005 	inc	r0
   2697 09                 3006 	inc	r1
   2698 E6                 3007 	mov	a,@r0
   2699 F7                 3008 	mov	@r1,a
                           3009 ;     genPointerGet
                           3010 ;     genGenPointerGet
   269A E5 12              3011 	mov	a,_bp
   269C 24 09              3012 	add	a,#0x09
   269E F8                 3013 	mov	r0,a
   269F 86 82              3014 	mov	dpl,@r0
   26A1 08                 3015 	inc	r0
   26A2 86 83              3016 	mov	dph,@r0
   26A4 08                 3017 	inc	r0
   26A5 86 F0              3018 	mov	b,@r0
   26A7 12 AE 30           3019 	lcall	__gptrget
   26AA FE                 3020 	mov	r6,a
   26AB A3                 3021 	inc	dptr
   26AC 12 AE 30           3022 	lcall	__gptrget
   26AF FF                 3023 	mov	r7,a
                           3024 ;     genCmpEq
   26B0 BE 00 06           3025 	cjne	r6,#0x00,00128$
   26B3 BF 00 03           3026 	cjne	r7,#0x00,00128$
   26B6 02 26 F6           3027 	ljmp	00111$
   26B9                    3028 00128$:
                           3029 ;../../Source/queue.c:514: if( cTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToSend ) ) != ( signed portCHAR ) pdFALSE )
                           3030 ;     genCall
   26B9 E5 12              3031 	mov	a,_bp
   26BB 24 09              3032 	add	a,#0x09
   26BD F8                 3033 	mov	r0,a
   26BE 86 82              3034 	mov	dpl,@r0
   26C0 08                 3035 	inc	r0
   26C1 86 83              3036 	mov	dph,@r0
   26C3 08                 3037 	inc	r0
   26C4 86 F0              3038 	mov	b,@r0
   26C6 C0 02              3039 	push	ar2
   26C8 C0 03              3040 	push	ar3
   26CA C0 04              3041 	push	ar4
   26CC 12 0E 69           3042 	lcall	_cTaskRemoveFromEventList
   26CF AE 82              3043 	mov	r6,dpl
   26D1 D0 04              3044 	pop	ar4
   26D3 D0 03              3045 	pop	ar3
   26D5 D0 02              3046 	pop	ar2
                           3047 ;     genCmpEq
   26D7 BE 00 03           3048 	cjne	r6,#0x00,00129$
   26DA 02 26 F6           3049 	ljmp	00111$
   26DD                    3050 00129$:
                           3051 ;../../Source/queue.c:518: *pcTaskWoken = ( signed portCHAR ) pdTRUE;
                           3052 ;     genPointerSet
                           3053 ;     genGenPointerSet
   26DD 8A 82              3054 	mov	dpl,r2
   26DF 8B 83              3055 	mov	dph,r3
   26E1 8C F0              3056 	mov	b,r4
   26E3 74 01              3057 	mov	a,#0x01
   26E5 12 A3 97           3058 	lcall	__gptrput
   26E8 02 26 F6           3059 	ljmp	00111$
   26EB                    3060 00110$:
                           3061 ;../../Source/queue.c:527: ++( pxQueue->cRxLock );
                           3062 ;     genPlus
                           3063 ;     genPlusIncr
   26EB 0D                 3064 	inc	r5
                           3065 ;     genPointerSet
                           3066 ;     genGenPointerSet
   26EC 8A 82              3067 	mov	dpl,r2
   26EE 8B 83              3068 	mov	dph,r3
   26F0 8C F0              3069 	mov	b,r4
   26F2 ED                 3070 	mov	a,r5
   26F3 12 A3 97           3071 	lcall	__gptrput
   26F6                    3072 00111$:
                           3073 ;../../Source/queue.c:530: cReturn = ( signed portCHAR ) pdPASS;
                           3074 ;     genAssign
   26F6 7A 01              3075 	mov	r2,#0x01
   26F8 02 26 FD           3076 	ljmp	00114$
   26FB                    3077 00113$:
                           3078 ;../../Source/queue.c:534: cReturn = ( signed portCHAR ) pdFAIL;
                           3079 ;     genAssign
   26FB 7A 00              3080 	mov	r2,#0x00
   26FD                    3081 00114$:
                           3082 ;../../Source/queue.c:537: return cReturn;
                           3083 ;     genRet
   26FD 8A 82              3084 	mov	dpl,r2
   26FF                    3085 00115$:
   26FF 85 12 81           3086 	mov	sp,_bp
   2702 D0 12              3087 	pop	_bp
   2704 22                 3088 	ret
                           3089 ;------------------------------------------------------------
                           3090 ;Allocation info for local variables in function 'ucQueueMessagesWaiting'
                           3091 ;------------------------------------------------------------
                           3092 ;pxQueue                   Allocated to registers r2 r3 r4 
                           3093 ;ucReturn                  Allocated to registers r2 
                           3094 ;------------------------------------------------------------
                           3095 ;../../Source/queue.c:541: unsigned portCHAR ucQueueMessagesWaiting( xQueueHandle pxQueue )
                           3096 ;	-----------------------------------------
                           3097 ;	 function ucQueueMessagesWaiting
                           3098 ;	-----------------------------------------
   2705                    3099 _ucQueueMessagesWaiting:
   2705 C0 12              3100 	push	_bp
   2707 85 81 12           3101 	mov	_bp,sp
                           3102 ;     genReceive
   270A AA 82              3103 	mov	r2,dpl
   270C AB 83              3104 	mov	r3,dph
   270E AC F0              3105 	mov	r4,b
                           3106 ;../../Source/queue.c:545: taskENTER_CRITICAL();
                           3107 ;     genInline
   2710 C0 E0 C0 A8        3108 	 push ACC push IE 
                           3109 ;     genAssign
   2714 C2 AF              3110 	clr	_EA
                           3111 ;../../Source/queue.c:546: ucReturn = pxQueue->ucMessagesWaiting;
                           3112 ;     genPlus
   2716 74 38              3113 	mov	a,#0x38
   2718 25 02              3114 	add	a,ar2
   271A FA                 3115 	mov	r2,a
   271B 74 00              3116 	mov	a,#0x00
   271D 35 03              3117 	addc	a,ar3
   271F FB                 3118 	mov	r3,a
                           3119 ;     genPointerGet
                           3120 ;     genGenPointerGet
   2720 8A 82              3121 	mov	dpl,r2
   2722 8B 83              3122 	mov	dph,r3
   2724 8C F0              3123 	mov	b,r4
   2726 12 AE 30           3124 	lcall	__gptrget
   2729 FA                 3125 	mov	r2,a
                           3126 ;     genAssign
                           3127 ;../../Source/queue.c:547: taskEXIT_CRITICAL();
                           3128 ;     genInline
   272A D0 E0              3129 	 pop ACC 
                           3130 ;     genAnd
   272C 53 E0 80           3131 	anl	_ACC,#0x80
                           3132 ;     genOr
   272F E5 E0              3133 	mov	a,_ACC
   2731 42 A8              3134 	orl	_IE,a
                           3135 ;     genInline
   2733 D0 E0              3136 	 pop ACC 
                           3137 ;../../Source/queue.c:549: return ucReturn;
                           3138 ;     genRet
   2735 8A 82              3139 	mov	dpl,r2
   2737                    3140 00101$:
   2737 85 12 81           3141 	mov	sp,_bp
   273A D0 12              3142 	pop	_bp
   273C 22                 3143 	ret
                           3144 ;------------------------------------------------------------
                           3145 ;Allocation info for local variables in function 'vQueueDelete'
                           3146 ;------------------------------------------------------------
                           3147 ;pxQueue                   Allocated to registers r2 r3 r4 
                           3148 ;------------------------------------------------------------
                           3149 ;../../Source/queue.c:553: void vQueueDelete( xQueueHandle pxQueue )
                           3150 ;	-----------------------------------------
                           3151 ;	 function vQueueDelete
                           3152 ;	-----------------------------------------
   273D                    3153 _vQueueDelete:
   273D C0 12              3154 	push	_bp
   273F 85 81 12           3155 	mov	_bp,sp
                           3156 ;     genReceive
   2742 AA 82              3157 	mov	r2,dpl
   2744 AB 83              3158 	mov	r3,dph
   2746 AC F0              3159 	mov	r4,b
                           3160 ;../../Source/queue.c:555: vPortFree( pxQueue->pcHead );
                           3161 ;     genPointerGet
                           3162 ;     genGenPointerGet
   2748 8A 82              3163 	mov	dpl,r2
   274A 8B 83              3164 	mov	dph,r3
   274C 8C F0              3165 	mov	b,r4
   274E 12 AE 30           3166 	lcall	__gptrget
   2751 FD                 3167 	mov	r5,a
   2752 A3                 3168 	inc	dptr
   2753 12 AE 30           3169 	lcall	__gptrget
   2756 FE                 3170 	mov	r6,a
   2757 A3                 3171 	inc	dptr
   2758 12 AE 30           3172 	lcall	__gptrget
   275B FF                 3173 	mov	r7,a
                           3174 ;     genCall
   275C 8D 82              3175 	mov	dpl,r5
   275E 8E 83              3176 	mov	dph,r6
   2760 8F F0              3177 	mov	b,r7
   2762 C0 02              3178 	push	ar2
   2764 C0 03              3179 	push	ar3
   2766 C0 04              3180 	push	ar4
   2768 12 32 8D           3181 	lcall	_vPortFree
   276B D0 04              3182 	pop	ar4
   276D D0 03              3183 	pop	ar3
   276F D0 02              3184 	pop	ar2
                           3185 ;../../Source/queue.c:556: vPortFree( pxQueue );
                           3186 ;     genCall
   2771 8A 82              3187 	mov	dpl,r2
   2773 8B 83              3188 	mov	dph,r3
   2775 8C F0              3189 	mov	b,r4
   2777 12 32 8D           3190 	lcall	_vPortFree
   277A                    3191 00101$:
   277A 85 12 81           3192 	mov	sp,_bp
   277D D0 12              3193 	pop	_bp
   277F 22                 3194 	ret
                           3195 ;------------------------------------------------------------
                           3196 ;Allocation info for local variables in function 'prvUnlockQueue'
                           3197 ;------------------------------------------------------------
                           3198 ;pxQueue                   Allocated to stack - offset 1
                           3199 ;cYieldRequired            Allocated to stack - offset 4
                           3200 ;------------------------------------------------------------
                           3201 ;../../Source/queue.c:560: static signed portCHAR prvUnlockQueue( xQueueHandle pxQueue )
                           3202 ;	-----------------------------------------
                           3203 ;	 function prvUnlockQueue
                           3204 ;	-----------------------------------------
   2780                    3205 _prvUnlockQueue:
   2780 C0 12              3206 	push	_bp
   2782 85 81 12           3207 	mov	_bp,sp
                           3208 ;     genReceive
   2785 C0 82              3209 	push	dpl
   2787 C0 83              3210 	push	dph
   2789 C0 F0              3211 	push	b
   278B 05 81              3212 	inc	sp
                           3213 ;../../Source/queue.c:562: signed portCHAR cYieldRequired = ( signed portCHAR ) pdFALSE;
                           3214 ;     genAssign
   278D E5 12              3215 	mov	a,_bp
   278F 24 04              3216 	add	a,#0x04
   2791 F8                 3217 	mov	r0,a
   2792 76 00              3218 	mov	@r0,#0x00
                           3219 ;../../Source/queue.c:570: taskENTER_CRITICAL();
                           3220 ;     genInline
   2794 C0 E0 C0 A8        3221 	 push ACC push IE 
                           3222 ;     genAssign
   2798 C2 AF              3223 	clr	_EA
                           3224 ;../../Source/queue.c:572: --( pxQueue->cTxLock );
                           3225 ;     genPlus
   279A E5 12              3226 	mov	a,_bp
   279C 24 01              3227 	add	a,#0x01
   279E F8                 3228 	mov	r0,a
   279F 74 3C              3229 	mov	a,#0x3C
   27A1 26                 3230 	add	a,@r0
   27A2 FE                 3231 	mov	r6,a
   27A3 74 00              3232 	mov	a,#0x00
   27A5 08                 3233 	inc	r0
   27A6 36                 3234 	addc	a,@r0
   27A7 FF                 3235 	mov	r7,a
   27A8 08                 3236 	inc	r0
   27A9 86 05              3237 	mov	ar5,@r0
                           3238 ;     genPointerGet
                           3239 ;     genGenPointerGet
   27AB 8E 82              3240 	mov	dpl,r6
   27AD 8F 83              3241 	mov	dph,r7
   27AF 8D F0              3242 	mov	b,r5
   27B1 12 AE 30           3243 	lcall	__gptrget
   27B4 FA                 3244 	mov	r2,a
                           3245 ;     genMinus
                           3246 ;     genMinusDec
   27B5 1A                 3247 	dec	r2
                           3248 ;     genPointerSet
                           3249 ;     genGenPointerSet
   27B6 8E 82              3250 	mov	dpl,r6
   27B8 8F 83              3251 	mov	dph,r7
   27BA 8D F0              3252 	mov	b,r5
   27BC EA                 3253 	mov	a,r2
   27BD 12 A3 97           3254 	lcall	__gptrput
                           3255 ;../../Source/queue.c:575: if( pxQueue->cTxLock > queueUNLOCKED )
                           3256 ;     genCmpGt
                           3257 ;     genCmp
   27C0 C3                 3258 	clr	c
   27C1 74 FF              3259 	mov	a,#0xFF
   27C3 64 80              3260 	xrl	a,#0x80
   27C5 8A F0              3261 	mov	b,r2
   27C7 63 F0 80           3262 	xrl	b,#0x80
   27CA 95 F0              3263 	subb	a,b
                           3264 ;     genIfxJump
   27CC 40 03              3265 	jc	00121$
   27CE 02 28 1D           3266 	ljmp	00106$
   27D1                    3267 00121$:
                           3268 ;../../Source/queue.c:577: pxQueue->cTxLock = queueUNLOCKED;
                           3269 ;     genPointerSet
                           3270 ;     genGenPointerSet
   27D1 8E 82              3271 	mov	dpl,r6
   27D3 8F 83              3272 	mov	dph,r7
   27D5 8D F0              3273 	mov	b,r5
   27D7 74 FF              3274 	mov	a,#0xFF
   27D9 12 A3 97           3275 	lcall	__gptrput
                           3276 ;../../Source/queue.c:581: if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) ) )
                           3277 ;     genPlus
   27DC E5 12              3278 	mov	a,_bp
   27DE 24 01              3279 	add	a,#0x01
   27E0 F8                 3280 	mov	r0,a
   27E1 74 22              3281 	mov	a,#0x22
   27E3 26                 3282 	add	a,@r0
   27E4 FA                 3283 	mov	r2,a
   27E5 74 00              3284 	mov	a,#0x00
   27E7 08                 3285 	inc	r0
   27E8 36                 3286 	addc	a,@r0
   27E9 FB                 3287 	mov	r3,a
   27EA 08                 3288 	inc	r0
   27EB 86 04              3289 	mov	ar4,@r0
                           3290 ;     genPointerGet
                           3291 ;     genGenPointerGet
   27ED 8A 82              3292 	mov	dpl,r2
   27EF 8B 83              3293 	mov	dph,r3
   27F1 8C F0              3294 	mov	b,r4
   27F3 12 AE 30           3295 	lcall	__gptrget
   27F6 FD                 3296 	mov	r5,a
   27F7 A3                 3297 	inc	dptr
   27F8 12 AE 30           3298 	lcall	__gptrget
   27FB FE                 3299 	mov	r6,a
                           3300 ;     genCmpEq
   27FC BD 00 06           3301 	cjne	r5,#0x00,00122$
   27FF BE 00 03           3302 	cjne	r6,#0x00,00122$
   2802 02 28 1D           3303 	ljmp	00106$
   2805                    3304 00122$:
                           3305 ;../../Source/queue.c:585: if( cTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToReceive ) ) != ( signed portCHAR ) pdFALSE )
                           3306 ;     genCall
   2805 8A 82              3307 	mov	dpl,r2
   2807 8B 83              3308 	mov	dph,r3
   2809 8C F0              3309 	mov	b,r4
   280B 12 0E 69           3310 	lcall	_cTaskRemoveFromEventList
   280E AA 82              3311 	mov	r2,dpl
                           3312 ;     genCmpEq
   2810 BA 00 03           3313 	cjne	r2,#0x00,00123$
   2813 02 28 1D           3314 	ljmp	00106$
   2816                    3315 00123$:
                           3316 ;../../Source/queue.c:589: cYieldRequired = ( signed portCHAR ) pdTRUE;
                           3317 ;     genAssign
   2816 E5 12              3318 	mov	a,_bp
   2818 24 04              3319 	add	a,#0x04
   281A F8                 3320 	mov	r0,a
   281B 76 01              3321 	mov	@r0,#0x01
   281D                    3322 00106$:
                           3323 ;../../Source/queue.c:594: taskEXIT_CRITICAL();
                           3324 ;     genInline
   281D D0 E0              3325 	 pop ACC 
                           3326 ;     genAnd
   281F 53 E0 80           3327 	anl	_ACC,#0x80
                           3328 ;     genOr
   2822 E5 E0              3329 	mov	a,_ACC
   2824 42 A8              3330 	orl	_IE,a
                           3331 ;     genInline
   2826 D0 E0              3332 	 pop ACC 
                           3333 ;../../Source/queue.c:597: taskENTER_CRITICAL();
                           3334 ;     genInline
   2828 C0 E0 C0 A8        3335 	 push ACC push IE 
                           3336 ;     genAssign
   282C C2 AF              3337 	clr	_EA
                           3338 ;../../Source/queue.c:599: --( pxQueue->cRxLock );
                           3339 ;     genPlus
   282E E5 12              3340 	mov	a,_bp
   2830 24 01              3341 	add	a,#0x01
   2832 F8                 3342 	mov	r0,a
   2833 74 3B              3343 	mov	a,#0x3B
   2835 26                 3344 	add	a,@r0
   2836 FA                 3345 	mov	r2,a
   2837 74 00              3346 	mov	a,#0x00
   2839 08                 3347 	inc	r0
   283A 36                 3348 	addc	a,@r0
   283B FB                 3349 	mov	r3,a
   283C 08                 3350 	inc	r0
   283D 86 04              3351 	mov	ar4,@r0
                           3352 ;     genPointerGet
                           3353 ;     genGenPointerGet
   283F 8A 82              3354 	mov	dpl,r2
   2841 8B 83              3355 	mov	dph,r3
   2843 8C F0              3356 	mov	b,r4
   2845 12 AE 30           3357 	lcall	__gptrget
   2848 FD                 3358 	mov	r5,a
                           3359 ;     genMinus
                           3360 ;     genMinusDec
   2849 1D                 3361 	dec	r5
                           3362 ;     genPointerSet
                           3363 ;     genGenPointerSet
   284A 8A 82              3364 	mov	dpl,r2
   284C 8B 83              3365 	mov	dph,r3
   284E 8C F0              3366 	mov	b,r4
   2850 ED                 3367 	mov	a,r5
   2851 12 A3 97           3368 	lcall	__gptrput
                           3369 ;../../Source/queue.c:601: if( pxQueue->cRxLock > queueUNLOCKED )
                           3370 ;     genCmpGt
                           3371 ;     genCmp
   2854 C3                 3372 	clr	c
   2855 74 FF              3373 	mov	a,#0xFF
   2857 64 80              3374 	xrl	a,#0x80
   2859 8D F0              3375 	mov	b,r5
   285B 63 F0 80           3376 	xrl	b,#0x80
   285E 95 F0              3377 	subb	a,b
                           3378 ;     genIfxJump
   2860 40 03              3379 	jc	00124$
   2862 02 28 B1           3380 	ljmp	00112$
   2865                    3381 00124$:
                           3382 ;../../Source/queue.c:603: pxQueue->cRxLock = queueUNLOCKED;
                           3383 ;     genPointerSet
                           3384 ;     genGenPointerSet
   2865 8A 82              3385 	mov	dpl,r2
   2867 8B 83              3386 	mov	dph,r3
   2869 8C F0              3387 	mov	b,r4
   286B 74 FF              3388 	mov	a,#0xFF
   286D 12 A3 97           3389 	lcall	__gptrput
                           3390 ;../../Source/queue.c:605: if( !listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) ) )
                           3391 ;     genPlus
   2870 E5 12              3392 	mov	a,_bp
   2872 24 01              3393 	add	a,#0x01
   2874 F8                 3394 	mov	r0,a
   2875 74 0C              3395 	mov	a,#0x0C
   2877 26                 3396 	add	a,@r0
   2878 FA                 3397 	mov	r2,a
   2879 74 00              3398 	mov	a,#0x00
   287B 08                 3399 	inc	r0
   287C 36                 3400 	addc	a,@r0
   287D FB                 3401 	mov	r3,a
   287E 08                 3402 	inc	r0
   287F 86 04              3403 	mov	ar4,@r0
                           3404 ;     genPointerGet
                           3405 ;     genGenPointerGet
   2881 8A 82              3406 	mov	dpl,r2
   2883 8B 83              3407 	mov	dph,r3
   2885 8C F0              3408 	mov	b,r4
   2887 12 AE 30           3409 	lcall	__gptrget
   288A FD                 3410 	mov	r5,a
   288B A3                 3411 	inc	dptr
   288C 12 AE 30           3412 	lcall	__gptrget
   288F FE                 3413 	mov	r6,a
                           3414 ;     genCmpEq
   2890 BD 00 06           3415 	cjne	r5,#0x00,00125$
   2893 BE 00 03           3416 	cjne	r6,#0x00,00125$
   2896 02 28 B1           3417 	ljmp	00112$
   2899                    3418 00125$:
                           3419 ;../../Source/queue.c:607: if( cTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToSend ) ) != ( signed portCHAR ) pdFALSE )
                           3420 ;     genCall
   2899 8A 82              3421 	mov	dpl,r2
   289B 8B 83              3422 	mov	dph,r3
   289D 8C F0              3423 	mov	b,r4
   289F 12 0E 69           3424 	lcall	_cTaskRemoveFromEventList
   28A2 AA 82              3425 	mov	r2,dpl
                           3426 ;     genCmpEq
   28A4 BA 00 03           3427 	cjne	r2,#0x00,00126$
   28A7 02 28 B1           3428 	ljmp	00112$
   28AA                    3429 00126$:
                           3430 ;../../Source/queue.c:609: cYieldRequired = ( signed portCHAR ) pdTRUE;
                           3431 ;     genAssign
   28AA E5 12              3432 	mov	a,_bp
   28AC 24 04              3433 	add	a,#0x04
   28AE F8                 3434 	mov	r0,a
   28AF 76 01              3435 	mov	@r0,#0x01
   28B1                    3436 00112$:
                           3437 ;../../Source/queue.c:614: taskEXIT_CRITICAL();
                           3438 ;     genInline
   28B1 D0 E0              3439 	 pop ACC 
                           3440 ;     genAnd
   28B3 53 E0 80           3441 	anl	_ACC,#0x80
                           3442 ;     genOr
   28B6 E5 E0              3443 	mov	a,_ACC
   28B8 42 A8              3444 	orl	_IE,a
                           3445 ;     genInline
   28BA D0 E0              3446 	 pop ACC 
                           3447 ;../../Source/queue.c:616: return cYieldRequired;
                           3448 ;     genRet
   28BC E5 12              3449 	mov	a,_bp
   28BE 24 04              3450 	add	a,#0x04
   28C0 F8                 3451 	mov	r0,a
   28C1 86 82              3452 	mov	dpl,@r0
   28C3                    3453 00113$:
   28C3 85 12 81           3454 	mov	sp,_bp
   28C6 D0 12              3455 	pop	_bp
   28C8 22                 3456 	ret
                           3457 ;------------------------------------------------------------
                           3458 ;Allocation info for local variables in function 'prvIsQueueEmpty'
                           3459 ;------------------------------------------------------------
                           3460 ;pxQueue                   Allocated to registers r2 r3 r4 
                           3461 ;cReturn                   Allocated to registers r2 
                           3462 ;------------------------------------------------------------
                           3463 ;../../Source/queue.c:620: static signed portCHAR prvIsQueueEmpty( const xQueueHandle pxQueue )
                           3464 ;	-----------------------------------------
                           3465 ;	 function prvIsQueueEmpty
                           3466 ;	-----------------------------------------
   28C9                    3467 _prvIsQueueEmpty:
   28C9 C0 12              3468 	push	_bp
   28CB 85 81 12           3469 	mov	_bp,sp
                           3470 ;     genReceive
   28CE AA 82              3471 	mov	r2,dpl
   28D0 AB 83              3472 	mov	r3,dph
   28D2 AC F0              3473 	mov	r4,b
                           3474 ;../../Source/queue.c:624: taskENTER_CRITICAL();
                           3475 ;     genInline
   28D4 C0 E0 C0 A8        3476 	 push ACC push IE 
                           3477 ;     genAssign
   28D8 C2 AF              3478 	clr	_EA
                           3479 ;../../Source/queue.c:625: cReturn = ( pxQueue->ucMessagesWaiting == ( unsigned portCHAR ) 0 );
                           3480 ;     genPlus
   28DA 74 38              3481 	mov	a,#0x38
   28DC 25 02              3482 	add	a,ar2
   28DE FA                 3483 	mov	r2,a
   28DF 74 00              3484 	mov	a,#0x00
   28E1 35 03              3485 	addc	a,ar3
   28E3 FB                 3486 	mov	r3,a
                           3487 ;     genPointerGet
                           3488 ;     genGenPointerGet
   28E4 8A 82              3489 	mov	dpl,r2
   28E6 8B 83              3490 	mov	dph,r3
   28E8 8C F0              3491 	mov	b,r4
   28EA 12 AE 30           3492 	lcall	__gptrget
   28ED FA                 3493 	mov	r2,a
                           3494 ;     genCmpEq
   28EE BA 00 04           3495 	cjne	r2,#0x00,00103$
   28F1 74 01              3496 	mov	a,#0x01
   28F3 80 01              3497 	sjmp	00104$
   28F5                    3498 00103$:
   28F5 E4                 3499 	clr	a
   28F6                    3500 00104$:
   28F6 FA                 3501 	mov	r2,a
                           3502 ;../../Source/queue.c:626: taskEXIT_CRITICAL();
                           3503 ;     genInline
   28F7 D0 E0              3504 	 pop ACC 
                           3505 ;     genAnd
   28F9 53 E0 80           3506 	anl	_ACC,#0x80
                           3507 ;     genOr
   28FC E5 E0              3508 	mov	a,_ACC
   28FE 42 A8              3509 	orl	_IE,a
                           3510 ;     genInline
   2900 D0 E0              3511 	 pop ACC 
                           3512 ;../../Source/queue.c:628: return cReturn;
                           3513 ;     genRet
   2902 8A 82              3514 	mov	dpl,r2
   2904                    3515 00101$:
   2904 85 12 81           3516 	mov	sp,_bp
   2907 D0 12              3517 	pop	_bp
   2909 22                 3518 	ret
                           3519 ;------------------------------------------------------------
                           3520 ;Allocation info for local variables in function 'prvIsQueueFull'
                           3521 ;------------------------------------------------------------
                           3522 ;pxQueue                   Allocated to registers r2 r3 r4 
                           3523 ;cReturn                   Allocated to registers r5 
                           3524 ;------------------------------------------------------------
                           3525 ;../../Source/queue.c:632: static signed portCHAR prvIsQueueFull( const xQueueHandle pxQueue )
                           3526 ;	-----------------------------------------
                           3527 ;	 function prvIsQueueFull
                           3528 ;	-----------------------------------------
   290A                    3529 _prvIsQueueFull:
   290A C0 12              3530 	push	_bp
   290C 85 81 12           3531 	mov	_bp,sp
                           3532 ;     genReceive
   290F AA 82              3533 	mov	r2,dpl
   2911 AB 83              3534 	mov	r3,dph
   2913 AC F0              3535 	mov	r4,b
                           3536 ;../../Source/queue.c:636: taskENTER_CRITICAL();
                           3537 ;     genInline
   2915 C0 E0 C0 A8        3538 	 push ACC push IE 
                           3539 ;     genAssign
   2919 C2 AF              3540 	clr	_EA
                           3541 ;../../Source/queue.c:637: cReturn = ( pxQueue->ucMessagesWaiting == pxQueue->ucLength );
                           3542 ;     genPlus
   291B 74 38              3543 	mov	a,#0x38
   291D 25 02              3544 	add	a,ar2
   291F FD                 3545 	mov	r5,a
   2920 74 00              3546 	mov	a,#0x00
   2922 35 03              3547 	addc	a,ar3
   2924 FE                 3548 	mov	r6,a
   2925 8C 07              3549 	mov	ar7,r4
                           3550 ;     genPointerGet
                           3551 ;     genGenPointerGet
   2927 8D 82              3552 	mov	dpl,r5
   2929 8E 83              3553 	mov	dph,r6
   292B 8F F0              3554 	mov	b,r7
   292D 12 AE 30           3555 	lcall	__gptrget
   2930 FD                 3556 	mov	r5,a
                           3557 ;     genPlus
   2931 74 39              3558 	mov	a,#0x39
   2933 25 02              3559 	add	a,ar2
   2935 FA                 3560 	mov	r2,a
   2936 74 00              3561 	mov	a,#0x00
   2938 35 03              3562 	addc	a,ar3
   293A FB                 3563 	mov	r3,a
                           3564 ;     genPointerGet
                           3565 ;     genGenPointerGet
   293B 8A 82              3566 	mov	dpl,r2
   293D 8B 83              3567 	mov	dph,r3
   293F 8C F0              3568 	mov	b,r4
   2941 12 AE 30           3569 	lcall	__gptrget
   2944 FA                 3570 	mov	r2,a
                           3571 ;     genCmpEq
   2945 ED                 3572 	mov	a,r5
   2946 B5 02 04           3573 	cjne	a,ar2,00103$
   2949 74 01              3574 	mov	a,#0x01
   294B 80 01              3575 	sjmp	00104$
   294D                    3576 00103$:
   294D E4                 3577 	clr	a
   294E                    3578 00104$:
   294E FD                 3579 	mov	r5,a
                           3580 ;     genAssign
                           3581 ;../../Source/queue.c:638: taskEXIT_CRITICAL();
                           3582 ;     genInline
   294F D0 E0              3583 	 pop ACC 
                           3584 ;     genAnd
   2951 53 E0 80           3585 	anl	_ACC,#0x80
                           3586 ;     genOr
   2954 E5 E0              3587 	mov	a,_ACC
   2956 42 A8              3588 	orl	_IE,a
                           3589 ;     genInline
   2958 D0 E0              3590 	 pop ACC 
                           3591 ;../../Source/queue.c:640: return cReturn;
                           3592 ;     genRet
   295A 8D 82              3593 	mov	dpl,r5
   295C                    3594 00101$:
   295C 85 12 81           3595 	mov	sp,_bp
   295F D0 12              3596 	pop	_bp
   2961 22                 3597 	ret
                           3598 	.area CSEG    (CODE)
                           3599 	.area XINIT   (CODE)
