a46 6
/* Byte swap */
#define FL_BYTE_SWAP(x)     (((x & 0xff000000) >> 24) |                     \
                                ((x & 0x00ff0000) >> 8) |                   \
                                ((x & 0x0000ff00) << 8) |                   \
                                ((x & 0x000000ff) << 24))

d1389 1
a1389 1
        u32     eccStored, eccComputed;
d1392 2
a1393 2
        eccComputed = *((u32 *) &spareBuf[FL_SPARE_ECC_OFFSET + eccOffset]);
        eccStored = *((u32 *)
d1395 1
a1395 1
                        eccOffset]);
d1397 3
a1399 2
        /* Check for bit errors */
        if (eccStored == eccComputed) {
d1401 1
a1401 8
        }

        eccStored = FL_BYTE_SWAP(eccStored);
        eccComputed = FL_BYTE_SWAP(eccComputed);

        /* Result is XOR'ed together, and AND'ed out the unrelated bits */
        eccResult = ((eccStored ^ eccComputed) & 0x0fff0fff);
        if ((eccResult & (eccResult - 1)) == 0) {
