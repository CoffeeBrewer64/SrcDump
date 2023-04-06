d14 2
a15 2
	v_clk, v_rst_l,
	v_me, v_addr, v_in, v_we, v_out, v_recall, v_store,
d20 1
a20 1
	input v_rst_l;			// reset input;
d23 1
a23 1
	input [3:0] v_addr;		// sram address;
a25 2
	input v_recall;			// recall controls;
	input v_store;			// store controls;
a31 4
	// test bus ports;
	// XXX TBD;


a37 16

	// for now, recall happens on rising edge;

	always @(posedge v_recall)
	begin
		$display("%t: %M: recall", $time);
		$readmemh("tests/v0.dat", v0sram);
	end

	// for now, store happens on rising edge;

	always @(posedge v_store)
	begin
		$display("%t: %M: store", $time);
		$writememh("tests/v0.dat", v0sram);
	end
