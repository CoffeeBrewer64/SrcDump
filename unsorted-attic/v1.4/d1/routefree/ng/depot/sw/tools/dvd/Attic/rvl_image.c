d1 1
a1 1
#ident "$Id: rvl_image.c,v 1.3 2006/02/10 23:22:42 craig Exp $"
d30 7
d110 1
a110 1
bool getTMD(const char* const TMDFileName, int *tmdSize,
d555 2
a556 1
getTMD(const char* const TMDFileName, int *tmdSize, ESTitleMeta **tmdHandle)
d627 1
a627 1
        fileOffset = ftello64(outFile);
d658 1
a658 1
        if (fseeko64(outFile, partitionStart, SEEK_SET) == -1) {
d668 1
a668 1
        if (fseeko64(outFile, tmdStart, SEEK_SET) == -1) {
d679 1
a679 1
        if (fseeko64(outFile, certArrayStart, SEEK_SET) == -1) {
d718 1
a718 1
    if ((content = fopen64(contentName, "r")) == NULL) {
d721 1
a721 1
    if (fseeko64(outFile, cryptAreaStart, SEEK_SET) == -1) {
d734 2
a735 2
    endOfImage = ftello64(outFile);
    if (fseeko64(outFile, h3HashStart, SEEK_SET) == -1) {
d743 1
a743 1
    if (fseeko64(outFile, endOfImage, SEEK_SET) == -1) {
d788 1
a788 1
        fileOffset = ftello64(outFile);
d818 1
a818 1
        if (fseeko64(outFile, partitionStart, SEEK_SET) == -1) {
d828 1
a828 1
        if (fseeko64(outFile, tmdStart, SEEK_SET) == -1) {
d839 1
a839 1
        if (fseeko64(outFile, certArrayStart, SEEK_SET) == -1) {
d852 1
a852 1
        if (fseeko64(outFile, imageStart, SEEK_SET) == -1) {
d924 1
a924 1
    if ((outFile = fopen64(outputName, "w")) == NULL) {
d964 1
a964 1
    if (fseeko64(outFile, globalTocOff, SEEK_SET) == -1) {
d973 1
a973 1
    if (fseeko64(outFile, updateOff, SEEK_SET) == -1) {
d994 1
a994 1
    if (fseeko64(outFile, updateTocOff, SEEK_SET) == -1) {
d1007 1
a1007 1
    if (fseeko64(outFile, updatePartPtrArrayOff, SEEK_SET) == -1) {
d1025 1
a1025 1
    if (fseeko64(outFile, gameTocOff, SEEK_SET) == -1) {
d1034 1
a1034 1
    if (fseeko64(outFile, gamePartPtrArrayOff, SEEK_SET) == -1) {
