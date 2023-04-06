d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.32 2006/03/01 19:45:55 craig Exp $"
a531 1
    diClearErrorStatus();
d610 1
a623 1
        DPRINT("### startTimedTransfer returned\n");
d849 1
a849 1
                DPRINT ("(handleDiCommand) Current command timed out\n");
a874 1
                debugPoint();
a904 1
            DPRINT("(handleDiCommand): Before FlushMem\n");  
d929 1
a929 1
        DPRINT("Note! not reading hash and encrypted state\n");
a931 1
    debugPoint();
