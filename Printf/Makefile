CC      = cc
CFLAGS  = -Wall -Werror -Wextra
NAME    = libftprintf.a
AR		= ar rcs

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

SRCS    = ft_printf.c \
		  ft_print_csuid.c \
		  ft_print_hexp.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
