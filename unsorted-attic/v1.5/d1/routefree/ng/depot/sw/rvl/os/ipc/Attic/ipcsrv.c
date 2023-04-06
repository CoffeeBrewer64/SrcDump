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
#include <iostypes.h>
#include "thread.h"
#include "message.h"
#include "ios.h"
#include "hw.h"
//#include "iosresource.h"
#include "iosressrv.h"
#include "ioslibc.h"

#define STACK_SIZE 1024
const u8 _initStack[STACK_SIZE];
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = 10;

//u8 __iosIpcStack[IPC_STACK_SIZE]; /* used in thread.c */

#ifdef LOG_FL
#   define IPC_LOG(...)       printf("SRV: " __VA_ARGS__)
#else
#   define IPC_LOG(...)
#endif

// TBD: {
#define IOP_DDR_START   0x0
#define IOP_DDR_END     0xffffffff
// } in iop.h

#define IOS_VirtualToPhysical(x) (u32)(x)
#define IOS_PhysicalToVirtual(x) (void*)(x)
// } TBD

static
IOSMessageQueueId __ipcMQ;

static u32 __mailboxAck;
static u32 __inFlight;

#define MAX_MSG_QUEUE       8
#define MAX_SRV_INFLIGHT    8

static struct 
{
    u32                 count;
    u32                 rptr;
    u32                 wptr;
    IOSResourceRequest *buf[MAX_SRV_INFLIGHT];
} __responses;

static void
__iosQueueResponse(IOSResourceRequest *resp)
{
    IPC_LOG("__iosQueueResponse: cnt: %d val: %p\n", 
            __responses.count, resp);
    __responses.buf[__responses.wptr] = resp;
    __responses.wptr = (__responses.wptr + 1) % 
                       (sizeof(__responses.buf) / sizeof(__responses.buf[0]));
    __responses.count++;
}

static void
__iosSendResponse(void)
{
    IPC_LOG("__iosSendResponse: ack: %d, cnt: %d val: %x\n", 
            __mailboxAck, __responses.count, 
            (u32)__responses.buf[__responses.rptr]);
    if (__mailboxAck && __responses.count > 0) 
    {
        u32 bitm = IPCIOPCTRL_OUT_MSG_MASK; // generate MSG IPC interrupt

        // write the reply address
        IO_WRITE(ACR_IPCS2PMSG_TRUSTED, 
                 IOS_VirtualToPhysical((u32)__responses.buf[__responses.rptr]));
        __responses.rptr = (__responses.rptr + 1) % (sizeof(__responses.buf) 
                            / sizeof(__responses.buf[0]));
        __responses.count--;

        if (__inFlight == sizeof(__responses.buf) / sizeof(__responses.buf[0])) 
        {
            // ACK the last IPC request - when buf[] got full, the last request 
            // was not ACK'ed
            bitm |= IPCIOPCTRL_OUT_ACK_MASK;
            IPC_LOG("__iosSendResponse: ACK\n"); 
        }
        __inFlight--;
        IPC_LOG("__iosSendResponse: count: %d inflight: %d\n", 
                __responses.count, __inFlight); 
        __mailboxAck = 0;
        IOS_WriteIPCIOPCtrlReg((IOS_ReadIPCIOPCtrlReg() 
                                & (IPCIOPCTRL_ACK_INTR_MASK 
                                   | IPCIOPCTRL_MSG_INTR_MASK)) 
                               | bitm);
    }
    return;
}

static void
__iosProcessIpc(IOSResourceRequest *req)
{
    /* Need to flush results back */
    if (req->status >= 0) 
    {
        /* req->cmd saved in req->handle */
        switch (req->handle) 
        {
        case IOS_READ:
            req->args.read.outPtr = (u8*)IOS_VirtualToPhysical(
                                            req->args.read.outPtr);
            break;

        case IOS_IOCTL:
            req->args.ioctl.outPtr = (u8*)IOS_VirtualToPhysical(
                                            req->args.ioctl.outPtr);
            break;

        case IOS_IOCTLV:
        {
            u32 i;
            IOSResourceIoctlv *v = &req->args.ioctlv;
/*
            for (i = 0; i < req->args.ioctlv.writeCount; ++i) 
            {
                v->vector[v->readCount + i].base = (u8*)IOS_VirtualToPhysical(
                                        (u32)v->vector[v->readCount + i].base);
            }
*/
            // convert everything
            for (i = 0; 
                 i < (req->args.ioctlv.readCount + req->args.ioctlv.writeCount);
                 ++i) 
            {
                v->vector[i].base = (u8*)IOS_VirtualToPhysical(
                                        (u32)v->vector[i].base);
            }
            req->args.ioctlv.vector = (IOSIoVector*)IOS_VirtualToPhysical(
                                                      req->args.ioctlv.vector);
            break;
        }
        default:
            // check for invalid cmd/handle 
            break;
        }
    }

    /* Flush status back to GBA */
    IOS_FlushMem(wb_iod);

    __iosQueueResponse(req);
    __iosSendResponse();
}

static void
__iosDispatchIpc(u32 v)
{
    IOSResourceRequest *req;
    IOSError rv = IOS_ERROR_OK;
    IOSFd fd;
    int   i;

    /* Check that v is in DRAM */
    if (!IN_RANGE(v, IOP_DDR_START, IOP_DDR_END)) 
    {
        IPC_LOG("ERROR Out of range: %u\n", v);
        goto end;
    }

    /* Examine cmd header */
    req = (IOSResourceRequest *)v;

    IOS_InvalidateRdb(rb_iod);

    fd = req->handle;
    req->handle = req->cmd;

    IPC_LOG("CMD: %d\n", req->cmd);
    switch (req->cmd) 
    {
    case IOS_OPEN:
        req->args.open.path = (u8*)IOS_PhysicalToVirtual(req->args.open.path);
        IPC_LOG("Open path: %s\n", req->args.open.path);
        rv = IOS_OpenAsync(req->args.open.path, req->args.open.flags, 
                          __ipcMQ, req);
        break;

    case IOS_CLOSE:
        rv = IOS_CloseAsync(fd, __ipcMQ, req);
        break;

    case IOS_READ:
        req->args.read.outPtr = (u8*)IOS_PhysicalToVirtual(req->args.read.outPtr);
        rv = IOS_ReadAsync(fd, req->args.read.outPtr, req->args.read.outLen, 
                          __ipcMQ, req);
        break;

    case IOS_WRITE:
        req->args.write.inPtr = (u8*)IOS_PhysicalToVirtual(req->args.write.inPtr);
        rv = IOS_WriteAsync(fd, req->args.write.inPtr, req->args.write.inLen, 
                           __ipcMQ, req);
        break;

    case IOS_SEEK:
        rv = IOS_SeekAsync(fd, req->args.seek.offset, req->args.seek.whence, 
                          __ipcMQ, req);
        break;

    case IOS_IOCTL:
        req->args.ioctl.inPtr = (u8*)IOS_PhysicalToVirtual(req->args.ioctl.inPtr);
        req->args.ioctl.outPtr = (u8*)IOS_PhysicalToVirtual(
                                        req->args.ioctl.outPtr);

        rv = IOS_IoctlAsync(fd, req->args.ioctl.cmd, req->args.ioctl.inPtr, 
                           req->args.ioctl.inLen, req->args.ioctl.outPtr, 
                           req->args.ioctl.outLen, __ipcMQ, req);
        break;

    case IOS_IOCTLV:
    {
        IOSResourceIoctlv *v = &req->args.ioctlv;

        req->args.ioctlv.vector = (IOSIoVector*)IOS_PhysicalToVirtual(
                                                    req->args.ioctlv.vector);

        for (i = 0; 
             i < (req->args.ioctlv.writeCount + req->args.ioctlv.readCount); 
             ++i) 
        {
            v->vector[i].base = (u8*)IOS_PhysicalToVirtual(v->vector[i].base);
        }
        
        rv = IOS_IoctlvAsync(fd, req->args.ioctlv.cmd, 
                            req->args.ioctlv.readCount, 
                            req->args.ioctlv.writeCount, 
                            req->args.ioctlv.vector, __ipcMQ, req);
        break;
    }

    default:
        rv = IOS_ERROR_INVALID;
    }

    if (rv < 0) 
    {
        // no reply expected, report the error
        IPC_LOG("Dispatch ERROR: %d cmd: %d\n", rv, req->cmd);
        req->status = rv;
        __iosProcessIpc(req);
    }
end:
    return;
}

void
main (void)
{
    static IOSMessage array[MAX_MSG_QUEUE];
    IOSMessage msg;
    static IOSResourceRequest ipcMsg;
    IOSError   rv;

    IPC_LOG("sample IPC server\n");

    ipcMsg.cmd = IOS_IPC_MSG;

    /* Create queue and register to handle events */
    if ((__ipcMQ = IOS_CreateMessageQueue(array, sizeof(array) / 
                                         sizeof(array[0]), 0xffffffff)) < 0) 
    {
        IPC_LOG("Unable to create IPC message queue: %d\n", __ipcMQ);
        goto out;
    }

    if ((rv = IOS_HandleEvent(IOS_EVENT_IPCIOP, __ipcMQ, (u32)&ipcMsg)) 
                != IOS_ERROR_OK) 
    {
        IPC_LOG("Unable to register IPC MSG event handler: %d\n", rv);
        goto out;
    }

    IOS_WriteIPCPPCCtrlReg(0);
    /* Enable IPC interrupts and allow incoming message */
    IOS_ClearAndEnableIPCIOPIntr();
    IOS_WriteIPCIOPCtrlReg(IPCIOPCTRL_ACK_INTR_MASK 
                           | IPCIOPCTRL_MSG_INTR_MASK 
                           | IPCIOPCTRL_OUT_ACK_MASK);

    while (1) 
    {
        IPC_LOG("INTSTS: %x INTMSK: %x IPCIOP: %x\n", 
                busRd32(ACR_IOPINTSTS_TRUSTED),
                busRd32(ACR_INTMASK_TRUSTED),
                IOS_ReadIPCIOPCtrlReg());

        if (IOS_ReceiveMessage(__ipcMQ, &msg, IOS_MESSAGE_BLOCK) == 
                IOS_ERROR_OK) 
        {
            IOSResourceRequest *req = (IOSResourceRequest*)msg;
            IPC_LOG("Got Msg %x\n", msg);

            switch (req->cmd)
            {
            case IOS_REPLY:
                IPC_LOG("Got REPLY\n");
                __iosProcessIpc(req);
                break;

            case IOS_IPC_MSG:
            {
                u32 bm = IOS_ReadIPCIOPCtrlReg();

                IPC_LOG("bitmask %x\n", bm);
                if (bm & IPCIOPCTRL_IN_ACK_MASK) {

                    /* ACK interrupt */
                    __mailboxAck = 1;

                    IPC_LOG("Got ACK\n");

                    // clear ACK INTR bit
                    IOS_WriteIPCIOPCtrlReg((IOS_ReadIPCIOPCtrlReg() 
                                            & (IPCIOPCTRL_ACK_INTR_MASK 
                                            | IPCIOPCTRL_MSG_INTR_MASK))
                                           | IPCIOPCTRL_IN_ACK_MASK);
                    IOS_ClearAndEnableIPCIOPIntr();
                    __iosSendResponse();
                }
                else
                if (bm & IPCIOPCTRL_IN_MSG_MASK) {

                    /* IPC request */
                    IPC_LOG("Got MSG\n");

                    u32 m = (u32)IOS_PhysicalToVirtual(
                                    IO_READ(ACR_IPCP2SMSG_TRUSTED));
                    bm = IPCIOPCTRL_IN_MSG_MASK; // clear MSG INTR bit

                    IPC_LOG("MSG READ: ipcp2smsg: %x inflight: %d\n", 
                            m, __inFlight);

                    if (__inFlight < sizeof(__responses.buf) 
                                      / sizeof(__responses.buf[0]) - 1) 
                    {
                        // generate ACK 
                        bm |= IPCIOPCTRL_OUT_ACK_MASK;
                        IPC_LOG("OUT_ACK\n");
                    }
                    // else prevent new requests being sent by not sending ACK

                    IOS_WriteIPCIOPCtrlReg((IOS_ReadIPCIOPCtrlReg() 
                                            & (IPCIOPCTRL_ACK_INTR_MASK 
                                               | IPCIOPCTRL_MSG_INTR_MASK)) 
                                           | bm);
                    IOS_ClearAndEnableIPCIOPIntr();
                    __inFlight++;
                    __iosDispatchIpc(m);
                }
                else {
                    IPC_LOG("Invalid INT\n");
                }
                break;
            }
            default:
                // error
                break;
            }
        }
    }

out:
    return;
}
