d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.8 2005/12/30 23:28:16 craig Exp $"
d64 1
d73 2
a74 1
    highThreadId = IOS_CreateThread(dvd_high_emu, NULL, highStack, HIGH_STACK_SIZE, 50);
d197 1
a197 1
#ifndef EMULATOR
d203 1
a203 1
#endif
