#include "../includes/nm.h"
#include <stdio.h>
/*
void printBits(unsigned int num){
    // unsigned int size = sizeof(unsigned int);
    unsigned int maxPow = 1<<(8-1);
    printf("MAX POW : %u\n",maxPow);
    unsigned int i=0;
    for(;i<8;++i){
        // print last bit and shift left.
        printf("%u ",num&maxPow ? 1 : 0);
        num = num<<1;
    }
    printf("\n");
}
*/

char        get_type(t_nm_basic *object)
{
    t_type      type;

    type = object->type;
    if (type.n_ext == 1 && type.n_type == 14 && type.n_pext == 16 && type.n_stab == 64)
    {
        if (object->sect == 1)
            return ('t');
        if (object->sect == 10)
            return ('b');
    }
    if (type.n_pext == 0 && type.n_stab == 96)
    {
        if ((type.n_ext == 0 && type.n_type == 8) || (type.n_ext == 1 && type.n_type == 4))
            return ('T');
        else
            return ('\0');
    }
    if (type.n_ext == 0 && type.n_type == 0 && type.n_pext == 0 && type.n_stab == 0)
    {
        if (object->desc >= 256)
            return ('U');
        else
            return ('\0');
    }
    return ('\0');
}

void        print_list(t_list *list)
{
    t_nm_basic      *objects;
    char            tp;

    if (!list)
        return ;
    while (list)
    {
        objects = (t_nm_basic *) list->content;
        tp = get_type(objects);
        // printf("Sect: %d\n", objects->sect);
        // printf("Desc: %hd Sect: %d Ext: %d Type: %d Pext: %d Stab: %d Name: %s\n",  objects->desc, objects->sect, objects->type.n_ext, objects->type.n_type, objects->type.n_pext, objects->type.n_stab, objects->name);
        if (ft_strlen(objects->name) > 0 && tp != '\0')
        {
            if (objects->value != 0)
                ft_printf("%016llx %c %s\n", objects->value, tp , objects->name);//, objects->sect
            else
                ft_printf("%16s %c %s\n", "", tp, objects->name); //, objects->sect
        }
        list = list->next;
    }
}

void        set_type(char *n_type, t_type *type)
{
    type->n_ext = 0x01 & *n_type;
    type->n_type = 0x0e & *n_type;
    type->n_pext = 0x10 & *n_type;
    type->n_stab = 0xe0 & *n_type;
}

void        build_list(int nsyms, int symoff, int stroff, char *ptr)
{
    int                 i;
    struct nlist_64     *arr;
    char                *s_table;
    t_list              *objects;
    t_nm_basic          *object;

    i = 0;
    s_table = (void *)ptr + stroff;
    arr = (void *)ptr + symoff;
    objects = (t_list *)malloc(sizeof(t_list));
    objects = NULL;
    while (i < nsyms)
    {
        object = (t_nm_basic *)malloc(sizeof(t_nm_basic));
        object->name = ft_strdup(s_table + arr[i].n_un.n_strx);
        object->value = arr[i].n_value;
        object->sect = arr[i].n_sect;
        object->desc = arr[i].n_desc;
        set_type(s_table + arr[i].n_type, &object->type);
        ft_lstadd(&objects, ft_lstnew(object, sizeof(t_nm_basic)));
        i++;
    }
    ft_lstsort(objects, comp_alpha, 0);
    print_list(objects);
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
            build_list (sym->nsyms, sym->symoff, sym->stroff, ptr);
            break;
        }
        lc = (void *) lc + lc->cmdsize;
        i++;
    }
}