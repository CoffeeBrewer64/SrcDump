include $(ROOT)/usr/include/make/NGdefs

TARGETS = \
    fs_regr2_ddr3.elf

ASFILES = \
    trylock.s

CFILES = \
    fs_regr2.c \
    fs_coproc.c 

FLASHLIB = \
    $(ROOT)/usr/lib/rvl/libintflash.a

FSLIB = \
    $(ROOT)/usr/lib/rvl/libintfs.a

FS_REGR_OBJS = \
    fs_regr.o 

FS_REGR2_OBJS = \
    fs_regr2.o 

FS_COPROC_OBJS = \
    trylock.o \
    fs_coproc.o

default: $(TARGETS)

include $(COMMONRULES)

LDIRT += fs_regr2_ddr3.elf fs_coproc.elf

LLDOPTS += -T ../ddr3_stdalone.link
LLDLIBS += -lioslibc -liossyscall 
#LLDLIBS += -lsys
LLDLIBS += -lioslibc
LCDEFS += -DISFS_DEBUG_LOG

fs_regr_ddr3.elf: $(CRT0) $(FS_REGR_OBJS) $(FSLIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

fs_regr2_ddr3.elf: $(CRT0) $(FS_REGR2_OBJS) $(FSLIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

fs_regr.elf: $(CRT0) $(FS_REGR_OBJS) $(FSLIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

fs_coproc.elf: $(CRT0) $(FS_COPROC_OBJS) $(FSLIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)


