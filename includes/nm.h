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
// #include <nlist.h

// typedef struct  s_error {
//     int         fd_error : 1;
//     int         fstat_error : 1;
//     int         mmap_error : 1;
//     int         munmap_error : 1;
// }               t_error;

typedef struct      s_type{
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
}                       t_nm_basic;

void            handle_64(char *ptr);
int				comp_alpha(void *p1, void *p2, int reverse);

#endif