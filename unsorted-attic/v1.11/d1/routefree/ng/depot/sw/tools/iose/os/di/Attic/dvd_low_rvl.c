d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.10 2006/01/28 03:38:11 craig Exp $"
d20 1
d89 1
d480 3
a483 1
#ifdef SIMPLE_IMAGE
d491 1
d493 4
d498 7
a504 2
            diFatalError("Offset command not given before RVL READ");
            /* Code doesn't reach here */
d506 1
a506 1
        returnVal = readVerifyGameMetaData(0);
a512 1
        printf ("(doRvlRead) Done reading H3 hashes\n");
d594 2
a595 1
                                         sizeof(diskInfo), DISK_INFO_OFFSET);
d600 2
d608 57
d697 2
a698 2
    diskState.h3WordOffset   = (uint32_t) gamePartition.h3Hashes;
    diskState.dataWordOffset = (uint32_t) gamePartition.encryptedArea;
d702 2
d773 1
a773 1
/*************************************************************/
