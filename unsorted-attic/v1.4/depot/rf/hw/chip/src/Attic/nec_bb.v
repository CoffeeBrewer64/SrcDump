d5 2
a6 2
//      Revision        : $Revision: 1.3 $
//      Date            : $Date: 2002/11/19 18:39:28 $
d766 8
a773 8
	wire test_ena;                  // enable test/jtag logic;
        wire test_rst;                  // test controller reset overwrite;
        wire bram_boot;                 // boot from bram instead of brom;
        wire bram_sena;                 // bram serial enable;
        wire bram_sclk;                 // bram serial clock;
        wire bram_swe;                  // bram serial write enable;
        wire bram_si;                   // bram serial data in;
        wire bram_so;                   // bram serial data out;     
d868 10
a877 1
		.usb_vbus_on_n(usb_vbus_on_n)
a880 1
	// XXX
a887 1

d900 3
a902 3
		.v_sclk(1'b0),	// XXX
		.v_sme(1'b0),	// XXX
		.v_si(1'b0),	// XXX
d919 3
a921 3
		.v_sclk(1'b0),	// XXX
		.v_sme(1'b0),	// XXX
		.v_si(1'b0),	// XXX
d992 1
a992 1
	 // instantiate test/jtag controller;
d994 22
a1015 22
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
