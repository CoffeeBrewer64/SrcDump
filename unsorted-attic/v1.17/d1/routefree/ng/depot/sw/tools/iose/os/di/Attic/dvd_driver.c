d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.16 2006/01/28 00:30:09 craig Exp $"
d233 9
a241 1
 * Input: h3HashSize in *bytes*
a257 1

d267 1
a267 1
        fprintf (stderr, "Error: can't allocate space for H3 hashes - exit\n");
d276 1
a276 1
        fprintf(stderr, "Can't allocate space for dvd in queue - exit\n");
d292 1
a292 1
        fprintf(stderr, "Can't allocate space for dvd OUT queue - exit\n");
d308 1
a308 1
        fprintf (stderr, "Can't register DVD resource mananger - exit\n");
d316 1
a316 1
        fprintf (stderr, "Can't register to handle DI_MESG_COVER  - exit\n");
d318 1
a318 1
            fprintf (stderr, "Invalid event or queue\n");
d321 1
a321 1
            fprintf (stderr, "Permission denied.\n");
d324 1
a324 1
            fprintf (stderr, "Unknown error\n");
d331 1
a331 2
        fprintf (stderr,
                 "Can't register to handle DI_TRANS_COMPLETE  - exit\n");
d336 1
a336 2
        fprintf (stderr,
                 "Can't register to handle DI_TRANS_ERROR  - exit\n");
