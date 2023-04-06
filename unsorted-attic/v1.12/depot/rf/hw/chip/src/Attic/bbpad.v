d184 52
a235 1
	// XXX ddr clock mulitplier;
d237 1
a237 24
	parameter MEMCLK_PERIOD = 8;	// default memclk is 125MHz;

	reg memclk180;
	reg P62p5;
	wire 	memclk    =  ~memclk180;
	wire #2 memclk270 =   memclk180;
	wire    memclk90  =  ~memclk270;

	always	@(posedge sysclk)
	begin
		memclk180 = 0;
		# (MEMCLK_PERIOD / 2)
		memclk180 = 1;
		# (MEMCLK_PERIOD / 2)
		memclk180 = 0;
		# (MEMCLK_PERIOD / 2)
		memclk180 = 1;
	end

	reg	delsysclk;
	always	@(posedge memclk90)
		delsysclk <= sysclk;
	always	@(posedge memclk)
		P62p5 <= ~delsysclk;
d241 1
a241 3
	// model off-chip clock delay

	wire	[1:0]	#2 pad_mclk =   {~memclk,memclk};
d272 1
a272 1
	always @(posedge memclk180) begin
d289 1
a289 1
	always @(posedge memclk180)
d301 1
a301 1
	assign	#2 pad_mdqs = oe[0] ? strobe_out : 1'bz;
d318 1
a318 1
	always @(posedge memclk180) begin
d344 1
a344 1
	always @(posedge memclk180) begin
d365 1
a365 1
	wire	#2 strobe_in   =  pad_mdqs;
d367 1
a367 1
	wire	#2 strobe_in_b = ~pad_mdqs;
d425 2
d430 2
d448 4
a451 4
		.BUNRI(1'b0),		// test mode;
		.TEST(1'b0),		// normal mode;
		.TBI(),				// test bus inputs;
		.ATBO()				// test bus outputs;
