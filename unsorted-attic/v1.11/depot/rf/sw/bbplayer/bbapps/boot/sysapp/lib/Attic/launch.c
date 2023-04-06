a46 1
    blkList = (u16 *)heap;
d51 1
a51 1
    fsret = osBbFStat(fd, &fsStat, blkList, heapSize/2);
d97 6
d105 1
a105 3
        blkList = (u16 *)heap;
        ALIGN_DCACHE_DYN(blkList);
        fsret = osBbFStat(fd, &fsStat, blkList, heapSize>>14);
d110 1
a110 1
        if(fsStat.size >= heapSize)
a112 2
        rlHeap = (u8 *)heap;

a123 1
        /* XXX: must fix this dependency on certHeap before using this code */
