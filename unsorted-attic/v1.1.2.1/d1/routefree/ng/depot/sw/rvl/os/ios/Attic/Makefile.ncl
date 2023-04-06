a0 277
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

AR = /opt/crosstool/bin/arm-elf-ar
ARFLAGS = cru

#
# To transition to use ios_crypto as the default IOS, ios_real.elf is now
# a duplicate of ios_crypto.elf 
#
OS = ios.elf
OS_CRYPTO = ios_crypto.elf
OS_CSL = ios_csl.elf
OS_REAL = ios_real.elf
OS_REAL_CSL = ios_real_csl.elf
OS_SKIPEF = ios_skipef_prod.elf
OS_NCRYPTO = ios_ncrypto.elf
OS_PROFILE = ios_profile.elf
BOOT2_OS_DEV = boot2_ios_dev.elf
BOOT2_OS_REAL = boot2_ios.elf
PROD_OS_REAL = ios_prod.elf
PROD_BOOT2_OS_REAL = boot2_ios_prod.elf

CRYPTO_LINKER_FILE = linker_sram_ddr.dat
NOCRYPTO_LINKER_FILE = linker_sram.dat

OS_TARGETS = $(OS) $(OS_CRYPTO) $(OS_REAL) $(OS_PROFILE) $(BOOT2_OS_REAL) \
             $(OS_SKIPEF) $(PROD_OS_REAL) $(PROD_BOOT2_OS_REAL) $(BOOT2_OS_DEV)\
             $(OS_CSL) $(OS_REAL_CSL)
TARGETS = $(CRYPTO_LINKER_FILE) $(NOCRYPTO_LINKER_FILE) crypto_objs $(OS_TARGETS)

# Separate objs for swi with and without crypto
# Separate objs for initc with and without crypto
# 
# Need to define other objects in the correct order.
# These are not all the required objects
ASFILES = \
	cache.s\
	mmu1.s	

OSCFILES = \
    hwinit.c    \
    message.c   \
    resource.c  \
    timer.c     \
    memory.c    \
    ipcsrv.c \
	mmu.c \
	napa_refresh.c\
	iobuf.c\
	cachec.c\
	cryptostack.c

RVLFILES = ahbops.c \
	       exceptc.c\
	       acr.c\
		   misc.c

TESTFILES =	testthr.c

CFILES = $(OSCFILES) $(RVLFILES) #$(TESTFILES) 

default: $(TARGETS)

exports install: $(TARGETS)
	$(INSTALL) $(OS_TARGETS) $(ROOT)/usr/bin/rvl

sdk-install: $(OS)
	$(INSTALL) -d $(SDK_ROOT)/usr/bin/rvl
	$(INSTALL) $(OS) $(SDK_ROOT)/usr/bin/rvl

include $(COMMONRULES)

# Fine-grained access flags
FG_FLAGS = #-DENABLE_FG -DENABLE_FG_DBG

# Remove the -mthumb flag.  Some of the .s files are not thumb-mode friendly.
LCDEFS  = -DBUILD_DATE='$(BUILD_DATE)' -DVERSION='$(VERSION)'
LCDEFS += -DENABLE_GET_USAGE $(FG_FLAGS)  -DENABLE_DI_HASHOPT

#LCDEFS += -DENABLE_THREAD_PROFILE
#LASDEFS += -DENABLE_THREAD_PROFILE
LASDEFS += $(FG_FLAGS)

LDIRT += swi_crypto.s ios.elf libios.a *.hex *.bin *.list *.dmp crypto_tmp shell_tmp
IOSSH_LIBS = -liossh -lapputils
LLDLIBS = -lsys -lioslibc -lee -lgcc 

CRYPTCALLS = $(ROOT)/usr/include/cryptcalls
SYSCALLS   = $(ROOT)/usr/include/rvl/syscalls
SYSCALLS2   = $(ROOT)/usr/include/rvl/syscalls2

swi_crypto.s: $(SYSCALLS) $(CRYPTCALLS) $(SYSCALLS2) swi.py
	./swi.py $(SYSCALLS) $(CRYPTCALLS) $(SYSCALLS2) swi_crypto.s
swi_crypto.o: swi_crypto.s

# Init with and without crypto
initc_crypto.o: initc.c
	$(CC) -mlong-calls -DENABLE_CRYPTO $(CFLAGS) -c $^ -o $@

thread_crypto.o: thread.c
	$(CC) -mlong-calls -DENABLE_CRYPTO $(CFLAGS) -c $^ -o $@

thread.o: thread.c
	$(CC) $(CFLAGS) -c $^ -o $@

thread_noshell.o: thread.c
	$(CC) -DENABLE_ELF_MERGE $(CFLAGS) -c $^ -o $@

thread_real.o: thread.c
	$(CC) -mlong-calls -DENABLE_CRYPTO -DENABLE_ELF_MERGE $(CFLAGS) -c $^ -o $@

thread_profile.o: thread.c
	$(CC) -mlong-calls -DENABLE_CRYPTO -DENABLE_ELF_MERGE -DENABLE_THREAD_PROFILE $(CFLAGS) -c $^ -o $@

thread_prod.o: thread.c
	$(CC) -mlong-calls -DENABLE_CRYPTO -DENABLE_ELF_MERGE -DRVL_PROD_PKI $(CFLAGS) -c $^ -o $@

except_profile.o: except.s
	$(AS) -DENABLE_THREAD_PROFILE $(ASFLAGS) -c $^ -o $@

initc.o: initc.c
	$(CC)  $(CFLAGS) -c $^ -o $@

# keyglobals
keyglobals.o: $(BSL_LIB)
	$(AR) x $(BSL_LIB) $@

# cslrsa_dev.o - Development version for CSL_VerifyRsaSig()
cslrsa_dev.o: $(CSL_DEV_LIB)
	$(AR) x $(CSL_DEV_LIB) $@
	rm -f crypto_tmp/cslrsa*.o
	mv $@ crypto_tmp/.

# cslrsa.o - Production version for CSL_VerifyRsaSig()
cslrsa.o: $(CSL_LIB)
	$(AR) x $(CSL_LIB) $@
	rm -f crypto_tmp/cslrsa*.o
	mv $@ crypto_tmp/.

# version for OS
version.o: version.c
	$(CC) $(CFLAGS) -c $^ -o $@

# version for BOOT2
version_boot2.o: version.c
	$(CC) -DBOOT2 $(CFLAGS) -c $^ -o $@

# eFuse/EEPROM check
nvram.o: nvram.c
	$(CC) $(CFLAGS) -DENABLE_EFINIT -c $^ -o $@

nvram_prod.o: nvram.c
	$(CC) $(CFLAGS) -DRVL_PROD_PKI -DENABLE_EFINIT -c $^ -o $@

nvram_skipef.o: nvram.c
	$(CC) $(CFLAGS) -DRVL_PROD_PKI -c $^ -o $@

#Crypto objects which live in DDR
BSL_LIB = $(ROOT)/usr/lib/rvl/libbsl.a
CSL_LIB =$(ROOT)/usr/lib/rvl/libcsl.a
CSL_DEV_LIB =$(ROOT)/usr/lib/rvl/libcsl_dev.a
CRYPTO_LIBS = $(BSL_LIB) $(CSL_LIB)

crypto_tmp/crypto.o: crypto.c
	rm -rf crypto_tmp;mkdir crypto_tmp
	$(CC) $(CFLAGS) -mlong-calls -c $^ -o $@

cryptostack.o: cryptostack.c
	$(CC) $(CFLAGS) -mlong-calls -marm -c cryptostack.c -o $@

root_devel.o: root.c
	$(CC) $(CFLAGS) -DRVL_DEVEL_PKI -c $^ -o $@


root_prod.o: root.c
	$(CC) $(CFLAGS) -DRVL_PROD_PKI -c $^ -o $@

crypto_objs: $(CRYPTO_LIBS) crypto_tmp/crypto.o
	cd crypto_tmp; ar x $(BSL_LIB);ar x $(CSL_LIB)
	rm crypto_tmp/aes*.o 
	rm crypto_tmp/keyglobals.o 
	rm crypto_tmp/sha1.o
	rm crypto_tmp/prng.o
	rm crypto_tmp/cslrsa.o

$(CRYPTO_LINKER_FILE): linker_sram_ddr.sed 
	sed -e 's/@@CRYPTO_START@@/$(MK_CRYPTO_START)/g' \
	-e 's/@@KERNEL_DATA_END@@/$(MK_KERNEL_DATA_END)/g' \
	-e 's/@@DIR_TMP@@/crypto_tmp/g' \
	-e 's/@@SHELL_TMP@@/shell_tmp/g' \
	$< > $@

#In non-crypto build, still use crypto addr space to put shell.
$(NOCRYPTO_LINKER_FILE): linker_sram.sed
	sed -e 's/@@CRYPTO_START@@/$(MK_CRYPTO_START)/g' \
	-e 's/@@KERNEL_DATA_END@@/$(MK_KERNEL_DATA_END)/g' \
	-e 's/@@SHELL_TMP@@/shell_tmp/g' \
	$< > $@

# IOSSH objects which live in DDR
IOSSH_LIB = $(ROOT)/usr/lib/rvl/libiossh.a
APPUTILS_LIB = $(ROOT)/usr/lib/rvl/libapputils.a

# Extract objects used by iossh (not everything in libapputils is
# needed)
IOSSH_OBJS = iossh.o
APPUTIL_OBJS = apputils.o\
			   binload.o\
			   bindump.o\
			   ppcboot.o\
			   minimon_bindump.o\
			   minimon_binload.o\
			   elfload.o\
			   little2big.o

shell_objs: $(IOSSH_LIB)
	rm -rf shell_tmp; mkdir shell_tmp
	cd shell_tmp; ar x $(IOSSH_LIB) $(IOSSH_OBJS); ar x $(APPUTILS_LIB) $(APPUTIL_OBJS)

# Crypto image: final link
CRYPTO_OBJS = init.o initc_crypto.o swi_crypto.o thread_crypto.o version.o root_devel.o nvram.o keyglobals.o except.o $(OBJECTS) 
$(OS_CRYPTO): $(CRYPTO_LINKER_FILE) crypto_objs cslrsa_dev.o shell_objs $(CRYPTO_OBJS)
	$(CC) $(CFLAGS) -o $(OS_CRYPTO) $(CRYPTO_OBJS) crypto_tmp/*.o shell_tmp/*.o $(LDFLAGS) $(LDLIBS) -T $(CRYPTO_LINKER_FILE)

$(OS): $(OS_CRYPTO)
	cp -f $(OS_CRYPTO) $@

# Real image with crypto, cslrsa and shell
$(OS_CSL): $(CRYPTO_LINKER_FILE) crypto_objs cslrsa.o shell_objs $(CRYPTO_OBJS)
	$(CC) $(CFLAGS) -o $(OS_CSL) $(CRYPTO_OBJS) crypto_tmp/*.o shell_tmp/*.o $(LDFLAGS) $(LDLIBS) -T $(CRYPTO_LINKER_FILE)

#Image without crypto support
IOS_OBJS = init.o swi.o initc.o thread.o version.o nvram.o except.o $(OBJECTS)
$(OS_NCRYPTO): $(NOCRYPTO_LINKER_FILE) $(IOS_OBJS)
	$(CC) $(CFLAGS) -o $@ $(IOS_OBJS) $(LDFLAGS) $(IOSSH_LIBS) $(LDLIBS) -T linker_sram.dat

# Real image with crypto and no shell
REAL_OBJS = init.o initc_crypto.o swi_crypto.o thread_real.o version.o root_devel.o nvram.o keyglobals.o except.o $(OBJECTS) 
$(OS_REAL): $(CRYPTO_LINKER_FILE) crypto_objs cslrsa_dev.o $(REAL_OBJS)
	$(CC) $(CFLAGS) -o $(OS_REAL) $(REAL_OBJS) crypto_tmp/*.o $(LDFLAGS) $(LDLIBS) -T $(CRYPTO_LINKER_FILE)

# Real image with crypto, cslrsa and no shell
$(OS_REAL_CSL): $(CRYPTO_LINKER_FILE) crypto_objs cslrsa.o $(REAL_OBJS)
	$(CC) $(CFLAGS) -o $(OS_REAL_CSL) $(REAL_OBJS) crypto_tmp/*.o $(LDFLAGS) $(LDLIBS) -T $(CRYPTO_LINKER_FILE)

# Real image with crypto, profile and no shell
PROFILE_OBJS = init.o initc_crypto.o swi_crypto.o thread_profile.o version.o root_devel.o nvram.o keyglobals.o except_profile.o $(OBJECTS) 
$(OS_PROFILE): $(CRYPTO_LINKER_FILE) crypto_objs cslrsa_dev.o $(PROFILE_OBJS)
	$(CC) $(CFLAGS) -o $(OS_PROFILE) $(PROFILE_OBJS) crypto_tmp/*.o $(LDFLAGS) $(LDLIBS) -T $(CRYPTO_LINKER_FILE)

# Real image with eFuse/EEPROM check disabled
SKIPEF_OBJS = init.o initc_crypto.o swi_crypto.o thread_real.o version.o root_prod.o nvram_skipef.o keyglobals.o except.o $(OBJECTS) 
$(OS_SKIPEF): $(CRYPTO_LINKER_FILE) crypto_objs cslrsa.o $(SKIPEF_OBJS)
	$(CC) $(CFLAGS) -o $(OS_SKIPEF) $(SKIPEF_OBJS) crypto_tmp/*.o $(LDFLAGS) $(LDLIBS) -T $(CRYPTO_LINKER_FILE)

# Real BOOT2 image with crypto, cslrsa.o and no shell
BOOT2_REAL_OBJS = init.o initc_crypto.o swi_crypto.o thread_real.o version_boot2.o root_devel.o nvram.o keyglobals.o except.o $(OBJECTS) 
$(BOOT2_OS_REAL): crypto_objs cslrsa.o $(BOOT2_REAL_OBJS)
	$(CC) $(CFLAGS) -o $(BOOT2_OS_REAL) $(BOOT2_REAL_OBJS) crypto_tmp/*.o $(LDFLAGS) $(LDLIBS) -T $(CRYPTO_LINKER_FILE)

# Real BOOT2 image with crypto, cslrsa_dev and no shell
$(BOOT2_OS_DEV): crypto_objs cslrsa_dev.o $(BOOT2_REAL_OBJS)
	$(CC) $(CFLAGS) -o $(BOOT2_OS_DEV) $(BOOT2_REAL_OBJS) crypto_tmp/*.o $(LDFLAGS) $(LDLIBS) -T $(CRYPTO_LINKER_FILE)


# Real production image with crypto, cslrsa.o and no shell
PROD_REAL_OBJS = init.o initc_crypto.o swi_crypto.o thread_prod.o version.o root_prod.o nvram_prod.o keyglobals.o except.o $(OBJECTS) 
$(PROD_OS_REAL): $(CRYPTO_LINKER_FILE) crypto_objs cslrsa.o $(PROD_REAL_OBJS)
	$(CC) $(CFLAGS) -o $(PROD_OS_REAL) $(PROD_REAL_OBJS) crypto_tmp/*.o $(LDFLAGS) $(LDLIBS) -T $(CRYPTO_LINKER_FILE)

# Real production BOOT2 image with crypto, cslrsa.o and no shell
PROD_BOOT2_REAL_OBJS = init.o initc_crypto.o swi_crypto.o thread_prod.o version_boot2.o root_prod.o nvram_prod.o keyglobals.o except.o $(OBJECTS) 
$(PROD_BOOT2_OS_REAL): crypto_objs cslrsa.o $(PROD_BOOT2_REAL_OBJS)
	$(CC) $(CFLAGS) -o $(PROD_BOOT2_OS_REAL) $(PROD_BOOT2_REAL_OBJS) crypto_tmp/*.o $(LDFLAGS) $(LDLIBS) -T $(CRYPTO_LINKER_FILE)

