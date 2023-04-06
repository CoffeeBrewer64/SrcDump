d1 1
a1 1
#ident "$Id: dvd_main.c,v 1.2 2006/02/26 02:14:53 craig Exp $"
d22 2
d36 1
a43 7

    busWrt32(ACR_PROT_REGS_BASE + AIPPROT_OFFSET,
                  (((unsigned long)1)<<AIPPROT_ENAHBIOPI_SHIFT)
                | (((unsigned long)1)<<AIPPROT_ENAHBPI2DI_SHIFT));

#define ONE_WAY
#ifdef ONE_WAY
d46 2
a47 2
    reg = busRd32(ACR_PROT_REGS_BASE + ACRCOMPAT_OFFSET);
    // Try '1' here as well'
d49 1
a49 7
    busWrt32(ACR_PROT_REGS_BASE + ACRCOMPAT_OFFSET, reg);
#else
    busWrt32(PI_REGSP_PI + PI_REG_CONFIG,
                                  PI_CONFIG_REG_DIRSTB_MASK
                                | PI_CONFIG_REG_SYSRSTB_MASK
                                | PI_CONFIG_REG_MEMRSTB_MASK);
#endif
d51 5
d58 5
a68 1
    testVal |= 0xa;
a75 1
    IOS_DestroyThread(0, NULL);
d79 1
a79 2
    printf ("Status reg is: 0x%x\n", readDIStatus());
    IOS_DestroyThread(0, NULL);
