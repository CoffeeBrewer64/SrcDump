a0 91
include $(ROOT)/usr/include/make/NGdefs

PROGS= di_boot.elf di_boot_dvd.elf di_boot_prod.elf 

LIBS = libdi.a libdi_prod.a
PRODUCTS = di_boot.elf di_boot_prod.elf 

TARGETS = $(PROGS) $(LIBS)

default: $(TARGETS)

include $(COMMONRULES)

LLDLIBS = -lsys -lioslibc -lios -liosc -lisfs
LDIRT += *.bin *.elf *.mrg *.img *.exe phys.link

LCINCS += -I.

CFLAGS += -std=c99
#CFLAGS += -DERR_DEBUG -DLOG_REGS
CFLAGS += -DERR_DEBUG

LCDEFS +=   -DENABLE_DI_HASHOPT
#LCFLAGS += -DSTACK_PRINT

OPTIMIZER += -O2 -fno-strict-aliasing

# When turned on, dvd-video access is always enabled
# THIS HACK NOT TO BE DISTRUBUTED WIDELY
# CFLAGS += -DDVD_ENABLE_HACK


# Size of the unprotected heap usable by applications and not
# the driver - in K bytes.
CFLAGS += -DAPP_HEAP_OPEN_SIZE=32

SRCS        = dvd_driver.c dvd_rvl_mem.c dvd_low.c dvd_low_rvl.c \
              crypto_stub.o sha1.c aes_api.c aes.c aes_imp.c key.c \
              di_boot.c stack.c

DI_BOOT_LDFLAGS =  $(LDLIBS) $(LDFLAGS) -les -Tddr.link -Tphys.link\
               -Ttext=$(MK_DI_VIRT_START)

APP_LDFLAGS =  $(LDLIBS) $(LDFLAGS) -Tddr.link \
               -Ttext=$(MK_APPS_START)
DRIVER_SRC = dvd_driver.c dvd_rvl_mem.c dvd_low.c stack.c

#Files are needed only when doing MD5 sums
DRIVER_SRC += debug.o md5.o

#Files are needed only when doing software decrypt
#DRIVER_SRC += crypto_stub.o sha1.o aes_api.o aes.o aes_imp.o key.o
             
DRIVER_OBJ = $(DRIVER_SRC:.c=.o) dvd_low_rvl.o di_boot.o
DRIVER_OBJ_PROD = $(DRIVER_SRC:.c=.o) dvd_low_rvl_prod.o di_boot_prod.o
DRIVER_OBJ_DVD  = $(DRIVER_SRC:.c=.o) dvd_low_rvl_dvd.o di_boot.o

libdi.a: dvd_low_rvl.o
	$(AR) rc $@ $^

libdi_prod.a: dvd_low_rvl_prod.o
	$(AR) rc $@ $^

di_boot.elf: $(CRT0) $(DRIVER_OBJ) phys.link
	$(CC) $(CFLAGS) -o $@ $(CRT0) $(DRIVER_OBJ) $(DI_BOOT_LDFLAGS)

di_boot_prod.elf: $(CRT0) $(DRIVER_OBJ_PROD) phys.link
	$(CC) $(CFLAGS) -o $@ $(CRT0) $(DRIVER_OBJ_PROD) $(DI_BOOT_LDFLAGS)

di_boot_dvd.elf: $(CRT0) $(DRIVER_OBJ_DVD) phys.link
	$(CC) $(CFLAGS) -o $@ $(CRT0) $(DRIVER_OBJ_DVD) $(DI_BOOT_LDFLAGS)

dvd_low_rvl_dvd.o: dvd_low_rvl.c 
	$(CC) $(CFLAGS) -c -DDVD_ENABLE_HACK -o $@ $^ 

dvd_low_rvl_prod.o: dvd_low_rvl.c 
	$(CC) $(CFLAGS) -c -DRETAIL -o $@ $^ 

di_boot_lo.o: di_boot.c 
	$(CC) $(CFLAGS) -c -DDI_LOW_PRIORITY -o $@ $^ 

di_boot_prod.o: di_boot.c 
	$(CC) $(CFLAGS) -c -DRETAIL -o $@ $^ 

phys.link: phys.sed $(NG_ADDR_MAP)
	sed -e 's/@@DI_PHYS_START@@/$(MK_DI_PHYS_START)/g' phys.sed > $@

exports install: $(PRODUCTS) $(LIBS)
	$(INSTALL) $(PRODUCTS) $(ROOT)/usr/bin/rvl
	$(INSTALL) $(LIBS) $(ROOT)/usr/lib/rvl

