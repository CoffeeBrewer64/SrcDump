#!/bin/bash

#
# Script to install the NC devkit
#
# Must be executed from the directory in which the devkit image
# has been unpacked or installed.
#
# Note that cygwin must already be installed before running this script.
#

#
# Install $ROOT files
#
if [ "x" == "x$ROOT" ]; then
	echo ROOT environment variable is not set.
	exit 1
fi

if [ ! -d $ROOT ]; then
	echo Directory $ROOT does not exist:  please create it before running this script.
	exit 1
fi

tar cf - usr | (cd $ROOT; tar xf -)

