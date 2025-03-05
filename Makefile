NAME = pipex

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

FT_PRINTF_LIBDIR = ./ft_printf/

FT_PRINTF_LIB = $(FT_PRINTF_LIBDIR)libftprintf.a 

SRCDIR = ./src/

INCDIR = ./inc/

FILES  = main\
		utils\
		error_and_exit\
		handle_procesess\
		ft_split_cmd\

SRC = $(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))

OBJ = $(SRC:.c=.o)

INC = $(INCDIR)pipex.h

all: aux_library $(NAME)

$(NAME): $(OBJ) $(FT_PRINTF_LIB)
	$(CC) $(OBJ) $(FT_PRINTF_LIB) -o $@

%.o: %.c
	$(CC) -I$(INCDIR) $(CFLAGS) -c $< -o $@

aux_library:
	@make -C $(FT_PRINTF_LIBDIR) all

clean:
	rm -f $(OBJ)
	@make -C $(FT_PRINTF_LIBDIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(FT_PRINTF_LIBDIR) fclean

re: fclean all

.PHONY: clean fclean all re aux_libraries
