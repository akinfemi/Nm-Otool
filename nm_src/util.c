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

char        get_type_o(t_nm_basic *object)
{
    t_type      type;

    type = object->type;
    if (type.n_ext == 1 && type.n_type == 14 && type.n_pext == 16 && type.n_stab == 64)
    {
        if (object->sect == 0)
            return ('U');
        if (object->sect == 1 && object->value != 0)
            return ('t');
        if (object->value == 0)
            return ('T');
    }
    if (type.n_stab == 96 )
    {
        if (object->value != 0)
        {
            return ('t');
        }
        return ('T');
    }
    if (type.n_ext == 0 && type.n_type == 0 && type.n_pext == 0 && type.n_stab == 0)
    {
        if (object->sect == 1 && object->value == 0)
            return ('T');
    }
    return ('\0');
}

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
        {
            if (object->sect == 9)
                return ('D');
            return ('T');
        }
    }
    if (type.n_ext == 0 && type.n_type == 0 && type.n_pext == 0 && type.n_stab == 0)
    {
        if (object->desc >= 256)
            return ('U');
    }
    return ('\0');
}

void        print_list(t_list *list, int obj)
{
    t_nm_basic      *objects;
    char            tp;

    if (!list)
        return ;
    while (list)
    {
        objects = (t_nm_basic *) list->content;
        if (obj)
            tp = get_type_o(objects);
        else
            tp = get_type(objects);
        // printf("Sect: %d\n", objects->sect);
        // ft_printf("Desc: %hd Sect: %d Ext: %d Type: %d Pext: %d Stab: %d Name: %s\n",  objects->desc, objects->sect, objects->type.n_ext, objects->type.n_type, objects->type.n_pext, objects->type.n_stab, objects->name);
        if (ft_strlen(objects->name) > 0 && tp != '\0')
        {
            if (tp != 'U')
                ft_printf("%016llx %c %s\n", objects->value, tp , objects->name);//, objects->sect
            else
                ft_printf("%16s %c %s\n", "", tp, objects->name); //, objects->sect
        }
        list = list->next;
    }
}

void        print_list_32(t_list *list, int obj)
{
    t_nm_basic      *objects;
    char            tp;

    if (!list)
        return ;
    while (list)
    {
        objects = (t_nm_basic *) list->content;
        if (obj)
            tp = get_type_o(objects);
        else
            tp = get_type(objects);
        // ft_printf("Desc: %hd Sect: %d Ext: %d Type: %d Pext: %d Stab: %d Name: %s\n",  objects->desc, objects->sect, objects->type.n_ext, objects->type.n_type, objects->type.n_pext, objects->type.n_stab, objects->name);
        if (ft_strlen(objects->name) > 0 && tp != '\0')
        {
            if (objects->value != 0)
                ft_printf("%08llx %c %s\n", objects->value, tp , objects->name);
            else
                ft_printf("%8s %c %s\n", "", tp, objects->name);
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

void        build_list(struct symtab_command *sym, char *ptr, int obj)
{
    uint32_t            i;
    struct nlist_64     *arr;
    char                *s_table;
    t_list              *objects;
    t_nm_basic          *object;

    i = 0;
    s_table = (void *)ptr + sym->stroff;
    arr = (void *)ptr + sym->symoff;
    objects = NULL;
    while (i < sym->nsyms)
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
    print_list(objects, obj);
}

void        build_list_32(struct symtab_command *sym, char *ptr, int obj)
{
    uint32_t            i;
    struct nlist        *arr;
    char                *s_table;
    t_list              *objects;
    t_nm_basic          *object;

    i = 0;
    s_table = (void *)ptr + sym->stroff;
    arr = (void *)ptr + sym->symoff;
    objects = (t_list *)malloc(sizeof(t_list));
    objects = NULL;
    while (i < sym->nsyms)
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
    print_list_32(objects, obj);
}