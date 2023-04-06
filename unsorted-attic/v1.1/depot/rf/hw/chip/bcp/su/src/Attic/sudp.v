a97 3
supply0 [31:0] vss;
supply1 [31:0] vdd;

d160 1
a160 1
		.I0({vss[31:16], inst_data[15:0]}),
d167 1
a167 1
		.I2({inst_data[15:0], vss[15:0]}),
d172 1
a172 1
                      inst_data[15], inst_data[15:0], vss[1:0]}),
d192 1
a192 1
                      inst_data[6], inst_data[6:0], vss[0]}),
d200 1
a200 1
                      inst_data[6:0], vss[1:0]}),
d208 1
a208 1
                      vss[2:0]}),
d215 1
a215 1
                      inst_data[6], inst_data[6:0], vss[3:0]}),
d225 1
a225 1
		.I5(vss[31:0]),
d249 1
a249 1
		.I4(vss[31:0]),
d270 3
a272 3
		.I0({vss[31], b15[31:1]}),
		.I1(vss[31:0]),
		.I2(vdd[31:0]),
d283 1
a283 1
		.I1({b15[0], vss[30:0]}),
d285 1
a285 1
		.I3({vss[31:24], link_pc_delay_pc[23:0]}),
d289 1
a289 1
		.I({vss[31:1], susltlt[0]}),
d317 1
a317 1
		.I1({vss[31:24], link_pc_delay_pc[23:0]}),
