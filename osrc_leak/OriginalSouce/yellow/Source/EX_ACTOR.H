;*********************************************************
;**							**
;**     POCKET MONSTER ACTOR				**
;**							**
;**							**
;*********************************************************
ActorWorkTop	equ	dmy_map
EntryActor	equ	ActorWorkTop
ActorWork	equ	20 +EntryActor
Act_Total	equ	0a0h +ActorWork	;10h*10
OAM_Address	equ	1 +Act_Total
Act_No		equ	1 +OAM_Address
A_VRAM_Offset	equ	1 +Act_No
A_Header	equ	1 +A_VRAM_Offset
A_Animetion	equ	2 +A_Header
A_Move		equ	2 +A_Animetion
A_Pat		equ	2 +A_Move

A_work0		equ	2 +A_Pat
A_work1		equ	1 +A_work0
A_work2		equ	1 +A_work1
A_work3		equ	1 +A_work2
A_work4		equ	1 +A_work3
A_work5		equ	1 +A_work4

Actor_OY	equ	1 +A_work5
Actor_OX	equ	1 +Actor_OY

ActorWorkEnd	equ	1 +Actor_OX

;=======================================;
;	EQU				;
;=======================================;
A_MAX		equ	10
ACTOR_LEN	equ	10h
ACTORCHR_MAX	equ	080h
OAM_END_VALUE	equ	0a0h

POSREV		equ	00000001b
PAL2		equ	00010000b
HREV		equ	00100000b
VREV		equ	01000000b
PRI_BG		equ	10000000b

;---------------------------------------;
;	EFFECT ANM EQU			;
;---------------------------------------;
ANMstop		equ	-1
ANMloop		equ	-2
ANMbanish	equ	-3
ANMdel		equ	-4

ANM_HREV	equ	01000000b
ANM_VREV	equ	10000000b

;---------------------------------------;
;	EFFECT ACTOR TABLE EQU		;
;---------------------------------------;
ACTOR_NO	equ	0		;0
ACTOR_ANM	equ	ACTOR_NO+1	;1
ACTOR_MV	equ	ACTOR_ANM+1	;2
ACTOR_COF	equ	ACTOR_MV+1	;3
ACTOR_X		equ	ACTOR_COF+1	;4
ACTOR_Y		equ	ACTOR_X+1	;5
ACTOR_DX	equ	ACTOR_Y+1	;6
ACTOR_DY	equ	ACTOR_DX+1	;7
ACTOR_AWT	equ	ACTOR_DY+1	;8
ACTOR_AWO	equ	ACTOR_AWT+1	;9
ACTOR_AOF	equ	ACTOR_AWO+1	;a
ACTOR_WK0	equ	ACTOR_AOF+1	;b
ACTOR_WK1	equ	ACTOR_WK0+1	;c
ACTOR_WK2	equ	ACTOR_WK1+1	;d
ACTOR_WK3	equ	ACTOR_WK2+1	;e
ACTOR_WK4	equ	ACTOR_WK3+1	;f







