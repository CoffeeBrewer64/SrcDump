d327 25
a351 141
	assign pad_mclk = { ~memclk, memclk };

	reg		emras;
	reg		emcas;
	reg		emwe;
	reg	[1:0]	embank;
	reg	[12:0]	emaddr;
	reg		emcke;

	always @(posedge memclk) begin
		emras <=  mras;
		emcas <=  mcas;
		emwe  <=  mwe;
		embank<=  mbank;
		emaddr<=  maddr;
		emcke <=  mcke;
	end

	reg		pad_mras;
	reg		pad_mcas;
	reg		pad_mwe;
	wire	[3:0]	pad_mdqm;
	reg	[1:0]	pad_mbank;
	reg	[12:0]	pad_maddr;
	reg		pad_mcke;

	// delay by 1/2 clock to avoid hold time issues

	always @(negedge memclk) begin
		pad_mras <= ~emras;
		pad_mcas <= ~emcas;
		pad_mwe  <= ~emwe;
		pad_mbank <=  embank;
		pad_maddr <=  emaddr;
		pad_mcke  <=  emcke;
	end

	reg	Write;
	reg	D4Write;
	reg	D8Write;

	always @(posedge memclk)
		Write <= mdout_ena;

	always @(negedge memclk)
		D4Write <= Write;

	always @(posedge memclk)
		D8Write <= D4Write;

	wire	pad_moe = {5{reset_l & (D4Write | D8Write)}};

	wire	strobe_out = memclk ? (D4Write | D8Write) : 1'b0;

	assign	pad_mdqs = pad_moe ? {4{strobe_out}} : 1'bz;

	reg	[3:0]	mout_01;
	reg	[3:0]	mout_23;
	reg	[3:0]	d2mout_01;
	reg	[3:0]	d2mout_23;

	wire	[3:0]	nxt_mout_01 = mdout_ena ? mdqm[7:4] 
						   : mout_01;

	wire	[3:0]	nxt_mout_23 = mdout_ena ? mdqm[3:0] 
						   : mout_23;
	always @(posedge memclk) begin
			mout_01 <= nxt_mout_01;
			mout_23 <= nxt_mout_23;
	end
			
	always @(negedge memclk) begin
			d2mout_01 <= mout_01;
	end

	always @(posedge memclk) begin
			d2mout_23 <= mout_23;
	end

	wire	[3:0]	pad_mdqm = memclk ? d2mout_01 : d2mout_23;

	reg	[31:0]	dout_01;
	reg	[31:0]	dout_23;
	reg	[31:0]	d2dout_01;
	reg	[31:0]	d2dout_23;

	wire	[31:0]	nxt_dout_01 = mdout_ena ? mdout[63:32]
						: dout_01;

	wire	[31:0]	nxt_dout_23 = mdout_ena ? mdout[31:0]
						: dout_23;

	always @(posedge memclk) begin
			dout_01 <= nxt_dout_01;
			dout_23 <= nxt_dout_23;
	end

	always @(negedge memclk) begin
			d2dout_01 <= dout_01;
	end

	always @(posedge memclk) begin
			d2dout_23 <= dout_23;
	end

	wire	[31:0]	data_out = memclk ? d2dout_01 : d2dout_23;

	assign		pad_mdata = pad_moe ? data_out : {32{1'bz}};

	reg	[31:0]	din_01;

	reg	[31:0]	din_23;

	wire	strobe_in   =  pad_mdqs[0];

	wire	strobe_in_b = ~pad_mdqs[0];

	always @(posedge strobe_in)
			din_01 <= pad_mdata;

	always @(posedge strobe_in_b)
			din_23 <= pad_mdata;

	reg	[63:0]	mdin;

	wire	[63:0]	nxt_mdin;

	assign	nxt_mdin[63:32] = din_01;

	assign	nxt_mdin[31:0]  = din_23;

	always @(posedge memclk)
		mdin[63:32] <= mdin_ena ? nxt_mdin[63:32] : mdin[63:32];

	reg		d1_mdin_ena;
	always @(posedge memclk)
		d1_mdin_ena <= mdin_ena;

	always @(negedge memclk)
		mdin[31:0] <= d1_mdin_ena ? nxt_mdin[31:0] : mdin[63:32];

