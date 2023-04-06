
// $Id: j_lantnq.v,v 1.1 2002/09/30 23:10:57 jeff Exp $

module j_lantnq (q, d, e);
    input d, e;
    output q;
    reg q;

    always @ (d or e)
        if (e)
            q = d;

endmodule

