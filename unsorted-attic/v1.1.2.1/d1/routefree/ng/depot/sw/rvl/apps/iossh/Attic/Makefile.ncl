a0 27
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

IOSSHLIB=libiossh.a
TARGETS = $(IOSSHLIB)

CFILES = iossh.c
LIBOBJS = $(CFILES:.c=.o)

default: $(TARGETS)

exports install: default
	$(INSTALL) $(TARGETS) $(ROOT)/usr/lib/rvl

include $(COMMONRULES)

LDIRT += $(TARGETS)
BUILD_TIME := $(shell date +"%D %r")
LCDEFS = -DBUILD_TIME='"$(BUILD_TIME)"'
LCDEFS += -DBUILD_DATE='$(BUILD_DATE)' -DVERSION='$(VERSION)'
LCOPTS += -mlong-calls

LLDLIBS = -lapputils 

$(IOSSHLIB): $(LIBOBJS)
	$(AR) $(ARFLAGS) $@ $^
