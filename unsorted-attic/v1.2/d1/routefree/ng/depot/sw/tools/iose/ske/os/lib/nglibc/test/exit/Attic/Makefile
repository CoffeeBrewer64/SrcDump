include $(ROOT)/usr/include/make/SKEdefs

TARGETS = exit-tst

VPATH = ..

CFILES =\
        exit-tst.c

default: $(TARGETS)

include $(COMMONRULES)


LLDLIBS = -lnglibc
LLDOPTS = -L$(ROOT)/usr/lib/ng

runtests: $(TARGETS)
	./exit-tst
