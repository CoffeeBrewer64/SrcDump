include $(ROOT)/usr/include/make/commondefs
include $(ROOT)/usr/include/make/IOSEdefs
include $(COMMONRULES)
TARGETS = usb_core.so

CFILES =  emu_usb.c \
		  emu_hcd.c\
		  usb.c
LIBUSB_PATH=/usr/local/libusb/lib
RPATH=$(SDK_ROOT)/usr/lib/iose
LIBPATH=-L$(ROOT)/usr/lib/iose -L$(LIBUSB_PATH)
LIBS=-liossyscall -lioslibc $(LIBUSB_PATH)/libusb.a
LDFLAGS += -shared -Wl,-export-dynamic --Wl,-rpath=$(RPATH) $(LIBPATH) $(LIBS) 
LCINCS += -I /usr/local/libusb/include -I../ios/
LCFLAGS += -g 
LDIRT +=*.so
default: $(TARGETS)
	
exports install: default
	$(INSTALL) -p $(TARGETS) $(ROOT)/usr/bin/iose

usb_core.so: $(OBJECTS) 
	$(CC) $^ $(LDFLAGS)  -o $@

sdk-install: default
	$(INSTALL) -d $(SDK_BIN)
	$(INSTALL) $(TARGETS) $(SDK_BIN)
