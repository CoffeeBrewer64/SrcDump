
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

