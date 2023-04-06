a34 6
#define FLUSH_OUTGOING(ptr, len)      IOS_FlushMem(wb_iod);
//    Writeback((ptr), (len)); 

#define INVAL_INCOMING(ptr, len)      IOS_InvalidateRdb(rb_iod); 
//    Invalidate((ptr), (len))

a112 1
            FLUSH_OUTGOING(req->args.read.outPtr, req->status);
a117 1
            FLUSH_OUTGOING(req->args.ioctl.outPtr, req->args.ioctl.outLen);
a128 2
                FLUSH_OUTGOING(v->vector[v->readCount + i].base, 
                               v->vector[v->readCount + i].length);
a131 2
            FLUSH_OUTGOING(&v->vector[v->readCount], 
                           req->args.ioctlv.writeCount * sizeof(IOSIoVector));
d143 1
a143 1
    FLUSH_OUTGOING(req, sizeof(IOSResourceRequest));
d167 1
a167 1
    INVAL_INCOMING(req, sizeof(IOSResourceRequest));
d177 1
a177 1
        INVAL_INCOMING(req->args.open.path, IOS_PATH_MAX + 1);
a193 1
        INVAL_INCOMING(req->args.write.inPtr, req->args.write.inLen);
a207 1
        INVAL_INCOMING(req->args.ioctl.inPtr, req->args.ioctl.inLen);
a218 1
        INVAL_INCOMING(&v->vector[0], i * sizeof(IOSIoVector));
a222 1
            INVAL_INCOMING(v->vector[i].base, v->vector[i].length);
