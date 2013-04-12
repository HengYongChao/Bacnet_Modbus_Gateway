                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.4.8 #964 (Feb 23 2005)
                              4 ; This file generated Fri May 20 14:05:28 2005
                              5 ;--------------------------------------------------------
                              6 	.module ______Source_portable_SDCC_ASIX_port
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
                            130 	.globl _pxPortInitialiseStack
                            131 	.globl _sPortStartScheduler
                            132 	.globl _vPortEndScheduler
                            133 	.globl _vPortYield
                            134 	.globl _vTimer2ISR
                            135 ;--------------------------------------------------------
                            136 ; special function registers
                            137 ;--------------------------------------------------------
                            138 	.area RSEG    (DATA)
                    0080    139 _P0	=	0x0080
                    0081    140 _SP	=	0x0081
                    0082    141 _DPL	=	0x0082
                    0083    142 _DPH	=	0x0083
                    0087    143 _PCON	=	0x0087
                    0088    144 _TCON	=	0x0088
                    0089    145 _TMOD	=	0x0089
                    008A    146 _TL0	=	0x008a
                    008B    147 _TL1	=	0x008b
                    008C    148 _TH0	=	0x008c
                    008D    149 _TH1	=	0x008d
                    0090    150 _P1	=	0x0090
                    0098    151 _SCON	=	0x0098
                    0099    152 _SBUF	=	0x0099
                    00A0    153 _P2	=	0x00a0
                    00A8    154 _IE	=	0x00a8
                    00B0    155 _P3	=	0x00b0
                    00B8    156 _IP	=	0x00b8
                    00D0    157 _PSW	=	0x00d0
                    00E0    158 _ACC	=	0x00e0
                    00F0    159 _B	=	0x00f0
                    00C8    160 _T2CON	=	0x00c8
                    00CA    161 _RCAP2L	=	0x00ca
                    00CB    162 _RCAP2H	=	0x00cb
                    00CC    163 _TL2	=	0x00cc
                    00CD    164 _TH2	=	0x00cd
                            165 ;--------------------------------------------------------
                            166 ; special function bits 
                            167 ;--------------------------------------------------------
                            168 	.area RSEG    (DATA)
                    0080    169 _P0_0	=	0x0080
                    0081    170 _P0_1	=	0x0081
                    0082    171 _P0_2	=	0x0082
                    0083    172 _P0_3	=	0x0083
                    0084    173 _P0_4	=	0x0084
                    0085    174 _P0_5	=	0x0085
                    0086    175 _P0_6	=	0x0086
                    0087    176 _P0_7	=	0x0087
                    0088    177 _IT0	=	0x0088
                    0089    178 _IE0	=	0x0089
                    008A    179 _IT1	=	0x008a
                    008B    180 _IE1	=	0x008b
                    008C    181 _TR0	=	0x008c
                    008D    182 _TF0	=	0x008d
                    008E    183 _TR1	=	0x008e
                    008F    184 _TF1	=	0x008f
                    0090    185 _P1_0	=	0x0090
                    0091    186 _P1_1	=	0x0091
                    0092    187 _P1_2	=	0x0092
                    0093    188 _P1_3	=	0x0093
                    0094    189 _P1_4	=	0x0094
                    0095    190 _P1_5	=	0x0095
                    0096    191 _P1_6	=	0x0096
                    0097    192 _P1_7	=	0x0097
                    0098    193 _RI	=	0x0098
                    0099    194 _TI	=	0x0099
                    009A    195 _RB8	=	0x009a
                    009B    196 _TB8	=	0x009b
                    009C    197 _REN	=	0x009c
                    009D    198 _SM2	=	0x009d
                    009E    199 _SM1	=	0x009e
                    009F    200 _SM0	=	0x009f
                    00A0    201 _P2_0	=	0x00a0
                    00A1    202 _P2_1	=	0x00a1
                    00A2    203 _P2_2	=	0x00a2
                    00A3    204 _P2_3	=	0x00a3
                    00A4    205 _P2_4	=	0x00a4
                    00A5    206 _P2_5	=	0x00a5
                    00A6    207 _P2_6	=	0x00a6
                    00A7    208 _P2_7	=	0x00a7
                    00A8    209 _EX0	=	0x00a8
                    00A9    210 _ET0	=	0x00a9
                    00AA    211 _EX1	=	0x00aa
                    00AB    212 _ET1	=	0x00ab
                    00AC    213 _ES	=	0x00ac
                    00AF    214 _EA	=	0x00af
                    00B0    215 _P3_0	=	0x00b0
                    00B1    216 _P3_1	=	0x00b1
                    00B2    217 _P3_2	=	0x00b2
                    00B3    218 _P3_3	=	0x00b3
                    00B4    219 _P3_4	=	0x00b4
                    00B5    220 _P3_5	=	0x00b5
                    00B6    221 _P3_6	=	0x00b6
                    00B7    222 _P3_7	=	0x00b7
                    00B0    223 _RXD	=	0x00b0
                    00B1    224 _TXD	=	0x00b1
                    00B2    225 _INT0	=	0x00b2
                    00B3    226 _INT1	=	0x00b3
                    00B4    227 _T0	=	0x00b4
                    00B5    228 _T1	=	0x00b5
                    00B6    229 _WR	=	0x00b6
                    00B7    230 _RD	=	0x00b7
                    00B8    231 _PX0	=	0x00b8
                    00B9    232 _PT0	=	0x00b9
                    00BA    233 _PX1	=	0x00ba
                    00BB    234 _PT1	=	0x00bb
                    00BC    235 _PS	=	0x00bc
                    00D0    236 _P	=	0x00d0
                    00D1    237 _F1	=	0x00d1
                    00D2    238 _OV	=	0x00d2
                    00D3    239 _RS0	=	0x00d3
                    00D4    240 _RS1	=	0x00d4
                    00D5    241 _F0	=	0x00d5
                    00D6    242 _AC	=	0x00d6
                    00D7    243 _CY	=	0x00d7
                    00AD    244 _ET2	=	0x00ad
                    00C8    245 _T2CON_0	=	0x00c8
                    00C9    246 _T2CON_1	=	0x00c9
                    00CA    247 _T2CON_2	=	0x00ca
                    00CB    248 _T2CON_3	=	0x00cb
                    00CC    249 _T2CON_4	=	0x00cc
                    00CD    250 _T2CON_5	=	0x00cd
                    00CE    251 _T2CON_6	=	0x00ce
                    00CF    252 _T2CON_7	=	0x00cf
                    00C8    253 _CP_RL2	=	0x00c8
                    00C9    254 _C_T2	=	0x00c9
                    00CA    255 _TR2	=	0x00ca
                    00CB    256 _EXEN2	=	0x00cb
                    00CC    257 _TCLK	=	0x00cc
                    00CD    258 _RCLK	=	0x00cd
                    00CE    259 _EXF2	=	0x00ce
                    00CF    260 _TF2	=	0x00cf
                            261 ;--------------------------------------------------------
                            262 ; overlayable register banks 
                            263 ;--------------------------------------------------------
                            264 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     265 	.ds 8
                            266 ;--------------------------------------------------------
                            267 ; internal ram data
                            268 ;--------------------------------------------------------
                            269 	.area DSEG    (DATA)
   0008                     270 _ucStackBytes:
   0008                     271 	.ds 1
   0009                     272 _pxXRAMStack:
   0009                     273 	.ds 2
   000B                     274 _pxRAMStack:
   000B                     275 	.ds 1
                            276 ;--------------------------------------------------------
                            277 ; overlayable items in internal ram 
                            278 ;--------------------------------------------------------
                            279 	.area OSEG    (OVR,DATA)
                            280 ;--------------------------------------------------------
                            281 ; indirectly addressable internal ram data
                            282 ;--------------------------------------------------------
                            283 	.area ISEG    (DATA)
                            284 ;--------------------------------------------------------
                            285 ; bit data
                            286 ;--------------------------------------------------------
                            287 	.area BSEG    (BIT)
                            288 ;--------------------------------------------------------
                            289 ; paged external ram data
                            290 ;--------------------------------------------------------
                            291 	.area PSEG    (PAG,XDATA)
                            292 ;--------------------------------------------------------
                            293 ; external ram data
                            294 ;--------------------------------------------------------
                            295 	.area XSEG    (XDATA)
                            296 ;--------------------------------------------------------
                            297 ; external initialized ram data
                            298 ;--------------------------------------------------------
                            299 	.area XISEG   (XDATA)
                            300 	.area CSEG    (CODE)
                            301 	.area GSINIT0 (CODE)
                            302 	.area GSINIT1 (CODE)
                            303 	.area GSINIT2 (CODE)
                            304 	.area GSINIT3 (CODE)
                            305 	.area GSINIT4 (CODE)
                            306 	.area GSINIT5 (CODE)
                            307 ;--------------------------------------------------------
                            308 ; global & static initialisations
                            309 ;--------------------------------------------------------
                            310 	.area CSEG    (CODE)
                            311 	.area GSINIT  (CODE)
                            312 	.area GSFINAL (CODE)
                            313 	.area GSINIT  (CODE)
                            314 ;--------------------------------------------------------
                            315 ; Home
                            316 ;--------------------------------------------------------
                            317 	.area HOME    (CODE)
                            318 	.area CSEG    (CODE)
                            319 ;--------------------------------------------------------
                            320 ; code
                            321 ;--------------------------------------------------------
                            322 	.area CSEG    (CODE)
                            323 ;------------------------------------------------------------
                            324 ;Allocation info for local variables in function 'pxPortInitialiseStack'
                            325 ;------------------------------------------------------------
                            326 ;pxCode                    Allocated to stack - offset -4
                            327 ;pvParameters              Allocated to stack - offset -7
                            328 ;pxTopOfStack              Allocated to stack - offset 1
                            329 ;ulAddress                 Allocated to registers r5 r6 r7 r2 
                            330 ;pxStartOfStack            Allocated to stack - offset 4
                            331 ;------------------------------------------------------------
                            332 ;../../Source/portable/SDCC/ASIX/port.c:221: portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters )
                            333 ;	-----------------------------------------
                            334 ;	 function pxPortInitialiseStack
                            335 ;	-----------------------------------------
   141B                     336 _pxPortInitialiseStack:
                    0002    337 	ar2 = 0x02
                    0003    338 	ar3 = 0x03
                    0004    339 	ar4 = 0x04
                    0005    340 	ar5 = 0x05
                    0006    341 	ar6 = 0x06
                    0007    342 	ar7 = 0x07
                    0000    343 	ar0 = 0x00
                    0001    344 	ar1 = 0x01
   141B C0 12               345 	push	_bp
   141D 85 81 12            346 	mov	_bp,sp
                            347 ;     genReceive
   1420 C0 82               348 	push	dpl
   1422 C0 83               349 	push	dph
   1424 C0 F0               350 	push	b
   1426 05 81               351 	inc	sp
   1428 05 81               352 	inc	sp
   142A 05 81               353 	inc	sp
                            354 ;../../Source/portable/SDCC/ASIX/port.c:227: pxStartOfStack = pxTopOfStack;
                            355 ;     genAssign
   142C E5 12               356 	mov	a,_bp
   142E 24 01               357 	add	a,#0x01
   1430 F8                  358 	mov	r0,a
   1431 E5 12               359 	mov	a,_bp
   1433 24 04               360 	add	a,#0x04
   1435 F9                  361 	mov	r1,a
   1436 E6                  362 	mov	a,@r0
   1437 F7                  363 	mov	@r1,a
   1438 08                  364 	inc	r0
   1439 09                  365 	inc	r1
   143A E6                  366 	mov	a,@r0
   143B F7                  367 	mov	@r1,a
   143C 08                  368 	inc	r0
   143D 09                  369 	inc	r1
   143E E6                  370 	mov	a,@r0
   143F F7                  371 	mov	@r1,a
                            372 ;../../Source/portable/SDCC/ASIX/port.c:228: pxTopOfStack++;
                            373 ;     genPlus
   1440 E5 12               374 	mov	a,_bp
   1442 24 01               375 	add	a,#0x01
   1444 F8                  376 	mov	r0,a
                            377 ;     genPlusIncr
   1445 74 01               378 	mov	a,#0x01
   1447 26                  379 	add	a,@r0
   1448 F6                  380 	mov	@r0,a
   1449 74 00               381 	mov	a,#0x00
   144B 08                  382 	inc	r0
   144C 36                  383 	addc	a,@r0
   144D F6                  384 	mov	@r0,a
                            385 ;../../Source/portable/SDCC/ASIX/port.c:244: ulAddress = ( unsigned portLONG ) pxCode;
                            386 ;     genCast
   144E E5 12               387 	mov	a,_bp
   1450 24 FC               388 	add	a,#0xfc
   1452 F8                  389 	mov	r0,a
   1453 86 05               390 	mov	ar5,@r0
   1455 08                  391 	inc	r0
   1456 86 06               392 	mov	ar6,@r0
   1458 7F 00               393 	mov	r7,#0x00
   145A 7A 00               394 	mov	r2,#0x00
                            395 ;../../Source/portable/SDCC/ASIX/port.c:245: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;
                            396 ;     genCast
   145C 8D 03               397 	mov	ar3,r5
                            398 ;     genPointerSet
                            399 ;     genGenPointerSet
   145E E5 12               400 	mov	a,_bp
   1460 24 01               401 	add	a,#0x01
   1462 F8                  402 	mov	r0,a
   1463 86 82               403 	mov	dpl,@r0
   1465 08                  404 	inc	r0
   1466 86 83               405 	mov	dph,@r0
   1468 08                  406 	inc	r0
   1469 86 F0               407 	mov	b,@r0
   146B EB                  408 	mov	a,r3
   146C 12 A3 97            409 	lcall	__gptrput
   146F A3                  410 	inc	dptr
   1470 18                  411 	dec	r0
   1471 18                  412 	dec	r0
   1472 A6 82               413 	mov	@r0,dpl
   1474 08                  414 	inc	r0
   1475 A6 83               415 	mov	@r0,dph
                            416 ;../../Source/portable/SDCC/ASIX/port.c:246: ulAddress >>= 8;
                            417 ;     genRightShift
                            418 ;     genRightShiftLiteral
                            419 ;     genrshFour
   1477 8E 05               420 	mov	ar5,r6
   1479 8F 06               421 	mov	ar6,r7
   147B 8A 07               422 	mov	ar7,r2
   147D 7A 00               423 	mov	r2,#0x00
                            424 ;../../Source/portable/SDCC/ASIX/port.c:247: pxTopOfStack++;
                            425 ;../../Source/portable/SDCC/ASIX/port.c:248: *pxTopOfStack = ( portSTACK_TYPE ) ( ulAddress );
                            426 ;     genCast
   147F 8D 03               427 	mov	ar3,r5
                            428 ;     genPointerSet
                            429 ;     genGenPointerSet
   1481 E5 12               430 	mov	a,_bp
   1483 24 01               431 	add	a,#0x01
   1485 F8                  432 	mov	r0,a
   1486 86 82               433 	mov	dpl,@r0
   1488 08                  434 	inc	r0
   1489 86 83               435 	mov	dph,@r0
   148B 08                  436 	inc	r0
   148C 86 F0               437 	mov	b,@r0
   148E EB                  438 	mov	a,r3
   148F 12 A3 97            439 	lcall	__gptrput
   1492 A3                  440 	inc	dptr
   1493 18                  441 	dec	r0
   1494 18                  442 	dec	r0
   1495 A6 82               443 	mov	@r0,dpl
   1497 08                  444 	inc	r0
   1498 A6 83               445 	mov	@r0,dph
                            446 ;../../Source/portable/SDCC/ASIX/port.c:249: pxTopOfStack++;
                            447 ;../../Source/portable/SDCC/ASIX/port.c:252: *pxTopOfStack = 0xaa;	/* acc */
                            448 ;     genPointerSet
                            449 ;     genGenPointerSet
   149A E5 12               450 	mov	a,_bp
   149C 24 01               451 	add	a,#0x01
   149E F8                  452 	mov	r0,a
   149F 86 82               453 	mov	dpl,@r0
   14A1 08                  454 	inc	r0
   14A2 86 83               455 	mov	dph,@r0
   14A4 08                  456 	inc	r0
   14A5 86 F0               457 	mov	b,@r0
   14A7 74 AA               458 	mov	a,#0xAA
   14A9 12 A3 97            459 	lcall	__gptrput
   14AC A3                  460 	inc	dptr
   14AD 18                  461 	dec	r0
   14AE 18                  462 	dec	r0
   14AF A6 82               463 	mov	@r0,dpl
   14B1 08                  464 	inc	r0
   14B2 A6 83               465 	mov	@r0,dph
                            466 ;../../Source/portable/SDCC/ASIX/port.c:253: pxTopOfStack++;	
                            467 ;../../Source/portable/SDCC/ASIX/port.c:256: *pxTopOfStack = portGLOBAL_INTERRUPT_BIT;
                            468 ;     genPointerSet
                            469 ;     genGenPointerSet
   14B4 E5 12               470 	mov	a,_bp
   14B6 24 01               471 	add	a,#0x01
   14B8 F8                  472 	mov	r0,a
   14B9 86 82               473 	mov	dpl,@r0
   14BB 08                  474 	inc	r0
   14BC 86 83               475 	mov	dph,@r0
   14BE 08                  476 	inc	r0
   14BF 86 F0               477 	mov	b,@r0
   14C1 74 80               478 	mov	a,#0x80
   14C3 12 A3 97            479 	lcall	__gptrput
   14C6 A3                  480 	inc	dptr
   14C7 18                  481 	dec	r0
   14C8 18                  482 	dec	r0
   14C9 A6 82               483 	mov	@r0,dpl
   14CB 08                  484 	inc	r0
   14CC A6 83               485 	mov	@r0,dph
                            486 ;../../Source/portable/SDCC/ASIX/port.c:257: pxTopOfStack++;
                            487 ;../../Source/portable/SDCC/ASIX/port.c:261: ulAddress = ( unsigned portLONG ) pvParameters;
                            488 ;     genCast
   14CE E5 12               489 	mov	a,_bp
   14D0 24 F9               490 	add	a,#0xf9
   14D2 F8                  491 	mov	r0,a
   14D3 86 05               492 	mov	ar5,@r0
   14D5 08                  493 	inc	r0
   14D6 86 06               494 	mov	ar6,@r0
   14D8 08                  495 	inc	r0
   14D9 86 07               496 	mov	ar7,@r0
   14DB 7A 00               497 	mov	r2,#0x00
                            498 ;../../Source/portable/SDCC/ASIX/port.c:262: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;	/* DPL */
                            499 ;     genCast
   14DD 8D 03               500 	mov	ar3,r5
                            501 ;     genPointerSet
                            502 ;     genGenPointerSet
   14DF E5 12               503 	mov	a,_bp
   14E1 24 01               504 	add	a,#0x01
   14E3 F8                  505 	mov	r0,a
   14E4 86 82               506 	mov	dpl,@r0
   14E6 08                  507 	inc	r0
   14E7 86 83               508 	mov	dph,@r0
   14E9 08                  509 	inc	r0
   14EA 86 F0               510 	mov	b,@r0
   14EC EB                  511 	mov	a,r3
   14ED 12 A3 97            512 	lcall	__gptrput
   14F0 A3                  513 	inc	dptr
   14F1 18                  514 	dec	r0
   14F2 18                  515 	dec	r0
   14F3 A6 82               516 	mov	@r0,dpl
   14F5 08                  517 	inc	r0
   14F6 A6 83               518 	mov	@r0,dph
                            519 ;../../Source/portable/SDCC/ASIX/port.c:263: ulAddress >>= 8;
                            520 ;     genRightShift
                            521 ;     genRightShiftLiteral
                            522 ;     genrshFour
   14F8 8E 05               523 	mov	ar5,r6
   14FA 8F 06               524 	mov	ar6,r7
   14FC 8A 07               525 	mov	ar7,r2
   14FE 7A 00               526 	mov	r2,#0x00
                            527 ;../../Source/portable/SDCC/ASIX/port.c:264: *pxTopOfStack++;
                            528 ;../../Source/portable/SDCC/ASIX/port.c:265: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;	/* DPH */
                            529 ;     genCast
   1500 8D 03               530 	mov	ar3,r5
                            531 ;     genPointerSet
                            532 ;     genGenPointerSet
   1502 E5 12               533 	mov	a,_bp
   1504 24 01               534 	add	a,#0x01
   1506 F8                  535 	mov	r0,a
   1507 86 82               536 	mov	dpl,@r0
   1509 08                  537 	inc	r0
   150A 86 83               538 	mov	dph,@r0
   150C 08                  539 	inc	r0
   150D 86 F0               540 	mov	b,@r0
   150F EB                  541 	mov	a,r3
   1510 12 A3 97            542 	lcall	__gptrput
   1513 A3                  543 	inc	dptr
   1514 18                  544 	dec	r0
   1515 18                  545 	dec	r0
   1516 A6 82               546 	mov	@r0,dpl
   1518 08                  547 	inc	r0
   1519 A6 83               548 	mov	@r0,dph
                            549 ;../../Source/portable/SDCC/ASIX/port.c:266: ulAddress >>= 8;
                            550 ;     genRightShift
                            551 ;     genRightShiftLiteral
                            552 ;     genrshFour
   151B 8E 05               553 	mov	ar5,r6
   151D 8F 06               554 	mov	ar6,r7
   151F 8A 07               555 	mov	ar7,r2
   1521 7A 00               556 	mov	r2,#0x00
                            557 ;../../Source/portable/SDCC/ASIX/port.c:267: pxTopOfStack++;
                            558 ;../../Source/portable/SDCC/ASIX/port.c:268: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;	/* b */
                            559 ;     genCast
                            560 ;     genPointerSet
                            561 ;     genGenPointerSet
   1523 E5 12               562 	mov	a,_bp
   1525 24 01               563 	add	a,#0x01
   1527 F8                  564 	mov	r0,a
   1528 86 82               565 	mov	dpl,@r0
   152A 08                  566 	inc	r0
   152B 86 83               567 	mov	dph,@r0
   152D 08                  568 	inc	r0
   152E 86 F0               569 	mov	b,@r0
   1530 ED                  570 	mov	a,r5
   1531 12 A3 97            571 	lcall	__gptrput
   1534 A3                  572 	inc	dptr
   1535 18                  573 	dec	r0
   1536 18                  574 	dec	r0
   1537 A6 82               575 	mov	@r0,dpl
   1539 08                  576 	inc	r0
   153A A6 83               577 	mov	@r0,dph
                            578 ;../../Source/portable/SDCC/ASIX/port.c:269: pxTopOfStack++;
                            579 ;../../Source/portable/SDCC/ASIX/port.c:272: *pxTopOfStack = 0x02;	/* R2 */
                            580 ;     genPointerSet
                            581 ;     genGenPointerSet
   153C E5 12               582 	mov	a,_bp
   153E 24 01               583 	add	a,#0x01
   1540 F8                  584 	mov	r0,a
   1541 86 82               585 	mov	dpl,@r0
   1543 08                  586 	inc	r0
   1544 86 83               587 	mov	dph,@r0
   1546 08                  588 	inc	r0
   1547 86 F0               589 	mov	b,@r0
   1549 74 02               590 	mov	a,#0x02
   154B 12 A3 97            591 	lcall	__gptrput
   154E A3                  592 	inc	dptr
   154F 18                  593 	dec	r0
   1550 18                  594 	dec	r0
   1551 A6 82               595 	mov	@r0,dpl
   1553 08                  596 	inc	r0
   1554 A6 83               597 	mov	@r0,dph
                            598 ;../../Source/portable/SDCC/ASIX/port.c:273: pxTopOfStack++;
                            599 ;../../Source/portable/SDCC/ASIX/port.c:274: *pxTopOfStack = 0x03;	/* R3 */
                            600 ;     genPointerSet
                            601 ;     genGenPointerSet
   1556 E5 12               602 	mov	a,_bp
   1558 24 01               603 	add	a,#0x01
   155A F8                  604 	mov	r0,a
   155B 86 82               605 	mov	dpl,@r0
   155D 08                  606 	inc	r0
   155E 86 83               607 	mov	dph,@r0
   1560 08                  608 	inc	r0
   1561 86 F0               609 	mov	b,@r0
   1563 74 03               610 	mov	a,#0x03
   1565 12 A3 97            611 	lcall	__gptrput
   1568 A3                  612 	inc	dptr
   1569 18                  613 	dec	r0
   156A 18                  614 	dec	r0
   156B A6 82               615 	mov	@r0,dpl
   156D 08                  616 	inc	r0
   156E A6 83               617 	mov	@r0,dph
                            618 ;../../Source/portable/SDCC/ASIX/port.c:275: pxTopOfStack++;
                            619 ;../../Source/portable/SDCC/ASIX/port.c:276: *pxTopOfStack = 0x04;	/* R4 */
                            620 ;     genPointerSet
                            621 ;     genGenPointerSet
   1570 E5 12               622 	mov	a,_bp
   1572 24 01               623 	add	a,#0x01
   1574 F8                  624 	mov	r0,a
   1575 86 82               625 	mov	dpl,@r0
   1577 08                  626 	inc	r0
   1578 86 83               627 	mov	dph,@r0
   157A 08                  628 	inc	r0
   157B 86 F0               629 	mov	b,@r0
   157D 74 04               630 	mov	a,#0x04
   157F 12 A3 97            631 	lcall	__gptrput
   1582 A3                  632 	inc	dptr
   1583 18                  633 	dec	r0
   1584 18                  634 	dec	r0
   1585 A6 82               635 	mov	@r0,dpl
   1587 08                  636 	inc	r0
   1588 A6 83               637 	mov	@r0,dph
                            638 ;../../Source/portable/SDCC/ASIX/port.c:277: pxTopOfStack++;
                            639 ;../../Source/portable/SDCC/ASIX/port.c:278: *pxTopOfStack = 0x05;	/* R5 */
                            640 ;     genPointerSet
                            641 ;     genGenPointerSet
   158A E5 12               642 	mov	a,_bp
   158C 24 01               643 	add	a,#0x01
   158E F8                  644 	mov	r0,a
   158F 86 82               645 	mov	dpl,@r0
   1591 08                  646 	inc	r0
   1592 86 83               647 	mov	dph,@r0
   1594 08                  648 	inc	r0
   1595 86 F0               649 	mov	b,@r0
   1597 74 05               650 	mov	a,#0x05
   1599 12 A3 97            651 	lcall	__gptrput
   159C A3                  652 	inc	dptr
   159D 18                  653 	dec	r0
   159E 18                  654 	dec	r0
   159F A6 82               655 	mov	@r0,dpl
   15A1 08                  656 	inc	r0
   15A2 A6 83               657 	mov	@r0,dph
                            658 ;../../Source/portable/SDCC/ASIX/port.c:279: pxTopOfStack++;
                            659 ;../../Source/portable/SDCC/ASIX/port.c:280: *pxTopOfStack = 0x06;	/* R6 */
                            660 ;     genPointerSet
                            661 ;     genGenPointerSet
   15A4 E5 12               662 	mov	a,_bp
   15A6 24 01               663 	add	a,#0x01
   15A8 F8                  664 	mov	r0,a
   15A9 86 82               665 	mov	dpl,@r0
   15AB 08                  666 	inc	r0
   15AC 86 83               667 	mov	dph,@r0
   15AE 08                  668 	inc	r0
   15AF 86 F0               669 	mov	b,@r0
   15B1 74 06               670 	mov	a,#0x06
   15B3 12 A3 97            671 	lcall	__gptrput
   15B6 A3                  672 	inc	dptr
   15B7 18                  673 	dec	r0
   15B8 18                  674 	dec	r0
   15B9 A6 82               675 	mov	@r0,dpl
   15BB 08                  676 	inc	r0
   15BC A6 83               677 	mov	@r0,dph
                            678 ;../../Source/portable/SDCC/ASIX/port.c:281: pxTopOfStack++;
                            679 ;../../Source/portable/SDCC/ASIX/port.c:282: *pxTopOfStack = 0x07;	/* R7 */
                            680 ;     genPointerSet
                            681 ;     genGenPointerSet
   15BE E5 12               682 	mov	a,_bp
   15C0 24 01               683 	add	a,#0x01
   15C2 F8                  684 	mov	r0,a
   15C3 86 82               685 	mov	dpl,@r0
   15C5 08                  686 	inc	r0
   15C6 86 83               687 	mov	dph,@r0
   15C8 08                  688 	inc	r0
   15C9 86 F0               689 	mov	b,@r0
   15CB 74 07               690 	mov	a,#0x07
   15CD 12 A3 97            691 	lcall	__gptrput
   15D0 A3                  692 	inc	dptr
   15D1 18                  693 	dec	r0
   15D2 18                  694 	dec	r0
   15D3 A6 82               695 	mov	@r0,dpl
   15D5 08                  696 	inc	r0
   15D6 A6 83               697 	mov	@r0,dph
                            698 ;../../Source/portable/SDCC/ASIX/port.c:283: pxTopOfStack++;
                            699 ;../../Source/portable/SDCC/ASIX/port.c:284: *pxTopOfStack = 0x00;	/* R0 */
                            700 ;     genPointerSet
                            701 ;     genGenPointerSet
   15D8 E5 12               702 	mov	a,_bp
   15DA 24 01               703 	add	a,#0x01
   15DC F8                  704 	mov	r0,a
   15DD 86 82               705 	mov	dpl,@r0
   15DF 08                  706 	inc	r0
   15E0 86 83               707 	mov	dph,@r0
   15E2 08                  708 	inc	r0
   15E3 86 F0               709 	mov	b,@r0
   15E5 74 00               710 	mov	a,#0x00
   15E7 12 A3 97            711 	lcall	__gptrput
   15EA A3                  712 	inc	dptr
   15EB 18                  713 	dec	r0
   15EC 18                  714 	dec	r0
   15ED A6 82               715 	mov	@r0,dpl
   15EF 08                  716 	inc	r0
   15F0 A6 83               717 	mov	@r0,dph
                            718 ;../../Source/portable/SDCC/ASIX/port.c:285: pxTopOfStack++;
                            719 ;../../Source/portable/SDCC/ASIX/port.c:286: *pxTopOfStack = 0x01;	/* R1 */
                            720 ;     genPointerSet
                            721 ;     genGenPointerSet
   15F2 E5 12               722 	mov	a,_bp
   15F4 24 01               723 	add	a,#0x01
   15F6 F8                  724 	mov	r0,a
   15F7 86 82               725 	mov	dpl,@r0
   15F9 08                  726 	inc	r0
   15FA 86 83               727 	mov	dph,@r0
   15FC 08                  728 	inc	r0
   15FD 86 F0               729 	mov	b,@r0
   15FF 74 01               730 	mov	a,#0x01
   1601 12 A3 97            731 	lcall	__gptrput
   1604 A3                  732 	inc	dptr
   1605 18                  733 	dec	r0
   1606 18                  734 	dec	r0
   1607 A6 82               735 	mov	@r0,dpl
   1609 08                  736 	inc	r0
   160A A6 83               737 	mov	@r0,dph
                            738 ;../../Source/portable/SDCC/ASIX/port.c:287: pxTopOfStack++;
                            739 ;../../Source/portable/SDCC/ASIX/port.c:288: *pxTopOfStack = 0x00;	/* PSW */
                            740 ;     genPointerSet
                            741 ;     genGenPointerSet
   160C E5 12               742 	mov	a,_bp
   160E 24 01               743 	add	a,#0x01
   1610 F8                  744 	mov	r0,a
   1611 86 82               745 	mov	dpl,@r0
   1613 08                  746 	inc	r0
   1614 86 83               747 	mov	dph,@r0
   1616 08                  748 	inc	r0
   1617 86 F0               749 	mov	b,@r0
   1619 74 00               750 	mov	a,#0x00
   161B 12 A3 97            751 	lcall	__gptrput
   161E A3                  752 	inc	dptr
   161F 18                  753 	dec	r0
   1620 18                  754 	dec	r0
   1621 A6 82               755 	mov	@r0,dpl
   1623 08                  756 	inc	r0
   1624 A6 83               757 	mov	@r0,dph
                            758 ;../../Source/portable/SDCC/ASIX/port.c:289: pxTopOfStack++;
                            759 ;../../Source/portable/SDCC/ASIX/port.c:290: *pxTopOfStack = 0xbb;	/* BP */
                            760 ;     genPointerSet
                            761 ;     genGenPointerSet
   1626 E5 12               762 	mov	a,_bp
   1628 24 01               763 	add	a,#0x01
   162A F8                  764 	mov	r0,a
   162B 86 82               765 	mov	dpl,@r0
   162D 08                  766 	inc	r0
   162E 86 83               767 	mov	dph,@r0
   1630 08                  768 	inc	r0
   1631 86 F0               769 	mov	b,@r0
   1633 74 BB               770 	mov	a,#0xBB
   1635 12 A3 97            771 	lcall	__gptrput
                            772 ;../../Source/portable/SDCC/ASIX/port.c:296: *pxStartOfStack = ( portSTACK_TYPE ) ( pxTopOfStack - pxStartOfStack );
                            773 ;     genMinus
   1638 E5 12               774 	mov	a,_bp
   163A 24 01               775 	add	a,#0x01
   163C F8                  776 	mov	r0,a
   163D E5 12               777 	mov	a,_bp
   163F 24 04               778 	add	a,#0x04
   1641 F9                  779 	mov	r1,a
   1642 E6                  780 	mov	a,@r0
   1643 C3                  781 	clr	c
   1644 97                  782 	subb	a,@r1
   1645 FA                  783 	mov	r2,a
   1646 08                  784 	inc	r0
   1647 E6                  785 	mov	a,@r0
   1648 09                  786 	inc	r1
   1649 97                  787 	subb	a,@r1
   164A FB                  788 	mov	r3,a
                            789 ;     genCast
                            790 ;     genPointerSet
                            791 ;     genGenPointerSet
   164B E5 12               792 	mov	a,_bp
   164D 24 04               793 	add	a,#0x04
   164F F8                  794 	mov	r0,a
   1650 86 82               795 	mov	dpl,@r0
   1652 08                  796 	inc	r0
   1653 86 83               797 	mov	dph,@r0
   1655 08                  798 	inc	r0
   1656 86 F0               799 	mov	b,@r0
   1658 EA                  800 	mov	a,r2
   1659 12 A3 97            801 	lcall	__gptrput
                            802 ;../../Source/portable/SDCC/ASIX/port.c:300: return pxStartOfStack;
                            803 ;     genRet
   165C E5 12               804 	mov	a,_bp
   165E 24 04               805 	add	a,#0x04
   1660 F8                  806 	mov	r0,a
   1661 86 82               807 	mov	dpl,@r0
   1663 08                  808 	inc	r0
   1664 86 83               809 	mov	dph,@r0
   1666 08                  810 	inc	r0
   1667 86 F0               811 	mov	b,@r0
   1669                     812 00101$:
   1669 85 12 81            813 	mov	sp,_bp
   166C D0 12               814 	pop	_bp
   166E 22                  815 	ret
                            816 ;------------------------------------------------------------
                            817 ;Allocation info for local variables in function 'sPortStartScheduler'
                            818 ;------------------------------------------------------------
                            819 ;sUsePreemption            Allocated to registers 
                            820 ;------------------------------------------------------------
                            821 ;../../Source/portable/SDCC/ASIX/port.c:307: portSHORT sPortStartScheduler( portSHORT sUsePreemption )
                            822 ;	-----------------------------------------
                            823 ;	 function sPortStartScheduler
                            824 ;	-----------------------------------------
   166F                     825 _sPortStartScheduler:
   166F C0 12               826 	push	_bp
   1671 85 81 12            827 	mov	_bp,sp
                            828 ;../../Source/portable/SDCC/ASIX/port.c:314: prvSetupTimerInterrupt();	
                            829 ;     genCall
   1674 12 18 D9            830 	lcall	_prvSetupTimerInterrupt
                            831 ;../../Source/portable/SDCC/ASIX/port.c:319: portCOPY_XRAM_TO_STACK();
                            832 ;     genAssign
   1677 90 1D 0B            833 	mov	dptr,#_pxCurrentTCB
   167A E0                  834 	movx	a,@dptr
   167B FA                  835 	mov	r2,a
   167C A3                  836 	inc	dptr
   167D E0                  837 	movx	a,@dptr
   167E FB                  838 	mov	r3,a
   167F A3                  839 	inc	dptr
   1680 E0                  840 	movx	a,@dptr
   1681 FC                  841 	mov	r4,a
                            842 ;     genPointerGet
                            843 ;     genGenPointerGet
   1682 8A 82               844 	mov	dpl,r2
   1684 8B 83               845 	mov	dph,r3
   1686 8C F0               846 	mov	b,r4
   1688 12 AE 30            847 	lcall	__gptrget
   168B F5 09               848 	mov	_pxXRAMStack,a
   168D A3                  849 	inc	dptr
   168E 12 AE 30            850 	lcall	__gptrget
   1691 F5 0A               851 	mov	(_pxXRAMStack + 1),a
                            852 ;     genAssign
   1693 75 0B 21            853 	mov	_pxRAMStack,#0x21
                            854 ;     genAssign
   1696 85 09 82            855 	mov	dpl,_pxXRAMStack
   1699 85 0A 83            856 	mov	dph,(_pxXRAMStack + 1)
                            857 ;     genPointerGet
                            858 ;     genFarPointerGet
   169C E0                  859 	movx	a,@dptr
   169D F5 08               860 	mov	_ucStackBytes,a
   169F                     861 00101$:
                            862 ;     genPlus
                            863 ;     genPlusIncr
   169F 05 09               864 	inc	_pxXRAMStack
   16A1 E4                  865 	clr	a
   16A2 B5 09 02            866 	cjne	a,_pxXRAMStack,00108$
   16A5 05 0A               867 	inc	(_pxXRAMStack + 1)
   16A7                     868 00108$:
                            869 ;     genPlus
                            870 ;     genPlusIncr
   16A7 05 0B               871 	inc	_pxRAMStack
                            872 ;     genAssign
   16A9 A8 0B               873 	mov	r0,_pxRAMStack
                            874 ;     genAssign
   16AB 85 09 82            875 	mov	dpl,_pxXRAMStack
   16AE 85 0A 83            876 	mov	dph,(_pxXRAMStack + 1)
                            877 ;     genPointerGet
                            878 ;     genFarPointerGet
   16B1 E0                  879 	movx	a,@dptr
   16B2 FA                  880 	mov	r2,a
                            881 ;     genPointerSet
                            882 ;     genNearPointerSet
   16B3 A6 02               883 	mov	@r0,ar2
                            884 ;     genMinus
                            885 ;     genMinusDec
   16B5 15 08               886 	dec	_ucStackBytes
                            887 ;     genIfx
   16B7 E5 08               888 	mov	a,_ucStackBytes
                            889 ;     genIfxJump
   16B9 60 03               890 	jz	00109$
   16BB 02 16 9F            891 	ljmp	00101$
   16BE                     892 00109$:
                            893 ;     genCast
   16BE 85 0B 81            894 	mov	_SP,_pxRAMStack
                            895 ;../../Source/portable/SDCC/ASIX/port.c:320: portRESTORE_CONTEXT();
                            896 ;     genInline
   02A6                     897  pop _bp pop PSW pop ar1 pop ar0 pop ar7 pop ar6 pop ar5 pop ar4 pop ar3 pop ar2 pop b pop DPH pop DPL pop ACC JB ACC.7,0098$ CLR IE.7 LJMP 0099$ 0098$:
   02CA                     898 SETB IE.7 0099$:
   16C1 D0 12 D0            899 	pop ACC reti 
                            900 ;../../Source/portable/SDCC/ASIX/port.c:323: return pdTRUE;
                            901 ;     genRet
   16C4 D0 D0 01            902 	mov	dpl,#0x01
   16C7 D0 00 D0            903 	mov	dph,#0x00
   02D5                     904 00104$:
   16CA 07 D0 06            905 	mov	sp,_bp
   16CD D0 05               906 	pop	_bp
   16CF D0                  907 	ret
                            908 ;------------------------------------------------------------
                            909 ;Allocation info for local variables in function 'vPortEndScheduler'
                            910 ;------------------------------------------------------------
                            911 ;------------------------------------------------------------
                            912 ;../../Source/portable/SDCC/ASIX/port.c:327: void vPortEndScheduler( void )
                            913 ;	-----------------------------------------
                            914 ;	 function vPortEndScheduler
                            915 ;	-----------------------------------------
   02DB                     916 _vPortEndScheduler:
   16D0 04 D0               917 	push	_bp
   16D2 03 D0 02            918 	mov	_bp,sp
                            919 ;../../Source/portable/SDCC/ASIX/port.c:330: }
   02E0                     920 00101$:
   16D5 D0 F0 D0            921 	mov	sp,_bp
   16D8 83 D0               922 	pop	_bp
   16DA 82                  923 	ret
                            924 ;------------------------------------------------------------
                            925 ;Allocation info for local variables in function 'vPortYield'
                            926 ;------------------------------------------------------------
                            927 ;------------------------------------------------------------
                            928 ;../../Source/portable/SDCC/ASIX/port.c:337: void vPortYield( void ) _naked
                            929 ;	-----------------------------------------
                            930 ;	 function vPortYield
                            931 ;	-----------------------------------------
   02E6                     932 _vPortYield:
                            933 ;	naked function: no prologue.
                            934 ;../../Source/portable/SDCC/ASIX/port.c:345: portSAVE_CONTEXT();
                            935 ;     genInline
   16DB D0 E0 20 E7 05 C2   936 	 push ACC push IE clr _EA push DPL push DPH push b push ar2 push ar3 push ar4 push ar5 push ar6 push ar7 push ar0 push ar1 push PSW 
        AF 02 16 E7 C0 F0
        C0 02 C0 03 C0 04
        C0 05 C0 06 C0 07
        C0 00 C0 01 C0 D0
                            937 ;     genAssign
   16E5 75 D0 00            938 	mov	_PSW,#0x00
                            939 ;     genInline
   16E5 D2 AF               940 	 push _bp 
                            941 ;../../Source/portable/SDCC/ASIX/port.c:346: portCOPY_STACK_TO_XRAM();
                            942 ;     genAssign
   16E7 90s00r00            943 	mov	dptr,#_pxCurrentTCB
   16E7 D0                  944 	movx	a,@dptr
   16E8 E0                  945 	mov	r2,a
   16E9 32                  946 	inc	dptr
   16EA 75                  947 	movx	a,@dptr
   16EB 82                  948 	mov	r3,a
   16EC 01                  949 	inc	dptr
   16ED 75                  950 	movx	a,@dptr
   16EE 83                  951 	mov	r4,a
                            952 ;     genPointerGet
                            953 ;     genGenPointerGet
   16EF 00 82               954 	mov	dpl,r2
   16F0 8B 83               955 	mov	dph,r3
   16F0 85 12               956 	mov	b,r4
   16F2 81 D0 12            957 	lcall	__gptrget
   16F5 22*01               958 	mov	_pxXRAMStack,a
   16F6 A3                  959 	inc	dptr
   16F6 C0 12 85            960 	lcall	__gptrget
   16F9 81 12               961 	mov	(_pxXRAMStack + 1),a
                            962 ;     genAssign
   16FB 75*03 22            963 	mov	_pxRAMStack,#0x22
                            964 ;     genMinus
   16FB 85 12               965 	mov	a,_SP
   16FD 81 D0               966 	add	a,#0xdf
   16FF 12 22               967 	mov	_ucStackBytes,a
                            968 ;     genAssign
   1701 85*01 82            969 	mov	dpl,_pxXRAMStack
   1701 C0 E0 C0            970 	mov	dph,(_pxXRAMStack + 1)
                            971 ;     genPointerSet
                            972 ;     genFarPointerSet
   1704 A8 C2               973 	mov	a,_ucStackBytes
   1706 AF                  974 	movx	@dptr,a
   0337                     975 00101$:
                            976 ;     genIfx
   1707 C0 82               977 	mov	a,_ucStackBytes
                            978 ;     genIfxJump
   1709 C0 83               979 	jnz	00113$
   170B C0 F0 C0            980 	ljmp	00103$
   033E                     981 00113$:
                            982 ;     genPlus
                            983 ;     genPlusIncr
   170E 02 C0               984 	inc	_pxXRAMStack
   1710 03                  985 	clr	a
   1711 C0 04 C0            986 	cjne	a,_pxXRAMStack,00114$
   1714 05 C0               987 	inc	(_pxXRAMStack + 1)
   0346                     988 00114$:
                            989 ;     genAssign
   1716 06 C0 07            990 	mov	dpl,_pxXRAMStack
   1719 C0 00 C0            991 	mov	dph,(_pxXRAMStack + 1)
                            992 ;     genAssign
   171C 01 C0               993 	mov	r0,_pxRAMStack
                            994 ;     genPointerGet
                            995 ;     genNearPointerGet
   171E D0 75               996 	mov	ar2,@r0
                            997 ;     genPointerSet
                            998 ;     genFarPointerSet
   1720 D0                  999 	mov	a,r2
   1721 00                 1000 	movx	@dptr,a
                           1001 ;     genPlus
                           1002 ;     genPlusIncr
   1722 C0 12              1003 	inc	_pxRAMStack
                           1004 ;     genMinus
                           1005 ;     genMinusDec
   1724 90 1D              1006 	dec	_ucStackBytes
   1726 0B E0 FA           1007 	ljmp	00101$
   0359                    1008 00103$:
                           1009 ;../../Source/portable/SDCC/ASIX/port.c:349: vTaskSwitchContext();
                           1010 ;     genCall
   1729 A3 E0 FB           1011 	lcall	_vTaskSwitchContext
                           1012 ;../../Source/portable/SDCC/ASIX/port.c:353: portCOPY_XRAM_TO_STACK();
                           1013 ;     genAssign
   172C A3 E0 FC           1014 	mov	dptr,#_pxCurrentTCB
   172F 8A                 1015 	movx	a,@dptr
   1730 82                 1016 	mov	r2,a
   1731 8B                 1017 	inc	dptr
   1732 83                 1018 	movx	a,@dptr
   1733 8C                 1019 	mov	r3,a
   1734 F0                 1020 	inc	dptr
   1735 12                 1021 	movx	a,@dptr
   1736 AE                 1022 	mov	r4,a
                           1023 ;     genPointerGet
                           1024 ;     genGenPointerGet
   1737 30 F5              1025 	mov	dpl,r2
   1739 09 A3              1026 	mov	dph,r3
   173B 12 AE              1027 	mov	b,r4
   173D 30 F5 0A           1028 	lcall	__gptrget
   1740 75 0B              1029 	mov	_pxXRAMStack,a
   1742 22                 1030 	inc	dptr
   1743 E5 81 24           1031 	lcall	__gptrget
   1746 DF F5              1032 	mov	(_pxXRAMStack + 1),a
                           1033 ;     genAssign
   1748 08 85 09           1034 	mov	_pxRAMStack,#0x21
                           1035 ;     genAssign
   174B 82 85 0A           1036 	mov	dpl,_pxXRAMStack
   174E 83 E5 08           1037 	mov	dph,(_pxXRAMStack + 1)
                           1038 ;     genPointerGet
                           1039 ;     genFarPointerGet
   1751 F0                 1040 	movx	a,@dptr
   1752 F5*00              1041 	mov	_ucStackBytes,a
   0384                    1042 00104$:
                           1043 ;     genPlus
                           1044 ;     genPlusIncr
   1752 E5 08              1045 	inc	_pxXRAMStack
   1754 70                 1046 	clr	a
   1755 03 02 17           1047 	cjne	a,_pxXRAMStack,00115$
   1758 74*02              1048 	inc	(_pxXRAMStack + 1)
   1759                    1049 00115$:
                           1050 ;     genPlus
                           1051 ;     genPlusIncr
   1759 05 09              1052 	inc	_pxRAMStack
                           1053 ;     genAssign
   175B E4 B5              1054 	mov	r0,_pxRAMStack
                           1055 ;     genAssign
   175D 09 02 05           1056 	mov	dpl,_pxXRAMStack
   1760 0A*02 83           1057 	mov	dph,(_pxXRAMStack + 1)
                           1058 ;     genPointerGet
                           1059 ;     genFarPointerGet
   1761 E0                 1060 	movx	a,@dptr
   1761 85                 1061 	mov	r2,a
                           1062 ;     genPointerSet
                           1063 ;     genNearPointerSet
   1762 09 82              1064 	mov	@r0,ar2
                           1065 ;     genMinus
                           1066 ;     genMinusDec
   1764 85 0A              1067 	dec	_ucStackBytes
                           1068 ;     genIfx
   1766 83 A8              1069 	mov	a,_ucStackBytes
                           1070 ;     genIfxJump
   1768 0B 86              1071 	jz	00116$
   176A 02 EA F0           1072 	ljmp	00104$
   03A3                    1073 00116$:
                           1074 ;     genCast
   176D 05 0B 15           1075 	mov	_SP,_pxRAMStack
                           1076 ;../../Source/portable/SDCC/ASIX/port.c:354: portRESTORE_CONTEXT();
                           1077 ;     genInline
   03A6                    1078  pop _bp pop PSW pop ar1 pop ar0 pop ar7 pop ar6 pop ar5 pop ar4 pop ar3 pop ar2 pop b pop DPH pop DPL pop ACC JB ACC.7,0098$ CLR IE.7 LJMP 0099$ 0098$:
   03CA                    1079 SETB IE.7 0099$:
   1770 08 02 17           1080 	pop ACC reti 
   03CF                    1081 00107$:
                           1082 ;	naked function: no epilogue.
                           1083 ;------------------------------------------------------------
                           1084 ;Allocation info for local variables in function 'vTimer2ISR'
                           1085 ;------------------------------------------------------------
                           1086 ;------------------------------------------------------------
                           1087 ;../../Source/portable/SDCC/ASIX/port.c:359: void vTimer2ISR( void ) interrupt 5 _naked
                           1088 ;	-----------------------------------------
                           1089 ;	 function vTimer2ISR
                           1090 ;	-----------------------------------------
   03CF                    1091 _vTimer2ISR:
                           1092 ;	naked function: no prologue.
                           1093 ;../../Source/portable/SDCC/ASIX/port.c:365: portSAVE_CONTEXT();
                           1094 ;     genInline
   1773 52 E0 C0 A8 C2 AF  1095 	 push ACC push IE clr _EA push DPL push DPH push b push ar2 push ar3 push ar4 push ar5 push ar6 push ar7 push ar0 push ar1 push PSW 
        C0 82 C0 83 C0 F0
        C0 02 C0 03 C0 04
        C0 05 C0 06 C0 07
        C0 00 C0 01 C0 D0
                           1096 ;     genAssign
   1774 75 D0 00           1097 	mov	_PSW,#0x00
                           1098 ;     genInline
   1774 12 0B              1099 	 push _bp 
                           1100 ;../../Source/portable/SDCC/ASIX/port.c:366: portCOPY_STACK_TO_XRAM();
                           1101 ;     genAssign
   1776 82 90 1D           1102 	mov	dptr,#_pxCurrentTCB
   1779 0B                 1103 	movx	a,@dptr
   177A E0                 1104 	mov	r2,a
   177B FA                 1105 	inc	dptr
   177C A3                 1106 	movx	a,@dptr
   177D E0                 1107 	mov	r3,a
   177E FB                 1108 	inc	dptr
   177F A3                 1109 	movx	a,@dptr
   1780 E0                 1110 	mov	r4,a
                           1111 ;     genPointerGet
                           1112 ;     genGenPointerGet
   1781 FC 8A              1113 	mov	dpl,r2
   1783 82 8B              1114 	mov	dph,r3
   1785 83 8C              1115 	mov	b,r4
   1787 F0 12 AE           1116 	lcall	__gptrget
   178A 30 F5              1117 	mov	_pxXRAMStack,a
   178C 09                 1118 	inc	dptr
   178D A3 12 AE           1119 	lcall	__gptrget
   1790 30 F5              1120 	mov	(_pxXRAMStack + 1),a
                           1121 ;     genAssign
   1792 0A 75 0B           1122 	mov	_pxRAMStack,#0x22
                           1123 ;     genMinus
   1795 21 85              1124 	mov	a,_SP
   1797 09 82              1125 	add	a,#0xdf
   1799 85 0A              1126 	mov	_ucStackBytes,a
                           1127 ;     genAssign
   179B 83 E0 F5           1128 	mov	dpl,_pxXRAMStack
   179E 08*02 83           1129 	mov	dph,(_pxXRAMStack + 1)
                           1130 ;     genPointerSet
                           1131 ;     genFarPointerSet
   179F E5*00              1132 	mov	a,_ucStackBytes
   179F 05                 1133 	movx	@dptr,a
   0420                    1134 00101$:
                           1135 ;     genIfx
   17A0 09 E4              1136 	mov	a,_ucStackBytes
                           1137 ;     genIfxJump
   17A2 B5 09              1138 	jnz	00113$
   17A4 02 05 0A           1139 	ljmp	00103$
   17A7                    1140 00113$:
                           1141 ;     genPlus
                           1142 ;     genPlusIncr
   17A7 05 0B              1143 	inc	_pxXRAMStack
   17A9 A8                 1144 	clr	a
   17AA 0B 85 09           1145 	cjne	a,_pxXRAMStack,00114$
   17AD 82 85              1146 	inc	(_pxXRAMStack + 1)
   042F                    1147 00114$:
                           1148 ;     genAssign
   17AF 0A 83 E0           1149 	mov	dpl,_pxXRAMStack
   17B2 FA A6 02           1150 	mov	dph,(_pxXRAMStack + 1)
                           1151 ;     genAssign
   17B5 15 08              1152 	mov	r0,_pxRAMStack
                           1153 ;     genPointerGet
                           1154 ;     genNearPointerGet
   17B7 E5 08              1155 	mov	ar2,@r0
                           1156 ;     genPointerSet
                           1157 ;     genFarPointerSet
   17B9 60                 1158 	mov	a,r2
   17BA 03                 1159 	movx	@dptr,a
                           1160 ;     genPlus
                           1161 ;     genPlusIncr
   17BB 02 17              1162 	inc	_pxRAMStack
                           1163 ;     genMinus
                           1164 ;     genMinusDec
   17BD 9F*00              1165 	dec	_ucStackBytes
   17BE 02s04r20           1166 	ljmp	00101$
   0442                    1167 00103$:
                           1168 ;../../Source/portable/SDCC/ASIX/port.c:368: vTaskIncrementTick();
                           1169 ;     genCall
   17BE 85 0B 81           1170 	lcall	_vTaskIncrementTick
                           1171 ;../../Source/portable/SDCC/ASIX/port.c:369: vTaskSwitchContext();
                           1172 ;     genCall
   17C1 D0 12 D0           1173 	lcall	_vTaskSwitchContext
                           1174 ;../../Source/portable/SDCC/ASIX/port.c:371: portCLEAR_INTERRUPT_FLAG();
                           1175 ;     genAnd
   17C4 D0 D0 01           1176 	anl	_T2CON,#0x7F
                           1177 ;../../Source/portable/SDCC/ASIX/port.c:372: portCOPY_XRAM_TO_STACK();
                           1178 ;     genAssign
   17C7 D0 00 D0           1179 	mov	dptr,#_pxCurrentTCB
   17CA 07                 1180 	movx	a,@dptr
   17CB D0                 1181 	mov	r2,a
   17CC 06                 1182 	inc	dptr
   17CD D0                 1183 	movx	a,@dptr
   17CE 05                 1184 	mov	r3,a
   17CF D0                 1185 	inc	dptr
   17D0 04                 1186 	movx	a,@dptr
   17D1 D0                 1187 	mov	r4,a
                           1188 ;     genPointerGet
                           1189 ;     genGenPointerGet
   17D2 03 D0              1190 	mov	dpl,r2
   17D4 02 D0              1191 	mov	dph,r3
   17D6 F0 D0              1192 	mov	b,r4
   17D8 83 D0 82           1193 	lcall	__gptrget
   17DB D0 E0              1194 	mov	_pxXRAMStack,a
   17DD 20                 1195 	inc	dptr
   17DE E7 05 C2           1196 	lcall	__gptrget
   17E1 AF 02              1197 	mov	(_pxXRAMStack + 1),a
                           1198 ;     genAssign
   17E3 17 E7 21           1199 	mov	_pxRAMStack,#0x21
                           1200 ;     genAssign
   17E5 85*01 82           1201 	mov	dpl,_pxXRAMStack
   17E5 D2 AF 83           1202 	mov	dph,(_pxXRAMStack + 1)
                           1203 ;     genPointerGet
                           1204 ;     genFarPointerGet
   17E7 E0                 1205 	movx	a,@dptr
   17E7 D0 E0              1206 	mov	_ucStackBytes,a
   0473                    1207 00104$:
                           1208 ;     genPlus
                           1209 ;     genPlusIncr
   17E9 32*01              1210 	inc	_pxXRAMStack
   17EA E4                 1211 	clr	a
   17EA B5*01 02           1212 	cjne	a,_pxXRAMStack,00115$
   17EA C0 E0              1213 	inc	(_pxXRAMStack + 1)
   047B                    1214 00115$:
                           1215 ;     genPlus
                           1216 ;     genPlusIncr
   17EC C0 A8              1217 	inc	_pxRAMStack
                           1218 ;     genAssign
   17EE C2 AF              1219 	mov	r0,_pxRAMStack
                           1220 ;     genAssign
   17F0 C0 82 C0           1221 	mov	dpl,_pxXRAMStack
   17F3 83 C0 F0           1222 	mov	dph,(_pxXRAMStack + 1)
                           1223 ;     genPointerGet
                           1224 ;     genFarPointerGet
   17F6 C0                 1225 	movx	a,@dptr
   17F7 02                 1226 	mov	r2,a
                           1227 ;     genPointerSet
                           1228 ;     genNearPointerSet
   17F8 C0 03              1229 	mov	@r0,ar2
                           1230 ;     genMinus
                           1231 ;     genMinusDec
   17FA C0 04              1232 	dec	_ucStackBytes
                           1233 ;     genIfx
   17FC C0 05              1234 	mov	a,_ucStackBytes
                           1235 ;     genIfxJump
   17FE C0 06              1236 	jz	00116$
   1800 C0 07 C0           1237 	ljmp	00104$
   0492                    1238 00116$:
                           1239 ;     genCast
   1803 00 C0 01           1240 	mov	_SP,_pxRAMStack
                           1241 ;../../Source/portable/SDCC/ASIX/port.c:373: portRESTORE_CONTEXT();
                           1242 ;     genInline
   0495                    1243  pop _bp pop PSW pop ar1 pop ar0 pop ar7 pop ar6 pop ar5 pop ar4 pop ar3 pop ar2 pop b pop DPH pop DPL pop ACC JB ACC.7,0098$ CLR IE.7 LJMP 0099$ 0098$:
   04B9                    1244 SETB IE.7 0099$:
   1806 C0 D0 75           1245 	pop ACC reti 
   04BE                    1246 00107$:
                           1247 ;	naked function: no epilogue.
                           1248 ;------------------------------------------------------------
                           1249 ;Allocation info for local variables in function 'prvSetupTimerInterrupt'
                           1250 ;------------------------------------------------------------
                           1251 ;ulTicksPerSecond          Allocated to registers 
                           1252 ;ulCaptureTime             Allocated to registers 
                           1253 ;ulCaptureValue            Allocated to registers 
                           1254 ;ucLowCaptureByte          Allocated to registers 
                           1255 ;ucHighCaptureByte         Allocated to registers 
                           1256 ;------------------------------------------------------------
                           1257 ;../../Source/portable/SDCC/ASIX/port.c:387: static void prvSetupTimerInterrupt( void )
                           1258 ;	-----------------------------------------
                           1259 ;	 function prvSetupTimerInterrupt
                           1260 ;	-----------------------------------------
   04BE                    1261 _prvSetupTimerInterrupt:
   1809 D0 00              1262 	push	_bp
   180B C0 12 90           1263 	mov	_bp,sp
                           1264 ;../../Source/portable/SDCC/ASIX/port.c:401: RCAP2L = ucLowCaptureByte;
                           1265 ;     genAssign
   180E 1D 0B E0           1266 	mov	_RCAP2L,#0x3D
                           1267 ;../../Source/portable/SDCC/ASIX/port.c:402: RCAP2H = ucHighCaptureByte;
                           1268 ;     genAssign
   1811 FA A3 E0           1269 	mov	_RCAP2H,#0x5D
                           1270 ;../../Source/portable/SDCC/ASIX/port.c:405: TL2 = ucLowCaptureByte;
                           1271 ;     genAssign
   1814 FB A3 E0           1272 	mov	_TL2,#0x3D
                           1273 ;../../Source/portable/SDCC/ASIX/port.c:406: TH2 = ucHighCaptureByte;
                           1274 ;     genAssign
   1817 FC 8A 82           1275 	mov	_TH2,#0x5D
                           1276 ;../../Source/portable/SDCC/ASIX/port.c:409: IE |= portTIMER_2_INTERRUPT_ENABLE;
                           1277 ;     genOr
   181A 8B 83 8C           1278 	orl	_IE,#0x20
                           1279 ;../../Source/portable/SDCC/ASIX/port.c:413: T2CON = portENABLE_TIMER;
                           1280 ;     genAssign
   181D F0 12 AE           1281 	mov	_T2CON,#0x04
   04D5                    1282 00101$:
   1820 30 F5 09           1283 	mov	sp,_bp
   1823 A3 12              1284 	pop	_bp
   1825 AE                 1285 	ret
                           1286 	.area CSEG    (CODE)
                           1287 	.area XINIT   (CODE)
