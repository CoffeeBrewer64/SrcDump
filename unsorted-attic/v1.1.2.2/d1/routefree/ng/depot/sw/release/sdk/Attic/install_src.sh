d6 1
a6 1
# Must be executed from the directory in which the SDK image
a14 2
echo ""
echo "Checking environment variables: ROOT, RVL_MEM, REVOLUTION_SDK_ROOT ..."
d16 1
a16 2
	echo "Please set environment variable 'ROOT' to continue."
	echo "ROOT path must contain pattern 'RVL' (i.e. /home/test/IOS_SRC_SDK/RVL_128/)."
d20 2
a21 6
if [[ "$ROOT" =~ "RVL" ]]; then
	echo "ROOT=$ROOT -> OK"
else
	echo "ROOT=$ROOT"
	echo "ROOT path must contain pattern 'RVL' (i.e. /home/test/IOS_SRC_SDK/RVL_128/)."
	echo "Please change your environment variable ROOT to continue."
d26 1
a26 7
	echo "Directory $ROOT does not exist."
    echo "Please create $ROOT to continue."
	exit 1
fi

if [ "x" == "x$RVL_MEM" ]; then
	echo "Please set environment variable 'RVL_MEM' to either 128 or 64 to continue."
d30 2
a31 11
if [ "128" == "$RVL_MEM" ] || [ "64" == "$RVL_MEM" ]; then
    echo "RVL_MEM=$RVL_MEM -> OK"
else
    echo "RVL_MEM=$RVL_MEM"
	echo "Please set environment variable 'RVL_MEM' to either 128 or 64 to continue."
	exit 1
fi

if [ "x" != "x$REVOLUTION_SDK_ROOT" ]; then
	echo "Please unset environment variable 'REVOLUTION_SDK_ROOT' to continue."
	exit 1
a33 6
echo ""
echo "Parameters:"
echo "   ROOT=$ROOT"
echo "   RVL_MEM=$RVL_MEM"
echo ""
echo "Installing image to $ROOT ..."
