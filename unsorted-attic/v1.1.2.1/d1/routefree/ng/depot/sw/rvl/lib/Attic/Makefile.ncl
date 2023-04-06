a0 12
include $(ROOT)/usr/include/make/NGdefs

SUBDIRS = ios ioslibc sys sdi ee fs


include $(COMMONRULES)

INSTALL_FILES = crt0.o crt0_noOS.o ddr.link sdram.link stdalone.link 

exports install: $(INSTALL_FILES)
	$(INSTALL) -m 444 $(INSTALL_FILES) $(ROOT)/usr/lib/rvl

