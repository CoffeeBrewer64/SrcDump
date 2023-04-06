d1 1
a1 1
#ident "$Id: dvd.h,v 1.11 2006/02/02 00:34:05 craig Exp $"
a28 1
    bool        currentHashRead;
a32 2


a57 7

typedef struct diskInfo {
    uint32_t    h3WordOffset;       
    uint32_t    h3Size;
    uint32_t    dataWordOffset;
} diskInfo_t;

