d1395 1
a1395 1
        u32     *eccStored, *eccComputed;
d1398 2
a1399 2
        eccComputed = (u32 *) &spareBuf[FL_SPARE_ECC_OFFSET + eccOffset];
        eccStored = (u32 *)
d1401 1
a1401 1
                        eccOffset];
d1404 1
a1404 1
        if (*eccStored == *eccComputed) {
d1408 2
a1409 2
        *eccStored = FL_BYTE_SWAP(*eccStored);
        *eccComputed = FL_BYTE_SWAP(*eccComputed);
d1412 1
a1412 1
        eccResult = ((*eccStored ^ *eccComputed) & 0x0fff0fff);
