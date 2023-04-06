d12 69
d194 46
d241 11
a251 1
int saGameLaunch(BbTicket *ticket,u8 *keyList,u8 *heap,u32 heapSize, u32 binding[4])
a253 2
    BbAppLaunchCrls appRls;
    BbTicketBundle ticketBundle;
d255 1
a255 1
    u8 *rlHeap,*certHeap;
d261 1
a261 1
    int i;
d280 1
d282 6
d290 5
a294 2
    if(BB_SYSAPP_PASS != saBundleTicket(ticket, &ticketBundle,&appRls,
                                        heap,heapSize)){
d299 215
a513 3
    if(SK_API_SUCCESS != skLaunchSetup(&ticketBundle, &appRls, keyList)){
        PRINTF("skLaunch() failure!\n");
        return SALAUNCH_ERR_DATA;
d516 16
a531 2
    /* XXX: recrypt may impact which extension to use */
    cidToAppName(pCmdh->id,gAppExt,appName);
d533 1
a533 1
    if( (fd = osBbFOpen(appName,"r")) < 0){
d537 1
a537 2
    for(i=0;i<heapSize;i++)
        heap[i]=0;
a538 1
//    ALIGN_DCACHE_DYN(blkList);
d546 1
d548 2
a549 1
        osBbLoadState(appName, &md.state, binding);
d551 1
a552 1
        PRINTF("Calling skLaunch()\n");
