/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 21:17:57 by aakin-al          #+#    #+#             */
/*   Updated: 2017/09/01 10:38:42 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

char			*ft_itoa_base_trim(uintmax_t val, int base, int trim)
{
	int8_t		len;
	char		*str;
	int			sign;

	sign = 1;
    len = trim;
	str = (char *)malloc(sizeof(char) * len + 1);
    str[len] = '\0';
	while (len > 0)
	{
        if (val == 0)
            str[--len] = '0';
        else
		    str[--len] = (val % base) + (val % base > 9 ? 'a' - 10 : '0');
        val /= base;
	}
	return (str);
}