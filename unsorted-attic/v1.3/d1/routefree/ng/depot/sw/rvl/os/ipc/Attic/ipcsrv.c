d27 5
a31 2
//#define IPC_LOG(...)
#define IPC_LOG(...)       printf("SRV: " __VA_ARGS__)
a37 6
#define FLUSH_OUTGOING(ptr, len)      IOS_FlushMem(wb_iod);
//    Writeback((ptr), (len)); 

#define INVAL_INCOMING(ptr, len)      IOS_InvalidateRdb(rb_iod); 
//    Invalidate((ptr), (len))

a115 1
            FLUSH_OUTGOING(req->args.read.outPtr, req->status);
a120 1
            FLUSH_OUTGOING(req->args.ioctl.outPtr, req->args.ioctl.outLen);
d129 1
a129 1

a131 2
                FLUSH_OUTGOING(v->vector[v->readCount + i].base, 
                               v->vector[v->readCount + i].length);
d135 9
a143 2
            FLUSH_OUTGOING(&v->vector[v->readCount], 
                           req->args.ioctlv.writeCount * sizeof(IOSIoVector));
d155 1
a155 1
    FLUSH_OUTGOING(req, sizeof(IOSResourceRequest));
d179 1
a179 1
    INVAL_INCOMING(req, sizeof(IOSResourceRequest));
d189 1
a189 1
        INVAL_INCOMING(req->args.open.path, IOS_PATH_MAX + 1);
a205 1
        INVAL_INCOMING(req->args.write.inPtr, req->args.write.inLen);
a219 1
        INVAL_INCOMING(req->args.ioctl.inPtr, req->args.ioctl.inLen);
a230 1
        INVAL_INCOMING(&v->vector[0], i * sizeof(IOSIoVector));
d232 3
a234 1
        for (i = 0; i < req->args.ioctlv.readCount; ++i) 
a236 1
            INVAL_INCOMING(v->vector[i].base, v->vector[i].length);
d297 5
