d48 39
a171 66
    message("Calling skLaunchBegin()\n");
    if(SK_API_SUCCESS != skLaunchBegin(&ticketBundle, 
                                       haveCrl ? &appRls : (void *)0, 
                                       (void *)0)){
        PRINTF("skLaunchBegin() failure!\n");
        return SALAUNCH_ERR_DATA;
    }
    message("Returned from skLaunchBegin()\n");

    cidToAppName(pCmdh->id,appName);

    message("Cmd id: ");
    output_int32_hex(pCmdh->id);
    message("\n");
    message(appName);
    message("\n");

    if( (fd = osBbFOpen(appName,"r")) < 0){
        message("Failed to open app on fs.\n");
        return SALAUNCH_ERR_FS;
    }

    for(i=0;i<heapSize;i++)
        heap[i]=0;
    blkList = (u16 *)heap;
//    ALIGN_DCACHE(blkList);

    message("Calling osBbFStat for app file.\n");
    fsret = osBbFStat(fd, &fsStat, blkList, heapSize/2);
    if(fsret !=0){
        message("Failed to stat app file\n");
        return SALAUNCH_ERR_FS;
    }
    message("osBbFStat, app size: ");
    output_int32_hex(fsStat.size);
    message("\n");
    
    message("Loop over app blks.\n");

    /* TODO: optimize to make single call for consecutive blocks. */
    for(i=0;blkList[i]!=0;i++){
        PRINTF("skLaunchData(), block %d\n",blkList[i]);
        message("Calling skLaunchData, block: ");
        output_int32_hex((u32)blkList[i]);
        message("\n");
        if(SK_API_SUCCESS != skLaunchData(blkList[i],1)){
            PRINTF("skLaunchData FAILED\n");
            osBbFClose(fd);
            return SALAUNCH_ERR_DATA;
        }
    }

    message("blocks processed = ");
    output_int32_hex(i);
    message("\n");

    osBbFClose(fd);

    message("Calling osBbAtbSetup().\n");

    /* setup atb mapping (sk will setup aes) */
    /* XXX: for now assume pi cartridge domain 1, addr range 2. */
    osBbAtbSetup(PI_DOM1_ADDR2, blkList, (heapSize>>1)-4);

    message("atb setup completed.\n");

d185 1
a185 1
    message("Calling skLaunchEnd().\n");
d187 9
a195 2
    /* should not return from this call if success. */
    skLaunchEnd();
