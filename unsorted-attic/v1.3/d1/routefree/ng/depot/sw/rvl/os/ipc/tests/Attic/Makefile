include $(ROOT)/usr/include/make/NGdefs

TESTS= ipcrm.elf

TARGETS = $(TESTS)

default: $(TARGETS)

include $(COMMONRULES)

LLDLIBS = -lsys -lioslibc -liossyscall 
LDIRT += *.bin *.elf
CFLAGS += -I../ios -I.
#CFLAGS += -I../ios -I. -DLOG_FL

DDR_LDFLAGS =  $(LDLIBS) $(LDFLAGS) -T$(ROOT)/usr/lib/rvl/ddr.link 

ipcrm.elf: $(CRT0) ipcrm.o
	$(CC) $(CFLAGS) -o $@ $^ $(DDR_LDFLAGS) -Ttext=0x13f20000

%.elf: $(CRT0)  %.o 
	$(CC) $(CFLAGS) -o $@ $^ $(DDR_LDFLAGS)

install: $(TESTS)
	$(INSTALL) $(TESTS) $(ROOT)/usr/bin/rvl

