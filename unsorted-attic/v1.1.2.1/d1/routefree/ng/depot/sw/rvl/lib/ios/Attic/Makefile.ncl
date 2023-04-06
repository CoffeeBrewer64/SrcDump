a0 23
include $(ROOT)/usr/include/make/NGdefs

TARGETS = libios.a

ASFILES = syscall.s

SYSCALLS1 = $(ROOT)/usr/include/rvl/syscalls
SYSCALLS2 = $(ROOT)/usr/include/rvl/syscalls2

default: $(TARGETS)

exports install: $(TARGETS)
	$(INSTALL) -m 444 $(TARGETS) $(ROOT)/usr/lib/rvl

$(TARGETS): %: %($(OBJECTS))
	ar cru $@ $?

LDIRT += syscall.s

syscall.s: $(SYSCALLS1) $(SYSCALLS2) syscall.py
	./syscall.py IOS $(SYSCALLS1) $(SYSCALLS2) $@

include $(COMMONRULES)
