d1 1
a1 1
// ABPLSSCH.v v1 Frank Berndt
d5 7
a11 2
// model only supports x2 on CLKOA;
// CLKOB and CLKOC are 0;
d16 6
a21 1
	RCLK, CLKI, M0, N, PA, PB, PC, STBY, PBSTBY, PCSTBY,
d23 5
a27 1
	MODE, ATBIO, TEST, BUNRI, TBI, TBO,
d33 16
a48 4
	input [3:0] N;		// N divider;
	input [3:0] PA;		// port A divider;
	input [3:0] PB;		// port B divider;
	input [3:0] PC;		// port C divider;
d57 1
a57 1
	input ATBIO;		// external clock;
d60 27
a86 2
	input [21:0] TBI;	// test bus inputs;
	output [4:0] TBO;	// test bus outputs;
d90 10
a99 1
	// warn about stub;
d102 6
a107 1
		$display("%M: behavioral pll stub");
d111 1
a111 1
	always @(MODE or ATBIO or TEST or BUNRI)
d113 3
a115 3
		$display("%t: %M: test mode not modelled", $time);
		$display("%t: %M: MODE %b ATBIO %b TEST %b BUNRI %B",
			$time, MODE, ATBIO, TEST, BUNRI);
d120 2
a121 1
	// require 8 master clocks before starting pll lock;
d123 1
a123 1
	reg [3:0] nrclock;		// lock timer;
d132 1
a132 1
		nrclock = 0;
d135 2
a136 2
		rclk_period = 10000;
		vco_period = 10000;
d139 1
a139 1
	assign lock = nrclock[3];
d149 1
a149 1
				nrclock = nrclock + 1;
d155 1
a155 1
	always @(posedge STBY)
d157 39
a195 3
		$display("%t: %M: relock started", $time);
		nrclock = 4'd0;
		locked = 0;
d204 19
a222 2
		vco_period = rclk_period / 2;
		if(lock & (rclk_period !== (vco_period * 2))) begin
d225 1
a229 20
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

d232 2
a233 1
	// limit frequency range between 2ns...2ns+2^12;
d238 3
d243 1
d245 4
a254 1
			$display("%t: %M: rclk %0dps, vco %0dps", $time, rclk_period, vco_period);
d256 17
a273 1
			vco = 1;
d276 1
a276 1
			vco_rand = 2000 + ($random & 12'hfff);
d282 30
a311 3
	assign CLKOA = vco;
	assign CLKOB = 1'b0;
	assign CLKOC = 1'b0;
d314 1
a314 1
	
