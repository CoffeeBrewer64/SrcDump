d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.55 2006/03/06 04:00:51 craig Exp $"
a630 4
#ifndef WORK_AROUND
    /* Enable control over PI_IO */
    AIPPROT_SET_ENAHBIOPI(reg, 1);
#endif
d633 1
