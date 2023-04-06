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

#ident "$Id: sd_api.c,v 1.4 2006/03/20 07:27:26 gbarnard Exp $"

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
	
	#include <sd_api.h>
	#include <sd_ioctl.h>
	
	#include "../../../drivers/sdio/include/sd_host.h"
	
	#ifndef bool
	typedef int bool;
	#define true 1
	#define false 0
	#endif	
#else
	#include <ios.h>
	#include <iostypes.h>
	#include <ioslibc.h>

	#include "sd.h"
	#include "sd_card.h"
	#include "sd_host.h"
	#include "sd_ioctl.h"
	#include "sdio_rm.h"
#endif
	
#include "sd_api.h"
#include "sdio_test.h"


/*
extern bool open_sdio (SDDevHandle fd);

extern bool read_card_reg (SDDevHandle fd, u32 addr, u32 size, u32 *data);
extern bool write_card_reg (SDDevHandle fd, u32 addr, u32 size, u32 data);
*/
extern bool valid_sdio (SDDevHandle fd);
extern bool isopen_sdio (SDDevHandle fd);

/* debug variables */
#define DEBUG_FATAL    0
#define DEBUG_ERR      1
#define DEBUG_CHATTY   2

int debug_level;

/*
 * IOS SD API code.  For individual routine's comments, please refer
 * to sdio_api.h.
 */
#define SDIO_DEVICE "/dev/sdio"

/* Table of pointers to device driver data structures */
SDDevHandle DevHandles[MAX_SLOTS][MAX_FUNCS]={
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}};

#define ZeroHandle(fd) (DevHandles[fd->SDDevSlot][0])

/*
 * IOSError ISD_ProbeCard (u32 slotNo)
 * 
 * Probe to see what card is inserted in slot.
 * Will work for SD and SDIO cards.
 * 
 */
IOSError ISD_ProbeCard (u32 slotNo)
{
	SDDevHandle fd = DevHandles[slotNo][0];
	IOSError status;
	u32 data;
	
	if (fd==NULL) return IOS_ERROR_INVALID;	/* Invalid argument */
	
	status = ISD_ResetDevice(fd);
 	status = ISD_GetDeviceStatus(fd, &data);
                        	
    #if 0
		printf("ISD_ProbeCard(%d): %s\n",slotNo,decode_device_status(data));
	#endif
	
	if (data&SD_CARD_REMOVED) return IOS_ERROR_SD_NOCARD;	/* No card or card type is inserted */
	
	if (data&SD_TYPE_MEMORY) return IOS_ERROR_OK;	/* SD card found */
	 
	return IOS_ERROR_SD_NOCARD;	/* not SD card, or other error */
}

/*
 * ISD_EraseBlocksAsync
 * 
 * Description: 
 * Main function to erase blocks. 
 * All erase function interface through this function.
 * 
 */
IOSError ISD_EraseBlocksAsync (	SDDevHandle fd, 
								u32 blk_start, 
								u32 blk_end, 
								SDCallbackFunc handler, 
								void *arg)
{
    IOSError status;
	u32 regBuf[4];
 	u32 cmd_arg; 						/* block addresses */ 
	   	
	/* (1) Set ersase start block CMD32 */
	cmd_arg = blk_start<<9;
   	status = sd_command (fd, 32, SD_COMMAND, ResponseR1, 0,cmd_arg,0,0,0,0, regBuf);
    if (status != IOS_ERROR_OK) 
    {
        printf ("%s Error: Command returned status:0x%X\n",__FUNCTION__,status);
        return IOS_ERROR_SDIO_ERR;
    }   		
	/* (2) Set ersase last block CMD33 */
	cmd_arg = blk_end<<9;
   	status = sd_command (fd, 33, SD_COMMAND, ResponseR1, 0,cmd_arg,0,0,0,0, regBuf);
    if (status != IOS_ERROR_OK) 
    {
        printf ("%s Error: Command returned status:0x%X\n",__FUNCTION__,status);
        return IOS_ERROR_SDIO_ERR;
    }   		 
	/* (3) Erase selected blocks CMD38 */
	cmd_arg = 0;
   	status = sd_command (fd, 38, SD_COMMAND, ResponseR1b, 0,cmd_arg,0,0,0,0, regBuf);
   	return status;	   	  	
}

IOSError ISD_EraseSectorAsync (SDDevHandle fd, u32 sector, SDCallbackFunc handler, void *arg)
{
	u32 blk_start = sector;
	u32 blk_end = sector+fd->SDSectorSize;	
	return ISD_EraseBlocksAsync (fd,blk_start,blk_end,handler,arg);
}

IOSError ISD_EraseAllSectorsAsync (SDDevHandle fd, SDCallbackFunc handler, void *arg)
{
	u32 blk_start = 0;
	u32 blk_end = 0xFFFF;	
	return ISD_EraseBlocksAsync (fd,blk_start,blk_end,handler,arg);	
}

IOSError ISD_EraseSector (SDDevHandle fd, u32 sector)
{
	return ISD_EraseSectorAsync(fd,sector,NULL,NULL);
}

IOSError ISD_EraseAllSectors (SDDevHandle fd)
{
	return ISD_EraseAllSectorsAsync(fd,NULL,NULL);
}



/* 
 * These functions either read data from or write data to a designated block on the SD Memory Card. 
 * For single block operation, multi block command is used with block count = 1.
 * For multi-block operation, CMD18 and CMD25 are used for read and write operation, respectively. 
 */
IOSError ISD_ReadBlock (SDDevHandle fd, u32 offset, u32 *data, u32 length)
{
	return ISD_ReadMultiBlockAsync (fd, offset, data, length, 0,0);
}

IOSError ISD_WriteBlock (SDDevHandle fd, u32 offset, u32 data, u32 length)
{
	return ISD_WriteMultiBlockAsync (fd, offset, data, length, 0, 0);
}

IOSError ISD_ReadBlockAsync (	SDDevHandle fd, u32 offset, u32 *data, u32 length, 
								SDCallbackFunc handler, void *arg)
{
	return ISD_ReadMultiBlockAsync (fd, offset, data, length, handler, arg);
}

IOSError ISD_WriteBlockAsync (	SDDevHandle fd, u32 offset, u32 data, u32 length, 
								SDCallbackFunc handler, void *arg)
{
	return ISD_WriteMultiBlockAsync (fd, offset, data, length, handler, arg);
}

IOSError ISD_ReadMultiBlock (SDDevHandle fd, u32 offset, u32 *data, u32 length)
{
	return ISD_ReadMultiBlockAsync (fd, offset, data, length, 0,0);
}

IOSError ISD_WriteMultiBlock (SDDevHandle fd, u32 offset, u32 data, u32 length)
{
	return ISD_WriteMultiBlockAsync (fd, offset, data, length, 0, 0);
}

/* Main overloaded read function */
/*
 * Mapping and population of this call to final destination:
 * (host driver entry in sdio_serial.c)
 * status = do_command (sdh_global, 
 * 				cmd_op.dev, 
 * 				cmd_op.command,
 *      		cmd_op.cmd_type, 
 * 				cmd_op.resp_type,
 *      		cmd_op.req_size, 
 * 				cmd_op.cmd_arg, 
 * 				cmd_op.sys_addr,		GBN add entry
 *             	cmd_op.blk_count,		GBN add entry
 *             	cmd_op.blk_size,		GBN add entry
 * 				cmd_op.dma,				GBN add entry
 *      		&response[0]);
 * 
 * actual call in sdio_util.c (host driver):
 * 
 * The command argument structure used is: (see sd_ioctl.h)
 *		typedef struct _cmd {
 *		    unsigned int dev;		which slot.
 *		    unsigned int command;	i.e. CMD0..CMDxx and ACMDxx
 *		    unsigned int cmd_type; 	read write.
 *		    unsigned int resp_type;	R4, etc
 *		    unsigned int req_size;	for block copy
 *		    unsigned int cmd_arg;	addr etc
 * 			unsigned int sys_addr;
 * 			unsigned int blk_count;
 * 			unsigned int blk_size;
 * 			unsigned int dma;
 *		    unsigned int *buffer;	user buffer for results.
 *		} cmd_t; 
 * 
 * IOSError  ISDIO_Ioctl(int fd, s32 cmd, void *input, u32 input_bytes, void *output, u32 output_bytes) 
 *                             
 */    
IOSError ISD_ReadMultiBlockAsync (	SDDevHandle fd, u32 offset, u32 *data, u32 length, 
									SDCallbackFunc handler, void *arg)
{

    IOSError status;
    cmd_t cmd_op;
    int value = 0;
	unsigned int response[4];
	
    memset (&cmd_op, 0, sizeof(cmd_op));
    
   // printf("ISD_ReadMultiBlockAsync Copy from:%x to %x size %x\n",data,offset,length);
    
 	{
 		u32 blk_size = 512;
 		u32 blk_count 		= length >>9;
	    cmd_op.dev 			= fd->SDDevSlot;
	    cmd_op.command 		= 0;
	    cmd_op.cmd_type 	= 0;
	    cmd_op.resp_type 	= 0;
	    cmd_op.req_size 	= 0;
	    cmd_op.cmd_arg 		= 0;
	    cmd_op.sys_addr		= (u32)data;
	    cmd_op.blk_count	= blk_count;
	    cmd_op.blk_size		= blk_size;
	    cmd_op.dma			= 1;    
	    cmd_op.buffer 		= response;
	    cmd_op.callback		= (u32)handler;
	    cmd_op.offset		= offset;
 	}
 
 	/* "Calling Read SD Card\n" */
    status = ISDIO_Ioctl(fd->SDDevFd, SD_READ_DATA, &cmd_op, sizeof(cmd_t), &value, sizeof(value));
    
    if (status != IOS_ERROR_OK) 
    {
        perror ("SD_READ_DATA");
    }

	return status;  
}

/*
 * ISD_WriteMultiBlockAsync
 * 
 * main overloaded write function
 */
IOSError ISD_WriteMultiBlockAsync (SDDevHandle fd, u32 offset, u32 data, u32 length, 
			SDCallbackFunc handler, void *arg)
{
    IOSError status;
    cmd_t cmd_op;
    int value = 0;
	unsigned int response[4];
	
    memset (&cmd_op, 0, sizeof(cmd_op));
    
//    printf("ISD_WriteMultiBlockAsync Copy from:%x to %x size %x\n",data,offset,length);
/*
 * Mapping and population of this call to final destination:
 * (host driver entry in sdio_serial.c)
 * status = do_command (sdh_global, 
 * 				cmd_op.dev, 
 * 				cmd_op.command,
 *      		cmd_op.cmd_type, 
 * 				cmd_op.resp_type,
 *      		cmd_op.req_size, 
 * 				cmd_op.cmd_arg, 
 * 				cmd_op.sys_addr,		GBN add entry
 *             	cmd_op.blk_count,		GBN add entry
 *             	cmd_op.blk_size,		GBN add entry
 * 				cmd_op.dma,				GBN add entry
 *      		&response[0]);
 * 
 * actual call in sdio_util.c (host driver):
 * 
 * The command argument structure used is: (see sd_ioctl.h)
 *		typedef struct _cmd {
 *		    unsigned int dev;		which slot.
 *		    unsigned int command;	i.e. CMD0..CMDxx and ACMDxx
 *		    unsigned int cmd_type; 	read write.
 *		    unsigned int resp_type;	R4, etc
 *		    unsigned int req_size;	for block copy
 *		    unsigned int cmd_arg;	addr etc
 * 			unsigned int sys_addr;
 * 			unsigned int blk_count;
 * 			unsigned int blk_size;
 * 			unsigned int dma;
 *		    unsigned int *buffer;	user buffer for results.
 *		} cmd_t;                             
 */    
 
 	{
 		u32 blk_size = 512;
 		u32 blk_count = length >>9;
	    cmd_op.dev 			= fd->SDDevSlot;
	    cmd_op.command 		= 0;
	    cmd_op.cmd_type 	= 0;
	    cmd_op.resp_type 	= 0;
	    cmd_op.req_size 	= 0;
	    cmd_op.cmd_arg 		= 0;
	    cmd_op.sys_addr		= data;
	    cmd_op.blk_count	= blk_count;
	    cmd_op.blk_size		= blk_size;
	    cmd_op.dma			= 1;    
	    cmd_op.buffer 		= response;
	    cmd_op.callback		= (int)handler;
	    cmd_op.offset		= offset;
 	}
    	
/* 
 * IOSError  ISDIO_Ioctl(int fd, s32 cmd, void *input, u32 input_bytes, void *output, u32 output_bytes) 
 */
 
// 	printf("Calling Write SD Card\n");
 	

    status = ISDIO_Ioctl(fd->SDDevFd, SD_WRITE_DATA, &cmd_op, sizeof(cmd_t), &value, sizeof(value));
    
    if (status != IOS_ERROR_OK) 
    {
        perror ("SD_WRITE");
    }
    else
    {
    	//printf("%s OK\n",__FUNCTION__);
    }

	return status;
}

/* 
 * These functions either read data from or write data to a designated sector on the SD Memory Card. 
 */
IOSError ISD_ReadSector (SDDevHandle fd, u32 sector, u32 *data, u32 length)
{
	return ISD_ReadSectorAsync (fd, sector, data, length, 0, 0);
}

IOSError ISD_WriteSector (SDDevHandle fd, u32 sector, u32 data, u32 length)
{
	return ISD_WriteSectorAsync (fd, sector, data, length, 0, 0);
}

/* --- Main Read Sector, translate sectors to blocks --- */
IOSError ISD_ReadSectorAsync (SDDevHandle fd, u32 sector, u32 *data, u32 length, 
			SDCallbackFunc handler, void *arg)
{
	u32 offset = sector * fd->SDSectorSize;
	return ISD_ReadMultiBlockAsync (fd, offset, data, length, handler, arg);
}

/* --- Main Write Sector, translate sectors to blocks --- */
IOSError ISD_WriteSectorAsync (SDDevHandle fd, u32 sector, u32 data, u32 length, 
			SDCallbackFunc handler, void *arg)
{
	u32 offset = sector * fd->SDSectorSize;
	return ISD_WriteMultiBlockAsync (fd, offset, data, length, handler, arg);
}





IOSError ISD_MountCard (u32 slotNo, SDDevHandle *fd)
{
    IOSError status;
    
    /* already mounted */
    if ((*fd)->SDMountState) 
    {
    	return IOS_ERROR_SDIO_ERR;
    }
    else
    {
    	u32 devStatus;
		status = GetSdStatus(*fd, &devStatus);
		printf("devstatus = %x\n",devStatus);
		if ((devStatus!=0x0700)&&(devStatus!=0x0900))
		{
			status = ISD_ResetDevice(*fd);
			if (status==IOS_ERROR_OK)
			{
				(*fd)->SDMountState++;
			}
		}
    }
    return status;
}


/*
 * ISD_UnmountCard
 * 
 * Once the card is unmounted, the device handle fd is no longer valid.
 */
IOSError ISD_UnmountCard (SDDevHandle fd)
{
	fd->SDMountState = 0;
	return IOS_ERROR_OK;
}



/*
 * GetSdStatus
 * 
 * Status register: see spec 4.10 p68
 * Interested in Current State: bits 12:9
 * 
 * CMD13
 * 
 */
IOSError GetSdStatus(SDDevHandle fd, u32 *devStatus)
{
    IOSError status;
    u32 regBuf[4];
    u32 cmd_type = SD_COMMAND; 	/* see sd_host.h sdio_util.c */
    u32 cmd_arg = (fd->SDDevRca)<<16;	/* RCA msb 16 */
    
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
     

    printf ("%s SD Command:%d Arg:0x%X\n",__FUNCTION__,cmd_type,cmd_arg);

    
    if (regBuf==NULL)
    {
    	return IOS_ERROR_SDIO_ERR;
    }
    
    if (cmd_arg == 0)
    {
    	printf("Card Not Selected!\n");
    	return IOS_ERROR_SDIO_ERR;
    }
        
	status = sd_command (fd, SD_REG_CS, cmd_type, ResponseR1, 0, cmd_arg,  0,0,0,0, regBuf);
    if (status != IOS_ERROR_OK) 
    {
        printf ("%s Error: ACMD returned status:0x%X\n",__FUNCTION__,status);
        return IOS_ERROR_SDIO_ERR;
    }      

	/* Note: theoretically this register could go up to 512 bits in future, now 32bits */
    if (devStatus) 
    {
        *devStatus = regBuf[0];
    }

    if (debug_level >= DEBUG_CHATTY)
        fprintf (stderr, "%s: get status succeeded\n",__FUNCTION__);

    return IOS_ERROR_OK;
}

/*
 * ISD_InitCard ()
 * 
 * Initialize SD card driver data structures. 
 * Only call once.
 * 
 */
IOSError ISD_InitCard (void)
{   
	int i,j;
	
	for (i=0;i<MAX_SLOTS;i++)
	{
		for (j=0;j<MAX_FUNCS;j++)
		{
			DevHandles[i][j] = 0;	/* make sure it is 0 */
		}
	}
	return IOS_ERROR_OK;
}

/*
 * ISD_GetDeviceRegisterInfo
 */
IOSError ISD_ReadCardRegister(SDDevHandle fd, u32 regType, u32 *regBuf, u32 bufLen)
{
    IOSError status;
    u32 command = regType; 	/* CMD0.. see sepc */
    u32 cmd_type = SD_COMMAND; 	/* see sd_host.h sdio_util.c */
    u32 resp_type = ResponseR2; /* see spec */
    u32 req_size = bufLen;			/* ??? doesnt seem to be used ... sdio_util.c */
    u32 cmd_arg = (fd->SDDevRca)<<16;	/* RCA msb 16 */
        
    /*
    printf ("%s SD Command:%d Arg:0x%X\n",__FUNCTION__,command,cmd_arg);
    */
    
    if (regBuf==NULL)
    {
    	return IOS_ERROR_SDIO_ERR;
    }
    
	switch (regType)
	{
		case SD_REG_CID:
			command = regType;
			resp_type = ResponseR2;
			break;
    	case SD_REG_CSD:
			command = regType;
			resp_type = ResponseR2;
    		break;
    	case SD_REG_SCR:
   			status = sd_command (fd, SD_REG_ACMD, cmd_type, ResponseR1, 0, cmd_arg,  0,0,0,0, regBuf);
		    if (status != IOS_ERROR_OK) 
		    {
		        printf ("%s Error: ACMD returned status:0x%X\n",__FUNCTION__,status);
		        return IOS_ERROR_SDIO_ERR;
		    }  
			command = regType;
			resp_type = ResponseR1;		
			cmd_type = SD_READ; /* read 64bits from databus */      	    	
    		break;
    	case SD_REG_OCR:	/* only available from RCA = 0x0000 */
    		status = sd_command (fd, 0, cmd_type, NoResponse, 0, 0,  0,0,0,0, regBuf);
    		status = sd_command (fd, SD_REG_ACMD, cmd_type, ResponseR1, 0, 0,  0,0,0,0, regBuf);
		    if (status != IOS_ERROR_OK) 
		    {
		        printf ("%s Error: ACMD returned status:0x%X\n",__FUNCTION__,status);
		        return IOS_ERROR_SDIO_ERR;
		    }    		
    		/* Now ready for ACMD 41 */
    		command = regType;
			resp_type = ResponseR3;
			cmd_arg = 0x0;
    		break;
    	case SD_REG_RCA:
    		regBuf[0]=(fd->SDDevRca);
    		return IOS_ERROR_OK;
    	default:
    		break;
	}
	
	status = sd_command (fd, command, cmd_type, resp_type, req_size, cmd_arg,  0,0,0,0, regBuf); 
    if (status != IOS_ERROR_OK) 
    {
        fprintf (stderr, "%s Error: Command returned status:0x%X\n",__FUNCTION__,status);
        return IOS_ERROR_SDIO_ERR;
    }
    else if (debug_level >= DEBUG_CHATTY)
    {
    	printf("%s command:%02d cmd_arg:%X st:%X response:%08X %08X %08X %08X\n",__FUNCTION__,
    		command,cmd_arg,status,
    		regBuf[0],regBuf[1],regBuf[2],regBuf[3]);
    }
    
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
    if (!fd) {
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

    if (fd->SDDevFd > 0) {
        return true;
    }

    fprintf (stderr, "%s: dev 0x%x function 0x%x not open\n",
             __FUNCTION__, fd->SDDevSlot, fd->SDDevFunc);

    return false;
}




/*
 * sd_command
 * 
 * call host driver command() with appropriate arguments
 * 
 */

IOSError sd_command (	SDDevHandle fd, 
						u32 command, 
						u32 cmd_type, 
						u32 resp_type, 
						u32 size, 
						u32 cmd_arg, 
						u32 sys_addr,
						u32 blk_count,
						u32 blk_size,
						u32 dma,					
						u32 *resp)
						/*,
						u32 callback,
						u32 offset)*/
{
    IOSError status;
    cmd_t cmd_op;
    int value = 0;
	unsigned int response[4]; /* short lower down! */
	
    memset (&cmd_op, 0, sizeof(cmd_op));
    
/*
 * Mapping and population of this call to final destination:
 * (host driver entry in sdio_serial.c)
 * status = do_command (sdh_global, 
 * 				cmd_op.dev, 
 * 				cmd_op.command,
 *      		cmd_op.cmd_type, 
 * 				cmd_op.resp_type,
 *      		cmd_op.req_size, 
 * 				cmd_op.cmd_arg, 
 * 				cmd_op.sys_addr,		GBN add entry
 *             	cmd_op.blk_count,		GBN add entry
 *             	cmd_op.blk_size,		GBN add entry
 * 				cmd_op.dma,				GBN add entry
 *      		&response[0]);
 * 
 * actual call in sdio_util.c (host driver):
 * int do_command (struct sd_host *sdh, 
 * 					int slot, 
 * 					int cmd, 
 * 					int cmd_type,
 * 			        int resp_type, 
 * 					int req_size, 
 * 					int cmd_arg, 
 * 					int sys_addr,
 * 			        int blk_count, 
 * 					int blk_size, 
 * 					int dma, 
 * 					unsigned short *resp)
 * 
 * The command argument structure used is: (see sd_ioctl.h)
 *		typedef struct _cmd {
 *		    unsigned int dev;		which slot.
 *		    unsigned int command;	i.e. CMD0..CMDxx and ACMDxx
 *		    unsigned int cmd_type; 	read write.
 *		    unsigned int resp_type;	R4, etc
 *		    unsigned int req_size;	for block copy
 *		    unsigned int cmd_arg;	addr etc
 * 			unsigned int sys_addr;
 * 			unsigned int blk_count;
 * 			unsigned int blk_size;
 * 			unsigned int dma;
 *		    unsigned int *buffer;	user buffer for results.
 *   		unsigned int callback;
 *   		unsigned int offset;
 * 
 *		} cmd_t;                             
 */    
    cmd_op.dev 			= fd->SDDevSlot;
    cmd_op.command 		= command;
    cmd_op.cmd_type 	= cmd_type;
    cmd_op.resp_type 	= resp_type;
    cmd_op.req_size 	= size;
    cmd_op.cmd_arg 		= cmd_arg;
    cmd_op.sys_addr		= sys_addr;
    cmd_op.blk_count	= blk_count;
    cmd_op.blk_size		= blk_size;
    cmd_op.dma			= dma;    
    if (resp)
    	cmd_op.buffer 	= resp;
    else
    	cmd_op.buffer 	= response;
    cmd_op.callback		= 0; //callback;
    cmd_op.offset		= 0; //offset;
    	
/* 
 * IOSError  ISDIO_Ioctl(int fd, s32 cmd, void *input, u32 input_bytes, void *output, u32 output_bytes) 
 */

    status = ISDIO_Ioctl(fd->SDDevFd, SD_CMD, &cmd_op, sizeof(cmd_t), &value, sizeof(value));
    
    if (status != IOS_ERROR_OK) 
    {
        perror ("SD_CMD");
        fprintf (stderr, "%s:ioctl FAIL: status 0x%x slot %d fnc %d cmd %d size %d\n", 
        	__FUNCTION__, 
        	status, fd->SDDevSlot, fd->SDDevFunc, command, size);
        	#if 0
        	(char*)decode_card_status(resp[0]));
        	#endif
    } 
	else
    {
    	if (debug_level > DEBUG_CHATTY)
    	{
        	printf ("%s:ioctl OK: slot %d fnc %d cmd %d size %d value 0x%x saddr 0x%X\n",
                __FUNCTION__, 
                fd->SDDevSlot, fd->SDDevFunc, 
                command, size, value, (u32)sys_addr);
              #if 0
			if (resp_type==ResponseR1)  printf(" %s",(char*)decode_card_status(resp[0]));
			printf ("\n");
			#endif
    	}
    }

	return status;
}


/*
 * cmd_databuswidth() 
 * 
 * SD card helper function to set Host Control Register and 
 * ACMD6 card bus width (D01)
 * 
 * D00 = LED Control: 			1 = On
 * D01 = Data Transfer Width: 	1 = 4-bit, 	0 = 1-bit
 * D02 = High Speed:			1 = 50MHz, 	0 = 25MHz
 */
IOSError cmd_databuswidth(SDDevHandle fd, int buswidth)
{
    IOSError status;
    u32 resp[4];
    u32 cmd_arg = buswidth;	/* SD Card */
    u32 reg_data;			/* Host Controller */

    if (buswidth==4)
    {
    	cmd_arg = 0x02;	/* 4bit */
    }
    else
    {
    	cmd_arg = 0x00;	/* default to 1bit */
    }

	/* CMD55 -> ACMD */
  	status = sd_command (fd, SD_REG_ACMD, SD_COMMAND, ResponseR1, 0, (fd->SDDevRca)<<16,  
  				0,0,0,0, resp);
    if (status != IOS_ERROR_OK) 
    {
        perror ("SD_REG_ACMD");
        fprintf (stderr, "%s: Bad ioctl 0x%x\n", __FUNCTION__, status);
        return status;
    }
        
	if (debug_level >= DEBUG_CHATTY) 
	{       
    	printf (" - %s Arg:0x%02X ",__FUNCTION__,cmd_arg);
	}
    
    /* ACMD6 SET_BUS_WIDTH */
    status = sd_command (fd, 6, SD_COMMAND, ResponseR1, 0, cmd_arg,  
    			0,0,0,0, resp);
    
    if (status != IOS_ERROR_OK) 
    {
        perror ("SET_BUS_WIDTH");
        fprintf (stderr, "%s: Bad ioctl 0x%x\n", __FUNCTION__, status);
        return status;
    }
    else 
    {
    //    printf(" - GetSdStatus:%X %s\n",resp[0],(char*)decode_card_status(resp[0])); 
    }
	
	/* --- Also set the Host Controller bus width --- */
    /* Read Host Control Register */
    status = ISD_GetHCRegister(fd, HOSTREG_HOSTCTRLREG, &reg_data, 1);
    if (status != IOS_ERROR_OK) 
    {
        fprintf (stderr, "%s: Error ISD_GetHCRegister %d\n",
                __FUNCTION__, 0x28);
        return status;
    }
    
    //printf(" - HCR:0x%X width=0x%x\n",reg_data,cmd_arg);
    
    /* Set Bus width bit */
    if (cmd_arg)
    	reg_data = reg_data | 0x2;
    else
    	reg_data = (reg_data & ~0x2);    
    
    /* Write Host Control Register */
    status = ISD_SetHCRegister(fd, HOSTREG_HOSTCTRLREG, &reg_data, 1);
    if (status != IOS_ERROR_OK) 
    {
		fprintf (stderr, "%s: Error ISD_SetHCRegister %d\n",
			__FUNCTION__, 0x28);
		return status;                
    }

	/* debug read back */
	if (debug_level >= DEBUG_CHATTY) 
	{  
		status = ISD_GetHCRegister(fd, HOSTREG_HOSTCTRLREG, &reg_data, 1);  
    	printf(" -> GetHCRegister:0x%02X\n",reg_data);  
	}  
	return status;
}

/* 
 * ISD_GetCardSize
 * 
 * This function calculates and returns the total size (in bytes), the number of sectors, 
 * and the sector size of the specified SD Card. 
 * Sector size: is specific to each SD Card type and should be a multiple of 512 bytes.
 * It is the number of blocks that will be erased in one portion.
 */
IOSError ISD_GetCardSize (SDDevHandle fd, u32 *totalSize, u32 *totalSectors, u32 *sectorSize)
{
    IOSError status;
    unsigned int resp[4];
    
    
    int c_size;
    int c_size_mult;
    int read_bl_len;
    int memory_capacity;
    int write_bl_length;
    int sector_size;
    int file_format;
    int total_sectors;
            
    status = ISD_ReadCardRegister(fd, SD_REG_CSD, resp, 0);

    if (status != IOS_ERROR_OK) 
    {
        fprintf (stderr,"CSD error status:0x%X\n",status);
    }
    #if 0
    {
    	u32 d0,d1,d2,d3,j;
    for (j=0;j<4;j++)
    {
	    d3 = (resp[j]<<24)&0xFF000000;
	    d2 = (resp[j]<<16)&0x00FF0000;
	    d1 =  (resp[j]<<8)&0x0000FF00;
	    d0 = resp[j]&0xFF;
	    resp[j] = d3|d2|d1|d0;
    }
    }
    #endif
    
    /* === Calculate the CARD size (-8 for response regiter mapping) === */
    /* C_SIZE 		73:62 -8 = 65:54 split -64=1:-32=22*/
    c_size = ((resp[1]&0xff300000)>>22) | ((resp[2]&0x3)<<10);
    /* C_SIZE_MULT 	49:47  = 17:15 in 32bits */
    c_size_mult = (resp[1]&0x000380)>>7;
    /* READ_BL_LEN 	83:80 - 64 = 19:16 (range 2^9..11 i.e. 512 to 2048) */
    read_bl_len = (resp[2]&0x000F00)>>8;
    
    memory_capacity = (c_size+1)*(1<<(c_size_mult+2))*(1<<read_bl_len);
    
    /* write_bl_length 25:22 -8 = 17:14*/
    write_bl_length = (resp[0]&0x03C000)>>14;
    
    /* sector_size[7] 45:39 -8 37:31 split (range 1 to 128) Erasable Sector Size */
    sector_size = (((resp[1]&0x0000003F)<<1) | ((resp[0]&0x80000000)>>31)) + 1;
    
    /* file_format[2] 10:11 -8 2:3 */
    file_format = (resp[0]&0xC)>>2;
    
    /* if (file_format==1) printf("file_format = DOS\n"); */
    total_sectors = 0x12345678;
    /* quick fix, no division in lib */
    if (sector_size==  8) total_sectors = (memory_capacity>>3)>>read_bl_len;
    if (sector_size== 16) total_sectors = (memory_capacity>>4)>>read_bl_len;
    if (sector_size== 32) total_sectors = (memory_capacity>>5)>>read_bl_len;
    if (sector_size== 64) total_sectors = (memory_capacity>>6)>>read_bl_len;
    if (sector_size==128) total_sectors = (memory_capacity>>7)>>read_bl_len;
    
    if (totalSectors) *totalSectors = total_sectors;
    if (totalSize) *totalSize = memory_capacity;
    if (sectorSize) *sectorSize = sector_size;
    
    fd->SDSectorSize = sector_size;
    fd->SDSectorNum = total_sectors;
    fd->SDDevSize = memory_capacity;
    	
    return IOS_ERROR_OK;
}
/* eof */
