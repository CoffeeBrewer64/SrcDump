/*
*************************************************************************
*                                                                       *
*               Copyright (C) 1994, Silicon Graphics, Inc.              *
*                                                                       *
*  These coded instructions, statements, and computer programs  contain *
*  unpublished  proprietary  information of Silicon Graphics, Inc., and *
*  are protected by Federal copyright  law.  They  may not be disclosed *
*  to  third  parties  or copied or duplicated in any form, in whole or *
*  in part, without the prior written consent of Silicon Graphics, Inc. *
*                                                                       *
*************************************************************************
*/

// $Id: div_rom_sc.v,v 1.1 2002/05/21 23:55:45 berndt Exp $

////////////////////////////////////////////////////////////////////////
//
// Project Reality
//
// module:	div_rom_sc
// description:	Standard cell divide rom replacement. No oe.
//
// designer:	Phil Gossett
// date:	4/12/95
//
////////////////////////////////////////////////////////////////////////

module div_rom_sc (clk, a, out);

input clk;
input [9:0] a;

output [15:0] out;

wire [9:0] areg;
wire [5:0] index;
wire [23:0] slope_incpt;
wire [3:0] frac;

dfntnq2 reg0  (.cp(clk), .d(a[0]),  .q(areg[0]));
dfntnq2 reg1  (.cp(clk), .d(a[1]),  .q(areg[1]));
dfntnq2 reg2  (.cp(clk), .d(a[2]),  .q(areg[2]));
dfntnq2 reg3  (.cp(clk), .d(a[3]),  .q(areg[3]));
dfntnq2 reg4  (.cp(clk), .d(a[4]),  .q(areg[4]));
dfntnq2 reg5  (.cp(clk), .d(a[5]),  .q(areg[5]));
dfntnq2 reg6  (.cp(clk), .d(a[6]),  .q(areg[6]));
dfntnq2 reg7  (.cp(clk), .d(a[7]),  .q(areg[7]));
dfntnq2 reg8  (.cp(clk), .d(a[8]),  .q(areg[8]));
dfntnq2 reg9  (.cp(clk), .d(a[9]),  .q(areg[9]));
mx21d1h mx0 (.s(index[5]), .i0(areg[0]), .i1(areg[1]), .z(frac[0]));
mx21d1h mx1 (.s(index[5]), .i0(areg[1]), .i1(areg[2]), .z(frac[1]));
mx21d1h mx2 (.s(index[5]), .i0(areg[2]), .i1(areg[3]), .z(frac[2]));
mx21d1h mx3 (.s(index[5]), .i0(areg[3]), .i1(areg[4]), .z(frac[3]));
mx21d1h mx4 (.s(index[5]), .i0(areg[4]), .i1(areg[5]), .z(index[0]));
mx21d1h mx5 (.s(index[5]), .i0(areg[5]), .i1(areg[6]), .z(index[1]));
mx21d1h mx6 (.s(index[5]), .i0(areg[6]), .i1(areg[7]), .z(index[2]));
mx21d1h mx7 (.s(index[5]), .i0(areg[7]), .i1(areg[8]), .z(index[3]));
mx21d1h mx8 (.s(index[5]), .i0(areg[8]), .i1(areg[0]), .z(index[4]));
ni01d5  ni9 (               .i(areg[9]),               .z(index[5]));
div_pnt_slp pntslp (.index(index), .slope_incpt(slope_incpt));
div_interp  interp (.pnt(slope_incpt[15:0]), .slp(slope_incpt[23:16]),
		    .frac(frac), .sum(out));

endmodule // div_rom_sc
