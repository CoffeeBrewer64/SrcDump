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
 * type definitions used inside the network stack
 * 
 *---------------------------------------------------------------------------*/

#ifndef __IOP_TYPES_H__
#define __IOP_TYPES_H__

typedef float               f32;
typedef double              f64;
typedef volatile f32        vf32;
typedef volatile f64        vf64;

#ifndef BOOL
typedef int                 BOOL;
#endif  // BOOL

#ifndef TRUE
// Any non zero value is considered TRUE
#define TRUE                1
#endif  // TRUE

#ifndef FALSE
#define FALSE               0
#endif  // FALSE

#ifndef NULL
#ifdef  __cplusplus
#define NULL                0
#else   // __cplusplus
#define NULL                ((void *)0)
#endif  // __cplusplus
#endif  // NULL

#define DOLPHIN_ALIGNMENT 32

// Use the following pragma wherever specific alignment is required for
// static variables.
#define ATTRIBUTE_ALIGN(num) __attribute__ ((aligned (num)))

#endif  // __IOP_TYPES_H__
