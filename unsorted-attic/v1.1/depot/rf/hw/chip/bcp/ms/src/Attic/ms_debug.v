d13 1
a13 1
// $Id: ms_debug.v,v 1.1 2002/03/28 00:26:13 berndt Exp $
d24 2
a25 1
   reg_write_enable, reg_address, reg_write_data, bist_done, bist_fail,
d43 2
a44 2
input bist_done;				// TMEM BIST done (pulse)
input [DP_BIST_FAIL_SIZE-1:0] bist_fail;	// TMEM BIST fail (pulse)
d144 2
a145 2
		next_bist_done = bist_done_reg | bist_done;
		next_bist_fail = bist_fail_reg | bist_fail;
