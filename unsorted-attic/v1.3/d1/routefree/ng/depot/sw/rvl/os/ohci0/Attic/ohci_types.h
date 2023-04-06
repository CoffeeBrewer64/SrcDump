#ifndef __OHCI_TYPES_H__
#define __OHCI_TYPES_H__
#include <types.h>

/* Ioctl commands
 * These are values for u32 cmd in struct IOSResourceIoctl.
 */
#define OHC_CTRL_MSG           0         
#define OHC_BLK_MSG            1
#define OHC_INTR_MSG           2
#define OHC_RESET_DEV          3
#define OHC_SUSPEND_MSG        5
#define OHC_RESUME_MSG         6
#define OHC_ISO_MSG            8
#define OHC_GET_DEVLIST_MSG   12
#define OHC_GET_RHDESCA_MSG   15
#define OHC_GET_RHPSTAT_MSG   20
#define OHC_SET_RHPSTAT_MSG   25
#define OHC_NOTIFYREMOVAL_MSG  26
#define OHC_NOTIFYINSERT_MSG  27

#define OHC_RSVD_HANDLE        0x7f

#define OHCI_TD_TYPE_TD     0x00000000 
#define OHCI_TD_TYPE_ITD    0x00010000 

typedef struct {
    /* hc sees these */
    u8 bmRequestType;
    u8 bRequest;
    u16 wValue;
    u16 wIndex;
    u16 wLength;
    u32 data;

    /* hcd use only */
    u8 ep;
    u8 addr;
} OHCCtrlReq;

typedef struct OHCIrp{
    IOSResourceRequest *req;
    s8 ntd;                  /* Number of TDs in this request */
    s32 done;                /* Bytes transferred */
    void *data;              /* Data to be read or written */
    u32 datalen;             /* Size of transferred data */
    struct ohci_td *td_list; /* List of TDs in this request */
    struct ohci_ed *ed;     
    struct OHCIrp *nxt;
    IOSMessageQueueId qid; /* for internal use only */
    OHCCtrlReq *clean1;
} OHCIrp;

typedef struct OHCDeviceInfo{
    IOSFd fd;
    u16 vid;
    u16 pid;
}OHCDeviceInfo;

typedef struct {
 u8 maxDev;
 u8 deviceClass;
 u8 *numDev;
 OHCDeviceInfo *deviceList;
} OHCGetDevListReq;
#endif /* __OHCI_TYPES_H__ */
