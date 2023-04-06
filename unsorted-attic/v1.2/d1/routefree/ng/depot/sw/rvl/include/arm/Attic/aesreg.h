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
#ifndef __AES_REG_H__
#define __AES_REG_H__

/* AES Unit */
#define AES_BASE_REG            AES_BASE

#define AES_CTRL_REG            (AES_BASE+AESCTRL)
#define AES_CTRL_EXEC           0x80000000
#define AES_CTRL_MASK           0x40000000
#define AES_CTRL_MVIOL	        0x20000000
#define AES_CTRL_MVIOL_SHIFT    29

#define AES_CTRL_CMD_MASK       0x18000000
#define AES_CTRL_CMD_SHIFT      27
#define AES_CTRL_CMD(v)        ((v) << AES_CTRL_CMD_SHIFT)
#define AES_CTRL_GET_CMD(v)   (((v) & AES_CTRL_CMD_MASK) >> AES_CTRL_CMD_SHIFT)

#define AES_CTRL_CHAIN          0x00001000	/* Bit 12 */

#define AES_CTRL_SIZE_MASK      0x00000fff	/* Bit 11:0 */
#define AES_MAX_BLOCKS          4096		/* Bit 11:0 */

#define AES_DMA_CMD             0
#define AES_KEYEXPAND_CMD       1
#define AES_ENCRYPT_CMD         2
#define AES_DECRYPT_CMD         3

#define AES_NO_VIOL             0
#define AES_DMA_VIOL            1

#define AES_RPTR_REG            (AES_BASE+AESRDPTR)
#define AES_RPTR_PTR_MASK       0xfffffff0

#define AES_WPTR_REG            (AES_BASE+AESWRPTR)
#define AES_WPTR_PTR_MASK       0xfffffff0

#define AES_IVPTR_REG           (AES_BASE+AESWIV)
#define AES_IVPTR_PTR_MASK      0xfffffff0

#define AES_KEY_REG             (AES_BASE+AESWKEY)
#define AES_WKEY_PTR_MASK       0xfffffff0

#endif /*__AES_REG_H__*/
