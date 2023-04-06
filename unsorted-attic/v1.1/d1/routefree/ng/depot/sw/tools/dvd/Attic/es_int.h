a0 1
#ident "$Id: es_int.h,v 1.28 2006/02/10 01:47:18 craig Exp $"
a213 17
    
#if !defined(NEXT_GEN)
#define htonll(x) ((u64)( ((u64)((htonl((u32)(x)))) << 32) | (htonl((u32)(((u64)(x))>>32))) ))
#define ntohll(x) ((u64)( ((u64)((ntohl((u32)(x)))) << 32) | (ntohl((u32)(((u64)(x))>>32))) ))
#else

#include <endian.h>
#if __BYTE_ORDER == __BIG_ENDIAN
#define htonll(x)       (x)
#define ntohll(x)       (x)
#elif __BYTE_ORDER == __LITTLE_ENDIAN
#define htonll(x) ((u64)( ((u64)((htonl((u32)(x)))) << 32) | (htonl((u32)(((u64)(x))>>32))) ))
#define ntohll(x) ((u64)( ((u64)((ntohl((u32)(x)))) << 32) | (ntohl((u32)(((u64)(x))>>32))) ))
#else
#error endian.h did not define __BIG_ENDIAN or __LITTLE_ENDIAN
#endif
#endif
