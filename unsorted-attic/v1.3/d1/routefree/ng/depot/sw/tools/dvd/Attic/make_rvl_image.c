d1 1
a1 1
#ident "$Id: make_rvl_image.c,v 1.2 2006/04/19 03:02:33 craig Exp $"
d45 1
d102 1
a102 1
static char* options = "efho:s:t:z";
d615 1
a615 1
    sprintf (commandBuf, "tmd -O -T 0x%x -c 0x%x",
d645 1
a645 1
    sprintf(tmdName, "%08x.tmd", titleId);
d652 1
a652 1
    sprintf(encryptedContentName, "%08x.app", contentCID);
d659 1
a659 1
    sprintf(titleKeyName, "%08x.titleKey", titleId);
d667 1
a667 1
        sprintf(h3HashName, "%08x.hash", contentCID);
d687 2
a688 2
    sprintf (commandBuf, "ticket -O -t %d -T %d -K %s", ticketID,
                          titleID, encryptedTitleKeyFile);
d706 1
a706 1
    sprintf(ticketName, "%x.tik", ticketID);
