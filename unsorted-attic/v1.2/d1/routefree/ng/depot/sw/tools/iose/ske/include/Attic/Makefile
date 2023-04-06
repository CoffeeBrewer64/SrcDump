include $(ROOT)/usr/include/make/SKEdefs

HFILES = ngtypes.h \
		 sktypes.h \
		 ng.h \
		 arm.h \
		 sk.h \
		 skerrno.h \
		 skusb.h \
	     emu_skusb.h\
		 skusbtypes.h

SDK_HEADERS = sk.h \
			  sktypes.h \
			  ngtypes.h \
			  skerrno.h \
			  ng.h \
			  skusb.h 

default: 

include $(COMMONRULES)

headers install: $(HFILES)
	$(INSTALL) -m 444 $(HFILES) $(ROOT)/usr/include/ske

sdk-install:
	$(INSTALL) -d $(SDK_ROOT)/usr/include/ske
	$(INSTALL) -m 444 $(SDK_HEADERS) $(SDK_ROOT)/usr/include/ske
