a0 44
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
#include <ios.h>
#include <versaios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <ohci.h>
#include <ohci_regs.h>
#include "ohci_core.h"
#include "ohci_ed.h"

extern struct ohci_device __ohci_dev[OHCI_DEV_MAX]; 
void
initOHCIDevNodes(void)
{ 
  memset(__ohci_dev, 0, sizeof(__ohci_dev)); /* UNUSED == 0 */
}

u16 
initDevNode(u8 port, u8 hub, u8 spd)
{
  u16 devnum = 0;
  for (devnum = 1; devnum < OHCI_DEV_MAX; ++devnum) {
    if (OHCI_DEV_UNUSED == __ohci_dev[devnum].type) {
        __ohci_dev[devnum].type = OHCI_DEV_DEV; /*XXX horti: adding hubs later */
        __ohci_dev[devnum].dev.dev.port = port;
        __ohci_dev[devnum].dev.dev.hub = hub;
        __ohci_dev[devnum].dev.dev.ed0 = allocED();
        __ohci_dev[devnum].dev.dev.spd = (spd == 0)? 0:1;
        __ohci_dev[devnum].dev.dev.maxP = 8;
        goto done;
    }
  }
done:
  return devnum;
}
