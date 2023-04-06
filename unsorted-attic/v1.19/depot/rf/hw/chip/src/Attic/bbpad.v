d9 2
a10 1
	pad_sysclk, sysclk, memclk,
d69 7
a75 1
	pad_tdo, tdo
d85 1
d231 11
a259 1
	wire pllx2_lock;			// x2 pll is locked;
d265 2
d274 2
a275 2
	assign pllx2_stby[1] = 1'b0;	// turn off port B;
	assign pllx2_stby[2] = 1'b0;	// turn off port C;
d339 2
a340 2
		.AVDD1(),
		.AGND1()
d344 35
