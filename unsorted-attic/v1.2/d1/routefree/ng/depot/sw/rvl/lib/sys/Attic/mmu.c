/*
 * $Id: mmu.c,v 1.1 2006/02/04 03:07:54 gzhang Exp $
 */

/*
 * Helper routines for MMU setup.
 */

#include "mmu.h"
#include "trace.h"


/*
 * Write the first level translation table.  Writes a section
 * descriptor to each of 4096 entries with increasing base address.
 *
 * entry_addr:   the start address of the translation table.
 * start_offset: where to begin writing in the translation table.
 *
 * Format of the translation table entry:
 *
 * Section case:
 *
 * 31                     20 19          12 1110 9 8      5 4 3 2 1 0
 * +------------------------+--------------+----+-+--------+-+---+-+-+
 * |    Base Address        |              | AP |0| Domain |1|C|B|1|0|
 * +------------------------+--------------+----+-+--------+-+---+-+-+
 */
void
setupTransTable (unsigned int *entry_addr, int start_offset,
                 unsigned int prototype)
{
    unsigned int ttb_entry;
    int entry;

    entry_addr += start_offset;

    for (entry = start_offset; entry < TRANS_TABLE_SIZE; entry++) {
        ttb_entry = prototype | (entry << 20);
	*entry_addr = ttb_entry;
	entry_addr++;
    }

    return;
}

/*
 * Write the first level translation table.  Writes a section
 * descriptor to one of 4096 entries.
 * VirtualAddress == PhysicalAddress mapping
 *
 * entry_addr:   the start address of the translation table.
 * offset:       where to write in the translation table.
 * prototype:    descriptor with no address bits.
 */
void
setupSectionEntry (unsigned int *entry_addr, int offset,
                     int prototype)
{
    unsigned int ttb_entry;

    entry_addr += offset;

    ttb_entry = prototype | (offset << 20);
    *entry_addr = ttb_entry;

    return;
}

/*
 * Write the first level translation table.  Writes a section
 * descriptor  (Physical Address and prototype) to one of 4096 entries 
 * according to the Virtual Address.
 * Accomplishes MMU VirtualAddress to PhysicalAddress mapping
 *
 * entry_addr:   the start address of the translation table.
 * vrt_addr:     virtual address
 * phy_addr:      physical address
 * prototype:    descriptor with no address bits.
 */
void
setupSectionVa2Pa (unsigned int *entry_addr, 
                   unsigned int vrt_addr, 
                   unsigned int phy_addr,
                   unsigned int prototype)
{
    unsigned int ttb_entry,
                 offset = vrt_addr >> 20;

    entry_addr += offset;

    ttb_entry = prototype | ((unsigned int)phy_addr & SECTION_ADDR_MASK);
    *entry_addr = ttb_entry;

    return;
}

/* eof */
