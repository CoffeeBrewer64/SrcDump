a0 142
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

# build IOS versions
IOS_VERS_1            = 249.0.0
IOS_TITLE_ID_1        = 249
IOS_TITLE_VERSION_1   = 0x0000

BOOT2_TITLE_VERSION ?= 2

BIN_ROOT=$(ROOT)/usr/bin/rvl

LOADER_BIN=$(BIN_ROOT)/loader.bin
LOADER_BOOT2_BIN=$(BIN_ROOT)/loader_boot2.bin

BOOT2_DEPEND_RMS= \
    $(BIN_ROOT)/boot2_ios.elf \
    $(BIN_ROOT)/boot2_ios_prod.elf \
    $(BIN_ROOT)/fs.elf \
    $(BIN_ROOT)/es.elf 

BOOT2_LINK_RMS= \
    -f $(BIN_ROOT)/fs.elf \
    -e $(BIN_ROOT)/es.elf

DEPEND_RMS= \
    $(BIN_ROOT)/ios_real.elf \
    $(BIN_ROOT)/ios_prod.elf \
    $(BIN_ROOT)/fs.elf \
    $(BIN_ROOT)/es.elf \
    $(BIN_ROOT)/di_boot.elf \
    $(BIN_ROOT)/di_boot_prod.elf \
    $(BIN_ROOT)/ehci.elf \
    $(BIN_ROOT)/ohci0.elf \
    $(BIN_ROOT)/ohci1.elf \
    $(BIN_ROOT)/sdi.elf \
    $(BIN_ROOT)/net.elf \
    \
    $(BIN_ROOT)/usb_hid.elf \
    $(BIN_ROOT)/kd.elf \
    $(BIN_ROOT)/ncd.elf \
    $(BIN_ROOT)/so.elf \
    $(BIN_ROOT)/ssl.elf \
    $(BIN_ROOT)/stm.elf \
    $(BIN_ROOT)/usbeth.elf \
    $(BIN_ROOT)/wd.elf \
    $(BIN_ROOT)/wldrvr.elf

CORE_RMS= \
    -f $(BIN_ROOT)/fs.elf \
    -e $(BIN_ROOT)/es.elf

FIRMWARES = \
          firmware.$(RVL_MEM).$(IOS_VERS_1).wad

TARGETS = boot2.$(RVL_MEM).wad boot2.wad boot2.bwf boot2_prod.img

TMD    = $(HOSTBINDIR)/tmd
TICKET = $(HOSTBINDIR)/ticket

default: $(TARGETS)

exports install: $(TARGETS)
	$(INSTALL) $(TARGETS) $(BIN_ROOT)

include $(COMMONRULES)

LDIRT += *.img *.tik *.tmd *.titleKey *.app *.wad *.bwf *.sys *.mrg *.met tmd.out

boot2.wad: boot2.img
	$(PUBLISHWAD) -b -n boot2 -q $(BOOT2_TITLE_VERSION) -l $^ -d

boot2.bwf: boot2.img
	$(PUBLISH) -b -n boot2 -q $(BOOT2_TITLE_VERSION) -l $^ -d

boot2.img: $(LOADER_BOOT2_BIN) boot2.mrg
	$(OSMERGE) -b $(LOADER_BOOT2_BIN) -m boot2.mrg -o $@

boot2_prod.img: $(LOADER_BOOT2_BIN) boot2_prod.mrg
	$(OSMERGE) -b $(LOADER_BOOT2_BIN) -m boot2_prod.mrg -o $@

boot2.mrg: $(BOOT2_DEPEND_RMS) $(NG_ADDR_MAP)
	$(MERGE) -o $@ \
		-s $(MK_SHARED_START) \
		-z $(MK_SHARED_SIZE) \
		-k $(BIN_ROOT)/boot2_ios.elf \
		$(BOOT2_LINK_RMS)

boot2_prod.mrg: $(BOOT2_DEPEND_RMS) $(NG_ADDR_MAP)
	$(MERGE) -o $@ \
		-s $(MK_SHARED_START) \
		-z $(MK_SHARED_SIZE) \
		-k $(BIN_ROOT)/boot2_ios_prod.elf \
		$(BOOT2_LINK_RMS)

boot2_prod.bwf:
	cat $(ROOT)/usr/etc/pki_data/ca_ppki.cert $(ROOT)/usr/etc/pki_data/cp_ppki.cert $(ROOT)/usr/etc/pki_data/xs_ppki.cert > cert_ppki.sys
	$(PUBLISH) -b -n sd_boot_prod -w "cert_ppki.sys 1.tik 100000001.tmd boot2.met 00000001.app" -d

boot2_prod_eTicket: boot2_prod.img
	rm -f 100000001.tmd 1.tik 00000001.app
	$(TMD) -O -C 1 -T 0x100000001 -n $^ -c 1 -i 0 -t 1 -b 0 -P c -k aeskey -s $(ROOT)/usr/etc/pki_data/cp_ppki.cert -D $(ROOT)/usr/etc/pki_data/cp_dpki.rsa 
	$(TICKET) -O -t 1 -T 0x100000001 -K 100000001.titleKey -P c -X $(ROOT)/usr/etc/pki_data/xs_ppki.cert -x $(ROOT)/usr/etc/pki_data/xs_dpki.rsa -S $(ROOT)/usr/etc/pki_data/xs_dpki.eccPubKey 

boot2.$(RVL_MEM).wad : boot2.wad
	cp $^ $@

firmware: $(FIRMWARES)

firmware.$(RVL_MEM).$(IOS_VERS_1).wad : os_devel_v1.wad
	cp $^ $@ 

os_devel_v1.wad: os.img
	$(PUBLISHWAD) -O -o $(IOS_TITLE_ID_1) -n os_devel_v1 -l os.img,di_boot.mrg,ehci.mrg,ohci0.mrg,ohci1.mrg,sdi.mrg,usbeth.mrg,so.mrg,ncd.mrg,wldrvr.mrg,wd.mrg,kd.mrg,usb_hid.mrg,ssl.mrg,stm.mrg -T1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 -I $(IOS_TITLE_VERSION_1) -d

os.img: $(LOADER_BIN) os.mrg
	$(OSMERGE) -b $(LOADER_BIN) -m os.mrg -o $@

os.mrg: $(DEPEND_RMS) $(NG_ADDR_MAP)
	$(MERGE) -o $@ \
		-s $(MK_SHARED_START) \
		-z $(MK_SHARED_SIZE) \
		-k $(BIN_ROOT)/ios_real.elf \
        $(CORE_RMS)
	$(MERGE) -o di_boot.mrg -r -d $(BIN_ROOT)/di_boot.elf
	$(MERGE) -o ehci.mrg -r -E $(BIN_ROOT)/ehci.elf
	$(MERGE) -o ohci0.mrg -r -u $(BIN_ROOT)/ohci0.elf
	$(MERGE) -o ohci1.mrg -r -v $(BIN_ROOT)/ohci1.elf
	$(MERGE) -o sdi.mrg -r -c $(BIN_ROOT)/sdi.elf
	$(MERGE) -o usbeth.mrg -r -a $(BIN_ROOT)/usbeth_ncl.elf
	$(MERGE) -o so.mrg -r -n $(BIN_ROOT)/so.elf
	$(MERGE) -o usbeth_bo.mrg -r -a $(BIN_ROOT)/usbeth.elf
	$(MERGE) -o so_bo.mrg -r -n $(BIN_ROOT)/net.elf
	$(MERGE) -o ncd.mrg -r -N $(BIN_ROOT)/ncd.elf
	$(MERGE) -o wldrvr.mrg -r -L $(BIN_ROOT)/wldrvr.elf
	$(MERGE) -o wd.mrg -r -W $(BIN_ROOT)/wd.elf
	$(MERGE) -o usb_hid.mrg -r -x $(BIN_ROOT)/usb_hid.elf
	$(MERGE) -o kd.mrg -r -K $(BIN_ROOT)/kd.elf
	$(MERGE) -o ssl.mrg -r -C $(BIN_ROOT)/ssl.elf
	$(MERGE) -o stm.mrg -r -S $(BIN_ROOT)/stm.elf

