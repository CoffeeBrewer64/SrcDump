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

/* USB HIDBP mouse driver */
//#include <usb.h>

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <iosusb.h>
#include <iosusbtypes.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define LOGITECH_VENDOR_ID 0x046d
#define LOGITECH_OPTICAL_MOUSE 0xc016
#define LOGITECH_ACER_MOUSE 0xc001

/* Buttons */
#define LBTN 0x1
#define RBTN 0x2
#define MBTN 0x4
#define BTN_IDX 0
/* X, Y displacements*/
#define X_IDX 1
#define X_MIOS 0xff /* 8 bits */
#define Y_IDX 2
#define Y_MIOS 0xff /* 8 bits */
#define SCROLL_IDX 3
#define SCROLL_MIOS 0xff /* 8 bits */

struct mouse_t {
    char data[8];
    int data_ep; 
};
static struct mouse_t mouse; 

struct mouse_report_t {
    unsigned lbtn;
    unsigned mbtn;
    unsigned rbtn;
    int xdis;
    int ydis;
    int scroll;
};

int
verify_mouse(USB_IntfDescr_t *intf)
{
    int ret = -1; 
    printf("verify_mouse: ");
    if ( intf->bNumEndpoints != 1 ) goto done;
    if (intf->bInterfaceClass != 3) goto done;
    if (intf->bInterfaceSubClass != 1) goto done;
    /* Verify we have a boot protocol mouse */
    if (intf->bInterfaceProtocol != 2) goto done;
    if ( (intf->ep[0].bmAttributes & 3) != 3) goto done;
    if ( (intf->ep[0].bEndpointAddress & 0x80) == 0) goto done;
    else ret = intf->ep[0].bEndpointAddress;
done:
    return ret;
}

void
fill_report(struct mouse_report_t *rep, char *data)
{
    rep->lbtn = data[BTN_IDX] & LBTN; 
    rep->mbtn = data[BTN_IDX] & MBTN; 
    rep->rbtn = data[BTN_IDX] & RBTN; 
    rep->xdis = (int) (data[X_IDX] & X_MIOS);
    rep->ydis = (int) (data[Y_IDX] & Y_MIOS);
    rep->scroll = (int) (data[SCROLL_IDX] & SCROLL_MIOS);
    return;
}

void
print_report(struct mouse_report_t rep, struct mouse_report_t oldrep)
{
    if (rep.lbtn && (rep.lbtn != oldrep.lbtn))
        printf("Left button clicked\n");
    if (rep.mbtn && (rep.mbtn != oldrep.mbtn))
        printf("Middle button clicked\n");
    if (rep.rbtn && (rep.rbtn != oldrep.rbtn))
        printf("Right button clicked\n");
    if (0 != (rep.xdis - oldrep.xdis)) 
        printf("X displacement [raw data] = 0x%02x\n", rep.xdis);
    if (0 != (rep.ydis - oldrep.ydis))
        printf("Y displacement [raw data] = 0x%02x\n", rep.ydis);
    if (0 != (rep.scroll - oldrep.scroll))
        printf("scroll input[raw data] = 0x%02x\n", rep.scroll);
    return; 
}

void
print_data(char * data)
{
    int i;
    for (i = 0; i < 8; ++i )
        printf("data[%d] = 0x%08x\n",i, data[i]);
}

#define NUM_POINTS 256
int
usb_mouse()
{   
    struct mouse_report_t report, old_report;
    int stat = 0;
    int verbose = 0;
    char buf[128];
    int maj, min;
    buf[127] = '\0';
    int i = NUM_POINTS;
    USB_ConfDescr_t c;

    printf("*** Sample USB HIDBP mouse driver ***\n");
    printf("Reads 256 data samples and exits \n");
    printf("Currently tested with Logitech optical usb mouse & Logitech USB Mouse\n");
    
    /* If debug is on, print all data */
    if ( getenv("IOS_USB_DEBUG") != NULL )
        verbose = 1;

    /* Find a supported mouse */
    if ( IOS_ERROR_OK == IUSB_FindDeviceIds(LOGITECH_VENDOR_ID, LOGITECH_OPTICAL_MOUSE, &maj, &min)) {
        printf("Found USB mouse: (qid: %d id: %d)\n", maj, min);
    }
    else if ( IOS_ERROR_OK == IUSB_FindDeviceIds(LOGITECH_VENDOR_ID, LOGITECH_ACER_MOUSE, &maj, &min)) {
        printf("Found USB mouse (qid: %d id: %d\n)", maj, min);
    }
    else {
        printf("Device (vendor 0x046d product 0xc016) not found\n");
        printf("No suitable mouse was found. Exiting...\n");
        IOS_ThreadExit(0);
    }
    /* Register device */
    if ( IOS_ERROR_OK != IUSB_RegisterResourceManager(min) ) {
        printf("Registering mouse driver failed. Exiting...\n");
        IOS_ThreadExit(0);
    }
    else
      printf("Mouse driver registered successfully...\n");
    /* Get info for config 1 */
    c.bConfigurationValue = 1; 
    IUSB_GetConfDescr(min, maj, &c);
    /* Get endpoint for data */
    if ( -1 == (mouse.data_ep = verify_mouse(&c.intf[0]))) {
        printf("Verifying that device found is a valid USB mouse failed. Exiting...\n");
        IOS_ThreadExit(0);
    }
    else
        printf("Verified that device found is a valid USB mouse\n");

    /* Start reading interrupt packets (256 + 1 data samples )*/
    stat = IUSB_ReadIntrMsg(min, maj, c.intf[0].ep[0].bEndpointAddress, sizeof(mouse.data), mouse.data);
    fill_report(&report, mouse.data);
    while(i--) {
        printf("Mouse data sample %d: \n", NUM_POINTS - i);
        stat = IUSB_ReadIntrMsg(min, maj, c.intf[0].ep[0].bEndpointAddress, sizeof(mouse.data), mouse.data);
        if (verbose)
            print_data(mouse.data);
        if ( 0 == stat ) {
            old_report = report;
            fill_report(&report, mouse.data);
            print_report(report, old_report);
        }
        usleep(10*1000); /* 100 scans a sec */
    }
    /* Unregister device */
    if ( IOS_ERROR_OK != IUSB_UnregisterResourceManager(min) ) {
        printf("Un-registering mouse driver failed. Exiting...\n");
        IOS_ThreadExit(0);
    }
    else
      printf("Mouse driver de-registered successfully...\n");
    IUSB_ResetEndpoint(min, maj, c.intf[0].ep[0].bEndpointAddress);
    IUSB_ResetDevice(min, maj);
    return IOS_ThreadExit(0);
}
