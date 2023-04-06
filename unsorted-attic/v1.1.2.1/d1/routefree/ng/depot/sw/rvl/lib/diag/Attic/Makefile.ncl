a0 43
include $(ROOT)/usr/include/make/NGdefs

INSTALLDIR=$(ROOT)/usr/lib/rvl

OPTIMIZER = -O2

# LCDEFS += -DUSE_SRAM_ONLY
LCINCS += -I. -I$(ROOT)/usr/include/rvl -I$(ROOT)/usr/include/rvl/diag
LASINCS += -I. -I$(ROOT)/usr/include/rvl -I$(ROOT)/usr/include/rvl/diag

CFILES = \
	aes_api.c \
	aes.c \
	aes_imp.c \
	sha1.c \
	aes_hal.c \
	aes_sha_sw.c \
	aes_test.c \
	sha_hal.c \
	sha_test.c \
	iop_utils.c \
	getopt.c \
	mmu.c \
	interrupt.c \
	setup.c

ASFILES = \
	util.s \
	int.s \
	mmu1.s 

TARGETS = libdiagutils.a

default: $(TARGETS)

exports install: default
	$(INSTALL) -m 444 $(TARGETS) $(INSTALLDIR)

$(TARGETS): $(OBJECTS)
	$(AR) rc $@ $^ 

include $(COMMONRULES)

