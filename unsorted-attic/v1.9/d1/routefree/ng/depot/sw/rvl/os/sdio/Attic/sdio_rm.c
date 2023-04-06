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

/*
 * This is the sd/sdio resource manager.  It is registered against a
 * /dev/sdio.... pathname, and it is invoked by the kernel when an
 * open(), close(), ioctl() system call is executed by a user process.
 *
 * Typically, this user process would invoked the system call via
 * the sd/sdio api interface.
 */
#ident "$Id: sdio_rm.c,v 1.8 2006/03/21 02:26:02 wheeler Exp $"

#include <ios.h>
#ifdef VERSA
	#include <versaios.h>
#endif
#include <iostypes.h>
#include <ioslibc.h>


#include "sd.h"
#include "sd_card.h"
#include "sd_host.h"
#include "sd_ioctl.h"
#include "sdio_rm.h"

typedef struct {
    u8 inUse;
    u8 dev;
    u16 pos;
} SDIOFileDescriptor;

#define SDIO_NUM_DESCRIPTORS 2
static SDIOFileDescriptor sdiodesc[SDIO_NUM_DESCRIPTORS];

#define SDIO_DEV0 "/dev/sdio0"
#define SDIO_DEV1 "/dev/sdio1"

extern char* sdio_ioctl_str;

// ------- Add Heap For SD/SDIO Use ---
#define SDRM_QUEUE_SIZE 	128	
#define SDRM_STACK_SIZE 	1024
	
IOSMessageQueueId 	sdrmQid;
IOSMessage 			sdrmQ[SDRM_QUEUE_SIZE];	

/* reponse or reply */
IOSMessageQueueId 	sdrmQidr;
IOSMessage 			sdrmQr[SDRM_QUEUE_SIZE];	

u8 stacksdio[SDRM_STACK_SIZE];
                          
 
u32 sdio_debug=1;                          

/*
 * SDIO_Open
 *
 * Open the chosen device and increment the in-use counter.
 */
static IOSError
SDIO_Open(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    u32 dev = 0;
    IOSResourceOpen *args = &req->args.open;
    int i;

    //SDIO_LOG(SDIO_OPEN, 
    printf("%s: '%s' flags 0x%x\n", 
             __FUNCTION__, args->path, args->flags);

    /*
     * Compare the pathname to the two device pathnames.
     */
    if (!strncmp(args->path, SDIO_DEV0, sizeof(SDIO_DEV0)-1)) 
    {
    	printf("Open SDIO_0\n");
        dev = 0;
    } 
    else if (!strncmp(args->path, SDIO_DEV1, sizeof(SDIO_DEV1)-1)) 
    {
    	printf("Open SDIO_1\n");
        dev = 1;
    } 
    else 
    {
        rv = IOS_ERROR_NOEXISTS;
        SDIO_LOG(SDIO_ERROR, "%s: bad path %s\n",
                 __FUNCTION__, args->path);
        return rv;
    }

    /*
     * Find a free descriptor and error if all are currently
     * in use.
     */
    for (i = 0; i < SDIO_NUM_DESCRIPTORS; ++i) 
    {
        if (!sdiodesc[i].inUse) 
        {
        	printf("Found descriptor %d\n",i);
            break;
        }
    }

    if (i == SDIO_NUM_DESCRIPTORS) 
    {
    	printf("No Descriptors\n");
        rv = IOS_ERROR_MAX;
        return rv;
    }   

    sdiodesc[i].inUse = 1;
    sdiodesc[i].pos = 0;
    sdiodesc[i].dev = dev;
    rv = (IOSError) &sdiodesc[i];

   // SDIO_LOG(SDIO_OPEN, 
    printf("%s: new context handle %08x\n", 
             __FUNCTION__, req->handle);
	printf("...rv = %X\n",rv);
    return rv;
}

/*
 * SDIO_Close
 *
 * Just clears the in-use flag.
 */
static IOSError
SDIO_Close(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    SDIOFileDescriptor *d = (SDIOFileDescriptor *) req->handle;

    SDIO_LOG(SDIO_CLOSE, "%s: Close\n",
             __FUNCTION__);

    d->inUse = 0;

    return rv;
}


/*
 * SDIO_Ioctl
 *
 * This is the resource manager ioctl routine.   Most of the
 * sd/sdio api routines end up calling one of these ioctl routines.
 *
 * There is extensive use of copy_from_user/copy_to_user.  In the
 * first devkit all of the IOS code will run in one address space, and
 * so these routines will be stubs.
 *
 * In the second and subsequent devkit releases, a resource amanger
 * and the user processes which call it will have their own address
 * spaces, and so the resource manager will have to map user pages.
 * The implementation of mapping user pages will be buried in
 * copy_from_user/copy_to_user.
 *
 * Our ioctl routine calls out to the driver code, so I have added 
 * temporary prototypes for that code.
 */
IOSError
SDIO_Ioctl(IOSResourceRequest *req)
{
    int status, value, rca;
    int *ret;
    u32 cmd, input,inLen;
    IOSError rv = IOS_ERROR_OK;
    IOSResourceIoctl *arg = &req->args.ioctl;

    /*
     * typedef struct {
     *     u32 cmd;
     *     u8 *inPtr;
     *     u32 inLen;
     *     u8 *outPtr;
     *     u32 outLen;
     * } IOSResourceIoctl;
    */

    cmd = arg->cmd;
    input = (u32)arg->inPtr;
    inLen = (u32)arg->inLen;

    switch (arg->cmd) {
    case SD_RESET:
			if (inLen!=sizeof(unsigned int))
			{
				printf("IOCTL SIZE ERROR expected %d, received %d \n",sizeof(unsigned int),inLen);
				return IOS_ERROR_INVALID;
			}    
	        rca  = sdio_ser_ioctl(NULL, NULL, cmd, input);
	        if (rca < 0) {
	            printf ("ioctl");
	            printf("%s: Bad ioctl %s rcs 0x%x\n", 
	                     __FUNCTION__, sdio_ioctl_str[cmd&0xFF], rca);
	            return IOS_ERROR_ACCESS;
	        }
	        // printf("Done RCA=%x\n",rca);
	        ret = (u32 *)arg->outPtr;
	        if (ret) {
	            *ret = rca;
	        }
	        break;

    case SD_IOWREG:
    case SD_IOWCREG:
    case SD_IORMCREG:
    case SD_IOWMCREG:
			if (inLen!=sizeof(reg_op_t))
			{
				printf("IOCTL SIZE ERROR expected %d, received %d \n",sizeof(reg_op_t),inLen);
				return IOS_ERROR_INVALID;
			}
    case SD_DEBUG_LEVEL:    		
    case SD_CINTEN:
    case SD_CINTDIS:
	        status = sdio_ser_ioctl(NULL, NULL, cmd, input);
	        if (status < 0) {
	            printf ("sdio_ioctl_str[cmd&0xFF]");
	            printf( "%s: Bad ioctl %s status 0x%x\n", 
	                     __FUNCTION__, sdio_ioctl_str[cmd&0xFF], status);
	            return IOS_ERROR_ACCESS;
	        }
	        break;    
    case SD_CMD:
    case SD_READ_DATA:
    case SD_WRITE_DATA:
			if (inLen!=sizeof(cmd_t))
			{
				printf("IOCTL SIZE ERROR expected %d, received %d \n",sizeof(reg_op_t),inLen);
				return IOS_ERROR_INVALID;
			}
	        status = sdio_ser_ioctl(NULL, NULL, cmd, input);
	        if (status < 0) {
	            printf ("sdio_ioctl_str[cmd&0xFF]");
	            printf( "%s: Bad ioctl %s status 0x%x\n", 
	                     __FUNCTION__, sdio_ioctl_str[cmd&0xFF], status);
	            return IOS_ERROR_ACCESS;
	        }
	        break;
	        
    case SD_IORREG:
    case SD_IORCREG:
			if (inLen!=sizeof(reg_op_t))
			{
				printf("IOCTL SIZE ERROR expected %d, received %d \n",sizeof(reg_op_t),inLen);
				return IOS_ERROR_INVALID;
			}    
    case SD_GET_STATUS:
	        value = sdio_ser_ioctl(NULL, NULL, cmd, input);
	        if (value < 0) {
	            printf ("sdio_ioctl_str[cmd&0xFF]");
	            printf( "%s: Bad ioctl %s value 0x%x\n",
	                     __FUNCTION__, sdio_ioctl_str[cmd&0xFF], value);
	            return IOS_ERROR_ACCESS;
	        }
	        //printf("   Read Register Returns:0x%x to ptr:0x%x\n",value,arg->outPtr);
	        ret = (u32 *)arg->outPtr;
	        if (ret) {
	            *ret = value;
	        }
	        break;

    default:
	        rv = IOS_ERROR_INVALID;
	        break;
    }

    return rv;
}

#define RMDEBUG 0

void sdioRmThread(u32 arg)
{
    IOSError rv; 
    IOSMessage msg; 
    /* Main dispatch loop */
    while (1) 
    {
    	rv = IOS_ERROR_INVALID;
    	
        /* Receive a command */
        SDIO_LOG(SDIO_INIT, "%s: Waiting for command id:%d mq:%d\n",
                 __FUNCTION__,IOS_GetThreadId(),sdrmQid);
                 
        if (IOS_ReceiveMessage(sdrmQid, &msg, IOS_MESSAGE_BLOCK) != IOS_ERROR_OK) 
        {
            SDIO_LOG(SDIO_ERROR, "%s: IOS_ReceiveMessage ERROR\n",
                     __FUNCTION__);
            break;
        }
        SDIO_LOG(SDIO_INIT,	"%s: Received resource request: %08x\n", 
                 __FUNCTION__, msg);

        /* Dispatch command */
        IOSResourceRequest *req = (IOSResourceRequest *) msg;
        switch (req->cmd) 
        {
        case IOS_OPEN:
            rv = SDIO_Open(req);
            break;
        case IOS_CLOSE:
            rv = SDIO_Close(req);
            break;
        case IOS_IOCTL:
            rv = SDIO_Ioctl(req);
            break;
        default:
        	
            SDIO_LOG(SDIO_ERROR, "%s: bad request command %d\n",
                     __FUNCTION__, req->cmd);
            break;
        }
        #if RMDEBUG
			//printf("%s RESPOND\n",__FUNCTION__);
	        IOS_SendMessage(sdrmQidr, msg, IOS_MESSAGE_NOBLOCK); 
        #else       
	        IOS_ResourceReply(req, rv);
        #endif
        }

}

u8				heapArea[32 * 1024] __attribute__((aligned(32)));
IOSHeapId       sdheapId;

/* ----------------------------------------------------------------- */

void
initSdioMemAlloc(void)
{
    sdheapId = IOS_CreateHeap(heapArea, sizeof(heapArea));
    if (sdheapId < 0) 
    {
        printf("Bad heapId returned from IOS_CreateHeap");
    }
    printf("sdheapId = %u\n", sdheapId);
}

IOSError sdio_rm(u32 arg)
{
	IOSError rv;
	
	/* Creating heap for SDIO */	
	initSdioMemAlloc();
	
    /* Create a message queue */
    SDIO_LOG(SDIO_INIT, "%s: Create message queue\n",
             __FUNCTION__);
    if ((sdrmQid = IOS_CreateMessageQueue(sdrmQ, sizeof(sdrmQ))) < 0) 
    {
        rv = sdrmQid;
        SDIO_LOG(SDIO_ERROR, "%s: IOS_CreateMessageQueue\n",
                 __FUNCTION__);
        return rv;
    }

    /* Register the message queue with the kernel */
    if ((rv = IOS_RegisterResourceManager("/dev/sdio", sdrmQid)) 
        != IOS_ERROR_OK) 
    {
        SDIO_LOG(SDIO_ERROR, "%s: IOS_RegisterResourceManager\n",
                 __FUNCTION__);
        return rv;
    }
  
  /* add reponse message queue, since this rm does not seem to support reply according to doc */
  
    if ((sdrmQidr = IOS_CreateMessageQueue(sdrmQr, sizeof(sdrmQr))) < 0) 
    {
        rv = sdrmQid;
        SDIO_LOG(SDIO_ERROR, "%s: IOS_CreateMessageQueue\n",
                 __FUNCTION__);
        return rv;
    }
    printf("QueueId = %d\n",sdrmQid);

	// --- async / sync RM ---
    #if 1
    {
		u32 pri = IOS_GetThreadPriority(0)-1;
		u32 id;    	
	    SDIO_LOG(SDIO_INIT, "%s: Create thread. pri:%d\n",__FUNCTION__,pri);
	    id = IOS_CreateThread(	(IOSEntryProc)sdioRmThread, 
	    						(void*)200, 
	    						stacksdio+SDRM_STACK_SIZE, SDRM_STACK_SIZE, 
	    						pri, 
	    						IOS_THREAD_CREATE_DETACHED);
	    SDIO_LOG(SDIO_INIT, "%s: Starting thread. id:%d mq:%d\n",__FUNCTION__,id,sdrmQid);
		IOS_StartThread(id);
    }
	#else
		sdioRmThread(0);
	#endif
	
	SDIO_LOG(SDIO_INIT, "%s: Done returning.\n",__FUNCTION__);
    return 0;
}

/* eof */
