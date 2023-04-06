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

#include <iostypes.h>
#include <hw.h>
#include <ioslibc.h>
#include <apputils.h>
#include <elf.h>

int
m_elfload(char *args, char *d)
{
    char *name;
    u32 rv = 0;
    u32 entry_point;
    if (getNextToken(&name, &args)) {
        rv = elfload(name, &entry_point);
        if ( rv > 0 ) {
            printf("Loaded ELF file: %s [size = %u bytes]\n", name);
            printf("Entry point: 0x%08x\n", entry_point);
        }
        else 
           printf("Failed to load ELF file: %s or size = 0\n", name);
    }
    else {
        printf("Usage: elfload <filename>\n");
    }
    return rv;
}

int
m_osrun(char *args, char *d)
{
    char *name;
    u32 rv = 0;
    u32 entry_point;
    if (getNextToken(&name, &args)) {
        if (elfload(name, &entry_point) > 0)
            (*(void (*)(void))(entry_point))();
        else 
           printf("Failed to load ELF file: %s or size = 0\n", name);
    }
    else 
        printf("Usage: osrun <filename>\n");
    return rv;
}

int 
m_ioprun(char *args, char *d)
{
    char *cmd;
    u32 rv = 0;
    u32 entry_point;
    if (getNextToken(&cmd, &args)) {
       entry_point = atou32(cmd);
       (*(void (*)(void))(entry_point))();
    }
    else 
        printf("Usage: ioprun <entry_point_address>\n");
    return rv;
}
