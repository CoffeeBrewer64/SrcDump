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

/*---------------------------------------------------------------------------*
 * 
 * Ethernet card setting
 * 
 *---------------------------------------------------------------------------*/

#ifndef __IOP_ETHTOOL_H__
#define __IOP_ETHTOOL_H__

typedef struct NETEthTool {
    u32 supported;  /* features this interface supports */
    u32 advertising;/* features this interface advertises */
    u16 speed;      /* the forced speed, 10Mb, 100Mb, gigabit */
    u8  duplex;     /* duplex, half or full */
    u8  autoneg;    /* enable or disable autonegotiation */
} NETEthTool;

/* The forced speed, 10Mb, 100Mb, gigabit. */
#define NET_SPEED_10            10
#define NET_SPEED_100           100
#define NET_SPEED_1000          1000

/* Duplex, half or full. */
#define NET_DUPLEX_HALF         0x00
#define NET_DUPLEX_FULL         0x01

/* Enable or disable autonegotiation. */
#define NET_AUTONEG_DISABLE     0x00
#define NET_AUTONEG_ENABLE      0x01

/* Indicates what features are supported by the interface. */
#define NET_SUPPORTED_10BASET_HALF      0x01
#define NET_SUPPORTED_10BASET_FULL      0x02
#define NET_SUPPORTED_100BASET_HALF     0x04
#define NET_SUPPORTED_100BASET_FULL     0x08
#define NET_SUPPORTED_1000BASET_HALF    0x10
#define NET_SUPPORTED_1000BASET_FULL    0x20
#define NET_SUPPORTED_AUTONEG           0x40

#endif // __IOP_ETHTOOL_H__
