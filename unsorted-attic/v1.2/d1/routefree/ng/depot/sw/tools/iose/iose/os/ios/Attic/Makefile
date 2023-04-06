include $(ROOT)/usr/include/make/commondefs
include $(ROOT)/usr/include/make/IOSEdefs
include $(COMMONRULES)
TARGETS = iose

CFILES = initc.c \
				 thread.c\
				 iose.c \
				 emu_thread.c \
				 emu_startprog.c \
				 emu_event.c \
				 idle.c \
				 message.c \
				 alloc.c  \
				 timer.c \
				 utils.c

LDFLAGS += -ldl -liossyscall 
LCINCS += -I /usr/local/libusb/include

default: $(TARGETS)
	
exports install: default
	$(INSTALL) -p $(TARGETS) $(ROOT)/usr/bin/iose


iose: $(OBJECTS)

sdk-install: default
	$(INSTALL) -d $(SDK_BIN)
	$(INSTALL) $(TARGETS) $(SDK_BIN)
