a10 3
#include <stdio.h>
#include <stdlib.h>

d16 8
a23 1
#include "iosresource.h"
d27 2
a28 2
#define IPC_LOG(...)
//#define IPC_LOG(...)       printf("SRV: " __VA_ARGS__)
a30 4
// iop.h needs a IPCIOPCTRL_REG & IPCS2PMSG_REG definitions {
#define IPCIOPCTRL_REG  0x77777777
#define IPCS2PMSG_REG   0x77777777

a34 6
// in iostypes.h: {
// to be made distinct events:
#define IOS_EVENT_IPC_MSG   IOS_EVENT_IPCIOP
#define IOS_EVENT_IPC_ACK   IOS_EVENT_IPCIOP
// } in iostypes.h

d84 1
a84 1
        IO_WRITE(IPCS2PMSG_REG, 
d101 4
a104 4
        IO_WRITE(IPCIOPCTRL_REG, 
                 (IO_READ(IPCIOPCTRL_REG) 
                  & (IPCIOPCTRL_ACK_INTR_MASK | IPCIOPCTRL_MSG_INTR_MASK)) 
                 | bitm);
d190 1
a190 1
        rv = iosOpenAsync(req->args.open.path, req->args.open.flags, 
d195 1
a195 1
        rv = iosCloseAsync(fd, __ipcMQ, req);
d200 1
a200 1
        rv = iosReadAsync(fd, req->args.read.outPtr, req->args.read.outLen, 
d207 1
a207 1
        rv = iosWriteAsync(fd, req->args.write.inPtr, req->args.write.inLen, 
d212 1
a212 1
        rv = iosSeekAsync(fd, req->args.seek.offset, req->args.seek.whence, 
d222 1
a222 1
        rv = iosIoctlAsync(fd, req->args.ioctl.cmd, req->args.ioctl.inPtr, 
d241 1
a241 1
        rv = iosIoctlvAsync(fd, req->args.ioctlv.cmd, 
d252 1
a252 1
    if (rv != IOS_ERROR_OK) 
d264 1
a264 1
iosIpcThread(u32 arg)
d268 1
a268 1
    static IOSMessage ipcMsg = IOS_IPC_MSG, ipcAck = IOS_IPC_ACK;
d271 4
d276 1
a276 1
    if ((__ipcMQ = iosCreateMessageQueue(array, sizeof(array) / 
d280 1
a280 1
        exit(1);
d283 1
a283 1
    if ((rv = IOS_HandleEvent(IOS_EVENT_IPC_MSG, __ipcMQ, ipcMsg)) 
d287 1
a287 7
        exit(1);
    }
    if ((rv = IOS_HandleEvent(IOS_EVENT_IPC_ACK, __ipcMQ, ipcAck)) 
                != IOS_ERROR_OK) 
    {
        IPC_LOG("Unable to register IPC ACK  event handler: %d\n", rv);
        exit(1);
d290 1
d292 4
a295 3
    IO_WRITE(IPCIOPCTRL_REG, IPCIOPCTRL_ACK_INTR_MASK 
                             | IPCIOPCTRL_MSG_INTR_MASK 
                             | IPCIOPCTRL_OUT_ACK_MASK);
d299 1
a299 1
        if (iosReceiveMessage(__ipcMQ, &msg, IOS_MESSAGE_BLOCK) == 
d303 2
a311 15
            case IOS_IPC_ACK:
                /* ACK interrupt */
                __mailboxAck = 1;

                IPC_LOG("Got ACK\n");

                // clear ACK bit
                IO_WRITE(IPCIOPCTRL_REG, 
                         (IO_READ(IPCIOPCTRL_REG) 
                          & (IPCIOPCTRL_ACK_INTR_MASK 
                             | IPCIOPCTRL_MSG_INTR_MASK))
                         | IPCIOPCTRL_IN_ACK_MASK);
                __iosSendResponse();
                break;

d314 1
a314 2
                /* IPC request */
                IPC_LOG("Got MSG\n");
d316 2
a317 2
                u32 m = (u32)IOS_PhysicalToVirtual(IO_READ(IPCS2PMSG_REG)),
                    bitm = IPCIOPCTRL_IN_MSG_MASK; // clear MSG bit
d319 2
a320 2
                IPC_LOG("MSG READ: ipcp2smsg: %x inflight: %d\n", 
                        ipcp2smsg, __inFlight);
d322 9
a330 6
                if (__inFlight < sizeof(__responses.buf) 
                                  / sizeof(__responses.buf[0]) - 1) 
                {
                    // generate ACK 
                    bitm |= IPCIOPCTRL_OUT_ACK_MASK;
                    IPC_LOG("OUT_ACK\n");
d332 5
a336 1
                // else prevent new requests being sent by not sending ACK
d338 27
a364 7
                IO_WRITE(IPCIOPCTRL_REG, 
                         (IO_READ(IPCIOPCTRL_REG) 
                          & (IPCIOPCTRL_ACK_INTR_MASK 
                             | IPCIOPCTRL_MSG_INTR_MASK)) 
                         | bitm);
                __inFlight++;
                __iosDispatchIpc(m);
d373 2
a376 1

