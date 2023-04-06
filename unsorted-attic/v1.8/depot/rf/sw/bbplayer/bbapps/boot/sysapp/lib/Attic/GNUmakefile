include $(ROOT)/usr/include/make/commondefs
include $(ROOT)/usr/include/make/PRdefs

TARGETS = libsysapp.a

CFILES = launch.c cert.c rl.c meta.c stdlib.c globals.c

OPTIMIZER=
LCOPTS += -mips2 -Wall -g 
ifdef DEBUG
LCOPTS += -DDEBUG
endif
LLDOPTS += -Ttext 0x80000000 -N -G 0
LDIRT += cpu.log*

default : $(TARGETS) 

headers:

exports install: default headers

LDIRT += $(TARGETS)

$(TARGETS): %: %($(OBJECTS))
	ar cru $@ $?
	rm -f $?

include $(COMMONRULES)
