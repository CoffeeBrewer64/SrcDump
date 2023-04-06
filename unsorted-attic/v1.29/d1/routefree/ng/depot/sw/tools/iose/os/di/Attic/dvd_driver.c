d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.28 2006/02/21 23:45:43 craig Exp $"
d20 10
d32 2
a35 4
#include <stdlib.h>
#include <signal.h>

#include "iostypes.h"
d38 7
a45 1
#include "iosiobuf.h"
d70 1
a70 1
uint8_t                 *h3HashArray;
d87 1
a87 3
diOtherMesg_t   coverMesg = {DI_MESG_COVER, true, 0};
diOtherMesg_t   tcMesg    = {DI_MESG_TRANS_COMPLETE, true, 0};
diOtherMesg_t   errorMesg = {DI_MESG_TRANS_ERROR, true, 0};
d134 4
d156 1
a156 1
            IOS_ResourceRespond(inMesg.resourceMesg, returnStatus);
d161 2
a162 1
                     inMesg.resourceMesg->handle, inMesg.resourceMesg->handle);
d164 1
a164 1
            IOS_ResourceRespond(inMesg.resourceMesg, returnStatus);
d169 1
a169 1
            IOS_ResourceRespond(inMesg.resourceMesg, returnStatus);
d175 23
a197 21
        case DI_MESG_TRANS_COMPLETE:
            /*
             * This occurs when a transaction completes after the
             * timeout has occurred
             */
            DPRINT("Note: Transaction done message in main DVD loop.\n");
            break;

        case DI_MESG_TRANS_ERROR:
            /*
             * This occurs when a transaction has an error after the
             * timeout has occurred
             */
            DPRINT("Note: Transaction error message in main DVD loop.\n");
            break;

        case DI_MESG_COVER:     /* A cover interrupt has occurred */
            if (withinResetTime(DUMMY_COVER_INTR_TIME) == false) {
                DPRINT ("Received cover interrupt message!\n");
                if ((readDICoverReg() & DI_COVER_STATUS) == 0) {
                    coverWasClosed = true;
d199 1
d201 1
d206 1
a206 3
                char        errorBuf[256];
                sprintf (errorBuf,
                         "ERROR Unknown message type (0x%x) received.\n",
d208 1
a208 1
                diFatalError(errorBuf);
d218 1
a218 1
    IOS_ThreadExit(0);
a223 5
#ifdef EMULATOR
#define SIGNAL_OFFSET   SIGRTMIN
#else
#define SIGNAL_OFFSET   0
#endif
a239 1
    int                 h3HashPages;
d254 1
d266 2
a273 2
        driverRunning = false;
        IOS_DestroyThread(0, NULL);
d278 1
a278 4
        fprintf (stderr, "Can't create DVD In queue (err #%d)\n",
                          dvdDriverInQueue);
        driverRunning = false;
        IOS_DestroyThread(0, NULL);
a284 2
        driverRunning = false;
        IOS_DestroyThread(0, NULL);
d290 1
a290 4
        fprintf (stderr, "Can't create DVD In queue (err #%d)\n",
                          dvdDriverInQueue);
        driverRunning = false;
        IOS_DestroyThread(0, NULL);
d299 3
a301 3
    /* Register to handle Cover, Transaction Complete, and Error interrupts */
    theError =  IOS_HandleEvent(IOS_EVENT_DI_COVER + SIGNAL_OFFSET,
                                dvdDriverInQueue, (IOSMessage) &coverMesg);
d303 1
a303 1
        diFatalError("Can't register to handle DI_MESG_COVER  - exit\n");
a314 11

    if (IOS_HandleEvent(IOS_EVENT_DI_TC + SIGNAL_OFFSET, dvdDriverInQueue,
                        (IOSMessage) &tcMesg) != IOS_ERROR_OK) {
        diFatalError("Can't register to handle DI_TRANS_COMPLETE  - exit\n");
        exit(1);
    }
    if (IOS_HandleEvent(IOS_EVENT_DI_ERR + SIGNAL_OFFSET, dvdDriverInQueue,
                        (IOSMessage) &errorMesg) != IOS_ERROR_OK) {
        diFatalError("Can't register to handle DI_TRANS_ERROR  - exit\n");
        exit(1);
    }
d372 2
d375 1
d388 1
d390 1
d495 3
d499 1
