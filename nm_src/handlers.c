#include "../includes/nm.h"

void        print_output(int nsyms, int symoff, int stroff, char *ptr)
{
    int                 i;
    struct nlist_64     *arr;
    char                *s_table;

    i = 0;
    s_table = (void *)ptr + stroff;
    arr = (void *)ptr + symoff;
    while (i < nsyms)
    {
        ft_printf("%ld %c %s\n", s_table + arr[i].n_value, s_table + arr[i].n_sect ,s_table + arr[i].n_un.n_strx);
        i++;
    }
}

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
            // ft_printf("handle_64 sym: %d\n", sym->nsyms);
            print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
            break;
        }
        lc = (void *) lc + lc->cmdsize;
        i++;
    }
}