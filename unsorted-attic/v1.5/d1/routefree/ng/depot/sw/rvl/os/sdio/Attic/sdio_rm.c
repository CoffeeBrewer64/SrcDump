d20 1
a20 1
#ident "$Id: sdio_rm.c,v 1.4 2006/03/18 01:16:12 gbarnard Exp $"
d42 2
a43 2
#define SDIO_NUM_DESCRIPTORS 4
static SDIOFileDescriptor desc[SDIO_NUM_DESCRIPTORS];
d110 1
a110 1
        if (!desc[i].inUse) 
d124 4
a127 4
    desc[i].inUse = 1;
    desc[i].pos = 0;
    desc[i].dev = dev;
    rv = (IOSError) &desc[i];
d286 1
a286 1
#define RMDEBUG 1
d334 1
