d18 1
a18 1
    u32 romPatch[64]; /* this is so total adds to 256 bytes */
d53 1
a53 1
    for(i =0 ;i < 64; i++){
d58 1
a58 1
    fwrite(romPatch, 4, 64, fptr);
