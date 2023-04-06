initndb	macro	mMap,mObj,mmode,mseqno
mcount	=	-1
	db	mMap
	db	mObj
	db	mmode
	ndbequ	mseqno
	endm


ndb	macro	mMap,mObj,mmode,mseqno
	db	mMap
	db	mObj
	db	mmode
	ndbequ	mseqno
	endm

ndbequ	macro	mcountequ
mcount		=	mcount + 1
mcountequ	equ	mcount
	endm



ndw_seq	macro	mroutine,mseqno,value
	dw	mroutine
	ndwadd	mseqno,value
	endm


ndwadd	macro	mcountequ_ndw,vle
mcount		=	mcount + vle
mcountequ_ndw	equ	mcount
	endm












