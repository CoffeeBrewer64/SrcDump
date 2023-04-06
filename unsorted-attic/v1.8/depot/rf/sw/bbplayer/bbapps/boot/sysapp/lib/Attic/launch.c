d15 1
a36 13

#if 0
    fsret = osBbFStat(fd, &fsStat, blkList, heapSize/2);
    if(fsret !=0){
        return SALAUNCH_ERR_FS;
    }
    
    osBbFClose(fd);

    /* setup atb mapping (sk will setup aes) */
    /* XXX: for now assume pi cartridge domain 1, addr range 2. */
    osBbAtbSetup(PI_DOM1_ADDR2, blkList, (heapSize>>1)-4);
#endif
d150 1
a150 2
        /* XXX: put this back! */
        //osBbLoadState(appName, &md.state, binding);
