#!/bin/bash
#
# $Id: boot2.sh,v 1.1 2006/05/05 23:43:06 cnguyen Exp $
#

exit

cd ../rvl/boot/boot2
rm boot2.o
make boot2.flash
cp boot2.flash ../../../elfmerge/block1.flash

# eof
