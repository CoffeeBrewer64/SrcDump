a0 45
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
#include <iostypes.h>
#include <ios.h>
#include <iop.h>
#include <ioslibc.h>

#include "ohci.h"
#include "ohci_regs.h"
#include "ohci_core.h"
#include "usb11.h"
#include "ohci_types.h"

u32 
calcBusTransTime_ns(u32 speed, u32 dir, u32 type, u32 bytes)
{
  u32 rv = 0;
  switch (speed) {
      case OHCI_SPD_FULL:
          rv = 8354L *(3167L + 8L*7*bytes*1000/6)/100000L + HOST_DELAY;
          if (USB_ENDPT_ATTR_ISO == type) {
              rv += (OHCI_ED_DIR_IN == dir)? 7268L: 6265L;
          } else {
              rv += 9107L;
          }
          goto done;
      case OHCI_SPD_LOW:
          rv = (OHCI_ED_DIR_IN == dir)? 64060L: 64107L 
                 + 2 *HUB_LS_SETUP 
                 + ((OHCI_ED_DIR_IN == dir)? 
                         67667L:66700L) * (3167L + 8L*7*bytes*1000/6)/100000L
                 + HOST_DELAY;
          goto done;
  }
done:
  return rv; /* us */
}
