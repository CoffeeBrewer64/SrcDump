d1 1
a1 1
#ident "$Id$"
d20 1
a20 2
enum dvdDisk {dvdDiskTypeError = 0, dvdNoDisk, dvdVideo,
              dvdGcDisk, dvdRvlDisk};
d23 9
a31 5
enum dvdStatus {dvdStatusError = 0,
                dvdStatusUnknown,
                dvdStatusCoverOpen,
                dvdStatusNoDisk,
                dvdStatusTypeKnown};
d34 11
a44 11
typedef struct dvdState {
    dvdStatus_t         dvdStatus;
    /* Only valid when dvdStatus is dvdStatusTypeKnown */
    dvdDisk_t           dvdDisk;
} dvdState_t;


typedef struct dvdFd {
    IOSCid              fd;
    uint32_t            currentPosition;
} dvdFd_t;
