#ifndef __BB_SYSAPP_COMMON_H_
#define __BB_SYSAPP_COMMON_H_

#define BB_SYSAPP_PASS  0
#define BB_SYSAPP_FAIL -1

#include <PR/R4300.h>
#include <PR/bbtypes.h>

/* extra stdlib funcs not supplied by libultra */
int strcmp(const char *s,const char *t);
void *memset(char *s,int c,size_t n);
int strncmp(const char *s,const char *t,int n);


#define NIBBLE_TO_ASCII(v) ((v)<10?('0'+(v)):('a'+(v)-10))
void cidToAppName(BbContentId cid, const char *ext, char *name);

#undef PRINTF

#ifdef DEBUG
#define PRINTF          osSyncPrintf
#else
#define	PRINTF(format, args...)
#endif

#define ALIGN_DCACHE_DYN(addr) ((addr)=(void *)((((u32)(addr))+ \
                            DCACHE_LINESIZE-1)&DCACHE_LINEMASK))

#endif

