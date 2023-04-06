d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.54 2006/03/14 06:36:20 craig Exp $"
d533 1
d540 8
d551 11
d1120 3
d1192 1
d1211 1
a1211 1
    commandResult = handleDiCommand(&diCommand, NULL);
a1324 2
    resetDriverState();

d1338 1
a1339 1
    diClearCoverIntr();
