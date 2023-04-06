d4 2
a5 2
    fs_regr.bin \
    fs_coproc.bin
d12 1
d24 3
d36 4
a39 3
# LLDOPTS += -Ttext $(MK_FS_START) -Tbss ${MK_FS_BSS_START} -T $(DA_LINK)
# LLDLIBS += -lsclibc -lios -liosc
LLDLIBS += -lioslibc -liossyscall 
d42 6
a53 4
# runtests_regr: fs_regr.elf
# 	$(MERGE) -k $(ROOT)/usr/bin/sc/sk.elf -s $(MK_SHARED_START) -f $^ -o os_regr.elf -z 0x100000
# 	$(ROOT)/usr/bin/x86/sce -f -t 0x1ff --flashinit -o os_regr.elf
# 	rm -f os_regr.elf
