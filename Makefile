# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aakin-al <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/01 10:11:56 by aakin-al          #+#    #+#              #
#    Updated: 2017/09/01 14:27:59 by aakin-al         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM := ft_nm
OTOOL := ft_otool

CFLAGS := -Wall -Wextra -g -Werror -I includes/

LIB := lib/lib.a

NM_FILES := nm.c handlers.c comp_func.c util.c ar.c util32.c clean_up.c

OT_FILES := otool.c otool_handlers.c otool_handlers2.c\
			ft_itoa_base_trim.c util.c clean_up.c

.PHONY = all fclean clean re

NM_F = $(addprefix nm_src/, $(NM_FILES))
OT_F = $(addprefix otool_src/, $(OT_FILES))

ONM_F = $(NM_F:.c=.o)
OOT_F = $(OT_F:.c=.o)

all : $(NM) $(OTOOL)

$(LIB):
	@make -C lib/

$(ONM_F):%.o: %.c
	@gcc -c $(CFLAGS) $< -o $@

$(OOT_F):%.o: %.c
	@gcc -c $(CFLAGS) $< -o $@

$(NM): $(LIB) $(ONM_F)
	@gcc $(ONM_F) $(LIB) -o $(NM)

$(OTOOL): $(LIB) $(OOT_F)
	@gcc $(OOT_F) $(LIB) -o $(OTOOL)

clean:
	@rm -f $(ONM_F)
	@rm -f $(OOT_F)
	@make -C lib clean

fclean: clean
	@rm -f $(LIB)
	@rm -f $(NM)
	@rm -f $(OTOOL)
	@make -C lib fclean

re: fclean all
