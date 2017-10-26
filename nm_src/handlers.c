    #include "../includes/nm.h"
#include <stdio.h>

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

void        print_list(t_list *list)
{
    t_nm_basic      *objects;

    if (!list)
        return ;
    while (list)
    {
        objects = (t_nm_basic *) list->content;
        if (objects->value != 0)
            ft_printf("%016llx %c %s\n", objects->value, 't', objects->name); //get_type(objects->type)
        else
            ft_printf("%16s %c %s\n", "", 't', objects->name); //get_type(objects->type)
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
        set_type(s_table + arr[i].n_type, &object->type);
        // ft_printf("%016llx %c %s\n", object->value, 't', object->name);
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