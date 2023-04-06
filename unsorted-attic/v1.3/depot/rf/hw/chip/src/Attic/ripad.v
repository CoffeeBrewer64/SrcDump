// ripad.v v1 
// ri chip pad module;
// :set tabstop=4

`timescale 1ns/1ns

module ripad (
	reset_l,
	memclk,
	pad_mclk,
	pad_mcke, mcke,
	pad_maddr, maddr,
	pad_mbank, mbank,
	mdin_ena,
	mdout_ena,
	strobe_rev,
	pad_mdata, mdin, mdout,
	pad_mras, mras,
	pad_mcas, mcas,
	pad_mwe, mwe,
	pad_mdqm, mdqm,
	pad_mdqs 
);
	// io pads;

	input reset_l;				// system reset for pad logic;
	input memclk;				// memory clock;

	output	[1:0]	pad_mclk;
	output		pad_mcke;
	input		mcke;
	output	[12:0]	pad_maddr;
	input	[12:0]	maddr;
	output	[1:0]	pad_mbank;
	input	[1:0]	mbank;
	input		mdin_ena;
	input		mdout_ena;
	input		strobe_rev;
	inout	[31:0]	pad_mdata;
	output	[63:0]	mdin;
	input	[63:0]	mdout;
	output		pad_mras;
	input		mras;
	output		pad_mcas;
	input		mcas;
	output		pad_mwe;
	input		mwe;
	output	[3:0]	pad_mdqm;
	input	[7:0]	mdqm;
	inout	[3:0]	pad_mdqs;

	// ddr io cells and registers;

	//	assign pad_mclk = { ~memclk, memclk };

	wire	memclk_b = ~memclk;

TDBIAST2NNC1 mclk (
	.H01		(memclk),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_mclk[0]),
	.N02		()
	);

TDBIAST2NNC1 mclkb (
	.H01		(memclk_b),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_mclk[1]),
	.N02		()
	);


	wire	strobe_in;
	wire	strobe_in_b;
	wire	strobe_in_p;
	wire	strobe_in_n;

//	assign	strobe_in_p = strobe_rev ? ~strobe_in :  strobe_in;
//	assign	strobe_in_n = strobe_rev ?  strobe_in : ~strobe_in;

TDINVX2 strbi0	(		// inverter
	.H01		(strobe_in),
	.N01		(strobe_in_b)
	);

TDMXI2X2 strbm0	(		// 2 to 1 Mux	(inverting)
	.H01		(strobe_in),	// D0
	.H02		(strobe_in_b),	// D1
	.H03		(strobe_rev),	// A		(select)
	.N01		(strobe_in_n)	// YB		(output)
	);

TDMXI2X2 strbm1	(		// 2 to 1 Mux	(inverting)
	.H01		(strobe_in_b),	// D0
	.H02		(strobe_in),	// D1
	.H03		(strobe_rev),	// A		(select)
	.N01		(strobe_in_p)	// YB		(output)
	);

	wire	[8:0]	pad_moe;
	wire	[3:0]	strobe_out;

//	assign	pad_mdqs = pad_moe ? strobe_out : {4{1'bz}};

TDBIAST2NNC1 mdqs0 (
	.H01		(strobe_out[0]),
	.H02		(pad_moe[8]),
	.H04		(1'b1),
	.N01		(pad_mdqs[0]),
	.N02		(strobe_in)
	);

TDBIAST2NNC1 mdqs1 (
	.H01		(strobe_out[1]),
	.H02		(pad_moe[8]),
	.H04		(1'b1),
	.N01		(pad_mdqs[1]),
	.N02		()
	);

TDBIAST2NNC1 mdqs2 (
	.H01		(strobe_out[2]),
	.H02		(pad_moe[8]),
	.H04		(1'b1),
	.N01		(pad_mdqs[2]),
	.N02		()
	);

TDBIAST2NNC1 mdqs3 (
	.H01		(strobe_out[3]),
	.H02		(pad_moe[8]),
	.H04		(1'b1),
	.N01		(pad_mdqs[3]),
	.N02		()
	);


	wire	[31:0]	pad_mdata_in;
	wire	[31:0]	data_out;

//	assign		pad_mdata = pad_moe ? data_out : {32{1'bz}};

TDBIAST2NNC1 mdq0 (
	.H01		(data_out[0]),
	.H02		(pad_moe[0]),
	.H04		(1'b1),
	.N01		(pad_mdata[0]),
	.N02		(pad_mdata_in[0])
	);

TDBIAST2NNC1 mdq1 (
	.H01		(data_out[1]),
	.H02		(pad_moe[0]),
	.H04		(1'b1),
	.N01		(pad_mdata[1]),
	.N02		(pad_mdata_in[1])
	);

TDBIAST2NNC1 mdq2 (
	.H01		(data_out[2]),
	.H02		(pad_moe[0]),
	.H04		(1'b1),
	.N01		(pad_mdata[2]),
	.N02		(pad_mdata_in[2])
	);

TDBIAST2NNC1 mdq3 (
	.H01		(data_out[3]),
	.H02		(pad_moe[0]),
	.H04		(1'b1),
	.N01		(pad_mdata[3]),
	.N02		(pad_mdata_in[3])
	);

TDBIAST2NNC1 mdq4 (
	.H01		(data_out[4]),
	.H02		(pad_moe[1]),
	.H04		(1'b1),
	.N01		(pad_mdata[4]),
	.N02		(pad_mdata_in[4])
	);

TDBIAST2NNC1 mdq5 (
	.H01		(data_out[5]),
	.H02		(pad_moe[1]),
	.H04		(1'b1),
	.N01		(pad_mdata[5]),
	.N02		(pad_mdata_in[5])
	);

TDBIAST2NNC1 mdq6 (
	.H01		(data_out[6]),
	.H02		(pad_moe[1]),
	.H04		(1'b1),
	.N01		(pad_mdata[6]),
	.N02		(pad_mdata_in[6])
	);

TDBIAST2NNC1 mdq7 (
	.H01		(data_out[7]),
	.H02		(pad_moe[1]),
	.H04		(1'b1),
	.N01		(pad_mdata[7]),
	.N02		(pad_mdata_in[7])
	);

TDBIAST2NNC1 mdq8 (
	.H01		(data_out[8]),
	.H02		(pad_moe[2]),
	.H04		(1'b1),
	.N01		(pad_mdata[8]),
	.N02		(pad_mdata_in[8])
	);

TDBIAST2NNC1 mdq9 (
	.H01		(data_out[9]),
	.H02		(pad_moe[2]),
	.H04		(1'b1),
	.N01		(pad_mdata[9]),
	.N02		(pad_mdata_in[9])
	);

TDBIAST2NNC1 mdq10 (
	.H01		(data_out[10]),
	.H02		(pad_moe[2]),
	.H04		(1'b1),
	.N01		(pad_mdata[10]),
	.N02		(pad_mdata_in[10])
	);

TDBIAST2NNC1 mdq11 (
	.H01		(data_out[11]),
	.H02		(pad_moe[2]),
	.H04		(1'b1),
	.N01		(pad_mdata[11]),
	.N02		(pad_mdata_in[11])
	);

TDBIAST2NNC1 mdq12 (
	.H01		(data_out[12]),
	.H02		(pad_moe[3]),
	.H04		(1'b1),
	.N01		(pad_mdata[12]),
	.N02		(pad_mdata_in[12])
	);

TDBIAST2NNC1 mdq13 (
	.H01		(data_out[13]),
	.H02		(pad_moe[3]),
	.H04		(1'b1),
	.N01		(pad_mdata[13]),
	.N02		(pad_mdata_in[13])
	);

TDBIAST2NNC1 mdq14 (
	.H01		(data_out[14]),
	.H02		(pad_moe[3]),
	.H04		(1'b1),
	.N01		(pad_mdata[14]),
	.N02		(pad_mdata_in[14])
	);

TDBIAST2NNC1 mdq15 (
	.H01		(data_out[15]),
	.H02		(pad_moe[3]),
	.H04		(1'b1),
	.N01		(pad_mdata[15]),
	.N02		(pad_mdata_in[15])
	);

TDBIAST2NNC1 mdq16 (
	.H01		(data_out[16]),
	.H02		(pad_moe[4]),
	.H04		(1'b1),
	.N01		(pad_mdata[16]),
	.N02		(pad_mdata_in[16])
	);

TDBIAST2NNC1 mdq17 (
	.H01		(data_out[17]),
	.H02		(pad_moe[4]),
	.H04		(1'b1),
	.N01		(pad_mdata[17]),
	.N02		(pad_mdata_in[17])
	);

TDBIAST2NNC1 mdq18 (
	.H01		(data_out[18]),
	.H02		(pad_moe[4]),
	.H04		(1'b1),
	.N01		(pad_mdata[18]),
	.N02		(pad_mdata_in[18])
	);

TDBIAST2NNC1 mdq19 (
	.H01		(data_out[19]),
	.H02		(pad_moe[4]),
	.H04		(1'b1),
	.N01		(pad_mdata[19]),
	.N02		(pad_mdata_in[19])
	);

TDBIAST2NNC1 mdq20 (
	.H01		(data_out[20]),
	.H02		(pad_moe[5]),
	.H04		(1'b1),
	.N01		(pad_mdata[20]),
	.N02		(pad_mdata_in[20])
	);

TDBIAST2NNC1 mdq21 (
	.H01		(data_out[21]),
	.H02		(pad_moe[5]),
	.H04		(1'b1),
	.N01		(pad_mdata[21]),
	.N02		(pad_mdata_in[21])
	);

TDBIAST2NNC1 mdq22 (
	.H01		(data_out[22]),
	.H02		(pad_moe[5]),
	.H04		(1'b1),
	.N01		(pad_mdata[22]),
	.N02		(pad_mdata_in[22])
	);

TDBIAST2NNC1 mdq23 (
	.H01		(data_out[23]),
	.H02		(pad_moe[5]),
	.H04		(1'b1),
	.N01		(pad_mdata[23]),
	.N02		(pad_mdata_in[23])
	);

TDBIAST2NNC1 mdq24 (
	.H01		(data_out[24]),
	.H02		(pad_moe[6]),
	.H04		(1'b1),
	.N01		(pad_mdata[24]),
	.N02		(pad_mdata_in[24])
	);

TDBIAST2NNC1 mdq25 (
	.H01		(data_out[25]),
	.H02		(pad_moe[6]),
	.H04		(1'b1),
	.N01		(pad_mdata[25]),
	.N02		(pad_mdata_in[25])
	);

TDBIAST2NNC1 mdq26 (
	.H01		(data_out[26]),
	.H02		(pad_moe[6]),
	.H04		(1'b1),
	.N01		(pad_mdata[26]),
	.N02		(pad_mdata_in[26])
	);

TDBIAST2NNC1 mdq27 (
	.H01		(data_out[27]),
	.H02		(pad_moe[6]),
	.H04		(1'b1),
	.N01		(pad_mdata[27]),
	.N02		(pad_mdata_in[27])
	);

TDBIAST2NNC1 mdq28 (
	.H01		(data_out[28]),
	.H02		(pad_moe[7]),
	.H04		(1'b1),
	.N01		(pad_mdata[28]),
	.N02		(pad_mdata_in[28])
	);

TDBIAST2NNC1 mdq29 (
	.H01		(data_out[29]),
	.H02		(pad_moe[7]),
	.H04		(1'b1),
	.N01		(pad_mdata[29]),
	.N02		(pad_mdata_in[29])
	);

TDBIAST2NNC1 mdq30 (
	.H01		(data_out[30]),
	.H02		(pad_moe[7]),
	.H04		(1'b1),
	.N01		(pad_mdata[30]),
	.N02		(pad_mdata_in[30])
	);

TDBIAST2NNC1 mdq31 (
	.H01		(data_out[31]),
	.H02		(pad_moe[7]),
	.H04		(1'b1),
	.N01		(pad_mdata[31]),
	.N02		(pad_mdata_in[31])
	);

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

	reg		mras_out;
	reg		mcas_out;
	reg		mwe_out;
	wire	[3:0]	mdqm_out;
	reg	[1:0]	mbank_out;
	reg	[12:0]	maddr_out;
	reg		mcke_out;

	// delay by 1/2 clock to avoid hold time issues

	always @(negedge memclk) begin
		mras_out <= ~emras;
		mcas_out <= ~emcas;
		mwe_out  <= ~emwe;
		mbank_out <=  embank;
		maddr_out <=  emaddr;
		mcke_out  <=  emcke;
	end

TDBIAST2NNC1 mras0 (
	.H01		(mras_out),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_mras),
	.N02		()
	);

TDBIAST2NNC1 mcas0 (
	.H01		(mcas_out),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_mcas),
	.N02		()
	);

TDBIAST2NNC1 mwe0 (
	.H01		(mwe_out),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_mwe),
	.N02		()
	);

TDBIAST2NNC1 mbank0 (
	.H01		(mbank_out[0]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_mbank[0]),
	.N02		()
	);

TDBIAST2NNC1 mbank1 (
	.H01		(mbank_out[1]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_mbank[1]),
	.N02		()
	);

	wire	rmcke_out = mcke_out & reset_l;

TDBIAST2NNC1 mcke0 (
	.H01		(rmcke_out),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_mcke),
	.N02		()
	);

TDBIAST2NNC1 maddr0 (
	.H01		(maddr_out[0]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[0]),
	.N02		()
	);

TDBIAST2NNC1 maddr1 (
	.H01		(maddr_out[1]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[1]),
	.N02		()
	);

TDBIAST2NNC1 maddr2 (
	.H01		(maddr_out[2]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[2]),
	.N02		()
	);

TDBIAST2NNC1 maddr3 (
	.H01		(maddr_out[3]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[3]),
	.N02		()
	);

TDBIAST2NNC1 maddr4 (
	.H01		(maddr_out[4]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[4]),
	.N02		()
	);

TDBIAST2NNC1 maddr5 (
	.H01		(maddr_out[5]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[5]),
	.N02		()
	);

TDBIAST2NNC1 maddr6 (
	.H01		(maddr_out[6]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[6]),
	.N02		()
	);

TDBIAST2NNC1 maddr7 (
	.H01		(maddr_out[7]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[7]),
	.N02		()
	);

TDBIAST2NNC1 maddr8 (
	.H01		(maddr_out[8]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[8]),
	.N02		()
	);

TDBIAST2NNC1 maddr9 (
	.H01		(maddr_out[9]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[9]),
	.N02		()
	);

TDBIAST2NNC1 maddr10 (
	.H01		(maddr_out[10]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[10]),
	.N02		()
	);

TDBIAST2NNC1 maddr11 (
	.H01		(maddr_out[11]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[11]),
	.N02		()
	);

TDBIAST2NNC1 maddr12 (
	.H01		(maddr_out[12]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_maddr[12]),
	.N02		()
	);

	reg	Write;
	reg	[1:0]	D4Write;
	reg	[1:0]	D8Write;

	always @(posedge memclk)
		Write <= mdout_ena;

	always @(negedge memclk)
		D4Write <= {2{Write}};

	always @(posedge memclk)
		D8Write <= D4Write;

//	assign	pad_moe = {9{reset_l & (D4Write[0] | D8Write[0])}};

	wire	reset = ~reset_l;

TDNR2X2 dnor0 (
	.H01		(D4Write[0]),
	.H02		(D8Write[0]),
	.N01		(D4OR8B0)
	);

TDNR2X2 moe0 (
	.H01		(D4OR8B0),
	.H02		(reset),
	.N01		(pad_moe[0])
	);

TDNR2X2 dnor1 (
	.H01		(D4Write[0]),
	.H02		(D8Write[0]),
	.N01		(D4OR8B1)
	);

TDNR2X2 moe1 (
	.H01		(D4OR8B1),
	.H02		(reset),
	.N01		(pad_moe[1])
	);

TDNR2X2 dnor2 (
	.H01		(D4Write[0]),
	.H02		(D8Write[0]),
	.N01		(D4OR8B2)
	);

TDNR2X2 moe2 (
	.H01		(D4OR8B2),
	.H02		(reset),
	.N01		(pad_moe[2])
	);

TDNR2X2 dnor3 (
	.H01		(D4Write[0]),
	.H02		(D8Write[0]),
	.N01		(D4OR8B3)
	);

TDNR2X2 moe3 (
	.H01		(D4OR8B3),
	.H02		(reset),
	.N01		(pad_moe[3])
	);

TDNR2X2 dnor4 (
	.H01		(D4Write[0]),
	.H02		(D8Write[0]),
	.N01		(D4OR8B4)
	);

TDNR2X2 moe4 (
	.H01		(D4OR8B4),
	.H02		(reset),
	.N01		(pad_moe[4])
	);

TDNR2X2 dnor5 (
	.H01		(D4Write[1]),
	.H02		(D8Write[1]),
	.N01		(D4OR8B5)
	);

TDNR2X2 moe5 (
	.H01		(D4OR8B5),
	.H02		(reset),
	.N01		(pad_moe[5])
	);

TDNR2X2 dnor6 (
	.H01		(D4Write[1]),
	.H02		(D8Write[1]),
	.N01		(D4OR8B6)
	);

TDNR2X2 moe6 (
	.H01		(D4OR8B6),
	.H02		(reset),
	.N01		(pad_moe[6])
	);

TDNR2X2 dnor7 (
	.H01		(D4Write[1]),
	.H02		(D8Write[1]),
	.N01		(D4OR8B7)
	);

TDNR2X2 moe7 (
	.H01		(D4OR8B7),
	.H02		(reset),
	.N01		(pad_moe[7])
	);

TDNR2X2 dnor8 (
	.H01		(D4Write[1]),
	.H02		(D8Write[1]),
	.N01		(D4OR8B8)
	);

TDNR2X2 moe8 (
	.H01		(D4OR8B8),
	.H02		(reset),
	.N01		(pad_moe[8])
	);

//	assign	strobe_out = {4{memclk ? D4Write : 1'b0}};

	wire	D4Write_dly;

TDDLY2X2 d4dly (				// delay approx 1/2 nsec
	.H01		(D4Write[1]),
	.N01		(D4Write_dly)
	);

TDINVX2 d4inv	(		// inverter
	.H01		(D4Write_dly),
	.N01		(D4Write_dly_b)
	);

TDMXI2X2 soutm0	(				// 2 to 1 Mux	(inverting)
	.H01		(1'b1),			// D0
	.H02		(D4Write_dly_b),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(strobe_out[0])		// YB		(output)
	);

TDMXI2X2 soutm1	(				// 2 to 1 Mux	(inverting)
	.H01		(1'b1),			// D0
	.H02		(D4Write_dly_b),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(strobe_out[1])		// YB		(output)
	);

TDMXI2X2 soutm2	(				// 2 to 1 Mux	(inverting)
	.H01		(1'b1),			// D0
	.H02		(D4Write_dly_b),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(strobe_out[2])		// YB		(output)
	);

TDMXI2X2 soutm3	(				// 2 to 1 Mux	(inverting)
	.H01		(1'b1),			// D0
	.H02		(D4Write_dly_b),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(strobe_out[3])		// YB		(output)
	);

	reg	[3:0]	mout_01;
	reg	[3:0]	mout_23;
	reg	[3:0]	d2mout_01_b;
	reg	[3:0]	d2mout_23_b;

	wire	[3:0]	nxt_mout_01 = mdout_ena ? mdqm[7:4] 
						   : mout_01;

	wire	[3:0]	nxt_mout_23 = mdout_ena ? mdqm[3:0] 
						   : mout_23;
	always @(posedge memclk) begin
			mout_01 <= nxt_mout_01;
			mout_23 <= nxt_mout_23;
	end
			
	always @(negedge memclk) begin
			d2mout_01_b <= ~mout_01;
	end

	always @(posedge memclk) begin
			d2mout_23_b <= ~mout_23;
	end

//	assign		mdqm_out = memclk ? ~d2mout_01_b : ~d2mout_23_b;

TDMXI2X2 moutm0	(				// 2 to 1 Mux	(inverting)
	.H01		(d2mout_23_b[0]),	// D0
	.H02		(d2mout_01_b[0]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(mdqm_out[0])		// YB		(output)
	);

TDMXI2X2 moutm1	(				// 2 to 1 Mux	(inverting)
	.H01		(d2mout_23_b[1]),	// D0
	.H02		(d2mout_01_b[1]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(mdqm_out[1])		// YB		(output)
	);

TDMXI2X2 moutm2	(				// 2 to 1 Mux	(inverting)
	.H01		(d2mout_23_b[2]),	// D0
	.H02		(d2mout_01_b[2]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(mdqm_out[2])		// YB		(output)
	);

TDMXI2X2 moutm3	(				// 2 to 1 Mux	(inverting)
	.H01		(d2mout_23_b[3]),	// D0
	.H02		(d2mout_01_b[3]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(mdqm_out[3])		// YB		(output)
	);

TDBIAST2NNC1 mdqm0 (
	.H01		(mdqm_out[0]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_mdqm[0]),
	.N02		()
	);

TDBIAST2NNC1 mdqm1 (
	.H01		(mdqm_out[1]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_mdqm[1]),
	.N02		()
	);

TDBIAST2NNC1 mdqm2 (
	.H01		(mdqm_out[2]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_mdqm[2]),
	.N02		()
	);

TDBIAST2NNC1 mdqm3 (
	.H01		(mdqm_out[3]),
	.H02		(1'b1),
	.H04		(1'b0),
	.N01		(pad_mdqm[3]),
	.N02		()
	);

	reg	[31:0]	dout_01;
	reg	[31:0]	dout_23;
	reg	[31:0]	d2dout_01_b;
	reg	[31:0]	d2dout_23_b;

	wire	[31:0]	nxt_dout_01 = mdout_ena ? mdout[63:32]
						: dout_01;

	wire	[31:0]	nxt_dout_23 = mdout_ena ? mdout[31:0]
						: dout_23;

	always @(posedge memclk) begin
			dout_01 <= nxt_dout_01;
			dout_23 <= nxt_dout_23;
	end

	always @(negedge memclk) 
			d2dout_01_b <= ~dout_01;

	always @(posedge memclk) 
			d2dout_23_b <= ~dout_23;

	assign		data_out = memclk ? ~d2dout_01_b : ~d2dout_23_b;

TDMXI2X2 doutm0	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[0]),	// D0
	.H02		(d2dout_01_b[0]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[0])		// YB		(output)
	);

TDMXI2X2 doutm1	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[1]),	// D0
	.H02		(d2dout_01_b[1]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[1])		// YB		(output)
	);

TDMXI2X2 doutm2	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[2]),	// D0
	.H02		(d2dout_01_b[2]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[2])		// YB		(output)
	);

TDMXI2X2 doutm3	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[3]),	// D0
	.H02		(d2dout_01_b[3]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[3])		// YB		(output)
	);

TDMXI2X2 doutm4	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[4]),	// D0
	.H02		(d2dout_01_b[4]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[4])		// YB		(output)
	);

TDMXI2X2 doutm5	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[5]),	// D0
	.H02		(d2dout_01_b[5]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[5])		// YB		(output)
	);

TDMXI2X2 doutm6	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[6]),	// D0
	.H02		(d2dout_01_b[6]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[6])		// YB		(output)
	);

TDMXI2X2 doutm7	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[7]),	// D0
	.H02		(d2dout_01_b[7]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[7])		// YB		(output)
	);

TDMXI2X2 doutm8	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[8]),	// D0
	.H02		(d2dout_01_b[8]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[8])		// YB		(output)
	);

TDMXI2X2 doutm9	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[9]),	// D0
	.H02		(d2dout_01_b[9]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[9])		// YB		(output)
	);

TDMXI2X2 doutm10	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[10]),	// D0
	.H02		(d2dout_01_b[10]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[10])		// YB		(output)
	);

TDMXI2X2 doutm11	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[11]),	// D0
	.H02		(d2dout_01_b[11]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[11])		// YB		(output)
	);

TDMXI2X2 doutm12	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[12]),	// D0
	.H02		(d2dout_01_b[12]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[12])		// YB		(output)
	);

TDMXI2X2 doutm13	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[13]),	// D0
	.H02		(d2dout_01_b[13]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[13])		// YB		(output)
	);

TDMXI2X2 doutm14	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[14]),	// D0
	.H02		(d2dout_01_b[14]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[14])		// YB		(output)
	);

TDMXI2X2 doutm15	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[15]),	// D0
	.H02		(d2dout_01_b[15]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[15])		// YB		(output)
	);

TDMXI2X2 doutm16	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[16]),	// D0
	.H02		(d2dout_01_b[16]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[16])		// YB		(output)
	);

TDMXI2X2 doutm17	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[17]),	// D0
	.H02		(d2dout_01_b[17]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[17])		// YB		(output)
	);

TDMXI2X2 doutm18	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[18]),	// D0
	.H02		(d2dout_01_b[18]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[18])		// YB		(output)
	);

TDMXI2X2 doutm19	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[19]),	// D0
	.H02		(d2dout_01_b[19]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[19])		// YB		(output)
	);

TDMXI2X2 doutm20	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[20]),	// D0
	.H02		(d2dout_01_b[20]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[20])		// YB		(output)
	);

TDMXI2X2 doutm21	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[21]),	// D0
	.H02		(d2dout_01_b[21]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[21])		// YB		(output)
	);

TDMXI2X2 doutm22	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[22]),	// D0
	.H02		(d2dout_01_b[22]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[22])		// YB		(output)
	);

TDMXI2X2 doutm23	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[23]),	// D0
	.H02		(d2dout_01_b[23]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[23])		// YB		(output)
	);

TDMXI2X2 doutm24	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[24]),	// D0
	.H02		(d2dout_01_b[24]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[24])		// YB		(output)
	);

TDMXI2X2 doutm25	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[25]),	// D0
	.H02		(d2dout_01_b[25]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[25])		// YB		(output)
	);

TDMXI2X2 doutm26	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[26]),	// D0
	.H02		(d2dout_01_b[26]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[26])		// YB		(output)
	);

TDMXI2X2 doutm27	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[27]),	// D0
	.H02		(d2dout_01_b[27]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[27])		// YB		(output)
	);

TDMXI2X2 doutm28	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[28]),	// D0
	.H02		(d2dout_01_b[28]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[28])		// YB		(output)
	);

TDMXI2X2 doutm29	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[29]),	// D0
	.H02		(d2dout_01_b[29]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[29])		// YB		(output)
	);

TDMXI2X2 doutm30	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[30]),	// D0
	.H02		(d2dout_01_b[30]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[30])		// YB		(output)
	);

TDMXI2X2 doutm31	(		// 2 to 1 Mux	(inverting)
	.H01		(d2dout_23_b[31]),	// D0
	.H02		(d2dout_01_b[31]),	// D1
	.H03		(memclk),		// A		(select)
	.N01		(data_out[31])		// YB		(output)
	);

	reg	[31:0]	din_01;

	reg	[31:0]	din_23;

	always @(posedge strobe_in_p)
			din_01 <= pad_mdata_in;

	always @(posedge strobe_in_n)
			din_23 <= pad_mdata_in;

	wire	[63:0]	mdin;
	reg	[63:0]	mdin_rs;
	reg	[31:0]	mdin_p;
	reg	[31:0]	mdin_n;

	always @(posedge memclk)
		mdin_p <=  din_01;

	always @(negedge memclk)
		mdin_n <=  din_23;

	always @(negedge memclk)
		mdin_rs <=  {mdin_n,mdin_p};

	wire	[63:0]	mdin = strobe_rev ? mdin_rs
					  : {mdin_p,mdin_n};

endmodule

