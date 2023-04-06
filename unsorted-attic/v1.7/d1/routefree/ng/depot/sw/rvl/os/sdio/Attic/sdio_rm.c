d20 1
a20 1
#ident "$Id: sdio_rm.c,v 1.6 2006/03/20 19:26:22 gbarnard Exp $"
d365 1
a365 1
    if ((sdrmQid = IOS_CreateMessageQueue(sdrmQ, sizeof(sdrmQ), 0)) < 0) 
d384 1
a384 1
    if ((sdrmQidr = IOS_CreateMessageQueue(sdrmQr, sizeof(sdrmQr), 0)) < 0) 
