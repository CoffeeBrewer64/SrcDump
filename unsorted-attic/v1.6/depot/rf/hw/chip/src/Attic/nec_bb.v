
//**************************************************************************************
//
//      Model Name      : nec_bb.v
//      Revision        : $Revision: 1.5 $
//      Date            : $Date: 2002/11/20 03:19:03 $
//      Author          : Bill Saperstein
//      Description     : bb top level for nec synthesis
//
//**************************************************************************************     
`timescale 1ns/1ns

module nec_bb 
	(
	PAD_RST_L, PAD_SYSCLK, PAD_USBCLKI, PAD_USBCLKO, PAD_VCLKI, PAD_VCLKO,
	PAD_BUTTON,
	PAD_VCLOCK, PAD_VDATA6,PAD_VDATA5,PAD_VDATA4,PAD_VDATA3,PAD_VDATA2,PAD_VDATA1,PAD_VDATA0,
	PAD_VSYNC,
	PAD_VOA, PAD_VOB, PAD_VOC,
	PAD_ACLOCK, PAD_ADATA, PAD_AWORD,
	PAD_JCHAN3,PAD_JCHAN2,PAD_JCHAN1,
	PAD_LX1,PAD_LX0, PAD_LY1,PAD_LY0,
	PAD_IO_RST, PAD_IO_AD15,PAD_IO_AD14,PAD_IO_AD13,PAD_IO_AD12,PAD_IO_AD11,PAD_IO_AD10,PAD_IO_AD9,
	PAD_IO_AD8,PAD_IO_AD7,PAD_IO_AD6,PAD_IO_AD5,PAD_IO_AD4,PAD_IO_AD3,PAD_IO_AD2,PAD_IO_AD1,
	PAD_IO_AD0, PAD_IO_ALE,
	PAD_IO_CS3, PAD_IO_CS2, PAD_IO_CS1, PAD_IO_CS0,
	PAD_IO_IOR, PAD_IO_IOW, pad_io_dmarq, pad_io_dmack, PAD_IO_INTR,
	PAD_FL_CE3,PAD_FL_CE2,PAD_FL_CE1,PAD_FL_CE0, PAD_FL_ALE, PAD_FL_CLE,PAD_FL_RE, PAD_FL_WE, 
	PAD_FL_WP, PAD_FL_RYBY, PAD_FL_MD,
	PAD_GPIO3,PAD_GPIO2,PAD_GPIO1,PAD_GPIO0,
	PAD_MCLK,PAD_MCLKN,PAD_MCKE,PAD_MADDR12,PAD_MADDR11,PAD_MADDR10,
	PAD_MADDR9,PAD_MADDR8,PAD_MADDR7,PAD_MADDR6,PAD_MADDR5,PAD_MADDR4,PAD_MADDR3,PAD_MADDR2,PAD_MADDR1,
	PAD_MADDR0,PAD_MBANK1,PAD_MBANK0,
	PAD_MDATA31,PAD_MDATA30,PAD_MDATA29,PAD_MDATA28,PAD_MDATA27,
	PAD_MDATA26,PAD_MDATA25,PAD_MDATA24,PAD_MDATA23,PAD_MDATA22,PAD_MDATA21,PAD_MDATA20,
	PAD_MDATA19,PAD_MDATA18,PAD_MDATA17,PAD_MDATA16,PAD_MDATA15,PAD_MDATA14,PAD_MDATA13,PAD_MDATA12,
	PAD_MDATA11,PAD_MDATA10,PAD_MDATA9,PAD_MDATA8,PAD_MDATA7,PAD_MDATA6,PAD_MDATA5,PAD_MDATA4,PAD_MDATA3,
	PAD_MDATA2,PAD_MDATA1,PAD_MDATA0,
	PAD_MRAS,PAD_MCAS,PAD_MWE,PAD_MDQM3,PAD_MDQM2,PAD_MDQM1,PAD_MDQM0,
	PAD_MDQS3,PAD_MDQS2,PAD_MDQS1,PAD_MDQS0,
	PAD_USB_DMINUS1,PAD_USB_DMINUS0, PAD_USB_DPLUS1,PAD_USB_DPLUS0, 
	PAD_USB_DP_HIGH1,PAD_USB_DP_HIGH0, PAD_USB_DM_HIGH1,PAD_USB_DM_HIGH0, 
	PAD_USB_ID1,PAD_USB_ID0, PAD_USB_VBUS_ON_N1,PAD_USB_VBUS_ON_N0,
	PAD_TRST, PAD_TDI, PAD_TMS, PAD_TCK, PAD_TDO,
	PAD_PLLX2_AVDD, PAD_PLLX2_AGND,
	PAD_PLLC_AVDD, PAD_PLLC_AGND,
	PAD_PLLV_AVDD, PAD_PLLV_AGND
	);

`include "define.vh"
`include "jctrl.vh"

	// io pads;

	input PAD_RST_L;			// chip reset input;
	input PAD_SYSCLK;			// chip system clock input;
	input PAD_USBCLKI;			// usb clock input;
	output PAD_USBCLKO;			// usb clock output;
	input PAD_VCLKI;			// video clock input;
	output PAD_VCLKO;			// video clock output;

	output PAD_VCLOCK;			// video clock;
	output PAD_VDATA6 ;			// video data
	output PAD_VDATA5 ;			// video data
	output PAD_VDATA4 ;			// video data
	output PAD_VDATA3 ;			// video data
	output PAD_VDATA2 ;			// video data
	output PAD_VDATA1 ;			// video data
	output PAD_VDATA0 ;			// video data
	output PAD_VSYNC;			// video sync;
	output PAD_VOA;				// analog video, chroma;
	output PAD_VOB;				// analog video, composite;
	output PAD_VOC;				// analog video, luminance;

	output PAD_ACLOCK;			// audio clock;
	output PAD_ADATA;			// audio data;
	output PAD_AWORD;			// audio word clock;

	inout PAD_JCHAN3 ;			// joy channel port
	inout PAD_JCHAN2 ;			// joy channel port
	inout PAD_JCHAN1 ;			// joy channel port
	input PAD_LX1 ;				// stick x input			
	input PAD_LX0 ;				// stick x input			
	input PAD_LY1 ;				// stick y input
	input PAD_LY0 ;				// stick y input
	input PAD_BUTTON;			// button input;

	output PAD_IO_RST;			// io bus reset;
	inout PAD_IO_AD15 ;			// io data bus
	inout PAD_IO_AD14 ;			// io data bus
	inout PAD_IO_AD13 ;			// io data bus
	inout PAD_IO_AD12 ;			// io data bus
	inout PAD_IO_AD11 ;			// io data bus
	inout PAD_IO_AD10 ;			// io data bus
	inout PAD_IO_AD9 ;			// io data bus
	inout PAD_IO_AD8 ;			// io data bus
	inout PAD_IO_AD7 ;			// io data bus
	inout PAD_IO_AD6 ;			// io data bus
	inout PAD_IO_AD5 ;			// io data bus
	inout PAD_IO_AD4 ;			// io data bus
	inout PAD_IO_AD3 ;			// io data bus
	inout PAD_IO_AD2 ;			// io data bus
	inout PAD_IO_AD1 ;			// io data bus
	inout PAD_IO_AD0 ;			// io data bus
	output PAD_IO_ALE;			// io address latch enable;
	output PAD_IO_CS3 ;			// io chip select
	output PAD_IO_CS2 ;			// io chip select
	output PAD_IO_CS1 ;			// io chip select
	output PAD_IO_CS0 ;			// io chip select
	output PAD_IO_IOR;			// io read pulse;
	output PAD_IO_IOW;			// io write pulse;
	input pad_io_dmarq;			// io dma request;
	output pad_io_dmack;			// io dma acknowledge;
	input PAD_IO_INTR;			// io device interrupt;

	output PAD_FL_CE3 ;			// flash chip enable
	output PAD_FL_CE2 ;			// flash chip enable
	output PAD_FL_CE1 ;			// flash chip enable
	output PAD_FL_CE0 ;			// flash chip enable
	output PAD_FL_ALE;			// address latch enable;
	output PAD_FL_CLE;			// command latch enable;
	output PAD_FL_RE;			// read eanble;
	output PAD_FL_WE;			// write eanble;
	output PAD_FL_WP;			// write protect;
	input PAD_FL_RYBY;			// ready/busy;
	input PAD_FL_MD;			// module detect;
	
	inout PAD_GPIO3 ;			// general purpose i/o
	inout PAD_GPIO2 ;			// general purpose i/o
	inout PAD_GPIO1 ;			// general purpose i/o
	inout PAD_GPIO0 ;			// general purpose i/o

	output PAD_MCLK ;
	output PAD_MCLKN ;
	output PAD_MCKE;
	output PAD_MADDR12 ;
	output PAD_MADDR11 ;
	output PAD_MADDR10 ;
	output PAD_MADDR9 ;
	output PAD_MADDR8 ;
	output PAD_MADDR7 ;
	output PAD_MADDR6 ;
	output PAD_MADDR5 ;
	output PAD_MADDR4 ;
	output PAD_MADDR3 ;
	output PAD_MADDR2 ;
	output PAD_MADDR1 ;
	output PAD_MADDR0 ;
	output PAD_MBANK1 ;
	output PAD_MBANK0 ;

	inout PAD_MDATA31 ;
	inout PAD_MDATA30 ;
	inout PAD_MDATA29 ;
	inout PAD_MDATA28 ;
	inout PAD_MDATA27 ;
	inout PAD_MDATA26 ;
	inout PAD_MDATA25 ;
	inout PAD_MDATA24 ;
	inout PAD_MDATA23 ;
	inout PAD_MDATA22 ;
	inout PAD_MDATA21 ;
	inout PAD_MDATA20 ;
	inout PAD_MDATA19 ;
	inout PAD_MDATA18 ;
	inout PAD_MDATA17 ;
	inout PAD_MDATA16 ;
	inout PAD_MDATA15 ;
	inout PAD_MDATA14 ;
	inout PAD_MDATA13 ;
	inout PAD_MDATA12 ;
	inout PAD_MDATA11 ;
	inout PAD_MDATA10 ;
	inout PAD_MDATA9 ;
	inout PAD_MDATA8 ;
	inout PAD_MDATA7 ;
	inout PAD_MDATA6 ;
	inout PAD_MDATA5 ;
	inout PAD_MDATA4 ;
	inout PAD_MDATA3 ;
	inout PAD_MDATA2 ;
	inout PAD_MDATA1 ;
	inout PAD_MDATA0 ;

	output PAD_MRAS;
	output PAD_MCAS;
	output PAD_MWE;

	output PAD_MDQM3 ;
	output PAD_MDQM2 ;
	output PAD_MDQM1 ;
	output PAD_MDQM0 ;

	inout PAD_MDQS3 ;
	inout PAD_MDQS2 ;
	inout PAD_MDQS1 ;
	inout PAD_MDQS0 ;

	inout PAD_USB_DPLUS1 ;			// usb D+
	inout PAD_USB_DPLUS0 ;			// usb D+

	inout PAD_USB_DMINUS1 ;			// usb D-
	inout PAD_USB_DMINUS0 ;			// usb D-

	output PAD_USB_DP_HIGH1 ;		// usb pull up control on D+
	output PAD_USB_DP_HIGH0 ;		// usb pull up control on D+

	output PAD_USB_DM_HIGH1 ;		// usb pull up control on D-
	output PAD_USB_DM_HIGH0 ;		// usb pull up control on D-
	input PAD_USB_ID1 ;			// usb id pin
	input PAD_USB_ID0 ;			// usb id pin
	output PAD_USB_VBUS_ON_N1 ;		// usb vbus control for host mode
	output PAD_USB_VBUS_ON_N0 ;		// usb vbus control for host mode

	// JTAG
	input PAD_TRST;
	input PAD_TDI;
	input PAD_TMS;
	input PAD_TCK;
	output PAD_TDO;

	// ananlog powers;

	input PAD_PLLX2_AVDD;		// ddr pll ananlog power;
	input PAD_PLLX2_AGND;		// ddr pll ananlog ground;
	input PAD_PLLC_AVDD;		// cpu pll ananlog power;
	input PAD_PLLC_AGND;		// cpu pll ananlog ground;
	input PAD_PLLV_AVDD;		// video pll ananlog power;
	input PAD_PLLV_AGND;		// video pll ananlog ground;

	//bcp outputs

	wire		mcke;
	wire	[12:0]	maddr;
	wire	[1:0]	mbank;
	wire		mdin_ena;
	wire		mdout_ena;
	wire		strobe_rev;
	wire	[63:0]	mdout;
	wire		mras;
	wire		mcas;
	wire		mwe;
	wire	[7:0]	mdqm;
	wire	[3:0]	mdqs;

	//bbpad output

	wire	[63:0]	mdin;

	// system environment;

	wire button;				// external button;

	// video interface;

	wire vclock;				// video clock;
	wire [6:0] #2 vdata;			// video data;
	wire #2 vsync;					// video sync;
	wire vdac_clk;				// video dac clock;
	wire vdac_pd;				// video dac power-down;
	wire [7:0] vda;				// video chroma;
	wire [7:0] vdb;				// video composite;
	wire [7:0] vdc;				// video luminance;
	wire vntpl;					// ntsc/pal mode;
	wire vmpal;					// pal/mpal mode;
	wire vtrap;					// trap filter mode;
	wire venc_test;				// video encoder test mode;

	wire reset_l;				// system reset to pads;

	// hack for generating 4 clk reset pulse, and repeat 28 clocks later, to ricoh
	reg [3:0] reset_d;
	reg [27:0] reset1_d;
	wire reset1 = reset_d[3] & reset_l;
	wire reset2 = reset1_d[27];

	always @(posedge vclock) begin
		reset_d <= {reset_d[2:0], ~reset_l};
		reset1_d <= {reset1_d[26:0], reset1};
	end

	assign vdac_pd = 1; //XXX
	assign vntpl = 1; // XXX Default to NTSC
	assign vmpal = 0; //XXX
	assign vtrap = 0; //XXX
	assign venc_test = reset1 | reset2;   //XXX
	// audio DAC interface;

	wire aclock;				// audio clock;
	wire adata;					// audio data;
	wire aword;					// audio word;

	// joy channel interface;

	wire [3:1] jchan_in;		// output of input register;
	wire [3:1] jchan_ena;		// input reg clock enables;
	wire [3:1] jchan_oe;		// output enable;

	// local controller joystick;

	wire [1:0] lctrl_x;			// stick x inputs;
	wire [1:0] lctrl_y;			// stick y inputs;

	// generic io bus controller;

	wire io_rst;				// io bus reset;
	wire [15:0] io_in;			// io input data;
	wire io_ena;				// io input clock enables;
	wire [15:0] io_out;			// io output data;
	wire [1:0] io_oe;			// io data output enables;
	wire io_ale;				// io address latch enable;
	wire [3:0] io_cs;			// io pio chip selects;
	wire io_ior;				// io read pulse;
	wire io_iow;				// io write pulse;
	wire io_dmarq;				// io dma request;
	wire io_dmack;				// io dma acknowledge;
	wire io_intr;				// io device interrupt;

	// nand flash controls;

	wire [3:0] fl_ce;			// chip enables;
	wire fl_ale;				// address latch enable;
	wire fl_cle;				// command latch enable;
	wire fl_re;					// read eanble;
	wire fl_we;					// write eanble;
	wire fl_wp;					// write protect;
	wire fl_ryby;				// ready/busy;
	wire fl_md;					// module detect;

	// usb xcr control
	wire [1:0] usb_dp;
	wire [1:0] usb_dpo;
	wire [1:0] usb_dm;
	wire [1:0] usbxr_ose;
	wire [1:0] usbxr_y1;
	wire [1:0] usbxr_oen;
	wire [1:0] usbxr_ien;
	wire [1:0] usbxr_fl;
	wire [1:0] usb_dp_high;
	wire [1:0] usb_dm_high;
	wire [1:0] usb_id;
	wire [1:0] usb_vbus_on_n;

	// JTAG
	wire trst;
	wire tdi;
	wire tms;
	wire tck;
	wire tdo;

	wire tdoen_o;

	// analog powers;

	wire pllc_avdd1;			// cpu pll analog power;
	wire pllc_agnd1;			// cpu pll analog ground;

	// general purpose io;

	wire [3:0] gpio_oe;			// output enables;
	wire [3:0] gpio_out;		// output values;
	wire [3:0] gpio_in;			// input values;


	// instantiate pad module;

	wire sysclk;				// system clock;
	wire usbclk;				// usb clock;
	wire vclk;					// video clock;
	wire memclk;				// memory clock;
	wire rst_l;					// chip reset;
	wire [1:0] pll_lock;		// important plls are locked;

	nec_bbpad	nec_pads
			(
			 .PAD_RST_L(PAD_RST_L),.rst_l(rst_l), .reset_l(reset_l),
                        .PAD_SYSCLK(PAD_SYSCLK), .sysclk(sysclk), .memclk(memclk),
                        .PAD_USBCLKI(PAD_USB_CLKI), .PAD_USBCLKO(PAD_USB_CLKO), .usbclk(usbclk),
                        .PAD_VCLKI(PAD_VCLKI), .PAD_VCLKO(PAD_VCLKO), .vclk(vclk),
                        .PAD_BUTTON(PAD_BUTTON), .button(button),
                        .PAD_VCLOCK(PAD_VCLOCK), .vclock(vclock),
                        .PAD_VDATA6(PAD_VDATA6),.PAD_VDATA5(PAD_VDATA5),
                        .PAD_VDATA4(PAD_VDATA4),.PAD_VDATA3(PAD_VDATA3),.PAD_VDATA2(PAD_VDATA2),
                        .PAD_VDATA1(PAD_VDATA1),.PAD_VDATA0(PAD_VDATA0),.vdata(vdata),
                        .PAD_VSYNC(PAD_VSYNC), .vsync(vsync),
                        .vdac_clk(vdac_clk), .vdac_pd(vdac_pd),
                        .PAD_VOA(PAD_VOA), .vda(vda),
                        .PAD_VOB(PAD_VOB), .vdb(vdb),
                        .PAD_VOC(PAD_VOC), .vdc(vdc),
                        .PAD_ACLOCK(PAD_ACLOCK), .aclock(aclock),
                        .PAD_ADATA(PAD_ADATA), .adata(adata),
                        .PAD_AWORD(PAD_AWORD), .aword(aword),
                        .PAD_JCHAN3(PAD_JCHAN3), .PAD_JCHAN2(PAD_JCHAN2),
                        .PAD_JCHAN1(PAD_JCHAN1), .jchan_in(jchan_in), .jchan_ena(jchan_ena),
                        .jchan_oe(jchan_oe),
                        .PAD_LX0(PAD_LX0), .PAD_LX1(PAD_LX1), .lctrl_x(lctrl_x),
                        .PAD_LY0(PAD_LY0), .PAD_LY1(PAD_LY1), .lctrl_y(lctrl_y),
                        .PAD_IO_RST(PAD_IO_RST), .io_rst(io_rst),    
			.PAD_IO_AD15(PAD_IO_AD15),.PAD_IO_AD14(PAD_IO_AD14),.PAD_IO_AD13(PAD_IO_AD13),
                        .PAD_IO_AD12(PAD_IO_AD12),.PAD_IO_AD11(PAD_IO_AD11),.PAD_IO_AD10(PAD_IO_AD10),
                        .PAD_IO_AD9(PAD_IO_AD9),.PAD_IO_AD8(PAD_IO_AD8),.PAD_IO_AD7(PAD_IO_AD7),
                        .PAD_IO_AD6(PAD_IO_AD6),.PAD_IO_AD5(PAD_IO_AD5),.PAD_IO_AD4(PAD_IO_AD4),
                        .PAD_IO_AD3(PAD_IO_AD3),
                        .PAD_IO_AD2(PAD_IO_AD2),.PAD_IO_AD1(PAD_IO_AD1),.PAD_IO_AD0(PAD_IO_AD0),
                        .io_in(io_in), .io_ena(io_ena), .io_out(io_out), .io_oe(io_oe),
                        .PAD_IO_ALE(PAD_IO_ALE), .io_ale(io_ale),
                        .PAD_IO_CS3(PAD_IO_CS3), .PAD_IO_CS2(PAD_IO_CS2), .PAD_IO_CS1(PAD_IO_CS1),
                        .PAD_IO_CS0(PAD_IO_CS0), .io_cs(io_cs),
                        .PAD_IO_IOR(PAD_IO_IOR), .io_ior(io_ior),
                        .PAD_IO_IOW(PAD_IO_IOW), .io_iow(io_iow),
                        .pad_io_dmarq(pad_io_dmaq), .io_dmarq(io_dmarq),
                        .pad_io_dmack(pad_io_dmack), .io_dmack(io_dmack),
                        .PAD_IO_INTR(PAD_IO_INTR), .io_intr(io_intr),
                        .PAD_FL_CE3(PAD_FL_CE3),.PAD_FL_CE2(PAD_FL_CE2),.PAD_FL_CE1(PAD_FL_CE1),
                        .PAD_FL_CE0(PAD_FL_CE0), .fl_ce(fl_ce),
                        .PAD_FL_ALE(PAD_FL_ALE), .fl_ale(fl_ale),
                        .PAD_FL_CLE(PAD_FL_CLE), .fl_cle(fl_cle),  
			 .PAD_FL_RE(PAD_FL_RE), .fl_re(fl_re),
                        .PAD_FL_WE(PAD_FL_WE), .fl_we(fl_we),
                        .PAD_FL_WP(PAD_FL_WP), .fl_wp(fl_wp),
                        .PAD_FL_RYBY(PAD_FL_RYBY), .fl_ryby(fl_ryby),
                        .PAD_FL_MD(PAD_FL_MD), .fl_md(fl_md),
                        .PAD_GPIO3(PAD_GPIO3), .PAD_GPIO2(PAD_GPIO2), .PAD_GPIO1(PAD_GPIO1),
                        .PAD_GPIO0(PAD_GPIO0), .gpio_oe(gpio_oe), .gpio_out(gpio_out), .gpio_in(gpio_in),
                        .PAD_MCLKN(PAD_MCLKN),.PAD_MCLK(PAD_MCLK),
                        .PAD_MCKE(PAD_MCKE), .mcke(mcke),
                        .PAD_MADDR12(PAD_MADDR12),.PAD_MADDR11(PAD_MADDR11),.PAD_MADDR10(PAD_MADDR10),
                        .PAD_MADDR9(PAD_MADDR9),.PAD_MADDR8(PAD_MADDR8),.PAD_MADDR7(PAD_MADDR7),
                        .PAD_MADDR6(PAD_MADDR6), .PAD_MADDR5(PAD_MADDR5), .PAD_MADDR4(PAD_MADDR4),
                        .PAD_MADDR3(PAD_MADDR3), .PAD_MADDR2(PAD_MADDR2), .PAD_MADDR1(PAD_MADDR1),
                        .PAD_MADDR0(PAD_MADDR0), .maddr(maddr),
                        .PAD_MBANK0(PAD_MBANK0), .PAD_MBANK1(PAD_MBANK1), .mbank(mbank),
                        .mdin_ena(mdin_ena),
                        .mdout_ena(mdout_ena),  
                        .strobe_rev(strobe_rev),  
			.PAD_MDATA31(PAD_MDATA31),.PAD_MDATA30(PAD_MDATA30),.PAD_MDATA29(PAD_MDATA29),
                        .PAD_MDATA28(PAD_MDATA28),.PAD_MDATA27(PAD_MDATA27),.PAD_MDATA26(PAD_MDATA26),
                        .PAD_MDATA25(PAD_MDATA25),.PAD_MDATA24(PAD_MDATA24),.PAD_MDATA23(PAD_MDATA23),
                        .PAD_MDATA22(PAD_MDATA22),.PAD_MDATA21(PAD_MDATA21),.PAD_MDATA20(PAD_MDATA20),
                        .PAD_MDATA19(PAD_MDATA19),.PAD_MDATA18(PAD_MDATA18),.PAD_MDATA17(PAD_MDATA17),
                        .PAD_MDATA16(PAD_MDATA16),.PAD_MDATA15(PAD_MDATA15),.PAD_MDATA14(PAD_MDATA14),
                        .PAD_MDATA13(PAD_MDATA13),.PAD_MDATA12(PAD_MDATA12),.PAD_MDATA11(PAD_MDATA11),
                        .PAD_MDATA10(PAD_MDATA10),
                        .PAD_MDATA9(PAD_MDATA9),.PAD_MDATA8(PAD_MDATA8),.PAD_MDATA7(PAD_MDATA7),
                        .PAD_MDATA6(PAD_MDATA6),.PAD_MDATA5(PAD_MDATA5),.PAD_MDATA4(PAD_MDATA4),
                        .PAD_MDATA3(PAD_MDATA3),
			.PAD_MDATA2(PAD_MDATA2),.PAD_MDATA1(PAD_MDATA1),.PAD_MDATA0(PAD_MDATA0),
                        .mdin(mdin), .mdout(mdout),
                        .PAD_MRAS(PAD_MRAS), .mras(mras),
                        .PAD_MCAS(PAD_MCAS), .mcas(mcas),
                        .PAD_MWE(PAD_MWE), .mwe(mwe),
                        .PAD_MDQM3(PAD_MDQM3), .PAD_MDQM2(PAD_MDQM2), .PAD_MDQM1(PAD_MDQM1),
                        .PAD_MDQM0(PAD_MDQM0), .mdqm(mdqm),
                        .PAD_MDQS3(PAD_MDQS3), .PAD_MDQS2(PAD_MDQS2), .PAD_MDQS1(PAD_MDQS1),
                        .PAD_MDQS0(PAD_MDQS0),
                        .PAD_USB_DMINUS0(PAD_USB_DMINUS0), .PAD_USB_DMINUS1(PAD_USB_DMINUS1),
                        .usb_dm(usb_dm), .usbxr_ose(usbxr_ose),
                        .PAD_USB_DPLUS0(PAD_USB_DPLUS0), .PAD_USB_DPLUS1(PAD_USB_DPLUS1),
                        .usb_dp(usb_dp), .usb_dpo(usb_dpo),
                        .usbxr_y1(usbxr_y1),.usbxr_oen(usbxr_oen),.usbxr_ien(usbxr_ien),.usbxr_fl(usbxr_fl),
			 .PAD_USB_DP_HIGH0(PAD_USB_DP_HIGH0),.PAD_USB_DP_HIGH1(PAD_USB_DP_HIGH1),
                        .usb_dp_high(usb_dp_high),
                        .PAD_USB_DM_HIGH0(PAD_USB_DM_HIGH0),.PAD_USB_DM_HIGH1(PAD_USB_DM_HIGH1),
                        .usb_dm_high(usb_dm_high),
                        .PAD_USB_ID0(PAD_USB_ID0),.PAD_USB_ID1(PAD_USB_ID1), .usb_id(usb_id),
                        .PAD_USB_VBUS_ON_N0(PAD_USB_VBUS_ON_N0),.PAD_USB_VBUS_ON_N1(PAD_USB_VBUS_ON_N1),
                        .usb_vbus_on_n(usb_vbus_on_n),
                        .PAD_TRST(PAD_TRST), .trst(trst),
                        .PAD_TDI(PAD_TDI), .tdi(tdi),
                        .PAD_TMS(PAD_TMS), .tms(tms),
                        .PAD_TCK(PAD_TCK), .tck(tck),
                        .tdoen(tdoen),
                        .PAD_TDO(PAD_TDO), .tdo(tdo),
                        .PAD_PLLX2_AVDD(PAD_PLLX2_AVDD), .PAD_PLLX2_AGND(PAD_PLLX2_AGND),
                        .pllx2_lock(pll_lock[1]),
                        .PAD_PLLC_AVDD(PAD_PLLC_AVDD), .PAD_PLLC_AGND(PAD_PLLC_AGND),
                        .PAD_PLLV_AVDD(PAD_PLLV_AVDD), .PAD_PLLV_AGND(PAD_PLLV_AGND),
                        .pllc_avdd1(pllc_avdd1), .pllc_agnd1(pllc_agnd1)
                        ) ;           



	// either instantiate the cpu model
	// or the behavioral bus model;

	wire [2:0] divmode;			// cpu frequency mode;
	wire coldrst_l;				// cpu cold reset;
	wire warmrst_l;				// cpu wam reset;

	wire [31:0] sysad_out;		// system addr/data from cpu;
	wire [4:0] syscmd_out;		// system command from cpu;
	wire pvalid_l;				// processor data valid;
	wire [31:0] `TCO sysad_in;	// system addr/data to cpu;
	wire [4:0] `TCO syscmd_in;	// system command to cpu;
	wire `TCO eok_l;			// external agent ok;
	wire `TCO evalid_l;			// external data valid;
	wire [4:0] `TCO int_l;		// cpu interrupts;
	wire `TCO nmi_l;			// non-maskable interrupt;

	wire pllc_bypass;			// bypass cpu pll;
	wire pllc_bypclk;			// bypassed cpu pipeline/system clock;

	assign pllc_bypass = 1'b0; //XXX
	assign pllc_bypclk = 1'b0; //XXX

`ifdef	SIMCPU

	// instantiate NEC cpu model;

	NB4300V01 cpu (
		.MASTERCLOCK(sysclk),
		.ISYSCMD4(syscmd_in[4]),
		.ISYSCMD3(syscmd_in[3]),
		.ISYSCMD2(syscmd_in[2]),
		.ISYSCMD1(syscmd_in[1]),
		.ISYSCMD0(syscmd_in[0]),
		.OSYSCMD4(syscmd_out[4]),
		.OSYSCMD3(syscmd_out[3]),
		.OSYSCMD2(syscmd_out[2]),
		.OSYSCMD1(syscmd_out[1]),
		.OSYSCMD0(syscmd_out[0]),
		.ISYSAD31(sysad_in[31]),
		.ISYSAD30(sysad_in[30]),
		.ISYSAD29(sysad_in[29]),
		.ISYSAD28(sysad_in[28]),
		.ISYSAD27(sysad_in[27]),
		.ISYSAD26(sysad_in[26]),
		.ISYSAD25(sysad_in[25]),
		.ISYSAD24(sysad_in[24]),
		.ISYSAD23(sysad_in[23]),
		.ISYSAD22(sysad_in[22]),
		.ISYSAD21(sysad_in[21]),
		.ISYSAD20(sysad_in[20]),
		.ISYSAD19(sysad_in[19]),
		.ISYSAD18(sysad_in[18]),
		.ISYSAD17(sysad_in[17]),
		.ISYSAD16(sysad_in[16]),
		.ISYSAD15(sysad_in[15]),
		.ISYSAD14(sysad_in[14]),
		.ISYSAD13(sysad_in[13]),
		.ISYSAD12(sysad_in[12]),
		.ISYSAD11(sysad_in[11]),
		.ISYSAD10(sysad_in[10]),
		.ISYSAD9(sysad_in[9]),
		.ISYSAD8(sysad_in[8]),
		.ISYSAD7(sysad_in[7]),
		.ISYSAD6(sysad_in[6]),
		.ISYSAD5(sysad_in[5]),
		.ISYSAD4(sysad_in[4]),
		.ISYSAD3(sysad_in[3]),
		.ISYSAD2(sysad_in[2]),
		.ISYSAD1(sysad_in[1]),
		.ISYSAD0(sysad_in[0]),
		.OSYSAD31(sysad_out[31]),
		.OSYSAD30(sysad_out[30]),
		.OSYSAD29(sysad_out[29]),
		.OSYSAD28(sysad_out[28]),
		.OSYSAD27(sysad_out[27]),
		.OSYSAD26(sysad_out[26]),
		.OSYSAD25(sysad_out[25]),
		.OSYSAD24(sysad_out[24]),
		.OSYSAD23(sysad_out[23]),
		.OSYSAD22(sysad_out[22]),
		.OSYSAD21(sysad_out[21]),
		.OSYSAD20(sysad_out[20]),
		.OSYSAD19(sysad_out[19]),
		.OSYSAD18(sysad_out[18]),
		.OSYSAD17(sysad_out[17]),
		.OSYSAD16(sysad_out[16]),
		.OSYSAD15(sysad_out[15]),
		.OSYSAD14(sysad_out[14]),
		.OSYSAD13(sysad_out[13]),
		.OSYSAD12(sysad_out[12]),
		.OSYSAD11(sysad_out[11]),
		.OSYSAD10(sysad_out[10]),
		.OSYSAD9(sysad_out[9]),
		.OSYSAD8(sysad_out[8]),
		.OSYSAD7(sysad_out[7]),
		.OSYSAD6(sysad_out[6]),
		.OSYSAD5(sysad_out[5]),
		.OSYSAD4(sysad_out[4]),
		.OSYSAD3(sysad_out[3]),
		.OSYSAD2(sysad_out[2]),
		.OSYSAD1(sysad_out[1]),
		.OSYSAD0(sysad_out[0]),
		.SYSEN(),				// XXX
		.PVALIDB(pvalid_l),
		.PREQB(),				// unused;
		.PMASTERB(),			// unused;
		.NMIB(nmi_l),
		.INTB4(int_l[4]),
		.INTB3(int_l[3]),
		.INTB2(int_l[2]),
		.INTB1(int_l[1]),
		.INTB0(int_l[0]),
		.EVALIDB(evalid_l),
		.EREQB(1'b1),			// never requested;
		.EOKB(eok_l),
		.DIVMODE2(divmode[2]),
		.DIVMODE1(divmode[1]),
		.DIVMODE0(divmode[0]),
		.COLDRESETB(coldrst_l),
		.RESETB(warmrst_l),
		.PLOCK(pll_lock[0]),	// cpu pll is locked;
		.SI7(1'b0),				// scan chain inputs;
		.SI6(1'b0),
		.SI5(1'b0),
		.SI4(1'b0),
		.SI3(1'b0),
		.SI2(1'b0),
		.SI1(1'b0),
		.SI0(1'b0),
		.SO7(),					// scan chain outputs;
		.SO6(),
		.SO5(),
		.SO4(),
		.SO3(),
		.SO2(),
		.SO1(),
		.SO0(),
		.BUNRI(1'b0),			// test mode;
		.TBI51(1'b0),			// test bus inputs;
		.TBI50(1'b0),
		.TBI49(1'b0),
		.TBI48(1'b0),
		.TBI47(1'b0),
		.TBI46(1'b0),
		.TBI45(1'b0),
		.TBI44(1'b0),
		.TBI43(1'b0),
		.TBI42(1'b0),
		.TBI41(1'b0),
		.TBI40(1'b0),
		.TBI39(1'b0),
		.TBI38(1'b0),
		.TBI37(1'b0),
		.TBI36(1'b0),
		.TBI35(1'b0),
		.TBI34(1'b0),
		.TBI33(1'b0),
		.TBI32(1'b0),
		.TBI31(1'b0),
		.TBI30(1'b0),
		.TBI29(1'b0),
		.TBI28(1'b0),
		.TBI27(1'b0),
		.TBI26(1'b0),
		.TBI25(1'b0),
		.TBI24(1'b0),
		.TBI23(1'b0),
		.TBI22(1'b0),
		.TBI21(1'b0),
		.TBI20(1'b0),
		.TBI19(1'b0),
		.TBI18(1'b0),
		.TBI17(1'b0),
		.TBI16(1'b0),
		.TBI15(1'b0),
		.TBI14(1'b0),
		.TBI13(1'b0),
		.TBI12(1'b0),
		.TBI11(1'b0),
		.TBI10(1'b0),
		.TBI9(1'b0),
		.TBI8(1'b0),
		.TBI7(1'b0),
		.TBI6(1'b0),
		.TBI5(1'b0),
		.TBI4(1'b0),
		.TBI3(1'b0),
		.TBI2(1'b0),
		.TBI1(1'b0),
		.TBI0(1'b0),
		.TBO39(),
		.TBO38(),
		.TBO37(),
		.TBO36(),
		.TBO35(),
		.TBO34(),
		.TBO33(),
		.TBO32(),
		.TBO31(),
		.TBO30(),
		.TBO29(),
		.TBO28(),
		.TBO27(),
		.TBO26(),
		.TBO25(),
		.TBO24(),
		.TBO23(),
		.TBO22(),
		.TBO21(),
		.TBO20(),
		.TBO19(),
		.TBO18(),
		.TBO17(),
		.TBO16(),
		.TBO15(),
		.TBO14(),
		.TBO13(),
		.TBO12(),
		.TBO11(),
		.TBO10(),
		.TBO9(),
		.TBO8(),
		.TBO7(),
		.TBO6(),
		.TBO5(),
		.TBO4(),
		.TBO3(),
		.TBO2(),
		.TBO1(),
		.TBO0(),
		.TEST(1'b0),			// test mode;
		.TEST1(1'b0),			// test mode;
		.TEST0(1'b0),			// test mode;
		.SCANSMC(1'b0),
		.SCANTMC(1'b0),
		.BYPASSPLLMODE(pllc_bypass),
		.BYPASSPLLPCLK(pllc_bypclk),
		.BYPASSPLLSCLK(pllc_bypclk),
		.AVDD1(pllc_avdd1),
		.AGND1(pllc_agnd1)
	);

`else	/* SIMCPU */

	// instantiate cpu behavioral bus model;
	// NECs embedded r4300 uses unidirectional sysad;

	assign pll_lock[0] = coldrst_l;

	r4300uni cpu (
		.sysclk(sysclk),
		.divmode(divmode),
		.coldrst_l(coldrst_l),
		.warmrst_l(warmrst_l),
		.sysad_out(sysad_out),
		.sysad_in(sysad_in),
		.syscmd_out(syscmd_out),
		.syscmd_in(syscmd_in),
		.pvalid_l(pvalid_l),
		.eok_l(eok_l),
		.evalid_l(evalid_l),
		.int_l(int_l),
		.nmi_l(nmi_l)
	);

`endif	/* SIMCPU */

	// instantiate bcp;

	wire v_time;			// virage time base, 1us;
	wire [2:0] v_me;		// virage enables;
	wire [2:0] v_we;		// virage write enables;
	wire [15:2] v0_addr;	// virage 0 address;
	wire [31:0] v0_in;		// virage 0 write data;
	wire [31:0] v0_out;		// virage 0 read data;
	wire [15:2] v1_addr;	// virage 1 address;
	wire [31:0] v1_in;		// virage 1 write data;
	wire [31:0] v1_out;		// virage 1 read data;
	wire [15:2] v2_addr;	// virage 2 address;
	wire [31:0] v2_in;		// virage 2 write data;
	wire [31:0] v2_out;		// virage 2 read data;

	wire test_ena;			// enable test/jtag logic;
	wire test_rst;			// test controller reset overwrite;
	wire bram_boot;			// boot from bram instead of brom;
	wire bram_sena;			// bram serial enable;
	wire bram_sclk;			// bram serial clock;
	wire bram_swe;			// bram serial write enable;
	wire bram_si;			// bram serial data in;
	wire bram_so;			// bram serial data out;     

	bcp bcp (
		.sysclk(sysclk),
		.memclk(memclk),
		.rst_l(rst_l),
		.reset_l(reset_l),
		.pll_lock(pll_lock),
		.button(button),

		.divmode(divmode),
		.coldrst_l(coldrst_l),
		.warmrst_l(warmrst_l),
		.sysad_out(sysad_out),
		.sysad_in(sysad_in),
		.syscmd_out(syscmd_out),
		.syscmd_in(syscmd_in),
		.pvalid_l(pvalid_l),
		.eok_l(eok_l),
		.evalid_l(evalid_l),
		.int_l(int_l),
		.nmi_l(nmi_l),
		.v_time(v_time),
		.v_me(v_me),
		.v_we(v_we),
		.v0_addr(v0_addr),
		.v0_in(v0_in),
		.v0_out(v0_out),
		.v1_addr(v1_addr),
		.v1_in(v1_in),
		.v1_out(v1_out),
		.v2_addr(v2_addr),
		.v2_in(v2_in),
		.v2_out(v2_out),
		
		.vclock(vclock),
		.vdata(vdata),
		.vsync(vsync),
		.aclock(aclock),
		.adata(adata),
		.aword(aword),
		.jchan_in(jchan_in),
		.jchan_ena(jchan_ena),
		.jchan_oe(jchan_oe),
		.lctrl_x(lctrl_x),
		.lctrl_y(lctrl_y),
		.io_rst(io_rst),
		.io_in(io_in),
		.io_ena(io_ena),
		.io_out(io_out),
		.io_oe(io_oe),
		.io_ale(io_ale),
		.io_cs(io_cs),
		.io_ior(io_ior),
		.io_iow(io_iow),
		.io_dmarq(io_dmarq),
		.io_dmack(io_dmack),
		.io_intr(io_intr),
		.fl_ce(fl_ce),
		.fl_ale(fl_ale),
		.fl_cle(fl_cle),
		.fl_re(fl_re),
		.fl_we(fl_we),
		.fl_wp(fl_wp),
		.fl_ryby(fl_ryby),
		.fl_md(fl_md),
		.gpio_oe(gpio_oe),
		.gpio_out(gpio_out),
		.gpio_in(gpio_in),

		.mcke(mcke),
		.maddr(maddr),
		.mbank(mbank),
		.mdin(mdin),
		.mdin_ena(mdin_ena),
		.mdout(mdout),
		.mdout_ena(mdout_ena),
		.strobe_rev(strobe_rev),
		.mras(mras),
		.mcas(mcas),
		.mwe(mwe),
		.mdqm(mdqm),
		
		.usb_clk(usbclk),
		.usb_dp(usb_dp),
		.usb_dm(usb_dm),
		.usb_dpo(usb_dpo),
		.usbxr_ose(usbxr_ose),
		.usbxr_y1(usbxr_y1),
		.usbxr_oen(usbxr_oen),
		.usbxr_ien(usbxr_ien),
		.usbxr_fl(usbxr_fl),
		.usb_dp_high(usb_dp_high),
		.usb_dm_high(usb_dm_high),
		.usb_id(usb_id),
		.usb_vbus_on_n(usb_vbus_on_n),

		.test_ena(test_ena),
		.test_rst(test_rst),
		.bram_boot(bram_boot),
		.bram_sena(bram_sena),
		.bram_sclk(bram_sclk),
		.bram_swe(bram_swe),
		.bram_si(bram_si),
		.bram_so(bram_so)
	);

	// virage test mode interface;

	wire v_sclk;			// virage serial clock;
	wire v_sme;				// virage serial mode;
	wire v_si;				// virage serial input data;
	wire v_so;				// virage serial output data;
	wire [2:0] v_vpp;		// programming voltage test pads;

	// instantiate virage 0 wrapper;
	// contains store controller, charge pump and novea block;

	v16x32wrap v0 (
		.sysclk(sysclk),
		.reset_l(reset_l),
		.v_time(v_time),
		.v_me(v_me[0]),
		.v_addr(v0_addr),
		.v_in(v0_in),
		.v_we(v_we[0]),
		.v_out(v0_out),
		.v_sclk(1'b0),
		.v_sme(1'b0),
		.v_si(1'b0),
		.v_so(),
		.v_vpp(v_vpp[0])
	);

	// instantiate virage 1 wrapper;
	// contains store controller, charge pump and novea block;

	v16x32wrap v1 (
		.sysclk(sysclk),
		.reset_l(reset_l),
		.v_time(v_time),
		.v_me(v_me[1]),
		.v_addr(v1_addr),
		.v_in(v1_in),
		.v_we(v_we[1]),
		.v_out(v1_out),
		.v_sclk(1'b0),
		.v_sme(1'b0),
		.v_si(1'b0),
		.v_so(),
		.v_vpp(v_vpp[1])
	);

	// instantiate virage 2 wrapper;
	// contains store controller, charge pump and novea block;

	v64x32wrap v2 (
		.sysclk(sysclk),
		.reset_l(reset_l),
		.v_time(v_time),
		.v_me(v_me[2]),
		.v_addr(v2_addr),
		.v_in(v2_in),
		.v_we(v_we[2]),
		.v_out(v2_out),
		.v_sclk(v_sclk),	
		.v_sme(v_sme),	
		.v_si(v_si),	
		.v_so(v_so),
		.v_vpp(v_vpp[2])
	);

	// instantiate video encoder;
	// triple video dac is instantiated in pad layer;

	A5C382CORE venc (
		.PTCLK(vclock),
		.PSRGB0(vdata[0]),
		.PSRGB1(vdata[1]),
		.PSRGB2(vdata[2]),
		.PSRGB3(vdata[3]),
		.PSRGB4(vdata[4]),
		.PSRGB5(vdata[5]),
		.PSRGB6(vdata[6]),
		.PTSYNCB(vsync),
		.PNTPL(vntpl),
		.PMPAL_I(vmpal),
		.PTESTI0(venc_test),
		.PTRAPB_I(vtrap),
		.PCSYNCB(),
		.CLK24DAC(vdac_clk),
		.COUT0(vda[0]),
		.COUT1(vda[1]),
		.COUT2(vda[2]),
		.COUT3(vda[3]),
		.COUT4(vda[4]),
		.COUT5(vda[5]),
		.COUT6(vda[6]),
		.COUT7(vda[7]),
		.VOUT0(vdb[0]),
		.VOUT1(vdb[1]),
		.VOUT2(vdb[2]),
		.VOUT3(vdb[3]),
		.VOUT4(vdb[4]),
		.VOUT5(vdb[5]),
		.VOUT6(vdb[6]),
		.VOUT7(vdb[7]),
		.YOUT0(vdc[0]),
		.YOUT1(vdc[1]),
		.YOUT2(vdc[2]),
		.YOUT3(vdc[3]),
		.YOUT4(vdc[4]),
		.YOUT5(vdc[5]),
		.YOUT6(vdc[6]),
		.YOUT7(vdc[7]),
		.PMPAL_O(),
		.PTRAPB_O()
	);

	// instantiate test/jtag controller;
 
	tap_blk tap_blk(
		.trst_i(trst),
		.tdi_i(tdi),
		.tms_i(tms),
		.tck_i(tck),
		.jtagen(test_ena),
		.treset(test_rst),
		.tbaddr(bram_boot),
		.spath_en(bram_sena),
		.clksram(bram_sclk),
		.stdi(bram_si),
		.stdo(bram_so),
		.tsram_we(bram_swe),
		.clkflash(v_sclk),
		.rpath_en(v_sme),
		.ftdi(v_si),
		.ftdo(v_so),
		.trom_store(trom_store),        // XXX
		.trom_recall(trom_recall),      // XXX
		.tdoen_o(tdoen),
		.tdo_o(tdo)
	);

//**************************************************************************************
// End of Model
//**************************************************************************************  

endmodule	// nec_bb

