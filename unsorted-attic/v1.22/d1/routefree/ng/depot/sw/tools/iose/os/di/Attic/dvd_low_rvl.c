d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.21 2006/03/20 23:02:10 craig Exp $"
d111 10
d275 4
a285 1
    uint8_t             readBuffer[BYTES_PER_BLOCK];
d467 4
d583 1
a583 1
     * Handle disk reads that don't start on a block boundary
a584 1

a655 1
    DVDDiskInfo         diskInfo __attribute__((aligned(32)));
a701 2
    globalTOC_t         globalTOC       __attribute__((aligned(32)));
    gameTOC_t           gameTOC         __attribute__((aligned(32)));
a768 1
    gamePartition_t     gamePartition __attribute__((aligned(32)));
