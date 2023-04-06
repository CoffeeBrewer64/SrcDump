
// $Id: j_nt01.v,v 1.1 2002/09/30 23:10:58 jeff Exp $

module j_nt01 (z, i, oe);
   input i, oe;
   output z;

   assign  z = oe ? i : 1'bz;

endmodule
