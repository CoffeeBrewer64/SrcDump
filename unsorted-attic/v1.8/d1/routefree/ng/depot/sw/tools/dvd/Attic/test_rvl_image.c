d1 1
a1 1
#ident "$Id: test_rvl_image.c,v 1.7 2006/02/23 00:28:14 craig Exp $"
a24 10
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

d237 1
a237 1
    // printf ("Certificate size: %d\n", sizeof(ESRsa2048RsaCert));
d240 1
a240 1
        ESRsa2048RsaCert        cert;
d242 1
a242 1
        certAddr = certArrayAddr + (i * sizeof(ESRsa2048RsaCert));
d247 1
a247 1
        doRawDiskRead((uint8_t *) &cert, sizeof(ESRsa2048RsaCert), certAddr);
d249 1
a249 1
        md5_append(&state, (md5_byte_t *) &cert, sizeof(ESRsa2048RsaCert));
d319 1
a319 1
    // printf ("Certificate size: %d\n", sizeof(ESRsa2048RsaCert));
d322 1
a322 1
        ESRsa2048RsaCert        cert;
d324 1
a324 1
        certAddr = certArrayAddr + (i * sizeof(ESRsa2048RsaCert));
d329 1
a329 1
        doRawDiskRead((uint8_t *) &cert, sizeof(ESRsa2048RsaCert), certAddr);
d331 1
a331 1
        md5_append(&state, (md5_byte_t *) &cert, sizeof(ESRsa2048RsaCert));
d388 2
a389 2
    printf ("ESRsa2048: %d/0x%x\n",
             sizeof(ESRsa2048RsaCert), sizeof(ESRsa2048RsaCert));
