a0 200
/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */
#include <iostypes.h>
#include <ios.h>
#include <iop.h>
#include <ioslibc.h>

#include "ohci.h"
#include "ohci_regs.h"
#include "ohci_core.h"
#include "usb11.h"
#include "ohci_types.h"

extern struct ohci_device __ohci_dev[OHCI_DEV_MAX]; 

/* Format:
 *  1 read buffer with ep.
 *  At least 1 write buffer. At most 8 write buffers.
 *  Write buffer constraints: [OHCI specs: Sec 4.3.2.3.5.4]
 *      - buffers should be contiguous
 *      - max buffer size = 1023*8 bytes
 */

static IOSError
__checkIsoWriteArgs(IOSResourceIoctlv *args)
{
    IOSError rv = IOS_ERROR_OK;
    u16 pktSize, buflen;
    CHK_RDWR(3, 1); 
    if (CHK_VEC(0, sizeof(u8)) || CHK_VEC(1, sizeof(u16))
         || CHK_VEC(2, sizeof(u16))
         || CHK_VEC(3, *((u16 *)args->vector[1].base))) {
        rv = IOS_ERROR_INVALID;
        goto done;
    }
    buflen = *((u16 *)args->vector[1].base);
    pktSize = *((u16 *)args->vector[2].base);
    if ( pktSize > 1023 || buflen/pktSize  > 8
            || ((8 == buflen/pktSize) && (buflen%pktSize != 0))) {
        printf("buffer size %u, packet size %u: invalid\n", buflen, pktSize);
        rv = IOS_ERROR_INVALID;
    }
done:
    return rv;
}

static void
__fillITD(ohci_itd *itd, u8 ep, u8 *buf, u16 buflen, u16 pktSize)
{
//  u32 flags;
  u8 i;
  u32 tmp;
  u8 fc = 0;
  
  itd->bp0 = CPU_TO_OHCI32(((u32)buf) & OHCI_ITD_BP0_MASK);
  itd->be =  CPU_TO_OHCI32(((u32)buf) + buflen  - 1);

  memset((u32 *)itd->psw, 0, sizeof(u32)*4);
  tmp = ((u32)buf & 0xfff); /* Offset within 1st 4K page */
  printf("tmp = %x\n", tmp);
  for (i = 0; i < 4; ++i) {
    u32 psw;
    psw = tmp;
    tmp += pktSize;
    fc++;

    psw |= (tmp << 16);
    itd->psw[i] = CPU_TO_OHCI32(psw);
    fc++;
    tmp += pktSize;
    if (tmp > (((u32)buf & 0xfff) + buflen)) {
        printf("tmp = %u be = 0x%08x\n", tmp, (u32)itd->be);
        break;
    }
  }
  fc -= 1; /* count from 0 */
  itd->flags =  CPU_TO_OHCI32(fc << OHCI_ITD_FC_SHIFT
                              |0xf0000000); /* Set SF later */
  dumpITD(itd);
}

static void
__fillITDSF(ohci_itd *itd, u32 fno)
{
  printf("frame: %x\n", fno);
  itd->flags = CPU_TO_OHCI32((OHCI_TO_CPU32(itd->flags) & 0xffff0000)| (fno & 0xffff));
}

static void
startIsocList(struct ohci_hcd *hcd)
{
    u32 reg;
//    if (0 == ((reg = OHCI_READ(hcd->opregs->ctrl)) & OHCI_CTRL_IE_MASK)) {
    reg = OHCI_READ(hcd->opregs->ctrl);
    reg |= OHCI_CTRL_IE_MASK | OHCI_CTRL_PLE_MASK;
    OHCI_WRITE(hcd->opregs->ctrl, reg);
    OHCI_DBG("Enabled isoc list processing\n");
    //    }
}

IOSError 
ohci_IsoWriteIRP(struct ohci_hcd *hcd, IOSResourceRequest *resReq)
{
    IOSError rv = IOS_ERROR_OK;
    u8 devnum;
    s8 idx = 0;
    u8 ep;
    u16 buflen;
    u16 pktSize;
    u8 *buf;
    //    u32 flags;
    ohci_ed *ed;
    ohci_itd *itd_data = NULL;
    ohci_itd *itd_dummy = NULL;
    //    ohci_itd *itd_tmp = NULL;
    OHCIrp *irp = NULL;
    IOSResourceIoctlv *args = (IOSResourceIoctlv *)&resReq->args.ioctlv;

    if ((rv = __checkIsoWriteArgs(args)) < 0) {
        printf("invalid write iso args\n");
        goto done;
    }

    disableMIE(hcd);
    IOS_FlushMem(hcd->hc_wb);
    IOS_InvalidateRdb(IOS_RB_IOD);

    ep = *((u8 *)args->vector[0].base);
    buflen = *((u16 *)args->vector[1].base);
    buf = args->vector[2].base;
    pktSize = *((u16 *)args->vector[2].base);

    printf("Transfer requested to endpoint: %u buf %p buflen %u\n", 
            ep, buf, buflen);
    devnum = resReq->handle;
   
    irp = IOS_Alloc(__ohcdHeapId, sizeof(OHCIrp));
    if (NULL == irp) {
        rv = IOS_ERROR_MAX;
        printf("failed to alloc irp\n");
        goto err;
    }
    
    idx = getEndpointIdx(devnum, ep);
    if (idx <= 0) {
        printf("failed to find ep %u in device %u\n", ep, devnum);
        rv = IOS_ERROR_INVALID;
        goto err;
    }
    ed = __ohci_dev[devnum].dev.dev.ep[idx].ed;

    irp->req = resReq;
    irp->ntd = 0;
    irp->err = 0;
    irp->done = 0;
    irp->nxt = NULL;
    irp->ed = ed;
    irp->qid = -1;
    irp->data = (void *)buf;
    irp->datalen = buflen;
    irp->clean1 = NULL;
   
    stopED(hcd, ed);
    
    /* ed stopped ------ */
    if (NULL == (itd_dummy = allocITD())) {
        rv = IOS_ERROR_MAX;
        printf("failed to alloc itd\n");
        goto err;
    }
    itd_data = (struct ohci_itd *)OHCI_TO_CPU32(ed->tailP);

    __fillITD(itd_data, ep, buf, buflen, pktSize);
    itd_data->nextTD = CPU_TO_OHCI32(itd_dummy);
    __fillITDSF(itd_data, OHCI_READ(hcd->opregs->prd_start) + 500);
    
    ed->tailP = CPU_TO_OHCI32(itd_dummy);

    printf("ed flags = 0x%08x\n", ed->flags);
    startIsocList(hcd);
    startED(hcd, ed);
    goto done;
err:
    if (NULL != irp)
        IOS_Free(__ohcdHeapId, irp);
    if (NULL != itd_data)
        freeITD(itd_data);
    /* Fall through */
done:
    enableMIE(hcd);
    return rv;
}
