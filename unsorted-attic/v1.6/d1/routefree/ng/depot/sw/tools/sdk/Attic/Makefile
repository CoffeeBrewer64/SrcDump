
DEVKIT=./DEVKIT
TEMP=./TEMP
NGTREE=../../

ifeq ($(RVL_MEM), 128)
SDK_IMAGE = iop_sdk_128.tgz
else
ifeq ($(RVL_MEM), 64)
SDK_IMAGE = iop_sdk_64.tgz
endif
endif

LDIRT = $(SDK_IMAGE)

default headers exports runtests:

install: 
#	make -C $(NGTREE) headers
#	make -C $(NGTREE) clobber
#	make -C $(NGTREE) exports
#	make -C $(NGTREE) install
	#
	# extract required files from ROOT
	#
	-rm -rf $(DEVKIT)
	mkdir -p $(DEVKIT)
	cat rootfiles | (cd $(ROOT); tar cf - -T -) | (cd $(DEVKIT); tar xf -)
	cp install.sh $(DEVKIT)
	#
	# tar up the resulting tree
	#
	-rm -f $(SDK_IMAGE)
	(cd $(DEVKIT); tar czf - .) > $(SDK_IMAGE)
	-rm -rf $(DEVKIT)
	-rm -rf $(TEMP)

clean clobber:
	-rm -f $(SDK_IMAGE)
