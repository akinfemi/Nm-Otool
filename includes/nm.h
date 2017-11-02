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
#include <ar.h>
#include <ranlib.h>
#define SWAP32(x) ((((x) & 0xff000000) >> 24) | (((x) & 0xff0000) >> 8) | (((x) & 0xff00) << 8) | (((x) & 0xff) << 24))

typedef struct          s_offset
{
    char                *name;
    uint32_t            offset;
    uint32_t            ran_strx;
    unsigned long long  make_time;
}                       t_offset;

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
    int                 obj_f;
}                       t_nm_basic;

void                    ft_nm(char *ptr, char *name, int args);
void                    handle_64(char *ptr, int o);
int				        comp_alpha(void *p1, void *p2, int reverse);
void                    handle_fat32(char *ptr);
void                    print_list(t_list *list, int obj);
char                    get_type(t_nm_basic *object);
void                    build_list(struct symtab_command *s, char *ptr, int obj);
void                    set_type(char *n_type, t_type *type);
void                    handle_32(char *ptr,int o);
void                    print_list_32(t_list *list, int o);
void                    build_list_32(struct symtab_command *s, char *ptr, int obj);
void                    handle_lib(char *ptr, char *name);
t_offset                *new_off_t_node(struct ranlib ran);
t_list                  *make_list(struct ranlib ran, char *ptr);
void                    parse_list(t_list *ar_list, char *ptr, char *lib_name);
int                     comp_alpha_two(void *p1, void *p2, int reverse);
#endif