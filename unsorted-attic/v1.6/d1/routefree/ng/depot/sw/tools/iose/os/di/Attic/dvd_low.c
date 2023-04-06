d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.5 2005/12/14 23:03:26 craig Exp $"
a208 11
diStartTransfer(const transferMode_t transferMode)
{
    if (transferMode == Immediate) {
        DIControl = DI_TRANSFER;
    }
    else {
        DIControl = DI_TRANSFER | DI_DMA_MODE;
    }
}

static inline void
d230 24
