#ifndef __NONULTRA_MSG_HDR__
#define __NONULTRA_MSG_HDR__

/*
 * Simple log mechanism for non-libultra test apps.
 * The define, LOG_MEM, controls if printing is for
 * simulation or to dram. (if defined, goes to dram,
 * the address defined in message.c)
 */

#include <PR/bcp.h>

void message(const char* s);
void output_int32_hex(u32 val);

#endif
