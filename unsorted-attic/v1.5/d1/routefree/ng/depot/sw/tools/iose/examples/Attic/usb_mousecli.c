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

/* Tests resource manager interface
 * There are 2 threads:
 * Driver:
 *        -  Registers a mouse "driver".
 *        -  Sits in a loop waiting for requests via resource manager API
 *        -  When it gets a request, it prints its contents. In a real
 *           driver, work would get done here.
 * Client:
 *       - Makes IOS_Open, IOS_Read, IOS_Write, IOS_Ioctl, IOS_Close calls to
 *         demonstrate talking to a driver via the resource manager
 *         API.
 */
#include <stdio.h>   /* for printf */

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <iosusb.h>
#include <iosusbtypes.h>
#include <iosresource.h>


#define LOGITECH_VENDOR_ID 0x046d
#define LOGITECH_OPTICAL_MOUSE 0xc016
#define LOGITECH_ACER_MOUSE 0xc001

/* Parameters for message queue used to register driver. If there were 
 * applications that used this driver, they would talk to it via this queue.
 */
#define MSGQ_SIZE 8
#define PID_MASK 0xFFFFFFFF

#define STACK_SIZE 16*1024

static void 
client_func(u32 devId)
{
  IOSCid fd;
  s32 count;
  char buf[8] = "0123456";
  fd = IOS_Open(devId, 0);
  count = IOS_Write(fd, buf, 8);
  printf("client: wrote %d bytes\n", count);
  count = IOS_Read(fd, buf, 7);
  buf[7] = '\0';
  printf("client: read %s\n", buf);
  printf("client: will wait for 10s using before issuing ioctl req...\n");
  printf("client: hit <enter> to drop back to shell...\n");
  IOS_MilliSleep(10000);
  printf("client: calling dummy ioctl: cmd = 1, inputBytes = 2, outputBytes = 3\n");
  IOS_Ioctl(fd, 1, NULL, 2, NULL, 3);
  IOS_Close(fd);
  IOS_ThreadExit(0);
}

static void
create_client(u32 devId)
{
  u32 *progStack = (void *) IOS_Alloc(STACK_SIZE/IOS_DDR_PAGE_SIZE);
  if ( NULL == progStack ) {
    printf("client: IOS_Alloc failed \n");
    return;
  }
  u32 id = IOS_CreateThread(client_func, &devId, progStack, STACK_SIZE, IOS_GetThreadPriority(0));
  IOS_StartThread(id);
  return;
}

static void
find_supported_mouse(int *devId)
{
    if ( IOS_ERROR_OK == IUSB_FindDeviceIds(LOGITECH_VENDOR_ID, LOGITECH_OPTICAL_MOUSE, devId)) {
        printf("Driver: found USB mouse: (id: %d)\n", *devId);
    }
    else if ( IOS_ERROR_OK == IUSB_FindDeviceIds(LOGITECH_VENDOR_ID, LOGITECH_ACER_MOUSE, devId)) {
        printf("Driver: found USB mouse (id: %d\n)", *devId);
    }
    else {
        printf("Driver: Device (vendor: 0x%04x product: 0x%04x or 0x%04x) not found\n",
                LOGITECH_VENDOR_ID, LOGITECH_OPTICAL_MOUSE, LOGITECH_ACER_MOUSE);
        printf("Driver: No suitable mouse was found. Exiting...\n");
        IOS_ThreadExit(0);
    }
}

static void
handleOpen(IOSRmReq *req, s32 *reply)
{
    printf("Driver got request: OPEN\n");
    printf("Driver: fd for request = %d\n", req->fd);
    *reply = req->fd;
    /* no payload for open */
    return;
}

static void
handleClose(IOSRmReq *req, s32 *reply)
{
    printf("Driver got request: CLOSE\n");
    printf("Driver: fd for request = %d\n", req->fd);
    *reply = IOS_ERROR_OK;
    /* no payload for close */
    return;
}

static void
handleRead(IOSRmReq *req, s32 *reply)
{
    int i;
    char *buf;
    IOSReadWriteMsg *msg;
    printf("Driver got request: READ\n");
    *reply = -1;
    if ( NULL == req->req )
        printf("Driver: invalid read message: NULL\n");
    else {
        msg = (IOSReadWriteMsg *) req->req;
        buf = (char *) msg->buf;
        printf("Driver: read request buffer size = %d\n", msg->bufLen);
        if ( NULL == buf) {
            printf("Driver: invalid read buffer: NULL\n");
        }
        else {
            printf("Driver: will fill read buffer with 'a'\n");
            for ( i = 0; i < msg->bufLen; ++i ) 
                buf[i] = 'a';
            *reply = msg->bufLen;
        }
    }
    return;
}

static void
handleWrite(IOSRmReq *req, s32 *reply)
{
    int i;
    char *buf;
    IOSReadWriteMsg *msg;
    printf("Driver got request: WRITE\n");
    *reply = -1;
    if ( NULL == req->req )
        printf("Driver: invalid write message: NULL\n");
    else {
        msg = (IOSReadWriteMsg *) req->req;
        buf = (char *) msg->buf;
        printf("Driver: got write request buffer size = %d\n", msg->bufLen);
        if ( NULL == buf) {
            printf("Driver: invalid write buffer: NULL\n");
        }
        else {
            buf = (char *)msg->buf;
            printf("Driver: write request buffer contents: ");
            for ( i = 0; i < msg->bufLen; ++i )
                printf("%c   ", buf[i]);
            printf("\n");
            *reply = msg->bufLen;
        }
    }
    return;
}

static void
handleIoctl(IOSRmReq *req, s32 *reply)
{
    IOSIoctlMsg *msg;
    printf("Driver got request: IOCTL\n");
    *reply = IOS_ERROR_INVALID;
    if ( NULL == req->req )
        printf("Driver: invalid ioctl message: NULL\n");
    else {
        msg = (IOSIoctlMsg *) req->req;
        printf("Driver: ioctl contents: \n");
        printf("Driver: ioctl cmd = %d\n", msg->cmd);
        printf("Driver: ioctl inputBytes = %d\n", msg->inputBytes);
        printf("Driver: ioctl outputBytes = %d\n", msg->outputBytes);
        *reply = IOS_ERROR_OK;
    }
    return;
}

static void
handleSeek(IOSRmReq *req, s32 *reply)
{
    printf("Driver got request: SEEK\n");
    return;
}

static void
handleStat(IOSRmReq *req, s32 *reply)
{
    printf("Driver got request: STAT\n");
    return;
}

int
usb_mousecli()
{   
    IOSCid devId;
    IOSMessageQueueId qid;
    IOSMessage msgQ[MSGQ_SIZE];
    IOSRmReq *req;

    printf("*** Sample USB \"mouse\" driver with dummy client ***\n");
    printf("Currently tested with Logitech optical usb mouse & Logitech USB Mouse\n");

    /* Find a supported mouse or exit */
    find_supported_mouse(&devId);

    /* Create a message queue that clients use to communicate with this
     * driver
     */
    if ( (qid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK )) < 0 ) {
        printf("Creating message queue failed\n");
        IOS_ThreadExit(0);
    }
    /* Register device */
    if ( IOS_ERROR_OK != IUSB_RegisterResourceManager(devId, qid) ) {
        printf("Registering mouse driver failed. Exiting...\n");
        IOS_ThreadExit(0);
    }
    else
        printf("Mouse driver registered successfully...\n");

    /* Create a dummy client thread that will send requests to this
     * driver using the Resource Manager API.
     */
    create_client(devId);

    /* Sit in a loop processing requests */
    while(1) {
        s32 reply = 0;
        printf("*** Mouse driver waiting for requests...\n");
        IOS_ReceiveMessage(qid, (IOSMessage *)&req, IOS_MESSAGE_BLOCK);
        switch(req->type) {
            case IOS_OPEN:
                handleOpen(req, &reply);
                break;
            case IOS_CLOSE:
                handleClose(req, &reply);
                break;
            case IOS_READ:
                handleRead(req, &reply);
                break;
            case IOS_WRITE:
                handleWrite(req, &reply);
                break;
            case IOS_IOCTL:
                handleIoctl(req, &reply);
                break;
            case IOS_SEEK:
                handleSeek(req, &reply);
                break;
            case IOS_STAT:
                handleStat(req, &reply);
                break;
            default:
                printf("Driver got request: UNKNOWN\n");
        }
        /* Send reply to waiting caller */
        if ( IOS_ERROR_OK != 
                IOS_SendMessage(req->replyQId, (IOSMessage)&reply, IOS_MESSAGE_NOBLOCK)){
            printf("Driver: sending reply to request failed\n");
        }
        IOS_MilliSleep(10); /* 100 scans a sec */
    }
    /* Unregister device. Destroys message queue for us. */
    if ( IOS_ERROR_OK != IUSB_UnregisterResourceManager(devId) ) {
        printf("Un-registering mouse driver failed. Exiting...\n");
        IOS_ThreadExit(0);
    }
    return IOS_ThreadExit(0);
}
