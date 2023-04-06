d1 1
a1 1
#ident "$Id: usbeth_boot.c,v 1.4 2006/05/05 01:23:44 psmith Exp $"
d17 3
d76 1
a76 1
    
d82 4
a85 1
    int i;
d91 1
a91 50
    for (i=0; i<1; i++) {
        printf("entering testProc\n");
    }
    
    printf ("opening usbeth driver\n");
    ueFd = rv = IOS_Open("/dev/net/usbeth/top",0);
    TEST(rv >= 0,"open");
    printf ("open returned rv = %d\n",rv);

    u8 mac[ETH_ALEN];
    v[0].base = (u8 *) &mac;
    v[0].length = ETH_ALEN;
    rv = IOS_Ioctlv(ueFd, NET_DEV_GET_MAC_ADDRESS, 0, 1, v);
    TEST(rv == 0,"get mac address");
    printf("MAC = %d:%d:%d:%d:%d:%d (0x%02x:%02x:%02x:%02x:%02x:%02x)\n",
           mac[0],mac[1],mac[2],mac[3],mac[4],mac[5],
           mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);

    struct NETEthTool et;
    v[0].base = (u8 *) &et;
    v[0].length = sizeof(NETEthTool);
    rv = IOS_Ioctlv(ueFd, NET_DEV_GET_ETHTOOL, 0, 1, v);
    TEST(rv == 0,"get ethTool");

    printf("NETEthTool:\n");
    printf("   supported = 0x%x\n",et.supported);
    printf("   advertising = 0x%x\n",et.advertising);
    printf("   speed = 0x%x (%s)\n",et.speed,(et.speed & NET_SPEED_10) ? "10 MHz" : "100 MHz");
    printf("   duplex = 0x%x (%s)\n",et.duplex,(et.duplex & NET_DUPLEX_FULL) ? "full" : "half");
    printf("   autoneg = 0x%x\n",et.autoneg);
    
    rv = IOS_Ioctlv(ueFd, NET_DEV_UP, 0, 0, 0);
    printf ("NET_DEV_UP, rv = %d\n",rv);
    TEST(rv == 0,"dev up");
  
    rv = IOS_AccessIobPool(POOL_DEFAULT);
    TEST(rv == 0,"access iobuf pool");
    
    txIob = IOS_AllocIob(POOL_DEFAULT, sizeof(pkt)+NET_IP_DRV_RESERVE, iobufDebugInfo);
    TEST(txIob != 0,"tx iobuf alloc")

    IOS_IOB_RESERVE(txIob, NET_IP_DRV_RESERVE);

    txPkt = IOS_PutIob(txIob, sizeof(pkt));
    memcpy( txPkt, pkt, sizeof(pkt));

    v[0].base = (char *) txIob;
    v[0].length = sizeof(*txIob);
    rv = IOS_Ioctlv(ueFd, NET_DEV_XMIT_PKT, 1, 0, v);
    TEST(rv == 0, "send packet");
d93 1
a93 7
    IPInterfaceStat stats;
    
    v[0].base = (u8 *) &stats;
    v[0].length = sizeof(stats);
    rv = IOS_Ioctlv(ueFd, NET_DEV_GET_STATS, 0, 1, v);
    TEST(rv == 0, "get stats");
    printStats(&stats);
d95 79
a173 6
    for (i=0; i<20; i++) {
        usleep(1000*1000); // 1000 msec
        rv = IOS_Ioctlv(ueFd, NET_DEV_GET_STATS, 0, 1, v);
        TEST(rv == 0, "get stats");
        printf("\ni = %d\n",i);
        printStats(&stats);
d175 2
a177 2
    //IOS_DestroyThread(0, NULL);
    //exit(0);
d180 1
