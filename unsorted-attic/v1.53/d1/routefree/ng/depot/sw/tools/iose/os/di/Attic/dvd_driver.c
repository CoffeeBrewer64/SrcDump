d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.52 2006/03/06 01:33:33 craig Exp $"
d251 7
a257 1
    IOSMessage          *dvdDriverInBuf;
d262 2
d276 24
d303 1
d306 6
d318 1
a318 4
 * ACTION: Initializes the DI specific memory allocater
 *         Allocates memory space for the H3 hashes.
 *         Creates the output and sleep queues.
 *         Registers Resource Manager.
a327 1
    IOSMessage          *dvdDriverOutBuf, *dvdDriverSleepBuf;
d330 1
a330 4
#ifdef RVL
    enableDIRegisterAccess();
    checkDIRegisterAccess();
#endif
a338 29

    currentCommandNum = 0;

    /* Create Out message queue */
    // FIXME - dvdDriverOutQueue can be removed - used for emulation only
    dvdDriverOutBuf = dvdMemAlloc(sizeof(IOSMessage) * DVD_OUT_QUEUE_LEN);
    if (dvdDriverOutBuf == NULL) {
        diFatalError("Can't allocate space for dvd OUT queue - exit\n");
    }
    dvdDriverOutQueue = IOS_CreateMessageQueue(dvdDriverOutBuf,
                                               DVD_OUT_QUEUE_LEN,
                                               ALL_PIDS);
    if (dvdDriverOutQueue < 0) {
        diFatalError ("Can't create DVD Out queue\n");
    }

    /* Create message queue for sleeping */
    dvdDriverSleepBuf = dvdMemAlloc(sizeof(IOSMessage) * DVD_SLEEP_QUEUE_LEN);
    if (dvdDriverSleepBuf == NULL) {
        diFatalError("Can't allocate space for dvd OUT queue - exit\n");
    }
    dvdDriverSleepQueue = IOS_CreateMessageQueue(dvdDriverSleepBuf,
                                                 DVD_SLEEP_QUEUE_LEN,
                                                 ALL_PIDS);
    if (dvdDriverOutQueue < 0) {
        diFatalError ("Can't create DVD Out queue\n");
    }


d355 1
a355 1
        /* Never reached */
a356 4
    resetDriverState();         // Code is in dvd_low_rvl.c
    DPRINT("resetDriverState: done \n");

    // DPRINT("(initDvdDriver) Doing ClearAndEnableDIIntr\n");
a357 1
    // DPRINT("(initDvdDriver) ClearAndEnableDIIntr done \n");
