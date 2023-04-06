d41 1
a41 1
#define FLUSH_OUTGOING(ptr, len)   ptr = ptr;
d43 2
a44 1
#define INVAL_INCOMING(ptr, len)   ptr = ptr;
d126 2
d132 2
d143 4
a146 2
                FLUSH_OUTGOING(v->vector[v->readCount+i].base, 
                               v->vector[v->readCount+i].length);
d148 4
d175 1
a175 1
    /* Check that v is in SDRAM */
d194 1
d205 1
d211 1
d223 4
d236 5
d243 1
d246 1
d253 1
