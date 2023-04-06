/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

/*---------------------------------------------------------------------------*
 * 
 * Libc functions used in the stack
 * 
 *---------------------------------------------------------------------------*/

#include <ios.h>
#include <ioslibc.h>

#include <dolphin/os.h>

int isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return 1;
    else
        return 0;
}

int isxdigit(int c)
{
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
        return 1;
    else
        return 0;
}

int islower(int c)
{
    if (c >= 'a' && c <= 'z')
        return 1;
    else
        return 0;
}

int isalnum(int c)
{
    if ((c >= '0' && c <= '9') || (c >='a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    else
        return 0;
}

u32 atoi(const char *s)
{
	int i, n;
	
	n = 0;
	
	for(i=0; s[i]>'0' && s[i]< '9'; ++i)
		n = 10 * n + ( s[i] - '0');
	
	return n;
}

u32 strlen(const char *s)
{
	char *p = (char *) s;

	while (*p != '\0')
		p++;

	return (p - s);
}

static int tolower(int c)
{
    if ((c >= 'A') && (c <= 'Z'))
        c += ('a' - 'A');
    return c;
}

int strnicmp(const char *s1, const char *s2, int len)
{
    char c1;
    char c2;
    int i = 0;

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
        if ((c1 == '\0') || (++i == len))
        {
            return 0;
        }
    }
    
    return 0;
}
