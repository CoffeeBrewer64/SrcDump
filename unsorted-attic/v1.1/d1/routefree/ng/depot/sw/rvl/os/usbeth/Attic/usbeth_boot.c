d1 1
a1 1
#ident "$Id: di_boot.c,v 1.4 2006/04/04 20:26:27 craig Exp $"
d13 3
a15 6
/*
 * Program comments here
 * 
 */

#include "arm_stdint.h"
d17 1
a17 2
#include "ios.h"
#include "ioslibc.h"
a18 4
#define STACK_SIZE (256 * 1024)
const uint8_t  _initStack[STACK_SIZE];
const uint32_t _initStackSize = sizeof(_initStack);
const uint32_t _initPriority = 11;
d20 5
a24 1
int UsbInitEthRM(void);
d26 1
a26 1
#define BUS_ENABLE_MASK 0x00800000
d28 2
a29 2
void
main(int argc, char *argv[])
d31 46
a76 5
    printf ("Booting usb driver\n");
	UsbInitEthRM();
    printf ("usb driver installed\n");
    IOS_DestroyThread(0, NULL);
    exit(0);
