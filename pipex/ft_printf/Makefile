CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = ./ft_printf.c ./ft_printf_utils.c
OBJS = $(SRCS:.c=.o)
HFILES = ft_printf.h
NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^	
$(OBJS): $(SRCS) $(HFILES)
	$(CC) $(CFLAGS) -c $(SRCS)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean $(NAME)

.PHONY: all bonus clean fclean re
