#include <ioslibc.h>

int main(void)
{
    puts("putchar:");
    putchar('p');
    putchar('\n');
    putchar('\n');

    puts("puts:");
    puts("simple string\n");

    puts("printf:");
    printf("simple string\n");
    printf("single character: ");
    printf("a");
    printf("\n");
    printf("percent %%\n");
    printf("string \"%s\"\n", "foo");
    printf("char '%c'\n", 'C');
    printf("hex %x %x\n", 0x123abc, 0xabcdef);
    printf("HEX %X %X\n", 0x123abc, 0xabcdef);
    printf("dec %d %d %d\n", 0, 1234, -1234);
    printf("all \"%s\" '%c' 0x%x %d\n", "Rob", 'W', 0x102469, 0x7fffffff);
    return 0;
}
