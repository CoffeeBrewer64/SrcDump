a0 104

# compile for all types

include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

INSTALLDIR = $(ROOT)/usr
CFILES = \
        aesreg.c \
	aes_ref_test.c \
	aes_dma_test.c \
	aes_block_test.c \
	aes_dma2_test.c \
	aes_dma3_test.c \
	dma.c \
	aes_intr_test.c \
	aes_simple_intr.c \
	aes_sha_sron_test.c \
	aes_rw_test.c \
	aes_ctrl_test.c \
	aes_encdec_test.c \
	aes_sha_test.c

LCINCS  += -I$(INSTALLDIR)/include/rvl/diag
LLDLIBS += -ldiagutils -lee -lsys -lrvldv -lioslibc -lios
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
               aesreg_sram.elf \
               aes_encdec_test_sram.elf \
               aes_sha_test_sram.elf \
               dma_sram.elf \
               \
               dma_napa.elf \
               \
               aesreg_ddr3.elf \
               aes_ref_test_ddr3.elf \
               aes_block_test_ddr3.elf \
               aes_dma_test_ddr3.elf \
               aes_dma3_test_ddr3.elf \
               dma_ddr3.elf \
               aes_rw_test_ddr3.elf \
               aes_ctrl_test_ddr3.elf \
               aes_encdec_test_ddr3.elf \
               aes_sha_test_ddr3.elf 

DDR_STDALONE_TGTS= \
               aesreg_ddr3.elf \
               aes_ref_test_ddr3.elf \
               aes_block_test_ddr3.elf \
               aes_dma_test_ddr3.elf \
               aes_dma3_test_ddr3.elf \
               aes_rw_test_ddr3.elf \
               aes_ctrl_test_ddr3.elf \
               aes_encdec_test_ddr3.elf \
               aes_sha_test_ddr3.elf 

NAPA_STDALONE_TGTS= \
               dma_napa.elf 
#               aes_ref_test_napa.elf \

MON_TGTS= $(CFILES .c = .elf)

# TARGETS = $(STDALONE_TGTS) $(MON_TGTS)
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

