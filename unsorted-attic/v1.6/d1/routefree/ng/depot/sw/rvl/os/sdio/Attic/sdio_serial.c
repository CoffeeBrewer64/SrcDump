d12 1
a12 1
#ident "$Id: sdio_serial.c,v 1.5 2006/03/17 01:49:31 gbarnard Exp $"
a38 4
	#ifdef VERSA
		#include <versaios.h>
		#include "ios_pci.h"
	#endif
d47 1
a47 1
	#define SD_QUEUE_SIZE 	32	
d59 3
a61 1
	inline IOSError sdusleep(u32 usec, IOSMessageQueueId mq, char *ids)
d63 15
a77 34
		#if 0
		    IOSError rv = IOS_ERROR_OK;   
		    
		    if (ids[0]!=0) printf("%s%d",ids,usec);
	//	    printf("%s Start\n",__FUNCTION__);
	//	    iosCreateTimer(IOSTime value, IOSTime interval, IOSMessageQueueId mqid, IOSMessage mesg)
		    if ((rv = IOS_CreateTimer(usec, 0, slpQid, 0xbabecafe)) < 0)
		    {
		    	printf("ERROR %x\n",rv);
		        return rv;
		    }
	//	    printf("   waiting TmrNo=%d ",rv);
		    IOS_ReceiveMessage(slpQid, slpQ, IOS_MESSAGE_BLOCK);
	//		printf("   timed %x",slpQ);
			//IOSError sDestroyTimer(IOSTimerId id)	
			rv = IOS_DestroyTimer(rv);
	//		if (ids[0]!=0) printf("%s\n",ids);
		    return rv;
	    #else
		    IOSMessageQueueId mqs;
		    IOSMessage array[4];
		    IOSMessage m;
		    IOSTimerId  t2; 
		
		    //printf("Creating message queue\n");
		    mqs = IOS_CreateMessageQueue(array, 4, 0);
		    
		    t2 = IOS_CreateTimer(usec, 0, mqs, 0xbabababa);
		    //printf("Waiting(%d) %08X", i, IOS_GetTimer());
		    IOS_ReceiveMessage(mqs, &m, IOS_MESSAGE_BLOCK);
		    //printf("Rx Msg[%x] @ %08X\n", m, IOS_GetTimer());
		    IOS_DestroyTimer(t2);
 	    	return 0;
	    #endif
d144 1
d146 1
d149 2
a150 1
		
d163 1
a163 1
	#define io(x)                *((volatile int *)(x))
d168 1
a168 1
#define DEVICE_NAME      "sdioserial"
d171 1
d286 1
a286 1
    IOSError rv;
d325 1
a325 1
    u32 pri = IOS_GetThreadPriority(0); //100; /* max prioroty for irq */ //IOS_GetThreadPriority(0);
d344 2
a345 2
    	baseaddress = 0x0D070100; // note d080000 for board?
    	sdh_global->m_slotcount = 2;
d368 1
a368 1
			sdh_global->m_sdslot[i].m_base = (void*)baseaddress; //+0x100;			
d390 1
a390 1
    sdusleep(30000,slpQid,"+");
d417 1
a417 1
    sdusleep(30000,slpQid,"+");
d657 1
