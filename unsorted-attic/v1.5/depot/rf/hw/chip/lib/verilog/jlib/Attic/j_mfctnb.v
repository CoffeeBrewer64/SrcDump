
// $Id: j_mfctnb.v,v 1.4 2002/12/24 22:29:57 doug Exp $

module j_mfctnb (q, qn, da, db, sa, cp, cdn);
   input da, db, sa, cp, cdn;
   output q, qn;
   reg tq;

   assign qn = ~q;
   assign q = cdn ? tq : 1'b0;

   always @ (posedge cp)
      if (sa)
         tq <= da;
      else if (~sa)
         tq <= db;
      else 
	 tq <= 'bx;

endmodule

