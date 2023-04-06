d56 1
a56 1
__fillITD(ohci_td *td, OHCIrp *irp, u8 *buf, u16 buflen, u16 pktSize)
d58 1
d63 2
a64 6
  td->cbp = CPU_TO_OHCI32(((u32)buf) & OHCI_ITD_BP0_MASK); /* bp0 */
  td->be =  CPU_TO_OHCI32(((u32)buf) + buflen  - 1);
  td->irp = irp;
  td->len = buflen;
  ++irp->ntd;
  
d66 1
a66 1
  memset((u32 *)td->psw, 0, sizeof(u32)*4);
d75 2
a76 2
        printf("tmp = %u be = 0x%08x\n", tmp, (u32)td->be);
        td->psw[i] = CPU_TO_OHCI32(psw);
d81 1
a81 1
    td->psw[i] = CPU_TO_OHCI32(psw);
d85 1
a85 1
        printf("tmp = %u be = 0x%08x\n", tmp, (u32)td->be);
d90 1
a90 1
  td->flags =  CPU_TO_OHCI32(fc << OHCI_ITD_FC_SHIFT
d92 1
a92 1
  dumpITD(td);
d96 1
a96 1
__fillITDSF(ohci_td *td, u32 fno)
d99 1
a99 1
  td->flags = CPU_TO_OHCI32((OHCI_TO_CPU32(td->flags) & 0xffff0000)| (fno & 0xffff));
d122 2
a123 2
    ohci_td *td_data = NULL;
    ohci_td *td_dummy = NULL;
d171 1
a171 1
    if (NULL == (td_dummy = allocTD())) {
d173 1
a173 1
        printf("failed to alloc td\n");
d176 1
a176 1
    td_data = (struct ohci_td *)OHCI_TO_CPU32(ed->tailP);
d178 4
a181 4
    __fillITD(td_data, irp, buf, buflen, pktSize);
    td_data->nextTD = CPU_TO_OHCI32(td_dummy);
    __fillITDSF(td_data, OHCI_READ(hcd->opregs->frm_num) + 5);
    ed->tailP = CPU_TO_OHCI32(td_dummy);
d191 2
a192 2
    if (NULL != td_data)
        freeTD(td_data);
