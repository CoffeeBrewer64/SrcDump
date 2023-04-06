// bb_v0_wrap.v v1 Frank Berndt
// bb wrapper around virage modules;
// :set tabstop=4

// this block is a separate synthesis block;
// output enables of virage sram are not used;
// read data come out of novea and hit ff in mi;

// serial mode is not implemented;

`timescale 1ns/1ns

module bb_v0_wrap (
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
		$display("%M: behavioral virage macro, 16x32");

	// behavioral code;

	reg [31:0] v0sram [0:15];	// 512bit sram;

	initial
		$readmemh("tests/v0.dat", v0sram);

	// sram access;

	reg [3:0] v0_addr;
	reg [31:0] v0_wdata;
	reg v0_me;
	reg v0_we;

	always @(posedge v_clk)
	begin
		v0_me <= v_me;
		v0_we <= v_we;
		if(v_me) begin
			v0_addr <= v_addr;
			v0_wdata <= v_in;
		end
	end

	// write at falling edge to simulate t[co];

	always @(negedge v_clk)
	begin
		if(v0_me & v0_we)
			v0sram[v0_addr] <= v0_wdata;
	end

	// read is enabled by v_me;

	assign v_out = v0_me? v0sram[v0_addr] : 32'bx;

endmodule

