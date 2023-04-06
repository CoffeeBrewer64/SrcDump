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

// $Id: vumult.v,v 1.3 2003/01/08 03:10:36 berndt Exp $

module vumult( csa4th_cout, csa4th_cin, csa1st_cout, csa1st_cin, mpldinvmu,
        csa2nd_cout, csa2nd_cin, csa3rd_cout, csa3rd_cin, csa6th_cout,
        csa6th_cin, csa7th_cout, csa7th_cin, csa5th_cout, csa5th_cin,
        csa8th_cout, csa8th_cin, sumlower, carrylower, sumupper, carryupper,
        mplcnd, mplr, sgnmlpcnd, unsgnmlpcnd, csa1cout, csa2cout, csa3cout,
        csa4cout, csa5cout, csa6cout, csa7cout);

output  csa4th_cout;
input   csa4th_cin;
output  csa1st_cout;
input   csa1st_cin;
input   mpldinvmu;
output  csa2nd_cout;
input   csa2nd_cin;
output  csa3rd_cout;
input   csa3rd_cin;
output  csa6th_cout;
input   csa6th_cin;
output  csa7th_cout;
input   csa7th_cin;
output  csa5th_cout;
input   csa5th_cin;
output  csa8th_cout;
input   csa8th_cin;
output  [15:0] sumlower;
output  [15:0] carrylower;
output  [15:0] sumupper;
output  [15:0] carryupper;
input   [15:0] mplcnd;
input   [15:0] mplr;
input   [0:0] sgnmlpcnd;
input   [0:0] unsgnmlpcnd;
input   [0:0] csa1cout;
input   [0:0] csa2cout;
input   [0:0] csa3cout;
input   [0:0] csa4cout;
input   [0:0] csa5cout;
input   [0:0] csa6cout;
input   [0:0] csa7cout;

wire    [15:0] b3;
wire    [15:0] b4;
wire    [15:0] b12;
wire    [15:0] b13;
wire    [15:0] b14;
wire    [15:0] b22;
wire    [15:0] b23;
wire    [15:0] b24;
wire    [15:0] b28;
wire    [15:0] b32;
wire    [15:0] b33;
wire    [15:0] b34;
wire    [15:0] b37;
wire    [15:0] b38;
wire    [15:0] b48;
wire    [15:0] b53;
wire    [15:0] b54;
wire    [15:0] b56;
wire    [15:0] b58;
wire    [15:0] b59;
wire    [15:0] b63;
wire    [15:0] b66;
wire    [15:0] b76;
wire    [15:0] b77;
wire    [15:0] b78;
wire    [15:0] b84;
wire    [15:0] b86;
wire    [15:0] b88;
wire    [15:0] b91;
wire    [15:0] b92;
wire    [15:0] b94;
wire    [15:0] b95;
wire    [15:0] b96;
wire    [15:0] b100;
wire    [15:0] b102;
wire    [15:0] b103;
wire    [15:0] b104;
wire    [15:0] b107;
wire    [15:0] b108;
wire    [15:0] b111;
wire    [15:0] b112;
wire    [15:0] b118;
wire    [15:0] b119;
wire    [15:0] b122;
wire    [15:0] b123;

  assign sumlower[15:14] = b123[1:0],
         sumlower[13:12] = b118[1:0],
         sumlower[11:10] = b112[1:0],
         sumlower[9:8] = b103[1:0],
         sumlower[7:6] = b100[1:0],
         sumlower[5:4] = b96[1:0],
         sumlower[3:2] = b59[1:0],
         sumlower[1:0] = b34[1:0];
  assign carrylower[15:15] = b122[1:1],
         carrylower[14:14] = b13[14:14],
         carrylower[13:13] = b119[1:1],
         carrylower[12:12] = b13[12:12],
         carrylower[11:11] = b111[1:1],
         carrylower[10:10] = b13[10:10],
         carrylower[9:9] = b107[1:1],
         carrylower[8:8] = b13[8:8],
         carrylower[7:7] = b102[1:1],
         carrylower[6:6] = b13[6:6],
         carrylower[5:5] = b95[1:1],
         carrylower[4:4] = b13[4:4],
         carrylower[3:3] = b58[1:1],
         carrylower[2:0] = b13[2:0];
  assign sumupper[15:0] = b3[15:0];
  assign carryupper[15:0] = b4[15:0];

  dpcsa010h #(16, 2, 0)  csa4th_i(
		.A3({b37[7:6], b100[15:2]}),
		.A2({csa3cout[0], csa3cout[0], b102[15:2]}),
		.S1(b108[15:0]),
		.S2(b104[15:0]),
		.A1(b86[15:0]),
		.INST_COUT(csa4th_cout),
		.INST_CIN(csa4th_cin));

  dpbuf0013 #(16, 1, 0)  csa4sumbuf_i(
		.I(b104[15:0]),
		.Z(b103[15:0]));

  dpaoi0041 #(16, 1, 0)  mlpcnd1sign_i(
		.ZN(b38[15:0]),
		.A2({1'b0, b12[14], 1'b0, b12[12], 1'b0, b12[10], 1'b0, b12[8],
                      1'b0, b12[6], 1'b0, b12[4], 1'b0, b12[2],
                      1'b0, b12[0]}),
		.A1({1'b0, b91[15], 1'b0, b78[15], 1'b0, b77[15], 1'b0, b76[15],
                      1'b0, b54[15], 1'b0, b53[15], 1'b0, b48[15],
                      1'b0, b32[15]}),
		.B({1'b0, b13[15], 1'b0, b13[13], 1'b0, b13[11], 1'b0, b13[9],
                      1'b0, b13[7], 1'b0, b13[5], 1'b0, b13[3],
                      1'b0, b13[1]}));

  dpbuf0013 #(16, 1, 0)  shftselbuf_i(
		.I(b12[15:0]),
		.Z(b23[15:0]));

  dpinv0012 #(16, 1, 0)  signinv_i(
		.I({b91[15], b78[15], sgnmlpcnd[0], unsgnmlpcnd[0], b77[15], b76[15],
                      sgnmlpcnd[0], unsgnmlpcnd[0], b54[15], b53[15],
                      sgnmlpcnd[0], unsgnmlpcnd[0], b48[15], b32[15],
                      sgnmlpcnd[0], unsgnmlpcnd[0]}),
		.ZN(b22[15:0]));

  dpxnr0021 #(16, 1, 0)  bthrcdexor_i(
		.A1({mplr[14], mplr[14], mplr[12], mplr[12], mplr[10], mplr[10], mplr[8],
                      mplr[8], mplr[6], mplr[6], mplr[4], mplr[4],
                      mplr[2], mplr[2], mplr[0], mplr[0]}),
		.A2({mplr[13], mplr[13], mplr[11], mplr[11], mplr[9], mplr[9], mplr[7],
                      mplr[7], mplr[5], mplr[5], mplr[3], mplr[3],
                      mplr[1], mplr[1], 2'd0}),
		.ZN(b12[15:0]));

  dpnor0031 #(16, 1, 0)  inc2comp_i(
		.A3({1'b0, mplr[13], 1'b0, mplr[11], 1'b0, mplr[9], 1'b0,
                      mplr[7], 1'b0, mplr[5], 1'b0, mplr[3], 1'b0,
                      mplr[1], 2'd0}),
		.A2({b14[15], mplr[14], b14[13], mplr[12], b14[11], mplr[10], b14[9],
                      mplr[8], b14[7], mplr[6], b14[5], mplr[4], b14[3],
                      mplr[2], b14[1], mplr[0]}),
		.A1({b12[15], b14[15], b12[13], b14[13], b12[11], b14[11], b12[9], b14[9],
                      b12[7], b14[7], b12[5], b14[5], b12[3], b14[3],
                      b12[1], b14[1]}),
		.ZN(b13[15:0]));

  dpoai0011 #(16, 1, 0)  mlpcnddata1_i(
		.B2({b24[0], b24[0], b24[0], b24[0], b24[0], b24[0], b24[0], b24[0], b24[0],
                      b24[0], b24[0], b24[0], b24[0], b24[0], b24[0],
                      b24[0]}),
		.B1(b33[15:0]),
		.A2({b24[1], b24[1], b24[1], b24[1], b24[1], b24[1], b24[1], b24[1], b24[1],
                      b24[1], b24[1], b24[1], b24[1], b24[1], b24[1],
                      b24[1]}),
		.A1(b28[15:0]),
		.ZN(b32[15:0]));

  dpmux0121 #(16, 1, 0)  mlpcndshft1_i(
		.I0(b32[15:0]),
		.I1({b32[14:0], 1'b0}),
		.SD({b23[1], b23[1], b23[1], b23[1], b23[1], b23[1], b23[1], b23[1:0],
                      b23[0], b23[0], b23[0], b23[0], b23[0], b23[0],
                      b23[0]}),
		.Z(b34[15:0]));

  dpmux0121 #(16, 1, 0)  mlpcndshft3_i(
		.I0(b53[15:0]),
		.I1({b53[14:0], 1'b0}),
		.SD({b23[5], b23[5], b23[5], b23[5], b23[5], b23[5], b23[5], b23[5:4],
                      b23[4], b23[4], b23[4], b23[4], b23[4], b23[4],
                      b23[4]}),
		.Z(b66[15:0]));

  dpoai0011 #(16, 1, 0)  mlpcnddata3_i(
		.B2({b24[4], b24[4], b24[4], b24[4], b24[4], b24[4], b24[4], b24[4], b24[4],
                      b24[4], b24[4], b24[4], b24[4], b24[4], b24[4],
                      b24[4]}),
		.B1(b33[15:0]),
		.A2({b24[5], b24[5], b24[5], b24[5], b24[5], b24[5], b24[5], b24[5], b24[5],
                      b24[5], b24[5], b24[5], b24[5], b24[5], b24[5],
                      b24[5]}),
		.A1(b28[15:0]),
		.ZN(b53[15:0]));

  dpoai0011 #(16, 1, 0)  mlpcnd2sign_i(
		.B2({b24[15], b38[14], b24[13], b38[12], b24[11], b38[10], b24[9], b38[8],
                      b24[7], b38[6], b24[5], b38[4], b24[3], b38[2],
                      b24[1], b38[0]}),
		.B1({b22[12], b22[12], b22[12], b22[12], b22[8], b22[8], b22[8], b22[8],
                      b22[4], b22[4], b22[4], b22[4], b22[0], b22[0],
                      b22[0], b22[0]}),
		.A2({b22[13], b22[13], b22[13], b22[13], b22[9], b22[9], b22[9], b22[9],
                      b22[5], b22[5], b22[5], b22[5], b22[1], b22[1],
                      b22[1], b22[1]}),
		.A1({b22[15], b22[15:14], b22[14], b22[11], b22[11:10], b22[10], b22[7],
                      b22[7:6], b22[6], b22[3], b22[3:2], b22[2]}),
		.ZN(b37[15:0]));

  dpoai0011 #(16, 1, 0)  mlpcnddata2_i(
		.B2({b24[2], b24[2], b24[2], b24[2], b24[2], b24[2], b24[2], b24[2], b24[2],
                      b24[2], b24[2], b24[2], b24[2], b24[2], b24[2],
                      b24[2]}),
		.B1(b33[15:0]),
		.A2({b24[3], b24[3], b24[3], b24[3], b24[3], b24[3], b24[3], b24[3], b24[3],
                      b24[3], b24[3], b24[3], b24[3], b24[3], b24[3],
                      b24[3]}),
		.A1(b28[15:0]),
		.ZN(b48[15:0]));

  dpoai0011 #(16, 1, 0)  mlpcnddata4_i(
		.B2({b24[6], b24[6], b24[6], b24[6], b24[6], b24[6], b24[6], b24[6], b24[6],
                      b24[6], b24[6], b24[6], b24[6], b24[6], b24[6],
                      b24[6]}),
		.B1(b33[15:0]),
		.A2({b24[7], b24[7], b24[7], b24[7], b24[7], b24[7], b24[7], b24[7], b24[7],
                      b24[7], b24[7], b24[7], b24[7], b24[7], b24[7],
                      b24[7]}),
		.A1(b28[15:0]),
		.ZN(b54[15:0]));

  dpmux0121 #(16, 1, 0)  mlpcndshft2_i(
		.I0(b48[15:0]),
		.I1({b48[14:0], 1'b0}),
		.SD({b23[3], b23[3], b23[3], b23[3], b23[3], b23[3], b23[3], b23[3:2],
                      b23[2], b23[2], b23[2], b23[2], b23[2], b23[2],
                      b23[2]}),
		.Z(b56[15:0]));

  dpcsa010h #(16, 2, 0)  csa1st_i(
		.A3({b37[1:0], b34[15:2]}),
		.A2(b56[15:0]),
		.S1(b58[15:0]),
		.S2(b59[15:0]),
		.A1({2'd0, b13[15], 1'b0, b13[13], 1'b0, b13[11], 1'b0,
                      b13[9], 1'b0, b13[7], 1'b0, b13[5], 1'b0,
                      b13[3], 1'b0}),
		.INST_COUT(csa1st_cout),
		.INST_CIN(csa1st_cin));

  dpmux0121 #(16, 1, 0)  mlpcndshft4_i(
		.I0(b54[15:0]),
		.I1({b54[14:0], 1'b0}),
		.SD({b23[7], b23[7], b23[7], b23[7], b23[7], b23[7], b23[7], b23[7:6],
                      b23[6], b23[6], b23[6], b23[6], b23[6], b23[6],
                      b23[6]}),
		.Z(b63[15:0]));

  dpoai0011 #(16, 1, 0)  mlpcnddata8_i(
		.B2({b24[14], b24[14], b24[14], b24[14], b24[14], b24[14], b24[14], b24[14],
                      b24[14], b24[14], b24[14], b24[14], b24[14],
                      b24[14], b24[14], b24[14]}),
		.B1(b33[15:0]),
		.A2({b24[15], b24[15], b24[15], b24[15], b24[15], b24[15], b24[15], b24[15],
                      b24[15], b24[15], b24[15], b24[15], b24[15],
                      b24[15], b24[15], b24[15]}),
		.A1(b28[15:0]),
		.ZN(b91[15:0]));

  dpinv0013 #(16, 1, 0)  mplrcomp_i(
		.I(mplr[15:0]),
		.ZN(b14[15:0]));

  dpinv0013 #(16, 1, 0)  mplcndcomp_i(
		.I(mplcnd[15:0]),
		.ZN(b33[15:0]));

  dpbuf0013 #(16, 1, 0)  mplcndbuf_i(
		.I(mplcnd[15:0]),
		.Z(b28[15:0]));

  dpoai0011 #(16, 1, 0)  mlpcnddata5_i(
		.B2({b24[8], b24[8], b24[8], b24[8], b24[8], b24[8], b24[8], b24[8], b24[8],
                      b24[8], b24[8], b24[8], b24[8], b24[8], b24[8],
                      b24[8]}),
		.B1(b33[15:0]),
		.A2({b24[9], b24[9], b24[9], b24[9], b24[9], b24[9], b24[9], b24[9], b24[9],
                      b24[9], b24[9], b24[9], b24[9], b24[9], b24[9],
                      b24[9]}),
		.A1(b28[15:0]),
		.ZN(b76[15:0]));

  dpoai0011 #(16, 1, 0)  mlpcnddata6_i(
		.B2({b24[10], b24[10], b24[10], b24[10], b24[10], b24[10], b24[10], b24[10],
                      b24[10], b24[10], b24[10], b24[10], b24[10],
                      b24[10], b24[10], b24[10]}),
		.B1(b33[15:0]),
		.A2({b24[11], b24[11], b24[11], b24[11], b24[11], b24[11], b24[11], b24[11],
                      b24[11], b24[11], b24[11], b24[11], b24[11],
                      b24[11], b24[11], b24[11]}),
		.A1(b28[15:0]),
		.ZN(b77[15:0]));

  dpoai0011 #(16, 1, 0)  mlpcnddata7_i(
		.B2({b24[12], b24[12], b24[12], b24[12], b24[12], b24[12], b24[12], b24[12],
                      b24[12], b24[12], b24[12], b24[12], b24[12],
                      b24[12], b24[12], b24[12]}),
		.B1(b33[15:0]),
		.A2({b24[13], b24[13], b24[13], b24[13], b24[13], b24[13], b24[13], b24[13],
                      b24[13], b24[13], b24[13], b24[13], b24[13],
                      b24[13], b24[13], b24[13]}),
		.A1(b28[15:0]),
		.ZN(b78[15:0]));

  dpmux0121 #(16, 1, 0)  vumlrmlpcndshft6_i(
		.I0(b77[15:0]),
		.I1({b77[14:0], 1'b0}),
		.SD({b23[11], b23[11], b23[11], b23[11], b23[11], b23[11], b23[11],
                      b23[11:10], b23[10], b23[10], b23[10], b23[10],
                      b23[10], b23[10], b23[10]}),
		.Z(b84[15:0]));

  dpmux0121 #(16, 1, 0)  mlpcndshft5_i(
		.I0(b76[15:0]),
		.I1({b76[14:0], 1'b0}),
		.SD({b23[9], b23[9], b23[9], b23[9], b23[9], b23[9], b23[9], b23[9:8],
                      b23[8], b23[8], b23[8], b23[8], b23[8], b23[8],
                      b23[8]}),
		.Z(b86[15:0]));

  dpmux0121 #(16, 1, 0)  mlpcndshft7_i(
		.I0(b78[15:0]),
		.I1({b78[14:0], 1'b0}),
		.SD({b23[13], b23[13], b23[13], b23[13], b23[13], b23[13], b23[13],
                      b23[13:12], b23[12], b23[12], b23[12], b23[12],
                      b23[12], b23[12], b23[12]}),
		.Z(b88[15:0]));

  dpnor1021 #(16, 1, 0)  mpldinvmu_i(
		.A1(b33[15:0]),
		.ZN(b92[15:0]),
		.INST(mpldinvmu));

  dpoai0041 #(16, 1, 0)  mlprbthrcd_i(
		.ZN(b24[15:0]),
		.A2({b14[14], mplr[14], b14[12], mplr[12], b14[10], mplr[10], b14[8],
                      mplr[8], b14[6], mplr[6], b14[4], mplr[4], b14[2],
                      mplr[2], b14[0], mplr[0]}),
		.A1({b14[13], mplr[13], b14[11], mplr[11], b14[9], mplr[9], b14[7], mplr[7],
                      b14[5], mplr[5], b14[3], mplr[3], b14[1], mplr[1],
                      1'b1, 1'b0}),
		.B({mplr[15], b14[15], mplr[13], b14[13], mplr[11], b14[11], mplr[9],
                      b14[9], mplr[7], b14[7], mplr[5], b14[5], mplr[3],
                      b14[3], mplr[1], b14[1]}));

  dpmux0121 #(16, 1, 0)  mlpcndshft8_i(
		.I0(b91[15:0]),
		.I1({b91[14:0], 1'b0}),
		.SD({b23[15], b23[15], b23[15], b23[15], b23[15], b23[15], b23[15],
                      b23[15:14], b23[14], b23[14], b23[14], b23[14],
                      b23[14], b23[14], b23[14]}),
		.Z(b94[15:0]));

  dpcsa010h #(16, 2, 0)  csa2nd_i(
		.A3({b37[3:2], b59[15:2]}),
		.A2({csa1cout[0], csa1cout[0], b58[15:2]}),
		.S1(b95[15:0]),
		.S2(b96[15:0]),
		.A1(b66[15:0]),
		.INST_COUT(csa2nd_cout),
		.INST_CIN(csa2nd_cin));

  dpcsa010h #(16, 2, 0)  csa3rd_i(
		.A3({b37[5:4], b96[15:2]}),
		.A2({csa2cout[0], csa2cout[0], b95[15:2]}),
		.S1(b102[15:0]),
		.S2(b100[15:0]),
		.A1(b63[15:0]),
		.INST_COUT(csa3rd_cout),
		.INST_CIN(csa3rd_cin));

  dpcsa010h #(16, 2, 0)  csa6th_i(
		.A3({b37[11:10], b112[15:2]}),
		.A2({csa5cout[0], csa5cout[0], b111[15:2]}),
		.S1(b119[15:0]),
		.S2(b118[15:0]),
		.A1(b88[15:0]),
		.INST_COUT(csa6th_cout),
		.INST_CIN(csa6th_cin));

  dpcsa010h #(16, 2, 0)  csa7th_i(
		.A3({b37[13:12], b118[15:2]}),
		.A2({csa6cout[0], csa6cout[0], b119[15:2]}),
		.S1(b122[15:0]),
		.S2(b123[15:0]),
		.A1(b94[15:0]),
		.INST_COUT(csa7th_cout),
		.INST_CIN(csa7th_cin));

  dpcsa010h #(16, 2, 0)  csa5th_i(
		.A3({b37[9:8], b103[15:2]}),
		.A2({csa4cout[0], csa4cout[0], b107[15:2]}),
		.S1(b111[15:0]),
		.S2(b112[15:0]),
		.A1(b84[15:0]),
		.INST_COUT(csa5th_cout),
		.INST_CIN(csa5th_cin));

  dpbuf0013 #(16, 1, 0)  csa4coutbuf_i(
		.I(b108[15:0]),
		.Z(b107[15:0]));

  dpcsa010h #(16, 2, 0)  csa8th_i(
		.A3({b37[15:14], b123[15:2]}),
		.A2({csa7cout[0], csa7cout[0], b122[15:2]}),
		.S1(b4[15:0]),
		.S2(b3[15:0]),
		.A1(b92[15:0]),
		.INST_COUT(csa8th_cout),
		.INST_CIN(csa8th_cin));

endmodule
