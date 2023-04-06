
// $Id: j_dfntnh.v,v 1.3 2002/12/24 22:29:57 doug Exp $

module j_dfntnh (q, qn, d, cp);
   input d, cp;
   output q, qn;
   reg q;

   assign qn = ~q;

   always @ (posedge cp) 
         q <= d;

endmodule

