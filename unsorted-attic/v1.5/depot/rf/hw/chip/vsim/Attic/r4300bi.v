// vr4300 behavioral bus model;
// bidirectional sysad;
// :set tabstop=4

module r4300bi (
	sysclk, reset_l,
	sysad, syscmd, pvalid_l, eok_l, evalid_l,
	preq_l, pmaster_l, ereq_l,
	int_l, nmi_l,
);

`include "rcp.vh"
`include "cpu.vh"
`include "define.vh"
`include "jctrl.vh"

	// cpu bus signals;
	// no sysad arbitration is used in the design;

	input sysclk;				// sysad clock;
	input reset_l;				// cpu reset;
	inout [31:0] sysad;			// system addr/data bus;
	inout [4:0] syscmd;			// system command bus;
	output pvalid_l;			// processor data valid;
	input eok_l;				// external agent ready;
	input evalid_l;				// external data valid;
	output preq_l;				// processor requests bus interface;
	output pmaster_l;			// processor is bus master;
	input ereq_l;				// external request for bus interface;
	input [4:0] int_l;			// cpu interrupts;
	input nmi_l;				// non-maskable interrupt;

	// internal variables;

	reg test_selected;

	// monitor cpu activity;

	reg cpu_mon;

	initial
	begin
		$display("%M: vr4300 behavioral bus model, bidirectional sysad");
		cpu_mon = $test$plusargs("cpu_mon");
	end

	// global cpu state;

	reg ready;				// cpu is ready;
	reg slave;				// bus interface in slave mode;
	reg [4:0] int_log;		// logged interrupts;
	reg nmi_log;			// logged nmi;
	integer word;			// nth read word;
	integer nwords;			// # of words expected;

	initial
	begin
		ready = 0;
		slave = 0;
		int_log = 5'd0;
		nmi_log = 0;
		word = 0;
		nwords = 0;
	end

	// SYSAD output enables;

	reg sysad_ena;
	reg [31:0] sysad_in, sysad_out;
	reg [4:0] syscmd_in, syscmd_out;
	reg pvalid;
	reg evalid;
	reg eok;
	reg [4:0] int;
	reg nmi;

	assign sysad = sysad_ena? sysad_out : 'bz;
	assign syscmd = sysad_ena? syscmd_out : 'bz;
	assign pvalid_l = ~pvalid;

	// register all cpu inputs;

	always @(posedge sysclk)
	begin
		sysad_in <= sysad;
		syscmd_in <= syscmd;
		eok <= ~eok_l;
		evalid <= ~evalid_l;
		int <= ~int_l;
		nmi <= ~nmi_l;
	end

	// slave state machine;

	reg [31:0] data [0:7];		// read/write data buffer;
	reg data_err;				// response error bit was set;
	integer rsp_timeout;		// read response timer;

	always @(posedge sysclk)
	begin
		if(evalid) begin
			if( !slave)
				$display("ERROR: %t: %M: evalid when not in slave state", $time);
			casex(syscmd_in)
				// read response;
				5'b1000x,
				5'b1100x,
				5'b1001x,
				5'b1101x: begin
					if(word >= nwords)
						$display("ERROR: %t: %M: excessive read response data", $time);
					if(word == 0)
						data_err = syscmd_in[1];
					if(cpu_mon) begin
						$display("%t: %M: rsp[%1d] 0x%h l%b e%b",
							$time, word, sysad_in, ~syscmd_in[3], data_err);
					end
					data[word] = sysad_in;
					word = word + 1;
					if(syscmd_in[3] == 0)
						slave = 0;
				end

				// all others are illegal;
				default:
					$display("ERROR: %t: %M: illegal syscmd %b", $time, syscmd_in);
			endcase
		end

		// timeout out read response;

		if(slave) begin
			rsp_timeout = rsp_timeout + 1;
			if(rsp_timeout > `CPU_RSP_TIMEOUT) begin
				$display("ERROR: %t: %M: read response timeout", $time);
				$finish;
			end
		end else begin
			rsp_timeout = 0;
			word = 0;
		end
	end

	// cpu ready flag and assertions;

	always @(posedge sysclk)
	begin
		ready = reset_l;
		if(ready) begin
			if((pvalid_l === 'bx) | (pvalid_l === 'bz))
				$display("ERROR: %t: %M: pvalid_l is %b", $time, pvalid_l);
			if((ereq_l === 'bx) | (ereq_l === 'bz))
				$display("ERROR: %t: %M: ereq_l is %b", $time, ereq_l);
			if((eok_l === 'bx) | (eok_l === 'bz))
				$display("ERROR: %t: %M: eok_l is %b", $time, eok_l);
			if((evalid_l === 'bx) | (evalid_l === 'bz))
				$display("ERROR: %t: %M: evalid_l is %b", $time, evalid_l);
		end
	end

	// reset is asynchronous;

	always @(reset_l)
	begin
		if(!reset_l) begin
			assign pvalid = 0;
			sysad_ena = 1;
			assign sysad_ena = 1;
			$display("%t: %M: reset asserted", $time);
		end else begin
			deassign pvalid;
			deassign sysad_ena;
			$display("%t: %M: reset deasserted", $time);
		end
	end

	// detect and log cpu interrupts and nmi;

	always @(int)
	begin
		if(ready & cpu_mon) begin
			$display("%t: %M: intr %b", $time, int);
			int_log = int_log | int;
		end
	end

	always @(nmi)
	begin
		if(ready & cpu_mon) begin
			$display("%t: %M: nmi %b", $time, nmi);
			nmi_log = nmi_log | nmi;
		end
	end

	// cpu bus interface tasks;

	task wait_eok;
		integer rdycnt;
		begin
			rdycnt = 0;
			while(eok !== 1) begin
				@(posedge sysclk);
				if(rdycnt >= `CPU_RDY_TIMEOUT) begin
					$display("ERROR: %t: %M: timeout", $time);
					$finish;
				end
				rdycnt = rdycnt + 1;
			end
			// XXX pmaster
		end
	endtask

	// single write request;
	// req[1:0] is write size;

	task swrite;
		input [31:0] addr;		// physical address;
		input [1:0] size;		// request size;
		input [31:0] data;		// write data;
		begin
			// output address, cmd and pvalid;
			// wait for eok;

			pvalid = 1;
			sysad_out = addr;
			syscmd_out = { 3'b010, size };
			@(posedge sysclk);
			wait_eok;
			if(cpu_mon)
				$display("%t: %M: addr 0x%h", $time, addr);

			// single writes have only one data phase;

			sysad_out <= data;
			syscmd_out <= 5'b10000;
			@(posedge sysclk);
			if(cpu_mon)
				$display("%t: %M: data[0] 0x%h", $time, data);

			// eok can cancel bus request;
			// spin until successfully issued;

			while(eok !== 1) begin
				sysad_out <= addr;
				syscmd_out <= { 3'b010, size };
				@(posedge sysclk);
				wait_eok;
				if(cpu_mon)
					$display("%t: %M: re-issue 0x%h", $time, addr);

				sysad_out <= data;
				syscmd_out <= 5'b10000;
				@(posedge sysclk);
				if(cpu_mon)
					$display("%t: %M: data[0] 0x%h", $time, data);
			end

			// deassert pvalid;
			// drive Xs on sysad;

			pvalid = 0;
			sysad_out = 'bx;
			syscmd_out = 'bx;

		end
	endtask

	// single read request;

	task sread;
		input [31:0] addr;		// phys address;
		input [1:0] size;		// single size;
		begin
			// output address, cmd and pvalid;
			// wait for eok;

			pvalid <= 1;
			sysad_out <= addr;
			syscmd_out <= { 3'b000, size };
			@(posedge sysclk);
			wait_eok;
			if(cpu_mon)
				$display("%t: %M: addr 0x%h", $time, addr);

			// tri-state sysad after address phase;

			nwords <= 1;
			pvalid <= 0;
			sysad_ena <= 0;
			sysad_out <= 'bx;
			syscmd_out <= 'bx;
			@(posedge sysclk);
			slave <= 1;

			// eok can cancel bus request;
			// spin until successfully issued;

			while(eok !== 1) begin
				slave <= 0;
				pvalid <= 1;
				sysad_ena <= 1;
				sysad_out <= addr;
				syscmd_out <= { 3'b000, size };
				@(posedge sysclk);
				wait_eok;
				if(cpu_mon)
					$display("%t: %M: re-issue 0x%h", $time, addr);

				pvalid <= 0;
				sysad_ena <= 0;
				sysad_out <= 'bx;
				syscmd_out <= 'bx;
				@(posedge sysclk);
				slave <= 1;
			end

			// wait for read response;
			// return mastership of sysad to cpu;

			@(negedge slave);
			sysad_ena <= 1;

		end
	endtask

	// block write request;
	// issued for cache line write-back;
	// target can only be main memory;

	task bwrite;
		input [31:0] addr;		// physical address;
		input [1:0] size;		// block size;
		integer i;
		begin
			// output address, cmd and pvalid;
			// wait for eok;

			pvalid <= 1;
			sysad_out <= addr;
			syscmd_out <= { 3'b011, size };
			@(posedge sysclk);
			wait_eok;
			if(cpu_mon)
				$display("%t: %M: addr 0x%h", $time, addr);

			// block writes have a fixed data size;
			// write data pattern is ADD or ADDDDDDDD;

			sysad_out <= data[0];
			syscmd_out <= 5'b11000;
			@(posedge sysclk);
			if(cpu_mon)
				$display("%t: %M: data[0] 0x%h", $time, data[0]);

			// eok can cancel bus request;
			// spin until successfully issued;

			while(eok !== 1) begin
				sysad_out <= addr;
				syscmd_out <= { 3'b011, size };
				@(posedge sysclk);
				wait_eok;
				if(cpu_mon)
					$display("%t: %M: re-issue 0x%h", $time, addr);

				sysad_out <= data[0];
				syscmd_out <= 5'b11000;
				@(posedge sysclk);
				if(cpu_mon)
					$display("%t: %M: data[0] 0x%h", $time, data[0]);
			end

			// finish sending the data;

			for(i = 1; i < (2 << size[1:0]) - 1; i = i + 1) begin
				sysad_out <= data[i];
				@(posedge sysclk);
				if(cpu_mon)
					$display("%t: %M: data[%1d] 0x%h", $time, i, data[i]);
			end

			// send last data item;

			sysad_out <= data[i];
			syscmd_out <= 5'b10000;
			@(posedge sysclk);
			if(cpu_mon)
				$display("%t: %M: data[%1d] 0x%h", $time, i, data[i]);

			pvalid <= 0;
			sysad_out <= 'bx;
			syscmd_out <= 'bx;
		end
	endtask

	// cpu block read;
	// issued to fill icache or dcache;
	// target can only be main memory, no io devices support block requests;

	task bread;
		input [31:0] addr;		// physical address;
		input [1:0] size;		// block size;
		integer i;
		begin
			// output address, cmd and pvalid;
			// wait for eok;

			pvalid <= 1;
			sysad_out <= addr;
			syscmd_out <= { 3'b001, size };
			@(posedge sysclk);
			wait_eok;
			if(cpu_mon)
				$display("%t: %M: addr 0x%h", $time, addr);

			// tri-state sysad after address phase;

			case(size)
				2'b00: nwords <= 2;
				2'b01: nwords <= 4;
				2'b10: nwords <= 8;
				2'b11: $display("ERROR: %t: %M: illegal block size %b", $time, size);
			endcase
			pvalid <= 0;
			sysad_ena <= 0;
			sysad_out <= 'bx;
			syscmd_out <= 'bx;
			@(posedge sysclk);
			slave <= 1;

			// eok can cancel bus request;
			// spin until successfully issued;

			while(eok !== 1) begin
				slave <= 0;
				pvalid <= 1;
				sysad_ena <= 1;
				sysad_out <= addr;
				syscmd_out <= { 3'b001, size };
				@(posedge sysclk);
				wait_eok;
				if(cpu_mon)
					$display("%t: %M: re-issue 0x%h", $time, addr);

				pvalid <= 0;
				sysad_ena <= 0;
				sysad_out <= 'bx;
				syscmd_out <= 'bx;
				@(posedge sysclk);
			end

			// wait for read response;
			// return mastership of sysad to cpu;

			@(negedge slave);
			sysad_ena <= 1;
		end
	endtask

	// put random delay between bus requests;

	task req_spacing;
		input [2:0] delay;
		begin
			repeat(delay) @(posedge sysclk);
		end
	endtask

	// make valid byte address for single size;

	function [1:0] sgl_addr;
		input [1:0] size;		// request size;
		reg [1:0] addr;			// valid low-order address bits;
		begin
			case(size)
				2'b00: addr = $random;			// byte;
				2'b01: addr = $random & 2'b10;	// 16-bit word;
				2'b10: addr = $random & 2'b01;	// tri-byte;
				2'b11: addr = 2'b00;			// 32-bit word;
			endcase
			sgl_addr = addr;
		end
	endfunction

	// check read data;

	task rd_check;
		input [2:0] word;		// word to check;
		input [31:0] exp;		// expected data;
		input [31:0] mask;		// compare mask;
		input err;				// extected error;
		begin
			if(mask == 32'h0)
				$display("ERROR: %t: %M: mask of 0", $time);
			if(((data[word] & mask) !== (exp & mask)) | (err !== data_err)) begin
				$display("ERROR: %t: %M: data[%1d] mask 0x%h miscompare 0x%h/%b exp 0x%h/%b",
					$time, word, mask, data[word], data_err, exp, err);
			end
		end
	endtask

	// make valid word address for block size;
	// block addresses are always double-word aligned;

	function [4:3] blk_addr;
		input [1:0] size;		// request size;
		input write;			// want write address;
		reg [4:2] addr;			// valid low-order address bits;
		begin
			case(size)
				2'b00: addr = $random;				// 64-bit word;
				2'b01: addr = $random & 2'b10;		// 16-byte block;
				2'b11: addr = 2'b00;				// 32-byte block;
				2'b11: $display("ERROR: %t: %M: illegal blk size %b", $time, size);
			endcase
			if(write)
				addr = addr & (2'b11 << size);		// sequential write align;
			blk_addr = addr;
		end
	endfunction

	// setup block data pattern;
	// use inverted, byte and bit swapped initial;

	task blk_data;
		input [31:0] word;
		integer n;
		reg [31:0] swap;
		begin
			for(n = 0; n < 32; n = n + 1)
				swap[n] = word[31 - n];
			data[0] = word;
			data[1] = ~data[0];
			data[2] = { word[15:0], word[31:16] };
			data[3] = ~data[2];
			data[4] = { word[23:16], word[31:24], word[7:0], word[15:8] };
			data[5] = ~data[4];
			data[6] = swap;
			data[7] = ~data[6];
		end
	endtask

	// check block read data;

	task blk_check;
		input [1:0] size;		// request size;
		input [31:0] exp;		// expected data;
		input err;				// extected error;
		input [2:0] sbo;		// subblock order;
		reg [31:0] word;		// expected word of burst;
		integer n;
		begin
			if(size == `CPU_SIZE_RSVD)
				$display("ERROR: %t: %M: blk size %b", $time, size);
			rd_check(0 ^ sbo, exp, 32'hffffffff, err);
			rd_check(1 ^ sbo, ~exp, 32'hffffffff, err);
			if((size == `CPU_SIZE_16) | (size == `CPU_SIZE_32)) begin
				word = { exp[15:0], exp[31:16] };
				rd_check(2 ^ sbo, word, 32'hffffffff, err);
				rd_check(3 ^ sbo, ~word, 32'hffffffff, err);
			end
			if(size == `CPU_SIZE_32) begin
				word = { exp[23:16], exp[31:24], exp[7:0], exp[15:8] };
				rd_check(4 ^ sbo, word, 32'hffffffff, err);
				rd_check(5 ^ sbo, ~word, 32'hffffffff, err);
				for(n = 0; n < 32; n = n + 1)
					word[n] = exp[31 - n];
				rd_check(6 ^ sbo, word, 32'hffffffff, err);
				rd_check(7 ^ sbo, ~word, 32'hffffffff, err);
			end
		end
	endtask

	// the simulator is build with either the ipc interface or the verilog tests;
	// both should not coexist because there is no synchronization between them;
	// include various tasks used by both ipc and verilog tests;

`include "tasks/mem_tasks.v"

`ifdef	IPC
`include "ipc.v"
`else	// IPC
`include "test.v"
`endif	// IPC

endmodule
