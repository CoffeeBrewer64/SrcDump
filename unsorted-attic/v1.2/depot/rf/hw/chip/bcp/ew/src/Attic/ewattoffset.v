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
// $Id: ewattoffset.v,v 1.1 2002/05/21 23:55:43 berndt Exp $
   /////////////////////////////////////////////////////////////////////////
   //
   // Project Reality
   //
   // module:      ewattoffset
   // description: computes A = A + 3/4(da/de - da/dy) - dx * xfrac
   //   
   //
   // designer:    Mike M. Cai   5/16/94
   //
   /////////////////////////////////////////////////////////////////////////

module ewattoffset(att_d_out, 
      	       	     att_d_in,
      	       	     de, dx, dy, 
		     x_frac, ld_x_frac,
		     sign_dxdy, 
		     left, ew_stall_attr, 
		     cycle_type, load_cmd, 
		     gclk);  
output [31:0]  att_d_out;
input [31:0]   att_d_in, de, dx, dy;
input [7:0]    x_frac;
input 	       ld_x_frac;
input 	       sign_dxdy, left;
input 	       ew_stall_attr;
input [1:0]    cycle_type; 
input 	       load_cmd;
input 	       gclk;

reg [31:0]     att_d_out;
wire  	       do_offset;
wire [31:0]    de_offset, dy_offset;
wire [39:0]    result_mult;
wire [31:0]    result_sum;
wire [31:0]    threequarterde, threequarterdy;
wire [31:0]    att_d_out_m;
reg [31:0]     att_d_out_s;
reg [7:0]      x_frac_s;
wire [7:0]     x_frac_ss;

always @(posedge gclk)
   x_frac_s <= ld_x_frac ? x_frac : x_frac_s;
assign x_frac_ss = x_frac_s & {8{~( (cycle_type[1] & ~cycle_type[0]) | load_cmd)}};
   

assign   do_offset = sign_dxdy ~^ left,
      	 de_offset = de & {32{do_offset}},
      	 dy_offset = dy & {32{do_offset}},
	 threequarterde = ({de_offset[31],de_offset[31:1]}) + 
	       	     	({{2{de_offset[31]}},de_offset[31:2]}),
	 threequarterdy = ({dy_offset[31],dy_offset[31:1]}) +
			({{2{dy_offset[31]}}, dy_offset[31:2]});

assign 	 result_mult = {{8{dx[31]}}, dx} * x_frac_ss,
      	 result_sum  = att_d_in + 
	       	     	threequarterde -
			threequarterdy;

assign att_d_out_m = result_sum - result_mult[39:8];

/*
assign att_d_out_m = att_d_in +
      	       	     	({de_offset[31],de_offset[31:1]}) + 
	       	     	({{2{de_offset[31]}},de_offset[31:2]}) -
			({dy_offset[31],dy_offset[31:1]}) -
			({{2{dy_offset[31]}}, dy_offset[31:2]}) -
			{{8{dx[31]}}, dx[31:8]} * x_frac_ss;
*/			 
always @(posedge gclk)
   begin
      att_d_out_s <= att_d_out_m;
      att_d_out <= att_d_out_s; 
   end

endmodule  //  ewattoffset
