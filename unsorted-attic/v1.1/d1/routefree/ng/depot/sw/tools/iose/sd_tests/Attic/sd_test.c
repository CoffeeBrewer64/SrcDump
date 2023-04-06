d11 1
a11 1
 * $Id: sdio_test.c,v 1.12 2005/11/19 00:39:52 jlivesey Exp $
d25 1
a25 1
#include <sd_api.h>
d125 38
d200 14
d215 14
d363 1
a363 2
    int dev, function, arg, reg, width;
    unsigned int data;
d366 1
a366 1
    unsigned int blk_size, blk_cnt;
d368 2
d761 27
d789 94
d939 18
a956 1
 
d1034 1
a1034 1
    IOSRmReq *req;
d1066 1
a1066 1
        switch(req->type) {
d1069 1
a1069 1
                   __FUNCTION__, req->type);
