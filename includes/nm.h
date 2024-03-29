/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:11:07 by aakin-al          #+#    #+#             */
/*   Updated: 2017/11/02 22:57:03 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "../lib/includes/lib.h"
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <ar.h>
# include <ranlib.h>

typedef struct			s_offset
{
	char				*name;
	uint32_t			offset;
	uint32_t			ran_strx;
	unsigned long long	make_time;
}						t_offset;

typedef struct			s_type
{
	unsigned int		n_stab;
	unsigned int		n_pext;
	unsigned int		n_type;
	unsigned int		n_ext;
}						t_type;

typedef struct			s_nm_basic
{
	unsigned long long	value;
	t_type				type;
	char				*name;
	short				desc;
	unsigned char		sect;
	int					obj_f;
}						t_nm_basic;

void					ft_nm(char *ptr, char *name, int args);
void					handle_64(char *ptr, int o);
int						comp_alpha(void *p1, void *p2, int reverse);
void					handle_fat32(char *ptr);
void					print_list(t_list *list, int obj);
char					get_type(t_nm_basic *object);
char					get_type_o(t_nm_basic *object);
void					build_list(struct symtab_command *s, char *p, int o);
void					set_type(char *n_type, t_type *type);
void					handle_32(char *ptr, int o);
void					print_list_32(t_list *list, int o);
void					build_list_32(struct symtab_command *s, char *p, int o);
void					handle_lib(char *ptr, char *name);
t_offset				*new_off_t_node(struct ranlib ran);
t_list					*make_list(struct ranlib ran, char *ptr);
void					parse_list(t_list *ar_list, char *ptr, char *lib_name);
int						comp_alpha_two(void *p1, void *p2, int reverse);
uint32_t				swap32(uint32_t x);
void					offset_del(void *off_struct, size_t size);
void					nm_del(void *nm, size_t size);
void					type_del(void *type, size_t sz);
#endif
