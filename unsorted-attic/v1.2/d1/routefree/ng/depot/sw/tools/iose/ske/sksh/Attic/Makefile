include $(ROOT)/usr/include/make/commondefs
include $(ROOT)/usr/include/make/SKEdefs
include $(COMMONRULES)

LCOPTS += -fPIC 

LLDOPTS = -shared 
LLDLIBS= -ldl -lngsyscall -lnglibc -lcurses


LIBEDIT=/usr/lib/libedit.a

OBJS = sksh.o        \
	   start_prog.o  \
	   print_usage.o \
	   run_cmd.o    \
	   edit_line.o

TARGETS = sksh.so

default: $(TARGETS)

sksh.so: $(OBJS)
	$(CC) $^ $(LDFLAGS) $(LLDLIBS) $(LIBEDIT) -o $@
	strip --strip-unneeded $@

exports install: default
	$(INSTALL) -p $(TARGETS) $(ROOT)/usr/bin/ske

sdk-install: sksh.so
	install -p $< $(SDK_BIN)
