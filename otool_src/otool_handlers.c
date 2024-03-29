/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:26:00 by aakin-al          #+#    #+#             */
/*   Updated: 2017/11/02 13:42:29 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/otool.h"

void			print_res(struct section_64 *sect, char *ptr)
{
	uint32_t	i;
	char		*res;
	uint64_t	addr;

	i = 0;
	addr = sect->addr;
	while (i < sect->size)
	{
		res = ft_itoa_base_trim(ptr[i], 16, 2);
		if (i == 0 || i % 16 == 0)
		{
			ft_printf("%016llx\t", addr);
			addr += 16;
		}
		ft_printf("%s ", res);
		free(res);
		if ((i + 1) % 16 == 0)
			ft_putchar('\n');
		i++;
	}
	if (i % 16 != 0)
		ft_putchar('\n');
}

void			print_res_32(struct section *sect, char *ptr)
{
	uint32_t	i;
	char		*res;
	uint64_t	addr;

	i = 0;
	addr = sect->addr;
	while (i < sect->size)
	{
		res = ft_itoa_base_trim(ptr[i], 16, 2);
		if (i == 0 || i % 16 == 0)
		{
			ft_printf("%08llx\t", addr);
			addr += 16;
		}
		ft_printf("%s ", res);
		free(res);
		if ((i + 1) % 16 == 0)
			ft_putchar('\n');
		i++;
	}
	if (i % 16 != 0)
		ft_putchar('\n');
}

void			get_text_64(struct segment_command_64 *seg,
		struct mach_header_64 *header)
{
	struct section_64	*sect;
	struct section_64	*temp;
	uint32_t			i;

	sect = (void *)seg + sizeof(struct segment_command_64);
	i = 0;
	temp = sect;
	while (i < seg->cmdsize)
	{
		if (!ft_strcmp(seg->segname, "__TEXT") ||
				!ft_strcmp(temp->sectname, "__text"))
		{
			sect = (void *)seg + sizeof(struct segment_command_64);
			ft_printf("Contents of (%s,%s) section\n", "__TEXT",
					sect->sectname);
			print_res(sect, (void *)header + sect->offset);
		}
		i++;
		seg = (void *)seg + sizeof(struct segment_command_64);
		temp = (void *)seg + sizeof(struct segment_command_64);
	}
}

void			get_text_32(struct segment_command *seg,
		struct mach_header *header)
{
	struct section		*sect;
	struct section		*temp;
	uint32_t			i;

	sect = (void *)seg + sizeof(struct segment_command);
	temp = sect;
	i = 0;
	while (i < seg->cmdsize)
	{
		if (!ft_strcmp(seg->segname, "__TEXT") ||
				!ft_strcmp(temp->sectname, "__text"))
		{
			sect = (void *)seg + sizeof(struct segment_command);
			ft_printf("Contents of (%s,%s) section\n", "__TEXT",
					sect->sectname);
			print_res_32(sect, (void *)header + sect->offset);
		}
		i++;
		seg = (void *)seg + sizeof(struct segment_command);
		temp = (void *)seg + sizeof(struct segment_command_64);
	}
}
