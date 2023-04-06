// cpu bus interface tasks for vr4300 processor;
// XXX change this for r4k cores;

// external variable cpu_mon dumps cpu activity;

// cpu single write;
// req[2:0] is write size;
// req[3] is back-to-back flag, 0=btb, 1=randomly spaced requests;
// last cpu_swrite in a sequence must have the btb flag 0;
// XXX add r4k data sizes;

task cpu_swrite;
	input [31:0] address;		// physical address;
	input [3:0] size;		// request size, and btb flag;
	input [31:0] data;		// write data;
	reg [3:0] req_spc;		// request spacing;

	begin
		// output address, cmd and pvalid;
		// wait for eok;

		p_valid <= HIGH;
		sys_cmd_out <= `SYS_CMD_SWRITE | size[1:0];
		sys_ad_out <= address;
		@(posedge sysclk);
		while( !e_ok)
			@(posedge sysclk);
		if(cpu_mon)
			$display("%t cpu: single write: addr 0x%h", $time, address);

		// single writes only have one data phase;

		sys_cmd_out <= `SYS_CMD_EOD;
		sys_ad_out <= data;
		@(posedge sysclk);
		if(cpu_mon)
			$display("%t cpu: write data 0x%h", $time, data);

		// eok can cancel bus request;
		// spin until successfully issued;

		while( !e_ok) begin
			sys_cmd_out <= `SYS_CMD_SWRITE | size[1:0];
			sys_ad_out <= address;
			@(posedge sysclk);
			while( !e_ok)
				@(posedge sysclk);
			if(cpu_mon)
				$display("%t cpu: single write re-issue", $time);

			sys_cmd_out <= `SYS_CMD_EOD;
			sys_ad_out <= data;
			@(posedge sysclk);
			if(cpu_mon)
				$display("%t cpu: write data 0x%h", $time, data);
		end

		// leave p_valid asserted for back-to-back write;
		// otherwise, apply a random spacing to next request;

		if( !size[3]) begin
			req_spc = $random & 4'hf;
			if(req_spc == 0)
				req_spc = 1;
			p_valid <= LOW;
			repeat(req_spc) @(posedge sysclk);
		end
	end
endtask

// cpu block write;
// issued for cache line write-back;
// target can only be main memory, no io devices support block requests;

task cpu_bwrite;
	input [31:0] address;		// physical address;
	input [3:0] size;
	integer i;

	begin
		// output address, cmd and pvalid;
		// wait for eok;

		p_valid <= HIGH;
		sys_cmd_out <= `SYS_CMD_BWRITE | size[1:0];
		sys_ad_out <= address;
		@(posedge sysclk);
		while( !e_ok)
			@(posedge sysclk);
		if(cpu_mon)
			$display("%t cpu: block write: addr 0x%h", $time, address);

		// block writes have a fixed data size;
		// write data pattern is ADD or ADDDDDDDD;

		sys_cmd_out <= `SYS_CMD_DATA;
		sys_ad_out <= data[0];
		@(posedge sysclk);
		if(cpu_mon)
			$display("%t cpu: write data[0] 0x%h", $time, data[0]);

		// eok can cancel bus request;
		// spin until successfully issued;

		while( !e_ok) begin
			sys_cmd_out <= `SYS_CMD_BWRITE | size[1:0];
			sys_ad_out <= address;
			@(posedge sysclk);
			while( !e_ok)
				@(posedge sysclk);
			if(cpu_mon)
				$display("%t cpu: block write re-issue", $time);

			sys_cmd_out <= `SYS_CMD_DATA;
			sys_ad_out <= data[0];
			@(posedge sysclk);
			if(cpu_mon)
				$display("%t cpu: write data[0] 0x%h", $time, data[0]);
		end

		// finish sending the data;

		for(i = 1; i < (2 << size[1:0]) - 1; i = i + 1) begin
			sys_ad_out <= data[i];
			@(posedge sysclk);
			if(cpu_mon)
				$display("%t cpu: write data[%1d] 0x%h", $time, i, data[i]);
		end

		// send last data item;

		sys_cmd_out <= `SYS_CMD_EOD;
		sys_ad_out <= data[i];
		@(posedge sysclk);
		if(cpu_mon)
			$display("%t cpu: write data[%1d] 0x%h", $time, i, data[i]);
	end
endtask

// cpu single read;
// XXX add r4k data sizes;

task cpu_sread;
	input [31:0] address;
	input [3:0] size;

	begin
		// output address, cmd and pvalid;
		// wait for eok;

		p_valid <= HIGH;
		sys_cmd_out <= `SYS_CMD_SREAD | size[1:0];
		sys_ad_out <= address;
		@(posedge sysclk);
		while(!e_ok)
			@(posedge sysclk);
		if(cpu_mon)
			$display("%t cpu: single read: addr 0x%h", $time, address);

		// tri-state sysad after address phase;

		sys_ad_enable <= LOW;
		p_valid <= LOW;
		@(posedge sysclk);

		// eok can cancel bus request;
		// spin until successfully issued;

		while(!e_ok) begin
			sys_ad_enable <= HIGH;
			p_valid <= HIGH;
			sys_cmd_out <= `SYS_CMD_SREAD | size[1:0];
			sys_ad_out <= address;
			@(posedge sysclk);
			while(!e_ok)
				@(posedge sysclk);
			if(cpu_mon)
				$display("%t cpu: single read re-issue", $time);
			sys_ad_enable <= LOW;
			p_valid <= LOW;
		end

		// successfully issued;
		// wait for return of read data;
		// XXX assertions for read protocol;

		while(!e_valid)
			@(posedge sysclk);
		data[0] = sys_ad_in;
		if(cpu_mon)
			$display("%t cpu: read data 0x%h", $time, sys_ad_in);
		sys_ad_enable <= HIGH;
	end
endtask

// cpu block read;
// issued to fill icache or dcache;
// target can only be main memory, no io devices support block requests;

task cpu_bread;
	input [31:0] address;
	input [3:0] size;
	integer i;

	begin
		// output address, cmd and pvalid;
		// wait for eok;

		p_valid <= HIGH;
		sys_cmd_out <= `SYS_CMD_BREAD | size[1:0];
		sys_ad_out <= address;
		@(posedge sysclk);
		while( !e_ok)
			@(posedge sysclk);
		if(cpu_mon)
			$display("%t cpu: block read: addr 0x%h", $time, address);

		// tri-state sysad after address phase;

		sys_ad_enable <= LOW;
		p_valid <= LOW;
		@(posedge sysclk);

		// eok can cancel bus request;
		// spin until successfully issued;

		while( !e_ok) begin
			sys_ad_enable <= HIGH;
			p_valid <= HIGH;
			sys_cmd_out <= `SYS_CMD_BREAD | size[1:0];
			sys_ad_out <= address;
			@(posedge sysclk);
			while( !e_ok)
				@(posedge sysclk);
			if(cpu_mon)
				$display("%t cpu: block read re-issue", $time);

			sys_ad_enable <= LOW;
			p_valid <= LOW;
			@(posedge sysclk);
		end

		// pull read data;

		for(i = 0; i < (2 << size[1:0]) - 1; i = i + 1) begin
			while( !e_valid)
				@(posedge sysclk);
			data[i] = sys_ad_in;
			if(cpu_mon)
				$display("%t cpu: read data[%1d] 0x%h", $time, i, sys_ad_in);
			@(posedge sysclk);
		end

		// pull last data word;

		while( !e_valid)
			@(posedge sysclk);
		data[i] = sys_ad_in;
		if(cpu_mon)
			$display("%t cpu: read data[%1d] 0x%h", $time, i, sys_ad_in);
		sys_ad_enable <= HIGH;
	end
endtask

