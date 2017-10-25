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

// typedef struct  s_error {
//     int         fd_error : 1;
//     int         fstat_error : 1;
//     int         mmap_error : 1;
//     int         munmap_error : 1;
// }               t_error;

void        handle_64(char *ptr);

#endif