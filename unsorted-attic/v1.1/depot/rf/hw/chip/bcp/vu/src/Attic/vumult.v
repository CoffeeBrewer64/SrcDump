d15 1
a15 1
// $Id: vumult.v,v 1.1 2002/03/28 00:26:14 berndt Exp $
a102 3
supply0 [15:0] vss;
supply1 [15:0] vdd;

d143 9
a151 9
		.A2({vss[15], b12[14], vss[13], b12[12], vss[11], b12[10], vss[9], b12[8],
                      vss[7], b12[6], vss[5], b12[4], vss[3], b12[2],
                      vss[1], b12[0]}),
		.A1({vss[15], b91[15], vss[13], b78[15], vss[11], b77[15], vss[9], b76[15],
                      vss[7], b54[15], vss[5], b53[15], vss[3], b48[15],
                      vss[1], b32[15]}),
		.B({vss[15], b13[15], vss[13], b13[13], vss[11], b13[11], vss[9], b13[9],
                      vss[7], b13[7], vss[5], b13[5], vss[3], b13[3],
                      vss[1], b13[1]}));
d170 1
a170 1
                      mplr[1], mplr[1], vss[1:0]}),
d174 3
a176 3
		.A3({vss[15], mplr[13], vss[13], mplr[11], vss[11], mplr[9], vss[9],
                      mplr[7], vss[7], mplr[5], vss[5], mplr[3], vss[3],
                      mplr[1], vss[1:0]}),
d198 1
a198 1
		.I1({b32[14:0], vss[0]}),
d206 1
a206 1
		.I1({b53[14:0], vss[0]}),
d261 1
a261 1
		.I1({b48[14:0], vss[0]}),
d272 3
a274 3
		.A1({vss[15:14], b13[15], vss[12], b13[13], vss[10], b13[11], vss[8],
                      b13[9], vss[6], b13[7], vss[4], b13[5], vss[2],
                      b13[3], vss[0]}),
d280 1
a280 1
		.I1({b54[14:0], vss[0]}),
d344 1
a344 1
		.I1({b77[14:0], vss[0]}),
d352 1
a352 1
		.I1({b76[14:0], vss[0]}),
d360 1
a360 1
		.I1({b78[14:0], vss[0]}),
d378 1
a378 1
                      vdd[1], vss[0]}),
d385 1
a385 1
		.I1({b91[14:0], vss[0]}),