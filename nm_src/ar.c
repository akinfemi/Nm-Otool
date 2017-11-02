/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 12:53:55 by aakin-al          #+#    #+#             */
/*   Updated: 2017/11/02 12:56:46 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void		parse_list(t_list *ar_list, char *ptr, char *lib_name)
{
	struct ar_hdr	*ar;
	t_offset		*off;
	int				name_off;

	while (ar_list)
	{
		off = ar_list->content;
		ar = (void *)ptr + off->offset;
		name_off = ft_atoi(ft_strchr(ar->ar_name, '/') + 1);
		ft_printf("\n%s(%s)\n", lib_name, off->name);
		ft_nm((void *)ar + sizeof(struct ar_hdr) + name_off, off->name, 1);
		ar_list = ar_list->next;
	}
}

t_offset	*new_off_t_node(struct ranlib ran)
{
	t_offset	*off_t_node;

	off_t_node = malloc(sizeof(t_offset));
	off_t_node->name = NULL;
	off_t_node->offset = ran.ran_off;
	off_t_node->ran_strx = ran.ran_un.ran_strx;
	return (off_t_node);
}

t_list		*make_list(struct ranlib ran, char *ptr)
{
	t_offset		*off_node;
	struct ar_hdr	*ar;

	off_node = new_off_t_node(ran);
	ar = (void *)ptr + off_node->offset;
	off_node->name = ft_strdup(ft_strchr(ar->ar_name, '`') + 2);
	off_node->make_time = ft_atomax(ar->ar_date);
	return (ft_lstnew(off_node, sizeof(t_offset)));
}
