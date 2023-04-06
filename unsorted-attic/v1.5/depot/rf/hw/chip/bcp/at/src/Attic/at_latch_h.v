/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

// $Id: at_latch_h.v,v 1.4 2003/01/11 02:55:05 berndt Exp $

module at_latch_h(clk, e, d, q);

// synopsys template
parameter size = 8;

input clk;
input e;
input [size-1:0] d;
output [size-1:0] q;

reg [size-1:0] q;

always @(negedge clk) begin
	if (e) begin
		q	<=	d;
	end
end

endmodule
