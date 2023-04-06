include $(ROOT)/usr/include/make/NGdefs

LCDEFS += -DISFS_DISABLE_SECURITY -DFL_DEBUG_LOG -DFS_DEBUG_LOG
# LLDOPTS += -Ttext $(MK_FS_START) -Tbss ${MK_FS_BSS_START} -T $(DA_LINK)

LLDLIBS = -lsys -lioslibc -liossyscall 
LDIRT += *.bin *.elf
CFLAGS += -I../ios -I.

TARGETS = sdio_test.elf \
#    libintsdio.a \
#    libintsd.a

CFILES = \
	sdio_serial.c \
	sdio_util.c \
	sd_slot.c \
	sdio_test.c \
	sdio_rm.c \
	sdio_api.c \
	sd_api.c \
	sdio_api_test.c \
	sd_api_test.c \
	test_util.c

HEADERS = \
    sdio_test.h \
    sdio_api_test.h \
	sd_api_test.h

default: $(TARGETS)

headers: $(HEADERS)
	$(INSTALL) $(HEADERS) $(ROOT)/usr/include/rvl

# SUBDIRS = test

include $(COMMONRULES)

#DDR_LDFLAGS =  $(LDLIBS) $(LDFLAGS) -Ttext=0x10010000
DDR_LDFLAGS =  $(LDLIBS) $(LDFLAGS) -T$(ROOT)/usr/lib/rvl/ddr.link 

sdio_test.elf: $(CRT0) $(OBJECTS)
	$(CC) $(CFLAGS) $(DDR_LDFLAGS) -o $@ $^ $(LDLIBS) 

