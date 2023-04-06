d46 1
a46 1
void 
d61 1
a61 1
  printf("client: calling dummy ioctl: cmd = 1, input_bytes = 2, output_bytes = 3\n");
d67 1
a67 1
void
d80 1
a80 1
void
d97 2
a98 2
void
handleOpen(IOSResourceReq *req, s32 *reply)
d106 3
a108 2
void
handleClose(IOSResourceReq *req, s32 *reply)
d116 3
a118 2
void
handleRead(IOSResourceReq *req, s32 *reply)
d125 1
a125 1
    if ( NULL == req->msg )
d128 1
a128 1
        msg = (IOSReadWriteMsg *) req->msg;
d130 1
a130 1
        printf("Driver: read request buffer size = %d\n", msg->count);
d136 1
a136 1
            for ( i = 0; i < msg->count; ++i ) 
d138 1
a138 1
            *reply = msg->count;
d144 2
a145 2
void
handleWrite(IOSResourceReq *req, s32 *reply)
d152 1
a152 1
    if ( NULL == req->msg )
d155 1
a155 1
        msg = (IOSReadWriteMsg *) req->msg;
d157 1
a157 1
        printf("Driver: got write request buffer size = %d\n", msg->count);
d164 1
a164 1
            for ( i = 0; i < msg->count; ++i )
d167 1
a167 1
            *reply = msg->count;
d172 3
a174 2
void
handleIoctl(IOSResourceReq *req, s32 *reply)
d179 1
a179 1
    if ( NULL == req->msg )
d182 1
a182 1
        msg = (IOSIoctlMsg *) req->msg;
d185 2
a186 2
        printf("Driver: ioctl input_bytes = %d\n", msg->input_bytes);
        printf("Driver: ioctl output_bytes = %d\n", msg->output_bytes);
d192 2
a193 2
void
handleSeek(IOSResourceReq *req, s32 *reply)
d198 3
a200 2
void
handleStat(IOSResourceReq *req, s32 *reply)
d212 1
a212 1
    IOSResourceReq *req;
