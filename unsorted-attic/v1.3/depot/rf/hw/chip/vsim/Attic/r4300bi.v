a43 1
		$timeformat(-9, 2, "ns", 12);
a481 23
		end
	endfunction

	// make read compare from address and size;

	function [31:0] sgl_mask;
		input [1:0] addr;		// requests address;
		input [1:0] size;		// request size;
		reg [31:0] mask;		// data compare mask;
		begin
			case({size,addr})
				4'b0000: mask = 32'hff000000;
				4'b0001: mask = 32'h00ff0000;
				4'b0010: mask = 32'h0000ff00;
				4'b0011: mask = 32'h000000ff;
				4'b0100: mask = 32'hffff0000;
				4'b0110: mask = 32'h0000ffff;
				4'b1000: mask = 32'hffffff00;
				4'b1001: mask = 32'h00ffffff;
				4'b1100: mask = 32'hffffffff;
				default: $display("ERROR: %t: %M: illegal addr %b, size %b", $time, addr, size);
			endcase
			sgl_mask = mask;
