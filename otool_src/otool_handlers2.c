/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_handlers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:26:00 by aakin-al          #+#    #+#             */
/*   Updated: 2017/11/02 13:42:57 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/otool.h"

void			otool_64(char *ptr)
{
	int							ncmds;
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct segment_command_64	*seg;
	int							i;

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
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void			otool_32(char *ptr)
{
	int						ncmds;
	struct mach_header		*header;
	struct load_command		*lc;
	struct segment_command	*seg;
	int						i;

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
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void			otool_fat32(char *ptr)
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
	ft_otool(ptr + swap32(offset), "\0");
}

void			handle_lib(char *ptr, char *lib_name)
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
