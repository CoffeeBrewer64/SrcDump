include $(ROOT)/usr/include/make/commondefs
include $(ROOT)/usr/include/make/SKEdefs
include $(COMMONRULES)
TARGETS = ske

CFILES = initc.c \
				 thread.c\
				 ske.c \
				 emu_thread.c \
				 emu_startprog.c \
				 emu_event.c \
				 idle.c \
				 message.c \
				 alloc.c  \
				 timer.c \
				 utils.c

LDFLAGS += -ldl -lngsyscall 
LCINCS += -I /usr/local/usb/include

default: $(TARGETS)
	
exports install: default
	$(INSTALL) -p $(TARGETS) $(ROOT)/usr/bin/ske


ske: $(OBJECTS)

sdk-install: default
	$(INSTALL) -d $(SDK_BIN)
	$(INSTALL) $(TARGETS) $(SDK_BIN)
