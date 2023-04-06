d12 1
a12 1
#ident "$Id: sd_api.c,v 1.8 2006/01/13 23:02:50 gbarnard Exp $"
a36 4
	#ifdef VERSA
		#include "ios_pci.h"
		#include <versaios.h>
	#endif
d40 5
a44 5
	#include "../../include/sd.h"
	#include "../../include/sd_card.h"
	#include "../../include/sd_host.h"
	#include "../../include/sd_ioctl.h"
	#include "../../include/sdio_rm.h"
d85 2
a86 3
 * Call Host Present State
 * 
 * Call Host Present State, Call AFTER Attach() to driver!
d97 1
d100 1
a100 1
     #if 0
d424 14
a437 8
    
	status = ISD_ResetDevice(*fd);
	
	if (status==IOS_ERROR_OK)
	{
		(*fd)->SDMountState++;
	}
	
d483 3
a485 3
    /*
    printf ("%s SD Command:%d Arg:0x%X\n",__FUNCTION__,command,cmd_arg);
    */
d492 6
d911 1
d927 13
d946 1
a946 1
    /* READ_BL_LEN 	83:80 - 64 = 19:16 */
d954 1
a954 1
    /* sector_size[7] 45:39 -8 37:31 split */
d961 7
a968 1
    if (sector_size) total_sectors = 0; //(memory_capacity/sector_size)>>read_bl_len;
