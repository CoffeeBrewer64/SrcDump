include $(ROOT)/usr/include/make/NGdefs

PROGS= net.elf

TARGETS = $(PROGS)

default: $(TARGETS)

include $(COMMONRULES)

LLDLIBS = -lsys -lioslibc -liossyscall 
LDIRT += *.bin *.elf

CINC = -I../include -I../../../../include -I../../../../../../../common/include 
CFLAGS += $(CINC)

#CFLAGS += -DDEBUG
CFLAGS += -DERR_DEBUG -DIOP_OS -DIP_INET6 -DDEBUG -DVERBOSE
#FIXME - see if you can get change code so that no-struct-aliasing isn't needed
CFLAGS += -O2 -fno-strict-aliasing

SRCS        = IP.c IP4.c IPArp.c IPIcmp.c IPRoute.c IPFrag.c IFFifo.c IFRing.c \
              IPZero.c IPOpt.c IPIgmp.c IPMisc.c IP6.c IP6Icmp.c IP6Zero.c \
			  IP6Mld.c IP6Frag.c IPUdp.c IPTcpTimer.c IPTcpTimeWait.c IPTcp.c \
			  IPTcpOutput.c IPTcpUser.c IPSocket.c IPDns.c IPDhcp.c IPPPP.c \
			  IPPPPoE.c IPLcp.c IPIpcp.c IPPap.c IPChap.c IPHdlc.c IPInterface.c \
			  IPEther.c iop_os.c iop_alarm.c iop_mutex.c iop_libc.c iop_sockrm.c \
			  iop_mem.c iop_ifrm.c
			 
APP_LDFLAGS =  $(LDLIBS) $(LDFLAGS) -T$(ROOT)/usr/lib/rvl/ddr.link \
               -Ttext=$(MK_APPS_START)

net.elf: $(CRT0) \
              IP.o IP4.o IPArp.o IPIcmp.o IPRoute.o IPFrag.o IFFifo.o IFRing.o \
              IPZero.o IPOpt.o IPIgmp.o IPMisc.o IP6.o IP6Icmp.o IP6Zero.o \
			  IP6Mld.o IP6Frag.o IPUdp.o IPTcpTimer.o IPTcpTimeWait.o IPTcp.o \
			  IPTcpOutput.o IPTcpUser.o IPSocket.o IPDns.o IPDhcp.o IPPPP.o \
			  IPPPPoE.o IPLcp.o IPIpcp.o IPPap.o IPChap.o IPHdlc.o IPInterface.o \
			  IPEther.o iop_os.o iop_alarm.o iop_mutex.o iop_libc.o iop_sockrm.o \
			  iop_mem.o iop_ifrm.c
			  
	$(CC) $(CFLAGS) -o $@ $^ $(APP_LDFLAGS)

