// bb_v2_wrap.v v1 Frank Berndt
// bb wrapper around virage modules;
// :set tabstop=4

// output enables of virage sram are not used;
// read data come out of novea and hit ff in mi;

// serial mode is not implemented;

`timescale 1ns/1ns

module bb_v2_wrap (
	v_clk, v_time,
	v_me, v_addr, v_in, v_we, v_out,
);
	// operational ports;

	input v_clk;			// sram clock;
	input v_time;			// time base, 1us;
	input v_me;				// sram enable;
	input v_we;				// sram write enable;
	input [15:2] v_addr;	// sram address;
	input [31:0] v_in;		// sram write data;
	output [31:0] v_out;	// sram read data;

	// print behavioral message;

	initial
		$display("%M: behavioral virage macro, 64x32");

	// test bus ports;
	// XXX TBD;


	// behavioral code;

	reg [31:0] v2sram [0:63];	// 2kbits sram;

	initial
		$readmemh("tests/v2.dat", v2sram);

	// sram access;

	reg [5:0] v2_addr;
	reg [31:0] v2_wdata;
	reg v2_me;
	reg v2_we;

	always @(posedge v_clk)
	begin
		v2_me <= v_me;
		v2_we <= v_we;
		if(v_me) begin
			v2_addr <= v_addr;
			v2_wdata <= v_in;
		end
	end

	// write at falling edge to simulate t[co];

	always @(negedge v_clk)
	begin
		if(v2_me & v2_we)
			v2sram[v2_addr] <= v2_wdata;
	end

	// read is enabled by v_me;

	assign v_out = v2_me? v2sram[v2_addr] : 32'bx;

endmodule

