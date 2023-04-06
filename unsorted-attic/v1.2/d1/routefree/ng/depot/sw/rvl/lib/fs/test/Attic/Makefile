include $(ROOT)/usr/include/make/NGdefs

TARGETS = \
    fs_apitest.elf

CFILES = \
    fs_apitest.c

FSAPI = \
    $(ROOT)/usr/lib/rvl/libisfs.a

FS_APITEST_OBJS = \
    fs_apitest.o

default: $(TARGETS)

include $(COMMONRULES)

LDIRT += fs_apitest.elf
#LLDOPTS += -Ttext $(MK_ET_START) -T $(DA_LINK)
LLDOPTS += -T ddr3_stdalone.link -Ttext 0x10101000
LLDLIBS += -lioslibc -liossyscall

fs_apitest.elf: $(CRT0) $(FS_APITEST_OBJS) $(FSAPI)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

#os_apitest.elf: fs_apitest.elf $(ROOT)/usr/bin/sc/sk.elf $(ROOT)/usr/bin/sc/fs.elf
	#$(MERGE) -k $(ROOT)/usr/bin/sc/sk.elf -s $(MK_SHARED_START) -f $(ROOT)/usr/bin/sc/fs.elf -e fs_apitest.elf -o os_apitest.elf -z 0x10000

#runtests: os_apitest.elf
	#$(ROOT)/usr/bin/x86/sce -f -t 0x1ff --flashinit -o os_apitest.elf
	#rm -f os_apitest.elf
