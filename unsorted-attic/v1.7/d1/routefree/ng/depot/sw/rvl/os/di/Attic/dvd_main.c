d1 1
a1 1
#ident "$Id: dvd_main.c,v 1.6 2006/02/28 04:01:47 craig Exp $"
d28 1
a28 1
#define STACK_SIZE (1024 * 1024)
d94 2
d107 1
a107 1
        printf (" 0x%2x", transBuf[i]);
a109 3
    printf ("Holding in a tight loop\n");
    for (int i = 0; i < 1000000; i++) {
    }
