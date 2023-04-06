// ABPLSSCH.v v1 Frank Berndt
// pll behavioral model;
// :set tabstop=4

// model only supports x2 on CLKOA;
// CLKOB and CLKOC are 0;

`timescale 1ps/1ps

module ABPLSSCHx (
	RCLK, CLKI, M0, N, PA, PB, PC, STBY, PBSTBY, PCSTBY,
	CLKOA, CLKOB, CLKOC, PLOCK,
	MODE, ATBIO, TEST, BUNRI, TBI, TBO,
	AVDD1, AGND1
);
	input RCLK;			// reference clock;
	input CLKI;			// feedback clock;
	input M0;			// M divider;
	input [3:0] N;		// N divider;
	input [3:0] PA;		// port A divider;
	input [3:0] PB;		// port B divider;
	input [3:0] PC;		// port C divider;
	input STBY;			// standby mode;
	input PBSTBY;		// port B standby;
	input PCSTBY;		// port C standby;
	output CLKOA;		// primary clock output, feedback;
	output CLKOB;		// port B clock output;
	output CLKOC;		// port C clock output;
	output PLOCK;		// lock indicator;
	input MODE;			// mode control;
	input ATBIO;		// external clock;
	input TEST;			// test mode;
	input BUNRI;		// test mode;
	input [21:0] TBI;	// test bus inputs;
	output [4:0] TBO;	// test bus outputs;
	input AVDD1;
	input AGND1;

	// warn about stub;

	initial
		$display("%M: behavioral pll stub");

	// monitor test mode changes;

	always @(MODE or ATBIO or TEST or BUNRI)
	begin
		$display("%t: %M: test mode not modelled", $time);
		$display("%t: %M: MODE %b ATBIO %b TEST %b BUNRI %B",
			$time, MODE, ATBIO, TEST, BUNRI);
	end

	// measure time between rising edges of reference clock;
	// start locking after falling edge of STBY;
	// require 8 master clocks before starting pll lock;

	reg [3:0] nrclock;		// lock timer;
	wire lock;				// start locking pll;
	reg locked;				// pll is locked;
	integer t0, t1;
	integer rclk_period;	// reference clock period;
	integer vco_period;		// check period;

	initial
	begin
		nrclock = 0;
		locked = 0;
		t0 = -1;
		rclk_period = 10000;
		vco_period = 10000;
	end

	assign lock = nrclock[3];
	assign PLOCK = lock;

	always @(posedge RCLK)
	begin
		if( !lock) begin
			t1 = $time;
			rclk_period = t1 - t0;
			t0 = t1;
			if(STBY === 1'b0)
				nrclock = nrclock + 1;
		end
	end

	// restart pll locking on assertion of STBY;

	always @(posedge STBY)
	begin
		$display("%t: %M: relock started", $time);
		nrclock = 4'd0;
		locked = 0;
	end

	// monitor change in reference clock;

	always @(rclk_period)
	begin
		if(lock)
			$display("ERROR: %t: %M: RCLK changed after pll started locking", $time);
		vco_period = rclk_period / 2;
		if(lock & (rclk_period !== (vco_period * 2))) begin
			$display("ERROR: %t: %M: fraction in clock ratios, rclk %0dps, vco %0dps",
				$time, rclk_period, vco_period);
			$finish;
		end
	end

	// monitor change of dividers;

	always @(M0 or N or PA or PB or PC)
	begin
		$display("%t: %M: M0 %b, N 0x%h, PA 0x%h, PB 0x%h, PC 0x%h",
			$time, M0, N, PA, PB, PC);
		if(lock)
			$display("ERROR: %t: %M: divider change after pll started locking", $time);
		if(M0 != 1)
			$display("ERROR: %t: %M: M0 %b, not 1", $time, M0);
		if(N != 7)
			$display("ERROR: %t: %M: N %0d, not 7", $time, N);
		if(PA != 1)
			$display("ERROR: %t: %M: PA %0d, not 1", $time, PA);
		if(PB != 1)
			$display("ERROR: %t: %M: PB %0d, not 1", $time, PB);
		if(PC != 1)
			$display("ERROR: %t: %M: PC %0d, not 1", $time, PC);
	end

	// model vco;
	// produce random vco clock until locked;
	// limit frequency range between 2ns...2ns+2^12;
	// align rising edges of RCLK and output clocks;

	reg vco;			// pll vco clock;
	integer vco_rand;	// random vco output before lock;

	initial
		vco = 1;

	always
	begin
		if(locked)
			#(vco_period / 2);
		else if(lock) begin
			$display("%t: %M: rclk %0dps, vco %0dps", $time, rclk_period, vco_period);
			@(posedge RCLK);
			locked = 1;
			vco = 1;
			#(vco_period / 2);
		end else begin
			vco_rand = 2000 + ($random & 12'hfff);
			#(vco_rand);
		end
		vco = ~vco;
	end

	assign CLKOA = vco;
	assign CLKOB = 1'b0;
	assign CLKOC = 1'b0;

endmodule
	
