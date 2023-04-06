a0 75
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

AR = /opt/crosstool/bin/arm-elf-ar
ARFLAGS = cru

#
# To transition to use ios_crypto as the default IOS, ios.elf is now
# a duplicate of ios_crypto.elf 
#
OS_MINI = mini_ios.elf

OS_TARGETS = $(OS_MINI)
TARGETS = $(OS_TARGETS)

# Separate objs for swi with and without crypto
# Separate objs for initc with and without crypto
# 
# Need to define other objects in the correct order.
# These are not all the required objects
ASFILES = \
    except.s \
	init.s\
	memset32.s

OSCFILES = \
    hwinit.c    \
    message.c   \
    resource.c  \
    timer.c     \
    memory.c    \
	compat_ppcboot.c \
	misc.c\
	clearDDR.c

RVLFILES = ahbops.c \
	       exceptc.c

CFILES = $(OSCFILES) $(RVLFILES) #$(TESTFILES) 

default: $(TARGETS)

exports install: $(TARGETS)
	$(INSTALL) $(OS_TARGETS) $(ROOT)/usr/bin/rvl

sdk-install: $(OS)
	$(INSTALL) -d $(SDK_ROOT)/usr/bin/rvl
	$(INSTALL) $(OS) $(SDK_ROOT)/usr/bin/rvl

include $(COMMONRULES)

# Remove the -mthumb flag.  Some of the .s files are not thumb-mode friendly.
LCDEFS  = -DBUILD_DATE='$(BUILD_DATE)' -DVERSION='$(VERSION)' -DSCRAMBLE_DDR #-DMEASURE_DLY=1

LCFLAGS +=   -Os 
LDIRT += mini_swi.s mini_ios.elf libios.a *.hex *.bin *.list *.dmp crypto_tmp
IOSSH_LIBS = -liossh -lapputils
LLDLIBS = -lsys -lapputils -lios -lioslibc -lgcc

# swi with and without crypto
mini_swi.s: $(ROOT)/usr/include/rvl/mini_syscalls swi.py
	./swi.py $(ROOT)/usr/include/rvl/mini_syscalls mini_swi.s
mini_swi.o: mini_swi.s

compat_thread.o: compat_thread.c
	$(CC) $(CFLAGS) -c $^ -o $@

initc.o: initc.c
	$(CC)  $(CFLAGS) -c $^ -o $@

# Mini IOS for compat mode
OS_MINI_OBJS = init.o mini_swi.o initc.o compat_thread.o $(OBJECTS) 
$(OS_MINI): $(OS_MINI_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS) -T linker_sram.dat
