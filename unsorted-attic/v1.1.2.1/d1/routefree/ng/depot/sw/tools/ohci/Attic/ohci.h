a0 64
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
 /* Data structures for the OHCI HCD. All section references refer to
    "OpenHCI for USB Release 1.0a". */

#ifndef __OHCI_H__
#define __OHCI_H__
#include <ios.h>
#include <iosdebug.h>
#include <iostypes.h>
#include <iosusbtypes.h>
#include <iosusb.h>

/* Endpoint descriptor [section 4.2] */
#define OHCI_ED_ALIGN 16
typedef struct ohci_ed {
 u32 flags;  
 u32 tailP;
 u32 headP;
 u32 nextED;
} ohci_ed __attribute__((aligned(OHCI_ED_ALIGN));


/* Fields in ohci_ed.flags */
#define OHCI_ED_RSVD_MASK   0x07ffffff 
#define OHCI_ED_FA_MASK     0x0000007f
#define OHCI_ED_EN_MASK     0x00000780

#define OHCI_ED_DIR_MASK    0x00001800
#define OHCI_ED_DIR_TD1     0x00000000  /* Get dir from TD */
#define OHCI_ED_DIR_OUT     0x00000100
#define OHCI_ED_DIR_IN      0x00001000 
#define OHCI_ED_DIR_TD2     0x00001100 /* Get dir from TD */

#define OHCI_ED_SPD_MASK    0x00002000
#define OHCI_ED_SKIP_MASK   0x00004000

#define OHCI_ED_FRMT_MASK   0x00008000
#define OHCI_ED_FRMT_GEN    0x00000000
#define OHCI_ED_FRMT_ISO    0x00008000

#define OHCI_ED_MPS_MASK    0x07ff0000
#define OHCI_ED_GETMPS(t)   ((t & OHCI_ED_MPS_MASK) >> 16)

/* Valid bits in ochi_ed.tailP */
#define OHCI_ED_TAILP_MASK 0xfffffff0

/* Bits in ochi_ed.headP */
#define OHCI_ED_HEADP_MASK 0xfffffff3
#define OHCI_ED_HLT_MASK   0x00000001
#define OHCI_ED_TGL_MASK   0x00000002

/* Valid bits in ochi_ed.nextED */
#define OHCI_ED_NEXTED_MASK 0xfffffff0

#endif /* __OHCI_H__ */
