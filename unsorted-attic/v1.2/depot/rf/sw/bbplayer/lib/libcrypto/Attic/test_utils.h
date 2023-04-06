typedef unsigned char u8;
typedef unsigned long u32;
int getFileSize(char *filename);
int getFileSizeAscii(char *filename);
void readAsciiBinaryData(char *filename,u8 *data,int bytes);
void writeAsciiBinaryData(char *filename,u8 *data,int bytes);
