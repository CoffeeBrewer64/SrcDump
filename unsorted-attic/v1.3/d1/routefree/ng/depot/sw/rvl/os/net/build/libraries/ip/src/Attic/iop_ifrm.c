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

/*---------------------------------------------------------------------------*
 * 
 * Network Device Interface RM
 * 
 *---------------------------------------------------------------------------*/

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <iosresource.h>
#include <iosiobuf.h>

#include <dolphin/os.h>
#include <dolphin/ip/iop_ethtool.h>
#include <dolphin/ip/iop_netif.h>
#include "IPPrivate.h"


/*---------------------------------------------------------------------------*
 * 
 * global variables
 * 
 *---------------------------------------------------------------------------*/

#define NET_IF_STACK_SIZE       (4 * 1024)
#define NET_IF_PRIORITY         60
#define NET_IF_MSGQ_SIZE        32

static char __netIfStack[NET_IF_STACK_SIZE] ATTRIBUTE_ALIGN(4);
extern IPInterface __IFDefault;

/*---------------------------------------------------------------------------*
 * 
 * Network Interface Resource Manager
 * 
 *---------------------------------------------------------------------------*/

static IOSError
netIfIoctlv(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    IOSResourceIoctlv *ioctlv = (IOSResourceIoctlv *) &req->args.ioctlv;
    
    switch (ioctlv->cmd)
    {
        case NET_IP_RECV_PKT:
        {
            // TODO: int ifID = *( (int *) ioctlv->vector[0].base);
            IOSIobuf * iob = (IOSIobuf *) ioctlv->vector[1].base;

            // TODO: dump out the packet
            {
                int len     = IOS_IOB_DATA_LEN(iob);
                u32 *ptr    = (u32*)IOS_IOB_DATA(iob);

	            OSDbgReport(("data = %p\n", IOS_IOB_DATA(iob)));
	            while (len)
	            {
		            if ( len >= 4 ) len -= 4;
		            else len = 0;
    	            OSDbgReport(("%08X\n",*ptr++));
	            }
	            OSDbgReport(("\n"));
            }

            // TODO: multi interfces need to be supported
            ETHIn(&__IFDefault, (ETHHeader *) IOS_IOB_DATA(iob), IOS_IOB_DATA_LEN(iob));
            IOS_FreeIob(iob);
            rv = 0;
        }
            break;

        case NET_IP_NOTIFY:
        {
            // TODO: int ifID        = *( (int *) ioctlv->vector[0].base);
            // TODO: int notifyID    = *( (int *) ioctlv->vector[1].base);

            // TODO: the notification needs to be implemented
            rv = 0;
        }
            break;
            
        default:
            rv = IOS_ERROR_INVALID;
            break;
    }

    return rv;
}

static void
netIfRM(u32 arg)
{   
    IOSMessageQueueId qid;
    IOSMessage msgQ[NET_IF_MSGQ_SIZE];
    IOSError rv = IOS_ERROR_OK;
    IOSMessage msg;
    IOSResourceRequest *req;

    OSDbgReport(("*** Network Device Interface Started ***\n"));

    /* Create a RM message queue for socket interface layer */
    if ( (qid = IOS_CreateMessageQueue(msgQ, NET_IF_MSGQ_SIZE)) < 0 ) {
        OSReport("Creating message queue failed\n");
        return;
    }
    
    /* Register RM */
    if ( IOS_ERROR_OK != IOS_RegisterResourceManager(NET_RM_IP_BOT, qid) ) {
        OSReport("Registering network IF RM failed. Exiting...\n");
        return;
    }

    /* Sit in a loop processing requests */
    while(1) {
        IOS_ReceiveMessage(qid, &msg, IOS_MESSAGE_BLOCK);
        req = (IOSResourceRequest *)msg;
        switch(req->cmd) {
            case IOS_OPEN:
            case IOS_CLOSE:
                rv = 0;
                break;
            case IOS_IOCTLV:
                rv = netIfIoctlv(req);
                break;
            default:
                OSReport("%s: Network IF RM got UNKNOWN request\n", __FUNCTION__);
                rv = IOS_ERROR_INVALID;
                break;
        }
        IOS_ResourceReply(req, rv);
    }

    OSDbgReport(("*** Network Device Interface Ended ***\n"));
    
    /* Unregister RM. Destroys message queue. */
    IOS_DestroyMessageQueue(qid);
    return;
}

BOOL
NetInitIfRM(void)
{
    IOSThreadId rmThreadId;

    rmThreadId = IOS_CreateThread(netIfRM, NULL, __netIfStack + sizeof(__netIfStack),
        sizeof(__netIfStack), NET_IF_PRIORITY, IOS_THREAD_CREATE_DETACHED);

    if (rmThreadId < 0) {
        OSReport("%s: could not create net IF RM thread - exiting\n", __FUNCTION__);
        return FALSE;
    }

    if (IOS_StartThread(rmThreadId) != IOS_ERROR_OK) {
        OSReport("%s: could not start net IF RM thread\n", __FUNCTION__);
        return FALSE;
    }

    return TRUE;
}
