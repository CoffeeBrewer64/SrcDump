a0 10
//**************************************************************************************
//
//      Model Name      : nec_bbpad.v
//      Revision        : $Revision: 1.2 $
//      Date            : $Date: 2002/11/19 18:39:28 $
//      Author          : Bill Saperstein
//      Description     : pad module for nec process
//
//**************************************************************************************
     
a3 4
//**************************************************************************************
// Module Definition
//**************************************************************************************   

d21 1
a21 1
	PAD_JCHAN3, PAD_JCHAN2,PAD_JCHAN1, jchan_in, jchan_ena, jchan_oe,
d26 3
a28 2
	PAD_IO_AD9,PAD_IO_AD8,PAD_IO_AD7,PAD_IO_AD6,PAD_IO_AD5,PAD_IO_AD4,PAD_IO_AD3,
	PAD_IO_AD2,PAD_IO_AD1,PAD_IO_AD0, io_in, io_ena, io_out, io_oe,
d45 1
a45 1
	PAD_MCLKN,PAD_MCLK,
d47 1
a47 1
	PAD_MADDR12,PAD_MADDR11,PAD_MADDR10,PAD_MADDR9,PAD_MADDR8,PAD_MADDR7,
d57 3
a59 3
	PAD_MDATA13,PAD_MDATA12,PAD_MDATA11,PAD_MDATA10,
	PAD_MDATA9,PAD_MDATA8,PAD_MDATA7,PAD_MDATA6,PAD_MDATA5,PAD_MDATA4,PAD_MDATA3,
	PAD_MDATA2,PAD_MDATA1,PAD_MDATA0,
d67 1
a67 1
	PAD_USB_DPLUS0, PAD_USB_DPLUS1,	usb_dp, usb_dpo, 
d69 4
a72 4
	PAD_USB_DP_HIGH0,PAD_USB_DP_HIGH1, usb_dp_high,
	PAD_USB_DM_HIGH0,PAD_USB_DM_HIGH1, usb_dm_high,
	PAD_USB_ID0,PAD_USB_ID1, usb_id,
	PAD_USB_VBUS_ON_N0,PAD_USB_VBUS_ON_N1,  usb_vbus_on_n,
d79 3
a81 2
	PAD_PLLX2_AVDD, PAD_PLLX2_AGND, pllx2_lock,PAD_PLLC_AVDD, PAD_PLLC_AGND,
	PAD_PLLV_AVDD, PAD_PLLV_AGND, pllc_avdd1, pllc_agnd1
d84 1
a84 1
//**************************************************************************************
d86 1
a86 1
//************************************************************************************** 
d108 7
a114 7
	output PAD_VDATA6 ;			// video data
	output PAD_VDATA5 ;			// video data
	output PAD_VDATA4 ;			// video data
	output PAD_VDATA3 ;			// video data
	output PAD_VDATA2 ;			// video data
	output PAD_VDATA1 ;			// video data
	output PAD_VDATA0 ;			// video data
d116 1
a116 1
	output PAD_VSYNC ;			// video sync pin;
d134 99
a232 99
	inout PAD_JCHAN3 ;		// joy channel
	inout PAD_JCHAN2 ;		// joy channel
	inout PAD_JCHAN1 ;		// joy channel
	output [3:1] jchan_in;		// output of input register;
	input [3:1] jchan_ena;		// input register clock enable;
	input [3:1] jchan_oe;		// drive 0 on jchan;

	input PAD_LX0 ;			// stick x
	input PAD_LX1 ;			// stick x
	output [1:0] lctrl_x;		// output of input buffer;
	input PAD_LY0 ;			// stick y
	input PAD_LY1 ;			// stick y
	output [1:0] lctrl_y;		// output of input buffer;

	output PAD_IO_RST;			// io bus reset pin;
	input io_rst;				// io bus reset;
	inout PAD_IO_AD15 ;		// io data bus 
	inout PAD_IO_AD14 ;		// io data bus 
	inout PAD_IO_AD13 ;		// io data bus 
	inout PAD_IO_AD12 ;		// io data bus 
	inout PAD_IO_AD11 ;		// io data bus 
	inout PAD_IO_AD10 ;		// io data bus 
	inout PAD_IO_AD9 ;		// io data bus 
	inout PAD_IO_AD8 ;		// io data bus 
	inout PAD_IO_AD7 ;		// io data bus 
	inout PAD_IO_AD6 ;		// io data bus 
	inout PAD_IO_AD5 ;		// io data bus 
	inout PAD_IO_AD4 ;		// io data bus 
	inout PAD_IO_AD3 ;		// io data bus 
	inout PAD_IO_AD2 ;		// io data bus 
	inout PAD_IO_AD1 ;		// io data bus 
	inout PAD_IO_AD0 ;		// io data bus 
	output [15:0] io_in;		// io input data;
	input io_ena;				// io input clock enables;
	input [15:0] io_out;		// io output data;
	input [1:0] io_oe;			// io data output enables;
	output PAD_IO_ALE;			// io address latch enable pin;
	input io_ale;				// io address latch enable;
	output PAD_IO_CS3 ;		// io pio chip select
	output PAD_IO_CS2 ;		// io pio chip select
	output PAD_IO_CS1 ;		// io pio chip select
	output PAD_IO_CS0 ;		// io pio chip select
	input [3:0] io_cs;			// io pio chip selects;
	output PAD_IO_IOR;			// io read pulse pin;
	input io_ior;				// io read pulse;
	output PAD_IO_IOW;			// io write pulse pin;
	input io_iow;				// io write pulse;
	input pad_io_dmarq;			// io dma request pin;
	output io_dmarq;			// io dma request;
	output pad_io_dmack;		// io dma acknowledge pin;
	input io_dmack;				// io dma acknowledge;
	input PAD_IO_INTR;			// io device interrupt pin;
	output io_intr;				// io device interrupt;

	output PAD_FL_CE3 ;			// flash chip select
	output PAD_FL_CE2 ;			// flash chip select
	output PAD_FL_CE1 ;			// flash chip select
	output PAD_FL_CE0 ;			// flash chip select
	input [3:0] fl_ce;			// chip enables pin;
	output PAD_FL_ALE;			// address latch enable pin;
	input fl_ale;				// address latch enable pin;
	output PAD_FL_CLE;			// command latch enable pin;
	input fl_cle;				// command latch enable pin;
	output PAD_FL_RE;			// read eanble pin;
	input fl_re;				// read eanble pin;
	output PAD_FL_WE;			// write eanble pin;
	input fl_we;				// write eanble pin;
	output PAD_FL_WP;			// write protect pin;
	input fl_wp;				// write protect pin;
	input PAD_FL_RYBY;			// ready/busy pin;
	output fl_ryby;				// ready/busy pin;
	input PAD_FL_MD;			// module detect pin;
	output fl_md;				// module detect;

	inout PAD_GPIO3 ;		// gpio 
	inout PAD_GPIO2 ;		// gpio 
	inout PAD_GPIO1 ;		// gpio 
	inout PAD_GPIO0 ;		// gpio 
	input [3:0] gpio_oe;		// output enables;
	input [3:0] gpio_out;		// output values;
	output [3:0] gpio_in;		// input values;

	output PAD_MCLKN ;
	output PAD_MCLK ;
	output PAD_MCKE ;
	input		mcke;
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
d234 2
a235 2
	output PAD_MBANK0 ;
	output PAD_MBANK1 ;
d237 35
a271 35
	input		mdin_ena;
	input		mdout_ena;
	input		strobe_rev;
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
d280 4
a283 4
	output PAD_MDQM3 ;
	output PAD_MDQM2 ;
	output PAD_MDQM1 ;
	output PAD_MDQM0 ;
d285 4
a288 4
	inout PAD_MDQS3 ;
	inout PAD_MDQS2 ;
	inout PAD_MDQS1 ;
	inout PAD_MDQS0 ;
d292 2
a293 2
	inout PAD_USB_DMINUS0 ;
	inout PAD_USB_DMINUS1 ;
d297 2
a298 2
	inout PAD_USB_DPLUS0 ;
	inout PAD_USB_DPLUS1 ;
d307 2
a308 2
	output PAD_USB_DP_HIGH0 ;
	output PAD_USB_DP_HIGH1 ;
d310 2
a311 2
	output PAD_USB_DM_HIGH0 ;
	output PAD_USB_DM_HIGH1 ;
d314 2
a315 2
	input PAD_USB_ID0 ;
	input PAD_USB_ID1 ;
d317 2
a318 2
	output PAD_USB_VBUS_ON_N0 ;
	output PAD_USB_VBUS_ON_N1 ;
d335 1
a335 1
	input PAD_PLLX2_AVDD;           // x2 pll analog power pin;
d338 1
a338 1
	output pllx2_lock ;		// x2 pll lock signal
d345 1
a345 1
//**************************************************************************************  
d347 1
a347 1
//**************************************************************************************  
d351 17
a367 2
	assign rst_l = PAD_RST_L;
	assign sysclk = PAD_SYSCLK;
a368 1
	assign button = PAD_BUTTON;
d386 2
a387 2
	wire pllx2_avdd1 ;			// pll analog power
	wire pllx2_agnd1 ;			// pll analog ground
d394 1
a394 1
	assign pllx2_stby[0] = ~rst_l; //XXX
d474 6
a479 6
 AAPLAIOH33 pllpwr_x2 (
                .AVDD(PAD_PLLX2_AVDD),
                .AGND(PAD_PLLX2_AGND),
                .AVDD1(pllx2_avdd1),
                .AGND1(pllx2_agnd1)
        );                           
d483 6
a488 6
        AAPLAIOH33 pllpwr_cpu (
                .AVDD(PAD_PLLC_AVDD),
                .AGND(PAD_PLLC_AGND),
                .AVDD1(pllc_avdd1),
                .AGND1(pllc_agnd1)
        );            
d492 8
a499 8
        AAPLSIOH33 pllpwr_v (
                .AVDD(PAD_PLLV_AVDD),
                .AGND(_AD_PLLV_AGND),
                .AVDD1(pllv_avdd1),
                .AGND1(pllv_agnd1),
                .DVDD1(),
                .DGND1()
        );              
d503 459
a961 35
	ripad	ripad (
		.reset_l	(reset_l),
		.memclk		(memclk),
		.pad_mclk	({PAD_MCLKN,PAD_MCLK}),
		.pad_mcke	(PAD_MCKE),
		.mcke		(mcke),
		.pad_maddr	({PAD_MADDR12,PAD_MADDR11,PAD_MADDR10,PAD_MADDR9,
					PAD_MADDR8,PAD_MADDR7,PAD_MADDR6,PAD_MADDR5,
					PAD_MADDR4,PAD_MADDR3,PAD_MADDR2,PAD_MADDR1,
					PAD_MADDR0}),
		.maddr		(maddr),
		.pad_mbank	({PAD_MBANK1,PAD_MBANK0}),
		.mbank		(mbank),
		.mdin_ena	(mdin_ena),
		.mdout_ena	(mdout_ena),
		.strobe_rev	(strobe_rev),
		.pad_mdata	({PAD_MDATA31,PAD_MDATA30,PAD_MDATA29,PAD_MDATA28,PAD_MDATA27,
					PAD_MDATA26,PAD_MDATA25,PAD_MDATA24,PAD_MDATA23,
					PAD_MDATA22,PAD_MDATA21,PAD_MDATA20,PAD_MDATA19,
					PAD_MDATA18,PAD_MDATA17,PAD_MDATA16,PAD_MDATA15,
					PAD_MDATA14,PAD_MDATA13,PAD_MDATA12,PAD_MDATA11,
					PAD_MDATA10,PAD_MDATA9,PAD_MDATA8,PAD_MDATA7,
					PAD_MDATA6,PAD_MDATA5,PAD_MDATA4,PAD_MDATA3,
					PAD_MDATA2,PAD_MDATA1,PAD_MDATA0}),
		.mdin		(mdin),
		.mdout		(mdout),
		.pad_mras	(PAD_MRAS),
		.mras		(mras),
		.pad_mcas	(PAD_MCAS),
		.mcas		(mcas),
		.pad_mwe	(PAD_MWE),
		.mwe		(mwe),
		.pad_mdqm	({PAD_MDQM3,PAD_MDQM2,PAD_MDQM1,PAD_MDQM0}),
		.mdqm		(mdqm),
		.pad_mdqs	({PAD_MDQS3,PAD_MDQS2,PAD_MDQS1,PAD_MDQS0})
d964 599
d1592 56
a1647 3
	assign {PAD_VDATA6,PAD_VDATA5,PAD_VDATA4,PAD_VDATA3,PAD_VDATA2,
			PAD_VDATA1,PAD_VDATA0} = r_vdata;
	assign PAD_VSYNC = r_vsync;
d1662 16
a1677 16
		.CLKA(vdac_clk),
		.CLKB(vdac_clk),
		.CLKC(vdac_clk),
		.DA(vda),
		.DB(vdb),
		.DC(vdc),
		.VOA(PAD_VOA),
		.VOB(PAD_VOB),
		.VOC(PAD_VOC),
		.PDB(vdac_pd),
		.MODE1(vdac_mode1),
		.MODE2(vdac_mode2),
		.BUNRI(vdac_bunri),		// test mode;
		.TEST(vdac_test),		// normal mode;
		.TBI(),					// test bus inputs;
		.ATBO()					// test bus outputs;
d1682 20
a1701 3
	assign PAD_ACLOCK = aclock;
	assign PAD_ADATA = adata;
	assign PAD_AWORD = aword;
d1706 25
a1730 3
	assign PAD_JCHAN1 = jchan_oe[1]? 'b0 : 'bz;
	assign PAD_JCHAN2 = jchan_oe[2]? 'b0 : 'bz;
	assign PAD_JCHAN3 = jchan_oe[3]? 'b0 : 'bz;
d1735 19
a1753 2
	assign lctrl_x = {PAD_LX1,PAD_LX0};
	assign lctrl_y = {PAD_LY1,PAD_LY0};
d1762 1
a1762 1
			jchan_in[1] <= PAD_JCHAN1;
d1764 1
a1764 1
			jchan_in[2] <= PAD_JCHAN2;
d1766 1
a1766 1
			jchan_in[3] <= PAD_JCHAN3;
d1783 19
d1804 12
a1815 12
		if(io_ena)
			io_in <= {PAD_IO_AD15,PAD_IO_AD14,PAD_IO_AD13,PAD_IO_AD12,
					PAD_IO_AD11,PAD_IO_AD10,PAD_IO_AD9,PAD_IO_AD8,
					PAD_IO_AD7,PAD_IO_AD6,PAD_IO_AD5,PAD_IO_AD4,
					PAD_IO_AD3,PAD_IO_AD2,PAD_IO_AD1,PAD_IO_AD0};	// flop with clock enable;
		rio_out <= io_out;
		rio_oe <= io_oe;
		rio_rst <= ~io_rst;
		rio_ale <= io_ale;
		rio_cs <= ~io_cs;
		rio_ior <= ~io_ior;
		rio_iow <= ~io_iow;
d1817 2
a1818 2
		io_dmarq <= pad_io_dmarq; //XXX synchronizer;
		io_intr <= PAD_IO_INTR; //XXX synchronizer;
d1821 176
a1996 13
	assign {PAD_IO_AD15,PAD_IO_AD14,PAD_IO_AD13,PAD_IO_AD12,PAD_IO_AD11,PAD_IO_AD10,
			PAD_IO_AD9,PAD_IO_AD8} = rio_oe[1]? rio_out[15:8] : 8'bz;
	assign {PAD_IO_AD7,PAD_IO_AD6,PAD_IO_AD5,PAD_IO_AD4,PAD_IO_AD3,PAD_IO_AD2,
			PAD_IO_AD1,PAD_IO_AD0} = rio_oe[0]? rio_out[7:0] : 8'bz;

	assign PAD_IO_RST = rio_rst;
	assign PAD_IO_ALE = rio_ale;
	assign PAD_IO_CS3 = rio_cs[3];
	assign PAD_IO_CS2 = rio_cs[2];
	assign PAD_IO_CS1 = rio_cs[1];
	assign PAD_IO_CS0 = rio_cs[0];
	assign PAD_IO_IOR = rio_ior;
	assign PAD_IO_IOW = rio_iow;
d2013 94
a2106 21
		rfl_ce <= ~fl_ce;
		rfl_cle <= fl_cle;
		rfl_ale <= fl_ale;
		rfl_we <= ~fl_we;
		rfl_re <= ~fl_re;
		rfl_wp <= ~fl_wp;
		rfl_ryby <= PAD_FL_RYBY;
		rfl_md <= PAD_FL_MD;
	end

	assign PAD_FL_CE3 = rfl_ce[3];
	assign PAD_FL_CE2 = rfl_ce[2];
	assign PAD_FL_CE1 = rfl_ce[1];
	assign PAD_FL_CE0 = rfl_ce[0];
	assign PAD_FL_ALE = rfl_ale;
	assign PAD_FL_CLE = rfl_cle;
	assign PAD_FL_RE = rfl_re;
	assign PAD_FL_WE = rfl_we;
	assign PAD_FL_WP = rfl_wp;
	assign fl_ryby = rfl_ryby;
	assign fl_md = rfl_md;
d2120 38
a2157 6
	assign PAD_GPIO0 = rgpio_oe[0]? rgpio_out[0] : 1'bz;
	assign PAD_GPIO1 = rgpio_oe[1]? rgpio_out[1] : 1'bz;
	assign PAD_GPIO2 = rgpio_oe[2]? rgpio_out[2] : 1'bz;
	assign PAD_GPIO3 = rgpio_oe[3]? rgpio_out[3] : 1'bz;

	assign gpio_in = {PAD_GPIO3,PAD_GPIO2,PAD_GPIO1,PAD_GPIO0};
d2192 12
a2203 2
	assign usb_id = {PAD_USB_ID1,PAD_USB_ID0};
	assign {PAD_USB_VBUS_ON_N1,PAD_USB_VBUS_ON_N0} = usb_vbus_on_n;
d2205 1
a2205 1
	assign {PAD_USB_DP_HIGH1,PAD_USB_DP_HIGH0} = usb_dp_high;
d2207 68
a2274 5
	assign trst = PAD_TRST;
	assign tdi = PAD_TDI;
	assign tms = PAD_TMS;
	assign tck = PAD_TCK;
	assign PAD_TDO = tdoen ? tdo : 1'bz ;
a2276 3
//**************************************************************************************
// End of Model
//**************************************************************************************
