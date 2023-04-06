a4 1
// this block is a separate synthesis block;
d13 2
a14 2
	v_clk, v_rst_l,
	v_me, v_addr, v_in, v_we, v_out, v_recall, v_store,
d19 1
a19 1
	input v_rst_l;			// reset input;
d22 1
a22 1
	input [5:0] v_addr;		// sram address;
a24 2
	input v_recall;			// recall controls;
	input v_store;			// store controls;
a40 16

	// for now, recall happens on rising edge;

	always @(posedge v_recall)
	begin
		$display("%t: %M: recall", $time);
		$readmemh("tests/v2.dat", v2sram);
	end

	// for now, store happens on rising edge;

	always @(posedge v_store)
	begin
		$display("%t: %M: store", $time);
		$writememh("tests/v2.dat", v2sram);
	end
