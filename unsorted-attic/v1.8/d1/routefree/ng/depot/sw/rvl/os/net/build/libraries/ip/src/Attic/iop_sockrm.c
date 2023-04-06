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
 * Socket Layer RM
 * 
 *---------------------------------------------------------------------------*/

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <iosresource.h>

#include <dolphin/socket.h>
#include <dolphin/iop_sock.h>
#include <dolphin/ip/iop_netif.h>
#include <dolphin/os.h>

#define NET_SOCK_STACK_SIZE       (4 * 1024)
#define NET_SOCK_PRIORITY         60
#define NET_SOCK_MSGQ_SIZE        64

/*---------------------------------------------------------------------------*
 * 
 * global variables
 * 
 *---------------------------------------------------------------------------*/

extern SOResolver __SOResolver;

const u8 _initStack[NET_SOCK_STACK_SIZE] ATTRIBUTE_ALIGN(4);
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = 10;

static char __netSockStack[(SO_SOCKET_MAX-1) * NET_SOCK_STACK_SIZE] ATTRIBUTE_ALIGN(4);
static IOSMessageQueueId __qid;
static IOSMessage __msgQ[NET_SOCK_MSGQ_SIZE];

/*---------------------------------------------------------------------------*
 * 
 * Socket Layer Resource Manager
 * 
 *---------------------------------------------------------------------------*/
static IOSError
sockRmIoctl(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;

    return rv;
}

// TODO: this is the testing code which will be removed once driver is integrated
extern IOSIobDebugInfo iobufDebugInfo;
static IOSFd __fdIfRM = -1;
static void 
testRecv(OSAlarm* alarm, OSContext* context)
{
    u16 length = 64;
    IOSIobuf * iob;
    char *data;
    int i = 0;
    int ifID = 0;
    IOSIoVector v[2];

    TCPIP_UNUSED(alarm);
    TCPIP_UNUSED(context);
    
    OSReport("%s: enter\n", __FUNCTION__);

    if (IOS_AccessIobPool(POOL_DEFAULT) != IOS_ERROR_OK) {
        OSReport("%s: getting access to iobuf pool failed\n", __FUNCTION__);
        return;
    }

    iob = IOS_AllocIob(POOL_DEFAULT, length, iobufDebugInfo);
    if (!iob) {
        OSReport("usbRecv error: allocating iobuf failed\n");
        return;
    }
    
    data = IOS_PutIob(iob, length);
    
    data[i++] = 0x00;
    data[i++] = 0x0e;
    data[i++] = 0xc6;
    data[i++] = 0x00;

    data[i++] = 0x00;
    data[i++] = 0x66;
    data[i++] = 0x00;
    data[i++] = 0x11;

    data[i++] = 0x11;
    data[i++] = 0xbd;
    data[i++] = 0xb8;
    data[i++] = 0x31;

    data[i++] = 0x08;
    data[i++] = 0x00;
    data[i++] = 0x00;
    data[i++] = 0x00;

    data[i++] = 0x45;
    data[i++] = 0x00;

    data[i++] = 0x00;
    data[i++] = 0x30;
    data[i++] = 0x00;
    data[i++] = 0x00;

    data[i++] = 0x40;
    data[i++] = 0x00;
    data[i++] = 0x40;
    data[i++] = 0x06;

    data[i++] = 0x26;
    data[i++] = 0x20;
    data[i++] = 0x0a;
    data[i++] = 0x00;

    data[i++] = 0x00;
    data[i++] = 0x88;
    data[i++] = 0x0a;
    data[i++] = 0x00;

    data[i++] = 0x00;
    data[i++] = 0x21;
    data[i++] = 0x1f;
    data[i++] = 0x40;

    data[i++] = 0xc0;
    data[i++] = 0x00;
    data[i++] = 0x4e;
    data[i++] = 0x58;

    data[i++] = 0x8c;
    data[i++] = 0x8b;
    data[i++] = 0x00;
    data[i++] = 0x00;

    data[i++] = 0x00;
    data[i++] = 0x01;
    data[i++] = 0x70;
    data[i++] = 0x12;

    data[i++] = 0x16;
    data[i++] = 0xd0;
    data[i++] = 0x9d;
    data[i++] = 0x71;

    data[i++] = 0x00;
    data[i++] = 0x00;
    data[i++] = 0x02;
    data[i++] = 0x04;

    data[i++] = 0x05;
    data[i++] = 0xb4;
    data[i++] = 0x01;
    data[i++] = 0x01;

    data[i++] = 0x04;
    data[i++] = 0x02;

    if (__fdIfRM == -1)
    {
        __fdIfRM = IOS_Open(NET_RM_IP_BOT, 0);
        OSReport("__fdIfRM = %d\n", __fdIfRM);
    }

    v[0].base   = (u8 *) &ifID;
    v[0].length = sizeof(int);
    v[1].base   = (u8 *) iob;
    v[1].length = sizeof(IOSIobuf);

    OSReport("%s: call ioctlv\n", __FUNCTION__);

    IOS_Ioctlv(__fdIfRM, NET_IP_RECV_PKT, 2, 0, v);

    return;
}

static IOSError
sockRmIoctlv(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_OK;
    IOSResourceIoctlv *ioctlv = (IOSResourceIoctlv *) &req->args.ioctlv;
    
    switch (ioctlv->cmd)
    {
        case NET_SO_ACCEPT:
        {
            int socket = *( (int *) ioctlv->vector[0].base);
            void * sockAddr = (void *) ioctlv->vector[1].base;

            OSDbgReport(("%s: receive accept\n", __FUNCTION__));
            rv = SOAccept(socket, sockAddr);
        }
            break;

        case NET_SO_BIND:
        {
            int socket = *( (int *) ioctlv->vector[0].base);
            const void * sockAddr = (const void *) ioctlv->vector[1].base;
            
            OSDbgReport(("%s: receive bind\n", __FUNCTION__));
            rv = SOBind(socket, sockAddr);
        }
            break;
            
        case NET_SO_CLOSE:
        {
            int socket = *( (int *) ioctlv->vector[0].base);

            OSDbgReport(("%s: receive close\n", __FUNCTION__));
            rv = SOClose(socket);
        }
            break;
            
        case NET_SO_CONNECT:
        {
            int socket = *( (int *) ioctlv->vector[0].base);
            const void * sockAddr = (const void *) ioctlv->vector[1].base;

            // TODO: this is the testing code which will be removed
            {
                OSAlarm alarm;
                
                OSCreateAlarm(&alarm);
                OSSetAlarm(&alarm, 500000, testRecv);
            }

            OSDbgReport(("%s: receive connect\n", __FUNCTION__));
            rv = SOConnect(socket, sockAddr);
        }
            break;

        case NET_SO_FCNTL:
        {
            int socket  = *( (int *) ioctlv->vector[0].base);
            int fcntl   = *( (int *) ioctlv->vector[1].base);
            int flag    = *( (int *) ioctlv->vector[2].base);

            OSDbgReport(("%s: receive fcntl\n", __FUNCTION__));
            rv = SOFcntl(socket, fcntl, flag);
        }
            break;

        case NET_SO_GETPEERNAME:
        {
            int socket = *( (int *) ioctlv->vector[0].base);
            void * sockAddr = (void *) ioctlv->vector[1].base;

            OSDbgReport(("%s: receive getpeername\n", __FUNCTION__));
            rv = SOGetPeerName(socket, sockAddr);
        }
            break;

        case NET_SO_GETSOCKNAME:
        {
            int socket = *( (int *) ioctlv->vector[0].base);
            void * sockAddr = (void *) ioctlv->vector[1].base;

            OSDbgReport(("%s: receive getsockname\n", __FUNCTION__));
            rv = SOGetSockName(socket, sockAddr);
        }
            break;

        case NET_SO_GETSOCKOPT:
        {
            int socket  = *( (int *) ioctlv->vector[0].base);
            int level   = *( (int *) ioctlv->vector[1].base);
            int optname = *( (int *) ioctlv->vector[2].base);
            void *optval= (void *) ioctlv->vector[3].base;
            int *optlen = (int *) ioctlv->vector[4].base;

            OSDbgReport(("%s: receive getsockopt\n", __FUNCTION__));
            rv = SOGetSockOpt(socket, level, optname, optval, optlen);
        }
            break;

        case NET_SO_SETSOCKOPT:
        {
            int socket  = *( (int *) ioctlv->vector[0].base);
            int level   = *( (int *) ioctlv->vector[1].base);
            int optname = *( (int *) ioctlv->vector[2].base);
            const void *optval = (const void *) ioctlv->vector[3].base;
            int optlen  = *( (int *) ioctlv->vector[4].base);

            OSDbgReport(("%s: receive setsockopt\n", __FUNCTION__));
            rv = SOSetSockOpt(socket, level, optname, optval, optlen);
        }
            break;

        case NET_SO_LISTEN:
        {
            int socket = *( (int *) ioctlv->vector[0].base);
            int backlog = *( (int *) ioctlv->vector[1].base);
            
            OSDbgReport(("%s: receive listen\n", __FUNCTION__));
            rv = SOListen(socket, backlog);
        }
            break;

        case NET_SO_POLL:
        {
            SOPollFD *fds = (SOPollFD *) ioctlv->vector[0].base;
            unsigned nfds = ioctlv->vector[0].length;
            OSTime timeout = *( (OSTime *) ioctlv->vector[1].base);
    
            OSDbgReport(("%s: receive poll\n", __FUNCTION__));
            rv = SOPoll(fds, nfds, timeout);
        }
            break;

        case NET_SO_RECVFROM:
        {
            int socket  = *( (int *) ioctlv->vector[0].base);
            int flags   = *( (int *) ioctlv->vector[1].base);
            void *buf   = (void *) ioctlv->vector[2].base;
            int len     = ioctlv->vector[2].length;
            void * sockFrom = (void *) ioctlv->vector[3].base;
            
            OSDbgReport(("%s: receive recvfrom\n", __FUNCTION__));
            rv = SORecvFrom(socket, buf, len, flags, sockFrom);
        }
            break;

        case NET_SO_SENDTO:
        {
            int socket      = *( (int *) ioctlv->vector[0].base);
            int flags       = *( (int *) ioctlv->vector[1].base);
            const void *buf = (const void *) ioctlv->vector[2].base;
            int len         = ioctlv->vector[2].length;
            void * sockTo   = (void *) ioctlv->vector[3].base;
            
            OSDbgReport(("%s: receive sendto\n", __FUNCTION__));
            rv = SOSendTo(socket, buf, len, flags, sockTo);
        }
            break;

        case NET_SO_SHUTDOWN:
        {
            int socket  = *( (int *) ioctlv->vector[0].base);
            int how     = *( (int *) ioctlv->vector[1].base);

            OSDbgReport(("%s: receive shutdown\n", __FUNCTION__));
            rv = SOShutdown(socket, how);
        }
            break;

        case NET_SO_SOCKET:
        {
            int af      = *( (int *) ioctlv->vector[0].base);
            int type    = *( (int *) ioctlv->vector[1].base);
            int protocol= *( (int *) ioctlv->vector[2].base);
            
            OSDbgReport(("%s: receive new socket\n", __FUNCTION__));
            rv = SOSocket(af, type, protocol);
        }
            break;

        case NET_SO_GETHOSTBYNAME:
        {
            const char *name = (const char *) ioctlv->vector[0].base;
            SOResolver *soResolver = (SOResolver *) ioctlv->vector[1].base;
            SOHostEnt * env  = SOGetHostByName(name);
            
            if (env == NULL)
                rv = IOS_ERROR_INVALID;
            else {
                u8  **ptr, **ptr2;
                u8  *addr2;
                
                strncpy(soResolver->name, __SOResolver.name, SO_MAXDNAME);
                soResolver->ent.addrType = SO_PF_INET;
                memcpy(soResolver->addrList, __SOResolver.addrList, 
                        sizeof(__SOResolver.addrList));
                
                ptr2    = soResolver->ptrList;
                addr2   = soResolver->addrList;
                for (ptr = __SOResolver.ptrList; ptr; ptr++) {
                    *ptr2 = addr2;
                    ptr2++;
                    addr2 += IP_ALEN;
                }
                *ptr2 = NULL;
                soResolver->ent.aliases = (char**) ptr;
            }
        }
            break;

        case NET_SO_GETHOSTBYADDR:
        {
            const void *addr    = (const void *) ioctlv->vector[0].base;
            int len             = ioctlv->vector[0].length;
            int type            = *( (int *) ioctlv->vector[1].base);
            SOResolver *soResolver = (SOResolver *) ioctlv->vector[2].base;
            SOHostEnt * env  = SOGetHostByAddr(addr, len, type);
            
            if (env == NULL)
                rv = IOS_ERROR_INVALID;
            else {
                u8  **ptr;

                ptr = soResolver->ptrList;
                *ptr = soResolver->addrList;
                ++ptr;
                *ptr = NULL;
                
                switch (type)
                {
                    case SO_PF_INET:
                        soResolver->ent.addrType = SO_PF_INET;
                        memcpy(soResolver->addrList, __SOResolver.addrList, sizeof(SOInAddr));
                        break;

                    case SO_PF_INET6:
                        soResolver->ent.addrType = SO_PF_INET6;
                        memcpy(soResolver->addrList, __SOResolver.addrList, sizeof(SOIn6Addr));
                        break;

                    default:
                        break;
                }
            }
        }
            break;

        default:
            rv = IOS_ERROR_INVALID;
            break;
    }

    return rv;
}

static void
sockRM(u32 arg)
{   
    IOSError rv = IOS_ERROR_OK;
    IOSMessage msg;
    IOSResourceRequest *req;

    /* Sit in a loop processing requests */
    while(1) {
        IOS_ReceiveMessage(__qid, &msg, IOS_MESSAGE_BLOCK);
        req = (IOSResourceRequest *)msg;
        switch(req->cmd) {
            case IOS_OPEN:
            case IOS_CLOSE:
                rv = 0;
                break;
            case IOS_IOCTL:
                rv = sockRmIoctl(req);
                break;
            case IOS_IOCTLV:
                rv = sockRmIoctlv(req);
                break;
            default:
                OSReport("%s: socket RM got UNKNOWN request\n", __FUNCTION__);
                rv = IOS_ERROR_INVALID;
                break;
        }
        IOS_ResourceReply(req, rv);
    }
}

BOOL
NetInitSockRM( void )
{
    IOSThreadId rmThreadId;
    u32 i;

    /* Create a RM message queue for socket interface layer */
    if ( (__qid = IOS_CreateMessageQueue(__msgQ, NET_SOCK_MSGQ_SIZE)) < 0 ) {
        OSReport("%s: creating message queue failed\n", __FUNCTION__);
        return FALSE;
    }
    
    /* Register RM */
    if ( IOS_ERROR_OK != IOS_RegisterResourceManager(NET_RM_SOCK, __qid) ) {
        IOS_DestroyMessageQueue(__qid);
        OSReport("%s: registering network socket RM failed\n", __FUNCTION__);
        return FALSE;
    }

    for (i = 1; i < SO_SOCKET_MAX; i++)
    {
        rmThreadId = IOS_CreateThread(sockRM, NULL, __netSockStack + i*NET_SOCK_STACK_SIZE,
            NET_SOCK_STACK_SIZE, NET_SOCK_PRIORITY, IOS_THREAD_CREATE_DETACHED);
    
        if (rmThreadId < 0) {
            OSReport("%s: could not create net socket RM thread - exiting\n", __FUNCTION__);
            return FALSE;
        }
    
        if (IOS_StartThread(rmThreadId) != IOS_ERROR_OK) {
            OSReport("%s: could not start net socket RM thread\n", __FUNCTION__);
            return FALSE;
        }
    }

    return TRUE;
}

BOOL
NetShutdownSockRM( void )
{
    /* Unregister RM. Destroys message queue. */
    IOS_DestroyMessageQueue(__qid);
    return TRUE;
}

/*---------------------------------------------------------------------------*
 * 
 * main functions
 * 
 *---------------------------------------------------------------------------*/

const u8 Client[4]      = {  10,   0,   0,  33 };
const u8 Netmask[4]     = { 255, 255, 255,   0 };
const u8 Gateway[4]     = {  10,   0,   0,   6 };

// TODO: it will be removed. This is to work around ARP
const u8 Server[4]      = {  10,   0,   0, 136 };
u8 CLIENT_MAC[]       = { 0x00,0x0e,0xc6,0x00,0x00,0x66 };
u8 GATEWAY_MAC[]      = { 0x00,0x11,0x11,0xBD,0xB8,0x31 }; // iose-2
u8 SERVER_MAC[]       = { 0x00,0x11,0x11,0xBD,0xB8,0x31 }; // iose-2

static void* Alloc(u32 name, s32 size)
{
    TCPIP_UNUSED(name);
    
    if (0 < size)
    {
        return OSAlloc((u32) size);
    }
    else
    {
        return NULL;
    }
}

static void Free(u32 name, void* ptr, s32 size)
{
    TCPIP_UNUSED(name);
    
    if (ptr && 0 < size)
    {
        OSFree(ptr);
    }
}

SOConfig Config =
{
    SO_VENDOR_NINTENDO,
    SO_VERSION,

    Alloc,
    Free,

    0,
    { SO_INADDR_ANY },
    { SO_INADDR_ANY },
    { SO_INADDR_ANY },
    { SO_INADDR_ANY },
    { SO_INADDR_ANY },

    4096,
    4096
};

// TODO: it will be removed. This is to work around ARP
extern void myAddArp( const u8 *Host, u8 *MAC );

void
main(int argc, char *argv[])
{
    int ret = 0;

    OSInitInterrupts();
    OSDbgReport(("%s: init interrupts done\n", __FUNCTION__));

    initNetMem();
    OSDbgReport(("%s: init mem done\n", __FUNCTION__));
    
    OSInitAlarm();
    OSDbgReport(("%s: init alarm done\n", __FUNCTION__));

    memcpy(&Config.addr,    Client,     4);
    memcpy(&Config.netmask, Netmask,    4);
    memcpy(&Config.router,  Gateway,    4);
    ret = SOStartup(&Config);
    OSDbgReport(("%s: SOStartup return = %d\n", __FUNCTION__, ret));
    
    // TODO: it will be removed. This is to work around ARP
    myAddArp(Client,   &CLIENT_MAC[0]);
    myAddArp(Gateway, &GATEWAY_MAC[0]);
    myAddArp(Server,  &SERVER_MAC[0]);

    NetInitIfRM();
    OSDbgReport(("%s: init dev if RM done\n", __FUNCTION__));

    NetInitSockRM();
    OSDbgReport(("%s: init sock RM done\n", __FUNCTION__));

    sockRM(0);

    OSDbgReport(("****** This should never be printed *******\n"));
    IOS_DestroyThread(0, NULL);
    exit(0);
}
