/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 * $Id: boot2.h,v 1.1 2006/05/05 23:43:06 cnguyen Exp $
 */
#ifndef __BOOT2_H__
#define __BOOT2_H__

#include <sdi.h>
#include <sd_api.h>

/*
 * Hide to turn off debug
 */
#define BOOT2_DEBUG

/*
 * Boot3 final location
 */
#define BOOT3_ADDR                    0x0d400000

/*
 * Boot3 staging address
 */
#define BOOT3_DECODE_BUFFER           0x00000800
#define BOOT3_STAGE_ADDR              0x00001800
#define BOOT3_START_PAGE              0x0
#define SD_PAGE_LEN                   0x800
#define SD_PAGE_SHIFT                 11
#define SD_MAX_PAGES                  64
#define SD_MAX_PAGE_SHIFT             6
#define ALIGN_SZ                      64

/* 
 * Delay for LED output
 */
#define LED_DELAY           1000000

/* 
 * Boot failure codes 
 */
#define BOOT_ERR_NOEXISTS             0x70
#define BOOT_ERR_INVALID              0x71
#define BOOT_ERR_FL_INIT              0x72
#define BOOT_ERR_FL_RD                0x73
#define BOOT_ERR_AES                  0x74
#define BOOT_ERR_SD                   0x75
#define BOOT_ERR_WAD                  0x76
#define BOOT_ERR_ELF                  0x77
#define BOOT_ERR_ETICKET              0x78

#ifdef BOOT2_DEBUG

#define BOOT2_ENTRY()                                          \
   do {                                                        \
              printf("%s: enter >>> %s(), line %d\n",          \
                     __FILE__, __FUNCTION__, __LINE__);        \
   } while (0)

#define BOOT2_EXIT()                                           \
   do {                                                        \
              printf("%s: leave <<< %s(), line %d\n",          \
                     __FILE__, __FUNCTION__, __LINE__);        \
   } while (0)

#else

#define BOOT2_ENTRY()                (void)(0)
#define BOOT2_EXIT()                 (void)(0)

#endif /* BOOT2_DEBUG */

/*
 * Prototypes
 */
extern IOSError init_aes(void);
extern IOSError sd_init (void);
extern IOSError sd_read(u32 offset, u32 *data, u32 length);
extern IOSError aes_decode(u8 *inputData, u32 inputSize, u8 *outputData);

#ifdef BOOT2_DEBUG

extern char *sd_status_decode (SD_API_STATUS status);

#else

#define sd_status_decode()           (void)(0)

#endif /* BOOT2_DEBUG */

#endif /* __BOOT2_H__ */

/* eof */
