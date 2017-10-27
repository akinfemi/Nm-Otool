#include "../includes/nm.h"

void            ft_nm(char *ptr)
{
    unsigned int     mag_no;

    mag_no = *(int *)ptr;
    if (mag_no == MH_MAGIC_64)
    {
        handle_64(ptr);
    }
    else if (mag_no == MH_MAGIC)
    {
        handle_32(ptr);
    }
    else if (mag_no == FAT_CIGAM)
    {
        handle_fat32(ptr);
        // print_fat_header(ptr);
    }
    else{
        ft_printf("Magic Number %d currently not handled. %d\n", mag_no, MH_MAGIC);
    }
}

int             main(int ac, char **ag)
{
    int         fd;
    char        *ptr;
    struct stat buf;

    if (ac == 1)
    {
        ft_printf("Usage: %s <exec1> <exec2>\n", ag[0]);
        return (EXIT_FAILURE);
    }
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
    ft_nm(ptr);
    if (munmap(ptr, buf.st_size) < 0)
    {
        ft_putstr_fd("munmap error\n", 2);
        return (EXIT_FAILURE);
    }
    close(fd);
    return (EXIT_SUCCESS);
}