#include "../includes/nm.h"

void		offset_del(void *in, size_t size)
{
	t_offset *off_struct;

	off_struct = (t_offset *)in;
	if (!off_struct)
		return ;
	(void)size;
	if (off_struct->name)
		free(off_struct->name);
	free(off_struct);
}

void		nm_del(void *in, size_t size)
{
	t_nm_basic		*nm;

	nm = (t_nm_basic *)in;
	if (!nm)
		return ;
	(void)size;
	if (nm->name)
		free(nm->name);
	free(nm);
}

void		type_del(void *in, size_t sz)
{
	t_type	*type;

	type = (t_type *)in;
	(void)sz;
	if (!type)
		return ;
	free(type);
}

uint32_t		swap32(uint32_t x)
{
	return((((x) & 0xff000000) >> 24) | (((x) & 0xff0000) >> 8) |
	(((x) & 0xff00) << 8) | (((x) & 0xff) << 24));
}