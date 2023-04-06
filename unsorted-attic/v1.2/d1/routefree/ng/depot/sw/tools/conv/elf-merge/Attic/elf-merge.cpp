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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>

#include <new>

using namespace std;

#include "elf-merge.h"
#include "util.h"

enum ADDRESS_SPACE_ID {
    SK_SID = 0,         /* secure kernel */
    EM_SID,             /* eTicket Manager */
    FS_SID,             /* file system */
    USB_SID,            /* usb */
    AUD_SID,            /* audio */
    VIEWER_SID,         /* viewer */
    NC_SID,             /* NC application */
    GBA_SID,            /* GBA application */
    VN_SID,             /* virtual network */
    DEVMON_SID,         /* dev monitor */
    SHARED_SID,         /* Shared data */
};


/*
 * IOS_LaunchElf assumes that GBA segments have a protection mask of
 * 0x7f. No other processes should use this mask
 */
uint32_t prot_mask[] = {
    0x00000000,				/* kernel space */
    0x00100000,				/* eTicket manager */
    0x00200000,				/* file system */
    0x00400000,				/* usb */
    0x00800000,				/* audio */
    0x01000000,				/* viewer */
    0x03f00000,				/* NC app */
    0x07f00000,  			/* GBA app */
    0x00400000,				/* virtual network */
    0x00100000,				/* dev monitor */
    0x01f00006,				/* shared data */
};

int32_t process_id[] = {
    0,					// kernel
    1,					// eTicket Manager
    2,					// file system
    3,					// usb
    4,					// audio
    5,					// viewer
    6,					// NC app
    -1,					// GBA app not an NC process
    8,					// virtual network
    9,					// dev monitor
    -1,					// Shared data not a process
};

int32_t process_mask[] = {
    0x0,					// kernel
    0x1,					// eTicket Manager
    0x2,					// file system
    0x4,					// usb
    0x8,					// audio
    0x10,					// viewer
    0x20,					// NC app
    0,						// GBA app not an NC process
    0x4,					// virtual network
    0x1,					// dev monitor
    0,						// Shared data not a process
};


#if !defined(_WIN32) && !defined(__CYGWIN__)
static struct option long_options[] = {
    {"sk", 1, 0, 'k'},			/* SK binary */
    {"sd_addr", 1, 0, 's'},		/* Shared Data address */
    {"sd_size", 1, 0, 'z'},		/* Shared Data size */
    {"file_system", 1, 0, 'f'},	/* file system */
    {"eT_mgr", 1, 0, 'e'},		/* eTicket manager */
    {"vn", 1, 0, 'v'},			/* VN */
    {"usb", 1, 0, 'u'},			/* USB */
    {"audio", 1, 0, 'a'},		/* Audio */
    {"viewer", 1, 0, 'l'},		/* Viewer */
    {"devmon", 1, 0, 'd'},		/* devmon */
    {"nc", 1, 0, 'n'},			/* NC binary */
    {"gba", 1, 0, 'g'},			/* GBA binary */
    {"GBA", 1, 0, 'G'},			/* GBA ROM */
    {"outfile", 1, 0, 'o'},		/* output file */
    {"help", 0, 0, 'h'},		/* print usage */
    {0, 0, 0, 0}
};
#endif // _WIN32

static char* options = "d:k:s:z:f:e:v:a:l:u:n:g:G:o:h";

static const char* outfile = NULL;
#define SD_ALIGNMENT 16384		/* SDRAM page size is 16KBytes */
static Elf32_Addr sd_addr = 0;
static Elf32_Word sd_size = 0;
static int load_phdr = 0;		/* true if program header needs to
					   be part of the image.  */
static Elf32_Addr entry = BAD_ENTRY;	/* "main" entry point */
static int pid = -1;			/* "main" process id */
static int entry_count;			/* number of entry points */


static void
process_infile(ELF_v& e, int id, const char* filename, bool isROM = false)
{
    ELF_v::iterator desc =
	e.insert(e.end(), ELF_DESC(filename, process_id[id], process_mask[id], prot_mask[id], isROM));
    desc->read_elf();

    if (id == GBA_SID)
	desc->entry = BAD_ENTRY;

    if (desc->entry != BAD_ENTRY && process_id[id] != -1) {
	++entry_count;
	if (process_id[id] < pid || pid == -1) {
	    entry = desc->entry;
	    pid = process_id[id];
	}
    }
} /* process_infile */


static void
usage(const char* progname)
{
    fprintf(stderr, "usage: %s\n", progname);
    fprintf(stderr,
            " -k, --sk filename      - SK executable file.\n"
            " -s, --sd_addr <addr>   - Shared Data Segment address.\n"
            " -z, --sd_size <size>   - Shared Data Segement size in bytes.\n"
            " -f, --file_system filename - File System executable file.\n"
            " -e, --eT_mgr filename  - eTicket Manager executable file.\n"
            " -v, --vn filename      - Virtual Network executable file.\n"
            " -u, --usb filename   - USB executable file.\n"
            " -a, --audio filename   - Audio executable file.\n"
            " -n, --nc filename      - NC executable file.\n"
            " -g, --gba filename     - GBA executable file.\n"
            " -G, --GBA filename     - GBA ROM file.\n"
            " -l, --viewer filename     - Viewer executable file.\n"
            " -d, --devmon filename     - Devmon executable file.\n"
            " -o, --outfile filename - output file.\n"
            " -h, --help             - print this message.\n");
    exit(1);
} /* usage */


static void
process_options(int argc, char* argv[], ELF_v& evec)
{
    while (1) {
#if defined(_WIN32) || defined(__CYGWIN__)
	int ch = getopt(argc, argv, options);
#else
	int ch = getopt_long_only(argc, argv, options, long_options, 0);
#endif

	if (ch == -1)
	    break;

	switch (ch) {
	case 'k':
	    load_phdr = 1;
	    process_infile(evec, SK_SID, optarg);
	    break;

	case 's':
	    sd_addr = strtoul(optarg, NULL, 16);
	    if (sd_addr & (SD_ALIGNMENT - 1)) {
		fprintf(stderr, "Shared Data address must be 0x%x aligned.\n", SD_ALIGNMENT);
		usage(argv[0]);
	    }
	    break;

	case 'z':
	    sd_size = strtoul(optarg, NULL, 16);
	    break;

	case 'f':
	    process_infile(evec, FS_SID, optarg);
	    break;

	case 'e':
	    process_infile(evec, EM_SID, optarg);
	    break;

	case 'v':
	    process_infile(evec, VN_SID, optarg);
	    break;

	case 'u':
	    process_infile(evec, USB_SID, optarg);
	    break;

	case 'a':
	    process_infile(evec, AUD_SID, optarg);
	    break;

	case 'l':
	    process_infile(evec, VIEWER_SID, optarg);
	    break;

	case 'd':
	    process_infile(evec, DEVMON_SID, optarg);
	    break;

	case 'n':
	    process_infile(evec, NC_SID, optarg);
	    break;

	case 'g':
	    process_infile(evec, GBA_SID, optarg);
	    break;

	case 'G':
	    process_infile(evec, GBA_SID, optarg, true);
	    break;
		
	case 'o':
	    outfile = optarg;
	    break;

	default:
	    usage(argv[0]);
	    break;
	}
    }

    if (outfile == NULL) {
	fprintf(stderr, "Output file undefined.\n");
	usage(argv[0]);
    }

    if (load_phdr && sd_addr == 0) {
	fprintf(stderr, "Shared Data Segment address not specified.\n");
	usage(argv[0]);
    }
} /* process_options */


static void
fixup_phdr(PHDR_v& pvec, Elf32_Off offset)
{
    PHDR_v::iterator iter = pvec.begin();
    int phdr_size = pvec.size() * sizeof(Elf32_Phdr);

    offset += phdr_size;
    if (load_phdr) {
	Elf32_Word sd_filesz = phdr_size;
	
	if (iter->p_type != PT_PHDR)
	    fatal("Internal error -- missing PT_PHDR program header entry.\n");
	iter->p_memsz = iter->p_filesz = phdr_size;

	++iter;
	
	if (entry_count > 0) {
	    /* must be PT_NOTE segment */
	    if (iter->p_type != PT_NOTE)
		fatal("Internal error -- missing PT_NOTE program header entry.\n");
	    iter->p_offset = offset;
	    iter->p_vaddr = iter->p_paddr = pvec.front().p_vaddr + phdr_size;
	    offset += iter->p_filesz;
	    sd_filesz += iter->p_filesz;

	    ++iter;
	}

	if (iter->p_type != PT_LOAD &&
	    iter->p_offset != pvec.front().p_offset)
	    fatal("Internal error -- missing PT_LOAD program header entry for Shared Data segment.\n");
	iter->p_filesz = sd_filesz;
	if (iter->p_memsz < sd_filesz)
	    iter->p_memsz = sd_size = sd_filesz;
	++iter;
    }

    while (iter != pvec.end()) {
	iter->p_offset += offset;

	// also check for overlapping with the shared data segment
	if (! (sd_addr >= (iter->p_vaddr + iter->p_memsz) ||
	       (sd_addr + sd_size) <= iter->p_vaddr))
	    fatal("Shared Data segment overlaps with program segment on "
		  "(0x%08x - 0x%08x).\n", iter->p_vaddr, (iter->p_vaddr + iter->p_memsz));
	
	++iter;
    }
} /* fixup_phdr */

int
main(int argc, char* argv[])
{
    ELF_v evec;
    PHDR_v pvec;
    SHDR_v svec;
    Elf32_Ehdr ehdr;
    NOTE_DESC* desc = NULL;
    int desc_size = 0;

    process_options(argc, argv, evec);

    merge_ehdr(evec, ehdr);
    ehdr.e_entry = entry;

    /* we don't need an aux vector for the "main" entry point, so we
       exclude that from the entry point count. */
    --entry_count;			
    if (load_phdr) {
	/* PT_PHDR segment */
	generate_phdr_segment(pvec.insert(pvec.end(), Elf32_Phdr()),
			      sd_addr, ehdr.e_phoff, prot_mask[SHARED_SID]);

	/* generate PT_NOTE segment */
	if (entry_count > 0) {
	    desc_size = NOTE_DESC::size(entry_count);
	    desc = new(malloc(desc_size)) NOTE_DESC(evec, pid, entry_count);
	    
	    generate_note_segment(pvec.insert(pvec.end(), Elf32_Phdr()),
				  prot_mask[SHARED_SID], desc_size);
	}

	/* generate the PT_LOAD segment for the Shared Data */
	PHDR_v::iterator phdr = pvec.insert(pvec.end(), Elf32_Phdr());
	phdr->p_type = PT_LOAD;
	phdr->p_offset = ehdr.e_phoff;
	phdr->p_vaddr = phdr->p_paddr = sd_addr;
	phdr->p_filesz = 0;			/* to be filled in later */
	phdr->p_memsz = sd_size;
	phdr->p_flags = prot_mask[SHARED_SID];
	phdr->p_align = SD_ALIGNMENT;
    }

    merge_shdr(pvec, svec, evec);

    /* now we know the exact size of the program header section.  Fill in
       all values that depend on it. */
    ehdr.e_phnum = pvec.size();
    fixup_phdr(pvec, ehdr.e_phoff);
    
    if (write_elf(outfile, &ehdr, pvec, desc, desc_size, svec) < 0)
	fatal("Error writing to %s -- %s.\n", outfile, strerror(errno));
    return 0;
} /* main */
