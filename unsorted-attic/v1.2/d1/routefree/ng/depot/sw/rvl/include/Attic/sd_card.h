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

#ident "$Id: sd_card.h,v 1.1 2006/03/16 19:22:55 gbarnard Exp $"

/*
 * Defines
 */

/*
 * SDIO R/W Flags, SDIO SPec 1.10 section 5.1
 */
#define SDIO_READ_FLAG  0
#define SDIO_WRITE_FLAG 1

#define SDIO_DO_RAW     1
#define SDIO_NO_RAW     0

/*
 * Command codes from the SDIO Specification 1.10.
 */
#define CMD_IO_RW_DIRECT            52
#define CMD_IO_RW_EXTENDED          53

/*
 * Macros
 */

/*
 * Commmand register (0x0e) format
 */
#define CMD_FORMAT(index, type, data_present, index_check, crc_check, resp_type) \
        (((index & 0x3f) << 8) | \
         ((type & 0x3) << 6) | \
         ((data_present & 0x1) << 5) | \
         ((index_check & 0x1) << 4) | \
         ((crc_check & 0x1) << 3) | \
          (resp_type & 0x7))
 
/*
 * SDIO direct I/O commands
 *
 * Data format is as follows:
 *
 *   31   30  28  27   26   25             9   8  7          0
 * +-----+------+-----+---+------------------+---+------------+
 * | R/W | Func | Raw | S | Register Address | S | Write Data |
 * +-----+------+-----+---+------------------+---+------------+
 *    1     3      1    1          17          1        8
 */
#define IO_RW_DIRECT_ARG(Read_Write, Function, Raw, Address, Data) \
        (((Read_Write & 1) << 31) | \
         ((Function & 0x7) << 28) | \
         ((Raw & 1) << 27) | \
         ((0 & 1) << 26) | \
         ((Address & 0x1ffff) << 9) | \
         ((0 & 1) << 8) | \
         (Data & 0xff))

/*
 * SDIO extended I/O commands
 *
 * Data format is as follows:
 *
 *   31   30  28  27   26   25             9   8             0
 * +-----+------+-----+---+------------------+----------------+
 * | R/W | Func | Blk | O | Register Address |   Data Count   |
 * +-----+------+-----+---+------------------+----------------+
 *    1     3      1    1          17          1        8
 */
#define IO_RW_DIRECT_EXT_ARG(Read_Write, Function, Blk, Op, Address, Count) \
        (((Read_Write & 1) << 31) | \
         ((Function & 0x7) << 28) | \
         ((Blk & 1) << 27) | \
         ((Op) << 26) | \
         ((Address & 0x1ffff) << 9) | \
         (Count & 0x1ff))
/*
 * Typedefs
 */

/*
 * Structs
 */

/*
 * Prototypes
 */

/* eof */
