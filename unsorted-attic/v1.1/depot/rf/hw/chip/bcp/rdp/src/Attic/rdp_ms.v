d13 1
a13 1
// $Id: rdp_ms.v,v 1.1 2002/03/28 00:26:13 berndt Exp $
a107 1
wire iddq;
a367 1
  assign iddq                 = 1'b0;	// tmem active
d554 1
a554 1
	.bist_go(bist_go), .bist_check(bist_check), .iddq(iddq),
