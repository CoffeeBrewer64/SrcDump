#ifndef _BYTE_SWAP_
#define _BYTE_SWAP_
#ifdef __sgi__
#define WORD_SWAP(x) ((((x) & 0xff000000) >> 24) | (((x) & 0xff0000) >> 8) | (((x) & 0xff00) << 8) | (((x) & 0xff) << 24))
#define SHORT_SWAP(x) ((((x) & 0xff00) >> 8) | (((x) & 0xff) << 8))
#else
#define WORD_SWAP(x) (x)
#define SHORT_SWAP(x) (x)
#endif
#endif
