/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

#ident "$Id: sdio_test.c,v 1.1 2006/03/30 16:50:23 gbarnard Exp $"

#include <hw.h>
#include <arm.h>

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <sys.h>

#include "sd.h"
#include "sd_ioctl.h"
#include "sdio_rm.h"

#include "sdio_api.h"
#include "sdio_test.h"
#include "sdio_api_test.h"

extern void msleep(unsigned int msecs);

//======= =======
// - Test Functions -
extern void 				iosYieldThread(void);
extern IOSError 			SDIO_Ioctl(IOSResourceRequest *req);
extern IOSMessageQueueId 	sdrmQid;

// -Test Applications -
extern int sdio_api_test(void);
extern int sd_api_test(void);
//=======

u8 iosshStack[1024];  



void sdio_test(u32 arg)
{    
   	int host_controller_number = 0; // --- 0 for SDIO0 and 1 for SDIO1

	// --- not required depends on ios.elf version ---
	printf("\n******* RVL *******\n");
	//init_USB_PLL();
	//enableChipBlocks();
	
	{
		volatile u32* addr;
		/*
		addr = (u32*)(ACR_PROT_REGS_BASE + 0x198); printf("ClkGate");printf("[%08X]:%08X\n",addr,*addr );
		addr = (u32*)(ACR_PROT_REGS_BASE + 0x190); printf("SysCtrl");printf("[%08X]:%08X\n",addr,*addr );
		addr = (u32*)(ACR_PROT_REGS_BASE + 0x194); printf("RstCtrl");printf("[%08X]:%08X\n",addr,*addr );
		addr = (u32*)(ACR_PROT_REGS_BASE + 0x19C); printf("PLLDura");printf("[%08X]:%08X\n",addr,*addr );
		
		addr = (u32*)(ACR_PROT_REGS_BASE + 0x1D4); printf("USBPLL ");printf("[%08X]:%08X\n",addr,*addr );
		addr = (u32*)(ACR_PROT_REGS_BASE + 0x1D8); printf("USBPLLE");printf("[%08X]:%08X\n",addr,*addr );
		
		addr = (u32*)(ACR_PROT_REGS_BASE + 0x1DC); printf("IOPWRCT");printf("[%08X]:%08X OE IE SDIO\n",addr,*addr );
		addr = (u32*)(ACR_PROT_REGS_BASE + 0x1E4); printf("IOStrn1");printf("[%08X]:%08X\n",addr,*addr );
		*/
		
		addr = (u32*)(ACR_PROT_REGS_BASE + 0x03C); printf("IOP_Ena");printf("[%08X]:%08X\n",addr,*addr );
		//*addr = 0x0181;
		//addr = (u32*)(ACR_PROT_REGS_BASE + 0x03C); printf("IOP_Ena");printf("[%08X]:%08X\n",addr,*addr );
		addr = (u32*)(ACR_PROT_REGS_BASE + 0x038); printf("IOP_Sta");printf("[%08X]:%08X\n",addr,*addr );
		//*addr = 0xFFFFFFFF;
		//addr = (u32*)(ACR_PROT_REGS_BASE + 0x038); printf("IOP_Sta");printf("[%08X]:%08X\n",addr,*addr );		
	}	
	
	// --- test timer ---
    msleep(10);
   
    {    	
    	printf("\n=== SDIO Init RM     ===\n");	
    	sdio_rm(host_controller_number);
    	msleep(10);
    	
    	printf("\n=== SDIO_%d Init Driver ===\n",host_controller_number);
		sdio_init_module(host_controller_number);
    	msleep(10);
    }
    
    // --- this section to test individual calls ---
    #if 0
	    printf("\n--- SDIO Test IOCTL ---\n");
		#if 0
		/* test ioctl command - direct driver */
		{
			struct inode *inode;
			struct file *file;
			unsigned int cmd;
			unsigned long arg;
			cmd = SD_RESET;
			int slot = 1;
			arg = (unsigned long)&slot;
			sdio_ser_ioctl (inode, file, cmd, arg);
		}
		#else
		{
			/* test ioctl command - direct rm call */
			IOSResourceRequest req;
			int slot = 1;	
			IOSResourceIoctl ioctl;	
			ioctl.cmd = SD_RESET;
			ioctl.inLen = 1;
			ioctl.inPtr = (u8*)&slot;
			
			req.cmd = IOS_IOCTL;
			req.args.ioctl = ioctl; 
			
			#if 0
				printf("Calling sdio_rm IO_CTL.\n");
				SDIO_Ioctl(&req);
			#else
			{
				IOSMessage msg;
				printf("Sending message to sdio_rm mq:%d\n",sdrmQid);
				msg = (IOSMessage)&req;
				IOS_SendMessage(sdrmQid, msg, IOS_MESSAGE_NOBLOCK);
				printf("Yield\n");
				IOS_YieldThread();
			}
			#endif
		}
		#endif
	#endif
	
	// --- this section to test ported applications ---
	printf("\n=== Run Test Application SDIO%d ===\n",host_controller_number);
	if (host_controller_number==0)
	{
		sdio_api_test();
	}
	else
	{
		sd_api_test();
	}
	
	printf("\n=== done ===\n");
	    
	// --- the following is required since iossh is killed after loading this program ---
    while(1) 
    {
    	int j;
    	j++;
    }
}

/* eof */
