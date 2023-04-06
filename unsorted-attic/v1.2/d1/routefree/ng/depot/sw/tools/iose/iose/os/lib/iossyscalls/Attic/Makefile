include $(ROOT)/usr/include/make/IOSEdefs

TARGETS = libiossyscall.a
OBJECTS = syscall.o 

default: $(TARGETS)

exports install: $(TARGETS)
	$(INSTALL) -m 444 $(TARGETS) $(ROOT)/usr/lib/iose

sdk-install: $(TARGETS)
	$(INSTALL) -d $(SDK_LIB)
	$(INSTALL)  -m 444 $(TARGETS) $(SDK_LIB)

$(TARGETS): %: %($(OBJECTS))
	ar cru $@ $?

LDIRT += syscall.o syscall.c

syscall.c: syscalls usb_syscalls syscall_emu.py
	./syscall_emu.py syscalls usb_syscalls $@


include $(COMMONRULES)
