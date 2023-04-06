// vr4300 behavioral bus model;
// used to simulate SYSAD bus requests;

module r4300 (
	sysclk, reset_l,
	p_valid_l, e_valid_l, e_ok_l,
	sys_ad, sys_cmd,
	int_l, nmi_l,
);

`include "rcp.vh"
`include "cpu.vh"
`include "define.vh"
`include "jctrl.vh"

	// cpu bus signals;
	// no sysad arbitration is used in the design;

	input sysclk;			// sysad clock;
	input reset_l;
	input e_valid_l;		// external data valid;
	input e_ok_l;			// external agent ready;
	input int_l;
	input nmi_l;
	output p_valid_l;		// processor data valid;
	inout [31:0] sys_ad;		// bidir sysad bus;
	inout [4:0] sys_cmd;		// bidir syscmd bus;

	// internal variables;

	reg e_valid;
	reg e_ok;
	reg int;
	reg p_valid;
	reg [31:0] sys_ad_in, sys_ad_out;
	reg [4:0] sys_cmd_in, sys_cmd_out;
	reg sys_ad_enable;
	reg [31:0] data [0:7];
	reg test_selected;
	integer tests_run;
	integer tests_failed;

	// SYSAD output enables;

	assign sys_ad = sys_ad_enable? sys_ad_out : 'bz;
	assign sys_cmd = sys_ad_enable? sys_cmd_out : 'bz;
	assign p_valid_l = ~p_valid;

	// monitor cpu activity;

	reg cpu_mon;

	initial
	begin
		$display("%M: vr4300 behavioral bus model");
		$timeformat(-9, 2, "ns", 12);
		cpu_mon = $test$plusargs("cpu_mon");
	end

	// register all cpu inputs;

	always @(posedge sysclk)
	begin
		e_valid <= ~e_valid_l;
		e_ok <= ~e_ok_l;
		int <= ~int_l;
		sys_ad_in <= sys_ad;
		sys_cmd_in <= sys_cmd;
	end

	// reset is asynchronous;

	always @(reset_l)
	begin
		if(!reset_l) begin
			assign p_valid = LOW;
			assign sys_ad_enable = HIGH;
			$display("%t cpu: reset asserted", $time);
		end else begin
			deassign p_valid;
			deassign sys_ad_enable;
			$display("%t cpu: reset deasserted", $time);
		end
	end

	// detect and log NMIs;

	always @(posedge sysclk)
	begin
		if(!nmi_l)
			$display("%t cpu: NMI detected", $time);
	end

	// print cpu test +options;

	initial
	begin
		if ($test$plusargs("help")) begin
			$display("cpu test +options:");
			$display("  +test_cpu_mi_version");
			$display("  +test_cpu_dp_counters");
			$display("  +test_cpu_pbus_reg");
			$display("  +test_cpu_pbus_io");
			$display("  +test_cpu_pbus_dma");
			$display("  +test_cpu_dmem");
			$display("  +test_cpu_imem");
			$display("  +test_cpu_rsp_dma");
			$display("  +test_cpu_sp_reg");
			$display("  +test_cpu_sp_dma_copy");
			$display("  +test_cpu_sp_dual");
			$display("  +test_cpu_cbuf_dma");
			$display("  +test_cpu_cbuf_dmem");
			$display("  +test_cpu_subblock");
			$display("  +test_cpu_byte_write");
			$display("  +test_cpu_external");
			$display("  +test_cpu_data_file");
			$display("  +test_cpu_vi_test");
			$display("  +test_cpu_ai_test");
			$display("  +test_cpu_span_buf_test");

			$display("  +test_si");
			$display("");
			#1 $finish;
		end
	end

// include various tasks;

`include "tasks/cpu_busif.v"
`include "tasks/mem_tasks.v"

`include "tests/si_tests.v"

`include "io_tasks.v"
`include "audio_tasks.v"
`include "video_tasks.v"
`include "rspdma_tasks.v"
`include "rdp_tasks.v"
`include "sp_tasks.v"

`ifdef IPC_PRESENT
`include "ipc_tasks.v"
`endif

	// wait for deassertion of reset;
	// run all the +option tests;
	// give some extra clocks before finishing;

	initial
	begin
		tests_run = 0;
		tests_failed = 0;
//XXX test that test at all;
		test_selected <= LOW;

		wait(`SYSTEM_READY);
		@(posedge sysclk);

		if($test$plusargs("test_cpu_mi_version")) mi_version;
		if($test$plusargs("test_cpu_dp_counters")) dp_counters;
		if($test$plusargs("test_cpu_pbus_reg")) pbus_reg;
		if($test$plusargs("test_cpu_pbus_io")) pbus_io;
		if($test$plusargs("test_cpu_pbus_dma")) pbus_dma;
		if($test$plusargs("test_cpu_dmem")) sp_dmem;
		if($test$plusargs("test_cpu_imem")) sp_imem;
		if($test$plusargs("test_cpu_rsp_dma")) rsp_dma;
		if($test$plusargs("test_cpu_sp_reg")) sp_reg;
		if($test$plusargs("test_cpu_sp_dma_copy")) sp_dma_copy;
		if($test$plusargs("test_cpu_sp_dual")) sp_dual;
		if($test$plusargs("test_cpu_cbuf_dma")) cbuf_dma;
		if($test$plusargs("test_cpu_cbuf_dmem")) cbuf_dmem;
		if($test$plusargs("test_cpu_subblock")) test_subblock;
		if($test$plusargs("test_cpu_byte_write")) test_byte_write;
		if($test$plusargs("test_cpu_external")) external;
		if($test$plusargs("test_cpu_data_file")) data_file;
		if($test$plusargs("test_cpu_vi_test")) vi_test;
		if($test$plusargs("test_cpu_ai_test")) ai_test;
		if($test$plusargs("test_cpu_span_buf_test")) span_buf_test;

		if($test$plusargs("test_si")) test_si;

		$display("Result: %4d tests run, %4d failed\n", tests_run, tests_failed);

		repeat(64) @(posedge sysclk);
		$finish;
	end

endmodule
