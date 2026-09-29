CC      = cc
CFLAGS  = -Wall -Werror -Wextra
NAME    = libft.a

SRCS    = srcs/ft_putchar.c \
          srcs/ft_putstr.c \
          srcs/ft_strcmp.c \
          srcs/ft_strlen.c \
          srcs/ft_swap.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar	rcs	$(NAME)	$(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I includes -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
