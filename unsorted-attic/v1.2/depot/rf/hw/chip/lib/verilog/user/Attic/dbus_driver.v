// dbus_driver.v v1 Frank Berndt;
// dbus tri-state driver;

module dbus_driver (
	dbus_data_out,
	dbus_enable,
	dbus_data
);

	input [63:0] dbus_data_out;
	input dbus_enable;
	output [63:0] dbus_data;

	// use define to assign tri-state driver from cell library;
	// XXX replace nt01d5

`define	DBUS_DRV nt01d5

	`DBUS_DRV g00(.i(dbus_data_out[00]), .oe(dbus_enable), .z(dbus_data[00]));
	`DBUS_DRV g01(.i(dbus_data_out[01]), .oe(dbus_enable), .z(dbus_data[01]));
	`DBUS_DRV g02(.i(dbus_data_out[02]), .oe(dbus_enable), .z(dbus_data[02]));
	`DBUS_DRV g03(.i(dbus_data_out[03]), .oe(dbus_enable), .z(dbus_data[03]));
	`DBUS_DRV g04(.i(dbus_data_out[04]), .oe(dbus_enable), .z(dbus_data[04]));
	`DBUS_DRV g05(.i(dbus_data_out[05]), .oe(dbus_enable), .z(dbus_data[05]));
	`DBUS_DRV g06(.i(dbus_data_out[06]), .oe(dbus_enable), .z(dbus_data[06]));
	`DBUS_DRV g07(.i(dbus_data_out[07]), .oe(dbus_enable), .z(dbus_data[07]));
	`DBUS_DRV g08(.i(dbus_data_out[08]), .oe(dbus_enable), .z(dbus_data[08]));
	`DBUS_DRV g09(.i(dbus_data_out[09]), .oe(dbus_enable), .z(dbus_data[09]));
	`DBUS_DRV g10(.i(dbus_data_out[10]), .oe(dbus_enable), .z(dbus_data[10]));
	`DBUS_DRV g11(.i(dbus_data_out[11]), .oe(dbus_enable), .z(dbus_data[11]));
	`DBUS_DRV g12(.i(dbus_data_out[12]), .oe(dbus_enable), .z(dbus_data[12]));
	`DBUS_DRV g13(.i(dbus_data_out[13]), .oe(dbus_enable), .z(dbus_data[13]));
	`DBUS_DRV g14(.i(dbus_data_out[14]), .oe(dbus_enable), .z(dbus_data[14]));
	`DBUS_DRV g15(.i(dbus_data_out[15]), .oe(dbus_enable), .z(dbus_data[15]));
	`DBUS_DRV g16(.i(dbus_data_out[16]), .oe(dbus_enable), .z(dbus_data[16]));
	`DBUS_DRV g17(.i(dbus_data_out[17]), .oe(dbus_enable), .z(dbus_data[17]));
	`DBUS_DRV g18(.i(dbus_data_out[18]), .oe(dbus_enable), .z(dbus_data[18]));
	`DBUS_DRV g19(.i(dbus_data_out[19]), .oe(dbus_enable), .z(dbus_data[19]));
	`DBUS_DRV g20(.i(dbus_data_out[20]), .oe(dbus_enable), .z(dbus_data[20]));
	`DBUS_DRV g21(.i(dbus_data_out[21]), .oe(dbus_enable), .z(dbus_data[21]));
	`DBUS_DRV g22(.i(dbus_data_out[22]), .oe(dbus_enable), .z(dbus_data[22]));
	`DBUS_DRV g23(.i(dbus_data_out[23]), .oe(dbus_enable), .z(dbus_data[23]));
	`DBUS_DRV g24(.i(dbus_data_out[24]), .oe(dbus_enable), .z(dbus_data[24]));
	`DBUS_DRV g25(.i(dbus_data_out[25]), .oe(dbus_enable), .z(dbus_data[25]));
	`DBUS_DRV g26(.i(dbus_data_out[26]), .oe(dbus_enable), .z(dbus_data[26]));
	`DBUS_DRV g27(.i(dbus_data_out[27]), .oe(dbus_enable), .z(dbus_data[27]));
	`DBUS_DRV g28(.i(dbus_data_out[28]), .oe(dbus_enable), .z(dbus_data[28]));
	`DBUS_DRV g29(.i(dbus_data_out[29]), .oe(dbus_enable), .z(dbus_data[29]));
	`DBUS_DRV g30(.i(dbus_data_out[30]), .oe(dbus_enable), .z(dbus_data[30]));
	`DBUS_DRV g31(.i(dbus_data_out[31]), .oe(dbus_enable), .z(dbus_data[31]));
	`DBUS_DRV g32(.i(dbus_data_out[32]), .oe(dbus_enable), .z(dbus_data[32]));
	`DBUS_DRV g33(.i(dbus_data_out[33]), .oe(dbus_enable), .z(dbus_data[33]));
	`DBUS_DRV g34(.i(dbus_data_out[34]), .oe(dbus_enable), .z(dbus_data[34]));
	`DBUS_DRV g35(.i(dbus_data_out[35]), .oe(dbus_enable), .z(dbus_data[35]));
	`DBUS_DRV g36(.i(dbus_data_out[36]), .oe(dbus_enable), .z(dbus_data[36]));
	`DBUS_DRV g37(.i(dbus_data_out[37]), .oe(dbus_enable), .z(dbus_data[37]));
	`DBUS_DRV g38(.i(dbus_data_out[38]), .oe(dbus_enable), .z(dbus_data[38]));
	`DBUS_DRV g39(.i(dbus_data_out[39]), .oe(dbus_enable), .z(dbus_data[39]));
	`DBUS_DRV g40(.i(dbus_data_out[40]), .oe(dbus_enable), .z(dbus_data[40]));
	`DBUS_DRV g41(.i(dbus_data_out[41]), .oe(dbus_enable), .z(dbus_data[41]));
	`DBUS_DRV g42(.i(dbus_data_out[42]), .oe(dbus_enable), .z(dbus_data[42]));
	`DBUS_DRV g43(.i(dbus_data_out[43]), .oe(dbus_enable), .z(dbus_data[43]));
	`DBUS_DRV g44(.i(dbus_data_out[44]), .oe(dbus_enable), .z(dbus_data[44]));
	`DBUS_DRV g45(.i(dbus_data_out[45]), .oe(dbus_enable), .z(dbus_data[45]));
	`DBUS_DRV g46(.i(dbus_data_out[46]), .oe(dbus_enable), .z(dbus_data[46]));
	`DBUS_DRV g47(.i(dbus_data_out[47]), .oe(dbus_enable), .z(dbus_data[47]));
	`DBUS_DRV g48(.i(dbus_data_out[48]), .oe(dbus_enable), .z(dbus_data[48]));
	`DBUS_DRV g49(.i(dbus_data_out[49]), .oe(dbus_enable), .z(dbus_data[49]));
	`DBUS_DRV g50(.i(dbus_data_out[50]), .oe(dbus_enable), .z(dbus_data[50]));
	`DBUS_DRV g51(.i(dbus_data_out[51]), .oe(dbus_enable), .z(dbus_data[51]));
	`DBUS_DRV g52(.i(dbus_data_out[52]), .oe(dbus_enable), .z(dbus_data[52]));
	`DBUS_DRV g53(.i(dbus_data_out[53]), .oe(dbus_enable), .z(dbus_data[53]));
	`DBUS_DRV g54(.i(dbus_data_out[54]), .oe(dbus_enable), .z(dbus_data[54]));
	`DBUS_DRV g55(.i(dbus_data_out[55]), .oe(dbus_enable), .z(dbus_data[55]));
	`DBUS_DRV g56(.i(dbus_data_out[56]), .oe(dbus_enable), .z(dbus_data[56]));
	`DBUS_DRV g57(.i(dbus_data_out[57]), .oe(dbus_enable), .z(dbus_data[57]));
	`DBUS_DRV g58(.i(dbus_data_out[58]), .oe(dbus_enable), .z(dbus_data[58]));
	`DBUS_DRV g59(.i(dbus_data_out[59]), .oe(dbus_enable), .z(dbus_data[59]));
	`DBUS_DRV g60(.i(dbus_data_out[60]), .oe(dbus_enable), .z(dbus_data[60]));
	`DBUS_DRV g61(.i(dbus_data_out[61]), .oe(dbus_enable), .z(dbus_data[61]));
	`DBUS_DRV g62(.i(dbus_data_out[62]), .oe(dbus_enable), .z(dbus_data[62]));
	`DBUS_DRV g63(.i(dbus_data_out[63]), .oe(dbus_enable), .z(dbus_data[63]));

endmodule

