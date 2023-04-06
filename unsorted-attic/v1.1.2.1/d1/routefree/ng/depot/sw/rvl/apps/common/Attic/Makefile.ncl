a0 63
include $(ROOT)/usr/include/make/NGdefs

OPTIMIZER = -O2

TARGETS = libapputils.a libapputils_fast.a

# LCDEFS += -DFL_DEBUG_LOG
LCOPTS += -mlong-calls

ASFILES = \
	cache_lock.s \
	mmu1.s

CFILES = \
	apputils.c \
	cache.c \
	elfload.c\
	dolload.c\
	minimon_elfload.c\
	minimon_osrun.c\
	minimon_ioprun.c\
	flash.c\
	mmu.c\
	mmu2.c\
	memory.c\
	printascii.c\
	little2big.c \
	minimon_binload.c\
	binload.c \
	minimon_bindump.c\
	bindump.c \
	minimon_hwinit.c\
	minimon_mem.c\
	ppcboot.c

HEADERS = \
    apputils.h

FL_OBJS = fl_ops.o

FL_FAST_OBJS = fl_ops_fast.o

default: $(TARGETS)

exports: default
	$(INSTALL) $(TARGETS) $(ROOT)/usr/lib/rvl

headers: $(HEADERS)
	$(INSTALL) $(HEADERS) $(ROOT)/usr/include/rvl

include $(COMMONRULES)

libapputils.a: $(OBJECTS) $(FL_OBJS)
	$(AR) rc $@ $^

libapputils_fast.a: $(OBJECTS) $(FL_FAST_OBJS)
	$(AR) rc $@ $^

libapputils_fl.a: $(FL_OBJS)
	$(AR) rc $@ $^

fl_ops_fast.o: fl_ops.c
	$(CC) $(CFLAGS) -DFL_FAST_TIMING -o $@ -c $^
