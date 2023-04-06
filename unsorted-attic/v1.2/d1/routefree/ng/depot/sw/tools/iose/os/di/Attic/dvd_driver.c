d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.1 2005/11/16 02:50:50 craig Exp $"
d25 3
a28 1
#include "dvd_struct.h"
a29 1
#define         DVD_MESG_LEN            8
d33 4
d38 2
a39 2
IOSMessageQueueId           dvdMesgQueue;
dvdState_t                  dvdState = {dvdStatusUnknown, dvdDiskTypeError};
d44 5
a48 9
    IOSMessage                  dvdMessageBuf[DVD_MESG_LEN];
    IOSRmReq                    *dvdMessage;
    IOSError                    sendError;

    dvdMesgQueue = IOS_CreateMessageQueue(dvdMessageBuf,
                                          DVD_MESG_LEN, ALL_PIDS);
    if (dvdMesgQueue < 0) {
        fprintf (stderr, "Can't create DVD message queue (err #%d)\n",
                          dvdMesgQueue);
d50 1
d52 3
a54 5
    if (IOS_RegisterResourceManager(DVD_PATH, dvdMesgQueue) != IOS_ERROR_OK) {
        fprintf (stderr, "Can't register DVD resource mananger - exit\n");
        exit(1);
    }
    /* FIXME - Set event handlers here */
d57 14
a70 16
        IOS_ReceiveMessage(dvdMesgQueue, (IOSMessage *) dvdMessage,
                           IOS_MESSAGE_NOBLOCK);
        switch (dvdMessage->type) {

        case IOS_OPEN:
            if (newDvdFd(dvdMessage->fd) == false) {
                dvdMessage->reply->status = IOS_ERROR_NOMEM;
                sendError = IOS_SendMessage(dvdMessage->replyQId,
                                            (IOSMessage) &(dvdMessage->reply),
                                            IOS_MESSAGE_BLOCK);
                if (sendError != IOS_ERROR_OK) {
                    /* FIXME */
                    printf ("Fill in code here #1\n");
                    exit(1);
                }
            }
d73 2
a74 1
        case IOS_CLOSE:
d77 1
a77 1
        case IOS_READ:
d79 4
d84 25
a108 11
        case IOS_WRITE:
            dvdMessage->reply->status = IOS_ERROR_INVALID;
            sendError = IOS_SendMessage(dvdMessage->replyQId,
                                        (IOSMessage) &(dvdMessage->reply),
                                        IOS_MESSAGE_BLOCK);
            if (sendError != IOS_ERROR_OK) {
                /* FIXME */
                printf ("Fill in code here #1\n");
                exit(1);
            }
            break;
d110 14
a123 2
        case IOS_SEEK:
            break;
d125 15
a139 2
        case IOS_STAT:
            break;
d141 4
a144 3
        case IOS_IOCTL:
            break;
        }
d146 9
