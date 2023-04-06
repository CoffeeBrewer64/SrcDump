
// $Id: j_lanfnb.v,v 1.1 2002/09/30 23:10:57 jeff Exp $

module j_lanfnb (q, qn, d, en);
    input d, en;
    output q, qn;
    reg q;

    assign qn = ~q;

    always @ (d or en)
        if (!en)
            q = d;

endmodule

