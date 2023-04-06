d12 1
a12 1
#ident "$Id: sdio_serial.c,v 1.7 2006/03/20 07:27:26 gbarnard Exp $"
d69 1
a69 1
	    mqs = IOS_CreateMessageQueue(array, 4, 0);
d279 1
a279 1
    mq = IOS_CreateMessageQueue(&array, 1, 0);
d289 1
a289 1
    if ((sdiQid = IOS_CreateMessageQueue(sdiQ, sizeof(sdiQ), 0)) < 0) 
d386 1
a386 1
    sdQid = IOS_CreateMessageQueue(sdQ, sizeof(sdQ), 0);
