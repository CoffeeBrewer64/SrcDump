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

#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "elf-merge.h"
#include "util.h"

struct SHDR_COMP
{
    bool operator()(const SHDR_HANDLE&x, const SHDR_HANDLE& y) {
	return (x.shdr->sh_addr < y.shdr->sh_addr);
    }
};

static void
select_sections(SHDR_v& v, const ELF_v& evec)
{
    /* first we pull out only the program bits (text and data) section */
    for (ELF_v::const_iterator iter = evec.begin(); iter != evec.end(); ++iter) {

	for (uint32_t j = 0; j < iter->shdr_size; ++j) {
	    const Elf32_Shdr& shdr = iter->shdr[j];

	    /* not part of the memory image */
	    if ((shdr.sh_flags & SHF_ALLOC) == 0)
		continue;

	    /* zero size */
	    if (shdr.sh_size == 0)
		continue;

	    /* invalid alignment */
	    if (shdr.sh_addr & (shdr.sh_addralign - 1))
		fatal("Section %d of %s has inconsistent alignment.\n",
		      j, iter->filename);

	    v.push_back(SHDR_HANDLE(&(*iter), &shdr));
	}
    }

    /* second, sort them according to virtual addresses */
    sort(v.begin(), v.end(), SHDR_COMP());

    /* last, a quick pass to make sure there is no overlapping */
    SHDR_v::const_iterator prev = v.begin();
    SHDR_v::const_iterator iter = prev + 1;

    while (iter != v.end()) {
	if (prev->shdr->sh_addr + prev->shdr->sh_size > iter->shdr->sh_addr)
	    fatal("Overlapping sections between %s [0x%08x - 0x%08x)"
		  " and %s [0x%08x - 0x%08x).\n",
		  prev->desc->filename, 
		  prev->shdr->sh_addr,
		  prev->shdr->sh_addr + prev->shdr->sh_size,
		  iter->desc->filename, iter->shdr->sh_addr,
		  iter->shdr->sh_addr + iter->shdr->sh_size);
	++iter;
	++prev;
    }
} /* select_sections */



static inline Elf32_Word
segment_flags(const Elf32_Shdr& shdr, uint32_t mask)
{
    Elf32_Word w =  PF_R;
    if (shdr.sh_flags & SHF_EXECINSTR)
	w |= PF_X;
    if (shdr.sh_flags & SHF_WRITE)
	w |= PF_W;
    return w | mask;

} /* segment_flags */
     

static bool
section_merged(Elf32_Phdr& phdr, const SHDR_HANDLE& handle)
{
    if (phdr.p_type != PT_LOAD)
	return false;

    const Elf32_Shdr& shdr = *(handle.shdr);

    /* virtual address must be contiguous */
    if (shdr.sh_addr != phdr.p_vaddr + phdr.p_memsz)
	return false;

    /* cannot leave holes in the file */
    if ((shdr.sh_type != SHT_NOBITS) && (phdr.p_filesz != phdr.p_memsz))
	return false;

    /* check protection bits */
    Elf32_Word  p_flags = segment_flags(shdr, handle.desc->prot_mask);
    if (p_flags != phdr.p_flags)
	return false;

    /* check alignment */
    if (shdr.sh_addralign > phdr.p_align) {
	if (phdr.p_vaddr & (shdr.sh_addralign - 1))
	    return false;
	else
	    phdr.p_align = shdr.sh_addralign;
    }

    /* finally, we can merge */
    if (shdr.sh_type == SHT_NOBITS)
	phdr.p_memsz += shdr.sh_size;
    else {
	phdr.p_filesz += shdr.sh_size;
	phdr.p_memsz += shdr.sh_size;
    }

    return true;
    
} /* section_merged */


/* generate program segments based on the sections.  merge the sections
   into a segment if possible. */
static void
generate_segments(PHDR_v& pvec, const SHDR_v& svec)
{
    PHDR_v::iterator phdr = pvec.end();
    Elf32_Off offset = 0;

    for (SHDR_v::const_iterator iter = svec.begin(); iter != svec.end(); ++iter) {

	if (phdr == pvec.end() || ! section_merged(*phdr, *iter)) {
	    const Elf32_Shdr& shdr = *(iter->shdr);
	    
	    phdr = pvec.insert(pvec.end(), Elf32_Phdr());
	    phdr->p_type = PT_LOAD;
	    phdr->p_offset = offset;
	    phdr->p_vaddr = shdr.sh_addr;
	    phdr->p_paddr = shdr.sh_addr;
	    phdr->p_filesz = (shdr.sh_type == SHT_NOBITS) ? 0 : shdr.sh_size;
	    phdr->p_memsz = shdr.sh_size;
	    phdr->p_flags = segment_flags(shdr, iter->desc->prot_mask);
	    phdr->p_align = shdr.sh_addralign;
	}

	offset = phdr->p_offset + phdr->p_filesz;
    }

} /* generate_segments */


void
merge_shdr(PHDR_v& pvec, SHDR_v& svec, const ELF_v& evec)
{
    select_sections(svec, evec);
    generate_segments(pvec, svec);
} /*_merge_shdr */


void
merge_ehdr(const ELF_v& evec, Elf32_Ehdr& ehdr)
{
    // this part should be the same for all Elf headers
    memset(&ehdr, 0, sizeof(Elf32_Ehdr));
    memcpy(ehdr.e_ident, ELFMAG, SELFMAG);
    ehdr.e_ident[EI_CLASS] = ELFCLASS32;
    ehdr.e_ident[EI_DATA] = ELFDATA2LSB;
    ehdr.e_ident[EI_VERSION] = EV_CURRENT;
    ehdr.e_ident[EI_OSABI] = ELFOSABI_ARM;
    ehdr.e_ident[EI_ABIVERSION] = ELFABIVERSION_BCC;
    ehdr.e_type = ET_EXEC;
    ehdr.e_machine = EM_ARM;
    ehdr.e_version = EV_CURRENT;
    ehdr.e_phoff = sizeof(Elf32_Ehdr);
    ehdr.e_ehsize = sizeof(Elf32_Ehdr);
    ehdr.e_phentsize = sizeof(Elf32_Phdr);

    // the e_flags is the only field needs to be merged from all Elf headers
    for (ELF_v::const_iterator iter = evec.begin(); iter != evec.end(); ++iter)
	ehdr.e_flags |= iter->ehdr->e_flags;
    
} /* merge_ehdr */


void
generate_phdr_segment(PHDR_v::iterator phdr, Elf32_Addr vaddr,
		      Elf32_Off offset, Elf32_Word flags)
{
    phdr->p_type = PT_PHDR;
    phdr->p_offset = offset;
    phdr->p_paddr = phdr->p_vaddr = vaddr;
    phdr->p_memsz = phdr->p_filesz = 0; /* to be filled in later */
    phdr->p_flags = flags;
    phdr->p_align = sizeof(Elf32_Word);

} /* generate_phdr_segment */


NOTE_DESC::NOTE_DESC(const ELF_v& evec, int pid, int entry_count)
{
    memset(this, 0, size(entry_count));
    descsz = entry_count * 2 * sizeof(Elf32_auxv_t);
    type = NT_AUXV;

    int av_idx = 0;
    for (ELF_v::const_iterator iter = evec.begin(); iter != evec.end(); ++iter) {
	
	if (iter->id != pid && iter->entry != BAD_ENTRY) {
	    auxv[av_idx].a_type = AT_UID;
	    auxv[av_idx++].a_un.a_val = (iter->pidMask << 16) | iter->id;
	    auxv[av_idx].a_type = AT_ENTRY;
	    auxv[av_idx++].a_un.a_ptr = (void*) iter->entry;
	}
    }

    if (av_idx != entry_count * 2)
	fatal("Internal error:  aux vector and entry point count mismatched.\n");
} // NOTE_DESC::NOTE_DESC


void
generate_note_segment(PHDR_v::iterator phdr, Elf32_Word flags, int desc_size)
{
    phdr->p_type = PT_NOTE;

    /* the offset and addresses depend on the actual size of the program
       header section, and need to be filled in later */
    phdr->p_offset = 0;
    phdr->p_vaddr = phdr->p_paddr = 0;

    phdr->p_memsz = phdr->p_filesz = desc_size;
    phdr->p_flags = flags;
    phdr->p_align = sizeof(Elf32_Word);

} /* generate_note_segment */
