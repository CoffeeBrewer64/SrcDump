d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.64 2006/03/22 01:09:34 craig Exp $"
d192 1
a192 1
            IOS_InvalidateRdb(rb_iod);
d201 1
a201 1
                IOS_FlushMem(wb_iod);
d223 1
a223 1
                IOS_FlushMem(wb_iod);
d424 1
a424 1
        IOS_InvalidateRdb(rb_iod);
d426 1
a426 1
        IOS_FlushMem(wb_iod);
d436 1
a436 1
        IOS_InvalidateRdb(rb_iod);
d457 1
a457 1
        IOS_InvalidateRdb(rb_iod);
d468 1
a468 1
        IOS_InvalidateRdb(rb_iod);
d472 1
a472 1
        IOS_FlushMem(wb_iod);
d477 1
a477 1
        IOS_InvalidateRdb(rb_iod);
d481 1
a481 1
        IOS_FlushMem(wb_iod);
d486 1
a486 1
        IOS_InvalidateRdb(rb_iod);
d490 1
a490 1
        IOS_FlushMem(wb_iod);
d495 1
a495 1
        IOS_InvalidateRdb(rb_iod);
