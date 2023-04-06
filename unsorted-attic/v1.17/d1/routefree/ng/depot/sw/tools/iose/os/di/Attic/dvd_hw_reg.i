d1 1
a1 1
#ident "$Id: dvd_hw_reg.i,v 1.16 2006/03/05 00:31:24 craig Exp $"
a77 3
#ifdef WORK_AROUND
    uint32_t    accessReg;
#endif
a79 8
#ifdef WORK_AROUND
    IOS_InvalidateRdb(rb_iod);
    accessReg = busRd32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK);
    /* Enable control over PI_IO */
    AIPPROT_SET_ENAHBIOPI(accessReg, 1);
    busWrt32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK, accessReg);
    IOS_FlushMem(wb_iod);
#endif
a83 9
#ifdef WORK_AROUND
    IOS_InvalidateRdb(rb_iod);
    accessReg = busRd32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK);
    /* Disable control over PI_IO */
    AIPPROT_SET_ENAHBIOPI(accessReg, 0);
    busWrt32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK, accessReg);
    IOS_FlushMem(wb_iod);
#endif

a195 3
#ifdef WORK_AROUND
    uint32_t    accessReg;
#endif
a197 9
#ifdef WORK_AROUND
    IOS_InvalidateRdb(rb_iod);
    accessReg = busRd32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK);
    /* Enable control over PI_IO */
    AIPPROT_SET_ENAHBIOPI(accessReg, 1);
    busWrt32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK, accessReg);
    IOS_FlushMem(wb_iod);
#endif

a200 9
#ifdef WORK_AROUND
    IOS_InvalidateRdb(rb_iod);
    accessReg = busRd32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK);
    /* Disable control over PI_IO */
    AIPPROT_SET_ENAHBIOPI(accessReg, 0);
    busWrt32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK, accessReg);
    IOS_FlushMem(wb_iod);
#endif

