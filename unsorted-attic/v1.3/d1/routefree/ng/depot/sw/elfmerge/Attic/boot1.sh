cd ../rvl/boot/boot1
rm boot1.o
rm boot1.flash
make boot1.flash
cp boot1.flash ../../../elfmerge/block0.flash
