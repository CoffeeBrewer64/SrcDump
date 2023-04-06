include $(ROOT)/usr/include/make/IOSEdefs

TARGETS = string-tst

VPATH = ..

CFILES =\
        string-tst.c

default: $(TARGETS)

include $(COMMONRULES)


LLDLIBS = -lioslibc

runtests: $(TARGETS)
	./string-tst
