a0 79
# compile for all types

include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

INSTALLDIR = $(ROOT)/usr
CFILES = \
	shareg.c \
	sha_block_test.c \
	sha_ref_test.c \
	sha_reg_test.c \
	sha_chain_test.c \
	sha_ctrl_test.c \
	sha_simple_test.c \
	sha_hash_test.c

LCINCS  += -I. -I$(INSTALLDIR)/include/rvl/diag
LLDLIBS += -lrvldv -liosc -ldiagutils -lsys -lioslibc -lios
MON_CRT0 = $(ROOT)/usr/lib/rvl/crt0_noOS.o
MON_LDFLAGS = $(LDLIBS) $(LDFLAGS) -T$(ROOT)/usr/lib/rvl/sdram.link

SRAM_CFLAGS = -DUSE_SRAM
STDALONE_LDFLAGS =  $(LDLIBS) $(LDFLAGS) -T $(ROOT)/usr/lib/rvl/stdalone.link

NAPA_CFLAGS = -DUSE_NAPA
STDALONE_NAPA_LDFLAGS =  $(LDLIBS) $(LDFLAGS) -T napa_stdalone.link

DDR3_CFLAGS = -DUSE_DDR3
STDALONE_DDR3_LDFLAGS =  $(LDLIBS) $(LDFLAGS) -T ddr3_stdalone.link -Ttext=$(MK_APPS_START)
STDALONE_DDR3_T_LDFLAGS = $(LDLIBS) $(LDFLAGS) -T ddr3_stdalone.link

include $(COMMONRULES)

#Standalone programs
STDALONE_TGTS= \
	shareg_sram.elf \
	sha_hash_test_sram.elf \
    sha_simple_test_sram.elf \
	sha_hw_sw.elf\
	sha_block_test_ddr3.elf \
	sha_ref_test_ddr3.elf \
	sha_reg_test_ddr3.elf \
	sha_chain_test_ddr3.elf \
	sha_ctrl_test_ddr3.elf \
	shareg_ddr3.elf \
	sha_hash_test_ddr3.elf 

#Targets to be run with minimon
MON_TGTS = $(CFILES:.c=.elf)

#TARGETS = $(MON_TGTS) $(STDALONE_TGTS)
TARGETS = $(STDALONE_TGTS)

default: $(TARGETS)

%_sram.elf : ../init.o %.o
	$(CC) $(CFLAGS) $(SRAM_CFLAGS) -o $@ $^ $(STDALONE_LDFLAGS)

%_napa.elf : ../init.o %_napa.o
	$(CC) $(CFLAGS) $(NAPA_CFLAGS) -o $@ $^ $(STDALONE_NAPA_LDFLAGS)

%_ddr3.elf : ../init.o %_ddr3.o
	$(CC) $(CFLAGS) $(DDR3_CFLAGS) -o $@ $^ $(STDALONE_DDR3_LDFLAGS)

%_sram.o: %.c
	$(CC) $(CFLAGS) $(SRAM_CFLAGS) -DSTDALONE -o $@  -c $^

%_napa.o: %.c
	rm -f %_napa.o;
	$(CC) $(CFLAGS) $(NAPA_CFLAGS) -DSTDALONE -o $@  -c $^

%_ddr3.o: %.c
	rm -f %_ddr3.o;
	$(CC) $(CFLAGS) $(DDR3_CFLAGS) -DSTDALONE -o $@  -c $^

%.elf : %.o
	$(CC) $(CFLAGS) -o $@ $(MON_CRT0) $^ $(MON_LDFLAGS)

