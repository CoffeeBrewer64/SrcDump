d1 1
a1 1
// $Id: vsim_mon.v,v 1.1 2002/03/28 00:26:14 berndt Exp $
d25 1
a25 1
		$display("  +mbus_mon	      - log mbus activity");
a31 2
		$display("  +load_rom	      - load cartridge ROM from rom_?.data");
		$display("  +load_rdram	      - load Rambus DRAM from rdram_reorderd_?.data"); //XXX
d46 12
a57 12
               //$dumpvars(0, vsim.bcp.if_logic);
               //$dumpvars(0, vsim.bcp.vclk_driver_0);
               $dumpvars(0, vsim.bcp.if_logic);
               //$dumpvars(0, vsim.bcp.ri);
               //$dumpvars(0, vsim.bcp.rsp_0_su );
               //$dumpvars(0, vsim.bcp.rsp_0_ls );
               //$dumpvars(0, vsim.bcp.rsp_0_io_logic );

               //$dumpvars(0, vsim.bcp.pi_0);
               //$dumpvars(0, vsim.bcp.rsp_0_io_logic );
               //$dumpvars(0, vsim.bcp.vi_0);
               //$dumpvars(0, vsim.bcp.left_pads.rac_0);
d59 7
a65 7
               //$dumpvars(0, vsim.bcp.rdp_0_tc_logic );
               //$dumpvars(0, vsim.bcp.rdp_0_ms_grp );
               //$dumpvars(0, vsim.bcp.rdp_0_tf_logic );
               //$dumpvars(0, vsim.bcp.rdp_0_tm_grp );
               //$dumpvars(0, vsim.bcp.rdp_0_cs_ew_cv );
               //$dumpvars(0, vsim.bcp.rdp_0_bl_logic );
               //$dumpvars(0, vsim.bcp.rdp_0_cc_logic );
d68 1
a68 1
           $dumpvars(1, vsim.bcp);
d71 1
a71 1
	if ($test$plusargs("rcp_dump")) $dumpvars(0, vsim.bcp);
d73 1
a73 1
	if ($test$plusargs("rcp_top_dump")) $dumpvars(1, vsim.bcp);
d76 2
a77 2
		$dumpvars(3, vsim.bcp.vi_0);
		//$dumpvars(0, vsim.bcp.vi_0.vi_grp.vi_logic.clk_blk);
d82 2
a83 2
		$dumpvars(1, vsim.bcp);
		$dumpvars(0, vsim.bcp.\rdp_0/memspan );	
d86 2
a87 2
		$dumpvars(1, vsim.bcp);
		$dumpvars(0, vsim.bcp.\rdp_0/tc_logic );	
d91 1
a91 1
	if ($test$plusargs("tst_dump")) $dumpvars(0, vsim.bcp.if_logic);
d99 10
a108 10
		$dumpvars(1, vsim.bcp);
		$dumpvars(0, vsim.bcp.rsp_0);
		$dumpvars(0, vsim.bcp.rdp_0);
		$dumpvars(0, vsim.bcp.mi_0);
		$dumpvars(0, vsim.bcp.pi_0);
		$dumpvars(0, vsim.bcp.si);
		$dumpvars(0, vsim.bcp.ai_0);
		$dumpvars(0, vsim.bcp.vi_0);
		$dumpvars(0, vsim.bcp.arb_0);
		$dumpvars(0, vsim.bcp.ri);
d113 12
a124 18
	if ($test$plusargs("rcp_top_dump")) $dumpvars(1, vsim.bcp);
	if ($test$plusargs("rcp_dump")) $dumpvars(0, vsim.bcp);
	if ($test$plusargs("rsp_dump")) $dumpvars(0, vsim.bcp.rsp_0);
	if ($test$plusargs("rdp_dump")) $dumpvars(0, vsim.bcp.rdp_0);
	if ($test$plusargs("tc_dump")) $dumpvars(0, vsim.bcp.rdp_0.tc);
	if ($test$plusargs("mi_dump")) $dumpvars(0, vsim.bcp.mi_0);
	if ($test$plusargs("pi_dump")) $dumpvars(0, vsim.bcp.pi_0);
	if ($test$plusargs("si_dump")) $dumpvars(0, vsim.bcp.si);
	if ($test$plusargs("ai_dump")) $dumpvars(0, vsim.bcp.ai_0);
	if ($test$plusargs("vi_dump")) $dumpvars(3, vsim.bcp.vi_0);
	if ($test$plusargs("arb_dump")) $dumpvars(0, vsim.bcp.arb_0);
	if ($test$plusargs("ri_dump")) $dumpvars(0, vsim.bcp.ri);
`endif
`ifdef ROM_0_PRESENT
	if ($test$plusargs("rom_dump")) $dumpvars(0, vsim.rom_0);
`endif
`ifdef ROM_1_PRESENT
	if ($test$plusargs("rom_dump")) $dumpvars(0, vsim.rom_1);
d129 1
a129 1
	if ($test$plusargs("ms_dump")) $dumpvars(0, vsim.bcp.rdp_0.ms);
d137 1
a137 1
// always @(vsim.bcp.syn_clk) $display($time,, vsim.bcp.syn_clk);
d152 1
a152 1
always @(posedge vsim.bcp.vi_0.vclk)
d154 1
a154 1
    if ($output_vi(vsim.bcp.vi_0.vbus_data, vsim.bcp.vi_0.vbus_sync) == -1)
d167 1
a167 1
		force vsim.bcp.refresh_strobe = LOW;
d170 1
a170 1
			force vsim.bcp.refresh_strobe = HIGH;
d172 1
a172 1
			force vsim.bcp.refresh_strobe = LOW;
d185 2
a186 2
`define  DMEM_L   vsim.bcp.rsp_0_dmemx2_dmemLow
`define  DMEM_H   vsim.bcp.rsp_0_dmemx2_dmemHigh
d190 1
a190 1
		vsim.bcp.rsp_0_dmemx2_dmemHigh.ram_prim7, 0);
d192 1
a192 1
		vsim.bcp.rsp_0_dmemx2_dmemHigh.ram_prim6 , 0);
d194 1
a194 1
		vsim.bcp.rsp_0_dmemx2_dmemHigh.ram_prim5 , 0);
d196 1
a196 1
		vsim.bcp.rsp_0_dmemx2_dmemHigh.ram_prim4 , 0);
d198 1
a198 1
		vsim.bcp.rsp_0_dmemx2_dmemHigh.ram_prim3 , 0);
d200 1
a200 1
		vsim.bcp.rsp_0_dmemx2_dmemHigh.ram_prim2 , 0);
d202 1
a202 1
		vsim.bcp.rsp_0_dmemx2_dmemHigh.ram_prim1 , 0);
d204 1
a204 1
		vsim.bcp.rsp_0_dmemx2_dmemHigh.ram_prim0 , 0);
d206 1
a206 1
		vsim.bcp.rsp_0_dmemx2_dmemLow.ram_prim7 , 0);
d208 1
a208 1
		vsim.bcp.rsp_0_dmemx2_dmemLow.ram_prim6 , 0);
d210 1
a210 1
		vsim.bcp.rsp_0_dmemx2_dmemLow.ram_prim5 , 0);
d212 1
a212 1
		vsim.bcp.rsp_0_dmemx2_dmemLow.ram_prim4 , 0);
d214 1
a214 1
		vsim.bcp.rsp_0_dmemx2_dmemLow.ram_prim3 , 0);
d216 1
a216 1
		vsim.bcp.rsp_0_dmemx2_dmemLow.ram_prim2 , 0);
d218 1
a218 1
		vsim.bcp.rsp_0_dmemx2_dmemLow.ram_prim1 , 0);
d220 1
a220 1
		vsim.bcp.rsp_0_dmemx2_dmemLow.ram_prim0 , 0);
d224 1
a224 1
			vsim.bcp.rsp_0.dmemx2.dmemHigh.ram_prim7, 0);
d226 1
a226 1
			vsim.bcp.rsp_0.dmemx2.dmemHigh.ram_prim6, 0);
d228 1
a228 1
			vsim.bcp.rsp_0.dmemx2.dmemHigh.ram_prim5, 0);
d230 1
a230 1
			vsim.bcp.rsp_0.dmemx2.dmemHigh.ram_prim4, 0);
d232 1
a232 1
			vsim.bcp.rsp_0.dmemx2.dmemHigh.ram_prim3, 0);
d234 1
a234 1
			vsim.bcp.rsp_0.dmemx2.dmemHigh.ram_prim2, 0);
d236 1
a236 1
			vsim.bcp.rsp_0.dmemx2.dmemHigh.ram_prim1, 0);
d238 1
a238 1
			vsim.bcp.rsp_0.dmemx2.dmemHigh.ram_prim0, 0);
d240 1
a240 1
			vsim.bcp.rsp_0.dmemx2.dmemLow.ram_prim7, 0);
d242 1
a242 1
			vsim.bcp.rsp_0.dmemx2.dmemLow.ram_prim6, 0);
d244 1
a244 1
			vsim.bcp.rsp_0.dmemx2.dmemLow.ram_prim5, 0);
d246 1
a246 1
			vsim.bcp.rsp_0.dmemx2.dmemLow.ram_prim4, 0);
d248 1
a248 1
			vsim.bcp.rsp_0.dmemx2.dmemLow.ram_prim3, 0);
d250 1
a250 1
			vsim.bcp.rsp_0.dmemx2.dmemLow.ram_prim2, 0);
d252 1
a252 1
			vsim.bcp.rsp_0.dmemx2.dmemLow.ram_prim1, 0);
d254 1
a254 1
			vsim.bcp.rsp_0.dmemx2.dmemLow.ram_prim0, 0);
d271 1
a271 1
			vsim.bcp.rsp_0_imem.ram_prim , 0);
d274 1
a274 1
			vsim.bcp.rsp_0.imem.ram_prim, 0);
