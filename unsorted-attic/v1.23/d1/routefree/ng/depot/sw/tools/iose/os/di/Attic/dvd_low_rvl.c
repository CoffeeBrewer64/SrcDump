d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.22 2006/03/21 01:15:36 craig Exp $"
d105 1
a105 1
// #define DEBUG   1
d107 1
a107 1
#ifdef DEBUG_1
a306 7
#ifdef DEBUG
    printf ("(DoBlockRead) RAW:\n\t");
    for (int i = 0; i < 16; i++) {
        printf ("0x%x ", readBuffer[i]);
    }
    printf ("\n");
#endif
d316 1
a316 1
#ifdef DEBUG
d327 1
a327 1
#ifdef DEBUG
d351 5
d360 1
a360 1
#ifdef DEBUG
d394 1
a394 1
            printf ("H0 Hashes failed to verify\n");
d397 3
d407 1
a407 1
            printf ("H1 Hashes failed to verify\n");
d410 3
d417 1
a417 1
            printf ("H2 Hashes failed to verify\n");
d420 3
d857 1
a857 1
    printf ("(NonConformtingDiskRead) Reading %u bytes from byte addr 0x%x\n",
