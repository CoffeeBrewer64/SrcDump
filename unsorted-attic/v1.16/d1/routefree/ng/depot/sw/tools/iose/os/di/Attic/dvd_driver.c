d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.15 2006/01/27 03:34:19 craig Exp $"
d160 1
a160 1
            printf ("Open returns: %d\n", sendError);
d220 7
d344 1
d370 2
a371 1
    uint32_t            ioctlReturn, commandResult;
a373 1

a435 2
        // FIXME - Move this to the Makefile
#define DEVELOPER
d437 4
