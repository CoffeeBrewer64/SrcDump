a12 13
#define NIBBLE_TO_ASCII(v) ((v)<10?('0'+(v)):('a'+(v)-10))
void cidToAppName(BbContentId cid, char *name)
{
    int i,j;
    u32 id=(u32)cid;
    for(j=0,i=28;i>=0;i-=4)
        name[j++]=NIBBLE_TO_ASCII((id>>i)&0xf);
    name[j++]='.';
    name[j++]='a';
    name[j++]='p';
    name[j++]='p';
    name[j++]='\0';
}
d39 1
