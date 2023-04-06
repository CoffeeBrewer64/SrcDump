d94 1
a94 3
                              |0xf0000000
                              |OHCI_TD_TYPE_ITD); /* Set SF later */
#ifdef ENABLE_OHCI_DBG
a95 1
#endif
d141 1
a141 1
    buf = args->vector[3].base;
d144 1
a144 1
    OHCI_DBG("ISO transfer requested to endpoint: %u buf %p buflen %u\n", 
d183 1
a183 1
    __fillITDSF(td_data, OHCI_READ(hcd->opregs->frm_num) + 50);
