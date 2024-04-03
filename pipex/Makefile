CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a
PRINTF = ft_printf/libftprintf.a
SRC_FILES = main.c 0_ft_init_pipex.c 1_ft_check_args.c 2_ft_parse_args.c 3_ft_exec.c free_pipex.c free_split.c
OBJ_FILES = $(SRC_FILES:%.c=%.o)
EXECUTABLE = pipex

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft all
	make -C libft bonus

$(PRINTF):
	make -C ft_printf

clean:
	rm -f $(OBJ_FILES)
	make -C libft clean
	make -C ft_printf clean

fclean: clean
	rm -f $(EXECUTABLE)
	make -C libft fclean
	make -C ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
