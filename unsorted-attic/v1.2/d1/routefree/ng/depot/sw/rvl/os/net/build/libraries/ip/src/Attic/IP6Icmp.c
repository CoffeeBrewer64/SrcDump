d15 3
d22 7
d613 1
a613 1
    datagram->vec[0].len  = (s32) sizeof(IP6Hdr) + plen;
d616 1
a616 1
    datagram->mtu = (u16) IP6GetPathMTU(dst);
d1533 1
a1533 1
    
d2438 1
a2438 1
    datagram->mtu = (u16) IP6GetPathMTU(dst);
d2722 1
a2722 1
    datagram->mtu = (u16) IP6GetPathMTU(destination);
d3235 1
a3235 1
    datagram->mtu = (u16) IP6GetPathMTU(dst);
d3423 1
a3423 1
s32 IP6GetPathMTU(IP6Entry* dst)
d3434 2
a3435 1
    if (dst->mtu < interface->linkMTU &&
d3442 1
a3442 2
        // Restore original MSS
        dst->mtu = interface->linkMTU;
d3457 1
a3457 1
                tcp->mss = mss;
d3464 2
