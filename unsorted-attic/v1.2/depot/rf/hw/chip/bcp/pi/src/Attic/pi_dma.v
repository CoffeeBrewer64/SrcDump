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

// $Id: pi_dma.v,v 1.1 2002/05/21 23:55:44 berndt Exp $

module pi_dma(clock, reset_l,
   cbus_read_enable, cbus_write_enable, cbus_select, cbus_command, read_grant,
   dma_read, dma_address, dma_length, reg_read_data, io_busy,
   read_request, reg_write_data, reg_address, io_address, reg_write_enable,
   cbus_data);

`include "pi.vh"

parameter READ_DELAY = 8'd2;
parameter WRITE_DELAY = -8'd1;

input clock;                                 // system clock
input reset_l;                               // system reset_l

input cbus_read_enable;                      // enable cbus tristate drivers
input cbus_write_enable;                     // enable cbus tristate drivers
input [1:0] cbus_select;    // cbus data select
input [2:0] cbus_command;  // cbus data type
input read_grant;                            // read response request granted
input dma_read;                              // DMA read/write select
input [DRAM_ADDRESS_SIZE-1:0] dma_address;   // DMA slave address
input [DMA_LENGTH_SIZE-1:0] dma_length;      // DMA length in words
input [31:0] reg_read_data;    // register read data to cbus
input io_busy;                               // operation in progress

output read_request;                         // request a read response cycle
output [31:0] reg_write_data;  // register write data from cbus
output [PI_REG_ADDRESS_SIZE-1:0] reg_address;// register read/write address
output [31:0] io_address;      // cbus read request address
output reg_write_enable;                     // register write enable

inout [31:0] cbus_data;        // IO bus


// input/output registers
reg read_request;
reg reg_write_enable;
reg [PI_REG_ADDRESS_SIZE-1:0] reg_address;
reg [31:0] io_address;
reg [2:0] cbus_command_reg;
reg [31:0] cbus_data_reg;


// internal registers
reg io_request0, io_request1;

// cbus tristate drivers
cbus_driver cbus_driver_0(cbus_data_reg, cbus_write_enable, cbus_data);

assign reg_write_data = cbus_data_reg;

always @(posedge clock) begin : cbus_block
   reg [31:0] cbus_data_out;

   case (cbus_select)
      `CBUS_SEL_ADDR :
        cbus_data_out = dma_address;
      `CBUS_SEL_LEN :
         if (dma_read) begin
            cbus_data_out = {`CBUS_DEV_PI, READ_DELAY, HIGH, dma_length};
            end
         else begin
            cbus_data_out = {`CBUS_DEV_PI, WRITE_DELAY, LOW, dma_length};
            end
      `CBUS_SEL_DATA :
        cbus_data_out = reg_read_data;
      default :
        cbus_data_out = 'bx;
      endcase

   cbus_command_reg <= cbus_command;
   cbus_data_reg <= cbus_read_enable ? cbus_data : cbus_data_out;
   end


always @(posedge clock or negedge reset_l) begin
   if (!reset_l) begin
      // resetable registers
      read_request <= LOW;
      reg_write_enable <= LOW;
      io_request0 <= LOW;
      io_request1 <= LOW;

      reg_address <= 'bx;
      io_address <= 'bx;
      end
   else begin : main_loop
      reg next_reg_write_enable;
      reg [BUS_ID_SIZE-1:0] next_id;
      reg next_pi_select;
      reg next_pif_select;
      reg next_pbus_select;
      reg next_write_command;
      reg next_read_command;
      reg next_read_request;
      reg next_io_request;

      next_reg_write_enable = LOW;
      next_id = cbus_data_reg >> BUS_ID_OFFSET;
      next_pi_select = next_id == `CBUS_PI;
      next_pif_select = next_id == `CBUS_BOOT;
      next_pbus_select = cbus_data_reg >= BUS_ADDRESS_PBUS && !next_pif_select;
      next_write_command = cbus_command_reg == `CBUS_CMD_WRITE;
      next_read_command = cbus_command_reg == `CBUS_CMD_READ;
      next_read_request = read_request;
      next_io_request = io_request0;

      if (next_pi_select) begin
         if (next_write_command) begin
            next_reg_write_enable = HIGH;
            reg_address <= cbus_data_reg >> 2;
            end
         else if (next_read_command) begin
            next_read_request = HIGH;
            reg_address <= cbus_data_reg >> 2;
            end
         end
      else if (next_pbus_select) begin
         if (next_write_command) begin
            next_reg_write_enable = HIGH;
            io_address <= cbus_data_reg;
            reg_address <= PI_IO_WRITE_REG;
            end
         else if (next_read_command) begin
            next_io_request = HIGH;
            next_reg_write_enable = HIGH;
            io_address <= cbus_data_reg;
            reg_address <= PI_IO_READ_REG;
            end
         end

      if (io_request0 && io_request1 && !io_busy) begin
         next_io_request = LOW;
         next_read_request = HIGH;
         end

      if (read_request && read_grant) begin
         next_read_request = LOW;
         end

      reg_write_enable <= next_reg_write_enable;
      read_request <= next_read_request;
      io_request0 <= next_io_request;
      io_request1 <= io_request0;
      end
   end
endmodule
