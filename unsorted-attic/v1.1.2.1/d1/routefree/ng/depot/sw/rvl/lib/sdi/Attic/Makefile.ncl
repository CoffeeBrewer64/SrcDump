a0 21
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

LCDEFS += -DSD_DEBUG_LOG #-DENABLE_SD_HISPD

TARGETS = libsdi.a

CFILES = sdi_api.c

LIB_TARGETS = libsdi.a

default: $(TARGETS)

exports install: $(TARGETS)
	$(INSTALL) -m 444 $(TARGETS) $(ROOT)/usr/lib/rvl

include $(COMMONRULES)

$(TARGETS): $(OBJECTS)
	ar rc $@ $^
