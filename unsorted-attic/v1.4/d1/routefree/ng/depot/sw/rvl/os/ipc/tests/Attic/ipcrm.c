/*
 *               Copyright (C) 2006, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

/* Sample resource manager. */
#include <ios.h>
#include "ioslibc.h"

#define STACK_SIZE 1024
const u8 _initStack[STACK_SIZE];
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = 10;

typedef struct 
{
    u8 inUse;
    u8 dev;
    u16 pos;
} DDFileDescriptor;

#define DD_NUM_DESCRIPTORS 4
static DDFileDescriptor desc[DD_NUM_DESCRIPTORS];
    
#define IPC_DEV0 "/dev/ipc0"
#define IPC_DEV1 "/dev/ipc1"

#ifdef LOG_FL
#   define RM_LOG(...) printf("RM: " __VA_ARGS__)
#   define RM_ERROR(msg, rv) printf("RM: Error: %s failed: %d\n", msg, rv)
#else
#   define RM_LOG(...)
#   define RM_ERROR(msg, rv)
#endif

#define TEST_BUFF_SIZE 20

static
u8 buf[2][TEST_BUFF_SIZE];
        
static IOSError
ipcOpen(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    u32 dev = 0;
    IOSResourceOpen *args;
    int i;

    RM_LOG("in ipcOpen\n");
    if (!req)
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }
    args = &req->args.open;
    RM_LOG("in ipcOpen: '%s'\n", args->path);

    if (!strncmp(args->path, IPC_DEV0, sizeof(IPC_DEV0)-1)) 
    {
        dev = 0;
    } 
    else 
    if (!strncmp(args->path, IPC_DEV1, sizeof(IPC_DEV1)-1)) 
    {
        dev = 1;
    } 
    else 
    {
        rv = IOS_ERROR_NOEXISTS;
        goto out;
    }

    for (i = 0; i < DD_NUM_DESCRIPTORS; ++i) 
    {
        if (!desc[i].inUse) 
        {
            break;
        }
    }

    if (i == DD_NUM_DESCRIPTORS) 
    {
        rv = IOS_ERROR_MAX;
        goto out;
    }   

    desc[i].inUse = 1;
    desc[i].pos = 0;
    desc[i].dev = dev;
    rv = (IOSError) &desc[i];
    RM_LOG("open: new context %d dev: %u handle: %08x\n", i, dev, rv);

out:
    return rv;
}

static IOSError
ipcClose(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    DDFileDescriptor *d;

    RM_LOG("in ipcClose\n");
    if (!req)
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }
    d = (DDFileDescriptor *) req->handle;

    if (!d->inUse)
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    d->inUse = 0;
out:
    return rv;
}

static IOSError
ipcRead(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    DDFileDescriptor *d;

    RM_LOG("in ipcRead\n");
    if (!req)
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }
    d = (DDFileDescriptor *) req->handle;

    if (!d->inUse) 
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    u32 _len = sizeof(buf[0]) / sizeof(buf[0][0]);
    u32 len = (req->args.read.outLen > _len) ? _len : req->args.read.outLen;

    memcpy(req->args.read.outPtr, &buf[d->dev], len);
    rv = len;
out:
    return rv;
}

static IOSError
ipcWrite(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    DDFileDescriptor *d;

    RM_LOG("in ipcWrite\n");
    if (!req)
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }
    d = (DDFileDescriptor *) req->handle;

    if (!d->inUse)
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    u32 _len = sizeof(buf[0]) / sizeof(buf[0][0]);
    u32 len = (req->args.write.inLen > _len) ? _len : req->args.write.inLen;

    memcpy(&buf[d->dev], req->args.read.outPtr, len);
    rv = len;
out:
    return rv;
}

static IOSError
ipcSeek(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    DDFileDescriptor *d;
    IOSResourceSeek  *args;

    RM_LOG("in ipcSeek\n");

    if (!req)
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }
    d = (DDFileDescriptor *) req->handle;
    args = (IOSResourceSeek *)&req->args.seek;

    if (!d->inUse) 
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    switch(args->whence) 
    {
    case IOS_SEEK_SET:
        d->pos = args->offset & 0xff;
        break;
    case IOS_SEEK_CURRENT:
        d->pos = (d->pos + args->offset) & 0xff;
        break;
    case IOS_SEEK_END:
        d->pos = (255 + args->offset) & 0xff;
        break;
    default:
        RM_LOG("ERROR in ipcSeek\n");
        rv = IOS_ERROR_INVALID;
        goto out;
    }

out:
    RM_LOG("in ipcSeek: %d\n", rv);
    return rv;
}

static IOSError
ipcIoctl(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    DDFileDescriptor *d;
    IOSResourceIoctl *args;

    RM_LOG("in ipcIoctl\n");

    if (!req)
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }
    d = (DDFileDescriptor *) req->handle;
    if (!d->inUse)
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }
    args = (IOSResourceIoctl *)&req->args.ioctl;

    if (args->inPtr == 0 || args->outPtr == 0 || 
        args->inLen == 0 || args->outLen == 0 ||
        args->inLen != args->outLen) 
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    memcpy(args->outPtr, args->inPtr, args->outLen);

out:
    return rv;
}

static IOSError
ipcIoctlv(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    DDFileDescriptor *d;
    IOSResourceIoctlv *args;

    RM_LOG("in ipcIoctlv\n");

    if (!req)
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }
    d = (DDFileDescriptor *) req->handle;
    if (!d->inUse)
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    args = (IOSResourceIoctlv *)&req->args.ioctlv;

    if (args->vector[0].base == 0 || args->vector[1].base == 0 || 
        args->vector[0].length == 0 || args->vector[1].length == 0 ||
        args->vector[0].length != args->vector[1].length) 
    {
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    memcpy(args->vector[1].base, args->vector[0].base, args->vector[1].length);

out:
    return rv;
}

void 
//ipcRm(u32 arg)
main(void)
{
    IOSError rv;
    IOSMessageQueueId mq;
    IOSMessage msgArray[3];
    IOSMessage msg;
    
    RM_LOG("Simple device driver example\n");

    /* Create a message queue */
    RM_LOG("Create message queue\n");
    if ((mq = IOS_CreateMessageQueue(msgArray, 
                   sizeof(msgArray) / sizeof(msgArray[0]), 0xffffffff)) < 0) 
    {
        rv = mq;
        RM_ERROR("IOS_CreateMessageQueue", rv);
        goto out;
    }

    /* Register the message queue with the kernel */
    if ((rv = IOS_RegisterResourceManager("/dev/ipc", mq)) != IOS_ERROR_OK) 
    {
        RM_ERROR("IOS_RegisterResourceManager", rv);
        goto out;
    }

    /* Main dispatch loop */
    while (1) {
        /* Receive a command */
        RM_LOG("Waiting for command\n");
        if ((rv = IOS_ReceiveMessage(mq, &msg, IOS_MESSAGE_BLOCK)) 
                != IOS_ERROR_OK) 
        {
            RM_ERROR("IOS_ReceiveMessage", rv);
            goto out;
        }
        RM_LOG("Received resource request: %08x\n", msg);

        /* Dispatch command */
        IOSResourceRequest *req = (IOSResourceRequest *) msg;
        switch (req->cmd) {
        case IOS_OPEN:
            RM_LOG("  IOS_OPEN\n");
            rv = ipcOpen(req);
            break;
        case IOS_CLOSE:
            RM_LOG("  IOS_CLOSE\n");
            rv = ipcClose(req);
            break;
        case IOS_READ:
            RM_LOG("  IOS_READ\n");
            rv = ipcRead(req);
            break;
        case IOS_WRITE:
            RM_LOG("  IOS_WRITE\n");
            rv = ipcWrite(req);
            break;
        case IOS_SEEK:
            RM_LOG("  IOS_SEEK\n");
            rv = ipcSeek(req);
            break;
        case IOS_IOCTL:
            RM_LOG("  IOS_IOCTL\n");
            rv = ipcIoctl(req);
            break;
        case IOS_IOCTLV:
            RM_LOG("  IOS_IOCTL\n");
            rv = ipcIoctlv(req);
            break;
        default:
            RM_LOG("  Unsupported\n");
            rv = IOS_ERROR_INVALID;
            break;
        }
        RM_LOG("Returning = %d\n", rv);
        IOS_ResourceReply(req, rv);
    }

out:
    return;
}
