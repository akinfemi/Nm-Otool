#include "../includes/otool.h"

void        print_res(struct section_64 *sect, char *ptr)
{
    uint32_t    i;
    char        *res;
    uint64_t    addr;

    i = 0;
    addr = sect->addr;
    while (i < sect->size)
    {
        res = ft_itoa_base_trim(ptr[i], 16, 2);
        if (i == 0 || i % 16 == 0)
        {
            ft_printf("%016llx \t", addr);
            addr+=16;
        }
        ft_printf("%s ", res);
        free(res);
        if ((i + 1) % 16 == 0)
            ft_putchar('\n');
        i++;
    }
    ft_putchar('\n');
}
void        print_res_32(struct section *sect, char *ptr)
{
    uint32_t    i;
    char        *res;
    uint64_t    addr;

    i = 0;
    addr = sect->addr;
    while (i < sect->size)
    {
        res = ft_itoa_base_trim(ptr[i], 16, 2);
        if (i == 0 || i % 16 == 0)
        {
            ft_printf("%08llx \t", addr);
            addr+=16;
        }
        ft_printf("%s ", res);
        free(res);
        if ((i + 1) % 16 == 0)
            ft_putchar('\n');
        i++;
    }
    ft_putchar('\n');
}
void        get_text_64(struct segment_command_64 *seg, struct mach_header_64 *header)
{
    struct section_64   *sect;
    uint32_t            i;

    sect = (void *)seg + sizeof(struct segment_command_64);
    i = 0;
    while (i < seg->cmdsize)
    {
        if (ft_strcmp(seg->segname, "__TEXT") == 0)
        {
            sect = (void *)seg + sizeof(struct segment_command_64);
            ft_printf("Contents of (%s,%s) section\n", seg->segname, sect->sectname);
            print_res(sect, (void *)header + sect->offset);
        }
        i++;
        seg = (void *)seg + sizeof(struct segment_command_64);
    }
}

void        get_text_32(struct segment_command *seg, struct mach_header *header)
{
    struct section      *sect;
    uint32_t            i;

    sect = (void *)seg + sizeof(struct segment_command);
    i = 0;
    while (i < seg->cmdsize)
    {
        if (ft_strcmp(seg->segname, "__TEXT") == 0)
        {
            sect = (void *)seg + sizeof(struct segment_command);
            ft_printf("Contents of (%s,%s) section\n", seg->segname, sect->sectname);
            print_res_32(sect, (void *)header + sect->offset);
        }
        i++;
        seg = (void *)seg + sizeof(struct segment_command);
    }
}

void        otool_64(char *ptr)
{
    int                         ncmds;
    struct mach_header_64       *header;
    struct load_command         *lc;
    struct segment_command_64   *seg;
    int                         i;

    i = 0;
    header = (struct mach_header_64 *)ptr;
    ncmds = header->ncmds;
    lc = (void *)ptr + sizeof(*header);
    while (i < ncmds)
    {
        if (lc->cmd == LC_SEGMENT_64)
        {
            seg = (struct segment_command_64 *)lc;
            get_text_64(seg, header);
            break;
        }
        lc = (void *) lc + lc->cmdsize;
        i++;
    }
}

void        otool_32(char *ptr)
{
    int                     ncmds;
    struct mach_header      *header;
    struct load_command     *lc;
    struct segment_command  *seg;
    int                     i;

    i = 0;
    header = (struct mach_header *)ptr;
    ncmds = header->ncmds;
    lc = (void *)ptr + sizeof(*header);
    while (i < ncmds)
    {
        if (lc->cmd == LC_SEGMENT)
        {
            seg = (struct segment_command *)lc;
            get_text_32(seg, header);
            break;
        }
        lc = (void *) lc + lc->cmdsize;
        i++;
    }
}

void        otool_fat32(char *ptr)
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
    ft_otool(ptr + SWAP32(offset));
}

void        otool_archive()
{

}