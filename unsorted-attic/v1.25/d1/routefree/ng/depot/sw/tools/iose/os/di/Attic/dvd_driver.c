d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.24 2006/02/16 00:25:31 craig Exp $"
d199 5
d288 1
a288 1
    theError =  IOS_HandleEvent(IOS_EVENT_DI_COVER + SIGRTMIN,
d304 1
a304 1
    if (IOS_HandleEvent(IOS_EVENT_DI_TC + SIGRTMIN, dvdDriverInQueue,
d309 1
a309 1
    if (IOS_HandleEvent(IOS_EVENT_DI_ERR + SIGRTMIN, dvdDriverInQueue,
