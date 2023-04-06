module rsp (.clk(clock), reset_l, iddq_test,
   sp_cbus_read_enable, sp_cbus_write_enable, mem_cbus_write_enable,
   cmd_cbus_read_enable, cmd_cbus_write_enable, cbus_select,
   cbus_command, dma_start, dma_last, sp_dma_grant, sp_read_grant,
   cmd_dma_grant, cmd_read_grant, sp_dbus_read_enable,
   sp_dbus_write_enable, cbuf_ready,
   cmd_busy, pipe_busy, tmem_busy, frozen,
   sp_dma_request, sp_read_request, mem_read_request, cmd_dma_request,
   cmd_read_request, cbuf_write, flush, freeze, unfreeze, sp_interrupt,
   xbus_data, cbus_data, dbus_data);

`include "sp.vh"
`include "define.vh"

input clock;
input reset_l;
input iddq_test;

input sp_cbus_read_enable;
input sp_cbus_write_enable;
input mem_cbus_write_enable;
input cmd_cbus_read_enable;
input cmd_cbus_write_enable;
input [CBUS_SELECT_SIZE-1:0] cbus_select;
input [CBUS_COMMAND_SIZE-1:0] cbus_command;
input dma_start;
input dma_last;
input sp_dma_grant;
input sp_read_grant;
input cmd_dma_grant;
input cmd_read_grant;
input sp_dbus_read_enable;
input sp_dbus_write_enable;
input cbuf_ready;
input cmd_busy;
input pipe_busy;
input tmem_busy;
input frozen;

output sp_dma_request;
output sp_read_request;
output mem_read_request;
output cmd_dma_request;
output cmd_read_request;
output cbuf_write;
output flush;
output freeze;
output unfreeze;
output sp_interrupt;
output [XBUS_DATA_SIZE-1:0] xbus_data;

inout [CBUS_DATA_SIZE-1:0] cbus_data;
inout [DBUS_DATA_SIZE-1:0] dbus_data;

wire [SP_REG_DATA_SIZE-1:0] cp0_data;
wire cp0_cmd_select;
wire [SP_REG_ADDRESS_SIZE-1:0] cp0_address;
wire cp0_write;
wire cp0_read;
wire cp0_enable;

wire imem_select;
wire [SP_MEM_ADDRESS_SIZE-1:0] mem_address;
wire mem_read;
wire mem_write;
wire [SP_MEM_MASK_SIZE-1:0] mem_mask;
wire xbus_dmem_dma;
wire halt;
wire single_step;
wire dma_busy;
wire set_broke;
wire cmd_ready;
wire cmd_read;
wire [SP_MEM_ADDRESS_SIZE-1:0] cmd_address;
wire pc_write;
wire [SP_PC_SIZE-1:0] pc_data;

reg bist_done;
reg [SP_BIST_FAIL_SIZE-1:0] bist_fail;
wire bist_go;
wire bit_check;

always @(negedge reset_l) begin
   bist_done = LOW;
   bist_fail = 0;
   end

assign set_broke = LOW;

io_cmd_dma io_cmd_dma_0(clock, reset_l,
   cp0_enable, cmd_cbus_read_enable, cmd_cbus_write_enable, cbus_select,
   cbus_command, dma_start, dma_last, cmd_dma_grant, cmd_read_grant,
   cbuf_ready, cp0_cmd_select, cp0_address, cp0_write, cmd_ready, cmd_busy,
   pipe_busy, tmem_busy, frozen, cmd_dma_request, cmd_read_request, cbuf_write,
   xbus_dmem_dma, cmd_read, cmd_address, flush, freeze, unfreeze, cp0_data,
   cbus_data);

io_mem_dma io_mem_dma_0(clock, reset_l,
   cp0_enable, sp_cbus_read_enable, sp_cbus_write_enable, cbus_select,
   cbus_command, dma_start, dma_last, sp_dma_grant, sp_read_grant,
   cp0_cmd_select, cp0_address, cp0_read, cp0_write, set_broke, cmd_read,
   cmd_address, bist_done, bist_fail, sp_dma_request, sp_read_request,
   mem_read_request, imem_select, mem_address, mem_read, mem_write, mem_mask,
   halt, single_step, dma_busy, cmd_ready, pc_write, pc_data, io_read_select,
   io_write_select, mem_load, io_load, sp_interrupt, bist_go, bist_check,
   cp0_data, cbus_data);

sp_mem sp_mem_0(clock, reset_l,
   imem_select, xbus_dmem_dma, mem_cbus_write_enable, sp_dbus_read_enable,
   sp_dbus_write_enable, mem_address,
   mem_read, mem_write, mem_mask, io_read_select, io_write_select, mem_load,
   io_load, xbus_data, cbus_data, dbus_data);

sp_test sp_test_0(clock, reset_l,
   {cp0_cmd_select, cp0_address}, cp0_read, cp0_write, cp0_enable, cp0_data);

endmodule

module sp_mem (clock, reset_l,
   dbus_imem_select, xbus_dmem_select, cbus_write_enable, dbus_read_enable,
   dbus_write_enable, mem_address, mem_read, mem_write, mem_mask,
   io_read_select, io_write_select, mem_load, io_load,
   xbus_data,
   cbus_data, dbus_data);

`include "sp.vh"
parameter DMEM_SIZE = 'h100;
parameter IMEM_SIZE = 'h200;

input clock;
input reset_l;

input dbus_imem_select;
input xbus_dmem_select;
input cbus_write_enable;
input dbus_write_enable;
input dbus_read_enable;
input [SP_MEM_ADDRESS_SIZE-1:0] mem_address;
input mem_read;
input mem_write;
input [SP_MEM_MASK_SIZE-1:0] mem_mask;
input io_read_select;
input io_write_select;
input mem_load;
input io_load;

output [XBUS_DATA_SIZE-1:0] xbus_data;

inout [CBUS_DATA_SIZE-1:0] cbus_data;
inout [DBUS_DATA_SIZE-1:0] dbus_data;

// memory arrays
reg [DBUS_DATA_SIZE-1:0] even_dmem[0:DMEM_SIZE-1], odd_dmem[0:DMEM_SIZE-1];
reg [DBUS_DATA_SIZE-1:0] imem[0:IMEM_SIZE-1];

// dmem registers
reg [SP_MEM_ADDRESS_SIZE-2:0] even_address, odd_address;
reg [DBUS_DATA_SIZE-1:0] even_write_data, odd_write_data;
reg [DBUS_DATA_SIZE-1:0] even_read_data, odd_read_data;
reg [SP_MEM_MASK_SIZE-1:0] even_write_enable, odd_write_enable;
reg [SP_MEM_MASK_SIZE-1:0] mem_mask_pl;
reg dmem_write_1;
reg dmem_read_1, dmem_read_2, dmem_read_3;
reg [DBUS_DATA_SIZE-1:0] secondary_read_data;
reg [DBUS_DATA_SIZE-1:0] secondary_write_data;
reg swap_1, swap_2;

// bus registers
reg [DBUS_DATA_SIZE-1:0] dbus_data_reg;
reg [CBUS_DATA_SIZE-1:0] cbus_data_reg;

// imem registers
reg imem_read_1, imem_read_2, imem_read_3;
reg imem_write_1, imem_write_2;
reg [SP_MEM_ADDRESS_SIZE-1:0] imem_address;
reg [DBUS_DATA_SIZE-1:0] imem_read_data;
reg [DBUS_DATA_SIZE-1:0] imem_write_data;

// busses
wire [DBUS_DATA_SIZE-1:0] dmem_read_data;
wire [DBUS_DATA_SIZE-1:0] primary_read_bus, secondary_read_bus;
wire [DBUS_DATA_SIZE-1:0] even_write_bus, odd_write_bus;
wire [DBUS_DATA_SIZE-1:0] mem_read_data;
wire [SP_MEM_MASK_SIZE-1:0] even_mask, odd_mask;
wire swap;
wire [CBUS_DATA_SIZE-1:0] mem_read_data_0, mem_read_data_1;
wire [CBUS_DATA_SIZE-1:0] io_read_data;
wire [CBUS_DATA_SIZE-1:0] mem_load_data;
wire [DBUS_DATA_SIZE-1:0] io_write_data;
wire [DBUS_DATA_SIZE-1:0] mem_write_data;
wire [CBUS_DATA_SIZE-1:0] next_cbus_data;
wire [DBUS_DATA_SIZE-1:0] next_dbus_data;

// debug registers
reg [SP_MEM_ADDRESS_SIZE-2:0] even_address_1, odd_address_1;
reg [SP_MEM_ADDRESS_SIZE-1:0] imem_address_1;

initial if ($test$plusargs("load_dmem")) begin
   $display("loading DMEM from dmem_even.data and dmem_odd.data...");
   $readmemh("dmem_even.data", even_dmem);
   $readmemh("dmem_odd.data", odd_dmem);
   end


initial if ($test$plusargs("load_imem")) begin
   $display("loading IMEM from imem.data...");
   $readmemh("imem.data", imem);
   end


reg mem_monitor;
initial mem_monitor = $test$plusargs("mem_mon");

cbus_driver cbus_driver_0(
   .cbus_data_out(cbus_data_reg),
   .cbus_enable(cbus_write_enable),
   .cbus_data(cbus_data));

dbus_driver dbus_driver_0(
   .dbus_data_out(dbus_data_reg),
   .dbus_enable(dbus_write_enable),
   .dbus_data(dbus_data));

// dma muxes
assign dmem_read_data = dmem_read_3 ? primary_read_bus : secondary_read_data;
assign primary_read_bus = swap_2 ? odd_read_data : even_read_data;
assign secondary_read_bus = swap_2 ? even_read_data : odd_read_data;
assign even_write_bus = swap ? dbus_data_reg : secondary_write_data;
assign odd_write_bus = swap ? secondary_write_data : dbus_data_reg;
assign mem_read_data = imem_read_3 ? imem_read_data : dmem_read_data;

assign even_mask = swap ? mem_mask : mem_mask_pl;
assign odd_mask = swap ? mem_mask_pl : mem_mask;
assign swap = mem_address[0];

// bus muxes
assign {mem_read_data_0, mem_read_data_1} = mem_read_data;
assign io_read_data = io_read_select ? mem_read_data_1 : mem_read_data_0;
assign mem_load_data = mem_load ? io_read_data : cbus_data_reg;
assign io_write_data = io_read_select
   ? {mem_read_data_0, cbus_data_reg}
   : {cbus_data_reg, mem_read_data_1};
assign mem_write_data = io_write_select ? io_write_data : dbus_data_reg;
assign next_cbus_data = io_load ? cbus_data : mem_load_data;
assign next_dbus_data = dbus_read_enable ? dbus_data : mem_read_data;

assign xbus_data = xbus_dmem_select ? dmem_read_data : dbus_data_reg;

always @(posedge clock) begin : main_block
   reg [DBUS_DATA_SIZE/2-1:0] old_data_low, old_data_high;
   reg [DBUS_DATA_SIZE/2-1:0] new_data_low, new_data_high;

   // ************************* DMEM model ***********************

   dmem_write_1 <= mem_write && !dbus_imem_select;
   dmem_read_1 <= mem_read && !dbus_imem_select;
   dmem_read_2 <= dmem_read_1;
   dmem_read_3 <= dmem_read_2;

   // swap address/data flag
   swap_1 <= swap;
   swap_2 <= swap_1;

   // load secondary register
   secondary_read_data <= secondary_read_bus;
   secondary_write_data <= mem_write_data;

   // load address registers
   if (dmem_write_1 || dmem_read_1) begin
      even_address <= mem_address[SP_MEM_ADDRESS_SIZE-1:1] + swap;
      odd_address <= mem_address[SP_MEM_ADDRESS_SIZE-1:1];
      end
   else begin
      even_address <= 'bx;
      odd_address <= 'bx;
      end

   // DMA read pipeline
   mem_mask_pl <= mem_mask;

   if (dmem_write_1) begin
      even_write_enable <= even_mask;
      even_write_data <= even_write_bus;
      odd_write_enable <= odd_mask;
      odd_write_data <= odd_write_bus;
      end
   else begin
      even_write_enable <= 0;
      even_write_data <= 64'bx;
      odd_write_enable <= 0;
      odd_write_data <= 64'bx;
      end

   {old_data_low, old_data_high} = even_dmem[even_address];
   {new_data_low, new_data_high} = even_write_data;
   even_dmem[even_address] <= {
     even_write_enable[1] ? new_data_low : old_data_low,
     even_write_enable[0] ? new_data_high : old_data_high};

   {old_data_low, old_data_high} = odd_dmem[odd_address];
   {new_data_low, new_data_high} = odd_write_data;
   odd_dmem[odd_address] <= {
     odd_write_enable[1] ? new_data_low : old_data_low,
     odd_write_enable[0] ? new_data_high : old_data_high};

   // DMA write pipeline
   even_read_data <= even_dmem[even_address];
   odd_read_data <= odd_dmem[odd_address];


   // ************************* IMEM model ***********************

   imem_write_1 <= mem_write && dbus_imem_select;
   imem_write_2 <= imem_write_1;

   imem_read_1 <= mem_read && dbus_imem_select;
   imem_read_2 <= imem_read_1;
   imem_read_3 <= imem_read_2;

   if (imem_write_1 || imem_read_1) begin
      imem_address <= mem_address;
      end
   else begin
      imem_address <= 'bx;
      end

   if (imem_write_1) begin
      imem_write_data <= mem_write_data;
      end
   else begin
      imem_write_data <= 64'bx;
      end

   if (imem_write_2) begin
      imem[imem_address] <= imem_write_data;
      end

   imem_read_data <= imem[imem_address];


   // ********************** interface *********************

   cbus_data_reg <= next_cbus_data;
   dbus_data_reg <= next_dbus_data;

   // DMEM monitor
   even_address_1 <= even_address;
   odd_address_1 <= odd_address;
   if (mem_monitor) begin : debug_block
      reg [31:0] high_data, low_data;

      if (swap_1) begin
         if (odd_write_enable) begin
            {high_data, low_data} = odd_write_data;
            $write(`CLOCK_COUNT, " : DMEM write - ");
            if (odd_write_enable[1]) begin
               $write("%h", high_data);
               end
            else begin
               $write("--------");
               end
            if (odd_write_enable[0]) begin
               $write("%h", low_data);
               end
            else begin
               $write("--------");
               end
            $display(" @ %h", odd_address * 16 + 8);
            end
         if (even_write_enable) begin
            {high_data, low_data} = even_write_data;
            $write(`CLOCK_COUNT, " : DMEM write - ");
            if (even_write_enable[1]) begin
               $write("%h", high_data);
               end
            else begin
               $write("--------");
               end
            if (even_write_enable[0]) begin
               $write("%h", low_data);
               end
            else begin
               $write("--------");
               end
            $display(" @ %h", even_address * 16);
            end
         end
      else begin   
         if (even_write_enable) begin
            {high_data, low_data} = even_write_data;
            $write(`CLOCK_COUNT, " : DMEM write - ");

            if (even_write_enable[1]) begin
               $write("%h", high_data);
               end
            else begin
               $write("--------");
               end

            if (even_write_enable[0]) begin
               $write("%h", low_data);
               end
            else begin
               $write("--------");
               end

            $display(" @ %h", even_address * 16);
            end

         if (odd_write_enable) begin
            {high_data, low_data} = odd_write_data;
            $write(`CLOCK_COUNT, " : DMEM write - ");

            if (odd_write_enable[1]) begin
               $write("%h", high_data);
               end
            else begin
               $write("--------");
               end

            if (odd_write_enable[0]) begin
               $write("%h", low_data);
               end
            else begin
               $write("--------");
               end

            $display(" @ %h", odd_address * 16 + 8);
            end
         end

      if (dmem_read_3) begin   
         if (swap_2) begin
            $display(`CLOCK_COUNT, " : DMEM read  - %h @ %h",
               odd_read_data, odd_address_1 * 16 + 8);
            $display(`CLOCK_COUNT, " : DMEM read  - %h @ %h",
               even_read_data, even_address_1 * 16);
            end
         else begin
            $display(`CLOCK_COUNT, " : DMEM read  - %h @ %h",
               even_read_data, even_address_1 * 16);
            $display(`CLOCK_COUNT, " : DMEM read  - %h @ %h",
               odd_read_data, odd_address_1 * 16 + 8);
            end
         end
      end


   // IMEM monitor
   imem_address_1 <= imem_address;
   if (mem_monitor) begin
      if (imem_read_3) begin
         $display(`CLOCK_COUNT, " : IMEM read  - %h @ %h",
            imem_read_data, imem_address_1 * 8);
         end
      if (imem_write_2) begin
         $display(`CLOCK_COUNT, " : IMEM write - %h @ %h",
           imem_write_data, imem_address * 8);
         end
      end
   end
endmodule


module sp_test (clock, reset_l,
   cp0_address, cp0_read, cp0_write, cp0_enable, cp0_data);

`include "sp.vh"

parameter
   DMA_MEM_ADDRESS      = 0,
   DMA_DBUS_ADDRESS      = 1,
   DMA_READ_LENGTH      = 2,
   DMA_WRITE_LENGTH      = 3,
   DMA_STATUS            = 4,
   CMD_START_ADDRESS      = 8,
   CMD_END_ADDRESS      = 9,
   CMD_CURRENT_ADDRESS   = 10,
   CMD_STATUS            = 11,
   COUNTER_CLOCK          = 12,
   COUNTER_CMD             = 13,
   COUNTER_PIPE          = 14,
   COUNTER_TMEM          = 15;

input clock;
input reset_l;

output [SP_REG_ADDRESS_SIZE:0] cp0_address;
output cp0_read;
output cp0_write;
output cp0_enable;
inout [SP_REG_DATA_SIZE-1:0] cp0_data;


reg [SP_REG_ADDRESS_SIZE:0] cp0_address;
reg cp0_enable;
reg cp0_read;
reg cp0_write;
reg [SP_REG_DATA_SIZE-1:0] cp0_data_out;

reg test_selected;

assign cp0_data = cp0_enable ? 32'bz : cp0_data_out;

initial begin
   cp0_read <= LOW;
   cp0_write <= LOW;
   cp0_enable <= LOW;
   test_selected <= LOW;

   wait(`SYSTEM_READY);

   @(posedge clock);

   if ($test$plusargs("test_sp_cbuf_dma")) cbuf_dma;
   if ($test$plusargs("test_sp_copy_imem")) copy_imem;
   if ($test$plusargs("test_sp_copy_dmem_aligned")) copy_dmem_aligned;
   if ($test$plusargs("test_sp_start_end_hazard")) start_end_hazard;
   if ($test$plusargs("test_sp_dbus_hazard")) dbus_hazard;
   if ($test$plusargs("test_sp_ras_again")) ras_again;
   if ($test$plusargs("test_sp_read_aligned")) read_aligned;
   if ($test$plusargs("test_sp_miss")) miss;
   if ($test$plusargs("test_sp_write_dmem_aligned")) write_dmem_aligned;
   if ($test$plusargs("test_sp_write_dmem_hazard")) write_dmem_hazard;
   if ($test$plusargs("test_sp_read_write_hazard")) read_write_hazard;
end


initial begin
   if ($test$plusargs("help")) begin
      $display("sp test arguments include:");
      $display("  +test_sp_cbuf_dma");
      $display("  +test_sp_copy_imem");
      $display("  +test_sp_copy_dmem_aligned");
      $display("  +test_sp_start_end_hazard");
      $display("  +test_sp_dbus_hazard");
      $display("  +test_sp_ras_again");
      $display("  +test_sp_read_aligned");
      $display("  +test_sp_miss");
      $display("  +test_sp_write_dmem_aligned");
      $display("  +test_sp_write_dmem_hazard");
      $display("  +test_sp_read_write_hazard");
      $display("");
      #0 $finish;
      end
   end

parameter START_ADDRESS = 'h0000_0000;
parameter END_ADDRESS   = 'h0000_0200;
parameter NUM_PACKETS   = 20;
reg [6:0] request_size;
reg [31:0] next_address, current_address, end_address;
reg [5:0] delay;

task cbuf_dma;
   begin
      test_selected <= HIGH;
      reality.r4200b_0.config_mem;

      // initial conditions
      next_address = END_ADDRESS;
      end_address = END_ADDRESS;
      write_reg(CMD_START_ADDRESS, next_address);
      write_reg(CMD_END_ADDRESS, end_address);

      repeat (NUM_PACKETS) begin
         delay = $random;
         request_size = $random * 8;
         while (request_size == 0) request_size = $random * 8;
         end_address = next_address + request_size;

         repeat (delay) begin
            cp0_write <= LOW;
            @(posedge clock);
            end   

         // wrap the buffer if the packet will not fit
         if (end_address > END_ADDRESS) begin
            // Wait until the current pointer advances past the
            // start address.  Be sure to leave START_ADDRESS
            // empty to prevent wrapping.
            read_reg(CMD_CURRENT_ADDRESS, current_address);
            while (current_address > next_address
              || current_address == START_ADDRESS) begin
               read_reg(CMD_CURRENT_ADDRESS, current_address);
               end
            next_address = START_ADDRESS;
            end_address = request_size;

            write_reg(CMD_START_ADDRESS, next_address);
            cp0_write <= LOW;
            end

         // this leaves one word empty to prevent wrapping
         read_reg(CMD_CURRENT_ADDRESS, current_address);
         while (current_address > next_address
           && current_address <= end_address) begin
            read_reg(CMD_CURRENT_ADDRESS, current_address);
            end

         write_reg(CMD_END_ADDRESS, end_address);
         cp0_write <= LOW;
         next_address = end_address;
         end

      repeat(1000) @(posedge clock);
      $finish;
      end
   endtask


task write_reg;
   input [31:0] address, data;

   begin
      cp0_enable <= LOW;
      cp0_write <= HIGH;
      cp0_address <= address;
      cp0_data_out <= data;
      @(posedge clock);
      end
   endtask


task read_reg;
   input [31:0] address;
   output [31:0] data;

   begin
      cp0_enable <= HIGH;
      cp0_address <= address;
      @(posedge clock);
      data = cp0_data;
      end
   endtask


task copy_imem;
   parameter length = 40 * 8;
   begin
      test_selected <= HIGH;

      repeat (10) @(posedge clock);

      reality.r4200b_0.config_mem;

      dma_read ('h1000, 'h000, 0, 0, length-1);
      dma_write('h1000, 'h800, 0, 0, length-1);
      dma_read ('h1800, 'h800, 0, 0, length-1);
      dma_write('h1800, 'h100, 0, 0, length-1);

      cp0_enable <= HIGH;
      cp0_address <= DMA_STATUS;
      @(posedge clock);
      while (cp0_data[2]) @(posedge clock);

      repeat(10) @(posedge clock);
      $finish;
      end
   endtask


task copy_dmem_aligned;
   begin
      test_selected <= HIGH;

      repeat (10) @(posedge clock);

      reality.r4200b_0.config_mem;

      dma_write((8*32)*0+0, (8*32)*0+0, 8*(32-5), 3, 8*5-1);
      dma_read ((8*32)*4+0, (8*32)*0+0, 8*(32-5), 3, 8*5-1);
      dma_write ((8*32)*4+0, (8*32)*4+0, 8*(32-5), 3, 8*5-1);

      cp0_enable <= HIGH;
      cp0_address <= DMA_STATUS;
      @(posedge clock);
      while (cp0_data[2]) @(posedge clock);

      repeat(10) @(posedge clock);
      $finish;
      end
   endtask


task start_end_hazard;
   begin
      test_selected <= HIGH;
      reality.r4200b_0.config_mem;

      dma_write(8, 'h008, 0, 0, 16 * 8 - 1);
      dma_read (8, 'h008, 0, 0, 16 * 8 - 1);
      dma_write(8, 'h008, 0, 0, 16 * 8 - 1);
      dma_read (8, 'h008, 0, 0, 16 * 8 - 1);

      cp0_enable <= HIGH;
      cp0_address <= DMA_STATUS;
      @(posedge clock);
      while (cp0_data[2]) @(posedge clock);
      repeat(10) @(posedge clock);
      $finish;
      end
   endtask


task ras_again;
   begin
      test_selected <= HIGH;
      reality.r4200b_0.config_mem;

      // dirty misses
      dma_write( 0*8, 'h00_0000, 0, 0,  1*8 - 1);
      dma_write( 1*8, 'h00_0800, 0, 0,  1*8 - 1);
      dma_write( 2*8, 'h00_1000, 0, 0,  1*8 - 1);
      dma_write( 3*8, 'h00_1800, 0, 0,  1*8 - 1);

      // clean misses
      dma_read ( 0*8, 'h00_0000, 0, 0,  1*8 - 1);
      dma_read ( 1*8, 'h00_0800, 0, 0,  1*8 - 1);
      dma_read ( 2*8, 'h00_1000, 0, 0,  1*8 - 1);
      dma_read ( 3*8, 'h00_1800, 0, 0,  1*8 - 1);

      // clean write misses
      dma_write( 0*8, 'h00_0800, 0, 0,  1*8 - 1);
      dma_write( 0*8, 'h10_0800, 0, 0,  1*8 - 1);
      dma_read ( 0*8, 'h00_0800, 0, 0,  1*8 - 1);
      dma_read ( 0*8, 'h10_0800, 0, 0,  1*8 - 1);
      dma_write( 0*8, 'h00_0000, 0, 0,  1*8 - 1);
      dma_write( 0*8, 'h10_0000, 0, 0,  1*8 - 1);

      // clean read miss
      dma_read ( 0*8, 'h00_0000, 0, 0,  1*8 - 1);
      dma_read ( 0*8, 'h00_0800, 0, 0,  1*8 - 1);
      cp0_enable <= HIGH;
      cp0_address <= DMA_STATUS;
      @(posedge clock);
      while (cp0_data[2]) @(posedge clock);
      repeat(10) @(posedge clock);
      $finish;
      end
   endtask


task dbus_hazard;
   begin
      test_selected <= HIGH;
      reality.r4200b_0.config_mem;

      dma_write(8, 0, 0, 0, 16 * 8 - 1);
      dma_read (8, 0, 0, 0, 16 * 8 - 1);
      dma_write(8, 0, 0, 0, 16 * 8 - 1);
      dma_read (8, 0, 0, 0, 16 * 8 - 1);

      cp0_enable <= HIGH;
      cp0_address <= DMA_STATUS;
      @(posedge clock);
      while (cp0_data[2]) @(posedge clock);
      repeat(10) @(posedge clock);
      $finish;
      end
   endtask


task read_aligned;
   begin
      $display("Running read_dmem_aligned");
      test_selected <= HIGH;
      reality.r4200b_0.config_mem;

      dma_read(0, 0, 0, 0, 50 * 8 - 1);
      dma_read(8, 0, 0, 0, 50 * 8 - 1);
      dma_read(0, 8, 0, 0, 50 * 8 - 1);

      cp0_enable <= HIGH;
      cp0_address <= DMA_STATUS;
      @(posedge clock);
      while (cp0_data[2]) @(posedge clock);
      repeat(10) @(posedge clock);
      $finish;
      end
   endtask


task miss;
   begin
      test_selected <= HIGH;
      reality.r4200b_0.config_mem;

      
      dma_write( 0*8, 'h00_0000, 0, 0, 16*8 - 1);
      dma_write( 0*8, 'h10_0000, 0, 0, 16*8 - 1);

      // both writes generate dirty misses
      dma_write(16*8, 'h00_0800, 0, 0, 16*8 - 1);
      dma_write(16*8, 'h10_0800, 0, 0, 16*8 - 1);

      // both reads generate dirty misses
      dma_read( 0*8, 'h00_0000, 0, 0, 16*8 - 1);
      dma_read( 0*8, 'h10_0000, 0, 0, 16*8 - 1);

      // both reads generate clean misses
      dma_read(16*8, 'h00_0800, 0, 0, 16*8 - 1);
      dma_read(16*8, 'h10_0800, 0, 0, 16*8 - 1);

      // both writes generate clean misses
      dma_write( 0*8, 'h00_0000, 0, 0, 16*8 - 1);
      dma_write( 0*8, 'h10_0000, 0, 0, 16*8 - 1);

      cp0_enable <= HIGH;
      cp0_address <= DMA_STATUS;
      @(posedge clock);
      while (cp0_data[2]) @(posedge clock);
      repeat(10) @(posedge clock);
      $finish;
      end
   endtask


task write_dmem_aligned;
   begin
      test_selected <= HIGH;
      reality.r4200b_0.config_mem;

      dma_write(0, 0, 0, 0, 17 * 8 - 1);
      dma_write(8, 0, 0, 0, 30 * 8 - 1);
      dma_write(0, 8, 0, 0, 17 * 8 - 1);

      cp0_enable <= HIGH;
      cp0_address <= DMA_STATUS;
      @(posedge clock);
      while (cp0_data[2]) @(posedge clock);
      repeat(10) @(posedge clock);
      $finish;
      end
   endtask


task write_dmem_hazard;
   begin
      test_selected <= HIGH;
      reality.r4200b_0.config_mem;
      dma_write(0, 0, 0, 0, 8-1);
      dma_write(0, 'h800, 0, 0, 8 - 1);
      dma_write(0, 0, 0, 0, 8 - 1);
      dma_write(0, 'h800, 0, 0, 8 - 1);

      cp0_enable <= HIGH;
      cp0_address <= DMA_STATUS;
      @(posedge clock);
      while (cp0_data[2]) @(posedge clock);
      repeat(10) @(posedge clock);
      $finish;
      end
   endtask


task read_write_hazard;
   begin
      test_selected <= HIGH;
      reality.r4200b_0.config_mem;

      dma_write(0, 0, 0, 0, 16*8-1);
      dma_read(0, 'h800, 0, 0, 16*8-1);
      dma_write(0, 0, 0, 0, 16*8-1);

      dma_write(0, 0, 0, 0, 8-1);
      dma_read(0, 'h800, 0, 0, 8-1);
      dma_write(0, 0, 0, 0, 8-1);

      cp0_enable <= HIGH;
      cp0_address <= DMA_STATUS;
      @(posedge clock);
      while (cp0_data[2]) @(posedge clock);
      repeat(10) @(posedge clock);
      $finish;
      end
   endtask


task dma_read;
   input [31:0] master_address;
   input [31:0] slave_address;
   input [11:0] skip;
   input [7:0] count;
   input [11:0] length;

   begin
      cp0_enable <= HIGH;
      cp0_address <= DMA_STATUS;
      @(posedge clock);
      while (cp0_data[3]) @(posedge clock);

      cp0_enable <= LOW;
      cp0_write <= HIGH;

      // write the master address
      cp0_address <= DMA_MEM_ADDRESS;
      cp0_data_out <= master_address;
      @(posedge clock);

      // write the slave address
      cp0_address <= DMA_DBUS_ADDRESS;
      cp0_data_out <= slave_address;
      @(posedge clock);

      // write the length
      cp0_address <= DMA_READ_LENGTH;
      cp0_data_out <= {skip, count, length};
      @(posedge clock);

      cp0_write <= LOW;
      @(posedge clock);
      end
   endtask


task dma_write;
   input [31:0] master_address;
   input [31:0] slave_address;
   input [11:0] skip;
   input [7:0] count;
   input [11:0] length;

   begin
      cp0_enable <= HIGH;
      cp0_address <= DMA_STATUS;
      @(posedge clock);
      while (cp0_data[3]) @(posedge clock);

      cp0_enable <= LOW;
      cp0_write <= HIGH;

      // write the master address
      cp0_address <= DMA_MEM_ADDRESS;
      cp0_data_out <= master_address;
      @(posedge clock);

      // write the slave address
      cp0_address <= DMA_DBUS_ADDRESS;
      cp0_data_out <= slave_address;
      @(posedge clock);

      // write the length
      cp0_address <= DMA_WRITE_LENGTH;
      cp0_data_out <= {skip, count, length};
      @(posedge clock);

      cp0_write <= LOW;
      @(posedge clock);
      end
   endtask
endmodule
