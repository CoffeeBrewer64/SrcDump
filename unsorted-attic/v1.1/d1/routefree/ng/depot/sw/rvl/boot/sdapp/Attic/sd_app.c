d10 1
a10 1
 * $Id: sd_boot.c,v 1.4 2006/05/11 00:28:56 achan Exp $
d166 1
d179 1
a179 1
    rc = sdLoadWadFile(SD_LOAD_ADDR, SD_OS_OFFSET);
d193 1
a193 1
    rc = sdLoadWadFile(SD_LOAD_ADDR, SD_PPCAPP_OFFSET);
