module vudp( vdpregoptrf_cp, vdpsumuprmu_cp, vdpsumuprmu, vdpsclrmxwhlrf,
        vdpstoredatargrf_cp, vdpdatatristen, vdpregopsrf_cp, vdpregopsrf,
        vdpregfile_rcl, vdpregfile_rch, vdpregfile_rbl, vdpregfile_rbh,
        vdpregfile_ral, vdpregfile_rah, vdpregfile_rclb, vdpregfile_rchb,
        vdpregfile_rblb, vdpregfile_rbhb, vdpregfile_ralb, vdpregfile_rahb,
        vdpregfile_w1ly, vdpregfile_w1lx, vdpregfile_w1hy, vdpregfile_w1hx,
        vdpregfile_w0l, vdpregfile_w0h, vdpregfile_w1lyb, vdpregfile_w1lxb,
        vdpregfile_w1hyb, vdpregfile_w1hxb, vdpregfile_w0lb, vdpregfile_w0hb,
        vdpcompvtmu, vdpsumlwrmu_cp, vdpsumlwrmu, vdpalumu_ovr, vdpalumu_cout,
        vdpalumu_cin, vdpalumu, vdpcoutlwrmu_cp, vdpcoutlwrmu, vdpzerodetvtmu_z,
        vdpsclrmxhalfrf, vdpsclrmxqurtrf, vdpcoutuprmu_cp, vdpcoutuprmu,
        vdponedetalumu_z, vdpzerodetalumu_z, vdpzerodetvsmu_z, vdpaccumlwrac_cp,
        vdpaccumlwrac, vdpadderlwrac_ovr, vdpadderlwrac_cout, vdpadderlwrac_cin,
        vdpcsalwrac_cout, vdpcsalwrac_cin, vdpcsalwrcinac, vdpcsalwrbinac,
        vdpcsalwrainac, vdpslctmxwb, vdpaccumuprac_cp, vdpaccummidac_cp,
        vdpaccummidac, vdpcsauprainac, vdpcsauprac_cout, vdpcsauprac_cin,
        vdpcsauprbinac, vdpcsauprcinnandac, vdpincremac_dwn, vdpincremac_cout,
        vdpincremac_cin, vdpadderuprac_ovr, vdpadderuprac_cout,
        vdpadderuprac_cin, vdpincremxac, vdpaccuprmxac, vdpacchighonewb_z,
        vdpacchighzerowb_z, vdpaccmidzerowb_z, vdpdivrsltwb, vdpstoredatamu,
        vdpsclrwhlinrf, vdpsclrhlfinrf, vdpsclrqurtinrf, vdpoperandtrf,
        vdpsclrhlfoutrf, vdpsclrwhloutrf, vdpmplcndmu, vdpoptsignmu, vdpmplrmu,
        vumsumlowermu, vumcarrylowermu, vumsumuppermu, vumcarryuppermu,
        vdpopssignrf, vdprundvluac, vdpaccsign15wb, vdpaccsign31wb,
        vdpaccsign21wb, vdpaccsign47wb, vdpclprsltwb,
	vdpfeedalucimu_top, vdpfeedalucimu_bot,
	vdpfeedcsaac_top, vdpfeedcsaac_bot,
	vdpfeedaddciac_top, vdpfeedaddciac_bot,
	vdpfeedaddcoac_top, vdpfeedaddcoac_bot,
	vdpfeedincrciac_top, vdpfeedincrciac_bot
	);

input   vdpregoptrf_cp;
input   vdpsumuprmu_cp;
input   [2:0] vdpsumuprmu;
input   [2:0] vdpsclrmxwhlrf;
input   vdpstoredatargrf_cp;
input   vdpdatatristen;
input   vdpregopsrf_cp;
input   [2:0] vdpregopsrf;
input   [15:0] vdpregfile_rcl;
input   [15:0] vdpregfile_rch;
input   [15:0] vdpregfile_rbl;
input   [15:0] vdpregfile_rbh;
input   [15:0] vdpregfile_ral;
input   [15:0] vdpregfile_rah;
input   [15:0] vdpregfile_rclb;
input   [15:0] vdpregfile_rchb;
input   [15:0] vdpregfile_rblb;
input   [15:0] vdpregfile_rbhb;
input   [15:0] vdpregfile_ralb;
input   [15:0] vdpregfile_rahb;
input   [15:0] vdpregfile_w1ly;
input   [15:0] vdpregfile_w1lx;
input   [15:0] vdpregfile_w1hy;
input   [15:0] vdpregfile_w1hx;
input   [15:0] vdpregfile_w0l;
input   [15:0] vdpregfile_w0h;
input   [15:0] vdpregfile_w1lyb;
input   [15:0] vdpregfile_w1lxb;
input   [15:0] vdpregfile_w1hyb;
input   [15:0] vdpregfile_w1hxb;
input   [15:0] vdpregfile_w0lb;
input   [15:0] vdpregfile_w0hb;
input   vdpcompvtmu;
input   vdpsumlwrmu_cp;
input   [2:0] vdpsumlwrmu;
output  vdpalumu_ovr;
output  vdpalumu_cout;
input   vdpalumu_cin;
input   [4:0] vdpalumu;
input   vdpcoutlwrmu_cp;
input   [2:0] vdpcoutlwrmu;
output  vdpzerodetvtmu_z;
input   vdpsclrmxhalfrf;
input   vdpsclrmxqurtrf;
input   vdpcoutuprmu_cp;
input   [2:0] vdpcoutuprmu;
output  vdponedetalumu_z;
output  vdpzerodetalumu_z;
output  vdpzerodetvsmu_z;
input   vdpaccumlwrac_cp;
input   [2:0] vdpaccumlwrac;
output  vdpadderlwrac_ovr;
output  vdpadderlwrac_cout;
input   vdpadderlwrac_cin;
output  vdpcsalwrac_cout;
input   vdpcsalwrac_cin;
input   vdpcsalwrcinac;
input   [2:0] vdpcsalwrbinac;
input   [2:0] vdpcsalwrainac;
input   [5:0] vdpslctmxwb;
input   vdpaccumuprac_cp;
input   vdpaccummidac_cp;
input   [2:0] vdpaccummidac;
input   [1:0] vdpcsauprainac;
output  vdpcsauprac_cout;
input   vdpcsauprac_cin;
input   [1:0] vdpcsauprbinac;
input   vdpcsauprcinnandac;
input   vdpincremac_dwn;
output  vdpincremac_cout;
input   vdpincremac_cin;
output  vdpadderuprac_ovr;
output  vdpadderuprac_cout;
input   vdpadderuprac_cin;
input   [1:0] vdpincremxac;
input   [2:0] vdpaccuprmxac;
output  vdpacchighonewb_z;
output  vdpacchighzerowb_z;
output  vdpaccmidzerowb_z;
input   [15:0] vdpdivrsltwb;
inout   [15:0] vdpstoredatamu;
input   [15:0] vdpsclrwhlinrf;
input   [15:0] vdpsclrhlfinrf;
input   [15:0] vdpsclrqurtinrf;
output  [15:0] vdpoperandtrf;
output  [15:0] vdpsclrhlfoutrf;
output  [15:0] vdpsclrwhloutrf;
output  [15:0] vdpmplcndmu;
output  [15:15] vdpoptsignmu;
output  [15:0] vdpmplrmu;
input   [15:0] vumsumlowermu;
input   [15:0] vumcarrylowermu;
input   [15:0] vumsumuppermu;
input   [15:0] vumcarryuppermu;
output  [15:15] vdpopssignrf;
input   [3:0] vdprundvluac;
output  [15:15] vdpaccsign15wb;
output  [15:15] vdpaccsign31wb;
output  [5:5] vdpaccsign21wb;
output  [15:15] vdpaccsign47wb;
input   [2:0] vdpclprsltwb;

input	[0:0]	vdpfeedalucimu_top;
output	[0:0]	vdpfeedalucimu_bot;
input	[0:0]	vdpfeedcsaac_top;
output	[0:0]	vdpfeedcsaac_bot;
input	[0:0]	vdpfeedaddciac_top;
output	[0:0]	vdpfeedaddciac_bot;
input	[0:0]	vdpfeedaddcoac_top;
output	[0:0]	vdpfeedaddcoac_bot;
input	[0:0]	vdpfeedincrciac_top;
output	[0:0]	vdpfeedincrciac_bot;

wire    [15:0] b6;
wire    [15:0] b7;
wire    [15:0] b8;
wire    [15:0] b9;
wire    [15:0] b10;
wire    [15:0] b18;
wire    [15:0] vdpslctdatawb;
wire    [15:0] b22;
wire    [15:0] vdpstoredatarf;
wire    [15:0] vdpopndtoutrf;
wire    [15:0] b28;
wire    [15:0] vdpwhlbufinrf;
wire    [15:0] b30;
wire    [15:0] vdpcompvtoutmu;
wire    [15:0] vdpsumuprdatamu;
wire    [15:0] vdpsumlwrdatamu;
wire    [15:0] vdpaluresultmu;
wire    [15:0] vdpcoutlwrdatamu;
wire    [15:0] vdphlfbufinrf;
wire    [15:0] vdpcoutuprdatamu;
wire    [15:0] b43;
wire    [15:0] b46;
wire    [15:0] b47;
wire    [15:0] b48;
wire    [15:0] b49;
wire    [15:0] vuadderinlowb;
wire    [15:0] vuadderinlowa;
wire    [15:0] vdpadderlwrdataac;
wire    [15:0] b54;
wire    [15:0] b56;
wire    [15:0] b60;
wire    [15:0] vuadderinhighb;
wire    [15:0] vuadderinhigha;
wire    [15:0] b63;
wire    [15:0] vdpcsauprcindataac;
wire    [15:0] b65;
wire    [15:0] vdpincrmdataac;
wire    [15:0] b69;
wire    [15:0] b70;
wire   [0:0] b_vdpfeedalucimu;
wire   [0:0] b_vdpfeedcsaac;
wire   [0:0] b_vdpfeedaddciac;
wire   [0:0] b_vdpfeedaddcoac;
wire   [0:0] b_vdpfeedincrciac;

  assign vdpoperandtrf[15:0] = b6[15:0];
  assign vdpsclrhlfoutrf[15:0] = b7[15:0];
  assign vdpsclrwhloutrf[15:0] = b8[15:0];
  assign vdpmplcndmu[15:0] = b9[15:0];
  assign vdpoptsignmu[15:15] = b9[15:15];
  assign vdpmplrmu[15:0] = b10[15:0];
  assign vdpopssignrf[15:15] = b22[15:15];
  assign vdpaccsign15wb[15:15] = b47[15:15];
  assign vdpaccsign31wb[15:15] = b48[15:15];
  assign vdpaccsign21wb[5:5] = b48[5:5];
  assign vdpaccsign47wb[15:15] = b56[15:15];
//  assign vdpfeedalucimu_top[0:0] = b_vdpfeedalucimu[0:0];
//  assign vdpfeedalucimu_bot[0:0] = b_vdpfeedalucimu[0:0];
//  assign vdpfeedcsaac_top[0:0] = b_vdpfeedcsaac[0:0];
//  assign vdpfeedcsaac_bot[0:0] = b_vdpfeedcsaac[0:0];
//  assign vdpfeedaddciac_top[0:0] = b_vdpfeedaddciac[0:0];
//  assign vdpfeedaddciac_bot[0:0] = b_vdpfeedaddciac[0:0];
//  assign vdpfeedaddcoac_top[0:0] = b_vdpfeedaddcoac[0:0];
//  assign vdpfeedaddcoac_bot[0:0] = b_vdpfeedaddcoac[0:0];
//  assign vdpfeedincrciac_top[0:0] = b_vdpfeedincrciac[0:0];
//  assign vdpfeedincrciac_bot[0:0] = b_vdpfeedincrciac[0:0];

  assign vdpfeedalucimu_bot[0:0] = vdpfeedalucimu_top[0:0];
  assign vdpfeedcsaac_bot[0:0] = vdpfeedcsaac_top[0:0];
  assign vdpfeedaddciac_bot[0:0] = vdpfeedaddciac_top[0:0];
  assign vdpfeedaddcoac_bot[0:0] = vdpfeedaddcoac_top[0:0];
  assign vdpfeedincrciac_bot[0:0] = vdpfeedincrciac_top[0:0];

  dpdff0101 #(16, 1, 0)  vdpregoptrf_i(
		.D(b30[15:0]),
		.Q(b18[15:0]),
		.INST_CP(vdpregoptrf_cp));

  dpdff0501 #(16, 1, 0)  vdpsumuprmu_i(
		.Q(vdpsumuprdatamu[15:0]),
		.D0(vdpsumuprdatamu[15:0]),
		.D1(vumsumuppermu[15:0]),
		.D2(b10[15:0]),
		.INST_CP(vdpsumuprmu_cp),
		.INST(vdpsumuprmu[2:0]));

  dpmux3031 #(16, 1, 0)  vdpsclrmxwhlrf_i(
		.Z(b30[15:0]),
		.I0(b18[15:0]),
		.I1(vdpwhlbufinrf[15:0]),
		.I2(vdpsclrwhlinrf[15:0]),
		.INST(vdpsclrmxwhlrf[2:0]));

  dpbuf0013 #(16, 1, 0)  vdpmplcndbufoutmu_i(
		.I(b18[15:0]),
		.Z(b9[15:0]));

  dpbuf0013 #(16, 1, 0)  vdpopndtbufoutrf_i(
		.I(vdpopndtoutrf[15:0]),
		.Z(b6[15:0]));

  dpdff0101 #(16, 1, 0)  vdpstoredatargrf_i(
		.D(vdpstoredatarf[15:0]),
		.Q(b28[15:0]),
		.INST_CP(vdpstoredatargrf_cp));

  dptsb1023 #(16, 1, 0)  vdpdatatristen_i(
		.I(b28[15:0]),
		.Z(vdpstoredatamu[15:0]),
		.INST(vdpdatatristen));

  dpdff0501 #(16, 1, 0)  vdpregopsrf_i(
		.Q(b10[15:0]),
		.D0(b10[15:0]),
		.D1(b22[15:0]),
		.D2({16{1'b1}}),
		.INST_CP(vdpregopsrf_cp),
		.INST(vdpregopsrf[2:0]));

//  dprgf020h #()  vdpregfile_i(
  dprgf020h  vdpregfile_i(
		.d0(vdpslctdatawb[15:0]),
		.a(vdpopndtoutrf[15:0]),
		.c(vdpstoredatarf[15:0]),
		.b(b22[15:0]),
		.d1(vdpstoredatamu[15:0]),
		.INST_RCL(vdpregfile_rcl[15:0]),
		.INST_RCH(vdpregfile_rch[15:0]),
		.INST_RBL(vdpregfile_rbl[15:0]),
		.INST_RBH(vdpregfile_rbh[15:0]),
		.INST_RAL(vdpregfile_ral[15:0]),
		.INST_RAH(vdpregfile_rah[15:0]),
		.INST_RCLB(vdpregfile_rclb[15:0]),
		.INST_RCHB(vdpregfile_rchb[15:0]),
		.INST_RBLB(vdpregfile_rblb[15:0]),
		.INST_RBHB(vdpregfile_rbhb[15:0]),
		.INST_RALB(vdpregfile_ralb[15:0]),
		.INST_RAHB(vdpregfile_rahb[15:0]),
		.INST_W1LY(vdpregfile_w1ly[15:0]),
		.INST_W1LX(vdpregfile_w1lx[15:0]),
		.INST_W1HY(vdpregfile_w1hy[15:0]),
		.INST_W1HX(vdpregfile_w1hx[15:0]),
		.INST_W0L(vdpregfile_w0l[15:0]),
		.INST_W0H(vdpregfile_w0h[15:0]),
		.INST_W1LYB(vdpregfile_w1lyb[15:0]),
		.INST_W1LXB(vdpregfile_w1lxb[15:0]),
		.INST_W1HYB(vdpregfile_w1hyb[15:0]),
		.INST_W1HXB(vdpregfile_w1hxb[15:0]),
		.INST_W0LB(vdpregfile_w0lb[15:0]),
		.INST_W0HB(vdpregfile_w0hb[15:0]));

  dpxnr1021 #(16, 1, 0)  vdpcompvtmu_i(
		.A1(b9[15:0]),
		.ZN(vdpcompvtoutmu[15:0]),
		.INST(vdpcompvtmu));

  dpdff0501 #(16, 1, 0)  vdpsumlwrmu_i(
		.Q(vdpsumlwrdatamu[15:0]),
		.D0(vdpsumlwrdatamu[15:0]),
		.D1(vumsumlowermu[15:0]),
		.D2(vdpcompvtoutmu[15:0]),
		.INST_CP(vdpsumlwrmu_cp),
		.INST(vdpsumlwrmu[2:0]));

  dpalu001s #(16, 4, 0)  vdpalumu_i(
		.A(b9[15:0]),
		.B(b10[15:0]),
		.SO(vdpaluresultmu[15:0]),
		.INST_OVR(vdpalumu_ovr),
		.INST_COUT(vdpalumu_cout),
		.INST_CIN(vdpalumu_cin),
		.INST(vdpalumu[4:0]));

  dpdff0501 #(16, 1, 0)  vdpcoutlwrmu_i(
		.Q(vdpcoutlwrdatamu[15:0]),
		.D0(vdpcoutlwrdatamu[15:0]),
		.D1(vumcarrylowermu[15:0]),
		.D2(vdpaluresultmu[15:0]),
		.INST_CP(vdpcoutlwrmu_cp),
		.INST(vdpcoutlwrmu[2:0]));

  dpbuf0013 #(16, 1, 0)  vdpwhlbufoutrf2_i(
		.I(vdpwhlbufinrf[15:0]),
		.Z(b8[15:0]));

  dpbuf0013 #(16, 1, 0)  vdphlfbufoutrf2_i(
		.I(vdphlfbufinrf[15:0]),
		.Z(b7[15:0]));

  dpzdt001s #(16, 1, 0)  vdpzerodetvtmu_i(
		.A(b9[15:0]),
		.INST_Z(vdpzerodetvtmu_z));

  dpmux1021 #(16, 1, 0)  vdpsclrmxhalfrf_i(
		.I1(vdpsclrhlfinrf[15:0]),
		.I0(vdphlfbufinrf[15:0]),
		.Z(vdpwhlbufinrf[15:0]),
		.INST(vdpsclrmxhalfrf));

  dpmux1021 #(16, 1, 0)  vdpsclrmxqurtrf_i(
		.I1(vdpsclrqurtinrf[15:0]),
		.I0(b6[15:0]),
		.Z(vdphlfbufinrf[15:0]),
		.INST(vdpsclrmxqurtrf));

  dpbuf0013 #(16, 1, 0)  vdphlfbufoutrf1_i(
		.I(vdphlfbufinrf[15:0]),
		.Z(b7[15:0]));

  dpbuf0013 #(16, 1, 0)  vdpwhlbufoutrf1_i(
		.I(vdpwhlbufinrf[15:0]),
		.Z(b8[15:0]));

  dpdff0501 #(16, 1, 0)  vdpcoutuprmu_i(
		.Q(vdpcoutuprdatamu[15:0]),
		.D0(vdpcoutuprdatamu[15:0]),
		.D1(vumcarryuppermu[15:0]),
		.D2(vdpaluresultmu[15:0]),
		.INST_CP(vdpcoutuprmu_cp),
		.INST(vdpcoutuprmu[2:0]));

  dp1dt001s #(16, 1, 0)  vdponedetalumu_i(
		.A(vdpaluresultmu[15:0]),
		.INST_Z(vdponedetalumu_z));

  dpzdt001s #(16, 1, 0)  vdpzerodetalumu_i(
		.A(vdpaluresultmu[15:0]),
		.INST_Z(vdpzerodetalumu_z));

  dpzdt001s #(16, 1, 0)  vdpzerodetvsmu_i(
		.A(b10[15:0]),
		.INST_Z(vdpzerodetvsmu_z));

  dpdff0501 #(16, 1, 0)  vdpaccumlwrac_i(
		.Q(b47[15:0]),
		.D0(b47[15:0]),
		.D1(vdpadderlwrdataac[15:0]),
		.D2(b54[15:0]),
		.INST_CP(vdpaccumlwrac_cp),
		.INST(vdpaccumlwrac[2:0]));

  dpadd001s #(16, 3, 0)  vdpadderlwrac_i(
		.A(vuadderinlowa[15:0]),
		.B(vuadderinlowb[15:0]),
		.SO(vdpadderlwrdataac[15:0]),
		.INST_OVR(vdpadderlwrac_ovr),
		.INST_COUT(vdpadderlwrac_cout),
		.INST_CIN(vdpadderlwrac_cin));

//  dpcsa020h #()  vdpcsalwrac_i(
  dpcsa020h #(16, 1, 0)  vdpcsalwrac_i(
		.A3(b43[15:0]),
		.A2(b46[15:0]),
		.S1(vuadderinlowa[15:0]),
		.S2(vuadderinlowb[15:0]),
		.A1(b49[15:0]),
		.INST_COUT(vdpcsalwrac_cout),
		.INST_CIN(vdpcsalwrac_cin));

  dpmux1021 #(16, 1, 0)  vdpcsalwrcinac_i(
		.I1(vdpsumuprdatamu[15:0]),
		.I0(vdpsumlwrdatamu[15:0]),
		.Z(b43[15:0]),
		.INST(vdpcsalwrcinac));

  dpmux3031 #(16, 1, 0)  vdpcsalwrbinac_i(
		.Z(b46[15:0]),
		.I0(vdpcoutlwrdatamu[15:0]),
		.I1({vdprundvluac[3:2], vdprundvluac[2], vdprundvluac[2], vdprundvluac[2],
                      vdprundvluac[2], vdprundvluac[2], vdprundvluac[2],
                      vdprundvluac[2], vdprundvluac[2:0],
                      vdprundvluac[0], vdprundvluac[0], vdprundvluac[0],
                      vdprundvluac[0]}),
		.I2(vdpcoutuprdatamu[15:0]),
		.INST(vdpcsalwrbinac[2:0]));

  dpmux3031 #(16, 1, 0)  vdpcsalwrainac_i(
		.Z(b49[15:0]),
		.I0(b47[15:0]),
		.I1(b48[15:0]),
		.I2({vdprundvluac[3:2], vdprundvluac[2], vdprundvluac[2], vdprundvluac[2],
                      vdprundvluac[2], vdprundvluac[2], vdprundvluac[2],
                      vdprundvluac[2], vdprundvluac[2:0],
                      vdprundvluac[0], vdprundvluac[0], vdprundvluac[0],
                      vdprundvluac[0]}),
		.INST(vdpcsalwrainac[2:0]));

  dpmux6061 #(16, 1, 0)  vdpslctmxwb_i(
		.Z(vdpslctdatawb[15:0]),
		.I0(b56[15:0]),
		.I1(b48[15:0]),
		.I2(b47[15:0]),
		.I3({b56[0], b48[15:5], 4'd0}),
		.I4({vdpclprsltwb[2:1], vdpclprsltwb[1], vdpclprsltwb[1], vdpclprsltwb[1],
                      vdpclprsltwb[1], vdpclprsltwb[1], vdpclprsltwb[1],
                      vdpclprsltwb[1], vdpclprsltwb[1], vdpclprsltwb[1],
                      vdpclprsltwb[1:0], vdpclprsltwb[0],
                      vdpclprsltwb[0], vdpclprsltwb[0]}),
		.I5(vdpdivrsltwb[15:0]),
		.INST(vdpslctmxwb[5:0]));

  dpdff0101 #(16, 1, 0)  vdpaccumuprac_i(
		.D(b70[15:0]),
		.Q(b56[15:0]),
		.INST_CP(vdpaccumuprac_cp));

  dpdff0501 #(16, 1, 0)  vdpaccummidac_i(
		.Q(b48[15:0]),
		.D0(b48[15:0]),
		.D1(b54[15:0]),
		.D2(vdpadderlwrdataac[15:0]),
		.INST_CP(vdpaccummidac_cp),
		.INST(vdpaccummidac[2:0]));

  dpmux2021 #(16, 1, 0)  vdpcsauprainac_i(
		.Z(b60[15:0]),
		.I1(b56[15:0]),
		.I0(b48[15:0]),
		.INST(vdpcsauprainac[1:0]));

//  dpcsa020h #()  vdpcsauprac_i(
  dpcsa020h #(16, 1, 0)  vdpcsauprac_i(
		.A3(vdpcsauprcindataac[15:0]),
		.A2(b63[15:0]),
		.S1(vuadderinhigha[15:0]),
		.S2(vuadderinhighb[15:0]),
		.A1(b60[15:0]),
		.INST_COUT(vdpcsauprac_cout),
		.INST_CIN(vdpcsauprac_cin));

  dpmux2021 #(16, 1, 0)  vdpcsauprbinac_i(
		.Z(b63[15:0]),
		.I1({vdprundvluac[3], vdprundvluac[3], vdprundvluac[3], vdprundvluac[3],
                      vdprundvluac[3], vdprundvluac[3], vdprundvluac[3],
                      vdprundvluac[3], vdprundvluac[3], vdprundvluac[3],
                      vdprundvluac[3], vdprundvluac[3], vdprundvluac[3],
                      vdprundvluac[3], vdprundvluac[3], vdprundvluac[3]}),
		.I0(vdpcoutuprdatamu[15:0]),
		.INST(vdpcsauprbinac[1:0]));

  dpnnd1021 #(16, 1, 0)  vdpcsauprcinnandac_i(
		.A1(vdpsumuprdatamu[15:0]),
		.ZN(b65[15:0]),
		.INST(vdpcsauprcinnandac));

  dpinv0011 #(16, 1, 0)  vdpcsauprcininvac_i(
		.ZN(vdpcsauprcindataac[15:0]),
		.I(b65[15:0]));

  dpidc000h #(16, 5, 0)  vdpincremac_i(
		.A(b56[15:0]),
		.Z(vdpincrmdataac[15:0]),
		.INST_DWN(vdpincremac_dwn),
		.INST_COUT(vdpincremac_cout),
		.INST_CIN(vdpincremac_cin));

  dpadd001s #(16, 3, 0)  vdpadderuprac_i(
		.A(vuadderinhigha[15:0]),
		.B(vuadderinhighb[15:0]),
		.SO(b54[15:0]),
		.INST_OVR(vdpadderuprac_ovr),
		.INST_COUT(vdpadderuprac_cout),
		.INST_CIN(vdpadderuprac_cin));

  dpmux2021 #(16, 1, 0)  vdpincremxac_i(
		.Z(b69[15:0]),
		.I1(vdpincrmdataac[15:0]),
		.I0({b54[15], b54[15], b54[15], b54[15], b54[15], b54[15], b54[15], b54[15],
                      b54[15], b54[15], b54[15], b54[15], b54[15],
                      b54[15], b54[15], b54[15]}),
		.INST(vdpincremxac[1:0]));

  dpmux3031 #(16, 1, 0)  vdpaccuprmxac_i(
		.Z(b70[15:0]),
		.I0(b56[15:0]),
		.I1(b69[15:0]),
		.I2(b54[15:0]),
		.INST(vdpaccuprmxac[2:0]));

  dp1dt001s #(16, 1, 0)  vdpacchighonewb_i(
		.A(b56[15:0]),
		.INST_Z(vdpacchighonewb_z));

  dpzdt001s #(16, 1, 0)  vdpacchighzerowb_i(
		.A(b56[15:0]),
		.INST_Z(vdpacchighzerowb_z));

  dpzdt001s #(16, 1, 0)  vdpaccmidzerowb_i(
		.A({b48[15:5], 5'd0}),
		.INST_Z(vdpaccmidzerowb_z));

endmodule
