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
// $Id: spasdff_9_0.v,v 1.1 2002/05/21 23:55:44 berndt Exp $

// spasdff_9_0.v: 9-bit dff w/ reset

`timescale 1ns / 10ps

module spasdff_9_0 (out, outn, in, clk, reset_l);

  output [8:0] out; output [8:0] outn; input [8:0] in; input clk; input reset_l;

  dfctnb dfctnb_9_0_0 (.q(out[0]), .qn(outn[0]), .d(in[0]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_9_0_1 (.q(out[1]), .qn(outn[1]), .d(in[1]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_9_0_2 (.q(out[2]), .qn(outn[2]), .d(in[2]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_9_0_3 (.q(out[3]), .qn(outn[3]), .d(in[3]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_9_0_4 (.q(out[4]), .qn(outn[4]), .d(in[4]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_9_0_5 (.q(out[5]), .qn(outn[5]), .d(in[5]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_9_0_6 (.q(out[6]), .qn(outn[6]), .d(in[6]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_9_0_7 (.q(out[7]), .qn(outn[7]), .d(in[7]), .cp(clk), .cdn(reset_l)); 
  dfctnb dfctnb_9_0_8 (.q(out[8]), .qn(outn[8]), .d(in[8]), .cp(clk), .cdn(reset_l)); 

endmodule
