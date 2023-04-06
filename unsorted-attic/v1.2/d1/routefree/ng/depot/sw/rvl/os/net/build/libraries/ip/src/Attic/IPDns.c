d14 3
d21 47
d205 1
a205 1
 
d212 3
d217 4
a220 2
#define MIN_WAIT        1000    // [msec]
#define MAX_WAIT        20000   // [msec]
d294 1
a294 1
    
d564 1
a564 1
static u8* SkipName(u8* ptr, u8* end)
d568 1
a568 1
    for (;;)
a569 4
        if (end <= ptr)
        {
            return NULL;
        }
d573 1
a573 1
            return (ptr <= end) ? ptr : NULL;
d584 1
a584 1
            return (ptr <= end) ? ptr : NULL;
d589 1
d592 2
a593 1
static char* CopyName(DNSHeader* dns, u8* end, u8* ptr, char* name, s32 namelen)
d597 5
a601 1
    while (*ptr && 1 < namelen)
a610 4
            if (ptr < (u8*) dns || end <= ptr)
            {
                return NULL;
            }
d613 1
a613 1
        if (end < ptr + count + 1)
d617 1
a617 2

        if (namelen <= count)
d619 1
a619 1
            count = namelen - 1;
d621 1
a621 1
        namelen -= count;
d623 2
a624 2
        memmove(name, ++ptr, (u32) count);
        ptr  += count;
d630 5
d636 1
a636 2
    *name = '\0';
    return name;
d639 1
a639 1
static u8* DupName(u8* opt, DNSHeader* dns, u8* ptr)
d641 2
a642 1
    u8 count;
d644 1
a644 1
    while (*ptr)
d652 9
d662 4
d670 132
a801 2
    *opt++ = 0;
    return opt;
d817 1
a817 1
    ptr = SkipName(ptr, end);
d856 1
a856 1
        ptr = SkipName(ptr, end);
d865 1
a865 1
        ptr = SkipName(ptr, end);
d870 1
a870 1
        ptr = SkipName(ptr, end);
d875 1
a875 1
        ptr = SkipName(ptr, end);
d879 1
a879 1
        ptr = SkipName(ptr, end);
d884 1
a884 1
        ptr = SkipName(ptr, end);
d905 1
a905 1
        ptr = end;
a913 1

d928 2
a929 1
    info->rxmit = OSMillisecondsToTicks((OSTime) MIN_WAIT);
d945 1
a945 2
            info->flag &= ~(DNS_FLAG_BROADCAST | DNS_FLAG_MULTICAST);
            if (IPIsBroadcastAddr(interface, info->socket.addr))
d947 1
a947 1
                info->flag |= DNS_FLAG_BROADCAST;
d949 1
a949 1
            else if (IP_CLASSD(info->socket.addr))
d951 1
a951 1
                info->flag |= DNS_FLAG_MULTICAST;
d1011 1
a1011 1
            (info->recvedLen < info->recvLen + 2 &&
d1024 1
a1024 1
            result = info->recvedLen - 2;
a1033 1
        // XXX maybe we should keep tcp open for a while
d1035 1
d1045 1
d1053 3
a1055 1
            OSSetAlarm(&info->alarm, info->rxmit, TimeoutCallback);
d1068 2
a1069 1
                OSSetAlarm(&info->alarm, OSMillisecondsToTicks((OSTime) MAX_WAIT), TimeoutCallback);
d1082 1
d1118 1
a1125 1
        TCPCloseAsync(&info->tcp, NULL, NULL);
a1269 1
        OSCancelAlarm(&info->alarm);
d1348 25
a1374 1
        info->flag &= ~DNS_FLAG_EDNS0;  // Not try using EDNS0 again
a1409 1
        info->flag &= ~DNS_FLAG_EDNS0;
a1425 1
        OSCancelAlarm(&info->alarm);
d1458 2
a1459 4
    info->rxmit <<= 1;

    if ((info->flag &= DNS_FLAG_EDNS0) &&
        OSMillisecondsToTicks((OSTime) MAX_WAIT) < info->rxmit)
d1466 1
a1466 1
        info->rxmit = OSMillisecondsToTicks((OSTime) MIN_WAIT);
d1469 1
a1469 1
    if ((info->rxmit < OSMillisecondsToTicks((OSTime) MAX_WAIT) || 0 <= SwitchServer(info)) &&
d1644 1
a1644 1
    info->rxmit = OSMillisecondsToTicks((OSTime) MIN_WAIT);
d1695 1
d1711 1
d1714 1
a1714 1
        if (DNS_NAME_MAX - 1 <= opt - info->query)
d1723 1
a1723 1
                DNS_NAME_MAX - 1 <= opt - info->query)
d2125 1
d2127 1
d2134 1
d2151 1
d2167 1
d2169 1
d2172 1
a2172 1
        if (DNS_NAME_MAX - 1 <= opt - info->query)
d2181 1
a2181 1
                DNS_NAME_MAX - 1 <= opt - info->query)
d2232 13
d2284 1
d2290 28
a2317 1
        for (i = 0; i < dns->ancount; ++i)
d2321 11
a2331 1
            switch (*(u16*) res)
d2333 33
a2365 2
              case DNS_TYPE_SRV:
                // XXX currently choose the 1st one.
d2367 5
a2371 2
                // Record srv->port.
                cmd->data.ai.port = *(u16*) (res + DNS_OFFSET_SRV_PORT);
d2373 1
a2373 5
                req = DupName(req, dns, res + DNS_OFFSET_SRV_TARGET);
                *(u16*) req = DNS_TYPE_A;
                req += 2;
                *(u16*) req = DNS_CLASS_IN;     // Class = Internet
                req += 2;
d2375 5
a2379 1
                info->queryLen = req - info->query;
d2381 9
a2389 5
                if ((info->flag & DNS_FLAG_EDNS0) && !(info->flag & DNS_FLAG_TCP))
                {
                    req = AppendOpt(dns, req);
                }
                info->sendLen = (u16) (req - info->query);
d2391 3
a2393 2
                cmd->precallback = NULL;
                switch (cmd->data.ai.hints->family)
d2395 19
a2413 2
                  case SO_PF_INET:
                    cmd->data.ai.type = DNS_TYPE_A;
d2415 1
a2415 3
#ifdef IP_INET6
                  case SO_PF_INET6:
                    cmd->data.ai.type = DNS_TYPE_AAAA;
a2416 1
#endif // IP_INET6
a2417 8
                cmd->callback = GetAddrInfoCallback;
                IFEnqueueHead(DNSCommand*, &info->queue, cmd, link);
                return;
                // NOT REACHED HERE

                break;
              default:
                break;
d2422 10
d2433 1
d2483 2
d2487 2
d2520 1
a2526 2
    // If no SRV records were found, the client performs an A or AAAA record
    // lookup of the domain name. [RFC 3263] XXX
d2708 1
d2722 1
d2734 1
d2744 1
d2766 1
d2772 1
d2858 1
a2858 1
    
d3365 1
d3370 1
d3396 1
d3442 37
