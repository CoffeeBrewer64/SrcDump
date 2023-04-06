a0 83
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

LCDEFS = -DBUILD_DATE='$(BUILD_DATE)' -DVERSION='$(VERSION)'
LCINCS = -I. -I$(ROOT)/usr/include/rvl/diag
LASINCS = -I$(ROOT)/usr/include/rvl/diag

# DO NOT enable this flag except for a specific debug build of mios
# used for testing drive specs. 
#LCDEFS += -DENABLE_DEBUG_ACRCOMPAT_DI

TARGETS = libsys.a

CFILES = \
	 aram_emu.c\
	 init_chip.c\
	 init_compat.c\
	 enable_chipblocks.c\
	 get_chipid.c\
	 init_sec.c\
	 init_sysmode.c\
	 mem.c \
	 wrk_around.c\
	 ahb.c \
	 boot_ppc.c\
	 set_ahbiopi.c\
	 init_lomem_common.c\
	 init_lomem_int.c\
	 init_lomem.c\
	 osversion.c\
	 setup_exiboot.c\
	 gpio.c\
	 refresh_napa.c\
	 refresh_napa1.c\
	 init_mem.c \
	 init_aram.c \
	 init_ios.c \
	 init_usb.c \
	 init_usbphy.c \
	 regrdwr.c\
	 init_vipll.c\
	 init_usbpll.c\
	 init_usb_ati.c\
	 init_aipll.c\
	 ddr_memctrl.c\
	 ddr_memctrl_fg.c\
	 ddr_accessctrl.c\
	 set_ppcacrperms.c\
	 udelay.c \
	 reset.c \
	 compat_reset.c \
	 set_rgb.c \
	 distraps.c\
	 get_rsvdsram_start.c \
	 hwfixes.c\
	 get_sysclk.c\
	 enable_ahbblocks.c\
	 reset_ahbblocks.c\
	 reset_legacyblocks.c\
	 enable_legacyblocks.c\
	 set_ss.c\
	 us_to_ticks.c

ASFILES = \
	cache_lock.s \
	enableICache.s\
	invaliICache.s

default: $(TARGETS) 

headers:

exports install: $(TARGETS) headers
	$(INSTALL) -m 444 $(TARGETS) $(ROOT)/usr/lib/rvl

sdk-install: default

$(TARGETS): %: %($(OBJECTS))
	ar cru $@ $?

include $(COMMONRULES)

