include $(ROOT)/usr/include/make/SKEdefs

TARGETS = libnglibc.a

CFILES = \
    exit.c \
    printf.c \
    string.c \
	perror.c \
	usb.c

LCINCS += -I /usr/local/usb/include 

default: $(TARGETS)

headers:
	$(INSTALL) -m 444 nglibc.h $(ROOT)/usr/include/ske

exports install: $(TARGETS) headers
	$(INSTALL) -m 444 $(TARGETS) $(ROOT)/usr/lib/ske

sdk-install: $(TARGETS)
	$(INSTALL) -m 444 $(TARGETS) $(SDK_LIB)
	$(INSTALL) -m 444 nglibc.h $(SDK_INC)

$(TARGETS): %: %($(OBJECTS))
	ar cru $@ $?

ifneq ($(filter runtests clean clobber, $(MAKECMDGOALS)),)
SUBDIRS = test
endif

include $(COMMONRULES)
