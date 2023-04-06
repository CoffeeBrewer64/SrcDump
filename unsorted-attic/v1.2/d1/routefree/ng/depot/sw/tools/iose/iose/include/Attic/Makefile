include $(ROOT)/usr/include/make/IOSEdefs

HFILES = iostypes.h \
		 arm.h \
		 ios.h \
		 ioserrno.h \
		 iosusb.h \
	     emu_iosusb.h\
		 iosusbtypes.h\
		 iosdebug.h

SDK_HEADERS = ios.h \
			  iostypes.h \
			  ioserrno.h \
			  iosusb.h\
			  iosusbtypes.h

default: 

include $(COMMONRULES)

headers install: $(HFILES)
	$(INSTALL) -m 444 $(HFILES) $(ROOT)/usr/include/iose

sdk-install:
	$(INSTALL) -d $(SDK_ROOT)/usr/include/iose
	$(INSTALL) -m 444 $(SDK_HEADERS) $(SDK_ROOT)/usr/include/iose
