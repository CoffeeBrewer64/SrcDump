
`timescale 1ns/1ns

module nec_bbpad (
	PAD_RST_L, rst_l, reset_l,
	PAD_SYSCLK, sysclk, memclk,
	PAD_USBCLKI, PAD_USBCLKO, usbclk,
	PAD_VCLKI, PAD_VCLKO, vclk,
	PAD_BUTTON, button,
	PAD_VCLOCK, vclock,
	PAD_VDATA6, PAD_VDATA5, PAD_VDATA4, PAD_VDATA3,
	PAD_VDATA2, PAD_VDATA1, PAD_VDATA0, vdata,
	PAD_VSYNC, vsync,
	vdac_clk, vdac_pd,
	PAD_VOA, vda,
	PAD_VOB, vdb,
	PAD_VOC, vdc,
	PAD_ACLOCK, aclock,
	PAD_ADATA, adata,
	PAD_AWORD, aword,
	PAD_JCHAN3, PAD_JCHAN2, PAD_JCHAN1, jchan_in, jchan_ena, jchan_oe,
	PAD_LX0, PAD_LX1, lctrl_x,
	PAD_LY0, PAD_LY1, lctrl_y,
	PAD_IO_RST, io_rst,
	PAD_IO_AD15,PAD_IO_AD14,PAD_IO_AD13,PAD_IO_AD12,PAD_IO_AD11,PAD_IO_AD10,
	PAD_IO_AD9, PAD_IO_AD8, PAD_IO_AD7, PAD_IO_AD6, PAD_IO_AD5, PAD_IO_AD4,
	PAD_IO_AD3, PAD_IO_AD2, PAD_IO_AD1, PAD_IO_AD0, 
	io_in, io_ena, io_out, io_oe,
	PAD_IO_ALE, io_ale,
	PAD_IO_CS3, PAD_IO_CS2, PAD_IO_CS1, PAD_IO_CS0, io_cs,
	PAD_IO_IOR, io_ior,
	PAD_IO_IOW, io_iow,
	pad_io_dmarq, io_dmarq,
	pad_io_dmack, io_dmack,
	PAD_IO_INTR, io_intr,
	PAD_FL_CE3, PAD_FL_CE2, PAD_FL_CE1, PAD_FL_CE0, fl_ce,
	PAD_FL_ALE, fl_ale,
	PAD_FL_CLE, fl_cle,
	PAD_FL_RE, fl_re,
	PAD_FL_WE, fl_we,
	PAD_FL_WP, fl_wp,
	PAD_FL_RYBY, fl_ryby,
	PAD_FL_MD, fl_md,
	PAD_GPIO3, PAD_GPIO2, PAD_GPIO1, PAD_GPIO0, gpio_oe, gpio_out, gpio_in,
	PAD_MCLKN, PAD_MCLK,
	PAD_MCKE, mcke,
	PAD_MADDR12,PAD_MADDR11,PAD_MADDR10,PAD_MADDR9, PAD_MADDR8, PAD_MADDR7,
	PAD_MADDR6, PAD_MADDR5, PAD_MADDR4, PAD_MADDR3, PAD_MADDR2, PAD_MADDR1, 
	PAD_MADDR0, maddr,
	PAD_MBANK0, PAD_MBANK1, mbank,
	mdin_ena,
	mdout_ena,
	strobe_rev,
	PAD_MDATA31,PAD_MDATA30,PAD_MDATA29,PAD_MDATA28,PAD_MDATA27,PAD_MDATA26,
	PAD_MDATA25,PAD_MDATA24,PAD_MDATA23,PAD_MDATA22,PAD_MDATA21,PAD_MDATA20,
	PAD_MDATA19,PAD_MDATA18,PAD_MDATA17,PAD_MDATA16,PAD_MDATA15,PAD_MDATA14,
	PAD_MDATA13,PAD_MDATA12,PAD_MDATA11,PAD_MDATA10,PAD_MDATA9, PAD_MDATA8,
	PAD_MDATA7, PAD_MDATA6, PAD_MDATA5, PAD_MDATA4, PAD_MDATA3, PAD_MDATA2,
	PAD_MDATA1, PAD_MDATA0,
	mdin, mdout,
	PAD_MRAS, mras,
	PAD_MCAS, mcas,
	PAD_MWE, mwe,
	PAD_MDQM3, PAD_MDQM2, PAD_MDQM1, PAD_MDQM0, mdqm,
	PAD_MDQS3, PAD_MDQS2, PAD_MDQS1, PAD_MDQS0, 
	PAD_USB_DMINUS0, PAD_USB_DMINUS1, usb_dm, usbxr_ose,
	PAD_USB_DPLUS0,  PAD_USB_DPLUS1,  usb_dp, usb_dpo, 
	usbxr_y1, usbxr_oen, usbxr_ien, usbxr_fl,
	PAD_USB_DP_HIGH0, PAD_USB_DP_HIGH1, usb_dp_high,
	PAD_USB_DM_HIGH0, PAD_USB_DM_HIGH1, usb_dm_high,
	PAD_USB_ID0, PAD_USB_ID1, usb_id,
	PAD_USB_VBUS_ON_N0, PAD_USB_VBUS_ON_N1, usb_vbus_on_n,
	PAD_TRST, trst,
	PAD_TDI, tdi,
	PAD_TMS, tms,
	PAD_TCK, tck,
	tdoen,
	PAD_TDO, tdo ,
	PAD_PLLX2_AVDD, PAD_PLLX2_AGND, pllx2_lock, 
	PAD_PLLC_AVDD,  PAD_PLLC_AGND, pllc_avdd1, pllc_agnd1,
	PAD_PLLV_AVDD,  PAD_PLLV_AGND
	);

//*****************************************************************************
// Port Declarations
//*****************************************************************************

	// io pads;

	input PAD_RST_L;			// chip reset input;
	output rst_l;				// chip reset;
	input reset_l;				// system reset for pad logic;
	input PAD_SYSCLK;			// system clock input pin;
	output sysclk;				// system clock;
	output memclk;				// memory clock;
	input PAD_USBCLKI;			// usb clock input pin;
	output PAD_USBCLKO;			// usb clock output pin;
	output usbclk;				// usb clock from oscillator;
	input PAD_VCLKI;			// video clock input pin;
	output PAD_VCLKO;			// video clock output pin;
	output vclk;				// video clock from oscillator;
	input PAD_BUTTON;			// button pin;
	output button;				// output of input buffer;

	output PAD_VCLOCK;			// video clock pin;
	output vclock;				// generated video clock to vi;
	
	output PAD_VDATA6;			// video data
	output PAD_VDATA5;			// video data
	output PAD_VDATA4;			// video data
	output PAD_VDATA3;			// video data
	output PAD_VDATA2;			// video data
	output PAD_VDATA1;			// video data
	output PAD_VDATA0;			// video data
	input [6:0] vdata;			// video data;
	output PAD_VSYNC;			// video sync pin;
	input vsync;				// video sync;
	input vdac_clk;				// video dac clock;
	input vdac_pd;				// video dac power-down;
	output PAD_VOA;				// analog video; chroma;
	input [7:0] vda;			// dac data chroma;
	output PAD_VOB;				// analog video; composite;
	input [7:0] vdb;			// dac data composite;
	output PAD_VOC;				// analog video; luminance;
	input [7:0] vdc;			// dac data luminance;

	output PAD_ACLOCK;			// audio clock pin;
	input aclock;				// audio clock;
	output PAD_ADATA;			// audio data pin;
	input adata;				// audio data;
	output PAD_AWORD;			// audio word clock pin;
	input aword;				// audio word clock;

	inout PAD_JCHAN3;		// joy channel
	inout PAD_JCHAN2;		// joy channel
	inout PAD_JCHAN1;		// joy channel
	output [3:1] jchan_in;	// output of input register;
	input [3:1] jchan_ena;	// input register clock enable;
	input [3:1] jchan_oe;	// drive 0 on jchan;

	input PAD_LX0;			// stick x
	input PAD_LX1;			// stick x
	output [1:0] lctrl_x;	// output of input buffer;
	input PAD_LY0;			// stick y
	input PAD_LY1;			// stick y
	output [1:0] lctrl_y;	// output of input buffer;

	output PAD_IO_RST;		// io bus reset pin;
	input io_rst;			// io bus reset;
	inout PAD_IO_AD15;		// io data bus 
	inout PAD_IO_AD14;		// io data bus 
	inout PAD_IO_AD13;		// io data bus 
	inout PAD_IO_AD12;		// io data bus 
	inout PAD_IO_AD11;		// io data bus 
	inout PAD_IO_AD10;		// io data bus 
	inout PAD_IO_AD9;		// io data bus 
	inout PAD_IO_AD8;		// io data bus 
	inout PAD_IO_AD7;		// io data bus 
	inout PAD_IO_AD6;		// io data bus 
	inout PAD_IO_AD5;		// io data bus 
	inout PAD_IO_AD4;		// io data bus 
	inout PAD_IO_AD3;		// io data bus 
	inout PAD_IO_AD2;		// io data bus 
	inout PAD_IO_AD1;		// io data bus 
	inout PAD_IO_AD0;		// io data bus 
	output [15:0] io_in;	// io input data;
	input io_ena;			// io input clock enables;
	input [15:0] io_out;	// io output data;
	input [1:0] io_oe;		// io data output enables;
	output PAD_IO_ALE;		// io address latch enable pin;
	input io_ale;			// io address latch enable;
	output PAD_IO_CS3;		// io pio chip select
	output PAD_IO_CS2;		// io pio chip select
	output PAD_IO_CS1;		// io pio chip select
	output PAD_IO_CS0;		// io pio chip select
	input [3:0] io_cs;		// io pio chip selects;
	output PAD_IO_IOR;		// io read pulse pin;
	input io_ior;			// io read pulse;
	output PAD_IO_IOW;		// io write pulse pin;
	input io_iow;			// io write pulse;
	input pad_io_dmarq;		// io dma request pin;
	output io_dmarq;		// io dma request;
	output pad_io_dmack;	// io dma acknowledge pin;
	input io_dmack;			// io dma acknowledge;
	input PAD_IO_INTR;		// io device interrupt pin;
	output io_intr;			// io device interrupt;

	output PAD_FL_CE3;		// flash chip select
	output PAD_FL_CE2;		// flash chip select
	output PAD_FL_CE1;		// flash chip select
	output PAD_FL_CE0;		// flash chip select
	input [3:0] fl_ce;		// chip enables pin;
	output PAD_FL_ALE;		// address latch enable pin;
	input fl_ale;			// address latch enable pin;
	output PAD_FL_CLE;		// command latch enable pin;
	input fl_cle;			// command latch enable pin;
	output PAD_FL_RE;		// read eanble pin;
	input fl_re;			// read eanble pin;
	output PAD_FL_WE;		// write eanble pin;
	input fl_we;			// write eanble pin;
	output PAD_FL_WP;		// write protect pin;
	input fl_wp;			// write protect pin;
	input PAD_FL_RYBY;		// ready/busy pin;
	output fl_ryby;			// ready/busy pin;
	input PAD_FL_MD;		// module detect pin;
	output fl_md;			// module detect;

	inout PAD_GPIO3;		// gpio 
	inout PAD_GPIO2;		// gpio 
	inout PAD_GPIO1;		// gpio 
	inout PAD_GPIO0;		// gpio 
	input [3:0] gpio_oe;	// output enables;
	input [3:0] gpio_out;	// output values;
	output [3:0] gpio_in;	// input values;

	output PAD_MCLKN;
	output PAD_MCLK;
	output PAD_MCKE;
	input			mcke;
	output PAD_MADDR12;
	output PAD_MADDR11;
	output PAD_MADDR10;
	output PAD_MADDR9;
	output PAD_MADDR8;
	output PAD_MADDR7;
	output PAD_MADDR6;
	output PAD_MADDR5;
	output PAD_MADDR4;
	output PAD_MADDR3;
	output PAD_MADDR2;
	output PAD_MADDR1;
	output PAD_MADDR0;
	input	[12:0]	maddr;
	output PAD_MBANK0;
	output PAD_MBANK1;
	input	[1:0]	mbank;
	input			mdin_ena;
	input			mdout_ena;
	input			strobe_rev;
	inout PAD_MDATA31;
	inout PAD_MDATA30;
	inout PAD_MDATA29;
	inout PAD_MDATA28;
	inout PAD_MDATA27;
	inout PAD_MDATA26;
	inout PAD_MDATA25;
	inout PAD_MDATA24;
	inout PAD_MDATA23;
	inout PAD_MDATA22;
	inout PAD_MDATA21;
	inout PAD_MDATA20;
	inout PAD_MDATA19;
	inout PAD_MDATA18;
	inout PAD_MDATA17;
	inout PAD_MDATA16;
	inout PAD_MDATA15;
	inout PAD_MDATA14;
	inout PAD_MDATA13;
	inout PAD_MDATA12;
	inout PAD_MDATA11;
	inout PAD_MDATA10;
	inout PAD_MDATA9;
	inout PAD_MDATA8;
	inout PAD_MDATA7;
	inout PAD_MDATA6;
	inout PAD_MDATA5;
	inout PAD_MDATA4;
	inout PAD_MDATA3;
	inout PAD_MDATA2;
	inout PAD_MDATA1;
	inout PAD_MDATA0;
	output	[63:0]	mdin;
	input	[63:0]	mdout;
	output PAD_MRAS;
	input		mras;
	output PAD_MCAS;
	input		mcas;
	output PAD_MWE;
	input		mwe;
	output PAD_MDQM3;
	output PAD_MDQM2;
	output PAD_MDQM1;
	output PAD_MDQM0;
	input	[7:0]	mdqm;
	inout PAD_MDQS3;
	inout PAD_MDQS2;
	inout PAD_MDQS1;
	inout PAD_MDQS0;

	// usb signals
	
	inout PAD_USB_DMINUS0;
	inout PAD_USB_DMINUS1;
	input   [1:0] usbxr_ose;
	output  [1:0] usb_dm;
	
	inout PAD_USB_DPLUS0;
	inout PAD_USB_DPLUS1;
	input   [1:0] usb_dpo;
	output  [1:0] usb_dp;

	output  [1:0] usbxr_y1;			  // xcvr side signals	
	input   [1:0] usbxr_oen;
	input   [1:0] usbxr_ien;
	input   [1:0] usbxr_fl;

	output PAD_USB_DP_HIGH0;
	output PAD_USB_DP_HIGH1;
	input   [1:0] usb_dp_high; 		  // pull up 
	output PAD_USB_DM_HIGH0;
	output PAD_USB_DM_HIGH1;
	input   [1:0] usb_dm_high;	 	  // pull down

	input PAD_USB_ID0;
	input PAD_USB_ID1;
	output  [1:0] usb_id;
	output PAD_USB_VBUS_ON_N0;
	output PAD_USB_VBUS_ON_N1;
	input   [1:0] usb_vbus_on_n;

	// JTAG
	output trst;
	input PAD_TRST;
	output tdi;
	input PAD_TDI;
	output tms;
	input PAD_TMS;
	output tck;
	input PAD_TCK;
	input tdoen;
	input tdo;
	output PAD_TDO;


	input PAD_PLLX2_AVDD;           	// x2 pll analog power pin;
        input PAD_PLLX2_AGND;           // x2 pll analog ground pin;
        input PAD_PLLC_AVDD;            // cpu pll analog power pin;
	output pllx2_lock;					// x2 pll lock signal
        output pllc_avdd1;              // cpu pll analog power;
        input PAD_PLLC_AGND;            // cpu pll analog ground pin;
        output pllc_agnd1;              // cpu pll analog ground;
        input PAD_PLLV_AVDD;            // video pll analog power pin;
        input PAD_PLLV_AGND;            // video pll analog ground pin;

//*****************************************************************************
// Net Assignments and Declarations
//*****************************************************************************

	// clock input buffer;

	TBCTSRS pad_ac5 (
		.H01		(PAD_RST_L),
		.N01		(rst_l)
		);

	TBCTS pad_ad20 (
		.H01		(PAD_SYSCLK),
		.N01		(sysclk)
		);

	// button input buffer

	TDIPAC33N pad_ac11 (
		.H01		(PAD_BUTTON),
		.N01		(button)
		);

	assign usbclk = PAD_USBCLKI;

	// instantiate x2 pll;
	// creates ddr clock x2, and aligns memclk with sysclk;
	// vco runs from 250...400Mhz (sysclk 62.5...100);

	wire pllx2_m;				// M divider;
	wire [3:0] pllx2_n;			// N divider;
	wire [3:0] pllx2_pa;		// PA divider;
	wire [3:0] pllx2_pb;		// PB divider;
	wire [3:0] pllx2_pc;		// PC divider;
	wire [2:0] pllx2_stby;		// standby controls;
	wire pllx2_lock;			// x2 pll is locked;
	wire pllx2_clk;				// x2 clock output;
	wire pllx2_mode;			// test mode;
	wire pllx2_atbi0;			// test mode;
	wire pllx2_test;			// test mode;
	wire pllx2_bunri;			// test mode;
	wire pllx2_avdd1;			// pll analog power
	wire pllx2_agnd1;			// pll analog ground

	assign pllx2_m = 1;				// rclk / 2 = 31.25...50Mhz;
	assign pllx2_n = 4'd3;			// vco / pa / 4 = 31.25...50Mhz;
	assign pllx2_pa = 4'd1;			// clk A = vco / 2;
	assign pllx2_pb = 4'd1;			// clk B = vco / 2;
	assign pllx2_pc = 4'd1;			// clk C = vco / 2;
	assign pllx2_stby[0] = ~rst_l;	// XXX
	assign pllx2_stby[1] = 1'b0;	// turn off port B;
	assign pllx2_stby[2] = 1'b0;	// turn off port C;
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
 
        wire pllv_avdd1;                        // pll analog power;
        wire pllv_agnd1;                        // pll analog ground;
 
        // ddr pll power interface;                            

	AAPLAIOH33 pad_j23_j22 (
		.AVDD		(PAD_PLLX2_AVDD),
		.AGND		(PAD_PLLX2_AGND),
		.AVDD1		(pllx2_avdd1),
		.AGND1		(pllx2_agnd1)
		);                           

 // cpu pll power interface;
 
	AAPLAIOH33 pad_ac20_ac21 (
		.AVDD		(PAD_PLLC_AVDD),
		.AGND		(PAD_PLLC_AGND),
		.AVDD1		(pllc_avdd1),
		.AGND1		(pllc_agnd1)
		);            

    // video pll power interface;
 
	AAPLSIOH33 pad_k23_k22 (
		.AVDD		(PAD_PLLV_AVDD),
		.AGND		(PAD_PLLV_AGND),
		.AVDD1		(pllv_avdd1),
		.AGND1		(pllv_agnd1),
		.DVDD1		(),
		.DGND1		()
		);              

	// XXX ddr io cells and registers;

	wire	memclk_b = ~memclk;

TDBIAST2NNC1 pad_b23 (
	.H01		(memclk),
	.H02		(nring_enl),
	.H04		(1'b1),
	.N01		(PAD_MCLK),
	.N02		(nring_b23)
	);

TDBIAST2NNC1 pad_a23 (
	.H01		(memclk_b),
	.H02		(nring_enl),
	.H04		(1'b1),
	.N01		(PAD_MCLKN),
	.N02		(nring_a23)
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

TDBIAST2NNC1 pad_a12 (
	.H01		(strobe_out[0]),
	.H02		(pad_moe[8]),
	.H04		(1'b1),
	.N01		(PAD_MDQS0),
	.N02		(strobe_in)
	);

TDBIAST2NNC1 pad_b12 (
	.H01		(strobe_out[1]),
	.H02		(pad_moe[8]),
	.H04		(1'b1),
	.N01		(PAD_MDQS1),
	.N02		(nring_b12)
	);

TDBIAST2NNC1 pad_b13 (
	.H01		(strobe_out[2]),
	.H02		(pad_moe[8]),
	.H04		(1'b1),
	.N01		(PAD_MDQS2),
	.N02		(nring_b13)
	);

TDBIAST2NNC1 pad_a13 (
	.H01		(strobe_out[3]),
	.H02		(pad_moe[8]),
	.H04		(1'b1),
	.N01		(PAD_MDQS3),
	.N02		(nring_a13)
	);


	wire	[31:0]	pad_mdata_in;
	wire	[31:0]	data_out;

//	assign		pad_mdata = pad_moe ? data_out : {32{1'bz}};

TDBIAST2NNC1 pad_a2 (
	.H01		(data_out[0]),
	.H02		(pad_moe[0]),
	.H04		(1'b1),
	.N01		(PAD_MDATA0),
	.N02		(pad_mdata_in[0])
	);

TDBIAST2NNC1 pad_b3 (
	.H01		(data_out[1]),
	.H02		(pad_moe[0]),
	.H04		(1'b1),
	.N01		(PAD_MDATA1),
	.N02		(pad_mdata_in[1])
	);

TDBIAST2NNC1 pad_a3 (
	.H01		(data_out[2]),
	.H02		(pad_moe[0]),
	.H04		(1'b1),
	.N01		(PAD_MDATA2),
	.N02		(pad_mdata_in[2])
	);

TDBIAST2NNC1 pad_a4 (
	.H01		(data_out[3]),
	.H02		(pad_moe[0]),
	.H04		(1'b1),
	.N01		(PAD_MDATA3),
	.N02		(pad_mdata_in[3])
	);

TDBIAST2NNC1 pad_b5 (
	.H01		(data_out[4]),
	.H02		(pad_moe[1]),
	.H04		(1'b1),
	.N01		(PAD_MDATA4),
	.N02		(pad_mdata_in[4])
	);

TDBIAST2NNC1 pad_a5 (
	.H01		(data_out[5]),
	.H02		(pad_moe[1]),
	.H04		(1'b1),
	.N01		(PAD_MDATA5),
	.N02		(pad_mdata_in[5])
	);

TDBIAST2NNC1 pad_b6 (
	.H01		(data_out[6]),
	.H02		(pad_moe[1]),
	.H04		(1'b1),
	.N01		(PAD_MDATA6),
	.N02		(pad_mdata_in[6])
	);

TDBIAST2NNC1 pad_a6 (
	.H01		(data_out[7]),
	.H02		(pad_moe[1]),
	.H04		(1'b1),
	.N01		(PAD_MDATA7),
	.N02		(pad_mdata_in[7])
	);

TDBIAST2NNC1 pad_a22 (
	.H01		(data_out[8]),
	.H02		(pad_moe[2]),
	.H04		(1'b1),
	.N01		(PAD_MDATA8),
	.N02		(pad_mdata_in[8])
	);

TDBIAST2NNC1 pad_b22 (
	.H01		(data_out[9]),
	.H02		(pad_moe[2]),
	.H04		(1'b1),
	.N01		(PAD_MDATA9),
	.N02		(pad_mdata_in[9])
	);

TDBIAST2NNC1 pad_a21 (
	.H01		(data_out[10]),
	.H02		(pad_moe[2]),
	.H04		(1'b1),
	.N01		(PAD_MDATA10),
	.N02		(pad_mdata_in[10])
	);

TDBIAST2NNC1 pad_b21 (
	.H01		(data_out[11]),
	.H02		(pad_moe[2]),
	.H04		(1'b1),
	.N01		(PAD_MDATA11),
	.N02		(pad_mdata_in[11])
	);

TDBIAST2NNC1 pad_a20 (
	.H01		(data_out[12]),
	.H02		(pad_moe[3]),
	.H04		(1'b1),
	.N01		(PAD_MDATA12),
	.N02		(pad_mdata_in[12])
	);

TDBIAST2NNC1 pad_b20 (
	.H01		(data_out[13]),
	.H02		(pad_moe[3]),
	.H04		(1'b1),
	.N01		(PAD_MDATA13),
	.N02		(pad_mdata_in[13])
	);

TDBIAST2NNC1 pad_a19 (
	.H01		(data_out[14]),
	.H02		(pad_moe[3]),
	.H04		(1'b1),
	.N01		(PAD_MDATA14),
	.N02		(pad_mdata_in[14])
	);

TDBIAST2NNC1 pad_a18 (
	.H01		(data_out[15]),
	.H02		(pad_moe[3]),
	.H04		(1'b1),
	.N01		(PAD_MDATA15),
	.N02		(pad_mdata_in[15])
	);

TDBIAST2NNC1 pad_b7 (
	.H01		(data_out[16]),
	.H02		(pad_moe[4]),
	.H04		(1'b1),
	.N01		(PAD_MDATA16),
	.N02		(pad_mdata_in[16])
	);

TDBIAST2NNC1 pad_a7 (
	.H01		(data_out[17]),
	.H02		(pad_moe[4]),
	.H04		(1'b1),
	.N01		(PAD_MDATA17),
	.N02		(pad_mdata_in[17])
	);

TDBIAST2NNC1 pad_a8 (
	.H01		(data_out[18]),
	.H02		(pad_moe[4]),
	.H04		(1'b1),
	.N01		(PAD_MDATA18),
	.N02		(pad_mdata_in[18])
	);

TDBIAST2NNC1 pad_b9 (
	.H01		(data_out[19]),
	.H02		(pad_moe[4]),
	.H04		(1'b1),
	.N01		(PAD_MDATA19),
	.N02		(pad_mdata_in[19])
	);

TDBIAST2NNC1 pad_a9 (
	.H01		(data_out[20]),
	.H02		(pad_moe[5]),
	.H04		(1'b1),
	.N01		(PAD_MDATA20),
	.N02		(pad_mdata_in[20])
	);

TDBIAST2NNC1 pad_b10 (
	.H01		(data_out[21]),
	.H02		(pad_moe[5]),
	.H04		(1'b1),
	.N01		(PAD_MDATA21),
	.N02		(pad_mdata_in[21])
	);

TDBIAST2NNC1 pad_a10 (
	.H01		(data_out[22]),
	.H02		(pad_moe[5]),
	.H04		(1'b1),
	.N01		(PAD_MDATA22),
	.N02		(pad_mdata_in[22])
	);

TDBIAST2NNC1 pad_a11 (
	.H01		(data_out[23]),
	.H02		(pad_moe[5]),
	.H04		(1'b1),
	.N01		(PAD_MDATA23),
	.N02		(pad_mdata_in[23])
	);

TDBIAST2NNC1 pad_b18 (
	.H01		(data_out[24]),
	.H02		(pad_moe[6]),
	.H04		(1'b1),
	.N01		(PAD_MDATA24),
	.N02		(pad_mdata_in[24])
	);

TDBIAST2NNC1 pad_a17 (
	.H01		(data_out[25]),
	.H02		(pad_moe[6]),
	.H04		(1'b1),
	.N01		(PAD_MDATA25),
	.N02		(pad_mdata_in[25])
	);

TDBIAST2NNC1 pad_b17 (
	.H01		(data_out[26]),
	.H02		(pad_moe[6]),
	.H04		(1'b1),
	.N01		(PAD_MDATA26),
	.N02		(pad_mdata_in[26])
	);

TDBIAST2NNC1 pad_a16 (
	.H01		(data_out[27]),
	.H02		(pad_moe[6]),
	.H04		(1'b1),
	.N01		(PAD_MDATA27),
	.N02		(pad_mdata_in[27])
	);

TDBIAST2NNC1 pad_b16 (
	.H01		(data_out[28]),
	.H02		(pad_moe[7]),
	.H04		(1'b1),
	.N01		(PAD_MDATA28),
	.N02		(pad_mdata_in[28])
	);

TDBIAST2NNC1 pad_a15 (
	.H01		(data_out[29]),
	.H02		(pad_moe[7]),
	.H04		(1'b1),
	.N01		(PAD_MDATA29),
	.N02		(pad_mdata_in[29])
	);

TDBIAST2NNC1 pad_a14 (
	.H01		(data_out[30]),
	.H02		(pad_moe[7]),
	.H04		(1'b1),
	.N01		(PAD_MDATA30),
	.N02		(pad_mdata_in[30])
	);

TDBIAST2NNC1 pad_b14 (
	.H01		(data_out[31]),
	.H02		(pad_moe[7]),
	.H04		(1'b1),
	.N01		(PAD_MDATA31),
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

TDBIAST2NNC1 pad_g1 (
	.H01		(mras_out),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MRAS),
	.N02		(nring_g1)
	);

TDBIAST2NNC1 pad_f1 (
	.H01		(mcas_out),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MCAS),
	.N02		(nring_f1)
	);

TDBIAST2NNC1 pad_g2 (
	.H01		(mwe_out),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MWE),
	.N02		(nring_g2)
	);

TDBIAST2NNC1 pad_e1 (
	.H01		(mbank_out[0]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MBANK0),
	.N02		(nring_e1)
	);

TDBIAST2NNC1 pad_d2 (
	.H01		(mbank_out[1]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MBANK1),
	.N02		(nring_d2)
	);

	wire	rmcke_out = mcke_out & reset_l;

TDBIAST2NNC1 pad_g23 (
	.H01		(rmcke_out),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MCKE),
	.N02		(nring_g23)
	);

TDBIAST2NNC1 pad_d1 (
	.H01		(maddr_out[0]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR0),
	.N02		(nring_d1)
	);

TDBIAST2NNC1 pad_c2 (
	.H01		(maddr_out[1]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR1),
	.N02		(nring_c2)
	);

TDBIAST2NNC1 pad_c1 (
	.H01		(maddr_out[2]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR2),
	.N02		(nring_c1)
	);

TDBIAST2NNC1 pad_b1 (
	.H01		(maddr_out[3]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR3),
	.N02		(nring_b1)
	);

TDBIAST2NNC1 pad_d23 (
	.H01		(maddr_out[4]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR4),
	.N02		(nring_d23)
	);

TDBIAST2NNC1 pad_d22 (
	.H01		(maddr_out[5]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR5),
	.N02		(nring_d22)
	);

TDBIAST2NNC1 pad_e23 (
	.H01		(maddr_out[6]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR6),
	.N02		(nring_e23)
	);

TDBIAST2NNC1 pad_f23 (
	.H01		(maddr_out[7]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR7),
	.N02		(nring_f23)
	);

TDBIAST2NNC1 pad_f22 (
	.H01		(maddr_out[8]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR8),
	.N02		(nring_f22)
	);

TDBIAST2NNC1 pad_c23 (
	.H01		(maddr_out[9]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR9),
	.N02		(nring_c23)
	);

TDBIAST2NNC1 pad_b2 (
	.H01		(maddr_out[10]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR10),
	.N02		(nring_b2)
	);

TDBIAST2NNC1 pad_a1 (
	.H01		(maddr_out[11]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR11),
	.N02		(nring_a1)
	);

TDBIAST2NNC1 pad_c22 (
	.H01		(maddr_out[12]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MADDR12),
	.N02		(nring_c22)
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

TDBIAST2NNC1 pad_h2 (
	.H01		(mdqm_out[0]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MDQM0),
	.N02		(nring_h2)
	);

TDBIAST2NNC1 pad_g22 (
	.H01		(mdqm_out[1]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MDQM1),
	.N02		(nring_g22)
	);

TDBIAST2NNC1 pad_h1 (
	.H01		(mdqm_out[2]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MDQM2),
	.N02		(nring_h1)
	);

TDBIAST2NNC1 pad_h22 (
	.H01		(mdqm_out[3]),
	.H02		(1'b1),
	.H04		(1'b1),
	.N01		(PAD_MDQM3),
	.N01		(nring_h22)
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

	// XXX instantiate video clock oscillator;
	// XXX instantiate video pll;
	// XXX for now run video clock input at required speed;

	wire vclk;			// video clock from oscillator;
	wire vclock;		// video clock from pll;

	assign vclk = PAD_VCLKI;
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

	assign PAD_VCLOCK = vclock;

	TDBIAC33NL03 pad_r22 (
		.N01		(PAD_VDATA0),
		.N02		(nring_r22),
		.H01		(r_vdata[0]),
		.H03		(nring_enl)
		);

	TDBIAC33NL03 pad_p22 (
		.N01		(PAD_VDATA1),
		.N02		(nring_p22),
		.H01		(r_vdata[1]),
		.H03		(nring_enl)
		);

	TDBIAC33NL03 pad_r23 (
		.N01		(PAD_VDATA2),
		.N02		(nring_r23),
		.H01		(r_vdata[2]),
		.H03		(nring_enl)
		);

	TDBIAC33NL03 pad_n22 (
		.N01		(PAD_VDATA3),
		.N02		(nring_n22),
		.H01		(r_vdata[3]),
		.H03		(nring_enl)
	 	);

	TDBIAC33NL03 pad_p23 (
		.N01		(PAD_VDATA4),
		.N02		(nring_p23),
		.H01		(r_vdata[4]),
		.H03		(nring_enl)
		);

	TDBIAC33NL03 pad_m22 (
		.N01		(PAD_VDATA5),
		.N02		(nring_m22),
		.H01		(r_vdata[5]),
		.H03		(nring_enl)
	 	);

	TDBIAC33NL03 pad_n23 (
		.N01		(PAD_VDATA6),
		.N02		(nring_n23),
		.H01		(r_vdata[6]),
		.H03		(nring_enl)
		);

	TDBIAC33NL03 pad_m23 (
		.N01		(PAD_VSYNC),
		.N02		(nring_m23),
		.H01		(r_vsync),
		.H03		(nring_enl)
		);

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
		.CLKA		(vdac_clk),
		.CLKB		(vdac_clk),
		.CLKC		(vdac_clk),
		.DA			(vda),
		.DB			(vdb),
		.DC			(vdc),
		.VOA		(PAD_VOA),
		.VOB		(PAD_VOB),
		.VOC		(PAD_VOC),
		.PDB		(vdac_pd),
		.MODE1		(vdac_mode1),
		.MODE2		(vdac_mode2),
		.BUNRI		(vdac_bunri),		// test mode;
		.TEST		(vdac_test),		// normal mode;
		.TBI		(),					// test bus inputs;
		.ATBO		()					// test bus outputs;
	);

	// XXX instantiate real io cells;

	TDBIAC33NL03 pad_ab23 (
		.N01		(PAD_ACLOCK),
		.N02		(nring_ab23),
		.H01		(aclock),
		.H03		(nring_enl)
		);

	TDBIAC33NL03 pad_aa23 (
		.N01		(PAD_ADATA),
		.N02		(nring_aa23),
		.H01		(adata),
		.H03		(nring_enl)
		);

	TDBIAC33NL03 pad_y22 (
		.N01		(PAD_AWORD),
		.N02		(nring_y22),
		.H01		(aword),
		.H03		(nring_enl)
		);

	// joy channel ports;
	// XXX instantiate real io cells;

	wire jchan1_oe = nring_enl & jchan_oe[1];
	wire jchan2_oe = nring_enl & jchan_oe[2];
	wire jchan3_oe = nring_enl & jchan_oe[3];
	wire jchan1_in, jchan2_in, jchan3_in;

	TDBIAC33NL12 pad_ad8 (
		.N01		(PAD_JCHAN1),
		.N02		(jchan1_in),
		.H01		(1'b0),
		.H03		(jchan1_oe)
		);

	TDBIAC33NL12 pad_ac8 (
		.N01		(PAD_JCHAN2),
		.N02		(jchan2_in),
		.H01		(1'b0),
		.H03		(jchan2_oe)
		);

	TDBIAC33NL12 pad_ad9 (
		.N01		(PAD_JCHAN3),
		.N02		(jchan3_in),
		.H01		(1'b0),
		.H03		(jchan3_oe)
		);

	// local joystick;
	// XXX instantiate real io cells;

	TDIPAC33N pad_ad6 (
		.H01		(PAD_LX0),
		.N01		(lctrl_x[0])
		);

	TDIPAC33N pad_ad7 (
		.H01		(PAD_LX1),
		.N01		(lctrl_x[1])
		);

	TDIPAC33N pad_ac6 (
		.H01		(PAD_LY0),
		.N01		(lctrl_y[0])
		);

	TDIPAC33N pad_ac7 (
		.H01		(PAD_LY1),
		.N01		(lctrl_y[1])
		);

	// XXX instantiate flop with clock enable;

	reg [3:1] jchan_in;

	always @(posedge sysclk)
	begin
		if(jchan_ena[1])
			jchan_in[1] <= jchan1_in;
		if(jchan_ena[2])
			jchan_in[2] <= jchan2_in;
		if(jchan_ena[3])
			jchan_in[3] <= jchan3_in;
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

	wire	io_ad_in15;
	wire	io_ad_in14;
	wire	io_ad_in13;
	wire	io_ad_in12;
	wire	io_ad_in11;
	wire	io_ad_in10;
	wire	io_ad_in9;
	wire	io_ad_in8;
	wire	io_ad_in7;
	wire	io_ad_in6;
	wire	io_ad_in5;
	wire	io_ad_in4;
	wire	io_ad_in3;
	wire	io_ad_in2;
	wire	io_ad_in1;
	wire	io_ad_in0;

	wire	pad_io_intr;

	always @(posedge sysclk)
	begin
		if(io_ena)	// f-f with clock enable
			io_in <= {io_ad_in15,io_ad_in14,io_ad_in13,io_ad_in12,
								io_ad_in11,io_ad_in10,io_ad_in9 ,io_ad_in8 ,
								io_ad_in7 ,io_ad_in6 ,io_ad_in5 ,io_ad_in4 ,
								io_ad_in3 ,io_ad_in2 ,io_ad_in1 ,io_ad_in0 };
		rio_out   <=  io_out;
		rio_oe    <=  io_oe;
		rio_rst   <= ~io_rst;
		rio_ale   <=  io_ale;
		rio_cs    <= ~io_cs;
		rio_ior   <= ~io_ior;
		rio_iow   <= ~io_iow;
		rio_dmack <= ~io_dmack;
		io_dmarq  <=  pad_io_dmarq; //XXX synchronizer;
		io_intr   <=  pad_io_intr; //XXX synchronizer;
	end

	wire	nr_rio_oe0 = nring_enl & rio_oe[0];
	wire	nr_rio_oe1 = nring_enl & rio_oe[1];

	TDIPAC33N pad_ac2 (
		.H01		(PAD_IO_INTR),
		.N01		(pad_io_intr)
		);

	TDBIAC33NL12 pad_p2 (
		.N01		(PAD_IO_AD0),
		.N02		(io_ad_in0),
		.H01		(rio_out[0]),
		.H03		(nr_rio_oe0)
		);

	TDBIAC33NL12 pad_p1 (
		.N01		(PAD_IO_AD1),
		.N02		(io_ad_in1),
		.H01		(rio_out[1]),
		.H03		(nr_rio_oe0)
		);

	TDBIAC33NL12 pad_r2 (
		.N01		(PAD_IO_AD2),
		.N02		(io_ad_in2),
		.H01		(rio_out[2]),
		.H03		(nr_rio_oe0)
		);

	TDBIAC33NL12 pad_r1 (
		.N01		(PAD_IO_AD3),
		.N02		(io_ad_in3),
		.H01		(rio_out[3]),
		.H03		(nr_rio_oe0)
		);

	TDBIAC33NL12 pad_t2 (
		.N01		(PAD_IO_AD4),
		.N02		(io_ad_in4),
		.H01		(rio_out[4]),
		.H03		(nr_rio_oe0)
		);

	TDBIAC33NL12 pad_t1 (
		.N01		(PAD_IO_AD5),
		.N02		(io_ad_in5),
		.H01		(rio_out[5]),
		.H03		(nr_rio_oe0)
		);

	TDBIAC33NL12 pad_u2 (
		.N01		(PAD_IO_AD6),
		.N02		(io_ad_in6),
		.H01		(rio_out[6]),
		.H03		(nr_rio_oe0)
		);

	TDBIAC33NL12 pad_u1 (
		.N01		(PAD_IO_AD7),
		.N02		(io_ad_in7),
		.H01		(rio_out[7]),
		.H03		(nr_rio_oe1)
		);

	TDBIAC33NL12 pad_w2 (
		.N01		(PAD_IO_AD8),
		.N02		(io_ad_in8),
		.H01		(rio_out[8]),
		.H03		(nr_rio_oe1)
		);

	TDBIAC33NL12 pad_w1 (
		.N01		(PAD_IO_AD9),
		.N02		(io_ad_in9),
		.H01		(rio_out[9]),
		.H03		(nr_rio_oe1)
		);

	TDBIAC33NL12 pad_y2 (
		.N01		(PAD_IO_AD10),
		.N02		(io_ad_in10),
		.H01		(rio_out[10]),
		.H03		(nr_rio_oe1)
		);

	TDBIAC33NL12 pad_y1 (
		.N01		(PAD_IO_AD11),
		.N02		(io_ad_in11),
		.H01		(rio_out[11]),
		.H03		(nr_rio_oe1)
		);

	TDBIAC33NL12 pad_aa2 (
		.N01		(PAD_IO_AD12),
		.N02		(io_ad_in12),
		.H01		(rio_out[12]),
		.H03		(nr_rio_oe1)
		);

	TDBIAC33NL12 pad_aa1 (
		.N01		(PAD_IO_AD13),
		.N02		(io_ad_in13),
		.H01		(rio_out[13]),
		.H03		(nr_rio_oe1)
		);

	TDBIAC33NL12 pad_ab2 (
		.N01		(PAD_IO_AD14),
		.N02		(io_ad_in14),
		.H01		(rio_out[14]),
		.H03		(nr_rio_oe1)
		);

	TDBIAC33NL12 pad_ab1 (
		.N01		(PAD_IO_AD15),
		.N02		(io_ad_in15),
		.H01		(rio_out[15]),
		.H03		(nr_rio_oe1)
		);

	TDBIAC33NL12 pad_ad5 (
		.N01		(PAD_IO_RST),
		.N02		(nring_ad5),
		.H01		(rio_rst),
		.H03		(nring_enl)
		);

	TDBIAC33NL12 pad_ad3 (
		.N01		(PAD_IO_CS0),
		.N02		(nring_ad3),
		.H01		(rio_cs[0]),
		.H03		(nring_enl)
		);

	TDBIAC33NL12 pad_ac3 (
		.N01		(PAD_IO_CS1),
		.N02		(nring_ac3),
		.H01		(rio_cs[1]),
		.H03		(nring_enl)
		);

	TDBIAC33NL12 pad_ad4 (
		.N01		(PAD_IO_CS2),
		.N02		(nring_ad4),
		.H01		(rio_cs[2]),
		.H03		(nring_enl)
		);

	TDBIAC33NL12 pad_ac4 (
		.N01		(PAD_IO_CS3),
		.N02		(nring_ac4),
		.H01		(rio_cs[3]),
		.H03		(nring_enl)
		);

	TDBIAC33NL12 pad_ad1 (
		.N01		(PAD_IO_ALE),
		.N02		(nring_ad1),
		.H01		(rio_ale),
		.H03		(nring_enl)
		);

	TDBIAC33NL12 pad_ac1 (
		.N01		(PAD_IO_IOR),
		.N02		(nring_ac1),
		.H01		(rio_ior),
		.H03		(nring_enl)
		);

	TDBIAC33NL12 pad_ad2 (
		.N01		(PAD_IO_IOW),
		.N02		(nring_ad2),
		.H01		(rio_iow),
		.H03		(nring_enl)
		);

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
		rfl_ce   <= ~fl_ce;
		rfl_cle  <=  fl_cle;
		rfl_ale  <=  fl_ale;
		rfl_we   <= ~fl_we;
		rfl_re   <= ~fl_re;
		rfl_wp   <= ~fl_wp;
		rfl_ryby <=  fl_ryby;
		rfl_md   <=  fl_md;
	end

//	assign PAD_FL_CE3 = rfl_ce[3];
//	assign PAD_FL_CE2 = rfl_ce[2];
//	assign PAD_FL_CE1 = rfl_ce[1];
//	assign PAD_FL_CE0 = rfl_ce[0];
//	assign PAD_FL_ALE = rfl_ale;
//	assign PAD_FL_CLE = rfl_cle;
//	assign PAD_FL_RE = rfl_re;
//	assign PAD_FL_WE = rfl_we;
//	assign PAD_FL_WP = rfl_wp;
//	assign fl_ryby = rfl_ryby;
//	assign fl_md = rfl_md;

	TDIPAC33N pad_j1 (
		.H01		(PAD_FL_RYBY),
		.N01		(fl_ryby)
		);

	TDIPAC33N pad_j2 (
		.H01		(PAD_FL_MD),
		.N01		(fl_md)
		);

	TDBIAC33NL09 pad_n1 (
		.N01		(PAD_FL_ALE),
		.N02		(nring_n1),
		.H01		(rfl_ce[3]),
		.H03		(nring_enl)
		);

	TDBIAC33NL09 pad_n2 (
		.N01		(PAD_FL_CLE),
		.N02		(nring_n2),
		.H01		(rfl_ce[3]),
		.H03		(nring_enl)
		);

	TDBIAC33NL09 pad_m1 (
		.N01		(PAD_FL_RE),
		.N02		(nring_m1),
		.H01		(rfl_ce[3]),
		.H03		(nring_enl)
		);

	TDBIAC33NL09 pad_m2 (
		.N01		(PAD_FL_WE),
		.N02		(nring_m2),
		.H01		(rfl_ce[3]),
		.H03		(nring_enl)
		);

	TDBIAC33NL09 pad_l1 (
		.N01		(PAD_FL_WP),
		.N02		(nring_l1),
		.H01		(rfl_ce[3]),
		.H03		(nring_enl)
		);

	TDBIAC33NL09 pad_xxx (
		.N01		(PAD_FL_CE3),
		.N02		(nring_xxx),
		.H01		(rfl_ce[3]),
		.H03		(nring_enl)
		);

	TDBIAC33NL09 pad_k2 (
		.N01		(PAD_FL_CE2),
		.N02		(nring_k2),
		.H01		(rfl_ce[2]),
		.H03		(nring_enl)
		);

	TDBIAC33NL09 pad_k1 (
		.N01		(PAD_FL_CE1),
		.N02		(nring_k1),
		.H01		(rfl_ce[1]),
		.H03		(nring_enl)
		);

	TDBIAC33NL09 pad_l2 (
		.N01		(PAD_FL_CE0),
		.N02		(nring_l2),
		.H01		(rfl_ce[0]),
		.H03		(nring_enl)
		);

	// XXX instantiate io registers;
	// XXX instantiate io buffers;

	reg [3:0] rgpio_oe;		// output enables;
	reg [3:0] rgpio_out;	// output register;

	always @(posedge sysclk)
	begin
		rgpio_oe <= gpio_oe;
		rgpio_out <= gpio_out;
	end

//	assign PAD_GPIO0 = rgpio_oe[0]? rgpio_out[0] : 1'bz;
//	assign PAD_GPIO1 = rgpio_oe[1]? rgpio_out[1] : 1'bz;
//	assign PAD_GPIO2 = rgpio_oe[2]? rgpio_out[2] : 1'bz;
//	assign PAD_GPIO3 = rgpio_oe[3]? rgpio_out[3] : 1'bz;
//	assign gpio_in = {PAD_GPIO3,PAD_GPIO2,PAD_GPIO1,PAD_GPIO0};

	wire	nr_rgpio_oe0 = rgpio_oe[0] & nring_enl;
	wire	nr_rgpio_oe1 = rgpio_oe[1] & nring_enl;
	wire	nr_rgpio_oe2 = rgpio_oe[2] & nring_enl;
	wire	nr_rgpio_oe3 = rgpio_oe[3] & nring_enl;

	TDBIAC33NL12 pad_ac9 (
		.N01		(PAD_GPIO0),
		.N02		(gpio_in[0]),
		.H01		(rgpio_out[0]),
		.H03		(nr_rgpio_oe0)
		);

	TDBIAC33NL12 pad_ad10 (
		.N01		(PAD_GPIO1),
		.N02		(gpio_in[1]),
		.H01		(rgpio_out[1]),
		.H03		(nr_rgpio_oe1)
		);

	TDBIAC33NL12 pad_ac10 (
		.N01		(PAD_GPIO2),
		.N02		(gpio_in[2]),
		.H01		(rgpio_out[2]),
		.H03		(nr_rgpio_oe2)
		);

	TDBIAC33NL12 pad_ad11 (
		.N01		(PAD_GPIO3),
		.N02		(gpio_in[3]),
		.H01		(rgpio_out[3]),
		.H03		(nr_rgpio_oe3)
		);

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
		
		.dp_o(PAD_USB_DPLUS0),
		.dm_o(PAD_USB_DMINUS0) 
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
		
		.dp_o(PAD_USB_DPLUS1),
		.dm_o(PAD_USB_DMINUS1) 
	);

	 	// XXXX buffer here later

	TDIPAC33N pad_ad14 (
		.H01		(PAD_USB_ID0),
		.N01		(usb_id[0])
		);

	TDIPAC33N pad_ad18 (
		.H01		(PAD_USB_ID1),
		.N01		(usb_id[1])
		);

//	assign {PAD_USB_VBUS_ON_N1,PAD_USB_VBUS_ON_N0} = usb_vbus_on_n;
	assign {PAD_USB_DM_HIGH1,PAD_USB_DM_HIGH0} = usb_dm_high;
//	assign {PAD_USB_DP_HIGH1,PAD_USB_DP_HIGH0} = usb_dp_high;

	TDBIAC33NL03 pad_ad19 (
		.N01		(PAD_USB_VBUS_ON_N1),
		.N02		(nring_ad18),
		.H01		(usb_vbus_on_n[1]),
		.H03		(nring_enl)
		);

	TDBIAC33NL03 pad_ad15 (
		.N01		(PAD_USB_VBUS_ON_N0),
		.N02		(nring_ad15),
		.H01		(usb_vbus_on_n[0]),
		.H03		(nring_enl)
		);

	TDBIAC33NL03 pad_ac18 (
		.N01		(PAD_USB_DM_HIGH1),
		.N02		(nring_ac18),
		.H01		(usb_dp_high[1]),
		.H03		(nring_enl)
		);

	TDBIAC33NL03 pad_ac14 (
		.N01		(PAD_USB_DM_HIGH0),
		.N02		(nring_ac14),
		.H01		(usb_dp_high[0]),
		.H03		(nring_enl)
		);

	wire	trst_in, tdi_in, tms_in, tck_in;
	
	TDIPAC33N pad_ac23 (
		.H01		(PAD_TRST),
		.N01		(trst_in)
		);

	TDIPAC33N pad_ac22 (
		.H01		(PAD_TDI),
		.N01		(tdi_in)
		);

	TDIPAC33N pad_ab22 (
		.H01		(PAD_TMS),
		.N01		(tms_in)
		);

	TDIPAC33N pad_ad22 (
		.H01		(PAD_TCK),
		.N01		(tck_in)
		);

	wire jtag_en = 1'b1;	//XXX needs to come from mi unit
	assign trst = trst_in & jtag_en;
	assign tdi = tdi_in & jtag_en;
	assign tms = tms_in & jtag_en;
	assign tck = tck_in & jtag_en;

	wire	nring_out = 1'b0;
	wire	nring_enl = 1'b1;

	wire	tdo_out = nring_enl ? tdo : nring_out;
	wire	tdo_en  = tdoen | ~nring_enl;

	TDBIAC33NL03 pad_ad21 (
		.N01		(PAD_TDO),
		.N02		(),
		.H01		(tdo_out),
		.H03		(tdo_en)
		);


endmodule // nec_bbpads

