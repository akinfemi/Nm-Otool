/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:11:07 by aakin-al          #+#    #+#             */
/*   Updated: 2017/11/02 23:44:41 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void		build_list_32(struct symtab_command *sym, char *ptr, int obj)
{
	uint32_t			i;
	struct nlist		*arr;
	char				*s_table;
	t_list				*objects;
	t_nm_basic			*object;

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

void		print_list_32(t_list *list, int obj)
{
	t_nm_basic		*objects;
	char			tp;

	if (!list)
		return ;
	while (list)
	{
		objects = (t_nm_basic *)list->content;
		if (obj)
			tp = get_type_o(objects);
		else
			tp = get_type(objects);
		if (ft_strlen(objects->name) > 0 && tp != '\0')
		{
			if (objects->value != 0)
				ft_printf("%08llx %c %s\n", objects->value, tp, objects->name);
			else
				ft_printf("%8s %c %s\n", "", tp, objects->name);
		}
		list = list->next;
	}
}

void		set_type(char *n_type, t_type *type)
{
	type->n_ext = 0x01 & *n_type;
	type->n_type = 0x0e & *n_type;
	type->n_pext = 0x10 & *n_type;
	type->n_stab = 0xe0 & *n_type;
}

void		build_list(struct symtab_command *sym, char *ptr, int obj)
{
	uint32_t			i;
	struct nlist_64		*arr;
	char				*s_table;
	t_list				*objects;
	t_nm_basic			*object;

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

void		print_list(t_list *list, int obj)
{
	t_nm_basic		*objects;
	char			tp;

	if (!list)
		return ;
	while (list)
	{
		objects = (t_nm_basic *)list->content;
		if (obj)
			tp = get_type_o(objects);
		else
			tp = get_type(objects);
		if (ft_strlen(objects->name) > 0 && tp != '\0')
		{
			if (tp != 'U')
				ft_printf("%016llx %c %s\n", objects->value, tp, objects->name);
			else
				ft_printf("%16s %c %s\n", "", tp, objects->name);
		}
		list = list->next;
	}
}
