a0 35
#!/bin/bash

#
# Script to install the IOS SRC SDK
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
	echo ROOT environment variable is not set - must be set to continue.
	exit 1
fi

if [ "x" == "x$RVL_MEM" ]; then
	echo RVL_MEM environment variable is not set - need to be either 128 or 64.
	exit 1
fi

if [ ! -d $ROOT ]; then
	echo Directory $ROOT does not exist:  please create it before running this script.
	exit 1
fi

if [ "x" == "x$REVOLUTION_SDK_ROOT" ]; then
	echo WARNING: REVOLUTION_SDK_ROOT environment variable is not set!
fi

tar cf - usr | (cd $ROOT; tar xf -)

