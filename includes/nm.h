#ifndef NM_H
#define NM_H

#include "../lib/includes/lib.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#define SWAP32(x) ((((x) & 0xff000000) >> 24) | (((x) & 0xff0000) >> 8) | (((x) & 0xff00) << 8) | (((x) & 0xff) << 24))

typedef struct          s_type
{
    unsigned int        n_stab;
    unsigned int        n_pext;
    unsigned int        n_type;
    unsigned int        n_ext;
}                       t_type;

typedef struct          s_nm_basic
{
    unsigned long long  value;
    t_type              type;
    char                *name;
    short               desc;
    unsigned char       sect;
}                       t_nm_basic;

// void                    ft_nm(char *ptr);
void                    ft_nm(char *ptr, char *name);
void                    handle_64(char *ptr);
int				        comp_alpha(void *p1, void *p2, int reverse);
void                    handle_fat32(char *ptr);
void                    print_list(t_list *list);
char                    get_type(t_nm_basic *object);
void                    build_list(int nsyms, int symoff, int stroff, char *ptr);
void                    set_type(char *n_type, t_type *type);
void                    handle_32(char *ptr);
void                    print_list_32(t_list *list);
void                    build_list_32(int nsyms, int symoff, int stroff, char *ptr);

#endif