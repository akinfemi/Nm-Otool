/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:47:36 by aakin-al          #+#    #+#             */
/*   Updated: 2017/11/02 22:49:39 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void			ft_otool2(char *ptr, char *name)
{
	unsigned int	mag_no;

	mag_no = *(int *)ptr;
	if (ft_strncmp(ptr, ARMAG, SARMAG) == 0)
	{
		if (ft_strlen(name) > 0)
			ft_printf("Archive : %s:\n", name);
		handle_lib(ptr, name);
	}
	else
		ft_printf("Magic Number %d currently not handled.\n", mag_no);
}

void				ft_otool(char *ptr, char *name)
{
	unsigned int	mag_no;

	mag_no = *(int *)ptr;
	if (mag_no == MH_MAGIC_64)
	{
		if (ft_strlen(name) > 0)
			ft_printf("%s:\n", name);
		otool_64(ptr);
	}
	else if (mag_no == MH_MAGIC)
	{
		if (ft_strlen(name) > 0)
			ft_printf("%s:\n", name);
		otool_32(ptr);
	}
	else if (mag_no == FAT_CIGAM)
	{
		if (ft_strlen(name) > 0)
			ft_printf("%s:\n", name);
		otool_fat32(ptr);
	}
	else
		ft_otool2(ptr, name);
}

int					main(int ac, char **ag)
{
	int			fd;
	char		*ptr;
	struct stat	buf;
	int			i;

	if (ac == 1)
	{
		ft_printf("Usage: %s <exec1> <exec2> ...\n", ag[0]);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (++i < ac)
	{
		if ((fd = open(ag[i], O_RDONLY)) < 0)
			return (EXIT_FAILURE);
		if (fstat(fd, &buf) < 0)
			return (EXIT_FAILURE);
		if (!(ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)))
			return (EXIT_FAILURE);
		ft_otool(ptr, ag[i]);
		if (munmap(ptr, buf.st_size) < 0)
			return (EXIT_FAILURE);
		close(fd);
	}
	return (EXIT_SUCCESS);
}
