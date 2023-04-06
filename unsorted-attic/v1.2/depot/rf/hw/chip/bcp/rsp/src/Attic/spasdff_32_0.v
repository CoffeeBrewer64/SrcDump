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
// $Id: spasdff_32_0.v,v 1.1 2002/05/21 23:55:44 berndt Exp $

// spasdff_32_0.v: 32-bit dff w/ reset

`timescale 1ns / 10ps

module spasdff_32_0 (out, outn, in, clk, reset_l);

  output [31:0] out; output [31:0] outn; input [31:0] in; input clk; input reset_l;

  dfctnb dfctnb_32_0_0 (.q(out[0]), .qn(outn[0]), .d(in[0]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_1 (.q(out[1]), .qn(outn[1]), .d(in[1]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_2 (.q(out[2]), .qn(outn[2]), .d(in[2]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_3 (.q(out[3]), .qn(outn[3]), .d(in[3]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_4 (.q(out[4]), .qn(outn[4]), .d(in[4]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_5 (.q(out[5]), .qn(outn[5]), .d(in[5]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_6 (.q(out[6]), .qn(outn[6]), .d(in[6]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_7 (.q(out[7]), .qn(outn[7]), .d(in[7]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_8 (.q(out[8]), .qn(outn[8]), .d(in[8]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_9 (.q(out[9]), .qn(outn[9]), .d(in[9]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_10 (.q(out[10]), .qn(outn[10]), .d(in[10]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_11 (.q(out[11]), .qn(outn[11]), .d(in[11]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_12 (.q(out[12]), .qn(outn[12]), .d(in[12]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_13 (.q(out[13]), .qn(outn[13]), .d(in[13]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_14 (.q(out[14]), .qn(outn[14]), .d(in[14]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_15 (.q(out[15]), .qn(outn[15]), .d(in[15]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_16 (.q(out[16]), .qn(outn[16]), .d(in[16]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_17 (.q(out[17]), .qn(outn[17]), .d(in[17]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_18 (.q(out[18]), .qn(outn[18]), .d(in[18]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_19 (.q(out[19]), .qn(outn[19]), .d(in[19]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_20 (.q(out[20]), .qn(outn[20]), .d(in[20]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_21 (.q(out[21]), .qn(outn[21]), .d(in[21]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_22 (.q(out[22]), .qn(outn[22]), .d(in[22]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_23 (.q(out[23]), .qn(outn[23]), .d(in[23]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_24 (.q(out[24]), .qn(outn[24]), .d(in[24]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_25 (.q(out[25]), .qn(outn[25]), .d(in[25]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_26 (.q(out[26]), .qn(outn[26]), .d(in[26]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_27 (.q(out[27]), .qn(outn[27]), .d(in[27]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_28 (.q(out[28]), .qn(outn[28]), .d(in[28]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_29 (.q(out[29]), .qn(outn[29]), .d(in[29]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_30 (.q(out[30]), .qn(outn[30]), .d(in[30]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_32_0_31 (.q(out[31]), .qn(outn[31]), .d(in[31]), .cp(clk), .cdn(reset_l)); 

endmodule
