d20 1
a20 1
#ident "$Id: sdio_rm.c,v 1.1 2006/03/02 19:02:05 gbarnard Exp $"
d110 2
a111 1
    SDIO_LOG(SDIO_OPEN, "%s: '%s' flags 0x%x\n", 
d117 3
a119 1
    if (!strncmp(args->path, SDIO_DEV0, sizeof(SDIO_DEV0)-1)) {
d121 4
a124 1
    } else if (!strncmp(args->path, SDIO_DEV1, sizeof(SDIO_DEV1)-1)) {
d126 3
a128 1
    } else {
d139 5
a143 2
    for (i = 0; i < SDIO_NUM_DESCRIPTORS; ++i) {
        if (!desc[i].inUse) {
d148 3
a150 1
    if (i == SDIO_NUM_DESCRIPTORS) {
d160 2
a161 1
    SDIO_LOG(SDIO_OPEN, "%s: new context handle %08x\n", 
d163 1
a163 1

d330 1
d382 8
a389 3
		//printf("%s RESPOND\n",__FUNCTION__);
        IOS_SendMessage(sdrmQidr, msg, IOS_MESSAGE_NOBLOCK);        
    }
a410 2
	u32 pri = 20; //IOS_GetThreadPriority(0);
	u32 id;
d447 18
a464 9
    
    SDIO_LOG(SDIO_INIT, "%s: Create thread. pri:%d\n",__FUNCTION__,pri);
    id = IOS_CreateThread(	(IOSEntryProc)sdioRmThread, 
    						(void*)200, 
    						stacksdio+SDRM_STACK_SIZE, SDRM_STACK_SIZE, 
    						pri, 
    						IOS_THREAD_CREATE_DETACHED);
    SDIO_LOG(SDIO_INIT, "%s: Starting thread. id:%d mq:%d\n",__FUNCTION__,id,sdrmQid);
	IOS_StartThread(id);
