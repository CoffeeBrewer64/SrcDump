
// $Id: j_mfntnh.v,v 1.4 2002/12/24 22:29:57 doug Exp $

module j_mfntnh (q, qn, da, db, sa, cp);
   input da, db, sa, cp;
   output q, qn;
   reg tq;

   assign qn = ~q;
   assign q = tq;

   always @ (posedge cp)
      if (sa)
         tq <= da;
      else if (~sa)
         tq <= db;
      else
	 tq <= 'bx;

endmodule

