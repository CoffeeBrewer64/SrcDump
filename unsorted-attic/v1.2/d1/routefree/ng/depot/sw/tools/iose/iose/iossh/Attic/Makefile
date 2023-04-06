include $(ROOT)/usr/include/make/commondefs
include $(ROOT)/usr/include/make/IOSEdefs
include $(COMMONRULES)

LCOPTS += -fPIC 
LCINCS += -I/usr/local/libedit/include
LLDOPTS = -shared 
LLDLIBS= -ldl -liossyscall -lioslibc -lcurses


LIBEDIT=/usr/local/libedit/lib/libedit.a

OBJS = iossh.o        \
	   start_prog.o  \
	   print_usage.o \
	   run_cmd.o    \
	   edit_line.o

TARGETS = iossh.so

default: $(TARGETS)

iossh.so: $(OBJS)
	$(CC) $^ $(LDFLAGS) $(LLDLIBS) $(LIBEDIT) -o $@
	strip --strip-unneeded $@

exports install: default
	$(INSTALL) -p $(TARGETS) $(ROOT)/usr/bin/iose

sdk-install: iossh.so
	install -p $< $(SDK_BIN)
