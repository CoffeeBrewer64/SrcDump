a0 109
include $(ROOT)/usr/include/make/NGdefs

HFILES = \
	asm.h\
	arm.h\
    dol.h\
	elf.h\
	iop.h\
	ios.h\
	mini_ios.h\
	hw.h\
	lomem.h\
	lomem_12M.h\
	memmap.h\
	mmu.h\
	addr_map.h\
	priority.h\
	rpc.h\
	iostypes.h\
	iosresource.h\
	iosiobuf.h\
	semihost.h\
	sys.h\
	swi.h\
	mini_swi.h\
	trace.h\
	sdi.h \
	sdio_api.h \
	sd_api.h \
	types.h \
	nvram.h \
	iosusb.h \
	iosusbtypes.h\
	usb11.h\
	ohci.h\
	ohci_regs.h\
	ohci_types.h

# Headers for use by x86 tools
TOOLS_HFILES = addr_map.h

# SUBDIRS = hw diag 
LDIRT += ios.h swi.h mini_swi.h addr_map.h mini_ios.h

default: 

include $(COMMONRULES)

headers install: $(HFILES)
	$(INSTALL) -m 444 $(HFILES) $(ROOT)/usr/include/rvl
	$(INSTALL) -m 444 $(TOOLS_HFILES) $(ROOT)/usr/include/x86
	$(INSTALL) -m 444 syscalls $(ROOT)/usr/include/rvl
	$(INSTALL) -m 444 syscalls2 $(ROOT)/usr/include/rvl
	$(INSTALL) -m 444 mini_syscalls $(ROOT)/usr/include/rvl

ios.h: ios.py syscalls syscalls2
	./ios.py IOS syscalls syscalls2 ios.h

mini_ios.h: ios.py mini_syscalls
	./ios.py MINIIOS mini_syscalls mini_ios.h

CRYPTCALLS = $(ROOT)/usr/include/cryptcalls

swi.h: swi.py syscalls $(CRYPTCALLS) syscalls2
	./swi.py syscalls $(CRYPTCALLS) syscalls2 swi.h

mini_swi.h: swi.py mini_syscalls 
	./swi.py mini_syscalls mini_swi.h

addr_map.h: addr_map.sed $(ROOT)/usr/include/make/NGaddrs
	sed -e 's/@@RSVD_START@@/$(MK_RSVD_START)/g'        \
	-e 's/@@IOP_GDDR3_START@@/$(MK_IOP_GDDR3_START)/g'      \
	-e 's/@@IOP_GDDR3_END@@/$(MK_IOP_GDDR3_END)/g'      \
	-e 's/@@DI_DMA_START@@/$(MK_DI_DMA_START)/g'  \
	-e 's/@@DI_DMA_SIZE@@/$(MK_DI_DMA_SIZE)/g'  \
	-e 's/@@IOBUF0_START@@/$(MK_IOBUF0_START)/g'      \
	-e 's/@@OH0_START@@/$(MK_OH0_START)/g'      \
	-e 's/@@OH1_START@@/$(MK_OH1_START)/g'      \
	-e 's/@@EHC_START@@/$(MK_EHC_START)/g'      \
	-e 's/@@STM_START@@/$(MK_STM_PHYS_START)/g'      \
	-e 's/@@NCD_START@@/$(MK_NCD_START)/g'      \
	-e 's/@@KD_START@@/$(MK_KD_START)/g'      \
	-e 's/@@OH0_TXT_START@@/$(MK_OH0_TXT_START)/g'      \
	-e 's/@@OH1_TXT_START@@/$(MK_OH1_TXT_START)/g'      \
	-e 's/@@EHC_TXT_START@@/$(MK_EHC_TXT_START)/g'      \
	-e 's/@@WD_START@@/$(MK_WD_START)/g'      \
	-e 's/@@DI_START@@/$(MK_DI_PHYS_START)/g'      \
	-e 's/@@NET_START@@/$(MK_NET_START)/g'      \
	-e 's/@@USBETH_START@@/$(MK_USBETH_START)/g'      \
	-e 's/@@SD0_START@@/$(MK_SD0_PHYS_START)/g'      \
	-e 's/@@FS_START@@/$(MK_FS_PHYS_START)/g'        \
	-e 's/@@ET_START@@/$(MK_ET_PHYS_START)/g'        \
	-e 's/@@PPCBOOT_START@@/$(MK_PPCBOOT_START)/g'        \
	-e 's/@@OSLAUNCH_START@@/$(MK_OSLAUNCH_START)/g'      \
	-e 's/@@OSLAUNCH_END@@/$(MK_OSLAUNCH_END)/g'      \
	-e 's/@@CRYPTO_START@@/$(MK_CRYPTO_START)/g'        \
	-e 's/@@SHARED_START@@/$(MK_SHARED_START)/g'  \
	-e 's/@@SHARED_SIZE@@/$(MK_SHARED_SIZE)/g'  \
	-e 's/@@IOP_GDDR3_END@@/$(MK_IOP_GDDR3_END)/g'      \
	-e 's/@@WL_START@@/$(MK_WL_START)/g'      \
	-e 's/@@APPS_START@@/$(MK_APPS_START)/g'      \
	-e 's/@@SYSCALL_START@@/$(MK_SYSCALL_STACK_START)/g'      \
	-e 's/@@SYS_RSVD_START@@/$(MK_SYS_RSVD_START)/g'      \
	-e 's/@@SSL_START@@/$(MK_SSL_START)/g'      \
	-e 's/@@KERNEL_DATA_START@@/$(MK_KERNEL_DATA_START)/g'      \
	-e 's/@@USB_START@@/$(MK_USB_START)/g'      \
	-e 's/@@P2P_START@@/$(MK_P2P_START)/g'      \
	-e 's/@@PS_START@@/$(MK_PS_START)/g'      \
	$< > $@
