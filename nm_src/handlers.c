#include "../includes/nm.h"
#include <stdio.h>


void        handle_64(char *ptr)
{
    int                     ncmds;
    struct mach_header_64   *header;
    struct load_command     *lc;
    struct symtab_command   *sym;
    int                     i;

    i = 0;
    header = (struct mach_header_64 *)ptr;
    ncmds = header->ncmds;
    lc = (void *)ptr + sizeof(*header);
    while (i < ncmds)
    {
        if (lc->cmd == LC_SYMTAB)
        {
            sym = (struct symtab_command *)lc;
            build_list (sym->nsyms, sym->symoff, sym->stroff, ptr);
            break;
        }
        lc = (void *) lc + lc->cmdsize;
        i++;
    }
}

void        handle_32(char *ptr)
{
    int                     ncmds;
    struct mach_header      *header;
    struct load_command     *lc;
    struct symtab_command   *sym;
    int                     i;

    i = 0;
    header = (struct mach_header *)ptr;
    ncmds = header->ncmds;
    lc = (void *)ptr + sizeof(*header);
    while (i < ncmds)
    {
        if (lc->cmd == LC_SYMTAB)
        {
            sym = (struct symtab_command *)lc;
            build_list_32(sym->nsyms, sym->symoff, sym->stroff, ptr);
            break;
        }
        lc = (void *) lc + lc->cmdsize;
        i++;
    }
}

void        handle_fat32(char *ptr)
{
    int                     nfat_archs;
    struct fat_header       *header;
    struct fat_arch         *f_arch;
    int                     i;
    int                     offset;

    i = 0;
    header = (struct fat_header *)ptr;
    nfat_archs = SWAP32(header->nfat_arch);
    f_arch = (void *)ptr + sizeof(f_arch);
    offset = 0;
    while (i < nfat_archs)
    {
        if (SWAP32(f_arch[i].cputype) == CPU_TYPE_X86_64)
        {
            offset = f_arch[i].offset;
            break;
        }
        i++;
    }
    ft_nm(ptr + SWAP32(offset));
}