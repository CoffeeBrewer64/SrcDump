a16 6
#ifdef __LONG_CALL__
#define ATTR_LONG __attribute__((long_call))
#else
#define ATTR_LONG
#endif

d19 11
a29 11
void *memcpy(void *dst, const void *src, size_t n) ATTR_LONG;
void *memmove(void *dst, const void *src, size_t n) ATTR_LONG;
void *memset(void *s, int c, size_t n) ATTR_LONG;
int memcmp(const void *s1, const void *s2, size_t n) ATTR_LONG;

size_t strnlen(const char *str, size_t n) ATTR_LONG;
char *strncpy(char *dst, const char *src, size_t n) ATTR_LONG;
int strncmp(const char *a, const char *b, size_t n) ATTR_LONG;
char *strchr(const char *s, int c) ATTR_LONG;
char *strrchr(const char *s, int c) ATTR_LONG;
char *strstr (const char *haystack, const char *needle) ATTR_LONG;
d36 20
a55 20
FILE *fopen(const char *filename, const char *mode) ATTR_LONG;
int flen(FILE *) ATTR_LONG;
int fclose(FILE *) ATTR_LONG;
int fread(void *ptr, int size, int nmemb, FILE *fp) ATTR_LONG;
int fwrite(void *ptr, int size, int nmemb, FILE *fp) ATTR_LONG;
int fseek(FILE *fp, long offset, int whence) ATTR_LONG;

int scanf(const char *fmt, ...) ATTR_LONG;
int busPrintf(const char *fmt, ...) ATTR_LONG;
int printf(const char *fmt, ...) ATTR_LONG;
int vprintf(const char *fmt, va_list ap) ATTR_LONG;
int puts(const char *s) ATTR_LONG;
char *gets(char *s) ATTR_LONG;
int putchar(int c) ATTR_LONG;
int getchar(void) ATTR_LONG;

char *tmpnam(char *s) ATTR_LONG;
int unlink(const char *pathname) ATTR_LONG;
int rename(const char *oldpath, const char *newpath) ATTR_LONG;
int time(int *t) ATTR_LONG;
d57 1
a57 1
void exit(int status) ATTR_LONG;
d59 1
a59 1
void get_cmdline(char *buf, unsigned long bufLen) ATTR_LONG;
d61 2
a62 2
void IOS_DebugDumpIobQueue(IOSIobuf *iob) ATTR_LONG;
void IOS_DebugDumpIobChain(IOSIobuf *iob) ATTR_LONG;
d64 1
a64 1
IOSError usleep(u32 usec) ATTR_LONG;
d76 1
a76 1
void busDelay(u32 cycles) ATTR_LONG;
