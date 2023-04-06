a0 67
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

TARGETS = loader.bin loader_boot2.bin

ASFILES = \
    loaders.s\
	run.s

CFILES = \
    loaderc.c\
	relocate.c

LOADER_OBJS = \
    loaders.o \
    loaderc.o \
	relocate.o

LOADER_BOOT2_OBJS = \
	loaders_boot2.o \
	loaderc_boot2.o

default: $(TARGETS)


exports: $(TARGETS)
	$(INSTALL) $^ $(ROOT)/usr/bin/rvl

install: exports

include $(COMMONRULES)

LDIRT += loader.elf loader_boot2.elf
LCDEFS += -fPIC
LLDOPTS += -T stdalone.link
LLDLIBS += -lsys -lioslibc

#loader.elf supports launch buffer relication.
#_Must_ link run.o at the end
loader.elf: $(LOADER_OBJS) run.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(LOADER_OBJS) $(LDLIBS) run.o

# boot2 loader does not support launch buffer relocation.
loaders_boot2.o: loaders.s
	$(AS) $(ASFLAGS) -DBUILD_BOOT2_LOADER $^ -o $@

loaderc_boot2.o: loaderc.c
	$(CC) $(CFLAGS) -DBUILD_BOOT2_LOADER -c $^ -o $@

loader_boot2.elf: $(LOADER_BOOT2_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# The loader should not need a BSS. If it does need one, then
# the createOSImage.py script needs to be modified to account
# for that when calculating the loader size
#
%.bin: %.elf
	size $^ > loader.size
	split -1 loader.size loader.split
	@if [ `awk '{print $$3}' loader.splitab` -gt 0 ]; then \
		echo "loader can not have a BSS"; \
		size $^; \
		exit 1; \
	fi
	rm -f loader.size loader.split*
	$(CONVERT) -o $@ $^
