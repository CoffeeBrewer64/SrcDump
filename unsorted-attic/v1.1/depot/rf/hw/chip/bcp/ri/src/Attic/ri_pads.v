d169 4
a172 4
	assign	data[31:24] = oe[1] ? data_out : {8{1'bz}};
	assign	data[23:16] = oe[2] ? data_out : {8{1'bz}};
	assign	data[15:8 ] = oe[3] ? data_out : {8{1'bz}};
	assign	data[ 7:0 ] = oe[4] ? data_out : {8{1'bz}};
