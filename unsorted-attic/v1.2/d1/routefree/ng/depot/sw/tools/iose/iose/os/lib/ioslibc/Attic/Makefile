include $(ROOT)/usr/include/make/IOSEdefs

TARGETS = libioslibc.a

CFILES = \
    exit.c \
    printf.c \
    string.c \
	perror.c \
	usb.c

LCINCS += -I /usr/local/libusb/include 

default: $(TARGETS)

headers:
	$(INSTALL) -m 444 ioslibc.h $(ROOT)/usr/include/iose

exports install: $(TARGETS) headers
	$(INSTALL) -m 444 $(TARGETS) $(ROOT)/usr/lib/iose

sdk-install: $(TARGETS)
	$(INSTALL) -m 444 $(TARGETS) $(SDK_LIB)
	$(INSTALL) -m 444 ioslibc.h $(SDK_INC)

$(TARGETS): %: %($(OBJECTS))
	ar cru $@ $?

ifneq ($(filter runtests clean clobber, $(MAKECMDGOALS)),)
SUBDIRS = test
endif

include $(COMMONRULES)
