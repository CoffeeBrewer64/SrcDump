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
#include <sk.h>
#include <ng.h>
#include <sktypes.h>
#include <arm.h>
#include "emu_usb.h"
#include <skusbtypes.h>
#include <skusb.h>
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

SKDevice_t  __devnodes[SK_DEV_NODE_MAX]; /* Space for allowed device nodes */
int __devroot = -1;
static int __usbInitialized = -1;

static inline int
__skInitDevList(void)
{
    unsigned int i;
    unsigned int k;
    for ( i = SK_DEV_NODE_MAX; i != 0; --i ) { 
        __devnodes[i - 1].typ = SK_DEV_UNUSED;
        for ( k = SK_DEV_CHLD_MAX; k != 0; --k )
            __devnodes[i - 1].chld[k - 1] = -1;
    }
    return 0;
}

static SKError
__skCheckDevName(char *src)
{
    SKError ret = SK_ERROR_OK;
    int i  = 0;
    if ( src[i] == '/') ++i; /* skip initial / */
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

static SKError 
__skFreeNode(int idx, int pidx)
{
    int k;
    __devnodes[idx].typ = SK_DEV_UNUSED;
    for ( k = SK_DEV_CHLD_MAX; k != 0; --k )
        __devnodes[idx].chld[k - 1] = -1;
    for ( k = SK_DEV_CHLD_MAX; k != 0; --k ) {
        if ( idx ==  __devnodes[pidx].chld[k - 1])
            __devnodes[pidx].chld[k -1] = -1;
    }
    return SK_ERROR_OK;
}

static SKError 
__skInitNode( int i,
              char *name, 
              SKDevType typ,
              void *dev,
              SKMessageQueueId driverQId
            )
{
    int k;
    if ( SK_ERROR_INVALID == __skCheckDevName(name) )
        return SK_ERROR_INVALID;
    __devnodes[i].typ = typ;
    sk_strncpy(__devnodes[i].name, name, SK_DEV_NAME_MAX);
    __devnodes[i].dev = dev;
    __devnodes[i].driverQId = driverQId;
  for ( k = 0; k < SK_DEV_CHLD_MAX; ++k) 
      __devnodes[i].chld[k] = -1;
    return SK_ERROR_OK;
}

static SKError
__skAllocNode(void)
{
    int i, k;
    for (i = 0; i < SK_DEV_NODE_MAX; ++i ) {
        if ( SK_DEV_UNUSED != __devnodes[i].typ )
            continue;
        __devnodes[i].typ = SK_DEV_USED;
        __devnodes[i].hcdQId = -1;
        __devnodes[i].driverQId = -1;
//        sk_strncpy(__devnodes[i].name, name, SK_DEV_NAME_MAX);
//        __devnodes[i].dev = dev;
//        __devnodes[i].driverQId = driverQId;
        for ( k = SK_DEV_CHLD_MAX; k >= 0; --k )
            __devnodes[i].chld[k - 1] = -1; 
        return i;
    }
    return SK_ERROR_MAX;
}

/* Find node in tree of name 'node' , starting at node 'idx' */
static int 
__skFindNode(const char *node, int idx)
{
    int i;
    if ( 0 == sk_strcmp(__devnodes[idx].name, node))
        return idx;
    for ( i = 0; i < SK_DEV_CHLD_MAX; ++i ) {
        if ( -1 == __devnodes[idx].chld[i]) 
            continue;
        if ( 0 == sk_strcmp(__devnodes[__devnodes[idx].chld[i]].name, node) ) 
            return __devnodes[idx].chld[i];
    }
    return -1;
}


static int 
__skAddNode(int chld_idx, int parent_idx)
{
  int i;
  for ( i = 0; i < SK_DEV_CHLD_MAX; ++i ) {
        if ( -1 !=  __devnodes[parent_idx].chld[i]) /* used */
            continue; 
        __devnodes[parent_idx].chld[i] = chld_idx; 
        __devnodes[chld_idx].parent = parent_idx;
        if ( __devnodes[chld_idx].typ == SK_DEV_USB )
            __devnodes[chld_idx].hcdQId = __devnodes[parent_idx].hcdQId;
        else if (__devnodes[chld_idx].typ == SK_DEV_USBHC )
            __devnodes[chld_idx].hcdQId = __devnodes[chld_idx].driverQId;
        return 0;
  }
  /* full */
  return -1;
}

static int 
__skDelNode(int idx, int pidx)
{
  int i;
  for ( i = 0; i < SK_DEV_CHLD_MAX; ++ i) {
    if ( -1 == __devnodes[idx].chld[i] ) 
        continue;
    __skDelNode(__devnodes[idx].chld[i], idx);
  }
  printf("Deleting node index: %d\n", idx);
  __skFreeNode(idx, pidx);
  if ( __devroot == idx ) {
      __devroot = -1;
  }
  return 0;
}

static void
skutil_strcpyn(char *dstn, const char *src, int start, int end)
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
    skutil_strcpyn(node, path, start, end);
    return i;
}

void 
dumpList(void)
{
    int i;
    for (i = 0; i < SK_DEV_NODE_MAX; ++i ) {
        if ( SK_DEV_UNUSED != __devnodes[i].typ )
            printf("Node %d: %s\n", i, __devnodes[i].name);
    }
}

void
dumpNode( SKDevice_t node)
{
  int i;
  printf("--- Node: %s ---\n", node.name);
  if ( NULL != node.dev ) {
      USB_emu_device_t *dev = (USB_emu_device_t *) node.dev;
      printf("\t Vendor id: 0x%04x\n", dev->idVendor);
      printf("\t Product id: 0x%04x\n", dev->idProduct);
  }
  printf("\t Parent node id: %d\n", node.parent);
  printf("\t Driver queue id: %d\n", node.driverQId);
  printf("\t HCD queue id: %d\n", node.hcdQId);
  for ( i = 0; i < SK_DEV_CHLD_MAX; ++i) {
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
  for ( i = 0; i < SK_DEV_CHLD_MAX; ++i) {
      if ( -1 != __devnodes[idx].chld[i]) {
          dumpTree(__devnodes[idx].chld[i]);
      }
  }
  return;
}

void 
skDumpDevTree(void)
{
  dumpTree(__devroot);      
}

static void
__skAddRoot(const char *path)
{
    char node[SK_DEV_NAME_MAX];
    if ( -1 != __devroot )
        goto done;
    getNode(path, node, 0);
    __devroot =  __skAllocNode();
    __skInitNode(__devroot, node, SK_DEV_DUMMY, NULL, -1);
done:
    return;
}

void
USB_AddTree(const char *path, SKDevType typ, void *dev, SKMessageQueueId driverQId)
{
    int idx = __devroot;
    int path_idx = 0;
    char node[SK_DEV_NAME_MAX];
    int chld;
    path_idx = getNode(path, node, path_idx); /* root */
    if ( idx == -1 || ( 0 != sk_strcmp(node, __devnodes[idx].name)) ) {
        printf("Trying to add device: %s\n", path);
        printf("Root should always be: /%s not /%s\n", __devnodes[idx].name, node);
        return;
    }
    do {
        path_idx = getNode(path, node, path_idx);
        if ( node[0] != '\0' && -1 == (chld = __skFindNode(node, idx))) {
            chld =  __skAllocNode();
            __skInitNode(chld, node, typ, dev, driverQId);
            __skAddNode(chld, idx);
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
    char node[SK_DEV_NAME_MAX];
    int chld;
    do {
        path_idx = getNode(path, node, path_idx);
        if ( -1 == (chld = __skFindNode(node, idx))) {
            printf("USB_DelTree: failed to find: %s\n", node);
            return;
        }
        pidx = idx;
        idx = chld;
        printf("idx = %d pidx = %d \n", idx, pidx);
    } while ( path[path_idx] != '\0');
    __skDelNode(idx, pidx);
    return;
}

static SKError 
__skUSBTreeInit(void)
{ 
    SKError ret = SK_ERROR_OK;
     if ( __usbInitialized == 0 ) {
         printf("USB Core already initialized\n");
         ret = SK_ERROR_INVALID;
         goto done;
     }
    __skInitDevList();
    __skAddRoot("/dev");
    USB_AddTree("/dev/usb", SK_DEV_USBROOT, NULL, -1);
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
    if ( SK_ERROR_OK == __skUSBTreeInit() )
        fprintf(stderr, "USB Core initialized...\n");
    SK_ThreadExit(0);
}

static int 
findUSBDevice(int idx, u16 vid, u16 pid, char *buf, 
             int buflen, int *bufidx)
{
    int i;
    int ret = -1;
    if ( __devnodes[idx].typ == SK_DEV_USB) {
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
    for ( i = 0; i < SK_DEV_CHLD_MAX; ++i) {
        if ( -1 != __devnodes[idx].chld[i]) {
            if ( 0 == findUSBDevice(__devnodes[idx].chld[i], vid, pid, buf, buflen, bufidx) )
                return 0;
        }
    }
    sprintf(buf,"/dev/usb/");
    *bufidx = 9;
    return -1;
}

SKError
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
        return SK_ERROR_OK;
    else 
        return SK_ERROR_USB_ERR;
}

static int 
findUSBIds(int idx, u16 vid, u16 pid, int *maj, int *min)
{
    int i;
    if ( __devnodes[idx].typ == SK_DEV_USB) {
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
    for ( i = 0; i < SK_DEV_CHLD_MAX; ++i) {
        if ( -1 != __devnodes[idx].chld[i]) {
            if ( 0 == findUSBIds(__devnodes[idx].chld[i], vid, pid, maj, min))
                return 0;
        }
    }
    return -1;
}

SKError 
usbFindDeviceIds(u16 vendorId,
           u16 productId,
           int *maj,
           int *min
        )
{
    if ( 0 == findUSBIds(1, vendorId, productId, maj, min))
        return SK_ERROR_OK;
    else 
        return SK_ERROR_USB_ERR;
}
