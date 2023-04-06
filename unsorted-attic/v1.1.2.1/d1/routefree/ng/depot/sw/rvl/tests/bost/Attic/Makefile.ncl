a0 71

# compile for all types

include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

INSTALLDIR = $(ROOT)/usr
CFILES = \
	aes.c \
	sha.c \
	mem.c \
	dma.c \
	mmu.c

LCINCS  += -I$(INSTALLDIR)/include/rvl/diag
LLDLIBS += -ldiagutils -lsys -lioslibc
MON_CRT0 = $(ROOT)/usr/lib/rvl/crt0_noOS.o
MON_LDFLAGS = $(LDLIBS) $(LDFLAGS) -T$(ROOT)/usr/lib/rvl/sdram.link

SRAM_CFLAGS = -DUSE_SRAM
STDALONE_LDFLAGS =  $(LDLIBS) $(LDFLAGS) -T $(ROOT)/usr/lib/rvl/stdalone.link

NAPA_CFLAGS = -DUSE_NAPA
STDALONE_NAPA_LDFLAGS = $(LDLIBS) $(LDFLAGS) -T napa_stdalone.link

DDR3_CFLAGS = -DUSE_DDR3 
STDALONE_DDR3_LDFLAGS = $(LDLIBS) $(LDFLAGS) -T ddr3_stdalone.link  -Ttext=$(MK_APPS_START)

include $(COMMONRULES)

STDALONE_TGTS= \
               aes_sram.elf \
               sha_sram.elf \
               mem_sram.elf \
               dma_sram.elf \
               dma_napa.elf \
               mmu_sram.elf

DDR_STDALONE_TGTS=

NAPA_STDALONE_TGTS= \
               dma_napa.elf 

TARGETS = $(STDALONE_TGTS) 

default: $(TARGETS)

%_sram.elf : ../init.o %_sram.o
	$(CC) $(CFLAGS) $(SRAM_CFLAGS) -o $@ $^ $(STDALONE_LDFLAGS)

%_napa.elf : ../init.o %_napa.o
	$(CC) $(CFLAGS) $(NAPA_CFLAGS) -o $@ $^ $(STDALONE_NAPA_LDFLAGS)

%_ddr3.elf : ../init.o %_ddr3.o
	$(CC) $(CFLAGS) $(DDR3_CFLAGS) -o $@ $^ $(STDALONE_DDR3_LDFLAGS)

%_sram.o: %.c
	rm -f $@;
	$(CC) $(CFLAGS) $(SRAM_CFLAGS) -DSTDALONE -o $@  -c $^

%_napa.o: %.c
	$(CC) $(CFLAGS) $(NAPA_CFLAGS) -DSTDALONE -o $@  -c $^

%_ddr3.o: %.c
	rm -f $@;
	$(CC) $(CFLAGS) $(DDR3_CFLAGS) -DSTDALONE -o $@  -c $^

%.elf : %.o
	$(CC) $(CFLAGS) -o $@ $(MON_CRT0) $^ $(MON_LDFLAGS)

