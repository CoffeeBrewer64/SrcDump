d38 1
a38 1
u32 test_mem_poff = 1;
d56 1
a56 1
output_led(u32 value)
d69 1
a69 1
test_fail(u32 reason)
d103 2
a104 2
u32
test_mem8(u8 *b, u8 *e, u32 poff)
d106 2
a107 2
	u32 roff, val, exp;
	u8 *p;
d125 2
a126 2
		val = (u32) *(p + (roff & 0x3));
		exp = (u32) test_mem_primes[roff++];
d139 2
a140 2
u32
test_mem16(u16 *b, u16 *e, u32 poff)
d142 2
a143 2
	u32 roff, val, exp;
	u16 *p;
d162 2
a163 2
		val = (u32) *(p + (roff & 0x1));
		exp = (u32) (test_mem_primes[roff+0])
d178 2
a179 2
u32
test_mem32(u32 *b, u32 *e, u32 poff)
d181 2
a182 2
	u32 roff, val, exp;
	u32 *p;
