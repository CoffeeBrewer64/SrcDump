/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

// $Id: at_latch64.v,v 1.1 2002/05/21 23:55:42 berndt Exp $

////////////////////////////////////////////////////////////////////////
//
// Project Reality
//
// module:      at_latch64
// description: Data delay latch for attribute buffers.
//
// designer:    Phil Gossett
// date:        9/5/94
//
////////////////////////////////////////////////////////////////////////

module at_latch64(clkn, i, z);

input clkn;
input [63:0] i;

output [63:0] z;

at_latch_l #(64) l(.en(clkn), .d(i), .q(z));

endmodule // at_latch64
