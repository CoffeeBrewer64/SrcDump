d1 1
a1 1
#ident "$Id$"
d48 1
a48 1
flushDItoIOP(void* const ptr, const uint32_t num_bytes)
d50 6
d57 1
d59 6
a64 1
    IOS_InvalidateDCache(ptr, num_bytes);
