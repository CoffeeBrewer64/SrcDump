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
#define __IOS_EMULATOR__
#ifdef __IOS_EMULATOR__
#include <ioserrno.h>
#include <iostypes.h>

#include <stdio.h>

static  const char *ios_errlist[] = {
  "Success",                             /* IOS_ERROR_OK        */
  "Permission denied",                   /* IOS_ERROR_ACCESS    */
  "File exists",                         /* IOS_ERROR_EXISTS    */
  "Interrupted system call",             /* IOS_ERROR_INTR      */    
  "Invalid argument",                    /* IOS_ERROR_INVALID   */
  "Resource limit exceeded",              /* IOS_ERROR_MAX       */
  "No such file or directory",           /* IOS_ERROR_NOEXISTS  */    
  "Queue empty",                         /* IOS_ERROR_QEMPTY    */   
  "Queue full",                          /* IOS_ERROR_QFULL     */   
  "Unknown error",                       /* IOS_ERROR_UNKNOWN   */     
  "Not ready",                           /* IOS_ERROR_NOTREADY  */  
  "USB error",                           /* IOS_ERROR_USB_ERR   */
  "Invalid errno"            /* Last entry: IOS_ERROR_INVALID_ERRNO*/  
};
static inline IOSError ios_erridx (IOSError i) 
{
  if ( i <= IOS_ERROR_INVALID_ERRNO || i > 0)
    return -IOS_ERROR_INVALID_ERRNO;
  return -i;
}
void
IOS_Perror(const char *s, IOSError err)
{
  printf("%s:%s\n",s, ios_errlist[ios_erridx(err)]);
}
#endif /*  __IOS_EMULATOR__ */
