a0 27
include $(ROOT)/usr/include/make/X86defs

OPTIMIZER = -O2

LLDLIBS = 

TARGETS = arm-elf-merge

CXXFILES = \
	io.cpp		\
	util.cpp	\
	collect.cpp	\
	elf-merge.cpp

default: $(TARGETS)

exports install: default
	$(INSTALL) $(TARGETS) $(BINDIR)

ifneq ($(filter runtests clean clobber, $(MAKECMDGOALS)),)
SUBDIRS = 
endif

include $(COMMONRULES)

arm-elf-merge: $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@ 
