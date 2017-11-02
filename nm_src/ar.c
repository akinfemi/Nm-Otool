#include "../includes/nm.h"
#include <stdio.h>


void        parse_list(t_list *ar_list, char *ptr, char *lib_name)
{
    struct  ar_hdr  *ar;
    char            *name;
    t_offset        *off;
    int             name_off;
    // (void)ptr;
    while (ar_list)
    {
        off = ar_list->content;
        ar = (void *)ptr + off->offset;
        name_off = ft_atoi(ft_strchr(ar->ar_name, '/') + 1);
        name = ft_strdup(ft_strchr(ar->ar_name, '`') + 2);
        ft_printf("\n%s(%s)\n", lib_name, name);
        ft_nm((void *)ar + sizeof(struct ar_hdr) + name_off, name, 1);
        ar_list = ar_list->next;
    }
}

t_offset      *new_off_t_node(struct ranlib ran, char *name)
{
    t_offset  *off_t_node;

    off_t_node = malloc(sizeof(t_offset));
    off_t_node->name = name;
    off_t_node->offset = ran.ran_off;
    off_t_node->ran_strx = ran.ran_un.ran_strx;
    return (off_t_node);
}

t_list         *make_list(struct ranlib ran, char *name)
{
    t_offset      *off_node;

    off_node = new_off_t_node(ran, name);
    return(ft_lstnew(off_node, sizeof(t_offset)));
}
