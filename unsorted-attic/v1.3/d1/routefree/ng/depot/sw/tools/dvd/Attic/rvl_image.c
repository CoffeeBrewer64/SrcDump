d1 1
a1 1
#ident "$Id: rvl_image.c,v 1.2 2006/02/10 02:22:30 craig Exp $"
a32 1
// FIXME - need to use htonl!!!!!
d78 5
a82 2
    {"full",    0, 0, 'f'},        /* Generate entire disk image */
    {"spec",    1, 0, 's'},
d87 2
d94 4
a97 1
inputDisk_t *parseScriptFile(const char* const scriptName);
d114 1
a114 1
DVDDiskInfo     defaultDiskInfo = {"CropDuster", 0, 0};
d116 1
a116 3
static char* options = "fs:";

static char     *scriptFileName = NULL;
d122 66
a187 1
usage(const char* const prog_name)
d189 7
a195 1
    printf ("Usage: %s file_name\n", prog_name);
d197 1
d205 1
a205 1
    inputDisk_t *inputDisk;
d208 11
a218 3
    inputDisk = parseScriptFile("format.script");
    if (inputDisk == NULL) {
        fprintf (stderr, "(%s) Processing of script file failed - exit\n",
d222 4
a225 4
    inputDisk->diskId   = &defaultDiskId;
    inputDisk->diskInfo = &defaultDiskInfo;
    if (generateDiskImage(inputDisk, "output.image") == false) {
        fprintf (stderr, "Generation of output disk image failed\n");
a228 8

}

/* ------------------------------------------------------------------------ */

static void
processOptions(int argc, char* argv[])
{
d579 4
a582 3
bool doHashEncrypt(FILE *outFile, const char* const contentName,
                   const bool hash, const bool encrypt,
                   const off_t h3HashStart, const off_t cryptAreaStart);
a685 1
        bool hash, encrypt;
d687 1
d718 1
a718 1
    printf ("Crypt area starts at: 0x%llx\n", cryptAreaStart);
d720 1
a720 1
                             TitleKey, false) == true) {
a896 3
#define DISK_INFO_OFFSET        0x20
#define GLOBAL_TOC_OFFSET       0x40000

d1065 2
a1066 2
inputDisk_t *
parseScriptFile(const char* const scriptName)
a1073 1
    inputDisk_t                 *returnVal;
d1079 2
a1080 1
        fprintf (stderr, "$0: Can't open file %s for read - exit\n",
d1082 1
d1140 1
a1140 1
                return(NULL);
d1145 1
a1145 1
                return(NULL);
d1151 1
a1151 1
                return(NULL);
d1161 1
a1161 1
                return(NULL);
d1166 1
a1166 1
                return(NULL);
d1172 1
a1172 1
                return(NULL);
d1183 1
a1183 1
                return(NULL);
d1188 1
a1188 1
                return(NULL);
d1194 1
a1194 1
                return(NULL);
d1205 1
a1205 1
                return(NULL);
d1208 2
a1209 1
                fprintf(stderr, "Error: Duplicate certificate lines (line %d)\n",
d1212 1
a1212 1
                return(NULL);
d1219 1
a1219 1
                return(NULL);
d1227 1
a1227 1
            return(NULL);
a1256 6
    returnVal = (inputDisk_t *) malloc(sizeof(inputDisk_t));
    if (returnVal == NULL) {
        fprintf (stderr, "(%s) Memory allocation failed - exit\n", ProgName);
        exit(1);
    }

d1258 2
a1259 2
    returnVal->numGameAreas = numGameAreas;
    returnVal->inputGameAreas =
d1262 1
a1262 1
    if (returnVal->inputGameAreas == NULL) {
d1266 2
a1267 2
    for (int i = 0; i < returnVal->numGameAreas; i++) {
        returnVal->inputGameAreas[i] = tempGamePtrs[i];
d1271 2
a1272 2
    returnVal->numUpdateAreas = numUpdateAreas;
    returnVal->inputUpdateAreas =
d1275 1
a1275 1
    if (returnVal->inputUpdateAreas == NULL) {
d1279 2
a1280 2
    for (int i = 0; i < returnVal->numUpdateAreas; i++) {
        returnVal->inputUpdateAreas[i] = tempUpdatePtrs[i];
d1282 1
a1282 1
    return(returnVal);
