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

// $Id: div_add15.v,v 1.1 2002/05/21 23:55:45 berndt Exp $

////////////////////////////////////////////////////////////////////////
//
// Project Reality
//
// module:	div_add15
// description:	Carry-propagating adder for divide rom replacement.
//		Conditional sum adder.
//
// designer:	Phil Gossett
// date:	4/13/95
//
////////////////////////////////////////////////////////////////////////

module div_add15 (a, b, s);

input [14:0] a;
input [14:0] b;

output [14:0] s;

wire [14:0] s0b;
wire [14:0] s1b;
wire [13:0] c0b;
wire [13:0] c1b;

// conditional cells:
xo02d2 s00  (.a1(a[0]), .a2(b[0]),  .z(s[0]));		// output
assign s0b[0] = s[0];	// just to avoid warning (net not driven)
assign s1b[0] = s[0];	// just to avoid warning (net not driven)
an02d2 c00  (.a1(a[0]), .a2(b[0]),  .z(c0b[0]));
assign c1b[0] = c0b[0];	// just to avoid warning (net not driven)

xo02d2 s01  (.a1(a[1]), .a2(b[1]),  .z(s0b[1]));
xn02d2 s11  (.a1(a[1]), .a2(b[1]), .zn(s1b[1]));
an02d2 c01  (.a1(a[1]), .a2(b[1]),  .z(c0b[1]));
or02d2 c11  (.a1(a[1]), .a2(b[1]),  .z(c1b[1]));

xo02d2 s02  (.a1(a[2]), .a2(b[2]),  .z(s0b[2]));
xn02d2 s12  (.a1(a[2]), .a2(b[2]), .zn(s1b[2]));
an02d2 c02  (.a1(a[2]), .a2(b[2]),  .z(c0b[2]));
or02d2 c12  (.a1(a[2]), .a2(b[2]),  .z(c1b[2]));

xo02d2 s03  (.a1(a[3]), .a2(b[3]),  .z(s0b[3]));
xn02d2 s13  (.a1(a[3]), .a2(b[3]), .zn(s1b[3]));
an02d2 c03  (.a1(a[3]), .a2(b[3]),  .z(c0b[3]));
or02d2 c13  (.a1(a[3]), .a2(b[3]),  .z(c1b[3]));

xo02d2 s04  (.a1(a[4]), .a2(b[4]),  .z(s0b[4]));
xn02d2 s14  (.a1(a[4]), .a2(b[4]), .zn(s1b[4]));
an02d2 c04  (.a1(a[4]), .a2(b[4]),  .z(c0b[4]));
or02d2 c14  (.a1(a[4]), .a2(b[4]),  .z(c1b[4]));

xo02d2 s05  (.a1(a[5]), .a2(b[5]),  .z(s0b[5]));
xn02d2 s15  (.a1(a[5]), .a2(b[5]), .zn(s1b[5]));
an02d2 c05  (.a1(a[5]), .a2(b[5]),  .z(c0b[5]));
or02d2 c15  (.a1(a[5]), .a2(b[5]),  .z(c1b[5]));

xo02d2 s06  (.a1(a[6]), .a2(b[6]),  .z(s0b[6]));
xn02d2 s16  (.a1(a[6]), .a2(b[6]), .zn(s1b[6]));
an02d2 c06  (.a1(a[6]), .a2(b[6]),  .z(c0b[6]));
or02d2 c16  (.a1(a[6]), .a2(b[6]),  .z(c1b[6]));

xo02d2 s07  (.a1(a[7]), .a2(b[7]),  .z(s0b[7]));
xn02d2 s17  (.a1(a[7]), .a2(b[7]), .zn(s1b[7]));
an02d2 c07  (.a1(a[7]), .a2(b[7]),  .z(c0b[7]));
or02d2 c17  (.a1(a[7]), .a2(b[7]),  .z(c1b[7]));

xo02d2 s08  (.a1(a[8]), .a2(b[8]),  .z(s0b[8]));
xn02d2 s18  (.a1(a[8]), .a2(b[8]), .zn(s1b[8]));
an02d2 c08  (.a1(a[8]), .a2(b[8]),  .z(c0b[8]));
or02d2 c18  (.a1(a[8]), .a2(b[8]),  .z(c1b[8]));

xo02d2 s09  (.a1(a[9]), .a2(b[9]),  .z(s0b[9]));
xn02d2 s19  (.a1(a[9]), .a2(b[9]), .zn(s1b[9]));
an02d2 c09  (.a1(a[9]), .a2(b[9]),  .z(c0b[9]));
or02d2 c19  (.a1(a[9]), .a2(b[9]),  .z(c1b[9]));

xo02d2 s010 (.a1(a[10]),.a2(b[10]), .z(s0b[10]));
xn02d2 s110 (.a1(a[10]),.a2(b[10]),.zn(s1b[10]));
an02d2 c010 (.a1(a[10]),.a2(b[10]), .z(c0b[10]));
or02d2 c110 (.a1(a[10]),.a2(b[10]), .z(c1b[10]));

xo02d2 s011 (.a1(a[11]),.a2(b[11]), .z(s0b[11]));
xn02d2 s111 (.a1(a[11]),.a2(b[11]),.zn(s1b[11]));
an02d2 c011 (.a1(a[11]),.a2(b[11]), .z(c0b[11]));
or02d2 c111 (.a1(a[11]),.a2(b[11]), .z(c1b[11]));

xo02d2 s012 (.a1(a[12]),.a2(b[12]), .z(s0b[12]));
xn02d2 s112 (.a1(a[12]),.a2(b[12]),.zn(s1b[12]));
an02d2 c012 (.a1(a[12]),.a2(b[12]), .z(c0b[12]));
or02d2 c112 (.a1(a[12]),.a2(b[12]), .z(c1b[12]));

xo02d2 s013 (.a1(a[13]),.a2(b[13]), .z(s0b[13]));
xn02d2 s113 (.a1(a[13]),.a2(b[13]),.zn(s1b[13]));
an02d2 c013 (.a1(a[13]),.a2(b[13]), .z(c0b[13]));
or02d2 c113 (.a1(a[13]),.a2(b[13]), .z(c1b[13]));

xo02d2 s014 (.a1(a[14]),.a2(b[14]), .z(s0b[14]));
xn02d2 s114 (.a1(a[14]),.a2(b[14]),.zn(s1b[14]));

// first rank of muxes (all muxes should be high performance):
mx21d1h mas02  (.s(c0b[1]), .i0(s0b[2]), .i1(s1b[2]), .z(mas0b2));
mx21d1h mas12  (.s(c1b[1]), .i0(s0b[2]), .i1(s1b[2]), .z(mas1b2));
mx21d1h mac02  (.s(c0b[1]), .i0(c0b[2]), .i1(c1b[2]), .z(mac0b2));
mx21d1h mac12  (.s(c1b[1]), .i0(c0b[2]), .i1(c1b[2]), .z(mac1b2));

mx21d1h mas04  (.s(c0b[3]), .i0(s0b[4]), .i1(s1b[4]), .z(mas0b4));
mx21d1h mas14  (.s(c1b[3]), .i0(s0b[4]), .i1(s1b[4]), .z(mas1b4));
mx21d1h mac04  (.s(c0b[3]), .i0(c0b[4]), .i1(c1b[4]), .z(mac0b4));
mx21d1h mac14  (.s(c1b[3]), .i0(c0b[4]), .i1(c1b[4]), .z(mac1b4));

mx21d1h mas06  (.s(c0b[5]), .i0(s0b[6]), .i1(s1b[6]), .z(mas0b6));
mx21d1h mas16  (.s(c1b[5]), .i0(s0b[6]), .i1(s1b[6]), .z(mas1b6));
mx21d1h mac06  (.s(c0b[5]), .i0(c0b[6]), .i1(c1b[6]), .z(mac0b6));
mx21d1h mac16  (.s(c1b[5]), .i0(c0b[6]), .i1(c1b[6]), .z(mac1b6));

mx21d1h mas08  (.s(c0b[7]), .i0(s0b[8]), .i1(s1b[8]), .z(mas0b8));
mx21d1h mas18  (.s(c1b[7]), .i0(s0b[8]), .i1(s1b[8]), .z(mas1b8));
mx21d1h mac08  (.s(c0b[7]), .i0(c0b[8]), .i1(c1b[8]), .z(mac0b8));
mx21d1h mac18  (.s(c1b[7]), .i0(c0b[8]), .i1(c1b[8]), .z(mac1b8));

mx21d1h mas010 (.s(c0b[9]), .i0(s0b[10]),.i1(s1b[10]),.z(mas0b10));
mx21d1h mas110 (.s(c1b[9]), .i0(s0b[10]),.i1(s1b[10]),.z(mas1b10));
mx21d1h mac010 (.s(c0b[9]), .i0(c0b[10]),.i1(c1b[10]),.z(mac0b10));
mx21d1h mac110 (.s(c1b[9]), .i0(c0b[10]),.i1(c1b[10]),.z(mac1b10));

mx21d1h mas012 (.s(c0b[11]),.i0(s0b[12]),.i1(s1b[12]),.z(mas0b12));
mx21d1h mas112 (.s(c1b[11]),.i0(s0b[12]),.i1(s1b[12]),.z(mas1b12));
mx21d1h mac012 (.s(c0b[11]),.i0(c0b[12]),.i1(c1b[12]),.z(mac0b12));
mx21d1h mac112 (.s(c1b[11]),.i0(c0b[12]),.i1(c1b[12]),.z(mac1b12));

mx21d1h mas014 (.s(c0b[13]),.i0(s0b[14]),.i1(s1b[14]),.z(mas0b14));
mx21d1h mas114 (.s(c1b[13]),.i0(s0b[14]),.i1(s1b[14]),.z(mas1b14));

// second rank of muxes:
mx21d1h mbs01  (.s(c0b[0]), .i0(s0b[1]), .i1(s1b[1]), .z(s[1]));
mx21d1h mbs02  (.s(c0b[0]), .i0(mas0b2), .i1(mas1b2), .z(s[2]));
mx21d1h mbc02  (.s(c0b[0]), .i0(mac0b2), .i1(mac1b2), .z(mbc0b2));

mx21d1h mbs05  (.s(mac0b4), .i0(s0b[5]), .i1(s1b[5]), .z(mbs0b5));
mx21d1h mbs15  (.s(mac1b4), .i0(s0b[5]), .i1(s1b[5]), .z(mbs1b5));
mx21d1h mbs06  (.s(mac0b4), .i0(mas0b6), .i1(mas1b6), .z(mbs0b6));
mx21d1h mbs16  (.s(mac1b4), .i0(mas0b6), .i1(mas1b6), .z(mbs1b6));
mx21d1h mbc06  (.s(mac0b4), .i0(mac0b6), .i1(mac1b6), .z(mbc0b6));
mx21d1h mbc16  (.s(mac1b4), .i0(mac0b6), .i1(mac1b6), .z(mbc1b6));

mx21d1h mbs09  (.s(mac0b8), .i0(s0b[9]), .i1(s1b[9]), .z(mbs0b9));
mx21d1h mbs19  (.s(mac1b8), .i0(s0b[9]), .i1(s1b[9]), .z(mbs1b9));
mx21d1h mbs010 (.s(mac0b8), .i0(mas0b10),.i1(mas1b10),.z(mbs0b10));
mx21d1h mbs110 (.s(mac1b8), .i0(mas0b10),.i1(mas1b10),.z(mbs1b10));
mx21d1h mbc010 (.s(mac0b8), .i0(mac0b10),.i1(mac1b10),.z(mbc0b10));
mx21d1h mbc110 (.s(mac1b8), .i0(mac0b10),.i1(mac1b10),.z(mbc1b10));

mx21d1h mbs013 (.s(mac0b12),.i0(s0b[13]),.i1(s1b[13]),.z(mbs0b13));
mx21d1h mbs113 (.s(mac1b12),.i0(s0b[13]),.i1(s1b[13]),.z(mbs1b13));
mx21d1h mbs014 (.s(mac0b12),.i0(mas0b14),.i1(mas1b14),.z(mbs0b14));
mx21d1h mbs114 (.s(mac1b12),.i0(mas0b14),.i1(mas1b14),.z(mbs1b14));

// third rank of muxes:
mx21d1h mcs03  (.s(mbc0b2), .i0(s0b[3]), .i1(s1b[3]), .z(s[3]));
mx21d1h mcs04  (.s(mbc0b2), .i0(mas0b4), .i1(mas1b4), .z(s[4]));
mx21d1h mcs05  (.s(mbc0b2), .i0(mbs0b5), .i1(mbs1b5), .z(s[5]));
mx21d1h mcs06  (.s(mbc0b2), .i0(mbs0b6), .i1(mbs1b6), .z(s[6]));
mx21d1h mcc06  (.s(mbc0b2), .i0(mbc0b6), .i1(mbc1b6), .z(mcc0b6));

mx21d1h mcs011 (.s(mbc0b10),.i0(s0b[11]),.i1(s1b[11]),.z(mcs0b11));
mx21d1h mcs111 (.s(mbc1b10),.i0(s0b[11]),.i1(s1b[11]),.z(mcs1b11));
mx21d1h mcs012 (.s(mbc0b10),.i0(mas0b12),.i1(mas1b12),.z(mcs0b12));
mx21d1h mcs112 (.s(mbc1b10),.i0(mas0b12),.i1(mas1b12),.z(mcs1b12));
mx21d1h mcs013 (.s(mbc0b10),.i0(mbs0b13),.i1(mbs1b13),.z(mcs0b13));
mx21d1h mcs113 (.s(mbc1b10),.i0(mbs0b13),.i1(mbs1b13),.z(mcs1b13));
mx21d1h mcs014 (.s(mbc0b10),.i0(mbs0b14),.i1(mbs1b14),.z(mcs0b14));
mx21d1h mcs114 (.s(mbc1b10),.i0(mbs0b14),.i1(mbs1b14),.z(mcs1b14));

// fourth rank of muxes:
mx21d1h mds07  (.s(mcc0b6), .i0(s0b[7]), .i1(s1b[7]), .z(s[7]));
mx21d1h mds08  (.s(mcc0b6), .i0(mas0b8), .i1(mas1b8), .z(s[8]));
mx21d1h mds09  (.s(mcc0b6), .i0(mbs0b9), .i1(mbs1b9), .z(s[9]));
mx21d1h mds010 (.s(mcc0b6), .i0(mbs0b10),.i1(mbs1b10),.z(s[10]));
mx21d1h mds011 (.s(mcc0b6), .i0(mcs0b11),.i1(mcs1b11),.z(s[11]));
mx21d1h mds012 (.s(mcc0b6), .i0(mcs0b12),.i1(mcs1b12),.z(s[12]));
mx21d1h mds013 (.s(mcc0b6), .i0(mcs0b13),.i1(mcs1b13),.z(s[13]));
mx21d1h mds014 (.s(mcc0b6), .i0(mcs0b14),.i1(mcs1b14),.z(s[14]));

endmodule // div_add15
