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

#ident "$Id: sdio_serial.c,v 1.9 2006/03/21 02:26:02 wheeler Exp $"

#ifdef LINUX

	#include <linux/types.h>
	#include <linux/init.h>
	#include <linux/module.h>
	#include <linux/kernel.h>
	#include <linux/config.h>
	#include <linux/fs.h>
	#include <linux/proc_fs.h>
	#include <linux/ioport.h>
	#include <linux/ioctl.h>
	#include <linux/wait.h>
	
	#include <asm/uaccess.h>
	#include <asm/io.h>
	
	#include "../include/sd.h"
	#include "../include/sd_pci.h"
	#include "../include/sd_card.h"
	#include "../include/sd_ioctl.h"
	#include "../include/sd_host.h"
	#include "../include/sd_debug.h"

#else
	#include <ios.h>
	#include <iostypes.h>
	#include <ioslibc.h>

	#include <hw.h>
	#include <arm.h>
	
	extern void testthr(u32 arg);
	
	#define SD_QUEUE_SIZE 	128
	#define STACK_SIZE 		2048
		
	IOSMessageQueueId 	sdQid;
	IOSMessage 			sdQ[SD_QUEUE_SIZE];	
	
	IOSMessageQueueId 	sdiQid;
	IOSMessage 			sdiQ[SD_QUEUE_SIZE];	
	
	IOSMessageQueueId 	slpQid;
	IOSMessage 			slpQ[SD_QUEUE_SIZE];
	
	extern void msleep(unsigned int msecs);
	
	inline IOSError sdusleep(u32 usec)
	{
	    IOSMessageQueueId mqs;
	    IOSMessage array[4];
	    IOSMessage m;
	    IOSTimerId  t2; 
	
	    //printf("Creating message queue\n");
	    mqs = IOS_CreateMessageQueue(array, 4);
	    
	    t2 = IOS_CreateTimer(usec, 0, mqs, 0xbabababa);
	    //printf("Waiting(%d) %08X", i, IOS_GetTimer());
	    IOS_ReceiveMessage(mqs, &m, IOS_MESSAGE_BLOCK);
	    //printf("Rx Msg[%x] @ %08X\n", m, IOS_GetTimer());
	    IOS_DestroyTimer(t2);
	    IOS_DestroyMessageQueue(mqs);
    	return 0;
	}

	u8 stackirq[STACK_SIZE];
	
	const u8        _initStack[STACK_SIZE];
	const u32       _initStackSize = sizeof(_initStack);
	const u32       _initPriority = 100;
	
	// ----------------
	#include "sd.h"
	#include "sd_card.h"
	#include "sd_host.h"
	#include "sd_ioctl.h"
	#include "sd_debug.h"
	

	/**
	 * copy_to_user: - Copy a block of data into user space.
	 * @to:   Destination address, in user space.
	 * @from: Source address, in kernel space.
	 * @n:    Number of bytes to copy.
	 *
	 * Context: User context only.  This function may sleep.
	 *
	 * Copy data from kernel space to user space.
	 *
	 * Returns number of bytes that could not be copied.
	 * On success, this will be zero.
	 */
	unsigned long
	copy_to_user(void *to, const void *from, unsigned long n)
	{
		memcpy(to, from, n);
		return 0;
	}
	
	/**
	 * copy_from_user: - Copy a block of data from user space.
	 * @to:   Destination address, in kernel space.
	 * @from: Source address, in user space.
	 * @n:    Number of bytes to copy.
	 *
	 * Context: User context only.  This function may sleep.
	 *
	 * Copy data from user space to kernel space.
	 *
	 * Returns number of bytes that could not be copied.
	 * On success, this will be zero.
	 *
	 * If some data could not be copied, this function will pad the copied
	 * data to the requested size using zero bytes.
	 */
	unsigned long
	copy_from_user(void *to, const void *from, unsigned long n)
	{
		memcpy(to, from, n);
		return 0;
	}
		
		
	/* equavalent for linux -> ios */
	#define GFP_USER	1
	#define GFP_KERNEL	2
	#define GFP_ATOMIC	4
	#define GFP_DMA 	8
	
	// - from resource manager -
	extern IOSHeapId       	sdheapId;
	
	#define malloc(size) 	IOS_Alloc(sdheapId,size)
	#define free(ptr) 		IOS_Free(sdheapId,ptr)	
	#define io(x)			*((volatile int *)(x))
			
	void* kmalloc (size_t size, int flags)
	{
		return IOS_Alloc(sdheapId,size); 
	}		
	
	void kfree (const void* objp)
	{
		IOS_Free(sdheapId,(void*)objp);
	}

	void sdioIrqThread(u32 arg);


	
#endif




#ifdef LINUX
	#define DEVICE_NAME      "sdioserial"
	MODULE_LICENSE ("Proprietory");
	
	
	/*
	 * These are all defined locally because they are not accessed from
	 * outside this source file.
	 */
	static int major_dev = 0;   /* global because one per module */
	static int device_open[MAX_DEV]; /* Used to disallow simultaneous opens */
	
	static int sdio_ser_open (struct inode *inode, struct file *file);
	static int sdio_ser_release (struct inode *inode, struct file *file);
	static int sdio_ser_read (struct file *file, 
	                          char *buf, size_t count, loff_t*ppos);
	static int sdio_ser_write (struct file *file, 
	                           const char *buf, size_t count, loff_t*ppos);
	static int sdio_ser_ioctl (struct inode *inode, struct file *file, 
	                           unsigned int cmd, unsigned long arg);
	static int sdio_ser_proc_read (char *buf, char **start, off_t offset,
	                               int count, int *eof, void *data);

#endif
 
/*
 * Allocate sd_host struct.
 */
struct sd_host *sdh_global; // = &g_sdh;
struct sd_host g_sdh;

/*
 * A pointer to this is passed to the completion routine.
 */
struct _sd_request *gp_sd_req;

int ser_debug = DEBUG_SER_ERR;  //||DEBUG_SER_CMD DEBUG_SER_REG_WRITE|DEBUG_SER_REG_READ;

extern int sdpci_debug;

#ifdef LINUX
static struct file_operations fops =
{
    .owner = THIS_MODULE,
	.read = sdio_ser_read,
	.write = sdio_ser_write,
	.poll = NULL /* SDSerial_poll */ ,
	.ioctl = sdio_ser_ioctl,
	.open = sdio_ser_open,
	.flush = NULL /* SDSerial_flush */ ,
	.release = sdio_ser_release,
	.sendfile = NULL /* SDSerial_sendfile */ ,
	.sendpage = NULL /* SDSerial_sendpage */
};
#endif

u32 sdio_ser_irq(void* arg);

extern unsigned int sdpci_base_address(int bar_no);
extern u8 sdpci_slot_count(void);
extern void sdpci_attach_irq(void* irq_function);

#ifdef LINUX
/* This function interfaces to the PCI system to retrieve:
 * 		a) number of slots on the SD controller (not PCI slots).
 * 		b) the base address for each SD slot register space
 * Then link irq and initialise each SD-slot.
 */
void sdio_config_pci(void)
{
	int i; 
	
	SER_DEBUG (DEBUG_SER_INIT, "%s:\n --- SD Init Start --- \n",__FUNCTION__);
 
 	/* a) Read number of slots on host controller */
	sdh_global->m_slotcount = sdpci_slot_count();

	/* b) Get Base Address for each slot */
	for (i=0;i<sdh_global->m_slotcount;i++)
	{
		sdh_global->m_sdslot[i].m_base = (void*)sdpci_base_address(i);
		SER_DEBUG (DEBUG_SER_INIT, "%s:Base Address(%d) = %x\n",__FUNCTION__, i,
					(u32)sdh_global->m_sdslot[i].m_base);
	}
	
	/* c) add irq handling to process card insert interrupts*/
	sdpci_attach_irq(sdio_ser_irq);
	
	/* d) initialise each slot */
	for (i=0;i<sdh_global->m_slotcount;i++)
	{
		SDHostslot_init(&sdh_global->m_sdslot[i]);
		SDHostslot_start(&sdh_global->m_sdslot[i]);
	}
}

#else

/*
 * ------- Main SDIO ARM based IOS Init -------
 */
 

void
dbgStartTimer(void)
{
    IOSMessageQueueId mq;
    IOSMessage array;
    IOSTimerId t;
    mq = IOS_CreateMessageQueue(&array, 1);
    t = IOS_CreateTimer(0, 0x100, mq, 0xdeadbeef);
}

IOSError 
sdio_init_irq(int hc)
{
    IOSError rv = -1;
   
    /* === Create a message queue and register for SDIO events === */
    if ((sdiQid = IOS_CreateMessageQueue(sdiQ, sizeof(sdiQ))) < 0) 
    {
        printf("Unable to create SD%d message queue: %d\n", hc, sdiQid);
        return -1;
    }
    printf("--- SD%d IRQ QID:%d ---\n",hc,sdiQid);
    
    if (hc==0)
    {
	    if ((rv = IOS_HandleEvent(IOS_EVENT_SD0, sdiQid, 0)) != IOS_ERROR_OK) 
	    {
	        printf("Unable to register SD0 event handler: %d\n", rv);
	        return rv;
	    }	  	   
    }
    else
    {
	    if ((rv = IOS_HandleEvent(IOS_EVENT_SD1, sdiQid, 0)) != IOS_ERROR_OK) 
	    {
	        printf("Unable to register SD1 event handler: %d\n", rv);
	        return rv;
	    }	     	
    }
    
    return rv;
}



IOSError
initSDIO(u32 hc)
{
    IOSError rv = IOS_ERROR_OK;
     
    int i;
    u32 id;
    u32 pri = IOS_GetThreadPriority(0)+10; //100; /* max prioroty for irq */ //IOS_GetThreadPriority(0);
    u32 baseaddress;
  
 	// --- allocate memory for host structures ---
	gp_sd_req = (struct _sd_request*)malloc(sizeof(struct _sd_request));
	#if 0
		sdh_global = (struct sd_host*)malloc(sizeof(struct sd_host));
	#else
		sdh_global = &g_sdh; 
	#endif
    
    // --- select which host controller ---
    if (hc==0)
    {
    	baseaddress = 0x0D070000;
    	sdh_global->m_slotcount = 2;
    }
    else if (hc==1)
    {
    	baseaddress = 0x0D080000; // note d080000 for board?
    	sdh_global->m_slotcount = 1;
    }
    else
    {
    	printf("Invalid Host Controller Number[0,1] = %d\n",hc);
    	return -1;
    }
    
//    debug
    if ((baseaddress&0x0D070000)==0x0D070000) hc = 0; else hc = 1;
 
	
	printf("Heap memory SD_Req = 0x%x, SD_Host = 0x%x\n",gp_sd_req,sdh_global);
	
	/* --- Assign Base Address for each slot in host controller --- */
	for (i=0;i<sdh_global->m_slotcount;i++)
	{
		if (i==0)
		{
			sdh_global->m_sdslot[i].m_base = (void*)baseaddress;
		}
		else
		{
			sdh_global->m_sdslot[i].m_base = (void*)baseaddress+0x100;			
		}
		
		sdh_global->m_sdslot[i].m_slotindex = i;
		
		//SER_DEBUG (DEBUG_SER_INIT, 
		printf("%s:Base Address(%d) = %x\n", __FUNCTION__, i,
						(u32)sdh_global->m_sdslot[i].m_base);
	}
	
	/* --- Add irq handling to process host interrupts --- */
	
	sdio_init_irq(hc);
    id = IOS_CreateThread((IOSEntryProc)sdioIrqThread, 0, stackirq, STACK_SIZE, pri, IOS_THREAD_CREATE_DETACHED);
   
    //printf("IRQ: Created thread Id:%d\n",id);
 	
    /* === Create SDIO IOCTL message queue === */
    sdQid = IOS_CreateMessageQueue(sdQ, sizeof(sdQ));
    
    printf("Starting IRQ Thread Id:%d mq:%d\n",id,sdiQid);
    IOS_StartThread(id);
    msleep(100); // debug only to seperate printf's
	
	//ser_debug = DEBUG_SER_ERR|DEBUG_SER_SD_CMD|DEBUG_SER_REG_READ|DEBUG_SER_REG_WRITE;
	/* === d) initialise each slot === */
	for (i=0;i<sdh_global->m_slotcount;i++)
	{
		SDHostslot_init(&sdh_global->m_sdslot[i]);
		SDHostslot_start(&sdh_global->m_sdslot[i]);
	}	

	// === enable ios irq processing ===  
	IOS_ClearAndEnableSDIntr(hc);
	
	#if 1
	{
		u16 dwIntStatus = READ_HOST_U16((u32)sdh_global->m_sdslot[0].m_base, HOSTREG_SLOTINTRS);
		printf("--- SIRQ slot 0x%04X\n",(u32)dwIntStatus);
		printf("--- NINT stat 0x%04x\n", 
	  			READ_HOST_U16((u32)sdh_global->m_sdslot[0].m_base, HOSTREG_NORMINTRSTAT) );			
	}
 	{
		volatile u32* addr;
		addr = (u32*)(ACR_PROT_REGS_BASE + 0x03C); printf("IOP_Ena");printf("[%08X]:%08X\n",addr,*addr );
		addr = (u32*)(ACR_PROT_REGS_BASE + 0x038); printf("IOP_Sta");printf("[%08X]:%08X\n",addr,*addr );	
	}	
	#endif   
	   
    msleep(100); // debug only to seperate printf's
 	
    return rv;
}
#endif

/*
 * sdio_init_module
 *
 * Module init function.  Its name is registered with the kernel
 * below.  The __init is a hint to the kernel that it can free up the
 * pace used by this function once it has run.
 *
 * Called at module installatin time.  It registers itself as a
 * character device, so its name - DEVICE_NAME above - will show up in
 * /proc/devices, along with its dynamically assigned major number.
 *
 * This allows a script to grep through /proc/devices, find the major
 * number, and then use it to mknod the desired driver entries in the
 * /dev/directory.
 *
 * It also creates a node for itself in the kernel internel sysfs tree
 * under device/sdio.
 */
int __init
sdio_init_module (u32 base)
{
	#ifdef LINUX
	    struct proc_dir_entry *entry;
	    mode_t mode = 0;
	    int dev;
	
	    SER_DEBUG (DEBUG_SER_INIT, "%s: initial major %d\n", __FUNCTION__, major_dev);
	    
	    SER_DEBUG (DEBUG_SER_ERR, "%s - %d\n", __FUNCTION__,2);
	
	    major_dev = register_chrdev (major_dev, DEVICE_NAME, &fops);
	    if (major_dev < 0) {
	        printk (KERN_CRIT "%s: failed major %d\n", __FUNCTION__, major_dev);
	        return major_dev;
	    }
	
	    SER_DEBUG (DEBUG_SER_INIT, "Register_chrdev succeeded major %d\n", major_dev);
	
	    entry = create_proc_read_entry ("driver/sdio", mode, NULL, 
	                                    sdio_ser_proc_read, NULL);
	    if (entry) {
	        SER_DEBUG (DEBUG_SER_INIT, "%s: created proc entry for sdio, major = %d\n",
	                __FUNCTION__, major_dev);
	    } else {
	        SER_DEBUG (DEBUG_SER_ERR, "%s: failed to create proc entry for sdio\n",
	                __FUNCTION__);
	    }
	
	    for (dev = 0; dev < MAX_DEV; dev++) {
	        device_open[dev] = 0;
	    }
	    
	 	/* SD PCI Interfacing */
	 	sdio_config_pci();
 	#else
 	
	 	/* SD Host Number Initialise */
	 	initSDIO(base);
 	#endif
 	
    return 0; /* caller does not need to know my major number */
}

/*
 * sdio_cleanup_module
 *
 * Module cleanup function.  Its name is registered with the kernel
 * below.
 *
 * Unregisters itself using its DEVICE_NAME and major number, which
 * will remove all mention of it from the /proc/devices file.  The
 * driver entries in /dev will not be removed automatically, but from
 * now on they will should return ENODEV on any operation.
 *
 * Also removes its node in the internal kernel sysfs tree.
 */
#ifdef LINUX 
static void 
__exit
sdio_cleanup_module (void)
{
    int status;

    status = unregister_chrdev (major_dev, DEVICE_NAME);
    if (status < 0) {
        printk (KERN_CRIT "%s: unregister_chrdev failed major %d\n", 
                __FUNCTION__, major_dev);
    }
    
    SDHostslot_SoftwareReset(&sdh_global->m_sdslot[0], SR_RESET_ALL);
	SDHostslot_SoftwareReset(&sdh_global->m_sdslot[1], SR_RESET_ALL);    
    remove_proc_entry ("sdio", NULL);
	sdpci_attach_irq(NULL);
    return;
}
#endif



/* main IRQ handle routine */
void sdioIrqThread(u32 arg)
{
	u8 dwSlot;
	
	printf("---> sdioIrqThread <---\n");
//	printf("%s Yielding\n");
// 	IOS_YieldThread();	
	while (1) 
	{
		//printf(">IRQ Blocking qID = %d<\n",sdiQid);
		if (IOS_ReceiveMessage(sdiQid, NULL, IOS_MESSAGE_BLOCK) == IOS_ERROR_OK) 
		{	
			/* Slot IRQ status is global so use address 0 */
			u16 dwIntStatus = READ_HOST_U16((u32)sdh_global->m_sdslot[0].m_base, HOSTREG_SLOTINTRS);
			//printf("<%04x %04x>",(u32)dwIntStatus,READ_HOST_U16((u32)sdh_global->m_sdslot[0].m_base, HOSTREG_NORMINTRSTAT));
		
			/*
			 * For each slot that has its main IRQ bit set, handle IRQ
			 */
		    for (dwSlot = 0; dwSlot < sdh_global->m_slotcount; dwSlot++) 
		    {
		        if ( (1 << dwSlot) & dwIntStatus )  
		        {
		        	//printk (KERN_CRIT "%s:handle slot[%d] irq\n",__FUNCTION__,dwSlot);
		 			//printf("%s: norm int status = 0x%x\n", __FUNCTION__,
		  			//	READ_HOST_U16((u32)sdh_global->m_sdslot[dwSlot].m_base, HOSTREG_NORMINTRSTAT) );	        	
		            SDHostslot_Handleinterrupt(&sdh_global->m_sdslot[dwSlot]);
					//WRITE_HOST_U16((u32)sdh_global->m_sdslot[dwSlot].m_base, HOSTREG_NORMINTRSTAT, 0x1FF);
					//WRITE_HOST_U16((u32)sdh_global->m_sdslot[dwSlot].m_base, HOSTREG_ERRINTRSTAT, 0x1FF);            
		        }
		    }	
		}
		IOS_ClearAndEnableSDIntr(0);
  		IOS_YieldThread(); 
	}

}

#ifdef LINUX
/*
 * sdio_ser_open
 *
 * Called on open.
 */
static int 
sdio_ser_open (struct inode *inode, struct file *file) 
{
    int      minor;

    SER_DEBUG (DEBUG_SER_OPEN, "%s\n", __FUNCTION__);

    minor = MINOR(inode->i_rdev);
    SER_DEBUG (DEBUG_SER_OPEN, "%s: minor %d\n", __FUNCTION__, minor);

    if (device_open[minor]) {
        return -EBUSY;
    }

    device_open[minor]++;
 	
    return (0);
}

/*
 * sdio_ser_release
 *
 * Called on close.
 */
static int 
sdio_ser_release (struct inode *inode, struct file *file) 
{
    int minor;

    minor = MINOR(inode->i_rdev);

    if (device_open[minor] <= 0) {
        return -EPERM;
    }

    device_open[minor]--;

    return (0);
}

/*
 * sdio_ser_read
 *
 * Called on read.
 */
static int 
sdio_ser_read (struct file *file, char *buf, size_t count, loff_t*ppos) 
{

    return (0);
}

/*
 * sdio_ser_write
 *
 * Called on write.
 */
static int 
sdio_ser_write (struct file *file, const char *buf, size_t count, loff_t*ppos) 
{

    return (0);
}
#endif
char* sd_cmd_str[] = {
	"GO IDLE",
	"resrv 1",
	"GET CID",
	"GET RCA",
	"SET DSR",
	"SDIO 5 ",
	"resrv 6",
	"SEL/DES",
	"resrv 8",
	"GET CSD",
	"GETCID2",
	"resrv11",
	"CMD12ST",
	"STATUS ",
	"resrv14",
	"INACTIV",
	"BLK LEN",
	"RD BLK ",
	"RD MBLK",
	"19","20","21","22","23",
	"WR BLK ",
	"WR MBLK",
	"26",
	"SET CSD"
};

char* sdio_ioctl_str[] = {
	"NULL",
	"SD_IOGSLOTS ",
	"SD_IOGIDENT ",
	"SD_IORREG   ",
	"SD_IORCREG  ",
	"SD_RESET    ",
	"SD_IOWREG   ",
	"SD_IOWCREG  ", 
	"SD_CINTEN   ", 
	"SD_CINTDIS  ",
	"SD_CMD      ", 
	"SD_GETVOLT  ", 
	"SD_GETCLOCK ", 
	"SD_SETVOLT  ", 
	"SD_SETCLOCK ", 
	"SD_SET_BUS_WIDTH ",
	"SD_SET_SPEED     ",
	"SD_SET_CLKON     ",
	"SD_SET_CLKOFF    ",
	"SD_SET_SDCLKON   ",
	"SD_SET_SDCLKOFF  ",
	"SD_RESET_CMD     ",
	"SD_RESET_DAT     ",
	"SD_RESET_ALL     ",
	"SD_SET_SPI_MODE  ", 
	"SD_IORMCREG  ",
	"SD_IOWMCREG  ", 
	"SD_HANDLE_INSERT ", 
	"SD_HANDLE_REINIT ", 
	"SD_GET_STATUS     ", 
	"SD_WAIT_INSERT    ",
	"SD_WAIT_INTERRUPT ",
	"SD_WAIT_ERROR     ",
	"SD_DEBUG_LEVEL    ",
	"SD_SET_STATUS     ",
	"SD_GET_OCR        ",
	"SD_READ_DATA      ",
	"SD_WRITE_DATA     ",
	"SD_IOGOCR         "
};

/*
 * sdio_ser_ioctl
 *
 * Called on ioctl.
 */
int 
sdio_ser_ioctl (struct inode *inode, struct file *file, 
		unsigned int cmd, unsigned long arg) 
{
    reg_op_t reg_op;
    cmd_t cmd_op;
    volt_clock_t vc_op;
    int slot, status;
    u16 norm_int_sig_en;
    unsigned int response[4];
    #ifdef LINUX
	    caddr_t buffer;
	    int buf_len;
	#endif

	#if 0
    printf("(%s arg:0x%08X)\n", 
               	sdio_ioctl_str[cmd&0xFF], (unsigned int)arg);
	#endif
	
    switch (cmd) {
    case SD_IOGSLOTS:
        return sdh_global->m_slotcount;
        break;
    case SD_IOGOCR:
        memset(&reg_op, 0, sizeof(reg_op));
        if (copy_from_user (&reg_op, (void __user *)arg, sizeof (reg_op))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return sdh_global->m_sdslot[reg_op.dev].m_ocr;
        break;        
    case SD_IOGIDENT:
        /* bcmsdh_query_device(sdh_global); */
        break;
    case SD_IORREG:
        memset(&reg_op, 0, sizeof(reg_op));
        if (copy_from_user (&reg_op, (void __user *)arg, sizeof (reg_op))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return read_slot_register(sdh_global, reg_op.dev, 
                                  reg_op.reg, reg_op.width);
        break;
    case SD_IOWREG:
        memset(&reg_op, 0, sizeof(reg_op));
        if (copy_from_user (&reg_op, (void __user *)arg, sizeof (reg_op))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return write_slot_register(sdh_global, reg_op.dev, 
                                  reg_op.reg, reg_op.width, reg_op.value);
        break;
    case SD_IORCREG:
        memset(&reg_op, 0, sizeof(reg_op));
        if (copy_from_user (&reg_op, (void __user *)arg, sizeof (reg_op))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return read_card_register(sdh_global, reg_op.dev, 
                                  reg_op.function, reg_op.reg, reg_op.width);
        break;
    case SD_IOWCREG:
        memset(&reg_op, 0, sizeof(reg_op));
        if (copy_from_user (&reg_op, (void __user *)arg, sizeof (reg_op))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return write_card_register(sdh_global, reg_op.dev, reg_op.function, 
                                   reg_op.reg, reg_op.width, reg_op.value);
        break;
    case SD_RESET:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return slot_reset (sdh_global, slot);
        break;
    case SD_CINTEN:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        norm_int_sig_en = read_slot_register(sdh_global, slot, 
                                0x34, 2);
        norm_int_sig_en |= 0x0100;
        return write_slot_register(sdh_global, slot, 
                                  0x34, 2, norm_int_sig_en);
    case SD_CINTDIS:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        norm_int_sig_en = read_slot_register(sdh_global, slot, 
                                0x34, 2);
        norm_int_sig_en &= ~0x0100;
        
        return write_slot_register(sdh_global, slot, 
                                  0x34, 2, norm_int_sig_en);
/* ---------------------------------------------------------------------------------------------- */
    case SD_READ_DATA:
       memset(&cmd_op, 0, sizeof(cmd_op));
        if (copy_from_user (&cmd_op, (void __user *)arg, sizeof (cmd_op))) 
        {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",__FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        
        memset(&response[0], 0, sizeof(response));
       
        SER_DEBUG (DEBUG_SER_SD_CMD, "------- READ -------\n%s: <saddr=%X>\n",__FUNCTION__,cmd_op.sys_addr);
       
		status = read_card_mem(	sdh_global, 
									cmd_op.dev, 		/* slot */
						           	cmd_op.offset, 		/* SD Card Address */
						            cmd_op.sys_addr, 	/* User Buffer Address */
						            cmd_op.blk_size, 
						            cmd_op.blk_count, 
						            cmd_op.dma, 		/* Use DMA, else memory copy */
						            cmd_op.callback		/* If not NULL then Async */
						            );      
						                   
		if (cmd_op.buffer) 
        {
            if (copy_to_user(cmd_op.buffer, &response[0], sizeof(response))) 
            {
                SER_DEBUG (DEBUG_SER_ERR, "%s: copy_to_user failed\n",__FUNCTION__);
                return IOS_ERROR_ACCESS;
            }
            /*SER_DEBUG (DEBUG_SER_ERR, "%s:cresp %04X %04X %04X %04X\n",__FUNCTION__,
            	cmd_op.buffer[0],cmd_op.buffer[1],cmd_op.buffer[2],cmd_op.buffer[3]);*/
        }                                                   
        return status;
        
    case SD_WRITE_DATA:
       memset(&cmd_op, 0, sizeof(cmd_op));
        if (copy_from_user (&cmd_op, (void __user *)arg, sizeof (cmd_op))) 
        {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",__FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        
        memset(&response[0], 0, sizeof(response));
       
        SER_DEBUG (DEBUG_SER_SD_CMD, "------- WRITE -------\n%s: <saddr=%X>\n",__FUNCTION__,cmd_op.sys_addr);
       
		status = write_card_mem(	sdh_global, 
									cmd_op.dev, 		/* slot */
						           	cmd_op.offset, 		/* SD Card Address */
						            cmd_op.sys_addr, 	/* User Buffer Address */
						            cmd_op.blk_size, 
						            cmd_op.blk_count, 
						            cmd_op.dma, 		/* Use DMA, else memory copy */
						            cmd_op.callback		/* If not NULL then Async */
						            );      
						                   
		if (cmd_op.buffer) 
        {
            if (copy_to_user(cmd_op.buffer, &response[0], sizeof(response))) 
            {
                SER_DEBUG (DEBUG_SER_ERR, "%s: copy_to_user failed\n",__FUNCTION__);
                return IOS_ERROR_ACCESS;
            }
            /*SER_DEBUG (DEBUG_SER_ERR, "%s:cresp %04X %04X %04X %04X\n",__FUNCTION__,
            	cmd_op.buffer[0],cmd_op.buffer[1],cmd_op.buffer[2],cmd_op.buffer[3]);*/
        }                                                   
        return status;
                                           
    case SD_CMD:													/* ======= Command ======= */
        memset(&cmd_op, 0, sizeof(cmd_op));
        if (copy_from_user (&cmd_op, (void __user *)arg, sizeof (cmd_op))) 
        {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",__FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        
        memset(&response[0], 0, sizeof(response));
        
        /* if callback given - attach */
        if (cmd_op.callback)
        {
        	gp_sd_req->callback = (void*)cmd_op.callback;
        }
        
        if (cmd_op.command < 27)
        {
        	SER_DEBUG (DEBUG_SER_SD_CMD,"%s(CMD:%d %s)\n",__FUNCTION__,cmd_op.command,sd_cmd_str[cmd_op.command]);
        }
        else
        {
        	SER_DEBUG (DEBUG_SER_SD_CMD,"%s(CMD:%d)\n",__FUNCTION__,cmd_op.command);
        }
        
        status = do_command (sdh_global, 
        						cmd_op.dev, 
        						cmd_op.command,
                             	cmd_op.cmd_type, 
                             	cmd_op.resp_type, 
                             	cmd_op.req_size, 
                             	cmd_op.cmd_arg, 
                             	cmd_op.sys_addr,
                             	cmd_op.blk_count, 
                             	cmd_op.blk_size, 
                             	cmd_op.dma,
                             	&response[0]);
                                                          
        if (cmd_op.buffer) 
        {
            if (copy_to_user(cmd_op.buffer, &response[0], sizeof(response))) 
            {
                SER_DEBUG (DEBUG_SER_ERR, "%s: copy_to_user failed\n",__FUNCTION__);
                return IOS_ERROR_ACCESS;
            }
            if ((cmd_op.command == 7)||(cmd_op.command == 13)||(cmd_op.command == 9))
            {
	            SER_DEBUG (DEBUG_SER_SD_CMD,"%s: Resp %08X %08X %08X %08X\n",__FUNCTION__,
	            	cmd_op.buffer[0],cmd_op.buffer[1],cmd_op.buffer[2],cmd_op.buffer[3]);
            }
        }
        return 0; //status;
        
    case SD_GETVOLT:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return get_slot_voltage(sdh_global, slot);
    case SD_GET_OCR:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return slot_ocr(sdh_global, slot, 0);
    case SD_GETCLOCK:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return get_slot_clock(sdh_global, slot);
    case SD_SETVOLT:
        memset(&vc_op, 0, sizeof(vc_op));
        if (copy_from_user (&vc_op, (void __user *)arg, sizeof (vc_op))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return set_slot_voltage(sdh_global, vc_op.dev, vc_op.volt);
    case SD_SETCLOCK:
        memset(&vc_op, 0, sizeof(vc_op));
        if (copy_from_user (&vc_op, (void __user *)arg, sizeof (vc_op))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return set_slot_clock(sdh_global, vc_op.dev, vc_op.clock);
    case SD_SET_BUS_WIDTH:
        memset(&vc_op, 0, sizeof(vc_op));
        if (copy_from_user (&vc_op, (void __user *)arg, sizeof (vc_op))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return set_slot_bus_width(sdh_global, vc_op.dev, vc_op.width);
    case SD_SET_SPEED:
        break;
    case SD_SET_CLKON:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return set_clock_on(sdh_global, slot);
        break;
    case SD_SET_CLKOFF:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return set_clock_off(sdh_global, slot);
        break;
    case SD_SET_SDCLKON:
        return IOS_ERROR_INVALID;
    case SD_SET_SDCLKOFF:
        return IOS_ERROR_INVALID;
    case SD_RESET_CMD:
        return IOS_ERROR_INVALID;
    case SD_RESET_DAT:
        return IOS_ERROR_INVALID;
    case SD_RESET_ALL:
        return IOS_ERROR_INVALID;
    case SD_SET_SPI_MODE:
        return IOS_ERROR_INVALID;
    case SD_IORMCREG:
    	//printf("(r)\n");
        //memset(&reg_op, 0, sizeof(reg_op));
        if (copy_from_user (&reg_op, (void __user *)arg, sizeof (reg_op))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        #ifdef LINUX
	        buf_len = (reg_op.blk_num == 0) ? reg_op.blk_size 
	            : reg_op.blk_num * reg_op.blk_size;
	        buffer = kmalloc(buf_len, GFP_KERNEL|GFP_DMA);
	        //printf("   buffer=%x\n",buffer);
	        memset (buffer, 0, buf_len);
	        status = read_card_data(sdh_global, reg_op.dev, reg_op.function,
	                                reg_op.reg, (u32)buffer, reg_op.blk_size, 
	                                reg_op.blk_num, reg_op.dma, reg_op.busy);
	        if (reg_op.buffer) {
	            if (copy_to_user(reg_op.buffer, buffer, buf_len)) {
	                SER_DEBUG (DEBUG_SER_ERR, "%s: copy_to_user failed\n",
	                        __FUNCTION__);
	                return IOS_ERROR_ACCESS;
	            }
	        }
	        kfree (buffer);
        #else
	        status = read_card_data(sdh_global, reg_op.dev, reg_op.function,
	                                reg_op.reg, (u32)reg_op.buffer, reg_op.blk_size, 
	                                reg_op.blk_num, reg_op.dma, reg_op.busy);        
        #endif
        return status;
    case SD_IOWMCREG:
    	//printf("(w)\n");
        //memset(&reg_op, 0, sizeof(reg_op));
        if (copy_from_user (&reg_op, (void __user *)arg, sizeof (reg_op))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        #ifdef LINUX
	        buf_len = (reg_op.blk_num == 0) ? reg_op.blk_size 
	            : reg_op.blk_num * reg_op.blk_size;
	        buffer = kmalloc(buf_len, GFP_KERNEL|GFP_DMA);
	        //printf("   buffer=%x\n",buffer);
	        
	        if (reg_op.buffer) {
	            if (copy_from_user(buffer, reg_op.buffer, buf_len)) {
	                SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
	                        __FUNCTION__);
	                return IOS_ERROR_ACCESS;
	            }
	        }
	        status = write_card_data(sdh_global, reg_op.dev, reg_op.function,
	                                 reg_op.reg, (u32)buffer, reg_op.blk_size, 
	                                 reg_op.blk_num, reg_op.dma, reg_op.busy);
	        kfree (buffer);
	    #else
	        status = write_card_data(sdh_global, reg_op.dev, reg_op.function,
	                                 reg_op.reg, (u32)reg_op.buffer, reg_op.blk_size, 
	                                 reg_op.blk_num, reg_op.dma, reg_op.busy);	    
	    #endif
        return status;
       
    case SD_HANDLE_INSERT:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return handle_insert(sdh_global, slot);
    case SD_HANDLE_REINIT:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return handle_reinit(sdh_global, slot);
    case SD_GET_STATUS:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return get_status(sdh_global, slot);
    case SD_WAIT_INSERT:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        return wait_insert(sdh_global, slot);
    case SD_DEBUG_LEVEL:
        if (copy_from_user (&slot, (void __user *)arg, sizeof (int))) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                    __FUNCTION__);
            return IOS_ERROR_ACCESS;
        }
        ser_debug = slot;
        sdpci_debug = slot;
		SER_DEBUG (DEBUG_SER_ERR, "%s: Debug Level:%X\n",
                    __FUNCTION__,ser_debug);        
        return 0;
    default:
        SER_DEBUG (DEBUG_SER_ERR, "%s: unrecognized ioctl 0x%x\n",
                __FUNCTION__, cmd);
        return IOS_ERROR_INVALID;
    }

    return (0);
}

/*
 * sdio_ser_proc_read
 *
 * Called on proc read.
 */
int 
sdio_ser_proc_read (char *buf, char **start, off_t offset, int count,
                           int *eof, void *data)
{
    int len = 0;

    return len;
}

#ifdef LINUX
/*
 * Module_init() and module_exit() are macros which handle the
 * registration and cleanup of kernel modules by registering the
 * corresponding names with the kernel.  This is new for Linux 2.6.
 * In Linux 2.4 and previously, init and cleanup were magic names, 
 * not defined explicitly like this.  Check <linux/init.h> for details.
 */
module_init (sdio_init_module);
module_exit (sdio_cleanup_module);
#endif

/* eof */
