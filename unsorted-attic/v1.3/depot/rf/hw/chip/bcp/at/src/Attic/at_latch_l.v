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

// $Id: at_latch_l.v,v 1.2 2002/11/07 02:18:10 rws Exp $

module at_latch_l(en, d, q);

// synopsys template
parameter size = 8;

input en;
input [size-1:0] d;
output [size-1:0] q;

wire [size-1:0] q = d;

endmodule
