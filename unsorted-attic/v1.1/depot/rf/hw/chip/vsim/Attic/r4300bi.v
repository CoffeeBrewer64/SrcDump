d470 3
a472 1
// include various tasks;
d476 5
a480 84
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

	// wait for deassertion of reset;
	// run all the +option tests;
	// give some extra clocks before finishing;

	initial
	begin
//XXX test that test at all;
		test_selected <= 0;

		@(posedge ready);
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

		repeat(64) @(posedge sysclk);
		$finish;
	end
