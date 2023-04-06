d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.12 2006/02/16 21:51:05 craig Exp $"
d35 1
d279 2
d286 1
d296 1
d302 1
d307 1
d324 2
d335 1
d342 1
a364 1
        printf ("*** DBR: 2 ***\n");
a389 5
    printf ("(DoBlockRead) :\n\t");
    for (int i = 0; i < 16; i++) {
        printf ("0x%x ", readBuffer[i]);
    }
    printf ("\n");
d490 1
a490 1
    printf ("Calling doRvlRead: byteLength = %u\n", byteLength);
a542 1
        // printf ("1:\n");
a563 1
        // printf ("2:\n");
a581 1
        // printf ("3:\n");
a583 1
            // printf ("4:\n");
d618 2
a619 2
        printf ("(readHashEncrypted) noEncrypt = %d, noHashed = %d\n",
                diskInfo.noEncryption, diskInfo.noHash);
d654 1
a654 1
    printf ("(gGPO) Game TOC addr: 0x%x (byte addr)\n",
d675 1
a675 1
    printf ("(gamePartitionOffset) game partition offset: 0x%x\n",
d720 1
a720 1
    printf ("(read meta data) H3 offset: 0x%x; data offset 0x%x (byte addrs)\n",
