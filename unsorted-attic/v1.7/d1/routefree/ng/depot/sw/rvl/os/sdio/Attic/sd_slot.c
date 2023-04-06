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

#ident "$Id: sd_slot.c,v 1.6 2006/03/20 07:27:26 gbarnard Exp $"

#ifdef LINUX
	#include <linux/config.h>
	#include <linux/module.h>
	#include <linux/init.h>
	#include <linux/ioport.h>
	#include <linux/device.h>
	#include <linux/delay.h>
	#include <linux/interrupt.h>
	#include <linux/dma-mapping.h>
	#include <linux/ioport.h>
	#include <linux/pci.h>
	
	#include "../include/sd.h"
	#include "../include/sd_pci.h"
	#include "../include/sd_host.h"
	#include "../include/sd_debug.h"
#else
	#include <ios.h>
	#include <iostypes.h>
	#include <ioslibc.h>
	
	#include "sd.h"
	#include "sd_card.h"
	#include "sd_host.h"
	#include "sd_ioctl.h"
	#include "sd_debug.h"
		
	//extern void kfree (const void* objp);
	//extern IOSMessageQueueId 	sdQid;
	
	extern IOSError sdusleep(u32 usec);
	
	void udelay(unsigned long usecs);
	void udelay(unsigned long usecs)
	{
		int i,j,k;
		IOSError rv = 0; //sdusleep((u32)usecs,sdQid,"<u>");
		
		for (i=0;i<usecs;i++)
		{
			for (k=0;k<20;k++) j=j+i*7;
			if (j>usecs*9) j=0;
		}
		
		if (rv!=IOS_ERROR_OK)
		{
			printf("%s Error. Status = 0x%x\n",__FUNCTION__,rv);
		}
	}

	void msleep(unsigned int msecs);
	void msleep(unsigned int msecs)
	{
		u32 usecs = msecs;
		for (usecs = 0; usecs<msecs; usecs++)
		{
			sdusleep((u32)1000);
		}
	}
				
#endif

struct _slot_regs {
    u32    reg_addr;
    char   *reg_name;
    u8     reg_width;
} slot_regs[] = {
  { HOSTREG_SYSADDRL, 	"HOSTREG_SYSADDRL    ", 4 },
//  { HOSTREG_SYSADDRH, 	"HOSTREG_SYSADDRH    ", 2 },
  { HOSTREG_BLOCKSZ, 	"HOSTREG_BLOCKSZ     ", 2 },
  { HOSTREG_BLOCKCNT, 	"HOSTREG_BLOCKCNT    ", 2 },
  { HOSTREG_ARG, 		"HOSTREG_ARG         ", 4 },
  { HOSTREG_TRANSMODE, 	"HOSTREG_TRANSMODE   ", 2 },
  { HOSTREG_COMMAND, 	"HOSTREG_COMMAND     ", 2 },
//  { HOSTREG_RES0, 		"HOSTREG_RES0        ", 2 },
//  { HOSTREG_RES1, 		"HOSTREG_RES1        ", 2 },
//  { HOSTREG_RES2, 		"HOSTREG_RES2        ", 2 },
//  { HOSTREG_RES3, 		"HOSTREG_RES3        ", 2 },
//  { HOSTREG_RES4, 		"HOSTREG_RES4        ", 2 },
//  { HOSTREG_RES5, 		"HOSTREG_RES5        ", 2 },
//  { HOSTREG_RES6, 		"HOSTREG_RES6        ", 2 },
//  { HOSTREG_RES7, 		"HOSTREG_RES7        ", 2 },
//  { HOSTREG_BUFFDP, 	"HOSTREG_BUFFDP      ", 4 },
  { HOSTREG_PSTATE, 	"HOSTREG_PSTATE      ", 4 },
  { HOSTREG_HOSTCTRLREG,"HOSTREG_HOSTCTRLREG ", 1 },
  { HOSTREG_PWRCTRLREG, "HOSTREG_PWRCTRLREG  ", 1 },
  { HOSTREG_BLOCKGAPREG,"HOSTREG_BLOCKGAPREG ", 1 },
  { HOSTREG_WAKEUPREG, 	"HOSTREG_WAKEUPREG   ", 1 },
  { HOSTREG_CLOCKCTRL, 	"HOSTREG_CLOCKCTRL   ", 2 },
  { HOSTREG_TIMEOUTCTRL,"HOSTREG_TIMEOUTCTRL ", 1 },
  { HOSTREG_SOFTRESET, 	"HOSTREG_SOFTRESET   ", 1 },
  {HOSTREG_NORMINTRSTAT,"HOSTREG_NORMINTRSTAT", 2 },
  { HOSTREG_ERRINTRSTAT,"HOSTREG_ERRINTRSTAT ", 2 },
  { HOSTREG_NORINTRSEN, "HOSTREG_NORINTRSEN  ", 2 },
  { HOSTREG_ERRINTRSEN, "HOSTREG_ERRINTRSEN  ", 2 },
  { HOSTREG_NORINTRSGEN,"HOSTREG_NORINTRSGEN ", 2 },
  { HOSTREG_ERRINTRSGEN,"HOSTREG_ERRINTRSGEN ", 2 },
  { HOSTREG_CAPABILITY, "HOSTREG_CAPABILITY  ", 4 },
//  { HOSTREG_CAPBILITYR, "HOSTREG_CAPBILITYR  ", 4 },
  { HOSTREG_MAXCURR, 	"HOSTREG_MAXCURR     ", 4 },
  { HOSTREG_SLOTINTRS, 	"HOSTREG_SLOTINTRS   ", 2 },
//  { HOSTREG_HOSTVER, 	"HOSTREG_HOSTVER     ", 2 },
};

int sdpci_debug = DEBUG_PCI_ERR; //|DEBUG_PCI_IRQN|DEBUG_PCI_INIT; //|DEBUG_PCI_IRQ

/*
 * DumpSlotRegs
 *
 * Dump the values of all the slot registers, observing the widths
 * listed in the table above.  Useful for debugging.
 */
void 
DumpSlotRegs(struct sd_slot_base *slot)
{
    int i;
    u8  byte_data;
    u16 word_data;
    u32 int_data;

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

	printf("--- %s(0x%08X) ---\n",__FUNCTION__,(u32)slot->m_base);
    for (i = 0; i < (sizeof(slot_regs) / sizeof (struct _slot_regs)); i++) 
    {
    	printf("[%02X]",slot_regs[i].reg_addr);
        switch (slot_regs[i].reg_width) 
        {
        case 1:
            byte_data = READ_HOST_U8((u32)slot->m_base, 
                                     slot_regs[i].reg_addr);
            PCI_DEBUG (DEBUG_PCI_ERR, "%s 0x%02x\n",
                    slot_regs[i].reg_name, byte_data);
            break;
        case 2:
            word_data = READ_HOST_U16((u32)slot->m_base, 
                                      slot_regs[i].reg_addr);
            PCI_DEBUG (DEBUG_PCI_ERR,"%s 0x%04x\n",
                    slot_regs[i].reg_name, word_data);
            break;
        case 4:
            int_data = READ_HOST_U32((u32)slot->m_base, 
                                      slot_regs[i].reg_addr);
            PCI_DEBUG (DEBUG_PCI_ERR,"%s 0x%08x\n",
                    slot_regs[i].reg_name, int_data);
            break;
        default:
			break;
        }
    }
    printf("\n");
}

/*
 * SDHostslot_Resetstruct
 *
 * Fill in the default initial values for the per-slot struct.
 */
void 
SDHostslot_Resetstruct(struct sd_slot_base *slot)
{

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    slot->m_base = NULL;
    slot->m_slotindex = -1;               /* physical slot number */
    slot->m_pbRegisters = NULL;           /* memory-mapped registers */
    slot->sdh = NULL;
    slot->m_capability = 0;               /* Capabilities */
    slot->m_cardtype = 0;                 /* SD / SDIO */
    slot->m_SysIntr = 0;                  /* system interrupt */
    slot->m_VddWindows = 0 ;              /* supported VDD windows */
    slot->m_dwMaxClockRate = 0;           /* maximum clock rate */
    slot->m_TimeoutControl = 0;           /* timeout control value */
    slot->m_dwMaxBlockLen = 0;            /* maximum block length */
    slot->m_pbDmaBuffer = 0;              /* virtual address of DMA buffer */
    slot->m_paDmaBuffer = 0;           /* physical address of DMA buffer */
    slot->m_wRegClockControl =0 ;         /* register value of Clock Control */
    slot->m_wIntSignals =0;               /* saved int signals for powerup */
    slot->m_uDefaultWakeupControl =0;     /* wakeup source list */
    slot->m_bWakeupControl = 0;           /* current wakeup interrupts */
    slot->m_fCommandCompleteOccurred = 0; /* has the Command Complete occurred for the current transfer? */
    slot->m_fSleepsWithPower = 0;         /* keep power in PowerDown()? */
    slot->m_fPowerUpDisabledInts = 0;     /* did PowerUp disable SDIO card interrupts? */
    slot->m_fIsPowerManaged = 0;          /* is the power manager handling us? */
    slot->m_fSDIOInterruptsEnabled = 0;   /* are SDIO card interrupts enabled? */
    slot->m_fCardPresent = 0;             /* is a card present */
    slot->m_fAutoCMD12Success = 0;        /* AutoCMD12 success */
    slot->m_fCheckSlot = 0;               /* does HandleInterrupt() need to be run? */
    slot->m_fCanWakeOnSDIOInterrupts = 0; /* can wake on SDIO interrupts */
    slot->m_f4BitMode = 0;                /* 4 bit bus mode? */
    slot->m_fFakeCardRemoval = 0;
    #ifdef LINUX
    init_waitqueue_head(&(slot->m_card_insert));           /* event queues */
    init_waitqueue_head(&(slot->m_card_interrupt));
    init_waitqueue_head(&(slot->m_card_error));
    #endif
}

/*
 * SDHostslot_SoftwareReset
 *
 * This is called when one of the Data, Cmd, All bts are set in the
 * present state register.  Writing to one of these bits should clear
 * the inhibit condition that they represent.
 */
u8 
SDHostslot_SoftwareReset( struct sd_slot_base *slot, u8 mask)
{
    u16 timeout = 0;
    u32 prev_state, present_state;

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return 0;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return 0;
    }
    
    prev_state = READ_HOST_U32((u32)slot->m_base, HOSTREG_PSTATE);

	WRITE_HOST_U8((u32)slot->m_base, HOSTREG_SOFTRESET, mask);
	
	
    do {
    	udelay(10);
        if(timeout > DEFAULT_TIMOUT_MS) 
        {
            PCI_DEBUG (DEBUG_PCI_ERR, "%s: timed out\n",
                    __FUNCTION__);
            return 0;
        }
        timeout += 1;
    } while (READ_HOST_U8((u32)slot->m_base, HOSTREG_SOFTRESET)&mask);

    /*
     * Get the present state to see if things were cleared.
     */
    present_state = READ_HOST_U32((u32)slot->m_base, HOSTREG_PSTATE);
    //PCI_DEBUG (DEBUG_PCI_INIT, 
    printf("SWReset(%x) PState:0x%x\n",slot->m_base,present_state);
	
    return 1;
}

/*
 * SDHostslot_GetCapability
 *
 * Read the capability register into the per-slot data structure.
 */
void 
SDHostslot_GetCapability(struct sd_slot_base *slot)
{

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

    slot->m_capability = READ_HOST_U32((u32)slot->m_base, 
                                       HOSTREG_CAPABILITY);
    PCI_DEBUG (DEBUG_PCI_INIT, "%s: Device capibilites %x\n", 
            __FUNCTION__, slot->m_capability);

    return;
}

/*
 * SDHostslot_DetermineVddWindows
 *
 * Read the voltage support bits from the capability register and set
 * the voltage support field in the per-slot data structure.
 */
void 
SDHostslot_DetermineVddWindows(struct sd_slot_base *slot)
{
    u8 Vddcap;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

    Vddcap = CCAP_VOLTAGE_SUPPORT(slot->m_capability);
    if(Vddcap & CCAP_18V_SUPPORT )
        slot->m_VddWindows |= (SD_VDD_17_18 | SD_VDD_18_19);
    if(Vddcap & CCAP_30V_SUPPORT )
        slot->m_VddWindows |= (SD_VDD_29_30 | SD_VDD_30_31);
    if(Vddcap & CCAP_33V_SUPPORT )
        slot->m_VddWindows |= (SD_VDD_32_33 | SD_VDD_33_34);

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: The supported Vdd Range is %x\n", 
           __FUNCTION__, slot->m_VddWindows);
    
    return;
}

/*
 * SDHostslot_Maxclock
 *
 * Read the clock bits from the capability register and return the
 * maximum supported clock rate.
 */
u32 
SDHostslot_Maxclock( struct sd_slot_base *slot)
{
    u32 dwMaxClockRate = 0;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return 0;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return 0;
    }

    if(slot->m_capability != 0) {
        dwMaxClockRate = CCAP_BASECLOCK(slot->m_capability) * 1000000;
        if (dwMaxClockRate == 0) {
            dwMaxClockRate = SDHOST_MAX_CLOCK;
        }
    }
    PCI_DEBUG (DEBUG_PCI_INIT, "%s: Maximum Clock rate is %d\n", 
            __FUNCTION__, dwMaxClockRate);
    
    return dwMaxClockRate;
}

/*
 * SDHostslot_Maxblocklen
 *
 * Read the block length bits from the capability register and return
 * the maximum supported block length.
 */
u32 
SDHostslot_Maxblocklen( struct sd_slot_base *slot)
{
    u32 dwMaxBlockLen = 0;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return 0;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return 0;
    }

    switch (CCAP_MAX_BLK_LEN(slot->m_capability)) {
    case CCAP_MAX_BLK_2048:
        dwMaxBlockLen = SD_HOST_MXBLOCK_LEN_2048;
        break;
    case CCAP_MAX_BLK_1024:
        dwMaxBlockLen = SD_HOST_MXBLOCK_LEN_1024;
        break;
    case CCAP_MAX_BLK_512:
        dwMaxBlockLen = SD_HOST_MXBLOCK_LEN_512;
        break;
    }

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: Max Block Len %x\n", 
           __FUNCTION__, dwMaxBlockLen);
    
    return dwMaxBlockLen;
}

/*
 * SDHostslot_Timeoutcontrol
 */
u32 
SDHostslot_Timeoutcontrol(struct sd_slot_base *slot)
{
#if 0
    u32 dwTimeoutClock = 0;
    double dTimeoutControl = 0;
#endif
    u32   dwToC= 0;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return 0;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return 0;
    }

#if 0
    if (dwTimeoutClock == 0) {
        dwTimeoutClock = CCAP_TIMEOUT_CLK_FRQ(slot->m_capability)*1000;
        if (dwTimeoutClock == 0) {
            dwTimeoutClock = SDHOST_MAX_CLOCK;
        } else {
            if (slot->m_capability & CCAP_TIMEOUT_CLK_MHZ)
                dwTimeoutClock *= 1000;
        }
    }

    dTimeoutControl = log(dTimeoutClock * (DEFAULT_TIMOUT_MS/1000)) 
        / log(2.0) - 13.0;

    if(dTimeoutControl < 0 ) {
        dTimeoutControl = 0;
    } else {
        dTimeoutControl = ceil(dTimeoutControl);
        dwToC = (u32)dTimeoutControl;
    }
    dwToC = min(dwToC, SDHC_TIMEOUT_CONTROL_MAX);
#endif

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: Value of the Timeout is %x\n", 
            __FUNCTION__, dwToC);
    
    return dwToC;
}

/*
 * SDHostslot_Findwakeupsources
 */
u8 
SDHostslot_Findwakeupsources(struct sd_slot_base *slot)
{
    u8    dwWakeupSources = 0;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return 0;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return 0;
    }

    dwWakeupSources = READ_HOST_U8((u32)slot->m_base, HOSTREG_WAKEUPREG);

    dwWakeupSources = WU_EVENT_CR_ENABLE | WU_EVENT_CI_ENABLE 
        | WU_EVENT_INTR_ENABLE;

    
    WRITE_HOST_U8((u32)slot->m_base, HOSTREG_WAKEUPREG, dwWakeupSources);
    
    return dwWakeupSources ;
}

/*
 * SDHostslot_init
 *
 * Do a general init of the per-slot struct by calling the routines
 * above.  This routine mostly looks to see what the host controller
 * is capable of.  It does not start up the slot.  That is left for
 * SDHostslot_start().
 *
 * Called from sd_pci_init_slot
 */
void 
SDHostslot_init(struct sd_slot_base *slot)
{

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: base 0x%x\n",
            __FUNCTION__, (u32)slot->m_base);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

    if (SDHostslot_SoftwareReset(slot, 0x07)) 
    {

        SDHostslot_GetCapability(slot);

        SDHostslot_DetermineVddWindows(slot);

        slot->m_dwMaxClockRate = SDHostslot_Maxclock(slot);

        slot->m_dwMaxBlockLen = SDHostslot_Maxblocklen(slot);

        slot->m_TimeoutControl = SDHostslot_Timeoutcontrol(slot);

        slot->m_uDefaultWakeupControl = SDHostslot_Findwakeupsources(slot);
    }
    else
    {
    	printf("Host Could Not Be RESET!!!\n");
    }
    
    // ======= Several Register Level Debug Routines =======
    #if 0
    WRITE_HOST_U16((u32)slot->m_base, 0, 0x1111);
    WRITE_HOST_U16((u32)slot->m_base, 2, 0x2222);
    printf("0x%04X 0x%04X\n",
    		READ_HOST_U16((u32)slot->m_base, 2),
    		READ_HOST_U16((u32)slot->m_base, 0) );	

    DumpSlotRegs(slot);
    
    WRITE_HOST_U8((u32)slot->m_base, 0, 0x33);
    WRITE_HOST_U8((u32)slot->m_base, 3, 0x44);
    printf("0x%02X 0x%02X\n",
    		READ_HOST_U8((u32)slot->m_base, 3),
    		READ_HOST_U8((u32)slot->m_base, 0) );	

    DumpSlotRegs(slot);
    #endif
	#if 0
		int k;			// debug
		u32*	dp32;	// debug
		u16*	dp16;
		u8*		dp8;
		printf("Reset State\n");
		dp32 = (u32*)slot->m_base;
		dp16 = (u16*)slot->m_base;
		dp8 = (u8*)slot->m_base;
		for (k=0;k<16;k++)
		{
			printf("0x%08X 0x%08X",dp32,*dp32);	
			{
				int j;
				for (j=0;j<2;j++)
				{	
					//*dp16 = 0xFFFF;
					//WRITE_HOST_U16((u32)dp16, 0, 0xFFFF);
					printf(" 0x%04X",*dp16);dp16++; 
											
				}
			}
			dp32++;
			printf("\n");
		}
	#endif
    return;
}

/*
 * SDHostslot_start
 *
 * Does the most radical reset by resetting the All bit of the
 * software reset register.  If this succeeds, set up timeout control
 * and enable interrupts.
 *
 * This is called after SDHostslot_init(), which is called to figure
 * out what the host controller is capable of, and uses the results of
 * that call.    When SDHostslot_start() is done, we are still not ready
 * to run, because we still have to call SDHostslot_Handlecardinsert()
 * to react to card insertion.
 *
 * Called from sd_pci_init_slot
 */
SD_API_STATUS 
SDHostslot_start(struct sd_slot_base *slot)
{
    SD_API_STATUS status;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return SD_STATUS_INVALID_HANDLE;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return SD_STATUS_INVALID_HANDLE;
    }

 
    PCI_DEBUG (DEBUG_PCI_INIT, "%s: timeout control and enable interrupts\n",
            __FUNCTION__);
    /* timeout control */
    WRITE_HOST_U8((u32)slot->m_base, HOSTREG_TIMEOUTCTRL,
                  slot->m_TimeoutControl);
   /* 
     * Enable error interrupt status and signals for all but the vendor
     * errors. This allows any normal error to generate an interrupt.
     */

    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_ERRINTRSEN, 0);
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_ERRINTRSGEN, 0);
    
    /* 
     * Enable card insert and remove status. During execution, we will enable
     * and disable interrupt statuses as desired.
     */        
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSGEN, NISR_CARD_INSERT | NISR_CARD_REMOVAL);
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSEN, NISR_CARD_INSERT | NISR_CARD_REMOVAL);
    
    //printf("%x NINE 0x%X NINS 0x%X\n",(u32)slot,
    //	READ_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSGEN),
    //	READ_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSEN) );
    status = SD_STATUS_SUCCESS;


	
    return status;
}

/*
 * SDHostslot_stop
 *
 * Calls SDHostslot_SoftwareReset() to clear any outstanding Data or
 * Cmd.
 *
 * Not currently called.
 */
SD_API_STATUS 
SDHostslot_stop(struct sd_slot_base *slot)
{

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return SD_STATUS_INVALID_HANDLE;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return SD_STATUS_INVALID_HANDLE;
    }

    SDHostslot_SoftwareReset(slot, SR_RESET_ALL);

    return SD_STATUS_SUCCESS;
}

/*
 * DoEnableSDIOInterrupts
 *
 * Enable or disable card interrupts in the normal interrupt
 * enable register.
 *
 * Called from SDHostslot_Enableinterrupt
 */
void 
DoEnableSDIOInterrupts(struct sd_slot_base *slot, u8 fEnable)
{
    u16 wIntStatusEn;

    PCI_DEBUG (DEBUG_PCI_IRQ, "%s: slot 0x%x enable 0x%x\n",
            __FUNCTION__, (u32)slot, fEnable);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

    wIntStatusEn = READ_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSEN);

    if (fEnable == ENABLE_INTERRUPT) {
        wIntStatusEn |= ENABLE_NIS_CARDINTRS;
    } else {
        wIntStatusEn &= (~ENABLE_NIS_CARDINTRS);
    }
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSEN, wIntStatusEn);

    return;
}


extern struct _sd_request *gp_sd_req;


/*
 * SDHostslot_Enableinterrupt
 *
 * Wrapper routine for DoEnableSDIOInterrupts that keeps a soft copy
 * of the interrupt state.
 *
 * Called from routines SDHostslot_Handleinterrupt() and
 * SDHostslot_Handlecardinsert()
 */
void 
SDHostslot_Enableinterrupt(struct sd_slot_base *slot, u8 fEnable)
{
    PCI_DEBUG (DEBUG_PCI_IRQ, "%s: slot 0x%x enable %d\n",
            __FUNCTION__, (u32)slot, fEnable);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

    if (fEnable == ENABLE_INTERRUPT) {
        slot->m_fSDIOInterruptsEnabled = ENABLE_INTERRUPT;
        DoEnableSDIOInterrupts(slot, fEnable);
    } else {
        DoEnableSDIOInterrupts(slot, fEnable);
        slot->m_fSDIOInterruptsEnabled = DISABLE_INTERRUPT;
    }

    return;
}


/*
 * SDHostslot_Handleinterrupt
 *
 * The slot interrupt handlig routine.  First check for an error
 * interrupt NISR_ERR_INTR.  Then check for command completion
 * interrupt.  We don't currently handle DMA.  Signal command
 * completion in the global command struct.  Finally handle card
 * insertion or removal.
 *
 * Called from sdstdhost_handleinterrupt for each slot that has an
 * outstanding interrupt.                  
 *                                          __________
 *                                         | Status   |
 *                   _______________       | Register |
 * interrupt source |               |      |         q|---------------> interrupt status
 * ---------------->| status enable |----->| set      |     \       _______________
 *                  |_______________|      |          |      \-----|               |      signals
 *                                         |__________|            | signal enable |-----> slot IRQ        
 *                                                                 |_______________|
 */
  
void 
SDHostslot_Handleinterrupt(struct sd_slot_base *slot)
{
    u16 wIntStatus;
    u16 wIntSignal;
    u32 dwPresentState;
    u16 command;
    SD_API_STATUS status;

	gp_sd_req->status = 0;
	///printf("   =======>\n");

    PCI_DEBUG (DEBUG_PCI_IRQ, "%s: base 0x%x\n",
               __FUNCTION__, (u32)slot->m_base);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

    wIntStatus = READ_HOST_U16((u32)slot->m_base, HOSTREG_NORMINTRSTAT);
                   
    /* disable irq while processing */
    wIntSignal = READ_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSGEN);
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSGEN, 0x00);
    /* 
     * Determine which status bits are interrupt (signal) enabled, 
     * some status signals may be polled.
     */
    wIntStatus = wIntStatus & wIntSignal;
    
    /* clear slot interrupts - also any ones not handled! */
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORMINTRSTAT, wIntStatus);
    
	command = READ_HOST_U16((u32)slot->m_base, HOSTREG_COMMAND);
	command = command>>8;
    PCI_DEBUG (DEBUG_PCI_IRQN, 
   // printf( 
    	"+++> NIntStatus(%d-0x%08X):0x%04x Cmd:%02d 0x%08X\n",
               (u32)slot->m_slotindex, (u32)slot->m_base, 
               wIntStatus, command, READ_HOST_U32((u32)slot->m_base, HOSTREG_TRANSMODE));
       

    

    if (wIntStatus != 0) 
    {
        /*
         * Error handling. Make sure to handle errors first.
         */
        if ( wIntStatus & NISR_ERR_INTR ) 
        {
        	PCI_DEBUG (DEBUG_PCI_IRQN, "%s[Error]\n", ":");
            status = SDHostslot_Handleerror(slot);
            gp_sd_req->norint = 0;
            gp_sd_req->status = status;
        }

        /*
         * Command Complete handling.
         */
        if ( wIntStatus & NISR_CMD_COMPLETE ) 
        {
            gp_sd_req->norint |= NISR_CMD_COMPLETE; /* polling feedback */
            //command = READ_HOST_U16((u32)slot->m_base, HOSTREG_COMMAND);
            //PCI_DEBUG (DEBUG_PCI_IRQN, 
            //printf("[Command %02d Done]", command);
            slot->m_fCommandCompleteOccurred = 1;
        }

        /*
         * DMA data transfer complete handling.
         */
        if ( wIntStatus & NISR_DATA_TRAN_COMPLETE ) 
        {
            gp_sd_req->norint |= NISR_DATA_TRAN_COMPLETE;
            //command = READ_HOST_U16((u32)slot->m_base, HOSTREG_COMMAND);
            //PCI_DEBUG (DEBUG_PCI_IRQN, "%s[Transfer]\n", ":");
            printf("[Transfer]");
        }	
        
        if ( wIntStatus & NISR_DMA_INTR)
		{
			gp_sd_req->norint |= NISR_DMA_INTR;
			printf("[DMA Boundary]");
		}

        if ( wIntStatus & NISR_BUFF_READ_RDY)
		{
			gp_sd_req->norint |= NISR_BUFF_READ_RDY;
			printf("[Read]");
		}

        if ( wIntStatus & NISR_BUFF_WRITE_RDY)
		{
			gp_sd_req->norint |= NISR_BUFF_WRITE_RDY;
			printf("[Write]");
		}
        
        /* Async functionality I.e. : (NISR_BUFF_R_RDY|... NISR_DATA_TRAN_COMPLETE) */	 
        if (wIntStatus & gp_sd_req->callback_on_irq)
        {
        	/* for polling feedback */
        	gp_sd_req->norint |= wIntStatus & gp_sd_req->callback_on_irq;
        	
            //gp_sd_req->norint |= NISR_DATA_TRAN_COMPLETE;
            //command = READ_HOST_U16((u32)slot->m_base, HOSTREG_COMMAND);
            //PCI_DEBUG (DEBUG_PCI_IRQN, 
            printf("[Data Ready]");

		   /* clear slot callback interrupts */
		    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORMINTRSTAT, wIntStatus & gp_sd_req->callback_on_irq);				
        }       

        /* 
         * Card Detect Interrupt Handling
         */
        if (wIntStatus & NISR_CARD_INSERT ) 
        {
        	//PCI_DEBUG (DEBUG_PCI_IRQN, "%s Insert/Remove\n", ":");
        	printf("[Insert]");
            slot->m_fCheckSlot = 1;
        }
       /* 
         * Card Detect Interrupt Handling
         */
        if (wIntStatus & NISR_CARD_REMOVAL) 
        {
        	//PCI_DEBUG (DEBUG_PCI_IRQN, "%s Insert/Remove\n", ":");
        	printf("[Remove]");
            slot->m_fCheckSlot = 1;
        }        
    }	/* if (wIntStatus != 0) */

	/*
	 * Copy command status
	 */
    if (slot->m_fCommandCompleteOccurred) 
    {
        gp_sd_req->response[0] = READ_HOST_U32((u32)slot->m_base, HOSTREG_RES0);
        gp_sd_req->response[1] = READ_HOST_U32((u32)slot->m_base, HOSTREG_RES2);
        gp_sd_req->response[2] = READ_HOST_U32((u32)slot->m_base, HOSTREG_RES4);
        gp_sd_req->response[3] = READ_HOST_U32((u32)slot->m_base, HOSTREG_RES6);
     
        gp_sd_req->cmd_wait = 1;
    }
    
    if (slot->m_fCheckSlot) 
    {
        slot->m_fCheckSlot = 0;

        /*
         * check card inserted or removed
         */
        dwPresentState = READ_HOST_U32((u32)slot->m_base, HOSTREG_PSTATE);
        if (dwPresentState & STATE_CARD_INSERTED) 
        {
            PCI_DEBUG (DEBUG_PCI_IRQ, "%s - Card is Inserted! \n",
                       __FUNCTION__);
            if (slot->m_fCardPresent == 0 ) 
            {
                SDHostslot_Handlecardinsert(slot);
            }
            PCI_DEBUG (DEBUG_PCI_IRQ, "%s: m_card_insert 0x%x\n",
                   __FUNCTION__, (u32)&(slot->m_card_insert));
            ///wake_up_interruptible(&(slot->m_card_insert));
        } 
        else 
        {
            PCI_DEBUG (DEBUG_PCI_IRQ, "%s - Card is Removed! \n",
                       __FUNCTION__);
            if (slot->m_fCardPresent) 
            {
                SDHostslot_Handlecardremove(slot, 0);
            }
            PCI_DEBUG (DEBUG_PCI_IRQ, "%s: m_card_insert 0x%x\n",
                   __FUNCTION__, (u32)&(slot->m_card_insert));
            ///wake_up_interruptible(&(slot->m_card_insert));
        }
    }
    
   
    

    
    /* debug safety check, disable irq's if it seems to be running without any commands */
    //if (request_global)
    //	gp_sd_req->heartbeat++; 
              
   	WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSGEN, wIntSignal);
   	//printf("<%X %x %d %d>", gp_sd_req, gp_sd_req->heartbeat, gp_sd_req->status, gp_sd_req->cmd_wait);
}

/*
 * SDHostslot_Setclockrate
 *
 * Find the closest clock rate to the desired rate that we can
 * support.
 *
 * Called from SDHostslot_Handlecardinsert()
 */
void 
SDHostslot_Setclockrate( struct sd_slot_base *slot, u32 *pdwRate)
{
    u32 uClockRate;
    u32 uMaxClockRate;
    u32 uDivisor;
    int i;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

    uClockRate = *pdwRate;

    uMaxClockRate = slot->m_dwMaxClockRate;

    i = 0; /* 2^i is the divisor value */

    uDivisor = 0;

    /* shift MaxClockRate until we find the closest frequency <= target */
    while ( (uClockRate < uMaxClockRate) && ( i < 8 ) ) {
        uMaxClockRate = uMaxClockRate >> 1;
        i++; 
    }

    /* set the actual clock rate */
    *pdwRate = uMaxClockRate; 

    slot->m_wRegClockControl = SDCLK_INTERNAL_ENABLE;
    if (i != 0) {
        uDivisor = 1 << (i - 1);
        slot->m_wRegClockControl |= (uDivisor << 8);
    }
    PCI_DEBUG (DEBUG_PCI_INIT, "%s - Clock Control Reg = %X\n", 
           __FUNCTION__, slot->m_wRegClockControl);
    PCI_DEBUG (DEBUG_PCI_INIT, "%s - Actual clock rate = %d\n", 
           __FUNCTION__, *pdwRate);
}

/*
 * SDHostslot_Handlecardinsert
 *
 * Set up a newly inserted card.  The slot has already been set up.
 * Do a software reset to remove outstanding Data and Cmd events, Set
 * voltage and clock, enable interrupts and turn on the slot LED.
 *
 * Called from SDHostslot_Handleinterrupt()
 */
void 
SDHostslot_Handlecardinsert(struct sd_slot_base *slot)
{
    u32 uClockRate;
    u32 uSleepMs;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

    SDHostslot_SoftwareReset(slot, SR_RESET_ALL);

    uClockRate = SD_DEFAULT_CARD_ID_CLOCK_RATE;
    slot->m_fCardPresent = 1;
    slot->m_cardtype = 0;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: maxvdd 0x%x\n",
            __FUNCTION__, SDHostslot_maxvdd(slot));

    /* 
     * Apply the initial voltage to the card. 
     */
    SDHostslot_Setvoltage(slot, SDHostslot_maxvdd(slot));

    /* 
     * Send at least 74 clocks to the card over the course of at least
     * 1 ms with allowance for power supply ramp-up time. (SD Phys
     * Layer 6.4) Note that power supply ramp-up time occurs in
     * SetVoltage().
     */

    SDHostslot_Setclockrate(slot, &uClockRate);
    SDHostslot_SDClockOn(slot);
    uSleepMs = 10; //(74 / (uClockRate / 1000)) + 1;
    udelay(uSleepMs*1000);
    SDHostslot_SDClockOff(slot);

    /*
     * Set maximum timeout value.
     */
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_TIMEOUTCTRL, 0xe);

    if ((slot->m_capability & CCAP_DMA_SUPPORT_MASK) != CCAP_DMA_SUPPORT_MASK) 
    {
        PCI_DEBUG (DEBUG_PCI_INIT, "%s: no dma support\n",
               __FUNCTION__);
    }

    /* Interrupts are not enabled on a newly inserted card. */
    SDHostslot_Enableinterrupt(slot, DISABLE_INTERRUPT);

    SDHostslot_EnableLED(slot, 1);

    return;
}

/*
 * SDHostslot_SDClockOn
 *
 * Write the previously calculated clock rate to the Clock Control
 * register, wait till the clock is stable, and then write the Clock
 * Enable bit.
 *
 * Called from SDHostslot_Handlecardinsert.
 */
void 
SDHostslot_SDClockOn(struct sd_slot_base *slot)
{
    u32   uTO= 0;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

    /* 
     * Must call SetClockRate() first to init m_wRegClockControl We
     * separate clock divisor calculation with ClockOn, so we can call
     * ClockOn without recalcuating the divisor.
     */
    WRITE_HOST_U16((u32)slot->m_base, 
                   HOSTREG_CLOCKCTRL, slot->m_wRegClockControl);
                   
    /* wait until clock stable */
    while ( !(READ_HOST_U32((u32)slot->m_base, HOSTREG_CLOCKCTRL) 
             & SDCLK_INTERNAL_STABLE) ) 
    {
        udelay(4);
        uTO += 5;
        if(uTO >= DEFAULT_TIMOUT_MS) {
            PCI_DEBUG (DEBUG_PCI_INIT, "%s: Timeout during SD Clock Stablization\n",
                   __FUNCTION__);
            break;
        }
    }
    
    /* enable it */
    WRITE_HOST_U16((u32)slot->m_base, 
                	HOSTREG_CLOCKCTRL, 
                	slot->m_wRegClockControl | SDCLK_ENABLE);
 
    //printf("    Clock 0x%04x timeout %d\n",
    //       		READ_HOST_U16((u32)slot->m_base, HOSTREG_CLOCKCTRL),
    //            uTO);
    return;
}

/*
 * SDHostslot_SDClockOff
 *
 * Disable the clock by writing the clock frequency without the Clock
 * Enable bit.
 *
 * Called from routines SDHostslot_Handlecardinsert() and
 * SDHostslot_Handlecardremove()
 */
void 
SDHostslot_SDClockOff(struct sd_slot_base *slot)
{   
    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_CLOCKCTRL, 
                   slot->m_wRegClockControl);
}


/*
 * SDHostslot_Handlecardremove
 *
 * Zero out all the slot parameter values, and kill the clock and
 * power to the slot.
 *
 * Called from SDHostslot_Handleinterrupt()
 */
void 
SDHostslot_Handlecardremove(struct sd_slot_base *slot, u8 fCancelRequest)
{

    PCI_DEBUG (DEBUG_PCI_IRQ, "%s: slot 0x%x cancel 0x%x\n",
            __FUNCTION__, (u32)slot, fCancelRequest);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

    slot->m_fCardPresent = 0;
    slot->m_fIsPowerManaged = 0;
    slot->m_fSleepsWithPower = 0;
    slot->m_fPowerUpDisabledInts = 0;
    slot->m_f4BitMode = 0;
    slot->m_cardtype = 0;

    /* 
     * Wait for complete power management implementation 
     */
    /* slot->m_cpsCurrent = D0; */

    /* 
     * Wake on SDIO interrupt must be set by the client 
     */
    slot->m_bWakeupControl &= ~WU_EVENT_INTR_ENABLE;

    if (slot->m_fSDIOInterruptsEnabled) {
        SDHostslot_Enableinterrupt(slot, DISABLE_INTERRUPT);
    }

    /* 
     * turn off clock and remove power from the slot 
     */
    SDHostslot_SDClockOff( slot);

    WRITE_HOST_U8((u32)slot->m_base, HOSTREG_PWRCTRLREG, 0);

    /*
     * Need to implement the cancle request logic to stop data transfer 
     */

    if (fCancelRequest) {
        /* 
         * get the current request 
         */
#if 0
        struct sd_request * request_global; /* = GetAndLockCurrentRequest(); */

        if (request_global != NULL) {
            PCI_DEBUG (DEBUG_PCI_IRQ, "%s:Card Removal Detected - Canceling request: 0x%08X, command: %d\n",
                   __FUNCTION__. request_global, gp_sd_req->commandcode);
            /*            
             * Dumrequest_global(request_global, SDHC_SEND_ZONE || SDHC_RECEIVE_ZONE); 
             */
            SDHostslot_IndicateBusRequestComplete(slot, request_global, SD_STATUS_DEVICE_REMOVED);
        }
#endif
    }

/*
    if (slot->m_pbDmaBuffer) {
        kfree((void *)slot->m_pbDmaBuffer);
        slot->m_pbDmaBuffer = (u32)NULL;
    }
*/

    /* 
     * The Pegasus requires the following so that the next 
     * insertion will work correctly. 
     */
    SDHostslot_SoftwareReset(slot, SR_RESET_ALL);

    WRITE_HOST_U32((u32)slot->m_base, HOSTREG_SYSADDRL, 0);
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_BLOCKSZ, 0);
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_BLOCKCNT, 0);
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORMINTRSTAT, NISR_DMA_INTR);

    SDHostslot_EnableLED(slot, 0);

    return;
}


SD_API_STATUS
SDHostslot_Handleerror(struct sd_slot_base *slot)
{
    SD_API_STATUS status = SD_STATUS_UNSUCCESSFUL;
    u16 uErrorStatus;
    u16 uErrIntSignal;
    u16 command;

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return SD_STATUS_DEVICE_NOT_CONNECTED;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return SD_STATUS_DEVICE_NOT_CONNECTED;
    }

   /* Perform basic error recovery */
    uErrIntSignal = READ_HOST_U16((u32)slot->m_base, HOSTREG_ERRINTRSGEN);
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_ERRINTRSGEN, 0);

    uErrorStatus = READ_HOST_U16((u32)slot->m_base, HOSTREG_ERRINTRSTAT);

    PCI_DEBUG (DEBUG_PCI_IRQ, "%s: error 0x%x\n",
            __FUNCTION__, uErrorStatus);


    if (uErrorStatus ) {
        if ( uErrorStatus  & EISR_RESPONSE_TIMEOUT ) {
            command = READ_HOST_U16((u32)slot->m_base, HOSTREG_COMMAND);
            PCI_DEBUG (DEBUG_PCI_ERR, "%s: response timeout 0x%x\n",
                    __FUNCTION__, command);
            status = SD_STATUS_RESPONSE_TIMEOUT;
        }

        if ( uErrorStatus  & EISR_CMD_CRC_ERR ) {
            PCI_DEBUG (DEBUG_PCI_ERR, "%s: CRC error\n",
                    __FUNCTION__);
            status = SD_STATUS_CRC_ERROR;
        }

        if ( uErrorStatus  & EISR_CMD_ENDBIT_ERR ) {
            PCI_DEBUG (DEBUG_PCI_ERR, "%s: end bit error\n",
                    __FUNCTION__);
            status = SD_STATUS_RESPONSE_TIMEOUT;
        }

        if ( uErrorStatus  & EISR_CMD_INDEX_ERR ) {
            PCI_DEBUG (DEBUG_PCI_ERR, "%s: index error error\n",
                    __FUNCTION__);
            status = SD_STATUS_DEVICE_RESPONSE_ERROR;
        }

        if ( uErrorStatus  & EISR_DATA_TIMEOUT ) {
            PCI_DEBUG (DEBUG_PCI_ERR, "%s: data timeout error\n",
                    __FUNCTION__);
            status = SD_STATUS_DATA_TIMEOUT;
        }

        if ( uErrorStatus  & EISR_DATA_CRC_ERR ) {
            PCI_DEBUG (DEBUG_PCI_ERR, "%s: data CRC error\n",
                    __FUNCTION__);
            status = SD_STATUS_CRC_ERROR;
        }

#if 0
        if ( wErrorStatus & EISR_DATA_ENDBIT_ERR ) {
                        status = SD_STATUS_DEVICE_RESPONSE_ERROR;
        }

        if ( wErrorStatus & EISR_CURR_LIMIT_ERR ) {
                        status = SD_STATUS_DEVICE_RESPONSE_ERROR;
        }
#endif
        if ( uErrorStatus  & EISR_AUTOCMD12_ERR ) {
            PCI_DEBUG (DEBUG_PCI_ERR, "%s: AutoCmd12 error\n",
                    __FUNCTION__);
            status = SD_STATUS_DEVICE_RESPONSE_ERROR;
        }


        if (IS_CMD_LINE_ERROR(uErrorStatus)) {
            PCI_DEBUG (DEBUG_PCI_ERR, "%s: Command Error.  Trying to reset slot\n",
                    __FUNCTION__);
            SDHostslot_SoftwareReset(slot, SR_CMD_LINE);
        }


        if (IS_DAT_LINE_ERROR(uErrorStatus)) {
            PCI_DEBUG (DEBUG_PCI_ERR, "%s: Data Error.  Trying to reset slot\n",
                    __FUNCTION__);
            SDHostslot_SoftwareReset(slot, SR_DAT_LINE);
        }

        /* clear all error status */
        WRITE_HOST_U16((u32)slot->m_base, 
                       HOSTREG_ERRINTRSTAT, uErrorStatus);

        /* re-enable error interrupt signals */
        WRITE_HOST_U16((u32)slot->m_base, 
                       HOSTREG_ERRINTRSGEN, uErrIntSignal);

    }
    return status;
}

/*
 * SDHostslot_Commandcomplete
 */
u8 
SDHostslot_Commandcomplete(struct sd_slot_base *slot)
{
    u8 fRet = 0;
    SD_API_STATUS transferStatus;

    PCI_DEBUG (DEBUG_PCI_IRQ, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return 0;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return 0;
    }

    transferStatus = SD_STATUS_SUCCESS;

    return fRet;
}

/*
 * SDHostslot_Setvoltage
 */
void 
SDHostslot_Setvoltage(struct sd_slot_base *slot, u32 uvddsetting)
{
    u8 ucVoltageSelection;
    u8 ucOldVoltage;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

    ucVoltageSelection = PW_CTRL_BUSPW_ON;
    if (uvddsetting & 
        (SD_VDD_32_33 | SD_VDD_33_34)) {
        ucVoltageSelection |= PW_CTRL_33V;
    }
    else if (uvddsetting &
             (SD_VDD_29_30 | SD_VDD_30_31)) {
        ucVoltageSelection |= PW_CTRL_30V;
    }
    else if (uvddsetting &
             (SD_VDD_17_18 | SD_VDD_18_19)) {
        ucVoltageSelection |= PW_CTRL_18V;
    }

    ucOldVoltage = READ_HOST_U8((u32)slot->m_base, HOSTREG_PWRCTRLREG);
    PCI_DEBUG (DEBUG_PCI_INIT, "%s: old power 0x%x power 0x%x\n",
            __FUNCTION__, ucOldVoltage, ucVoltageSelection);

    if (ucOldVoltage != ucVoltageSelection) {
        /*
         * SD Bus Power must be initially set to 0 when changing
         * voltages
         */
        WRITE_HOST_U8((u32)slot->m_base, HOSTREG_PWRCTRLREG, 0);
        WRITE_HOST_U8((u32)slot->m_base, HOSTREG_PWRCTRLREG, 
                      ucVoltageSelection);
        udelay(DEFAULT_TIMOUT_MS);
        PCI_DEBUG (DEBUG_PCI_INIT, "%s: Slot SetVoltage: 0x%x\n", 
               __FUNCTION__, ucVoltageSelection);
    }

    return;
}

/*
 * SDHostslot_EnableLED
 */
void 
SDHostslot_EnableLED(struct sd_slot_base *slot, u8 fEnable)
{
    u8 bHostControl ;

    bHostControl = READ_HOST_U8((u32)slot->m_base, HOSTREG_HOSTCTRLREG);
    if (fEnable) {
        bHostControl |= HC_LED_ON;
    } else {
        bHostControl &= ~HC_LED_ON;
    }
    WRITE_HOST_U8((u32)slot->m_base, HOSTREG_HOSTCTRLREG, bHostControl);
}


/*
 * SDHostslot_reportslotstatechange
 */
void 
SDHostslot_reportslotstatechange(struct sd_slot_base *slot, 
                                 sd_slot_event event)
{
    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return;
    }

}

/*
 * SDHostslot_Desiredvdd
 */
u32 
SDHostslot_Desiredvdd( struct sd_slot_base *slot)
{
    u32 dwDesiredVddWindow = 0;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return 0;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return 0;
    }

    /* Return lowest supportable voltage. */
    if (slot->m_VddWindows & SD_VDD_17_18) {
        dwDesiredVddWindow = SD_VDD_17_18;
    }
    else if (slot->m_VddWindows & SD_VDD_29_30) {
        dwDesiredVddWindow = SD_VDD_29_30;
    }
    else if (slot->m_VddWindows & SD_VDD_32_33) {
        dwDesiredVddWindow = SD_VDD_32_33;
    }

    return dwDesiredVddWindow;
}

/*
 * SDHostslot_maxvdd
 */
u32 
SDHostslot_maxvdd(struct sd_slot_base *slot)
{
    u32 dwMaxVddWindow = 0;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

    if (!slot) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot\n", __FUNCTION__);
        return 0;
    }

    if (!slot->m_base) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null slot base\n", __FUNCTION__);
        return 0;
    }

    if (slot->m_VddWindows & SD_VDD_32_33) {
        dwMaxVddWindow = SD_VDD_32_33;
    }
    else if (slot->m_VddWindows & SD_VDD_29_30) {
        dwMaxVddWindow = SD_VDD_29_30;
    }
    else if (slot->m_VddWindows & SD_VDD_17_18) {
        dwMaxVddWindow = SD_VDD_17_18;
    }

    return dwMaxVddWindow;
}

void
SDHostslot_reinit(struct sd_slot_base *slot)
{

#if 0
    SDHostslot_Handlecardremove(slot, 0);

    SDHostslot_init (slot);

    SDHostslot_start (slot);

    SDHostslot_Handlecardinsert(slot);

    /*
     * Re-enable interrupts.
     */
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_ERRINTRSEN, 0x1f);
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_ERRINTRSGEN, 0x1f);
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSEN, 0xc3);
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSGEN, 0xc3);
#endif

    return;
}

#ifdef LINUX
EXPORT_SYMBOL (SDHostslot_reinit);
EXPORT_SYMBOL (SDHostslot_Handlecardinsert);
#endif

/* eof */
