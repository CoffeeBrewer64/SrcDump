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

#ident "$Id: sd_ioctl.h,v 1.2 2006/03/20 07:29:40 gbarnard Exp $"
#ifndef _SD_IOCTL_H_
#define _SD_IOCTL_H_
/*
 * Structs
 */
typedef enum {
    REG_READ=0,
    REG_WRITE=1,
    REG_READ_M=2,
    REG_WRITE_M=3,
} dir_t;

typedef struct _reg_op {
    unsigned int dev;
    unsigned int reg;
    unsigned int width;
    unsigned int blk_size;
    unsigned int blk_num;
    dir_t rw;
    unsigned int value;
    unsigned int dma;
    unsigned int busy;
    unsigned int function;
    unsigned int *buffer;
} reg_op_t;

/*
 * cmd_t
 * 
 * Command Type Structure, used extensively by the SD card driver.
 * 
 * Dev: which slot.
 * command: to execute.
 * commmand type: read write.
 * response type: R4, etc
 * req_size: for block copy.
 * buffer: user buffer for results.
 * 
 * Structure used to call the following function:
 * 
 * do_command (struct sd_host *sdh, int slot, int cmd, int cmd_type, 
 *           int resp_type, int req_size, int cmd_arg, int sys_addr,
 *           int blk_count, int blk_size, int dma, unsigned short *resp)
 */
 
typedef struct _cmd {
    unsigned int dev;
    unsigned int command;
    unsigned int cmd_type;
    unsigned int resp_type;
    unsigned int req_size;
    unsigned int cmd_arg;
    unsigned int sys_addr;
    unsigned int blk_count;
    unsigned int blk_size;
    unsigned int dma;
    unsigned int *buffer;
    unsigned int callback;
    unsigned int offset;
} cmd_t;

/*
 * dev: which slot
 * clock: new clock value
 * volt: new voltage
 */
typedef struct _volt_clock {
    unsigned int dev;
    unsigned int clock;
    unsigned int volt;
    unsigned int width;
} volt_clock_t;

/*
 * Status bits for device status query
 */
#define SD_CARD_INSERTED   0x00000001
#define SD_CARD_REMOVED    0x00000002
#define SD_CARD_WPROTECTED 0x00000004
#define SD_STATE_SUSPEND   0x00000008

#define SD_TYPE_UNKNOWN    0x00000000
#define SD_TYPE_MEMORY     0x00010000
#define SD_TYPE_SDIO       0x00020000
#define SD_TYPE_COMBO      0x00040000
#define SD_TYPE_MMC        0x00080000

/*
 * This file contains constants and macros used in the SD/SDIO bus
 * protocol.
 */
#define SD_IOC_MAGIC 'S'

#ifndef LINUX
	/*
	 * The following is for compatibility across the various Linux
	 * platforms.  The i386 ioctl numbering scheme doesn't really enforce
	 * a type field.  De facto, however, the top 8 bits of the lower 16
	 * bits are indeed used as a type field, so we might just as well make
	 * this explicit here.  Please be sure to use the decoding macros
	 * below from now on.
	 */
	#define _IOC_NRBITS	8
	#define _IOC_TYPEBITS	8
	#define _IOC_SIZEBITS	14
	#define _IOC_DIRBITS	2
	
	#define _IOC_NRMASK	((1 << _IOC_NRBITS)-1)
	#define _IOC_TYPEMASK	((1 << _IOC_TYPEBITS)-1)
	#define _IOC_SIZEMASK	((1 << _IOC_SIZEBITS)-1)
	#define _IOC_DIRMASK	((1 << _IOC_DIRBITS)-1)
	
	#define _IOC_NRSHIFT	0
	#define _IOC_TYPESHIFT	(_IOC_NRSHIFT+_IOC_NRBITS)
	#define _IOC_SIZESHIFT	(_IOC_TYPESHIFT+_IOC_TYPEBITS)
	#define _IOC_DIRSHIFT	(_IOC_SIZESHIFT+_IOC_SIZEBITS)
	/*
	 * Direction bits.
	 */
	#define _IOC_NONE	0U
	#define _IOC_WRITE	1U
	#define _IOC_READ	2U
	
	#define _IOC(dir,type,nr,size) \
		(((dir)  << _IOC_DIRSHIFT) | \
		 ((type) << _IOC_TYPESHIFT) | \
		 ((nr)   << _IOC_NRSHIFT) | \
		 ((size) << _IOC_SIZESHIFT))
	
	/* used to create numbers |Direction 2bits|Size 14bits|Type 8bits|Command Number 8bits| */
	#define _IO(type,nr)		_IOC(_IOC_NONE,(type),(nr),0)
	#define _IOR(type,nr,size)	_IOC(_IOC_READ,(type),(nr),sizeof(size))
	#define _IOW(type,nr,size)	_IOC(_IOC_WRITE,(type),(nr),sizeof(size))
	#define _IOWR(type,nr,size)	_IOC(_IOC_READ|_IOC_WRITE,(type),(nr),sizeof(size))
	
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

#define SD_IOGSLOTS _IO(SD_IOC_MAGIC, 1)
#define SD_IOGIDENT _IO(SD_IOC_MAGIC, 2)
#define SD_IORREG   _IOW(SD_IOC_MAGIC, 3, reg_op_t)
#define SD_IORCREG  _IOW(SD_IOC_MAGIC, 4, reg_op_t)
#define SD_RESET    _IOW(SD_IOC_MAGIC, 5, unsigned int)
#define SD_IOWREG   _IOW(SD_IOC_MAGIC, 6, reg_op_t)
#define SD_IOWCREG  _IOW(SD_IOC_MAGIC, 7, reg_op_t)
#define SD_CINTEN   _IOW(SD_IOC_MAGIC, 8, unsigned int)
#define SD_CINTDIS  _IOW(SD_IOC_MAGIC, 9, unsigned int)
#define SD_CMD      _IOW(SD_IOC_MAGIC, 10, cmd_t)
#define SD_GETVOLT  _IOW(SD_IOC_MAGIC, 11, unsigned int)
#define SD_GETCLOCK _IOW(SD_IOC_MAGIC, 12, unsigned int)
#define SD_SETVOLT  _IOW(SD_IOC_MAGIC, 13, volt_clock_t)
#define SD_SETCLOCK _IOW(SD_IOC_MAGIC, 14, volt_clock_t)

#define SD_SET_BUS_WIDTH _IOW(SD_IOC_MAGIC, 15, volt_clock_t)
#define SD_SET_SPEED     _IOW(SD_IOC_MAGIC, 16, unsigned int)
#define SD_SET_CLKON     _IOW(SD_IOC_MAGIC, 17, unsigned int)
#define SD_SET_CLKOFF    _IOW(SD_IOC_MAGIC, 18, unsigned int)
#define SD_SET_SDCLKON   _IO(SD_IOC_MAGIC, 19)
#define SD_SET_SDCLKOFF  _IO(SD_IOC_MAGIC, 20)
#define SD_RESET_CMD     _IO(SD_IOC_MAGIC, 21)
#define SD_RESET_DAT     _IO(SD_IOC_MAGIC, 22)
#define SD_RESET_ALL     _IO(SD_IOC_MAGIC, 23)
#define SD_SET_SPI_MODE  _IOW(SD_IOC_MAGIC, 24, unsigned int)

#define SD_IORMCREG  _IOW(SD_IOC_MAGIC, 25, reg_op_t)
#define SD_IOWMCREG  _IOW(SD_IOC_MAGIC, 26, reg_op_t)

#define SD_HANDLE_INSERT _IOW(SD_IOC_MAGIC, 27, unsigned int)
#define SD_HANDLE_REINIT _IOW(SD_IOC_MAGIC, 28, unsigned int)

#define SD_GET_STATUS     _IOW(SD_IOC_MAGIC, 29, unsigned int)
#define SD_WAIT_INSERT    _IOW(SD_IOC_MAGIC, 30, unsigned int)
#define SD_WAIT_INTERRUPT _IOW(SD_IOC_MAGIC, 31, unsigned int)
#define SD_WAIT_ERROR     _IOW(SD_IOC_MAGIC, 32, unsigned int)
#define SD_DEBUG_LEVEL    _IOW(SD_IOC_MAGIC, 33, unsigned int)
#define SD_SET_STATUS     _IOW(SD_IOC_MAGIC, 34, unsigned int)
#define SD_GET_OCR        _IOW(SD_IOC_MAGIC, 35, unsigned int)
#define SD_READ_DATA      _IOW(SD_IOC_MAGIC, 36, cmd_t)
#define SD_WRITE_DATA     _IOW(SD_IOC_MAGIC, 37, cmd_t)
#define SD_IOGOCR         _IO(SD_IOC_MAGIC, 38)

/*
 * Defines
 */

/*
 * Macros
 */

/*
 * Inlines
 */

/*
 * Prototypes
 */
#endif
/* eof */
