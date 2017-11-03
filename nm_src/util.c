/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:11:07 by aakin-al          #+#    #+#             */
/*   Updated: 2017/11/03 00:02:49 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

static char		gt_o(t_nm_basic *object)
{
	t_type		type;

	type = object->type;
	if (type.n_ext == 0 && type.n_type == 0 && type.n_pext == 0
			&& type.n_stab == 0)
	{
		if (object->sect == 1 && object->value == 0)
			return ('T');
	}
	return ('\0');
}

char			get_type_o(t_nm_basic *object)
{
	t_type		type;

	type = object->type;
	if (type.n_ext == 1 && type.n_type == 14 && type.n_pext == 16
			&& type.n_stab == 64)
	{
		if (object->sect == 0)
			return ('U');
		if (object->sect == 1 && object->value != 0)
			return ('t');
		if (object->value == 0)
			return ('T');
	}
	if (type.n_stab == 96)
	{
		if ((object->value != 0 && type.n_pext == 2) ||
			(type.n_type == 12 && type.n_ext == 1))
			return ('t');
		if (object->sect == 2)
			return ('D');
		return ('T');
	}
	return (gt_o(object));
}

static char		get_type_one(t_nm_basic *object)
{
	t_type		type;

	type = object->type;
	if ((type.n_ext == 0 && type.n_type == 8) ||
			(type.n_ext == 1 && type.n_type == 4))
	{
		if (object->sect == 9 || object->sect == 8 || object->sect == 11)
			return ('D');
		return ('T');
	}
	if ((type.n_ext == 1 && type.n_type == 8 && object->sect == 1) ||
			(object->sect == 1 && type.n_type == 4))
		return ('t');
	if (object->sect == 1 && type.n_type == 14 && type.n_ext == 0)
		return ('T');
	if ((object->sect == 4 || object->sect == 14 || object->sect == 6) &&
			type.n_type == 4)
		return ('s');
	if (object->sect == 16 && type.n_type == 4)
		return ('b');
	return ('\0');
}

static char		get_type_two(t_nm_basic *object)
{
	t_type		type;

	type = object->type;
	if (type.n_ext == 0 && type.n_type == 0 && type.n_pext == 0 &&
			type.n_stab == 0)
	{
		if (object->desc >= 256)
			return ('U');
	}
	if (object->sect == 1 && type.n_ext == 1 && type.n_type == 2 &&
			type.n_stab == 64)
		return ('T');
	if (object->sect == 15 && type.n_ext == 0 && type.n_type == 4 &&
			type.n_stab == 96)
		return ('d');
	if (type.n_ext == 0 && type.n_type == 10 && type.n_stab == 64)
	{
		if (object->sect == 1)
			return ('T');
		return ('S');
	}
	return ('\0');
}

char			get_type(t_nm_basic *object)
{
	t_type		type;

	type = object->type;
	if (type.n_ext == 1 && type.n_type == 14 && type.n_pext == 16 &&
			type.n_stab == 64)
	{
		if (object->sect == 1)
			return ('t');
		if (object->sect == 10 || object->sect == 12)
			return ('b');
		if (object->sect == 11)
			return ('d');
		if (object->sect == 5)
			return ('s');
	}
	if (type.n_pext == 0 && type.n_stab == 96)
	{
		return (get_type_one(object));
	}
	return (get_type_two(object));
}
