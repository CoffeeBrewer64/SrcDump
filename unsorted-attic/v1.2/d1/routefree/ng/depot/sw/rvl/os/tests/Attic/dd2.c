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

#include "iop.h"
#include <rvldv.h>

/* Sample Device Driver
 *
 * int ddriver(void) is main driver;
 *   main launches the driver in its independent thread,
 *   then sends a stream of requests to the driver.
 *
 *   All tests will flag an error and exit immediately
 *   if unexpected error occurs
 */

#define STACK_SIZE 1024
const u8 _initStack[STACK_SIZE * 4];
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = 9;

#define APP_LOG(...) printf("APP: " __VA_ARGS__)
#define APP_LOG_CONT(...) printf(__VA_ARGS__)

typedef struct {
    u8 inUse;
    u8 dev;
    u16 pos;
} DDFileDescriptor;

#define DD_NUM_DESCRIPTORS 4
static DDFileDescriptor desc[DD_NUM_DESCRIPTORS];
    
#define DD_DEV0 "/dev/byte0"
#define DD_DEV1 "/dev/byte1"
#define DD_DEV2 "/dev/byte2"
u8 dev2[256];

#define DD_LOG(...) printf("DD: " __VA_ARGS__)
#define DD_ERROR(msg) printf("DD: Error: %s failed\n", msg)

u8 ddStack[STACK_SIZE] __attribute__ ((aligned(0x20)));
int ddriver(void);
IOSThreadId driver;


void error(char *str)
{
    APP_LOG("Error: %s\n", str);
    exit(-1);
}

void checkBuffer(u8 *buf, u32 len, u8 start, u32 inc)
{
    u32 valid = 1;
    APP_LOG("");
    while (len--) {
        if (*buf != start) valid = 0;
        start += inc;
        APP_LOG_CONT("%02x ", *buf++);
    }
    APP_LOG_CONT("\n\n");
    if (!valid) error("checkBuffer");
}

int main(void)
{
    APP_LOG("Device driver test application; NOTE: all unexpected errors will fail immediately\n");

    int i;
    IOSFd fd0, fd1, fd2;
    IOSError rv;
    u8 buffer[10];
    u32 *p = (u32 *)buffer;
    IOSIoVector vector[3];

    APP_LOG("Launch DD\n");
    driver = IOS_CreateThread((IOSEntryProc)ddriver,
		     NULL,
		     ddStack+STACK_SIZE,
		     STACK_SIZE,
		     IOS_GetThreadPriority(0) + 4,
		     IOS_THREAD_CREATE_DETACHED);
    if(driver < 0) {
	APP_LOG("Device Driver uninitialized; exiting ...");
	exit(-1);
    }
    else {
	IOS_StartThread(driver);
	IOS_YieldThread();
    }
    
    memset(buffer, 0xff, sizeof(buffer));

    APP_LOG("Before IOS_Open(\"/dev/foo\")\n");
    fd0 = IOS_Open("/dev/foo", 0);
    APP_LOG("After IOS_Open(): %d\n\n", fd0);
    if (fd0 != IOS_ERROR_NOEXISTS) error("open");

    APP_LOG("Before IOS_Open(\"/dev/bytefoo\")\n");
    fd0 = IOS_Open("/dev/bytefoo", 0);
    APP_LOG("After IOS_Open(): %d\n\n", fd0);
    if (fd0 != IOS_ERROR_NOEXISTS) error("open");

    APP_LOG("Before IOS_Open(\"/dev/byte0\")\n");
    fd0 = IOS_Open("/dev/byte0", 0);
    APP_LOG("After IOS_Open(): %d\n\n", fd0);
    if (fd0 != 0) error("open");

    APP_LOG("Before IOS_Open(\"/dev/byte1\")\n");
    fd1 = IOS_Open("/dev/byte1", 0);
    APP_LOG("After IOS_Open(): %d\n\n", fd1);
    if (fd1 != 1) error("open");

    APP_LOG("Before IOS_Open(\"/dev/byte2\")\n");
    fd2 = IOS_Open("/dev/byte2", 0);
    APP_LOG("After IOS_Open(): %d\n\n", fd2);
    if (fd2 != 2) error("open");

    APP_LOG("Before 1st IOS_Read()\n");
    rv = IOS_Read(fd0, buffer, sizeof(buffer));
    APP_LOG("After 1st IOS_Read(): %d\n", rv);
    checkBuffer(buffer, sizeof(buffer), 0, 1);
    if (rv != sizeof(buffer)) error("read");

    APP_LOG("Before 2nd IOS_Read()\n");
    rv = IOS_Read(fd0, buffer, sizeof(buffer));
    APP_LOG("After 2nd IOS_Read(): %d\n", rv);
    checkBuffer(buffer, sizeof(buffer), sizeof(buffer), 1);
    if (rv != sizeof(buffer)) error("read");

    APP_LOG("Before IOS_Seek()\n");
    rv = IOS_Seek(fd0, 0x80, IOS_SEEK_SET);
    APP_LOG("After IOS_Seek(): %d\n\n", rv);
    if (rv != 0x80) error("seek");

    APP_LOG("Before seek set IOS_Read()\n");
    rv = IOS_Read(fd0, buffer, sizeof(buffer));
    APP_LOG("After seek set IOS_Read(): %d\n", rv);
    checkBuffer(buffer, sizeof(buffer), 0x80, 1);
    if (rv != sizeof(buffer)) error("read");

    APP_LOG("Before IOS_Seek()\n");
    rv = IOS_Seek(fd0, 0x10, IOS_SEEK_CURRENT);
    APP_LOG("After IOS_Seek(): %d\n\n", rv);
    if (rv != 0x9a) error("seek");

    APP_LOG("Before seek current IOS_Read()\n");
    rv = IOS_Read(fd0, buffer, sizeof(buffer));
    APP_LOG("After seek current IOS_Read(): %d\n", rv);
    checkBuffer(buffer, sizeof(buffer), 0x80+0x10+sizeof(buffer), 1);
    if (rv != sizeof(buffer)) error("read");

    APP_LOG("Before IOS_Seek()\n");
    rv = IOS_Seek(fd0, -8, IOS_SEEK_END);
    APP_LOG("After IOS_Seek(): %d\n\n", rv);
    if (rv != (255-8)) error("seek");

    APP_LOG("Before seek end IOS_Read()\n");
    rv = IOS_Read(fd0, buffer, sizeof(buffer));
    APP_LOG("After seek end IOS_Read(): %d\n", rv);
    checkBuffer(buffer, sizeof(buffer), 255-8, 1);
    if (rv != sizeof(buffer)) error("read");

    IOSMessageQueueId mq;
    IOSMessage array[2];
    IOSMessage m;
    IOSResourceRequest reply[2];

    mq = IOS_CreateMessageQueue(array, sizeof(array)/sizeof(array[0]));
    APP_LOG("Before async IOS_Read()\n");
    rv = IOS_ReadAsync(fd0, buffer, sizeof(buffer), mq, &reply[0]);
    if (rv != IOS_ERROR_OK) error("read async");
    APP_LOG("After async IOS_Read(): %d\n", rv);
    APP_LOG("Before async IOS_Read() recv\n");
    rv = IOS_ReceiveMessage(mq, &m, IOS_MESSAGE_BLOCK);
    APP_LOG("After async IOS_Read() recv: %d [%08x == %08x]\n", rv, m, &reply[0]);
    APP_LOG("cmd = %d, status = %d\n", reply[0].cmd, reply[0].status);
    checkBuffer(buffer, sizeof(buffer), (u8)(255-8+sizeof(buffer)), 1);
    if (reply[0].status != sizeof(buffer)) error("read async");

    APP_LOG("Before byte1 IOS_Read()\n");
    rv = IOS_Read(fd1, buffer, sizeof(buffer));
    APP_LOG("After byte1 IOS_Read(): %d\n", rv);
    checkBuffer(buffer, sizeof(buffer), 255, -1);
    if (rv != sizeof(buffer)) error("read");

    APP_LOG("Before byte2 IOS_Read()\n");
    rv = IOS_Read(fd2, buffer, sizeof(buffer));
    APP_LOG("After byte2 IOS_Read(): %d\n", rv);
    checkBuffer(buffer, sizeof(buffer), 0, 0);
    if (rv != sizeof(buffer)) error("read");

    APP_LOG("Before IOS_Write()\n");
    rv = IOS_Write(fd0, buffer, sizeof(buffer));
    APP_LOG("After IOS_Write(): %d\n\n", rv);
    if (rv != IOS_ERROR_INVALID) error("write");

    APP_LOG("Before IOS_Seek()\n");
    rv = IOS_Seek(fd2, 0, IOS_SEEK_SET);
    APP_LOG("After IOS_Seek(): %d\n\n", rv);
    if (rv != 0) error("seek");

    APP_LOG("Before IOS_Write()\n");
    for (i = 0; i < sizeof(buffer); ++i) buffer[i] = i << 1;
    rv = IOS_Write(fd2, buffer, sizeof(buffer));
    APP_LOG("After IOS_Write(): %d\n\n", rv);
    if (rv != sizeof(buffer)) error("write");

    APP_LOG("Before byte2 IOS_Read()\n");
    rv = IOS_Read(fd2, buffer, sizeof(buffer));
    APP_LOG("After byte2 IOS_Read(): %d\n", rv);
    checkBuffer(buffer, sizeof(buffer), 0, 0);
    if (rv != sizeof(buffer)) error("read");

    APP_LOG("Before IOS_Seek()\n");
    rv = IOS_Seek(fd2, 0, IOS_SEEK_SET);
    APP_LOG("After IOS_Seek(): %d\n\n", rv);
    if (rv != 0) error("seek");

    APP_LOG("Before byte2 IOS_Read()\n");
    rv = IOS_Read(fd2, buffer, sizeof(buffer));
    APP_LOG("After byte2 IOS_Read(): %d\n", rv);
    checkBuffer(buffer, sizeof(buffer), 0, 2);
    if (rv != sizeof(buffer)) error("read");

    APP_LOG("Before IOS_Ioctl(0)\n");
    p[0] = 24; p[1] = 10; p[2] = 0;
    rv = IOS_Ioctl(fd0, 0, p, 2*sizeof(p[0]), p+2, sizeof(p[0]));
    APP_LOG("After IOS_Ioctl(0): %d [%d]\n\n", rv, p[2]);
    if (rv != IOS_ERROR_OK || p[2] != 34) error("ioctl");

    APP_LOG("Before IOS_Ioctl(1)\n");
    p[0] = 24; p[1] = 10; p[2] = 0;
    rv = IOS_Ioctl(fd0, 1, p, 2*sizeof(p[0]), p+2, sizeof(p[0]));
    APP_LOG("After IOS_Ioctl(1): %d [%d]\n\n", rv, p[2]);
    if (rv != IOS_ERROR_OK || p[2] != 14) error("ioctl");

    APP_LOG("Before IOS_Ioctl(2)\n");
    p[0] = 24; p[1] = 10; p[2] = 0;
    rv = IOS_Ioctl(fd0, 2, p, 2*sizeof(p[0]), p+2, sizeof(p[0]));
    APP_LOG("After IOS_Ioctl(2): %d [%d]\n\n", rv, p[2]);
    if (rv != IOS_ERROR_INVALID) error("ioctl");

    APP_LOG("Before IOS_Ioctlv(0)\n");
    vector[0].base = (u8 *)p;
    vector[0].length = sizeof(u32);
    vector[1].base = (u8 *)(p+1);
    vector[1].length = sizeof(u32);
    vector[2].base = (u8 *)(p+2);
    vector[2].length = sizeof(u32);
    p[0] = 24; p[1] = 10; p[2] = 0;
    rv = IOS_Ioctlv(fd0, 0, 2, 1, vector);
    APP_LOG("After IOS_Ioctlv(0): %d [%d]\n\n", rv, p[2]);
    if (rv != IOS_ERROR_OK || p[2] != 34) error("ioctl");

    APP_LOG("Before IOS_Ioctlv(1)\n");
    p[0] = 24; p[1] = 10; p[2] = 0;
    rv = IOS_Ioctlv(fd0, 1, 2, 1, vector);
    APP_LOG("After IOS_Ioctlv(1): %d [%d]\n\n", rv, p[2]);
    if (rv != IOS_ERROR_OK || p[2] != 14) error("ioctl");

    APP_LOG("Before IOS_Ioctlv(2)\n");
    p[0] = 24; p[1] = 10; p[2] = 0;
    rv = IOS_Ioctlv(fd0, 2, 2, 1, vector);
    APP_LOG("After IOS_Ioctlv(2): %d [%d]\n\n", rv, p[2]);
    if (rv != IOS_ERROR_INVALID) error("ioctl");

    APP_LOG("Before async IOS_Write()\n");
    rv = IOS_WriteAsync(fd2, buffer, sizeof(buffer), mq, &reply[0]);
    APP_LOG("After async IOS_Write(): %d\n", rv);
    if (rv != IOS_ERROR_OK) error("write async");

    APP_LOG("Before async IOS_Read()\n");
    rv = IOS_ReadAsync(fd0, buffer, sizeof(buffer), mq, &reply[1]);
    if (rv != IOS_ERROR_OK) error("read async");
    APP_LOG("After async IOS_Read(): %d\n", rv);

    APP_LOG("Before async recv\n");
    rv = IOS_ReceiveMessage(mq, &m, IOS_MESSAGE_BLOCK);
    APP_LOG("After async write recv: %d [%08x == %08x]\n", rv, m, &reply[0]);
    APP_LOG("cmd = %d, status = %d\n", reply[0].cmd, reply[0].status);
    if (reply[0].status != sizeof(buffer)) error("write async");
    APP_LOG("Before async recv\n");
    rv = IOS_ReceiveMessage(mq, &m, IOS_MESSAGE_BLOCK);
    APP_LOG("After async read recv: %d [%08x == %08x]\n", rv, m, &reply[1]);
    if (reply[1].status != sizeof(buffer)) error("read async");

    APP_LOG("Try multiple async reads\n");
    for (i = 0; i < 10; ++i) {
        rv = IOS_ReadAsync(fd0, buffer, sizeof(buffer), mq, &reply[1]);
        if (rv != IOS_ERROR_OK) error("read async");
        rv = IOS_ReceiveMessage(mq, &m, IOS_MESSAGE_BLOCK);
        if (rv != IOS_ERROR_OK) error("read async");
    }

    APP_LOG("Before IOS_Close()\n");
    rv = IOS_Close(fd0);
    APP_LOG("After IOS_Close(): %d\n\n", rv);
    if (rv != IOS_ERROR_OK) error("close");

    APP_LOG("Before IOS_Close()\n");
    rv = IOS_Close(fd1);
    APP_LOG("After IOS_Close(): %d\n\n", rv);
    if (rv != IOS_ERROR_OK) error("close");

    APP_LOG("Before re-IOS_Close()\n");
    rv = IOS_Close(fd1);
    APP_LOG("After re-IOS_Close(): %d\n\n", rv);
    if (rv != IOS_ERROR_INVALID) error("close");

    APP_LOG("Before IOS_Close()\n");
    rv = IOS_Close(fd2);
    APP_LOG("After IOS_Close(): %d\n\n", rv);
    if (rv != IOS_ERROR_OK) error("close");

    APP_LOG("Before closed IOS_Read()\n");
    rv = IOS_Read(fd0, buffer, sizeof(buffer));
    APP_LOG("After closed IOS_Read(): %d\n", rv);
    if (rv != IOS_ERROR_INVALID) error("read");

    APP_LOG("\nTest Passed\n");
    exit(0);
    return 0;
}



static void
sleep(int t)
{
    IOSMessageQueueId mq;
    IOSMessage array;
    IOSMessage m;
    IOSTimerId t1;
    
    mq = IOS_CreateMessageQueue(&array, 1);
    t1 = IOS_CreateTimer(t, 0, mq, 0);
    IOS_ReceiveMessage(mq, &m, IOS_MESSAGE_BLOCK);
    IOS_DestroyTimer(t1);
}

static u8 deathStack[256];
static void
death(u32 arg)
{
    sleep(100000);
    exit(0);
}

static void
die(void)
{
    IOSThreadId id = IOS_CreateThread(death, 0, deathStack+sizeof(deathStack), sizeof(deathStack), 1, IOS_THREAD_CREATE_DETACHED);
    IOS_StartThread(id);
}


static IOSError
ddOpen(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    u32 dev = 0;
    IOSResourceOpen *args = &req->args.open;
    int i;

    DD_LOG("in ddOpen: '%s', u=%d, g=%d\n", args->path, args->uid, args->gid);

    if (!strncmp(args->path, DD_DEV0, sizeof(DD_DEV0)-1)) {
        dev = 0;
    } else if (!strncmp(args->path, DD_DEV1, sizeof(DD_DEV1)-1)) {
        dev = 1;
    } else if (!strncmp(args->path, DD_DEV2, sizeof(DD_DEV2)-1)) {
        dev = 2;
    } else {
        rv = IOS_ERROR_NOEXISTS;
        goto out;
    }

    for (i = 0; i < DD_NUM_DESCRIPTORS; ++i) {
        if (!desc[i].inUse) {
            break;
        }
    }

    if (i == DD_NUM_DESCRIPTORS) {
        rv = IOS_ERROR_MAX;
        goto out;
    }   

    desc[i].inUse = 1;
    desc[i].pos = 0;
    desc[i].dev = dev;
    rv = (IOSError) &desc[i];

    DD_LOG("open: new context handle %08x\n", req->handle);

out:
    return rv;
}

static IOSError
ddClose(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    DDFileDescriptor *d = (DDFileDescriptor *) req->handle;

    DD_LOG("in ddClose\n");

    d->inUse = 0;

    return rv;
}

static IOSError
ddRead(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    DDFileDescriptor *d = (DDFileDescriptor *) req->handle;

    DD_LOG("in ddRead\n");

    if (!d->inUse) {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    u8 toggle = d->dev ? 0xff : 0x0;
    u32 len = req->args.read.outLen;
    u8 *p = req->args.read.outPtr;

    while (len) {
        *p++ = d->dev == 2 ? dev2[d->pos++] : ((d->pos++ & 0xff) ^ toggle);
        --len;
    }
    rv = req->args.read.outLen;

out:
    return rv;
}

static IOSError
ddWrite(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    DDFileDescriptor *d = (DDFileDescriptor *) req->handle;

    DD_LOG("in ddWrite\n");

    if (!d->inUse || d->dev != 2) {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    sleep(100000);

    u32 len = req->args.write.inLen;
    u8 *p = req->args.write.inPtr;

    while (len) {
        dev2[d->pos++] = *p++;
        --len;
    }
    rv = req->args.write.inLen;

out:
    return rv;
}

static IOSError
ddSeek(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    DDFileDescriptor *d = (DDFileDescriptor *) req->handle;
    IOSResourceSeek *args = (IOSResourceSeek *)&req->args.seek;

    if (!d->inUse) {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    switch(args->whence) {
    case IOS_SEEK_SET:
        rv = d->pos = args->offset & 0xff;
        break;
    case IOS_SEEK_CURRENT:
        rv = d->pos = (d->pos + args->offset) & 0xff;
        break;
    case IOS_SEEK_END:
        rv = d->pos = (255 + args->offset) & 0xff;
        break;
    default:
        rv = IOS_ERROR_INVALID;
        goto out;
    }

out:
    return rv;
}

static IOSError
ddIoctl(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    DDFileDescriptor *d = (DDFileDescriptor *) req->handle;
    IOSResourceIoctl *args = (IOSResourceIoctl *)&req->args.ioctl;

    DD_LOG("in ddIoctl: %d\n", args->cmd);

    if (!d->inUse) {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    u32 *in = (u32 *)args->inPtr;
    u32 *out = (u32 *)args->outPtr;

    if (args->inLen != 2*sizeof(u32) || args->outLen != sizeof(u32)) {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    switch(args->cmd) {
    case 0: /* Add */
        out[0] = in[0] + in[1];
        break;
    case 1: /* Subtract */
        out[0] = in[0] - in[1];
        break;
    case 3:
        die();
        break;
    default:
        rv = IOS_ERROR_INVALID;
        goto out;
    }

out:
    return rv;
}

static IOSError
ddIoctlv(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    DDFileDescriptor *d = (DDFileDescriptor *) req->handle;
    IOSResourceIoctlv *args = (IOSResourceIoctlv *)&req->args.ioctlv;

    if (!d->inUse) {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    if (args->readCount != 2 || args->writeCount != 1) {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    if (args->vector[0].length != sizeof(u32) ||
        args->vector[1].length != sizeof(u32) ||
        args->vector[2].length != sizeof(u32)) {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    u32 *a = (u32 *)args->vector[0].base;
    u32 *b = (u32 *)args->vector[1].base;
    u32 *c = (u32 *)args->vector[2].base;

    switch(args->cmd) {
    case 0: /* Add */
        *c = *a + *b;
        break;
    case 1: /* Subtract */
        *c = *a - *b;
        break;
    default:
        rv = IOS_ERROR_INVALID;
        goto out;
    }

out:
    return rv;
}

int ddriver(void)
{
    IOSError rv;
    IOSMessageQueueId mq;
    IOSMessage msgArray[3];
    IOSMessage msg;
    
    DD_LOG("Simple device driver example\n");

    /* Create a message queue */
    DD_LOG("Create message queue\n");
    if ((mq = IOS_CreateMessageQueue(msgArray, sizeof(msgArray)/sizeof(msgArray[0]))) < 0) {
        rv = mq;
        DD_ERROR("IOS_CreateMessageQueue");
        goto out;
    }

    /* Register the message queue with the kernel */
    if ((rv = IOS_RegisterResourceManager("/dev/byte", mq)) != IOS_ERROR_OK) {
        DD_ERROR("IOS_RegisterResourceManager");
        goto out;
    }
        
    /* Main dispatch loop */
    while (1) {
        /* Receive a command */
        DD_LOG("Waiting for command\n");
        if ((rv = IOS_ReceiveMessage(mq, &msg, IOS_MESSAGE_BLOCK)) != IOS_ERROR_OK) {
            DD_ERROR("IOS_ReceiveMessage");
            goto out;
        }
        DD_LOG("Received resource request: %08x\n", msg);

        /* Dispatch command */
        IOSResourceRequest *req = (IOSResourceRequest *) msg;
        switch (req->cmd) {
        case IOS_OPEN:
            DD_LOG("  IOS_OPEN\n");
            rv = ddOpen(req);
            break;
        case IOS_CLOSE:
            DD_LOG("  IOS_CLOSE\n");
            rv = ddClose(req);
            break;
        case IOS_READ:
            DD_LOG("  IOS_READ\n");
            rv = ddRead(req);
            break;
        case IOS_WRITE:
            DD_LOG("  IOS_WRITE\n");
            rv = ddWrite(req);
            break;
        case IOS_SEEK:
            DD_LOG("  IOS_SEEK\n");
            rv = ddSeek(req);
            break;
        case IOS_IOCTL:
            DD_LOG("  IOS_IOCTL\n");
            rv = ddIoctl(req);
            break;
        case IOS_IOCTLV:
            DD_LOG("  IOS_IOCTLV\n");
            rv = ddIoctlv(req);
            break;
        default:
            DD_LOG("  Unsupported\n");
            rv = IOS_ERROR_INVALID;
            break;
        }
        IOS_ResourceReply(req, rv);
        DD_LOG("Returning = %d\n", rv);
    }

out:
    return 0;
}
