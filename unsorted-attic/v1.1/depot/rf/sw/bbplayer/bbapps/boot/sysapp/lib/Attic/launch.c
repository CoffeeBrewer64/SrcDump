d79 12
d103 1
a103 1
        blkList = (u16 *)(certHeap + fsStat.size);
d105 1
a105 2
        fsret = osBbFStat(fd, &fsStat, blkList, 
                          ((u32)((u8 *)blkList-(u8 *)certHeap))/2);
d110 1
a110 1
        if(fsStat.size >= (heapSize-(u32)((u8 *)blkList-(u8 *)certHeap)))
d113 1
a113 1
        rlHeap = (u8 *)blkList;
a123 2
    }

d125 2
a126 13
    /* create ticket bundle */
    if(saCertCreateChain(certHeap,ticket->head.issuer,
                         ticketBundle.ticketChain)<0){
        PRINTF("saCertCreateChain() failure for ticket chain.\n");
        return SALAUNCH_ERR_DATA;
    }
    if(saCertCreateChain(certHeap,pCmdh->issuer,
                         ticketBundle.cmdChain)<0){
        PRINTF("saCertCreateChain() failure for cmd chain.\n");
        return SALAUNCH_ERR_DATA;
    }
    memset((void *)&appRls,0,sizeof(appRls));
    if(haveCrl){
a137 1

d152 7
a158 4
    blkList = (u16 *)(rlHeap + fsStat.size);
    ALIGN_DCACHE(blkList);
    fsret = osBbFStat(fd, &fsStat, blkList, 
                      ((u32)((u8 *)blkList-(u8 *)rlHeap))/2);
d164 2
d177 4
d183 2
d187 3
a189 2
    osBbAtbSetup(PI_DOM1_ADDR2, blkList, 
                 ((u32)((u8 *)blkList-(u8 *)rlHeap))/2);
d203 2
