d1 1
a1 1
#ident "$Id: test_rvl_image.c,v 1.2 2006/02/11 02:33:12 craig Exp $"
d18 7
d26 1
d47 1
a47 1
efseeko64 (FILE *stream, off_t offset, int whence)
d49 1
a49 1
    if (fseeko64(stream, offset, whence) == -1) {
d77 1
a77 1
    if ( (imageFile = fopen64(argv[1], "r")) == NULL) {
d92 2
a93 2
    printf ("Update TOC: 0x%x; Game TOC: 0x%x\n", updateTOCOff << 2,
             gameTOCOff << 2);
d101 1
a101 1
    printf ("Number of update partitions: %u\n", numUpdates);
d121 1
a121 1
    printf ("Number of game partitions: %u\n", numGames);
d178 2
a179 1
    printf ("\tUpdate partition starts at: 0x%x\n", updatePartitionAddr << 2);
d196 1
a196 1
    printf ("\tTMD size: %u\n", tmdSize);
d214 2
a215 1
    printf ("\tNum certificates: %u; Array start addr: 0x%x\n",
d224 2
a225 1
        printf ("\t\tCertificate #%d Address = 0x%x\n", i, certAddr << 2);
d238 1
a238 1
    printf ("\tImage: Address 0x%x\n", imageAddr << 2);
d258 2
a259 1
    printf ("\tGame partition starts at: 0x%x\n", gamePartitionAddr << 2);
d276 1
a276 1
    printf ("\tTMD size: %u\n", tmdSize);
d294 2
a295 2
    printf ("\tNum certificates: %u; Array start addr: 0x%x\n",
             numCerts, certArrayAddr << 2);
d303 2
a304 1
        printf ("\t\tCertificate #%d Address = 0x%x\n", i, certAddr << 2);
d319 1
a319 1
    printf ("\tImage: Address 0x%x\n", cryptAddr << 2);
d342 1
a342 1
    efseeko64(imageFile, wordOffset << 2, SEEK_SET);
d352 1
a352 1
            printf ("Read from addr 0x%x failed\n", wordOffset << 2);
d362 2
a363 1
            printf ("Error: scratch is too small for request of %d bytes\n",
d368 1
a368 1
            printf ("Read from addr 0x%x failed\n", wordOffset << 2);
