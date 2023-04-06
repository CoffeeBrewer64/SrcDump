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
#ifndef __SKERRNO_H__
#define __SKERRNO_H__
#include <ng.h>
#include <ngtypes.h>

#define SK_ERROR_OK              0
#define SK_ERROR_ACCESS         -1
#define SK_ERROR_EXISTS         -2
#define SK_ERROR_INTR           -3
#define SK_ERROR_INVALID        -4
#define SK_ERROR_MAX            -5
#define SK_ERROR_NOEXISTS       -6
#define SK_ERROR_QEMPTY         -7
#define SK_ERROR_QFULL          -8
#define SK_ERROR_UNKNOWN        -9
#define SK_ERROR_NOTREADY       -10
#define SK_ERROR_USB_ERR        -11
#define SK_ERROR_INVALID_ERRNO  -12  /* Leave this as last errno */
#endif /*__SKERRNO_H__*/
