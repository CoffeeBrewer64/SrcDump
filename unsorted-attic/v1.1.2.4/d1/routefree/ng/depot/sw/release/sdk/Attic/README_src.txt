d68 1
a68 1
                          * This image is for old ATI diag (3 blocks) boot.
d70 1
a70 1
                          * This image is for old Nintendo diag boot.
d73 1
d76 1
d117 6
a122 19
   - Unpack the SDK image (unzip) onto a temporary directory 
     For example:
        $ cp IOS_SRC_SDK_128_x.zip /tmp
        $ cd tmp; unzip IOS_SRC_SDK_128_x.zip
   - Create the installed directory and set the ROOT variable.
     NOTES:
       * Make sure that the ROOT path contains the case-sensitive pattern "RVL".
       * Make sure that the ROOT path has the Linux/Cygwin format (i.e. /home/x)
     For example (using bash):
        $ mkdir -p /home/test/IOS_SRC_SDK/RVL_128
        $ export ROOT=/home/test/IOS_SRC_SDK/RVL_128
   - Set the environment variable RVL_MEM to 128 (for 128MB) and 64 (for 64MB).
     For example (using bash):
        $ export RVL_MEM=128
   - Unset the environment variable REVOLUTION_SDK_ROOT 
     For example (using bash):
        $ unset REVOLUTION_SDK_ROOT
   - Run the install_src.sh script to install the image to $ROOT
        $ ./install_src.sh
