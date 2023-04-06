
// $Id: j_lantnz.v,v 1.1 2002/09/30 23:10:57 jeff Exp $

module j_lantnz (z, d, e, oe);
    input d, e, oe;
    output z;
    reg q;

    assign  z = oe ? q : 1'bz;
    always @ (d or e)
        if (e)
            q = d;

endmodule

