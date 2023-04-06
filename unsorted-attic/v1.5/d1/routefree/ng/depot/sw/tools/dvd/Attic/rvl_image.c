d1 1
a1 1
#ident "$Id: rvl_image.c,v 1.4 2006/02/13 22:47:05 craig Exp $"
d85 1
a85 1
    {"encypt",          0, 0, 'e'},     /* Generate entire disk image */
d87 1
d95 1
a95 1
static char* options = "efho:s:";
d697 2
a698 2
        encrypt    = inputDisk->diskInfo->noEncryption != 0 ? true : false;
        hash       = inputDisk->diskInfo->noHash       != 0 ? true : false;
d729 1
a729 1
                             TitleKey, false, false) == true) {
