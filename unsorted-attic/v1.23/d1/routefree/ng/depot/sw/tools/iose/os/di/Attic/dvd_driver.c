d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.22 2006/02/07 04:39:08 horti Exp $"
d85 1
d87 2
d104 1
d106 3
a108 4
    /*
     * TODO - Remove this line once we can calculate where
     * the encrypted area really begins.
     */
a109 2
    diskInfo.dataWordOffset = (96 * 1024) / 4;
    driverRunning = true;
a115 1
    resetDriverState();
d208 1
d220 4
a223 1
    /* FIXME - uncomment this after we send code to Nintendo */
a229 2
    dvdState.currentHashRead = false;

d309 2
a310 1
}
a520 1

