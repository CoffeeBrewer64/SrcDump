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
#define __SK_EMULATOR__
#ifdef __SK_EMULATOR__
#include <skerrno.h>
#include <sktypes.h>
#include <ngtypes.h>

#include <stdio.h>

static  const char *sk_errlist[] = {
  "Success",                             /* SK_ERROR_OK        */
  "Permission denied",                   /* SK_ERROR_ACCESS    */
  "File exists",                         /* SK_ERROR_EXISTS    */
  "Interrupted system call",             /* SK_ERROR_INTR      */    
  "Invalid argument",                    /* SK_ERROR_INVALID   */
  "Resource limit exceeded",              /* SK_ERROR_MAX       */
  "No such file or directory",           /* SK_ERROR_NOEXISTS  */    
  "Queue empty",                         /* SK_ERROR_QEMPTY    */   
  "Queue full",                          /* SK_ERROR_QFULL     */   
  "Unknown error",                       /* SK_ERROR_UNKNOWN   */     
  "Not ready",                           /* SK_ERROR_NOTREADY  */  
  "USB error",                           /* SK_ERROR_USB_ERR   */
  "Invalid errno"            /* Last entry: SK_ERROR_INVALID_ERRNO*/  
};
static inline SKError sk_erridx (SKError i) 
{
  if ( i <= SK_ERROR_INVALID_ERRNO || i > 0)
    return -SK_ERROR_INVALID_ERRNO;
  return -i;
}
void
SK_Perror(const char *s, SKError err)
{
  printf("%s:%s\n",s, sk_errlist[sk_erridx(err)]);
}
#endif /*  __SK_EMULATOR__ */
