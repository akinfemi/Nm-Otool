#include "../includes/nm.h"

int				comp_alpha(void *p1, void *p2, int reverse)
{
	int		result;
	char	*tmp1;
    char	*tmp2;
    t_nm_basic  *f1;
    t_nm_basic  *f2;

    f1 = (t_nm_basic *)p1;
    f2 = (t_nm_basic *)p2;
	tmp1 = ft_strtolower(ft_strdup(f1->name));
	tmp2 = ft_strtolower(ft_strdup(f2->name));
	result = (ft_strcmp(tmp1, tmp2));
	free(tmp1);
	free(tmp2);
	if (reverse)
	{
		if (result == 0)
			return (f1->value > f2->value ? 1 : 0);
		return (result < 0 ? 1 : 0);
	}
	else
	{
		if (result == 0)
			return (f1->value > f2->value ? 1 : 0);
		return (result > 0 ? 1 : 0);
	}
}

// int				comp_alpha_two(void *p1, void *p2, int reverse)
// {
// 	int		result;
// 	char	*tmp1;
//     char	*tmp2;
//     t_offset  *f1;
//     t_offset  *f2;

//     f1 = (t_offset *)p1;
//     f2 = (t_offset *)p2;
// 	tmp1 = ft_strtolower(ft_strdup(f1->name));
// 	tmp2 = ft_strtolower(ft_strdup(f2->name));
// 	result = (ft_strcmp(tmp1, tmp2));
// 	free(tmp1);
// 	free(tmp2);
// 	if (reverse)
// 	{
// 		if (result == 0)
// 			return (f1->offset > f2->offset ? 1 : 0);
// 		return (result < 0 ? 1 : 0);
// 	}
// 	else
// 	{
// 		if (result == 0)
// 			return (f1->offset > f2->offset ? 1 : 0);
// 		return (result > 0 ? 1 : 0);
// 	}
// }

int				comp_alpha_two(void *p1, void *p2, int reverse)
{
    t_offset  *f1;
    t_offset  *f2;

    f1 = (t_offset *)p1;
	f2 = (t_offset *)p2;
	if (!reverse)
		return (f1->make_time > f2->make_time ? 1 : 0);
	return (f1->make_time < f2->make_time ? 1 : 0);
}