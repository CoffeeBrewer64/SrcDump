d311 3
a313 3
	assign CLKOA = locked? pa_clk : vco;
	assign CLKOB = PBSTBY & (locked? pb_clk : vco);
	assign CLKOC = PCSTBY & (locked? pc_clk : vco);
