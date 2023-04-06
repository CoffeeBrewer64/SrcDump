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

#ident "$Id: sd.h,v 1.1 2006/03/16 19:22:55 gbarnard Exp $"

#define MAX_DEV 4

typedef enum _status {
    st_illegal, /* not an error but an invalid value */
    st_success,
    st_fail_bad_op,
    st_fail_no_ops,
    st_fail_no_slots,
    st_fail_bad_slot_count,
    st_fail_no_sdh,
    st_fail_bad_slot_window,
} status_t;

#define IOS_ERROR_SDIO_ERR       -64

typedef enum SDStatusCode
{
        SD_STATUS_SUCCESS                         = 0x00000000L,
        SD_STATUS_PENDING                         = 0x00000001L,
        SD_STATUS_BUFFER_OVERFLOW                 = 0xC0000001L,
        SD_STATUS_DEVICE_BUSY                     = 0xC0000002L,
        SD_STATUS_UNSUCCESSFUL                    = 0xC0000003L,
        SD_STATUS_NOT_IMPLEMENTED                 = 0xC0000004L,
        SD_STATUS_ACCESS_VIOLATION                = 0xC0000005L,
        SD_STATUS_INVALID_HANDLE                  = 0xC0000006L,
        SD_STATUS_INVALID_PARAMETER               = 0xC0000007L,
        SD_STATUS_NO_SUCH_DEVICE                  = 0xC0000008L,
        SD_STATUS_INVALID_DEVICE_REQUEST          = 0xC0000009L,
        SD_STATUS_NO_MEMORY                       = 0xC000000AL,
        SD_STATUS_BUS_DRIVER_NOT_READY            = 0xC000000BL,
        SD_STATUS_DATA_ERROR                      = 0xC000000CL,
        SD_STATUS_CRC_ERROR                       = 0xC000000DL,
        SD_STATUS_INSUFFICIENT_RESOURCES          = 0xC000000EL,
        SD_STATUS_DEVICE_NOT_CONNECTED            = 0xC0000010L,
        SD_STATUS_DEVICE_REMOVED                  = 0xC0000011L,
        SD_STATUS_DEVICE_NOT_RESPONDING           = 0xC0000012L,
        SD_STATUS_CANCELED                        = 0xC0000013L,
        SD_STATUS_RESPONSE_TIMEOUT                = 0xC0000014L,
        SD_STATUS_DATA_TIMEOUT                    = 0xC0000015L,
        SD_STATUS_DEVICE_RESPONSE_ERROR           = 0xC0000016L,
        SD_STATUS_DEVICE_UNSUPPORTED              = 0xC0000017L,
        SD_STATUS_SHUT_DOWN                       = 0xC0000018L,
        SD_STATUS_OUT_OF_RANGE                    = 0xC0000019L,
        SD_STATUS_FUNCTION_NUMBER_ERR             = 0xC0000020L,
        SD_STATUS_ILLEGAL_CMD                     = 0xC0000021L,
        SD_STATUS_CMD_TIMEOUT                     = 0xC0000022L,
        SD_STATUS_UNKNOWN_ERR                     = 0xC0000023L
} SD_API_STATUS;

/*
 * enum for response types 
 */
typedef enum  _sd_response_type
{
    NoResponse  = 0,
    ResponseR1  = 1,
    ResponseR1b = 2,
    ResponseR2  = 3,
    ResponseR3  = 4,
    ResponseR4  = 5,
    ResponseR5  = 6,
    ResponseR6  = 7
} sd_response_type;

#define NUM_RESP_REGS 4
/*
 * Global memory structure passed to bus driver.
 * 
 * command: to execute.
 * commmand type: read write.
 * response type: R4, etc
 * req_size: for block copy.
 * response: response for results from resp0-7.
 * callback: callback for async
 * callback_on_irq: on which irqs do we want callback to be called
 */
typedef struct _sd_request {
    unsigned int command;
    unsigned int cmd_type;
    unsigned int resp_type;
    unsigned int req_size;
    unsigned int cmd_arg;
    unsigned int cmd_wait;
    unsigned int status;
    unsigned int norint;
    unsigned int (*callback)(void *arg);
    unsigned int callback_on_irq;
    unsigned int heartbeat;
    unsigned int response[NUM_RESP_REGS];
} sd_request;


/*
 * Inlines
 */

/*
 * Prototypes
 */
/*
 * Defines
 */
#ifndef bool
typedef unsigned int bool;
#define true 1
#define false 0
#endif

/*
 * SD PCI REGISTERS
 */
#define SD_PCI_SLOT_INFO     0x40

/*
 * Slots
 */
#define SDHOST_MAX_SLOTS     6

/*
 * Macros
 */

/*
 * These refer to in-lines in device.h
 */
#define sd_get_drvdata(c)   dev_get_drvdata(&(c)->dev)
#define sd_set_drvdata(c,d) dev_set_drvdata(&(c)->dev, d)

/*
 * This is obscure.   This returns the address of the first
 * location past the end of the passed-in struct.   There
 * are other ways to do this.
 */
#define sd_priv(x)    ((void *)((x) + 1))
#define sd_dev(x)     ((x)->dev)

struct sd_host;

extern struct sd_host *sdh_global;

typedef enum _sd_slot_event {
    NOP,                // no operation
    DeviceEjected,      // device was ejected
    DeviceInserted,     // device was inserted
    DeviceInterrupting, // device is interrupting
    BusRequestComplete, // a bus request was completed
} sd_slot_event, *psd_slot_event;

typedef enum _sd_slot_state{
    SlotInactive = 0,    // slot is inactive
    SlotIdle,            // slot is idle (after power up)
    Ready,               // the slot is ready, the client driver now has control
    SlotDeviceEjected,   // the device is being ejected
    SlotInitFailed       // slot initialization failed
} sd_slot_state, *psd_slot_state;

#define wait_queue_head_t u32
#define size_t u32

/* 
 * Structs
 */
struct sd_slot_base {
    void*			   m_base;
    u16                m_slotindex;               /* physical slot number */
    volatile u8        *m_pbRegisters;         /* memory-mapped registers */
    struct sd_host     *sdh;
	sd_slot_state      m_slotstate;
	u32                m_cardtype;				/* SD SDIO or Combo */
    u32				   m_capability;			/* Capabilities */
    u32				   m_ocr;					/* Save copy of OCR */
    u32                m_SysIntr;				/* system interrupt */
    u32                m_VddWindows;			/* supported VDD windows */
    u32                m_dwMaxClockRate;       /* maximum clock rate */
    u32                m_TimeoutControl;     /* timeout control value */
    u32                m_dwMaxBlockLen;        /* maximum block length */
    u32                m_pbDmaBuffer;          /* virtual address of DMA buffer */
    u32                m_paDmaBuffer;          /* physical address of DMA buffer */
    u16                m_wRegClockControl;     /* register value of Clock Control */
    u16                m_wIntSignals;          /* saved int signals for powerup */
#if 0
    sdslot_power_state m_cpsCurrent;           /* current power state */
    sdslot_power_state m_cpsAtPowerDown;       /* power state at PowerDown() */
#endif
    u8                 m_uDefaultWakeupControl;   /* wakeup source list */
    u8                 m_bWakeupControl;           /* current wakeup interrupts */
    u32     		   m_fCommandCompleteOccurred;     /* has the Command Complete occurred for the current transfer? */
    u32				   m_fSleepsWithPower : 1;         /* keep power in PowerDown()? */
    u32				   m_fPowerUpDisabledInts : 1;     /* did PowerUp disable SDIO card interrupts? */
    u32				   m_fIsPowerManaged : 1;          /* is the power manager handling us? */
    u32				   m_fSDIOInterruptsEnabled : 1;   /* are SDIO card interrupts enabled? */
    u32				   m_fCardPresent : 1;             /* is a card present */
    u32				   m_fAutoCMD12Success : 1;        /* AutoCMD12 success */
    u32				   m_fCheckSlot : 1;               /* does HandleInterrupt() need to be run? */
    u32				   m_fCanWakeOnSDIOInterrupts : 1; /* can wake on SDIO interrupts */
    u32				   m_f4BitMode : 1;                /* 4 bit bus mode? */
    u32				   m_fFakeCardRemoval : 1;         /* should we simulate card removal? */
	u32				   Flags;
	u16				   PowerUpDelay;
    wait_queue_head_t  m_card_insert;                 /* event queues */
    wait_queue_head_t  m_card_interrupt;
    wait_queue_head_t  m_card_error;
};

struct sd_host_ops 
{
	/* 
     * Power management for host 
     */
	u32 	(*sdhostdeterminpowerstate)(struct sd_host *);
	/* 
     * Need to know how many slots are available.
     */
	u8	(*sdhostdetermineslotcount)(struct sd_host *);
	/* 
     * Its power awake function: sometimes needed for embedded platforms.
     */
	u8	(*sdhostdeterminAllotWakeuponSDIOInterrupts)(struct sd_host *);
	/* 
     * To allocate and intilize base pointer address and memory for
     * the slots  .
     */
	u8	(*sdhostinitilizeslotwindow)(struct sd_host *);
	/* 
     * For removing base pointer memory for the slots.
     */
	u8	(*sdhostdeinitilizeslotwindow)(struct sd_host *);

};

struct sd_host 
{
	struct sd_slot_base	m_sdslot[SDHOST_MAX_SLOTS];
	struct device		*dev;
	struct sd_host_ops	*ops;
	u32 				base;
	u32 				f_min;
	u32 				f_max;
	u32					ocr_avail;
	char				host_name[8];
	
	u8  				cardtype;		/* better located in slot, since each slot could have different card */

	/* host specific block data */

	u32 				max_seg_size;	/* see blk_queue_max_segment_size */
	u16 				max_hw_segs;	/* see blk_queue_max_hw_segments */
	u16 				max_phys_segs;	/* see blk_queue_max_phys_segments */
	u16 				max_sectors;	/* see blk_queue_max_sectors */
	u16 				unused;

	/* private data */
#if 0
	struct sd_ios		ios;		/* current io bus settings */


	struct list_head	cards;		/* devices attached to this host */

	wait_queue_head_t	wq;
	spinlock_t			lock;		/* card_busy lock */
	struct sd_card		*card_busy;	/* the MMC card claiming host */
	struct sd_card		*card_selected;	/* the selected MMC card */
#endif

	u8  				m_slotcount;

#if 0
	struct work_struct	detect;
	sd_slot_event		event;
#endif
};

struct sdpci_host {
	struct sd_host		*sd;
	#if 0
	spinlock_t			lock;
	spinlock_t			irslock;
	#endif
	struct resource		*res;
	int					irq;
	int					dma;
	u32				    imask;
	u32 				errmask;
	u8  				power_mode;
	u32 				blocksize;

	#if 0
	dma_addr_t			sg_dma;
	#endif

	struct 	pci_dev		*dev;
	u32 				dma_size;
	u32 				dma_dir;
};

struct sd_host *sd_alloc_host(int extra, struct device *dev);

int sd_add_host(struct sd_host *host);

void sd_free_host(struct sd_host *host);
void sd_remove_host(struct sd_host *host);

/*
 * sdbuscore.c
 */
extern int sd_suspend_host(struct sd_host *host, u32 state);
extern int sd_resume_host(struct sd_host *host);

/*
 * sd_slot.c
 */
 
extern void DoEnableSDIOInterrupts(struct sd_slot_base *slot, u8 fEnable);
extern void DumpSlotRegs(struct sd_slot_base *slot);

extern void SDHostslot_Resetstruct(struct sd_slot_base *slot);
extern void SDHostslot_Handleinterrupt( struct sd_slot_base *slot);
extern void SDHostslot_Handlecardinsert( struct sd_slot_base *);
extern void SDHostslot_Resetstru(struct sd_slot_base *);
extern void SDHostslot_GetCapability(struct sd_slot_base *);
extern void SDHostslot_DetermineVddWindows(struct sd_slot_base *);
extern void SDHostslot_init(struct sd_slot_base *slot);
extern void SDHostslot_Enableinterrput(struct sd_slot_base *slot, u8 fEnable);
extern void SDHostslot_Handlecardremove(struct sd_slot_base *slot, u8 fCancelRequest);
extern void SDHostslot_SDClockOn(struct sd_slot_base *slot);
extern void SDHostslot_SDClockOff(struct sd_slot_base *slot);
extern void SDHostslot_reportslotstatechange(struct sd_slot_base *slot, sd_slot_event event);
extern void SDHostslot_Enableinterrput( struct sd_slot_base *slot, u8 fEnable);
extern void SDHostslot_Setvoltage(struct sd_slot_base *slot, u32 uvddsetting);
extern void SDHostslot_EnableLED(struct sd_slot_base *slot, u8 fEnable);
extern void SDHostslot_reinit(struct sd_slot_base *slot);
extern u32  SDHostslot_Desiredvdd( struct sd_slot_base *slot);
extern u32  SDHostslot_maxvdd( struct sd_slot_base *slot);
extern u32  SDHostslot_Maxclock(struct sd_slot_base *slot);
extern u32  SDHostslot_Maxblocklen(struct sd_slot_base *slot);
extern u8   SDHostslot_Findwakeupsources(struct sd_slot_base *slot);
extern u8   SDHostslot_Commandcomplete(struct sd_slot_base *slot);
extern u8   SDHostslot_SoftwareReset( struct sd_slot_base *slot, u8 mask);
extern SD_API_STATUS SDHostslot_Handleerror( struct sd_slot_base *);
extern SD_API_STATUS SDHostslot_start(struct sd_slot_base *slot);

/*
 * sdio_util.c
 */
extern int read_slot_register(struct sd_host *sdh, 
                              int slot, int reg, int width);
extern int write_slot_register(struct sd_host *sdh, int slot, 
                               int reg, int width, int data);
extern int read_card_register(struct sd_host *sdh, int slot, 
                              int function, int reg, int width);
extern int write_card_register(struct sd_host *sdh, int slot, 
                               int function, int reg, int width, int data);
extern int slot_reset(struct sd_host *sdh, int slot);
extern int do_command (struct sd_host *sdh, int slot, int cmd, 
                       int cmd_type, int resp_type, int req_size, 
                       int sysaddr, int cmd_arg, int blk_cnt, 
                       int blk_size, int dma, unsigned int *resp);
extern int set_clock_on(struct sd_host *sdh, int slot);
extern int set_clock_off(struct sd_host *sdh, int slot);
extern int read_card_data(struct sd_host *sdh, int slot, unsigned int function,
                          unsigned int reg, unsigned int sysaddr, 
                          unsigned int blk_size, unsigned int blk_cnt, 
                          unsigned int dma, unsigned int resp_with_busy);
extern int write_card_data(struct sd_host *sdh, int slot, unsigned int function,
                           unsigned int reg, unsigned int sysaddr, 
                           unsigned int blk_size, unsigned int blk_cnt, 
                           unsigned int dma, unsigned int resp_with_busy);
extern int read_card_mem(	struct sd_host *sdh, int slot, 
               	unsigned int offset, 	/* SD Card Address */
                unsigned int sysaddr, 	/* User Buffer Address */
                unsigned int blk_size, 
                unsigned int blk_cnt, 
                unsigned int dma, 		/* Use DMA, else memory copy */
                unsigned int callback	/* If not NULL then Async */
                );
extern int write_card_mem(	struct sd_host *sdh, int slot, 
               	unsigned int offset, 	/* SD Card Address */
                unsigned int sysaddr, 	/* User Buffer Address */
                unsigned int blk_size, 
                unsigned int blk_cnt, 
                unsigned int dma, 		/* Use DMA, else memory copy */
                unsigned int callback	/* If not NULL then Async */
                );
extern unsigned int get_slot_voltage(struct sd_host *sdh, int slot);
extern unsigned int get_slot_clock(struct sd_host *sdh, int slot);
extern unsigned int set_slot_voltage(struct sd_host *sdh, int slot,
                                     int new);
extern unsigned int set_slot_clock(struct sd_host *sdh, int slot,
                                   int new);
extern unsigned int set_slot_bus_width(struct sd_host *sdh, int slot,
                                   int new);
extern unsigned int handle_insert (struct sd_host *sdh, int slot);
extern unsigned int handle_reinit (struct sd_host *sdh, int slot);
extern unsigned int get_status (struct sd_host *sdh, int slot);
extern unsigned int wait_insert (struct sd_host *sdh, int slot);
extern unsigned int slot_ocr (struct sd_host *sdh, int dev, int data);

#ifndef LINUX
#define __init
struct inode { 
	u32 i_rdev;
};
	
struct file {
	u32 name;
};	

typedef char* caddr_t;

#define loff_t u32
#define off_t u32

#define printk printf
#define __user 
#define __init	
extern int __init sdio_init_module (u32 base);
extern int sdio_ser_ioctl (struct inode *inode, struct file *file, 
				unsigned int cmd, unsigned long arg);
				
#endif
/*
 * sdstdhost.c
 */
extern u8 READ_HOST_U8(u32 base, u16 reg);
extern void WRITE_HOST_U8(u32 base, u16 reg, u8 val);
extern u16 READ_HOST_U16(u32 base, u16 reg);
extern void WRITE_HOST_U16(u32 base, u16 reg, u16 val);
extern u32 READ_HOST_U32(u32 base, u16 reg);
extern void WRITE_HOST_U32(u32 base, u16 reg, u32 val);

/*
 * sd-pci.c
 */
extern char *decode_status (status_t status);

/* eof */
