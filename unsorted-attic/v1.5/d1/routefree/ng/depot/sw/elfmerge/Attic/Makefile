include $(ROOT)/usr/include/make/NGdefs
include $(COMMONRULES)

INSTALLDIR=$(ROOT)/usr/bin/rvl/ios_images
BIN_ROOT=$(ROOT)/usr/bin/rvl
TOOLS_DIR=$(ROOT)/usr/bin/x86

#
# Non-crypto versions of files below:
#


IOS=-k $(BIN_ROOT)/ios_noshell.elf
DI=-f $(BIN_ROOT)/di_boot_nocrypto.elf
FS=-f $(BIN_ROOT)/fs_nocrypto.elf
PPCBOOT=-f $(BIN_ROOT)/ppcboot.elf

FILES= $(IOS) $(FS) $(PPCBOOT) $(DI)

#
# Crypto versions of files below
#


IOS_C=-k $(BIN_ROOT)/ios_crypto.elf
DI_C=-f $(BIN_ROOT)/di_boot.elf
FS_C=-f $(BIN_ROOT)/fs.elf
PPCBOOT_C=-f $(BIN_ROOT)/ppcboot.elf

FILES_C = $(IOS_C) $(FS_C) $(PPCBOOT_C) $(DI_C)

FLASHES = \
	block0.flash \
	block1.flash \
	block2.flash \
	block3.flash \
	block4.flash

DIRT += bin *.bin ios* 

headers all default exports:

flash: 
	mkdir -p bin/nintendo
	mkdir -p bin/broadon
	cp -lrf $(ROOT)/usr/bin/nintendo bin
ifeq ($(origin NOCRYPTO), undefined)
	$(TOOLS_DIR)/arm-elf-merge $(FILES) -o ios.merged
else
	@echo ""
	@echo "---- BUILDING CRYPTO VERSION ----"
	$(TOOLS_DIR)/arm-elf-merge $(FILES_C) -o ios.merged
endif
	cp ios.merged bin/broadon/ios.merged
	$(TOOLS_DIR)/createIOSFlashImg.sh

install: flash
	. boot1.sh
	mkdir -p $(INSTALLDIR)
	$(INSTALL) -m 755 $(FLASHES) $(INSTALLDIR)
	make clean
	@echo ""
	@echo ""
	@echo "Flash files installed into $(INSTALLDIR)"
	@echo ""

files:
	cd ../; make clobber; make headers
	cd ../tools/conv; make install 
	cd ../tools/elf-merge; make install
	cd ../server; make exports
	cd ../nintendo/boot; make install
	cd ../rvl/lib; make exports; make install
	cd ../rvl/apps; make exports; make install
	cd ../rvl/os/ios; make exports; make install
	cd ../rvl/os/di; make exports; make install
	cd ../rvl/os/ppcboot; make install

64:
	. ../rvl_64.sh; make files install

128:
	. ../rvl_128.sh; make files install

both:
	make 64; mkdir RVL_64; cp *.flash RVL_64; make clean;
	make 128; mkdir RVL_128; cp *.flash RVL_128; make clean;
