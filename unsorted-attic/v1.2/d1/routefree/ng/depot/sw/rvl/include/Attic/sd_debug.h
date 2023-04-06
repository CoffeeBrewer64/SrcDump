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

#ident "$Id: sd_debug.h,v 1.1 2006/03/16 19:22:55 gbarnard Exp $"

/*
 * This file contains constants and macros used in SD/SDIO driver
 * debugging.
 */

/*
 * Defines
 */


#define DEBUG_SER_ERR            0x00000001
#define DEBUG_SER_INIT           0x00000002
#define DEBUG_SER_PROBE          0x00000004
#define DEBUG_SER_OPEN           0x00000008
#define DEBUG_SER_CLOSE          0x00000010
#define DEBUG_SER_IOCTL          0x00000020
#define DEBUG_SER_IRQ            0x00000040
#define DEBUG_SER_REMOVE         0x00000080
#define DEBUG_SER_REG_READ       0x00000100
#define DEBUG_SER_REG_WRITE      0x00000200
#define DEBUG_SER_CMD            0x00000400
#define DEBUG_SER_REG_MREAD      0x00000800
#define DEBUG_SER_REG_MWRITE     0x00001000
#define DEBUG_SER_SD_CMD         0x00002000
#define DEBUG_SER_SD_SETUP       0x00004000
#define DEBUG_PCI_ERR            0x00000001
#define DEBUG_PCI_INIT           0x00020000
#define DEBUG_PCI_PROBE          0x00040000
#define DEBUG_PCI_OPEN           0x00080000
#define DEBUG_PCI_CLOSE          0x00100000
#define DEBUG_PCI_IOCTL          0x00200000
#define DEBUG_PCI_IRQ            0x00400000
#define DEBUG_PCI_REMOVE         0x00800000
#define DEBUG_PCI_REG_READ       0x01000000
#define DEBUG_PCI_REG_WRITE      0x02000000
#define DEBUG_PCI_REG_MREAD      0x04000000
#define DEBUG_PCI_REG_MWRITE     0x08000000
#define DEBUG_PCI_IRQN           0x10000000


/*
 * Macros
 */
#ifdef LINUX
	#define PCI_DEBUG(x, y, ...) if (sdpci_debug & x) printk (KERN_INFO y, __VA_ARGS__);
	#define SER_DEBUG(x, y, ...) if (ser_debug & x) printk (KERN_INFO y, __VA_ARGS__);
#else
	#define PCI_DEBUG(x, y, ...) if (sdpci_debug & x) printf (y, __VA_ARGS__);
	#define SER_DEBUG(x, y, ...) if (ser_debug & x) printf (y, __VA_ARGS__);
#endif
/*
 * Structs
 */

/*
 * Externs
 */
//extern int pci_debug;
extern int ser_debug;

/*
 * Prototypes
 */

/* eof */
