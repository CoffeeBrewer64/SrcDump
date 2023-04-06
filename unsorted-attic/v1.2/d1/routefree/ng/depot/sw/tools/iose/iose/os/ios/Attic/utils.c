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
int 
ios_strcmp(const char *l, const char *r)
{
    int i = 0;
    while ( l[i] != '\0' && r[i] != '\0' ) {
        if ( l[i] != r[i] ) return 1;
        ++i;
    }
    if ( r[i] != 0 || l[i] != '\0')
        return 1;
    return 0;
}

unsigned
ios_strncpy(char *dstn, const char *src, unsigned int max_len)
{
    unsigned i = 0;
    while ( i < max_len - 1 && src[i] != '\0') {
        dstn[i] = src[i];
        ++i;
    }
    dstn[i] = '\0';
    return i - 1;
}
