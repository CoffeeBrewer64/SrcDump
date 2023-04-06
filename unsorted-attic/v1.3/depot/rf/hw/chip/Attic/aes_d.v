// aes_dummy.v v1 Frank Berndt
// aes dumy for export limitations;

module aes_d (
	clk, rstn,
	en, go, ksize, din, key, din_req,
	dout, dout_vld
);
	input clk, rstn;
	input en, go;
	input [1:0] ksize;
	input [31:0] din, key;
	output din_req;
	output [31:0] dout;
	output dout_vld;

	// use all signals so they don't get optimized out;

	reg [31:0] dout;
	reg [1:0] key_size;
	reg din_req;
	reg dout_vld;

	always @(clk)
	begin
		if(en)
			dout <= din ^ key;
		key_size <= ksize;
		din_req <= en & rstn;
		dout_vld <= go & rstn;
	end

endmodule
