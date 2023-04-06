// $Id: div_pnt_slp.v,v 1.2 2002/11/13 01:08:08 rws Exp $

module div_pnt_slp (index, slope_incpt);

input   [5:0] index;

output  [23:0] slope_incpt;
reg	[23:0] slope_incpt_reg;

assign slope_incpt = slope_incpt_reg;

always @(index)
  begin
  // slope/intercept table
  case (index[5:0]) //
						//  Reciprocal
    6'h00:	slope_incpt_reg = 24'h08fff0;	// Value=0.999878, Delta=0xf82
    6'h01:	slope_incpt_reg = 24'h17f06e;	// Value=0.969589, Delta=0xe9a
    6'h02:	slope_incpt_reg = 24'h24e1d4;	// Value=0.941071, Delta=0xdc4
    6'h03:	slope_incpt_reg = 24'h30d410;	// Value=0.914185, Delta=0xd00
    6'h04:	slope_incpt_reg = 24'h3cc710;	// Value=0.888794, Delta=0xc4c
    6'h05:	slope_incpt_reg = 24'h46bac4;	// Value=0.864777, Delta=0xba7
    6'h06:	slope_incpt_reg = 24'h50af1d;	// Value=0.842010, Delta=0xb0d
    6'h07:	slope_incpt_reg = 24'h58a410;	// Value=0.820435, Delta=0xa80
    6'h08:	slope_incpt_reg = 24'h619990;	// Value=0.799927, Delta=0x9fd
    6'h09:	slope_incpt_reg = 24'h688f93;	// Value=0.780411, Delta=0x984
    6'h0a:	slope_incpt_reg = 24'h6f860f;	// Value=0.761826, Delta=0x912
    6'h0b:	slope_incpt_reg = 24'h767cfd;	// Value=0.744110, Delta=0x8a8
    6'h0c:	slope_incpt_reg = 24'h7c7455;	// Value=0.727203, Delta=0x846
    6'h0d:	slope_incpt_reg = 24'h826c0f;	// Value=0.711044, Delta=0x7ea
    6'h0e:	slope_incpt_reg = 24'h876425;	// Value=0.695587, Delta=0x794
    6'h0f:	slope_incpt_reg = 24'h8c5c91;	// Value=0.680786, Delta=0x742
    6'h10:	slope_incpt_reg = 24'h91554f;	// Value=0.666611, Delta=0x6f7
    6'h11:	slope_incpt_reg = 24'h954e58;	// Value=0.653015, Delta=0x6b0
    6'h12:	slope_incpt_reg = 24'h9a47a8;	// Value=0.639954, Delta=0x66d
    6'h13:	slope_incpt_reg = 24'h9e413b;	// Value=0.627396, Delta=0x62d
    6'h14:	slope_incpt_reg = 24'ha13b0e;	// Value=0.615341, Delta=0x5f2
    6'h15:	slope_incpt_reg = 24'ha5351c;	// Value=0.603729, Delta=0x5b9
    6'h16:	slope_incpt_reg = 24'ha82f63;	// Value=0.592545, Delta=0x584
    6'h17:	slope_incpt_reg = 24'hab29df;	// Value=0.581772, Delta=0x552
    6'h18:	slope_incpt_reg = 24'hae248d;	// Value=0.571381, Delta=0x521
    6'h19:	slope_incpt_reg = 24'hb11f6c;	// Value=0.561371, Delta=0x4f5
    6'h1a:	slope_incpt_reg = 24'hb41a77;	// Value=0.551682, Delta=0x4ca
    6'h1b:	slope_incpt_reg = 24'hb615ad;	// Value=0.542328, Delta=0x4a0
    6'h1c:	slope_incpt_reg = 24'hb9110d;	// Value=0.533295, Delta=0x47a
    6'h1d:	slope_incpt_reg = 24'hbb0c93;	// Value=0.524551, Delta=0x455
    6'h1e:	slope_incpt_reg = 24'hbd083e;	// Value=0.516098, Delta=0x432
    6'h1f:	slope_incpt_reg = 24'hc0040c;	// Value=0.507904, Delta=0x40c
						// 1/sqrt 1:(2-e)
    6'h30:	slope_incpt_reg = 24'h0cfff0;	// Value=0.999878, Delta=0xf47
    6'h31:	slope_incpt_reg = 24'h21f0a9;	// Value=0.970032, Delta=0xdfe
    6'h32:	slope_incpt_reg = 24'h33e2ab;	// Value=0.942703, Delta=0xcdf
    6'h33:	slope_incpt_reg = 24'h42d5cc;	// Value=0.917572, Delta=0xbe5
    6'h34:	slope_incpt_reg = 24'h50c9e7;	// Value=0.894333, Delta=0xb08
    6'h35:	slope_incpt_reg = 24'h5cbedf;	// Value=0.872787, Delta=0xa46
    6'h36:	slope_incpt_reg = 24'h67b499;	// Value=0.852722, Delta=0x998
    6'h37:	slope_incpt_reg = 24'h71ab01;	// Value=0.833984, Delta=0x8fe
    6'h38:	slope_incpt_reg = 24'h79a203;	// Value=0.816422, Delta=0x871
    6'h39:	slope_incpt_reg = 24'h819992;	// Value=0.799942, Delta=0x7f4
    6'h3a:	slope_incpt_reg = 24'h88919e;	// Value=0.784409, Delta=0x782
    6'h3b:	slope_incpt_reg = 24'h8f8a1c;	// Value=0.769745, Delta=0x719
    6'h3c:	slope_incpt_reg = 24'h958303;	// Value=0.755875, Delta=0x6bc
    6'h3d:	slope_incpt_reg = 24'h9a7c47;	// Value=0.742722, Delta=0x664
    6'h3e:	slope_incpt_reg = 24'h9f75e3;	// Value=0.730240, Delta=0x614
    6'h3f:	slope_incpt_reg = 24'ha46fcf;	// Value=0.718369, Delta=0x5c6
						// 1/sqrt 2:(4-e)
    6'h20:	slope_incpt_reg = 24'h5469ff;	// Value=0.707016, Delta=0xace
    6'h21:	slope_incpt_reg = 24'h625f31;	// Value=0.685913, Delta=0x9e5
    6'h22:	slope_incpt_reg = 24'h6f554c;	// Value=0.666595, Delta=0x91a
    6'h23:	slope_incpt_reg = 24'h7a4c32;	// Value=0.648819, Delta=0x868
    6'h24:	slope_incpt_reg = 24'h8443ca;	// Value=0.632401, Delta=0x7ce
    6'h25:	slope_incpt_reg = 24'h8c3bfc;	// Value=0.617157, Delta=0x743
    6'h26:	slope_incpt_reg = 24'h9434b9;	// Value=0.602966, Delta=0x6c9
    6'h27:	slope_incpt_reg = 24'h9b2df0;	// Value=0.589722, Delta=0x65b
    6'h28:	slope_incpt_reg = 24'ha12795;	// Value=0.577301, Delta=0x5f9
    6'h29:	slope_incpt_reg = 24'ha6219c;	// Value=0.565643, Delta=0x5a0
    6'h2a:	slope_incpt_reg = 24'hac1bfc;	// Value=0.554657, Delta=0x54f
    6'h2b:	slope_incpt_reg = 24'hb016ad;	// Value=0.544281, Delta=0x505
    6'h2c:	slope_incpt_reg = 24'hb411a8;	// Value=0.534485, Delta=0x4c2
    6'h2d:	slope_incpt_reg = 24'hb80ce6;	// Value=0.525192, Delta=0x485
    6'h2e:	slope_incpt_reg = 24'hbc0861;	// Value=0.516357, Delta=0x44d
    6'h2f:	slope_incpt_reg = 24'hbf0414;	// Value=0.507965, Delta=0x414
  endcase
  end

endmodule // div_pnt_slp
