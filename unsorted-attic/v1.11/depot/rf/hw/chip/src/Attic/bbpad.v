a7 1
	pad_clk, sysclk, memclk,
d9 3
a60 3
	input pad_clk;				// input clock;
	output sysclk;				// system clock;
	output memclk;				// memory clock;
d64 9
d77 1
a77 1
	output vclock;				// generated video clock;
a178 1
	assign sysclk = pad_clk;
d180 3
a182 10

	// video/audio clock generator;
	// XXX instantiate PLL here;

	reg vclock;				// internally generated video clock;

	initial
		vclock = 0;
	always
		#10 vclock = ~vclock;
d363 12
d377 1
d382 1
a382 1
	always @(posedge vclock or negedge reset_l)
a391 2

	// XXX instantiate real io cells;
