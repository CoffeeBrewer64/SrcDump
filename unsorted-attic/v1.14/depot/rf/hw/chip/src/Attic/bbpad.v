d228 1
a228 1
	wire pllx2_atbio;			// test mode;
d233 4
a236 4
	assign pllx2_n = 4'b0111;		// vco / 8 = 31.25...50Mhz;
	assign pllx2_pa = 4'b0001;		// clk A = vco / 2;
	assign pllx2_pb = 4'b0001;
	assign pllx2_pc = 4'b0001;
d241 1
a241 1
	assign pllx2_atbio = 1'b0;
d247 1
a247 1
		.CLKI(sysclk),
d249 16
a264 4
		.N(pllx2_n),
		.PA(pllx2_pa),
		.PB(pllx2_pb),
		.PC(pllx2_pc),
d273 1
a273 1
		.ATBIO(pllx2_atbio),
d276 29
a304 2
		.TBI(22'd0),
		.TBO()
