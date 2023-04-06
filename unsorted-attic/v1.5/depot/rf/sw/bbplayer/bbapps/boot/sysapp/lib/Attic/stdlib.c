#include <PR/os.h>
#include "common.h"

/*
 * Extra stdlib functions not supplied by libultra
 */

/* util string compare function. */
int strcmp(const char *s,const char *t)
{
    for(;*s==*t;s++,t++)
        if(*s=='\0')
            return 0;
    return *s - *t;
}

#if 0
int strlen(const char *s)
{
    int n;
    for(n=0;*s!='\0';s++)
        n++;
    return n;
}
#endif

void *memset(char *s,int c,size_t n)
{
    int i;
    for(i=0;i<n;i++)
        s[i]=(unsigned char)c;

    return s;
}

int strncmp(const char *s,const char *t,int n)
{
    int i;
    for(i=0; (*s==*t) && (i<n); s++, t++, i++){
        if(*s=='\0' && *t=='\0')
            return 0;
        if(*s=='\0' || *t=='\0')
            break;
    }
    if(i==n)
        return 0;
    return *s - *t;    
} 

/*
 * Misc functions for internal consumption.
 */
void cidToAppName(BbContentId cid, const char *ext, char *name)
{
    int i,j;
    u32 id=(u32)cid;
    for(j=0,i=28;i>=0;i-=4)
        name[j++]=NIBBLE_TO_ASCII((id>>i)&0xf);
    name[j++]='.';
    name[j++]=ext[0];
    name[j++]=ext[1];
    name[j++]=ext[2];
    name[j++]='\0';
}
