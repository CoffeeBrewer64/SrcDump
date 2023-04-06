d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.47 2006/03/08 20:54:01 craig Exp $"
d58 1
a58 1
void                    doResetCommand();
d594 1
a594 1
        doResetCommand();
d1123 3
a1125 1
 * to a cover status changed interrupt and the cover is now closed.
d1134 1
a1134 4
    if ((readDICoverReg() & DI_COVER_STATUS) == 0) {
        DPRINT ("(doWaitForCoverClose) Cover is already closed - returning\n");
        return;
    }
a1151 2
                    // Do resetDriverState() here?
                    done = true;
d1158 3
d1164 4
d1169 1
a1169 1
doResetCommand()
d1175 16
d1200 6
d1211 1
a1211 1
    time = RESET_HOLD_TIME_MSEC;
d1240 7
