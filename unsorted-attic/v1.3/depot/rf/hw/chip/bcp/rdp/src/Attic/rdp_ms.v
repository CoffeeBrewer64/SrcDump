/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

// $Id: rdp_ms.v,v 1.2 2002/11/17 19:55:48 berndt Exp $

////////////////////////////////////////////////////////////////////////
//
// Project Reality
//
// module:	rdp
// description:	RDP top level. For now, without mem span unit.
//
// designer:	Phil Gossett
// date:	6/15/95
//
////////////////////////////////////////////////////////////////////////

module rdp_ms (clk, gclk, gclock_enable, reset_l,
	xbus_cs_data, xbus_cs_valid,
	load_dv, copy_load,
	mem_r, mem_g, mem_b, mem_a, mem_z,
	rel_sync_full, flush,
	cs_xbus_req,
	span_r, span_g, span_b, span_a, span_z,
	span_color_we, span_depth_we,
	strobe_sync_full,
	ew_ms_length, ew_ms_addr,
        ew_ms_newspan,
	ew_ms_startspan,
	at_color_base,
	at_color_format,
	at_color_size,
	at_z_base,
	at_cycle_type,
	color_rmw,
	at_z_rmw,
	at_z_enable,
	at_fill_color,
	tex_base,
	tex_width,
	tex_size,
	tex_format,
	ew_scissor_load,
	tc_load,
	load_tlut_en,
	rgb_dither_sel,
	rgb_dither);

input clk;
input gclk;
input reset_l;
input [63:0] xbus_cs_data;
input xbus_cs_valid;
input load_dv;			// valid load data on copy_load bus
inout [63:0] copy_load;		// bidirectional copy / load bus
input [7:0] mem_r;		// from mem_span unit
input [7:0] mem_g;
input [7:0] mem_b;
input [2:0] mem_a;
input [17:0] mem_z;		// z and delta from memory (fp format)
input rel_sync_full;		// from mem_span
input flush;			// CP0 control bit
input gclock_enable;		// from C clock driver

output cs_xbus_req;
output [7:0] span_r;		// to mem_span unit
output [7:0] span_g;
output [7:0] span_b;
output [2:0] span_a;
output [17:0] span_z;		// z and delta to memory (fp format)
output span_color_we;
output span_depth_we;
output strobe_sync_full;	// 29 (counter, to mem span)
output [11:0] ew_ms_length;
output [19:0] ew_ms_addr;
output ew_ms_newspan;
output ew_ms_startspan;
output [25:0] at_color_base;
output [2:0] at_color_format;
output [1:0] at_color_size;
output [25:0] at_z_base;
output [1:0] at_cycle_type;
output color_rmw;
output at_z_rmw;
output at_z_enable;
output [31:0] at_fill_color;

output [25:0] tex_base;
output [9:0]  tex_width;
output [1:0]  tex_size;
output [2:0]  tex_format;
output	ew_scissor_load;
output	tc_load;
output	load_tlut_en;
output [1:0] rgb_dither_sel;	// for memspan
output [2:0] rgb_dither;	// for memspan

// not used for csim

// cs
wire [2:0] tile_addr;
wire [47:0] cs_tc_data;
wire we_tile_size;
wire we_tile_attr;
wire [63:0] cs_ew_data;
wire cs_ew_newprim;
wire [5:0] cmd;
wire start_prim;
wire attr_valid;
wire cmd_busy;

// ew
wire ew_cs_busy;
wire [12:0] ew_cv_d;
wire ew_cv_newspan;
wire [11:0] ew_cv_start_x;
wire [21:0] ew_ep_d;
wire ew_ep_startspan;
wire [1:0] y_dither;

// cv
wire [3:0] cv_value;
wire mask15;
wire [1:0] x_offset;
wire [1:0] y_offset;
wire [1:0] x_dither;

// ep
wire st_span_st_w;
wire st_span_st_s;
wire st_span_st_t;
wire st_span_st_r;
wire st_span_st_g;
wire st_span_st_b;
wire st_span_st_a;
wire st_span_st_z;
wire st_span_tc;
wire st_span_tf;
wire st_span_cc;
wire st_span_bl;
wire st_span_ms;
wire [21:0] d_w;
wire [21:0] d_s;
wire [21:0] d_t;
wire [21:0] d_r;
wire [21:0] d_g;
wire [21:0] d_b;
wire [21:0] d_a;
wire [21:0] d_z;
wire [1:0] x_offset_r;
wire [1:0] x_offset_g;
wire [1:0] x_offset_b;
wire [1:0] x_offset_a;
wire [1:0] x_offset_z;
wire [1:0] y_offset_r;
wire [1:0] y_offset_g;
wire [1:0] y_offset_b;
wire [1:0] y_offset_a;
wire [1:0] y_offset_z;
wire [3:0] cvg_cc;
wire mask_bl;
wire [2:0] alpha_dither;

// at
wire [22:0] ew_dxr;           // s15.7  (single buffer)
wire [22:0] ew_dxg;           // s15.7  (single buffer)
wire [22:0] ew_dxb;           // s15.7  (single buffer)
wire [22:0] ew_dxa;           // s15.7  (single buffer)
wire [22:0] ew_dxz;           // s15.7  (single buffer)
wire [22:0] ew_dxs;           // s15.7  (single buffer)
wire [22:0] ew_dxt;           // s15.7  (single buffer)
wire [22:0] ew_dxw;           // s15.7  (single buffer)
wire [22:0] ew_dyr;           // s15.7  (single buffer)
wire [22:0] ew_dyg;           // s15.7  (single buffer)
wire [22:0] ew_dyb;           // s15.7  (single buffer)
wire [22:0] ew_dya;           // s15.7  (single buffer)
wire [22:0] ew_dyz;           // s15.7  (single buffer)
wire [22:0] ew_dys;           // s15.7  (single buffer)
wire [22:0] ew_dyt;           // s15.7  (single buffer)
wire [22:0] ew_dyw;           // s15.7  (single buffer)
wire [21:0] st_dxr;           // s10.11 (triple buffer)
wire [21:0] st_dxg;           // s10.11 (triple buffer)
wire [21:0] st_dxb;           // s10.11 (triple buffer)
wire [21:0] st_dxa;           // s10.11 (triple buffer)
wire [31:0] st_dxz;           // s15.16 (triple buffer)
wire [26:0] st_dxs;           // s15.11 (double buffer)
wire [26:0] st_dxt;           // s15.11 (double buffer)
wire [26:0] st_dxw;           // s15.11 (double buffer)
wire [12:0] st_dyr;           // s10.2  (double buffer)
wire [12:0] st_dyg;           // s10.2  (double buffer)
wire [12:0] st_dyb;           // s10.2  (double buffer)
wire [12:0] st_dya;           // s10.2  (double buffer)
wire [21:0] st_dyz;           // s15.6  (double buffer)
wire [16:0] st_dys;           // s15.1  (single buffer)
wire [16:0] st_dyt;           // s15.1  (single buffer)
wire [16:0] st_dyw;           // s15.1  (single buffer)
wire st_ncyc;                 // ncyc for s,t steppers (load overrides)
wire [55:0] color_image;      // 3f 55:51, 43:32, 25:0 (unsynced)
wire [55:0] z_image;          // 3e               25:0 (unsynced)
wire [55:0] tex_image;        // 3d 55:51, 43:32, 25:0 (unsynced)
wire [55:0] combine_mode;     // 3c 55:0               (unsynced)
wire [55:0] env_color;        // 3b 31:0               (unsynced)
wire [55:0] prim_color;       // 3a 47:40, 39:0        (triple buffer)
wire [55:0] blend_color;      // 39 31:0               (unsynced)
wire [55:0] fog_color;        // 38 31:0               (unsynced)
wire [55:0] fill_color;       // 37 31:0               (unsynced)
wire [55:0] other_modes;      // 2f 53:0               (unsynced)
wire [55:0] prim_depth;       // 2e 31:16, 15:0        (triple buffer)
wire [55:0] scissor;          // 2d 55:32, 25:0        (single buffer)
wire [55:0] convert;          // 2c 53:0               (unsynced)
wire [55:0] key_r;            // 2b 27:0               (unsynced)
wire [55:0] key_gb;           // 2a 55:0               (unsynced)
wire [8:0] noise;             // pseudo-random noise   (shift registers)
wire rel_sync_tile;           // 28                    (counter)
wire rel_sync_pipe;           // 27                    (counter)
wire rel_sync_load;           // 31                    (counter)
wire ew_image_load;           // tile(34),block(33),tlut(30) (pipe)
wire ew_scissor_load;         // tile(34),block(33),tlut(30) (pipe)
wire ew_stall_load;           // tile(34),block(33),tlut(30) (pipe)
wire ew_offset_load;          // tile(34),block(33),tlut(30) (pipe)
wire tc_load;                 // tile(34),block(33),tlut(30) (pipe)
wire shift_coord;             // load_block(33),tlut(34)     (triple buffer)
wire [2:0] level;             // primitives (36,24,25,0f-08) (triple buffer)
wire [2:0] tile;              // primitives (36,24,25,0f-08) (triple buffer)
wire ew_major_sign;           // sign of dxhdy               (pipe)
wire ew_offset_sign;          // sign of dxhdy               (pipe)
wire ew_major_left;           // primitives (36,24,25,0f-08) (pipe)
wire ew_minor_left;           // primitives (36,24,25,0f-08) (pipe)
wire ew_offset_left;          // primitives (36,24,25,0f-08) (pipe)
wire cv_left;                 // primitives (36,24,25,0f-08) (pipe)
wire st_r_left;               // primitives (36,24,25,0f-08) (pipe)
wire st_g_left;               // primitives (36,24,25,0f-08) (pipe)
wire st_b_left;               // primitives (36,24,25,0f-08) (pipe)
wire st_a_left;               // primitives (36,24,25,0f-08) (pipe)
wire st_z_left;               // primitives (36,24,25,0f-08) (pipe)
wire st_s_left;               // primitives (36,24,25,0f-08) (pipe)
wire st_t_left;               // primitives (36,24,25,0f-08) (pipe)
wire st_w_left;               // primitives (36,24,25,0f-08) (pipe)
wire spanbufmt;               // span buffer empty 
wire [19:0]  nextspanxi;      // EW initial span pix coord
wire [11:0]  nextspanxf;      // EW final span pix coord
wire [11:0]  nextspancount;   // EW count per span
wire nextspanxdec;            // right major per span
wire load_en;                 // load enable per span
wire load_tlut_en;            // load tlut cmd per span
wire ew_stall_tlut;	      // tlut(30) (pipe, fifo)
wire at_cs_busy;              // busy to force atomic primitives

// st
wire [7:0] st_cc_r;
wire [7:0] st_cc_g;
wire [7:0] st_cc_b;
wire [7:0] st_cc_a;
wire [17:0] st_bl_z;
wire [15:0] st_tc_s;
wire [15:0] st_tc_t;
wire [15:0] st_tc_w;

// tc
wire [7:0] adrs_bnk0l;        // sorted address to low bank 0
wire [7:0] adrs_bnk1l;        // sorted address to low bank 1
wire [7:0] adrs_bnk2l;        // sorted address to low bank 2
wire [7:0] adrs_bnk3l;        // sorted address to low bank 3
wire [7:0] adrs_bnk0h;        // sorted address to high bank 0
wire [7:0] adrs_bnk1h;        // sorted address to high bank 1
wire [7:0] adrs_bnk2h;        // sorted address to high bank 2
wire [7:0] adrs_bnk3h;        // sorted address to high bank 3
wire [4:0] adrs_a;            // address of texel a <12,3:0>
wire [4:0] adrs_b_ba;         // address of texel b (ba banks) <12,3:0>
wire [4:0] adrs_c;            // address of texel c <12,3:0>
wire [4:0] adrs_d_ba;         // address of texel d (ba banks) <12,3:0>
wire [4:0] adrs_b_rg;         // address of texel b (rg banks) <12,3:0>
wire [4:0] adrs_d_rg;         // address of texel d (rg banks) <12,3:0>
wire swap_rg;                 // swap texels (RG)
wire swap_ba;                 // swap texels (BA)
wire [2:0] tile_tex_type_1d;  // tile_tex_type 
wire [1:0] tile_tex_size_1d;  // tile_tex_size 
wire [3:0] palette;           // palette for 4-bit color index
wire odd_t;                   // odd line
wire a_three;                 // address a[3] before interleave
wire a_twelve;                // address a[12] 
wire [7:0] clr_ind_a;         // color index texel a
wire [7:0] clr_ind_b;         // color index texel b
wire [7:0] clr_ind_c;         // color index texel c
wire [7:0] clr_ind_d;         // color index texel d

// tm
wire [8:0] l_frac;          // lod fraction for 3rd-axis interpolation
wire lod_ge_one;            // lod >= 1
wire [7:0] s_frac_rg;       // s interp fraction to filter (RG)
wire [7:0] t_frac_rg;       // t interp fraction to filter (RG)
wire [7:0] s_frac_ba;       // s interp fraction to filter (BA)
wire [7:0] t_frac_ba;       // t interp fraction to filter (BA)
wire [8:0] tm_ra;           // texel a, red / u channel
wire [8:0] tm_ga;           // texel a, green / v channel
wire [8:0] tm_ba;           // texel a, blue / y channel
wire [8:0] tm_aa;           // texel a, alpha / y channel
wire [8:0] tm_rb;           // texel b, red / u channel
wire [8:0] tm_gb;           // texel b, green / v channel
wire [8:0] tm_bb;           // texel b, blue / y channel
wire [8:0] tm_ab;           // texel b, alpha / y channel
wire [8:0] tm_rc;           // texel c, red / u channel
wire [8:0] tm_gc;           // texel c, green / v channel
wire [8:0] tm_bc;           // texel c, blue / y channel
wire [8:0] tm_ac;           // texel c, alpha / y channel
wire [8:0] tm_rd;           // texel d, red / u channel
wire [8:0] tm_gd;           // texel d, green / v channel
wire [8:0] tm_bd;           // texel d, blue / y channel
wire [8:0] tm_ad;           // texel d, alpha / y channel
wire bist_go;
wire bist_check;
wire bist_done;
wire bist0_fail;
wire bist1_fail;
wire bist2_fail;
wire bist3_fail;
wire bist4_fail;
wire bist5_fail;
wire bist6_fail;
wire bist7_fail;

// tf
wire [8:0] tf_r;		// texture filter unit outputs
wire [8:0] tf_g;
wire [8:0] tf_b;
wire [8:0] tf_a;
wire [8:0] tf_lod_frac;		// pipe thru to CCU

// cc
wire [7:0] shade_a;
wire [7:0] pixel_r;
wire [7:0] pixel_g;
wire [7:0] pixel_b;
wire [8:0] pixel_a;		// 1.8
wire [3:0] pixel_cvg;		// 1.3

// ms (unused)
wire spanbufrd;                 //pop span buffer

// for C mem span
  assign ew_ms_newspan        = ew_cv_newspan;
  assign ew_ms_startspan      = ew_ep_startspan;
  assign at_color_base[25:0]  = color_image[25:0];
  assign at_color_format[2:0] = color_image[55:53];
  assign at_color_size[1:0]   = color_image[52:51];
  assign at_z_base[25:0]      = z_image[25:0];
  assign at_cycle_type[1:0]   = other_modes[53:52];
  assign color_rmw            = other_modes[6];
  assign at_z_rmw             = other_modes[5];
  assign at_z_enable          = other_modes[4];
  assign at_fill_color[31:0]  = fill_color[31:0];
  assign at_fill_color[31:0]  = fill_color[31:0];
  assign tex_base[25:0]       = tex_image[25:0];
  assign tex_width[9:0]       = tex_image[41:32];
  assign tex_size[1:0]        = tex_image[52:51];
  assign tex_format[2:0]      = tex_image[55:53];
  assign bist_go              = 1'b0;	// no bist for csim
  assign bist_check           = 1'b0;	// no bist for csim
  assign spanbufrd	      = 1'b0;   // don't use spanbuf without ms
  assign load_tlut_en         = ew_stall_tlut;
  assign rgb_dither_sel       = other_modes[39:38];

cs cs (	.clk(clk), .gclk(gclk), .reset_l(reset_l),
	.xbus_cs_data(xbus_cs_data), .xbus_cs_valid(xbus_cs_valid),
	.ew_cs_busy(ew_cs_busy), .ms_busy(at_cs_busy),
	.rel_sync_tile(rel_sync_tile), .rel_sync_pipe(rel_sync_pipe),
	.rel_sync_full(rel_sync_full), .rel_sync_load(rel_sync_load),
	.texel_size(tex_image[52:51]), .copy_fill(other_modes[53]),

	.tile_addr(tile_addr), .cs_tc_data(cs_tc_data),
	.we_tile_size(we_tile_size), .we_tile_attr(we_tile_attr),
	.cs_ew_data(cs_ew_data), .cs_ew_newprim(cs_ew_newprim),
	.cs_xbus_req(cs_xbus_req),
	.cmd(cmd), .start_prim(start_prim), .attr_valid(attr_valid),
	.cmd_busy(cmd_busy));

ew ew (	.gclk(gclk), .reset_l(reset_l),
	.cs_ew_d(cs_ew_data), .cs_ew_newprim(cs_ew_newprim),
	.dxr(ew_dxr), .dxg(ew_dxg), .dxb(ew_dxb), .dxa(ew_dxa), .dxz(ew_dxz),
	.dxs(ew_dxs), .dxt(ew_dxt), .dxw(ew_dxw),
	.dyr(ew_dyr), .dyg(ew_dyg), .dyb(ew_dyb), .dya(ew_dya), .dyz(ew_dyz),
	.dys(ew_dys), .dyt(ew_dyt), .dyw(ew_dyw),
	.left_xmajor(ew_major_left), .left_xminor(ew_minor_left),
	.left_offset(ew_offset_left),
	.sign_dxhdy_xmajor(ew_major_sign), .sign_dxhdy_offset(ew_offset_sign),
	.width_cimage(color_image[41:32]), .width_timage(tex_image[41:32]),
	.pixel_size(color_image[52:51]), .texel_size(tex_image[52:51]),
	.cycle_type(other_modes[53:52]),
	.scbox_xmin(scissor[55:44]), .scbox_xmax(scissor[23:12]),
	.scbox_ymin(scissor[43:32]), .scbox_ymax(scissor[11:0]),
	.load_cmd_image(ew_image_load), .load_cmd_scissor(ew_scissor_load),
	.load_cmd_ewstall(ew_stall_load), .load_cmd_offset(ew_offset_load),
        .load_cmd_tlut(ew_stall_tlut),
	.sc_field(scissor[25]), .odd_line(scissor[24]), .flush(flush),

	.ew_cs_busy(ew_cs_busy),
	.ew_cv_d(ew_cv_d), .ew_cv_newspan(ew_cv_newspan),
	.ew_cv_start_x(ew_cv_start_x), .ew_ms_length(ew_ms_length),
	.ew_ep_d(ew_ep_d), .ew_ep_startspan(ew_ep_startspan),
	.ew_ms_addr(ew_ms_addr),
	.y_dither(y_dither));

cv cv (	.gclk(gclk), .reset_l(reset_l),
	.ew_cv_data(ew_cv_d), .ew_cv_start_x(ew_cv_start_x),
	.cycle_type(other_modes[52]),
	 .ew_cv_newspan(ew_cv_newspan), .left(cv_left),

	.cv_value(cv_value), .mask15(mask15),
	.x_offset(x_offset), .y_offset(y_offset), .x_dither(x_dither));

ep ep (	.gclk(gclk), .dither_type(other_modes[38]),
	.cycle_type(other_modes[53:52]), .tlut_en(other_modes[47]),
	.tc_load(tc_load), .ew_st_span(ew_ep_startspan), .ew_d(ew_ep_d),
	.cv_x_offset(x_offset), .cv_y_offset(y_offset),
        .cv_cvg(cv_value), .cv_mask(mask15),
	.x_dither(x_dither), .y_dither(y_dither),

        .st_span_st_w(st_span_st_w),
	.st_span_st_s(st_span_st_s), .st_span_st_t(st_span_st_t),
        .st_span_st_r(st_span_st_r), .st_span_st_g(st_span_st_g),
	.st_span_st_b(st_span_st_b), .st_span_st_a(st_span_st_a),
        .st_span_st_z(st_span_st_z),
	.st_span_tc(st_span_tc), .st_span_tf(st_span_tf),
	.st_span_cc(st_span_cc), .st_span_bl(st_span_bl),
	.st_span_ms(st_span_ms),
        .d_w(d_w), .d_s(d_s), .d_t(d_t),
	.d_r(d_r), .d_g(d_g), .d_b(d_b), .d_a(d_a), .d_z(d_z),
        .x_offset_r(x_offset_r), .x_offset_g(x_offset_g),
	.x_offset_b(x_offset_b), .x_offset_a(x_offset_a),
	.x_offset_z(x_offset_z),
        .y_offset_r(y_offset_r), .y_offset_g(y_offset_g),
	.y_offset_b(y_offset_b), .y_offset_a(y_offset_a),
	.y_offset_z(y_offset_z),
        .cvg_cc(cvg_cc), .mask_bl(mask_bl),
	.rgb_dither(rgb_dither), .alpha_dither(alpha_dither));

at at (	.clk(clk), .gclk(gclk), .reset_l(reset_l),
	.ew_ep_startspan(ew_ep_startspan),
	.cs_st_prim(start_prim), .cs_st_attr(attr_valid),
	.cs_cmd(cmd), .cs_ew_d(cs_ew_data), .ew_cs_busy(ew_cs_busy),
	.ew_addr(ew_ms_addr), .ew_length(ew_ms_length), .spanbufrd(spanbufrd),

        .ew_dxr(ew_dxr), .ew_dxg(ew_dxg), .ew_dxb(ew_dxb), .ew_dxa(ew_dxa),
	.ew_dxz(ew_dxz), .ew_dxs(ew_dxs), .ew_dxt(ew_dxt), .ew_dxw(ew_dxw),
        .ew_dyr(ew_dyr), .ew_dyg(ew_dyg), .ew_dyb(ew_dyb), .ew_dya(ew_dya),
	.ew_dyz(ew_dyz), .ew_dys(ew_dys), .ew_dyt(ew_dyt), .ew_dyw(ew_dyw),
        .st_dxr(st_dxr), .st_dxg(st_dxg), .st_dxb(st_dxb), .st_dxa(st_dxa),
	.st_dxz(st_dxz), .st_dxs(st_dxs), .st_dxt(st_dxt), .st_dxw(st_dxw),
        .st_dyr(st_dyr), .st_dyg(st_dyg), .st_dyb(st_dyb), .st_dya(st_dya),
	.st_dyz(st_dyz), .st_dys(st_dys), .st_dyt(st_dyt), .st_dyw(st_dyw),
	.st_ncyc(st_ncyc), .color_image(color_image), .z_image(z_image),
	.tex_image(tex_image), .combine_mode(combine_mode),
        .env_color(env_color), .prim_color(prim_color),
	.blend_color(blend_color), .fog_color(fog_color),
	.fill_color(fill_color),
        .other_modes(other_modes), .prim_depth(prim_depth),
	.scissor(scissor), .convert(convert), .key_r(key_r), .key_gb(key_gb),
	.noise(noise), .strobe_sync_full(strobe_sync_full),
        .rel_sync_tile(rel_sync_tile), .rel_sync_pipe(rel_sync_pipe),
	.rel_sync_load(rel_sync_load), .ew_image_load(ew_image_load),
	.ew_scissor_load(ew_scissor_load), .ew_stall_load(ew_stall_load),
	.ew_offset_load(ew_offset_load), .tc_load(tc_load),
        .shift_coord(shift_coord), .level(level), .tile(tile),
	.ew_major_sign(ew_major_sign), .ew_offset_sign(ew_offset_sign),
        .ew_major_left(ew_major_left), .ew_minor_left(ew_minor_left),
	.ew_offset_left(ew_offset_left), .cv_left(cv_left),
        .st_r_left(st_r_left), .st_g_left(st_g_left),
	.st_b_left(st_b_left), .st_a_left(st_a_left), .st_z_left(st_z_left),
        .st_s_left(st_s_left), .st_t_left(st_t_left),
	.st_w_left(st_w_left),
	.ms_xi(nextspanxi), .ms_xf(nextspanxf), .ms_count(nextspancount),
	.ms_load(load_en),
	.ms_xdec(nextspanxdec), .spanbufmt(spanbufmt),
	.ew_stall_tlut(ew_stall_tlut), .at_cs_busy(at_cs_busy));

st st (	.gclk(gclk),
	.ep_st_r(d_r[15:0]), .startspan_r(st_span_st_r),
	.at_st_dxr(st_dxr), .at_st_dyr(st_dyr),
	.x_offsetr(x_offset_r), .y_offsetr(y_offset_r),
	.ep_st_g(d_g[15:0]), .startspan_g(st_span_st_g),
	.at_st_dxg(st_dxg), .at_st_dyg(st_dyg),
	.x_offsetg(x_offset_g), .y_offsetg(y_offset_g),
	.ep_st_b(d_b[15:0]), .startspan_b(st_span_st_b),
	.at_st_dxb(st_dxb), .at_st_dyb(st_dyb),
	.x_offsetb(x_offset_b), .y_offsetb(y_offset_b),
	.ep_st_a(d_a[15:0]), .startspan_a(st_span_st_a),
	.at_st_dxa(st_dxa), .at_st_dya(st_dya),
	.x_offseta(x_offset_a), .y_offseta(y_offset_a),
	.ep_st_z(d_z), .startspan_z(st_span_st_z),
	.at_st_dxz(st_dxz), .at_st_dyz(st_dyz),
	.x_offsetz(x_offset_z), .y_offsetz(y_offset_z),
	.ep_st_s(d_s), .startspan_s(st_span_st_s),
	.at_st_dxs(st_dxs), .at_st_dys(st_dys),
	.ep_st_t(d_t), .startspan_t(st_span_st_t),
	.at_st_dxt(st_dxt), .at_st_dyt(st_dyt),
	.ep_st_w(d_w), .startspan_w(st_span_st_w),
	.at_st_dxw(st_dxw), .at_st_dyw(st_dyw),
	.ncyc_r(other_modes[52]), .ncyc_g(other_modes[52]),
	.ncyc_b(other_modes[52]), .ncyc_a(other_modes[52]),
	.ncyc_z(other_modes[52]),
	.ncyc_s(st_ncyc),         .ncyc_t(st_ncyc),
	.ncyc_w(other_modes[52]),
	.left_r(st_r_left), .left_g(st_g_left),
	.left_b(st_b_left), .left_a(st_a_left),
	.left_z(st_z_left),
	.left_s(st_s_left), .left_t(st_t_left),
	.left_w(st_w_left),

	.st_cc_r(st_cc_r), .st_cc_g(st_cc_g),
	.st_cc_b(st_cc_b), .st_cc_a(st_cc_a),
	.st_bl_z(st_bl_z),
	.st_tc_s(st_tc_s), .st_tc_t(st_tc_t),
	.st_tc_w(st_tc_w));

tc tc (	.gclk(gclk),
	.st_span(st_span_tc), .ncyc(other_modes[52]),
	.s(st_tc_s), .t(st_tc_t), .w(st_tc_w),
	.min_level(prim_color[44:40]),
	.detail_en(other_modes[50]), .sharp_en(other_modes[49]),
	.lod_en(other_modes[48]), .persp_en(other_modes[51]), 
        .copy(other_modes[53]), .samp_type(other_modes[45]),
	.tlut_en(other_modes[47]), 
        .max_level(level), .prim_tile(tile), .load(tc_load), 
        .shift_coord(shift_coord), .tile_adrs(tile_addr), 
        .tile_data(cs_tc_data), .we_tile_size(we_tile_size), 
        .we_tile_attr(we_tile_attr),
	.clr_ind_a(clr_ind_a), .clr_ind_b(clr_ind_b),
	.clr_ind_c(clr_ind_c), .clr_ind_d(clr_ind_d), 

	.l_frac(l_frac),
	.s_frac_rg(s_frac_rg), .t_frac_rg(t_frac_rg),
	.s_frac_ba(s_frac_ba), .t_frac_ba(t_frac_ba), 
        .adrs_bnk0l(adrs_bnk0l), .adrs_bnk1l(adrs_bnk1l), 
        .adrs_bnk2l(adrs_bnk2l), .adrs_bnk3l(adrs_bnk3l), 
        .adrs_bnk0h(adrs_bnk0h), .adrs_bnk1h(adrs_bnk1h), 
        .adrs_bnk2h(adrs_bnk2h), .adrs_bnk3h(adrs_bnk3h),
	.adrs_a(adrs_a), .adrs_b_ba(adrs_b_ba), .adrs_b_rg(adrs_b_rg),
	.adrs_c(adrs_c), .adrs_d_ba(adrs_d_ba), .adrs_d_rg(adrs_d_rg),
	.swap_rg(swap_rg), .swap_ba(swap_ba),
	.tile_tex_type_1d(tile_tex_type_1d), 
        .tile_tex_size_1d(tile_tex_size_1d), .palette(palette), 
        .odd_t(odd_t), .a_three(a_three), .a_twelve(a_twelve));

tm tm (	.gclk(gclk), .reset_l(reset_l),
	.bist_go(bist_go), .bist_check(bist_check),
	.tlut_en(other_modes[47]), .tlut_type(other_modes[46]), 
        .adrs_bnk0l(adrs_bnk0l), .adrs_bnk1l(adrs_bnk1l), 
        .adrs_bnk2l(adrs_bnk2l), .adrs_bnk3l(adrs_bnk3l), 
        .adrs_bnk0h(adrs_bnk0h), .adrs_bnk1h(adrs_bnk1h), 
        .adrs_bnk2h(adrs_bnk2h), .adrs_bnk3h(adrs_bnk3h), 
        .adrs_a(adrs_a), .adrs_b_ba(adrs_b_ba), .adrs_b_rg(adrs_b_rg),
	.adrs_c(adrs_c), .adrs_d_ba(adrs_d_ba), .adrs_d_rg(adrs_d_rg), 
        .swap_rg(swap_rg), .swap_ba(swap_ba),
	.tile_tex_type(tile_tex_type_1d),
	.tile_tex_size(tile_tex_size_1d), .palette(palette),
	.odd_t(odd_t), .a_three(a_three), .a_twelve(a_twelve),

	.clr_ind_a(clr_ind_a), .clr_ind_b(clr_ind_b), 
	.clr_ind_c(clr_ind_c), .clr_ind_d(clr_ind_d),
	.red_a(tm_ra), .green_a(tm_ga), .blue_a(tm_ba), .alpha_a(tm_aa),
	.red_b(tm_rb), .green_b(tm_gb), .blue_b(tm_bb), .alpha_b(tm_ab),
	.red_c(tm_rc), .green_c(tm_gc), .blue_c(tm_bc), .alpha_c(tm_ac),
	.red_d(tm_rd), .green_d(tm_gd), .blue_d(tm_bd), .alpha_d(tm_ad),
	.copy_load(copy_load), .load_dv(load_dv), .bist_done(bist_done),
	.bist0_fail(bist0_fail), .bist1_fail(bist1_fail),
	.bist2_fail(bist2_fail), .bist3_fail(bist3_fail),
	.bist4_fail(bist4_fail), .bist5_fail(bist5_fail),
	.bist6_fail(bist6_fail), .bist7_fail(bist7_fail));

tf tf (	.gclk(gclk),
	.st_span(st_span_tf), .ncyc(other_modes[52]),
	.bilerp0m(other_modes[43]), .bilerp1m(other_modes[42]),
	.convert_one(other_modes[41]), .mid_texel(other_modes[44]),
        .k0_coeff(convert[53:45]), .k1_coeff(convert[44:36]),
	.k2_coeff(convert[35:27]), .k3_coeff(convert[26:18]),
        .lod_frac(l_frac),
	.sfrac_rg(s_frac_rg), .tfrac_rg(t_frac_rg),
	.sfrac_ba(s_frac_ba), .tfrac_ba(t_frac_ba),
        .tm_ra(tm_ra), .tm_ga(tm_ga), .tm_ba(tm_ba), .tm_aa(tm_aa),
        .tm_rb(tm_rb), .tm_gb(tm_gb), .tm_bb(tm_bb), .tm_ab(tm_ab),
        .tm_rc(tm_rc), .tm_gc(tm_gc), .tm_bc(tm_bc), .tm_ac(tm_ac),
        .tm_rd(tm_rd), .tm_gd(tm_gd), .tm_bd(tm_bd), .tm_ad(tm_ad),

        .tf_r(tf_r), .tf_g(tf_g), .tf_b(tf_b), .tf_a(tf_a),
	.tf_lod_frac(tf_lod_frac));

cc cc (	.gclk(gclk),
	.st_span(st_span_cc), .ncyc(other_modes[52]),
        .key_en(other_modes[40]), .texture_edge_mode(other_modes[15]),
	.cvg_times_alpha(other_modes[12]), .alpha_cvg_select(other_modes[13]),
        .cc_x_sel_0_r(combine_mode[55:52]), .cc_y_sel_0_r(combine_mode[31:28]),
	.cc_a_sel_0_r(combine_mode[51:47]), .cc_c_sel_0_r(combine_mode[17:15]),
        .cc_x_sel_0_a(combine_mode[46:44]), .cc_y_sel_0_a(combine_mode[14:12]),
	.cc_a_sel_0_a(combine_mode[43:41]), .cc_c_sel_0_a(combine_mode[11:9]),
        .cc_x_sel_1_r(combine_mode[40:37]), .cc_y_sel_1_r(combine_mode[27:24]),
	.cc_a_sel_1_r(combine_mode[36:32]), .cc_c_sel_1_r(combine_mode[8:6]),
        .cc_x_sel_1_a(combine_mode[23:21]), .cc_y_sel_1_a(combine_mode[5:3]),
	.cc_a_sel_1_a(combine_mode[20:18]), .cc_c_sel_1_a(combine_mode[2:0]),
        .st_r(st_cc_r), .st_g(st_cc_g), .st_b(st_cc_b), .st_a(st_cc_a),
        .tf_r(tf_r), .tf_g(tf_g), .tf_b(tf_b), .tf_a(tf_a),
        .tf_lod_frac(tf_lod_frac), .prim_lod_frac({1'b0,prim_color[39:32]}),
        .prim_r(prim_color[31:24]), .prim_g(prim_color[23:16]),
	.prim_b(prim_color[15:8]), .prim_a(prim_color[7:0]),
        .env_r(env_color[31:24]), .env_g(env_color[23:16]),
	.env_b(env_color[15:8]), .env_a(env_color[7:0]),
        .center_r(key_r[15:8]), .center_g(key_gb[31:24]),
	.center_b(key_gb[15:8]),
        .scale_r(key_r[7:0]), .scale_g(key_gb[23:16]),
	.scale_b(key_gb[7:0]),
        .width_r(key_r[27:16]), .width_g(key_gb[55:44]),
	.width_b(key_gb[43:32]),
        .k4_coeff(convert[17:9]), .k5_coeff(convert[8:0]),
        .noise(noise), .cvg(cvg_cc),
        .dither_sel(other_modes[37:36]), .alpha_dither(alpha_dither),

        .shade_a(shade_a),
        .pixel_r(pixel_r), .pixel_g(pixel_g), .pixel_b(pixel_b),
	.pixel_a(pixel_a), .pixel_cvg(pixel_cvg));

bl bl (	.gclk(gclk),
	.st_span(st_span_bl), .ncyc(other_modes[52]),
        .z_source_select(other_modes[2]),
	.antialias_enable(other_modes[3]), .z_compare_enable(other_modes[4]),
	.z_update_enable(other_modes[5]), .z_mode(other_modes[11:10]),
        .cvg_dest(other_modes[9:8]), .color_on_cvg(other_modes[7]),
	.force_blend(other_modes[14]), .mask15b(mask_bl),
        .bl_p_sel_0_r(other_modes[31:30]), .bl_m_sel_0_r(other_modes[23:22]),
	.bl_a_sel_0_r(other_modes[27:26]), .bl_b_sel_0_r(other_modes[19:18]),
        .bl_p_sel_1_r(other_modes[29:28]), .bl_m_sel_1_r(other_modes[21:20]),
	.bl_a_sel_1_r(other_modes[25:24]), .bl_b_sel_1_r(other_modes[17:16]),
        .blend_r(blend_color[31:24]), .blend_g(blend_color[23:16]),
	.blend_b(blend_color[15:8]),
	.fog_r(fog_color[31:24]), .fog_g(fog_color[23:16]),
	.fog_b(fog_color[15:8]), .fog_a(fog_color[7:0]),
        .pixel_r(pixel_r), .pixel_g(pixel_g), .pixel_b(pixel_b),
	.pixel_a(pixel_a), .pixel_cvg(pixel_cvg), .shade_a(shade_a),
	.st_z(st_bl_z), .dzdx(st_dxz[31:16]), .dzdy(st_dyz[21:6]),
	.prim_z(prim_depth[31:16]), .prim_delta_z(prim_depth[15:0]),
        .mem_r(mem_r), .mem_g(mem_g), .mem_b(mem_b),
	.mem_a(mem_a), .mem_z(mem_z),

        .span_r(span_r), .span_g(span_g), .span_b(span_b),
	.span_a(span_a), .span_z(span_z),
        .span_color_we(span_color_we), .span_depth_we(span_depth_we));

endmodule // rdp
