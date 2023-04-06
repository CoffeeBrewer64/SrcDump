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

// $Id: ms_latch_h.v,v 1.1 2002/05/21 23:55:43 berndt Exp $

module ms_latch_h (e, d, q);

// synopsys template
parameter size = 8;

input e;
input [size-1:0] d;
output [size-1:0] q;

reg [size-1:0] q;

always @(e or d)
   if (e)
      q = d;

endmodule
