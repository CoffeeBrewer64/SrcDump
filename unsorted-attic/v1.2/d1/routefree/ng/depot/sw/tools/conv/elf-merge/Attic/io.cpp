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

#ifndef _WIN32
#include <unistd.h>
#else
#include <io.h>
#endif


#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "elf-merge.h"
#include "util.h"

// For linux define O_BINARY. Its defined for cygwin, and necessary
#ifndef O_BINARY
#define O_BINARY 0
#endif

// verify the Elf file header is acceptable 
void
ELF_DESC::parse_headers()
{
    ehdr = (Elf32_Ehdr*) base;

    /* verify all Elf header fields */
    if (*((uint32_t*)ehdr) != *((uint32_t*)ELFMAG) ||
	ehdr->e_ident[EI_CLASS] != ELFCLASS32 ||
	ehdr->e_ident[EI_DATA] != ELFDATA2LSB ||
	ehdr->e_ident[EI_VERSION] != EV_CURRENT ||
	ehdr->e_ident[EI_OSABI] != ELFOSABI_ARM)
	fatal("%s is not a supported Elf file.\n", filename);

    if (ehdr->e_type != ET_EXEC ||
	ehdr->e_machine != EM_ARM ||
	ehdr->e_version != EV_CURRENT)
	fatal("%s is not an ARM executable.\n", filename);
    
    entry = ehdr->e_entry;

    /* the only flags we care is that it is not PIC and not RELEXEC */
    if (ehdr->e_flags & (EF_ARM_RELEXEC | EF_ARM_PIC))
	fatal("%s is either PIC or relocatable.\n", filename);

    if (ehdr->e_ehsize != sizeof(Elf32_Ehdr))
	fatal("%s has inconsisten Elf header size.\n", filename);

    /* we mostly ignore the input program headers, just keep a point here
       for reference. */
    phdr = (Elf32_Phdr*) (base + ehdr->e_phoff);
    phdr_size = ehdr->e_phnum;

    if (ehdr->e_shoff + ehdr->e_shentsize * ehdr->e_shnum >= size)
	fatal("%s has invalid section header table\n.", filename);

    shdr = (Elf32_Shdr*) (base + ehdr->e_shoff);
    shdr_size = ehdr->e_shnum;

    /* briefly scan the sections for out-of-range indices.
       we only care about program data (SHT_PROGBITS). */
    for (uint32_t i = 0; i < shdr_size; ++i) {
	if ((shdr[i].sh_type == SHT_PROGBITS) && (shdr[i].sh_offset + shdr[i].sh_size >= size))
	    fatal("%s: section %d is invalid\n", filename, i);
    }
} /* parse_headers */


/*
 * The input file is a GBA ROM, i.e., not an ELF file.  In this case we
 * fake it as an ELF file with only one section.
 */
void
ELF_DESC::fake_headers()
{
    entry = BAD_ENTRY;
    ehdr = (Elf32_Ehdr*) malloc(sizeof(Elf32_Ehdr));
    shdr = (Elf32_Shdr*) malloc(sizeof(Elf32_Shdr));

    if (ehdr == NULL || shdr == NULL)
	return;

    memset(ehdr, 0, sizeof(Elf32_Ehdr));
    memset(shdr, 0, sizeof(Elf32_Shdr));

    memcpy(ehdr->e_ident, ELFMAG, SELFMAG);
    ehdr->e_ident[EI_CLASS] = ELFCLASS32;
    ehdr->e_ident[EI_DATA] = ELFDATA2LSB;
    ehdr->e_ident[EI_VERSION] = EV_CURRENT;
    ehdr->e_ident[EI_OSABI] = ELFOSABI_ARM;
    ehdr->e_ident[EI_ABIVERSION] = ELFABIVERSION_BCC;
    ehdr->e_type = ET_EXEC;
    ehdr->e_machine = EM_ARM;
    ehdr->e_version = EV_CURRENT;
    ehdr->e_phoff = sizeof(Elf32_Ehdr);
    ehdr->e_ehsize = sizeof(Elf32_Ehdr);
    ehdr->e_phentsize = sizeof(Elf32_Phdr);

    shdr_size = 1;
    shdr->sh_type = SHT_PROGBITS;
    shdr->sh_flags = SHF_ALLOC|SHF_EXECINSTR;
    shdr->sh_addr = ROM_ENTRY;
    shdr->sh_addralign = 1;
    shdr->sh_offset = 0;
    shdr->sh_size = size;
    
} // fake_headers


// auto close the file descriptor
struct File
{
    int fd;
    File(const char* filename, int flags) {
#ifdef _WIN32
	_fmode = _O_BINARY;		// open files in binary mode
#endif
	
	fd = open(filename, flags);
    }

    ~File() {
	if (fd >= 0)
	    close(fd);
    }

    /* read a file into a newly allocated memory buffer.  returns the size of
       the file */
    int read_file(uint8_t** buf) {
	struct stat stat_buf;
	int ret_size;
    
	if ((ret_size = fstat(fd, &stat_buf)) < 0)
	    return ret_size;

	ret_size = stat_buf.st_size;
	
	*buf = (uint8_t*) malloc(ret_size);
	if (*buf == NULL)
	    return -1;
	if (read(fd, *buf, ret_size) != ret_size) {
	    free(*buf);
	    *buf = NULL;
	    return -1;
	}
	return ret_size;
    } // read_file
};


void
ELF_DESC::read_elf()
{
    File file(filename, O_RDONLY | O_BINARY);
    if (file.fd < 0) {
	fatal("Error opening file %s -- %s\n",  filename, strerror(errno));
	return;
    }

    if ((size = file.read_file(&base)) < 0) {
	 fatal("Error reading file %s -- %s\n", filename, strerror(errno));
	 return;
    }

    if (isROM)
	fake_headers();
    else
	parse_headers();
} // ELF_DESC::read_elf


ELF_DESC::ELF_DESC(const char* filename, int id, int pidMask, uint32_t mask,
		   bool isROM)
{
    memset(this, 0, sizeof(ELF_DESC));
    this->filename = filename;
    this->id = id;
    this->pidMask = pidMask;
    prot_mask = mask;
    this->isROM = isROM;
} // ELF_DESC::ELF_DESC


#define WRITE(fd, buf, size)						\
    if (write(fd, buf, size) != size)					\
	fatal("Error writing to %s -- %s.\n", filename, strerror(errno))
	
int
write_elf(const char* filename, const Elf32_Ehdr* ehdr, const PHDR_v& pvec,
	  const NOTE_DESC* desc, int d_size, const SHDR_v& svec)
{
    int fd = open(filename, O_CREAT|O_WRONLY|O_TRUNC|O_BINARY, 0755);

    if (fd < 0) {
	fatal("Error opening output file %s -- %s.\n", filename,
	      strerror(errno));
	return fd;
    }

    WRITE(fd, ehdr, sizeof(Elf32_Ehdr));
    WRITE(fd, &(pvec.front()), (int) (pvec.size() * sizeof(Elf32_Phdr)));
    if (d_size > 0 && desc != NULL)
	WRITE(fd, desc, d_size);

    for (SHDR_v::const_iterator iter = svec.begin(); iter != svec.end(); ++iter) {

	void* buf = iter->desc->base + iter->shdr->sh_offset;
	int size = (iter->shdr->sh_type == SHT_NOBITS) ? 0 : iter->shdr->sh_size;
	if (size > 0)
	    WRITE(fd, buf, size);
    }

    return close(fd);
} /* write_elf */
