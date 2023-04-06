d12 1
a12 1
#ident "$Id: sdio_api.c,v 1.4 2006/03/18 01:16:12 gbarnard Exp $"
d575 1
a575 1
    unsigned int code, offset;
d599 5
a603 1
        if (!read_card_reg(fd, i, 1, &offset)) {
d608 5
a612 1
        if ((code == 0xff) || (code == 0x0)) {
d615 1
d619 4
a622 3
        for (j = 0; i < next; i++, j++) {
            if (!read_card_reg(fd, i, 1,
                               (unsigned int *)regData)) {
d627 3
d633 5
a637 2
    } while ((code != 0xff) && (k < length));

