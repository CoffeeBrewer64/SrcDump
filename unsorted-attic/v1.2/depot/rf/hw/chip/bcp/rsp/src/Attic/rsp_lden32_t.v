
module rsp_lden32_t(ld_bar,clk,en_t);
input  [31:0] ld_bar;
input clk;
output [31:0] en_t;

nr02d2 u00(.zn(en_t[ 0]), .a1(ld_bar[ 0]), .a2(clk));
nr02d2 u01(.zn(en_t[ 1]), .a1(ld_bar[ 1]), .a2(clk));
nr02d2 u02(.zn(en_t[ 2]), .a1(ld_bar[ 2]), .a2(clk));
nr02d2 u03(.zn(en_t[ 3]), .a1(ld_bar[ 3]), .a2(clk));
nr02d2 u04(.zn(en_t[ 4]), .a1(ld_bar[ 4]), .a2(clk));
nr02d2 u05(.zn(en_t[ 5]), .a1(ld_bar[ 5]), .a2(clk));
nr02d2 u06(.zn(en_t[ 6]), .a1(ld_bar[ 6]), .a2(clk));
nr02d2 u07(.zn(en_t[ 7]), .a1(ld_bar[ 7]), .a2(clk));
nr02d2 u08(.zn(en_t[ 8]), .a1(ld_bar[ 8]), .a2(clk));
nr02d2 u09(.zn(en_t[ 9]), .a1(ld_bar[ 9]), .a2(clk));
nr02d2 u10(.zn(en_t[10]), .a1(ld_bar[10]), .a2(clk));
nr02d2 u11(.zn(en_t[11]), .a1(ld_bar[11]), .a2(clk));
nr02d2 u12(.zn(en_t[12]), .a1(ld_bar[12]), .a2(clk));
nr02d2 u13(.zn(en_t[13]), .a1(ld_bar[13]), .a2(clk));
nr02d2 u14(.zn(en_t[14]), .a1(ld_bar[14]), .a2(clk));
nr02d2 u15(.zn(en_t[15]), .a1(ld_bar[15]), .a2(clk));
nr02d2 u16(.zn(en_t[16]), .a1(ld_bar[16]), .a2(clk));
nr02d2 u17(.zn(en_t[17]), .a1(ld_bar[17]), .a2(clk));
nr02d2 u18(.zn(en_t[18]), .a1(ld_bar[18]), .a2(clk));
nr02d2 u19(.zn(en_t[19]), .a1(ld_bar[19]), .a2(clk));
nr02d2 u20(.zn(en_t[20]), .a1(ld_bar[20]), .a2(clk));
nr02d2 u21(.zn(en_t[21]), .a1(ld_bar[21]), .a2(clk));
nr02d2 u22(.zn(en_t[22]), .a1(ld_bar[22]), .a2(clk));
nr02d2 u23(.zn(en_t[23]), .a1(ld_bar[23]), .a2(clk));
nr02d2 u24(.zn(en_t[24]), .a1(ld_bar[24]), .a2(clk));
nr02d2 u25(.zn(en_t[25]), .a1(ld_bar[25]), .a2(clk));
nr02d2 u26(.zn(en_t[26]), .a1(ld_bar[26]), .a2(clk));
nr02d2 u27(.zn(en_t[27]), .a1(ld_bar[27]), .a2(clk));
nr02d2 u28(.zn(en_t[28]), .a1(ld_bar[28]), .a2(clk));
nr02d2 u29(.zn(en_t[29]), .a1(ld_bar[29]), .a2(clk));
nr02d2 u30(.zn(en_t[30]), .a1(ld_bar[30]), .a2(clk));
nr02d2 u31(.zn(en_t[31]), .a1(ld_bar[31]), .a2(clk));

endmodule
