d1 1
a1 1
#ident "$Id: rvl_image.c,v 1.12 2006/03/28 04:04:40 craig Exp $"
a821 6
        /*
         * ASSUMES that there is only one content structure in the TMD.
         */
        printf ("Warning: not putting H4 into TMD\n");
        // memcpy(gamePart->tmd->contents[0].hash, h4HashArray, SHA1_DIGESTSIZE);

d846 5
a850 2
                            data.
 *             h4Hash: an array of at least SHA1_DIGESTSIZE. 
