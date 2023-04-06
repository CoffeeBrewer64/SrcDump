d12 1
a12 1
#ident "$Id: sdio_api.c,v 1.1 2006/03/02 19:02:05 gbarnard Exp $"
d88 2
d92 3
a94 2
	#if 1
		*fd = sdrmQid;	//GB to be completed
d96 3
a98 1
		*fd = IOS_Open(fn, 0);
a100 1
    printf("ISDIO_Open(path = %s): rmQid = %d\n\n", fn, *fd);	
d104 1
d109 16
a124 2
	// --- request resource action ---
	IOSResourceRequest req;
d126 15
a140 8
		// --- sending an ioctl type request ---
		IOSResourceIoctl ioctl;	
		
		ioctl.cmd = cmd;
		ioctl.inLen = input_bytes;
		ioctl.inPtr = (u8*)input; // &slot;
		ioctl.outLen = output_bytes;
		ioctl.outPtr = (u8*)output;
a141 2
	req.cmd = IOS_IOCTL;
	req.args.ioctl = ioctl; 
a142 12
	// --- assemble message ---
	{
		IOSMessage msg;
		//printf("ISDIO_Ioctl -> SDIO RM mq:%d\n",sdrmQid);
		msg = (IOSMessage)&req;
		IOS_SendMessage(sdrmQid, msg, IOS_MESSAGE_NOBLOCK);
		// --- wait for done ---
		IOS_ReceiveMessage(sdrmQidr, &msg, IOS_MESSAGE_BLOCK);
		//printf("ISDIO_Ioctl <- Done Reply\n");
	}
	
	return 0;
d150 1
d156 2
a157 2
IOSError  ISDIO_RegisterResourceManager(IOSCid fd, 
                                    IOSMessageQueueId mq)
d186 2
a187 1
	if (!Handle) {
d228 3
a230 2
	printf("Now assigning handle %x %xto fd=%x\n",DevHandles[devCfg->SDDevSlot][devCfg->SDDevFunc],Handle,fd);
    if (fd) {
d1388 6
a1393 2
    fprintf (stderr, "%s: dev 0x%x function 0x%x not open\n",
             __FUNCTION__, fd->SDDevSlot, fd->SDDevFunc);
d1471 2
a1472 1
        if (fd->SDDevFd < 0) {
d1481 2
a1482 2
        if (debug_level >= DEBUG_CHATTY)
            printf ("%s: linux fd %x\n",
