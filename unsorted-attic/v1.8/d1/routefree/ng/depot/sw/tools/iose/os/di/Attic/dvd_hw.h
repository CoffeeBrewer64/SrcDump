d1 1
a1 1
#ident "$Id: dvd_hw.h,v 1.7 2005/12/30 23:28:16 craig Exp $"
d72 14
a85 9
#define DI_READ_DISK_ID                 0x70
#define DI_READ_RVL                     0x71
#define DI_SEEK_RVL                     0x72
#define DI_WAIT_FOR_COVER_CLOSE         0x79
#define DI_GET_COVER_STATUS             0x7A
#define DI_NOTIFY_RESET                 0x7E
#define DI_READ_DVD_PHYSICAL            0x80
#define DI_READ_DVD_COPYRIGHT           0x81
#define DI_READ_DVD_DISC_KEY            0x82
d173 1
a173 1
} DVDLowDriverSer;
