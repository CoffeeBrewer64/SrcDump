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

#ident "$Id: sdio_api.c,v 1.7 2006/03/20 19:21:41 gbarnard Exp $"

/*
 * System includes
 */
#ifdef LINUX
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <iostypes.h>
	#include <sys/types.h>
	#include <linux/ioctl.h>
	#include <sdio_api.h>
	#include <sd_ioctl.h>
	#include "sdio_test.h"	
#else
	#include <ios.h>
	#ifdef VERSA
		#include <versaios.h>
	#endif
	#include <ioslibc.h>

	#include "sd.h"
	#include "sd_card.h"
	#include "sd_host.h"
	#include "sd_ioctl.h"
	#include "sdio_rm.h"
#endif

#include "sdio_api.h"
#include "sdio_test.h"

static bool open_sdio (SDDevHandle fd);
static bool valid_sdio (SDDevHandle fd);
static bool isopen_sdio (SDDevHandle fd);
static bool read_card_reg (SDDevHandle fd, u32 addr, u32 size, u32 *data);
static bool write_card_reg (SDDevHandle fd, u32 addr, u32 size, u32 data);
static bool set_bus_width(SDDevHandle fd, u32 buswidth);

/*
 * IOS SDIO API code.  For individual routine's comments, please refer
 * to sdio_api.h.
 */

SDDevHandle DevHandles[MAX_SLOTS][MAX_FUNCS];
int debug_level;

#define ZeroHandle(fd) (DevHandles[fd->SDDevSlot][0])


#ifndef LINUX
	extern IOSHeapId       sdheapId;
	#define malloc(size) IOS_Alloc(sdheapId,size)
	#define free(ptr) 	IOS_Free(sdheapId,ptr)	
	/*
	void* malloc(size_t size)
	{
		return IOS_Alloc(0,size); 
	}		
	
	void free(void *ptr)
	{
		IOS_Free(0,ptr);
	}
	*/
	
	#define fprintf(file, format, ...) printf(format,__VA_ARGS__)
	#define perror(s) printf(s)
	#define strlen(s) strnlen(s,40)

#endif
//================================================================

extern IOSMessageQueueId 	sdrmQid;	// froward queue
extern IOSMessageQueueId 	sdrmQidr;	// return queue - debug only

#define RMDEBUG 0	// debug only

// ======= Open SDIO Driver via Resource Manager =======
IOSError  ISDIO_Open(char *fn, u32 flags, int *fd)
{
	#if RMDEBUG
		if (fd) *fd = sdrmQid;	//async debug version
		printf("ISDIO_Open(path = %s): rmQid = %d\n\n", fn, *fd);
	#else
		IOSFd ifd = IOS_Open(fn, 0);
		printf("ISDIO_Open(path = %s): handle = 0x%X\n\n", fn, ifd);
		if (ifd<0)
		{
			printf("Could not open %s\n",fn);
			return SD_STATUS_UNSUCCESSFUL;
		}
		if (fd) *fd = ifd;
	#endif
	
	return IOS_ERROR_OK;
}

// ======= Access SDIO Driver via Resource Manager =======
IOSError  ISDIO_Ioctl(	int fd, s32 cmd, 
						void *input,	u32 input_bytes, 
						void *output,	u32 output_bytes)
{
	#if RMDEBUG
		// === async debug version ===
		// --- request resource action ---
		IOSResourceRequest req;
		IOSMessage msg;	
		IOSError rc;	
			// --- sending an ioctl type request ---
			IOSResourceIoctl ioctl;	
			
			ioctl.cmd = cmd;
			ioctl.inLen = input_bytes;
			ioctl.inPtr = (u8*)input; // &slot;
			ioctl.outLen = output_bytes;
			ioctl.outPtr = (u8*)output;
		
		req.cmd = IOS_IOCTL;
		req.args.ioctl = ioctl; 
	
		// --- assemble message ---
		{
			//printf("ISDIO_Ioctl -> SDIO RM mq:%d\n",sdrmQid);
			msg = (IOSMessage)&req;
			IOS_SendMessage(sdrmQid, msg, IOS_MESSAGE_NOBLOCK);
			// --- wait for done ---
			rc = IOS_ReceiveMessage(sdrmQidr, &msg, IOS_MESSAGE_BLOCK);
			//printf("ISDIO_Ioctl <- Done Reply\n");
		}
		return rc;
	#else
		// === proper IOS version ===
		return IOS_Ioctl(fd, cmd, input, input_bytes, output, output_bytes);
	#endif
	

}       

#define IOSCid u32 
                     
IOSError  ISDIO_Close(IOSCid fd)
{
	IOSError rv;
	rv = IOS_Close(fd);
	return rv;
}

IOSError  ISDIO_FindDevice(int *min)
{
	*min = 0;
	return 0;
}

IOSError  ISDIO_RegisterResourceManager(IOSCid fd, IOSMessageQueueId mq)
{
	return 0;
}                                                


//==================================================================		
/*
 * ISD_AttachDevice
 */
IOSError ISD_AttachDevice(SDDevConfig *devCfg, SDDevHandle *fd)
{
    SDDevHandle Handle, Handle0;

    if (devCfg->SDDevSlot >= MAX_SLOTS) {
        if (fd) {
            *fd = (SDDevHandle)0;
        }
        return IOS_ERROR_SDIO_ERR;
    }

    if (devCfg->SDDevFunc >= MAX_FUNCS) {
        if (fd) {
            *fd = (SDDevHandle)0;
        }
        return IOS_ERROR_SDIO_ERR;
    }

	Handle = DevHandles[devCfg->SDDevSlot][devCfg->SDDevFunc];
	if (!Handle) 
	{
		printf("Allocating memory for slot=%d func=%d\n",devCfg->SDDevSlot,devCfg->SDDevFunc);
	    Handle = (SDDevHandle)malloc(sizeof(*Handle));
	    if (!Handle) {
	        perror (__FUNCTION__);
	        if (fd) {
	            *fd = (SDDevHandle)0;
	        }
	        return IOS_ERROR_SDIO_ERR;
	    }
	    memset (Handle, 0, sizeof(*Handle));
	    Handle->SDDevFd = -1;
	}

    /*
     * If this is an open for a function, we need to copy some
     * information from the zero function handle.
     */
    if (devCfg->SDDevFunc != 0) {
    	printf("Handling a non-zero function\n");
        Handle0 = DevHandles[devCfg->SDDevSlot][0];
        if (!isopen_sdio (Handle0)) {
            fprintf (stderr, "%s: Zero handle must be open\n",
                     __FUNCTION__);
            return IOS_ERROR_SDIO_ERR;
        }
        Handle->SDDevRca = Handle0->SDDevRca;
    }
    else
    {
    	printf("Handling Zero (open) function\n");
    }

    Handle->SDDevSlot = devCfg->SDDevSlot;
    Handle->SDDevFunc = devCfg->SDDevFunc;
    if (!open_sdio (Handle)) {
        fprintf (stderr, "%s: bad device open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

	DevHandles[devCfg->SDDevSlot][devCfg->SDDevFunc] = Handle;
	printf("Now assigning handle %x %x to fd=%x\n",DevHandles[devCfg->SDDevSlot][devCfg->SDDevFunc],Handle,fd);
    if (fd) 
    {
    	
        *fd = Handle;
    }

    if (debug_level >= DEBUG_CHATTY)
        fprintf (stderr, "%s: attach succeeded\n",
                 __FUNCTION__);

    return IOS_ERROR_OK;
}

/*
 * ISD_DetachDevice
 */
IOSError ISD_DetachDevice(SDDevHandle fd)
{

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (fd->SDDevFd > 0) {
        ISDIO_Close(fd->SDDevFd);
    }

    DevHandles[fd->SDDevSlot][fd->SDDevFunc] = NULL;

    free (fd);

    if (debug_level >= DEBUG_CHATTY)
        fprintf (stderr, "%s: detach succeeded\n",
                 __FUNCTION__);

    return IOS_ERROR_OK;
}

/*
 * ISD_ResetDevice
 */
IOSError ISD_ResetDevice(SDDevHandle fd)
{
    IOSError status;
    int rca;

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    status = ISDIO_Ioctl(fd->SDDevFd, SD_RESET, &fd->SDDevSlot, 
                         0x4, &rca, 0x4);
    if (status != IOS_ERROR_OK) {
        perror ("SD_RESET");
        fprintf (stderr, "%s: Bad ioctl 0x%x\n", 
                 __FUNCTION__, status);
        return IOS_ERROR_SDIO_ERR;
    }
    fd->SDDevRca = rca;

    if (debug_level >= DEBUG_CHATTY)
        fprintf (stderr, "%s: reset succeeded, rca 0x%x\n",
                 __FUNCTION__, rca);

    return IOS_ERROR_OK;
}

/*
 * ISD_EnableDevice
 */
IOSError ISD_EnableDevice(SDDevHandle fd, u32 funcId)
{
    u32 new;
    u8 bit = (1<<funcId);
    
    read_card_reg (fd, 3, 1, &new);
    //printf("<Enable> Function (%x) Ready Status:0x%02X\n",bit,new);
    
    /* If function is not ready */
    if ((new&&bit)==0)
    {
		/* addr = 2 size = 1 */
	    if (!write_card_reg (fd, 2, 1, bit)) {
	        fprintf (stderr, "%s: bad write_card_reg\n",
	                 __FUNCTION__);
	        return IOS_ERROR_SDIO_ERR;
	    }
	
		
	    if (!read_card_reg (fd, 3, 1, &new)) {
	        fprintf (stderr, "%s: bad read_card_reg\n",
	                 __FUNCTION__);
	        return IOS_ERROR_SDIO_ERR;
	    }
		printf("<ReEnbl> Function (%x) Ready Status:0x%02X\n",bit,new);
	
	    if (debug_level >= DEBUG_CHATTY)
	        printf ("%s: new value 0x%x\n",
	                __FUNCTION__, new);
    }
    return IOS_ERROR_OK;
}

/*
 * ISD_DisableDevice
 */
IOSError ISD_DisableDevice(SDDevHandle fd, u32 funcId)
{
    u32 old, new;

    if (!read_card_reg (fd, 2, 1, &old)) {
        fprintf (stderr, "%s: bad read_card_reg\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    new = old & ~(1 << funcId);

    if (!write_card_reg (fd, 2, 1, new)) {
        fprintf (stderr, "%s: bad write_card_reg\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    return IOS_ERROR_OK;
}

/*
 * ISD_GetDeviceStatus
 */
IOSError ISD_GetDeviceStatus(SDDevHandle fd, u32 *devStatus)
{
    IOSError status;
    int device_status;

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    status = ISDIO_Ioctl(fd->SDDevFd, SD_GET_STATUS, &fd->SDDevSlot,
                         0x0, &device_status, 0x0);
    if (status != IOS_ERROR_OK) {
        perror ("SD_GET_STATUS");
        fprintf (stderr, "%s: Bad ioctl 0x%x\n", 
                 __FUNCTION__, device_status);
        return IOS_ERROR_SDIO_ERR;
    }

    if (devStatus) {
        *devStatus = device_status;
    }

    if (debug_level >= DEBUG_CHATTY)
        fprintf (stderr, "%s: get status succeeded\n",
                 __FUNCTION__);

    return IOS_ERROR_OK;
}

/*
 * ISD_SetDeviceState
 */
IOSError ISD_SetDeviceState(SDDevHandle fd, u8 state)
{
    IOSError status = IOS_ERROR_OK;

    return status;
}

/*
 * ISD_GetDeviceRegisterInfo
 */
IOSError ISD_GetDeviceRegisterInfo(SDDevHandle fd, u32 regType, 
                                   u8 *regBuf, u32 bufLen)
{
    IOSError status = IOS_ERROR_OK;
    int ocr;

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    switch (regType) {
    case SD_REG_CID:
        /* 
         * No such register on sdio only cards.
         * See SDIO Specification sec 4.2.
         */
        status = IOS_ERROR_INVALID;
        break;
    case SD_REG_CSD:
        /* 
         * No such register on sdio only cards.
         * See SDIO Specification sec 4.2.
         */
        status = IOS_ERROR_INVALID;
        break;
    case SD_REG_SCR:
        /* 
         * No such register on sdio only cards.
         * See SDIO Specification sec 4.2.
         */
        status = IOS_ERROR_INVALID;
        break;
    case SD_REG_OCR:
        status = ISDIO_Ioctl(fd->SDDevFd, SD_GET_OCR, &fd->SDDevSlot, 
                         0x0, &ocr, 0x0);
        if (status != IOS_ERROR_OK) {
            perror ("SD_GET_OCR");
            fprintf (stderr, "%s: Bad ioctl 0x%x\n", 
                     __FUNCTION__, status);
            return IOS_ERROR_SDIO_ERR;
        }
        if (regBuf) {
            *(int *)regBuf = ocr;
        }
        break;
    case SD_REG_RCA:
        if (regBuf) {
            *regBuf = (u8)fd->SDDevRca;
        }
        break;
    default:
        status = IOS_ERROR_INVALID;
        break;
    }

    return status;
}

/*
 * ISD_ReadCCCR
 */
IOSError ISD_ReadCCCR(SDDevHandle fd, u32 regAddr, u8 *regData)
{
    u32 reg_data;

    if (!read_card_reg(fd, regAddr, 1, &reg_data)) {
        fprintf (stderr, "%s: bad read_card_reg\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (debug_level >= DEBUG_CHATTY)
        printf ("%s: reg addr 0x%x data 0x%x\n", 
                __FUNCTION__, regAddr, reg_data);

    if (regData) {
        *regData = reg_data;
    }

    return IOS_ERROR_OK;
}

/*
 * ISD_WriteCCCR
 */
IOSError ISD_WriteCCCR(SDDevHandle fd, u32 regAddr, u8 regData)
{
    u32 reg_data;

    if (!write_card_reg(fd, regAddr, 1, regData)) {
        fprintf (stderr, "%s: bad write_card_reg\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!read_card_reg(fd, regAddr, 1, &reg_data)) {
        fprintf (stderr, "%s: bad read_card_reg\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (debug_level >= DEBUG_CHATTY)
        printf ("%s: reg addr 0x%x data 0x%x new 0x%x\n", 
                __FUNCTION__, regAddr, regData, reg_data);

    return IOS_ERROR_OK;
}

/*
 * ISD_ReadFBR
 */
IOSError ISD_ReadFBR(SDDevHandle fd, u32 funcId, u32 regAddr, u8 *regData)
{
    u32 reg_data;
    
    if (!read_card_reg(fd, regAddr, 1, &reg_data)) {
        fprintf (stderr, "%s: bad read_card_reg\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (debug_level >= DEBUG_CHATTY)
        printf ("%s: reg addr 0x%x data 0x%x\n", 
                __FUNCTION__, regAddr, reg_data);

    if (regData) {
        *regData = reg_data;
    }


    return IOS_ERROR_OK;
}

/*
 * ISD_ReadCIS
 */
IOSError ISD_ReadCIS(SDDevHandle fd, u32 funcId, u8 *regData, u32 length)
{
    int i, j, k, next;
    unsigned int code, offset, data;

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    i = 0x1000 * funcId;
    k = 0;
    do {
        if (!read_card_reg(fd, i, 1, &code)) {
            fprintf (stderr, "%s: bad read_card_reg\n",
                     __FUNCTION__);
            return IOS_ERROR_SDIO_ERR;
        }
        i++; k++;
        *regData++ = (code & 0xff);
        if (debug_level >= DEBUG_CHATTY)
        	printf("\nCIS[%02d] = 0x%02x ",k,(code&0xff));
        
        if (!read_card_reg(fd, i, 1, &offset)) 
        {
            fprintf (stderr, "%s: bad read_card_reg\n",
                     __FUNCTION__);
            return IOS_ERROR_SDIO_ERR;
        }
        if (debug_level >= DEBUG_CHATTY)
        	printf("(0x%02x) ",(offset&0xff));
        
        if ((code == 0xff) || (code == 0x0)) 
        {
            break;
        }
        
        i++; k++;
        *regData++ = (offset & 0xff);
        next = i + offset;
        for (j = 0; i < next; i++, j++) 
        {
            if (!read_card_reg(fd, i, 1,&data))
            {
                fprintf (stderr, "%s: bad read_card_reg\n",
                         __FUNCTION__);
                return IOS_ERROR_SDIO_ERR;
            }
            *regData = (data & 0xFF);
            if (debug_level >= DEBUG_CHATTY)
            	printf("0x%02x ",(*regData));
            regData++;
            k++;
        }
    } 
    while ((code != 0xff) && (k < length));
    
    if (debug_level >= DEBUG_CHATTY)
		printf("\n");
    return IOS_ERROR_OK;
}

/*
 * ISD_QueryDeviceIntr
 */
IOSError ISD_QueryDeviceIntr(SDDevHandle fd, u32 funcId, u8 *intrStatus)
{
    IOSError status;
    int reg = 0x5; /* interrupt pending register */

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    status = ISD_ReadCCCR(DevHandles[fd->SDDevSlot][fd->SDDevFunc], reg, 
                             intrStatus);
    if (status != IOS_ERROR_OK) {
        fprintf (stderr, "%s: bad read cccr register %d\n",
                 __FUNCTION__, reg);
        return IOS_ERROR_SDIO_ERR;
    }


    return IOS_ERROR_OK;
}

/*
 * ISD_EnableDeviceIntr
 */
IOSError ISD_EnableDeviceIntr(SDDevHandle fd)
{
    IOSError status;
    int slot;

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    slot = fd->SDDevSlot;

    status = ISDIO_Ioctl(fd->SDDevFd, SD_CINTEN, &slot,
                         0x0, NULL, 0x0);
    if (status != IOS_ERROR_OK) {
        perror ("SD_CINTEN");
        printf ("%s: Bad ioctl 0x%x\n", 
                 __FUNCTION__, status);
        return IOS_ERROR_OK;
    }

    if (debug_level >= DEBUG_CHATTY)
        printf ("%s: status 0x%x\n",
                __FUNCTION__, status);

    return IOS_ERROR_OK;
}

/*
 * ISD_DisableDeviceIntr
 */
IOSError ISD_DisableDeviceIntr(SDDevHandle fd)
{
    IOSError status;
    int slot;

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    slot = fd->SDDevSlot;

    status = ISDIO_Ioctl(fd->SDDevFd, SD_CINTDIS, &slot,
                         0x0, NULL, 0x0);
    if (status != IOS_ERROR_OK) {
        perror ("SD_CINTDIS");
        printf ("%s: Bad ioctl 0x%x\n", 
                 __FUNCTION__, status);
        return IOS_ERROR_OK;
    }

    if (debug_level >= DEBUG_CHATTY)
        printf ("%s: status 0x%x\n",
                __FUNCTION__, status);

    return IOS_ERROR_OK;
}

/*
 * ISD_RegisterDeviceIntrHandler
 */
IOSError ISD_RegisterDeviceIntrHandler(SDDevHandle fd, 
                               SDCallbackFunc handler, void *arg)
{
    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    fd->SDDevInterruptHandler = handler;

    return IOS_ERROR_OK;
}

/*
 * ISD_UnregisterDeviceIntrHandler
 */
IOSError ISD_UnregisterDeviceIntrHandler(SDDevHandle fd)
{
    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    fd->SDDevInterruptHandler = 0;

    return IOS_ERROR_OK;
}

/*
 * ISD_RegisterDeviceRemovalHandler
 */
IOSError ISD_RegisterDeviceRemovalHandler(SDDevHandle fd, 
                                       SDCallbackFunc handler, void *arg)
{
    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    fd->SDDevRemoveHandler = handler;

    return IOS_ERROR_OK;
}

/*
 * ISD_UnregisterDeviceRemovalHandler
 */
IOSError ISD_UnregisterDeviceRemovalHandler(SDDevHandle fd)
{
    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    fd->SDDevRemoveHandler = NULL;

    return IOS_ERROR_OK;
}

/*
 * ISD_RegisterDeviceErrorHandler
 */
IOSError ISD_RegisterDeviceErrorHandler(SDDevHandle fd, 
                                   SDCallbackFunc handler, void *arg)
{
    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    fd->SDDevErrorHandler = handler;

    return IOS_ERROR_OK;
}

/*
 * ISD_UnregisterDeviceErrorHandler
 */
IOSError ISD_UnregisterDeviceErrorHandler(SDDevHandle fd)
{
    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    fd->SDDevErrorHandler = NULL;

    return IOS_ERROR_OK;
}

/*
 * ISD_ReadReg
 */
IOSError ISD_ReadReg(SDDevHandle fd, u32 addr, u32 *data)
{
    u32 value = 0;

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!read_card_reg (fd, addr, 1, &value)) {
        fprintf (stderr, "%s: bad read_card_reg\n",
                 __FUNCTION__);
        return false;
    }

    if (data) {
        *data = value;
    }

    return IOS_ERROR_OK;
}

/*
 * ISD_WriteReg
 */
IOSError ISD_WriteReg(SDDevHandle fd, u32 addr, u32 data)
{

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!write_card_reg (fd, addr, 1, data)) {
        fprintf (stderr, "%s: bad write_card_reg\n",
                 __FUNCTION__);
    }

    if (debug_level > DEBUG_ERR)
        printf ("%s: slot 0x%x reg 0x%x width x%x data 0x%x\n",
                __FUNCTION__, fd->SDDevSlot, addr, 1, data);

    return IOS_ERROR_OK;
}

/*
 * ISD_ReadMultiReg
 */
IOSError ISD_ReadMultiReg(SDDevHandle fd, u32 addr, 
                                 u32 count, u32 incrFlag, u32 *data, u32 dma)
{
    IOSError status;
    reg_op_t reg_op;
    SDDevHandle fd0;

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    fd0 = ZeroHandle(fd);

    if (!valid_sdio(fd0)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd0)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

/*
    if (!set_bus_width (fd0, 1)) {
        fprintf (stderr, "%s: bad set bus width %d\n",
                __FUNCTION__, 1);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!write_card_reg (fd0, 0x0110, 1, count & 0xff)) {
        fprintf (stderr, "%s: bad card reg write %x\n",
                __FUNCTION__, 0x0110);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!write_card_reg (fd0, 0x0111, 1, (count >> 8) & 0xff)) {
        fprintf (stderr, "%s: bad card reg write %x\n",
                __FUNCTION__, 0x0110);
        return IOS_ERROR_SDIO_ERR;
    }
*/
    if (data) {
        memset (data, 0xe, count);
    }
    memset (&reg_op, 0, sizeof(reg_op));
    reg_op.dev = fd->SDDevSlot;
    reg_op.reg = addr;
    reg_op.rw = REG_READ_M;
    reg_op.blk_size = count;
    reg_op.blk_num = 0;
    reg_op.dma = dma;
    reg_op.busy = 0;
    reg_op.function = fd->SDDevFunc;
    reg_op.buffer = (unsigned int *)data;

    status = ISDIO_Ioctl(fd->SDDevFd, SD_IORMCREG, &reg_op,
                         sizeof(reg_op), NULL, 0x0);
    if (status != IOS_ERROR_OK) {
        perror ("SD_IORMCREG");
        printf ("%s: Bad ioctl 0x%x\n", 
                 __FUNCTION__, status);
        return IOS_ERROR_OK;
    }

	/*
    if (!set_bus_width (fd0, 0)) {
        fprintf (stderr, "%s: bad set bus width %d\n",
                __FUNCTION__, 0);
        return IOS_ERROR_SDIO_ERR;
    }
    */

	/*
    if (debug_level > DEBUG_ERR) {
        mem_dump ((char *)data, count);
        printf ("%s: slot 0x%x reg 0x%x width x%x data 0x%x\n",
                __FUNCTION__, fd->SDDevSlot, addr, count, (u32)data);
    }
	*/
	
    return IOS_ERROR_OK;
}

/*
 * ISD_WriteMultiReg
 */
IOSError ISD_WriteMultiReg(SDDevHandle fd, u32 addr, 
                           u32 count, u32 incrFlag, u32 *data, u32 dma)
{
    IOSError status;
    reg_op_t reg_op;
    SDDevHandle fd0;
    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    fd0 = ZeroHandle(fd);

    if (!valid_sdio(fd0)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd0)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }
/*
    if (!set_bus_width (fd0, 1)) {
        fprintf (stderr, "%s: bad set bus width %d\n",
                __FUNCTION__, 1);
        return IOS_ERROR_SDIO_ERR;
    }
*/

	/* write fn!=0 block size */
/*
    if (!write_card_reg (fd0, 0x0110, 1, count & 0xff)) {
        fprintf (stderr, "%s: bad card reg write %x\n",
                __FUNCTION__, 0x0110);
        return IOS_ERROR_SDIO_ERR;
    }
    if (!write_card_reg (fd0, 0x0111, 1, (count >> 8) & 0xff)) {
        fprintf (stderr, "%s: bad card reg write %x\n",
                __FUNCTION__, 0x0110);
        return IOS_ERROR_SDIO_ERR;
    }
*/

    memset (&reg_op, 0, sizeof(reg_op));
    reg_op.dev = fd->SDDevSlot;
    reg_op.reg = addr;
    reg_op.rw = REG_WRITE_M;
    reg_op.blk_size = count;
    reg_op.blk_num = 0;
    reg_op.dma = dma;
    reg_op.busy = 0;
    reg_op.function = fd->SDDevFunc;
    reg_op.buffer = (unsigned int *)data;

    status = ISDIO_Ioctl(fd->SDDevFd, SD_IOWMCREG, &reg_op,
                         sizeof(reg_op), NULL, 0x0);
    if (status != IOS_ERROR_OK) {
        perror ("SD_IOWMCREG");
        printf ("%s: Bad ioctl 0x%x\n", 
                 __FUNCTION__, status);
        return IOS_ERROR_OK;
    }

	/*
    if (!set_bus_width (fd0, 0)) {
        fprintf (stderr, "%s: bad set bus width %d\n",
                __FUNCTION__, 0);
        return IOS_ERROR_SDIO_ERR;
    }
    */

    if (debug_level >= DEBUG_CHATTY)
        printf ("%s: status 0x%x\n",
                __FUNCTION__, status);

    return IOS_ERROR_OK;
}

/*
 * ISD_GetHCRegister
 */
IOSError 
ISD_GetHCRegister(SDDevHandle fd, u32 addr, u32 *data, u32 size)
{
    int value = -1;
    int status = -1;
    reg_op_t reg_op;

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    memset (&reg_op, 0, sizeof(reg_op));
    reg_op.dev = fd->SDDevSlot;
    reg_op.reg = addr;
    reg_op.rw = REG_READ;
    reg_op.width = size;
    reg_op.value = 0;

    status = ISDIO_Ioctl(fd->SDDevFd, SD_IORREG, &reg_op,
                        sizeof(reg_op), &value, 0x0);
    if (status) {
        perror ("SD_IORREG");
        return IOS_ERROR_SDIO_ERR;
    }

    if (debug_level >= DEBUG_CHATTY)
        fprintf (stderr,
                 "read host reg: slot %d reg 0x%x width %d value 0x%x\n",
                 fd->SDDevSlot, addr, size, value);

    if (data) {
        *data = value;
    }

    return IOS_ERROR_OK;
}

/*
 * ISD_SetHCRegister
 */
IOSError 
ISD_SetHCRegister(SDDevHandle fd, u32 addr, u32 *data, u32 size)
{
    int status = -1;
    reg_op_t reg_op;

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    memset (&reg_op, 0, sizeof(reg_op));
    reg_op.dev = fd->SDDevSlot;
    reg_op.reg = addr;
    reg_op.rw = REG_WRITE;
    reg_op.width = size;
    reg_op.value = *data;

    status = ISDIO_Ioctl(fd->SDDevFd, SD_IOWREG, &reg_op,
                         0x0, NULL, 0x0);
    if (status < 0) {
        perror ("SD_IOWREG");
        return IOS_ERROR_SDIO_ERR;
    }

    if (debug_level >= DEBUG_CHATTY)
        fprintf (stderr,
                 "write host reg: slot %d reg 0x%x width x%x data 0x%x status 0x%x\n",
                 fd->SDDevSlot, addr, size, *data, status);


    return IOS_ERROR_OK;
}

/*
 * ISD_SetBusWidth
 */
IOSError 
ISD_SetBusWidth (SDDevHandle fd, u32 *busWidth)
{
    int width;
    bool status;

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!busWidth) {
        return IOS_ERROR_SDIO_ERR;
    }

    switch (*busWidth) {
    case SD_BW_1BIT:
        width = 0;
        status = set_bus_width(fd, width);
        if (!status) {
            fprintf (stderr, "%s: can't set bus width 1\n",
                     __FUNCTION__);
            return IOS_ERROR_SDIO_ERR;
        }
        break;
    case SD_BW_4BIT:
        width = 1;
        status = set_bus_width(fd, width);
        if (!status) {
            width = 0;
            status = set_bus_width(fd, width);
            if (!status) {
                /*
                 * If we can't set width 1 or 4, return error.
                 */
                fprintf (stderr, "%s: can't set bus width 1\n",
                         __FUNCTION__);
                return IOS_ERROR_SDIO_ERR;
            } else {
                /*
                 * If we can't set width 1 but we can set width 4,
                 * return success, but also return the successful
                 * width.
                 */
                *busWidth = SD_BW_1BIT;
            }
        }
        break;
    default:
        fprintf (stderr, "%s: bad width %d\n",
                 __FUNCTION__, *busWidth);
        return IOS_ERROR_SDIO_ERR;
    }

    return IOS_ERROR_OK;
}

/*
 * ISD_SetBlockLength
 */
IOSError 
ISD_SetBlockLength (SDDevHandle fd, u32 blockLength)
{
    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if ((blockLength < 0) || (blockLength > MAX_BLOCK_SIZE)) {
        blockLength = DEF_BLOCK_SIZE;
    }

    fd->SDBlockLen = blockLength;

    return IOS_ERROR_OK;
}

/*
 * Global utility routines.
 */

/*
 * set_driver_debug
 */
IOSError
set_driver_debug (SDDevHandle fd, int arg)
{
    IOSError status;
    int level = arg;

    if (!valid_sdio(fd)) {
        fprintf (stderr, "%s: invalid handle\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    if (!isopen_sdio(fd)) {
        fprintf (stderr, "%s: device is not open\n",
                 __FUNCTION__);
        return IOS_ERROR_SDIO_ERR;
    }

    status = ISDIO_Ioctl(fd->SDDevFd, SD_DEBUG_LEVEL, &level,
                         0x0, NULL, 0x0);
    if (status != IOS_ERROR_OK) {
        perror ("SD_DEBUG_LEVEL");
        fprintf (stderr, "%s: Bad ioctl 0x%x\n", 
                 __FUNCTION__, status);
        return IOS_ERROR_SDIO_ERR;
    }

    if (debug_level >= DEBUG_CHATTY)
        fprintf (stderr, "%s: status 0x%x\n",
                 __FUNCTION__, status);

    return IOS_ERROR_OK;

}

/*
 * Static utility routines.
 */

/*
 * valid_sdio
 *
 * Validate a passed-in SDIO handle.
 */
bool valid_sdio (SDDevHandle fd)
{
    if (fd==0) {
        fprintf (stderr, "%s: NULL handle\n",
                 __FUNCTION__);
        return false;
    }

    if ((fd->SDDevSlot >= MAX_SLOTS) || (fd->SDDevFunc >= MAX_FUNCS)) {
        fprintf (stderr, "%s: illegal slot 0x%x or function 0x%x\n",
                 __FUNCTION__, fd->SDDevSlot, fd->SDDevFunc);
        return false;
    }

    if (DevHandles[fd->SDDevSlot][fd->SDDevFunc] != fd) {
        fprintf (stderr, "%s: Handle 0x%x does not match\n",
                 __FUNCTION__, (u32)fd);
        return false;
    }

    return true;
}

/*
 * isopen_sdio
 *
 * Check if an sdio device is open.  We assume that valid_sdio() was
 * already called for this handle.
 */
bool isopen_sdio (SDDevHandle fd)
{

    if (!fd) {
        fprintf (stderr, "%s: NULL handle\n",
                 __FUNCTION__);
        return false;
    }

    if (fd->SDDevFd > -1) {
        return true;
    }

    fprintf (stderr, "%s: sdhnd:0x%X, sdfd:0x%x, dev 0x%x function 0x%x not open.\n",
             __FUNCTION__, 
             fd, 
             fd->SDDevFd,
             fd->SDDevSlot, 
             fd->SDDevFunc);

    return false;
}

/*
 * Open an SDIO device and write the driver fd.   Return true/false.
 */
static bool
open_sdio (SDDevHandle fd)
{
    int dev;
    SDDevHandle zero_handle;

    dev = fd->SDDevSlot;

    if ((dev < 0) || (dev >= MAX_SLOTS)) {
        fprintf (stderr, "%s: dev %d not supported\n",
                 __FUNCTION__, dev);
        return false;
    }

	#ifndef LINUX
	switch (dev) 
	{
		case 0: fd->SDDevName = SDIO_DEVICE0; break;
		case 1: fd->SDDevName = SDIO_DEVICE1; break;
		case 2: fd->SDDevName = SDIO_DEVICE2; break;
		case 3: fd->SDDevName = SDIO_DEVICE3; break;
		default:
			fprintf (stderr, "%s: unknown\n", __FUNCTION__);
	        free (fd->SDDevName);
	        fd->SDDevName = NULL;
	        return false;	
	}	
	#else
	{
		int count;
	    int count1 = sprintf (fd->SDDevName, "%s%d",
	             SDIO_DEVICE, dev);
	    if (!fd->SDDevName) {
	        count = strlen(SDIO_DEVICE) + 1 + 1;
	        fd->SDDevName = malloc (count);
	        if (!fd->SDDevName) {
	            perror ("malloc2");
	            return false;
	        }
	    } else {
	        count = strlen(fd->SDDevName);
	    }
	    if (count1 > count) {
	        fprintf (stderr, "%s: sprintf overrun\n", __FUNCTION__);
	        free (fd->SDDevName);
	        fd->SDDevName = NULL;
	        return false;
	    }
	}
    #endif

    if (fd->SDDevFd > -1) {
        //if (debug_level >= DEBUG_ERR)
            fprintf (stderr, "%s: dev %d already open fd %d\n", 
                     __FUNCTION__, dev, fd->SDDevFd);
            return false;
    }

    /*
     * We only do a real open for the 0 function of any card.  For
     * other functions we just check if the zero function is open,
     * fail if not, and copy over the file descriptor from the zero
     * function if it is open.
     */
    // #ifdef LINUX
    if (fd->SDDevFunc == 0) {
    	
    	/* --- Call Resource Manager Open --- */
        ISDIO_Open(fd->SDDevName, 0x0, &fd->SDDevFd);
        
        if (fd->SDDevFd < 0) 
        {
            if (debug_level >= DEBUG_ERR)
                fprintf (stderr, "%s: bad open %s\n",
                         __FUNCTION__, fd->SDDevName);
            perror ("open1");
            free (fd->SDDevName);
            fd->SDDevName = NULL;
            return false;
        }
        //if (debug_level >= DEBUG_CHATTY)
            printf ("%s: fd %x\n",
                    __FUNCTION__, fd->SDDevFd);
    } else {
        zero_handle = ZeroHandle(fd);
        if (!zero_handle) {
            fprintf (stderr, "%s: NULL handle for 0x%x 0x%x\n",
                     __FUNCTION__, fd->SDDevSlot, 0);
            return false;
        }
        if (zero_handle->SDDevFd < 0) {
            fprintf (stderr, "%s: not yet open 0x%x 0x%x\n",
                     __FUNCTION__, fd->SDDevSlot, 0);
            return false;
        }
        fd->SDDevFd = zero_handle->SDDevFd;
    }
    //#endif

    if (debug_level >= DEBUG_CHATTY)
        fprintf (stderr, "%s: opened %s fd %d slot %d function %d\n",
                 __FUNCTION__, 
                 fd->SDDevName, 
                 fd->SDDevFd,
                 fd->SDDevSlot,
                 fd->SDDevFunc);

    return true;


}

// --- CMD52 read byte from SDIO card ---
static bool read_card_reg (SDDevHandle fd, u32 addr, u32 size, u32 *data)
{
    IOSError status;
    reg_op_t reg_op;
    int value = 0;

	if (size!=1)
	{
		printf("%s ERROR Does not support size other than one (%d)\n",__FUNCTION__,size);
		return false;
	}

    memset (&reg_op, 0, sizeof(reg_op));
    reg_op.dev = fd->SDDevSlot;
    reg_op.reg = addr;
    reg_op.rw = REG_READ;
    reg_op.width = size;
    reg_op.function = fd->SDDevFunc;
    reg_op.value = 0;

    status = ISDIO_Ioctl(fd->SDDevFd, SD_IORCREG, &reg_op,
                         sizeof(reg_op), &value, sizeof(value));

    //printf("   (Read Register Got:0x%x to ptr:0x%x)\n",value,&value);
                         
    if (status != IOS_ERROR_OK) {
        perror ("SD_IORCREG");
        fprintf (stderr, 
                 "%s: Bad ioctl 0x%x slot %d func %d reg 0x%x width %d dest 0x%x\n", 
                 __FUNCTION__, status, fd->SDDevSlot, fd->SDDevFunc,
                 addr, size, (u32)data);
        return false;
    } 

    if (debug_level > DEBUG_CHATTY)
        printf ("%s: good ioctl slot %d func %d reg 0x%x size %d value 0x%x dest 0x%x\n",
                __FUNCTION__, fd->SDDevSlot, fd->SDDevFunc, 
                addr, size, value, (u32)data);

    if (data) {
        *data = value;
    }

    return true;
}

// --- CMD52 write byte to SDIO card ---
static bool write_card_reg (SDDevHandle fd, u32 addr, u32 size, u32 data)
{
    IOSError status;
    reg_op_t reg_op;

	if (size!=1)
	{
		printf("%s ERROR Does not support size other than one (%d)\n",__FUNCTION__,size);
		return false;
	}

    memset (&reg_op, 0, sizeof(reg_op));
    reg_op.dev = fd->SDDevSlot;
    reg_op.reg = addr;
    reg_op.rw = REG_READ;
    reg_op.width = size;
    reg_op.function = fd->SDDevFunc;
    reg_op.value = data;

	//#ifdef LINUX
    status = ISDIO_Ioctl(fd->SDDevFd, SD_IOWCREG, &reg_op,
                         sizeof(reg_op), NULL, 0x0);
    //#endif
    if (status != IOS_ERROR_OK) {
        perror ("SD_IOWCREG");
        fprintf (stderr, "%s: Bad ioctl 0x%x reg 0x%x data 0x%x\n", 
                 __FUNCTION__, status, addr, data);
        return false;
    }

    if (debug_level > DEBUG_CHATTY)
        printf ("%s: slot 0x%x reg 0x%x width x%x data 0x%x status 0x%x\n",
                __FUNCTION__, fd->SDDevSlot, addr, size, data, status);

    return true;
}

static bool set_bus_width(SDDevHandle fd, u32 buswidth)
{
    IOSError status;
    u32 bus_data, reg_data;

    if ((buswidth != 0x0) && (buswidth != 0x1)) {
        fprintf (stderr, "%s: bad bus width %d\n",
                __FUNCTION__, buswidth);
        return false;
    }

    bus_data = buswidth << 1;
    if (!write_card_reg (fd, 0x4, 1, 0x0)) {
        fprintf (stderr, "%s: bad card write reg 0x%x data 0x%x width 0x%x\n",
                __FUNCTION__, 0x4, 0x0, buswidth);
        return false;
    }
    if (!write_card_reg (fd, 0x7, 1, bus_data)) {
        fprintf (stderr, "%s: bad card write reg 0x%x data 0x%x\n",
                __FUNCTION__, 0x7, bus_data);
        return false;
    }
    status = ISD_GetHCRegister(fd, 0x28, &reg_data, 1);
    if (status != IOS_ERROR_OK) {
        fprintf (stderr, "%s: bad slot read reg 0x%x\n",
                __FUNCTION__, 0x28);
    }
    reg_data = (reg_data & ~0x2) | (buswidth << 0x1);
    status = ISD_SetHCRegister(fd, 0x28, &reg_data, 1);
    if (status != IOS_ERROR_OK) {
        fprintf (stderr, "%s: bad slot write reg 0x%x data 0x%x\n",
                __FUNCTION__, 0x28, reg_data);
    }
    if (!write_card_reg (fd, 0x4, 1, 0x3)) {
        fprintf (stderr, "%s: bad card write reg 0x%x data 0x%x\n",
                __FUNCTION__, 0x4, 0x3);
        return false;
    }

    return true;
}

/* eof */
