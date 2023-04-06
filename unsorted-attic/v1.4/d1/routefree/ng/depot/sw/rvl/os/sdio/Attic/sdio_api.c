d12 1
a12 1
#ident "$Id: sdio_api.c,v 1.3 2006/03/15 20:44:38 gbarnard Exp $"
d85 4
a88 2
extern IOSMessageQueueId 	sdrmQid;
extern IOSMessageQueueId 	sdrmQidr;
a89 1
#define RMDEBUG 1
d94 1
a94 1
		*fd = sdrmQid;	//async debug version
d99 5
d107 1
a107 1
	return 0;
d151 2
a152 1
#define IOSCid u32                      
d155 3
a157 1
	return 0;
d299 1
a299 1
                         0x0, &rca, 0x0);
d1000 1
a1000 1
                         0x0, NULL, 0x0);
d1095 1
a1095 1
                         0x0, NULL, 0x0);
d1148 1
a1148 1
                        0x0, &value, 0x0);
d1537 1
a1537 1
                         0x0, &value, 0x0);
d1577 1
a1577 1
                         0x0, NULL, 0x0);
