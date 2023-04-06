d196 3
a198 1
	wire	[1:0]	pad_mclk =   {memclk180,memclk};
d227 1
a227 1
	// delay by 1/4 clock to avoid hold time issues
d229 1
a229 1
	always @(posedge memclk90) begin
d241 1
d249 2
a250 1
	reg	[4:0]	oe;
d252 1
a252 1
	wire	nxt_oe = Write | mdout_ena;
d254 1
a254 2
	always @(posedge memclk)
		oe <= {5{nxt_oe}};
d256 1
a256 1
	wire	strobe_out = memclk270 ? D4Write : 1'b0;
d258 1
a258 1
	wire	pad_mdqs = oe[0] ? strobe_out : 1'bz;
d262 1
d275 5
a279 1
	always @(posedge memclk180)
d281 1
d283 1
a283 1
	wire	[3:0]	pad_mdqm = memclk ? d2mout_23 : mout_01;
d287 1
d290 2
a291 2
	wire	[31:0]	nxt_dout_01 = mdout_ena ? mdout[63:32]
						: dout_01;
d293 2
a294 2
	wire	[31:0]	nxt_dout_23 = mdout_ena ? mdout[31:0]
						: dout_23;
d301 5
a305 1
	always @(posedge memclk180)
d307 1
d309 1
a309 1
	wire	[31:0]	data_out = memclk ? d2dout_23 : dout_01;
d320 7
a326 1
	always @(posedge memclk90)
d329 1
a329 1
	always @(posedge memclk270)
d336 1
a336 1
	assign	nxt_mdin[63:32] = mdin_ena ? din_01 : mdin[63:32];
d338 1
a338 1
	assign	nxt_mdin[31:0]  = mdin_ena ? din_23 : mdin[31:0];
d341 4
a344 1
		mdin <= nxt_mdin;
