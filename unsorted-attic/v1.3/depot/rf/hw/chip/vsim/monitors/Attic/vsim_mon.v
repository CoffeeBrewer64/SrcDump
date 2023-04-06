d1 1
a1 1
// $Id: vsim_mon.v,v 1.2 2002/06/20 19:05:45 berndt Exp $
a10 1
reg [1:256*8] vifilename;
a136 23

`ifdef IPC_PRESENT

initial
  begin
    if ($getstr$plusarg("vitab=", vifilename) == 1)
      begin
       if ($open_viout_file(vifilename) == -1)
         begin
           $write("Cannot open vi out file \n");	   
         end
      end
  end

always @(posedge vsim.bb.bcp.vi.vclk)
  begin
    if ($output_vi(vsim.bb.bcp.vi.vbus_data, vsim.bb.bcp.vi.vbus_sync) == -1)
      begin
	$write("Cannot write vi output values \n");
      end	
  end

`endif
