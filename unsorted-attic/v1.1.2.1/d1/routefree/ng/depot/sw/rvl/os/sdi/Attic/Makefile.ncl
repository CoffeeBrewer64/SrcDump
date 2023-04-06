a0 39
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

LCDEFS += -DIOS_ENABLE #-DSD_DEBUG_LOG
LCINCS += -I../ios -I.
LLDLIBS = -lsys -lioslibc -lios
LLDOPTS += -Ttext=$(MK_SD0_VIRT_START) -Tddr.link -Tphys.link

LDIRT += *.bin *.elf phys.link

TARGETS = sdi.elf

CFILES = \
	sdi_ops.c \
	sdi_utils.c \
	sdi_mgr.c

HEADERS = \
	sdi_ops.h \
	sdi_utils.h \
	sdi_host.h

default: $(TARGETS)

headers: $(HEADERS)
	$(INSTALL) $(HEADERS) $(ROOT)/usr/include/rvl

exports: sdi.elf
	$(INSTALL) sdi.elf $(ROOT)/usr/bin/rvl

include $(COMMONRULES)


sdi.elf: $(CRT0) $(OBJECTS) phys.link
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(CRT0) $(OBJECTS) $(LDLIBS) 

phys.link: phys.sed $(NG_ADDR_MAP)
	sed -e 's/@@SDI_PHYS_START@@/$(MK_SD0_PHYS_START)/g' phys.sed > $@
