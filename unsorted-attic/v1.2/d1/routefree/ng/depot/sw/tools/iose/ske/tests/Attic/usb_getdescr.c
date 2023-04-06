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

#include <usb.h>

#include <sk.h>
#include <ng.h>
#include <sktypes.h>
#include <arm.h>
#include <nglibc.h>
#include <skusb.h>

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
#define X_MSK 0xff /* 8 bits */
#define Y_IDX 2
#define Y_MSK 0xff /* 8 bits */
#define SCROLL_IDX 3
#define SCROLL_MSK 0xff /* 8 bits */

//typedef unsigned short u16;
struct mouse_t {
    char data[8];
    char name[64];
    struct usb_device *dev;
    struct usb_dev_handle *handle;
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

void
print_info(struct usb_device *dev, usb_dev_handle *udev)
{
    char string[64];
    if (dev->descriptor.iManufacturer)
        if ( usb_get_string_simple(udev, dev->descriptor.iManufacturer,
                    string, sizeof(string)) > 0 )
            printf("Manufacturer: %s \t", string);
    if (dev->descriptor.iProduct)
        if ( usb_get_string_simple(udev, dev->descriptor.iProduct,
                    string, sizeof(string)) > 0 )
            printf("Product: %s\n", string);
    strncpy(mouse.name, string, strlen(string));
    return;
}

int
verify_mouse(struct usb_device *dev, usb_dev_handle *udev)
{
    int ret = 0;
    struct usb_interface_descriptor *intf = dev->config[0].interface[0].altsetting;
    if ( intf->bNumEndpoints != 1 ) ret = -1;
    if (intf->bInterfaceClass != 3) ret = -1;
    if (intf->bInterfaceSubClass != 1) ret = -1;
    if (intf->bInterfaceProtocol != 2) ret = -1; /* Boot protocol mouse */

    if ( (intf->endpoint->bmAttributes & 3) != 3) ret = -1;
    if ( (intf->endpoint->bEndpointAddress & 0x80) == 0) ret = -1;
    else
        mouse.data_ep = intf->endpoint->bEndpointAddress;

    return ret;
}

usb_dev_handle *
find_mouse(struct usb_device *dev, 
        u16 vendor_id, 
        u16 product_id,
        struct mouse_t *mouse)
{
    int i;
    usb_dev_handle *udev = usb_open(dev);
    if ( NULL == udev ) 
        return NULL;
    if ( vendor_id == dev->descriptor.idVendor  
            && product_id == dev->descriptor.idProduct
       ) {
        print_info(dev, udev);
        if ( -1 == verify_mouse(dev,udev) )
            return NULL;
        mouse->dev = dev;
        return udev;
    }
    else {
        for (i = 0; i < dev->num_children; i++)
            if ( NULL != (udev = find_mouse(dev->children[i], vendor_id, product_id, mouse)))
                return udev;
    }
    return NULL;
}

usb_dev_handle *
mouse_find_device(u16 vendor_id, u16 product_id, struct mouse_t  *mouse)
{
    struct usb_bus *bus;
    usb_dev_handle *ret;
    usb_init();
    usb_find_busses();
    usb_find_devices();
    for (bus = usb_busses; bus; bus = bus->next) {
        ret = find_mouse(bus->root_dev, vendor_id, product_id, mouse);
        if ( NULL != ret ) 
            return ret;

    }
    return NULL;
}

void
fill_report(struct mouse_report_t *rep, char *data)
{
    rep->lbtn = data[BTN_IDX] & LBTN; 
    rep->mbtn = data[BTN_IDX] & MBTN; 
    rep->rbtn = data[BTN_IDX] & RBTN; 
    rep->xdis = (int) (data[X_IDX] & X_MSK);
    rep->ydis = (int) (data[Y_IDX] & Y_MSK);
    rep->scroll = (int) (data[SCROLL_IDX] & SCROLL_MSK);
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

int
register_mouse(void)
{
    int intf_num = mouse.dev->config[0].interface[0].altsetting->bInterfaceNumber;
    return usb_claim_interface(mouse.handle, intf_num);
}

int
unregister_mouse(void)
{
    int intf_num = mouse.dev->config[0].interface[0].altsetting->bInterfaceNumber;
    return usb_release_interface(mouse.handle, intf_num);
}

void
dumpEp(USB_EpDescr_t e)
{
  printf("-----  Endpoint descriptor  (%p) -------------------\n", &e);
  printf("Endpoint address:  = %d\n", e.bEndpointAddress);
  printf("MaxPacket size:  = %d\n", e.wMaxPacketSize);
  printf("----------------------------------------------------\n");
}
void
dumpInterface(USB_IntfDescr_t i)
{
  int k;
  printf("-----  Interface descriptor  (%p) -------------------\n", &i);
  printf("Interface[%d]: numInterfaces = %d\n", i.bInterfaceNumber,
          i.bNumEndpoints);
  for ( k = 0; k < i.bNumEndpoints; ++k ) {
      dumpEp(i.ep[k]);
  }
  printf("----------------------------------------------------\n");
}

void
dumpConfDescr(USB_ConfDescr_t c)
{
  int i;
  printf("-----  Conf descriptor  (%p) -------------------\n", &c);
  printf("Configuration[%d]: numInterfaces = %d\n", c.bConfigurationValue,
          c.bNumInterfaces);
  for ( i = 0; i < c.bNumInterfaces; ++i ) {
      dumpInterface(c.intf[i]);
  }
  printf("----------------------------------------------------\n");
}

void dumpDevDescr(USB_DevDescr_t d)
{
  printf("-----  dev descriptor (%p) -------------------\n", &d);
  printf("Vendor id:0x%x Product id:0x%x\n", d.idVendor, d.idProduct);
  printf("bcdUSB: 0x%x  DeviceClass: %u  DeviceSubClass:%u DeviceProtocol%u\n",
          d.bcdDevice, d.bDeviceClass, d.bDeviceSubClass, d.bDeviceProtocol);
  printf("numConfigurations = %u\n", d.bNumConfigurations);
  printf("----------------------------------------------------\n");
}

int
usb_getdescr()
{   
    int verbose = 0;
    int maj, min;
    USB_DevDescr_t d;
    USB_ConfDescr_t c;

    if ( getenv("USB_DEBUG") != NULL )
        verbose = 1;

    if ( SK_ERROR_OK == IUSB_FindDeviceIds(LOGITECH_VENDOR_ID, LOGITECH_OPTICAL_MOUSE, &maj, &min)) {
        printf("Found device: qid: %d id: %d\n", maj, min);
    }
    else if ( SK_ERROR_OK == IUSB_FindDeviceIds(LOGITECH_VENDOR_ID, LOGITECH_ACER_MOUSE, &maj, &min)) {
        printf("Found device: qid: %d id: %d\n", maj, min);
    }
    else {
        printf("Device (vendor 0x046d product 0xc016) not found\n");
        printf("No suitable mouse was found. Exiting...\n");
        SK_ThreadExit(0);
    }
    USB_GetDevDescr(min, maj, &d);
    dumpDevDescr(d);
    c.bConfigurationValue = 1; /* get info for config 1 */
    USB_GetConfDescr(min, maj, &c);
    dumpConfDescr(c);
    return SK_ThreadExit(0);
}
