
// $Id: j_dfptnb.v,v 1.6 2002/12/24 22:29:57 doug Exp $

module j_dfptnb (q, qn, d, cp, sdn);
   input d, cp, sdn;
   output q, qn;
   reg tq;

   assign qn = ~tq;
   assign q  = tq;

   always @ (posedge cp) begin
      if (~sdn)
         tq <= 1'b1;
      else if (sdn)
         tq <= d;
      else
	 tq <= 'bx;
   end

endmodule

