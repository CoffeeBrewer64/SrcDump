module ri_pads (
	memclk,
	memclk90,
	memclk180,
	memclk270,
	mcs,
	mras,
	mcas,
	mwe,
	mcke,
	mdqm,
	maddr,
	mbank,
	mdin,
	mdin_ena,
	mdout,
	mdout_ena,

	clk,
	clkb,
	csb,
	rasb,
	casb,
	web,
	cke,
	dqm,
	addr,
	bank,

	strobe,
	data
	);


	input		memclk;
	input		memclk90;
	input		memclk180;
	input		memclk270;
	input		mcs;
	input		mras;
	input		mcas;
	input		mwe;
	input		mcke;
	input	[7:0]	mdqm;
	input	[12:0]	maddr;
	input	[1:0]	mbank;
	output	[63:0]	mdin;
	input		mdin_ena;
	input	[63:0]	mdout;
	input		mdout_ena;

	output		clk;
	output		clkb;
	output		csb;
	output		rasb;
	output		casb;
	output		web;
	output		cke;
	output	[3:0]	dqm;
	output	[12:0]	addr;
	output	[1:0]	bank;

	inout		strobe;
	inout	[31:0]	data;

	//XXX

	wire	clk =   memclk;
	wire	clkb =  memclk180;

	reg		ecs;
	reg		eras;
	reg		ecas;
	reg		ewe;
	reg	[1:0]	ebank;
	reg	[12:0]	eaddr;
	reg		ecke;

	always @(posedge memclk) begin
		ecs  <=  mcs;
		eras <=  mras;
		ecas <=  mcas;
		ewe  <=  mwe;
		ebank<=  mbank;
		eaddr<=  maddr;
		ecke <=  mcke;
	end

	reg		csb;
	reg		rasb;
	reg		casb;
	reg		web;
	wire	[3:0]	dqm;
	reg	[1:0]	bank;
	reg	[12:0]	addr;
	reg		cke;

	// delay by 1/4 clock to avoid hold time issues

	always @(posedge memclk90) begin
		csb  <= ~ecs;
		rasb <= ~eras;
		casb <= ~ecas;
		web  <= ~ewe;
		bank <=  ebank;
		addr <=  eaddr;
		cke  <=  ecke;
	end

	reg	Write;
	reg	D4Write;

	always @(posedge memclk)
		Write <= mdout_ena;

	always @(posedge memclk180)
		D4Write <= Write;

	reg	[4:0]	oe;

	wire	nxt_oe = Write | mdout_ena;

	always @(posedge memclk)
		oe <= {5{nxt_oe}};

	wire	strobe_out = memclk270 ? D4Write : 1'b0;

	assign	strobe = oe[0] ? strobe_out : 1'bz;

	reg	[3:0]	mout_01;
	reg	[3:0]	mout_23;
	reg	[3:0]	d2mout_23;

	wire	[3:0]	nxt_mout_01 = mdout_ena ? mdqm [7:4] 
						: mout_01;

	wire	[3:0]	nxt_mout_23 = mdout_ena ? mdqm [3:0] 
						: mout_23;
	always @(posedge memclk) begin
			mout_01 <= nxt_mout_01;
			mout_23 <= nxt_mout_23;
	end
			
	always @(posedge memclk180)
			d2mout_23 <= mout_23;

	wire	[3:0]	dqm = memclk ? d2mout_23 : mout_01;

	reg	[31:0]	dout_01;
	reg	[31:0]	dout_23;
	reg	[31:0]	d2dout_23;

	wire	[31:0]	nxt_dout_01 = mdout_ena ? mdout[63:32]
						: dout_01;

	wire	[31:0]	nxt_dout_23 = mdout_ena ? mdout[31:0]
						: dout_23;

	always @(posedge memclk) begin
			dout_01 <= nxt_dout_01;
			dout_23 <= nxt_dout_23;
	end

	always @(posedge memclk180)
			d2dout_23 <= dout_23;

	wire	[31:0]	data_out = memclk ? d2dout_23 : dout_01;

	assign	data[31:24] = oe[1] ? data_out[31:24] : {8{1'bz}};
	assign	data[23:16] = oe[2] ? data_out[23:16] : {8{1'bz}};
	assign	data[15:8 ] = oe[3] ? data_out[15:8 ] : {8{1'bz}};
	assign	data[ 7:0 ] = oe[4] ? data_out[ 7:0 ] : {8{1'bz}};

	reg	[31:0]	din_01;

	reg	[31:0]	din_23;

	always @(posedge memclk90)
			din_01 <= data;

	always @(posedge memclk270)
			din_23 <= data;

	reg	[63:0]	mdin;

	wire	[63:0]	nxt_mdin;

	assign	nxt_mdin[63:32] = mdin_ena ? din_01 : mdin[63:32];

	assign	nxt_mdin[31:0]  = mdin_ena ? din_23 : mdin[31:0];

	always @(posedge memclk)
		mdin <= nxt_mdin;
endmodule

	

	


	

	
