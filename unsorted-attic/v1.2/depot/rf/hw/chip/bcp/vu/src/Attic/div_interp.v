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

// $Id: div_interp.v,v 1.1 2002/05/21 23:55:45 berndt Exp $

////////////////////////////////////////////////////////////////////////
//
// Project Reality
//
// module:	div_interp
// description:	Carry-save adder tree for divide rom replacement.
//
// designer:	Phil Gossett
// date:	4/13/95
//
////////////////////////////////////////////////////////////////////////

module div_interp (pnt, slp, frac, sum);

input [15:0] pnt;
input [7:0] slp;
input [3:0] frac;

output [15:0] sum;

wire [7:0] p0p;
wire [7:0] p1p;
wire [7:0] p2p;
wire [7:0] p3p;

wire [9:0] sa;
wire [9:0] ca;
wire [11:0] sb;
wire [11:0] cb;
wire [15:0] sc;
wire [14:0] cc;

an02d1h p0p0 (.a1(slp[0]), .a2(frac[0]), .z(p0p[0]));
an02d1h p0p1 (.a1(slp[1]), .a2(frac[0]), .z(p0p[1]));
an02d1h p0p2 (.a1(slp[2]), .a2(frac[0]), .z(p0p[2]));
an02d1h p0p3 (.a1(slp[3]), .a2(frac[0]), .z(p0p[3]));
an02d1h p0p4 (.a1(slp[4]), .a2(frac[0]), .z(p0p[4]));
an02d1h p0p5 (.a1(slp[5]), .a2(frac[0]), .z(p0p[5]));
an02d1h p0p6 (.a1(slp[6]), .a2(frac[0]), .z(p0p[6]));
an02d1h p0p7 (.a1(slp[7]), .a2(frac[0]), .z(p0p[7]));

an02d1h p1p0 (.a1(slp[0]), .a2(frac[1]), .z(p1p[0]));
an02d1h p1p1 (.a1(slp[1]), .a2(frac[1]), .z(p1p[1]));
an02d1h p1p2 (.a1(slp[2]), .a2(frac[1]), .z(p1p[2]));
an02d1h p1p3 (.a1(slp[3]), .a2(frac[1]), .z(p1p[3]));
an02d1h p1p4 (.a1(slp[4]), .a2(frac[1]), .z(p1p[4]));
an02d1h p1p5 (.a1(slp[5]), .a2(frac[1]), .z(p1p[5]));
an02d1h p1p6 (.a1(slp[6]), .a2(frac[1]), .z(p1p[6]));
an02d1h p1p7 (.a1(slp[7]), .a2(frac[1]), .z(p1p[7]));

an02d1h p2p0 (.a1(slp[0]), .a2(frac[2]), .z(p2p[0]));
an02d1h p2p1 (.a1(slp[1]), .a2(frac[2]), .z(p2p[1]));
an02d1h p2p2 (.a1(slp[2]), .a2(frac[2]), .z(p2p[2]));
an02d1h p2p3 (.a1(slp[3]), .a2(frac[2]), .z(p2p[3]));
an02d1h p2p4 (.a1(slp[4]), .a2(frac[2]), .z(p2p[4]));
an02d1h p2p5 (.a1(slp[5]), .a2(frac[2]), .z(p2p[5]));
an02d1h p2p6 (.a1(slp[6]), .a2(frac[2]), .z(p2p[6]));
an02d1h p2p7 (.a1(slp[7]), .a2(frac[2]), .z(p2p[7]));

an02d1h p3p0 (.a1(slp[0]), .a2(frac[3]), .z(p3p[0]));
an02d1h p3p1 (.a1(slp[1]), .a2(frac[3]), .z(p3p[1]));
an02d1h p3p2 (.a1(slp[2]), .a2(frac[3]), .z(p3p[2]));
an02d1h p3p3 (.a1(slp[3]), .a2(frac[3]), .z(p3p[3]));
an02d1h p3p4 (.a1(slp[4]), .a2(frac[3]), .z(p3p[4]));
an02d1h p3p5 (.a1(slp[5]), .a2(frac[3]), .z(p3p[5]));
an02d1h p3p6 (.a1(slp[6]), .a2(frac[3]), .z(p3p[6]));
an02d1h p3p7 (.a1(slp[7]), .a2(frac[3]), .z(p3p[7]));

xo02d1h sa0  (.a1(p1p[1]), .a2(p2p[0]),               .z(sa[0]));
an02d1h ca0  (.a1(p1p[1]), .a2(p2p[0]),                           .z(ca[0]));
ad01d1h sa1  (.ci(p1p[2]),  .a(p2p[1]),  .b(p3p[0]),  .s(sa[1]), .co(ca[1]));
ad01d1h sa2  (.ci(p1p[3]),  .a(p2p[2]),  .b(p3p[1]),  .s(sa[2]), .co(ca[2]));
ad01d1h sa3  (.ci(p1p[4]),  .a(p2p[3]),  .b(p3p[2]),  .s(sa[3]), .co(ca[3]));
ad01d1h sa4  (.ci(p1p[5]),  .a(p2p[4]),  .b(p3p[3]),  .s(sa[4]), .co(ca[4]));
ad01d1h sa5  (.ci(p1p[6]),  .a(p2p[5]),  .b(p3p[4]),  .s(sa[5]), .co(ca[5]));
ad01d1h sa6  (.ci(p1p[7]),  .a(p2p[6]),  .b(p3p[5]),  .s(sa[6]), .co(ca[6]));
ad01d1h sa7  (.ci(frac[1]), .a(p2p[7]),  .b(p3p[6]),  .s(sa[7]), .co(ca[7]));
ad01d1h sa8  (.ci(frac[1]), .a(frac[2]), .b(p3p[7]),  .s(sa[8]), .co(ca[8]));
ad01d1h sa9  (.ci(frac[1]), .a(frac[2]), .b(frac[3]), .s(sa[9]), .co(ca[9]));

xo02d1h sb0  (.a1(p1p[0]),            .a2(p0p[1]), .z(sb[0]));
an02d1h cb0  (.a1(p1p[0]),            .a2(p0p[1]),              .z(cb[0]));
xo02d1h sb1  ( .a1(sa[0]),            .a2(p0p[2]), .z(sb[1]));
an02d1h cb1  ( .a1(sa[0]),            .a2(p0p[2]),              .z(cb[1]));
ad01d1h sb2  ( .ci(sa[1]), .a(ca[0]),  .b(p0p[3]), .s(sb[2]),  .co(cb[2]));
ad01d1h sb3  ( .ci(sa[2]), .a(ca[1]),  .b(p0p[4]), .s(sb[3]),  .co(cb[3]));
ad01d1h sb4  ( .ci(sa[3]), .a(ca[2]),  .b(p0p[5]), .s(sb[4]),  .co(cb[4]));
ad01d1h sb5  ( .ci(sa[4]), .a(ca[3]),  .b(p0p[6]), .s(sb[5]),  .co(cb[5]));
ad01d1h sb6  ( .ci(sa[5]), .a(ca[4]),  .b(p0p[7]), .s(sb[6]),  .co(cb[6]));
ad01d1h sb7  ( .ci(sa[6]), .a(ca[5]), .b(frac[0]), .s(sb[7]),  .co(cb[7]));
ad01d1h sb8  ( .ci(sa[7]), .a(ca[6]), .b(frac[0]), .s(sb[8]),  .co(cb[8]));
ad01d1h sb9  ( .ci(sa[8]), .a(ca[7]), .b(frac[0]), .s(sb[9]),  .co(cb[9]));
ad01d1h sb10 ( .ci(sa[9]), .a(ca[8]), .b(frac[0]), .s(sb[10]), .co(cb[10]));
ad01d1h sb11 ( .ci(sa[9]), .a(ca[9]), .b(frac[0]), .s(sb[11]), .co(cb[11]));

xo02d1h sc0  (.a1(p0p[0]),             .a2(pnt[0]),  .z(sc[0]));
an02d1h cc0  (.a1(p0p[0]),             .a2(pnt[0]),               .z(cc[0]));
xo02d1h sc1  ( .a1(sb[0]),             .a2(pnt[1]),  .z(sc[1]));
an02d1h cc1  ( .a1(sb[0]),             .a2(pnt[1]),               .z(cc[1]));
ad01d1h sc2  ( .ci(sb[1]),  .a(cb[0]),  .b(pnt[2]),  .s(sc[2]),  .co(cc[2]));
ad01d1h sc3  ( .ci(sb[2]),  .a(cb[1]),  .b(pnt[3]),  .s(sc[3]),  .co(cc[3]));
ad01d1h sc4  ( .ci(sb[3]),  .a(cb[2]),  .b(pnt[4]),  .s(sc[4]),  .co(cc[4]));
ad01d1h sc5  ( .ci(sb[4]),  .a(cb[3]),  .b(pnt[5]),  .s(sc[5]),  .co(cc[5]));
ad01d1h sc6  ( .ci(sb[5]),  .a(cb[4]),  .b(pnt[6]),  .s(sc[6]),  .co(cc[6]));
ad01d1h sc7  ( .ci(sb[6]),  .a(cb[5]),  .b(pnt[7]),  .s(sc[7]),  .co(cc[7]));
ad01d1h sc8  ( .ci(sb[7]),  .a(cb[6]),  .b(pnt[8]),  .s(sc[8]),  .co(cc[8]));
ad01d1h sc9  ( .ci(sb[8]),  .a(cb[7]),  .b(pnt[9]),  .s(sc[9]),  .co(cc[9]));
ad01d1h sc10 ( .ci(sb[9]),  .a(cb[8]),  .b(pnt[10]), .s(sc[10]), .co(cc[10]));
ad01d1h sc11 ( .ci(sb[10]), .a(cb[9]),  .b(pnt[11]), .s(sc[11]), .co(cc[11]));
ad01d1h sc12 ( .ci(sb[11]), .a(cb[10]), .b(pnt[12]), .s(sc[12]), .co(cc[12]));
ad01d1h sc13 ( .ci(sb[11]), .a(cb[11]), .b(pnt[13]), .s(sc[13]), .co(cc[13]));
ad01d1h sc14 ( .ci(sb[11]), .a(cb[11]), .b(pnt[14]), .s(sc[14]), .co(cc[14]));
ad01d1h sc15 ( .ci(sb[11]), .a(cb[11]), .b(pnt[15]), .s(sc[15]));

assign sum[0] = sc[0];
div_add15 add15 (.a(sc[15:1]), .b(cc[14:0]), .s(sum[15:1]));

endmodule // div_interp
