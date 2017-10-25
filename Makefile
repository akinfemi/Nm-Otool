NM := ft_nm
OTOOL := ft_otool

CFLAGS := -Wall -Wextra -g -Werror -I includes/

LIB := lib/lib.a

NM_FILES := 

OT_FILES := 

.PHONY = all fclean clean re

NM_F = $(addprefix nm_src/, $(NM_FILES))
OT_F = $(addprefix otool_src/, $(OT_FILES))

ONM_F = $(NM_F:.c=.o)
OOT_F = $(OT_F:.c=.o)

all : $(NM) $(OTOOL)

#all : $(OTOOL)

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
	@rm -f $(OOT_F)
	@rm -f $(ONM_F)
	@make -C lib clean

fclean: clean
	@rm -f $(LIB)
	@rm -f $(OTOOL)
	@rm -f $(NM)
	@make -C lib fclean

re: fclean all
