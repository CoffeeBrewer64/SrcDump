d13 1
a13 1
// $Id: at_latch_l.v,v 1.1 2002/03/28 00:26:12 berndt Exp $
d24 1
a24 5
reg [size-1:0] q;

always @(en or d)
   if (!en)
      q = d;
