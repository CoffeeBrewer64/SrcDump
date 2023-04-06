include $(ROOT)/usr/include/make/NGdefs

TESTS= \
	  ipcsrv.elf

TARGETS = $(TESTS)

default: $(TARGETS)

include $(COMMONRULES)

LLDLIBS = -lsys -lioslibc -liossyscall 
LDIRT += *.bin *.elf

#CFLAGS += -I../../../rvl/os/ios -I. -DLOG_FL
CFLAGS += -I../../../rvl/os/ios -I.
SUBDIRS = tests

DDR_LDFLAGS =  $(LDLIBS) $(LDFLAGS) -T$(ROOT)/usr/lib/rvl/ddr.link 

ipcsrv.elf: $(CRT0) ipcsrv.o
	$(CC) $(CFLAGS) -o $@ $^ $(DDR_LDFLAGS) -Ttext=0x13f10000

%.elf: $(CRT0)  %.o 
	$(CC) $(CFLAGS) -o $@ $^ $(DDR_LDFLAGS)

install: $(TESTS)
	$(INSTALL) $(TESTS) $(ROOT)/usr/bin/rvl

