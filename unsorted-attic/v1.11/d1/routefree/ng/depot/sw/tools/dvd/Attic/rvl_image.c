d1 1
a1 1
#ident "$Id: rvl_image.c,v 1.10 2006/03/21 21:11:39 craig Exp $"
d20 1
a57 1
#include "key.h"
d63 2
a92 1
    {"hash",            0, 0, 'z'},     /* Hash disk image */
d96 3
a98 1
    {"verbose",         0, 0, 'v'},     /* Input script file */             
d103 1
a103 1
static char* options = "efho:s:z";
d116 1
a148 1
        " -z, --hash            - hash disk image\n"
d150 1
d152 3
a154 2
        " -o, --out <file>      - output image name [default: output.image]\n"
        " -v, --verbose         - print out messages as image is created\n");
d158 6
d165 2
a166 1
processOptions(int argc, char* argv[], inputDisk_t* const inputDisk)
d168 5
d198 4
d205 3
a207 3

        case 'o':
            outputFileName = optarg;
d230 20
d256 1
d265 1
a265 1
    processOptions(argc, argv, &inputDisk);
d275 1
a275 1
    if (generateDiskImage(&inputDisk, outputFileName) == false) {
d304 1
a304 1
        printf ("(truncateImage) rename failed - exit\n");
d699 3
a701 1
              const off_t h3HashStart, const off_t cryptAreaStart);
d715 3
a717 1
writeGames(inputDisk_t* const inputDisk, FILE *outFile)
d734 2
a785 10
        /* Write out TMD structure */
        if (fseeko(outFile, tmdStart, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(gamePart->tmd, 1, gamePart->tmdSize, outFile)
                   != gamePart->tmdSize) {
            fprintf(stderr, "Game partition TMD write failed\n");
            return(NULL);
        }
d808 3
a810 3
        bool            encrypt, hash;
        encrypt    = inputDisk->diskInfo->noEncryption == 0 ? true : false;
        hash       = inputDisk->diskInfo->noHash       == 0 ? true : false;
d813 18
a830 2
                          hash, encrypt, h3HashStart,
                          cryptAreaStart) == false) {
d833 1
d839 13
d855 3
a857 1
              const off_t h3HashStart, const off_t cryptAreaStart)
d862 1
d879 1
a879 1
                             TitleKey, encrypt, hash) == true) {
d895 3
d901 4
d1080 1
d1158 1
a1158 1
     * because in writing the game partitions we determine where
d1161 1
a1161 1
    gameToc = writeGames(inputDisk, outFile);
d1735 1
a1735 1
        fprintf (stderr, "Can't write %u 0 bytes to file - exit\n", length);
