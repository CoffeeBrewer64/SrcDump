d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.37 2006/03/01 19:45:55 craig Exp $"
d114 1
d151 1
a151 1
        DPRINT ("(dvd_driver) Doing IOS_ReceiveMessage\n");
d187 1
a187 1
            DPRINT("(dvd_driver) Receiving MESG_INTR\n");
d189 2
d196 1
a196 1
                DPRINT("Note: Transaction done message in main DVD loop.\n");
d205 1
a205 1
                DPRINT("Note: Transaction error message in main DVD loop.\n");
d209 1
d216 3
d624 1
d627 1
d649 1
d654 1
d657 1
d662 1
