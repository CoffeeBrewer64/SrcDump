a0 28

#include <types.h>
#include <iop.h>
#include <ios.h>
#include <iosc.h>
#include <ioslibc.h>


#define WFS_RM_STACK_SIZE  512
#define WFS_RM_PRIORITY    9

const u8 _initStack[WFS_RM_STACK_SIZE];
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = WFS_RM_PRIORITY;


#define BUFFER_SIZE     (32*1024)
u8 _usb_wfs_buffer[BUFFER_SIZE] __attribute__ ((aligned(64)));


int main(int argc, char **argv)
{

    memset(_usb_wfs_buffer, 0x69, BUFFER_SIZE);

    return 0;
}

