
// $Id: j_dfntnq.v,v 1.3 2002/12/27 01:53:16 doug Exp $

module j_dfntnq (q, d, cp);
   input d, cp;
   output q;
   reg q;

   always @ (posedge cp) 
         q <= d;

endmodule

