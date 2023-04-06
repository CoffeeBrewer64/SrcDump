module mbus_mon(clock, reset_l, p_valid_l, e_valid_l, e_ok_l, int_l,
   sys_ad, sys_cmd);

`include "rcp.vh"
`include "define.vh"

input clock;
input reset_l;
input e_valid_l;
input e_ok_l;
input int_l;
input p_valid_l;
input [31:0] sys_ad;
input [4:0] sys_cmd;

reg read_cycle;
reg write_cycle;
reg e_ok_l_d1;
reg sys_cmd_data;
reg sys_cmd_write;
reg sys_cmd_block;
reg [1:0] sys_cmd_block_size;

reg monitor_enable;
initial monitor_enable = $test$plusargs("mbus_mon");

always @(posedge clock) begin
   if (!reset_l) begin
      read_cycle <= LOW;
      write_cycle <= LOW;
      e_ok_l_d1 <= HIGH;
      end
   else if (monitor_enable) begin
      if (read_cycle) begin
         if (!e_valid_l) begin
            if (sys_cmd[3]) begin
               $display(`CLOCK_COUNT, " : mbus   read data next  - data = %h", sys_ad);
               end
            else begin
               $display(`CLOCK_COUNT, " : mbus   read data last  - data = %h", sys_ad);
               read_cycle <= LOW;
               end
            end
         end
      else if (write_cycle) begin
         if (!p_valid_l) begin
            if (sys_cmd[3]) begin
               $display(`CLOCK_COUNT, " : mbus   write data next - data = %h", sys_ad);
               end
            else begin
               $display(`CLOCK_COUNT, " : mbus   write data last - data = %h", sys_ad);
               write_cycle <= LOW;
               end
            end
         else begin
            $display("%m: Panic!  p_valid_l unexpectly deasserted - %h", p_valid_l);
            $finish;
            end
         end
      else if (!p_valid_l && !e_ok_l && !e_ok_l_d1) begin
         {sys_cmd_data, sys_cmd_write, sys_cmd_block, sys_cmd_block_size} = sys_cmd;
         casez ({sys_cmd_data, sys_cmd_write, sys_cmd_block})
            'b000 : begin
               $display(`CLOCK_COUNT, " : mbus   read word       - address = %h, length = %h",
                  sys_ad, sys_cmd_block_size);
               read_cycle <= HIGH;
               end

            'b001 : begin
               $display(`CLOCK_COUNT, " : mbus   read block      - address = %h, length = %h",
                  sys_ad, sys_cmd_block_size);
               read_cycle <= HIGH;
               end

            'b010 : begin
               $display(`CLOCK_COUNT, " : mbus   write word      - address = %h, length = %h",
                  sys_ad, sys_cmd_block_size);
               write_cycle <= HIGH;
               end

            'b011 : begin
               $display(`CLOCK_COUNT, " : mbus   write block     - address = %h, length = %h",
                  sys_ad, sys_cmd_block_size);
               write_cycle <= HIGH;
               end

            'b1?? : begin
               $display("%m: Panic!  Data command during command cycle - %h", sys_cmd);
               $finish;
               end

            default : begin
               $display("%m: Panic!  Unknown processor command - %h", sys_cmd);
               $finish;
               end
            endcase
         end
      end
   e_ok_l_d1 <= e_ok_l;
   end
endmodule
