d14 3
d21 4
d509 1
a509 1
    memmove(info->broadcast, IPLimited, IP_ALEN);
d562 1
a562 1
    if (IP_ADDR_NE(update->broadcast, IPLimited))
d809 15
a823 15
	switch (messageType)
	{
	  case DHCP_OFFER:
	  case DHCP_ACK:
	    // Check dhcp->yiaddr
	    if (IP_CLASSD(dhcp->yiaddr) ||
	        IP_CLASSE(dhcp->yiaddr) ||
	        IP_ADDR_EQ(dhcp->yiaddr, IPAddrAny) ||
	        IP_ADDR_EQ(dhcp->yiaddr, IPLoopbackAddr) ||
	        IP_ADDR_EQ(dhcp->yiaddr, IPLimited))
	    {
	        return -1;
	    }
	    break;
	}
d1650 5
a1654 1
    IPSetBroadcastAddr(&__IFDefault, info->broadcast);
