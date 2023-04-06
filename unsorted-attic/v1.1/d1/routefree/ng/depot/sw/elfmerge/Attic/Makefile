d8 3
a10 9
IOS=$(BIN_ROOT)/ios_noshell.elf
DI=$(BIN_ROOT)/di_boot_nocrypto.elf
FS=$(BIN_ROOT)/fs_nocrypto.elf
PPCBOOT=$(BIN_ROOT)/ppcboot.elf

IOS_C=$(BIN_ROOT)/ios_crypto.elf
DI_C=$(BIN_ROOT)/di_boot.elf
PS_C=$(BIN_ROOT)/fs.elf
PPCBOOT_C=$(BIN_ROOT)/ppcboot.elf
d12 21
a32 1
TARGETS = \
d39 1
a39 1
DIRT += *.flash bin
d43 1
a43 1
flash:
d47 7
a53 1
	$(TOOLS_DIR)/arm-elf-merge.exe -k $(IOS) -f $(FS) -f $(PPCBOOT) -f $(DI) -o ios.merged
a55 2
	rm *.bin
	rm ios*
d60 2
a61 1
	$(INSTALL) -m 755 $(TARGETS) $(INSTALLDIR)
d67 11
a77 8
crypto:
	mkdir -p crypto/bin/nintendo
	mkdir -p crypto/bin/broadon
	cp -lrf $(ROOT)/usr/bin/nintendo crypto/bin
	$(TOOLS_DIR)/arm-elf-merge.exe -k $(IOS_C), -f $(FS_C) -f $(PPCBOOT_C) -f $(DI_C) -o ios.merged.crypto
	cp ios.merged crypto/bin/broadon/ios.merged.crypto
	cd crypto
	$(TOOLS_DIR)/createIOSFlashImg.sh
