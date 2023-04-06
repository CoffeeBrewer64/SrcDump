d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.51 2006/03/05 06:11:22 craig Exp $"
d268 5
a334 4
    if (IOS_RegisterResourceManager(DVD_PATH, dvdDriverInQueue)
                                    != IOS_ERROR_OK) {
        diFatalError("Can't register DVD resource mananger - exit\n");
    }
