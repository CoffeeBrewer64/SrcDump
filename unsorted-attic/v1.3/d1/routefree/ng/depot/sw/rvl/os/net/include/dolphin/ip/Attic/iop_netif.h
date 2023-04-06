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
 * Network Interface header file. This is the interface between network stack
 * and device drivers
 * 
 *---------------------------------------------------------------------------*/

#ifndef __IOP_NETIF_H__
#define __IOP_NETIF_H__

#include "iop_ethtool.h"

#define NET_RM_IP_BOT       "/dev/net/ip/bottom"
#define NET_RM_WD_TOP       "/dev/net/wd/top"
#define NET_RM_USB_TOP      "/dev/net/usbeth/top"

/* network stack interface commands */
#define NET_IP_RECV_PKT             1
#define NET_IP_NOTIFY               2

/* network device driver commands */
#define NET_DEV_XMIT_PKT            3
#define NET_DEV_UP                  4
#define NET_DEV_DOWN                5
#define NET_DEV_SET_MULTICAST_LIST  6
#define NET_DEV_SET_MAC_ADDRESS     7
#define NET_DEV_GET_MAC_ADDRESS     8
#define NET_DEV_SET_MRU             9
#define NET_DEV_GET_STATS           10
#define NET_DEV_SET_ETHTOOL         11
#define NET_DEV_GET_ETHTOOL         12

/* Supported network interface */
#define NET_IF_ETH_WIFI     0x01    /* Ethernet wireless interface */
#define NET_IF_ETH_USB      0x02    /* Ethernet USB interface */

/* Standard interface flags */
#define NET_IF_UP           0x1     /* interface is up */
#define NET_IF_BROADCAST    0x2     /* broadcast address valid */
#define NET_IF_NOARP        0x4     /* no ARP protocol */
#define NET_IF_PROMISC      0x8     /* receive all packets */
#define NET_IF_ALLMULTI     0x10    /* receive all multicast packets */

/* Device state change notification index */
#define NET_NOTIFY_DEV_UP          0x0001  /* device is up */
#define NET_NOTIFY_DEV_DOWN        0x0002  /* device is down */
#define NET_NOTIFY_DEV_LINK_UP     0x0003  /* link is up */
#define NET_NOTIFY_DEV_LINK_DOWN   0x0004  /* link is down */
#define NET_NOTIFY_DEV_XMIT_ERR    0x0005  /* device xmit enqueue failure */

//#ifndef ETH_ALEN
//#define ETH_ALEN            6       // Ethernet address length
//#endif

/*
 * When setting up receive packets that an ethernet device will DMA into, 
 * we typically reserve NET_IP_ALIGN bytes. By default NET_IP_ALIGN is defined 
 * to '2'. This makes it so that, after the ethernet header, the protocol 
 * header will be aligned on at least a 4-byte boundary. Nearly all of the 
 * IPV4 and IPV6 protocol processing assumes that the headers are properly 
 * aligned. 
 */
#define NET_IP_ALIGN            2

BOOL NetInitIfRM(void);

#if 0

/* Others */
#define NET_IF_NAME_LEN     16

/*
 *	Device mapping structure.
 */
typedef struct NETIfMap 
{
    u8  irq;
    u32 memstart;
    u32 memend;
    u16 baseaddr; 
    u8  dma;
    u8  port;
} NETIfMap;

struct NETEthTool;
typedef struct NETIfReq
{
    u32     netif;                      /* network interface ID */
    u8      name[NET_IF_NAME_LEN];      /* network interface name */
    union {
        u32     flags;
        struct  SOInAddr addr;          /* network IP address */
        struct  SOInAddr broadAddr;     /* protocol broadcast addr */
        struct  SOInAddr netmask;       /* network mask */
        struct  SOInAddr alias;         /* internet alias address */
        struct  SOInAddr gateway;       /* default gateway */
        struct  SOInAddr dns[2];        /* primary and secondary DNS */
        u8      macAddr[ETH_ALEN];      /* mac address */
        u32     mtu;                    /* mtu setting */
        u32     mru;                    /* mru setting */
        struct  NETIfMap ifMap;         /* device mapping */
        struct  IPInterfaceStat stat;   /* interface statistics */
        s32     cfgErr;                 /* interface config error */
        struct  SOIn6Addr addr6;        /* network IPv6 address */
        struct  NETEthTool ethTool;     /* for Ethernet card */
    } ifru;
} NETIfReq;

/*
 * Interface request structure used for PPPoE
 */
#define NET_USERNAME_LEN        16
#define NET_PASSWD_LEN          16
#define NET_SRVNAME_LEN         32

typedef struct NETIfReqPPPoE
{
    char    userName[NET_USERNAME_LEN];     /* login name */
    char    passwd[NET_PASSWD_LEN];         /* password */
    char    serviceName[NET_SRVNAME_LEN];   /* service name */
    struct  SOInAddr primaryDNS;            /* primary DNS */
    struct  SOInAddr secondaryDNS;          /* secondary DNS */
} NETIfReqPPPoE;

/*
 * Interface request structure used for DHCP
 */
#define NET_HOSTNAME_LEN         32

typedef struct NETIfReqDhcp
{
    char    userName[NET_HOSTNAME_LEN];     /* host name */
    struct  SOInAddr primaryDNS;            /* primary DNS */
    struct  SOInAddr secondaryDNS;          /* secondary DNS */
} NETIfReqDhcp;

#endif

#endif // __IOP_NETIF_H__
