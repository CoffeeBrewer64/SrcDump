include $(ROOT)/usr/include/make/X86defs

LLDLIBS = 

TARGETS = arm-elf-merge

CXXFILES = \
	io.cpp		\
	util.cpp	\
	collect.cpp	\
	elf-merge.cpp

default: $(TARGETS)

exports install: default
	$(INSTALL) $(TARGETS) $(ROOT)/usr/bin/x86

ifneq ($(filter runtests clean clobber, $(MAKECMDGOALS)),)
SUBDIRS = 
endif

include $(COMMONRULES)

arm-elf-merge: $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@ 
