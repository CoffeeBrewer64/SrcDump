d248 8
a255 11
    printf("starting iso OUT transfers\n");
    while (1) {
        rv = IUSB_IsoMsgAsync(fd0, &ep, &buflen, buf,
                &pktsize, qid, &reply, vecBuf);
        if (rv < 0) {
            printf("iso write msg async failed: %d\n", rv);
        } else {
//            printf("waiting for iso write async reply\n");
            IOS_ReceiveMessage(qid, &msg, IOS_MESSAGE_BLOCK);
//            printf("iso write async done\n");
        }
