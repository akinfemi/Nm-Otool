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
            build_list (sym->nsyms, sym->symoff, sym->stroff, ptr);
            break;
        }
        lc = (void *) lc + lc->cmdsize;
        i++;
    }
}
/*
void        handle_fat32(char *ptr)
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
            build_list (sym->nsyms, sym->symoff, sym->stroff, ptr);
            break;
        }
        lc = (void *) lc + lc->cmdsize;
        i++;
    }
}
*/