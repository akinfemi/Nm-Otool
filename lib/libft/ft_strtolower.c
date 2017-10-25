/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:22:33 by aakin-al          #+#    #+#             */
/*   Updated: 2017/09/01 14:28:51 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *str)
{
	int		len;
	int		i;
	char	*res;

	if (!str)
		return (0);
	i = -1;
	len = ft_strlen(str);
	res = (char *)ft_memalloc(sizeof(char) * len + 1);
	while (++i < len)
		res[i] = ft_tolower(str[i]);
	res[len] = '\0';
	return (res);
}
