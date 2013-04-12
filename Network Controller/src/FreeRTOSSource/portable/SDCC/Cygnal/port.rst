                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.4.8 #964 (Feb 23 2005)
                              4 ; This file generated Wed Mar 02 13:24:16 2005
                              5 ;--------------------------------------------------------
                              6 	.module ______Source_portable_SDCC_cygnal_port
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
                    0080    139 G$P0$0$0 == 0x0080
                    0080    140 _P0	=	0x0080
                    0081    141 G$SP$0$0 == 0x0081
                    0081    142 _SP	=	0x0081
                    0082    143 G$DPL$0$0 == 0x0082
                    0082    144 _DPL	=	0x0082
                    0083    145 G$DPH$0$0 == 0x0083
                    0083    146 _DPH	=	0x0083
                    0087    147 G$PCON$0$0 == 0x0087
                    0087    148 _PCON	=	0x0087
                    0088    149 G$TCON$0$0 == 0x0088
                    0088    150 _TCON	=	0x0088
                    0089    151 G$TMOD$0$0 == 0x0089
                    0089    152 _TMOD	=	0x0089
                    008A    153 G$TL0$0$0 == 0x008a
                    008A    154 _TL0	=	0x008a
                    008B    155 G$TL1$0$0 == 0x008b
                    008B    156 _TL1	=	0x008b
                    008C    157 G$TH0$0$0 == 0x008c
                    008C    158 _TH0	=	0x008c
                    008D    159 G$TH1$0$0 == 0x008d
                    008D    160 _TH1	=	0x008d
                    0090    161 G$P1$0$0 == 0x0090
                    0090    162 _P1	=	0x0090
                    0098    163 G$SCON$0$0 == 0x0098
                    0098    164 _SCON	=	0x0098
                    0099    165 G$SBUF$0$0 == 0x0099
                    0099    166 _SBUF	=	0x0099
                    00A0    167 G$P2$0$0 == 0x00a0
                    00A0    168 _P2	=	0x00a0
                    00A8    169 G$IE$0$0 == 0x00a8
                    00A8    170 _IE	=	0x00a8
                    00B0    171 G$P3$0$0 == 0x00b0
                    00B0    172 _P3	=	0x00b0
                    00B8    173 G$IP$0$0 == 0x00b8
                    00B8    174 _IP	=	0x00b8
                    00D0    175 G$PSW$0$0 == 0x00d0
                    00D0    176 _PSW	=	0x00d0
                    00E0    177 G$ACC$0$0 == 0x00e0
                    00E0    178 _ACC	=	0x00e0
                    00F0    179 G$B$0$0 == 0x00f0
                    00F0    180 _B	=	0x00f0
                    00C8    181 G$T2CON$0$0 == 0x00c8
                    00C8    182 _T2CON	=	0x00c8
                    00CA    183 G$RCAP2L$0$0 == 0x00ca
                    00CA    184 _RCAP2L	=	0x00ca
                    00CB    185 G$RCAP2H$0$0 == 0x00cb
                    00CB    186 _RCAP2H	=	0x00cb
                    00CC    187 G$TL2$0$0 == 0x00cc
                    00CC    188 _TL2	=	0x00cc
                    00CD    189 G$TH2$0$0 == 0x00cd
                    00CD    190 _TH2	=	0x00cd
                            191 ;--------------------------------------------------------
                            192 ; special function bits 
                            193 ;--------------------------------------------------------
                            194 	.area RSEG    (DATA)
                    0080    195 G$P0_0$0$0 == 0x0080
                    0080    196 _P0_0	=	0x0080
                    0081    197 G$P0_1$0$0 == 0x0081
                    0081    198 _P0_1	=	0x0081
                    0082    199 G$P0_2$0$0 == 0x0082
                    0082    200 _P0_2	=	0x0082
                    0083    201 G$P0_3$0$0 == 0x0083
                    0083    202 _P0_3	=	0x0083
                    0084    203 G$P0_4$0$0 == 0x0084
                    0084    204 _P0_4	=	0x0084
                    0085    205 G$P0_5$0$0 == 0x0085
                    0085    206 _P0_5	=	0x0085
                    0086    207 G$P0_6$0$0 == 0x0086
                    0086    208 _P0_6	=	0x0086
                    0087    209 G$P0_7$0$0 == 0x0087
                    0087    210 _P0_7	=	0x0087
                    0088    211 G$IT0$0$0 == 0x0088
                    0088    212 _IT0	=	0x0088
                    0089    213 G$IE0$0$0 == 0x0089
                    0089    214 _IE0	=	0x0089
                    008A    215 G$IT1$0$0 == 0x008a
                    008A    216 _IT1	=	0x008a
                    008B    217 G$IE1$0$0 == 0x008b
                    008B    218 _IE1	=	0x008b
                    008C    219 G$TR0$0$0 == 0x008c
                    008C    220 _TR0	=	0x008c
                    008D    221 G$TF0$0$0 == 0x008d
                    008D    222 _TF0	=	0x008d
                    008E    223 G$TR1$0$0 == 0x008e
                    008E    224 _TR1	=	0x008e
                    008F    225 G$TF1$0$0 == 0x008f
                    008F    226 _TF1	=	0x008f
                    0090    227 G$P1_0$0$0 == 0x0090
                    0090    228 _P1_0	=	0x0090
                    0091    229 G$P1_1$0$0 == 0x0091
                    0091    230 _P1_1	=	0x0091
                    0092    231 G$P1_2$0$0 == 0x0092
                    0092    232 _P1_2	=	0x0092
                    0093    233 G$P1_3$0$0 == 0x0093
                    0093    234 _P1_3	=	0x0093
                    0094    235 G$P1_4$0$0 == 0x0094
                    0094    236 _P1_4	=	0x0094
                    0095    237 G$P1_5$0$0 == 0x0095
                    0095    238 _P1_5	=	0x0095
                    0096    239 G$P1_6$0$0 == 0x0096
                    0096    240 _P1_6	=	0x0096
                    0097    241 G$P1_7$0$0 == 0x0097
                    0097    242 _P1_7	=	0x0097
                    0098    243 G$RI$0$0 == 0x0098
                    0098    244 _RI	=	0x0098
                    0099    245 G$TI$0$0 == 0x0099
                    0099    246 _TI	=	0x0099
                    009A    247 G$RB8$0$0 == 0x009a
                    009A    248 _RB8	=	0x009a
                    009B    249 G$TB8$0$0 == 0x009b
                    009B    250 _TB8	=	0x009b
                    009C    251 G$REN$0$0 == 0x009c
                    009C    252 _REN	=	0x009c
                    009D    253 G$SM2$0$0 == 0x009d
                    009D    254 _SM2	=	0x009d
                    009E    255 G$SM1$0$0 == 0x009e
                    009E    256 _SM1	=	0x009e
                    009F    257 G$SM0$0$0 == 0x009f
                    009F    258 _SM0	=	0x009f
                    00A0    259 G$P2_0$0$0 == 0x00a0
                    00A0    260 _P2_0	=	0x00a0
                    00A1    261 G$P2_1$0$0 == 0x00a1
                    00A1    262 _P2_1	=	0x00a1
                    00A2    263 G$P2_2$0$0 == 0x00a2
                    00A2    264 _P2_2	=	0x00a2
                    00A3    265 G$P2_3$0$0 == 0x00a3
                    00A3    266 _P2_3	=	0x00a3
                    00A4    267 G$P2_4$0$0 == 0x00a4
                    00A4    268 _P2_4	=	0x00a4
                    00A5    269 G$P2_5$0$0 == 0x00a5
                    00A5    270 _P2_5	=	0x00a5
                    00A6    271 G$P2_6$0$0 == 0x00a6
                    00A6    272 _P2_6	=	0x00a6
                    00A7    273 G$P2_7$0$0 == 0x00a7
                    00A7    274 _P2_7	=	0x00a7
                    00A8    275 G$EX0$0$0 == 0x00a8
                    00A8    276 _EX0	=	0x00a8
                    00A9    277 G$ET0$0$0 == 0x00a9
                    00A9    278 _ET0	=	0x00a9
                    00AA    279 G$EX1$0$0 == 0x00aa
                    00AA    280 _EX1	=	0x00aa
                    00AB    281 G$ET1$0$0 == 0x00ab
                    00AB    282 _ET1	=	0x00ab
                    00AC    283 G$ES$0$0 == 0x00ac
                    00AC    284 _ES	=	0x00ac
                    00AF    285 G$EA$0$0 == 0x00af
                    00AF    286 _EA	=	0x00af
                    00B0    287 G$P3_0$0$0 == 0x00b0
                    00B0    288 _P3_0	=	0x00b0
                    00B1    289 G$P3_1$0$0 == 0x00b1
                    00B1    290 _P3_1	=	0x00b1
                    00B2    291 G$P3_2$0$0 == 0x00b2
                    00B2    292 _P3_2	=	0x00b2
                    00B3    293 G$P3_3$0$0 == 0x00b3
                    00B3    294 _P3_3	=	0x00b3
                    00B4    295 G$P3_4$0$0 == 0x00b4
                    00B4    296 _P3_4	=	0x00b4
                    00B5    297 G$P3_5$0$0 == 0x00b5
                    00B5    298 _P3_5	=	0x00b5
                    00B6    299 G$P3_6$0$0 == 0x00b6
                    00B6    300 _P3_6	=	0x00b6
                    00B7    301 G$P3_7$0$0 == 0x00b7
                    00B7    302 _P3_7	=	0x00b7
                    00B0    303 G$RXD$0$0 == 0x00b0
                    00B0    304 _RXD	=	0x00b0
                    00B1    305 G$TXD$0$0 == 0x00b1
                    00B1    306 _TXD	=	0x00b1
                    00B2    307 G$INT0$0$0 == 0x00b2
                    00B2    308 _INT0	=	0x00b2
                    00B3    309 G$INT1$0$0 == 0x00b3
                    00B3    310 _INT1	=	0x00b3
                    00B4    311 G$T0$0$0 == 0x00b4
                    00B4    312 _T0	=	0x00b4
                    00B5    313 G$T1$0$0 == 0x00b5
                    00B5    314 _T1	=	0x00b5
                    00B6    315 G$WR$0$0 == 0x00b6
                    00B6    316 _WR	=	0x00b6
                    00B7    317 G$RD$0$0 == 0x00b7
                    00B7    318 _RD	=	0x00b7
                    00B8    319 G$PX0$0$0 == 0x00b8
                    00B8    320 _PX0	=	0x00b8
                    00B9    321 G$PT0$0$0 == 0x00b9
                    00B9    322 _PT0	=	0x00b9
                    00BA    323 G$PX1$0$0 == 0x00ba
                    00BA    324 _PX1	=	0x00ba
                    00BB    325 G$PT1$0$0 == 0x00bb
                    00BB    326 _PT1	=	0x00bb
                    00BC    327 G$PS$0$0 == 0x00bc
                    00BC    328 _PS	=	0x00bc
                    00D0    329 G$P$0$0 == 0x00d0
                    00D0    330 _P	=	0x00d0
                    00D1    331 G$F1$0$0 == 0x00d1
                    00D1    332 _F1	=	0x00d1
                    00D2    333 G$OV$0$0 == 0x00d2
                    00D2    334 _OV	=	0x00d2
                    00D3    335 G$RS0$0$0 == 0x00d3
                    00D3    336 _RS0	=	0x00d3
                    00D4    337 G$RS1$0$0 == 0x00d4
                    00D4    338 _RS1	=	0x00d4
                    00D5    339 G$F0$0$0 == 0x00d5
                    00D5    340 _F0	=	0x00d5
                    00D6    341 G$AC$0$0 == 0x00d6
                    00D6    342 _AC	=	0x00d6
                    00D7    343 G$CY$0$0 == 0x00d7
                    00D7    344 _CY	=	0x00d7
                    00AD    345 G$ET2$0$0 == 0x00ad
                    00AD    346 _ET2	=	0x00ad
                    00C8    347 G$T2CON_0$0$0 == 0x00c8
                    00C8    348 _T2CON_0	=	0x00c8
                    00C9    349 G$T2CON_1$0$0 == 0x00c9
                    00C9    350 _T2CON_1	=	0x00c9
                    00CA    351 G$T2CON_2$0$0 == 0x00ca
                    00CA    352 _T2CON_2	=	0x00ca
                    00CB    353 G$T2CON_3$0$0 == 0x00cb
                    00CB    354 _T2CON_3	=	0x00cb
                    00CC    355 G$T2CON_4$0$0 == 0x00cc
                    00CC    356 _T2CON_4	=	0x00cc
                    00CD    357 G$T2CON_5$0$0 == 0x00cd
                    00CD    358 _T2CON_5	=	0x00cd
                    00CE    359 G$T2CON_6$0$0 == 0x00ce
                    00CE    360 _T2CON_6	=	0x00ce
                    00CF    361 G$T2CON_7$0$0 == 0x00cf
                    00CF    362 _T2CON_7	=	0x00cf
                    00C8    363 G$CP_RL2$0$0 == 0x00c8
                    00C8    364 _CP_RL2	=	0x00c8
                    00C9    365 G$C_T2$0$0 == 0x00c9
                    00C9    366 _C_T2	=	0x00c9
                    00CA    367 G$TR2$0$0 == 0x00ca
                    00CA    368 _TR2	=	0x00ca
                    00CB    369 G$EXEN2$0$0 == 0x00cb
                    00CB    370 _EXEN2	=	0x00cb
                    00CC    371 G$TCLK$0$0 == 0x00cc
                    00CC    372 _TCLK	=	0x00cc
                    00CD    373 G$RCLK$0$0 == 0x00cd
                    00CD    374 _RCLK	=	0x00cd
                    00CE    375 G$EXF2$0$0 == 0x00ce
                    00CE    376 _EXF2	=	0x00ce
                    00CF    377 G$TF2$0$0 == 0x00cf
                    00CF    378 _TF2	=	0x00cf
                            379 ;--------------------------------------------------------
                            380 ; overlayable register banks 
                            381 ;--------------------------------------------------------
                            382 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     383 	.ds 8
                            384 ;--------------------------------------------------------
                            385 ; internal ram data
                            386 ;--------------------------------------------------------
                            387 	.area DSEG    (DATA)
                    0000    388 F______Source_portable_SDCC_cygnal_port$ucStackBytes$0$0==.
   0008                     389 _ucStackBytes:
   0008                     390 	.ds 1
                    0001    391 F______Source_portable_SDCC_cygnal_port$pxXRAMStack$0$0==.
   0009                     392 _pxXRAMStack:
   0009                     393 	.ds 2
                    0003    394 F______Source_portable_SDCC_cygnal_port$pxRAMStack$0$0==.
   000B                     395 _pxRAMStack:
   000B                     396 	.ds 1
                            397 ;--------------------------------------------------------
                            398 ; overlayable items in internal ram 
                            399 ;--------------------------------------------------------
                            400 	.area OSEG    (OVR,DATA)
                            401 ;--------------------------------------------------------
                            402 ; indirectly addressable internal ram data
                            403 ;--------------------------------------------------------
                            404 	.area ISEG    (DATA)
                            405 ;--------------------------------------------------------
                            406 ; bit data
                            407 ;--------------------------------------------------------
                            408 	.area BSEG    (BIT)
                            409 ;--------------------------------------------------------
                            410 ; paged external ram data
                            411 ;--------------------------------------------------------
                            412 	.area PSEG    (PAG,XDATA)
                            413 ;--------------------------------------------------------
                            414 ; external ram data
                            415 ;--------------------------------------------------------
                            416 	.area XSEG    (XDATA)
                            417 ;--------------------------------------------------------
                            418 ; external initialized ram data
                            419 ;--------------------------------------------------------
                            420 	.area XISEG   (XDATA)
                            421 	.area CSEG    (CODE)
                            422 	.area GSINIT0 (CODE)
                            423 	.area GSINIT1 (CODE)
                            424 	.area GSINIT2 (CODE)
                            425 	.area GSINIT3 (CODE)
                            426 	.area GSINIT4 (CODE)
                            427 	.area GSINIT5 (CODE)
                            428 ;--------------------------------------------------------
                            429 ; global & static initialisations
                            430 ;--------------------------------------------------------
                            431 	.area CSEG    (CODE)
                            432 	.area GSINIT  (CODE)
                            433 	.area GSFINAL (CODE)
                            434 	.area GSINIT  (CODE)
                            435 ;--------------------------------------------------------
                            436 ; Home
                            437 ;--------------------------------------------------------
                            438 	.area HOME    (CODE)
                            439 	.area CSEG    (CODE)
                            440 ;--------------------------------------------------------
                            441 ; code
                            442 ;--------------------------------------------------------
                            443 	.area CSEG    (CODE)
                            444 ;------------------------------------------------------------
                            445 ;Allocation info for local variables in function 'pxPortInitialiseStack'
                            446 ;------------------------------------------------------------
                            447 ;pxCode                    Allocated to stack - offset -4
                            448 ;pvParameters              Allocated to stack - offset -7
                            449 ;pxTopOfStack              Allocated to stack - offset 1
                            450 ;ulAddress                 Allocated to registers r5 r6 r7 r2 
                            451 ;pxStartOfStack            Allocated to stack - offset 4
                            452 ;------------------------------------------------------------
                    0000    453 	G$pxPortInitialiseStack$0$0 ==.
                    0000    454 	C$port.c$222$0$0 ==.
                            455 ;../../Source/portable/SDCC/cygnal/port.c:222: portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters )
                            456 ;	-----------------------------------------
                            457 ;	 function pxPortInitialiseStack
                            458 ;	-----------------------------------------
   13F3                     459 _pxPortInitialiseStack:
                    0002    460 	ar2 = 0x02
                    0003    461 	ar3 = 0x03
                    0004    462 	ar4 = 0x04
                    0005    463 	ar5 = 0x05
                    0006    464 	ar6 = 0x06
                    0007    465 	ar7 = 0x07
                    0000    466 	ar0 = 0x00
                    0001    467 	ar1 = 0x01
   13F3 C0 0D               468 	push	_bp
   13F5 85 81 0D            469 	mov	_bp,sp
                            470 ;     genReceive
   13F8 C0 82               471 	push	dpl
   13FA C0 83               472 	push	dph
   13FC C0 F0               473 	push	b
   13FE 05 81               474 	inc	sp
   1400 05 81               475 	inc	sp
   1402 05 81               476 	inc	sp
                    0011    477 	C$port.c$228$1$1 ==.
                            478 ;../../Source/portable/SDCC/cygnal/port.c:228: pxStartOfStack = pxTopOfStack;
                            479 ;     genAssign
   1404 E5 0D               480 	mov	a,_bp
   1406 24 01               481 	add	a,#0x01
   1408 F8                  482 	mov	r0,a
   1409 E5 0D               483 	mov	a,_bp
   140B 24 04               484 	add	a,#0x04
   140D F9                  485 	mov	r1,a
   140E E6                  486 	mov	a,@r0
   140F F7                  487 	mov	@r1,a
   1410 08                  488 	inc	r0
   1411 09                  489 	inc	r1
   1412 E6                  490 	mov	a,@r0
   1413 F7                  491 	mov	@r1,a
   1414 08                  492 	inc	r0
   1415 09                  493 	inc	r1
   1416 E6                  494 	mov	a,@r0
   1417 F7                  495 	mov	@r1,a
                    0025    496 	C$port.c$229$1$1 ==.
                            497 ;../../Source/portable/SDCC/cygnal/port.c:229: pxTopOfStack++;
                            498 ;     genPlus
   1418 E5 0D               499 	mov	a,_bp
   141A 24 01               500 	add	a,#0x01
   141C F8                  501 	mov	r0,a
                            502 ;     genPlusIncr
   141D 74 01               503 	mov	a,#0x01
   141F 26                  504 	add	a,@r0
   1420 F6                  505 	mov	@r0,a
   1421 74 00               506 	mov	a,#0x00
   1423 08                  507 	inc	r0
   1424 36                  508 	addc	a,@r0
   1425 F6                  509 	mov	@r0,a
                    0033    510 	C$port.c$245$1$1 ==.
                            511 ;../../Source/portable/SDCC/cygnal/port.c:245: ulAddress = ( unsigned portLONG ) pxCode;
                            512 ;     genCast
   1426 E5 0D               513 	mov	a,_bp
   1428 24 FC               514 	add	a,#0xfc
   142A F8                  515 	mov	r0,a
   142B 86 05               516 	mov	ar5,@r0
   142D 08                  517 	inc	r0
   142E 86 06               518 	mov	ar6,@r0
   1430 7F 00               519 	mov	r7,#0x00
   1432 7A 00               520 	mov	r2,#0x00
                    0041    521 	C$port.c$246$1$1 ==.
                            522 ;../../Source/portable/SDCC/cygnal/port.c:246: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;
                            523 ;     genCast
   1434 8D 03               524 	mov	ar3,r5
                            525 ;     genPointerSet
                            526 ;     genGenPointerSet
   1436 E5 0D               527 	mov	a,_bp
   1438 24 01               528 	add	a,#0x01
   143A F8                  529 	mov	r0,a
   143B 86 82               530 	mov	dpl,@r0
   143D 08                  531 	inc	r0
   143E 86 83               532 	mov	dph,@r0
   1440 08                  533 	inc	r0
   1441 86 F0               534 	mov	b,@r0
   1443 EB                  535 	mov	a,r3
   1444 12 3C 02            536 	lcall	__gptrput
   1447 A3                  537 	inc	dptr
   1448 18                  538 	dec	r0
   1449 18                  539 	dec	r0
   144A A6 82               540 	mov	@r0,dpl
   144C 08                  541 	inc	r0
   144D A6 83               542 	mov	@r0,dph
                    005C    543 	C$port.c$247$1$1 ==.
                            544 ;../../Source/portable/SDCC/cygnal/port.c:247: ulAddress >>= 8;
                            545 ;     genRightShift
                            546 ;     genRightShiftLiteral
                            547 ;     genrshFour
   144F 8E 05               548 	mov	ar5,r6
   1451 8F 06               549 	mov	ar6,r7
   1453 8A 07               550 	mov	ar7,r2
   1455 7A 00               551 	mov	r2,#0x00
                    0064    552 	C$port.c$248$1$1 ==.
                            553 ;../../Source/portable/SDCC/cygnal/port.c:248: pxTopOfStack++;
                    0064    554 	C$port.c$249$1$1 ==.
                            555 ;../../Source/portable/SDCC/cygnal/port.c:249: *pxTopOfStack = ( portSTACK_TYPE ) ( ulAddress );
                            556 ;     genCast
   1457 8D 03               557 	mov	ar3,r5
                            558 ;     genPointerSet
                            559 ;     genGenPointerSet
   1459 E5 0D               560 	mov	a,_bp
   145B 24 01               561 	add	a,#0x01
   145D F8                  562 	mov	r0,a
   145E 86 82               563 	mov	dpl,@r0
   1460 08                  564 	inc	r0
   1461 86 83               565 	mov	dph,@r0
   1463 08                  566 	inc	r0
   1464 86 F0               567 	mov	b,@r0
   1466 EB                  568 	mov	a,r3
   1467 12 3C 02            569 	lcall	__gptrput
   146A A3                  570 	inc	dptr
   146B 18                  571 	dec	r0
   146C 18                  572 	dec	r0
   146D A6 82               573 	mov	@r0,dpl
   146F 08                  574 	inc	r0
   1470 A6 83               575 	mov	@r0,dph
                    007F    576 	C$port.c$250$1$1 ==.
                            577 ;../../Source/portable/SDCC/cygnal/port.c:250: pxTopOfStack++;
                    007F    578 	C$port.c$253$1$1 ==.
                            579 ;../../Source/portable/SDCC/cygnal/port.c:253: *pxTopOfStack = 0xaa;	/* acc */
                            580 ;     genPointerSet
                            581 ;     genGenPointerSet
   1472 E5 0D               582 	mov	a,_bp
   1474 24 01               583 	add	a,#0x01
   1476 F8                  584 	mov	r0,a
   1477 86 82               585 	mov	dpl,@r0
   1479 08                  586 	inc	r0
   147A 86 83               587 	mov	dph,@r0
   147C 08                  588 	inc	r0
   147D 86 F0               589 	mov	b,@r0
   147F 74 AA               590 	mov	a,#0xAA
   1481 12 3C 02            591 	lcall	__gptrput
   1484 A3                  592 	inc	dptr
   1485 18                  593 	dec	r0
   1486 18                  594 	dec	r0
   1487 A6 82               595 	mov	@r0,dpl
   1489 08                  596 	inc	r0
   148A A6 83               597 	mov	@r0,dph
                    0099    598 	C$port.c$254$1$1 ==.
                            599 ;../../Source/portable/SDCC/cygnal/port.c:254: pxTopOfStack++;	
                    0099    600 	C$port.c$257$1$1 ==.
                            601 ;../../Source/portable/SDCC/cygnal/port.c:257: *pxTopOfStack = portGLOBAL_INTERRUPT_BIT;
                            602 ;     genPointerSet
                            603 ;     genGenPointerSet
   148C E5 0D               604 	mov	a,_bp
   148E 24 01               605 	add	a,#0x01
   1490 F8                  606 	mov	r0,a
   1491 86 82               607 	mov	dpl,@r0
   1493 08                  608 	inc	r0
   1494 86 83               609 	mov	dph,@r0
   1496 08                  610 	inc	r0
   1497 86 F0               611 	mov	b,@r0
   1499 74 80               612 	mov	a,#0x80
   149B 12 3C 02            613 	lcall	__gptrput
   149E A3                  614 	inc	dptr
   149F 18                  615 	dec	r0
   14A0 18                  616 	dec	r0
   14A1 A6 82               617 	mov	@r0,dpl
   14A3 08                  618 	inc	r0
   14A4 A6 83               619 	mov	@r0,dph
                    00B3    620 	C$port.c$258$1$1 ==.
                            621 ;../../Source/portable/SDCC/cygnal/port.c:258: pxTopOfStack++;
                    00B3    622 	C$port.c$262$1$1 ==.
                            623 ;../../Source/portable/SDCC/cygnal/port.c:262: ulAddress = ( unsigned portLONG ) pvParameters;
                            624 ;     genCast
   14A6 E5 0D               625 	mov	a,_bp
   14A8 24 F9               626 	add	a,#0xf9
   14AA F8                  627 	mov	r0,a
   14AB 86 05               628 	mov	ar5,@r0
   14AD 08                  629 	inc	r0
   14AE 86 06               630 	mov	ar6,@r0
   14B0 08                  631 	inc	r0
   14B1 86 07               632 	mov	ar7,@r0
   14B3 7A 00               633 	mov	r2,#0x00
                    00C2    634 	C$port.c$263$1$1 ==.
                            635 ;../../Source/portable/SDCC/cygnal/port.c:263: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;	/* DPL */
                            636 ;     genCast
   14B5 8D 03               637 	mov	ar3,r5
                            638 ;     genPointerSet
                            639 ;     genGenPointerSet
   14B7 E5 0D               640 	mov	a,_bp
   14B9 24 01               641 	add	a,#0x01
   14BB F8                  642 	mov	r0,a
   14BC 86 82               643 	mov	dpl,@r0
   14BE 08                  644 	inc	r0
   14BF 86 83               645 	mov	dph,@r0
   14C1 08                  646 	inc	r0
   14C2 86 F0               647 	mov	b,@r0
   14C4 EB                  648 	mov	a,r3
   14C5 12 3C 02            649 	lcall	__gptrput
   14C8 A3                  650 	inc	dptr
   14C9 18                  651 	dec	r0
   14CA 18                  652 	dec	r0
   14CB A6 82               653 	mov	@r0,dpl
   14CD 08                  654 	inc	r0
   14CE A6 83               655 	mov	@r0,dph
                    00DD    656 	C$port.c$264$1$1 ==.
                            657 ;../../Source/portable/SDCC/cygnal/port.c:264: ulAddress >>= 8;
                            658 ;     genRightShift
                            659 ;     genRightShiftLiteral
                            660 ;     genrshFour
   14D0 8E 05               661 	mov	ar5,r6
   14D2 8F 06               662 	mov	ar6,r7
   14D4 8A 07               663 	mov	ar7,r2
   14D6 7A 00               664 	mov	r2,#0x00
                    00E5    665 	C$port.c$265$1$1 ==.
                            666 ;../../Source/portable/SDCC/cygnal/port.c:265: *pxTopOfStack++;
                    00E5    667 	C$port.c$266$1$1 ==.
                            668 ;../../Source/portable/SDCC/cygnal/port.c:266: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;	/* DPH */
                            669 ;     genCast
   14D8 8D 03               670 	mov	ar3,r5
                            671 ;     genPointerSet
                            672 ;     genGenPointerSet
   14DA E5 0D               673 	mov	a,_bp
   14DC 24 01               674 	add	a,#0x01
   14DE F8                  675 	mov	r0,a
   14DF 86 82               676 	mov	dpl,@r0
   14E1 08                  677 	inc	r0
   14E2 86 83               678 	mov	dph,@r0
   14E4 08                  679 	inc	r0
   14E5 86 F0               680 	mov	b,@r0
   14E7 EB                  681 	mov	a,r3
   14E8 12 3C 02            682 	lcall	__gptrput
   14EB A3                  683 	inc	dptr
   14EC 18                  684 	dec	r0
   14ED 18                  685 	dec	r0
   14EE A6 82               686 	mov	@r0,dpl
   14F0 08                  687 	inc	r0
   14F1 A6 83               688 	mov	@r0,dph
                    0100    689 	C$port.c$267$1$1 ==.
                            690 ;../../Source/portable/SDCC/cygnal/port.c:267: ulAddress >>= 8;
                            691 ;     genRightShift
                            692 ;     genRightShiftLiteral
                            693 ;     genrshFour
   14F3 8E 05               694 	mov	ar5,r6
   14F5 8F 06               695 	mov	ar6,r7
   14F7 8A 07               696 	mov	ar7,r2
   14F9 7A 00               697 	mov	r2,#0x00
                    0108    698 	C$port.c$268$1$1 ==.
                            699 ;../../Source/portable/SDCC/cygnal/port.c:268: pxTopOfStack++;
                    0108    700 	C$port.c$269$1$1 ==.
                            701 ;../../Source/portable/SDCC/cygnal/port.c:269: *pxTopOfStack = ( portSTACK_TYPE ) ulAddress;	/* b */
                            702 ;     genCast
                            703 ;     genPointerSet
                            704 ;     genGenPointerSet
   14FB E5 0D               705 	mov	a,_bp
   14FD 24 01               706 	add	a,#0x01
   14FF F8                  707 	mov	r0,a
   1500 86 82               708 	mov	dpl,@r0
   1502 08                  709 	inc	r0
   1503 86 83               710 	mov	dph,@r0
   1505 08                  711 	inc	r0
   1506 86 F0               712 	mov	b,@r0
   1508 ED                  713 	mov	a,r5
   1509 12 3C 02            714 	lcall	__gptrput
   150C A3                  715 	inc	dptr
   150D 18                  716 	dec	r0
   150E 18                  717 	dec	r0
   150F A6 82               718 	mov	@r0,dpl
   1511 08                  719 	inc	r0
   1512 A6 83               720 	mov	@r0,dph
                    0121    721 	C$port.c$270$1$1 ==.
                            722 ;../../Source/portable/SDCC/cygnal/port.c:270: pxTopOfStack++;
                    0121    723 	C$port.c$273$1$1 ==.
                            724 ;../../Source/portable/SDCC/cygnal/port.c:273: *pxTopOfStack = 0x02;	/* R2 */
                            725 ;     genPointerSet
                            726 ;     genGenPointerSet
   1514 E5 0D               727 	mov	a,_bp
   1516 24 01               728 	add	a,#0x01
   1518 F8                  729 	mov	r0,a
   1519 86 82               730 	mov	dpl,@r0
   151B 08                  731 	inc	r0
   151C 86 83               732 	mov	dph,@r0
   151E 08                  733 	inc	r0
   151F 86 F0               734 	mov	b,@r0
   1521 74 02               735 	mov	a,#0x02
   1523 12 3C 02            736 	lcall	__gptrput
   1526 A3                  737 	inc	dptr
   1527 18                  738 	dec	r0
   1528 18                  739 	dec	r0
   1529 A6 82               740 	mov	@r0,dpl
   152B 08                  741 	inc	r0
   152C A6 83               742 	mov	@r0,dph
                    013B    743 	C$port.c$274$1$1 ==.
                            744 ;../../Source/portable/SDCC/cygnal/port.c:274: pxTopOfStack++;
                    013B    745 	C$port.c$275$1$1 ==.
                            746 ;../../Source/portable/SDCC/cygnal/port.c:275: *pxTopOfStack = 0x03;	/* R3 */
                            747 ;     genPointerSet
                            748 ;     genGenPointerSet
   152E E5 0D               749 	mov	a,_bp
   1530 24 01               750 	add	a,#0x01
   1532 F8                  751 	mov	r0,a
   1533 86 82               752 	mov	dpl,@r0
   1535 08                  753 	inc	r0
   1536 86 83               754 	mov	dph,@r0
   1538 08                  755 	inc	r0
   1539 86 F0               756 	mov	b,@r0
   153B 74 03               757 	mov	a,#0x03
   153D 12 3C 02            758 	lcall	__gptrput
   1540 A3                  759 	inc	dptr
   1541 18                  760 	dec	r0
   1542 18                  761 	dec	r0
   1543 A6 82               762 	mov	@r0,dpl
   1545 08                  763 	inc	r0
   1546 A6 83               764 	mov	@r0,dph
                    0155    765 	C$port.c$276$1$1 ==.
                            766 ;../../Source/portable/SDCC/cygnal/port.c:276: pxTopOfStack++;
                    0155    767 	C$port.c$277$1$1 ==.
                            768 ;../../Source/portable/SDCC/cygnal/port.c:277: *pxTopOfStack = 0x04;	/* R4 */
                            769 ;     genPointerSet
                            770 ;     genGenPointerSet
   1548 E5 0D               771 	mov	a,_bp
   154A 24 01               772 	add	a,#0x01
   154C F8                  773 	mov	r0,a
   154D 86 82               774 	mov	dpl,@r0
   154F 08                  775 	inc	r0
   1550 86 83               776 	mov	dph,@r0
   1552 08                  777 	inc	r0
   1553 86 F0               778 	mov	b,@r0
   1555 74 04               779 	mov	a,#0x04
   1557 12 3C 02            780 	lcall	__gptrput
   155A A3                  781 	inc	dptr
   155B 18                  782 	dec	r0
   155C 18                  783 	dec	r0
   155D A6 82               784 	mov	@r0,dpl
   155F 08                  785 	inc	r0
   1560 A6 83               786 	mov	@r0,dph
                    016F    787 	C$port.c$278$1$1 ==.
                            788 ;../../Source/portable/SDCC/cygnal/port.c:278: pxTopOfStack++;
                    016F    789 	C$port.c$279$1$1 ==.
                            790 ;../../Source/portable/SDCC/cygnal/port.c:279: *pxTopOfStack = 0x05;	/* R5 */
                            791 ;     genPointerSet
                            792 ;     genGenPointerSet
   1562 E5 0D               793 	mov	a,_bp
   1564 24 01               794 	add	a,#0x01
   1566 F8                  795 	mov	r0,a
   1567 86 82               796 	mov	dpl,@r0
   1569 08                  797 	inc	r0
   156A 86 83               798 	mov	dph,@r0
   156C 08                  799 	inc	r0
   156D 86 F0               800 	mov	b,@r0
   156F 74 05               801 	mov	a,#0x05
   1571 12 3C 02            802 	lcall	__gptrput
   1574 A3                  803 	inc	dptr
   1575 18                  804 	dec	r0
   1576 18                  805 	dec	r0
   1577 A6 82               806 	mov	@r0,dpl
   1579 08                  807 	inc	r0
   157A A6 83               808 	mov	@r0,dph
                    0189    809 	C$port.c$280$1$1 ==.
                            810 ;../../Source/portable/SDCC/cygnal/port.c:280: pxTopOfStack++;
                    0189    811 	C$port.c$281$1$1 ==.
                            812 ;../../Source/portable/SDCC/cygnal/port.c:281: *pxTopOfStack = 0x06;	/* R6 */
                            813 ;     genPointerSet
                            814 ;     genGenPointerSet
   157C E5 0D               815 	mov	a,_bp
   157E 24 01               816 	add	a,#0x01
   1580 F8                  817 	mov	r0,a
   1581 86 82               818 	mov	dpl,@r0
   1583 08                  819 	inc	r0
   1584 86 83               820 	mov	dph,@r0
   1586 08                  821 	inc	r0
   1587 86 F0               822 	mov	b,@r0
   1589 74 06               823 	mov	a,#0x06
   158B 12 3C 02            824 	lcall	__gptrput
   158E A3                  825 	inc	dptr
   158F 18                  826 	dec	r0
   1590 18                  827 	dec	r0
   1591 A6 82               828 	mov	@r0,dpl
   1593 08                  829 	inc	r0
   1594 A6 83               830 	mov	@r0,dph
                    01A3    831 	C$port.c$282$1$1 ==.
                            832 ;../../Source/portable/SDCC/cygnal/port.c:282: pxTopOfStack++;
                    01A3    833 	C$port.c$283$1$1 ==.
                            834 ;../../Source/portable/SDCC/cygnal/port.c:283: *pxTopOfStack = 0x07;	/* R7 */
                            835 ;     genPointerSet
                            836 ;     genGenPointerSet
   1596 E5 0D               837 	mov	a,_bp
   1598 24 01               838 	add	a,#0x01
   159A F8                  839 	mov	r0,a
   159B 86 82               840 	mov	dpl,@r0
   159D 08                  841 	inc	r0
   159E 86 83               842 	mov	dph,@r0
   15A0 08                  843 	inc	r0
   15A1 86 F0               844 	mov	b,@r0
   15A3 74 07               845 	mov	a,#0x07
   15A5 12 3C 02            846 	lcall	__gptrput
   15A8 A3                  847 	inc	dptr
   15A9 18                  848 	dec	r0
   15AA 18                  849 	dec	r0
   15AB A6 82               850 	mov	@r0,dpl
   15AD 08                  851 	inc	r0
   15AE A6 83               852 	mov	@r0,dph
                    01BD    853 	C$port.c$284$1$1 ==.
                            854 ;../../Source/portable/SDCC/cygnal/port.c:284: pxTopOfStack++;
                    01BD    855 	C$port.c$285$1$1 ==.
                            856 ;../../Source/portable/SDCC/cygnal/port.c:285: *pxTopOfStack = 0x00;	/* R0 */
                            857 ;     genPointerSet
                            858 ;     genGenPointerSet
   15B0 E5 0D               859 	mov	a,_bp
   15B2 24 01               860 	add	a,#0x01
   15B4 F8                  861 	mov	r0,a
   15B5 86 82               862 	mov	dpl,@r0
   15B7 08                  863 	inc	r0
   15B8 86 83               864 	mov	dph,@r0
   15BA 08                  865 	inc	r0
   15BB 86 F0               866 	mov	b,@r0
   15BD 74 00               867 	mov	a,#0x00
   15BF 12 3C 02            868 	lcall	__gptrput
   15C2 A3                  869 	inc	dptr
   15C3 18                  870 	dec	r0
   15C4 18                  871 	dec	r0
   15C5 A6 82               872 	mov	@r0,dpl
   15C7 08                  873 	inc	r0
   15C8 A6 83               874 	mov	@r0,dph
                    01D7    875 	C$port.c$286$1$1 ==.
                            876 ;../../Source/portable/SDCC/cygnal/port.c:286: pxTopOfStack++;
                    01D7    877 	C$port.c$287$1$1 ==.
                            878 ;../../Source/portable/SDCC/cygnal/port.c:287: *pxTopOfStack = 0x01;	/* R1 */
                            879 ;     genPointerSet
                            880 ;     genGenPointerSet
   15CA E5 0D               881 	mov	a,_bp
   15CC 24 01               882 	add	a,#0x01
   15CE F8                  883 	mov	r0,a
   15CF 86 82               884 	mov	dpl,@r0
   15D1 08                  885 	inc	r0
   15D2 86 83               886 	mov	dph,@r0
   15D4 08                  887 	inc	r0
   15D5 86 F0               888 	mov	b,@r0
   15D7 74 01               889 	mov	a,#0x01
   15D9 12 3C 02            890 	lcall	__gptrput
   15DC A3                  891 	inc	dptr
   15DD 18                  892 	dec	r0
   15DE 18                  893 	dec	r0
   15DF A6 82               894 	mov	@r0,dpl
   15E1 08                  895 	inc	r0
   15E2 A6 83               896 	mov	@r0,dph
                    01F1    897 	C$port.c$288$1$1 ==.
                            898 ;../../Source/portable/SDCC/cygnal/port.c:288: pxTopOfStack++;
                    01F1    899 	C$port.c$289$1$1 ==.
                            900 ;../../Source/portable/SDCC/cygnal/port.c:289: *pxTopOfStack = 0x00;	/* PSW */
                            901 ;     genPointerSet
                            902 ;     genGenPointerSet
   15E4 E5 0D               903 	mov	a,_bp
   15E6 24 01               904 	add	a,#0x01
   15E8 F8                  905 	mov	r0,a
   15E9 86 82               906 	mov	dpl,@r0
   15EB 08                  907 	inc	r0
   15EC 86 83               908 	mov	dph,@r0
   15EE 08                  909 	inc	r0
   15EF 86 F0               910 	mov	b,@r0
   15F1 74 00               911 	mov	a,#0x00
   15F3 12 3C 02            912 	lcall	__gptrput
   15F6 A3                  913 	inc	dptr
   15F7 18                  914 	dec	r0
   15F8 18                  915 	dec	r0
   15F9 A6 82               916 	mov	@r0,dpl
   15FB 08                  917 	inc	r0
   15FC A6 83               918 	mov	@r0,dph
                    020B    919 	C$port.c$290$1$1 ==.
                            920 ;../../Source/portable/SDCC/cygnal/port.c:290: pxTopOfStack++;
                    020B    921 	C$port.c$291$1$1 ==.
                            922 ;../../Source/portable/SDCC/cygnal/port.c:291: *pxTopOfStack = 0xbb;	/* BP */
                            923 ;     genPointerSet
                            924 ;     genGenPointerSet
   15FE E5 0D               925 	mov	a,_bp
   1600 24 01               926 	add	a,#0x01
   1602 F8                  927 	mov	r0,a
   1603 86 82               928 	mov	dpl,@r0
   1605 08                  929 	inc	r0
   1606 86 83               930 	mov	dph,@r0
   1608 08                  931 	inc	r0
   1609 86 F0               932 	mov	b,@r0
   160B 74 BB               933 	mov	a,#0xBB
   160D 12 3C 02            934 	lcall	__gptrput
                    021D    935 	C$port.c$297$1$1 ==.
                            936 ;../../Source/portable/SDCC/cygnal/port.c:297: *pxStartOfStack = ( portSTACK_TYPE ) ( pxTopOfStack - pxStartOfStack );
                            937 ;     genMinus
   1610 E5 0D               938 	mov	a,_bp
   1612 24 01               939 	add	a,#0x01
   1614 F8                  940 	mov	r0,a
   1615 E5 0D               941 	mov	a,_bp
   1617 24 04               942 	add	a,#0x04
   1619 F9                  943 	mov	r1,a
   161A E6                  944 	mov	a,@r0
   161B C3                  945 	clr	c
   161C 97                  946 	subb	a,@r1
   161D FA                  947 	mov	r2,a
   161E 08                  948 	inc	r0
   161F E6                  949 	mov	a,@r0
   1620 09                  950 	inc	r1
   1621 97                  951 	subb	a,@r1
   1622 FB                  952 	mov	r3,a
                            953 ;     genCast
                            954 ;     genPointerSet
                            955 ;     genGenPointerSet
   1623 E5 0D               956 	mov	a,_bp
   1625 24 04               957 	add	a,#0x04
   1627 F8                  958 	mov	r0,a
   1628 86 82               959 	mov	dpl,@r0
   162A 08                  960 	inc	r0
   162B 86 83               961 	mov	dph,@r0
   162D 08                  962 	inc	r0
   162E 86 F0               963 	mov	b,@r0
   1630 EA                  964 	mov	a,r2
   1631 12 3C 02            965 	lcall	__gptrput
                    0241    966 	C$port.c$301$1$1 ==.
                            967 ;../../Source/portable/SDCC/cygnal/port.c:301: return pxStartOfStack;
                            968 ;     genRet
   1634 E5 0D               969 	mov	a,_bp
   1636 24 04               970 	add	a,#0x04
   1638 F8                  971 	mov	r0,a
   1639 86 82               972 	mov	dpl,@r0
   163B 08                  973 	inc	r0
   163C 86 83               974 	mov	dph,@r0
   163E 08                  975 	inc	r0
   163F 86 F0               976 	mov	b,@r0
   1641                     977 00101$:
   1641 85 0D 81            978 	mov	sp,_bp
   1644 D0 0D               979 	pop	_bp
                    0253    980 	C$port.c$302$1$1 ==.
                    0253    981 	XG$pxPortInitialiseStack$0$0 ==.
   1646 22                  982 	ret
                            983 ;------------------------------------------------------------
                            984 ;Allocation info for local variables in function 'sPortStartScheduler'
                            985 ;------------------------------------------------------------
                            986 ;sUsePreemption            Allocated to registers 
                            987 ;------------------------------------------------------------
                    0254    988 	G$sPortStartScheduler$0$0 ==.
                    0254    989 	C$port.c$308$1$1 ==.
                            990 ;../../Source/portable/SDCC/cygnal/port.c:308: portSHORT sPortStartScheduler( portSHORT sUsePreemption )
                            991 ;	-----------------------------------------
                            992 ;	 function sPortStartScheduler
                            993 ;	-----------------------------------------
   1647                     994 _sPortStartScheduler:
   1647 C0 0D               995 	push	_bp
   1649 85 81 0D            996 	mov	_bp,sp
                    0259    997 	C$port.c$315$1$1 ==.
                            998 ;../../Source/portable/SDCC/cygnal/port.c:315: prvSetupTimerInterrupt();	
                            999 ;     genCall
   164C 12 18 B1           1000 	lcall	_prvSetupTimerInterrupt
                    025C   1001 	C$port.c$323$2$2 ==.
                           1002 ;../../Source/portable/SDCC/cygnal/port.c:323: portCOPY_XRAM_TO_STACK();
                           1003 ;     genAssign
   164F 90 18 AB           1004 	mov	dptr,#_pxCurrentTCB
   1652 E0                 1005 	movx	a,@dptr
   1653 FA                 1006 	mov	r2,a
   1654 A3                 1007 	inc	dptr
   1655 E0                 1008 	movx	a,@dptr
   1656 FB                 1009 	mov	r3,a
   1657 A3                 1010 	inc	dptr
   1658 E0                 1011 	movx	a,@dptr
   1659 FC                 1012 	mov	r4,a
                           1013 ;     genPointerGet
                           1014 ;     genGenPointerGet
   165A 8A 82              1015 	mov	dpl,r2
   165C 8B 83              1016 	mov	dph,r3
   165E 8C F0              1017 	mov	b,r4
   1660 12 46 95           1018 	lcall	__gptrget
   1663 F5 09              1019 	mov	_pxXRAMStack,a
   1665 A3                 1020 	inc	dptr
   1666 12 46 95           1021 	lcall	__gptrget
   1669 F5 0A              1022 	mov	(_pxXRAMStack + 1),a
                           1023 ;     genAssign
   166B 75 0B 0D           1024 	mov	_pxRAMStack,#0x0D
                           1025 ;     genAssign
   166E 85 09 82           1026 	mov	dpl,_pxXRAMStack
   1671 85 0A 83           1027 	mov	dph,(_pxXRAMStack + 1)
                           1028 ;     genPointerGet
                           1029 ;     genFarPointerGet
   1674 E0                 1030 	movx	a,@dptr
   1675 F5 08              1031 	mov	_ucStackBytes,a
   1677                    1032 00101$:
                           1033 ;     genPlus
                           1034 ;     genPlusIncr
   1677 05 09              1035 	inc	_pxXRAMStack
   1679 E4                 1036 	clr	a
   167A B5 09 02           1037 	cjne	a,_pxXRAMStack,00108$
   167D 05 0A              1038 	inc	(_pxXRAMStack + 1)
   167F                    1039 00108$:
                           1040 ;     genPlus
                           1041 ;     genPlusIncr
   167F 05 0B              1042 	inc	_pxRAMStack
                           1043 ;     genAssign
   1681 A8 0B              1044 	mov	r0,_pxRAMStack
                           1045 ;     genAssign
   1683 85 09 82           1046 	mov	dpl,_pxXRAMStack
   1686 85 0A 83           1047 	mov	dph,(_pxXRAMStack + 1)
                           1048 ;     genPointerGet
                           1049 ;     genFarPointerGet
   1689 E0                 1050 	movx	a,@dptr
   168A FA                 1051 	mov	r2,a
                           1052 ;     genPointerSet
                           1053 ;     genNearPointerSet
   168B A6 02              1054 	mov	@r0,ar2
                           1055 ;     genMinus
                           1056 ;     genMinusDec
   168D 15 08              1057 	dec	_ucStackBytes
                           1058 ;     genIfx
   168F E5 08              1059 	mov	a,_ucStackBytes
                           1060 ;     genIfxJump
   1691 60 03              1061 	jz	00109$
   1693 02 16 77           1062 	ljmp	00101$
   1696                    1063 00109$:
                           1064 ;     genCast
   1696 85 0B 81           1065 	mov	_SP,_pxRAMStack
                    02A6   1066 	C$port.c$324$2$4 ==.
                           1067 ;../../Source/portable/SDCC/cygnal/port.c:324: portRESTORE_CONTEXT();
                           1068 ;     genInline
   02A6                    1069  pop _bp pop PSW pop ar1 pop ar0 pop ar7 pop ar6 pop ar5 pop ar4 pop ar3 pop ar2 pop b pop DPH pop DPL pop ACC JB ACC.7,0098$ CLR IE.7 LJMP 0099$ 0098$:
   02CA                    1070 SETB IE.7 0099$:
   1699 D0 0D D0           1071 	pop ACC reti 
                    02CF   1072 	C$port.c$327$1$1 ==.
                           1073 ;../../Source/portable/SDCC/cygnal/port.c:327: return pdTRUE;
                           1074 ;     genRet
   169C D0 D0 01           1075 	mov	dpl,#0x01
   169F D0 00 D0           1076 	mov	dph,#0x00
   02D5                    1077 00104$:
   16A2 07 D0 06           1078 	mov	sp,_bp
   16A5 D0 05              1079 	pop	_bp
                    02DA   1080 	C$port.c$328$1$1 ==.
                    02DA   1081 	XG$sPortStartScheduler$0$0 ==.
   16A7 D0                 1082 	ret
                           1083 ;------------------------------------------------------------
                           1084 ;Allocation info for local variables in function 'vPortEndScheduler'
                           1085 ;------------------------------------------------------------
                           1086 ;------------------------------------------------------------
                    02DB   1087 	G$vPortEndScheduler$0$0 ==.
                    02DB   1088 	C$port.c$331$1$1 ==.
                           1089 ;../../Source/portable/SDCC/cygnal/port.c:331: void vPortEndScheduler( void )
                           1090 ;	-----------------------------------------
                           1091 ;	 function vPortEndScheduler
                           1092 ;	-----------------------------------------
   02DB                    1093 _vPortEndScheduler:
   16A8 04 D0              1094 	push	_bp
   16AA 03 D0 02           1095 	mov	_bp,sp
                    02E0   1096 	C$port.c$334$1$1 ==.
                           1097 ;../../Source/portable/SDCC/cygnal/port.c:334: }
   02E0                    1098 00101$:
   16AD D0 F0 D0           1099 	mov	sp,_bp
   16B0 83 D0              1100 	pop	_bp
                    02E5   1101 	C$port.c$334$1$1 ==.
                    02E5   1102 	XG$vPortEndScheduler$0$0 ==.
   16B2 82                 1103 	ret
                           1104 ;------------------------------------------------------------
                           1105 ;Allocation info for local variables in function 'vPortYield'
                           1106 ;------------------------------------------------------------
                           1107 ;------------------------------------------------------------
                    02E6   1108 	G$vPortYield$0$0 ==.
                    02E6   1109 	C$port.c$341$1$1 ==.
                           1110 ;../../Source/portable/SDCC/cygnal/port.c:341: void vPortYield( void ) _naked
                           1111 ;	-----------------------------------------
                           1112 ;	 function vPortYield
                           1113 ;	-----------------------------------------
   02E6                    1114 _vPortYield:
                           1115 ;	naked function: no prologue.
                    02E6   1116 	C$port.c$349$2$2 ==.
                           1117 ;../../Source/portable/SDCC/cygnal/port.c:349: portSAVE_CONTEXT();
                           1118 ;     genInline
   16B3 D0 E0 20 E7 05 C2  1119 	 push ACC push IE clr _EA push DPL push DPH push b push ar2 push ar3 push ar4 push ar5 push ar6 push ar7 push ar0 push ar1 push PSW 
        AF 02 16 BF C0 F0
        C0 02 C0 03 C0 04
        C0 05 C0 06 C0 07
        C0 00 C0 01 C0 D0
                           1120 ;     genAssign
   16BD 75 D0 00           1121 	mov	_PSW,#0x00
                           1122 ;     genInline
   16BD D2 AF              1123 	 push _bp 
                    0309   1124 	C$port.c$350$2$3 ==.
                           1125 ;../../Source/portable/SDCC/cygnal/port.c:350: portCOPY_STACK_TO_XRAM();
                           1126 ;     genAssign
   16BF 90s00r00           1127 	mov	dptr,#_pxCurrentTCB
   16BF D0                 1128 	movx	a,@dptr
   16C0 E0                 1129 	mov	r2,a
   16C1 32                 1130 	inc	dptr
   16C2 75                 1131 	movx	a,@dptr
   16C3 82                 1132 	mov	r3,a
   16C4 01                 1133 	inc	dptr
   16C5 75                 1134 	movx	a,@dptr
   16C6 83                 1135 	mov	r4,a
                           1136 ;     genPointerGet
                           1137 ;     genGenPointerGet
   16C7 00 82              1138 	mov	dpl,r2
   16C8 8B 83              1139 	mov	dph,r3
   16C8 85 0D              1140 	mov	b,r4
   16CA 81 D0 0D           1141 	lcall	__gptrget
   16CD 22*01              1142 	mov	_pxXRAMStack,a
   16CE A3                 1143 	inc	dptr
   16CE C0 0D 85           1144 	lcall	__gptrget
   16D1 81 0D              1145 	mov	(_pxXRAMStack + 1),a
                           1146 ;     genAssign
   16D3 75*03 0E           1147 	mov	_pxRAMStack,#0x0E
                           1148 ;     genMinus
   16D3 85 0D              1149 	mov	a,_SP
   16D5 81 D0              1150 	add	a,#0xf3
   16D7 0D 22              1151 	mov	_ucStackBytes,a
                           1152 ;     genAssign
   16D9 85*01 82           1153 	mov	dpl,_pxXRAMStack
   16D9 C0 E0 C0           1154 	mov	dph,(_pxXRAMStack + 1)
                           1155 ;     genPointerSet
                           1156 ;     genFarPointerSet
   16DC A8 C2              1157 	mov	a,_ucStackBytes
   16DE AF                 1158 	movx	@dptr,a
   0337                    1159 00101$:
                           1160 ;     genIfx
   16DF C0 82              1161 	mov	a,_ucStackBytes
                           1162 ;     genIfxJump
   16E1 C0 83              1163 	jnz	00113$
   16E3 C0 F0 C0           1164 	ljmp	00103$
   033E                    1165 00113$:
                           1166 ;     genPlus
                           1167 ;     genPlusIncr
   16E6 02 C0              1168 	inc	_pxXRAMStack
   16E8 03                 1169 	clr	a
   16E9 C0 04 C0           1170 	cjne	a,_pxXRAMStack,00114$
   16EC 05 C0              1171 	inc	(_pxXRAMStack + 1)
   0346                    1172 00114$:
                           1173 ;     genAssign
   16EE 06 C0 07           1174 	mov	dpl,_pxXRAMStack
   16F1 C0 00 C0           1175 	mov	dph,(_pxXRAMStack + 1)
                           1176 ;     genAssign
   16F4 01 C0              1177 	mov	r0,_pxRAMStack
                           1178 ;     genPointerGet
                           1179 ;     genNearPointerGet
   16F6 D0 75              1180 	mov	ar2,@r0
                           1181 ;     genPointerSet
                           1182 ;     genFarPointerSet
   16F8 D0                 1183 	mov	a,r2
   16F9 00                 1184 	movx	@dptr,a
                           1185 ;     genPlus
                           1186 ;     genPlusIncr
   16FA C0 0D              1187 	inc	_pxRAMStack
                           1188 ;     genMinus
                           1189 ;     genMinusDec
   16FC 90 18              1190 	dec	_ucStackBytes
   16FE AB E0 FA           1191 	ljmp	00101$
   0359                    1192 00103$:
                    0359   1193 	C$port.c$353$1$1 ==.
                           1194 ;../../Source/portable/SDCC/cygnal/port.c:353: vTaskSwitchContext();
                           1195 ;     genCall
   1701 A3 E0 FB           1196 	lcall	_vTaskSwitchContext
                    035C   1197 	C$port.c$357$2$5 ==.
                           1198 ;../../Source/portable/SDCC/cygnal/port.c:357: portCOPY_XRAM_TO_STACK();
                           1199 ;     genAssign
   1704 A3 E0 FC           1200 	mov	dptr,#_pxCurrentTCB
   1707 8A                 1201 	movx	a,@dptr
   1708 82                 1202 	mov	r2,a
   1709 8B                 1203 	inc	dptr
   170A 83                 1204 	movx	a,@dptr
   170B 8C                 1205 	mov	r3,a
   170C F0                 1206 	inc	dptr
   170D 12                 1207 	movx	a,@dptr
   170E 46                 1208 	mov	r4,a
                           1209 ;     genPointerGet
                           1210 ;     genGenPointerGet
   170F 95 F5              1211 	mov	dpl,r2
   1711 09 A3              1212 	mov	dph,r3
   1713 12 46              1213 	mov	b,r4
   1715 95 F5 0A           1214 	lcall	__gptrget
   1718 75 0B              1215 	mov	_pxXRAMStack,a
   171A 0E                 1216 	inc	dptr
   171B E5 81 24           1217 	lcall	__gptrget
   171E F3 F5              1218 	mov	(_pxXRAMStack + 1),a
                           1219 ;     genAssign
   1720 08 85 09           1220 	mov	_pxRAMStack,#0x0D
                           1221 ;     genAssign
   1723 82 85 0A           1222 	mov	dpl,_pxXRAMStack
   1726 83 E5 08           1223 	mov	dph,(_pxXRAMStack + 1)
                           1224 ;     genPointerGet
                           1225 ;     genFarPointerGet
   1729 F0                 1226 	movx	a,@dptr
   172A F5*00              1227 	mov	_ucStackBytes,a
   0384                    1228 00104$:
                           1229 ;     genPlus
                           1230 ;     genPlusIncr
   172A E5 08              1231 	inc	_pxXRAMStack
   172C 70                 1232 	clr	a
   172D 03 02 17           1233 	cjne	a,_pxXRAMStack,00115$
   1730 4C*02              1234 	inc	(_pxXRAMStack + 1)
   1731                    1235 00115$:
                           1236 ;     genPlus
                           1237 ;     genPlusIncr
   1731 05 09              1238 	inc	_pxRAMStack
                           1239 ;     genAssign
   1733 E4 B5              1240 	mov	r0,_pxRAMStack
                           1241 ;     genAssign
   1735 09 02 05           1242 	mov	dpl,_pxXRAMStack
   1738 0A*02 83           1243 	mov	dph,(_pxXRAMStack + 1)
                           1244 ;     genPointerGet
                           1245 ;     genFarPointerGet
   1739 E0                 1246 	movx	a,@dptr
   1739 85                 1247 	mov	r2,a
                           1248 ;     genPointerSet
                           1249 ;     genNearPointerSet
   173A 09 82              1250 	mov	@r0,ar2
                           1251 ;     genMinus
                           1252 ;     genMinusDec
   173C 85 0A              1253 	dec	_ucStackBytes
                           1254 ;     genIfx
   173E 83 A8              1255 	mov	a,_ucStackBytes
                           1256 ;     genIfxJump
   1740 0B 86              1257 	jz	00116$
   1742 02 EA F0           1258 	ljmp	00104$
   03A3                    1259 00116$:
                           1260 ;     genCast
   1745 05 0B 15           1261 	mov	_SP,_pxRAMStack
                    03A6   1262 	C$port.c$358$2$7 ==.
                           1263 ;../../Source/portable/SDCC/cygnal/port.c:358: portRESTORE_CONTEXT();
                           1264 ;     genInline
   03A6                    1265  pop _bp pop PSW pop ar1 pop ar0 pop ar7 pop ar6 pop ar5 pop ar4 pop ar3 pop ar2 pop b pop DPH pop DPL pop ACC JB ACC.7,0098$ CLR IE.7 LJMP 0099$ 0098$:
   03CA                    1266 SETB IE.7 0099$:
   1748 08 02 17           1267 	pop ACC reti 
   03CF                    1268 00107$:
                           1269 ;	naked function: no epilogue.
                    03CF   1270 	C$port.c$359$2$7 ==.
                    03CF   1271 	XG$vPortYield$0$0 ==.
                           1272 ;------------------------------------------------------------
                           1273 ;Allocation info for local variables in function 'vTimer2ISR'
                           1274 ;------------------------------------------------------------
                           1275 ;------------------------------------------------------------
                    03CF   1276 	G$vTimer2ISR$0$0 ==.
                    03CF   1277 	C$port.c$363$2$7 ==.
                           1278 ;../../Source/portable/SDCC/cygnal/port.c:363: void vTimer2ISR( void ) interrupt 5 _naked
                           1279 ;	-----------------------------------------
                           1280 ;	 function vTimer2ISR
                           1281 ;	-----------------------------------------
   03CF                    1282 _vTimer2ISR:
                           1283 ;	naked function: no prologue.
                    03CF   1284 	C$port.c$369$2$2 ==.
                           1285 ;../../Source/portable/SDCC/cygnal/port.c:369: portSAVE_CONTEXT();
                           1286 ;     genInline
   174B 2A E0 C0 A8 C2 AF  1287 	 push ACC push IE clr _EA push DPL push DPH push b push ar2 push ar3 push ar4 push ar5 push ar6 push ar7 push ar0 push ar1 push PSW 
        C0 82 C0 83 C0 F0
        C0 02 C0 03 C0 04
        C0 05 C0 06 C0 07
        C0 00 C0 01 C0 D0
                           1288 ;     genAssign
   174C 75 D0 00           1289 	mov	_PSW,#0x00
                           1290 ;     genInline
   174C 12 0B              1291 	 push _bp 
                    03F2   1292 	C$port.c$370$2$3 ==.
                           1293 ;../../Source/portable/SDCC/cygnal/port.c:370: portCOPY_STACK_TO_XRAM();
                           1294 ;     genAssign
   174E 5A 90 18           1295 	mov	dptr,#_pxCurrentTCB
   1751 AB                 1296 	movx	a,@dptr
   1752 E0                 1297 	mov	r2,a
   1753 FA                 1298 	inc	dptr
   1754 A3                 1299 	movx	a,@dptr
   1755 E0                 1300 	mov	r3,a
   1756 FB                 1301 	inc	dptr
   1757 A3                 1302 	movx	a,@dptr
   1758 E0                 1303 	mov	r4,a
                           1304 ;     genPointerGet
                           1305 ;     genGenPointerGet
   1759 FC 8A              1306 	mov	dpl,r2
   175B 82 8B              1307 	mov	dph,r3
   175D 83 8C              1308 	mov	b,r4
   175F F0 12 46           1309 	lcall	__gptrget
   1762 95 F5              1310 	mov	_pxXRAMStack,a
   1764 09                 1311 	inc	dptr
   1765 A3 12 46           1312 	lcall	__gptrget
   1768 95 F5              1313 	mov	(_pxXRAMStack + 1),a
                           1314 ;     genAssign
   176A 0A 75 0B           1315 	mov	_pxRAMStack,#0x0E
                           1316 ;     genMinus
   176D 0D 85              1317 	mov	a,_SP
   176F 09 82              1318 	add	a,#0xf3
   1771 85 0A              1319 	mov	_ucStackBytes,a
                           1320 ;     genAssign
   1773 83 E0 F5           1321 	mov	dpl,_pxXRAMStack
   1776 08*02 83           1322 	mov	dph,(_pxXRAMStack + 1)
                           1323 ;     genPointerSet
                           1324 ;     genFarPointerSet
   1777 E5*00              1325 	mov	a,_ucStackBytes
   1777 05                 1326 	movx	@dptr,a
   0420                    1327 00101$:
                           1328 ;     genIfx
   1778 09 E4              1329 	mov	a,_ucStackBytes
                           1330 ;     genIfxJump
   177A B5 09              1331 	jnz	00113$
   177C 02 05 0A           1332 	ljmp	00103$
   177F                    1333 00113$:
                           1334 ;     genPlus
                           1335 ;     genPlusIncr
   177F 05 0B              1336 	inc	_pxXRAMStack
   1781 A8                 1337 	clr	a
   1782 0B 85 09           1338 	cjne	a,_pxXRAMStack,00114$
   1785 82 85              1339 	inc	(_pxXRAMStack + 1)
   042F                    1340 00114$:
                           1341 ;     genAssign
   1787 0A 83 E0           1342 	mov	dpl,_pxXRAMStack
   178A FA A6 02           1343 	mov	dph,(_pxXRAMStack + 1)
                           1344 ;     genAssign
   178D 15 08              1345 	mov	r0,_pxRAMStack
                           1346 ;     genPointerGet
                           1347 ;     genNearPointerGet
   178F E5 08              1348 	mov	ar2,@r0
                           1349 ;     genPointerSet
                           1350 ;     genFarPointerSet
   1791 60                 1351 	mov	a,r2
   1792 03                 1352 	movx	@dptr,a
                           1353 ;     genPlus
                           1354 ;     genPlusIncr
   1793 02 17              1355 	inc	_pxRAMStack
                           1356 ;     genMinus
                           1357 ;     genMinusDec
   1795 77*00              1358 	dec	_ucStackBytes
   1796 02s04r20           1359 	ljmp	00101$
   0442                    1360 00103$:
                    0442   1361 	C$port.c$372$1$1 ==.
                           1362 ;../../Source/portable/SDCC/cygnal/port.c:372: vTaskIncrementTick();
                           1363 ;     genCall
   1796 85 0B 81           1364 	lcall	_vTaskIncrementTick
                    0445   1365 	C$port.c$373$1$1 ==.
                           1366 ;../../Source/portable/SDCC/cygnal/port.c:373: vTaskSwitchContext();
                           1367 ;     genCall
   1799 D0 0D D0           1368 	lcall	_vTaskSwitchContext
                    0448   1369 	C$port.c$375$1$1 ==.
                           1370 ;../../Source/portable/SDCC/cygnal/port.c:375: portCLEAR_INTERRUPT_FLAG();
                           1371 ;     genAnd
   179C D0 D0 01           1372 	anl	_T2CON,#0x7F
                    044B   1373 	C$port.c$376$2$5 ==.
                           1374 ;../../Source/portable/SDCC/cygnal/port.c:376: portCOPY_XRAM_TO_STACK();
                           1375 ;     genAssign
   179F D0 00 D0           1376 	mov	dptr,#_pxCurrentTCB
   17A2 07                 1377 	movx	a,@dptr
   17A3 D0                 1378 	mov	r2,a
   17A4 06                 1379 	inc	dptr
   17A5 D0                 1380 	movx	a,@dptr
   17A6 05                 1381 	mov	r3,a
   17A7 D0                 1382 	inc	dptr
   17A8 04                 1383 	movx	a,@dptr
   17A9 D0                 1384 	mov	r4,a
                           1385 ;     genPointerGet
                           1386 ;     genGenPointerGet
   17AA 03 D0              1387 	mov	dpl,r2
   17AC 02 D0              1388 	mov	dph,r3
   17AE F0 D0              1389 	mov	b,r4
   17B0 83 D0 82           1390 	lcall	__gptrget
   17B3 D0 E0              1391 	mov	_pxXRAMStack,a
   17B5 20                 1392 	inc	dptr
   17B6 E7 05 C2           1393 	lcall	__gptrget
   17B9 AF 02              1394 	mov	(_pxXRAMStack + 1),a
                           1395 ;     genAssign
   17BB 17 BF 0D           1396 	mov	_pxRAMStack,#0x0D
                           1397 ;     genAssign
   17BD 85*01 82           1398 	mov	dpl,_pxXRAMStack
   17BD D2 AF 83           1399 	mov	dph,(_pxXRAMStack + 1)
                           1400 ;     genPointerGet
                           1401 ;     genFarPointerGet
   17BF E0                 1402 	movx	a,@dptr
   17BF D0 E0              1403 	mov	_ucStackBytes,a
   0473                    1404 00104$:
                           1405 ;     genPlus
                           1406 ;     genPlusIncr
   17C1 32*01              1407 	inc	_pxXRAMStack
   17C2 E4                 1408 	clr	a
   17C2 B5*01 02           1409 	cjne	a,_pxXRAMStack,00115$
   17C2 C0 E0              1410 	inc	(_pxXRAMStack + 1)
   047B                    1411 00115$:
                           1412 ;     genPlus
                           1413 ;     genPlusIncr
   17C4 C0 A8              1414 	inc	_pxRAMStack
                           1415 ;     genAssign
   17C6 C2 AF              1416 	mov	r0,_pxRAMStack
                           1417 ;     genAssign
   17C8 C0 82 C0           1418 	mov	dpl,_pxXRAMStack
   17CB 83 C0 F0           1419 	mov	dph,(_pxXRAMStack + 1)
                           1420 ;     genPointerGet
                           1421 ;     genFarPointerGet
   17CE C0                 1422 	movx	a,@dptr
   17CF 02                 1423 	mov	r2,a
                           1424 ;     genPointerSet
                           1425 ;     genNearPointerSet
   17D0 C0 03              1426 	mov	@r0,ar2
                           1427 ;     genMinus
                           1428 ;     genMinusDec
   17D2 C0 04              1429 	dec	_ucStackBytes
                           1430 ;     genIfx
   17D4 C0 05              1431 	mov	a,_ucStackBytes
                           1432 ;     genIfxJump
   17D6 C0 06              1433 	jz	00116$
   17D8 C0 07 C0           1434 	ljmp	00104$
   0492                    1435 00116$:
                           1436 ;     genCast
   17DB 00 C0 01           1437 	mov	_SP,_pxRAMStack
                    0495   1438 	C$port.c$377$2$7 ==.
                           1439 ;../../Source/portable/SDCC/cygnal/port.c:377: portRESTORE_CONTEXT();
                           1440 ;     genInline
   0495                    1441  pop _bp pop PSW pop ar1 pop ar0 pop ar7 pop ar6 pop ar5 pop ar4 pop ar3 pop ar2 pop b pop DPH pop DPL pop ACC JB ACC.7,0098$ CLR IE.7 LJMP 0099$ 0098$:
   04B9                    1442 SETB IE.7 0099$:
   17DE C0 D0 75           1443 	pop ACC reti 
   04BE                    1444 00107$:
                           1445 ;	naked function: no epilogue.
                    04BE   1446 	C$port.c$378$2$7 ==.
                    04BE   1447 	XG$vTimer2ISR$0$0 ==.
                           1448 ;------------------------------------------------------------
                           1449 ;Allocation info for local variables in function 'prvSetupTimerInterrupt'
                           1450 ;------------------------------------------------------------
                           1451 ;ulTicksPerSecond          Allocated to registers 
                           1452 ;ulCaptureTime             Allocated to registers 
                           1453 ;ulCaptureValue            Allocated to registers 
                           1454 ;ucLowCaptureByte          Allocated to registers 
                           1455 ;ucHighCaptureByte         Allocated to registers 
                           1456 ;------------------------------------------------------------
                    04BE   1457 	F______Source_portable_SDCC_cygnal_port$prvSetupTimerInterrupt$0$0 ==.
                    04BE   1458 	C$port.c$391$2$7 ==.
                           1459 ;../../Source/portable/SDCC/cygnal/port.c:391: static void prvSetupTimerInterrupt( void )
                           1460 ;	-----------------------------------------
                           1461 ;	 function prvSetupTimerInterrupt
                           1462 ;	-----------------------------------------
   04BE                    1463 _prvSetupTimerInterrupt:
   17E1 D0 00              1464 	push	_bp
   17E3 C0 0D 90           1465 	mov	_bp,sp
                    04C3   1466 	C$port.c$413$1$1 ==.
                           1467 ;../../Source/portable/SDCC/cygnal/port.c:413: RCAP2L = ucLowCaptureByte;
                           1468 ;     genAssign
   17E6 18 AB E0           1469 	mov	_RCAP2L,#0x19
                    04C6   1470 	C$port.c$414$1$1 ==.
                           1471 ;../../Source/portable/SDCC/cygnal/port.c:414: RCAP2H = ucHighCaptureByte;
                           1472 ;     genAssign
   17E9 FA A3 E0           1473 	mov	_RCAP2H,#0xE0
                    04C9   1474 	C$port.c$419$1$1 ==.
                           1475 ;../../Source/portable/SDCC/cygnal/port.c:419: TL2 = ucLowCaptureByte;
                           1476 ;     genAssign
   17EC FB A3 E0           1477 	mov	_TL2,#0x19
                    04CC   1478 	C$port.c$420$1$1 ==.
                           1479 ;../../Source/portable/SDCC/cygnal/port.c:420: TH2 = ucHighCaptureByte;
                           1480 ;     genAssign
   17EF FC 8A 82           1481 	mov	_TH2,#0xE0
                    04CF   1482 	C$port.c$423$1$1 ==.
                           1483 ;../../Source/portable/SDCC/cygnal/port.c:423: IE |= portTIMER_2_INTERRUPT_ENABLE;
                           1484 ;     genOr
   17F2 8B 83 8C           1485 	orl	_IE,#0x20
                    04D2   1486 	C$port.c$428$1$1 ==.
                           1487 ;../../Source/portable/SDCC/cygnal/port.c:428: T2CON = portENABLE_TIMER;
                           1488 ;     genAssign
   17F5 F0 12 46           1489 	mov	_T2CON,#0x04
   04D5                    1490 00101$:
   17F8 95 F5 09           1491 	mov	sp,_bp
   17FB A3 12              1492 	pop	_bp
                    04DA   1493 	C$port.c$432$1$1 ==.
                    04DA   1494 	XF______Source_portable_SDCC_cygnal_port$prvSetupTimerInterrupt$0$0 ==.
   17FD 46                 1495 	ret
                           1496 	.area CSEG    (CODE)
                           1497 	.area XINIT   (CODE)
