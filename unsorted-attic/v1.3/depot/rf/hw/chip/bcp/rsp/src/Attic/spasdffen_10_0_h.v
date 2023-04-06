// Module instances modified by /home/rws/workarea/rf/sw/bbplayer/tools/necprimfix 
//
//    10 instances of mfctnh changed to j_mfctnh.
//

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
// $Id: spasdffen_10_0_h.v,v 1.2 2002/11/13 02:11:41 rws Exp $

// spasdffen_10_0_h.v: high-performance 10-bit dff w/ reset and enable

`timescale 1ns / 10ps

module spasdffen_10_0_h (out, outn, in, en, clk, reset_l);

  inout [9:0] out; output [9:0] outn; input [9:0] in; input en; input clk; input reset_l;
  wire enb;

  j_mfctnh mfctnh_10_0_0 (.q(out[0]), .qn(outn[0]), .da(in[0]), .db(out[0]), .sa(en), .cp(clk), .cdn(reset_l)); 
  j_mfctnh mfctnh_10_0_1 (.q(out[1]), .qn(outn[1]), .da(in[1]), .db(out[1]), .sa(en), .cp(clk), .cdn(reset_l)); 
  j_mfctnh mfctnh_10_0_2 (.q(out[2]), .qn(outn[2]), .da(in[2]), .db(out[2]), .sa(en), .cp(clk), .cdn(reset_l)); 
  j_mfctnh mfctnh_10_0_3 (.q(out[3]), .qn(outn[3]), .da(in[3]), .db(out[3]), .sa(en), .cp(clk), .cdn(reset_l)); 
  j_mfctnh mfctnh_10_0_4 (.q(out[4]), .qn(outn[4]), .da(in[4]), .db(out[4]), .sa(en), .cp(clk), .cdn(reset_l)); 
  j_mfctnh mfctnh_10_0_5 (.q(out[5]), .qn(outn[5]), .da(in[5]), .db(out[5]), .sa(en), .cp(clk), .cdn(reset_l)); 
  j_mfctnh mfctnh_10_0_6 (.q(out[6]), .qn(outn[6]), .da(in[6]), .db(out[6]), .sa(en), .cp(clk), .cdn(reset_l)); 
  j_mfctnh mfctnh_10_0_7 (.q(out[7]), .qn(outn[7]), .da(in[7]), .db(out[7]), .sa(en), .cp(clk), .cdn(reset_l)); 
  j_mfctnh mfctnh_10_0_8 (.q(out[8]), .qn(outn[8]), .da(in[8]), .db(out[8]), .sa(en), .cp(clk), .cdn(reset_l)); 
  j_mfctnh mfctnh_10_0_9 (.q(out[9]), .qn(outn[9]), .da(in[9]), .db(out[9]), .sa(en), .cp(clk), .cdn(reset_l)); 

endmodule
