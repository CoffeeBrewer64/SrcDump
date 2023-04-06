a0 190
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

CFILES = \
    fl_bitwalk_test.c \
    fl_ecc_test.c \
    fl_misc_test.c \
    fl_ops_test.c \
    fl_performance_test.c \
    fl_simple.c \
    fl_dv.c \
    fl_dv_ops.c \
    fl_direct.c

FLASHLIB = \
    $(ROOT)/usr/lib/rvl/libintflash.a

FL_SIMPLE_OBJS = \
    fl_simple.o

FL_DV_OBJS = \
    fl_bitwalk_test.o \
    fl_ecc_test.o \
    fl_misc_test.o \
    fl_ops_test.o \
    fl_performance_test.o \
    fl_dv.o

FL_DV_OPS_SRAM_OBJS = \
    fl_ops_test_sram.o \
    fl_dv_ops_sram.o

FL_DV_BTW_SRAM_OBJS = \
    fl_bitwalk_test_sram.o \
    fl_dv_btw_sram.o

FL_DV_ECC_SRAM_OBJS = \
    fl_ecc_test_sram.o \
    fl_dv_ecc_sram.o

FL_DV_MISC_SRAM_OBJS = \
    fl_misc_test_sram.o \
    fl_dv_misc_sram.o

FL_DV_PRF_SRAM_OBJS = \
    fl_performance_test_sram.o \
    fl_dv_prf_sram.o

FL_DV_DDR3_OBJS = \
    fl_bitwalk_test_ddr3.o \
    fl_ecc_test_ddr3.o \
    fl_misc_test_ddr3.o \
    fl_ops_test_ddr3.o \
    fl_performance_test_ddr3.o \
    fl_dv_ddr3.o

FL_DV_OPS_DDR3_OBJS = \
    fl_ops_test_ddr3.o \
    fl_dv_ops_ddr3.o

FL_DV_BTW_DDR3_OBJS = \
    fl_bitwalk_test_ddr3.o \
    fl_dv_btw_ddr3.o

FL_DV_ECC_DDR3_OBJS = \
    fl_ecc_test_ddr3.o \
    fl_dv_ecc_ddr3.o

FL_DV_MISC_DDR3_OBJS = \
    fl_misc_test_ddr3.o \
    fl_dv_misc_ddr3.o

FL_DV_PRF_DDR3_OBJS = \
    fl_performance_test_ddr3.o \
    fl_dv_prf_ddr3.o


LCINCS += -I . -I $(ROOT)/usr/include/rvl
# LLDLIBS += -lrvldv -ldiagutils -lsys -ioslibc -lios
# LLDLIBS += -lrvldv -ldiagutils -lsys -lintflash -lioslibc -lios -liosc
LLDLIBS += -lrvldv -ldiagutils -lsys -lapputils -lioslibc 
MON_CRT0 = $(ROOT)/usr/lib/rvl/crt0_noOS.o
MON_LDFLAGS = $(LDLIBS) $(LDFLAGS) -T$(ROOT)/usr/lib/rvl/sdram.link

SRAM_CFLAGS = -DUSE_SRAM
STDALONE_LDFLAGS = $(LDLIBS) $(LDFLAGS) -T$(ROOT)/usr/lib/rvl/stdalone.link

DDR3_CFLAGS = -DUSE_DDR3
STDALONE_DDR3_LDFLAGS = $(LDLIBS) $(LDFLAGS) -T ddr3_stdalone.link -Ttext=$(MK_APPS_START)

LCDEFS += -DFL_DEBUG_LOG
LDIRT += *.elf *.elf

include $(COMMONRULES)

#Standalone programs
STDALONE_TGTS = \
	fl_direct_sram.elf \
	fl_simple_sram.elf \
 	fl_dv_ops_sram.elf \
 	fl_dv_btw_sram.elf \
 	fl_dv_ecc_sram.elf \
 	fl_dv_misc_sram.elf \
 	fl_dv_prf_sram.elf \
        \
	fl_simple_ddr3.elf \
	fl_dv_ddr3.elf \
 	fl_dv_ops_ddr3.elf \
 	fl_dv_btw_ddr3.elf \
 	fl_dv_ecc_ddr3.elf \
 	fl_dv_misc_ddr3.elf \
 	fl_dv_prf_ddr3.elf

# Targets to be run with minimon
MON_TGTS = \
	fl_simple.elf \
 	fl_dv.elf

TARGETS = $(STDALONE_TGTS)

default: $(TARGETS)

%_sram.elf : ../init.o %.o exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_LDFLAGS)

%_ddr3.elf : ../init.o %_ddr3.o exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_DDR3_LDFLAGS)

%_sram.o: %.c
	$(CC) $(CFLAGS) $(SRAM_CFLAGS) -DSTDALONE -o $@ -c $^

%_ddr3.o: %.c
	rm -f $@;
	$(CC) $(CFLAGS) $(DDR3_CFLAGS) -DSTDALONE -o $@ -c $^

fl_simple_sram.elf : ../init.o fl_simple_sram.o exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_LDFLAGS)

fl_dv_ops_sram.elf : ../init.o $(FL_DV_OPS_SRAM_OBJS) exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_LDFLAGS)

fl_dv_btw_sram.elf : ../init.o $(FL_DV_BTW_SRAM_OBJS) exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_LDFLAGS)

fl_dv_ecc_sram.elf : ../init.o $(FL_DV_ECC_SRAM_OBJS) exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_LDFLAGS)

fl_dv_misc_sram.elf : ../init.o $(FL_DV_MISC_SRAM_OBJS) exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_LDFLAGS)

fl_dv_prf_sram.elf : ../init.o $(FL_DV_PRF_SRAM_OBJS) exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_LDFLAGS)

fl_simple_ddr3.elf : ../init.o fl_simple_ddr3.o exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_DDR3_LDFLAGS)

fl_dv_ddr3.elf: ../init.o $(FL_DV_DDR3_OBJS)  exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_DDR3_LDFLAGS)

fl_dv_ops_ddr3.elf : ../init.o $(FL_DV_OPS_DDR3_OBJS) exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_DDR3_LDFLAGS)

fl_dv_btw_ddr3.elf : ../init.o $(FL_DV_BTW_DDR3_OBJS) exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_DDR3_LDFLAGS)

fl_dv_ecc_ddr3.elf : ../init.o $(FL_DV_ECC_DDR3_OBJS) exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_DDR3_LDFLAGS)

fl_dv_misc_ddr3.elf : ../init.o $(FL_DV_MISC_DDR3_OBJS) exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_DDR3_LDFLAGS)

fl_dv_prf_ddr3.elf : ../init.o $(FL_DV_PRF_DDR3_OBJS) exit.o
	$(CC) $(CFLAGS) -o $@ $^ $(STDALONE_DDR3_LDFLAGS)

%.elf: %.o exit.o
	$(CC) $(CFLAGS) -o $@ $(MON_CRT0) $^ $(MON_LDFLAGS)

fl_simple.elf: $(FL_SIMPLE_OBJS) exit.o
	$(CC) $(CFLAGS) -o $@ $(MON_CRT0) $^ $(MON_LDFLAGS)

fl_dv.elf: $(FL_DV_OBJS)  exit.o
	$(CC) $(CFLAGS) -o $@ $(MON_CRT0) $^ $(MON_LDFLAGS)

# fl_simple.elf: $(CRT0) $(FL_SIMPLE_OBJS) $(FLASHLIB)
# 	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# fl_dv.elf: $(CRT0) $(FL_DV_OBJS) $(FLASHLIB)
# 	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

