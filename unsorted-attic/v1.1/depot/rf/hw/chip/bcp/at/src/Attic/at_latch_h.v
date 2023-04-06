d13 1
a13 1
// $Id: at_latch_h.v,v 1.1 2002/03/28 00:26:12 berndt Exp $
d15 1
a15 1
module at_latch_h(e, d, q);
d20 1
d27 5
a31 3
always @(e or d)
   if (e)
      q = d;
