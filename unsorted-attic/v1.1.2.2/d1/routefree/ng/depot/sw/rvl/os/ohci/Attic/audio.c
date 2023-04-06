a230 1
static u8 buf[512] __attribute__((aligned(4096)));
d234 1
a246 1
    memset(buf, 0xab, sizeof(buf));
d276 1
a276 1
    printf("audio driver exiting \n");
