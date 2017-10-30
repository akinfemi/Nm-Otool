#include "otool.h"

void            ft_otool(char *ptr)
{
    unsigned int     mag_no;
    
    mag_no = *(int *)ptr;
    if (mag_no == MH_MAGIC_64)
    {
        otool_64(ptr);
    }
    else if (mag_no == MH_MAGIC)
    {
        otool_32(ptr);
    }
    else if (mag_no == FAT_CIGAM)
    {
        otool_fat32(ptr);
    }
    else {
        ft_printf("Magic Number %d currently not handled.\n", mag_no);
    }
}

int             main(int ac, char **ag)
{
    int         fd;
    char        *ptr;
    struct stat buf;
    int         i;

    if (ac == 1)
    {
        ft_printf("Usage: %s <exec1> <exec2> ...\n", ag[0]);
        return (EXIT_FAILURE);
    }
    i = 1;
    while (i < ac)
    {
        if ((fd = open(ag[1], O_RDONLY)) < 0)
        {
            ft_putstr_fd("Open Error\n", 2);
            return (EXIT_FAILURE);
        }
        if (fstat(fd, &buf) < 0)
        {
            ft_putstr_fd("fstat Error\n", 2);
            return (EXIT_FAILURE);
        }
        if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
        {
            ft_putstr_fd("mmap error\n", 2);
            return (EXIT_FAILURE);
        }
        ft_printf("%s:\n", ag[1]);
        ft_otool(ptr);
        if (munmap(ptr, buf.st_size) < 0)
        {
            ft_putstr_fd("munmap error\n", 2);
            return (EXIT_FAILURE);
        }
        close(fd);
        i++;
    }
    return (EXIT_SUCCESS);
}