include $(ROOT)/usr/include/make/NGdefs

TARGETS = libisfs.a

CFILES = fs.c

default: $(TARGETS)

exports: $(TARGETS)
	$(INSTALL) $(TARGETS) $(ROOT)/usr/lib/rvl

SUBDIRS = test

include $(COMMONRULES)

$(TARGETS): $(OBJECTS)
	ar rc $@ $^
