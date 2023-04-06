;===============================================================
;
;	Printer.h
;			1998 Tetsu
;
;===============================================================
ef_initndw	macro
mcount	=	0	
	endm

ef_inc_ndw	macro	maddress
	dw	maddress
mcount	=	mcount + 1
	endm

ef_ndw_g	macro	maddress,mequno
	dw	maddress
mequno	equ	mcount
mcount	=	mcount + 1
	public	mequno
	endm

ef_ndw		macro	maddress,mequno
	dw	maddress
mequno	equ	mcount
mcount	=	mcount + 1
	endm

PREAMBLE_1	equ	88h
PREAMBLE_2	equ	33h
DUMMY_DATA	equ	00h
NULL_DATA1	equ	0Fh
NULL_DATA2	equ	00h
BREAK_DATA	equ	08h



PrinterWorkTop		equ	ram_map

SeqNo			equ	PrinterWorkTop
TransCounter		equ	1+SeqNo
HeaderBuffer		equ	1+TransCounter
CheckSumBuffer		equ	4+HeaderBuffer
TransDataBuffer		equ	2+CheckSumBuffer
PrinterStatus		equ	280h+TransDataBuffer
NULLcount		equ	2+PrinterStatus
WaitCount		equ	1+NULLcount

PSIO_TransDataPointer	equ	1+WaitCount
PSIO_TransDataCounter	equ	2+PSIO_TransDataPointer

PRTOUT_DmyVram		equ	2+PSIO_TransDataCounter
PrinterStatusMSGNo	equ	20*18+PRTOUT_DmyVram

PRT_WaitFlag		equ	1+PrinterStatusMSGNo
PRT_FeedCounter		equ	1+PRT_WaitFlag
PRT_Contrast		equ	1+PRT_FeedCounter

PrinterWork		equ	1+PRT_Contrast

 ifn	ASSEMBLE__ENGLISH
TransMaxLine		equ	10h+PrinterWork		; ì]ëóÉâÉCÉìêî (1◊≤›==40*2∑¨◊) 
PrinterWorkEnd		equ	1+TransMaxLine

PRT_work0		equ	PrinterWorkEnd
PRT_work1		equ	1+PRT_work0
PRT_work2		equ	1+PRT_work1
PRT_work3		equ	1+PRT_work2
PRT_work4		equ	1+PRT_work3

 else
PrinterWorkEnd		equ	10h+PrinterWork
 endif

