// Module instances modified by /home/rws/workarea/rf/sw/bbplayer/tools/necprimfix 
//
//    1 instance of dfctnh changed to j_dfctnh.
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
// $Id: spasdff_1_0_h.v,v 1.2 2002/11/13 02:11:41 rws Exp $

// spasdff_1_0_h.v: 1-bit high-performance dff w/ reset

`timescale 1ns / 10ps

module spasdff_1_0_h(out, outn, in, clk, reset_l);

  output out; output outn; input  in; input clk; input reset_l;
  j_dfctnh dfctnh_1_0_h_0 (.q(out), .qn(outn), .d(in), .cp(clk), .cdn(reset_l)); 

endmodule


