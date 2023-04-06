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

// $Id: dummy_rdp.v,v 1.1 2002/05/20 23:25:41 berndt Exp $

module rdp(clk, gclk, reset_l, iddq,
   cbus_read_enable,
   cbus_write_enable,
   cbus_select,
   cbus_command, 
   .xbus_cs_data(xbus_data),
   .xbus_cs_valid(cbuf_write),
   vm_in,
   vm_dv,
   flush,
   freeze,
   unfreeze,
   .grant(dma_grant),
   .start(dma_start),
   .finish(dma_last),
   read_grant,
   dma_write_enable,
   dma_read_enable,

   .cs_xbus_req(cbuf_ready),
   vm_out,
   start_gclk,
   .rdramreq(dma_request),
   read_request,
   cmd_busy,
   pipe_busy,
   tmem_busy,
   cbus_data,
   dbus_data,
   ebus_data);

`include "dp.vh"
`include "define.vh"

input clk;
input gclk;
input reset_l;
input iddq;

input cbus_read_enable;
input cbus_write_enable;
input [CBUS_SELECT_SIZE-1:0] cbus_select;
input [CBUS_COMMAND_SIZE-1:0] cbus_command;
input [XBUS_DATA_SIZE-1:0] xbus_data;
input cbuf_write;
input [7:0] vm_in;
input vm_dv;
input flush, freeze, unfreeze;
input dma_grant;
input dma_start;
input dma_last;
input read_grant;
input dma_write_enable;
input dma_read_enable;

output cbuf_ready;
output [15:0] vm_out;
output start_gclk;
output dma_request;
output read_request;
output cmd_busy;
output pipe_busy;
output tmem_busy;

inout [CBUS_DATA_SIZE-1:0] cbus_data;
inout [DBUS_DATA_SIZE-1:0] dbus_data;
inout [EBUS_DATA_SIZE-1:0] ebus_data;


wire dma_read;
wire dma_up;
wire [DRAM_ADDRESS_SIZE-1:0] dma_address;
wire [DMA_LENGTH_SIZE-1:0] dma_length;
wire [CBUS_DATA_SIZE-1:0] reg_read_data;
wire [CBUS_DATA_SIZE-1:0] reg_write_data;
wire [DP_REG_ADDRESS_SIZE-1:0] reg_address;
wire reg_write_enable;

assign cmd_busy = LOW;
assign pipe_busy = HIGH;
assign tmem_busy = LOW;
assign start_gclk = HIGH;

ms_dma ms_dma_0(clk, reset_l, cbus_read_enable, cbus_write_enable,
   cbus_select, cbus_command, read_grant, dma_read, dma_up, dma_address,
   dma_length, reg_read_data, read_request, reg_write_data, reg_address,
   reg_write_enable, cbus_data);

dp_test dp_test_0(clk, reset_l, dma_write_enable, dma_grant, dma_start,
   dma_last, dma_request, dma_read, dma_up, dma_address, dma_length,
   dbus_data);

dp_cbuf dp_cbuf_0(clk, reset_l, cbuf_write, xbus_data, cbuf_ready);

endmodule


module ms_dma(clock, reset_l,
   cbus_read_enable, cbus_write_enable, cbus_select, cbus_command,
   read_grant, dma_read, dma_down, dma_address, dma_length, reg_read_data,
   read_request, reg_write_data, reg_address, reg_write_enable,
   cbus_data);

`include "ms.vh"

parameter READ_DELAY = 8'd2;
parameter WRITE_DELAY = -8'd2;

input clock;
input reset_l;

input cbus_read_enable;
input cbus_write_enable;
input [CBUS_SELECT_SIZE-1:0] cbus_select;
input [CBUS_COMMAND_SIZE-1:0] cbus_command;
input read_grant;
input dma_read;
input dma_down;
input [DRAM_ADDRESS_SIZE-1:0] dma_address;
input [DMA_LENGTH_SIZE-1:0] dma_length;
input [CBUS_DATA_SIZE-1:0] reg_read_data;

output read_request;
output [CBUS_DATA_SIZE-1:0] reg_write_data;
output [DP_REG_ADDRESS_SIZE-1:0] reg_address;
output reg_write_enable;

inout [CBUS_DATA_SIZE-1:0] cbus_data;


// input/output registers
reg read_request;
reg reg_write_enable;
reg [DP_REG_ADDRESS_SIZE-1:0] reg_address;
reg [CBUS_COMMAND_SIZE-1:0] cbus_command_reg;
reg [CBUS_DATA_SIZE-1:0] cbus_data_reg;


// cbus tristate drivers
cbus_driver cbus_driver_0(cbus_data_reg, cbus_write_enable, cbus_data);

assign reg_write_data = cbus_data_reg;


always @(posedge clock) begin : cbus_block
   reg [CBUS_DATA_SIZE-1:0] cbus_data_out;

   case (cbus_select)
      CBUS_ADDRESS_SELECT : cbus_data_out = dma_address;
      CBUS_LENGTH_SELECT : case ({dma_down, dma_read})
         2'b00 : cbus_data_out = {DMA_BLOCK, DMA_MASKED, DMA_UP,
           DMA_NSEQ, BUS_DEVICE_DP_SPAN, WRITE_DELAY, DMA_WRITE, dma_length};

         2'b01 : cbus_data_out = {DMA_BLOCK, DMA_NON_MASKED, DMA_UP,
           DMA_SEQ, BUS_DEVICE_DP_SPAN, READ_DELAY, DMA_READ, dma_length};

         2'b10 : cbus_data_out = {DMA_BLOCK, DMA_MASKED, DMA_DOWN,
           DMA_NSEQ, BUS_DEVICE_DP_SPAN, WRITE_DELAY, DMA_WRITE, dma_length};

         2'b11 : cbus_data_out = {DMA_BLOCK, DMA_NON_MASKED, DMA_DOWN,
           DMA_NSEQ, BUS_DEVICE_DP_SPAN, READ_DELAY, DMA_READ, dma_length};
         endcase
      CBUS_DATA_SELECT : cbus_data_out = reg_read_data;
      default : cbus_data_out = 'bx;
      endcase

   cbus_command_reg <= cbus_command;
   cbus_data_reg <= cbus_read_enable ? cbus_data : cbus_data_out;
   end


always @(posedge clock or negedge reset_l) begin
   if (!reset_l) begin
      // resetable registers
      read_request <= LOW;
      reg_write_enable <= LOW;
      end
   else begin : main_block
      reg next_read_request;
      reg next_reg_write_enable;
      reg [BUS_ID_SIZE-1:0] next_id;
      reg next_select;
      reg next_write_command;
      reg next_read_command;

      next_read_request = read_request;
      next_reg_write_enable = LOW;

      next_id = cbus_data_reg >> BUS_ID_OFFSET;
      next_select = next_id == BUS_ID_SPAN;
      next_write_command = cbus_command_reg == CBUS_WRITE_COMMAND;
      next_read_command = cbus_command_reg == CBUS_READ_COMMAND;

      if (next_select) begin
         if (next_write_command) begin
            next_reg_write_enable = HIGH;
            reg_address <= cbus_data_reg >> 2;
            end
         else if (next_read_command) begin
            next_read_request = HIGH;
            reg_address <= cbus_data_reg >> 2;
            end
         end

      if (read_request && read_grant) begin
         next_read_request = LOW;
         end

      read_request <= next_read_request;
      reg_write_enable <= next_reg_write_enable;
      end
   end
endmodule


module dp_test(clock, reset_l,
   dbus_enable, dma_grant, dma_start, dma_last,
   dma_request, dma_read, dma_up, dma_address, dma_length,
   dbus_data);

`include "dp.vh"

parameter UP   = LOW;
parameter DOWN   = HIGH;

input clock;
input reset_l;

input dbus_enable;
input dma_grant;
input dma_start;
input dma_last;

output dma_request;
output dma_read;
output dma_up;
output [DRAM_ADDRESS_SIZE-1:0] dma_address;
output [DMA_LENGTH_SIZE-1:0] dma_length;

inout [DBUS_DATA_SIZE-1:0] dbus_data;

// input/output registers
reg dma_request;
reg dma_read;
reg dma_up;
reg [DRAM_ADDRESS_SIZE-1:0] dma_address;
reg [DMA_LENGTH_SIZE-1:0] dma_length;
reg [DBUS_DATA_SIZE-1:0] dbus_data_in;
reg [DBUS_DATA_SIZE-1:0] dbus_data_out;


// internal registers
reg [3:0] span_address;
reg busy;
reg test_selected;

// memory buffer
reg [DBUS_DATA_SIZE-1:0] memory[0:'hf];

// state machine
reg [2:0] state;
parameter
   STATE_IDLE           = 0,
   STATE_WRITE          = 1,
   STATE_WRITE_WAIT     = 2,
   STATE_WRITE_DELAY    = 3,
   STATE_READ           = 4,
   STATE_READ_WAIT      = 5;


reg monitor;
initial monitor = $test$plusargs("span_mon");


assign dbus_data = dbus_enable ? dbus_data_out : 64'bz;


always @(posedge clock) begin
   dbus_data_in <= dbus_data;
   end


initial begin
   test_selected <= LOW;
   @(posedge clock);

   wait(`SYSTEM_READY);

   if ($test$plusargs("test_dp_read")) read;
   if ($test$plusargs("test_dp_write")) write;
   if ($test$plusargs("test_dp_copy_up")) copy_up;
   if ($test$plusargs("test_dp_copy_down")) copy_down;
   end


initial begin
   if ($test$plusargs("help")) begin
      $display("dp test arguments include:");
      $display("  +test_dp_read");
      $display("  +test_dp_write");
      $display("  +test_dp_copy_up");
      $display("  +test_dp_copy_down");
      $display("");
      #1 $finish;
      end
   end


task read;
   begin
      test_selected <= HIGH;
      repeat (10) @(posedge clock);

      read_span(BUS_ADDRESS_DRAM, 'h70, UP);
      repeat (10) @(posedge clock);
      $finish;
      end
   endtask


task write;
   integer i;
   reg [31:0] high_half, low_half;

   begin
      test_selected <= HIGH;
      repeat (10) @(posedge clock);

      for (i = 0; i < 16; i = i + 1) begin
         high_half = i + 1;
         low_half = i * 8;
         memory[i] = {high_half, low_half};
         end

      write_span(BUS_ADDRESS_DRAM, 'h70, UP);
      repeat (10) @(posedge clock);
      $finish;
      end
   endtask


task copy_up;
   begin
      test_selected <= HIGH;
      reality.r4200b_0.config_mem;

      repeat (10) @(posedge clock);

      read_span(BUS_ADDRESS_DRAM, 'h48, UP);
      write_span(BUS_ADDRESS_DRAM + 'h90, 'h40, UP);
      read_span(BUS_ADDRESS_DRAM + 'h80, 'h80, UP);
      repeat (10) @(posedge clock);
      $finish;
      end
   endtask


task copy_down;
   begin
      test_selected <= HIGH;
      reality.r4200b_0.config_mem;

      repeat (10) @(posedge clock);

      read_span(BUS_ADDRESS_DRAM + 'h78, 'h48, DOWN);
      write_span(BUS_ADDRESS_DRAM + 'he8, 'h40, DOWN);
      read_span(BUS_ADDRESS_DRAM + 'h80, 'h80, UP);
      repeat (10) @(posedge clock);
      $finish;
      end
   endtask


task write_span;
   input [31:0] address;
   input [31:0] size;
   input up;

   begin
      dma_address <= address;
      dma_length <= size-1;
      dma_read <= LOW;
      dma_up <= up;
      dma_request <= HIGH;
      busy <= HIGH;
      @(posedge clock);
      while (busy) @(posedge clock);
      end
   endtask


task read_span;
   input [31:0] address;
   input [31:0] size;
   input up;

   begin
      dma_address <= address;
      dma_length <= size-1;
      dma_read <= HIGH;
      dma_up <= up;
      dma_request <= HIGH;
      busy <= HIGH;
      @(posedge clock);
      while (busy) @(posedge clock);
      end
   endtask


always @(posedge clock or negedge reset_l) begin
   if (!reset_l) begin
      dma_request <= LOW;
      busy <= LOW;
      state <= STATE_IDLE;
      end
   else begin
      case (state)
         STATE_IDLE : begin
            span_address <= 0;
            if (dma_grant) begin
               // DMA operation has begun
               dma_request <= LOW;
               if (dma_read) begin
                  state <= STATE_READ_WAIT;
                  end
               else begin
                  state <= STATE_WRITE_WAIT;
                  end
               end
            end

         STATE_READ_WAIT : begin
            if (dma_start) begin
               memory[span_address] <= dbus_data_in;
               span_address <= span_address + 1;

               if (monitor) begin
                  $display(`CLOCK_COUNT, " : span write - %h @ %h",
                     dbus_data_in, span_address);
                  end

               if (dma_last) begin
                  busy <= LOW;
                  state <= STATE_IDLE;
                  end
               else begin
                  state <= STATE_READ;
                  end
               end
            else begin
               state <= STATE_READ_WAIT;
               end
            end

         STATE_READ : begin
            memory[span_address] <= dbus_data_in;
            span_address <= span_address + 1;

            if (monitor) begin
               $display(`CLOCK_COUNT, " : span write - %h @ %h",
                  dbus_data_in, span_address);
               end

            if (dma_last) begin
               busy <= LOW;
               state <= STATE_IDLE;
               end
            else begin
               state <= STATE_READ;
               end
            end

         STATE_WRITE_WAIT : begin
            if (dma_start) begin
               dbus_data_out <= memory[span_address];
               span_address <= span_address + 1;

               if (monitor) begin
                  $display(`CLOCK_COUNT, " : span read  - %h @ %h",
                     memory[span_address], span_address);
                  end

               if (dma_last) begin
                  state <= STATE_WRITE_DELAY;
                  end
               else begin
                  state <= STATE_WRITE;
                  end
               end
            else begin
               state <= STATE_WRITE_WAIT;
               end
            end

         STATE_WRITE : begin
            dbus_data_out <= memory[span_address];
            span_address <= span_address + 1;

            if (monitor) begin
               $display(`CLOCK_COUNT, " : span read  - %h @ %h",
                  memory[span_address], span_address);
               end

            if (dma_last) begin
               state <= STATE_WRITE_DELAY;
               end
            else begin
               state <= STATE_WRITE;
               end
            end

         STATE_WRITE_DELAY : begin
            dbus_data_out <= memory[span_address];
            span_address <= span_address + 1;

            if (monitor) begin
               $display(`CLOCK_COUNT, " : span read  - %h @ %h",
                  memory[span_address], span_address);
               end

            busy <= LOW;
            state <= STATE_IDLE;
            end
         endcase
      end
   end
endmodule


module dp_cbuf (clock, reset_l,
   cbuf_write, xbus_data,
   cbuf_ready);

`include "dp.vh"

parameter BUFFER_SIZE = 32;
parameter ADDRESS_SIZE = 6;
parameter LOW_WATER = 10;

input clock;
input reset_l;
input cbuf_write;
input [XBUS_DATA_SIZE-1:0] xbus_data;
output cbuf_ready;

// output registers
reg cbuf_ready;

// internal registers
reg [ADDRESS_SIZE-1:0] write_pointer;
reg [ADDRESS_SIZE-1:0] read_pointer;
reg cbuf_read;

wire [XBUS_DATA_SIZE-1:0] read_data;

// pseudo registers
reg [ADDRESS_SIZE-1:0] count;
reg [ADDRESS_SIZE-1:0] next_write_pointer;
reg [ADDRESS_SIZE-1:0] next_read_pointer;

wire [ADDRESS_SIZE-2:0] write_address;
wire [ADDRESS_SIZE-2:0] read_address;
wire write_flag;
wire read_flag;
wire empty;

// memory
reg [XBUS_DATA_SIZE-1:0] buffer [0:BUFFER_SIZE-1];

reg monitor_enable;
initial monitor_enable = $test$plusargs("cbuf_mon");

assign {write_flag, write_address} = write_pointer;
assign {read_flag, read_address} = read_pointer;
assign read_data = buffer[read_address];
assign empty = read_pointer == write_pointer;

always @(posedge clock) begin
   if (!reset_l) begin
      cbuf_ready <= HIGH;
      write_pointer <= 0;
      read_pointer <= 0;
      end
   else begin
      if (cbuf_write) begin
         buffer[write_address] <= xbus_data;
         end

      write_pointer <= cbuf_write
         ? write_pointer + 1
         : write_pointer;

      read_pointer <= (cbuf_read && !empty)
         ? read_pointer + 1
         : read_pointer;

      cbuf_ready <= (write_pointer - read_pointer) <= (BUFFER_SIZE - LOW_WATER);

      if (cbuf_write && !cbuf_read
         && read_address == write_address
         && read_flag != write_flag) begin
         $display("Panic!  Cbuf overflow.");
         $finish;
         end

      if (cbuf_write & monitor_enable) begin
         $display(`CLOCK_COUNT,
            " : cbuf write - %h of %d", xbus_data, write_pointer-read_pointer);
         end

      if (cbuf_read & !empty & monitor_enable) begin
         $display(`CLOCK_COUNT,
            " : cbuf read  - %h of %d", read_data, write_pointer-read_pointer);
         end
      end
   end


// consumer
// parameter THRESHOLD = 'h00;
parameter THRESHOLD = 'h20;
parameter START_DATA = 64'h0000_0000_0000_0000;
reg [7:0] rand;
reg [XBUS_DATA_SIZE-1:0] expect_data;

always @(posedge clock) begin
   rand = $random;
   cbuf_read <= rand < THRESHOLD;
   if (cbuf_read && !empty) begin
      if (read_data == START_DATA) begin
         expect_data = START_DATA;
         end
      else if (read_data !== expect_data) begin
         $display("Panic!  Unexpected cbuf read data - expect %h, actual %h",
            expect_data, read_data);
         $finish;
         end
      expect_data = expect_data + 8;
      end
   end
endmodule

