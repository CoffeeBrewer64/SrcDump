a0 115
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

# Tool paths
IOSTOOLDIR ?= /opt/crosstool/bin
TOOLDIR=$(HOSTBINDIR)
ASCII2BIN=$(TOOLDIR)/ascii2bin.py
BIN2C=$(TOOLDIR)/bin2c.py
LIBROOT=$(ROOT)/usr/lib/rvl
OBJDUMP ?= $(IOSTOOLDIR)/arm-elf-objdump

# Maximum size for code, data, and bss
BOOT1_MAX_CODEDATA_SIZE = 24576
BOOT1_MAX_BSS_SIZE = 8192

# Targets
PRODUCTS = boot1_dev.flash \
           boot1_prod_diag.flash \
           boot1_ati.flash \
           boot1_nintendo.flash boot1_dev.aes

TARGETS = $(PRODUCTS)

default: $(TARGETS)

exports install: $(TARGETS)
	$(INSTALL) $(PRODUCTS) $(ROOT)/usr/bin/rvl

# Build options
LDIRT += *.elf *.list *.hex *.mem *.sha *.bin *.padded *.decrypted \
        *.flash *.aes *.log

LCDEFS += -DENABLE_DEBUG
LCDEFS += -DENABLE_SS
LCDEFS += -DBOOT1_DISABLE_EFUSE -DBOOT1_DISABLE_EEPROM
LLDLIBS += -L . -lee -lsys -lioslibc
LLDOPTS += -T $(ROOT)/usr/lib/rvl/stdalone.link -Ttext 0x0d400000

# Boot1-specific flags
BOOT1_CFLAGS = -DLOAD_TO_NAPA
BOOT1_CFLAGS += -DBOOT1_MAX_CODEDATA_SIZE='$(BOOT1_MAX_CODEDATA_SIZE)'
BOOT1_CFLAGS += -DBOOT1_MAX_BSS_SIZE='$(BOOT1_MAX_BSS_SIZE)'

# Common rules
include $(COMMONRULES)


# boot1 using the development PKI 
boot1_dev.o: boot1_dev.c
	$(CC) -c -DRVL_DEVEL_PKI $(BOOT1_CFLAGS) $(CFLAGS) -o $@ $^ 

boot1_dev.elf: boot1_sram1.o boot1_dev.o
	$(CC) $(CFLAGS) -o $@ $^ $(LINK_SRAM_FLAGS) $(LDFLAGS) -lboot1_dev $(LDLIBS) -lcsl_dev

boot1_dev.bin: boot1_dev.elf
	size $^ > boot1_dev.size
	split -1 boot1_dev.size boot1_dev.split
	@if [ `awk '{print $$3}' boot1_dev.splitab` -gt $(BOOT1_MAX_BSS_SIZE) ]; then \
		echo "boot1_dev.elf BSS too large"; \
		size $^; \
		exit 1; \
	fi
	rm -f boot1_dev.size boot1_dev.split*
	$(CONVERT) -o $@ $^

boot1_dev.aes: boot1_dev.bin
	@if [ `ls -l $^ | awk '{print $$5}'` -gt $(BOOT1_MAX_CODEDATA_SIZE) ]; then \
		echo "boot1_dev.bin code+data too large"; \
		ls -l $^; \
		exit 1; \
	fi
	$(HOSTBINDIR)/aes_encode $^ $@

boot1_dev.padded: boot1_dev.aes
	$(HOSTBINDIR)/padfile.sh 131072 $^ boot1_dev.padded

boot1_dev.flash: boot1_dev.elf
	$(HOSTBINDIR)/makeimg boot1_dev 0
	mv boot1_dev.flash.bin.big $@

# Build boot1 using the production PKI
boot1_prod_diag.o: boot1_dev.c
	$(CC) -c -DRVL_PROD_PKI $(BOOT1_CFLAGS) $(CFLAGS) -o $@ $^ 

boot1_prod_diag.elf: boot1_sram1.o boot1_prod_diag.o
	$(CC) $(CFLAGS) -o $@ $^ $(LINK_SRAM_FLAGS) $(LDFLAGS) -lboot1_prod $(LDLIBS) -lcsl 

boot1_prod_diag.flash: boot1_prod_diag.elf
	$(HOSTBINDIR)/makeimg boot1_prod_diag 0
	mv boot1_prod_diag.flash.bin.big $@

# Build PPC boot1
BOOT1_PPCBOOT_LDFLAGS = -lapputils $(LDFLAGS) $(LDLIBS)  -T $(ROOT)/usr/lib/rvl/stdalone.link

boot1N.o: boot1_ppcboot.c
	$(CC) -c -D__RVL_BUILD__  $(CFLAGS) -o $@ $^ 

boot1_ppcboot_nintendo.elf: init.o boot1N.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LINK_SRAM_FLAGS) $(BOOT1_PPCBOOT_LDFLAGS)

boot1_nintendo.flash: boot1_ppcboot_nintendo.elf
	$(HOSTBINDIR)/makeimg boot1_ppcboot_nintendo 0
	mv boot1_ppcboot_nintendo.flash.bin.big $@

boot1A.o: boot1_ppcboot.c
	$(CC) -c -D__ATI_BUILD__  $(CFLAGS) -o $@ $^ 

boot1_ppcboot_ati.elf: init.o boot1A.o
	$(CC) $(CFLAGS) -o $@ $^ $(LINK_SRAM_FLAGS) $(BOOT1_PPCBOOT_LDFLAGS)

boot1_ati.flash: boot1_ppcboot_ati.elf
	$(HOSTBINDIR)/makeimg boot1_ppcboot_ati 0
	mv boot1_ppcboot_ati.flash.bin.big $@

