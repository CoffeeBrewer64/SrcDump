/*
*************************************************************************
*									*
*               Copyright (C) 1994, Silicon Graphics, Inc.		*
*									*
*  These coded instructions, statements, and computer programs  contain	*
*  unpublished  proprietary  information of Silicon Graphics, Inc., and	*
*  are protected by Federal copyright  law.  They  may not be disclosed	*
*  to  third  parties  or copied or duplicated in any form, in whole or	*
*  in part, without the prior written consent of Silicon Graphics, Inc.	*
*									*
*************************************************************************
*/

// $Id: vulca.v,v 1.1 2002/05/21 23:55:45 berndt Exp $

////////////////////////////////////////////////////////////////////////
//
// Project Reality
//
// module:	vulca
// description:	Carry-lookahead adjustment for vector unit multiply.
//		Compliment of carry out across 25 bits. Conditional sum
//		style. Use xn02d1 of registered complimented carry out
//		with carry out from carry-save adder, then xo02d1h that
//		with carry out from carry-propagating adder to form true
//		carry. This corrects for the unwanted carry out from the
//		multiplier that would otherwise be injected into the
//		high-order bits of the accumulator.
//
// designer:	Phil Gossett
// date:	10/16/94
//
////////////////////////////////////////////////////////////////////////

module vulca (a, b, co_l);

input [24:0] a;
input [24:0] b;

output co_l;

wire [30:6] c0b;
wire [30:7] c1b;

// conditional cells:
nd02d2 c06  (.a1(a[0]),  .a2(b[0]),  .zn(c0b[6]));

nd02d2 c07  (.a1(a[1]),  .a2(b[1]),  .zn(c0b[7]));
nr02d2 c17  (.a1(a[1]),  .a2(b[1]),  .zn(c1b[7]));

nd02d2 c08  (.a1(a[2]),  .a2(b[2]),  .zn(c0b[8]));
nr02d2 c18  (.a1(a[2]),  .a2(b[2]),  .zn(c1b[8]));

nd02d2 c09  (.a1(a[3]),  .a2(b[3]),  .zn(c0b[9]));
nr02d2 c19  (.a1(a[3]),  .a2(b[3]),  .zn(c1b[9]));

nd02d2 c010 (.a1(a[4]),  .a2(b[4]),  .zn(c0b[10]));
nr02d2 c110 (.a1(a[4]),  .a2(b[4]),  .zn(c1b[10]));

nd02d2 c011 (.a1(a[5]),  .a2(b[5]),  .zn(c0b[11]));
nr02d2 c111 (.a1(a[5]),  .a2(b[5]),  .zn(c1b[11]));

nd02d2 c012 (.a1(a[6]),  .a2(b[6]),  .zn(c0b[12]));
nr02d2 c112 (.a1(a[6]),  .a2(b[6]),  .zn(c1b[12]));

nd02d2 c013 (.a1(a[7]),  .a2(b[7]),  .zn(c0b[13]));
nr02d2 c113 (.a1(a[7]),  .a2(b[7]),  .zn(c1b[13]));

nd02d2 c014 (.a1(a[8]),  .a2(b[8]),  .zn(c0b[14]));
nr02d2 c114 (.a1(a[8]),  .a2(b[8]),  .zn(c1b[14]));

nd02d2 c015 (.a1(a[9]),  .a2(b[9]),  .zn(c0b[15]));
nr02d2 c115 (.a1(a[9]),  .a2(b[9]),  .zn(c1b[15]));

nd02d2 c016 (.a1(a[10]), .a2(b[10]), .zn(c0b[16]));
nr02d2 c116 (.a1(a[10]), .a2(b[10]), .zn(c1b[16]));

nd02d2 c017 (.a1(a[11]), .a2(b[11]), .zn(c0b[17]));
nr02d2 c117 (.a1(a[11]), .a2(b[11]), .zn(c1b[17]));

nd02d2 c018 (.a1(a[12]), .a2(b[12]), .zn(c0b[18]));
nr02d2 c118 (.a1(a[12]), .a2(b[12]), .zn(c1b[18]));

nd02d2 c019 (.a1(a[13]), .a2(b[13]), .zn(c0b[19]));
nr02d2 c119 (.a1(a[13]), .a2(b[13]), .zn(c1b[19]));

nd02d2 c020 (.a1(a[14]), .a2(b[14]), .zn(c0b[20]));
nr02d2 c120 (.a1(a[14]), .a2(b[14]), .zn(c1b[20]));

nd02d2 c021 (.a1(a[15]), .a2(b[15]), .zn(c0b[21]));
nr02d2 c121 (.a1(a[15]), .a2(b[15]), .zn(c1b[21]));

nd02d2 c022 (.a1(a[16]), .a2(b[16]), .zn(c0b[22]));
nr02d2 c122 (.a1(a[16]), .a2(b[16]), .zn(c1b[22]));

nd02d2 c023 (.a1(a[17]), .a2(b[17]), .zn(c0b[23]));
nr02d2 c123 (.a1(a[17]), .a2(b[17]), .zn(c1b[23]));

nd02d2 c024 (.a1(a[18]), .a2(b[18]), .zn(c0b[24]));
nr02d2 c124 (.a1(a[18]), .a2(b[18]), .zn(c1b[24]));

nd02d2 c025 (.a1(a[19]), .a2(b[19]), .zn(c0b[25]));
nr02d2 c125 (.a1(a[19]), .a2(b[19]), .zn(c1b[25]));

nd02d2 c026 (.a1(a[20]), .a2(b[20]), .zn(c0b[26]));
nr02d2 c126 (.a1(a[20]), .a2(b[20]), .zn(c1b[26]));

nd02d2 c027 (.a1(a[21]), .a2(b[21]), .zn(c0b[27]));
nr02d2 c127 (.a1(a[21]), .a2(b[21]), .zn(c1b[27]));

nd02d2 c028 (.a1(a[22]), .a2(b[22]), .zn(c0b[28]));
nr02d2 c128 (.a1(a[22]), .a2(b[22]), .zn(c1b[28]));

nd02d2 c029 (.a1(a[23]), .a2(b[23]), .zn(c0b[29]));
nr02d2 c129 (.a1(a[23]), .a2(b[23]), .zn(c1b[29]));

nd02d2 c030 (.a1(a[24]), .a2(b[24]), .zn(c0b[30]));
nr02d2 c130 (.a1(a[24]), .a2(b[24]), .zn(c1b[30]));

// first rank of muxes (all muxes before register should be high performance):
mx21d1h mac08  (.s(c0b[7]),  .i1(c0b[8]),  .i0(c1b[8]),  .z(mac0b8));
mx21d1h mac18  (.s(c1b[7]),  .i1(c0b[8]),  .i0(c1b[8]),  .z(mac1b8));

mx21d1h mac010 (.s(c0b[9]),  .i1(c0b[10]), .i0(c1b[10]), .z(mac0b10));
mx21d1h mac110 (.s(c1b[9]),  .i1(c0b[10]), .i0(c1b[10]), .z(mac1b10));

mx21d1h mac012 (.s(c0b[11]), .i1(c0b[12]), .i0(c1b[12]), .z(mac0b12));
mx21d1h mac112 (.s(c1b[11]), .i1(c0b[12]), .i0(c1b[12]), .z(mac1b12));

mx21d1h mac014 (.s(c0b[13]), .i1(c0b[14]), .i0(c1b[14]), .z(mac0b14));
mx21d1h mac114 (.s(c1b[13]), .i1(c0b[14]), .i0(c1b[14]), .z(mac1b14));

mx21d1h mac016 (.s(c0b[15]), .i1(c0b[16]), .i0(c1b[16]), .z(mac0b16));
mx21d1h mac116 (.s(c1b[15]), .i1(c0b[16]), .i0(c1b[16]), .z(mac1b16));

mx21d1h mac018 (.s(c0b[17]), .i1(c0b[18]), .i0(c1b[18]), .z(mac0b18));
mx21d1h mac118 (.s(c1b[17]), .i1(c0b[18]), .i0(c1b[18]), .z(mac1b18));

mx21d1h mac020 (.s(c0b[19]), .i1(c0b[20]), .i0(c1b[20]), .z(mac0b20));
mx21d1h mac120 (.s(c1b[19]), .i1(c0b[20]), .i0(c1b[20]), .z(mac1b20));

mx21d1h mac022 (.s(c0b[21]), .i1(c0b[22]), .i0(c1b[22]), .z(mac0b22));
mx21d1h mac122 (.s(c1b[21]), .i1(c0b[22]), .i0(c1b[22]), .z(mac1b22));

mx21d1h mac024 (.s(c0b[23]), .i1(c0b[24]), .i0(c1b[24]), .z(mac0b24));
mx21d1h mac124 (.s(c1b[23]), .i1(c0b[24]), .i0(c1b[24]), .z(mac1b24));

mx21d1h mac026 (.s(c0b[25]), .i1(c0b[26]), .i0(c1b[26]), .z(mac0b26));
mx21d1h mac126 (.s(c1b[25]), .i1(c0b[26]), .i0(c1b[26]), .z(mac1b26));

mx21d1h mac028 (.s(c0b[27]), .i1(c0b[28]), .i0(c1b[28]), .z(mac0b28));
mx21d1h mac128 (.s(c1b[27]), .i1(c0b[28]), .i0(c1b[28]), .z(mac1b28));

mx21d1h mac030 (.s(c0b[29]), .i1(c0b[30]), .i0(c1b[30]), .z(mac0b30));
mx21d1h mac130 (.s(c1b[29]), .i1(c0b[30]), .i0(c1b[30]), .z(mac1b30));

// second rank of muxes:
mx21d1h mbc010 (.s(mac0b8),  .i1(mac0b10), .i0(mac1b10), .z(mbc0b10));
mx21d1h mbc110 (.s(mac1b8),  .i1(mac0b10), .i0(mac1b10), .z(mbc1b10));

mx21d1h mbc014 (.s(mac0b12), .i1(mac0b14), .i0(mac1b14), .z(mbc0b14));
mx21d1h mbc114 (.s(mac1b12), .i1(mac0b14), .i0(mac1b14), .z(mbc1b14));

mx21d1h mbc018 (.s(mac0b16), .i1(mac0b18), .i0(mac1b18), .z(mbc0b18));
mx21d1h mbc118 (.s(mac1b16), .i1(mac0b18), .i0(mac1b18), .z(mbc1b18));

mx21d1h mbc022 (.s(mac0b20), .i1(mac0b22), .i0(mac1b22), .z(mbc0b22));
mx21d1h mbc122 (.s(mac1b20), .i1(mac0b22), .i0(mac1b22), .z(mbc1b22));

mx21d1h mbc026 (.s(mac0b24), .i1(mac0b26), .i0(mac1b26), .z(mbc0b26));
mx21d1h mbc126 (.s(mac1b24), .i1(mac0b26), .i0(mac1b26), .z(mbc1b26));

mx21d1h mbc030 (.s(mac0b28), .i1(mac0b30), .i0(mac1b30), .z(mbc0b30));
mx21d1h mbc130 (.s(mac1b28), .i1(mac0b30), .i0(mac1b30), .z(mbc1b30));

// third rank of muxes:
mx21d1h mcc014 (.s(mbc0b10), .i1(mbc0b14), .i0(mbc1b14), .z(mcc0b14));
mx21d1h mcc114 (.s(mbc1b10), .i1(mbc0b14), .i0(mbc1b14), .z(mcc1b14));

mx21d1h mcc022 (.s(mbc0b18), .i1(mbc0b22), .i0(mbc1b22), .z(mcc0b22));
mx21d1h mcc122 (.s(mbc1b18), .i1(mbc0b22), .i0(mbc1b22), .z(mcc1b22));

mx21d1h mcc030 (.s(mbc0b26), .i1(mbc0b30), .i0(mbc1b30), .z(mcc0b30));
mx21d1h mcc130 (.s(mbc1b26), .i1(mbc0b30), .i0(mbc1b30), .z(mcc1b30));

// fourth rank of muxes:
mx21d1h mdc014 (.s(c0b[6]),  .i1(mcc0b14), .i0(mcc1b14), .z(mdc0b14));

mx21d1h mdc030 (.s(mcc0b22), .i1(mcc0b30), .i0(mcc1b30), .z(mdc0b30));
mx21d1h mdc130 (.s(mcc1b22), .i1(mcc0b30), .i0(mcc1b30), .z(mdc1b30));

// fifth rank of muxes:
mx21d1h mec030 (.s(mdc0b14), .i1(mdc0b30), .i0(mdc1b30), .z(co_l));

endmodule // vulca
