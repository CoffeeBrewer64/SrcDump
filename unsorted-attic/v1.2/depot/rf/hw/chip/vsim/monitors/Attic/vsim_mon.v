d1 1
a1 1
// $Id: vsim_mon.v,v 1.1 2002/05/20 23:25:41 berndt Exp $
a160 15

initial begin
	if ($test$plusargs("refresh")) begin
		wait(reset_l);
		wait(~reset_l);
		wait(reset_l);
		force vsim.bb.bcp.refresh_strobe = LOW;
		forever begin
			repeat (200) @(posedge clock);
			force vsim.bb.bcp.refresh_strobe = HIGH;
			@(posedge clock);
			force vsim.bb.bcp.refresh_strobe = LOW;
			end
		end
	end
