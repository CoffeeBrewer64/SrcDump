
// $Id: j_dfntnq2.v,v 1.3 2002/12/24 22:29:57 doug Exp $

module j_dfntnq2 (q, d, cp);
   input d, cp;
   output q;
   reg q;

   always @ (posedge cp) 
         q <= d;

endmodule

