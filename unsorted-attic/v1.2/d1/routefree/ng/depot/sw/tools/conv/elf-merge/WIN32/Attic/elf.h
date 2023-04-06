#ifdef _WIN32

#ifndef __ELF_H__
#define	__ELF_H__

// This file contains only those ELF defintions needed.  See the ELF
// document for explanation of fields.

typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef long int32_t;
typedef unsigned long uint32_t;


typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Word;
typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Off;

#define EI_NIDENT (16)

struct Elf32_Ehdr
{
    unsigned char e_ident[EI_NIDENT];	/* Magic number and other info */
    Elf32_Half	e_type;			/* Object file type */
    Elf32_Half	e_machine;		/* Architecture */
    Elf32_Word	e_version;		/* Object file version */
    Elf32_Addr	e_entry;		/* Entry point virtual address */
    Elf32_Off	e_phoff;		/* Program header table file offset */
    Elf32_Off	e_shoff;		/* Section header table file offset */
    Elf32_Word	e_flags;		/* Processor-specific flags */
    Elf32_Half	e_ehsize;		/* ELF header size in bytes */
    Elf32_Half	e_phentsize;		/* Program header table entry size */
    Elf32_Half	e_phnum;		/* Program header table entry count */
    Elf32_Half	e_shentsize;		/* Section header table entry size */
    Elf32_Half	e_shnum;		/* Section header table entry count */
    Elf32_Half	e_shstrndx;		/* Section header string table index */
};

#define	ELFMAG		"\177ELF"
#define SELFMAG		4

#define EI_CLASS	4		/* File class byte index */
#define ELFCLASS32	1		/* 32-bit objects */

#define EI_DATA		5		/* Data encoding byte index */
#define ELFDATA2LSB	1		/* 2's complement, little endian */

#define EI_VERSION	6		/* File version byte index */
					/* Value must be EV_CURRENT */

#define EI_OSABI	7		/* OS ABI identification */
#define ELFOSABI_ARM		97	/* ARM */

#define EI_ABIVERSION	8		/* ABI version */

#define ET_EXEC		2		/* Executable file */

#define EM_ARM		40		/* ARM */

#define EV_CURRENT	1		/* Current version */


/* Section header.  */

struct Elf32_Shdr
{
    Elf32_Word	sh_name;		/* Section name (string tbl index) */
    Elf32_Word	sh_type;		/* Section type */
    Elf32_Word	sh_flags;		/* Section flags */
    Elf32_Addr	sh_addr;		/* Section virtual addr at execution */
    Elf32_Off	sh_offset;		/* Section file offset */
    Elf32_Word	sh_size;		/* Section size in bytes */
    Elf32_Word	sh_link;		/* Link to another section */
    Elf32_Word	sh_info;		/* Additional section information */
    Elf32_Word	sh_addralign;		/* Section alignment */
    Elf32_Word	sh_entsize;		/* Entry size if section holds table */
};


/* section type.  */

#define SHT_PROGBITS	  1		/* Program data */
#define SHT_NOBITS	  8		/* Program space with no data (bss) */

/* section flags  */

#define SHF_WRITE	     (1 << 0)	/* Writable */
#define SHF_ALLOC	     (1 << 1)	/* Occupies memory during execution */
#define SHF_EXECINSTR	     (1 << 2)	/* Executable */


/* Program segment header.  */

struct Elf32_Phdr
{
    Elf32_Word	p_type;			/* Segment type */
    Elf32_Off	p_offset;		/* Segment file offset */
    Elf32_Addr	p_vaddr;		/* Segment virtual address */
    Elf32_Addr	p_paddr;		/* Segment physical address */
    Elf32_Word	p_filesz;		/* Segment size in file */
    Elf32_Word	p_memsz;		/* Segment size in memory */
    Elf32_Word	p_flags;		/* Segment flags */
    Elf32_Word	p_align;		/* Segment alignment */
};


/* segment type */

#define PT_LOAD		1		/* Loadable program segment */
#define PT_NOTE		4		/* Auxiliary information */
#define PT_PHDR		6		/* Entry for header table itself */

/* segment flags  */

#define PF_X		(1 << 0)	/* Segment is executable */
#define PF_W		(1 << 1)	/* Segment is writable */
#define PF_R		(1 << 2)	/* Segment is readable */

#define NT_AUXV		6		/* auxv array */


/* Auxiliary vector.  */

typedef struct
{
  int a_type;			/* Entry type */
  union
    {
      long int a_val;		/* Integer value */
      void *a_ptr;		/* Pointer value */
      void (*a_fcn) (void);	/* Function pointer value */
    } a_un;
} Elf32_auxv_t;


/* entry type */

#define AT_ENTRY	9		/* Entry point of program */
#define AT_UID		11		/* Real uid */

/* ARM specific declarations */

/* Processor specific flags for the ELF header e_flags field.  */
#define EF_ARM_RELEXEC     0x01
#define EF_ARM_PIC         0x20

#endif	/* __ELF_H__ */

#endif /* _WIN32 */
