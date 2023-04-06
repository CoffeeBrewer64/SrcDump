a0 129
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

# Targets
TARGETS = boot1_compat.img bc.bwf mios.bwf boot1_compat_prod.img mios.img bc.wad mios.wad bc_prod_dev.bwf boot1_compat.elf boot1_compat_prod.elf

default: $(TARGETS)

exports install: $(TARGETS)
	$(INSTALL) $(TARGETS) $(ROOT)/usr/bin/rvl

#Names of produced wad files
BOOT1_COMPAT_NAME=bc
MINI_IOS_NAME=mios

# Build options
LDIRT += *.elf *.list *.hex *.o *.mem *.sha *.bin *.padded *.decrypted \
        *.flash *.log *.aes .*.d key.c iv.c *.wad *.mrg \
        *.app *.met *.tik *.tmd *.titleKey

LLDLIBS += -lsys -lioslibc
#Don't link -lee if EEPROM is disabled
DEVEL_LIBS = -lcsl_dev #-lee
PROD_LIBS = -lcsl -lee 

LLDOPTS += -T $(ROOT)/usr/lib/rvl/stdalone.link -Ttext 0xffff0000


# Common rules
include $(COMMONRULES)

# bc.wad -- version of boot1_compat built to use devel pki
bc.wad: boot1_compat.img
	$(PUBLISHWAD) -B -n $(BOOT1_COMPAT_NAME) -l $^ -d

bc.bwf: boot1_compat.img
	$(PUBLISH) -B -n $(BOOT1_COMPAT_NAME) -l $^ -d

boot1_compat.img: $(ROOT)/usr/bin/rvl/loader.bin boot1_compat.mrg
	$(OSMERGE) -b $(ROOT)/usr/bin/rvl/loader.bin -m boot1_compat.mrg -o $@

boot1_compat.mrg: boot1_compat.elf $(NG_ADDR_MAP)
	$(MERGE) -o $@ -k boot1_compat.elf \
		-s $(MK_SHARED_START) \
		-z $(MK_SHARED_SIZE) 

boot1_compat.o: boot1_compat.c
	$(CC) -c -DLOAD_TO_DDR $(CFLAGS) -o $@ $^ 

load_boot2_devel.o: load_boot2.c
	$(CC) -c -DRVL_DEVEL_PKI -DBOOT1_DISABLE_EEPROM $(CFLAGS) -o $@ $^ 

boot1_compat.elf: init.o boot1_compat.o load_boot2_devel.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(DEVEL_LIBS) $(LDLIBS)

#boot1_compat prod pki image to be run with os_devel
bc_prod_dev.wad: boot1_compat_prod.img
	$(PUBLISHWAD) -B -n $(BOOT1_COMPAT_NAME)_prod_dev -l $^ -d

bc_prod_dev.bwf: boot1_compat_prod.img
	$(PUBLISH) -B -n $(BOOT1_COMPAT_NAME)_prod_dev -l $^ -d


# boot1_compat image built to use prod pki
boot1_compat_prod.img: $(ROOT)/usr/bin/rvl/loader.bin boot1_compat_prod.mrg
	$(OSMERGE) -b $(ROOT)/usr/bin/rvl/loader.bin -m boot1_compat_prod.mrg -o $@


boot1_compat_prod.mrg: boot1_compat_prod.elf $(NG_ADDR_MAP)
	$(MERGE) -o $@ -k boot1_compat_prod.elf \
		-s $(MK_SHARED_START) \
		-z $(MK_SHARED_SIZE) 

# boot1_compat.o has no dependency on prod/devel pki
load_boot2_prod.o: load_boot2.c
	$(CC) -c -DRVL_PROD_PKI $(CFLAGS) -o $@ $^ 

boot1_compat_prod.elf: init.o boot1_compat.o load_boot2_prod.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(PROD_LIBS) $(LDLIBS)


bc_titid = 100000100
bc_tikid = 100
bc_cid = 00000100
bc_mid = bc
bc_minor = 0

cert_ppki.sys:
	cat $(ROOT)/usr/etc/pki_data/ca_ppki.cert $(ROOT)/usr/etc/pki_data/cp_ppki.cert $(ROOT)/usr/etc/pki_data/xs_ppki.cert > cert_ppki.sys

bc_prod.bwf: cert_ppki.sys
	$(PUBLISH) -O -n bc_prod -w "cert_ppki.sys $(bc_tikid).tik $(bc_titid).tmd $(bc_mid).met $(bc_cid).app" -d

bc_prod_eTicket: boot1_compat_prod.img
	rm -f $(bc_titid).tmd $(bc_tikid).tik $(bc_cid).app
	$(HOSTBINDIR)/tmd -O -C 1 -T 0x$(bc_titid) -n $^ -c 0x$(bc_cid) -m $(bc_minor) -i 0 -t 1 -b 0 -P c -k aeskey -s $(ROOT)/usr/etc/pki_data/cp_ppki.cert -D $(ROOT)/usr/etc/pki_data/cp_dpki.rsa 
	$(HOSTBINDIR)/ticket -O -t 0x$(bc_tikid) -T 0x$(bc_titid) -K $(bc_titid).titleKey -P c -X $(ROOT)/usr/etc/pki_data/xs_ppki.cert -x $(ROOT)/usr/etc/pki_data/xs_dpki.rsa -S $(ROOT)/usr/etc/pki_data/xs_dpki.eccPubKey 

# mini_ios has no dependency on which PKI is in use (prod/devel)
mios.wad: mios.img
	$(PUBLISHWAD) -A -n $(MINI_IOS_NAME) -l $^ -d

mios.bwf: mios.img
	$(PUBLISH) -A -n $(MINI_IOS_NAME) -l $^ -d

mios.img: $(ROOT)/usr/bin/rvl/loader.bin mini_ios.mrg
	$(OSMERGE) -b $(ROOT)/usr/bin/rvl/loader.bin -m mini_ios.mrg -o $@

mini_ios.mrg: $(ROOT)/usr/bin/rvl/mini_ios.elf $(NG_ADDR_MAP)
	$(MERGE) -o $@ -k $(ROOT)/usr/bin/rvl/mini_ios.elf \
	    -P $(ROOT)/usr/bin/nintendo/compat/BS2.img \
	    -p $(ROOT)/usr/bin/nintendo/compat/BS1.img \
		-s $(MK_SHARED_START) \
		-z $(MK_SHARED_SIZE) \

mios_titid = 100000101
mios_tikid = 101
mios_cid = 00000101
mios_mid = mios
mios_minor = 0

mios_prod.bwf: cert_ppki.sys
	$(PUBLISH) -O -n mios_prod -w "cert_ppki.sys $(mios_tikid).tik $(mios_titid).tmd $(mios_mid).met $(mios_cid).app" -d

mios_prod_eTicket: mios.img
	rm -f $(mios_titid).tmd $(mios_tikid).tik $(mios_cid).app
	$(HOSTBINDIR)/tmd -O -C 1 -T 0x$(mios_titid) -n $^ -c 0x$(mios_cid) -m $(mios_minor) -i 0 -t 1 -b 0 -P c -k aeskey -s $(ROOT)/usr/etc/pki_data/cp_ppki.cert -D $(ROOT)/usr/etc/pki_data/cp_dpki.rsa 
	$(HOSTBINDIR)/ticket -O -t 0x$(mios_tikid) -T 0x$(mios_titid) -K $(mios_titid).titleKey -P c -X $(ROOT)/usr/etc/pki_data/xs_ppki.cert -x $(ROOT)/usr/etc/pki_data/xs_dpki.rsa -S $(ROOT)/usr/etc/pki_data/xs_dpki.eccPubKey 
