/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 * $Id: sd_load.c,v 1.1 2006/05/05 21:46:55 jlivesey Exp $
 */

#include <iostypes.h>
#include <iop.h>
#include <ios.h>
#include <ioslibc.h>

#include "boot2.h"

SDDevHandle fd;

/*
 * sd_init
 *
 * Open the SD device and object a handle for it.
 */
IOSError
sd_init(void)
{
    IOSError rc = IOS_ERROR_OK;
    u32 slotNo;

    BOOT2_ENTRY();

    rc = ISD_InitCard ();
    if (rc != IOS_ERROR_OK) {
        printf ("%s: bad sd init %d\n",
                __FUNCTION__, rc);
        return rc;
    }

    for (slotNo = 0; slotNo < 2; slotNo++) {
        fd->SDDevSlot = slotNo;
        fd->SDDevFd = -1;
        rc = ISD_MountCard (fd->SDDevSlot, &fd);
        if (rc == IOS_ERROR_OK) {
            printf ("%s: mount succeeded slot %d\n",
                    __FUNCTION__, fd->SDDevSlot);
            break;
        } else {
            printf ("%s: mount failed %d slot %d\n",
                    __FUNCTION__, rc, fd->SDDevSlot);
        }
    }
    if (rc != IOS_ERROR_OK) {
        printf ("%s: no card in any slot %d\n",
                __FUNCTION__, rc);
        return rc;
    }

    BOOT2_EXIT();

    return rc;
}

/*
 * sd_read
 *
 * Read a page from the SD card into the memory staging area.
 */
IOSError
sd_read(u32 offset, u32 *data, u32 length)
{
    IOSError rc = IOS_ERROR_OK;

    BOOT2_ENTRY();

    rc = ISD_ReadBlock (fd, offset, data, length);
    if (rc != IOS_ERROR_OK) {
        printf ("%s: read failed 0x%08x slot %d\n",
                __FUNCTION__, rc, fd->SDDevSlot);
        return rc;
    }

    BOOT2_EXIT();

    return rc;
}

/* eof */
