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
#include <iostypes.h>
#include <arm.h>
#include <ioslibc.h>
#include <iosusbtypes.h>
#include <iosusb.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void 
start_test(IOSMessageQueueId qid, u32 devId)
{
    char buf[255];
    buf[0] = '\0';
    IUSB_GetAsciiStr(devId, qid, 1, USB_STD_LANG_EN_US, 255, buf);
    printf("usb_cdrvr: ascii string = %s\n", buf);
}

void
usb_cdrvr(void)
{
    char buf[128];
    int maj, min;
    buf[127] = '\0';
    if ( IOS_ERROR_OK == IUSB_FindDevice(0x046d, 0xc016, buf, 127))
        printf("Found device: %s\n", buf);
    bzero(buf, sizeof(buf));
    if ( IOS_ERROR_OK == IUSB_FindDevice(0x0781, 0x5151, buf, 127)) 
        printf("Found device: %s\n", buf);
    if ( IOS_ERROR_OK == IUSB_FindDeviceIds(0x0781, 0x5151, &maj, &min)) {
        printf("Found device: qid: %d id: %d\n", maj, min);
        start_test(maj, min);
    }
    else
        printf("Device (vendor 0x0781 product 0x5151) not found\n");
    if ( IOS_ERROR_OK == IUSB_FindDeviceIds(0x046d, 0xc016, &maj, &min)) {
        printf("Found device: qid: %d id: %d\n", maj, min);
        start_test(maj, min); 
    }
    else
        printf("Device (vendor 0x046d product 0xc016) not found\n");
    if ( IOS_ERROR_OK == IUSB_FindDeviceIds(0x046d, 0xc001, &maj, &min)) {
        printf("Found device: qid: %d id: %d\n", maj, min);
        start_test(maj, min); 
    }
    else
        printf("Device (vendor 0x046d product 0xc001) not found\n");
    IOS_ThreadExit(0);
}
