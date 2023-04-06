d17 6
d25 11
a35 11
void *memcpy(void *dst, const void *src, size_t n);
void *memmove(void *dst, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

size_t strnlen(const char *str, size_t n);
char *strncpy(char *dst, const char *src, size_t n);
int strncmp(const char *a, const char *b, size_t n);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strstr (const char *haystack, const char *needle);
d42 20
a61 20
FILE *fopen(const char *filename, const char *mode);
int flen(FILE *);
int fclose(FILE *);
int fread(void *ptr, int size, int nmemb, FILE *fp);
int fwrite(void *ptr, int size, int nmemb, FILE *fp);
int fseek(FILE *fp, long offset, int whence);

int scanf(const char *fmt, ...);
int busPrintf(const char *fmt, ...);
int printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list ap);
int puts(const char *s);
char *gets(char *s);
int putchar(int c);
int getchar(void);

char *tmpnam(char *s);
int unlink(const char *pathname);
int rename(const char *oldpath, const char *newpath);
int time(int *t);
d63 1
a63 1
void exit(int status);
d65 1
a65 1
void get_cmdline(char *buf, unsigned long bufLen);
d67 2
a68 2
void IOS_DebugDumpIobQueue(IOSIobuf *iob);
void IOS_DebugDumpIobChain(IOSIobuf *iob);
d70 1
a70 1
IOSError usleep(u32 usec);
d82 1
a82 1
void busDelay(u32 cycles);
