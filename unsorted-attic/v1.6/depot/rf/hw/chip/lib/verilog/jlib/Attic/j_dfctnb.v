d2 1
a2 1
// $Id: j_dfctnb.v,v 1.5 2002/11/14 02:33:27 rws Exp $
d9 2
a10 2
   assign #1 qn = ~tq;
   assign #1 q  = tq;
d14 1
a14 1
         tq = 1'b0;
d16 1
a16 1
         tq = d;
d18 1
a18 1
	 tq = 'bx;
