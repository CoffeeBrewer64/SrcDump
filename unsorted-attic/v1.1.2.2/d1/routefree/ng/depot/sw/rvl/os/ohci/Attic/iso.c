d70 2
a71 1
    u32 psw = 0xf000 |tmp;
a73 6
    
    if (tmp > (((u32)buf & 0xfff) + buflen)) {
        printf("tmp = %u be = 0x%08x\n", tmp, (u32)itd->be);
        itd->psw[i] = CPU_TO_OHCI32(psw);
        break;
    }
d75 1
a75 1
    psw |= 0xf0000000 | (tmp << 16);
d101 1
d105 2
d119 1
d123 1
d171 3
d183 2
a184 1
    __fillITDSF(itd_data, OHCI_READ(hcd->opregs->frm_num) + 5);
a185 2
    IOS_FlushMem(IOS_WB_IOD);
    IOS_InvalidateRdb(hcd->hc_rdb);
d187 1
