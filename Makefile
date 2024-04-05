CC = cc
CFLAGS = -Wall -Werror #-Wextra 
LIBFT = libft/libft.a
SRC_FILES = main.c ./parsing/0_ft_split_args.c ./parsing/ft_substrdup.c
OBJ_FILES = $(SRC_FILES:%.c=%.o)
EXECUTABLE = minishell

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS)  -lreadline -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft all

clean:
	rm -f $(OBJ_FILES)
	make -C libft clean

fclean: cleans

	rm -f $(EXECUTABLE)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
