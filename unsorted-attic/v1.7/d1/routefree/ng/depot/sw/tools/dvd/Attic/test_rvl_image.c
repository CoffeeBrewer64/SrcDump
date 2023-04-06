d1 1
a1 1
#ident "$Id: test_rvl_image.c,v 1.6 2006/02/21 23:49:05 craig Exp $"
d25 10
d59 1
a59 1
uint8_t *h3HashArray;
a103 3
    h3HashArray = (uint8_t *) malloc(3 * 32 * 1024);
    assert(h3HashArray != NULL);

d130 12
a141 10
    updatePartArray = (updatePartition_t **)
                       malloc (sizeof(updatePartition_t *) * numUpdates);
    assert(updatePartArray != NULL);

    doRawDiskRead((uint8_t *) updatePartArray,
                sizeof(updatePartition_t *) * numUpdates, updateArrayOff);

    for (int i = 0; i < numUpdates; i++) {
        printf ("Update partition #%d:\n", i);
        dumpUpdatePartition(ntohl((uint32_t) updatePartArray[i]));
d419 7
d457 14
