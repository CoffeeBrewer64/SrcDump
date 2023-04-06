module sudp( surfile_rbl, surfile_rbh, surfile_ral, surfile_rah, surfile_rblb,
        surfile_rbhb, surfile_ralb, surfile_rahb, surfile_wl, surfile_wh,
        surfile_wlb, surfile_whb, suwben, suedff_cp, sudwff_cp, suimmlsmux,
        sureinstff_cp, suimmmux, suvulsoffsetmux, surdbmux, surebff_cp,
        suloaden, sudrivels, surdamux, sureaff_cp, suonesdet_z, sushift_s,
        sushbmux, sushamux, suslten, sushen, sualuen, sualu_ovr, sualu_cout,
        sualu_cin, sualu, sualuamux, sualubmux, inst_data, link_pc_delay_pc,
        branch_or_addr, ls_data, suexbsign, sushvamt, suexasign, susltlt,
        sualumsb, shiftamt,
// 3 Feedthrough Outputs:
        suonesdetz_bot, sualucoutl_bot, sualuovr_bot);

input   [15:0] surfile_rbl;
input   [15:0] surfile_rbh;
input   [15:0] surfile_ral;
input   [15:0] surfile_rah;
input   [15:0] surfile_rblb;
input   [15:0] surfile_rbhb;
input   [15:0] surfile_ralb;
input   [15:0] surfile_rahb;
input   [15:0] surfile_wl;
input   [15:0] surfile_wh;
input   [15:0] surfile_wlb;
input   [15:0] surfile_whb;
input   suwben;
input   suedff_cp;
input   sudwff_cp;
input   [1:0] suimmlsmux;
input   sureinstff_cp;
input   [3:0] suimmmux;
input   [4:0] suvulsoffsetmux;
input   [5:0] surdbmux;
input   surebff_cp;
input   suloaden;
input   sudrivels;
input   [4:0] surdamux;
input   sureaff_cp;
output  suonesdet_z;
input   sushift_s;
input   [2:0] sushbmux;
input   [3:0] sushamux;
input   suslten;
input   sushen;
input   sualuen;
output  sualu_ovr;
output  sualu_cout;
input   sualu_cin;
input   [4:0] sualu;
input   [1:0] sualuamux;
input   [1:0] sualubmux;
input   [15:0] inst_data;
input   [23:0] link_pc_delay_pc;
output  [11:0] branch_or_addr;
inout   [31:0] ls_data;
output  [31:31] suexbsign;
output  [4:0] sushvamt;
output  [31:31] suexasign;
input   [0:0] susltlt;
output  [31:31] sualumsb;
input   [31:0] shiftamt;

// 3 Feedthrough Outputs:
output   [0:0] suonesdetz_bot;
output   [0:0] sualucoutl_bot;
output   [0:0] sualuovr_bot;

wire    [31:0] ls_offset;
wire    [31:0] b15;
wire    [31:0] b16;
wire    [31:0] b17;
wire    [31:0] imm_data;
wire    [31:0] b23;
wire    [31:0] rt;
wire    [31:0] ex_data;
wire    [31:0] df_data;
wire    [31:0] wb_data;
wire    [31:0] eximmdata;
wire    [31:0] b31;
wire    [31:0] rdbsrc;
wire    [31:0] rs;
wire    [31:0] b38;
wire    [31:0] b40;
wire    [31:0] shbsrc;
wire    [31:0] shasrc;
wire    [31:0] shift_out;
wire    [31:0] aluasrc;
wire    [31:0] alubsrc;
wire    [31:0] b54;
wire   [0:0] b_suonesdetz;
wire   [0:0] b_sualucoutl;
wire   [0:0] b_sualuovr;

// 3 Feedthrough Wires:
wire   [0:0] suonesdetz_top;
wire   [0:0] sualucoutl_top;
wire   [0:0] sualuovr_top;

// 3 Hand-made Connections:
  assign b_suonesdetz = suonesdet_z;
  assign b_sualucoutl = sualu_ovr;
  assign b_sualuovr = sualu_cout;

  assign branch_or_addr[11:0] = b38[11:0];
  assign suexbsign[31:31] = b15[31:31];
  assign sushvamt[4:0] = b16[4:0];
  assign suexasign[31:31] = b17[31:31];
  assign sualumsb[31:31] = b38[31:31];
  assign suonesdetz_top[0:0] = b_suonesdetz[0:0];
  assign suonesdetz_bot[0:0] = b_suonesdetz[0:0];
  assign sualucoutl_top[0:0] = b_sualucoutl[0:0];
  assign sualucoutl_bot[0:0] = b_sualucoutl[0:0];
  assign sualuovr_top[0:0] = b_sualuovr[0:0];
  assign sualuovr_bot[0:0] = b_sualuovr[0:0];

  dprgf011h  suRFile_i(
		.d(wb_data[31:0]),
		.a(rs[31:0]),
		.b(rt[31:0]),
		.INST_RBL(surfile_rbl[15:0]),
		.INST_RBH(surfile_rbh[15:0]),
		.INST_RAL(surfile_ral[15:0]),
		.INST_RAH(surfile_rah[15:0]),
		.INST_RBLB(surfile_rblb[15:0]),
		.INST_RBHB(surfile_rbhb[15:0]),
		.INST_RALB(surfile_ralb[15:0]),
		.INST_RAHB(surfile_rahb[15:0]),
		.INST_WL(surfile_wl[15:0]),
		.INST_WH(surfile_wh[15:0]),
		.INST_WLB(surfile_wlb[15:0]),
		.INST_WHB(surfile_whb[15:0]));

  dptsb1021 #(32, 1, 0)  suWbEn_i(
		.I(b54[31:0]),
		.Z(wb_data[31:0]),
		.INST(suwben));

  dpdff0101 #(32, 1, 0)  suEdFF_i(
		.D(ex_data[31:0]),
		.Q(df_data[31:0]),
		.INST_CP(suedff_cp));

  dpdff0101 #(32, 1, 0)  suDwFF_i(
		.D(df_data[31:0]),
		.Q(b54[31:0]),
		.INST_CP(sudwff_cp));

  dpmux2021 #(32, 1, 0)  suImmLsMux_i(
		.Z(b31[31:0]),
		.I1(ls_offset[31:0]),
		.I0(imm_data[31:0]),
		.INST(suimmlsmux[1:0]));

  dpdff0101 #(32, 1, 0)  suREinstFF_i(
		.D(b31[31:0]),
		.Q(eximmdata[31:0]),
		.INST_CP(sureinstff_cp));

  dpmux4041 #(32, 1, 0)  suImmMux_i(
		.Z(imm_data[31:0]),
		.I0({16'd0, inst_data[15:0]}),
		.I1({inst_data[15], inst_data[15], inst_data[15], inst_data[15],
                      inst_data[15], inst_data[15], inst_data[15],
                      inst_data[15], inst_data[15], inst_data[15],
                      inst_data[15], inst_data[15], inst_data[15],
                      inst_data[15], inst_data[15], inst_data[15],
                      inst_data[15:0]}),
		.I2({inst_data[15:0], 16'd0}),
		.I3({inst_data[15], inst_data[15], inst_data[15], inst_data[15],
                      inst_data[15], inst_data[15], inst_data[15],
                      inst_data[15], inst_data[15], inst_data[15],
                      inst_data[15], inst_data[15], inst_data[15],
                      inst_data[15], inst_data[15:0], 2'd0}),
		.INST(suimmmux[3:0]));

  dpmux5051 #(32, 1, 0)  suVuLsOffsetMux_i(
		.Z(ls_offset[31:0]),
		.I0({inst_data[6], inst_data[6], inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6:0]}),
		.I1({inst_data[6], inst_data[6], inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6:0], 1'b0}),
		.I2({inst_data[6], inst_data[6], inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6:0], 2'd0}),
		.I3({inst_data[6], inst_data[6], inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6:0],
                      3'd0}),
		.I4({inst_data[6], inst_data[6], inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6], inst_data[6],
                      inst_data[6], inst_data[6:0], 4'd0}),
		.INST(suvulsoffsetmux[4:0]));

  dpmux6061 #(32, 1, 0)  suRdBMux_i(
		.Z(rdbsrc[31:0]),
		.I0(rt[31:0]),
		.I1(ex_data[31:0]),
		.I2(df_data[31:0]),
		.I3(wb_data[31:0]),
		.I4(imm_data[31:0]),
		.I5(32'd0),
		.INST(surdbmux[5:0]));

  dpdff0101 #(32, 1, 0)  suReBFF_i(
		.D(rdbsrc[31:0]),
		.Q(b15[31:0]),
		.INST_CP(surebff_cp));

  dptsb1023 #(32, 1, 0)  suLoadEn_i(
		.I(ls_data[31:0]),
		.Z(wb_data[31:0]),
		.INST(suloaden));

  dptsb1023 #(32, 1, 0)  suDriveLS_i(
		.I(b15[31:0]),
		.Z(ls_data[31:0]),
		.INST(sudrivels));

  dpmux5051 #(32, 1, 0)  suRdAMux_i(
		.Z(b16[31:0]),
		.I0(rs[31:0]),
		.I1(ex_data[31:0]),
		.I2(df_data[31:0]),
		.I3(wb_data[31:0]),
		.I4(32'd0),
		.INST(surdamux[4:0]));

  dpdff0101 #(32, 1, 0)  suReAFF_i(
		.D(b16[31:0]),
		.Q(b17[31:0]),
		.INST_CP(sureaff_cp));

  dp1dt001s #(32, 2, 0)  suOnesDet_i(
		.A(b40[31:0]),
		.INST_Z(suonesdet_z));

  dpbsh004h #(32, 32, 3, 0)  suShift_i(
		.A(shasrc[31:0]),
		.B(shbsrc[31:0]),
		.Z(shift_out[31:0]),
		.SEL(shiftamt[31:0]),
		.INST_S(sushift_s));

  dpmux3031 #(32, 1, 0)  suShBMux_i(
		.Z(shbsrc[31:0]),
		.I0({1'b0, b15[31:1]}),
		.I1(32'd0),
		.I2({32{1'b1}}),
		.INST(sushbmux[2:0]));

  dpxnr0021 #(32, 1, 0)  suEq_i(
		.A1(b17[31:0]),
		.A2(b15[31:0]),
		.ZN(b40[31:0]));

  dpmux4041 #(32, 1, 0)  suShAMux_i(
		.Z(shasrc[31:0]),
		.I0(b17[31:0]),
		.I1({b15[0], 31'd0}),
		.I2(b15[31:0]),
		.I3({8'd0, link_pc_delay_pc[23:0]}),
		.INST(sushamux[3:0]));

  dptsb1021 #(32, 1, 0)  suSltEn_i(
		.I({31'd0, susltlt[0]}),
		.Z(ex_data[31:0]),
		.INST(suslten));

  dptsb1021 #(32, 1, 0)  suShEn_i(
		.I(shift_out[31:0]),
		.Z(ex_data[31:0]),
		.INST(sushen));

  dprpt0010 #(32, 0)  suExRpt_i(
		.I(ex_data[31:0]));

  dptsb1021 #(32, 1, 0)  suAluEn_i(
		.I(b38[31:0]),
		.Z(ex_data[31:0]),
		.INST(sualuen));

  dpalu001s #(32, 4, 0)  suAlu_i(
		.A(aluasrc[31:0]),
		.B(alubsrc[31:0]),
		.SO(b38[31:0]),
		.INST_OVR(sualu_ovr),
		.INST_COUT(sualu_cout),
		.INST_CIN(sualu_cin),
		.INST(sualu[4:0]));

  dpmux2021 #(32, 1, 0)  suAluAMux_i(
		.Z(aluasrc[31:0]),
		.I1({8'd0, link_pc_delay_pc[23:0]}),
		.I0(b17[31:0]),
		.INST(sualuamux[1:0]));

  dpmux2021 #(32, 1, 0)  suAluBMux_i(
		.Z(alubsrc[31:0]),
		.I1(eximmdata[31:0]),
		.I0(b15[31:0]),
		.INST(sualubmux[1:0]));

  dprpt0010 #(32, 0)  suWbRpt_i(
		.I(wb_data[31:0]));

endmodule
