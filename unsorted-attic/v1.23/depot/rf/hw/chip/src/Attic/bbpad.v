// bbpad.v v1 Frank Berndt
// bb chip pad module;
// :set tabstop=4

`timescale 1ns/1ns

module bbpad (
	pad_rst_l, rst_l, reset_l,
	pad_sysclk, sysclk,
	memclk, pllx2_lock,
	pad_usbclki, pad_usbclko, usbclk,
	pad_vclki, pad_vclko, vclk,
	pad_button, button,
	pad_vclock, vclock,
	pad_vdata, vdata,
	pad_vsync, vsync,
	vdac_clk, vdac_pd,
	pad_voa, vda,
	pad_vob, vdb,
	pad_voc, vdc,
	pad_aclock, aclock,
	pad_adata, adata,
	pad_aword, aword,
	pad_jchan, jchan_in, jchan_ena, jchan_oe,
	pad_lx, lctrl_x,
	pad_ly, lctrl_y,
	pad_io_rst, io_rst,
	pad_io_ad, io_in, io_ena, io_out, io_oe,
	pad_io_ale, io_ale,
	pad_io_cs, io_cs,
	pad_io_ior, io_ior,
	pad_io_iow, io_iow,
	pad_io_dmarq, io_dmarq,
	pad_io_dmack, io_dmack,
	pad_io_intr, io_intr,
	pad_fl_ce, fl_ce,
	pad_fl_ale, fl_ale,
	pad_fl_cle, fl_cle,
	pad_fl_re, fl_re,
	pad_fl_we, fl_we,
	pad_fl_wp, fl_wp,
	pad_fl_ryby, fl_ryby,
	pad_fl_md, fl_md,
	pad_gpio, gpio_oe, gpio_out, gpio_in,
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
	pad_mdqs, 
	pad_usb_dminus, usb_dm, usbxr_ose,
	pad_usb_dplus, 	usb_dp, usb_dpo, 
	usbxr_y1, usbxr_oen, usbxr_ien, usbxr_fl,
	pad_usb_dp_high, usb_dp_high,
	pad_usb_dm_high, usb_dm_high,
	pad_usb_id, usb_id,
	pad_usb_vbus_on_n,  usb_vbus_on_n,
	pad_trst, trst,
	pad_tdi, tdi,
	pad_tms, tms,
	pad_tck, tck,
	tdoen,
	pad_tdo, tdo,
	pad_pllx2_avdd,
	pad_pllx2_agnd,
	pad_pllc_avdd, pllc_avdd1,
	pad_pllc_agnd, pllc_agnd1,
	pad_pllv_avdd,
	pad_pllv_agnd
);
	// io pads;

	input pad_rst_l;			// chip reset input;
	output rst_l;				// chip reset;
	input reset_l;				// system reset for pad logic;
	input pad_sysclk;			// system clock input pin;
	output sysclk;				// system clock;
	output memclk;				// memory clock;
	output pllx2_lock;			// x2 pll locked;
	input pad_usbclki;			// usb clock input pin;
	output pad_usbclko;			// usb clock output pin;
	output usbclk;				// usb clock from oscillator;
	input pad_vclki;			// video clock input pin;
	output pad_vclko;			// video clock output pin;
	output vclk;				// video clock from oscillator;
	input pad_button;			// button pin;
	output button;				// output of input buffer;

	output pad_vclock;			// video clock pin;
	output vclock;				// generated video clock to vi;
	output [6:0] pad_vdata;		// video data pins;
	input [6:0] vdata;			// video data;
	output pad_vsync;			// video sync pin;
	input vsync;				// video sync;
	input vdac_clk;				// video dac clock;
	input vdac_pd;				// video dac power-down;
	output pad_voa;				// analog video; chroma;
	input [7:0] vda;			// dac data chroma;
	output pad_vob;				// analog video; composite;
	input [7:0] vdb;			// dac data composite;
	output pad_voc;				// analog video; luminance;
	input [7:0] vdc;			// dac data luminance;

	output pad_aclock;			// audio clock pin;
	input aclock;				// audio clock;
	output pad_adata;			// audio data pin;
	input adata;				// audio data;
	output pad_aword;			// audio word clock pin;
	input aword;				// audio word clock;

	inout [3:1] pad_jchan;		// jchan pins;
	output [3:1] jchan_in;		// output of input register;
	input [3:1] jchan_ena;		// input register clock enable;
	input [3:1] jchan_oe;		// drive 0 on jchan;

	input [1:0] pad_lx;			// stick x pins;
	output [1:0] lctrl_x;		// output of input buffer;
	input [1:0] pad_ly;			// stick y pins;
	output [1:0] lctrl_y;		// output of input buffer;

	output pad_io_rst;			// io bus reset pin;
	input io_rst;				// io bus reset;
	inout [15:0] pad_io_ad;		// io data bus pins;
	output [15:0] io_in;		// io input data;
	input io_ena;				// io input clock enables;
	input [15:0] io_out;		// io output data;
	input [1:0] io_oe;			// io data output enables;
	output pad_io_ale;			// io address latch enable pin;
	input io_ale;				// io address latch enable;
	output [3:0] pad_io_cs;		// io pio chip select pins;
	input [3:0] io_cs;			// io pio chip selects;
	output pad_io_ior;			// io read pulse pin;
	input io_ior;				// io read pulse;
	output pad_io_iow;			// io write pulse pin;
	input io_iow;				// io write pulse;
	input pad_io_dmarq;			// io dma request pin;
	output io_dmarq;			// io dma request;
	output pad_io_dmack;		// io dma acknowledge pin;
	input io_dmack;				// io dma acknowledge;
	input pad_io_intr;			// io device interrupt pin;
	output io_intr;				// io device interrupt;

	output [3:0] pad_fl_ce;		// chip enables pin;
	input [3:0] fl_ce;			// chip enables pin;
	output pad_fl_ale;			// address latch enable pin;
	input fl_ale;				// address latch enable pin;
	output pad_fl_cle;			// command latch enable pin;
	input fl_cle;				// command latch enable pin;
	output pad_fl_re;			// read eanble pin;
	input fl_re;				// read eanble pin;
	output pad_fl_we;			// write eanble pin;
	input fl_we;				// write eanble pin;
	output pad_fl_wp;			// write protect pin;
	input fl_wp;				// write protect pin;
	input pad_fl_ryby;			// ready/busy pin;
	output fl_ryby;				// ready/busy pin;
	input pad_fl_md;			// module detect pin;
	output fl_md;				// module detect;

	inout [3:0] pad_gpio;		// gpio pins;
	input [3:0] gpio_oe;		// output enables;
	input [3:0] gpio_out;		// output values;
	output [3:0] gpio_in;		// input values;

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

	// usb singles
	
	inout   [1:0] pad_usb_dminus;     // D-
	input   [1:0] usbxr_ose;
	output  [1:0] usb_dm;
	
	inout   [1:0] pad_usb_dplus;      // D+ 
	input   [1:0] usb_dpo;
	output  [1:0] usb_dp;

	output  [1:0] usbxr_y1;			  // xcvr side signals	
	input   [1:0] usbxr_oen;
	input   [1:0] usbxr_ien;
	input   [1:0] usbxr_fl;

	output  [1:0] pad_usb_dp_high;   
	input   [1:0] usb_dp_high; 		  // pull up 
	output  [1:0] pad_usb_dm_high; 	
	input   [1:0] usb_dm_high;	 	  // pull down

	input   [1:0] pad_usb_id;
	output  [1:0] usb_id;
	output  [1:0] pad_usb_vbus_on_n;
	input   [1:0] usb_vbus_on_n;

	// JTAG
	output trst;
	input pad_trst;
	output tdi;
	input pad_tdi;
	output tms;
	input pad_tms;
	output tck;
	input pad_tck;
	input tdoen;
	input tdo;
	output pad_tdo;

	// pll power interfaces;

	input pad_pllx2_avdd;		// x2 pll analog power pin;
	input pad_pllx2_agnd;		// x2 pll analog ground pin;
	input pad_pllc_avdd;		// cpu pll analog power pin;
	output pllc_avdd1;			// cpu pll analog power;
	input pad_pllc_agnd;		// cpu pll analog ground pin;
	output pllc_agnd1;			// cpu pll analog ground;
	input pad_pllv_avdd;		// video pll analog power pin;
	input pad_pllv_agnd;		// video pll analog ground pin;

	// clock input buffer;
	// XXX

	assign rst_l = pad_rst_l;
	assign sysclk = pad_sysclk;
	assign usbclk = pad_usbclki;
	assign pad_usbclko = ~pad_usbclki;

	// instantiate x2 pll;
	// creates ddr clock x2, and aligns memclk with sysclk;
	// vco runs from 250...400Mhz (sysclk 62.5...100);

	wire pllx2_m;				// M divider;
	wire [3:0] pllx2_n;			// N divider;
	wire [3:0] pllx2_pa;		// PA divider;
	wire [3:0] pllx2_pb;		// PB divider;
	wire [3:0] pllx2_pc;		// PC divider;
	wire [2:0] pllx2_stby;		// standby controls;
	wire pllx2_clk;				// x2 clock output;
	wire pllx2_mode;			// test mode;
	wire pllx2_atbi0;			// test mode;
	wire pllx2_test;			// test mode;
	wire pllx2_bunri;			// test mode;
	wire pllx2_avdd1;			// pll analog power;
	wire pllx2_agnd1;			// pll analog ground;

	assign pllx2_m = 1;				// rclk / 2 = 31.25...50Mhz;
	assign pllx2_n = 4'd3;			// vco / pa / 4 = 31.25...50Mhz;
	assign pllx2_pa = 4'd1;			// clk A = vco / 2;
	assign pllx2_pb = 4'd1;			// clk B = vco / 2;
	assign pllx2_pc = 4'd1;			// clk C = vco / 2;
	assign pllx2_stby[0] = ~rst_l; //XXX
	assign pllx2_stby[1] = 1'b1;	// turn off port B;
	assign pllx2_stby[2] = 1'b1;	// turn off port C;
	assign pllx2_mode = 1'b0;
	assign pllx2_atbi0 = 1'b0;
	assign pllx2_test = 1'b0;
	assign pllx2_bunri = 1'b0;

	ABPLSSCH pllx2 (
		.RCLK(sysclk),
		.CLKI(memclk),
		.M0(pllx2_m),
		.N0(pllx2_n[0]),
		.N1(pllx2_n[1]),
		.N2(pllx2_n[2]),
		.N3(pllx2_n[3]),
		.PA0(pllx2_pa[0]),
		.PA1(pllx2_pa[1]),
		.PA2(pllx2_pa[2]),
		.PA3(pllx2_pa[3]),
		.PB0(pllx2_pb[0]),
		.PB1(pllx2_pb[1]),
		.PB2(pllx2_pb[2]),
		.PB3(pllx2_pb[3]),
		.PC0(pllx2_pc[0]),
		.PC1(pllx2_pc[1]),
		.PC2(pllx2_pc[2]),
		.PC3(pllx2_pc[3]),
		.STBY(pllx2_stby[0]),
		.PBSTBY(pllx2_stby[1]),
		.PCSTBY(pllx2_stby[1]),
		.CLKOA(pllx2_clk),
		.CLKOB(),
		.CLKOC(),
		.PLOCK(pllx2_lock),
		.MODE(pllx2_mode),
		.ATBI0(pllx2_atbi0),
		.TEST(pllx2_test),
		.BUNRI(pllx2_bunri),
		.TBI0(1'b0),
		.TBI1(1'b0),
		.TBI2(1'b0),
		.TBI3(1'b0),
		.TBI4(1'b0),
		.TBI5(1'b0),
		.TBI6(1'b0),
		.TBI7(1'b0),
		.TBI8(1'b0),
		.TBI9(1'b0),
		.TBI10(1'b0),
		.TBI11(1'b0),
		.TBI12(1'b0),
		.TBI13(1'b0),
		.TBI14(1'b0),
		.TBI15(1'b0),
		.TBI16(1'b0),
		.TBI17(1'b0),
		.TBI18(1'b0),
		.TBI19(1'b0),
		.TBI20(1'b0),
		.TBI21(1'b0),
		.TBO0(),
		.TBO1(),
		.TBO2(),
		.TBO3(),
		.TBO4(),
		.AVDD1(pllx2_avdd1),
		.AGND1(pllx2_agnd1)
	);

	wire memclk = pllx2_clk;

	// instantiate video pll;
	// XXX

	wire pllv_avdd1;			// pll analog power;
	wire pllv_agnd1;			// pll analog ground;

	// ddr pll power interface;

	AAPLAIOH33 pllpwr_x2 (
		.AVDD(pad_pllx2_avdd),
		.AGND(pad_pllx2_agnd),
		.AVDD1(pllx2_avdd1),
		.AGND1(pllx2_agnd1)
	);

	// cpu pll power interface;

	AAPLAIOH33 pllpwr_cpu (
		.AVDD(pad_pllc_avdd),
		.AGND(pad_pllc_agnd),
		.AVDD1(pllc_avdd1),
		.AGND1(pllc_agnd1)
	);

	// video pll power interface;

	AAPLSIOH33 pllpwr_v (
		.AVDD(pad_pllv_avdd),
		.AGND(pad_pllv_agnd),
		.AVDD1(pllv_avdd1),
		.AGND1(pllv_agnd1),
		.DVDD1(),
		.DGND1()
	);

	ripad	ripad (
		.reset_l	(reset_l),
		.memclk		(memclk),
		.pad_mclk	(pad_mclk),
		.pad_mcke	(pad_mcke),
		.mcke		(mcke),
		.pad_maddr	(pad_maddr),
		.maddr		(maddr),
		.pad_mbank	(pad_mbank),
		.mbank		(mbank),
		.mdin_ena	(mdin_ena),
		.mdout_ena	(mdout_ena),
		.strobe_rev	(strobe_rev),
		.pad_mdata	(pad_mdata),
		.mdin		(mdin),
		.mdout		(mdout),
		.pad_mras	(pad_mras),
		.mras		(mras),
		.pad_mcas	(pad_mcas),
		.mcas		(mcas),
		.pad_mwe	(pad_mwe),
		.mwe		(mwe),
		.pad_mdqm	(pad_mdqm),
		.mdqm		(mdqm),
		.pad_mdqs	(pad_mdqs)
	);

	// XXX instantiate video clock oscillator;
	// XXX instantiate video pll;
	// XXX for now run video clock input at required speed;

	wire vclk;			// video clock from oscillator;
	wire vclock;		// video clock from pll;

	assign vclk = pad_vclki;
	assign pad_vclko = ~pad_vclki;
	assign vclock = vclk;

	// video output registers;
	// XXX instantiate real io cells;
	// XXX instantiate real io cells;

	reg [6:0] r_vdata;
	reg r_vsync;

	always @(posedge vclock)
	begin
		if(reset_l) begin
			r_vdata <= vdata;
			r_vsync <= vsync;
		end else begin
			r_vdata <= 7'd0;
			r_vsync <= 1'b0;
		end
	end

	assign pad_vclock = vclock;
	assign pad_vdata = r_vdata;
	assign pad_vsync = r_vsync;

	// instantiate triple video dac;

	wire vdac_test;			// vdac test mode;
	wire vdac_bunri;		// vdac test mode;
	wire vdac_mode1;		// vdac test mode;
	wire vdac_mode2;		// vdac test mode;

	assign vdac_test = 0; //XXX
	assign vdac_bunri = 0; //XXX
	assign vdac_mode1 = 0; //XXX
	assign vdac_mode2 = 0; //XXX

	AAD3835BM vdac (
		.CLKA(vdac_clk),
		.CLKB(vdac_clk),
		.CLKC(vdac_clk),
		.DA(vda),
		.DB(vdb),
		.DC(vdc),
		.VOA(pad_voa),
		.VOB(pad_vob),
		.VOC(pad_voc),
		.PDB(vdac_pd),
		.MODE1(vdac_mode1),
		.MODE2(vdac_mode2),
		.BUNRI(vdac_bunri),		// test mode;
		.TEST(vdac_test),		// normal mode;
		.TBI(),					// test bus inputs;
		.ATBO()					// test bus outputs;
	);

	// XXX instantiate real io cells;

	assign pad_aclock = aclock;
	assign pad_adata = adata;
	assign pad_aword = aword;

	// power button;
	// XXX instantiate io buffer;

	assign button = pad_button;

	// joy channel ports;
	// XXX instantiate real io cells;

	assign pad_jchan[1] = jchan_oe[1]? 'b0 : 'bz;
	assign pad_jchan[2] = jchan_oe[2]? 'b0 : 'bz;
	assign pad_jchan[3] = jchan_oe[3]? 'b0 : 'bz;

	// local joystick;
	// XXX instantiate real io cells;

	assign lctrl_x = pad_lx;
	assign lctrl_y = pad_ly;

	// XXX instantiate flop with clock enable;

	reg [3:1] jchan_in;

	always @(posedge sysclk)
	begin
		if(jchan_ena[1])
			jchan_in[1] <= pad_jchan[1];
		if(jchan_ena[2])
			jchan_in[2] <= pad_jchan[2];
		if(jchan_ena[3])
			jchan_in[3] <= pad_jchan[3];
	end

	// XXX instantiate io registers;

	reg [15:0] io_in;			// io bus input register;
	reg [15:0] rio_out;			// io bus output register;
	reg [1:0] rio_oe;			// registered output enables;
	reg rio_rst;				// rst output register;
	reg rio_ale;				// ale output register;
	reg [3:0] rio_cs;			// cs output registers;
	reg rio_ior;				// ior output register;
	reg rio_iow;				// iow output register;
	reg io_dmarq;				// dmarq input register;
	reg rio_dmack;				// dmack output register;
	reg io_intr;				// io interrupt input register;

	always @(posedge sysclk)
	begin
		if(io_ena)
			io_in <= pad_io_ad;		// flop with clock enable;
		rio_out <= io_out;
		rio_oe <= io_oe;
		rio_rst <= ~io_rst;
		rio_ale <= io_ale;
		rio_cs <= ~io_cs;
		rio_ior <= ~io_ior;
		rio_iow <= ~io_iow;
		rio_dmack <= ~io_dmack;
		io_dmarq <= pad_io_dmarq; //XXX synchronizer;
		io_intr <= pad_io_intr; //XXX synchronizer;
	end

	assign pad_io_ad[15:8] = rio_oe[1]? rio_out[15:8] : 8'bz;
	assign pad_io_ad[7:0] = rio_oe[0]? rio_out[7:0] : 8'bz;

	assign pad_io_rst = rio_rst;
	assign pad_io_ale = rio_ale;
	assign pad_io_cs = rio_cs;
	assign pad_io_ior = rio_ior;
	assign pad_io_iow = rio_iow;
	assign pad_io_dmack = rio_dmack;

	// XXX instantiate io registers;
	// XXX instantiate io buffers;

	reg [3:0] rfl_ce;	// ce output register;
	reg rfl_cle;		// cle output register;
	reg rfl_ale;		// ale output register;
	reg rfl_we;			// we output register;
	reg rfl_re;			// re output register;
	reg rfl_wp;			// wp output register;
	reg rfl_ryby;		// ryby input register;
	reg rfl_md;			// md input register;

	always @(posedge sysclk)
	begin
		rfl_ce <= ~fl_ce;
		rfl_cle <= fl_cle;
		rfl_ale <= fl_ale;
		rfl_we <= ~fl_we;
		rfl_re <= ~fl_re;
		rfl_wp <= ~fl_wp;
		rfl_ryby <= pad_fl_ryby;
		rfl_md <= pad_fl_md;
	end

	assign pad_fl_ce = rfl_ce;
	assign pad_fl_ale = rfl_ale;
	assign pad_fl_cle = rfl_cle;
	assign pad_fl_re = rfl_re;
	assign pad_fl_we = rfl_we;
	assign pad_fl_wp = rfl_wp;
	assign fl_ryby = rfl_ryby;
	assign fl_md = rfl_md;

	// XXX instantiate io registers;
	// XXX instantiate io buffers;

	reg [3:0] rgpio_oe;		// output enables;
	reg [3:0] rgpio_out;	// output register;

	always @(posedge sysclk)
	begin
		rgpio_oe <= gpio_oe;
		rgpio_out <= gpio_out;
	end

	assign pad_gpio[0] = rgpio_oe[0]? rgpio_out[0] : 1'bz;
	assign pad_gpio[1] = rgpio_oe[1]? rgpio_out[1] : 1'bz;
	assign pad_gpio[2] = rgpio_oe[2]? rgpio_out[2] : 1'bz;
	assign pad_gpio[3] = rgpio_oe[3]? rgpio_out[3] : 1'bz;

	assign gpio_in = pad_gpio;

	// instantiate usb tranceivers;

	usb_xcvr usb_xcvr0 (
		.usb_dpo(usb_dpo[0]),
		.usbxr_ose(usbxr_ose[0]),
		.usbxr_oen(usbxr_oen[0]),
		.usbxr_ien(usbxr_ien[0]),
		.usbxr_fl(usbxr_fl[0]),
		
		.usbxr_y1(usbxr_y1[0]),
		.usb_dp(usb_dp[0]),
		.usb_dm(usb_dm[0]),
		
		.dp_o(pad_usb_dplus[0]),
		.dm_o(pad_usb_dminus[0]) 
	);

	usb_xcvr usb_xcvr1 (
		.usb_dpo(usb_dpo[1]),
		.usbxr_ose(usbxr_ose[1]),
		.usbxr_oen(usbxr_oen[1]),
		.usbxr_ien(usbxr_ien[1]),
		.usbxr_fl(usbxr_fl[1]),
		
		.usbxr_y1(usbxr_y1[1]),
		.usb_dp(usb_dp[1]),
		.usb_dm(usb_dm[1]),
		
		.dp_o(pad_usb_dplus[1]),
		.dm_o(pad_usb_dminus[1]) 
	);

	 	// XXXX buffer here later
	assign usb_id = pad_usb_id;
	assign pad_usb_vbus_on_n = usb_vbus_on_n;
	assign pad_usb_dm_high = usb_dm_high;
	assign pad_usb_dp_high = usb_dp_high;

	assign trst = pad_trst;
	assign tdi = pad_tdi;
	assign tms = pad_tms;
	assign tck = pad_tck;
	assign pad_tdo = tdoen ? tdo : 1'bz ;


endmodule

