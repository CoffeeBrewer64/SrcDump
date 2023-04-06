d12 1
a12 1
#ident "$Id: sd_api.c,v 1.2 2006/03/16 19:31:58 gbarnard Exp $"
d283 1
a283 1
    status = ISDIO_Ioctl(fd->SDDevFd, SD_READ_DATA, &cmd_op, 0x0, &value, 0x0);
d368 1
a368 1
    status = ISDIO_Ioctl(fd->SDDevFd, SD_WRITE_DATA, &cmd_op, 0x0, &value, 0x0);
d775 1
a775 1
    status = ISDIO_Ioctl(fd->SDDevFd, SD_CMD, &cmd_op, 0x0, &value, 0x0);
