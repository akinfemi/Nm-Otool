#include "libft.h"

int     ft_sqrt(size_t num)
{
    size_t i;

    i = 1;
    while (i * i <= num)
        i++;
    return ((int)i - 1);
}