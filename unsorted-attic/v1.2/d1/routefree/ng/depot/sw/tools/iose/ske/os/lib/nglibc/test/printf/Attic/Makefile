include $(ROOT)/usr/include/make/SKEdefs

TARGETS = printf-tst

VPATH = ..

CFILES =\
        printf-tst.c

default: $(TARGETS)

include $(COMMONRULES)


LLDLIBS = -lnglibc
LLDOPTS = -L$(ROOT)/usr/lib/ng

runtests: $(TARGETS)
	./printf-tst> test.out
	cmp gold.out test.out  && rm -f test.out
