include $(ROOT)/usr/include/make/commondefs
include $(ROOT)/usr/include/make/SKEdefs
include $(COMMONRULES)
TARGETS = usb_core.so

CFILES =  emu_usb.c \
		  emu_hcd.c\
		  usb.c
LIBUSB_PATH=/usr/local/usb/lib
RPATH=$(SDK_ROOT)/usr/lib/ske
LIBPATH=-L$(ROOT)/usr/lib/ske -L$(LIBUSB_PATH)
LIBS=-lngsyscall -lnglibc $(LIBUSB_PATH)/libusb.a
LDFLAGS += -shared -Wl,-export-dynamic --Wl,-rpath=$(RPATH) $(LIBPATH) $(LIBS) 
LCINCS += -I /usr/local/usb/include -I../sk/
LCFLAGS += -g 
LDIRT +=*.so
default: $(TARGETS)
	
exports install: default
	$(INSTALL) -p $(TARGETS) $(ROOT)/usr/bin/ske

usb_core.so: $(OBJECTS) 
	$(CC) $^ $(LDFLAGS)  -o $@

sdk-install: default
	$(INSTALL) -d $(SDK_BIN)
	$(INSTALL) $(TARGETS) $(SDK_BIN)
