/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:11:07 by aakin-al          #+#    #+#             */
/*   Updated: 2017/11/02 22:59:45 by aakin-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

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

void					ft_otool(char *ptr, char *name);
void					otool_64(char *ptr);
void					otool_32(char *ptr);
void					otool_fat32(char *ptr);
char					*ft_itoa_base_trim(uintmax_t val, int base, int trim);
void					handle_lib(char *ptr, char *name);
int						comp_alpha_two(void *p1, void *p2, int reverse);
t_list					*make_list(struct ranlib ran, char *ptr);
t_offset				*new_off_t_node(struct ranlib ran);
void					parse_list(t_list *ar_list, char *ptr, char *lib_name);
void					get_text_64(struct segment_command_64 *seg,
		struct mach_header_64 *header);
void					get_text_32(struct segment_command *seg,
		struct mach_header *header);
uint32_t				swap32(uint32_t x);
void					offset_del(void *off_struct, size_t size);
void					nm_del(void *nm, size_t size);
void					type_del(void *type, size_t sz);
#endif
