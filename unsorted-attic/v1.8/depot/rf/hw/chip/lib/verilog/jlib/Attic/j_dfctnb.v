
// $Id: j_dfctnb.v,v 1.7 2002/12/24 22:29:57 doug Exp $

module j_dfctnb (q, qn, d, cp, cdn);
   input d, cp, cdn;
   output q, qn;
   reg tq;

   assign qn = ~tq;
   assign q  = tq;

   always @ (posedge cp) begin
      if (~cdn)
         tq <= 1'b0;
      else if (cdn) 
         tq <= d;
      else
	 tq <= 'bx;
   end

endmodule

