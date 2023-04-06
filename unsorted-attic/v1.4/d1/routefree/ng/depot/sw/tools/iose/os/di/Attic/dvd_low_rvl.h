#ident "$Id: dvd_low_rvl.h,v 1.3 2006/03/20 23:02:10 craig Exp $"
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

#ifndef DVD_LOW_RVL_H
#define DVD_LOW_RVL_H

#include <stdint.h>

typedef struct diskState {
    bool        isRvlDisk;
    /* false after power on/reset, true after DVDDiskInfo is read */
    bool        hashEncryptedValid;
    bool        encrypted;
    bool        hashesValid;    /* If false, don't verify hashes */
    bool        hashesExist;    /* If false, 1K hash subblocks not present */
    /* false after power on/reset, true after game partition is read */
    bool        gameMetaDataRead;
    uint32_t    h3WordOffset;       /* Disk offset to the start of H3 Hashes */
    uint32_t    h3Size;
    uint32_t    dataWordOffset;     /* Disk offset to the start of data */
    uint32_t    lastDiskOffset;     /* Last value for DI_OFFSET_CMD command */      
} diskState_t;

extern diskState_t      diskState;

void                    resetDriverState(void);
uint32_t                doRvlRead(uint8_t *destAddr, uint32_t byteLength,
                                  uint32_t virtWordOffset);
uint32_t                doReadHashEncryptedState(void);
#endif
