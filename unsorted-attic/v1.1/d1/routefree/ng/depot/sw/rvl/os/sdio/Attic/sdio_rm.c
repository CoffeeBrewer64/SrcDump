d20 1
a20 1
#ident "$Id: sdio_rm.c,v 1.2 2006/01/27 19:16:40 jlivesey Exp $"
d22 6
a27 6
	#include <ios.h>
	#ifdef VERSA
		#include <versaios.h>
	#endif
	#include <iostypes.h>
	#include <ioslibc.h>
d30 5
a34 5
	#include "../../include/sd.h"
	#include "../../include/sd_card.h"
	#include "../../include/sd_host.h"
	#include "../../include/sd_ioctl.h"
	#include "../../include/sdio_rm.h"
d47 14
a316 13

	#define SDRM_QUEUE_SIZE 	64	
	#define SDRM_STACK_SIZE 	1024
		
	IOSMessageQueueId 	sdrmQid;
	IOSMessage 			sdrmQ[SDRM_QUEUE_SIZE];	
	
	/* reponse or reply */
	IOSMessageQueueId 	sdrmQidr;
	IOSMessage 			sdrmQr[SDRM_QUEUE_SIZE];	

	u8 stacksdio[SDRM_STACK_SIZE];

d335 3
a337 2
        //SDIO_LOG(SDIO_INIT,
        printf("%s: Received resource request: %08x\n", 
d391 1
a391 1
	u32 pri = 90; //IOS_GetThreadPriority(0);
