#
# $Id: makefile,v 1.1 2006/05/05 21:48:04 jlivesey Exp $
#
include $(ROOT)/usr/include/make/NGdefs
include $(COMMONRULES)

INSTALLDIR=$(ROOT)/usr/bin/rvl/ios_manuf_images
BIN_ROOT=$(ROOT)/usr/bin/rvl
TOOLS_DIR=$(ROOT)/usr/bin/x86
MERGE=arm-elf-merge
OBJ_DUMP=/opt/crosstool/arm-elf/bin/objdump

IOS_C=-k $(BIN_ROOT)/ios_crypto.elf
IOS_NOSHELL_C=-k $(BIN_ROOT)/ios_real.elf
SD_C=-f $(BIN_ROOT)/sdi.elf
SD_BOOT_C=-f sd_boot.elf

LLDLIBS = -mthumb -lsys -liossyscall -lioslibc -lsdi -lios -liosc
LLDOPTS += -T $(ROOT)/usr/lib/rvl/stdalone.link -Ttext $(MK_PPCBOOT_START)

FILES_C = $(IOS_C) $(SD_C) $(SD_BOOT_C)
FILES_NOSHELL_C = $(IOS_NOSHELL_C) $(SD_C) $(SD_BOOT_C)
MERGE_FLAGS="-s 0x13d00000 -z 0x80000"

LCDEFS += -DLOAD_TO_NAPA
C_FILES=sd_boot.c sd_load.c aes_util.c
H_FILES=boot2.h

TARGETS = \
        block1.flash

DIRT += *.flash *.bin *.pad

headers all default exports:

sd_boot.elf: $(CRT0) sd_boot.o sd_load.o aes_util.o key.o iv.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	$(OBJ_DUMP) -h $@
	$(OBJ_DUMP) -d $@ > $@.dump

flash: sd_boot.elf
	mkdir -p bin/broadon
	$(TOOLS_DIR)/$(MERGE) $(FILES_C) $(MERGE_FLAGS) -o ios.merged
	cp ios.merged bin/broadon/ios.merged
	$(TOOLS_DIR)/createManufFlashImg.sh

flash_noshell: sd_boot.elf
	mkdir -p bin/broadon
	$(TOOLS_DIR)/$(MERGE) $(FILES_NOSHELL_C) $(MERGE_FLAGS) -o ios.merged.noshell
	cp ios.merged.noshell bin/broadon/ios.merged.noshell
	# $(TOOLS_DIR)/createManufFlashImg.sh

install: flash flash_noshell
	. boot2.sh
	mkdir -p $(INSTALLDIR)
	$(INSTALL) -m 755 $(TARGETS) $(INSTALLDIR)
	@echo ""
	@echo ""
	@echo "Flash files installed into $(INSTALLDIR)"
	@echo ""

boot2.tar: $(H_FILES) $(C_FILES)
	tar cvf $@ $(H_FILES) $(C_FILES) Makefile

# eof
