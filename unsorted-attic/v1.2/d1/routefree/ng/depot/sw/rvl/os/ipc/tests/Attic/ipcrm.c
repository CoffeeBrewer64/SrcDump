d34 7
a40 2
#define RM_LOG(...) printf("RM: " __VA_ARGS__)
#define RM_ERROR(msg, rv) printf("RM: Error: %s failed: %d\n", msg, rv)
d236 1
a236 1
    IOSResourceSeek  *args;
d246 6
a251 1
    args = (IOSResourceSeek *)&req->args.ioctl;
d253 3
a255 1
    if (!d->inUse)
d261 2
d272 1
a272 1
    IOSResourceSeek  *args;
d282 7
a288 1
    args = (IOSResourceSeek *)&req->args.ioctlv;
d290 3
a292 1
    if (!d->inUse)
d298 2
