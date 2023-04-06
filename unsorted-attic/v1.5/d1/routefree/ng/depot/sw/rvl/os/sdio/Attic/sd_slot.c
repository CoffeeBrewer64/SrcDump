d12 1
a12 1
#ident "$Id: sd_slot.c,v 1.4 2006/03/17 01:49:31 gbarnard Exp $"
a31 4
	#ifdef VERSA
		#include "ios_pci.h"
		#include <versaios.h>
	#endif
d42 1
a42 3

	extern IOSMessageQueueId 	sdQid;
	
d44 1
a44 1
	extern IOSError sdusleep(u32 usec, IOSMessageQueueId mq, char *ids);
a63 10
    void msleepx(u32 msecs, char* str)
    {
		u32 usecs = msecs; //*1000;
		IOSError rv = sdusleep((u32)usecs,sdQid,str);
		if (rv!=IOS_ERROR_OK)
		{
			printf("%s Error. Status = 0x%x\n",__FUNCTION__,rv);
		}    	
    }

d67 1
a67 2
		u32 usecs = msecs; //*1000;
		//IOSError rv = 
d70 1
a70 1
			sdusleep((u32)2000,sdQid,"+");
a71 1
		//udelay(usecs);
d144 1
a247 1
	//WRITE_HOST_U32((u32)slot->m_base, 0x2C, 0x00000070);
d265 2
a266 1
    PCI_DEBUG (DEBUG_PCI_INIT, "%s: Present State:0x%X\n", __FUNCTION__,present_state);
d829 5
a833 4
	//printf(" ");
    //PCI_DEBUG (DEBUG_PCI_IRQN, 
    //printf( "%s NIntStatus(%d):0x%04x Cmd:%d 0x%08X",
    //           "===->", (u32)slot->m_slotindex, wIntStatus, command, READ_HOST_U32((u32)slot->m_base, HOSTREG_TRANSMODE));
