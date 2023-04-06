#ident "$Id: dvd_command.h,v 1.6 2006/03/05 04:17:12 craig Exp $"
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

/*
 */

#ifndef DVD_COMMAND_H
#define DVD_COMMAND_H

#include <stdint.h>

/*
 * This structure must be of length 32 or a multiple thereof
 */
typedef struct diCommand {
    /* Command code or psuedo-command code from dvd_hw.h */
    uint8_t     theCommand;
    uint8_t     pad1[3];
    uint32_t    arg[5];
    uint32_t    pad2[2];
} diCommand_t;

extern diCommand_t      interfaceDiCommand;

/*
 * This structure must be of length 32 or a multiple thereof
 */
typedef struct diRegVals {
    uint32_t    ImmRegVal;
    uint32_t    unused[3];
} diRegVals_t;

/*
 * These are the values taken by the argument to the
 * callback function
 */

#define DVD_INTTYPE_TC                  0x00000001
#define DVD_INTTYPE_DE                  0x00000002
#define DVD_INTTYPE_CVR                 0x00000004
#define DVD_INTTYPE_BRK                 0x00000008
#define DVD_INTTYPE_TIMEOUT             0x00000010
#define DVD_INTTYPE_SECURITY_ERROR      0x00000020

#endif /* DVD_COMMAND_H */
