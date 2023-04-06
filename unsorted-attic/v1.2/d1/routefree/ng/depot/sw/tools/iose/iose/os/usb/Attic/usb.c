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
#include <iosdebug.h>
#include <iostypes.h>
#include <arm.h>
#include "emu_usb.h"
#include <iosusbtypes.h>
#include <iosusb.h>
#include "utils.h"
#include "thread.h"
#include "alloc.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <errno.h>

IOSDevice_t  __devnodes[IOS_DEV_NODE_MAX]; /* Space for allowed device nodes */
int __devroot = -1;
static int __usbInitialized = -1;

static inline int
__iosInitDevList(void)
{
    unsigned int i;
    unsigned int k;
    for ( i = IOS_DEV_NODE_MAX; i != 0; --i ) { 
        __devnodes[i - 1].typ = IOS_DEV_UNUSED;
        for ( k = IOS_DEV_CHLD_MAX; k != 0; --k )
            __devnodes[i - 1].chld[k - 1] = -1;
    }
    return 0;
}

static IOSError
__iosCheckDevName(char *src)
{
    IOSError ret = IOS_ERROR_OK;
    int i  = 0;
    if ( src[i] == '/') ++i; /* iosip initial / */
    while ( src[i] != '\0' ) {
        if ( ( (src[i] < 'a' || src[i] > 'z') 
                 && (src[i] < 'A' || src[i] > 'Z' )
                 && (src[i] < '0' || src[i] > '9' )
                 && (src[i] != '_')
                 && (src[i] != '-' ) 
                )) {
            DBG_PRINTF((dbg_fp, "Invalid device name: %s\n", src));
            goto done;
        }
        ++i;
    }
done:
    return ret;
}

static IOSError 
__iosFreeNode(int idx, int pidx)
{
    int k;
    __devnodes[idx].typ = IOS_DEV_UNUSED;
    for ( k = IOS_DEV_CHLD_MAX; k != 0; --k )
        __devnodes[idx].chld[k - 1] = -1;
    for ( k = IOS_DEV_CHLD_MAX; k != 0; --k ) {
        if ( idx ==  __devnodes[pidx].chld[k - 1])
            __devnodes[pidx].chld[k -1] = -1;
    }
    return IOS_ERROR_OK;
}

static IOSError 
__iosInitNode( int i,
              char *name, 
              IOSDevType typ,
              void *dev,
              IOSMessageQueueId driverQId
            )
{
    int k;
    if ( IOS_ERROR_INVALID == __iosCheckDevName(name) )
        return IOS_ERROR_INVALID;
    __devnodes[i].typ = typ;
    ios_strncpy(__devnodes[i].name, name, IOS_DEV_NAME_MAX);
    __devnodes[i].dev = dev;
    __devnodes[i].drvQId = driverQId;
  for ( k = 0; k < IOS_DEV_CHLD_MAX; ++k) 
      __devnodes[i].chld[k] = -1;
    return IOS_ERROR_OK;
}

static IOSError
__iosAllocNode(void)
{
    int i, k;
    for (i = 0; i < IOS_DEV_NODE_MAX; ++i ) {
        if ( IOS_DEV_UNUSED != __devnodes[i].typ )
            continue;
        __devnodes[i].typ = IOS_DEV_USED;
        __devnodes[i].hcdQId = -1;
        __devnodes[i].drvQId = -1;
//        ios_strncpy(__devnodes[i].name, name, IOS_DEV_NAME_MAX);
//        __devnodes[i].dev = dev;
//        __devnodes[i].driverQId = driverQId;
        for ( k = IOS_DEV_CHLD_MAX; k >= 0; --k )
            __devnodes[i].chld[k - 1] = -1; 
        return i;
    }
    return IOS_ERROR_MAX;
}

/* Find node in tree of name 'node' , starting at node 'idx' */
static int 
__iosFindNode(const char *node, int idx)
{
    int i;
    if ( 0 == ios_strcmp(__devnodes[idx].name, node))
        return idx;
    for ( i = 0; i < IOS_DEV_CHLD_MAX; ++i ) {
        if ( -1 == __devnodes[idx].chld[i]) 
            continue;
        if ( 0 == ios_strcmp(__devnodes[__devnodes[idx].chld[i]].name, node) ) 
            return __devnodes[idx].chld[i];
    }
    return -1;
}


static int 
__iosAddNode(int chld_idx, int parent_idx)
{
  int i;
  for ( i = 0; i < IOS_DEV_CHLD_MAX; ++i ) {
        if ( -1 !=  __devnodes[parent_idx].chld[i]) /* used */
            continue; 
        __devnodes[parent_idx].chld[i] = chld_idx; 
        __devnodes[chld_idx].parent = parent_idx;
        if ( __devnodes[chld_idx].typ == IOS_DEV_USB )
            __devnodes[chld_idx].hcdQId = __devnodes[parent_idx].hcdQId;
        else if (__devnodes[chld_idx].typ == IOS_DEV_USBHC )
            __devnodes[chld_idx].hcdQId = __devnodes[chld_idx].drvQId;
        return 0;
  }
  /* full */
  return -1;
}

static int 
__iosDelNode(int idx, int pidx)
{
  int i;
  for ( i = 0; i < IOS_DEV_CHLD_MAX; ++ i) {
    if ( -1 == __devnodes[idx].chld[i] ) 
        continue;
    __iosDelNode(__devnodes[idx].chld[i], idx);
  }
  printf("Deleting node index: %d\n", idx);
  __iosFreeNode(idx, pidx);
  if ( __devroot == idx ) {
      __devroot = -1;
  }
  return 0;
}

static void
iosutil_strcpyn(char *dstn, const char *src, int start, int end)
{
    int i = start;
    for ( i = start; i <= end; ++i ) {
        dstn[ i - start] = src[i];
    }
    dstn[end - start + 1] = '\0';
    return;
}

int
getNode(const char *path, char *node, int idx)
{
    int i = idx;
    int start, end;
    while ( path[i] == '/' && path[i] != '\0') ++i;
    start = i;
    while ( path[i] != '/' && path[i] != '\0') ++i;
    end = i - 1;
    iosutil_strcpyn(node, path, start, end);
    return i;
}

void 
dumpList(void)
{
    int i;
    for (i = 0; i < IOS_DEV_NODE_MAX; ++i ) {
        if ( IOS_DEV_UNUSED != __devnodes[i].typ )
            printf("Node %d: %s\n", i, __devnodes[i].name);
    }
}

void
dumpNode( IOSDevice_t node)
{
  int i;
  printf("--- Node: %s ---\n", node.name);
  if ( NULL != node.dev ) {
      USB_emu_device_t *dev = (USB_emu_device_t *) node.dev;
      printf("\t Vendor id: 0x%04x\n", dev->idVendor);
      printf("\t Product id: 0x%04x\n", dev->idProduct);
  }
  printf("\t Parent node id: %d\n", node.parent);
  printf("\t Driver queue id: %d\n", node.drvQId);
  printf("\t Driver TId: %d\n", node.drvTId);
  printf("\t HCD queue id: %d\n", node.hcdQId);
  printf("\t Node type = %d\n", node.typ);
  for ( i = 0; i < IOS_DEV_CHLD_MAX; ++i) {
      if ( -1 != node.chld[i]) {
          printf("node: %s child[%d] = %s\n", node.name,
                  i, __devnodes[node.chld[i]].name);
      }
  }
}

void
dumpTree(int idx)
{
  int i;
  printf("node: %s\n", __devnodes[idx].name);
  dumpNode(__devnodes[idx]);
  for ( i = 0; i < IOS_DEV_CHLD_MAX; ++i) {
      if ( -1 != __devnodes[idx].chld[i]) {
          dumpTree(__devnodes[idx].chld[i]);
      }
  }
  return;
}

void 
iosDumpDevTree(void)
{
  dumpTree(__devroot);      
}

static void
__iosAddRoot(const char *path)
{
    char node[IOS_DEV_NAME_MAX];
    if ( -1 != __devroot )
        goto done;
    getNode(path, node, 0);
    __devroot =  __iosAllocNode();
    __iosInitNode(__devroot, node, IOS_DEV_DUMMY, NULL, -1);
done:
    return;
}

void
USB_AddTree(const char *path, IOSDevType typ, void *dev, IOSMessageQueueId driverQId)
{
    int idx = __devroot;
    int path_idx = 0;
    char node[IOS_DEV_NAME_MAX];
    int chld;
    path_idx = getNode(path, node, path_idx); /* root */
    if ( idx == -1 || ( 0 != ios_strcmp(node, __devnodes[idx].name)) ) {
        printf("Trying to add device: %s\n", path);
        printf("Root should always be: /%s not /%s\n", __devnodes[idx].name, node);
        return;
    }
    do {
        path_idx = getNode(path, node, path_idx);
        if ( node[0] != '\0' && -1 == (chld = __iosFindNode(node, idx))) {
            chld =  __iosAllocNode();
            __iosInitNode(chld, node, typ, dev, driverQId);
            __iosAddNode(chld, idx);
        }
        idx = chld;
    } while ( path[path_idx] != '\0');
    return;
}

void
USB_DelTree(const char *path)
{
    int idx = __devroot;
    int pidx = __devroot;
    int path_idx = 0;
    char node[IOS_DEV_NAME_MAX];
    int chld;
    do {
        path_idx = getNode(path, node, path_idx);
        if ( -1 == (chld = __iosFindNode(node, idx))) {
            printf("USB_DelTree: failed to find: %s\n", node);
            return;
        }
        pidx = idx;
        idx = chld;
        printf("idx = %d pidx = %d \n", idx, pidx);
    } while ( path[path_idx] != '\0');
    __iosDelNode(idx, pidx);
    return;
}

static IOSError 
__iosUSBTreeInit(void)
{ 
    IOSError ret = IOS_ERROR_OK;
     if ( __usbInitialized == 0 ) {
         printf("USB Core already initialized\n");
         ret = IOS_ERROR_INVALID;
         goto done;
     }
    __iosInitDevList();
    __iosAddRoot("/dev");
    USB_AddTree("/dev/usb", IOS_DEV_USBROOT, NULL, -1);
    USB_EmuTreeInit();
    __usbInitialized = 0;
//    dumpList();
//    dumpTree(__devroot);
done:
    return ret;
}

void
usb_core(u32 dummy)
{
    if ( IOS_ERROR_OK == __iosUSBTreeInit() )
        fprintf(stderr, "USB Core initialized...\n");
    IOS_ThreadExit(0);
}

static int 
findUSBDevice(int idx, u16 vid, u16 pid, char *buf, 
             int buflen, int *bufidx)
{
    int i;
    int ret = -1;
    if ( __devnodes[idx].typ == IOS_DEV_USB) {
        USB_emu_device_t *dev = (USB_emu_device_t *) __devnodes[idx].dev;
        if ((dev->idVendor == vid) && (dev->idProduct == pid)) {
            if ( buflen - *bufidx  < strlen(__devnodes[idx].name)) {
                printf("buffer too small\n");
            }
            else {
                strcat(buf, __devnodes[idx].name);
                strcat(buf, " ");
                ret = 0;
            }
        }
        return ret;
    }
    strcat(buf,__devnodes[idx].name);
    strcat(buf,"/");
    *bufidx += strlen(__devnodes[idx].name) + 1;
    for ( i = 0; i < IOS_DEV_CHLD_MAX; ++i) {
        if ( -1 != __devnodes[idx].chld[i]) {
            if ( 0 == findUSBDevice(__devnodes[idx].chld[i], vid, pid, buf, buflen, bufidx) )
                return 0;
        }
    }
    sprintf(buf,"/dev/usb/");
    *bufidx = 9;
    return -1;
}

IOSError
usbFindDevice(u16 vendorId,
        u16 productId, 
        char *buf, 
        int buflen,
        int *numDevs)
{
    int bufidx;
    bzero(buf, buflen);
    sprintf(buf,"/dev/");
    bufidx = 5;
    if ( 0 == findUSBDevice(1, vendorId, productId, buf, buflen, &bufidx))
        return IOS_ERROR_OK;
    else 
        return IOS_ERROR_USB_ERR;
}

static int 
findUSBIds(int idx, u16 vid, u16 pid, int *maj, int *min)
{
    int i;
    if ( __devnodes[idx].typ == IOS_DEV_USB) {
//        printf("findUSBIds: node %d type = USB device\n", idx);
        USB_emu_device_t *dev = (USB_emu_device_t *) __devnodes[idx].dev;
//        printf("findUSBIds: vendor 0x%02x product 0x%02x\n", dev->idVendor, dev->idProduct);
        if ((dev->idVendor == vid) && (dev->idProduct == pid)) {
            *maj = __devnodes[idx].hcdQId;
            *min = idx;
            return 0;
        }
        return -1;
    }
//    printf("findUSBIds: node %d type != USB device\n", idx);
    for ( i = 0; i < IOS_DEV_CHLD_MAX; ++i) {
        if ( -1 != __devnodes[idx].chld[i]) {
            if ( 0 == findUSBIds(__devnodes[idx].chld[i], vid, pid, maj, min))
                return 0;
        }
    }
    return -1;
}

IOSError 
usbFindDeviceIds(u16 vendorId,
           u16 productId,
           int *maj,
           int *min
        )
{
    if ( 0 == findUSBIds(1, vendorId, productId, maj, min))
        return IOS_ERROR_OK;
    else 
        return IOS_ERROR_USB_ERR;
}
