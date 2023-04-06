// ABPLSSCH.v v1 Frank Berndt, BroadOn Inc.
// pll behavioral model;
// :set tabstop=4

// this model does not measure the feedback clock CLKI for locking;
// the internal variable 'feedback' must be set to indicate the clock fed back;

// pll lock seuqnece is sped up for functional simulation;
// STBY=1 puts the pll into unlocked mode;
// pll starts locking 16 clocks after negedge STBY;
// pll is locked one RCLK later;

`timescale 1ps/1ps

module ABPLSSCH (
	RCLK, CLKI,
	M0, N0, N1, N2, N3,
	PA0, PA1, PA2, PA3,
	PB0, PB1, PB2, PB3,
	PC0, PC1, PC2, PC3,
	STBY, PBSTBY, PCSTBY,
	CLKOA, CLKOB, CLKOC, PLOCK,
	MODE, ATBI0, TEST, BUNRI,
	TBI0, TBI1, TBI2, TBI3, TBI4, TBI5, TBI6, TBI7, TBI8, TBI9,
	TBI10, TBI11, TBI12, TBI13, TBI14, TBI15, TBI16, TBI17, TBI18, TBI19,
	TBI20, TBI21,
	TBO0, TBO1, TBO2, TBO3, TBO4,
	AVDD1, AGND1
);
	input RCLK;			// reference clock;
	input CLKI;			// feedback clock;
	input M0;			// M divider;
	input N0;			// N divider;
	input N1;
	input N2;
	input N3;
	input PA0;			// port A divider;
	input PA1;
	input PA2;
	input PA3;
	input PB0;			// port B divider;
	input PB1;
	input PB2;
	input PB3;
	input PC0;			// port C divider;
	input PC1;
	input PC2;
	input PC3;
	input STBY;			// standby mode;
	input PBSTBY;		// port B standby;
	input PCSTBY;		// port C standby;
	output CLKOA;		// primary clock output, feedback;
	output CLKOB;		// port B clock output;
	output CLKOC;		// port C clock output;
	output PLOCK;		// lock indicator;
	input MODE;			// mode control;
	input ATBI0;		// external clock;
	input TEST;			// test mode;
	input BUNRI;		// test mode;
	input TBI0;			// test bus inputs;
	input TBI1;
	input TBI2;
	input TBI3;
	input TBI4;
	input TBI5;
	input TBI6;
	input TBI7;
	input TBI8;
	input TBI9;
	input TBI10;
	input TBI11;
	input TBI12;
	input TBI13;
	input TBI14;
	input TBI15;
	input TBI16;
	input TBI17;
	input TBI18;
	input TBI19;
	input TBI20;
	input TBI21;
	output TBO0;		// test bus outputs;
	output TBO1;
	output TBO2;
	output TBO3;
	output TBO4;
	input AVDD1;
	input AGND1;

	// warn about model;

	initial
		$display("%M: behavioral pll without test mode");

	// feedback control;
	// overwrite feedback if clock other than CLKOA is used;
	// 0=CLKOA, 1=CLKOB, 2=CLKOC;

	reg [1:0] feedback;

	initial
		feedback = 2'd0;

	// vco frequency limits;

	parameter VCO_MIN = 2500;
	parameter VCO_MAX = 5000;

	// monitor test mode changes;

	always @(MODE or TEST or BUNRI)
	begin
		$display("%t: %M: MODE %b ATBI0 %b TEST %b BUNRI %B",
			$time, MODE, ATBI0, TEST, BUNRI);
		$display("%t: %M: test modes not modelled", $time);
	end

	// measure time between rising edges of reference clock;
	// start locking after falling edge of STBY;
	// require 16 clocks before starting pll lock;
	// default vco to 200MHz;

	reg [4:0] lock_timer;	// lock timer;
	wire lock;				// start locking pll;
	reg locked;				// pll is locked;
	integer t0, t1;
	integer rclk_period;	// reference clock period;
	integer vco_period;		// check period;

	initial
	begin
		lock_timer = 0;
		locked = 0;
		t0 = -1;
		rclk_period = 5000;
		vco_period = 5000;
	end

	assign lock = lock_timer[4];
	assign PLOCK = lock;

	always @(posedge RCLK)
	begin
		if( !lock) begin
			t1 = $time;
			rclk_period = t1 - t0;
			t0 = t1;
			if(STBY === 1'b0)
				lock_timer = lock_timer + 1;
		end
	end

	// restart pll locking on assertion of STBY;

	always @(STBY)
	begin
		$display("%t: %M: STBY %b", $time, STBY);
		if(STBY === 1'b1) begin
			lock_timer = 0;
			locked = 0;
		end
	end

	// monitor port B & C standby;

	always @(PBSTBY)
		$display("%t: %M: PBSTBY %b", $time, PBSTBY);
	always @(PCSTBY)
		$display("%t: %M: PCSTBY %b", $time, PCSTBY);

	// output dividers;

	reg m_div;				// M divider;
	reg [3:0] n_div;		// N divider;
	reg [3:0] pa_div;		// PA divider value;
	reg [3:0] pb_div;		// PB divider value;
	reg [3:0] pc_div;		// PC divider value;

	always @(posedge RCLK)
	begin
		m_div <= M0;
		n_div <= { N3, N2, N1, N0 };
		pa_div <= { PA3, PA2, PA1, PA0 };
		pb_div <= { PB3, PB2, PB1, PB0 };
		pc_div <= { PC3, PC2, PC1, PC0 };
	end

	// monitor change of dividers;

	always @(m_div or n_div or pa_div or pb_div or pc_div)
	begin
		$display("%t: %M: M0 %b, N 0x%h, PA 0x%h, PB 0x%h, PC 0x%h",
			$time, m_div, n_div, pa_div, pb_div, pc_div);
		if(lock)
			$display("ERROR: %t: %M: divider change after pll started locking", $time);
	end

	// monitor change in reference clock;

	always @(rclk_period)
	begin
		if(lock)
			$display("ERROR: %t: %M: RCLK changed after pll started locking", $time);
	end

	// update vco;
	// on divider changes, feedback changes or rclk changes;

	integer p_div;
	integer check_period;		// fraction check;

	always @(rclk_period or m_div or n_div or pa_div or pb_div or pc_div or feedback or lock)
	begin
		case(feedback)
			0: p_div = pa_div;
			1: p_div = pb_div;
			2: p_div = pc_div;
			default: $display("ERROR: %t: %M: illegal feedback: %0d", $time, feedback);
		endcase
		vco_period = rclk_period * (m_div + 1) / ((n_div + 1) * (p_div + 1));
		check_period = vco_period * (n_div + 1) * (p_div + 1) / (m_div + 1);
		if(lock & (vco_period[0] | (rclk_period !== check_period))) begin
			$display("ERROR: %t: %M: fraction in clock ratios, rclk %0dps, vco %0dps",
				$time, rclk_period, vco_period);
			#100000;
			$finish;
		end
	end

	// model vco;
	// produce random vco clock until locked;
	// maximum frequency in unlocked state is 200Mhz;
	// limit frequency range between 5ns...5ns+2^12;
	// align rising edges of RCLK and output clocks;

	reg vco;			// pll vco clock;
	integer vco_rand;	// random vco output before lock;
	reg pa_clk;			// A clock;
	reg pb_clk;			// B clock;
	reg pc_clk;			// C clock;

	initial
	begin
		vco = 1;
		pa_clk = 0;
		pb_clk = 0;
		pc_clk = 0;
	end

	always
	begin
		if(locked)
			#(vco_period / 2);
		else if(lock) begin
			@(negedge RCLK);
			vco = 0;
			@(posedge RCLK);
			$display("%t: %M: pll locked", $time);
			$display("%t: %M: rclk %0dps, vco %0dps, feedback CLKO%0s", $time,
				rclk_period, vco_period,
				(feedback == 0)? "A"
				: (feedback == 1)? "B"
				: (feedback == 2)? "C"
				: "X");
			$display("%t: %M: clka %0dps, clkb %0dps, clkc %0dps", $time,
				vco_period * (pa_div + 1),
				vco_period * (pb_div + 1),
				vco_period * (pc_div + 1));
			if((vco_period < VCO_MIN) | (vco_period > VCO_MAX))
				$display("ERROR: %t: %M: vco frequency out of range: %0dps", $time, vco_period);
			vco = 1;
			pa_clk = 1;
			pb_clk = 1;
			pc_clk = 1;
			locked = 1;
			#(vco_period / 2);
		end else begin
			vco_rand = 2500 + ($random & 12'hfff);
			#(vco_rand);
		end
		vco = ~vco;
	end

	// output clock dividers;
	// output vco clock when not locked;

	reg clk_lock;
	reg [3:0] pa_cnt;		// divide counter;
	reg [3:0] pb_cnt;		// divide counter;
	reg [3:0] pc_cnt;		// divide counter;
	wire [2:0] clr;			// counter clears;

	assign clr[0] = (pa_cnt == pa_div);
	assign clr[1] = (pb_cnt == pb_div);
	assign clr[2] = (pc_cnt == pc_div);

	always @(vco)
	begin
		clk_lock <= locked;
		pa_cnt <= {4{clk_lock & ~clr[0]}} & (pa_cnt + 1);
		pb_cnt <= {4{clk_lock & ~clr[1]}} & (pb_cnt + 1);
		pc_cnt <= {4{clk_lock & ~clr[2]}} & (pc_cnt + 1);
		if(clr[0])
			pa_clk <= ~pa_clk;
		if(clr[1])
			pb_clk <= ~pb_clk;
		if(clr[2])
			pc_clk <= ~pc_clk;
	end

	assign CLKOA = ~STBY & (locked? pa_clk : vco);
	assign CLKOB = ~(STBY | PBSTBY) & (locked? pb_clk : vco);
	assign CLKOC = ~(STBY | PCSTBY) & (locked? pc_clk : vco);

endmodule

