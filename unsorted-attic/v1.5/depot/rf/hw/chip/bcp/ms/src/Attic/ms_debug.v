 /************************************************************************\
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 \************************************************************************/

// $Id: ms_debug.v,v 1.4 2002/12/27 01:40:16 rws Exp $

//mods history
//1-4  Fixed a bug in the span buffer test modes (made WE's unknown);
//  rename test_mode to "test_mode0", output to reset rb*ptrs in ms_sc;
//  add new reg "test_mode1" and output to ms_si (kill spanbuf we's from rdram),
//	and output to ms_rp (force setting c/zwmzero to kill rdram writes); 
//	input:  rbc/zr/wptrs, stall contributors;
//1-5  add rel_sync_full to observability; also stb_sync_full;

module ms_debug(clock, reset_l,
   reg_write_enable, reg_address, reg_write_data, 
//    bist_done, bist_fail,
   we0, we1, addr0, addr1, din, dout,
   rbcrptrd, rbcwptrd, rbzrptrd, rbzwptrd,
   stallrdctxtd, stallwrctxtd, stallczwmd,
   stallcrd, stallcwd, stallzrd, stallzwd,
   stopgclockd, rel_sync_full, stb_sync_full,
   reg_read_data, bist_go, bist_check,
   test_mode0, test_mode1,
   we0d, we1d, addr0d, addr1d, dind);

`include "dp.vh"

input clock;					// system clock
input reset_l;					// system reset_l

input [31:0] reg_write_data;	// *diag* register wrdata
input [DP_REG_ADDRESS_SIZE-1:0] reg_address;	// *diag* reg r/w address
input reg_write_enable;				// *diag* reg write enable
// input bist_done;				// TMEM BIST done (pulse)
// input [DP_BIST_FAIL_SIZE-1:0] bist_fail;	// TMEM BIST fail (pulse)
input we0;
input we1;
input [3:0] addr0;
input [3:0] addr1;
input [143:0] din;
input [143:0] dout;
input [3:0] rbcrptrd, rbcwptrd, rbzrptrd, rbzwptrd;
					//monitor circular buffer ptrs |w-r|=8
input stallrdctxtd, stallwrctxtd, stallczwmd;	//monitor stalls
input stallcrd, stallcwd, stallzrd, stallzwd;	//monitor stalls, ctd.
input stopgclockd;
input rel_sync_full;
input stb_sync_full;

output [31:0] reg_read_data;	// *diag* read data to cbus
output bist_go;					// start IMEM BIST
output bist_check;				// BIST BIST
output we0d;
output we1d;
output [3:0] addr0d;
output [3:0] addr1d;
output [143:0] dind;
output test_mode0;
output test_mode1;

// input/output registers
reg bist_go;
reg bist_check;
reg bist_done_reg;
reg [DP_BIST_FAIL_SIZE-1:0] bist_fail_reg;
reg test_mode0;
reg test_mode1;
reg [6:0] test_addr;
reg [71:0] staged_data;
reg rel_sync_fulld;
reg stb_sync_fulld;


wire [31:0] test_data;

assign we0d   = !test_mode0 ? we0   : ((test_addr[2:0]==3) && 
					reg_address==DP_DATA && reg_write_enable);
assign we1d   = !test_mode0 ? we1   : ((test_addr[2:0]==7) &&  
					reg_address==DP_DATA && reg_write_enable);
assign addr0d = !test_mode0 ? addr0 : test_addr[6:3];
assign addr1d = !test_mode0 ? addr1 : test_addr[6:3];
assign dind   = !test_mode0 ? din   : {staged_data, staged_data};

assign reg_read_data = !reg_address[1] ?
                                (!reg_address[0] ?
                                        {bist_fail_reg, bist_done_reg,
					bist_go, bist_check} :
        		{rbcwptrd, rbcrptrd, rbzwptrd, rbzrptrd,
			stallcrd, stallcwd, stallzrd, stallzwd,
			stopgclockd, stallrdctxtd, stallwrctxtd, stallczwmd,
			stb_sync_fulld, rel_sync_fulld, test_mode1, test_mode0}) :
                                (!reg_address[0] ?
                                        test_addr :
                                        test_data) ;
assign test_data =
	!test_addr[2] ?
		(!test_addr[1] ?
			(!test_addr[0] ?
				{dout[143:128], dout[125:110]} :
				{dout[107: 92], dout[ 89: 74]} ) :
			(!test_addr[0] ?
				{dout[127:126], dout[109:108],
				 dout[ 91: 90], dout[ 73: 72]} :
				0 )) :
		(!test_addr[1] ?
			(!test_addr[0] ?
				{dout[ 71: 56], dout[ 53: 38]} :
				{dout[ 35: 20], dout[ 17:  2]} ) :
			(!test_addr[0] ?
				{dout[ 55: 54], dout[ 37: 36],
				 dout[ 19: 18], dout[  1:  0]} :
				0 )) ;

always @(posedge clock) begin
	if (!reset_l) begin
		// resetable registers
		bist_go <= LOW;
		bist_check <= LOW;
		test_mode0 <= 0;
		test_mode1 <= 0;
		end
	else begin : main_block
		reg next_bist_done;
		reg [DP_BIST_FAIL_SIZE-1:0] next_bist_fail;

		// bist pulse capture
		next_bist_done = bist_done_reg; //  JCM | bist_done;
		next_bist_fail = bist_fail_reg; //  JCM | bist_fail;

                rel_sync_fulld <= rel_sync_full;
		stb_sync_fulld <= stb_sync_full;

		if (reg_write_enable)
			begin
			case (reg_address)
			DP_BIST : begin : bist_block
				reg clear_bist;
				reg next_bist_go;
				reg next_bist_check;

				{clear_bist, next_bist_go,
				next_bist_check} = reg_write_data;

				bist_go <= next_bist_go;
				bist_check <= next_bist_check;

				if (clear_bist)
					begin
					next_bist_done = LOW;
					next_bist_fail = 0;
					end
				end
			DP_MODE : 
				begin
				test_mode1 <= reg_write_data[1];
				test_mode0 <= reg_write_data[0];
				end
			DP_ADDR : 
				begin
				test_addr <= reg_write_data[6:0];
				end
			DP_DATA : 
				begin
				case (test_addr[1:0])
				0:
					begin
					{staged_data[ 71: 56],
					 staged_data[ 53: 38]} <=
						reg_write_data;
					end
				1:
					begin
					{staged_data[ 35: 20],
					 staged_data[ 17:  2]} <=
						reg_write_data;
					end
				2:
					begin
					{staged_data[ 55: 54],
					 staged_data[ 37: 36],
					 staged_data[ 19: 18],
					 staged_data[  1:  0]} <=
						reg_write_data[7:0];
					end
				endcase
				end
			endcase
			end
		bist_done_reg <= next_bist_done;
		bist_fail_reg <= next_bist_fail;
		end
	end

endmodule
