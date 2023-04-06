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

/*      Project Reality
        MDP
        Created by Mike M. Cai  5/28/94
*/

`timescale 100 ps / 100 ps

module sttoptest;
wire [7:0]   st_cc_r, st_cc_g, st_cc_b, st_cc_a;
wire [17:0]  st_bl_z;
wire [15:0]  st_tc_s, st_tc_t, st_tc_w, st_tc_l;
reg 	       load_r, load_g, load_b, load_a, load_z, 
      	       load_s, load_t, load_w, load_l;
reg [20:0]   ep_st_r, ep_st_g, ep_st_b, ep_st_a;
reg [31:0]   ep_st_z;
reg [31:0]   ep_st_s, ep_st_t, ep_st_w, ep_st_l;
reg [21:0]   at_st_dxr, at_st_dxg, at_st_dxb, at_st_dxa;
reg [31:0]   at_st_dxz, at_st_dxs, at_st_dxt, at_st_dxw, at_st_dxl;
reg [12:0]   at_st_dyr, at_st_dyg, at_st_dyb, at_st_dya;
reg [21:0]   at_st_dyz;
reg [1:0]    x_offsetr, x_offsetg, x_offsetb, x_offseta, x_offsetz,
      	     y_offsetr, y_offsetg, y_offsetb, y_offseta, y_offsetz;
reg 	     st_stall, left_major, clk;

parameter    cycle = 160;  

sttop sttopins ( st_cc_r, st_cc_g, st_cc_b, st_cc_a,
      	       st_bl_z,
	       st_tc_s, st_tc_t, st_tc_w, st_tc_l,
	       ep_st_r, load_r, at_st_dxr, at_st_dyr, x_offsetr, y_offsetr,
	       ep_st_g, load_g, at_st_dxg, at_st_dyg, x_offsetg, y_offsetg,
	       ep_st_b, load_b, at_st_dxb, at_st_dyb, x_offsetb, y_offsetb,
	       ep_st_a, load_a, at_st_dxa, at_st_dya, x_offseta, y_offseta,
	       ep_st_z, load_z, at_st_dxz, at_st_dyz, x_offsetz, y_offsetz,
	       ep_st_s, load_s, at_st_dxs,
	       ep_st_t, load_t, at_st_dxt,
	       ep_st_w, load_w, at_st_dxw,
	       ep_st_l, load_l, at_st_dxl,
	       st_stall, left_major, clk);

initial 
   begin
      clk = 0;
      st_stall = 0;
      at_st_dyr=21'h0;
      at_st_dyg=21'h0;
      at_st_dyb=21'h0;
      at_st_dya=21'h0;
      at_st_dyz=31'h0;
      x_offsetr=2'h0; y_offsetr=2'h0;
      x_offsetg=2'h0; y_offsetg=2'h0;
      x_offsetb=2'h0; y_offsetb=2'h0;
      x_offseta=2'h0; y_offseta=2'h0;
      x_offsetz=2'h0; y_offsetz=2'h0;
      left_major = 1;
   end
   
always
   begin
      #(cycle/2) clk = ~clk;
   end
   
initial
   begin
      #(cycle/8)     	// 1
      load_r=1; load_g=1; load_b=1; load_a=1; load_z=1;
      load_s=1; load_t=1; load_w=1; load_l=1;
      ep_st_r=21'h0fa00; at_st_dxr=21'h0fff; 
      ep_st_g=21'h0fa00; at_st_dxg=21'h17ff; 
      ep_st_b=21'h0fa00; at_st_dxb=21'h1fff; 
      ep_st_a=21'h0fa00; at_st_dxa=21'h27ff; 
      ep_st_z=32'h1f4000; at_st_dxz=32'h05ffff; 
      ep_st_s=32'h1f4000; at_st_dxs=32'h06ffff; 
      ep_st_t=32'h1f4000; at_st_dxt=32'h07ffff; 
      ep_st_w=32'h1f4000; at_st_dxw=32'h08ffff; 
      ep_st_l=32'h1f4000; at_st_dxl=32'h09ffff; 
      #cycle   	     // 2
      load_r=0; load_g=0; load_b=0; load_a=0; load_z=0;
      load_s=0; load_t=0; load_w=0; load_l=0;
      #cycle;  	     // 3
      #cycle;  	     // 4
      #cycle;  	     // 5
      #cycle;  	     // 6
      #cycle;  	     // 7
      #cycle;  	     // 8
      #cycle;  	     // 9
      #cycle;  	     // 10
      #cycle   	     // 11
      load_r=1; load_g=1; load_b=1; load_a=1; load_z=1;
      load_s=1; load_t=1; load_w=1; load_l=1;
      ep_st_r=21'h0fa00; at_st_dxr=21'h0fff; 
      at_st_dyr=12'h008; x_offsetr=2'b01; y_offsetr=2'b01;
      ep_st_g=21'h0fa00; at_st_dxg=21'h17ff; 
      at_st_dyg=12'h008; x_offsetg=2'b10; y_offsetg=2'b10;
      ep_st_b=21'h0fa00; at_st_dxb=21'h1fff; 
      at_st_dyb=12'h008; x_offsetb=2'b11; y_offsetb=2'b11;
      ep_st_a=21'h0fa00; at_st_dxa=21'h27ff; 
      at_st_dya=12'h008; x_offseta=2'b11; y_offseta=2'b11;
      ep_st_z=32'h1f4000; at_st_dxz=32'h05ffff; 
      at_st_dyz=22'h0080; x_offsetz=2'b10; y_offsetz=2'b10;
      ep_st_s=32'h1f4000; at_st_dxs=32'h06ffff; 
      ep_st_t=32'h1f4000; at_st_dxt=32'h07ffff; 
      ep_st_w=32'h1f4000; at_st_dxw=32'h08ffff; 
      ep_st_l=32'h1f4000; at_st_dxl=32'h09ffff; 
      #cycle  	     // 12
      load_r=0; load_g=0; load_b=0; load_a=0; load_z=0;
      load_s=0; load_t=0; load_w=0; load_l=0;      
      #cycle;  	     // 13
      #cycle;  	     // 14
      #cycle;  	     // 15
      #cycle;  	     // 16
      #cycle;  	     // 17
      #cycle;  	     // 18
      #cycle;  	     // 19
      #cycle;  	     // 20
      $stop;
   end
      
always @(negedge clk)
   begin
      $display("%0d ", $time, "ouputs: ",
      	 "st_cc_r,g,b,a %h %h %h %h ", st_cc_r, st_cc_g, st_cc_b, st_cc_a,
	 "st_bl_z %h ", st_bl_z,
	 "st_tc_s,t,w,l %h %h %h %h ", st_tc_s, st_tc_t, st_tc_w, st_tc_l
	 );
/*      $display("inputs: ",
      	 "ep_st_r %h ", ep_st_r,
	 "load_r %b ", load_r,
	 "at_st_dxr %h ", at_st_dxr,
	 "at_st_dyr %h ", at_st_dyr,
	 "x,y_offset %b %b \n", x_offsetr, y_offsetr,
	 "att_cur_m %h ", sttopins.redstepper.att_cur_m,
      	 "att_cur_s %h ", sttopins.redstepper.att_cur_s,
      	 "att_accum %h ", sttopins.redstepper.att_accum,
      	 "att_offset %h ", sttopins.redstepper.att_offset,
      	 "att_clamp_value %h ", sttopins.redstepper.att_clamp_value,
      	 "att_clamped %h ", sttopins.redstepper.att_clamped,
      	 "att_data_out %h ", sttopins.redstepper.att_data_out
	 );
*/
      $display(" ");
   end


endmodule  //  sttoptest
