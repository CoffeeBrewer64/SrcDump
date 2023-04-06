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
#ifndef __SK_USB_H__
#define __SK_USB_H__

#include <ng.h>
#include <sktypes.h>
#include <ngtypes.h>
#include <arm.h>
#include "thread.h"
#include "message.h"
#include "emu_usb.h"

#define SK_DEV_NODE_MAX 16
#define SK_DEV_CHLD_MAX 4
#define SK_DEV_NAME_MAX 8 /* [a-zA-Z0-9_-] */
#define USB_DEV_EHCI_MAX 1

typedef enum {SK_DEV_UNUSED, SK_DEV_USED, SK_DEV_DUMMY, SK_DEV_USBROOT, SK_DEV_USBHC, SK_DEV_USB} SKDevType; 

struct SKDevice {
    char name[SK_DEV_NAME_MAX];
    SKDevType typ;
    void *dev; /* device-type specific struct */
    SKMessageQueueId driverQId;
    SKMessageQueueId hcdQId;
    int parent;
    int chld[SK_DEV_CHLD_MAX];
};
typedef struct SKDevice SKDevice_t;

struct USB_hcd {
    SKMessage inQ[USB_DEV_INQ_MAX];
    SKMessageQueueId in;
};
typedef struct USB_hcd USB_hcd_t;

void USB_AddTree(const char *path, SKDevType typ, void *dev, SKMessageQueueId driverQId);
#endif /* __SK_USB_H__ */
