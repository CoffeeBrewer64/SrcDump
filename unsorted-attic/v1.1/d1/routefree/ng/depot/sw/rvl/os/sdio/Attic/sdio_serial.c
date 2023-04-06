d12 1
a12 1
#ident "$Id: sdio_serial.c,v 1.2 2006/01/31 02:12:12 gbarnard Exp $"
d45 3
d49 1
d51 2
a52 3
	
	#define SD_QUEUE_SIZE 	64	
	#define STACK_SIZE 		1024
d56 1
d59 5
a63 2

	IOSError sdusleep(u32 usec, IOSMessageQueueId mq, char *ids)
d65 22
a86 17
	    IOSError rv = IOS_ERROR_OK;   
	    IOSMessage m;
	    if (ids[0]!=0) printf("%s%d",ids,usec);
	    printf("%s Start\n",__FUNCTION__);
//	    iosCreateTimer(IOSTime value, IOSTime interval, IOSMessageQueueId mqid, IOSMessage mesg)
	    if ((rv = IOS_CreateTimer(usec, 0, mq, 0xbabecafe)) < 0)
	    {
	    	printf("ERROR %x\n",rv);
	        return rv;
	    }
	    printf("   waiting...\n");
	    IOS_ReceiveMessage(mq, &m, IOS_MESSAGE_BLOCK);
		printf("   timed %x\n",m);
		//IOSError sDestroyTimer(IOSTimerId id)	
		rv = IOS_DestroyTimer(rv);
		if (ids[0]!=0) printf("%s\n",ids);
	    return rv;
d89 1
a89 1
	u8 stack2[STACK_SIZE];
d93 1
a93 1
	const u32       _initPriority = 127;
d96 5
a100 5
	#include "../../include/sd.h"
	#include "../../include/sd_card.h"
	#include "../../include/sd_host.h"
	#include "../../include/sd_ioctl.h"
	#include "../../include/sd_debug.h"
d153 4
d159 1
a159 1
		return IOS_Alloc(0,size); 
d164 1
a164 1
		IOS_Free(0,(void*)objp);
d209 3
a211 2
sd_request sd_req;
sd_request *request_global=&sd_req;
a212 1
int ser_debug = DEBUG_SER_ERR|DEBUG_SER_SD_CMD|DEBUG_SER_REG_MREAD;  //||DEBUG_SER_CMD DEBUG_SER_REG_WRITE|DEBUG_SER_REG_READ;
d289 1
a289 1
sdio_init_irq_pci0(void)
d294 1
a294 1
    /* Create a message queue and register for PCI0 events */
d300 3
d310 8
a317 1
	    if ((rv = IOS_HandleEvent(0, sdiQid, 0)) != IOS_ERROR_OK) 
d319 1
a319 1
	        printf("Unable to register PCI0 event handler: %d\n", rv);
d321 2
a322 1
	    }
d324 1
a324 2
    /* Initialize actual PCI card in slot 0*/

d326 1
d330 3
d340 3
a342 1
static IOSError
d363 3
a365 2
	sdh_global->m_slotcount = 2; //((io(pci_cfg_addr+0x40)& 0x70)>>4)+1;
	printf("Slot Count = %d\n",sdh_global->m_slotcount);
d371 1
d377 1
a377 1
		int j,k;		// debug
a385 1
		
a388 29
				
				#if 0
				dp32 = (u32*)sdh_global->m_sdslot[i].m_base;
				dp16 = (u16*)sdh_global->m_sdslot[i].m_base;
				dp8 = (u8*)sdh_global->m_sdslot[i].m_base;
				for (k=0;k<16;k++)
				{
					printf("0x%08X",dp32);
					#if 0
						//*dp32 = (u32)0xFFFFFFFF;
						dp32++;
						for (j=0;j<2;j++)
						{	
							//*dp16 = 0xFFFF;
							WRITE_HOST_U16((u32)dp16, 0, 0xFFFF);
							printf(" 0x%04X",*dp16);dp16++; 
													
						}
					#else
						for (j=0;j<4;j++)
						{	
							//*dp8 = 0xFF;
							WRITE_HOST_U8((u32)dp8, 0, 0xFF);
							printf(" 0x%02X",*dp8);dp8++; 						
						}
					#endif					
					printf("\n");
				}
				#endif
a393 1
			
d395 1
d397 1
d403 13
a415 5
	/* c) add irq handling to process card insert interrupts*/
    //printf("IRQ: IOS_CreateThread\n");
    id = IOS_CreateThread((IOSEntryProc)sdioIrqThread, (void*)200, stack2+STACK_SIZE, STACK_SIZE, pri, IOS_THREAD_CREATE_DETACHED);
    //printf("IRQ: Created thread Id %c\n", '0'+id);
    sdio_init_irq_pci0();
d417 2
a418 1
	/* d) initialise each slot */
d424 2
d427 27
a453 10
    /* Create SDIO message queue */
    sdQid = IOS_CreateMessageQueue(sdQ, sizeof(sdQ), 0);
    
    IOS_StartThread(id);
    printf("%s, IRQ Thread Started, id:%d mq:%d\n",__FUNCTION__,id,sdQid);
    
    //sdusleep(1000,sdQid,"+");	
    //sdusleep(1000,sdQid,"+");	
    
//done:
a520 1
extern u8 SDHostslot_SoftwareReset( struct sd_slot_base *slot, u8 mask);
d562 1
a562 1
//	printf("%s Called %x\n",arg);
d567 1
d572 1
a572 1
			//printf("   ---> IRQ in slot 0x%04X<---\n",(u32)dwIntStatus);
d593 1
d595 1
a595 1
  		IOS_YieldThread(); 
d686 1
a686 1
    unsigned short response[8];
d863 1
a863 1
        	sd_req.callback = (void*)cmd_op.callback;
