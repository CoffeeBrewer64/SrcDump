#define CABLE
//#define LINK_PARTNER_LINKSYS_EW5HUB
#define LINK_PARTNER_NETGEAR_DS104
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
#include <ioslibc.h>
#include <priority.h>

#include "net_if.h"

#define TEST_STACK_SIZE  (32 * 1024)
#define TEST_PRIORITY  60
const u8 _initStack[TEST_STACK_SIZE];
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = IOS_PRIORITY_USBETH + 2;

/*
 * globals
 */
IOSFd ueFd;
IOSFd ipbFd;


#ifdef CABLE
 #define NOPEN 0
 #define NUP 0
 #define NPKT 0
#else
 #define NOPEN 1
 #define NUP (128*3*2*2)  // 2^7 advertising, 3 speed, 2 duplex, 2 autoneg
 #define NPKT 0
#endif

#define TEST(expr,msg, ...) \
   if ( !(expr) ) { \
      __VA_ARGS__; \
      printf("%s: error: " #expr " failed, rv = %d: %s\n",__FUNCTION__,rv,msg); \
      goto out; \
   }


#if 1
// packet captured by Ethereal -- ARP, Who has 10.0.0.130? Tell 10.0.0.17
u8 pkt[] = {
//    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x0f, 0xb5, 0xbe, 0x67, 0xf2, 0x08, 0x06, 0x00, 0x01,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x16, 0xce, 0x40, 0x75, 0xa4, 0x08, 0x06, 0x00, 0x01,
    0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0x00, 0x0f, 0xb5, 0xbe, 0x67, 0xf2, 0x0a, 0x00, 0x00, 0x11,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x82, 0x33, 0x35, 0x0a, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#else
// packet from ../net/iop_sockrm.c
u8 pkt[] = {
    0x00, 0x0e, 0xc6, 0x00, 
    0x00, 0x66, 0x00, 0x11, 
    0x11, 0xbd, 0xb8, 0x31, 
    0x08, 0x00, 0x00, 0x00, 
    0x45, 0x00, 
    0x00, 0x30, 0x00, 0x00, 
    0x40, 0x00, 0x40, 0x06, 
    0x26, 0x20, 0x0a, 0x00, 
    0x00, 0x88, 0x0a, 0x00, 
    0x00, 0x21, 0x1f, 0x40, 
    0xc0, 0x00, 0x4e, 0x58, 
    0x8c, 0x8b, 0x00, 0x00, 
    0x00, 0x01, 0x70, 0x12, 
    0x16, 0xd0, 0x9d, 0x71, 
    0x00, 0x00, 0x02, 0x04, 
    0x05, 0xb4, 0x01, 0x01, 
    0x04, 0x02
};
#endif

/*
 * these min/max ethernet packet lengths do not including the FCS
 * since hardware automatically adds it and strips it off
 *
 * NOTE: if VLAN support is desired, then add 4 to ETH_MAX_PACKET_SIZE
 */
#define ETH_MIN_PACKET_SIZE  (ETH_HLEN)
#define ETH_MAX_PACKET_SIZE  (ETH_HLEN+1500)

void
printStats(IPInterfaceStat *stats, char *msg)
{
    printf("%s: stats:\n", msg);
    printf("   inUcastPackets     = %d\n",stats->inUcastPackets);
    printf("   inNonUcastPackets  = %d\n",stats->inNonUcastPackets);
    printf("   inDiscards         = %d\n",stats->inDiscards);
    printf("   inErrors           = %d\n",stats->inErrors);
    printf("   outUcastPackets    = %d\n",stats->outUcastPackets);
    printf("   outNonUcastPackets = %d\n",stats->outNonUcastPackets);
    printf("   outDiscards        = %d\n",stats->outDiscards);
    printf("   outErrors          = %d\n",stats->outErrors);
    printf("   outCollisions      = %d\n",stats->outCollisions);
}

void
resetStats(IPInterfaceStat *stats)
{
    memset(stats, 0, sizeof(IPInterfaceStat));
}

int
compareStats(IPInterfaceStat *expect, IPInterfaceStat *actual, IPInterfaceStat *mask)
{
//    return memcmp(expect, actual, sizeof(IPInterfaceStat));
    if ( (mask->inUcastPackets     && expect->inUcastPackets     != actual->inUcastPackets)     ||
         (mask->inNonUcastPackets  && expect->inNonUcastPackets  != actual->inNonUcastPackets)  ||
         (mask->inDiscards         && expect->inDiscards         != actual->inDiscards)         ||
         (mask->inErrors           && expect->inErrors           != actual->inErrors)           ||
         (mask->outUcastPackets    && expect->outUcastPackets    != actual->outUcastPackets)    ||
         (mask->outNonUcastPackets && expect->outNonUcastPackets != actual->outNonUcastPackets) ||
         (mask->outDiscards        && expect->outDiscards        != actual->outDiscards)        ||
         (mask->outErrors          && expect->outErrors          != actual->outErrors)          ||
         (mask->outCollisions      && expect->outCollisions      != actual->outCollisions)      )
        return 1;
    else
        return 0;
}

int
checkStats(IPInterfaceStat *expect, IPInterfaceStat *mask, IPInterfaceStat *actual)
{
    IPInterfaceStat local_stat, *sp;
    IOSIoVector v[2];
    IOSError rv;

    if ( actual == (IPInterfaceStat *) 0x0 )
        sp = &local_stat;
    else
        sp = actual;
    
    memset(sp, 0xff, sizeof(IPInterfaceStat));
    
    v[0].base = (u8 *) sp;
    v[0].length = sizeof(IPInterfaceStat);

    rv = IOS_Ioctlv(ueFd, NET_DEV_GET_STATS, 0, 1, v);
    TEST(rv == 0, "ioctlv: NET_DEV_GET_STATS");

    rv = compareStats(expect, sp, mask);
    TEST(rv == 0, "compareStats",
         printStats(expect, "expected");
         printStats(sp, "actual");
         printStats(mask, "mask");
        );

    return 0;
    
out:
    return 1;
}

void
printInfo(NetIfInfo *info, char *msg)
{
    printf("%s: info:\n", msg);
    printf("   ip_notify   = %d\n",info->ip_notify);
    printf("   up          = %d\n",info->up);
    printf("   down        = %d\n",info->down);
    printf("   xmit_error  = %d\n",info->xmit_error);
}

void
resetInfo(NetIfInfo *info)
{
    memset(info, 0, sizeof(NetIfInfo));
}

int
compareInfo(NetIfInfo *expect, NetIfInfo *actual, NetIfInfo *mask)
{
    // return memcmp(expect, actual, sizeof(NetIfInfo));
    if ( (mask->up && expect->up != actual->up) ||
         (mask->down && expect->down != actual->down) ||
         (mask->xmit_error && expect->xmit_error != actual->xmit_error) )
        return 1;
    else
        return 0;
}

int
checkInfo(NetIfInfo *expect, NetIfInfo *mask, NetIfInfo *actual)
{
    NetIfInfo local_info, *ip;
    IOSIoVector v[2];
    IOSError rv;

    if ( actual == (NetIfInfo *) 0x0 )
        ip = &local_info;
    else
        ip = actual;
    
    memset(ip, 0xff, sizeof(NetIfInfo));
    
    v[0].base = (u8 *) ip;
    v[0].length = sizeof(NetIfInfo);

    rv = IOS_Ioctlv(ipbFd, DUMMY_NET_IP_GET_INFO, 0, 1, v);
    TEST(rv == 0, "ioctlv: DUMMY_NET_IP_GET_INFO ioctlv");

    rv = compareInfo(expect, ip, mask);
    TEST(rv == 0, "compareInfo",
         printInfo(expect, "expected");
         printInfo(ip, "actual");
         printInfo(mask, "mask");
        );

    return 0;
    
out:
    return 1;
}

void
printNETEthTool(NETEthTool *et, char *msg)
{
    printf("%s: NETEthTool:\n", msg);
    printf("   supported = 0x%x (",et->supported);
    if ( et->supported & NET_SUPPORTED_AUTONEG )
        printf(" autoneg");
    if ( et->supported & NET_SUPPORTED_1000BASET_FULL )
        printf(" 1000-full");
    if ( et->supported & NET_SUPPORTED_1000BASET_HALF )
        printf(" 1000-half");
    if ( et->supported & NET_SUPPORTED_100BASET_FULL )
        printf(" 100-full");
    if ( et->supported & NET_SUPPORTED_100BASET_HALF )
        printf(" 100-half");
    if ( et->supported & NET_SUPPORTED_10BASET_FULL )
        printf(" 10-full");
    if ( et->supported & NET_SUPPORTED_10BASET_HALF )
        printf(" 10-half");
    printf(")\n");
    printf("   advertising = 0x%x (",et->advertising);
    if ( et->advertising & NET_SUPPORTED_AUTONEG )
        printf(" autoneg");
    if ( et->advertising & NET_SUPPORTED_1000BASET_FULL )
        printf(" 1000-full");
    if ( et->advertising & NET_SUPPORTED_1000BASET_HALF )
        printf(" 1000-half");
    if ( et->advertising & NET_SUPPORTED_100BASET_FULL )
        printf(" 100-full");
    if ( et->advertising & NET_SUPPORTED_100BASET_HALF )
        printf(" 100-half");
    if ( et->advertising & NET_SUPPORTED_10BASET_FULL )
        printf(" 10-full");
    if ( et->advertising & NET_SUPPORTED_10BASET_HALF )
        printf(" 10-half");
    printf(")\n");
    printf("   speed = 0x%x (%s)\n",et->speed,
           (et->speed == NET_SPEED_10) ? "10 MHz" :
           (et->speed == NET_SPEED_100) ? "100 MHz" :
           (et->speed == NET_SPEED_1000) ? "1000 MHz" :
           "unknown");
    printf("   duplex = 0x%x (%s)\n",et->duplex,
           (et->duplex == NET_DUPLEX_FULL) ? "full" :
           (et->duplex == NET_DUPLEX_HALF) ? "half" :
           "unknown");
    printf("   autoneg = 0x%x\n",et->autoneg);
 
}

void
setNETEthTool(NETEthTool *et, u32 advertising, u32 speed, u32 duplex, u32 autoneg)
{
/*
    et->supported = 0x0;
    
    if ( supported & 0x1 ) 
        et->supported |= NET_SUPPORTED_AUTONEG;
    if ( supported & 0x2 )
        et->supported |= NET_SUPPORTED_100BASET_FULL;
    if ( supported & 0x4 )
         et->supported |= NET_SUPPORTED_100BASET_HALF;
    if ( supported & 0x8 )
         et->supported |= NET_SUPPORTED_10BASET_FULL;
    if ( supported & 0x10 )
         et->supported |= NET_SUPPORTED_10BASET_HALF;
*/
    et->advertising = 0x0;

    if ( advertising & 0x1 )
         et->supported |= NET_SUPPORTED_AUTONEG;
    if ( advertising & 0x2 )
         et->advertising |= NET_SUPPORTED_1000BASET_FULL;
    if ( advertising & 0x4 )
         et->advertising |= NET_SUPPORTED_1000BASET_HALF;
    if ( advertising & 0x8 )
         et->advertising |= NET_SUPPORTED_100BASET_FULL;
    if ( advertising & 0x10 )
         et->advertising |= NET_SUPPORTED_100BASET_HALF;
    if ( advertising & 0x20 )
         et->advertising |= NET_SUPPORTED_10BASET_FULL;
    if ( advertising & 0x40 )
         et->advertising |= NET_SUPPORTED_10BASET_HALF;

    et->speed = speed;
    et->duplex = duplex;
    et->autoneg = autoneg;
}

int
validNETEthTool(NETEthTool *et)
{
    int valid = 0;

    if ( et->advertising & ~et->supported ) {
        // invalid
    } else if ( et->autoneg && ~(et->advertising & NET_SUPPORTED_AUTONEG) ) {
        // invalid
    } else if ( et->autoneg ) {
        valid = 1;
    } else if ( !et->autoneg ) {
        
        if ( et->speed == NET_SPEED_1000 &&
             et->duplex == NET_DUPLEX_FULL &&
             (et->supported & NET_SUPPORTED_1000BASET_FULL) ) {
            valid = 1;
        } else if ( et->speed == NET_SPEED_1000 &&
                    et->duplex == NET_DUPLEX_HALF &&
                    (et->supported & NET_SUPPORTED_1000BASET_HALF) ) {
            valid = 1;
        } else if ( et->speed == NET_SPEED_100 &&
             et->duplex == NET_DUPLEX_FULL &&
             (et->supported & NET_SUPPORTED_100BASET_FULL) ) {
            valid = 1;
        } else if ( et->speed == NET_SPEED_100 &&
                    et->duplex == NET_DUPLEX_HALF &&
                    (et->supported & NET_SUPPORTED_100BASET_HALF) ) {
            valid = 1;
        } else if ( et->speed == NET_SPEED_10 &&
                    et->duplex == NET_DUPLEX_FULL &&
                    (et->supported & NET_SUPPORTED_10BASET_FULL) ) {
            valid = 1;
        } else if ( et->speed == NET_SPEED_10 &&
                    et->duplex == NET_DUPLEX_HALF &&
                    (et->supported & NET_SUPPORTED_10BASET_HALF) ) {
            valid = 1;
        }
        
    }

    return valid;
}


int
predictNETEthTool(NETEthTool *self, NETEthTool *partner, NETEthTool *expect)
{
    int link = 0;

    if (self->autoneg && partner->autoneg) {
        link = 1;
        expect->advertising = self->advertising & partner->advertising;
        if ( expect->advertising & NET_SUPPORTED_1000BASET_FULL ) {
            expect->speed = NET_SPEED_1000;
            expect->duplex = NET_DUPLEX_FULL;
        } else if ( expect->advertising & NET_SUPPORTED_1000BASET_HALF ) {
            expect->speed = NET_SPEED_1000;
            expect->duplex = NET_DUPLEX_HALF;
        } else if ( expect->advertising & NET_SUPPORTED_100BASET_FULL ) {
            expect->speed = NET_SPEED_100;
            expect->duplex = NET_DUPLEX_FULL;
        } else if ( expect->advertising & NET_SUPPORTED_100BASET_HALF ) {
            expect->speed = NET_SPEED_100;
            expect->duplex = NET_DUPLEX_HALF;
        } else if ( expect->advertising & NET_SUPPORTED_10BASET_FULL ) {
            expect->speed = NET_SPEED_10;
            expect->duplex = NET_DUPLEX_FULL;
        } else if ( expect->advertising & NET_SUPPORTED_10BASET_HALF ) {
            expect->speed = NET_SPEED_10;
            expect->duplex = NET_DUPLEX_HALF;
        } else {
            link = 0;
            expect->speed = ~0; // an invalid value -> trigger an error
            expect->duplex = ~0;// an invalid value -> trigger an error
        }
        
    } else if ( self->autoneg && !partner->autoneg) {

        link = 1;
        if ( partner->supported & NET_SUPPORTED_1000BASET_FULL ) {
            expect->speed = NET_SPEED_1000;
            expect->duplex = NET_DUPLEX_FULL;
        } else if ( partner->supported & NET_SUPPORTED_1000BASET_HALF ) {
            expect->speed = NET_SPEED_1000;
            expect->duplex = NET_DUPLEX_HALF;
        } else  if ( partner->supported & NET_SUPPORTED_100BASET_FULL ) {
            expect->speed = NET_SPEED_100;
            expect->duplex = NET_DUPLEX_FULL;
        } else if ( partner->supported & NET_SUPPORTED_100BASET_HALF ) {
            expect->speed = NET_SPEED_100;
            expect->duplex = NET_DUPLEX_HALF;
        } else if ( partner->supported & NET_SUPPORTED_10BASET_FULL ) {
            expect->speed = NET_SPEED_10;
            expect->duplex = NET_DUPLEX_FULL;
        } else if ( partner->supported & NET_SUPPORTED_10BASET_HALF ) {
            expect->speed = NET_SPEED_10;
            expect->duplex = NET_DUPLEX_HALF;
        } else {
            link = 0;
            expect->speed = ~0; // an invalid value -> trigger an error
            expect->duplex = ~0;// an invalid value -> trigger an error
        }

    } else if ( !self->autoneg ) {

        expect->speed = self->speed;
        expect->duplex = self->duplex;
        
        if ( self->speed == NET_SPEED_1000 &&
             self->duplex == NET_DUPLEX_FULL &&
             (partner->supported & NET_SUPPORTED_1000BASET_FULL) ) {
            link = 1;
        } else if ( self->speed == NET_SPEED_1000 &&
             self->duplex == NET_DUPLEX_HALF &&
             (partner->supported & NET_SUPPORTED_1000BASET_HALF) ) {
            link = 1;
        } else if ( self->speed == NET_SPEED_100 &&
             self->duplex == NET_DUPLEX_FULL &&
             (partner->supported & NET_SUPPORTED_100BASET_FULL) ) {
            link = 1;
        } else if ( self->speed == NET_SPEED_100 &&
             self->duplex == NET_DUPLEX_HALF &&
             (partner->supported & NET_SUPPORTED_100BASET_HALF) ) {
            link = 1;
        } else if ( self->speed == NET_SPEED_10 &&
             self->duplex == NET_DUPLEX_FULL &&
             (partner->supported & NET_SUPPORTED_10BASET_FULL) ) {
            link = 1;
        } else if ( self->speed == NET_SPEED_10 &&
             self->duplex == NET_DUPLEX_HALF &&
             (partner->supported & NET_SUPPORTED_10BASET_HALF) ) {
            link = 1;
        } else {
            link = 0;
            expect->speed = ~0; // an invalid value -> trigger an error
            expect->duplex = ~0;// an invalid value -> trigger an error
        }
        
    }

    return link;
}

    
void
printMacAddr(u8 *mac, char *msg)
{
    printf("%s: MAC = %d:%d:%d:%d:%d:%d (0x%02x:%02x:%02x:%02x:%02x:%02x)\n",
           msg,
           mac[0],mac[1],mac[2],mac[3],mac[4],mac[5],
           mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
}

int 
testProc(u32 arg)
{
    int ipkt;
    int iopen;
    int iup;

    int i;
    
    IOSIoVector v[2];
    IOSIobuf *txIob;
    u8 *txPkt;
    IOSIobDebugInfo iobufDebugInfo;
    
    IOSError rv = IOS_ERROR_OK;
    IPInterfaceStat stats, tmp_stats, expect_stats, mask_stats;
    struct NETEthTool raw_open_et, raw_up_et, tmp_et, tmp_et2;
    struct NETEthTool partner_et = {
#ifdef LINK_PARTNER_LINKSYS_EW5HUB
        NET_SUPPORTED_10BASET_FULL |
        NET_SUPPORTED_10BASET_HALF,   // supported
        0,                            // advertising
        NET_SPEED_10,                 // speed
        NET_DUPLEX_HALF,              // duplex
        0                             // autoneg
#else
#ifdef LINK_PARTNER_NETGEAR_DS104
        (NET_SUPPORTED_100BASET_FULL |
         NET_SUPPORTED_100BASET_HALF |
         NET_SUPPORTED_10BASET_FULL |
         NET_SUPPORTED_10BASET_HALF |
         NET_SUPPORTED_AUTONEG),      // supported
        (NET_SUPPORTED_100BASET_FULL |
         NET_SUPPORTED_100BASET_HALF |
         NET_SUPPORTED_10BASET_FULL |
         NET_SUPPORTED_10BASET_HALF |
         NET_SUPPORTED_AUTONEG),      // advertising
        ~0,                           // speed
        ~0,                           // duplex
        1                             // autoneg
#else
#error Ethernet link partner characteristics not given
#endif
#endif
    };
    
    NetIfInfo ipbInfo, expect_ipbInfo, mask_ipbInfo;
    
    u8 raw_mac[ETH_ALEN];
    u8 set_mac[ETH_ALEN];
    u8 tmp_mac[ETH_ALEN];
    
    // make sure cable is unplugged
#ifdef CABLE
    char cmd[80];
    printf("please unplug the ethernet cable and then press <enter>");
    gets(cmd);
    usleep(1000*1000*2); // sleep until no-link has been detected
#endif
    
    // reset ipb stats
    rv = IOS_Ioctlv(ipbFd, DUMMY_NET_IP_RESET_INFO, 0, 0, v);
    TEST(rv == 0,"reset ipb stats");
    
    // good open
    ueFd = rv = IOS_Open("/dev/net/usbeth/top",0);
    TEST(rv >= 0,"good open -- test 1a/1c");
    
    // bad open (repeat) -- test 1b
    rv = IOS_Open("/dev/net/usbeth/top",0);
    TEST(rv < 0,"bad open (repeat) -- test 1b");

    // good close -- test 2a
    rv = IOS_Close(ueFd);
    TEST(rv == 0,"good close (state = USBETH_STATE_DOWN), test 2a/2b");
   
    // bad close (repeat) -- test 2a
    rv = IOS_Close(ueFd);
    TEST(rv < 0,"bad close (repeat, state = USBETH_STATE_CLOSED), test 2a");

    // good open after close -- test 2b
    ueFd = rv = IOS_Open("/dev/net/usbeth/top",0);
    TEST(rv >= 0,"good open after close -- test 2b");

    // reset stats
    resetStats(&expect_stats);
    resetStats(&mask_stats);

    mask_stats.outUcastPackets = 1;
    mask_stats.outNonUcastPackets = 1;
    mask_stats.outDiscards = 1;
    mask_stats.outErrors = 1;
    mask_stats.outCollisions = 1;
    
    resetInfo(&expect_ipbInfo);
    resetInfo(&mask_ipbInfo);

    mask_ipbInfo.up = 1;
    mask_ipbInfo.down = 1;
    mask_ipbInfo.xmit_error = 1;
    
    // good get ethtool (post-open) -- test 11a/11d
    v[0].base = (u8 *) &raw_open_et;
    v[0].length = sizeof(NETEthTool);
    rv = IOS_Ioctlv(ueFd, NET_DEV_GET_ETHTOOL, 0, 1, v);
    TEST(rv == 0,"good get ethTool (post-open) -- test 11a/11d");

    printNETEthTool(&raw_open_et, "good get ethtool (post-open) -- test 11a/11d");

    // good set ethtool (post-open) -- test 11e/11f
    memcpy(&tmp_et, &raw_open_et, sizeof(NETEthTool));
    if ( raw_open_et.autoneg == NET_AUTONEG_ENABLE ) 
        tmp_et.autoneg = NET_AUTONEG_DISABLE;
    else 
        tmp_et.autoneg = NET_AUTONEG_ENABLE;
    v[0].base = (u8 *) &tmp_et;
    v[0].length = sizeof(NETEthTool);
    rv = IOS_Ioctlv(ueFd, NET_DEV_SET_ETHTOOL, 1, 0, v);
    TEST(rv == 0,"good set ethTool (post-open) -- test 11e/11f");
    
    // good get ethtool (post-open), check that set succeeded -- test 11e/11f
    v[0].base = (u8 *) &tmp_et2;
    v[0].length = sizeof(NETEthTool);
    rv = IOS_Ioctlv(ueFd, NET_DEV_GET_ETHTOOL, 0, 1, v);
    TEST(rv == 0,"good get ethTool (post-open), check that set succeeded -- test 11e/11f");

    rv = memcmp(&tmp_et2, &tmp_et, sizeof(NETEthTool));
    TEST(rv == 0,"good get ethTool (post-open), set did not succeeded -- test 11e/11f",
         printNETEthTool(&tmp_et, "expected");
         printNETEthTool(&tmp_et2, "actual");
        );

    // good set/restore ethtool (post-open) -- test 11e/11f
    v[0].base = (u8 *) &raw_open_et;
    v[0].length = sizeof(NETEthTool);
    rv = IOS_Ioctlv(ueFd, NET_DEV_SET_ETHTOOL, 1, 0, v);
    TEST(rv == 0,"good set/restore ethTool (post-open) -- test 11e/11f");
   
    // good get (post-open), check set/restore -- test 11e/11f
    v[0].base = (u8 *) &tmp_et;
    v[0].length = sizeof(NETEthTool);
    rv = IOS_Ioctlv(ueFd, NET_DEV_GET_ETHTOOL, 0, 1, v);
    TEST(rv == 0,"good get ethTool (post-open), check that set/restore succeeded -- test 11e/11f");

    rv = memcmp(&raw_open_et, &tmp_et, sizeof(NETEthTool));
    TEST(rv == 0,"good get ethTool (post-open), set/restore did not succeeded -- test 11e/11f",
         printNETEthTool(&raw_open_et, "expected");
         printNETEthTool(&tmp_et, "actual");
        );
   
    // bad set ethtool (post-open)
    memcpy(&tmp_et, &raw_open_et, sizeof(raw_open_et));
    tmp_et.supported = ~tmp_et.supported;
    v[0].base = (u8 *) &tmp_et;
    v[0].length = sizeof(NETEthTool);
    rv = IOS_Ioctlv(ueFd, NET_DEV_SET_ETHTOOL, 1, 0, v);

    TEST(rv < 0,"bad set ethTool (post-open)",
         printNETEthTool(&tmp_et, "bad set ethtool (post-open)");
        );
    
    // good get mac addr -- test 8c/8d
    v[0].base = (u8 *) &raw_mac;
    v[0].length = ETH_ALEN;
    rv = IOS_Ioctlv(ueFd, NET_DEV_GET_MAC_ADDRESS, 0, 1, v);
    TEST(rv == 0,"good get mac address");

    printMacAddr(raw_mac, "good get mac address -- test 8c/8d");

    // good set mac addr -- test 7b/7c
    for (i=0; i<ETH_ALEN; i++) { // invert mac addr
        set_mac[i] = ~raw_mac[i]; 
    }
    v[0].base = (u8 *) &set_mac;
    v[0].length = ETH_ALEN;
    rv = IOS_Ioctlv(ueFd, NET_DEV_SET_MAC_ADDRESS, 1, 0, v);
    TEST(rv == 0,"good set mac address -- test 7b/7c");

    printMacAddr(set_mac, "good set mac address -- test 7b/7c");

    // good get mac addr, check that set succeeded -- test 7b/7c
    v[0].base = (u8 *) &tmp_mac;
    v[0].length = ETH_ALEN;
    rv = IOS_Ioctlv(ueFd, NET_DEV_GET_MAC_ADDRESS, 0, 1, v);
    TEST(rv == 0,"good get mac address, check that set succeeded -- test 7b/7c");

    printMacAddr(tmp_mac, "good get mac address, check that set succeeded -- test 7b/7c");

    rv = memcmp(tmp_mac, set_mac, ETH_ALEN);
    TEST(rv == 0,"good get mac address, set did not succeed -- test 7b/7c");
    
    // bad xmit (not up) -- test 3f
    txIob = IOS_AllocIob(POOL_DEFAULT, sizeof(pkt)+NET_IP_DRV_RESERVE, iobufDebugInfo);
    TEST(txIob != 0,"tx iobuf alloc, bad xmit (not up) -- test 3f");
                
    IOS_IOB_RESERVE(txIob, NET_IP_DRV_RESERVE);
    
    txPkt = IOS_PutIob(txIob, ETH_MIN_PACKET_SIZE-1);
    memcpy( txPkt, pkt, ETH_MIN_PACKET_SIZE-1);
    
    v[0].base = (char *) txIob;
    v[0].length = sizeof(*txIob);
    rv = IOS_Ioctlv(ueFd, NET_DEV_XMIT_PKT, 1, 0, v);
    TEST(rv < 0, "send packet, bad xmit (not up) -- test 3f");

    rv = IOS_FreeIob(txIob);
    TEST(rv == 0, "send packet, bad xmit (not up) -- test 3f, free iob failed");

    expect_stats.outErrors++;
    expect_ipbInfo.xmit_error++;
    
    // bad xmit (not up), check NET_IP_NOTIFY sent -- test 3e
    rv = checkInfo(&expect_ipbInfo, &mask_ipbInfo, &ipbInfo);
    TEST(rv == 0, "bad xmit (not up), check NET_IP_NOTIFY sent -- test 3e");

#ifdef CABLE
    // bad up (no cable) -- test 4c
    rv = IOS_Ioctlv(ueFd, NET_DEV_UP, 0, 0, 0);
    TEST(rv < 0,"bad up (no cable) -- test 4c");

    // bad up (no cable), check NET_IP_NOTIFY sent -- test 4c
    rv = checkInfo(&expect_ipbInfo, &mask_ipbInfo, &ipbInfo);
    TEST(rv == 0, "bad up (no cable), check NET_IP_NOTIFY sent -- test 4c");

    // insert cable
    printf("please plug in the ethernet cable and then press <enter>");
    gets(cmd);
#endif
    
    // good up
    rv = IOS_Ioctlv(ueFd, NET_DEV_UP, 0, 0, 0);
    TEST(rv == 0,"good up -- test 1a/1c");

    expect_ipbInfo.up++;
    
    // good up, check NET_IP_NOTIFY sent -- test 4b
    rv = checkInfo(&expect_ipbInfo, &mask_ipbInfo, &ipbInfo);
    TEST(rv == 0, "good up, check NET_IP_NOTIFY sent -- test 4b");

    // unplug cable again
#ifdef CABLE
    printf("please unplug the ethernet cable and then press <enter>");
    gets(cmd);
    usleep(1000*1000*2); // sleep until no-link has been detected

    expect_ipbInfo.down++;
#endif
    
    // bad up, repeat -- test 4a
    rv = IOS_Ioctlv(ueFd, NET_DEV_UP, 0, 0, 0);
    TEST(rv < 0,"bad up, repeat -- test 4a");
            
    // bad up, check NET_IP_NOTIFY not sent -- test 4b
    rv = checkInfo(&expect_ipbInfo, &mask_ipbInfo, &ipbInfo);
    TEST(rv == 0, "bad up, check NET_IP_NOTIFY not sent -- test 4b");

    // good get ethtool (post-up)
    v[0].base = (u8 *) &raw_up_et;
    v[0].length = sizeof(NETEthTool);
    rv = IOS_Ioctlv(ueFd, NET_DEV_GET_ETHTOOL, 0, 1, v);
    TEST(rv == 0,"good get ethTool (post-up)");

    printNETEthTool(&raw_up_et, "good get ethtool (post-up)");

    // check for access to IOB's
    rv = IOS_AccessIobPool(POOL_DEFAULT);
    TEST(rv == 0,"access iobuf pool");
    
    // good xmit (broadcast) -- test 3a/3g
    txIob = IOS_AllocIob(POOL_DEFAULT, sizeof(pkt)+NET_IP_DRV_RESERVE, iobufDebugInfo);
    TEST(txIob != 0,"tx iobuf alloc, good xmit (broadcast) -- test 3a/3g");
                
    IOS_IOB_RESERVE(txIob, NET_IP_DRV_RESERVE);
    
    txPkt = IOS_PutIob(txIob, sizeof(pkt));
    memcpy( txPkt, pkt, sizeof(pkt));
    
    v[0].base = (char *) txIob;
    v[0].length = sizeof(*txIob);
    rv = IOS_Ioctlv(ueFd, NET_DEV_XMIT_PKT, 1, 0, v);

#ifdef CABLE
    TEST(rv < 0, "send packet, good xmit (broadcast) -- test 3g");

    expect_stats.outErrors++;
    expect_ipbInfo.xmit_error++;
#else
    TEST(rv == 0, "send packet, good xmit (broadcast) -- test 3a");

    expect_stats.outNonUcastPackets++;
#endif
    
    // good xmit (unicast) -- test 3a/3g
    txIob = IOS_AllocIob(POOL_DEFAULT, sizeof(pkt)+NET_IP_DRV_RESERVE, iobufDebugInfo);
    TEST(txIob != 0,"tx iobuf alloc, good xmit (unicast) -- test 3a/3g");
                
    IOS_IOB_RESERVE(txIob, NET_IP_DRV_RESERVE);
    
    txPkt = IOS_PutIob(txIob, sizeof(pkt));
    memcpy( txPkt, pkt, sizeof(pkt));
    memcpy( txPkt, raw_mac, sizeof(raw_mac));
    
    v[0].base = (char *) txIob;
    v[0].length = sizeof(*txIob);
    rv = IOS_Ioctlv(ueFd, NET_DEV_XMIT_PKT, 1, 0, v);

#ifdef CABLE
    TEST(rv < 0, "send packet, good xmit (unicast) -- test 3g");

    expect_stats.outErrors++;
    expect_ipbInfo.xmit_error++;
#else
    TEST(rv == 0, "send packet, good xmit (unicast) -- test 3a");

    expect_stats.outUcastPackets++;
#endif
    
    // bad xmit (too short) -- test 3b
    txIob = IOS_AllocIob(POOL_DEFAULT, sizeof(pkt)+NET_IP_DRV_RESERVE, iobufDebugInfo);
    TEST(txIob != 0,"tx iobuf alloc, bad xmit (too short) -- test 3b");
                
    IOS_IOB_RESERVE(txIob, NET_IP_DRV_RESERVE);
    
    txPkt = IOS_PutIob(txIob, ETH_MIN_PACKET_SIZE-1);
    memcpy( txPkt, pkt, ETH_MIN_PACKET_SIZE-1);
    
    v[0].base = (char *) txIob;
    v[0].length = sizeof(*txIob);
    rv = IOS_Ioctlv(ueFd, NET_DEV_XMIT_PKT, 1, 0, v);
    TEST(rv < 0, "send packet, bad xmit (too short) -- test 3b");

    rv = IOS_FreeIob(txIob);
    TEST(rv == 0, "send packet, bad xmit (too short) -- test 3b, free iob failed");
    
    expect_stats.outErrors++;
    expect_ipbInfo.xmit_error++;

    // bad xmit (too short), check NET_IP_NOTIFY sent -- test 3e
    rv = checkInfo(&expect_ipbInfo, &mask_ipbInfo, &ipbInfo);
    TEST(rv == 0, "bad xmit (too short), check NET_IP_NOTIFY sent -- test 3e");

    // bad xmit (too long) -- test 3c
    txIob = IOS_AllocIob(POOL_DEFAULT, ETH_MAX_PACKET_SIZE+1+NET_IP_DRV_RESERVE, iobufDebugInfo);
    TEST(txIob != 0,"tx iobuf alloc, bad xmit (too long) -- test 3c");
    
    IOS_IOB_RESERVE(txIob, NET_IP_DRV_RESERVE);
    
    txPkt = IOS_PutIob(txIob, ETH_MAX_PACKET_SIZE+1);
    memset( txPkt, 0, ETH_MAX_PACKET_SIZE+1);
    memcpy( txPkt, pkt, sizeof(pkt));
    
    v[0].base = (char *) txIob;
    v[0].length = sizeof(*txIob);
    rv = IOS_Ioctlv(ueFd, NET_DEV_XMIT_PKT, 1, 0, v);
    TEST(rv < 0, "send packet, bad xmit (too long) -- test 3c");

    rv = IOS_FreeIob(txIob);
    TEST(rv == 0, "send packet, bad xmit (too long) -- test 3c, free iob failed");

    expect_stats.outErrors++;
    expect_ipbInfo.xmit_error++;

    // bad xmit (too long), check NET_IP_NOTIFY sent -- test 3e
    rv = checkInfo(&expect_ipbInfo, &mask_ipbInfo, &ipbInfo);
    TEST(rv == 0, "bad xmit (too long), check NET_IP_NOTIFY sent -- test 3e");

    // bad xmit (no reserve) -- test 3e
    txIob = IOS_AllocIob(POOL_DEFAULT, sizeof(pkt)+NET_IP_DRV_RESERVE, iobufDebugInfo);
    TEST(txIob != 0,"tx iobuf alloc, bad xmit (no reserve) -- test 3e");
    
    // omit reserve -- IOS_IOB_RESERVE(txIob, NET_IP_DRV_RESERVE);
    
    txPkt = IOS_PutIob(txIob, sizeof(pkt));
    memcpy( txPkt, pkt, sizeof(pkt));
    
    v[0].base = (char *) txIob;
    v[0].length = sizeof(*txIob);
    rv = IOS_Ioctlv(ueFd, NET_DEV_XMIT_PKT, 1, 0, v);
    TEST(rv <= 0, "send packet, bad xmit (no reserve) -- test 3e");

    rv = IOS_FreeIob(txIob);
    TEST(rv == 0, "send packet, bad xmit (no reserve) -- test 3e, free iob failed");

#ifdef CABLE
    expect_stats.outErrors++;
#else
    expect_stats.outDiscards++;
#endif
    expect_ipbInfo.xmit_error++;

    // bad xmit (no reserve), check NET_IP_NOTIFY sent -- test 3e
    rv = checkInfo(&expect_ipbInfo, &mask_ipbInfo, &ipbInfo);
    TEST(rv == 0, "bad xmit (no reserve), check NET_IP_NOTIFY sent -- test 3e");

    // get stats, check xmit success and error -- test 3c
    rv = checkStats(&expect_stats, &mask_stats, &stats);
    TEST(rv == 0, "get stats, check xmit success and error -- test 3c");
    
    // good down -- test 5d/5e
    rv = IOS_Ioctlv(ueFd, NET_DEV_DOWN, 0, 0, 0);
    TEST(rv == 0,"good down -- test 5d/5e");

    expect_ipbInfo.down++;
    
    // good down, check NET_IP_NOTIFY sent -- test 5b/5e
    rv = checkInfo(&expect_ipbInfo, &mask_ipbInfo, &ipbInfo);
    TEST(rv == 0, "good down, check NET_IP_NOTIFY sent -- test 5b/5e");
    
    // bad down, repeat -- test 5a
    rv = IOS_Ioctlv(ueFd, NET_DEV_DOWN, 0, 0, 0);
    TEST(rv < 0,"bad down, repeat -- test 5a");

    // bad down, check NET_IP_NOTIFY not sent -- test 5b
    rv = checkInfo(&expect_ipbInfo, &mask_ipbInfo, &ipbInfo);
    TEST(rv == 0, "bad down, check NET_IP_NOTIFY not sent -- test 5b");
    
    // insert cable
#ifdef CABLE
    printf("please plug in the ethernet cable and then press <enter>");
    gets(cmd);
#endif
    
    // good up after down
    rv = IOS_Ioctlv(ueFd, NET_DEV_UP, 0, 0, 0);
    TEST(rv == 0,"good up after down");

    expect_ipbInfo.up++;
    
    // good up after down, check NET_IP_NOTIFY sent -- test 4b
    rv = checkInfo(&expect_ipbInfo, &mask_ipbInfo, &ipbInfo);
    TEST(rv == 0, "good up after down, check NET_IP_NOTIFY sent -- test 4b");
    
    // unplug cable again
#ifdef CABLE
    printf("please unplug the ethernet cable and then press <enter>");
    gets(cmd);
    usleep(1000*1000*2); // sleep until no-link has been detected
    
    expect_ipbInfo.down++;
#endif
    
    // good get mac addr, persistent across down/up -- test 7a+8a
    memset(tmp_mac, 0, ETH_ALEN);
    v[0].base = (u8 *) &tmp_mac;
    v[0].length = ETH_ALEN;
    rv = IOS_Ioctlv(ueFd, NET_DEV_GET_MAC_ADDRESS, 0, 1, v);
    TEST(rv == 0, "good get mac addr, persistent across down/up -- test 7a+8a");

    printMacAddr(tmp_mac, "good get mac addr, persistent across down/up -- test 7a+8a");

    rv = memcmp(tmp_mac, set_mac, ETH_ALEN);
    TEST(rv == 0, "good get mac addr, persistent across down/up -- test 7a+8a did not succeed");
    
    // good get ethtool (post-up), persistent across down/up -- test 11a
    v[0].base = (u8 *) &tmp_et;
    v[0].length = sizeof(NETEthTool);
    rv = IOS_Ioctlv(ueFd, NET_DEV_GET_ETHTOOL, 0, 1, v);
    TEST(rv == 0,"good get ethTool (post-up)");

    printNETEthTool(&tmp_et, "good get ethtool (post-up), persistent across down/up -- test 11a");

    rv = memcmp(&tmp_et, &raw_up_et, sizeof(raw_up_et));
    TEST(rv == 0, "good get ethTool (post-up), persistent across down/up -- test 11a, compare failed");

    // good get stats, persistent across down/up -- test 9a
    rv = checkStats(&expect_stats, &mask_stats, &stats);
    TEST(rv == 0, "good get stats, persistent across down/up -- test 9a");
     
    // good close with auto-down, test 2a+5c
    rv = IOS_Close(ueFd);
    TEST(rv == 0,"close from state=USBETH_STATE_UP, test 2a+5c");

    expect_ipbInfo.down++;
    
    // good auto-down, check NET_IP_NOTIFY sent -- test 5b
    rv = checkInfo(&expect_ipbInfo, &mask_ipbInfo, &ipbInfo);
    TEST(rv == 0, "good auto-down, check NET_IP_NOTIFY sent -- test 5b");

    //
    //
    //

    printf("testProc: NOPEN=%d, NUP=%d, NPKT=%d\n",NOPEN,NUP,NPKT);
    
    for (iopen=0; iopen<NOPEN; iopen++) {
        
        printf("**************** iopen = %d ****************\n",iopen);
        
        printf ("opening usbeth driver\n");
        ueFd = rv = IOS_Open("/dev/net/usbeth/top",0);
        TEST(rv >= 0,"open -- test 2b");

        // good get mac addr, reset across open/close -- test 8b
        u8 mac[ETH_ALEN];
        v[0].base = (u8 *) &mac;
        v[0].length = ETH_ALEN;
//        printf("%s: NET_DEV_GET_MAC_ADDRESS entry\n", __FUNCTION__);
        rv = IOS_Ioctlv(ueFd, NET_DEV_GET_MAC_ADDRESS, 0, 1, v);
//        printf("%s: NET_DEV_GET_MAC_ADDRESS exit\n", __FUNCTION__);
        TEST(rv == 0,"good get mac addr, reset across open/close -- test 8b");
        printMacAddr(mac,"good get mac addr, reset across open/close -- test 8b");
        
        rv = memcmp(mac, raw_mac, ETH_ALEN);
        TEST(rv == 0,"good get mac addr, reset across open/close -- test 8b did not succeed");
    
        // good get ethtool (post-open), reset across open/close -- test 11b
        v[0].base = (u8 *) &tmp_et;
        v[0].length = sizeof(NETEthTool);
        rv = IOS_Ioctlv(ueFd, NET_DEV_GET_ETHTOOL, 0, 1, v);
        TEST(rv == 0,"good get ethTool (post-open), reset across open/close -- test 11b");

        printNETEthTool(&tmp_et, "good get ethtool (post-open), reset across open/close -- test 11b");

        rv = memcmp(&tmp_et, &raw_open_et, sizeof(raw_open_et));
        TEST(rv == 0, "good get ethTool (post-open), reset across open/close -- test 11b, compare failed");

        // good get stats, reset across open/close -- test 9b
        memset(&tmp_stats, 0xff, sizeof(tmp_stats));
        v[0].base = (u8 *) &tmp_stats;
        v[0].length = sizeof(tmp_stats);
        rv = IOS_Ioctlv(ueFd, NET_DEV_GET_STATS, 0, 1, v);
        TEST(rv == 0, "good get stats, reset across open/close -- test 9b");
        printStats(&tmp_stats,"good get stats, reset across open/close -- test 9b");

        if ( tmp_stats.inUcastPackets ||
             tmp_stats.inNonUcastPackets ||
             tmp_stats.inDiscards ||
             tmp_stats.inErrors ||
             tmp_stats.outUcastPackets ||
             tmp_stats.outNonUcastPackets ||
             tmp_stats.outDiscards ||
             tmp_stats.outErrors ||
             tmp_stats.outCollisions )
            rv = 1;
        else
            rv = 0;

        TEST(rv == 0, "good get stats, reset across open/close -- test 9b, compare failed");

        for (iup=0; iup<NUP; iup++) {
            
            printf("================ iup = %d ================\n",iup);

            char msg[80];

            int nadv = iup & 0x1f;
            int ndup = (iup>>5) & 0x1;
            int nauto = (iup>>6) & 0x1;
            int nspd = (iup>>7) % 3;

            ndup = (ndup == 0) ? NET_DUPLEX_HALF:
                NET_DUPLEX_FULL;
            nspd = (nspd == 0) ? NET_SPEED_10:
                (nspd == 1) ? NET_SPEED_100:
                NET_SPEED_1000;
            
            struct NETEthTool et, expect_et;
            memcpy( &et, &raw_up_et, sizeof(raw_up_et));

            setNETEthTool(&et, nadv, nspd, ndup, nauto);
    
            v[0].base = (u8 *) &et;
            v[0].length = sizeof(NETEthTool);
            rv = IOS_Ioctlv(ueFd, NET_DEV_SET_ETHTOOL, 1, 0, v);

            if ( validNETEthTool(&et) ) {
                TEST(rv == 0,"good set ethTool",
                     snprintf(msg, sizeof(msg), "setting ETH: iup=%d, nadv=%d, ndup=%d, nauto=%d, nspd=%d",
                              iup, nadv, ndup, nauto, nspd);
                     printNETEthTool(&et, msg);
                    );
            } else {
                TEST(rv < 0, "bad set ethtool",
                     snprintf(msg, sizeof(msg), "setting ETH: iup=%d, nadv=%d, ndup=%d, nauto=%d, nspd=%d",
                              iup, nadv, ndup, nauto, nspd);
                     printNETEthTool(&et, msg);
                    );
                continue; // skip to next NET_DEV_SET_ETHTOOL
            }

            int expect_good_link_up = predictNETEthTool(&et,&partner_et,&expect_et);
            
//            printf("%s: NET_DEV_UP entry\n", __FUNCTION__);
            rv = IOS_Ioctlv(ueFd, NET_DEV_UP, 0, 0, 0);
//            printf("%s: NET_DEV_UP exit\n", __FUNCTION__);
            if ( expect_good_link_up ) {
                TEST(rv == 0,"dev up", printNETEthTool(&et, msg););
            } else {
                TEST(rv < 0,"dev up", printNETEthTool(&et, msg););
                continue; // skip to next NET_DEV_SET_ETHTOOL
            }

            // good get ethtool (post-open 2)
            
            v[0].base = (u8 *) &tmp_et;
            v[0].length = sizeof(NETEthTool);
            rv = IOS_Ioctlv(ueFd, NET_DEV_GET_ETHTOOL, 0, 1, v);
            TEST(rv == 0,"good get ethTool (post-open 2)",
                 snprintf(msg, sizeof(msg), "predict ETH: iup=%d, nadv=%d, ndup=%d, nauto=%d, nspd=%d",
                          iup, nadv, ndup, nauto, nspd);
                 printNETEthTool(&expect_et, msg);
                );
            
            rv = tmp_et.speed;
            TEST(rv == expect_et.speed, "good get ethtool (post-open 2), speed mismatch",
                 snprintf(msg, sizeof(msg), "actual ETH: iup=%d, nadv=%d, ndup=%d, nauto=%d, nspd=%d",
                          iup, nadv, ndup, nauto, nspd);
                 printNETEthTool(&tmp_et, msg);
                );

            rv = tmp_et.duplex;
            TEST(rv == expect_et.duplex, "good get ethtool (post-open 2), duplex mismatch",
                 snprintf(msg, sizeof(msg), "actual ETH: iup=%d, nadv=%d, ndup=%d, nauto=%d, nspd=%d",
                          iup, nadv, ndup, nauto, nspd);
                 printNETEthTool(&tmp_et, msg);
                );
            
            // check access to iobuf's
            
            rv = IOS_AccessIobPool(POOL_DEFAULT);
            TEST(rv == 0,"access iobuf pool");
            
            for (ipkt=0; ipkt<NPKT; ipkt++) {
                
                printf("---------------- ipkt = %d ----------------\n",ipkt);
                txIob = IOS_AllocIob(POOL_DEFAULT, sizeof(pkt)+NET_IP_DRV_RESERVE, iobufDebugInfo);
                TEST(txIob != 0,"tx iobuf alloc");
                
                IOS_IOB_RESERVE(txIob, NET_IP_DRV_RESERVE);
                
                txPkt = IOS_PutIob(txIob, sizeof(pkt));
                memcpy( txPkt, pkt, sizeof(pkt));
                
                v[0].base = (char *) txIob;
                v[0].length = sizeof(*txIob);
//                printf("%s: NET_DEV_XMIT_PKT entry\n", __FUNCTION__);
                rv = IOS_Ioctlv(ueFd, NET_DEV_XMIT_PKT, 1, 0, v);
//                printf("%s: NET_DEV_XMIT_PKT exit\n", __FUNCTION__);
                TEST(rv == 0, "send packet");
                
                usleep(1000*1000); // 1000 msec
                
                v[0].base = (u8 *) &stats;
                v[0].length = sizeof(stats);
//                printf("%s: NET_DEV_GET_STATS entry\n", __FUNCTION__);
                rv = IOS_Ioctlv(ueFd, NET_DEV_GET_STATS, 0, 1, v);
//                printf("%s: NET_DEV_GET_STATS exit\n", __FUNCTION__);
                TEST(rv == 0, "get stats");
                printStats(&stats, "get stats");
            }

//            printf("%s: NET_DEV_DOWN entry\n", __FUNCTION__);
            rv = IOS_Ioctlv(ueFd, NET_DEV_DOWN, 0, 0, 0);
//            printf("%s: NET_DEV_DOWN exit\n", __FUNCTION__);
            TEST(rv == 0,"dev down");
            
        }
        
        printf ("closing usbeth driver\n");
        rv = IOS_Close(ueFd);
        TEST(rv >= 0,"close from state=USBETH_STATE_DOWN, test 2a");
        
    }
    
    printf("%s: PASSED\n", __FUNCTION__);
    
out:
    printf("%s: exiting\n",__FUNCTION__);
//    IOS_DestroyThread(0, NULL);
    return 0;
}

int
main(void)
{
    IOSError rv;
    IOSThreadId tid;
    
    // start dummy net if RM
    printf("%s: starting dummy net_if thread\n", __FUNCTION__);
    tid = rv = NetInitIfRM();
    if ( rv < 0 ) {
        printf("%s: failed to start net_if RM\n", __FUNCTION__);
        goto out;
    }
    printf("%s: dummy net_if thread started, tid = %d\n", __FUNCTION__, tid);

    // adjust priority down so it's below that of usbeth and dummy net if
    IOSThreadId self = IOS_GetThreadId();
    if ( (rv = IOS_SetThreadPriority(self, IOS_PRIORITY_USBETH-2)) < 0 ) {
        printf("%s: unable to lower thread priority rv = %d\n", __FUNCTION__, rv);
        goto out;
    }
    
    // open dummy net if RM
    if ( (ipbFd = rv = IOS_Open(NET_RM_IP_BOT, 0)) < 0 ) {
        printf("%s: %s open failed with rv = %d\n", __FUNCTION__, NET_RM_IP_BOT, rv);
        goto out;
    }

    // run test
    printf("%s: starting test\n", __FUNCTION__);
    rv = testProc(0);
    printf("%s: test complete\n", __FUNCTION__);

    // close dummy net if RM
    if ( ipbFd >= 0 && (rv = IOS_Close(ipbFd)) != IOS_ERROR_OK ) {
        printf("%s: unable to close IP stack connection, rv = %d\n", __FUNCTION__, rv);
        goto out;
    }

out:
    return 0;
}
