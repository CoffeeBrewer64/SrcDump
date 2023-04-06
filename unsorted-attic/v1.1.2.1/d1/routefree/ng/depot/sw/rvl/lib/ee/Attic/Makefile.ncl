a0 26
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

TARGETS = libee.a

HFILES = \
    ee.h

CFILES = \
    ee_basic.c \
    ee_api.c

default: $(TARGETS)

headers: $(HFILES)
	$(INSTALL) -m 444 $(HFILES) $(ROOT)/usr/include/rvl

exports: $(TARGETS)
	$(INSTALL) -m 444 $(TARGETS) $(ROOT)/usr/lib/rvl

$(TARGETS): %: %($(OBJECTS))
	ar cru $@ $?

include $(COMMONRULES)

