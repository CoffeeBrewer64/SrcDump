;------------;
; macro code ;
;------------;

GET	macro	xx,yy
	ld	a,(actlow)
;	ifn	yy			; Y=0  actlow       = L reg
;	 else
;	 ifn	yy			; Y=1  actlow + 1   = L reg
;	  inc	a
;	 else
	  add	a,yy			; Y=>2 actlow + val = L reg
;	 endif
;	endif
	ld	xx,a
	endm

ADDM	macro	xx,yy
;	ifn	(yy == 0)		; Y=0  No action
;	 else
;	 ifn	(yy == 1)		; Y=1  L reg + 1
;	  inc	xx
;	 else
	  ld	a,xx			; Y=>2 L reg + Y = L reg
	  add	a,yy
	  ld	xx,a
;	 endif
;	endif
	endm

;--- S_POS HL = DMY_VRAM + Y*20 + X only
S_POS 	macro	xx,yy			; Start Position ( Window,Message )
	ld	hl,yy*20+dmy_vram + xx
	endm

;---- E_POS BC = Y*256 + X only
E_POS	macro   xx,yy			; End Position ( Window )
	ld	bc,yy*256 + xx
	endm

;---- PSH_BTN ... Check Push Key 
PSH_BTN	macro numm,inn
	bit	numm,inn
	endm

;---- Set Message Position .... In : Locate X,Locate Y,Message Address
SET_MSG_POS macro xx,yy,madrs
	ld	hl,yy*20 + dmy_vram + xx
	ld	de,madrs
	endm

;---- Set Window Position ..... In : START_X,START_Y,END_X,END_Y
;        Compute BC Register Set End Position Non Compute Number
SET_WIN_POS macro sxx,syy,exx,eyy
	ld	hl,syy*20 + dmy_vram + sxx
;	ld	b,eyy - syy - 1		; B = End Pos - Start Pos - 1(Y)
;	ld	c,exx - sxx - 1		; C = End Pos - Start Pos - 1(X)
	ld	bc,eyy - syy - 1 * 0100h + exx - sxx - 1
	endm

;---- Set Block Position ..... In : START_X,START_Y,END_X,END_Y
;        Compute BC Register Set End Position Non Compute Number
SET_BLOCK   macro sxx,syy,exx,eyy
	ld	hl,syy*20 + dmy_vram + sxx
;	ld	b,eyy - syy  	; B = End Pos - Start Pos (Y)
;	ld	c,exx - sxx 	; C = End Pos - Start pos (X)
	ld	bc,eyy - syy * 0100h + exx - sxx 
	endm

;------- Set Window Mode ... disp_win_mode in data set
SET_WIN_MOD macro md
	ld	a,md
	ld	(disp_win_mode),a
	endm


CALL_HL	macro 	 
	ld	de,mlabel$
	push	de

	jp	(hl)

mlabel$:
	endm


bset	macro	mbit,mflagset
	push	hl

	ld	hl,mflagset
	bit	mbit,(hl)
	set	mbit,(hl)

	pop	hl

	endm

bclr	macro	mbit,mflagset
	push	hl

	ld	hl,mflagset
	bit	mbit,(hl)
	res	mbit,(hl)

	pop	hl

	endm

btst	macro	mbit,mflagset
	push	hl

	ld	hl,mflagset
	bit	mbit,(hl)

	pop	hl

	endm

a_push	macro
	push	hl
	push	de
	push	bc

	endm

a_pop	macro
	pop	bc
	pop	de
	pop	hl

	endm


;-------------------------------;
; sequence routine table define ;
;-------------------------------;
msgndw	macro	mroutine,mseqno
mcount	=	0
	dw	mroutine
	ndwequ	mseqno
	endm


initndw	macro	mroutine,mseqno
mcount	=	-1
	dw	mroutine
	ndwequ	mseqno
	endm

ndw	macro	mroutine,mseqno
	dw	mroutine
	ndwequ	mseqno
	endm

ndwequ	macro	mcountequ_ndw
mcount		=	mcount + 1
mcountequ_ndw	equ	mcount
	endm





