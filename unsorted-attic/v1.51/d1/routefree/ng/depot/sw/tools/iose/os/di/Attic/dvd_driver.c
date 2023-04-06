d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.50 2006/03/05 04:10:40 craig Exp $"
d76 3
a78 2
static bool                     driverRunning = false;
void                            initDvdDriver(const uint32_t h3HashSize);
d125 1
a125 1
    initDvdDriver(MAX_H3_HASH_SIZE);
d153 4
d173 4
d227 1
a227 1
                printf ("ERROR Unknown message type (0x%x) received.\n",
d245 26
d276 1
a276 1
 *         Creates the input and output queues.
d278 1
a278 2
 *         Registers to handle the Transaction Complete, Error,
 *         and Cover Interrupts.
a279 1
 *
d285 1
a285 1
initDvdDriver(const uint32_t h3HashSize)
d287 1
a287 1
    IOSMessage          *dvdDriverInBuf, *dvdDriverOutBuf, *dvdDriverSleepBuf;
a301 10
    initDvdMemAlloc();

    /* Code currently doesn't use IOB pools.  Uncomment these
     * lines if it needs them
     */
    /*
    if (IOS_AccessIobPool(POOL_DEFAULT) != IOS_ERROR_OK) {
        diFatalError("Can't access IOB pool\n");
    }
    */
a304 12
    /* Create In message queue */
    dvdDriverInBuf = dvdMemAlloc(sizeof(IOSMessage) * DVD_IN_QUEUE_LEN);
    if (dvdDriverInBuf == NULL) {
        diFatalError("Can't allocate space for dvd in queue - exit\n");
    }
    dvdDriverInQueue = IOS_CreateMessageQueue(dvdDriverInBuf, DVD_IN_QUEUE_LEN,
                                              ALL_PIDS);
    if (dvdDriverInQueue < 0) {
        diFatalError ("Can't create DVD In queue");
    }
    DPRINT2("(InitDVDDriver) dvdDriverInQueue is: %d\n", dvdDriverInQueue);

d306 1
a332 1
        exit(1);
d351 1
a351 1
        exit(1);
d359 1
a359 1
} // initDvdDriver
d378 1
a378 1
    printf ("Returning ERROR_MAX\n");
d556 1
a556 1
    printf("Fatal error in DI driver: %s\nExiting\n", mesg);
