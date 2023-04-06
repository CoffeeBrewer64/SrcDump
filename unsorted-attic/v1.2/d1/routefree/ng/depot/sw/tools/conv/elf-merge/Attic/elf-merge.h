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

#ifndef __ELF_MERGE_H__
#define __ELF_MERGE_H__

#include <vector>

using namespace std;

#include <elf.h>

#define ELFABIVERSION_BCC	1	/* BroadOn specific version */

#define BAD_ENTRY	0xffffffff	/* invalid program entry point */

#define ROM_ENTRY	0x08000000	/* ROM entry point */


// one for each input Elf file.  The entire file is read into memory and
// pointers to various sections set up here.
struct ELF_DESC {
    uint8_t* base;
    uint32_t size;

    const char* filename;		
    uint32_t prot_mask;			/* memory protection mask */
    int id;				/* process id */
    int pidMask;			/* process id mask */
    bool isROM;				/* true if the file is a GBA ROM,
					   in which case we fake it as a an
					   ELF file. */

    Elf32_Addr entry;			/* entry point */
    Elf32_Ehdr* ehdr;			/* in-memory Elf header */
    Elf32_Phdr* phdr;			/* in-memory program header */
    uint32_t phdr_size;			/* # of entries in phdr */
    Elf32_Shdr* shdr;			/* in-memory section header */
    uint32_t shdr_size;			/* # of entries in shdr */

    void parse_headers();
    void fake_headers();
    
    void read_elf();
    
    ELF_DESC(const char* filename, int id, int pidMask, uint32_t mask,
	     bool isROM);
    ELF_DESC() { memset(this, 0, sizeof(ELF_DESC)); }
};
typedef vector<ELF_DESC> ELF_v;


// One for each section selected to be included in the output file.
struct SHDR_HANDLE
{
    const ELF_DESC* desc;		/* input file containing this section */
    const Elf32_Shdr* shdr;		/* handle to this section */

    SHDR_HANDLE(const ELF_DESC* d, const Elf32_Shdr* s) : desc(d), shdr(s) {}
    SHDR_HANDLE() : desc(NULL), shdr(NULL) {}
};
typedef vector<SHDR_HANDLE> SHDR_v;


// this vector is for the generated program headers
typedef vector<Elf32_Phdr> PHDR_v;


// this is for the Elf Note Section
// note the variable size array at the end.
struct NOTE_DESC {
    Elf32_Word namesz;
    Elf32_Word descsz;
    Elf32_Word type;
    Elf32_auxv_t auxv[];

    static uint32_t size(int entry_count) {
	return sizeof(NOTE_DESC) + entry_count * 2 * sizeof(Elf32_auxv_t);
    }

    NOTE_DESC(const ELF_v& evec, int pid, int entry_count);
};


extern int
write_elf(const char* filename, const Elf32_Ehdr* ehdr,
	  const PHDR_v& pvec, const NOTE_DESC* desc, int d_size,
	  const SHDR_v& svec);

extern void
merge_shdr(PHDR_v& pvec, SHDR_v& svec, const ELF_v& evec);


extern void
merge_ehdr(const ELF_v& evec, Elf32_Ehdr& ehdr);


extern void
generate_phdr_segment(PHDR_v::iterator phdr, Elf32_Addr vaddr,
		      Elf32_Off offset, Elf32_Word flags);


extern void
generate_note_segment(PHDR_v::iterator phdr, Elf32_Word flags, int desc_size);


#endif /* __ELF_MERGE_H__ */
