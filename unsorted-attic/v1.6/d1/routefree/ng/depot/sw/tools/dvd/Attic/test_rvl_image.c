d1 1
a1 1
#ident "$Id: test_rvl_image.c,v 1.5 2006/02/16 21:41:17 craig Exp $"
d42 2
a43 1
void dumpGamePartition(const uint32_t gamePartitionAddr);
d76 2
d81 2
a82 2
    if (argc != 2) {
        printf ("Usage: %s rvl_image\n", argv[0]);
d85 9
d97 1
a97 1
    if ( (imageFile = fopen(argv[1], "r")) == NULL) {
d152 1
a152 1
        dumpGamePartition(ntohl((uint32_t) gamePartArray[i]));
d268 2
a269 1
dumpGamePartition(const uint32_t gamePartitionAddr)
d278 1
d361 20
