####
##
##  Trade secret of ATI Technologies Inc.
##  Unpublished work, Copyright 2005 ATI Technologies Inc.
##
##  All rights reserved.  This notice is intended as a precaution against
##  inadvertent publication and does not imply publication or any waiver
##  of confidentiality.  The year included in the foregoing notice is the
##  year of creation of the work.
##
####
include $(ROOT)/usr/include/make/NGdefs
COMMONPREF=ng
include $(COMMONRULES)
INSTALLDIR = $(ROOT)/usr/lib/rvl

LCINCS += -I. -I.. -I$(ROOT)/usr/include/rvl/diag
LCOPTS += -L$(INSTALLDIR)/lib/rvl
LCDEFS = -D_LANGUAGE_C -DINTEL_GCC 

CFILES = \
	sha_hal.c \
	sha_test.c

OBJS = $(CFILES:.c=.o) 
LIB_TARGETS = libshautils.a
AR = ar rc
DIRT += *.o *.a

default: install

install: $(LIB_TARGETS)
	$(INSTALL) -m 444 $(LIB_TARGETS) $(INSTALLDIR)

clobber: $(COMMONPREF)clobber
	cd $(INSTALLDIR); $(RM) $(LIB_TARGETS)

clean: $(COMMONPREF)clean

$(LIB_TARGETS): $(OBJS)
	$(AR) $@ $^ 

