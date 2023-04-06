d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.23 2006/03/21 01:47:12 craig Exp $"
d46 1
a154 14
/*
 */

uint32_t
readH3Hashes(uint8_t* const destAddr, const uint32_t wordOffset)
{
    uint32_t    returnVal;

    returnVal = doRawDiskRead(destAddr, MAX_H3_HASH_SIZE, wordOffset);
    return(returnVal);
}

/*************************************************************/

d187 1
a187 1
 *           false  - if the they don't or some other error occurs.
d256 4
a266 3
 *         The raw data is written by the disk into a separate 32K buffer.
 *         The data is decrypted into the buffer pointed to by destAddr.
 *         The hash data remains in the separate buffer.
d295 5
d661 2
d701 1
a701 1
getGamePartitionOffset(uint32_t *WordOffset, uint32_t *error)
d718 3
d732 1
d734 1
a734 1
    /* Read partition offset */
d742 2
a743 1
    *WordOffset = ntohl(partitionOffset);
d745 1
a745 1
             *WordOffset << 2);
d785 1
d808 1
d814 1
a814 17
	printf ("H3 hash read FAILED!!\n");
    }
#ifdef NOT_DONE
    // FIXME - malloc isn't available - use something else
    tmd = (ESTitleMeta *) malloc (gamePartition.tmdSize);
    assert(tmd != NULL);
    returnVal = doRawDiskRead(tmd, gamePartition.tmdSize, diskState.tmd);
    if (returnVal != DI_ERR_NO_ERROR) {
        return(returnVal);
    }
    certs = (ESRsa2048Rsa *) (malloc (sizeof (ESRsa2048RsaCert)) * diskState.numCertificates);
    assert(certs != NULL);
    returnVal = doRawDiskRead(certs,
                              sizeof(ESRsa2048RsaCert) * diskState.numCertificates,
                              diskState.certificates);
    if (returnVal != DI_ERR_NO_ERROR) {
        return(returnVal);
d817 1
a817 1
#endif
