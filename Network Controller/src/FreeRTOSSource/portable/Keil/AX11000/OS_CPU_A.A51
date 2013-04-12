
$NOMOD51
; 
; The uC/OS II port for Dallas 80C390 on Keil C51 V7
;
; Ported date:     Dec 2, 2003
; By:              Stuart Wright (swright@jiskoot.com)
; Target platform: Keil C51 V7.07 and above 

; Based on port for 8051 by John X. Liu, China, (johnxliu@163.com)

	NAME	OS_CPU_A_ASM

; ?C_XBP is the simulated external stack pointer in large mode, but its origianal
; declare makes it can not be used in c files, so redeclare it in this module 
; insteading of the old one
	PUBLIC	?C_XBP, C_XBP, TICK_INT				;

	EXTRN   CODE(_?vPortContextSwitch)
	EXTRN   CODE(_?vIntPortContextSwitch)
	PUBLIC	_?LoadCtx, STACK_START, _?KCOSCtxSw, _?vPortYield

#include "reg80390.h"

LoadXBP	MACRO
		MOV 	DPX,#0
		MOV	DPH, C_XBP
		MOV	DPL, C_XBP+1
	ENDM

SaveXBP MACRO
		PUSH	IE
		CLR	EA
		MOV	C_XBP,   DPH
		MOV	C_XBP+1, DPL
		POP	IE
	ENDM

LoadREG	MACRO   REG
		MOVX	A,   @DPTR
		MOV	REG, A
	ENDM

SaveREG MACRO   REG
		MOV	A,	REG
		MOVX	@DPTR,  A
	ENDM

; The PUSHA now emulates the pushing sequence what Keil C does.
PUSHR	MACRO
;		IRP	REG,	<ACC, B, DPX, DPH, DPL, DPX1, DPH1, DPL1, DPS, PSW, 0, 1, 2, 3, 4, 5, 6, 7> ;Code for two DPTR's
		IRP	REG,	<ACC, B, DPX, DPH, DPL, PSW, 0, 1, 2, 3, 4, 5, 6, 7> ;Code for one DPTR ; Code for one DPTR
		PUSH	REG
		ENDM
	ENDM

POPR	MACRO
;		IRP	REG,	<7, 6, 5, 4, 3, 2, 1, 0, PSW, DPS, DPL1, DPH1, DPX1, DPL, DPH, DPX, B, ACC> ;Code for two DPTR's
		IRP	REG,	<7, 6, 5, 4, 3, 2, 1, 0, PSW, DPL, DPH, DPX, B, ACC> ;Code for one DPTR ; Code for one DPTR
		POP	REG
		ENDM
	ENDM

; Declare the external stack pointer by ourself, so that we can use it freely.
; you know, in the name of '?C_XBP' it can not be used in c modules but in the 
; name of 'C_XBP' it can do.
DT?C_XBP	SEGMENT	DATA
		RSEG	DT?C_XBP
?C_XBP:					; These two labels point to the same address
C_XBP:					;
	DS	2
TICK_INT:					;
	DS	1
IEREG:
        DS      1 

; Declare a label 'Stack' in the hardware stack segment so that we know where it begins.
?STACK		SEGMENT		IDATA
		RSEG	?STACK
STACK_START:
	DS	1

; Load context from the external stack pointed by C_XBP
PR?LoadCtx      SEGMENT CODE
	RSEG	PR?LoadCtx
_?LoadCtx:
	LoadXBP					; Load the C_XBP to DPTR

	LoadREG	SP				; Load the hardware stack pointer
	INC	DPTR				;

        MOV     R0, SP				; Now we pop the hardware stack
LC_1:						; from the external one.
	LoadREG	@R0				; Did not use the PUSH ACC instruction for if we want to
	INC     DPTR				; do so, we have to DEC DPTR, which costs much.
	DEC     R0				;
	CJNE    R0, #BYTE0 (STACK_START-1), LC_1		;

	SaveXBP					; after the hardware stack has been popped,
						; the external stack pointer should be adjusted

RestoreCtx:

        POP	ACC				; Safe way to do the same thing.
	ANL	A,#0x80				;
        MOV     IEREG,IE
	ORL     IEREG,A
						; Now that the context has been loaded into hardware
 	POPR					; stack, what we need do is just popping them upto registers.
        MOV     IE,IEREG

	RET					; Now everything is ready, a RET will bring the task to run.

; Task level context switch entry point, which is intended to be called by task gracefully. 
_?OSCtxSw:
_?vPortYield:
	PUSHR					; Save current context first into hardware stack
	PUSH	IE
	CLR EA
; _?KCOSCtxSw:					; Now begin pushing hardware stack to external one
	LoadXBP					; Load the external stack pointer first to prepare storing 
						; data into it.

	MOV	A, SP				; Calculate how much memory in external stack needed
	CLR	C				; so that we can adjust the external stack pointer
	SUBB	A, #BYTE0 (STACK_START-1)			; Calculated the length of hardware stack

	MOV	R0, A				; Save the length of hardware stack to R0, which is used as a counter on saving hardware stack.

	INC	A				; Add the space for storing SP

	CLR	C
	XCH	A, DPL				; Now ACC contains the right amount of external stack memory should be used.
	SUBB	A, DPL				; Adjust the external pointer.stored in DPTR to make to point to the new stack top from where we will store hardware stack.
	JNC	SC_1
	DEC	DPH
SC_1:
	MOV	DPL,A				; Now DPTR contains the external stack pointer after pushing context into external stack.

	SaveXBP					; Save to external stack pointer.
						; Keeps the DPTR containing the external stack pointer still.
	SaveREG SP				; Save hardware stack pointer in the top of external stack

SC_2:
	INC	DPTR				;
	POP	ACC				; Pop the data from hareware stack
	MOVX	@DPTR, A			; and save into external one.
	DJNZ    R0, SC_2			; Remember, R0 contains the hardware stack's length.

	LJMP	_?vPortContextSwitch			; 


_?KCOSCtxSw:					; Now begin pushing hardware stack to external one
	LoadXBP					; Load the external stack pointer first to prepare storing 
						; data into it.

	MOV	A, SP				; Calculate how much memory in external stack needed
	CLR	C				; so that we can adjust the external stack pointer
	SUBB	A, #BYTE0 (STACK_START-1)			; Calculated the length of hardware stack

	MOV	R0, A				; Save the length of hardware stack to R0, which is used as a counter on saving hardware stack.

	INC	A				; Add the space for storing SP

	CLR	C
	XCH	A, DPL				; Now ACC contains the right amount of external stack memory should be used.
	SUBB	A, DPL				; Adjust the external pointer.stored in DPTR to make to point to the new stack top from where we will store hardware stack.
	JNC	SC_3
	DEC	DPH
SC_3:
	MOV	DPL,A				; Now DPTR contains the external stack pointer after pushing context into external stack.

	SaveXBP					; Save to external stack pointer.
						; Keeps the DPTR containing the external stack pointer still.
	SaveREG SP				; Save hardware stack pointer in the top of external stack

SC_4:
	INC	DPTR				;
	POP	ACC				; Pop the data from hareware stack
	MOVX	@DPTR, A			; and save into external one.
	DJNZ    R0, SC_4			; Remember, R0 contains the hardware stack's length.

	LJMP	_?vIntPortContextSwitch			; 

	END
