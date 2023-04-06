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
#ifndef __IOSDEBUG_H__
#define __IOSDEBUG_H__
#include <iostypes.h>


#define __IOS_EMU_DBG__ 1

#if __IOS_EMU_DBG__
#include <stdio.h>
extern FILE *dbg_fp;
#define DBG_PRINTF(x) fprintf x; fflush(dbg_fp);
#define DBG_ENTRY  \
  fprintf(dbg_fp,"Entering: %s\n", __FUNCTION__);
#define DBG_EXIT  \
  fprintf(dbg_fp,"Leaving: %s\n", __FUNCTION__);

#else

#define DBG_PRINTF(x) /* Debug is off */
#define DBG_ENTRY   /* Debug is off */
#define DBG_EXIT   /* Debug is off */

#endif /* __IOS_EMU_DBG__ */
#endif /*__IOSDEBUG_H__*/
