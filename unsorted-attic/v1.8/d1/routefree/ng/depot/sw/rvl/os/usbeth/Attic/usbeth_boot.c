#ident "$Id: usbeth_boot.c,v 1.7 2006/05/23 00:33:02 psmith Exp $"
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
#include <iop_netif.h>

#define NOPEN 5
#define NUP 2
#define NPKT 3

#define TEST(expr,msg) \
   if ( !(expr) ) { \
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

void
printStats(IPInterfaceStat *stats)
{
    printf("stats:\n");
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

int 
testProc(u32 arg)
{
    IOSFd ueFd;
    int ipkt;
    int iopen;
    int iup;

    IOSIoVector v[2];
    IOSIobuf *txIob;
    u8 *txPkt;
    IOSIobDebugInfo iobufDebugInfo;
    
    IOSError rv = IOS_ERROR_OK;
    IPInterfaceStat stats;

    printf("testProc: NOPEN=%d, NUP=%d, NPKT=%d\n",NOPEN,NUP,NPKT);
    
    for (iopen=0; iopen<NOPEN; iopen++) {
        
        printf("**************** iopen = %d ****************\n",iopen);
        
        printf ("opening usbeth driver\n");
        ueFd = rv = IOS_Open("/dev/net/usbeth/top",0);
        TEST(rv >= 0,"open");
        
        u8 mac[ETH_ALEN];
        v[0].base = (u8 *) &mac;
        v[0].length = ETH_ALEN;
//        printf("%s: NET_DEV_GET_MAC_ADDRESS entry\n", __FUNCTION__);
        rv = IOS_Ioctlv(ueFd, NET_DEV_GET_MAC_ADDRESS, 0, 1, v);
//        printf("%s: NET_DEV_GET_MAC_ADDRESS exit\n", __FUNCTION__);
        TEST(rv == 0,"get mac address");
        printf("MAC = %d:%d:%d:%d:%d:%d (0x%02x:%02x:%02x:%02x:%02x:%02x)\n",
               mac[0],mac[1],mac[2],mac[3],mac[4],mac[5],
               mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
        
        for (iup=0; iup<NUP; iup++) {
            
            printf("================ iup = %d ================\n",iup);
            
            struct NETEthTool et;
            v[0].base = (u8 *) &et;
            v[0].length = sizeof(NETEthTool);
//            printf("%s: NET_DEV_GET_ETHTOOL entry\n", __FUNCTION__);
            rv = IOS_Ioctlv(ueFd, NET_DEV_GET_ETHTOOL, 0, 1, v);
//            printf("%s: NET_DEV_GET_ETHTOOL exit\n", __FUNCTION__);
            TEST(rv == 0,"get ethTool");
            
            printf("NETEthTool:\n");
            printf("   supported = 0x%x\n",et.supported);
            printf("   advertising = 0x%x\n",et.advertising);
            printf("   speed = 0x%x (%s)\n",et.speed,(et.speed & NET_SPEED_10) ? "10 MHz" : "100 MHz");
            printf("   duplex = 0x%x (%s)\n",et.duplex,(et.duplex & NET_DUPLEX_FULL) ? "full" : "half");
            printf("   autoneg = 0x%x\n",et.autoneg);
            
//            printf("%s: NET_DEV_UP entry\n", __FUNCTION__);
            rv = IOS_Ioctlv(ueFd, NET_DEV_UP, 0, 0, 0);
//            printf("%s: NET_DEV_UP exit\n", __FUNCTION__);
            TEST(rv == 0,"dev up");
            
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
                printStats(&stats);
            }
            
//            printf("%s: NET_DEV_DOWN entry\n", __FUNCTION__);
            rv = IOS_Ioctlv(ueFd, NET_DEV_DOWN, 0, 0, 0);
//            printf("%s: NET_DEV_DOWN exit\n", __FUNCTION__);
            TEST(rv == 0,"dev down");
            
        }

        printf ("closing usbeth driver\n");
        rv = IOS_Close(ueFd);
        TEST(rv >= 0,"close");
        
    }

    printf("%s: PASSED\n", __FUNCTION__);
    
out:
    printf("%s: exiting\n",__FUNCTION__);
    IOS_DestroyThread(0, NULL);
    return 0;
}
