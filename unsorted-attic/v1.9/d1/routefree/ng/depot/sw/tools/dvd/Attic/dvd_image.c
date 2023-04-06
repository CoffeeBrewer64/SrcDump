d1 1
a1 1
#ident "$Id: dvd_image.c,v 1.8 2006/01/20 02:34:42 craig Exp $"
a52 4
bool computeSuperBlock(FILE *inFile, FILE *outFile, uint8_t* h3Ptr,
                       uint8_t* const titleKey, const bool encrypt);


d99 1
a99 1
                             TitleKey, true) == true) {
