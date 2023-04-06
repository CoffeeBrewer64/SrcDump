d10 1
a10 3

static const char gCertFname[]   = "cert.sys";
static const char gRlFname[]     = "crl.sys";
d15 11
a25 1
int saGameLaunch(BbTicket *ticket,u8 *heap,u32 heapSize)
a26 2
    BbAppLaunchCrls appRls;
    BbTicketBundle ticketBundle;
a32 2
    u32 haveCrl=1;
    char appName[16];
d36 4
a39 2
    ticketBundle.ticket = ticket;
    pCmdh = &(ticketBundle.ticket->cmd.head);
d78 1
a78 1
                         ticketBundle.ticketChain)<0){
d83 1
a83 1
                         ticketBundle.cmdChain)<0){
d95 1
a95 1
        haveCrl = 0;
d97 1
a97 1
    if(haveCrl){
d122 1
a122 1
        memset((void *)&appRls,0,sizeof(appRls));
d124 1
a124 1
        if(saRlBundle(rlHeap,certHeap,&appRls)!=BB_SYSAPP_PASS)
d128 28
d158 1
a158 1
                                  (void *)0)){
d167 1
a167 1
    cidToAppName(pCmdh->id,appName);
