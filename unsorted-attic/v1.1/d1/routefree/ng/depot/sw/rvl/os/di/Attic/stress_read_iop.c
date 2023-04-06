d1 1
a1 1
#ident "$Id: test_read_iop.c,v 1.2 2006/03/16 23:55:21 craig Exp $"
d19 1
d65 2
d70 2
d75 3
d85 1
a85 1
    md5_byte_t          digest[16];
d95 12
d143 6
a148 1
    // do_read_stress(diFilePtr);
d150 2
a151 1
    MD5_sum_disk_section(diFilePtr, 0x40000, 0x240000 - 0x40000, digest);
d153 1
a153 1
    printf ("MD5 Sum: ");
d158 2
d171 38
d210 17
a226 14
    MD5_sum_disk_section(diFilePtr, 0x40000, 32, disk_digest);
    MD5_sum_rand_sequence(0x40000, 32, rand_digest);

    printf ("Disk MD5 Sum: ");
    for (int di = 0; di < 16; ++di) {
        printf("%02x", disk_digest[di]);
    }
    printf ("\n");

    printf ("Rand MD5 Sum: ");
    for (int di = 0; di < 16; ++di) {
        printf("%02x", disk_digest[di]);
    }
    printf ("\n");
d232 2
a241 1
    uint8_t     buf[1024] __attribute__((aligned(32)));
d264 3
a266 1
        /*
d270 2
a271 1
        */
a292 1
    md5_init(&state);
d294 4
d299 1
d303 10
d317 1
d326 1
a327 1
        // printf ("Cur: 0x%x; End: 0x%x\n", currentAddr, endAddr);
d335 1
d338 1
d342 1
d366 1
d369 1
d371 1
d440 1
d491 23
