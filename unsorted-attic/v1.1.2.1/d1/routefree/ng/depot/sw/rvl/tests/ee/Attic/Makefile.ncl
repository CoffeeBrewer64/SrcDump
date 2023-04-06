a0 53
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

#LCDEFS += -DEEPROM_DEBUG

LCINCS += -I. -I $(ROOT)/usr/include/rvl
LLDLIBS += -lee -lioslibc -lsys

MON_CRT0 = $(ROOT)/usr/lib/rvl/crt0_noOS.o
MON_LDFLAGS = $(LDLIBS) $(LDFLAGS) -T$(ROOT)/usr/lib/rvl/sdram.link

STDALONE_LDFLAGS =  $(LDLIBS) $(LDFLAGS) -T $(ROOT)/usr/lib/rvl/stdalone.link

HFILES = ee_int.h

CFILES = \
        ee.c eefuse.c eetest.c ee_dv.c

include $(COMMONRULES)

#Standalone programs
STDALONE_TGTS= ee_dv.elf  eetest.elf eefuse.elf eetest2.elf

#Targets to be run with minimon
# MON_TGTS = $(CFILES:.c=.elf)

TARGETS = $(STDALONE_TGTS)

default: $(TARGETS)

ee_dv.elf : ../init.o ee_dv.o 
	$(CC) $(CFLAGS) -o $@  $^ $(STDALONE_LDFLAGS) 

ee_dv_sram.o: ee_dv.c
	$(CC) $(CFLAGS) -DSTDALONE -o $@  -c $^ 

eetest.elf : ../init.o eetest.o ee.o
	$(CC) $(CFLAGS) -o $@  $^ $(STDALONE_LDFLAGS) 

eetest2.elf : ../init.o eetest_libee.o ee_libee.o
	$(CC) $(CFLAGS) -DUSE_LIBEE -o $@  $^ $(STDALONE_LDFLAGS) 

eetest_libee.o : eetest.c
	$(CC) $(CFLAGS) -DUSE_LIBEE -o $@  -c $^ 

ee_libee.o : ee.c
	$(CC) $(CFLAGS) -DUSE_LIBEE -o $@  -c $^ 

eefuse.elf : ../init.o eefuse.o ee.o
	$(CC) $(CFLAGS) -o $@  $^ $(STDALONE_LDFLAGS) 
	

