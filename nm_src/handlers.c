/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:02:47 by aakin-al          #+#    #+#             */
/*   Updated: 2017/11/02 13:10:14 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void		handle_64(char *ptr, int obj)
{
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	int						i;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			build_list(sym, ptr, obj);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void		handle_32(char *ptr, int obj)
{
	int						ncmds;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	int						i;

	i = 0;
	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			build_list_32(sym, ptr, obj);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void		handle_fat32(char *ptr)
{
	int						nfat_archs;
	struct fat_header		*header;
	struct fat_arch			*f_arch;
	int						i;
	int						offset;

	i = 0;
	header = (struct fat_header *)ptr;
	nfat_archs = swap32(header->nfat_arch);
	f_arch = (void *)ptr + sizeof(f_arch);
	offset = 0;
	while (i < nfat_archs)
	{
		if (swap32(f_arch[i].cputype) == CPU_TYPE_X86_64)
		{
			offset = f_arch[i].offset;
			break ;
		}
		i++;
	}
	ft_nm(ptr + swap32(offset), "\0", 1);
}

void		handle_lib(char *ptr, char *lib_name)
{
	struct ar_hdr		*ar;
	struct ranlib		*ran;
	int					i;
	int					l_size;
	t_list				*ar_list;

	ar = (void *)ptr + SARMAG;
	i = 0;
	l_size = ft_atoi(ft_strchr(ar->ar_name, '/') + 1);
	ran = (void *)ptr + sizeof(*ar) + SARMAG + l_size;
	l_size = *(int *)ran / sizeof(*ran);
	ar_list = NULL;
	while (i < l_size)
	{
		ft_lstadd(&ar_list, make_list(ran[i], ptr));
		i++;
	}
	ft_lstsort(ar_list, comp_alpha_two, 0);
	parse_list(ar_list, ptr, lib_name);
	ft_lstdel(&ar_list, offset_del);
}
