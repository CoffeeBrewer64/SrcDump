# This Makefile does not use the common infrastructure
# because the programs in this directory can be used as 
# standalone examples and this Makefile can be used as a
# template to build examples

#Paths
SDK_ROOT?=/opt/iop-sdk/
BINDIR=$(ROOT)/usr/bin/ske
LIBDIR= $(ROOT)/usr/lib/ske

#Build tools and flags
CC=gcc
CDEFS=-D_LANGUAGE_C 
CINC=-I$(ROOT)/usr/include/ske 
CFLAGS=-c -fPIC $(CINC) $(CDEFS) -Wall -g -O0

RPATH=$(SDK_ROOT)/usr/lib/ske
LIBPATH=-L$(ROOT)/usr/lib/ske -L/usr/local/usb/lib
LIBS=-lngsyscall -lnglibc -lusb
LIBEDIT=/usr/lib/libedit.a
LDFLAGS= -shared -Wl,-export-dynamic --Wl,-rpath=$(RPATH) $(LIBPATH) $(LIBS) 

progs=thread_tst.so  \
	  msg.so \
	  jam.so \
	  block.so \
	  mem.so \
	  event.so \
	  multi_event.so  \
	  timer.so   \
	  timer1.so \
	  timer2.so \
	  timer3.so \
	  timer4.so \
	  periodic1.so \
	  usb_cdrvr.so \
	  usb_mouse.so \
	  usb_getdescr.so 

all:$(progs)


#Generic rules
%.so: %.o $(LIBDIR)/libngsyscall.a $(LIBDIR)/libnglibc.a
	$(CC) $^ $(LDFLAGS)  -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean clobber install sdk-install

clean:
	rm -f *.o *.so
clobber:
	rm -f *.o  *.so $(BINDIR)/*.so
	
exports install: $(progs)
	install -p $(progs) $(BINDIR)

headers:

sdk-install: 
