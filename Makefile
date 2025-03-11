NAME = pipex

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

FT_PRINTF_LIBDIR = ./ft_printf/

FT_PRINTF_LIB = $(FT_PRINTF_LIBDIR)printf.a

LIBFTDIR = ./libft/

LIBFT_LIB = $(LIBFTDIR)libft.a

SRCDIR = ./src/

INCDIR = ./inc/

FILES  = main\
		utils\
		error_and_exit\
		handle_procesess\
		parsing\
		parsing_cmd\
		parsing_cmd_utils\

SRC = $(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))

OBJ = $(SRC:.c=.o)

INC = $(INCDIR)pipex.h

all: aux_librarys $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(FT_PRINTF_LIB) $(LIBFT_LIB) -o $@

%.o: %.c
	$(CC) -I$(INCDIR) $(CFLAGS) -c $< -o $@

aux_librarys:
	make -C $(FT_PRINTF_LIBDIR) all
	make -C $(LIBFTDIR) all

clean:
	rm -f $(OBJ)
	make -C $(FT_PRINTF_LIBDIR) clean
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT_PRINTF_LIBDIR) fclean
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: clean fclean all re aux_libraries
