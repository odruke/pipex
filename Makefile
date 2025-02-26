NAME = pipex

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

FT_PRINTF_LIBDIR = ./ft_printf

SRCDIR = ./src/

INCDIR = ./inc/

files = main\

SRC = $(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))

OBJ = (SRC:.c=.o)

INC = $(INCDIR)pipex.h

all: aux_librarie $(NAME)

$(NAME): $(OBJ) $(FT_PRINTF_LIB)
	$(CC) $(OBJ) $(FT_PRINTF_LIB) -o $@

%.o: %.c
	$(CC) -I$(INCDIR) $(CFLAGS) -c $< -o $@

aux_libraries:
	@make -C $(FT_PRINTF_LIBDIR) all

clean:
	rm -f $(OBJ)
	@make -C $(FT_PRINTF_LIBDIR) clean

fclean:
	rm -f $(NAME)
	@make -C $(FT_PRINTF_LIBDIR) fclean

re: fclean all

.PHONY: clean fclean all re aux_libraries
