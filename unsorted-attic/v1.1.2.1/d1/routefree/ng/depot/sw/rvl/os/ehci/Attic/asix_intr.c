a0 538
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

#include "iosusbtypes.h"
#include "iosusb.h"

#ifndef ENABLE_TEST
#define STACK_SIZE 4096
const u8        _initStack[STACK_SIZE];
const u32       _initStackSize = sizeof(_initStack);
const u32       _initPriority = 20;
#endif /* ENABLE_TEST */

#define AX_ENABLE_DBG 1

#ifdef AX_ENABLE_DBG
#define AX_DBG(format, ...) printf(format, ##__VA_ARGS__)
#else
#define AX_DBG(format, ...)
#endif /* OHCI_ENABLE_DBG */


#define AX_SWRESET_DEFAULT    0x4c
#define AX_SWRESET_IPPD		0x40 //int phy power down (1) make 0
#define AX_SWRESET_RR 		0x1  //clr frame length error bulk in(0)
#define AX_SWRESET_RT 		0x2  //clr frame length error bulk out(0)
#define AX_SWRESET_PRTE		0x4  //ext phy reset pin tri-state enab(1)
#define AX_SWRESET_PRL		0x8  //ext phy reset pin lvl (1)
#define AX_SWRESET_BZ		    0x10  //force bulk in to ret 0 len pkt(0) 
#define AX_SWRESET_IPRL		0x20 //int phy reset (0) make 1
#define AX_SWRESET_IPPD		0x40 //int phy power down (1) make 0

#define AX_MONMODE_RWLU_MASK   0x02
#define AX_MONMODE_USBFS_MASK  0x10

#define AX_MEDMODE_RE_MASK     0x0100
#define AX_MEDMODE_RSVD0_MASK  0xffb6 /* bits that are 0 here, must be 0 */
#define AX_MEDMODE_RSVD1_MASK  0x0004 /* bits that are 1 here, must be 1 */

#define AX_PHYREG_BMCR_OFFSET          0
#define AX_PHYREG_BMSR_OFFSET          1
#define AX_PHYREG_PHYIDR1_OFFSET	   2
#define AX_PHYREG_PHYIDR2_OFFSET       3
#define AX_PHYREG_ANAR_OFFSET          4
#define AX_PHYREG_ANLPAR_OFFSET        5
#define AX_PHYREG_ANER_OFFSET          6

#define AX_PHYREG_BMCR_ANE_MASK        0x1000    
#define AX_PHYREG_BMCR_DUP_MASK        0x1000    
#define AX_PHYREG_BMCR_SPD_MASK        0x2000   

#define AX_PHYREG_BMSR_LINKSTAT_MASK   0x0004

#define AX_PHYREG_ANER_LPANAB_MASK     0x0001

#define AX_EEPROM_PHYID_MASK   0x1f

#define AX_RXCTRL_PROMISC_MASK 0x1
#define AX_RXCTRL_SO_MASK      0x0080
#define AX_RXCTRL_MFB_MASK     0x0300

/* Supposed to come from some header exported by net */
#define NET_AUTONEG_ENABLE            0x01
#define NET_AUTONEG_DISABLE           0x00
/* The forced speed, 10Mb, 100Mb, gigabit. */
#define NET_SPEED_10            10
#define NET_SPEED_100           100
#define NET_SPEED_1000          1000

/* Duplex, half or full. */
#define NET_DUPLEX_HALF         0x00
#define NET_DUPLEX_FULL         0x01

typedef struct 
{
    u8 wordCount4Preload;		
    u8 reserved00;
    
    u16 flag;				
    
    u8 offsetHSDevDescr;
    u8 lengthHSDevDescr;
    
    u8 offsetHSConfigDescr;	
    u8 lengthHSConfigDescr;
    
    u8 NodeId[6];
    
    u8 languageIdlow;
    u8 languageIdhi;
    
    u8 offsetMfgStr;
    u8 lengthMfgStr;
    
    u8 offsetProductStr;
    u8 lengthProductStr;
    
    u8 offsetSerialNo;
    u8 lengthSerialNo;
    
    u8 offsetCfgStr;
    u8 lengthCfgStr;
    
    u8 offsetIF0Str;
    u8 lengthIF0Str;
    
    u8 offsetIF1_0Str;
    u8 lengthIF1_0Str;
    
    u8 offsetIF1_1Str;
    u8 lengthIF1_1Str;
    
    u16 phyRegOffsetInterruptEndPoint;
    
    u16 maxPktSize;
    
    u8 primaryPhyInfo; 
    u8 secondaryPhyInfo;
    
    u8 pauseFrameLowWatermark;
    u8 pauseFrameHighWaterMark;
    
    u8 offsetFSDevDescr;
    u8 lengthFSDevDescr;
    
    u8 offsetFSConfDescr;
    u8 lengthFSConfDescr;
} AX_EEPROM;

static void
__usbEthGetMac(IOSFd fd, u8 *mac)
{
    IUSB_ReadCtrlMsg(fd,0xc0, 0x13, 0, 0, 6, mac);
}

static void
__usbEthDumpMac(u8 *__mac)
{
   u8 i;

   AX_DBG("MAC address: ");
   for (i = 0; i < 6; ++i) {
       AX_DBG("%02x", __mac[i]);
       if (i != 5) AX_DBG(":");
   }
   AX_DBG("\n");
}

static void 
readMacTest(IOSFd fd0, u8 *__mac)
{
  __usbEthGetMac(fd0, __mac);
  __usbEthDumpMac(__mac);
  return;
}
static void
AX_ReadEEPROMReg(IOSFd fd, u8 i, u16 *data)
{
    IUSB_ReadCtrlMsg(fd, 0xc0, 0x0b, i, 0, 2, (char *)data);
}
 
void
AX_WriteSWResetReg(IOSFd fd, u16 val)
{
    IUSB_ReadCtrlMsg(fd, 0x40, 0x20, val, 0, 0, 0);
}

void
AX_ReadSWPHYSelStatReg(IOSFd fd, u16 val, char *data)
{
    IUSB_ReadCtrlMsg(fd, 0xc0, 0x21, val, 0, 0x01, data);
}
void
AX_WriteSWPHYSelReg(IOSFd fd, u16 val)
{
    IUSB_WriteCtrlMsg(fd, 0x40, 0x22, val, 0, 0x00, 0);
}

IOSError 
AX_LockPHY(IOSFd fd)
{
    u8 tries = 100;
    u8 lock;
    IOSError rv = IOS_ERROR_OK;
    /*Get lock */
    IUSB_WriteCtrlMsg(fd, 0x40, 0x06, 0, 0, 0, 0);
    while (tries--) {
        IUSB_ReadCtrlMsg(fd, 0xc0,0x09, 0, 0, 0x01, &lock);
        if (1 == (lock & 0x01))
            break;
    }
    if (1 != (lock & 0x01)) {
       rv = IOS_ERROR_ACCESS; 
    }
    return rv;
}

IOSError 
AX_UnlockPHY(IOSFd fd)
{
    u8 tries = 100;
    u8 lock;
    IOSError rv = IOS_ERROR_OK;
    /*Get lock */
    IUSB_WriteCtrlMsg(fd, 0x40, 0x0a, 0, 0, 0, 0);
    while (tries--) {
        IUSB_ReadCtrlMsg(fd, 0xc0,0x09, 0, 0, 0x01, &lock);
        if (0 == (lock & 0x01))
            break;
    }
    if (0 != (lock & 0x01)) {
       rv = IOS_ERROR_ACCESS; 
    }
    return rv;
}

void
AX_ReadPHYReg(IOSFd fd, u16 phy, u16 reg, u16 *data)
{
    if (IOS_ERROR_OK != AX_LockPHY(fd)) 
        goto done;
    IUSB_ReadCtrlMsg(fd, 0xc0, 0x07, phy, reg, 0x02, (char *)data);
    AX_UnlockPHY(fd); 
    *data = SWAP16((*data));
done:
    return;
}

void
AX_WritePHYReg(IOSFd fd, u16 phy, u16 reg, u16 *data)
{
    if (IOS_ERROR_OK != AX_LockPHY(fd)) 
        goto done;
    *data = SWAP16((*data));
    IUSB_WriteCtrlMsg(fd, 0x40, 0x08, phy, reg, 0x02, (char *)data);
    AX_UnlockPHY(fd); 
done:
  return;
}

void	
AX_ReadRxCtrlReg(IOSFd fd, u16 *data)
{
    IUSB_ReadCtrlMsg(fd, 0xc0, 0x0f, 0, 0, 0x02, (char *)data);
    *data = SWAP16((*data));
}

void	
AX_WriteRxCtrlReg(IOSFd fd, u16 d)
{
    IUSB_WriteCtrlMsg(fd, 0x40, 0x10, d, 0, 0, 0);
}

void
AX_ReadMonModeReg(IOSFd fd, u8 *data)
{
    IUSB_ReadCtrlMsg(fd, 0xc0, 0x1c, 0, 0, 1, data);
}

void
AX_WriteMonModeReg(IOSFd fd, u8 data)
{
    IUSB_WriteCtrlMsg(fd, 0x40, 0x1d, data, 0, 0, 0);
}

void
AX_ReadMedModeReg(IOSFd fd, u16 *data)
{
    IUSB_ReadCtrlMsg(fd, 0xc0, 0x1a, 0, 0, 2, (char *)data);
    *data = SWAP16((*data));
}

void
AX_WriteMedModeReg(IOSFd fd, u16 data)
{
    IUSB_ReadCtrlMsg(fd, 0x40, 0x1b, data, 0, 0, 0);
}

static void
__usbEthGetEEPROM(IOSFd fd0, AX_EEPROM *eeprom)
{
    u8 i;
    u16 *data = (u16 *) eeprom;
    for (i = 0; i < 22; ++i) {
        AX_ReadEEPROMReg(fd0, i, &data[i]);
    }
    return;
}

static void
__dumpEEPROM(AX_EEPROM *eeprom)
{
#ifdef AX_ENABLE_DBG
    u8 i;
    u16 *data = (u16 *) eeprom;
    AX_DBG("size of AX_EEPROM = %u\n", sizeof(AX_EEPROM));
    for (i = 0; i < 22; ++i) {
        AX_DBG("EEPROM[%x] = 0x%04x\n", i, SWAP16(data[i]));
    }
#endif /* AX_ENABLE_DBG */
    return;
}

static void
readEEPROMTest(IOSFd fd0, AX_EEPROM *eeprom)
{ 
  __usbEthGetEEPROM(fd0, eeprom);
  __dumpEEPROM(eeprom);
  return;
}

IOSError
getLinkStatus(IOSFd fd0)
{
    char data[512];
    memset(data, 0, sizeof(data));
    IUSB_ReadIntrMsg(fd0, 0x81, 512, data);
    return IOS_ERROR_OK;
}

/* XXX EthCardSettings is an alias struct for NETEthTool */
typedef struct NETEthTool {
    u32 supported;  /* features this interface supports */
    u32 advertising;/* features this interface advertises */
    u16 speed;      /* the forced speed, 10Mb, 100Mb, gigabit */
    u8  duplex;     /* duplex, half or full */
    u8  autoneg;    /* enable or disable autonegotiation */
} NETEthTool;

typedef NETEthTool EthCardSettings;

void
AX_InitEthSettings(IOSFd fd, u16 phy, EthCardSettings *setting)
{
    u16 bmcr = 0;
    u16 bmsr = 0;
    u16 aner = 0;
    u8 iter;

    if (NET_AUTONEG_ENABLE == setting->autoneg) {
        /* Enable auto negotiation */
        AX_ReadPHYReg(fd, phy, AX_PHYREG_BMCR_OFFSET, &bmcr);
        bmcr |= AX_PHYREG_BMCR_ANE_MASK; /* Enable auto neg */
        //bmcr |= AX88772_PHY_REG_BMCR_RST_AN; /* XXX restart auto neg? */
        AX_WritePHYReg(fd, phy, AX_PHYREG_BMCR_OFFSET, &bmcr );

        /* if link down and new page rcvd go fixup ?? */

        iter = 255;
        while ((iter > 0) && (0 == (bmsr & AX_PHYREG_BMSR_LINKSTAT_MASK))) {
            AX_ReadPHYReg(fd, phy, AX_PHYREG_BMSR_OFFSET, &bmsr );
            usleep(25000);
        }
        if( 0 != (bmsr & AX_PHYREG_BMSR_LINKSTAT_MASK)) {
            AX_DBG("BMSR: Link up\n");
        }
        else {
            AX_DBG("BMSR: Link down\n");
            /* XXX  do what? */
            goto done;
        }
        /* Determine if partner can do auto neg */
        AX_ReadPHYReg(fd, phy, AX_PHYREG_ANER_OFFSET, &aner);
        AX_DBG("PHY reg ANER = 0x%x\n", aner);
        if (0 == (aner & AX_PHYREG_ANER_LPANAB_MASK)) {
            AX_DBG("Link partner does not support auto negotiation\n");
            /* XXX do what? */
        }
        else 
            AX_DBG("Link partner supports auto negotiation\n");

        AX_ReadPHYReg(fd, phy, AX_PHYREG_BMCR_OFFSET, &bmcr );
        if (bmcr & AX_PHYREG_BMCR_SPD_MASK) {
            setting->speed= NET_SPEED_100;
        }
        else {
            setting->speed= NET_SPEED_10;
        }
        if (bmcr & AX_PHYREG_BMCR_DUP_MASK) {
            setting->duplex= NET_DUPLEX_FULL;
        }
        else {
            setting->duplex= NET_DUPLEX_HALF;
        }
    }
done:
    return;
}

#define INIT_ATTEMPTS 100 /* How many times to try to see if link is up 
                           * after initialization.
                           */
static IOSError
initEth(IOSFd fd, u16 phy, EthCardSettings *setting)
{
    u16 i;
    u16 data16;
    u8 data8;
    IOSError rv = IOS_ERROR_NOTREADY;
    

    /* Select default PHY */
    /* XXX Don't know why usbeth changes this. */
    AX_ReadSWPHYSelStatReg(fd, phy, &data8);
    AX_DBG("SW PHY select data = %02x\n", data8);
    
    /* This will start the PHY */
    { 
        u16 data = AX_SWRESET_DEFAULT;
        data &= ~AX_SWRESET_IPPD;
        data |= AX_SWRESET_IPRL;
        AX_WriteSWResetReg(fd, data);
    }

    /* XXX debug: Fetch and print PHY regs */
    for (i = 0; i < 7; ++i) {
        AX_ReadPHYReg(fd, phy, i, &data16 );
        AX_DBG("PHY reg %d = 0x%04x\n", i, data16);
    }

    /* Initialize RX Ctrl reg. Start MAC. */
    AX_ReadRxCtrlReg(fd, &data16);
    data16 |= AX_RXCTRL_SO_MASK;   
    data16  &= ~AX_RXCTRL_MFB_MASK; 
    AX_WriteRxCtrlReg(fd, data16);

    /* Enable remote wake up */
    AX_ReadMonModeReg(fd, &data8);
    data8 |= AX_MONMODE_RWLU_MASK;
    AX_WriteMonModeReg(fd, data8);

    /* Enable RX path of ASIC */
    AX_ReadMedModeReg(fd, &data16);
    data16 |= AX_MEDMODE_RE_MASK; 
    AX_WriteMedModeReg(fd, data16);

    /* Set up auto/manual negotiation.
     * Fetch current parameters into setting.
     */
    AX_InitEthSettings(fd, phy, setting);

    /* For some reason the first read always say not ready */
    getLinkStatus(fd);
    /* Interrupt EP should now report that link's up */
    for (i = 0; i < INIT_ATTEMPTS; ++i) {
        if (IOS_ERROR_OK == (rv = getLinkStatus(fd))) {
            goto done;
        }
        usleep(500);
    }
    printf("ASIX initialization failed\n");
done:
    return rv;
}

void
__intrTransferTest(IOSFd fd)
{
   u32 i;
   for (i = 0; i < 1024; ++i) {
       getLinkStatus(fd);
   }
}

static void
__registerInsertionHandlerTest(const char *path, u16 vid, u16 pid)
{
    IOSError rv;
    IOSMessage msgQ[1];
    IOSMessage msg;
    IOSMessageQueueId qid;
    IOSResourceRequest reply; 
    u8 buffer[IUSB_DEVINSERT_BUFSIZE];

    printf("-- RegisterInsertionHandler test\n");
    qid = IOS_CreateMessageQueue(msgQ, 1);
    if (qid < 0) {
        printf("test: creating message queue failed\n");
        goto done;
    }
    rv = IUSB_RegisterInsertionNotify(path, qid, &reply, &vid, &pid, (u8 *) buffer);
    if (rv < 0) {
        printf("test: registering insertion notification handler failed: %d\n", rv);
    } else {
        printf("test: registering insertion notification handler succeeded\n");
        printf("test: waiting for device insertion...\n");
        rv = IOS_ReceiveMessage(qid, &msg, IOS_MESSAGE_BLOCK);
        if (IOS_ERROR_OK != rv) {
            printf("test: failed to receive msg: %d\n", rv);
        } else if (IOS_ERROR_OK == reply.status ){ 
            printf("test: device vid: 0x%04x pid: 0x%04x inserted\n", vid, pid);
        } else {
            printf("RegisterInsertion returned error: %d\n", reply.status);
        }
    }
done:
    printf("** RegisterInsertionHandler test\n");
    return;
}

#ifdef ENABLE_TEST
void
ehci_test(u32 arg)
#else
void
main(u32 arg)
#endif
{
    IOSFd fd0;
    u8 __mac[6];
    AX_EEPROM __eeprom;
    EthCardSettings setting;
    AX_DBG("\n\n*** ASIX driver running ...\n");
    __registerInsertionHandlerTest("/dev/usb/ehc", 0x0b95, 0x7720);
    /* Get here after device has been inserted */
    fd0 = IOS_Open("/dev/usb/ehc/0b95/7720", 0);
    readMacTest(fd0, __mac);
    readEEPROMTest(fd0, &__eeprom); 
    memset(&setting, 0, sizeof(setting));
    setting.autoneg = NET_AUTONEG_ENABLE;
    initEth(fd0, __eeprom.primaryPhyInfo & AX_EEPROM_PHYID_MASK, &setting);
    __intrTransferTest(fd0);
    AX_DBG("ASIX usb ethernet driver exiting \n");
    IOS_DestroyThread(0, NULL);
    return;
}
