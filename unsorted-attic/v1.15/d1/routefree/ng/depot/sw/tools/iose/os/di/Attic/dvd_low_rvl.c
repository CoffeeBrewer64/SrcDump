d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.14 2006/02/22 20:59:46 craig Exp $"
d19 7
a27 2
#include <stdbool.h>
#include <stdint.h>
d30 4
d60 1
a60 1
#define SUBBLOCK_OFFSET_WORD(addr)      (addr & 0xFF)
d67 1
a67 1
#define MIN(X,Y)                        (X > Y ? Y : X)
d92 1
a92 1
                    const uint32_t wordOffset);
d460 1
d462 1
d604 1
d606 1
d657 1
d660 1
d740 1
d743 1
a800 1
            char printBuf[256];
d802 3
a804 4
            sprintf(printBuf,
                "Error: scratch buffer is too small for request of %u bytes",
                length);
            diFatalError(printBuf);
