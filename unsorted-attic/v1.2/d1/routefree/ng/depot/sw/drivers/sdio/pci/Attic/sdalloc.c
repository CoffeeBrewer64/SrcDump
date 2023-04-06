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

#ident "$Id: sdalloc.c,v 1.1 2005/11/17 19:52:41 jlivesey Exp $"

#include <linux/config.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/completion.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/pagemap.h>
#include <linux/err.h>

#include "../include/sd.h"
#include "../include/sd_pci.h"

/*
 * sd_alloc_host
 *
 * This routine actually allocates space for struct sd_host
 * plus extra space for private data, length passed in.
 *
 * Originally this code used the variable 'host', but I have
 * changed this to 'sdh' to be compatible with sdpci_probe.
 * The convention seems to be:
 *
 * struct sd_host    *sdh;
 * struct sdpci_host *host
 */
struct sd_host *
sd_alloc_host(int extra, struct device *dev)
{
	struct sd_host *sdh;

	sdh = kmalloc(sizeof(struct sd_host) + extra, GFP_KERNEL);
	if (sdh) {
		memset(sdh, 0, sizeof(struct sd_host) + extra);

		spin_lock_init(&sdh->lock);
		init_waitqueue_head(&sdh->wq);
#if 0
		INIT_LIST_HEAD(&sdh->cards);
		INIT_WORK(&sdh->detect, sd_rescan, sdh);
#endif

		sdh->dev = dev;

		/*
		 * By default, hosts do not support SGIO or large requests.
		 * They have to set these according to their abilities.
		 */
		sdh->max_hw_segs = 1;
		sdh->max_phys_segs = 1;
		sdh->max_sectors = 1 << (PAGE_CACHE_SHIFT - 9);
		sdh->max_seg_size = PAGE_CACHE_SIZE;
	}

	return sdh;
}

/*
 * sd_free_host
 *
 * Free all the host allocated space, including the extra
 * space allocated for private data.
 */
void 
sd_free_host(struct sd_host *sdh)
{

	if (sdh) {
#if 0
		flush_scheduled_work();
#endif
		kfree(sdh);
	}
}

/*
 * sd_add_host
 */
int 
sd_add_host(struct sd_host *sdh)
{
	static u32 host_num;

	snprintf(sdh->host_name, sizeof(sdh->host_name), "SD%d", host_num++);

//	sd_power_up(sdh);

#if 0
	sd_detect_change(sdh);
#endif

	return 0;
}

/*
 * sd_remove_host
 */
void 
sd_remove_host(struct sd_host *sdh)
{

#if 0
	struct list_head *l, *n;

	list_for_each_safe(l, n, &sdh->cards) {
		struct sd_card *card = sd_list_to_card(l);

		sd_remove_card(card);
	}
#endif
}
/* eof */
