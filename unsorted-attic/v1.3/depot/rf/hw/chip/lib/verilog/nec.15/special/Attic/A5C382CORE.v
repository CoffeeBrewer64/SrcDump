// A5C382CORE.v v1 Frank Berndt
// behavioral stub for Ricoh N64 video encoder;
// :set tabstop=4

`timescale 1ns/1ns

module A5C382CORE (
	PTCLK, PSRGB, PTSYNCB, PNTPL, PTESTI0,
	CLK24DAC, COUT, VOUT, YOUT, PCSYNCB,
	PMPAL_I, PMPAL_O, PTRAPB_I, PTRAPB_O,
);
	input PTCLK;			// square pixel clock;
	input [6:0] PSRGB;		// SRGB pixel port;
	input PTSYNCB;			// sync input;
	input PNTPL;			// tv norm select, 0=pal, 1=ntsc;
	input PTESTI0;			// test mode, 0=normal 1=test mode;
	output CLK24DAC;		// video clock to DACs;
	output [7:0] COUT;		// chroma outputs to DAC;
	output [7:0] VOUT;		// composite outputs to DAC;
	output [7:0] YOUT;		// luminance outputs to DAC;
	output PCSYNCB;			// composite sync output;
	input PMPAL_I;			// pal/mpal mode;
	output PMPAL_O;			// test output;
	input PTRAPB_I;			// trap filer 0=on, 1=s[4];
	output PTRAPB_O;		// test output;

	// warn about stub;

	initial
		$display("%M: behavioral stub");

	// clock inputs into registers;
	// so they don't get optimized out;

	reg [7:0] COUT;
	reg [7:0] VOUT;
	reg [7:0] YOUT;
	reg PMPAL_O;
	reg PTRAPB_O;

	always @(posedge PTCLK)
	begin
		COUT <= { PTSYNCB, PSRGB };
		VOUT <= { PNTPL, PSRGB };
		YOUT <= { PTESTI0, PSRGB };
		PMPAL_O <= PMPAL_I;
		PTRAPB_O <= PTRAPB_I;
	end

	// divide video clock by 2;

	reg CLK24DAC;

	initial
		CLK24DAC = 0;

	always @(posedge PTCLK)
		CLK24DAC <= ~CLK24DAC;

	// report mode changes;

	always @(PTESTI0)
		$display("%t: %M: PTESTI0 %b", $time, PTESTI0);

	always @(PNTPL)
		$display("%t: %M: %0s mode", $time, PNTPL? "pal" : "ntsc");

	always @(PMPAL_I)
		$display("%t: %M: PMPAL_I %b", $time, PNTPL);

	always @(PTRAPB_I)
		$display("%t: %M: PTRAPB_I %b", $time, PTRAPB_I);

endmodule

