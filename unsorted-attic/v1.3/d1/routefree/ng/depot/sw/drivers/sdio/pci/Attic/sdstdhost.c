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

#ident "$Id: sdstdhost.c,v 1.2 2005/12/21 04:07:57 gbarnard Exp $"

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

int host_debug = 0;

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

/*
 * reg_name
 *
 * Retrun the name of a host controller slot register, or "unknown".
 * Useful for debugging.
 */
static char *
reg_name(int reg)
{

    reg = reg >> 1;

    if ((reg >= 0) && (reg < (sizeof(reg_names)/sizeof(char *)))) {
        return reg_names[reg];
    }

    return "unknown";
}


/*
 * Routines to access card registers.  These are called out here
 * because on another system we may have to supply different low-level
 * calls to replace the Linux calls.
 */
u8 
READ_HOST_U8(u32 base, u16 reg)
{
    u8 ret;

    ret = readb((void __iomem *)base + reg);

    PCI_DEBUG (DEBUG_PCI_REG_READ, "%s: reg 0x%x ==> 0x%x (%s)\n",
               __FUNCTION__, reg, ret, reg_name(reg));

    return ret;
}

void 
WRITE_HOST_U8(u32 base, u16 reg, u8 val)
{
    PCI_DEBUG (DEBUG_PCI_REG_WRITE, "%s: reg 0x%x <== 0x%x (%s)\n",
               __FUNCTION__, reg, val, reg_name(reg));

    writeb(val, (void __iomem *)base + reg);
}

u16
READ_HOST_U16(u32 base, u16 reg)
{
    u16 ret;

    ret = readw((void __iomem *)base + reg);

    PCI_DEBUG (DEBUG_PCI_REG_READ, "%s: reg 0x%x ==> 0x%x (%s)\n",
               __FUNCTION__, reg, ret, reg_name(reg));

    return ret;
}

void 
WRITE_HOST_U16(u32 base, u16 reg, u16 val)
{
    PCI_DEBUG (DEBUG_PCI_REG_WRITE, "%s: reg 0x%x <== 0x%x (%s)\n",
               __FUNCTION__, reg, val, reg_name(reg));

    writew(val, (void __iomem *)base + reg);
}

u32 
READ_HOST_U32(u32 base, u16 reg)
{
    u32 ret;

    ret = readl((void __iomem *)base + reg);

    PCI_DEBUG (DEBUG_PCI_REG_READ, "%s: reg 0x%x ==> 0x%x (%s)\n",
               __FUNCTION__, reg, ret, reg_name(reg));

    return ret;
}

void 
WRITE_HOST_U32(u32 base, u16 reg, u32 val)
{
    PCI_DEBUG (DEBUG_PCI_REG_WRITE, "%s: reg 0x%x <== 0x%x (%s)\n",
               __FUNCTION__, reg, val, reg_name(reg));

    writel(val, (void __iomem *)base + reg);
}

/*
 * sdstdhost_init
 *
 * All the routine does is to check the slot count from the host
 * controller hardware, and make sure that it's a reasonable value.
 * Then call sdstdhost_initializehost.
 */
status_t
sdstdhost_init(struct sd_host *sdh)
{
    status_t status = st_success;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: 0x%x\n",
            __FUNCTION__, (u32)sdh);

    if (!sdh) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return st_fail_no_sdh;
    }

    if (!sdh->ops) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: ops not set\n",
                __FUNCTION__);
        return st_fail_no_ops;
    }

    sdh->m_slotcount = sdh->ops->sdhostdetermineslotcount(sdh);
    if (sdh->m_slotcount == 0) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: zero slots\n",
                __FUNCTION__);
        return st_fail_no_slots;
    }

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: slot count %d\n",
            __FUNCTION__, sdh->m_slotcount);

    if (sdh->m_slotcount > SDHOST_MAX_SLOTS) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: bad slot count %d\n",
                __FUNCTION__, sdh->m_slotcount);
        return st_fail_bad_slot_count;
    }

    spin_lock_init(&sdh->lock);

    status = sdstdhost_initializehost(sdh);
    if (status != st_success) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: bad sdstdhost_initializehost() %s\n",
                __FUNCTION__, decode_status(status)); 
    }


    

    return status;
}

/*
 * sdstdhost_initializehost
 *
 * This calls sd_pci_init_slot().  See the comments for that routine
 * in sd-pci.c.
 */
status_t
sdstdhost_initializehost(struct sd_host *sdh)
{
    status_t status = st_success;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: 0x%x\n",
            __FUNCTION__, (u32)sdh);

    if (!sdh) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return st_fail_no_sdh;
    }

    if (!sdh->ops) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: ops not set\n",
                __FUNCTION__);
        return st_fail_no_ops;
    }

    if (0 == sdh->ops->sdhostinitilizeslotwindow(sdh)) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: sdhostinitilizeslotwindow failed\n",
                __FUNCTION__);
        return st_fail_bad_slot_window;
    }

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: done\n",
            __FUNCTION__);

    return status;
}

/*
 * sdstdhost_deinitializehost
 *
 * This calls sd_pci_deinit_slot.  See the comments for that routine
 * in sd-pci.c.
 */
status_t
sdstdhost_deinitializehost(struct sd_host *sdh)
{
    status_t status = st_success;

    PCI_DEBUG (DEBUG_PCI_INIT, "%s: 0x%x\n",
            __FUNCTION__, (u32)sdh);

    if (!sdh) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return st_fail_no_sdh;
    }

    if (!sdh->ops) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: ops not set\n",
                __FUNCTION__);
        return st_fail_no_ops;
    }

    if (0 == sdh->ops->sdhostdeinitilizeslotwindow(sdh)) {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: sdhostdeinitilizeslotwindow failed\n",
                __FUNCTION__);
        return st_fail_bad_slot_window;
    }

    return status; 
}

/*
 * sdstdhost_handleinterrupt
 *
 * Call this function from the Interrupt thread.  It looks at the
 * global interrrupt status value, dwIntStatus, and for each bit set
 * in that value, it calls the slot interrupt routine for the
 * corresponding slot.
 */

void 
sdstdhost_handleinterrupt(struct sd_host *sdh, u16 dwIntStatus)
{
    struct sd_slot_base *pbaseptr, *pSlot = 0;
    u8 dwSlot;

    if (host_debug)
        PCI_DEBUG (DEBUG_PCI_IRQ, "%s: sdh 0x%x\n",
                __FUNCTION__, (u32)sdh);

    spin_lock_irq(&sdh->lock);

    /*
     * Use slot zero to get the shared global interrupt register
     */
    pbaseptr = sdh->m_sdslot;
    if (!pbaseptr) {
        spin_unlock(&sdh->lock);
        return;
    }

    PCI_DEBUG (DEBUG_PCI_IRQ, "%s: dwIntStatus 0x%x\n",
            __FUNCTION__, dwIntStatus);

	/*
	 * For each slot that has its main IRQ bit set, handle IRQ
	 */
    for (dwSlot = 0; dwSlot < sdh->m_slotcount; dwSlot++) 
    {
        if (((1 << dwSlot) & dwIntStatus) /* || pSlot->NeedsServicing() */ ) 
        {
        	PCI_DEBUG (DEBUG_PCI_IRQ, "%s:handle slot[%d] irq\n",__FUNCTION__,dwSlot);
        	pSlot = &sdh->m_sdslot[dwSlot];
            SDHostslot_Handleinterrupt(pSlot);
        }
    }

    spin_unlock(&sdh->lock);

    return;
}


/* eof */
