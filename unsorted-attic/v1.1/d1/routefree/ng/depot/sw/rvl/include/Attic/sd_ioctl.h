d12 1
a12 1
#ident "$Id: sd_ioctl.h,v 1.1 2006/01/30 23:43:35 gbarnard Exp $"
d142 1
a142 1
	/* used to create numbers */
d208 2
a209 2
#define SD_READ_DATA      _IOW(SD_IOC_MAGIC, 36, unsigned int)
#define SD_WRITE_DATA     _IOW(SD_IOC_MAGIC, 37, unsigned int)
