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

// $Id: ms_latch8.v,v 1.1 2002/05/21 23:55:43 berndt Exp $

////////////////////////////////////////////////////////////////////////
//
// Project Reality
//
// module:      ms_latch8
// description: Transparent latches
//
// designer:    Mike M. Cai / Robert W. Sherburne
// date:        12/16/94
//
////////////////////////////////////////////////////////////////////////

module ms_latch8 (d_out, clk, g, d_in);
output [7:0] 	  d_out;
input [7:0]  	  d_in;
input 	       	  clk, g;

wire  	       	  l_en_m, l_en0, l_en1;

nd02d2 lenm(.zn(l_en_m), .a1(g), .a2(clk));
in01d3 len1(.zn(l_en), .i(l_en_m));

lantnq
lat0(.e(l_en), .d(d_in[0]), .q(d_out[0])),
lat1(.e(l_en), .d(d_in[1]), .q(d_out[1])),
lat2(.e(l_en), .d(d_in[2]), .q(d_out[2])),
lat3(.e(l_en), .d(d_in[3]), .q(d_out[3])),
lat4(.e(l_en), .d(d_in[4]), .q(d_out[4])),
lat5(.e(l_en), .d(d_in[5]), .q(d_out[5])),
lat6(.e(l_en), .d(d_in[6]), .q(d_out[6])),
lat7(.e(l_en), .d(d_in[7]), .q(d_out[7]));

endmodule  //  ms_latch8
