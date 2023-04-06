d1 1
a1 1
#ident "$Id: dvd_image.c,v 1.6 2006/01/10 20:33:37 craig Exp $"
d97 1
a97 1
    if ((inFile = fopen(argv[1], "r")) == NULL) {
d131 1
a131 1
    h3Bytes = h3BufPtr - h3Buf;
a231 1
    readPtr = 
d333 3
a335 1
        assert(ftello(outFile) - blockStartPos == DVD_BLOCK_SIZE);
