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
// #include <nlist.h

// typedef struct  s_error {
//     int         fd_error : 1;
//     int         fstat_error : 1;
//     int         mmap_error : 1;
//     int         munmap_error : 1;
// }               t_error;

typedef struct      s_type
{
    unsigned int    n_stab;
    unsigned int    n_pext;
    unsigned int    n_type;
    unsigned int    n_ext;
} t_type;

typedef struct          s_nm_basic
{
    unsigned long long  value;
    t_type              type;
    char                *name;
    short               desc;
    unsigned char       sect;
}                       t_nm_basic;

void            handle_64(char *ptr);
int				comp_alpha(void *p1, void *p2, int reverse);
void            handle_fat32(char *ptr);
void            print_list(t_list *list);
char            get_type(t_nm_basic *object);
void            build_list(int nsyms, int symoff, int stroff, char *ptr);
void            set_type(char *n_type, t_type *type);
void            handle_32(char *ptr);

#endif