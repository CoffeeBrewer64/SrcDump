d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.63 2006/03/21 02:26:02 wheeler Exp $"
d148 1
a148 1
        DPRINT2 ("(dvd_driver [after ReceiveMessage]) Status reg val is: 0x%x\n",
d154 1
a158 1
            DPRINT("(dvd_driver) Receiving OPEN request\n");
d160 2
a261 1

d330 1
a330 1
    DPRINT("(initDvdDriverStage2) enter");
d343 1
a343 1
    DPRINT("Done calling IOS_HandleEvent for IOS_EVENT_DI\n");
d498 1
a498 1
            printf("(DiIoctl) Driver calling clearDriveErrorInterupt on own\n");
