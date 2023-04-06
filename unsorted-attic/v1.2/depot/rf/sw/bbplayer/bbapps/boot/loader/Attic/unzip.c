#include "ultra64.h"
#include "gzip.h"

static u32 bb_outbytes_limit; 

struct huft {
	u8 e;			/* number of extra bits or operation */
	u8 b;			/* number of bits in this code or subcode */
	union {
	u16 n;			/* literal, length base, or distance base */
	struct huft *t;	/* pointer to next level of table */
	} v;
};


int huft_build(unsigned int *, unsigned int, unsigned int, u16 *, u16 *, struct huft **, int *);
int huft_free(struct huft *);
int inflate_codes(struct huft *, struct huft *, int, int);
int inflate_stored(void);
int inflate_fixed(void);
int inflate_dynamic(void);
int inflate_block(int *);
int inflate(void);


#define wp outcnt
#define flush_output(w) (wp=(w),flush_window())


// Order of the bit length code lengths
static unsigned int border[] = {
		16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
// Copy lengths for literal codes 257..285
static u16 cplens[] = {
		3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,
		35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0};
// Extra bits for literal codes 257..285
static u16 cplext[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
		3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 99, 99};		// 99==invalid
// Copy offsets for distance codes 0..29
static u16 cpdist[] = {
		1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
		257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145,
		8193, 12289, 16385, 24577};
// Extra bits for distance codes
static u16 cpdext[] = {
		0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
		7, 7, 8, 8, 9, 9, 10, 10, 11, 11,
		12, 12, 13, 13};

u32 bb;				// bit buffer
unsigned int bk;	// bits in bit buffer

u16 mask_bits[] = {
	0x0000,
	0x0001, 0x0003, 0x0007, 0x000f, 0x001f, 0x003f, 0x007f, 0x00ff,
	0x01ff, 0x03ff, 0x07ff, 0x0fff, 0x1fff, 0x3fff, 0x7fff, 0xffff
};

#define NEXTBYTE()	(u8)get_byte()
#define NEEDBITS(n) {while(k<(n)){b|=((u32)NEXTBYTE())<<k;k+=8;}}
#define DUMPBITS(n) {b>>=(n);k-=(n);}

int lbits = 9;			/* bits in base literal/length lookup table */
int dbits = 6;			/* bits in base distance lookup table */

/* If BMAX needs to be larger than 16, then h and x[] should be u32. */
#define BMAX 16		 /* maximum bit length of any code (16 for explode) */
#define N_MAX 288		 /* maximum number of codes in any set */

unsigned int hufts;		 /* track memory usage */

// Buffer
#define	GZIP_MEM_BUFFSIZ	16384
static	char	gzip_mem_buff[GZIP_MEM_BUFFSIZ];
static	char	*gzip_malloc_addr = gzip_mem_buff;
static	long	gzip_malloc_tmp = 0;


//===========================================================================
//
//
char *gzip_malloc(long size)
{
	char	*ret;

	gzip_malloc_tmp += size;

	if ( gzip_malloc_tmp > GZIP_MEM_BUFFSIZ ) {
		// Debug
		// printf("memory overflow\n");
		return(NULL);
	}

	ret = gzip_malloc_addr;
	gzip_malloc_addr += size;

	return(ret);
}



//===========================================================================
//
//
void	gzip_free(char *ptr)
{
	// Debug
	//if ( gzip_malloc_tmp != 0 ) printf("%ld byte free\n", gzip_malloc_tmp);

	gzip_malloc_tmp = 0;
	gzip_malloc_addr = gzip_mem_buff;
}



//===========================================================================
//
//
int huft_build(unsigned int *b, unsigned int n, unsigned int s, u16 *d, u16 *e, struct huft **t, int *m)
{
	unsigned int a;				/* counter for codes of length k */
	unsigned int c[BMAX+1];		/* bit length count table */
	unsigned int f;				/* i repeats in table every f entries */
	int g;						/* maximum code length */
	int h;						/* table level */
	register unsigned int i;	/* counter, current code */
	register unsigned int j;	/* counter */
	register int k;				/* number of bits in current code */
	int l;						/* bits per table (returned in m) */
	register unsigned int *p;	/* pointer into c[], b[], or v[] */
	register struct huft *q;	/* points to current table */
	struct huft r;				/* table entry for structure assignment */
	struct huft *u[BMAX];		/* table stack */
	static unsigned int v[N_MAX];		/* values in order of bit length */
	register int w;				/* bits before this table == (l * h) */
	unsigned int x[BMAX+1];		/* bit offsets, then code stack */
	unsigned int *xp;			/* pointer into x */
	int y;						/* number of dummy codes added */
	unsigned int z;				/* number of entries in current table */

	/* Generate counts for each bit length */
	for ( j = 0; j < (BMAX+1); j++ ) c[j] = 0;

	p = b;	i = n;
	do {
		c[*p]++;					/* assume all entries <= BMAX */
		p++;						/* Can't combine with above line (Solaris bug) */
	} while (--i);
	if (c[0] == n) {				/* null input--all zero length codes */
		*t = (struct huft *)NULL;
		*m = 0;
		return 0;
	}

	/* Find minimum and maximum length, bound *m by those */
	l = *m;
	for (j = 1; j <= BMAX; j++)
	if (c[j]) break;
	k = j;						/* minimum code length */
	if ((unsigned int)l < j) l = j;
	for (i = BMAX; i; i--) if (c[i]) break;
	g = i;						/* maximum code length */
	if ((unsigned int)l > i) l = i;
	*m = l;

	/* Adjust last length count to fill out codes, if needed */
	for (y = 1 << j; j < i; j++, y <<= 1) {
		if ((y -= c[j]) < 0) return 2;				 /* bad input: more codes than bits */
	}
	if ((y -= c[i]) < 0) return 2;
	c[i] += y;

	/* Generate starting offsets into the value table for each length */
	x[1] = j = 0;
	p = c + 1;	xp = x + 2;
	while (--i) {				 /* note that i == g from above */
		*xp++ = (j += *p++);
	}


	/* Make a table of values in order of bit lengths */
	p = b;	i = 0;
	do {
		if ((j = *p++) != 0) v[x[j]++] = i;
	} while (++i < n);


	/* Generate the Huffman codes and for each, make the table entries */
	x[0] = i = 0;				 /* first Huffman code is zero */
	p = v;						/* grab values in bit order */
	h = -1;						 /* no tables yet--level -1 */
	w = -l;						 /* bits decoded == (l * h) */
	u[0] = (struct huft *)NULL;	 /* just to keep compilers happy */
	q = (struct huft *)NULL;		/* ditto */
	z = 0;						/* ditto */

	/* go through the bit lengths (k already is bits in shortest code) */
	for (; k <= g; k++) {
		a = c[k];
		while (a--) {
			/* here i is the Huffman code of length k bits for value *p */
			/* make tables up to required level */
			while (k > w + l) {
				h++;
				w += l;				 /* previous table always l bits */

				/* compute minimum size table less than or equal to l bits */
				z = (z = g - w) > (unsigned int)l ? l : z;	/* upper limit on table size */
				if ((f = 1 << (j = k - w)) > a + 1)	{ /* try a k-w bit table */
					/* too few codes for k-w bit table */
					f -= a + 1;			 /* deduct codes from patterns left */
					xp = c + k;
					while (++j < z)		 /* try smaller tables up to z bits */
					{
						if ((f <<= 1) <= *++xp)	break;			/* enough codes to use up j bits */
						f -= *xp;			 /* else deduct codes from patterns */
					}
				}
				z = 1 << j;			 /* table entries for j-bit table */

				/* allocate and link in new table */
				if ( ( q = (struct huft *)gzip_malloc( (z + 1)*sizeof(struct huft) ) ) == (struct huft *)NULL ) {
					if (h) huft_free(u[0]);
					return 3;			 /* not enough memory */
				}
				hufts += z + 1;		 /* track memory usage */
				*t = q + 1;			 /* link to list for huft_free() */
				*(t = &(q->v.t)) = (struct huft *)NULL;
				u[h] = ++q;			 /* table starts after link */

				/* connect to last table, if there is one */
				if (h) {
					x[h] = i;			 /* save pattern for backing up */
					r.b = (u8)l;		 /* bits to dump before this table */
					r.e = (u8)(16 + j);	/* bits in this table */
					r.v.t = q;			/* pointer to this table */
					j = i >> (w - l);	 /* (get around Turbo C bug) */
					u[h-1][j] = r;		/* connect to last table */
				}
			}

			/* set up table entry in r */
			r.b = (u8)(k - w);
			if (p >= v + n) {
				r.e = 99;				 /* out of values--invalid code */
			} else if (*p < s) {
				r.e = (u8)(*p < 256 ? 16 : 15);	/* 256 is end-of-block code */
				r.v.n = (u16)(*p);			 /* simple code is just the value */
				p++;							 /* one compiler does not like *p++ */
			} else {
				r.e = (u8)e[*p - s];	 /* non-simple--look up in lists */
				r.v.n = d[*p++ - s];
			}

			/* fill code-like entries with r */
			f = 1 << (k - w);
			for (j = i >> w; j < z; j += f) q[j] = r;

			/* backwards increment the k-bit code i */
			for (j = 1 << (k - 1); i & j; j >>= 1) i ^= j;
			i ^= j;

			/* backup over finished tables */
			while ((i & ((1 << w) - 1)) != x[h]) {
				h--;					/* don't need to update q */
				w -= l;
			}
		}
	}

	/* Return true (1) if we were given an incomplete table */
	return y != 0 && g != 1;
}



int huft_free(struct huft *t)
{
	register struct huft *p, *q;

	/* Go through linked list, freeing from the malloced (t[-1]) address. */
	p = t;
	while (p != (struct huft *)NULL) {
		q = (--p)->v.t;
		gzip_free((char*)p);
		p = q;
	} 
	return 0;
}


int inflate_codes(struct huft *tl, struct huft *td, int bl, int bd)
{
	register unsigned int e;	/* table entry flag/number of extra bits */
	unsigned int n, d;		/* length and index for copy */
	unsigned int w;			 /* current window position */
	struct huft *t;		 /* pointer to table entry */
	unsigned int ml, md;		/* masks for bl and bd bits */
	register u32 b;		 /* bit buffer */
	register unsigned int k;	/* number of bits in bit buffer */

	/* make local copies of globals */
	b = bb;						 /* initialize bit buffer */
	k = bk;
	w = wp;						 /* initialize window position */

	/* inflate the coded data */
	ml = mask_bits[bl];			 /* precompute masks for speed */
	md = mask_bits[bd];
	for (;;) {						/* do until end of block */
		NEEDBITS((unsigned int)bl)
		if ((e = (t = tl + ((unsigned int)b & ml))->e) > 16) {
			do {
				if (e == 99) return 1;
				DUMPBITS(t->b)
				e -= 16;
				NEEDBITS(e)
			} while ((e = (t = t->v.t + ((unsigned int)b & mask_bits[e]))->e) > 16);
		}
		DUMPBITS(t->b)
		if (e == 16) {				/* then it's a literal */
			window[w++] = (u8)t->v.n;
			if (w == WSIZE) {
				if(flush_output(w)<0)return -1;;
				w = 0;
			}
		} else {					/* it's an EOB or a length */
			/* exit if end of block */
			if (e == 15) break;
			/* get length of block to copy */
			NEEDBITS(e)
			n = t->v.n + ((unsigned int)b & mask_bits[e]);
			DUMPBITS(e);
			/* decode distance of block to copy */
			NEEDBITS((unsigned int)bd)
			if ((e = (t = td + ((unsigned int)b & md))->e) > 16) {
				do {
					if (e == 99)
					return 1;
					DUMPBITS(t->b)
					e -= 16;
					NEEDBITS(e)
				} while ((e = (t = t->v.t + ((unsigned int)b & mask_bits[e]))->e) > 16);
			}
			DUMPBITS(t->b)
			NEEDBITS(e)
			d = w - t->v.n - ((unsigned int)b & mask_bits[e]);
			DUMPBITS(e)

			/* do the copy */
			do {
				n -= (e = (e = WSIZE - ((d &= WSIZE-1) > w ? d : w)) > n ? n : e);
/*
//#if !defined(NOMEMCPY) && !defined(DEBUG)
				if (w - d >= e) {			// (this test assumes unsigned comparison)
					dst = (u8 *)( (u32)window + (u32)w );
					src = (u8 *)( (u32)window + (u32)d );
					for ( i = 0; i < e; i++ ) {
						*dst = *src;
						dst++;
						src++;
					}
					w += e;
					d += e;
				} else						// do it slow to avoid memcpy() overlap
//#endif  !NOMEMCPY
*/
				do {
					window[w++] = window[d++];
				} while (--e);
				if (w == WSIZE) {
					if(flush_output(w)<0)return -1;
					w = 0;
				}
			} while (n);
		}
	}


	/* restore the globals from the locals */
	wp = w;						 /* restore global window pointer */
	bb = b;						 /* restore global bit buffer */
	bk = k;

	/* done */
	return 0;
}



int inflate_stored(void)
/* "decompress" an inflated type 0 (stored) block. */
{
	unsigned int n;			 /* number of bytes in block */
	unsigned int w;			 /* current window position */
	register u32 b;		 /* bit buffer */
	register unsigned int k;	/* number of bits in bit buffer */

	/* make local copies of globals */
	b = bb;						 /* initialize bit buffer */
	k = bk;
	w = wp;						 /* initialize window position */

	/* go to byte boundary */
	n = k & 7;
	DUMPBITS(n);

	/* get the length and its complement */
	NEEDBITS(16)
	n = ((unsigned int)b & 0xffff);
	DUMPBITS(16)
	NEEDBITS(16)
	if (n != (unsigned int)((~b) & 0xffff)) return 1;			/* error in compressed data */
	DUMPBITS(16)

	/* read and output the compressed data */
	while (n--) {
		NEEDBITS(8)
		window[w++] = (u8)b;
		if (w == WSIZE) {
			if(flush_output(w)<0)return -1;
			w = 0;
		}
		DUMPBITS(8)
	}

	/* restore the globals from the locals */
	wp = w;						 /* restore global window pointer */
	bb = b;						 /* restore global bit buffer */
	bk = k;
	return 0;
}



int inflate_fixed(void)
/* decompress an inflated type 1 (fixed Huffman codes) block.	We should
	 either replace this with a custom decoder, or at least precompute the
	 Huffman tables. */
{
	int i;				/* temporary variable */
	struct huft *tl;		/* literal/length code table */
	struct huft *td;		/* distance code table */
	int bl;				 /* lookup bits for tl */
	int bd;				 /* lookup bits for td */
static	unsigned int l[288];		/* length list for huft_build */

	/* set up literal table */
	for (i = 0; i < 144; i++)
	l[i] = 8;
	for (; i < 256; i++)
	l[i] = 9;
	for (; i < 280; i++)
	l[i] = 7;
	for (; i < 288; i++)			/* make a complete, but wrong code set */
	l[i] = 8;
	bl = 7;
	if ((i = huft_build(l, 288, 257, cplens, cplext, &tl, &bl)) != 0) return i;

	/* set up distance table */
	for (i = 0; i < 30; i++) l[i] = 5;	/* make an incomplete code set */
	bd = 5;
	if ((i = huft_build(l, 30, 0, cpdist, cpdext, &td, &bd)) > 1) {
		huft_free(tl);
		return i;
	}

	/* decompress until an end-of-block code */
	if (inflate_codes(tl, td, bl, bd)) return 1;

	/* free the decoding tables, return */
	huft_free(td);
	huft_free(tl);
	return 0;
}



int inflate_dynamic(void)
/* decompress an inflated type 2 (dynamic Huffman codes) block. */
{
	int i;				/* temporary variables */
	unsigned int j;
	unsigned int l;			 /* last length */
	unsigned int m;			 /* mask for bit lengths table */
	unsigned int n;			 /* number of lengths to get */
	struct huft *tl;		/* literal/length code table */
	struct huft *td;		/* distance code table */
	int bl;				 /* lookup bits for tl */
	int bd;				 /* lookup bits for td */
	unsigned int nb;			/* number of bit length codes */
	unsigned int nl;			/* number of literal/length codes */
	unsigned int nd;			/* number of distance codes */
static	unsigned int ll[288+32];	/* literal/length and distance code lengths */
	register u32 b;		 /* bit buffer */
	register unsigned int k;	/* number of bits in bit buffer */

	/* make local bit buffer */
	b = bb;
	k = bk;

	/* read in table lengths */
	NEEDBITS(5)
	nl = 257 + ((unsigned int)b & 0x1f);		/* number of literal/length codes */
	DUMPBITS(5)
	NEEDBITS(5)
	nd = 1 + ((unsigned int)b & 0x1f);			/* number of distance codes */
	DUMPBITS(5)
	NEEDBITS(4)
	nb = 4 + ((unsigned int)b & 0xf);			/* number of bit length codes */
	DUMPBITS(4)
	if (nl > 288 || nd > 32) return 1;		/* bad lengths */

	/* read in bit-length-code lengths */
	for (j = 0; j < nb; j++) {
		NEEDBITS(3)
		ll[border[j]] = (unsigned int)b & 7;
		DUMPBITS(3)
	}
	for (; j < 19; j++) ll[border[j]] = 0;

	/* build decoding table for trees--single level, 7 bit lookup */
	bl = 7;
	if ((i = huft_build(ll, 19, 19, NULL, NULL, &tl, &bl)) != 0) {
		if (i == 1) huft_free(tl);
		return i;					 /* incomplete code set */
	}

	/* read in literal and distance code lengths */
	n = nl + nd;
	m = mask_bits[bl];
	i = l = 0;
	while ((unsigned int)i < n) {
		NEEDBITS((unsigned int)bl)
		j = (td = tl + ((unsigned int)b & m))->b;
		DUMPBITS(j)
		j = td->v.n;
		if (j < 16) {				 /* length of code in bits (0..15) */
			ll[i++] = l = j;			/* save last length in l */
		} else if (j == 16) {			 /* repeat last length 3 to 6 times */
			NEEDBITS(2)
			j = 3 + ((unsigned int)b & 3);
			DUMPBITS(2)
			if ((unsigned int)i + j > n) return 1;
			while (j--) ll[i++] = l;
		} else if (j == 17) {			 /* 3 to 10 zero length codes */
			NEEDBITS(3)
			j = 3 + ((unsigned int)b & 7);
			DUMPBITS(3)
			if ((unsigned int)i + j > n) return 1;
			while (j--) ll[i++] = 0;
			l = 0;
		} else {						/* j == 18: 11 to 138 zero length codes */
			NEEDBITS(7)
			j = 11 + ((unsigned int)b & 0x7f);
			DUMPBITS(7)
			if ((unsigned int)i + j > n) return 1;
			while (j--) ll[i++] = 0;
			l = 0;
		}
	}


	/* free decoding table for trees */
	huft_free(tl);

	/* restore the global bit buffer */
	bb = b;
	bk = k;

	/* build the decoding tables for literal/length and distance codes */
	bl = lbits;
	if ((i = huft_build(ll, nl, 257, cplens, cplext, &tl, &bl)) != 0) {
		if (i == 1) {
			huft_free(tl);
		}
		return i;					 /* incomplete code set */
	}
	bd = dbits;
	if ((i = huft_build(ll + nl, nd, 0, cpdist, cpdext, &td, &bd)) != 0) {
		if (i == 1) i = 0;
	}

	/* decompress until an end-of-block code */
	if (inflate_codes(tl, td, bl, bd)) return 1;

	/* free the decoding tables, return */
	huft_free(td);
	huft_free(tl);
	return 0;
}



/* decompress an inflated block */
int inflate_block(int *e)
{
	unsigned int t;				/* block type */
	register u32 b;				/* bit buffer */
	register unsigned int k;	/* number of bits in bit buffer */

	/* make local bit buffer */
	b = bb;
	k = bk;

	/* read in last block bit */
	NEEDBITS(1)
	*e = (int)b & 1;
	DUMPBITS(1)

	/* read in block type */
	NEEDBITS(2)
	t = (unsigned int)b & 3;
	DUMPBITS(2)

	/* restore the global bit buffer */
	bb = b;
	bk = k;

	/* inflate that block type */
	if (t == 2) return inflate_dynamic();
	if (t == 0) return inflate_stored();
	if (t == 1) return inflate_fixed();

	/* bad block type */
	return 2;
}



//===========================================================================
// decompress an inflated entry
//===========================================================================
int inflate(void)
{
	int e;				// last block flag
	int r;				// result code
	unsigned int h;		// maximum struct huft's malloc'ed

	// initialize window, bit buffer
	wp = 0;
	bk = 0;
	bb = 0;

	// initialize malloc buffer
	gzip_malloc_tmp = 0;
	gzip_malloc_addr = gzip_mem_buff;

	// decompress until the last block
	h = 0;
	do {
		hufts = 0;
		if ( ( r = inflate_block(&e) ) != 0 ) return r;
		if ( hufts > h ) h = hufts;
	} while (!e);

	// Undo too much lookahead. The next read will be byte aligned so we
	// can discard unused bits in the last meaningful byte.
	while ( bk >= 8 ) {
		bk -= 8;
		inptr--;
	}

	// flush out window
	if(flush_output(wp)<0)return -1;

	// return success
	return 0;
}

// 展開バッファ
unsigned char	inbuf[INBUFSIZ];
unsigned char	outbuf[OUTBUFSIZ];
unsigned char	window[WSIZE];

// ワーク
FILE_HND  ifd;				/* input file descriptor */
FILE_HND  ofd;				/* output file descriptor */
long bytes_in;				/* number of input bytes */
long bytes_out;				/* number of output bytes */
unsigned int insize;		/* valid bytes in inbuf */
unsigned int inptr;			/* index of next byte to be processed in inbuf */
unsigned int outcnt;		/* bytes in output buffer */


void clear_bufs(void);
u32 updcrc(u8 *s, unsigned int n);


//========================================================================
// Table of CRC-32's of all single-byte values
//========================================================================
static	u32 crc_32_tab[] = {
 0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4,
 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7, 0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
 0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
 0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59, 0x26d930ac, 0x51de003a,
 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f,
 0x9fbfe4a5, 0xe8b8d433, 0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
 0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65, 0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5,
 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
 0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6,
 0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1, 0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
 0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
 0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b, 0xd80d2bda, 0xaf0a1b4c,
 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
 0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31,
 0x2cd99e8b, 0x5bdeae1d, 0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777, 0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7,
 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
 0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8,
 0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};




u32	data_read(FILE_HND *infile, u8 *dst_addr, u32 size)
{
	u32	i;

	if ( infile->rest_size < size ) size = infile->rest_size;

	i = ( size + 7 ) & 0xfffffff8;

	if ( i != 0 ) {
            bcopy(infile->next_addr, dst_addr, i);
	}

	infile->rest_size -= i;
	infile->next_addr += i;
	if ( infile->rest_size & 0x80000000 ) infile->rest_size = 0;

	return(size);
}



//===========================================================================
// メモリ書き出し
//
u32	data_write(FILE_HND *outfile, u8 *src_addr, unsigned int size)
{
	u32	i;
	u8	*dst_addr = (u8 *)outfile->next_addr;

	for ( i = 0; i < size; i++ ) {
		*dst_addr = src_addr[i];
		dst_addr++;
	}
	outfile->rest_size += size;
	outfile->next_addr = dst_addr;

	return(size);
}



//===========================================================================
// 展開
//
int unzip(void)
{
	int	res;
	int	n;
	u8	buf[32];		// extended local header

	updcrc(NULL, 0);	// initialize crc

	// Decompress
	res = inflate();
	if ( res == 3 ) {
		return(-1);
	} else if ( res != 0 ) {
		return(-1);
	}

	// Get the crc and original length
	for ( n = 0; n < 8; n++ ) buf[n] = (u8)get_byte();

#if 0
        // def DEBUG
	if ( orig_len == bytes_out ) {
		PRINTF("=== ExpOK ===\n");
	} else {
		PRINTF("**** ExpError ****  orglen : %d ,  outlen : %d\n", orig_len, bytes_out);
	}
#endif

	return(0);
}



//===========================================================================
// Run a set of bytes through the crc shift register.  If s is a NULL
// pointer, then initialize the crc shift register contents instead.
// Return the current crc in either case.
//
u32 updcrc(u8 *s, unsigned int n)
{
	register u32 c;		/* temporary variable */

	static u32 crc = 0xffffffff; /* shift register contents */

	if ( s == NULL ) {
		c = 0xffffffff;
	} else {
		c = crc;
		if (n) do {
			c = crc_32_tab[((int)c ^ (*s++)) & 0xff] ^ (c >> 8);
		} while (--n);
	}
	crc = c;
	return c ^ 0xffffffff;	/* (instead of ~c for 64-bit machines) */
}



//===========================================================================
// Clear input and output buffers
void clear_bufs(void)
{
	outcnt = 0;
	insize = inptr = 0;
	bytes_in = bytes_out = 0;
}



//===========================================================================
// Fill the input buffer. This is called only when the buffer is empty.
int fill_inbuf(int eof_ok)
{
	int len;

	insize = 0;
	do {
		len = data_read(&ifd, (char*)inbuf+insize, INBUFSIZ-insize);
		if ( len == 0 || len == -1 ) break;
		insize += len;
	} while (insize < INBUFSIZ);

	if ( insize == 0 ) {
		if (eof_ok) return -1;
	}

	bytes_in += (u32)insize;
	inptr = 1;

	return inbuf[0];
}



//===========================================================================
// Does the same as write(), but also handles partial pipe writes and checks
// for error return.
void write_buf(FILE_HND *fd, char *buf, unsigned int cnt)
{
	u32 n;

	while ( ( n = data_write(fd, buf, cnt) ) != cnt ) {
		cnt -= n;
		buf += n;
	}
}



//===========================================================================
// Write the output window window[0..outcnt-1] and update crc and bytes_out.
// (Used for the decompressed data only.)
int flush_window(void)
{
	if (outcnt == 0) return 0;
	updcrc(window, outcnt);

    if((bytes_out+outcnt)>bb_outbytes_limit)
        return -1;
	write_buf(&ofd, (char *)window, outcnt);
	bytes_out += (u32)outcnt;
	outcnt = 0;

    return 0;
}

u32 expand_gzip(u8 *src_addr, u8 *dst_addr, u32 size, u32 outbytes_limit)
{
	ifd.next_addr = src_addr;
	ifd.rest_size = size;
	ofd.next_addr = dst_addr;
	ofd.rest_size = 0;
        bb_outbytes_limit = outbytes_limit;

	clear_bufs();
	unzip();
	return ofd.rest_size;
}
