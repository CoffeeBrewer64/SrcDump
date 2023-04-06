
// $Id: cp0_driver.v,v 1.2 2002/09/30 23:10:04 jeff Exp $

module cp0_driver(cp0_data_out, cp0_enable, cp0_data);

`include "rcp.vh"

input [CP0_DATA_SIZE-1:0] cp0_data_out;
input cp0_enable;
output [CP0_DATA_SIZE-1:0] cp0_data;

assign cp0_data = cp0_enable ? cp0_data_out : {32{1'bz}};

// nt01d3 g00(.i(cp0_data_out[00]), .oe(cp0_enable), .z(cp0_data[00]));
// nt01d3 g01(.i(cp0_data_out[01]), .oe(cp0_enable), .z(cp0_data[01]));
// nt01d3 g02(.i(cp0_data_out[02]), .oe(cp0_enable), .z(cp0_data[02]));
// nt01d3 g03(.i(cp0_data_out[03]), .oe(cp0_enable), .z(cp0_data[03]));
// nt01d3 g04(.i(cp0_data_out[04]), .oe(cp0_enable), .z(cp0_data[04]));
// nt01d3 g05(.i(cp0_data_out[05]), .oe(cp0_enable), .z(cp0_data[05]));
// nt01d3 g06(.i(cp0_data_out[06]), .oe(cp0_enable), .z(cp0_data[06]));
// nt01d3 g07(.i(cp0_data_out[07]), .oe(cp0_enable), .z(cp0_data[07]));
// nt01d3 g08(.i(cp0_data_out[08]), .oe(cp0_enable), .z(cp0_data[08]));
// nt01d3 g09(.i(cp0_data_out[09]), .oe(cp0_enable), .z(cp0_data[09]));
// nt01d3 g10(.i(cp0_data_out[10]), .oe(cp0_enable), .z(cp0_data[10]));
// nt01d3 g11(.i(cp0_data_out[11]), .oe(cp0_enable), .z(cp0_data[11]));
// nt01d3 g12(.i(cp0_data_out[12]), .oe(cp0_enable), .z(cp0_data[12]));
// nt01d3 g13(.i(cp0_data_out[13]), .oe(cp0_enable), .z(cp0_data[13]));
// nt01d3 g14(.i(cp0_data_out[14]), .oe(cp0_enable), .z(cp0_data[14]));
// nt01d3 g15(.i(cp0_data_out[15]), .oe(cp0_enable), .z(cp0_data[15]));
// nt01d3 g16(.i(cp0_data_out[16]), .oe(cp0_enable), .z(cp0_data[16]));
// nt01d3 g17(.i(cp0_data_out[17]), .oe(cp0_enable), .z(cp0_data[17]));
// nt01d3 g18(.i(cp0_data_out[18]), .oe(cp0_enable), .z(cp0_data[18]));
// nt01d3 g19(.i(cp0_data_out[19]), .oe(cp0_enable), .z(cp0_data[19]));
// nt01d3 g20(.i(cp0_data_out[20]), .oe(cp0_enable), .z(cp0_data[20]));
// nt01d3 g21(.i(cp0_data_out[21]), .oe(cp0_enable), .z(cp0_data[21]));
// nt01d3 g22(.i(cp0_data_out[22]), .oe(cp0_enable), .z(cp0_data[22]));
// nt01d3 g23(.i(cp0_data_out[23]), .oe(cp0_enable), .z(cp0_data[23]));
// nt01d3 g24(.i(cp0_data_out[24]), .oe(cp0_enable), .z(cp0_data[24]));
// nt01d3 g25(.i(cp0_data_out[25]), .oe(cp0_enable), .z(cp0_data[25]));
// nt01d3 g26(.i(cp0_data_out[26]), .oe(cp0_enable), .z(cp0_data[26]));
// nt01d3 g27(.i(cp0_data_out[27]), .oe(cp0_enable), .z(cp0_data[27]));
// nt01d3 g28(.i(cp0_data_out[28]), .oe(cp0_enable), .z(cp0_data[28]));
// nt01d3 g29(.i(cp0_data_out[29]), .oe(cp0_enable), .z(cp0_data[29]));
// nt01d3 g30(.i(cp0_data_out[30]), .oe(cp0_enable), .z(cp0_data[30]));
// nt01d3 g31(.i(cp0_data_out[31]), .oe(cp0_enable), .z(cp0_data[31]));

endmodule
