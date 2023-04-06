include $(ROOT)/usr/include/make/NGdefs

VPATH = string stdio other

LCINCS = -I$(ROOT)/usr/include/rvl
LCOPTS = -O2

TARGETS = libioslibc.a

STRING_CFILES = \
    memcmp.c \
    memmove.c \
    strchr.c \
    strstr.c \
    strncpy.c \
    strrchr.c \
    memcpy.c \
    memset.c \
    strncmp.c \
    strnlen.c

STDIO_CFILES = \
    fclose.c \
    flen.c \
    fopen.c \
    fread.c \
    fseek.c \
    fwrite.c \
    getchar.c \
    gets.c \
    busPrintf.c \
    printf.c \
    putchar.c \
    puts.c \
    rename.c  \
    scanf.c \
    time.c \
    tmpnam.c \
    unlink.c

CFILES = \
    $(STDIO_CFILES) \
    $(STRING_CFILES) \
    get_cmdline.c \
    exit.c \
	usleep.c\
	iobuf.c \
	busdelay.c

ASFILES = \
    vio.s

default: $(TARGETS)

headers:
	$(INSTALL) -m 444 ioslibc.h $(ROOT)/usr/include/rvl

exports install: $(TARGETS) headers
	$(INSTALL) -m 444 $(TARGETS) $(ROOT)/usr/lib/rvl

sdk-install: default
	$(INSTALL) -d $(SDK_ROOT)/usr/lib/rvl
	$(INSTALL) $(TARGETS) $(SDK_ROOT)/usr/lib/rvl

$(TARGETS): %: %($(OBJECTS))
	ar cru $@ $?

include $(COMMONRULES)
