d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.61 2006/03/18 05:59:36 craig Exp $"
d270 1
a270 2
    dvdDriverInQueue = IOS_CreateMessageQueue(dvdDriverInBuf, DVD_IN_QUEUE_LEN,
                                              ALL_PIDS);
d282 1
a282 2
                                               DVD_OUT_QUEUE_LEN,
                                               ALL_PIDS);
d293 1
a293 2
                                                 DVD_SLEEP_QUEUE_LEN,
                                                 ALL_PIDS);
