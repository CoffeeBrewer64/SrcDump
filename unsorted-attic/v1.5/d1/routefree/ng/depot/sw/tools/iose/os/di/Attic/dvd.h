d1 1
a1 1
#ident "$Id: dvd.h,v 1.4 2005/12/30 23:28:16 craig Exp $"
d25 1
d35 9
a43 5
#define DI_MESG_TIMEOUT                 1
#define DI_MESG_TRANS_COMPLETE          2
#define DI_MESG_TRANS_ERROR             3
#define DI_MESG_COMMAND                 4
#define DI_MESG_COVER                   5
d45 3
a47 2
typedef struct diInQueueMesg {
    uint8_t     mesgType;       /* DI_MESG_TIMEOUT, DI_MESG_TRANS_COMPLETE... */
d53 5
a57 1
    uint8_t     padding[2];
a59 5
typedef union diIOSMessage {
    IOSMessage          mesg;
    diInQueueMesg_t     inMesg;
} diIOSMessage_t;

