include $(ROOT)/usr/include/make/IOSEdefs

TARGETS = printf-tst

VPATH = ..

CFILES =\
        printf-tst.c

default: $(TARGETS)

include $(COMMONRULES)


LLDLIBS = -lioslibc
LLDOPTS = -L$(ROOT)/usr/lib/ios

runtests: $(TARGETS)
	./printf-tst> test.out
	cmp gold.out test.out  && rm -f test.out
