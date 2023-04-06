d20 1
a20 1
#ident "$Id: sdio_rm.c,v 1.3 2006/03/16 19:22:00 gbarnard Exp $"
d48 1
d51 1
a51 1
#define SDRM_QUEUE_SIZE 	64	
a62 32
static struct _sdio_ioctl_names {
    u32  ioctl_val;
    char *ioctl_name;
} sdio_ioctl_names[] = {
	{ SD_RESET, "SD_RESET" },
	{ SD_DEBUG_LEVEL, "SD_DEBUG_LEVEL" },
	{ SD_IOWREG, "SD_IOWREG" },
	{ SD_IOWCREG, "SD_IOWCREG" },
	{ SD_IORMCREG, "SD_IORMCREG" },
	{ SD_IOWMCREG, "SD_IOWMCREG" },
	{ SD_CINTEN, "SD_CINTEN" },
	{ SD_CINTDIS, "SD_CINTDIS" },
	{ SD_IORREG, "SD_IORREG" },
	{ SD_IORCREG, "SD_IORCREG" },
	{ SD_GET_STATUS, "SD_GET_STATUS" },
};

char*
sdio_ioctl_name (u32 ioctl_val)
{
    struct _sdio_ioctl_names *p;
    int i;

    for (i = 0, p = &sdio_ioctl_names[0]; 
         i < (sizeof (sdio_ioctl_names)/sizeof (struct _sdio_ioctl_names));
         p++, i++) {
        if (p->ioctl_val == ioctl_val)
            return p->ioctl_name;
    }

    return "unknown";
}
a154 38
/*
 * SDIO_Read
 *
 * Not implemented for sd/sdio.
 */
static IOSError
SDIO_Read(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_INVALID;

    return rv;
}

/*
 * SDIO_Write
 *
 * Not implemented for sd/sdio.
 */
static IOSError
SDIO_Write(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_INVALID;

    return rv;
}

/*
 * SDIO_Seek
 *
 * Not implemented for sd/sdio.
 */
static IOSError
SDIO_Seek(IOSResourceRequest *req)
{
    IOSError rv = IOS_ERROR_INVALID;

    return rv;
}
d180 1
a180 1
    u32 cmd, input;
d196 1
a198 6
    case SD_IOC_MAGIC:
        break;
    case SD_IOGSLOTS:
        break;
    case SD_IOGIDENT:
        break;
d200 19
a218 14
        rca  = sdio_ser_ioctl(NULL, NULL, cmd, input);
        if (rca < 0) {
            printf ("ioctl");
            printf("%s: Bad ioctl %s rcs 0x%x\n", 
                     __FUNCTION__, sdio_ioctl_name (cmd), rca);
            return IOS_ERROR_ACCESS;
        }
        printf("Done RCA=%x\n",rca);
        ret = (u32 *)arg->outPtr;
        if (ret) {
            *ret = rca;
        }
        break;
    case SD_DEBUG_LEVEL:
d223 6
d231 8
d242 14
a255 8
        status = sdio_ser_ioctl(NULL, NULL, cmd, input);
        if (status < 0) {
            printf ("sdio_ioctl_name (cmd)");
            printf( "%s: Bad ioctl %s status 0x%x\n", 
                     __FUNCTION__, sdio_ioctl_name (cmd), status);
            return IOS_ERROR_ACCESS;
        }
        break;
d258 5
d264 13
a276 13
        value = sdio_ser_ioctl(NULL, NULL, cmd, input);
        if (value < 0) {
            printf ("sdio_ioctl_name (cmd)");
            printf( "%s: Bad ioctl %s value 0x%x\n",
                     __FUNCTION__, sdio_ioctl_name (cmd), value);
            return IOS_ERROR_ACCESS;
        }
        //printf("   Read Register Returns:0x%x to ptr:0x%x\n",value,arg->outPtr);
        ret = (u32 *)arg->outPtr;
        if (ret) {
            *ret = value;
        }
        break;
d279 2
a280 2
        rv = IOS_ERROR_INVALID;
        break;
d295 2
d298 1
a298 3
        SDIO_LOG(SDIO_INIT,
        //printf(
        		"%s: Waiting for command id:%d mq:%d\n",
d300 1
d305 1
a305 1
            return;
d307 1
a307 3
        SDIO_LOG(SDIO_INIT,
        //printf(
        		"%s: Received resource request: %08x\n", 
a319 9
        case IOS_READ:
            rv = SDIO_Read(req);
            break;
        case IOS_WRITE:
            rv = SDIO_Write(req);
            break;
        case IOS_SEEK:
            rv = SDIO_Seek(req);
            break;
d324 1
