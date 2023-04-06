d8 1
d14 1
d24 2
a25 1
    s32 fsret,fd;
d29 1
a35 15
    /* 
     * setup atb first, so can reclaim blkList memory 
     */

    /* XXX: recrypt may impact which extension to use */
    cidToAppName(pCmdh->id,appName);

    if( (fd = osBbFOpen(appName,"r")) < 0){
        return SALAUNCH_ERR_FS;
    }

    for(i=0;i<heapSize;i++)
        heap[i]=0;
    blkList = (u16 *)heap;
//    ALIGN_DCACHE_DYN(blkList);
d37 1
d48 1
a48 1

d134 1
a134 18
    /* configure flash */
    /* NOTE: assuming fs already has correctly configured
     *       PI_FLASH_CONFIG_REG for the module.
     */
    IO_WRITE(PI_FLASH_CTRL_REG, PI_FLASH_CTRL_RDPH  |
                                0xf << PI_FLASH_CTRL_ADPH_SHIFT |
                                0x0 << PI_FLASH_CTRL_CMD_SHIFT |
                                PI_FLASH_CTRL_WRDY |
                                0 << PI_FLASH_CTRL_BUF_SHIFT |
                                0 << PI_FLASH_CTRL_DEV_SHIFT |
                                PI_FLASH_CTRL_ECC |
                                0x3ff);

    /* inval d-cache (sk will inval icache on entry) */
    osWritebackDCacheAll();
    __osDisableInt();

    if(SK_API_SUCCESS != skLaunch(&ticketBundle, 
d140 29
d171 1
