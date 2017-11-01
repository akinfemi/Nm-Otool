NM := ft_nm
OTOOL := ft_otool

CFLAGS := -Wall -Wextra -g -Werror -I includes/

LIB := lib/lib.a

NM_FILES := nm.c handlers.c comp_func.c util.c ar.c

OT_FILES := otool.c otool_handlers.c ft_itoa_base_trim.c

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