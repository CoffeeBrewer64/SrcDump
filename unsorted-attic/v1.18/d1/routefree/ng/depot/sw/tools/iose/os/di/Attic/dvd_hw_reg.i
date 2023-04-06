d1 1
a1 1
#ident "$Id: dvd_hw_reg.i,v 1.17 2006/03/05 02:46:48 craig Exp $"
d81 1
a81 1
    IOS_InvalidateRdb(rb_iod);
d199 1
a199 1
    IOS_FlushMem(wb_iod);
d201 1
a201 1
    IOS_InvalidateRdb(rb_iod);
