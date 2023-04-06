d33 1
a33 1
__checkIsoArgs(IOSResourceIoctlv *args)
d118 1
a118 1
ohci_IsoIRP(struct ohci_hcd *hcd, IOSResourceRequest *resReq)
d133 1
a133 1
    if ((rv = __checkIsoArgs(args)) < 0) {
