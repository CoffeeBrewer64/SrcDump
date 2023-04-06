d16 1
d38 1
d56 2
d67 1
a67 1
	.H01		(~memclk),
a73 1
//	assign	pad_mdqs = pad_moe ? {4{strobe_out}} : 1'bz;
d76 30
a105 3
	wire	strobe_in_b = ~strobe_in;
	wire	strobe_out;
	wire	pad_moe;
d108 2
a109 2
	.H01		(strobe_out),
	.H02		(pad_moe),
d116 2
a117 2
	.H01		(strobe_out),
	.H02		(pad_moe),
d124 2
a125 2
	.H01		(strobe_out),
	.H02		(pad_moe),
d132 2
a133 2
	.H01		(strobe_out),
	.H02		(pad_moe),
a138 1
//	assign		pad_mdata = pad_moe ? data_out : {32{1'bz}};
d143 2
d147 1
a147 1
	.H02		(pad_moe),
d155 1
a155 1
	.H02		(pad_moe),
d163 1
a163 1
	.H02		(pad_moe),
d171 1
a171 1
	.H02		(pad_moe),
d179 1
a179 1
	.H02		(pad_moe),
d187 1
a187 1
	.H02		(pad_moe),
d195 1
a195 1
	.H02		(pad_moe),
d203 1
a203 1
	.H02		(pad_moe),
d211 1
a211 1
	.H02		(pad_moe),
d219 1
a219 1
	.H02		(pad_moe),
d227 1
a227 1
	.H02		(pad_moe),
d235 1
a235 1
	.H02		(pad_moe),
d243 1
a243 1
	.H02		(pad_moe),
d251 1
a251 1
	.H02		(pad_moe),
d259 1
a259 1
	.H02		(pad_moe),
d267 1
a267 1
	.H02		(pad_moe),
d275 1
a275 1
	.H02		(pad_moe),
d283 1
a283 1
	.H02		(pad_moe),
d291 1
a291 1
	.H02		(pad_moe),
d299 1
a299 1
	.H02		(pad_moe),
d307 1
a307 1
	.H02		(pad_moe),
d315 1
a315 1
	.H02		(pad_moe),
d323 1
a323 1
	.H02		(pad_moe),
d331 1
a331 1
	.H02		(pad_moe),
d339 1
a339 1
	.H02		(pad_moe),
d347 1
a347 1
	.H02		(pad_moe),
d355 1
a355 1
	.H02		(pad_moe),
d363 1
a363 1
	.H02		(pad_moe),
d371 1
a371 1
	.H02		(pad_moe),
d379 1
a379 1
	.H02		(pad_moe),
d387 1
a387 1
	.H02		(pad_moe),
d395 1
a395 1
	.H02		(pad_moe),
d591 2
a592 2
	reg	D4Write;
	reg	D8Write;
d598 1
a598 1
		D4Write <= Write;
d603 113
a715 1
	assign	pad_moe = {5{reset_l & (D4Write | D8Write)}};
d717 39
a755 1
	assign	strobe_out = memclk ? (D4Write | D8Write) : 1'b0;
d759 2
a760 2
	reg	[3:0]	d2mout_01;
	reg	[3:0]	d2mout_23;
d773 1
a773 1
			d2mout_01 <= mout_01;
d777 1
a777 1
			d2mout_23 <= mout_23;
d780 29
a808 1
	assign		mdqm_out = memclk ? d2mout_01 : d2mout_23;
d844 2
a845 2
	reg	[31:0]	d2dout_01;
	reg	[31:0]	d2dout_23;
d859 1
a859 1
			d2dout_01 <= dout_01;
d862 3
a864 1
			d2dout_23 <= dout_23;
d866 223
a1088 1
	assign		data_out = memclk ? d2dout_01 : d2dout_23;
d1094 1
a1094 1
	always @(posedge strobe_in)
d1097 1
a1097 1
	always @(posedge strobe_in_b)
d1100 4
a1103 7
	reg	[63:0]	mdin;

	wire	[63:0]	nxt_mdin;

	assign	nxt_mdin[63:32] = din_01;

	assign	nxt_mdin[31:0]  = din_23;
d1106 1
a1106 1
		mdin[63:32] <= mdin_ena ? nxt_mdin[63:32] : mdin[63:32];
d1108 2
a1109 3
	reg		d1_mdin_ena;
	always @(posedge memclk)
		d1_mdin_ena <= mdin_ena;
d1112 4
a1115 1
		mdin[31:0] <= d1_mdin_ena ? nxt_mdin[31:0] : mdin[63:32];
