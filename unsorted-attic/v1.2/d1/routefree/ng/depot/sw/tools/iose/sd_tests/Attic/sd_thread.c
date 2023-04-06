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

#ident "$Id: sd_thread.c,v 1.1 2005/12/21 02:51:31 gbarnard Exp $"

/*
 * System includes
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <string.h>
#include <linux/ioctl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <iostypes.h>

/*
 * Local includes
 */
#include "./sd_test.h"
#include "./sd_api.h"
#include <sd_ioctl.h>

/*
 * SDDevRemoveThread
 *
 * This thread is created when ISD_RegisterDeviceRemovalHandler() is
 * called.  When created, this thread makes an SD_WAIT_ENSERT ioctl
 * and when it returns, it calls the SDDevRemoveHandler call-back
 * routine.  This thread will be cancelled when the API routine
 * ISD_UnregisterDeviceRemovalHandler() is called.
 */
static void *
SDDevRemovalThread(void *data)
{
    SDDevHandle fd;
    int status;

    fd = (SDDevHandle)data;

    while (1) {
        status = ioctl(fd->SDDevFd, SD_WAIT_INSERT, &fd->SDDevSlot);
        if (status < 0) {
            perror ("ioctl");
            printf ("%s: Bad ioctl 0x%x\n", 
                     __FUNCTION__, status);
            return false;
        }
        if (fd->SDDevRemoveHandler) {
            fd->SDDevRemoveHandler (status);
        } else {
            printf ("%s: no remove handler installed\n",
                    __FUNCTION__);
            pthread_exit (0);
        }
    }
}

/*
 * SDDevRemoveThread
 *
 * This thread is created when ISD_RegisterDeviceInterruptHandler() is
 * called.  When created, this thread makes an SD_WAIT_ENSERT ioctl
 * and when it returns, it calls the SDDevRemoveHandler call-back
 * routine.  This thread will be cancelled when the API routine
 * ISD_UnregisterDeviceInterruptHandler() is called.
 */
static void *
SDDevInterruptThread(void *data)
{
    SDDevHandle fd;
    int status;

    printf ("%s: data 0x%x\n",
            __FUNCTION__, (u32)data);

    fd = (SDDevHandle)data;

    while (1) {
        printf ("%s: about to call SD_WAIT_INSERT\n",
                __FUNCTION__);
        status = ioctl(fd->SDDevFd, SD_WAIT_INSERT, &fd->SDDevSlot);
        if (status < 0) {
            perror ("ioctl");
            printf ("%s: Bad ioctl 0x%x\n", 
                     __FUNCTION__, status);
            return false;
        }
        printf ("%s: SD_WAIT_INSERT status 0x%x\n",
                __FUNCTION__, status);
        if (fd->SDDevInterruptHandler) {
            fd->SDDevInterruptHandler (status);
        } else {
            printf ("%s: no interrupt handler installed\n",
                    __FUNCTION__);
            pthread_exit (0);
        }
    }
}

/*
 * SDDevRemoveThread
 *
 * This thread is created when ISD_RegisterDeviceRemovalHandler() is
 * called.  When created, this thread makes an SD_WAIT_ENSERT ioctl
 * and when it returns, it calls the SDDevErrHandler call-back
 * routine.  This thread will be cancelled when the API routine
 * ISD_UnregisterDeviceRemovalHandler() is called.
 */
static void *
SDDevErrThread(void *data)
{
    SDDevHandle fd;
    int status;

    printf ("%s: data 0x%x\n",
            __FUNCTION__, (u32)data);

    fd = (SDDevHandle)data;

    while (1) {
        printf ("%s: about to call SD_WAIT_INSERT\n",
                __FUNCTION__);
        status = ioctl(fd->SDDevFd, SD_WAIT_INSERT, &fd->SDDevSlot);
        if (status < 0) {
            perror ("ioctl");
            printf ("%s: Bad ioctl 0x%x\n", 
                     __FUNCTION__, status);
            return false;
        }
        printf ("%s: SD_WAIT_INSERT status 0x%x\n",
                __FUNCTION__, status);
        if (fd->SDDevErrorHandler) {
            fd->SDDevErrorHandler (status);
        } else {
            printf ("%s: no err handler installed\n",
                    __FUNCTION__);
            pthread_exit (0);
        }
    }
}

/*
 * sdio_thread_create
 *
 * Creates the background threads that wait for events from the driver
 * and then invoke call-back routines.
 *
 * We assume that if we get here, the basic error checking on the 'fd'
 * being valid and open has already been done by the API routine.  If
 * this turns out to be a fragile assumption, we will open up the
 * is_valid and is_open routines that are currently defined statis.
 */
IOSError
sdio_thread_create (SDDevHandle fd, SDDevThread type) 
{

    switch (type) {
    case SDDevRemove:
        fd->SDDevRemoval_tid = pthread_create(&fd->SDDevRemoval_thread,
                                              NULL, SDDevRemovalThread,
                                              (void *)fd);
        if (fd->SDDevRemoval_tid) {
            perror ("pthread_create");
            printf ("%s: thread create failed\n",
                    __FUNCTION__);
            return IOS_ERROR_SDIO_ERR;
        }
        break;
    case SDDDevInterrupt:
        fd->SDDevInt_tid = pthread_create(&fd->SDDevInt_thread,
                                              NULL, SDDevInterruptThread,
                                              (void *)fd);
        if (fd->SDDevInt_tid) {
            perror ("pthread_create");
            printf ("%s: thread create failed\n",
                    __FUNCTION__);
            return IOS_ERROR_SDIO_ERR;
        }
        break;
    case SDDevError:
        fd->SDDevErr_tid = pthread_create(&fd->SDDevErr_thread,
                                              NULL, SDDevErrThread,
                                              (void *)fd);
        if (fd->SDDevErr_tid) {
            perror ("pthread_create");
            printf ("%s: thread create failed\n",
                    __FUNCTION__);
            return IOS_ERROR_SDIO_ERR;
        }
        break;
    default:
        printf ("%s: bad thread type 0x%x\n",
                __FUNCTION__, type);
        return IOS_ERROR_SDIO_ERR;
    }

    return IOS_ERROR_OK;
}
/* eof */
