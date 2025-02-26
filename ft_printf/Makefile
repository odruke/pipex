#variables

NAME = libftprintf.a

LIB = libft.a

SRCDIR = ./src/

INCDIR = ../inc/

FILES = ft_flags\
		ft_printchar\
		ft_printf\
		ft_printstr\
		ft_utils\
		ft_printhex\
		ft_printnbr\
		ft_printptr\
		ft_printunsigned\
		ft_printf_itoa

SRC = $(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))

INC = $(addprefix $(INCDIR), ft_printf.h)

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

#rules
all: $(NAME)

bonus: $(all)

$(NAME): $(LIB) $(OBJ)
	mv  $(INCDIR)$(LIB) $(NAME)
	ar rcs $(NAME) $(OBJ)

$(LIB):
	make -C libft

%.o: %.c
	$(CC) -I$(INCDIR) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C libft
fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: clean fclean re all
