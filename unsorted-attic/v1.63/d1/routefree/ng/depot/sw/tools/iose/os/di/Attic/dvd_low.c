d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.62 2006/03/23 00:52:09 craig Exp $"
d361 1
a361 1
    IOS_FlushMem(wb_iod);
d539 1
a539 1
    IOS_InvalidateRdb(rb_iod);
d562 1
a562 1
    IOS_FlushMem(wb_iod);
d1005 1
a1005 1
        IOS_InvalidateRdb(rb_iod);
d1076 1
a1076 1
            IOS_FlushMem(wb_iod);
d1206 1
a1206 1
    IOS_InvalidateRdb(rb_iod);
d1208 1
a1208 1
    IOS_FlushMem(wb_iod);
d1239 1
a1239 1
            IOS_InvalidateRdb(rb_iod);
