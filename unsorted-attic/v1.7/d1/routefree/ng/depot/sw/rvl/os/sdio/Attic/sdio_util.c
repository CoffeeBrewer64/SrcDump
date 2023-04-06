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

#ident "$Id: sdio_util.c,v 1.6 2006/03/20 07:27:25 gbarnard Exp $"

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
	
	#include <asm/uaccess.h>
	#include <asm/io.h>
	#include <asm/delay.h>
	
	#include "../include/sd.h"
	#include "../include/sd_pci.h"
	#include "../include/sd_card.h"
	#include "../include/sd_host.h"
	#include "../include/sd_ioctl.h"
	#include "../include/sd_debug.h"
	
	
#else
	#include <ios.h>
	#ifdef VERSA
		#include "ios_pci.h"
		#include <versaios.h>
	#endif
	#include <iostypes.h>
	#include <ioslibc.h>
	
	#include "sd.h"
	#include "sd_card.h"
	#include "sd_host.h"
	#include "sd_ioctl.h"
	#include "sd_debug.h"
		
	extern void	msleep(u32 msecs);
	extern void	msleepx(u32 msecs, char* str);
	
	u32 virt_to_bus(void* vaddr)
	{
		return (u32)vaddr;
	}
	
	#define EFAULT -IOS_ERROR_ACCESS

#endif

extern void msleep(unsigned int msecs);

#define MAX_TIMEOUT    5

extern struct _sd_request* gp_sd_req;

static char *reg_names[] = {
    "sysaddrlo", /* 0x00, 0 */
    "sysaddrhi", /* 0x02, 1 */
    "blksz",     /* 0x04, 2 */
    "blkcnt",    /* 0x06, 3 */
    "arglo",      /* 0x08, 4 */
    "arghi",     /* 0x0a, 5 */
    "transmod",  /* 0x0c, 6 */
    "command",   /* 0x0E, 7 */
    "res0",      /* 0x10, 8 */
    "res1",   /* 0x12, 9 */
    "res2",   /* 0x14, 10 */
    "res3",   /* 0x16, 11 */
    "res4",   /* 0x18, 12 */
    "res5",   /* 0x1A, 13 */
    "res6",   /* 0x1C, 14 */
    "res7",   /* 0x1E, 15 */
    "buffdp0",   /* 0x20, 16 */
    "buffdp1",   /* 0x22, 17 */
    "pstatelo",   /* 0x24, 18 */
    "pstatehi",   /* 0x26, 19 */
    "host/pwrctrl",   /* 0x28, 20 */
    "blockgap/wake",   /* 0x2A, 21 */
    "clockctrl",   /* 0x2C, 22 */
    "timeout/reset",   /* 0x2E, 23 */
    "normintrstat",   /* 0x30, 24 */
    "errintrstat",   /* 0x32, 25 */
    "norintrsen",   /* 0x34, 26 */
    "errintrsen",   /* 0x36, 27 */
    "norintrsgen",   /* 0x38, 28 */
    "errintrsgen",   /* 0x3A, 29 */
    "auto12stat",   /* 0x3C, 30 */
    "missing",      /* 0x3E, 31 */
    "capabilitylo",   /* 0x40, 32 */
    "capabilityhi",   /* 0x42, 33 */
    "capbilityrlo",   /* 0x44, 34 */
    "capbilityrhi",   /* 0x46, 35 */
    "maxcurr",   /* 0x48, 36 */

};

#if 0
static char *status[]={
	"idle ",
	"ready",
	"ident",
	"stby ",
	"tran ",
	"data ",
	"rcv  ",
	"prg  ",
	"dis  "
	};   
#endif
        
static char *
reg_name(int reg)
{

    reg = reg >> 1;

    if ((reg >= 0) && (reg < (sizeof(reg_names)/sizeof(char *)))) {
        return reg_names[reg];
    }

    return "unknown";
}


u8
READ_HOST_U8(u32 base, u16 reg)
{
    u8 ret;

	#ifdef LINUX
    	ret = readb((void __iomem *)base + reg);
    #else
    
    	#if 1
	    	u32 absolute = base+reg;
	    	u32* bp32 = (u32*)(absolute&0xFFFFFFFC);
	    	u32 data = *bp32;
	    	int byte = (absolute&0x00000003);
	    	//printf("abs=%08x, bp32=%08x, d32=%08x",absolute,bp32,data);
	    	if (byte==0)
	    	{
	    		ret = (data & 0x000000FF);
	    	}
	    	else if (byte==1)
	    	{
	    		ret = (data & 0x0000FF00)>>8;
	    	}
	    	else if (byte==2)
	    	{
	    		ret = (data & 0x00FF0000)>>16;
	    	}
	    	else if (byte==3)
	    	{
	    		ret = (data & 0xFF000000)>>24;
	    	}	    		    	
	    	//printf(", dat=%02x\n",ret);
    	#else        
	    	u8* bp = (u8*)(base + reg);
	    	ret = *bp;
	    #endif
   	#endif
    

    SER_DEBUG (DEBUG_SER_REG_READ, "%s: reg 0x%x ==> 0x%x (%s)\n",
               __FUNCTION__, reg, ret, reg_name(reg));

    return ret; 
}

void
WRITE_HOST_U8(u32 base, u16 reg, u8 val)
{

    SER_DEBUG (DEBUG_SER_REG_WRITE, "%s: reg 0x%x <== 0x%x (%s)\n",
               __FUNCTION__, reg, val, reg_name(reg));

	#ifdef LINUX
	    writeb(val, (void __iomem *)base + reg);
    #else
    	#if 1
	    	u32 absolute = base+reg;
	    	u32* bp32 = (u32*)(absolute&0xFFFFFFFC);
	    	u32 data = *bp32;
	    	int byte = (absolute&0x00000003);
	    	//printf("abs=%08x, bp32=%08x, d32=%08x",absolute,bp32,data);
	    	if (byte==0)
	    	{
	    		data = (data & 0xFFFFFF00)|val;
	    	}
	    	else if (byte==1)
	    	{
	    		data = (data & 0xFFFF00FF)|(val<<8);
	    	}
	    	else if (byte==2)
	    	{
	    		data = (data & 0xFF00FFFF)|(val<<16);
	    	}
	    	else if (byte==3)
	    	{
	    		data = (data & 0x00FFFFFF)|(val<<24);
	    	}	    		    	
	    	//printf(", dat=%08X",data);
	    	*bp32 = data;
	    	//printf(" now=%08X\n",*bp32);
    	#else    
	 		u8* bp = (u8*)(base + reg);
	    	*bp = val;
    	#endif
   	#endif
}

u16
READ_HOST_U16(u32 base, u16 reg)
{
    u16 ret;

	#ifdef LINUX
    	ret = readw((void __iomem *)base + reg);
    #else
   	#if 1
	    	u32 absolute = base+reg;
	    	u32* bp32 = (u32*)(absolute&0xFFFFFFFC);
	    	u32 data = *bp32;
	    	int byte = (absolute&0x00000002);
	    	//printf("abs=%08x, bp32=%08x, d32=%08x",absolute,bp32,data);
 			if (byte==0)
	    	{
	    		ret = (data & 0x0000FFFF);
	    	}
	    	else if (byte==2)
	    	{
	    		ret = (data & 0xFFFF0000)>>16;
	    	}	    		    	
	    	//printf(", dat=%08x\n",data);
    	#else            
	 		u16* bp = (u16*)(base + reg);
	    	ret = *bp;
	    #endif
   	#endif
    SER_DEBUG (DEBUG_SER_REG_READ, "%s: reg 0x%x ==> 0x%x (%s)\n",
               __FUNCTION__, reg, ret, reg_name(reg));

    return ret;
}

void
WRITE_HOST_U16(u32 base, u16 reg, u16 val)
{
    SER_DEBUG (DEBUG_SER_REG_WRITE, "%s: reg 0x%x <== 0x%x (%s)\n",
               __FUNCTION__, reg, val, reg_name(reg));
	#ifdef LINUX
	    writew(val, (void __iomem *)base + reg);
    #else
    	#if 1
	    	u32 absolute = base+reg;
	    	u32* bp32 = (u32*)(absolute&0xFFFFFFFC);
	    	u32 data = *bp32;
	    	int byte = (absolute&0x00000002);
	    	//printf("abs=%08x, bp32=%08x, d32=%08x, val=%04x",absolute,bp32,data,val);
	    	if (byte==0)
	    	{
	    		data = (data & 0xFFFF0000)|val;
	    	}
	    	else if (byte==2)
	    	{
	    		data = (data & 0x0000FFFF)|(val<<16);
	    	}
	    	//printf(", dat=%08x\n",data);
	    	*bp32 = data;
    	#else
	 		u16* bp = (u16*)(base + reg);
	    	*bp = val;
    	#endif
   	#endif
}

u32
READ_HOST_U32(u32 base, u16 reg)
{
    u32 ret;

	#ifdef LINUX
    	ret = readl((void __iomem *)base + reg);
    #else
		u32* bp = (u32*)(base + reg);
    	ret = *bp;
   	#endif
    SER_DEBUG (DEBUG_SER_REG_READ, "%s: reg 0x%x ==> 0x%x (%s)\n",
               __FUNCTION__, reg, ret, reg_name(reg));

    return ret;
}

void
WRITE_HOST_U32(u32 base, u16 reg, u32 val)
{
    SER_DEBUG (DEBUG_SER_REG_WRITE, "%s: reg 0x%x <== 0x%x (%s)\n",
               __FUNCTION__, reg, val, reg_name(reg));

	#ifdef LINUX
	    writel(val, (void __iomem *)base + reg);
    #else
 		u32* bp = (u32*)(base + reg);
    	*bp = val;
   	#endif
}

#define TIMEOUT  100000
#define TIMEOUT1 10000

/*
 * rw_direct_arg
 *
 * This constructs the 32-bit argument value HOSTREG_ARG
 * for the cmd52 io_rdw_direct command that is used to 
 * read and write 8-bit card registers.
 *
 *   31   30  28  27   26   25             9   8  7          0
 * +-----+------+-----+---+------------------+---+------------+
 * | R/W | Func | Raw | S | Register Address | S | Write Data |
 * +-----+------+-----+---+------------------+---+------------+
 *    1     3      1    1          17          1        8
 *
 * pslot: slot base address.
 * rw:    read/write flag
 * func:  function address on card.   0 is common function.
 * raw:   read after write check.
 * reg:   address of eight-bit register.
 * data:  data to write, ignored on read.
 */
int
rw_direct_arg (struct sd_slot_base *pslot, int rw, int func, 
               int raw, int reg, int data)
{
    u32 arg;

    //SER_DEBUG (DEBUG_SER_ERR, "%s: slot 0x%x rw 0x%x func 0x%x raw 0x%x reg 0x%x data 0x%x\n",
    //        __FUNCTION__, (u32)pslot, rw, func, 
    //           raw, reg, data);

    if (!pslot) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null pslot\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    arg = IO_RW_DIRECT_ARG(rw, func, 0, reg, data);

    //SER_DEBUG (DEBUG_SER_ERR, "%s: arg 0x%x\n",
    //        __FUNCTION__, arg);

    return arg;
}

/*
 * rw_direct_ext_arg
 *
 * This constructs the 32-bit argument value HOSTREG_ARG
 * for the cmd53 io_rdw_extended command that is used to 
 * read and write multiple 8-bit card registers.
 *
 *    31  30  28  27    26 25               9 8              0
 * +-----+------+-----+---+------------------+----------------+
 * | R/W | Func | Blk |Op | Register Address |  Data Length   |
 * +-----+------+-----+---+------------------+----------------+
 *    1     3      1    1          17                9   
 *
 * pslot: slot base address.
 * rw:    read/write flag
 * func:  function address on card.   0 is common function.
 * blk:   block mode
 * op:    op-code (0 - r/w fixed address, 1 - r/w incrementing address)
 * reg:   address of eight-bit register.
 */
int
rw_direct_ext_arg (struct sd_slot_base *pslot, int rw, int func, 
               int blkmode, int opcode, int reg, int count)
{
    u32 arg;

    //SER_DEBUG (DEBUG_SER_REG_MREAD, "%s:\n",
    //        __FUNCTION__);

    if (!pslot) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null pslot\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    arg = IO_RW_DIRECT_EXT_ARG(rw, func, blkmode, opcode, reg, count);

   SER_DEBUG (DEBUG_SER_REG_MREAD, 
    //printf(
               "%s: ARG32=0x%04x, rw %d func %d blk %d op %d reg 0x%04X cnt %d\n",
            __FUNCTION__, arg, rw, func, blkmode, opcode, reg, count);

    return arg;
}

/*
 * rw_transfer_mode
 *
 * This constructs the 16-bit transfer mode register for the cmd53
 * io_rdw_extended command that is used to read and write multiple
 * 8-bit card registers.
 *
 *  15                              6   5   4   3   2   1   0 
 * +----------------------------------+---+---+---+---+---+---+
 * |  Reserved                        | M | d | R | A | B | D |
 * +----------------------------------+---+---+---+---+---+---+
 *                                      1   1   1   1   1   1
 *
 *  D:  DMA enable (1 enable)
 *  B:  Block count enable (1 enable)
 *  A:  Auto CMD 12 enable (1 enable)
 *  R:  Reserved
 *  d:  Direction (1 read, 0 write)
 *  M:  Multi-single block.  (0 single block)
 */
unsigned short
rw_transfer_mode (int dma, int blk_cnt, int auto12, int rw, int multi)
{
    unsigned short tmode = 0;



    tmode = (multi & 0x1) << 5
        | (rw & 0x1 ) << 4 
        | 0 << 3
        | (auto12 & 0x1) << 2
        | (blk_cnt & 0x1) << 1
        | (dma & 1);

    SER_DEBUG (DEBUG_SER_REG_MWRITE, 
    			"%s: tmode = 0x%04X, dma %d blk %d auto12 %d rw %d m %d\n",
               __FUNCTION__, tmode, dma, blk_cnt, auto12, rw, multi);
    return tmode;
}

/*
 * slot_ocr, Operating Conditions, This is where power is applied.
 */
bool
slot_ocr (struct sd_host *sdh, int dev, int data)
{
    int status;
    unsigned int regs[4];
    unsigned int ocr;
   	int i=10;	/* currently the do loop takes 3ms to complete, total timeout in spec is 1s */
    struct sd_slot_base *pslot = &sdh->m_sdslot[dev];
    
    SER_DEBUG (DEBUG_SER_CMD, "\n%s    ---    Try SDIO:    ---\n",__FUNCTION__);
    status = do_command(sdh, dev, 5, 2, 4, 0, data, 0, 0, 0, 0, &regs[0]);
    if (status < 0) 
    {
        /* Some function is turning off power?, maybe reset slot on timeout ... */
        WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_PWRCTRLREG, 0xF);
        WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_TIMEOUTCTRL, 0xE);
        //msleep (1000);
    	
        SER_DEBUG (DEBUG_SER_CMD, "\n%s    ---    Try SD:    ---\n",__FUNCTION__);
    	status = do_command(sdh, dev, 0, SD_COMMAND, NoResponse, 0,    0, 0, 0, 0, 0, &regs[0]);
    	msleep (1000);
    	
    	status = do_command(sdh, dev, 55, SD_COMMAND, ResponseR1, 0,    0, 0, 0, 0, 0, &regs[0]); 
    	if (status!=0) 
    	{
    		DumpSlotRegs(pslot);
    		return false;
    	}
    	ocr = 0x0; /* 0x00FF8000;*/ /* 0x0 according to spec, value according to palm */
    	/* 	This will return OCR with cards voltage range */
    	status = do_command(sdh, dev, 41, SD_COMMAND, ResponseR3, 0,  ocr, 0, 0, 0, 0, &regs[0]);
	    SER_DEBUG (DEBUG_SER_CMD, "%s    OCR:R0=0x%X R1=0x%X\n",__FUNCTION__,regs[0],regs[1]);
    	/* NB Set Desired Card voltage (range), not zero and valid else card disables! */
    	ocr = 0x00FF8000;	/* Somewhat empirical */
    	do
    	{
	    	msleep (100); /* 1ms replace with sleep ... message queue block or schedule timeout */
	    	status = do_command(sdh, dev, 55, SD_COMMAND, ResponseR1, 0,    0, 0, 0, 0, 0, &regs[0]); 
	    	status = do_command(sdh, dev, 41, SD_COMMAND, ResponseR3, 0,  ocr, 0, 0, 0, 0, &regs[0]);
	    	i--;
    	}
    	while (((regs[0]&(unsigned int)0x80000000)==0)&&(i>0));
    	ser_debug = 1;
    		
		if (i==0)
		{
       		SER_DEBUG (DEBUG_SER_ERR, "%s: Timeout no SD found: 0x%x\n", 
                __FUNCTION__, status);
        	return false;
 		}
 		
   	    ocr = regs[0];
	    SER_DEBUG (DEBUG_SER_ERR, "%s: ******* SD Card found, OCR:0x%x *******\n", 
	            __FUNCTION__, ocr);	    	
 
    	/* Get CARD CID, CMD2 */
	    status = do_command(sdh, dev, 2, SD_COMMAND, ResponseR2, 0,    0, 0, 0, 0, 0, &regs[0]);  
	    if (status < 0) 
	    {
       		SER_DEBUG (DEBUG_SER_ERR, "%s: SD get CID failed: 0x%x\n", 
                __FUNCTION__, status);
	    	return false;
	    }
	    //printf("Setting Card Type = SD\n");
	    
	    pslot->m_cardtype = SD_TYPE_MEMORY;
	    pslot->m_fCardPresent = 1;
	    pslot->m_ocr = ocr;
		return true; 
    }
    
    pslot->m_cardtype = SD_TYPE_SDIO;
    pslot->m_fCardPresent = 1;
    

    do 
    {
    	msleep (100); /* 1ms replace with sleep ... message queue block or schedule timeout */
    	status = do_command(sdh, dev, 5, 2, 4, 0, data, 0, 0, 0, 0, &regs[0]);
		i--;
    } 
    while (((regs[0]&(unsigned int)0x80000000)==0)&&(i>0));


	if (i==0)
	{
		SER_DEBUG (DEBUG_SER_ERR, "%s: Timeout on SDIO init: 0x%x\n", 
	        __FUNCTION__, status);
		return false;
	} 
	else
	{   
	    /* 24 bits */
	    ocr = regs[0];
		
	    SER_DEBUG (DEBUG_SER_ERR, "%s: ******* SDIO Card found, OCR:0x%x *******\n", 
	            __FUNCTION__, ocr);
	}
    pslot->m_ocr = ocr;
    return true;
}

/*
 * slot_power
 */
bool
slot_power (struct sd_host *sdh, int dev)
{
    unsigned int cap, reg, power_data, vsel;

	/* write to power control */
    reg = 0x29;
#if 0    
    if (write_slot_register(sdh, dev, reg, 1, 0x0E) != 0) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: bad slot reg write 0x%x\n",
                 __FUNCTION__, reg);
        return false;
    }
#endif
    power_data = read_slot_register(sdh, dev, reg, 1);

    SER_DEBUG (DEBUG_SER_SD_CMD, "%s voltage      = 0x%x\n",
             "       ", power_data);

    reg = 0x40;
    cap = read_slot_register(sdh, dev, reg, 4);

    SER_DEBUG (DEBUG_SER_SD_CMD, "%s capabilities = 0x%x\n",
             "       ", cap);

    vsel = (power_data & 0xe) >> 1;

    SER_DEBUG (DEBUG_SER_CMD, "%s: vsel 0x%x\n", __FUNCTION__, vsel);

	/* Detect card in slot by sending reset sequence for SDIO and then SD */
    return slot_ocr (sdh, dev, 0);
}

/*
 * slot_reset
 */
int
slot_reset(struct sd_host *sdh, int slot)
{
    struct sd_slot_base *pslot;
    int status;
    unsigned int regs[4];
    u32 rca;
	
    SER_DEBUG (DEBUG_SER_CMD, "%s: sdh 0x%x slot 0x%x\n",
            __FUNCTION__, (u32)sdh, (u32)slot);

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }
    
	SER_DEBUG (DEBUG_SER_SD_CMD, "------- %s(%x) ------- \n", __FUNCTION__,(u32)pslot->m_base);
	/* Turn OFF power and clock */	    
	SDHostslot_SoftwareReset(pslot, SR_CMD_LINE|SR_DAT_LINE|SR_RESET_ALL);   
    WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_CLOCKCTRL, 0x0);
    WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_PWRCTRLREG, 0);
    pslot->m_cardtype = 0;
    pslot->m_fCardPresent = 0;

	/* wait 0.1s */
    msleep(100);
  	printf("PSTATE = 0x%08X\n",READ_HOST_U32((u32)pslot->m_base,HOSTREG_PSTATE));
  
  	/* Turn on power 3.3V and slow clock */
    pslot->m_wRegClockControl = 0x8005;
    if (set_clock_on(sdh, slot)<0) return -1;   
    WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_PWRCTRLREG, 0xF); 
    msleep (100);

	/* timeout control */
	pslot->m_TimeoutControl = 0x0E;
    WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_TIMEOUTCTRL, pslot->m_TimeoutControl);    
    
    /* Turn on interrupts required at this stage */
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_ERRINTRSGEN,0xC0);      
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_ERRINTRSEN,0xC0);                    
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSGEN,0xC1);
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSEN,0xC1);
	pslot->m_fSDIOInterruptsEnabled = ENABLE_INTERRUPT;
	
	msleep (100);
	//DumpSlotRegs(pslot);
	// --- Reset SDIO Card (for case where it has been initialised with valid RCA) ---
	write_card_register(sdh, slot, 0, 0x06, 1, 0x08);
	// --- Reset SD Card (TBD) ---
	///status = do_command(sdh, slot, 0, SD_COMMAND, NoResponse, 0,    0, 0, 0, 0, 0, &regs[0]);
	msleep (100);            

    if (!slot_power(sdh, slot)) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: Bad slot_power 0x%x\n", 
                   __FUNCTION__, false);
        return IOS_ERROR_INVALID;
    }

    status = do_command(sdh, slot, 3, 2, 7, 0, 0, 0, 0, 0, 0, &regs[0]);
    if (status < 0) {
        SER_DEBUG (DEBUG_SER_ERR, "%s:command(%d) failed", 
                   __FUNCTION__, 3);
        return IOS_ERROR_INVALID;
    }
    rca = regs[0]>>16;
    //printf("RCA=%04X\n",rca);

    status = do_command(sdh, slot, 7, 2, 2, 0, rca << 16, 0, 0, 0, 0, &regs[0]);
    if (status < 0) {
        SER_DEBUG (DEBUG_SER_ERR, "%s:command(%d) failed", 
                   __FUNCTION__, 7);
        return IOS_ERROR_INVALID;
    }

    return rca;
}

/*
 * read_slot_register
 */
int
read_slot_register(struct sd_host *sdh, int slot, int reg, int width)
{
    struct sd_slot_base *pslot;

    SER_DEBUG (DEBUG_SER_CMD, "%s: sdh 0x%x slot 0x%x reg 0x%x width 0x%x\n",
               __FUNCTION__, (u32)sdh, (u32)slot, (u32)reg, (u32)width);

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    switch (width) {
    case 1:
        return READ_HOST_U8((u32)pslot->m_base, reg);
    case 2:
        return READ_HOST_U16((u32)pslot->m_base, reg);
    case 4:
        return READ_HOST_U32((u32)pslot->m_base, reg);
    default:
        SER_DEBUG (DEBUG_SER_ERR, "%s: bad register width 0x%x\n",
                __FUNCTION__, width);
        return IOS_ERROR_ACCESS;
    }
}

/*
 * write_slot_register
 */
int
write_slot_register(struct sd_host *sdh, int slot, int reg, int width, int data)
{
    struct sd_slot_base *pslot;

    SER_DEBUG (DEBUG_SER_CMD, "%s: sdh 0x%x slot 0x%x reg 0x%x width 0x%x data 0x%x\n",
               __FUNCTION__, (u32)sdh, (u32)slot, (u32)reg, (u32)width, data);

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    switch (width) {
    case 1:
        WRITE_HOST_U8((u32)pslot->m_base, reg, data);
        return 0;
    case 2:
        WRITE_HOST_U16((u32)pslot->m_base, reg, data);
        return 0;
    case 4:
        WRITE_HOST_U32((u32)pslot->m_base, reg, data);
        return 0;
    default:
        SER_DEBUG (DEBUG_SER_ERR, "%s: bad register width 0x%x\n",
                __FUNCTION__, width);
        return IOS_ERROR_ACCESS;
    }

    return 0;
}

/*
 * read_card_register
 */
int
read_card_register(struct sd_host *sdh, int slot, 
                   int function, int reg, int width)
{
    struct sd_slot_base *pslot;
    unsigned int arg;
    unsigned int response[4];
    int status = 0;

    //SER_DEBUG (DEBUG_SER_ERR, "%s: sdh 0x%x slot 0x%x reg 0x%x width 0x%x\n",
    //        __FUNCTION__, (u32)sdh, (u32)slot, (u32)reg, (u32)width);

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    arg = rw_direct_arg (pslot, 0, function, 0, reg, 0);

   // msleep (100);
    status = do_command(sdh, slot, CMD_IO_RW_DIRECT, SD_READ_REG, 
                    ResponseR5, 1, arg, 0, 0, 0, 0, &response[0]);

	#if 0
	{
		int timeout = MAX_TIMEOUT
	    while (timeout-- >= 0) {
	    	 msleep (10);
	        status = do_command(sdh, slot, CMD_IO_RW_DIRECT, SD_READ_REG, 
	                        ResponseR5, 1, arg, 0, 0, 0, 0, &response[0]);
	        if (status == 0) break;
	        SER_DEBUG (DEBUG_SER_ERR, 
	                   "%s: command timeout reg 0x%x status 0x%x %d\n",
	                   __FUNCTION__, reg, status, timeout);
	       
	    }
	}
	#endif
    
    SER_DEBUG (DEBUG_SER_CMD, "%s() slot %d reg 0x%x width %d data=0x%X\n",
            __FUNCTION__, (u32)slot, (u32)reg, (u32)width, response[0] & 0xff);

    return (status == 0) ? response[0] & 0xff : IOS_ERROR_INVALID;

}

/*
 * write_card_register
 */
int
write_card_register(struct sd_host *sdh, int slot, int function,
                    int reg, int width, int data)
{
    struct sd_slot_base *pslot;
    unsigned int arg;
    unsigned int response[4];
    int status = 0;

    SER_DEBUG (DEBUG_SER_CMD, "%s: sdh 0x%x slot 0x%x reg 0x%x width 0x%x data 0x%x\n",
            __FUNCTION__, (u32)sdh, (u32)slot, (u32)reg, (u32)width, (u32)data);

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    arg = rw_direct_arg (pslot, 1, 0, function, reg, data);
    status = do_command(sdh, slot, CMD_IO_RW_DIRECT, SD_WRITE_REG, 
                        ResponseR5, 1, arg, 0, 0, 0, 0, &response[0]);
                        
    #if REPEAT_COMMAND
    if (status!=0)
    {      
    	int timeout = MAX_TIMEOUT;              
	    while (timeout-- >= 0) 
	    {
	        msleep (10);
	        status = do_command(sdh, slot, CMD_IO_RW_DIRECT, SD_WRITE_REG, 
	                            ResponseR5, 1, arg, 0, 0, 0, 0, &response[0]);
	        if (status == 0) break;
	        SER_DEBUG (DEBUG_SER_ERR, 
	                   "%s: command timeout reg 0x%x status 0x%x data 0x%x %d\n",
	                   __FUNCTION__, reg, status, data, timeout);
	    }
    }
	#endif

    SER_DEBUG (DEBUG_SER_CMD, "%s: status 0x%x data 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
            __FUNCTION__, status, response[0], 
            response[1], response[2], 
            response[3], response[4], 
            response[5], response[6], 
            response[7]);

    return status;
}

#if 1
/*
 * read_card_data
 *
 * Read multiple registers from card, or read a block of data.
 */
int
read_card_data(struct sd_host *sdh, int slot, unsigned int function,
               unsigned int reg, unsigned int sysaddr, 
               unsigned int blk_size, unsigned int blk_cnt, 
               unsigned int dma, unsigned int resp_with_busy)
{
    struct sd_slot_base *pslot;
    int status = 0, length;
    unsigned int arg;
    unsigned int response[4];

    SER_DEBUG (DEBUG_SER_REG_MREAD, "%s slot 0x%x func 0x%x reg 0x%x sysaddr 0x%x blk_size 0x%x blk_cnt 0x%x dma 0x%x resp_with_busy 0x%x\n",
            __FUNCTION__, 
            slot, function, reg, sysaddr, blk_size, blk_cnt, dma, resp_with_busy);

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    length = (blk_cnt == 0) ? blk_size : blk_cnt * blk_size;
    
    blk_cnt = (blk_cnt == 0) ? 1:blk_cnt;

    SER_DEBUG (DEBUG_SER_REG_MREAD, "%s: length 0x%x blk_cnt=%d\n",
            __FUNCTION__, length,blk_cnt);
	{
		u32* dp = (u32*)sysaddr;
    	*dp = 0xeeeeeeee;
	}            

    /*
     * Construct the cmd53 argument.
     */
	/*
	 *    31  30  28  27    26 25               9 8              0
	 * +-----+------+-----+---+------------------+----------------+
	 * | R/W | Func | Blk |Op | Register Address |  Data Length   |
	 * +-----+------+-----+---+------------------+----------------+
	 *    1     3      1    1          17                9   
	 *
	 * pslot: slot base address.
	 * rw:    read/write flag
	 * func:  function address on card.   0 is common function.
	 * blk:   block mode
	 * op:    op-code (0 - r/w fixed address, 1 - r/w incrementing address)
	 * reg:   address of eight-bit register.
	 */
   	blk_size = 4;
   	blk_cnt = 1;
    arg = rw_direct_ext_arg (pslot, 0, function, 0, 1, reg, blk_size);

    status = do_command(sdh, slot, CMD_IO_RW_EXTENDED, SD_READ, 
                        ResponseR5, 1, arg, sysaddr, blk_cnt, 
                        blk_size, dma, &response[0]);

	#if 0
	{
		int timeout = MAX_TIMEOUT;
	    while (timeout-- >= 0) {
	        status = do_command(sdh, slot, CMD_IO_RW_EXTENDED, SD_READ, 
	                            ResponseR5, 1, arg, sysaddr, blk_cnt, 
	                            blk_size, dma, &response[0]);
	        if (status == 0) break;
	        SER_DEBUG (DEBUG_SER_ERR, 
	                   "%s: command timeout reg 0x%x status 0x%x %d\n",
	                   __FUNCTION__, reg, status, timeout);
	        msleep (10);
	    }
	}
    #endif
	DumpSlotRegs(pslot);
 	{
		u32* dp = (u32*)sysaddr;
    	//SER_DEBUG (DEBUG_SER_REG_MREAD, 
    	printf("   %s: reg %04X data 0x%08x\n",
            __FUNCTION__, reg,*dp);
	}
    return 0;
}

/*
 * write_card_data
 *
 * Write multiple registers from card, or write a block of data.
 */
int
write_card_data(struct sd_host *sdh, int slot, unsigned int function,
                unsigned int reg, unsigned int sysaddr, 
                unsigned int blk_size, unsigned int blk_cnt, 
                unsigned int dma, unsigned int resp_with_busy)
{
    struct sd_slot_base *pslot;
    int status = 0, length, timeout = MAX_TIMEOUT;
    unsigned int arg;
    unsigned int response[4];

    SER_DEBUG (DEBUG_SER_REG_MREAD, "%s slot 0x%x sysaddr 0x%x blk_size 0x%x blk_cnt 0x%x dma 0x%x resp_with_busy 0x%x\n",
            __FUNCTION__, 
            slot, sysaddr, blk_size, blk_cnt, dma, resp_with_busy);

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    length = (blk_cnt == 0) ? blk_size : blk_cnt * blk_size;
    
    blk_cnt = (blk_cnt == 0) ? 1:blk_cnt;

	{
		u32* dp = (u32*)sysaddr;
    //SER_DEBUG (DEBUG_SER_REG_MREAD, 
    printf( "   %s: reg %04X data 0x%04x\n",
            __FUNCTION__, reg,*dp);
	}

    /*
     * Construct the cmd53 argument.
     */
/*
 *    31  30  28  27    26 25               9 8              0
 * +-----+------+-----+---+------------------+----------------+
 * | R/W | Func | Blk |Op | Register Address |  Data Length   |
 * +-----+------+-----+---+------------------+----------------+
 *    1     3      1    1          17                9   
 *
 * pslot: slot base address.
 * rw:    read/write flag
 * func:  function address on card.   0 is common function.
 * blk:   block mode
 * op:    op-code (0 - r/w fixed address, 1 - r/w incrementing address)
 * reg:   address of eight-bit register.
 */
     arg = rw_direct_ext_arg (pslot, 1, function, 0, 1, reg, blk_size);

    while (timeout-- >= 0) {
        status = do_command(sdh, slot, CMD_IO_RW_EXTENDED, SD_WRITE, 
                            ResponseR5, 1, arg, sysaddr, blk_cnt, 
                            blk_size, dma, &response[0]);
        if (status == 0) break;
        SER_DEBUG (DEBUG_SER_ERR, 
                   "%s: command timeout reg 0x%x status 0x%x data 0x%x %d\n",
                   __FUNCTION__, reg, status, 
                   *(unsigned int *)sysaddr, timeout);
        msleep (10);
    }

    return 0;
}
#else
/*
 * read_card_data
 *
 * Read multiple registers from card, or read a block of data.
 */
int
read_card_data(struct sd_host *sdh, int slot, unsigned int function,
               unsigned int reg, unsigned int sysaddr, 
               unsigned int blk_size, unsigned int blk_cnt, 
               unsigned int dma, unsigned int resp_with_busy)
{
    struct sd_slot_base *pslot;
    int status = 0, length, timeout = MAX_TIMEOUT;
    unsigned int arg;
    unsigned short response[8];

    SER_DEBUG (DEBUG_SER_REG_MREAD, "%s slot 0x%x func 0x%x reg 0x%x sysaddr 0x%x blk_size 0x%x blk_cnt 0x%x dma 0x%x resp_with_busy 0x%x\n",
            __FUNCTION__, 
            slot, function, reg, sysaddr, blk_size, blk_cnt, dma, resp_with_busy);

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return -EFAULT;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return -EFAULT;
    }

    length = (blk_cnt == 0) ? blk_size : blk_cnt * blk_size;

    SER_DEBUG (DEBUG_SER_REG_MREAD, "%s: length 0x%x\n",
            __FUNCTION__, length);

    /*
     * Construct the cmd53 argument.
     */
    if (dma) {
        arg = rw_direct_ext_arg (pslot, 0, function, 1, 0, reg, blk_size);
    } else {
        arg = rw_direct_ext_arg (pslot, 0, function, 0, 1, reg, blk_size);
    }

    while (timeout-- >= 0) {
        status = do_command(sdh, slot, CMD_IO_RW_EXTENDED, SD_READ, 
                            ResponseR5, 1, arg, sysaddr, blk_size, 
                            blk_size, dma, &response[0]);
        if (status == 0) break;
        SER_DEBUG (DEBUG_SER_ERR, 
                   "%s: command timeout reg 0x%x status 0x%x %d\n",
                   __FUNCTION__, reg, status, timeout);
        msleep (10);
    }

    SER_DEBUG (DEBUG_SER_REG_MREAD, "%s: status 0x%x data 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
            __FUNCTION__, status, response[0], 
            response[1], response[2], 
            response[3], response[4], 
            response[5], response[6], 
            response[7]);

    return 0;
}

/*
 * write_card_data
 *
 * Write multiple registers from card, or write a block of data.
 */
int
write_card_data(struct sd_host *sdh, int slot, unsigned int function,
                unsigned int reg, unsigned int sysaddr, 
                unsigned int blk_size, unsigned int blk_cnt, 
                unsigned int dma, unsigned int resp_with_busy)
{
    struct sd_slot_base *pslot;
    int status = 0, length, timeout = MAX_TIMEOUT;
    unsigned int arg;
    unsigned short response[8];

    SER_DEBUG (DEBUG_SER_REG_MREAD, "%s slot 0x%x sysaddr 0x%x blk_size 0x%x blk_cnt 0x%x dma 0x%x resp_with_busy 0x%x\n",
            __FUNCTION__, 
            slot, sysaddr, blk_size, blk_cnt, dma, resp_with_busy);

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return -EFAULT;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return -EFAULT;
    }

    length = (blk_cnt == 0) ? blk_size : blk_cnt * blk_size;

    SER_DEBUG (DEBUG_SER_REG_MREAD, "%s: length 0x%x\n",
            __FUNCTION__, length);

    /*
     * Construct the cmd53 argument.
     */
    arg = rw_direct_ext_arg (pslot, 1, function, 0, 1, reg, blk_size);

    while (timeout-- >= 0) {
        status = do_command(sdh, slot, CMD_IO_RW_EXTENDED, SD_WRITE, 
                            ResponseR5, 1, arg, sysaddr, blk_cnt, 
                            blk_size, dma, &response[0]);
        if (status == 0) break;
        SER_DEBUG (DEBUG_SER_ERR, 
                   "%s: command timeout reg 0x%x status 0x%x data 0x%x %d\n",
                   __FUNCTION__, reg, status, 
                   *(unsigned int *)sysaddr, timeout);
        msleep (10);
    }

    SER_DEBUG (DEBUG_SER_REG_MREAD, "%s: status 0x%x data 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
            __FUNCTION__, status, response[0], 
            response[1], response[2], 
            response[3], response[4], 
            response[5], response[6], 
            response[7]);

    return 0;
}
#endif
int myCallback(void *arg)
{
	struct sd_slot_base *slot = arg;

    unsigned int *pdwUserBuffer;
    unsigned int dwDwordsRemaining = (READ_HOST_U16((u32)slot->m_base, HOSTREG_BLOCKSZ))/4;
    	
	SER_DEBUG (DEBUG_SER_ERR, "%s: called NintStatus 0x%X ClBkSt 0x%X Blocks=%d\n",__FUNCTION__,
		READ_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSEN),
		gp_sd_req->callback_on_irq,
		READ_HOST_U16((u32)slot->m_base, HOSTREG_BLOCKCNT)
		);

    
    pdwUserBuffer = (u32*)READ_HOST_U32((u32)slot->m_base, HOSTREG_SYSADDRL);
    
   	SER_DEBUG (DEBUG_SER_ERR, "%s: User address = %X Size = 0x%x\n", 
   		__FUNCTION__,(u32)pdwUserBuffer,dwDwordsRemaining);
 
    if (pdwUserBuffer==NULL)
    {
    	 SER_DEBUG (DEBUG_SER_ERR, "%s: User address Error = 0x%X\n", __FUNCTION__,(u32)pdwUserBuffer);
    	 return 0;
    }
    if (dwDwordsRemaining!=128)
    {
    	 SER_DEBUG (DEBUG_SER_ERR, "%s: Size Error = 0x%X\n", __FUNCTION__,dwDwordsRemaining);
    	 return 0;
    }

	/* 15) Data Transfer Complete */
	if (gp_sd_req->norint&NISR_DATA_TRAN_COMPLETE)
	{
		gp_sd_req->callback_on_irq = 0;
		SER_DEBUG (DEBUG_SER_ERR, "%s: Transfer Complete\n",__FUNCTION__);
	}
	
	/* TBD buffer alignment */
	
	if (gp_sd_req->norint&NISR_BUFF_READ_RDY)
	{
   		SER_DEBUG (DEBUG_SER_ERR, "%s: Reading Data\n",	__FUNCTION__);
		/* 11-R) Clr Buffer Write Ready Status */
		WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORMINTRSTAT, NISR_BUFF_READ_RDY);
	    /* 12-R) === Read the data from the device === */
	    while ( dwDwordsRemaining-- ) 
		{
	        *(pdwUserBuffer++) = READ_HOST_U32((u32)slot->m_base, HOSTREG_BUFFDP);
	        //pdwUserBuffer[i] = data;
	        // (i<4) SER_DEBUG (DEBUG_SER_ERR, "%s: data[%d]=%X\n",	__FUNCTION__,i,data);
	        //i++;
	    }
	    /* enable data transfer complete status */
	     gp_sd_req->callback_on_irq=0; //|=NISR_DATA_TRAN_COMPLETE;
	}
		
	/* 10W) Buffer write ready int */
	if (gp_sd_req->norint&NISR_BUFF_WRITE_RDY)
	{
		SER_DEBUG (DEBUG_SER_ERR, "%s: Writing Data\n",	__FUNCTION__);
		/* 11-W) Clr Buffer Write Ready Status */
		WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORMINTRSTAT, NISR_BUFF_WRITE_RDY);
	    /* 12-W) === Write the data from the device === */
	    while ( dwDwordsRemaining-- ) 
		{
	        //if (i<4) SER_DEBUG (DEBUG_SER_ERR, "%s: data[%d]=%X\n",	__FUNCTION__,i,*(pdwUserBuffer));
			//u32 data = *(pdwUserBuffer++);
	         WRITE_HOST_U32((u32)slot->m_base, HOSTREG_BUFFDP, *(pdwUserBuffer++));
	         //WRITE_HOST_U32((u32)slot->m_base, HOSTREG_BUFFDP, *(pdwUserBuffer));
	         //WRITE_HOST_U32((u32)slot->m_base, HOSTREG_BUFFDP, *(pdwUserBuffer));
	         //WRITE_HOST_U32((u32)slot->m_base, HOSTREG_BUFFDP, *(pdwUserBuffer));
	         //i++;
	    }
	    //SER_DEBUG (DEBUG_SER_ERR, "%s: i=%d\n",	__FUNCTION__,i);
	    /* 13-W) More Blocks? */
	    /* 15) enable data transfer complete status */
	   gp_sd_req->callback_on_irq=0; //|=NISR_DATA_TRAN_COMPLETE;
	}	

	gp_sd_req->norint = 0;
    /* Write next address back */
    //WRITE_HOST_U32((u32)slot->m_base,HOSTREG_SYSADDRL,(u32)pdwUserBuffer);	
        
	return 0;
}

/*
 * read_card_mem
 *
 * Read blocks of data form card.
 */
int
read_card_mem(	struct sd_host *sdh, 
				int slot, 
               	unsigned int offset, 	/* SD Card Address */
                unsigned int sysaddr, 	/* User Buffer Address */
                unsigned int blk_size, 
                unsigned int blk_cnt, 
                unsigned int dma, 		/* Use DMA, else memory copy */
                unsigned int callback	/* If not NULL then Async */
                )
{
    struct sd_slot_base *pslot;
    int status = 0, length, timeout = MAX_TIMEOUT;
    unsigned int response[4];

    SER_DEBUG (DEBUG_SER_SD_CMD, 
    	"%s slot %d rca 0x%x sysaddr 0x%08X blk_size 0x%x blk_cnt 0x%x dma 0x%x call 0x%x\n",
            __FUNCTION__, 
            slot, offset, sysaddr, blk_size, blk_cnt, dma, callback);

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    length = (blk_cnt == 0) ? blk_size : blk_cnt * blk_size;

    SER_DEBUG (DEBUG_SER_SD_CMD, "%s: length 0x%x\n",
            __FUNCTION__, length);

	gp_sd_req->callback = (void*)callback; //myCallback;
    gp_sd_req->callback_on_irq = NISR_BUFF_READ_RDY;
    /*
     * If blk_cnt > 1 then multi-block else one block
     * 1) Start Command
     * if DMA
     *  2) Wait for DMA done IRQ, next DMA if multiblocks 
     *  3) If all blocks done - call callback function
     * else
     *  2) Wait for data available IRQ
     *  3) Copy memory (inside IRQ), next if multiblocks
     *  4) If all blocks done - call callback fucntion
     */

	/* 
	 * Send command to start write transfer
	 * 1) to 9)
	 * use CMD25 multi block, for single block set blk_cnt to 1
	 * 
	 */
	status = do_command(	sdh, slot, 
							18, SD_COMMAND, 
                            ResponseR1, 1, offset, sysaddr, blk_cnt, 
                            blk_size, dma, &response[0]);
              
    if (callback==0)
    {
    	if (dma==0)
    	{
	    	/* Read Block */
			while (gp_sd_req->req_size)	
			{
			    /* 10R Wait for buffer read ready */ 
			    timeout = 1000;                
				while (((gp_sd_req->norint&NISR_BUFF_READ_RDY)==0)&&(timeout))
				{
					msleep (200);
		
					timeout--;
				}
				if (timeout == 0)
				{
					SER_DEBUG (DEBUG_SER_ERR, "%s: Reading Data Ready Timeout:\n",	__FUNCTION__);
					return 1;
				}
				
				if (gp_sd_req->norint&NISR_BUFF_READ_RDY)
				{
					SER_DEBUG (DEBUG_SER_SD_CMD, "%s: NISR_BUFF_READ_RDY set\n",	__FUNCTION__);
					gp_sd_req->norint &=~NISR_BUFF_READ_RDY;
				}	
				
				/* copy section */
				{
					int i = 0;
					int data;
			    	unsigned int *pdwUserBuffer = (u32*)READ_HOST_U32((u32)pslot->m_base, HOSTREG_SYSADDRL);
			    	unsigned int dwDwordsRemaining = (READ_HOST_U16((u32)pslot->m_base, HOSTREG_BLOCKSZ))/4;
			   		SER_DEBUG (DEBUG_SER_SD_CMD, "%s: Reading Data\n",	__FUNCTION__);
		   			SER_DEBUG (DEBUG_SER_SD_CMD, "%s: User address = %X Size = 0x%x\n", 
		   				__FUNCTION__,(u32)pdwUserBuffer,dwDwordsRemaining);
		   			/* 11-R) Clr Buffer Write Ready Status */
					//WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORMINTRSTAT, NISR_BUFF_READ_RDY);
				    /* 12-R) === Read the data from the device === */
				    while ( dwDwordsRemaining-- ) 
					{
				        data = READ_HOST_U32((u32)pslot->m_base, HOSTREG_BUFFDP);
				        *(pdwUserBuffer++) = data;
				        //if (i<4) SER_DEBUG (DEBUG_SER_ERR, "%s: data[%d]=%X\n",	__FUNCTION__,i,data);
				        i++;
				    }
					/* next block */
				     gp_sd_req->req_size--;
				     WRITE_HOST_U32((u32)pslot->m_base, HOSTREG_SYSADDRL,(u32)pdwUserBuffer);
				}
			}
    	} /* non dma */
    	
		/* Wait until data transfer is complete - sync */
		timeout = 0;
        while ( ((READ_HOST_U16((u32)pslot->m_base, HOSTREG_NORMINTRSTAT) & NISR_DATA_TRAN_COMPLETE) == 0) &&
        		((gp_sd_req->norint & NISR_DATA_TRAN_COMPLETE) == 0) )
        {
            msleep (100);
            timeout += 1;
            if (timeout++ >= DEFAULT_TIMOUT_MS) {
                SER_DEBUG (DEBUG_SER_ERR, "%s: >>> Timeout mem Read <<<\n",
                           __FUNCTION__);
                if (gp_sd_req->status == SD_STATUS_SUCCESS)
                    gp_sd_req->status = SD_STATUS_DATA_TIMEOUT;
                break;
            }
        }
	
   		SER_DEBUG (DEBUG_SER_SD_CMD,"   %s: done, sysaddr now 0x%08x\n",
            __FUNCTION__, READ_HOST_U32((u32)pslot->m_base, HOSTREG_SYSADDRL));           		
    }
    
	 gp_sd_req->callback_on_irq=0; //|=NISR_DATA_TRAN_COMPLETE;
	     
    return 0;
}

/*
 * write_card_data
 *
 * Write multiple registers from card, or write a block of data.
 */
int
write_card_mem(	struct sd_host *sdh, 
				int slot, 
               	unsigned int offset, 	/* SD Card Address */
                unsigned int sysaddr, 	/* User Buffer Address */
                unsigned int blk_size, 
                unsigned int blk_cnt, 
                unsigned int dma, 		/* Use DMA, else memory copy */
                unsigned int callback	/* If not NULL then Async */
                )
{
    struct sd_slot_base *pslot;
    int status = 0, length, timeout = MAX_TIMEOUT;
    unsigned int response[4];
 
    SER_DEBUG (DEBUG_SER_SD_CMD, 
    	"%s slot 0x%x offset 0x%x sysaddr 0x%x blk_size 0x%x blk_cnt 0x%x dma 0x%x callback 0x%x\n",
            __FUNCTION__, 
            slot, offset, sysaddr, blk_size, blk_cnt, dma, callback);

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    length = (blk_cnt == 0) ? blk_size : blk_cnt * blk_size;

    SER_DEBUG (DEBUG_SER_SD_CMD, "%s: length 0x%x\n",
            __FUNCTION__, length);

	gp_sd_req->callback = (void*)callback; //myCallback;
    gp_sd_req->callback_on_irq = NISR_BUFF_WRITE_RDY; /*|NISR_BUFF_READ_RDY|NISR_DATA_TRAN_COMPLETE;*/
    /*
     * If blk_cnt > 1 then multi-block else one block
     * 1) Start Command
     * if DMA
     *  2) Wait for DMA done IRQ, next DMA if multiblocks 
     *  3) If all blocks done - call callback function
     * else
     *  2) Wait for data available IRQ
     *  3) Copy memory (inside IRQ), next if multiblocks
     *  4) If all blocks done - call callback fucntion
     */
     
	#if 0
	   /* SET BLOCK LENGTH 	CMD16, default is 512, bigger will ERROR */
	status = do_command(sdh, slot, 16, SD_COMMAND, 
							ResponseR1, 0, blk_size,  0, 0,
							0,0, &response[0]); 
	#endif
	
  	#if 0
    if (access_ok(VERIFY_READ,pdwUserBuffer,512))
    {
    	SER_DEBUG (DEBUG_SER_ERR, "%s access OK\n", __FUNCTION__);
	}
	#endif
	
	/* 
	 * Send command to start write transfer
	 * 
	 * use CMD25 multi block, for single block set blk_cnt to 1
	 * 
	 */
	status = do_command(	sdh, slot, 
							25, SD_COMMAND, 
                            ResponseR1, 0, offset, sysaddr, 
                            blk_cnt, 
                            blk_size, dma, &response[0]);                           
                            
    if (callback==0)
    {
    	if (dma==0)
    	{
	    	/* Read Block */
			while (gp_sd_req->req_size)	
			{
			    /* 10R Wait for buffer read ready */ 
			    timeout = 1000;                
				while (((gp_sd_req->norint&NISR_BUFF_WRITE_RDY)==0)&&(timeout))
				{
					msleep (20);
		
					timeout--;
				}
				if (timeout == 0)
				{
					SER_DEBUG (DEBUG_SER_ERR, "%s: Write Data Ready Timeout:\n",	__FUNCTION__);
					return 1;
				}
				
				if (gp_sd_req->norint&NISR_BUFF_WRITE_RDY)
				{
					SER_DEBUG (DEBUG_SER_SD_CMD, "%s: NISR_BUFF_WRITE_RDY set\n",	__FUNCTION__);
					gp_sd_req->norint &=~NISR_BUFF_WRITE_RDY;
				}	
				
				/* copy section */
				{
			    	unsigned int *pdwUserBuffer = (u32*)READ_HOST_U32((u32)pslot->m_base, HOSTREG_SYSADDRL);
			    	unsigned int dwDwordsRemaining = (READ_HOST_U16((u32)pslot->m_base, HOSTREG_BLOCKSZ))/4;
			   		SER_DEBUG (DEBUG_SER_SD_CMD, "%s: Writing Data\n",	__FUNCTION__);
		   			SER_DEBUG (DEBUG_SER_SD_CMD, "%s: User address = %X Size = 0x%x\n", 
		   				__FUNCTION__,(u32)pdwUserBuffer,dwDwordsRemaining);
		   			/* 11-R) Clr Buffer Write Ready Status */
					//WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORMINTRSTAT, NISR_BUFF_READ_RDY);
				    /* 12-R) === Read the data from the device === */
				    while ( dwDwordsRemaining-- ) 
					{
						WRITE_HOST_U32((u32)pslot->m_base, HOSTREG_BUFFDP, *(pdwUserBuffer++));
				        //*(pdwUserBuffer++) = READ_HOST_U32((u32)pslot->m_base, HOSTREG_BUFFDP);
				        //pdwUserBuffer[i] = data;
				        //if (i<4) SER_DEBUG (DEBUG_SER_ERR, "%s: data[%d]=%X\n",	__FUNCTION__,i,data);
				        //i++;
				    }
					/* next block */
				     gp_sd_req->req_size--;
				     WRITE_HOST_U32((u32)pslot->m_base, HOSTREG_SYSADDRL,(u32)pdwUserBuffer);
				}
			}
    	} /* non dma */
    	
		/* Wait until data transfer is complete - sync */
		timeout = 0;
        while ( ((READ_HOST_U16((u32)pslot->m_base, HOSTREG_NORMINTRSTAT) & NISR_DATA_TRAN_COMPLETE) == 0)&&
        		((gp_sd_req->norint & NISR_DATA_TRAN_COMPLETE) == 0) )
        {
            msleep (10);
            timeout += 1;
            if (timeout++ >= DEFAULT_TIMOUT_MS) {
                SER_DEBUG (DEBUG_SER_ERR, "%s: timeout data transfer done\n",
                           __FUNCTION__);
                if (gp_sd_req->status == SD_STATUS_SUCCESS)
                    gp_sd_req->status = SD_STATUS_DATA_TIMEOUT;
                break;
            }
        }
		SER_DEBUG (DEBUG_SER_SD_CMD, "%s: DONE\n",
		       __FUNCTION__);      		
    }
    
	gp_sd_req->callback_on_irq=0; //|=NISR_DATA_TRAN_COMPLETE;
    return 0;
}

/*
 * get_slot_voltage
 */
unsigned int
get_slot_voltage(struct sd_host *sdh, int slot)
{
    struct sd_slot_base *pslot;
    unsigned int value = 0;

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }
    value = (READ_HOST_U8((u32)pslot->m_base, HOSTREG_PWRCTRLREG) 
             & 0xe) >> 1;

    return value;
}

/*
 * get_slot_clock
 */
unsigned int
get_slot_clock(struct sd_host *sdh, int slot)
{
    struct sd_slot_base *pslot;
    unsigned int value = 0;

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }
    value = (READ_HOST_U16((u32)pslot->m_base, HOSTREG_CLOCKCTRL) 
             & 0xff00) >> 8;

    return value;
}

/*
 * set_slot_bus_width
 */
unsigned int
set_slot_bus_width(struct sd_host *sdh, int slot, int new)
{
    struct sd_slot_base *pslot;
    unsigned int value = 0;
    unsigned char old;

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    old = READ_HOST_U8((u32)pslot->m_base, HOSTREG_HOSTCTRLREG);

    switch (new) {
    case 1:
        /*
         * Voltage is rest to zero, and then to the new level.
         */
        WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_HOSTCTRLREG, 
                      HC_TRANSFER_WIDTH_1BIT);
        break;
    case 4:
        WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_HOSTCTRLREG, 
                      HC_TRANSFER_WIDTH_4BIT);
        break;
    default:
        SER_DEBUG (DEBUG_SER_ERR, "%s: bad bus width %d\n",
                __FUNCTION__, new);
        return IOS_ERROR_INVALID;
    }

    SER_DEBUG (DEBUG_SER_CMD, "%s: old 0x%x new 0x%x\n",
            __FUNCTION__, old, new);

    value = READ_HOST_U8((u32)pslot->m_base, HOSTREG_HOSTCTRLREG);

    return value;
}

/*
 * set_slot_voltage
 */
unsigned int
set_slot_voltage(struct sd_host *sdh, int slot, int new)
{
    struct sd_slot_base *pslot;
    unsigned int value = 0;
    unsigned char old;

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }
    new = ((new & 0x7) << 1) | 0x1;
    old = READ_HOST_U8((u32)pslot->m_base, HOSTREG_PWRCTRLREG);

    if (old != new) {
        /*
         * Voltage is rest to zero, and then to the new level.
         */
        WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_PWRCTRLREG, 0);
        WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_PWRCTRLREG, new);
        msleep(DEFAULT_TIMOUT_MS);
    }

    SER_DEBUG (DEBUG_SER_CMD, "%s: old 0x%x new 0x%x\n",
            __FUNCTION__, old, new);

    value = READ_HOST_U8((u32)pslot->m_base, HOSTREG_PWRCTRLREG);

    return value;
}

/*
 * set_slot_clock
 */
unsigned int
set_slot_clock(struct sd_host *sdh, int slot, int new)
{
    struct sd_slot_base *pslot;
    unsigned int value = 0;

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    SER_DEBUG (DEBUG_SER_CMD, "%s: old clock 0x%x\n",
            __FUNCTION__, pslot->m_wRegClockControl);

    pslot->m_wRegClockControl = ((new & 0xff) << 8) | 0x1;

    value = (pslot->m_wRegClockControl & 0xff00) >> 8;

    SER_DEBUG (DEBUG_SER_CMD, "%s: new clock 0x%x\n",
            __FUNCTION__, pslot->m_wRegClockControl);

    return value;
}

/*
 * set_clock_on
 */
int
set_clock_on(struct sd_host *sdh, int slot)
{
	SDHostslot_SDClockOn(&sdh->m_sdslot[slot]);
    return 0;
}

/*
 * set_clock_off
 */
int
set_clock_off(struct sd_host *sdh, int slot)
{
    struct sd_slot_base *pslot;
    unsigned int clock_control;

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    /*
     * We called SetClockRate() previously to init m_wRegClockControl.
     * We separate clock divisor calculation from ClockOn, so we can
     * call ClockOn without recalculating the divisor.
     */
    clock_control = pslot->m_wRegClockControl;

    SER_DEBUG (DEBUG_SER_CMD, "%s: clock_control 0x%x\n",
            __FUNCTION__, clock_control);

    WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_CLOCKCTRL, clock_control);

    SER_DEBUG (DEBUG_SER_CMD, "%s: wrote clock 0x%x\n",
               __FUNCTION__, clock_control | SDCLK_ENABLE);

    return 0;
}

unsigned int
handle_insert (struct sd_host *sdh, int slot)
{
    struct sd_slot_base *pslot;

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    SDHostslot_Handlecardinsert(pslot);

    return 0;
}

unsigned int
handle_reinit (struct sd_host *sdh, int slot)
{
    struct sd_slot_base *pslot;

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    SDHostslot_reinit(pslot);

    return 0;
}

/*
 * get_status
 *
 * Get the card status.  See sdio_ioctl.h for the meanings of the
 * status bits.
 * #define SD_CARD_INSERTED   0x00000001
#define SD_CARD_REMOVED    0x00000002
#define SD_CARD_WPROTECTED 0x00000004
#define SD_STATE_SUSPEND   0x00000008

#define SD_TYPE_MEMORY     0x00010000
#define SD_TYPE_SDIO       0x00020000
#define SD_TYPE_COMBO      0x00040000
#define SD_TYPE_MMC        0x00080000
 */
unsigned int
get_status (struct sd_host *sdh, int slot)
{
    struct sd_slot_base *pslot;
    unsigned int device_status;

	SER_DEBUG (DEBUG_SER_SD_CMD, "%s: Called(slot = %d)\n",
                __FUNCTION__,slot);

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

	/* only available after a RESET! */
	if (pslot->m_cardtype==SD_TYPE_UNKNOWN)
	{
		printf("   CardType Not Set - Reset\n");
		slot_reset(sdh,slot);
	}
    device_status = pslot->m_cardtype;

    if (pslot->m_fCardPresent) 
    {
        device_status |= SD_CARD_INSERTED;
    } 
    else 
    {
        device_status |= SD_CARD_REMOVED;
    }
    
    return device_status;
}



/*
 * wait_insert
 *
 * Get the card status.  See sdio_ioctl.h for the meanings of the
 * status bits.
 */
unsigned int
wait_insert (struct sd_host *sdh, int slot)
{
    struct sd_slot_base *pslot;
    unsigned int device_status;

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

	#ifdef LINUX
    	interruptible_sleep_on(&(pslot->m_card_insert));
    #endif

    device_status = SD_TYPE_SDIO;

    if (pslot->m_fCardPresent) {
        device_status |= SD_CARD_INSERTED;
    } else {
        device_status |= SD_CARD_REMOVED;
    }

    return device_status;
}

struct _sd_status_decode {
    int sd_status_int;
    char *sd_status_name;
} sd_status_decodes[] = {
    { SD_STATUS_SUCCESS, "SD_STATUS_SUCCESS" },
    { SD_STATUS_PENDING, "SD_STATUS_PENDING" },
    { SD_STATUS_BUFFER_OVERFLOW, "SD_STATUS_BUFFER_OVERFLOW" },
    { SD_STATUS_DEVICE_BUSY, "SD_STATUS_DEVICE_BUSY" },
    { SD_STATUS_UNSUCCESSFUL, "SD_STATUS_UNSUCCESSFUL" },
    { SD_STATUS_NOT_IMPLEMENTED, "SD_STATUS_NOT_IMPLEMENTED" },
    { SD_STATUS_ACCESS_VIOLATION, "SD_STATUS_ACCESS_VIOLATION" },
    { SD_STATUS_INVALID_HANDLE, "SD_STATUS_INVALID_HANDLE" },
    { SD_STATUS_INVALID_PARAMETER, "SD_STATUS_INVALID_PARAMETER" },
    { SD_STATUS_NO_SUCH_DEVICE, "SD_STATUS_NO_SUCH_DEVICE" },
    { SD_STATUS_INVALID_DEVICE_REQUEST, "SD_STATUS_INVALID_DEVICE_REQUEST" },
    { SD_STATUS_NO_MEMORY, "SD_STATUS_NO_MEMORY" },
    { SD_STATUS_BUS_DRIVER_NOT_READY, "SD_STATUS_BUS_DRIVER_NOT_READY" },
    { SD_STATUS_DATA_ERROR, "SD_STATUS_DATA_ERROR" },
    { SD_STATUS_CRC_ERROR, "SD_STATUS_CRC_ERROR" },
    { SD_STATUS_INSUFFICIENT_RESOURCES, "SD_STATUS_INSUFFICIENT_RESOURCES" },
    { SD_STATUS_DEVICE_NOT_CONNECTED, "SD_STATUS_DEVICE_NOT_CONNECTED" },
    { SD_STATUS_DEVICE_REMOVED, "SD_STATUS_DEVICE_REMOVED" },
    { SD_STATUS_DEVICE_NOT_RESPONDING, "SD_STATUS_DEVICE_NOT_RESPONDING" },
    { SD_STATUS_CANCELED, "SD_STATUS_CANCELED" },
    { SD_STATUS_RESPONSE_TIMEOUT, "SD_STATUS_RESPONSE_TIMEOUT" },
    { SD_STATUS_DATA_TIMEOUT, "SD_STATUS_DATA_TIMEOUT" },
    { SD_STATUS_DEVICE_RESPONSE_ERROR, "SD_STATUS_DEVICE_RESPONSE_ERROR" },
    { SD_STATUS_DEVICE_UNSUPPORTED, "SD_STATUS_DEVICE_UNSUPPORTED" },
    { SD_STATUS_SHUT_DOWN, "SD_STATUS_SHUT_DOWN" },
    { SD_STATUS_OUT_OF_RANGE, "SD_STATUS_OUT_OF_RANGE" },
    { SD_STATUS_FUNCTION_NUMBER_ERR, "SD_STATUS_FUNCTION_NUMBER_ERR" },
    { SD_STATUS_ILLEGAL_CMD, "SD_STATUS_ILLEGAL_CMD" },
    { SD_STATUS_CMD_TIMEOUT, "SD_STATUS_CMD_TIMEOUT" },
    { SD_STATUS_UNKNOWN_ERR, "SD_STATUS_UNKNOWN_ERR" },
};

char *
sd_status_decode (SD_API_STATUS status)
{
    int i;

    for (i = 0; 
         i < (sizeof(sd_status_decodes)/sizeof(struct _sd_status_decode)); i++) {
        if (sd_status_decodes[i].sd_status_int == status) {
            return sd_status_decodes[i].sd_status_name;
        }
    }

    return "unknown";
}

/* 
 * Debug - Check Command Setup
 */
void show_command_setup(struct sd_slot_base *pslot, u32 command, u32 transfer_mode)
{
	/* 1 Set System Address */
	u32 sysaddr = READ_HOST_U32((u32)pslot->m_base, HOSTREG_SYSADDRL);	
	/* 2 Set Block Size */
	u16 blk_size = READ_HOST_U16((u32)pslot->m_base, HOSTREG_BLOCKSZ);
	/* 3 Set Block Count */
	u16 blk_count =	READ_HOST_U16((u32)pslot->m_base, HOSTREG_BLOCKCNT);
	/* 4 Set Argument */
	u32 cmd_arg = READ_HOST_U32((u32)pslot->m_base, HOSTREG_ARG);
	
	if (command & 0x20)
	{
		SER_DEBUG (DEBUG_SER_SD_CMD, "%s Data Transfer Command Issued:0x%04X\n", " >",command); 
		if (transfer_mode&0x10)
		{
			 SER_DEBUG (DEBUG_SER_SD_CMD, "%s Read From SD Card\n", " >");
		}
		else
		{
			 SER_DEBUG (DEBUG_SER_SD_CMD, "%s Write To SD Card\n", " >");
		}
		if (transfer_mode&0x20)
		{
			SER_DEBUG (DEBUG_SER_SD_CMD, "%s Multi Block Transfer, Blocks=%d AutoCMD12=%d Enabled=%d\n", " >",
				blk_count,transfer_mode&0x4,transfer_mode&0x2);
		}
		if (transfer_mode&0x01)
		{
			SER_DEBUG (DEBUG_SER_SD_CMD, "%s DMA Transfer\n"," >");
		}
		else
		{
			SER_DEBUG (DEBUG_SER_SD_CMD, "%s PIO Transfer %04X\n"," >",transfer_mode);
		}	
		SER_DEBUG (DEBUG_SER_SD_CMD, "%s SysAddr:0x%08X\n", " >", sysaddr);
		SER_DEBUG (DEBUG_SER_SD_CMD, "%s BlkSize:0x%04X Cnt:%04X u32=%08X\n", " >",blk_size,blk_count,
					READ_HOST_U32((u32)pslot->m_base, HOSTREG_BLOCKSZ));
		SER_DEBUG (DEBUG_SER_SD_CMD, "%s CmdArg :0x%08X\n", " >",cmd_arg);
		
		SER_DEBUG (DEBUG_SER_SD_CMD, "%s NINTSts:0x%04X Signal:0x%04X\n", " >",
			READ_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSEN),
			READ_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSGEN));
		//DumpSlotRegs(pslot);				
	}	

}

/*
 * do_command
 */
int
do_command (struct sd_host *sdh, int slot, int cmd, int cmd_type, 
            int resp_type, int req_size, int cmd_arg, int sys_addr,
            int blk_count, int blk_size, int dma, unsigned int *resp)
{
    struct sd_slot_base *pslot;
    u16 command, transfer_mode = 0;
    u32 timeout, multi_data_count, p_state = 0;
    u32 cmd32;	// GB add new way to work around 16/8 bit write bug.
    int checkforbusy = 0;

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }
    
    SER_DEBUG (DEBUG_SER_SD_CMD, "%s: pslot 0x%x cmd %d arg:0x%08x maddr:0x%08x dma=%d\n",
	            __FUNCTION__, (u32)(u32)pslot->m_base, (u32)cmd, (u32)cmd_arg, (u32)sys_addr, dma);

    gp_sd_req->command = cmd;
    gp_sd_req->cmd_type = cmd_type;
    gp_sd_req->resp_type = resp_type;
    gp_sd_req->cmd_arg = cmd_arg;
    gp_sd_req->norint = 0;
    gp_sd_req->status = 0;
    gp_sd_req->cmd_wait = 0;
    gp_sd_req->callback = 0; //myCallback;
    gp_sd_req->heartbeat = 0x12345678;
    gp_sd_req->req_size = blk_count;
    
    command = (cmd << CMD_INDEX_SHIFT) & CMD_INDEX_MASK;

    switch (resp_type) {
        SER_DEBUG (DEBUG_SER_CMD, "%s: resp 0x%x\n",
                   __FUNCTION__, 0);
        case NoResponse:
        break;

    case ResponseR2:
        SER_DEBUG (DEBUG_SER_CMD, "%s: resp 0x%x\n",
                   __FUNCTION__, CMD_RESPONSE_R2);
        command |= CMD_RESPONSE_R2;
        break;

    case ResponseR3:
    case ResponseR4:
        SER_DEBUG (DEBUG_SER_CMD, "%s: resp 0x%x\n",
                   __FUNCTION__, CMD_RESPONSE_R3_R4);
        command |= CMD_RESPONSE_R3_R4;
        break;

    case ResponseR1:
    case ResponseR5:
    case ResponseR6:
        SER_DEBUG (DEBUG_SER_CMD, "%s: resp 0x%x\n",
                   __FUNCTION__, CMD_RESPONSE_R1_R5_R6);
        command |= CMD_RESPONSE_R1_R5_R6;
        break;

    case ResponseR1b:
        SER_DEBUG (DEBUG_SER_CMD, "%s: resp 0x%x\n",
                   __FUNCTION__, CMD_RESPONSE_R1B_R5B);
        command |= CMD_RESPONSE_R1B_R5B;  
        checkforbusy = 1; 
        break;

    default:
        return -1;
    }

    //SER_DEBUG (DEBUG_SER_CMD, 
   // printf("%s: command 0x%x\n",
     //          __FUNCTION__, command);

    /*
     * === Wait until command_inhibit is not set. ===
     */
    p_state = READ_HOST_U32((u32)pslot->m_base,HOSTREG_PSTATE);
    if (p_state & PS_CMD_INHIBIT_CMD)
    {
    	printf("<soft reset pstate: 0x%08X ~ ",p_state);
 		SDHostslot_SoftwareReset(pslot, SR_CMD_LINE);
 		p_state = READ_HOST_U32((u32)pslot->m_base,HOSTREG_PSTATE);
 		//if (p_state & PS_CMD_INHIBIT_CMD)
 		printf("0x%08X>\n",p_state);
    }             


    /*
     * Program the registers needed for different command types.
     */
     
    transfer_mode = 0x00;
    switch (cmd_type) {
    case SD_COMMAND:
    	{
    		int read = 1;
    		int cmd12 = 1;
    				
	    	if ((cmd==17)||(cmd==18))
	    	{
    			SER_DEBUG (DEBUG_SER_SD_CMD, "%s ---CMD READ--- %04X %04X\n",__FUNCTION__,
    				READ_HOST_U16((u32)pslot->m_base,0x24),
    				READ_HOST_U16((u32)pslot->m_base,0x26));
    			read = 1;
    			/* param 2 is for infinite transfers, I dont think we will use */
	    		transfer_mode = rw_transfer_mode (	dma, 
	    											(blk_count>0)?1:0, 
	    											cmd12, read, 
	    											(blk_count>0)?1:0);
		        command |= CMD_DATA_PRESENT_SEL;
		        /* enable data read status */
		        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSEN,0xC3|NISR_BUFF_READ_RDY|NISR_DMA_INTR|NISR_DATA_TRAN_COMPLETE);
		        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSGEN,0xC3|NISR_BUFF_READ_RDY|NISR_DMA_INTR|NISR_DATA_TRAN_COMPLETE);
		        if (dma==0) gp_sd_req->callback_on_irq = NISR_BUFF_READ_RDY;	    			    	
			}
	    	if ((cmd==24)||(cmd==25))
	    	{
    			SER_DEBUG (DEBUG_SER_SD_CMD, "%s ---CMD WRITE--- %04X %04X\n",__FUNCTION__,
    				READ_HOST_U16((u32)pslot->m_base,0x24),
    				READ_HOST_U16((u32)pslot->m_base,0x26));
    			read = 0;
    			/* param 2 is for infinite transfers, I dont think we will use */
	    		transfer_mode = rw_transfer_mode (	dma, 
	    											(blk_count>0)?1:0, 
	    											cmd12, read, 
	    											(blk_count>0)?1:0);
		        command |= CMD_DATA_PRESENT_SEL;
		        /* enable data write status and callback */
		        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSEN,0xC3|NISR_BUFF_WRITE_RDY|NISR_DMA_INTR|NISR_DATA_TRAN_COMPLETE);
		        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSGEN,0xC3|NISR_BUFF_WRITE_RDY|NISR_DMA_INTR|NISR_DATA_TRAN_COMPLETE);
		       if (dma==0) gp_sd_req->callback_on_irq = NISR_BUFF_WRITE_RDY;	    			    	
			}			
    	}
        break;
        
	/*-------------------------------------------------------
	 * The following is required for some cards. If it is not
	 * present, command-only transfers will sometimes fail
	 * (especially R1B and R5B).
	 */

	    case SD_READ: // (dma, blk_cnt, cmd12, rw, multi)
	        if (dma) 
	        {
	        	printf("(dmaRD)\n");
	            transfer_mode = rw_transfer_mode (dma, 1, 0, 1, 1);
	        } 
	        else 
	        {
	            transfer_mode = rw_transfer_mode (dma, 0, 0, 1, 0);
	        }
	        command |= CMD_DATA_PRESENT_SEL;
		        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSEN,0xC3|NISR_BUFF_READ_RDY|NISR_DMA_INTR|NISR_DATA_TRAN_COMPLETE);
		        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSGEN,0xC3|NISR_BUFF_READ_RDY|NISR_DMA_INTR|NISR_DATA_TRAN_COMPLETE);
	        break;
	    case SD_WRITE:
	    	if (dma)
	    	{
		    	printf("(dmaWR)\n");
		        transfer_mode = rw_transfer_mode (dma, 1, 0, 0, 1);
	    	}
	        else
	        {
	        	transfer_mode = rw_transfer_mode (dma, 0, 0, 0, 0);
	        }
	        command |= CMD_DATA_PRESENT_SEL;
	        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSEN,0xC3);
	        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSGEN,0xC3);
	        break;
        
    case SD_READ_REG:
        break;
    case SD_WRITE_REG:
        break;
    default:
        break;
    }

    if ((READ_HOST_U16((u32)pslot->m_base, HOSTREG_CLOCKCTRL)&0x07)!=0x07)
    {
    	if (set_clock_on(sdh, slot)<0) 
    	{
    		printf("Error - Clock Not Stable\n");
    		return -1;
    	}
    }

    /*
     * Data Transfer Parameters, these should not be changed while data transfer
     * busy.
     */
     if (command&CMD_DATA_PRESENT_SEL)
     {
     	u32 sysaddr = sys_addr;
     	
     	#ifdef LINUX
     	if (dma) 
     	{
     		sysaddr = virt_to_bus((void *)sys_addr);
     		SER_DEBUG (DEBUG_SER_REG_MWRITE, "%s: DMA Adjust %X %X\n", __FUNCTION__,sys_addr,sysaddr);
     	}
     	#else
		if (dma) 
     	{
     		//sysaddr = sys_addr | 0x50000000;
     		SER_DEBUG (DEBUG_SER_REG_MWRITE, "%s: DMA Adjust %X %X\n", __FUNCTION__,sys_addr,sysaddr);
     	}     	
     	#endif
     	
   
	    /*
	     * === Wait until data_inhibit is not set. ===
	     */
	    p_state = READ_HOST_U32((u32)pslot->m_base,HOSTREG_PSTATE);
	    if (p_state & PS_CMD_INHIBIT_DATA)
	    {
	    	printf("<data reset pstate: 0x%08X ~ ",p_state);
	 		SDHostslot_SoftwareReset(pslot, SR_DAT_LINE);
	 		p_state = READ_HOST_U32((u32)pslot->m_base,HOSTREG_PSTATE);
	 		printf("0x%08X>\n",p_state);
	    }        
         
	 	/* 1 Set System Address */
		WRITE_HOST_U32((u32)pslot->m_base, HOSTREG_SYSADDRL,sysaddr);     	

		/* 2 Set Block Size */
		WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_BLOCKSZ, blk_size);
		//printf("size=%x",blk_size);
		
		/* 3 Set Block Count */
		WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_BLOCKCNT, blk_count);
     }
     
	/* 4 Set Argument */
	WRITE_HOST_U32((u32)pslot->m_base, HOSTREG_ARG, cmd_arg);

	/* 5 Set Transfer Mode */
	cmd32 = (transfer_mode) | (command<<16);
	///WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_TRANSMODE, transfer_mode);
	
	/* Debug - Check setup */
	//show_command_setup(pslot,command,transfer_mode);
	
    /* 
     * 6 Set Command
     * 
     * Writing the upper byte of the command register starts the
     * command.  All register initialization must already be complete
     * by this point.
     */

	//msleep(100);
	WRITE_HOST_U32((u32)pslot->m_base, HOSTREG_TRANSMODE, cmd32);


    /*
     * If this is a CMD53 multi-write, we should start writing the data
     * to the data port right away.
     */
    if ((cmd == CMD_IO_RW_EXTENDED) && (cmd_arg & CMD_ARG_WRITE) && (!dma)) {
        int remaining, written = 0;

        multi_data_count = cmd_arg & 0x1ff;

        //SER_DEBUG (DEBUG_SER_REG_MWRITE,
        printf( "   %s: multi-write count 0x%x\n",
                __FUNCTION__, multi_data_count);

        for (remaining = multi_data_count; remaining > 0;
             remaining -= written) 
        {
            timeout = 0;
            while ((READ_HOST_U32((u32)pslot->m_base, HOSTREG_PSTATE)
                    & BUFFER_WRITE_ENABLE) == 0) {
                msleep (10);
                if (timeout++ >= 200 /* DEFAULT_TIMOUT_MS */) {
                    SER_DEBUG (DEBUG_SER_ERR, "%s: timeout during data write count 0x%x remaining 0x%x\n",
                            __FUNCTION__, multi_data_count, remaining);
                    gp_sd_req->status = SD_STATUS_DATA_TIMEOUT;
                    goto out;
                }
            }
            
            if (remaining >= 4) 
            {
            	written = 4;
            	printf("writing %d bytes:%04X\n",written,*(unsigned int *)sys_addr);
                WRITE_HOST_U32((u32)pslot->m_base, HOSTREG_BUFFDP, 
                               *(unsigned int *)sys_addr);
            } 
            else 
            
            if (remaining >= 2) 
            {
            	written = 2;
            	printf("writing %d bytes:%04X\n",written,*(unsigned int *)sys_addr);
                WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_BUFFDP, 
                                   *(unsigned int *)sys_addr);
            } 
          
            else 
          
            {
            	u8* pd = (u8*)sys_addr;
            	written = 1;
            	printf("->write %d bytes:%02X\n",written,*pd);
                WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_BUFFDP,*pd);
            }
            //SER_DEBUG (DEBUG_SER_REG_MREAD, 
            //printf("   %s: write data 0x%08x cnt %d written %d\n",
            //           __FUNCTION__, *(unsigned int *)sys_addr,
            //           multi_data_count, written);
            sys_addr += written;
        }
    }

    /*
     * We do not have to wait for command completion to begin reading
     * data from the read port.   We just have to test the buffer
     * read enable flag in the present state register.
     */
    if ((cmd == CMD_IO_RW_EXTENDED) && ((cmd_arg & CMD_ARG_WRITE) == 0) && (!dma)) 
    {
        int remaining, read;

        SER_DEBUG (DEBUG_SER_REG_MREAD, "%s: cmd 53\n",
                __FUNCTION__);
        multi_data_count = cmd_arg & 0x1ff;

        //SER_DEBUG (DEBUG_SER_REG_MREAD, 
        printf("%s: multi-read count 0x%x\n",
                __FUNCTION__, multi_data_count);
        for (remaining = multi_data_count; remaining > 0; 
             remaining -= read) {
            timeout = 0;
            while ((READ_HOST_U32((u32)pslot->m_base, HOSTREG_PSTATE)
                    & BUFFER_READ_ENABLE) == 0) {
                msleep (10);
                if (timeout++ >= 200 /* DEFAULT_TIMOUT_MS */) {
                    SER_DEBUG (DEBUG_SER_ERR, "%s: timeout during data read count 0x%x remaining 0x%x\n",
                            __FUNCTION__, multi_data_count, remaining);
                    gp_sd_req->status = SD_STATUS_DATA_TIMEOUT;
                    goto out;
                }
            }
            
            
            if (remaining >= 4) 
            {
                *(u32*)sys_addr = 
                    READ_HOST_U32((u32)pslot->m_base, HOSTREG_BUFFDP);
                read = 4;
            } 
            else 
            if (remaining >= 2) 
            {
                    *(u16*)sys_addr = 
                        READ_HOST_U16((u32)pslot->m_base, HOSTREG_BUFFDP);
                    read = 2;
            } 
            else 
            
            {
                    *(u8*)sys_addr = 
                        READ_HOST_U8((u32)pslot->m_base, HOSTREG_BUFFDP);
                    read = 1;
            }
            //SER_DEBUG (DEBUG_SER_REG_MREAD, 
            printf("%s: read data 0x%08x %d %d %d\n",
                       __FUNCTION__, *(unsigned int *)sys_addr,
                       multi_data_count, remaining, read);
            sys_addr += read;
        }
    }





out: // ======= === Command Done === =======
	command = command>>8;
	// === Wait for command to complete, either via IRQ or poll IRQ status (ref CMD12 issue) ===
	if ((7 == command) && ( 0 == cmd_arg))
	{
		printf("Cards Deselected\n");
	}
	else
	{
	    timeout = 0;
	    do 
	    {
	        msleep(1);
	        timeout += 5;
	        if (timeout++ >= DEFAULT_TIMOUT_MS) 
	        {
	            //SER_DEBUG (DEBUG_SER_ERR, "%s: timeout during command execution\n",
	            //        __FUNCTION__);
	            if (gp_sd_req->status == SD_STATUS_SUCCESS)
	            {
	            	gp_sd_req->status = SD_STATUS_CMD_TIMEOUT; // c00000022
	            }
	            break;
	        }
	    } while (( (READ_HOST_U16((u32)pslot->m_base, HOSTREG_NORMINTRSTAT)&NISR_CMD_COMPLETE) == 0) && 
	    			(gp_sd_req->cmd_wait == 0) );
		// --- report error condition, for some commands timeout is quite valid ---
	    if ((gp_sd_req->status != SD_STATUS_SUCCESS)&&(command!=500))
	        SER_DEBUG (DEBUG_SER_ERR, "%s(%d) Failed:0x%x\n",
	                __FUNCTION__, command, gp_sd_req->status);
	}
	
	/* ------- For CMD53 with dma, check if dma is done ------- */
    if ((cmd == CMD_IO_RW_EXTENDED) && dma) 
    {
		//SER_DEBUG (DEBUG_SER_ERR, "   %s: waiting for CMD53 dma done\n", __FUNCTION__);    	
        msleep (10);
        timeout = 0;
        while ((gp_sd_req->norint & NISR_DATA_TRAN_COMPLETE) == 0) 
        {
            msleep (10);
            timeout += 1;
            if (timeout++ >= DEFAULT_TIMOUT_MS) 
            {
                SER_DEBUG (DEBUG_SER_ERR, "%s: timeout waiting data transfer\n",
                           __FUNCTION__);
                if (gp_sd_req->status == SD_STATUS_SUCCESS)
                    gp_sd_req->status = SD_STATUS_DATA_TIMEOUT;
                break;
            }
        }
        //SER_DEBUG (DEBUG_SER_REG_MREAD, 
        printf("   CMD53 DMA, sys_addr = 0x%08X reponse = 0x%08x\n", 
                   READ_HOST_U32((u32)pslot->m_base, HOSTREG_SYSADDRL),
                   gp_sd_req->response[0]);
    }

	if (checkforbusy)
	{
		p_state = READ_HOST_U32((u32)pslot->m_base,HOSTREG_PSTATE);
    	printf("   cpstate: 0x%08X ~ ",p_state);		 
    	printf("   respons: 0x%08X\n",gp_sd_req->response[0]);
        timeout = 0;
        while ((READ_HOST_U32((u32)pslot->m_base,HOSTREG_PSTATE) & PS_CMD_INHIBIT_CMD)) 
        {
            msleep (10);
            timeout += 1;
            if (timeout++ >= DEFAULT_TIMOUT_MS) 
            {
                SER_DEBUG (DEBUG_SER_ERR, "%s: timeout waiting busy\n",
                           __FUNCTION__);
                if (gp_sd_req->status == SD_STATUS_SUCCESS)
                    gp_sd_req->status = SD_STATUS_DATA_TIMEOUT;
                break;
            }
        }    	
	}
	
    if (resp) 
    {
    	//resp[0] = gp_sd_req->response[0];
	   	//resp[1] = gp_sd_req->response[1];
	   	//resp[2] = gp_sd_req->response[2];
	   	//resp[3] = gp_sd_req->response[3];
        memcpy(resp, &gp_sd_req->response[0], 8 * sizeof(unsigned short));
    }


    return gp_sd_req->status;
}

/* eof */
