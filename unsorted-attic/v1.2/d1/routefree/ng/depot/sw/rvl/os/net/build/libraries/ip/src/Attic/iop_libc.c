a83 26
int stricmp(const char *s1, const char *s2)
{
    char c1;
    char c2;

    for (;;)
    {
        c1 = (char) (tolower)(*s1++);
        c2 = (char) (tolower)(*s2++);
        if (c1 < c2)
        {
            return -1;
        }
        if (c1 > c2)
        {
            return 1;
        }
        if (c1 == '\0')
        {
            return 0;
        }
    }
    
    return 0;
}

