d13 8
d23 6
a28 4
#define SALAUNCH_ERR_FS       -1 /* error opening file on fs */
#define SALAUNCH_ERR_MEM      -2 /* not enough memory (heap) */
#define SALAUNCH_ERR_DATA     -3 /* data error               */
#define SALAUNCH_ERR_EXPIRED  -4 /* ticket expired           */
d34 5
a38 2
int saGameLaunch(BbTicket *ticket,u8 *keyList,u8 *heap,u32 heapSize, u32 binding[4]);
                                 
