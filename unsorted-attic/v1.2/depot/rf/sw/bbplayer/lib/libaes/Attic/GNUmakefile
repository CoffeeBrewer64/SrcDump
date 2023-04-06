#!smake
#

PRDEPTH = ../..
include $(PRDEPTH)/PRdefs
CC=$(HOST_CC)
GCINCS=-I$(ROOT)/host_include -D_LANGUAGE_C
LCOPTS += -Os -Wall -mcpu=pentiumpro -pedantic -fomit-frame-pointer -DINTEL_GCC

TARGETS = libaes.a

CFILES = rijndael-alg-ref.c  rijndael-api-ref.c

default: $(TARGETS)

include $(PRDEPTH)/PRrules

exports install: default
	$(INSTALL) -m 444 -F /host_lib $(TARGETS)
	$(INSTALL) -m 444 -F /host_include -src rijndael-api-ref.h aes.h

libaes.a: $(OBJECTS)
	ar rc $@ $(OBJECTS)

