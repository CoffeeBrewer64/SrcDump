d1 1
a1 1
#ident "$Id$"
d33 1
d54 1
d57 1
a57 1
    uint32_t            numUpdates;
d59 1
d78 1
d101 20
d135 1
a178 1
        uint8_t                 imageBytes[256];
d192 75
a266 5
        doDiskRead(imageBytes, sizeof(imageBytes), imageAddr);
        printf ("\tImage: Address 0x%x\n", imageAddr << 2);
        printf ("\tImage bytes: ");
        for (int i = 0; i < 16; ++i) {
            printf("%02x ", imageBytes[i]);
d270 9
d280 1
