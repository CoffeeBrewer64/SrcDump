d231 1
a231 2
static u8 buf[5120] __attribute__((aligned(4096)));
#if 0
d238 1
a238 1
//    IOSMessage msg;
d242 2
a243 2
    u16 buflen = 2048;
    u16 pktsize = 784;
d250 5
a254 90
            rv = IUSB_IsoMsgAsync(fd0, &ep, &buflen, buf,
                    &pktsize, qid, &reply, vecBuf);
//            if (rv < 0) {
//                printf("iso write msg async failed: %d\n", rv);
//            }
            usleep(200);
//            IOS_ReceiveMessage(qid, &msg, IOS_MESSAGE_BLOCK);
//        printf("cmd = %u status = %d\n", reply[i].cmd, reply[i].status);
    }

}
#endif
void
__initPacketSize(u16 *packetSize, u8 numpackets)
{
        packetSize[0] = 784;
        packetSize[1] = 128;
        packetSize[2] = 128;
        packetSize[3] = 128;
        packetSize[4] = 256;
        packetSize[5] = 128;
        packetSize[6] = 128;
        packetSize[7] = 368 ;

}

u8 vecBuf[1024];
u8 vecBuf1[1024];
u8 vecBuf2[1024];
u16 packetSize[8];
u16 packetSize1[8];
u16 packetSize2[8];
void
__isoTest(IOSFd fd0)
{
    u8 ep = 0x06;
    u16 buflen = 2048;
    u8 numPackets = 8;
    //    u8 i;

    IOSError rv; 
    IOSMessage msgQ[8];
    IOSMessage msg;
    IOSMessageQueueId qid;
    IOSResourceRequest reply; 

    qid = IOS_CreateMessageQueue(msgQ, 8);
    printf("iso test: %p\n", buf);
   
    { 
        __initPacketSize(packetSize, 8);
        __initPacketSize(packetSize1, 8);
        __initPacketSize(packetSize2, 8);
        /* Initialize buffer */
        char *b = buf + 3*1024;
        memset(b, 0xab, packetSize[0]);
        b += packetSize[0];
        memset(b, 0xcd, packetSize[1]);
        b += packetSize[1];
        memset(b, 0xef, packetSize[2]);
        b += packetSize[2];
        memset(b, 0x12, packetSize[3]);
        b += packetSize[3];
        memset(b, 0x34, packetSize[4]);
        b += packetSize[4];
        memset(b, 0x56, packetSize[5]);
        b += packetSize[5];
        memset(b, 0x78, packetSize[6]);
        b += packetSize[6];
        memset(b, 0x9a, packetSize[7]);
    }
    printf("starting iso OUT transfers\n");
    rv = IUSB_IsoMsgAsync(fd0, &ep, &buflen, buf,
            &numPackets, (u16 *)packetSize1, 
            qid, &reply, vecBuf1);
    printf("enqueing iso xfer returned %d\n", rv);
    while (1) {
        usleep(1000000);
    }
    
    rv = IUSB_IsoMsgAsync(fd0, &ep, &buflen, buf,
            &numPackets, (u16 *)packetSize2, 
            qid, &reply, vecBuf2);
    while (1) 
    {
        char *b = buf + 3*1024;
        rv = IUSB_IsoMsgAsync(fd0, &ep, &buflen, b,
                &numPackets, (u16 *)packetSize, 
                qid, &reply, vecBuf);
        if (rv >= 0) {
d256 1
a256 4
            __initPacketSize(packetSize, 8);
        } else {
            printf("error rv = %d\n", rv);
            usleep(1000);
d277 8
a284 1
    __isoTest(fd0);
