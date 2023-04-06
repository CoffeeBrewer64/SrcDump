#!/bin/bash
#
# $Id: boot2.sh,v 1.1 2006/05/05 21:46:55 jlivesey Exp $
#

exit

cd ../rvl/boot/boot2
rm boot2.o
make boot2.flash
cp boot2.flash ../../../elfmerge/block1.flash

# eof
