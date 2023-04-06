d1 10
d17 1
d19 16
d104 1
a104 1
   // use aes_sbox module from opencores verilog;
d144 5
a148 4
   aes_sbox ksbox3 ( .a(kw0[23:16]), .d(ksub[31:24]) );
   aes_sbox ksbox2 ( .a(kw0[15:8]),  .d(ksub[23:16]) );
   aes_sbox ksbox1 ( .a(kw0[7:0]),   .d(ksub[15:8])  );
   aes_sbox ksbox0 ( .a(kw0[31:24]), .d(ksub[7:0])   );
a175 17

















d298 17
a314 16
   aes_inv_sbox isbox15 ( .a(de_sr[127:120]), .d(de_sub[127:120]) );
   aes_inv_sbox isbox14 ( .a(de_sr[119:112]), .d(de_sub[119:112]) );
   aes_inv_sbox isbox13 ( .a(de_sr[111:104]), .d(de_sub[111:104]) );
   aes_inv_sbox isbox12 ( .a(de_sr[103:96]),  .d(de_sub[103:96])  );
   aes_inv_sbox isbox11 ( .a(de_sr[95:88]),   .d(de_sub[95:88])   );
   aes_inv_sbox isbox10 ( .a(de_sr[87:80]),   .d(de_sub[87:80])   );
   aes_inv_sbox isbox09 ( .a(de_sr[79:72]),   .d(de_sub[79:72])   );
   aes_inv_sbox isbox08 ( .a(de_sr[71:64]),   .d(de_sub[71:64])   );
   aes_inv_sbox isbox07 ( .a(de_sr[63:56]),   .d(de_sub[63:56])   );
   aes_inv_sbox isbox06 ( .a(de_sr[55:48]),   .d(de_sub[55:48])   );
   aes_inv_sbox isbox05 ( .a(de_sr[47:40]),   .d(de_sub[47:40])   );
   aes_inv_sbox isbox04 ( .a(de_sr[39:32]),   .d(de_sub[39:32])   );
   aes_inv_sbox isbox03 ( .a(de_sr[31:24]),   .d(de_sub[31:24])   );
   aes_inv_sbox isbox02 ( .a(de_sr[23:16]),   .d(de_sub[23:16])   );
   aes_inv_sbox isbox01 ( .a(de_sr[15:8]),    .d(de_sub[15:8])    );
   aes_inv_sbox isbox00 ( .a(de_sr[7:0]),     .d(de_sub[7:0])     );
a357 1
   reg [127:0] en_in;			// data to decrypt;
a358 1
   reg [127:0] 	en_out;			// encrypted data;
d400 16
a415 16
   aes_sbox fsbox15 ( .a(en_x[127:120]), .d(en_sub[127:120]) );
   aes_sbox fsbox14 ( .a(en_x[119:112]), .d(en_sub[119:112]) );
   aes_sbox fsbox13 ( .a(en_x[111:104]), .d(en_sub[111:104]) );
   aes_sbox fsbox12 ( .a(en_x[103:96]),  .d(en_sub[103:96])  );
   aes_sbox fsbox11 ( .a(en_x[95:88]),   .d(en_sub[95:88])   );
   aes_sbox fsbox10 ( .a(en_x[87:80]),   .d(en_sub[87:80])   );
   aes_sbox fsbox09 ( .a(en_x[79:72]),   .d(en_sub[79:72])   );
   aes_sbox fsbox08 ( .a(en_x[71:64]),   .d(en_sub[71:64])   );
   aes_sbox fsbox07 ( .a(en_x[63:56]),   .d(en_sub[63:56])   );
   aes_sbox fsbox06 ( .a(en_x[55:48]),   .d(en_sub[55:48])   );
   aes_sbox fsbox05 ( .a(en_x[47:40]),   .d(en_sub[47:40])   );
   aes_sbox fsbox04 ( .a(en_x[39:32]),   .d(en_sub[39:32])   );
   aes_sbox fsbox03 ( .a(en_x[31:24]),   .d(en_sub[31:24])   );
   aes_sbox fsbox02 ( .a(en_x[23:16]),   .d(en_sub[23:16])   );
   aes_sbox fsbox01 ( .a(en_x[15:8]),    .d(en_sub[15:8])    );
   aes_sbox fsbox00 ( .a(en_x[7:0]),     .d(en_sub[7:0])     );
d455 2
d458 521
d980 1
