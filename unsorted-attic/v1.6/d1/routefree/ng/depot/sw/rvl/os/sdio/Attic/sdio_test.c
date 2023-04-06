d12 1
a12 1
#ident "$Id: sdio_test.c,v 1.5 2006/03/17 01:49:31 gbarnard Exp $"
a16 1

a21 5
#ifdef VERSA
	#include "ios_pci.h"
	#include <versaios.h>
#endif

d26 1
a26 42
/*
#define PI_REG_CONFIG				0x024
#define PI_REGSP_CP					0x0c000000
#define PI_REGSP_PE					0x0c001000
#define PI_REGSP_DSP				0x0c005000
#define PI_GFXSP					0x0c008000
#define PI_REGSP_PI					0x0c003000
#define PI_CONFIG_REG_SYSRSTB_MASK	0x00000001
#define PI_CONFIG_REG_MEMRSTB_MASK	0x00000002
*/

//===========================

//#define STACK_SIZE 4096
//const u8 _initStack[STACK_SIZE];
//const u32 _initStackSize = sizeof(_initStack);
//const u32 _initPriority = 10;

// --- code for testing timer ---
void
test_sleep(u32 arg)
{
    IOSMessageQueueId mq;
    IOSMessage array[4];
    IOSMessage m;
    IOSTimerId  t2; 

    //printf("Creating message queue\n");
    mq = IOS_CreateMessageQueue(array, 4, 0);
    
    t2 = IOS_CreateTimer(arg, 0, mq, 0xbabababa);
    //printf("Waiting(%d) %08X", i, IOS_GetTimer());
    IOS_ReceiveMessage(mq, &m, IOS_MESSAGE_BLOCK);
    //printf("Rx Msg[%x] @ %08X\n", m, IOS_GetTimer());
    IOS_DestroyTimer(t2);
    
    return;
}

//===========================

extern void iosYieldThread(void);
d28 3
d34 1
d37 1
a37 1
// --------------
d43 1
a43 1
   	int host_controller_number = 0; // 0 for SDIO0 and 1 for SDIO1  
d70 1
a70 5
		//addr = (u32*)(ACR_PROT_REGS_BASE + 0x038); printf("IOP_Sta");printf("[%08X]:%08X\n",addr,*addr );
		
		/// Writing to PI config register for deasserting the soft reset 
		/// busWrt32(PI_REGSP_PI + PI_REG_CONFIG,
		///	 PI_CONFIG_REG_SYSRSTB_MASK | PI_CONFIG_REG_MEMRSTB_MASK);		
d74 1
a74 1
    test_sleep(10000);
d79 1
a79 1
    	test_sleep(10000);
d83 1
a83 1
    	test_sleep(10000);
d144 1
a148 1
        IOS_YieldThread();
