#ifndef OTOOL_H
#define OTOOL_H

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

void            ft_otool(char *ptr);
void            otool_64(char *ptr);
void            otool_32(char *ptr);
void            otool_fat32(char *ptr);
char            *ft_itoa_base_trim(uintmax_t val, int base, int trim);

#endif