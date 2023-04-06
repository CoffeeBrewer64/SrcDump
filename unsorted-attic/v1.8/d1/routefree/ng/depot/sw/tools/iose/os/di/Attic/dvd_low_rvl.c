d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.7 2006/01/20 02:39:01 craig Exp $"
d56 1
a56 1
static bool     h3HashesRead = false, decryptDataValid = false;
d76 2
d93 2
a94 2
    h3HashesRead     = false;
    decryptDataValid = false;
a132 1
    return(0);
d354 1
d372 2
d418 1
a422 1
    static blockCache_t         blockCache = {false};
d429 7
a435 2
        readH3Hashes(h3HashArray, H3_HASH_WORD_OFFSET);
        printf ("Done reading H3 hashes\n");
d443 3
a445 3
        if (blockCache.isValid == false ||
            blockCache.physBlockNum != startPosition.physBlockNum) {
            returnVal = fillBlockCache(&blockCache,
d451 1
a451 1
        if (fillRequestFromCache(&blockCache, &destAddr, &byteLength,
d480 2
a481 2
        if (blockCache.isValid == false ||
            blockCache.physBlockNum != startPosition.physBlockNum) {
d483 2
a484 1
            returnVal = fillBlockCache(&blockCache, startPosition.physBlockNum);
d489 1
a489 1
        requestFilled = fillRequestFromCache(&blockCache, &destAddr,
