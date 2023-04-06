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

#ident "$Id: sdbuscore.c,v 1.1 2005/11/17 19:52:41 jlivesey Exp $"

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

/*
 * sd_suspend_host
 */
int 
sd_suspend_host(struct sd_host *host, u32 state)
{
#if 0
        sd_claim_host(host);
//      sd_deselect_cards(host);
        sd_release_host(host);
#endif

        return 0;
}

/*
 * sd_resume_host
 */
int 
sd_resume_host(struct sd_host *host)
{
#if 0
        sd_detect_change(host);
#endif

        return 0;
}



/* eof */
