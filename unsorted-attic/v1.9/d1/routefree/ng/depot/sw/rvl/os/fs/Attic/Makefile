include $(ROOT)/usr/include/make/NGdefs

#LCDEFS += -DISFS_DISABLE_SECURITY -DFL_DEBUG_LOG -DISFS_DEBUG_LOG
LCDEFS += -DISFS_DISABLE_SECURITY -DIOS_ENABLE -DNAPA_WORKAROUND
# LLDOPTS += -Ttext $(MK_FS_START) -Tbss ${MK_FS_BSS_START} -T $(DA_LINK)
#LLDOPTS += -T ddr3_stdalone.link
LLDOPTS += -Ttext $(MK_FS_START) -Tddr3_stdalone.link
# LLDLIBS += -lsclibc -lios -liosc
LLDLIBS += -lioslibc -liossyscall 
LDIRT += fs.elf fs.bin

TARGETS = \
    libintflash.a \
    libintfs.a \
    fs.elf

CFILES = \
    fl_ops.c \
    fs_block.c \
    fs_fat.c \
    fs_ops.c \
    fs_mgr.c

HEADERS = \
    fl_utils.h \
    fl_ops.h \
    fs_utils.h \
    fs_ops.h

FLASHLIB_OBJS = \
    fl_ops.o

FSLIB_OBJS = \
    fl_ops.o \
    fs_block.o \
    fs_fat.o \
    fs_ops.o

default: $(TARGETS)

exports: libintflash.a libintfs.a fs.elf
	$(INSTALL) libintflash.a libintfs.a $(ROOT)/usr/lib/rvl
	$(INSTALL) fs.elf $(ROOT)/usr/bin/rvl

# install: fs.bin
# 	$(INSTALL) fs.bin fs.elf $(ROOT)/usr/bin/rvl

headers: $(HEADERS)
	$(INSTALL) $(HEADERS) $(ROOT)/usr/include/rvl

SUBDIRS = test

include $(COMMONRULES)

fs.elf: $(CRT0) $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS) -Ttext=$(MK_FS_START)

libintflash.a: $(FLASHLIB_OBJS)
	ar rc $@ $^

libintfs.a: $(FSLIB_OBJS)
	ar rc $@ $^
