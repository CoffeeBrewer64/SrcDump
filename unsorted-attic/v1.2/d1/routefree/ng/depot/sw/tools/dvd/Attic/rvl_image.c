d1 1
a1 1
#ident "$Id: rvl_image.c,v 1.1 2006/02/08 01:46:44 craig Exp $"
d33 2
a34 1
#include <netinet/in.h>         // For ntohl()
d544 1
a544 1
                                (gamePartition_t *) WORD_OFFSET(partitionStart);
d560 7
a566 5
        gameCopy.tmd = (ESTitleMeta *) WORD_OFFSET(tmdStart);
        gameCopy.certificates = (ESRsa2048RsaCert *)
                                  WORD_OFFSET(certArrayStart);
        gameCopy.h3Hashes      = (uint8_t *) WORD_OFFSET(h3HashStart);
        gameCopy.encryptedArea = (uint8_t *) WORD_OFFSET(cryptAreaStart);
d705 1
a705 1
                            (updatePartition_t *) WORD_OFFSET(partitionStart);
d721 3
a723 1
        updateCopy.tmd = (ESTitleMeta *) WORD_OFFSET(tmdStart);
d725 2
a726 2
                                  WORD_OFFSET(certArrayStart);
        updateCopy.image        = (uint8_t *) WORD_OFFSET(imageStart);
d878 2
a879 2
    globalToc.updateTOC = (updateTOC_t *) WORD_OFFSET(updateTocOff);
    globalToc.gameTOC   = (gameTOC_t *) WORD_OFFSET(gameTocOff);
d906 4
a909 9
    updatePartition_t   **memUpdatePartArrayPtr;

    /*
     * Must save updateTOC->updatePartitions, because memory address
     * will be replaced with disk address.
     */
    memUpdatePartArrayPtr = updateToc->updatePartitions;
    updateToc->updatePartitions = (updatePartition_t **)
                                   WORD_OFFSET(updatePartPtrArrayOff);
d915 5
a919 1
    if (fwrite(updateToc, sizeof(updateTOC_t), 1, outFile) != 1) {
d928 1
a928 1
    if (fwrite(memUpdatePartArrayPtr, sizeof(updatePartition_t *),
d936 1
a936 1
    gamePartition_t   **memGamePartArrayPtr;
d938 3
a940 7
    /*
     * Must save gameTOC->updatePartitions, because memory address
     * will be replaced with disk address.
     */
    memGamePartArrayPtr = gameToc->gamePartitions;
    gameToc->gamePartitions = (gamePartition_t **)
                               WORD_OFFSET(gamePartPtrArrayOff);
d946 1
a946 1
    if (fwrite(gameToc, sizeof(gameTOC_t), 1, outFile) != 1) {
d955 1
a955 1
    if (fwrite(memGamePartArrayPtr, sizeof(gamePartition_t *),
d975 6
