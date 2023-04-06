d14 3
d21 11
d589 1
a589 1
                break;  // quit loop
d600 1
a600 1
                break;
d603 4
a607 1

a608 1

d612 1
a612 1
                break;
a615 1

a618 1

a619 1

d821 1
a821 1
    datagram->mtu = (u16) IP6GetPathMTU(destination);
d1901 1
d1982 2
d1999 10
a2008 1
        accepted->mss = accepted->mssBase = interface->mtu - IP_MIN_HLEN - TCP_MIN_HLEN;
d2024 10
a2033 1
        accepted->mss = accepted->mssBase = interface->linkMTU - (s32) sizeof(IP6Hdr) - TCP_MIN_HLEN;
