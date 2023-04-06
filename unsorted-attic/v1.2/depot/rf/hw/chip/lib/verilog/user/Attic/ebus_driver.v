module ebus_driver(ebus_data_out, ebus_enable, ebus_data);

`include "rcp.vh"

input [EBUS_DATA_SIZE-1:0] ebus_data_out;
input ebus_enable;
output [EBUS_DATA_SIZE-1:0] ebus_data;

nt01d5 g00(.i(ebus_data_out[00]), .oe(ebus_enable), .z(ebus_data[00]));
nt01d5 g01(.i(ebus_data_out[01]), .oe(ebus_enable), .z(ebus_data[01]));
nt01d5 g02(.i(ebus_data_out[02]), .oe(ebus_enable), .z(ebus_data[02]));
nt01d5 g03(.i(ebus_data_out[03]), .oe(ebus_enable), .z(ebus_data[03]));
nt01d5 g04(.i(ebus_data_out[04]), .oe(ebus_enable), .z(ebus_data[04]));
nt01d5 g05(.i(ebus_data_out[05]), .oe(ebus_enable), .z(ebus_data[05]));
nt01d5 g06(.i(ebus_data_out[06]), .oe(ebus_enable), .z(ebus_data[06]));
nt01d5 g07(.i(ebus_data_out[07]), .oe(ebus_enable), .z(ebus_data[07]));

endmodule
