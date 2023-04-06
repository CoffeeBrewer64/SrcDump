d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.10 2006/01/10 20:40:59 craig Exp $"
d51 6
a56 6
dvdState_t      dvdState;
IOSMessage      dvdDriverInQueue, dvdDriverOutQueue;
diCommand_t     interfaceDiCommand;
uint8_t         *h3HashArray;
uint32_t        dvdCoverStatus;
uint8_t         currentCommandNum;
a196 1
static void initDiMesgPool(void);
a208 1
    initDiMesgPool();
d333 2
d339 1
a339 1
    static uint32_t     lastErrorVal;
d355 1
a355 1
    default:
d357 21
a377 2
        lastErrorVal = handleDiCommand(command);
        * (uint32_t *) ioctlMesg->outPtr = lastErrorVal;
d394 1
d435 1
