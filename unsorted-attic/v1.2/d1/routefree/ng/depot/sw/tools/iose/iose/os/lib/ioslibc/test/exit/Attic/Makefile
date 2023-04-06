include $(ROOT)/usr/include/make/IOSEdefs

TARGETS = exit-tst

VPATH = ..

CFILES =\
        exit-tst.c

default: $(TARGETS)

include $(COMMONRULES)


LLDLIBS = -lioslibc
LLDOPTS = -L$(ROOT)/usr/lib/ios

runtests: $(TARGETS)
	./exit-tst
