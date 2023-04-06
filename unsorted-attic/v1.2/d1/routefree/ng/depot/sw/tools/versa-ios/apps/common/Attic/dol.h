/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished proprietary information of BroadOn Communications Corp.,
 *  and are protected by federal copyright law. They may not be disclosed
 *  to third parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 *  Description:
 *  Adapted from Nintendo's sample code to load .dol files and from
 *  orcatools in ATi's tree.
 */
#include <iostypes.h>
#include <ioslibc.h>

#define DOL_MAX_TEXT 7
#define DOL_MAX_DATA 11

typedef struct DolImage
{
    u8*     textData[DOL_MAX_TEXT]; // actual text segments
    u8*     dataData[DOL_MAX_DATA]; // actual data segments

    u32     text[DOL_MAX_TEXT];     // virtual address destination
    u32     data[DOL_MAX_DATA];     // virtual address destination

    u32     textLen[DOL_MAX_TEXT];  // length of each text segment
    u32     dataLen[DOL_MAX_DATA];  // length of each data segment

    u32     bss;                    // All bss sections lumped together
    u32     bssLen;

    u32     entry;                  // entry point

#if ((3*(DOL_MAX_TEXT+DOL_MAX_DATA)+3)*4)%32
    u8       padding[32-((3*(DOL_MAX_TEXT+DOL_MAX_DATA)+3)*4)%32];
#endif
} DolImage;

