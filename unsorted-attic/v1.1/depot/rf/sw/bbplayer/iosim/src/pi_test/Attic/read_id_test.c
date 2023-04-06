a2 1
#define NUM_FLASH_DEVS 4
d5 1
a5 1
int piReadIdTest(const u16 expectedIds[])
d8 5
a12 1
    u32 ret;
d19 2
a20 2
    for(i=0;i<NUM_FLASH_DEVS;i++){
        IO_WRITE(PI_FLASH_CTRL,(PI_READ_ID_BASE|PI_CTRL_DEV_SHIFT(i)));
d28 1
