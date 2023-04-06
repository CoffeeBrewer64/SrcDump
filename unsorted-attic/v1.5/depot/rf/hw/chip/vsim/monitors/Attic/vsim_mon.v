// $Id: vsim_mon.v,v 1.4 2002/07/26 17:03:32 whs Exp $

module vsim_mon(clock, reset_l);

`include "rcp.vh"
`include "define.vh"

input clock;
input reset_l;

reg [31:0] timelimit;
reg [31:0] cyclelimit;
reg [31:0] startdump;
reg [31:0] cycle_count;

initial begin
	if ($test$plusargs("help")) begin
		$display("general arguments include:");
		$display("  +help	      - log this message");
		$display("  +dump	      - generate a verilog dump file");
		$display("  +adac_mon	      - log audio dac activity");
		$display("  +cbuf_mon	      - log cbuf activity");
		$display("  +cbus_mon	      - log cbus activity");
		$display("  +cpu_mon	      - log cbus sysad activity");
		$display("  +xbus_mon	      - log xbus activity");
		$display("  +cart_mon	      - log cartridge activity");
		$display("  +mem_mon	      - log mem activity");
		$display("  +span_mon	      - log span activity");
		$display("  +spandata_mon     - log span data read/write activity");
		$display("  +cpu_mon	      - log cpu activity");
		$display("  +load_dmem	      - load SP DMEM from dmem_even.data & dmem_odd.data");
		$display("  +load_imem	      - load SP IMEM from imem.data");
		$display("  +load_pif	      - load PIF ROM from pif.data");
		$display("  +cyclelimit=<cyc> - limit simulation to no more than <cyc> cycles");
		$display("  +startdump=<cyc>  - turn dump on at cycle <cyc>");
		$display("  +enable_nmi	      - enable nmi generation from PIF");
		$display("  +vitab=file       - turn on dumping of video data for software monitor");
		$display("  +mmap_rdram=file  - load Rambus DRAM from memory mapped file.main and file.hidden"); //XXX
		$display("");
		#1 $finish;
		end
`ifdef GATE_LEVEL

	if ($test$plusargs("dump")) begin
               //$dumpvars(0, vsim.bb.bcp.if_logic);
               //$dumpvars(0, vsim.bb.bcp.vclk_driver_0);
               $dumpvars(0, vsim.bb.bcp.if_logic);
               //$dumpvars(0, vsim.bb.bcp.ri);
               //$dumpvars(0, vsim.bb.bcp.rsp_0_su );
               //$dumpvars(0, vsim.bb.bcp.rsp_0_ls );
               //$dumpvars(0, vsim.bb.bcp.rsp_0_io_logic );

               //$dumpvars(0, vsim.bb.bcp.pi);
               //$dumpvars(0, vsim.bb.bcp.rsp_0_io_logic );
               //$dumpvars(0, vsim.bb.bcp.vi);
               //$dumpvars(0, vsim.bb.bcp.left_pads.rac_0);
 
               //$dumpvars(0, vsim.bb.bcp.rdp_0_tc_logic );
               //$dumpvars(0, vsim.bb.bcp.rdp_0_ms_grp );
               //$dumpvars(0, vsim.bb.bcp.rdp_0_tf_logic );
               //$dumpvars(0, vsim.bb.bcp.rdp_0_tm_grp );
               //$dumpvars(0, vsim.bb.bcp.rdp_0_cs_ew_cv );
               //$dumpvars(0, vsim.bb.bcp.rdp_0_bl_logic );
               //$dumpvars(0, vsim.bb.bcp.rdp_0_cc_logic );
 
           $dumpvars(1, vsim);
           $dumpvars(1, vsim.bb.bcp);
	end
		 
	if ($test$plusargs("rcp_dump")) $dumpvars(0, vsim.bb.bcp);
	
	if ($test$plusargs("rcp_top_dump")) $dumpvars(1, vsim.bb.bcp);

	if ($test$plusargs("vi_dump")) begin
		$dumpvars(3, vsim.bb.bcp.vi);
		//$dumpvars(0, vsim.bb.bcp.vi.vi_grp.vi_logic.clk_blk);
	end

	/*
	if ($test$plusargs("ms_dump")) begin
		$dumpvars(1, vsim.bb.bcp);
		$dumpvars(0, vsim.bb.bcp.\rdp_0/memspan );	
	end
	if ($test$plusargs("tc_dump")) begin
		$dumpvars(1, vsim.bb.bcp);
		$dumpvars(0, vsim.bb.bcp.\rdp_0/tc_logic );	
	end
	*/

	if ($test$plusargs("tst_dump")) $dumpvars(0, vsim.bb.bcp.if_logic);



`else

	if ($test$plusargs("dump")) begin
		$dumpvars(1, vsim);
		$dumpvars(1, vsim.bb.bcp);
		$dumpvars(0, vsim.bb.bcp.rsp_0);
		$dumpvars(0, vsim.bb.bcp.rdp_0);
		$dumpvars(0, vsim.bb.bcp.mi);
		$dumpvars(0, vsim.bb.bcp.pi);
		$dumpvars(0, vsim.bb.bcp.si);
		$dumpvars(0, vsim.bb.bcp.ai);
		$dumpvars(0, vsim.bb.bcp.vi);
		$dumpvars(0, vsim.bb.bcp.arb_0);
		$dumpvars(0, vsim.bb.bcp.ri);
		end

	if ($test$plusargs("all_dump")) $dumpvars;
	if ($test$plusargs("vsim_top_dump")) $dumpvars(1, vsim);
	if ($test$plusargs("rcp_top_dump")) $dumpvars(1, vsim.bb.bcp);
	if ($test$plusargs("rcp_dump")) $dumpvars(0, vsim.bb.bcp);
	if ($test$plusargs("rsp_dump")) $dumpvars(0, vsim.bb.bcp.rsp_0);
	if ($test$plusargs("rdp_dump")) $dumpvars(0, vsim.bb.bcp.rdp_0);
	if ($test$plusargs("tc_dump")) $dumpvars(0, vsim.bb.bcp.rdp_0.tc);
	if ($test$plusargs("mi_dump")) $dumpvars(0, vsim.bb.bcp.mi);
	if ($test$plusargs("pi_dump")) $dumpvars(0, vsim.bb.bcp.pi);
	if ($test$plusargs("si_dump")) $dumpvars(0, vsim.bb.bcp.si);
	if ($test$plusargs("ai_dump")) $dumpvars(0, vsim.bb.bcp.ai);
	if ($test$plusargs("vi_dump")) $dumpvars(3, vsim.bb.bcp.vi);
	if ($test$plusargs("arb_dump")) $dumpvars(0, vsim.bb.bcp.arb_0);
	if ($test$plusargs("ri_dump")) $dumpvars(0, vsim.bb.bcp.ri);
`endif
`ifdef GATE_LEVEL
`else
`ifdef IPC_PRESENT
	if ($test$plusargs("ms_dump")) $dumpvars(0, vsim.bb.bcp.rdp_0.ms);
`endif
`endif

	if ($getnum$plusarg("timelimit=", timelimit) == 1) $set_timelimit(timelimit);
	end


// always @(vsim.bb.bcp.syn_clk) $display($time,, vsim.bb.bcp.syn_clk);

`ifdef RSP_PRESENT

initial begin
	if ($test$plusargs("load_dmem")) begin
		$display("Loading DMEM ........");
`ifdef GATE_LEVEL

//from rcpgate_rsp_regr.h
`define  DMEM_L   vsim.bb.bcp.rsp_0_dmemx2_dmemLow
`define  DMEM_H   vsim.bb.bcp.rsp_0_dmemx2_dmemHigh

// $display(" You want me to load DMEM ??? Do it yourself");
	        $readmemh("SpData/d_0.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemHigh.ram_prim7, 0);
	        $readmemh("SpData/d_1.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemHigh.ram_prim6 , 0);
	        $readmemh("SpData/d_2.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemHigh.ram_prim5 , 0);
	        $readmemh("SpData/d_3.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemHigh.ram_prim4 , 0);
	        $readmemh("SpData/d_4.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemHigh.ram_prim3 , 0);
	        $readmemh("SpData/d_5.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemHigh.ram_prim2 , 0);
	        $readmemh("SpData/d_6.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemHigh.ram_prim1 , 0);
	        $readmemh("SpData/d_7.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemHigh.ram_prim0 , 0);
	        $readmemh("SpData/d_8.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemLow.ram_prim7 , 0);
	        $readmemh("SpData/d_9.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemLow.ram_prim6 , 0);
	        $readmemh("SpData/d_a.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemLow.ram_prim5 , 0);
	        $readmemh("SpData/d_b.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemLow.ram_prim4 , 0);
	        $readmemh("SpData/d_c.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemLow.ram_prim3 , 0);
	        $readmemh("SpData/d_d.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemLow.ram_prim2 , 0);
	        $readmemh("SpData/d_e.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemLow.ram_prim1 , 0);
	        $readmemh("SpData/d_f.dhex", 
		vsim.bb.bcp.rsp_0_dmemx2_dmemLow.ram_prim0 , 0);

`else
	        $readmemh("SpData/d_0.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemHigh.ram_prim7, 0);
	        $readmemh("SpData/d_1.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemHigh.ram_prim6, 0);
	        $readmemh("SpData/d_2.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemHigh.ram_prim5, 0);
	        $readmemh("SpData/d_3.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemHigh.ram_prim4, 0);
	        $readmemh("SpData/d_4.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemHigh.ram_prim3, 0);
	        $readmemh("SpData/d_5.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemHigh.ram_prim2, 0);
	        $readmemh("SpData/d_6.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemHigh.ram_prim1, 0);
	        $readmemh("SpData/d_7.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemHigh.ram_prim0, 0);
	        $readmemh("SpData/d_8.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemLow.ram_prim7, 0);
	        $readmemh("SpData/d_9.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemLow.ram_prim6, 0);
	        $readmemh("SpData/d_a.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemLow.ram_prim5, 0);
	        $readmemh("SpData/d_b.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemLow.ram_prim4, 0);
	        $readmemh("SpData/d_c.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemLow.ram_prim3, 0);
	        $readmemh("SpData/d_d.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemLow.ram_prim2, 0);
	        $readmemh("SpData/d_e.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemLow.ram_prim1, 0);
	        $readmemh("SpData/d_f.dhex", 
			vsim.bb.bcp.rsp_0.dmemx2.dmemLow.ram_prim0, 0);
`endif
		end
	end

initial begin
	/* wait for reset to go away */
	wait(`SYSTEM_READY);
	/*
	 * wait additional cycles just to be sure.
	 * config_mem should easily use up these cycles anyway
	 */
	repeat (4) @(posedge clock);
	if ($test$plusargs("load_imem")) begin
		$display($time," Loading IMEM ........");
`ifdef GATE_LEVEL
		$readmemh("SpData/idata.ihex", 
			vsim.bb.bcp.rsp_0_imem.ram_prim , 0);
`else
		$readmemh("SpData/idata.ihex", 
			vsim.bb.bcp.rsp_0.imem.ram_prim, 0);
`endif
		end
	end
`endif

initial begin

        cycle_count = 0;
	cyclelimit = 32'hfffffff0;
	startdump = 32'hfffffff0;

	if ($getnum$plusarg("cyclelimit=", cyclelimit) == 1)
		begin
		end

	if ($getnum$plusarg("startdump=", startdump) == 1)
	    begin
		$dumpoff;
		$display("Dump=OFF (dump will be turned on at cycle 0x%h or %d)",
			 startdump, startdump);
	    end

	forever @(posedge clock) begin
	    if (cycle_count === cyclelimit) 
		$finish;
	    else if (cycle_count == startdump) begin
		$dumpon;
		$display("Dump=ON");
	        end
	    cycle_count = cycle_count + 32'h1;
	end
end

endmodule
