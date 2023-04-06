d12 1
a12 1
#ident "$Id: sdstdhost.c,v 1.26 2005/11/16 21:44:27 jlivesey Exp jlivesey $"
d327 10
a336 8
    do {
        for (dwSlot = 0; dwSlot < sdh->m_slotcount; ++dwSlot) {
            pSlot = &sdh->m_sdslot[dwSlot];

            if (((1 << dwSlot) & dwIntStatus) /* || pSlot->NeedsServicing() */ ) {
                SDHostslot_Handleinterrupt(pSlot);
                dwIntStatus &= ~(1 << dwSlot);
            }
d338 1
a339 6
    } while (dwIntStatus);

    /*
     * Usually return from function with ISR_DONE
     */
    // InterruptDone(m_dwSysIntr);
