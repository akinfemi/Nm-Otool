#include "../includes/nm.h"
#include <stdio.h>

// static char     *get_name(char *ar_name)
// {
//     return (ft_strstr(ar_name, ARFMAG) + ft_strlen(ARFMAG));
// }

void        parse_list(t_list *ar_list, char *ptr, char *lib_name, int l_size)
{
    struct  ar_hdr  *ar;
    // char            *name;
    t_offset        *off;
    // (void)ptr;
    while (ar_list)
    {
        off = ar_list->content;
        ar = (void *)ptr + off->ran_strx;
        ft_printf("%s %s\n", lib_name, ar->ar_name);
        ft_nm((void *)ar + sizeof(struct ar_hdr) + l_size, lib_name, 1);
        ar_list = ar_list->next;
    }
}

t_offset      *new_off_t_node(struct ranlib ran, char *name)
{
    t_offset  *off_t_node;

    off_t_node = malloc(sizeof(t_offset));
    off_t_node->name = ft_strdup(name);
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
