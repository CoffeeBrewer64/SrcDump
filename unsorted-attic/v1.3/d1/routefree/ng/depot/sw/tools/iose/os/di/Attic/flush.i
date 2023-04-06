d1 1
a1 1
#ident "$Id: flush.i,v 1.2 2006/03/23 00:52:09 craig Exp $"
d34 2
a35 2
    IOS_FlushMem(wb_iod);
    IOS_InvalidateRdb(rb_aim);
d52 4
a55 4
    // printf ("(flushDItoIOP) doing FlushMem wb_aim\n");
    IOS_FlushMem(wb_aim);
    // printf ("(flushDItoIOP) doing invalidateRdb rb_iod\n");
    IOS_InvalidateRdb(rb_iod);
d74 2
a75 2
    IOS_FlushMem(wb_aim);
    IOS_InvalidateRdb(rb_aes);
d88 2
a89 2
    IOS_FlushMem(wb_aes);
    IOS_InvalidateRdb(rb_sha);
