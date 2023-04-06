d14 3
d21 19
d48 1
a48 1
    Moved SO_SOCKET_MAX  to socket.h.
d353 1
d591 2
a592 1
    return IPAtoN(cp, inp ? (u8*) &inp->addr : addr) ? 1 : 0;
d634 2
a635 1
        return IPAtoN(src, dst) ? 1 : 0;
d638 2
a639 1
        return IP6AtoN(src, dst) ? 1 : 0;
d641 2
d644 1
a644 1
    return SO_EAFNOSUPPORT;
d1657 4
d1765 2
a1766 5
            // in background and waits up to 15 seconds (changeable by
            // I_SETCLTIME ioctl request).
            OSSetAlarm(&obj->lingerAlarm,
                       OSSecondsToTicks((OSTime) 15),
                       LingerTimeout);
d1787 1
a1787 1
        ASSERT(0 <= rc);
d1796 1
a1796 1
    return (rc < 0) ? SO_EBADF : 0;
