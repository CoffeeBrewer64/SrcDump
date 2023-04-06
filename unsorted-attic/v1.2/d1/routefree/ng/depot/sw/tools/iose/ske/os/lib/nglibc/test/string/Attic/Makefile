include $(ROOT)/usr/include/make/SKEdefs

TARGETS = string-tst

VPATH = ..

CFILES =\
        string-tst.c

default: $(TARGETS)

include $(COMMONRULES)


LLDLIBS = -lnglibc
LLDOPTS = -L$(ROOT)/usr/lib/ng

runtests: $(TARGETS)
	./string-tst
