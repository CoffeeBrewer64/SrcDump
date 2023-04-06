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
#ifndef __ADDR_MAP_H__
#define __ADDR_MAP_H__

/* Well-known addresses in RVL */

/* Reserved space */
#define RSVD_SP_START	0x17800000
#define RSVD_SP_END		0x17880000

/*IPC space */
#define IPC_SP_START	0x17880000
#define IPC_SP_END		0x178c0000

/* Free0 space */
#define FREE0_SP_START	0x178c0000
#define FREE0_SP_END    0x17980000

/* DI space */
#define DI_SP_START 	0x17980000
#define DI_SP_END       0x179c0000

/* Free1 space */
#define FREE1_SP_START	0x179c0000
#define FREE1_SP_END    0x17a80000

/* File system */
#define FS_SP_START	    0x17a80000
#define FS_SP_END		0x17b40000

/* File system BSS*/
#define FS_BSS_SP_START	    0x17a80000
#define FS_BSS_SP_END		0x17b80000

/* Free2 space */
#define FREE2_SP_START	    0x17b80000
#define FREE2_SP_END        0x17c80000

/* Crypto space */
#define CRYPTO_SP_START	    0x17c80000
#define CRYPTO_SP_END       0x17d00000

/* Shared Data */
#define SHARED_SP_START		0x17d00000
#define SHARED_SP_END		0x17d80000
#define SHARED_SP_SIZE		0x80000

/* Application space */
#define APP_SP_START    	0x17d80000
#define APP_SP_END		    0x18000000

#endif /* __ADDR_MAP_H__ */
