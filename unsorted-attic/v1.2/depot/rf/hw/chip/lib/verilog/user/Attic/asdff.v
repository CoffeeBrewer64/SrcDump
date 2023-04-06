
module asdff (out, in, clk, reset);
//synopsys template

  parameter width = 1, reset_value = 0;

  output [width-1:0] out;
  input  [width-1:0] in;
  input clk;
  input reset;

  reg [width-1:0] out;

  always @ (posedge clk or negedge reset)
    begin
        if (!reset)
                out <= {width{reset_value}};
        else
                out <= in;
    end
endmodule

