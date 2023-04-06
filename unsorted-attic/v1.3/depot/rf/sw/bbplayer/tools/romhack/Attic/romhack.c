#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <getopt.h>

#include "romhack.h"

#define ERRATA_MAX_SIZE 16384
#define ERRATA_START_ADDR 0x80700000
u8 *errata_start, *errata_end;

#include "sigs/os20d_sgi.sigs"
#include "sigs/os20e_sgi.sigs"
#include "sigs/os20f_sgi.sigs"
#include "sigs/os20g_sgi.sigs"
#include "sigs/os20h_sgi.sigs"
#include "sigs/os20i_sgi.sigs"
#include "sigs/os20j_sgi.sigs"
#include "sigs/os20k_sgi.sigs"
#include "sigs/os20l_sgi.sigs"

#include "sigs/os20h_pc.sigs"
#include "sigs/os20i_pc.sigs"
#include "sigs/os20j_pc.sigs"
#include "sigs/os20k_pc.sigs"
#include "sigs/os20l_pc.sigs"

#include "sigs/bb_ultra_rom.sigs"

#if 1
struct {
    char version;
    sig_t *sgi_sigs;
    sig_t *pc_sigs;
    sym_t **sgi_syms;
    sym_t **pc_syms;
} libraries[] = {
    'D', os20d_sgi_sigs, NULL, os20d_sgi_syms, NULL,
    'E', os20e_sgi_sigs, NULL, os20e_sgi_syms, NULL,
    'F', os20f_sgi_sigs, NULL, os20f_sgi_syms, NULL,
    'G', os20g_sgi_sigs, NULL, os20g_sgi_syms, NULL,
    'H', os20h_sgi_sigs, os20h_pc_sigs, os20h_sgi_syms, os20h_pc_syms,
    'I', os20i_sgi_sigs, os20i_pc_sigs, os20i_sgi_syms, os20i_pc_syms,
    'J', os20j_sgi_sigs, os20j_pc_sigs, os20j_sgi_syms, os20j_pc_syms,
    'K', os20k_sgi_sigs, os20k_pc_sigs, os20k_sgi_syms, os20k_pc_syms,
    'L', os20l_sgi_sigs, os20l_pc_sigs, os20l_sgi_syms, os20l_pc_syms,
};
#endif

typedef struct _siglist_t {
    sig_t *sig;
    struct _siglist_t *next;
} siglist_t;

siglist_t *first_ops[64];
siglist_t *found;
sig_t *sigs;
sym_t **syms;

override_t *override = NULL;

char *strstrip(char *s)
{
    int x;

    x = strlen(s) - 1;
    while (x>=0 && isspace(s[x])) s[x--] = '\0';

    while (*s && isspace(*s)) s++;

    return s;
}

void byteswap(u8* rom, u32 rom_len)
{
    u32 i;
    u32 *p = (u32 *)rom;

    for (i = 0; i < rom_len; i += 4) {
       *p++ = htonl(*p); 
    }
}

int load_file(char *filename, u8 **buf, u32 *size)
{
    FILE *in;
    struct stat sb;

    if ((in = fopen(filename, "r")) == NULL) {
        perror("fopen");
        return -1;
    }

    if (fstat(fileno(in), &sb) < 0) {
        perror("fstat");
        return -1;
    }

    if ((*buf = malloc(sb.st_size)) == NULL) {
        fprintf(stderr, "Unable to malloc %d bytes\n", sb.st_size);
        return -1;
    }

    fprintf(stderr, "Loading '%s'\n", filename);
    if (fread(*buf, sb.st_size, 1, in) != 1) {
        fprintf(stderr, "Unable to read %d bytes\n", sb.st_size);
        return -1;
    }
    fclose(in);
    *size = sb.st_size;
    fprintf(stderr, "  %d bytes loaded.\n", *size);
    return 0;
}

void make_first_ops(void)
{
    int i;

    bzero(first_ops, sizeof(first_ops));
    for (i = 0; sigs[i].symbol; ++i) {
        siglist_t *p = malloc(sizeof(siglist_t));
        p->sig = &sigs[i];
        p->next = first_ops[sigs[i].first_op];
        first_ops[sigs[i].first_op] = p;
    }
}


void patch_rom(u8 *rom, char *filename)
{
    int i;
    FILE *fp;
    char line[256], *p;
    u32 offset;
    u32 jump_addr;

    if ((fp = fopen(filename, "r")) == NULL) {
        perror("fopen");
        return;
    }
 
    while (fgets(line, sizeof(line), fp)) {
        sig_t *rs = sigs, *ps = bb_libultra_rom_sigs;
        char rname[256];
        u32 rsize, *rp, *pp;
        u32 hi16 = 0, lo16 = 0, rel26;
        u8 *r;
        rel_t *rel, dummy = {~0, 0, 0, 0, NULL};
        sym_t dummy_sym, *dp;

        if (line[0] == '#') continue;
        p = strstrip(line);
        while (rs->symbol) {
            if (!strcmp(p, rs->symbol)) {
                break;
            }
            ++rs;
        }
        if (!rs->symbol) {
            fprintf(stderr, "Unable to locate '%s' in rom sigs\n\n", p);
            continue;
        }
        if (!rs->offset) {
            fprintf(stderr, "Unable to patch. '%s' has not been found in the ROM\n\n", rs->symbol);
            continue;
        }
        while (ps->symbol) {
            if (!strcmp(p, ps->symbol)) {
                break;
            }
            ++ps;
        }
        if (!ps->symbol) {
            fprintf(stderr, "Unable to locate '%s' in patch sigs\n\n", p);
            continue;
        }
        if (!strcmp(rs->symbol, "__osDevMgrMain") || 
            ps->num_ops > rs->num_ops) {
#if 0
            fprintf(stderr, "Unable to patch '%s'. New routine is larger than original (%d > %d)\n\n", rs->symbol, ps->num_ops, rs->num_ops);
            continue;
#else
            fprintf(stderr, "Unable to patch '%s' in place. New routine is larger than original (%d > %d)\n", rs->symbol, ps->num_ops, rs->num_ops);
            offset = errata_end - rom;
            jump_addr = ERRATA_START_ADDR+(errata_end-errata_start);
            fprintf(stderr, "Insert jump to 0x%08x\n", jump_addr);

            errata_end += ps->num_ops<<2;
#endif
        } else {
            offset = rs->offset;
            jump_addr = 0;
        }
        fprintf(stderr, "Patching '%s' [%d] with [%d] @ 0x%08x\n", rs->symbol, rs->num_ops, ps->num_ops, rs->offset);
        snprintf(rname, sizeof(rname), "routines/%s", p);
        load_file(rname, &r, &rsize);
        byteswap(r, rsize);
        rp =  (u32 *)(rom + rs->offset);
        rel = rs->relocs ? rs->relocs : &dummy;
        for (i = 0; i < rs->num_ops; ++i) {
            u32 op = *rp++;
            if (i == rel->index) {
                if (rel->sym == NULL && rel->text) {
                    switch (rel->type) {
                    case R_MIPS_HI16:
                        hi16 = (op & 0xffff) - rel->hi_offset;
                        fprintf(stderr, "In '%s': setting hi16=0x%04x\n", rs->symbol, hi16);
                        break;
                    case R_MIPS_LO16:
                        lo16 = (op & 0xffff) - rel->lo_offset;
                        fprintf(stderr, "In '%s': setting lo16=0x%04x\n", rs->symbol, lo16);
                        break;
                    case R_MIPS_26:
                        rel26 = (op & 0x03ffffff) - rel->hi_offset;
                        hi16 = (rel26 >> 14) | 0x8000;
                        lo16 = (rel26 << 2) & 0xffff;
                        fprintf(stderr, "In '%s': setting hi16=0x%04x, lo16=0x%04x (rel26=0x%08x)\n", rs->symbol, hi16, lo16, rel26);
                        break;
                    }
                }
                ++rel;
            }
        }
        if (jump_addr) {
            rp =  (u32 *)(rom + rs->offset);
            *rp++ = 0x08000000 | ((jump_addr & 0x1fffffff) >> 2);
            *rp++ = 0;
        }
        rp =  (u32 *)(rom + offset);
        pp = (u32 *) r;
        rel = ps->relocs ? ps->relocs : &dummy;
        for (i = 0; i < ps->num_ops; ++i) {
            u32 op = *pp++;
            if (i == rel->index) {
                sym_t **s = syms;
                if (rel->sym) {
                    while (*s) {
                        if (!strcmp((*s)->symbol, rel->sym->symbol)) {
                            break;
                        }
                        ++s;
                    }
                } else {
                    if (!rel->text) {
                        fprintf(stderr, "ERROR: Don't know how to handle .rodata!!!\n");
                    }
                    dummy_sym.symbol = ".text";
                    if (hi16 || lo16) {
                        dummy_sym.hi = hi16;
                        dummy_sym.lo = lo16;
                    } else {
                        dummy_sym.hi = ((0x80000000 - 0xc00 + rs->offset) >> 16) & 0xffff;
                        dummy_sym.lo = ((0x80000000 - 0xc00 + rs->offset) >> 0) & 0xffff;
                    }
                    if (jump_addr) {
                        dummy_sym.hi = (jump_addr >> 16) & 0xffff;
                        dummy_sym.lo = (jump_addr >>  0) & 0xffff;
                    }
                    dummy_sym.found = 1;
                    dp = &dummy_sym;
                    s = &dp;
                }
                if (!*s) {
                    fprintf(stderr, "Ack!!! Unable to find symbol '%s'\n", rel->sym->symbol);
                } else {
                    switch (rel->type) {
                    case R_MIPS_HI16:
                        if ((*s)->found) {
                            op = (op & 0xffff0000) | ((op & 0xffff) + (*s)->hi);
                            fprintf(stderr, "relocating '%s' to 0x%08x @ %d\n", (*s)->symbol, (*s)->hi, i);
                        } else {
                            fprintf(stderr, "ERROR: '%s' has not been found in rom\n", (*s)->symbol);
                        }
                        break;
                    case R_MIPS_LO16:
                        if ((*s)->found) {
                            op = (op & 0xffff0000) | ((op & 0xffff) + (*s)->lo);
                            fprintf(stderr, "relocating '%s' to 0x%08x @ %d\n", (*s)->symbol, (*s)->lo, i);
                        } else {
                            fprintf(stderr, "ERROR: '%s' has not been found in rom\n", (*s)->symbol);
                        }
                        break;
                    case R_MIPS_26:
                        if ((*s)->found) {
                            u32 reloc = (*s)->lo;
                            op = (op & 0xfc000000) | ((op & 0x03ffffff) + ((((*s)->hi<<16)|(*s)->lo)>>2)&0x03ffffff);
                            fprintf(stderr, "relocating '%s' to 0x%08x @ %d\n", (*s)->symbol, ((((*s)->hi<<16)|(*s)->lo)>>2)&0x03ffffff, i);
                        } else {
                            fprintf(stderr, "ERROR: '%s' has not been found in rom\n", (*s)->symbol);
                        }
                        break;
                    }
                }
                ++rel;
            }
   
            *rp++ = op;
        } 
        free(r);
        fprintf(stderr, "\n");
    }

    fclose(fp);
}

extern void make_crc_table();
extern u32 crc32(u32 crc, u8* buf, u32 len);

typedef enum {
    NOT_FOUND,
    FOUND,
    AMBIGUOUS,
} sig_return_t;

sig_return_t check_signature(u32 *code, sig_t *sig)
{
    u32 crc = 0;
    u32 op;
    int i;
    rel_t dummy = {~0, 0, 0, 0, NULL};
    rel_t *p;
    u32 *start = code;
    u8 not_sure = 0;
   
    p = sig->relocs ? sig->relocs : &dummy;

    for (i = 0; i < sig->num_ops; ++i) {
        op = *code++;
        if (i == p->index) {
            sym_t *s = p->sym;
            switch (p->type) {
            case R_MIPS_HI16:
                if (s) {
                    if (s->found) {
                        if ((op & 0x0000ffff) != (s->hi + p->hi_offset)) {
                            return 0;
                        }
                    } else {
                        not_sure = 1;
                    }
                }
                op &= 0xffff0000;
                break;
            case R_MIPS_LO16:
                if (s) {
                    if (s->found) {
                        if ((op & 0x0000ffff) != (s->lo + p->lo_offset)) {
                            return 0;
                        }
                    } else {
                        not_sure = 1;
                    }
                }
                op &= 0xffff0000;
                break;
            case R_MIPS_26:
                if (s) {
                    if (s->found) {
                        if ((op & 0x03ffffff) != ( (((s->hi<<16)|s->lo) & 0x0ffffffc)>>2)) {
                            return 0;
                        }
                    } else {
                        not_sure = 1;
                    }
                }
                op &= 0xfc000000;
                break;
            default:
                fprintf(stderr, "Invalid relocation type: %d\n", p->type);
                break;
            }
            ++p;
        } else {
            if (((op >> 26) & 0x3f) == 2) { /* Jump */
                op &= 0xfc000000;
            }
        }
        crc = crc32(crc, (u8*)&op, sizeof(op));
        if (i == 3 && crc != sig->partial_crc)
            return 0;
    }
    //printf("crc = %08x\n", crc);

    if (crc == sig->crc) {
        if (sig->ambiguous && not_sure)
            return AMBIGUOUS;
        code = start;
        p = sig->relocs ? sig->relocs : &dummy;
        for (i = 0; i < sig->num_ops; ++i) {
            op = *code++;
            if (i == p->index) {
                sym_t *s = p->sym;
                if (s) {
                    switch (p->type) {
                    case R_MIPS_HI16:
                        if (!s->found) {
                            s->hi = (op-p->hi_offset) & 0xffff;
                            s->found = s->lo != 0;
                        }
                        break;
                    case R_MIPS_LO16:
                        if (!s->found) {
                            s->lo = (op-p->lo_offset) & 0xffff;
                            s->found = s->hi != 0;
                        }
                        break;
                    case R_MIPS_26:
                        if (!s->found) {
                            s->lo = ((op - p->hi_offset) << 2) & 0xffff;
                            s->hi = (((op - p->hi_offset) & 0x03ffffff) >> 14) | 0x8000;
                            fprintf(stderr, "%s set to 0x%04x 0x%04x\n", s->symbol, s->lo, s->hi);
                            s->found = 1;
                        }
                        break;
                    }
                }
                ++p;
            }
        }
        return FOUND;
    } else {
        return NOT_FOUND;
    }
}

void delete_signature(sig_t *s)
{
    siglist_t **prev, *c;

    prev = &first_ops[s->first_op];
    for (c = first_ops[s->first_op]; c; c = c->next) {
        if (c->sig == s) {
            *prev = c->next;
            c->next = found;
            found = c;
            break;
        }
        prev = &(c->next);
    }
}

void scan_rom(u8* rom, u32 rom_len)
{
    u32 *p = (u32 *) rom;
    u32 *rom_end = (u32 *)(rom + rom_len);

    fprintf(stderr, "Scanning ROM for functions\n");
    while (p < rom_end) {
        u32 first_op = (*p >> 26) & 0x3f;
        siglist_t *sl;
        //printf("%d: %08x (%d)\n", p - (u32*)rom, *p, first_op);
        for (sl = first_ops[first_op]; sl; sl = sl->next) {
            if ((rom_end - p) >= sl->sig->num_ops) {
                //printf(" First_op match @ %d\n", p-(u32*)rom);
                sig_return_t r = check_signature(p, sl->sig);
                if (r == FOUND) {
                    printf("%s found @ 0x%08x\n", sl->sig->symbol, (u8*)p - rom);
                    sl->sig->offset = (u8*)p - rom;
                    delete_signature(sl->sig);
                    break;
                } else if (r == AMBIGUOUS) {
                    fprintf(stderr, "Found ambiguous match @ 0x%08x [%s]\n", (u8*)p - rom, sl->sig->symbol);
                    break;
                }
            }
        }
        p += sl ? sl->sig->num_ops : 1;
    }
    fprintf(stderr, "done.\n\n");
}

static char *progname;

void Usage(void)
{
    fprintf(stderr, "Usage: %s [options] rom\n", progname);
    fprintf(stderr,
            "\t-i, --input <rom>        Read rom image from <rom>\n"
            "\t-o, --output <rom>       Write patched rom file to <rom>\n"
            "\t-j, --jdebug <file>      Dump symbol information for jdebug\n"
            "\t-p, --patch <funcfile>   Attempt to patch the functions in <funcfile>\n"
            "\t    --sgi                Use the SGI signatures\n"
            "\t    --pc                 Use the PC signatures\n"
            "\t-f, --force-lib <lib>    Use OS 20<lib> signatures\n"
            "\t-D <symbol>=<offset>     Override <symbol> @ <offset>\n"
            "\t-v, --vitbl              Scan for and patch vitbl\n"
            "\t    --osinit             Scan for and patch osInitialize\n"
            "\t-c, --crc                Scan for and patch crc miscompare (Indy)\n"
            "\t    --pal                Scan boot code and set osTvType = PAL(Indy)\n"
            "\t-h, --help               Print this message and exit\n"
           );
    exit(EXIT_FAILURE);
}

char *infile = NULL;
char *outfile = NULL;
char *patch_funcs = NULL;
char *patch_with = NULL;
char *scan_with = NULL;
int do_vitbl = 0;
int do_crc = 0;
int do_pal = 0;
int do_osinit = 0;
char *jdebug_file = NULL;
int use_sgi = 1;
char force_lib = 0;

void parse_args(int argc, char *argv[])
{
    static struct option long_options[] = {
        {"patch", 1, 0, 'p'},
        {"vitbl", 0, 0, 'v'},
        {"crc", 0, 0, 'c'},
        {"osinit", 0, &do_osinit, 1},
        {"input", 1, 0, 'i'},
        {"output", 1, 0, 'o'},
        {"pal", 0, &do_pal, 1},
        {"sgi", 0, &use_sgi, 1},
        {"pc", 0, &use_sgi, 0},
        {"force-lib", 1, 0, 'f'},
        {"help", 0, 0, 'h'},
        {"jdebug", 1, 0, 'j'},
        {0, 0, 0, 0,}
    };
    int longindex;
    progname = argv[0];

    while (1) {
        int c;
        char *p;

        if ((c = getopt_long(argc, argv, "cf:hi:j:o:p:vD:", long_options, &longindex)) == -1) {
            break;
        }
        switch(c) {
        case 0:
            break;
        case 'c':
            do_crc = !do_crc;
            break;
        case 'f':
            force_lib = optarg[0];
            break;
        case 'h':
            Usage();
            break;
        case 'i':
            infile = optarg;
            break;
        case 'j':
            jdebug_file = optarg;
            break;
        case 'o':
            outfile = optarg;
            break;
        case 'p':
            patch_funcs = optarg;
            break;
        case 'v':
            do_vitbl++;
            break;
        case 'D':
            if ((p = strchr(optarg, '='))) {
                override_t *o;
                *p++ = 0;
                o = malloc(sizeof(override_t));
                o->symbol = optarg;
                o->offset = strtoul(p, NULL, 0);
                o->next = override;
                override = o;
            } else {
                fprintf(stderr, "-D<symbol>=<offset>\n");
            }
            break;
        default:
            fprintf(stderr, "Illegal option '%c'\n", c);
            Usage();
            break;
        }
    }

    if (infile == NULL) {
        fprintf(stderr, "You must specify an input rom file\n");
        Usage();
    }
}

int output_rom(u8 *rom, u32 rom_size, char *outfile)
{
    FILE *out;

    byteswap(rom, rom_size);
    if ((out = fopen(outfile, "w+")) == NULL) {
        perror(outfile);
        return -1;
    }
    if (fwrite(rom, rom_size, 1, out) != 1) {
        fprintf(stderr, "Unable to write %d bytes\n", rom_size);
        return -1;
    }
    fclose(out);
}

extern vimode_t vimodes[];
extern void *memmem (__const void *__haystack, size_t __haystacklen,
		     __const void *__needle, size_t __needlelen);
void patch_vitbl(u8*rom, u32 rom_size)
{
    int i;
    vimode_t *p = vimodes;

    fprintf(stderr, "Scanning ROM for vitbl entries...\n");
    while (p->data[0] != 0xff) {
        vimode_t *v;
        u8 *r = rom;
        u32 size = rom_size;
        while ((v=memmem(r, size, p, sizeof(vimode_t))) != NULL) {
            v->data[1] &= ~0x00002000;
            fprintf(stderr, "  Video mode %d found @ 0x%x\n", p->data[0]>>24, (u8*)v-rom);
            if (do_vitbl == 1) {
                break;
            }
            r = (u8*)(v+1);
            size = rom_size - (r - rom);
        }

        ++p;
    }
    fprintf(stderr, "done\n\n");
}

void patch_crc(u8 *rom, u32 rom_size)
{
    u32 *p = (u32 *)rom;
    u32 *end = (u32 *) (rom_size < 0x1000 ? rom+rom_size : rom+0x1000);

    fprintf(stderr, "Scanning ROM boot code for infinite loop...\n");
    while (p < end) {
        if (*p == 0x0411ffff) {
            fprintf(stderr, "  Patching infinite loop @ 0x%x\n", (u8*)p-rom);
            *p = 0;
        }
        ++p;
    }
    fprintf(stderr, "done\n\n");
}

void patch_pal(u8 *rom, u32 rom_size)
{
    u32 *p = (u32 *)rom;
    u32 *end = (u32 *) (rom_size < 0x1000 ? rom+rom_size : rom+0x1000);

    fprintf(stderr, "Scanning ROM boot code for osTvType...\n");
    while (p < end) {
        if (*p == 0xad140000) {
            fprintf(stderr, "  Patching osTvType @ 0x%x\n", (u8*)p-rom);
            *p = 0xad000000;
        }
        ++p;
    }
    fprintf(stderr, "done\n\n");
}

void patch_osinit(u8 *rom, u32 rom_size)
{
    u32 *p = (u32 *)rom;
    u32 *end = (u32 *) (rom+rom_size);
    static u32 sgi_initcode[] = {
        0x3c041fc0, 0x348407fc, 0x0c000000, 0x27a50034, 0x10400007, 0x00000000,
        0x3c041fc0, 0x348407fc, 0x0c000000, 0x27a50034, 0x1440fffb, 0x00000000,
        0x8fa50034, 0x3c041fc0, 0x348407fc, 0x34af0008, 0x0c000000, 0x01e02825,
        0x10400009, 0x00000000, 0x8fa50034, 0x3c041fc0, 0x348407fc, 0x34b80008,
        0x0c000000, 0x03002825, 0x1440fff9
    };
    static u32 sgi_initmask[] = {
        0xffffffff, 0xffffffff, 0xfc000000, 0xffffffe7, 0xffffffff, 0xffffffff, 
        0xffffffff, 0xffffffff, 0xfc000000, 0xffffffe7, 0xffffffff, 0xffffffff, 
        0xffffffe7, 0xffffffff, 0xffffffff, 0xffffffff, 0xfc000000, 0xffffffff, 
        0xffffffff, 0xffffffff, 0xffffffe7, 0xffffffff, 0xffffffff, 0xffffffff, 
        0xfc000000, 0xffffffff, 0xffffffff
    };
    static u32 pc_initcode[] = {
        0x3c041fc0, 0x348407fc, 0x0c000000, 0x27a50010, 0x1440fffc, 0x3c041fc0,
        0x8fa50010, 0x3c041fc0, 0x348407fc, 0x0c000000, 0x34a50008, 0x1440fffa
    };
    static u32 pc_initmask[] = {
        0xffffffff, 0xffffffff, 0xfc000000, 0xffffffff, 0xffffffff, 0xffffffff,
        0xffffffff, 0xffffffff, 0xffffffff, 0xfc000000, 0xffffffff, 0xffffffff
    };
    u32 *initcode, *initmask, codesize;
    if (use_sgi) {
        initcode = sgi_initcode;
        initmask = sgi_initmask;
        codesize = sizeof(sgi_initcode);
    } else {
        initcode = pc_initcode;
        initmask = pc_initmask;
        codesize = sizeof(pc_initcode);
    }

    fprintf(stderr, "Scanning ROM for osInitialize chunk...\n");
    while (p < end) {
        if (*p == initcode[0]) {
            int i;
            for (i = 1; i < codesize/sizeof(u32); ++i) {
                if ((p[i] & initmask[i]) != (initcode[i] & initmask[i])) {
                    break;
                }
            }
            if (i == codesize/sizeof(u32)) {
                fprintf(stderr, "  Patching osInitialize chunk @ 0x%x\n", (u8*)p-rom);
                bzero(p, codesize);
                p += i-1;
            }
        }
        ++p;
    }
    fprintf(stderr, "done.\n\n");
}

void dump_jdebug(const char *file)
{
    FILE *fp;
    sym_t **s = syms;
    fprintf(stderr, "Dumping jdebug data:\n");
    if ((fp = fopen(file, "w")) == NULL) {
        perror(file);
        return;
    }
    while (*s) {
        if ((*s)->found) {
            fprintf(fp, "%s 0x%04x%04x 0x%x\n", (*s)->symbol, (*s)->hi, (*s)->lo, 4);
        }
        ++s;
    }
    fprintf(stderr, "done.\n\n");
    fclose(fp);
}

void override_symbols(void)
{
    override_t *p = override;
    fprintf(stderr, "Overriding symbols:\n");
    while (p) {
        sig_t *rs = sigs;
        while (rs->symbol) {
            if (!strcmp(p->symbol, rs->symbol)) {
                break;
            }
            ++rs;
        }
        if (rs->symbol) {
            fprintf(stderr, "  overriding '%s' from 0x%08x to 0x%08x\n", rs->symbol, rs->offset, p->offset);
            rs->offset = p->offset;
        } else {
            fprintf(stderr, "Unable to override '%s', not found.\n", p->symbol);
        }
        p = p->next;
    }
    fprintf(stderr, "done.\n\n");
}

int main(int argc, char *argv[])
{
    u8 *rom, *lib;
    u32 rom_size;
    int i;
    char version;
    u32 pad;

    parse_args(argc, argv);

    if (load_file(infile, &rom, &rom_size) < 0 ) {
        return -1;
    }

    pad = (rom_size + 0x3fff) & ~0x3fff;
    rom = realloc(rom, pad+ERRATA_MAX_SIZE);
    errata_start = errata_end = rom + pad;


    sigs = libraries[sizeof(libraries)/sizeof(libraries[0]) - 1].sgi_sigs;
    syms = libraries[sizeof(libraries)/sizeof(libraries[0]) - 1].sgi_syms;
    fprintf(stderr, "Rom is using version '%c'\n", rom[15]);
    if (force_lib) {
        fprintf(stderr, "Forcing version '%c'\n", force_lib);
        version = force_lib;
    } else {
        version = rom[15];
    }
    for (i = 0; i < sizeof(libraries)/sizeof(libraries[0]); ++i) {
        if (version == libraries[i].version) {
            sigs = use_sgi ? libraries[i].sgi_sigs : libraries[i].pc_sigs;
            syms = use_sgi ? libraries[i].sgi_syms : libraries[i].pc_syms;
            fprintf(stderr, "  found signatures for this library\n");
            break;
        }
    }

    byteswap(rom, rom_size);
    make_crc_table();
    make_first_ops();

    if (do_vitbl) {
        patch_vitbl(rom, rom_size);
    }

    if (do_crc) {
        patch_crc(rom, rom_size);
    }
    
    if (do_pal) {
        patch_pal(rom, rom_size);
    }

    if (patch_funcs || jdebug_file) {
        scan_rom(rom, rom_size);
    }

    if (override) {
        override_symbols();
    }

    if (patch_funcs) {
        patch_rom(rom, patch_funcs);
    }

    if (do_osinit) {
        patch_osinit(rom, rom_size);
    }

    if (jdebug_file) {
        dump_jdebug(jdebug_file);
    }

    if (outfile) {
        if (output_rom(rom, pad+ERRATA_MAX_SIZE, outfile) < 0) {
            return -1;
        }
    }

    return 0;
}
