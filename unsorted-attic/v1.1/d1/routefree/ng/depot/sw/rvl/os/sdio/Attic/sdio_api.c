d12 1
a12 1
#ident "$Id: sdio_api.c,v 1.25 2006/01/13 22:54:55 gbarnard Exp $"
d34 5
a38 5
	#include "../../include/sd.h"
	#include "../../include/sd_card.h"
	#include "../../include/sd_host.h"
	#include "../../include/sd_ioctl.h"
	#include "../../include/sdio_rm.h"
d90 7
a96 3
	*fd = sdrmQid;	//GB to be completed
	//*fd = IOS_Open(fn, 0);
    printf("IOS_Open(%s): remeber to complete %d\n\n", fn, *fd);	
d122 1
a122 1
		printf("ISDIO_Ioctl -> SDIO RM mq:%d\n",sdrmQid);
d127 1
a127 1
		printf("ISDIO_Ioctl <- Done Reply\n");
