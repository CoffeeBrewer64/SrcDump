d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.9 2005/12/31 03:28:14 craig Exp $"
d35 1
d40 10
a49 1
#define         DVD_PATH                "/dev/dvd"
d62 14
a75 1
extern void dvd_high_emu(uint32_t junk);
d85 1
d88 1
a88 1
    extern void         dvd_high();
d95 7
d104 12
d126 1
a127 1
    initDvdDriver(MAX_H3_HASH_SIZE);
d133 1
d140 22
a161 1
        switch (inMesg.mesgType) {
d188 2
d197 2
d210 1
d277 1
a277 2
                                dvdDriverInQueue,
                                DI_MESG_COVER);
d293 1
a293 1
                        DI_MESG_TRANS_COMPLETE) != IOS_ERROR_OK) {
d299 1
a299 1
                        DI_MESG_TRANS_ERROR) != IOS_ERROR_OK) {
d308 58
d372 43
