
/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 * $Id: sd_api_test.c,v 1.7 2006/03/21 02:26:02 wheeler Exp $
 */

static char ident[] = "$Id: sd_api_test.c,v 1.7 2006/03/21 02:26:02 wheeler Exp $";

#ifdef LINUX
	#include <ios.h>
	#include <iostypes.h>
	#include <ioslibc.h>
	#include <iossdiotypes.h>
	#include <iosresource.h>
	#include <sys/types.h>
	
	#include <stdio.h>   /* for printf */
	#include <stdlib.h>  /* for getenv */
	#include <string.h>  /* for memcpy */
	#include <unistd.h>  /* for sleep */
	
	#include <sd_api.h>	/* includes sdio_api shared */
#else
	#include <ios.h>
	#include <iostypes.h>
	#include <ioslibc.h>
	
	#ifdef VERSA
		#include "ios_pci.h"
		#include <versaios.h>
	#endif
	
	#include "sd.h"
	#include "sd_ioctl.h"
	#include "sdio_rm.h"
	
	#include <sd_api.h>	/* includes sdio_api shared */	
	
	#include "sd_debug.h"
	
	#define IOS_ThreadExit(X)  IOS_DestroyThread(0, NULL)

#endif

/* Structure to keep handles to drivers */
SDDevHandle Handles[MAX_SLOTS][MAX_FUNCS];
/* Structure to keep info on which card to access */
SDDevConfig config;

/* 
 * Parameters for message queue used to register driver. If there were
 * applications that used this driver, they would talk to it via this
 * queue.
 */
#define MSGQ_SIZE 4

/*
 * sd_command_test
 */
void cmd_deselect(void)
{
    SDDevHandle fd = Handles[config.SDDevSlot][0];;
    IOSError status;
    u32 resp[4];
    u32 command = 7; 			/* CMD0.. see sepc */
    u32 cmd_type = SD_COMMAND; 	/* see sd_host.h sdio_util.c */
    u32 resp_type = ResponseR1b; /* see spec */
    u32 req_size = 0;			/* ??? doesnt seem to be used ... sdio_util.c */
    u32 cmd_arg = 0; /*(fd->SDDevRca)<<16;*/	/* RCA msb 16 */
    
    status = sd_command (fd, command, cmd_type, resp_type, req_size, cmd_arg, 0,0,0,0, resp);
    status = GetSdStatus(fd, resp);
    
    if (status != IOS_ERROR_OK) 
    {
        printf (" - Command returned status:0x%X -\n",status);
        return;
    }
    else 
    {
    	printf(" - cmd_deselect OK -\n");
    }

}



/*
 * cmd_select, put card in transfer state
 */
IOSError cmd_select(void)
{
    SDDevHandle fd = Handles[config.SDDevSlot][0];;
    IOSError status;
    u32 resp[4];
    u32 command = 7; 					/* CMDxx see spec. */
    u32 cmd_type = SD_COMMAND; 			/* see sd_host.h sdio_util.c */
    u32 resp_type = ResponseR1b; 		/* see spec */
    u32 req_size = 0;					/* ??? doesnt seem to be used ... sdio_util.c */
    u32 cmd_arg = (fd->SDDevRca)<<16;	/* RCA msb 16 */
    
    status = sd_command (fd, command, cmd_type, resp_type, req_size, cmd_arg,  0,0,0,0, resp);
	status = GetSdStatus(fd, resp);    
    if (status != IOS_ERROR_OK) 
    {
        printf ("Command returned status:0x%X\n",status);
        return 1;
    }
    else 
    {
    	printf(" - select SD card for R/W -\n");
    	if (resp[0]!=0x900)
    	{
    		printf("State Not Ready ERROR\n");
    		return 1;
    	}
    }
	return IOS_ERROR_OK;
}


/* 
 * Card Specific Data Register, size etc.
 */
void cmd_cardsize(void)
{
	u32 totalSize, totalSectors, sectorSize;
    SDDevHandle fd = Handles[config.SDDevSlot][0];
    IOSError status = ISD_GetCardSize (fd, &totalSize, &totalSectors, &sectorSize);
    if (status) 
    {
    	printf("ISD_GetCardSize ERROR\n");
    }
    else
    {
    	printf("ISD_GetCardSize OK\n");
  		printf("     Sector Size   = %d\n",sectorSize);
  		printf("     Total Sectors = %d\n",totalSectors);
    	printf("     Card Capacity = %d\n",totalSize); 
    }   
}

/*
 * Test Read Card Register, with CID
 */
void cmd_cid(void)
{
    SDDevHandle fd = Handles[config.SDDevSlot][0];
    IOSError status;
    unsigned int resp[4];
         
    status = ISD_ReadCardRegister(fd, SD_REG_CID, resp, 0);

    if (status != IOS_ERROR_OK) 
    {
        printf ("ISD_ReadCardRegister(CID) ERROR:0x%X\n",status);
    }
    else
    {
    	printf("ISD_ReadCardRegister(CID) OK\n     0x%08X%08X%08X%08X\n",
    		resp[3],resp[2],resp[1],resp[0]);
    }
}

void cmd_scr(void)
{
    SDDevHandle fd = Handles[config.SDDevSlot][0];
    IOSError status;
    unsigned int resp[4];
         
    status = ISD_ReadCardRegister(fd, SD_REG_SCR, resp, 0);

    if (status != IOS_ERROR_OK) 
    {
        printf ("SCR error status:0x%X\n",status);
    }
    else
    {
    	printf("SCR response:%08X %08X\n",resp[0],resp[1]);
    }
}

void cmd_ocr(void)
{
    SDDevHandle fd = Handles[config.SDDevSlot][0];
    IOSError status;
    unsigned int resp[4];
         
    status = ISD_ReadCardRegister(fd, SD_REG_OCR, resp, 0);

    if (status != IOS_ERROR_OK) 
    {
        printf ("OCR error status:0x%X\n",status);
    }
    else
    {
    	printf("OCR response:%08X\n",resp[0]);
    }
}

void cmd_rca(void)
{
    SDDevHandle fd = Handles[config.SDDevSlot][0];
    IOSError status;
    unsigned int resp[4];
         
    status = ISD_ReadCardRegister(fd, SD_REG_RCA, resp, 0);

    if (status != IOS_ERROR_OK) 
    {
        printf ("RCA error status:0x%X\n",status);
    }
    else
    {
    	printf("RCA response:%08X\n",resp[0]);
    }
}

extern char* decode_card_status (int card_status);
/*
 * Get the SD card state
 */
void cmd_status(void)
{
    SDDevHandle fd = Handles[config.SDDevSlot][0];
    IOSError status;
    unsigned int resp[4];
             
    status = GetSdStatus(fd, resp);

    if (status != IOS_ERROR_OK) 
    {
        printf (" - GetSdStatus ERROR:0x%X\n",status);
    }
    else
    {
    	printf(" - GetSdStatus:%X\n",resp[0]);  	
    	//printf(" - GetSdStatus:%X %s\n",resp[0],(char*)decode_card_status(resp[0]));  	
    }
}



u32 data[1024];	/* max 4 blocks for test example */
u32* pd = data;

/* test for multiblock async, callback to done at filesys integration */					
void cmd_readblocks(u32 offset, u32 length)
{
	SDDevHandle fd = Handles[config.SDDevSlot][0];
    IOSError status;
    void *arg = NULL;
    SDCallbackFunc handler = NULL;
   	int i,j;
   	u32* data = pd;
    
    /* clear data, use 0xEEEEEEEE since 0 could be same as erased */
    for ( i=0 ; i<512 ; i++) data[i] = 0xEEEEEEEE;
    
    printf("ISD_ReadMultiBlockAsync(offset=0x%x to data=0x%x blocks=%d)\n",
    	offset,(unsigned int)data,length>>9);
    
	status = ISD_ReadMultiBlockAsync (fd, offset, data, length, handler, arg);
	
    if (status != IOS_ERROR_OK) 
    {
        printf("Status:0x%X\n",status);
    }
    else
    {
    	/* For each block do: Note that here 512 bytes = 128 u32's */
		for (j=0; j<length/512; j++)
		{
			printf("Read block #%d (display in 32bit address)\n",j);
			{
				/* print couple of words from each block... */
		        for (i=0; i<16; i+=8)
		        {
		        	int addr = j*128+i;
		            printf("0x%08x:  %08x %08x %08x %08x %08x %08x %08x %08x\n", (u32)data+addr, 
		            	data[addr+0], data[addr+1], data[addr+2], data[addr+3], 
		            	data[addr+4], data[addr+5], data[addr+6], data[addr+7]);
		        }
			}
		}
   //    	printf("     %x %x %x %x\n", data[0], data[1], data[2], data[3]);
   // 	printf("     %x %x %x %x\n", data[128], data[129], data[130], data[131]);
    }	
}

void cmd_readblock(u32 offset)
{
	SDDevHandle fd = Handles[config.SDDevSlot][0];
    IOSError status;
    
    /* clear data */
    data[0]=0xEEEEEEEE;
    data[1]=0xEEEEEEEE;
    data[2]=0xEEEEEEEE;
    data[3]=0xEEEEEEEE;
    
    printf("ISD_ReadBlock(offset=0x%x to data=0x%x)\n",offset,(unsigned int)data);
    
	status = ISD_ReadBlock (fd, offset, data, 512);
	//sleep(1);
	
    if (status != IOS_ERROR_OK) 
    {
        printf("Status:0x%X\n",status);
    }
    else
    {
    	printf("     %x %x %x %x\n", data[0], data[1], data[2], data[3]);
    }	
}

void cmd_writeblock(unsigned int offset)
{
	SDDevHandle fd = Handles[config.SDDevSlot][0];
    IOSError status;

    int i;
    
    for (i=0; i<512; i++) data[i]=0x80000000+i+(offset<<8);
    
    printf("ISD_WriteBlock(data=0x%x to offset=0x%x)\n",(unsigned int)data,offset);
 
	status = ISD_WriteBlock (fd, offset, (unsigned int)&data, 512);
    if (status != IOS_ERROR_OK) 
    {
        printf("     ERROR:0x%X\n",status);
    }
    else
    {
    	printf("     %x %x %x %x ... \n",data[0],data[1],data[2],data[3]);    
    }	
}

/* test for erasing sectors - multiple blocks */
void cmd_erase_sector(u32 sector)
{
	SDDevHandle fd = Handles[config.SDDevSlot][0];
    IOSError status;
    void *arg = NULL;
    SDCallbackFunc handler = NULL;	
    printf("ISD_EraseSectorAsync(sector=%d)\n",sector);   
     
	status = ISD_EraseSectorAsync (fd, sector, handler, arg);
}

/* test for writing data to SD card, callback to be done at filesys integration */
void cmd_writeblocks(u32 offset, u32 length)
{
	SDDevHandle fd = Handles[config.SDDevSlot][0];
    IOSError status;
    void *arg = NULL;
    SDCallbackFunc handler = NULL;
    int i,j;
    
    for (i=0; i<512; i++) data[i]=0x80000000+i+(offset<<8);
    
    printf("ISD_WriteMultiBlockAsync(data=0x%x to offset=0x%x blocks=%d)\n",
    	(unsigned int)data,offset,length>>9);

	status = ISD_WriteMultiBlockAsync (fd, offset, (unsigned int)&data, length, handler, arg);
    if (status != IOS_ERROR_OK) 
    {
        printf("     ERROR:0x%X\n",status);
    }
    else
    {
    	/* For each block do: Note that here 512 bytes = 128 u32's */
		for (j=0; j<length/512; j++)
		{
			printf("Write block #%d (display in 32bit address)\n",j);
			{
				/* print couple of words from each block... */
		        for (i=0; i<16; i+=8)
		        {
		        	int addr = j*128+i;
		            printf("0x%08x:  %08x %08x %08x %08x %08x %08x %08x %08x\n", (u32)data+addr, 
		            	data[addr+0], data[addr+1], data[addr+2], data[addr+3], 
		            	data[addr+4], data[addr+5], data[addr+6], data[addr+7]);
		        }
			}
		}
    }	
}

/* 
 * Card Specific Optimisations, High Speed, 4-bits, etc.
 */
void cmd_optimise(void)
{
	IOSError status;
    SDDevHandle fd = Handles[config.SDDevSlot][0];
    u32 databuswidth = 4;
    
    /* set data bus width 1 or 4 bits */
    status = cmd_databuswidth(fd,databuswidth);  
    if (status != IOS_ERROR_OK) 
    {
        printf("     %s ERROR:0x%X\n",__FUNCTION__,status);
    }
    else
    {
    	printf(" - Set DataBus Width to %d -\n",databuswidth);
    }	
}

/*
 * sd_test
 *
 * Test driver for the sdio_api_test program.
 */
void sd_test(void)
{
    IOSError status;
    int slot_active = 0;
    
    { /* make buffer align */
    	u32 temp = (u32)data;
    	pd = (u32*)(temp&0xFFFFFF00)+0x100;
    }
 
    memset (&config, 0, sizeof (config));
  
    printf("\n------- Tests Start -------\n");
     
    ISD_InitCard();
    
	/* ======= Device Setup ======= */
   	config.SDDevSlot = 0;
    config.SDDevFunc = 0;
    
    /* --- Attach to driver --- */	
    status = ISD_AttachDevice(&config, &Handles[config.SDDevSlot][config.SDDevFunc]);
    if (status != IOS_ERROR_OK) 
    {
        printf ("ISD_AttachDevice:ERROR\n");
        return;
    }
    if (Handles[config.SDDevSlot][0])
    {
    	printf ("ISD_AttachDevice, attach to Host Driver Dev:0x%x OK\n",Handles[config.SDDevSlot][0]->SDDevFd);
    }
    
	set_driver_debug(Handles[config.SDDevSlot][0],1); //|DEBUG_SER_SD_CMD); //|DEBUG_SER_CMD|DEBUG_SER_SD_CMD|DEBUG_SER_REG_READ|DEBUG_SER_REG_WRITE); /* debug error messages in sdio host driver */    
    
    /* --- See if memory card is in slot --- */
    status = ISD_ProbeCard(config.SDDevSlot);
	if (status==IOS_ERROR_OK) 
	{
		printf(" - Probe found SD Card in slot %d -\n",config.SDDevSlot);  
	}
	else /* see if memory card in other slot */
	{
		#if 1
		config.SDDevSlot = 1;
		status = ISD_AttachDevice(&config, &Handles[config.SDDevSlot][config.SDDevFunc]);
		status = ISD_ProbeCard(config.SDDevSlot);
		if (status==IOS_ERROR_OK) 
		{
			printf(" - Probe found SD Card in slot %d -\n",config.SDDevSlot);  
		}	
		else
		#endif
		{	
			printf(" - Probe could not find SD Card. -\n"); 
			return;
		}
	}
		 
   	/* --- Mount (device becomes write/read able, and retrieve RCA (address) --- */
    status = ISD_MountCard(config.SDDevSlot,&Handles[config.SDDevSlot][0]);
    if (status != IOS_ERROR_OK) 
    {
        printf ("ISD_MountCard:ERROR\n");
        return;
    }
    else
    {
    	printf ("ISD_MountCard RCA:0x%x OK\n",Handles[config.SDDevSlot][0]->SDDevRca);
    	slot_active = 1;
    }
    
#if 1
    cmd_deselect();	/* need to be in state: for cmd, reset comes up in data transfer mode */
	cmd_status();
    cmd_cardsize();
    cmd_cid();
    cmd_status();
    cmd_rca();
#endif

#if 0 
	cmd_scr(); 									/* requires data bus tfer */
	cmd_ocr(); 									/* requires reset */
#endif   
	
	//set_driver_debug(Handles[config.SDDevSlot][0],0x0001|DEBUG_SER_SD_CMD); //0x2401

#if 1
	/* Data Transfer Testing */
	if (cmd_select()==IOS_ERROR_OK)
	{	
		cmd_optimise();	/* put in 4bit mode */
		
		#if 1
			cmd_writeblocks(0,1024);
		#else
			cmd_writeblock(0);	
			//cmd_writeblock(512);
		#endif
	
		#if 1
			cmd_readblocks(0,1024);
		#else
	    	cmd_readblock(0);
	    	//cmd_readblock(512);
	    #endif
	    
	    #if 1
	    	cmd_erase_sector(0);
	    	cmd_readblocks(0,1024);
	    #endif
	}
#endif   
   
    printf("\n------- Tests Done -------\n");
    config.SDDevSlot = 0;
    config.SDDevFunc = 0;
    status = ISD_DetachDevice(Handles[config.SDDevSlot][config.SDDevFunc]);
    if (status==IOS_ERROR_OK)
    {
    	printf("ISD_DetachDevice OK\n ... done ...");
    }
}


//    IOSMessageQueueId qid;
//    IOSMessage msgQ[MSGQ_SIZE];
/*
 * sd_api_test
 *
 * This is the entry point of the sd_api_test program.
 */
int
sd_api_test (void)
{
    IOSCid devId;


	printf ("%s\n", ident);
    printf("\n======= SD API Test Program 2 =======\n"); 
	
    ISDIO_FindDevice(&devId);
    printf("%s: devId %d\n",__FUNCTION__, devId);

#if 0
    /* 
     * Create a message queue that clients use to communicate with this driver
     */
    if ( (qid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE))<0)
    {
        printf("Creating SD message queue failed: 0x%x exit\n",qid);
        IOS_ThreadExit(0);
    }

    /* 
     * Register device 
     */
    if ( IOS_ERROR_OK != ISDIO_RegisterResourceManager(devId, qid) ) 
    {
        printf("Registering SD failed. Exiting...\n");
        IOS_ThreadExit(0);
    }
#endif

	/* Call main SD API test function */
    sd_test();


    /* Unregister device. Destroys message queue for us. */
/*    
    if ( IOS_ERROR_OK != ISDIO_UnregisterResourceManager(devId) ) 
    {
        printf("Un-registering SD driver failed. Exiting...\n");
    }	
*/
    return 0; //IOS_ThreadExit(0);
}
