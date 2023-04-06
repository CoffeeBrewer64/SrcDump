#include "pi_util.h"


/* for now, assumes all devices use only 2B for id */
int piReadId(int intEnable,int numDevices,const u16 expectedIds[])
{
    int i;
    u32 ret,flashCmd;

    flashCmd = PI_READ_ID_BASE;
    if(intEnable)
        flashCmd |= PI_AES_CTRL_INTR;

    /*
     * Read device IDs
     */ 
    IO_WRITE(PI_DEV_ADDR,0);
    /* Read ID's of all flash devices */
    for(i=0;i<numDevices;i++){
        IO_WRITE(PI_FLASH_CTRL,(flashCmd | PI_CTRL_DEV_SHIFT(i)));
        POLL_CTRL_BUSY;
        ret = IO_READ(PI_BUF_0);
        if( (u16)((ret>>16)&0xffff) != expectedIds[i] )
            return FAIL;
    }
    return PASS;
}

