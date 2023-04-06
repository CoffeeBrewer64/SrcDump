include $(ROOT)/usr/include/make/commondefs
include $(ROOT)/usr/include/make/PRdefs

FLASH_FILE = signverify.nand

OBJCOPY = mips-linux-objcopy
REMOVE_SECTS = -R .reginfo -R .note -R .comment -R .mdebug

TARGETS = signverify.hex
ASFILES = ../entry.s skapi.s 
CFILES  = signverify.c

OPTIMIZER=

#LCOPTS += -mips3 -g 
LCOPTS += -mips3 -Os -G 0
LASOPTS += -mips3 -Os -G 0
ifdef ENTRY_ADDR
LLDOPTS += -Ttext $(ENTRY_ADDR) -N
else
LLDOPTS += -Ttext 0x80004000 -N
endif
LDIRT += cpu.log*

ifeq ($(BIG_APP), 1)
LASOPTS += -DBIG_APP
endif

LDIRT += signverify.elf signverify.bin

.PRECIOUS: %.bin

default: $(TARGETS)

#test: default copy

signverify.elf: $(OBJECTS)
	$(CCF) -o signverify.elf $(OBJECTS) $(LDFLAGS)

%.bin: %.elf
	$(OBJCOPY) -O binary -S $(REMOVE_SECTS) $< $@

%.hex: %.bin
	od -v -w4 -An -tx1 $< | tr -d " " > $@
	
install exports headers:

include $(COMMONRULES)
