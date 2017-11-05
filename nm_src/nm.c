/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:14:04 by aakin-al          #+#    #+#             */
/*   Updated: 2017/11/02 23:18:18 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void			ft_nm(char *ptr, char *name, int args)
{
	unsigned int	mag_no;

	mag_no = *(int *)ptr;
	if (mag_no == MH_MAGIC_64)
	{
		if (args > 1)
			ft_printf("\n%s:\n", name);
		handle_64(ptr, (ft_strstr(name, ".o") &&
			!ft_strstr(name, "a.out") ? 1 : 0));
	}
	else if (mag_no == MH_MAGIC)
	{
		if (args > 1)
			ft_printf("\n%s:\n", name);
		handle_32(ptr, (ft_strstr(name, ".o") &&
			!ft_strstr(name, "a.out") ? 1 : 0));
	}
	else if (mag_no == FAT_CIGAM)
		handle_fat32(ptr);
	else if (ft_strncmp(ptr, ARMAG, SARMAG) == 0)
		handle_lib(ptr, name);
	else
		ft_printf("Magic Number not handled.\n");
}

int				main(int ac, char **ag)
{
	int			fd;
	char		*ptr;
	struct stat	buf;
	int			i;

	i = 0;
	if (ac == 1)
		return (EXIT_FAILURE);
	while (++i < ac)
	{
		if ((fd = open(ag[i], O_RDONLY)) < 0)
			return (EXIT_FAILURE);
		if (fstat(fd, &buf) < 0)
			return (EXIT_FAILURE);
		if (!(ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)))
			return (EXIT_FAILURE);
		ft_nm(ptr, ag[i], ac - 1);
		if (munmap(ptr, buf.st_size) < 0)
			return (EXIT_FAILURE);
		close(fd);
	}
	return (EXIT_SUCCESS);
}
