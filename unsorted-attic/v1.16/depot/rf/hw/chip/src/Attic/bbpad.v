a50 1
	pad_mcs, mcs,
d163 4
a166 4
	output	[1:0]	pad_mcke;
	input	[1:0]	mcke;
	output	[13:0]	pad_maddr;
	input	[13:0]	maddr;
d169 2
a170 2
	input	[7:0]	mdin_ena;
	input	[7:0]	mdout_ena;
a173 2
	output	[1:0]	pad_mcs;
	input	[1:0]	mcs;
d182 1
a182 1
	inout		pad_mdqs;
a326 1
	reg	[1:0]	emcs;
d332 1
a332 1
	reg	[1:0]	emcke;
a334 1
		emcs  <=  mcs;
a342 1
	reg	[1:0]	pad_mcs;
d348 2
a349 2
	reg	[13:0]	pad_maddr;
	reg	[1:0]	pad_mcke;
a353 1
		pad_mcs  <= ~emcs;
d367 1
a367 1
		Write <= mdout_ena[0];
d375 1
a375 1
	wire	[4:0]	oe = {5{D4Write | D8Write}};
d379 1
a379 3
	// model off-chip strobe delay (output to ddr)

	assign pad_mdqs = oe[0] ? strobe_out : 1'bz;
d386 1
a386 1
	wire	[3:0]	nxt_mout_01 = mdout_ena[0] ? mdqm[7:4] 
d389 1
a389 1
	wire	[3:0]	nxt_mout_23 = mdout_ena[0] ? mdqm[3:0] 
d411 2
a412 2
	wire	[31:0]	nxt_dout_01 = mdout_ena[0] ? mdout[63:32]
						   : dout_01;
d414 2
a415 2
	wire	[31:0]	nxt_dout_23 = mdout_ena[0] ? mdout[31:0]
						   : dout_23;
d432 1
a432 4
	assign	pad_mdata[31:24] = oe[1] ? data_out[31:24] : {8{1'bz}};
	assign	pad_mdata[23:16] = oe[2] ? data_out[23:16] : {8{1'bz}};
	assign	pad_mdata[15:8 ] = oe[3] ? data_out[15:8 ] : {8{1'bz}};
	assign	pad_mdata[ 7:0 ] = oe[4] ? data_out[ 7:0 ] : {8{1'bz}};
d438 1
a438 3
	// model off-chip strobe delay (input from ddr)

	wire	strobe_in   =  pad_mdqs;
d440 1
a440 1
	wire	strobe_in_b = ~pad_mdqs;
d457 5
a461 1
		mdin[63:32] <= nxt_mdin[63:32];
d464 1
a464 1
		mdin[31:0] <= nxt_mdin[31:0];
