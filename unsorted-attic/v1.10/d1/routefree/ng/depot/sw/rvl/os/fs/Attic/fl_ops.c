d672 4
a675 4
    IOS_FlushMem(wb_iod);
    IOS_FlushMem(wb_fla);
    IOS_InvalidateRdb(rb_iod);
    IOS_InvalidateRdb(rb_fla);
d677 4
a680 4
    ahbMemFlush(wb_iod);
    ahbMemFlush(wb_fla);
    ahbMemRBInvalidate(rb_iod);
    ahbMemRBInvalidate(rb_fla);
d722 4
a725 4
    IOS_FlushMem(wb_iod);
    IOS_FlushMem(wb_fla);
    IOS_InvalidateRdb(rb_iod);
    IOS_InvalidateRdb(rb_fla);
d727 4
a730 4
    ahbMemFlush(wb_iod);
    ahbMemFlush(wb_fla);
    ahbMemRBInvalidate(rb_iod);
    ahbMemRBInvalidate(rb_fla);
