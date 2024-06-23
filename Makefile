CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g
 
LIBFT = libft/libft.a

SRC_FILES = main.c \
			parsing/1-split_tokens.c \
			parsing/free_split.c \
			parsing/ft_substrdup.c \
			parsing/utils.c \
			parsing/handle_specials/ft_handle_env_variables.c \
			parsing/handle_specials/ft_handle_herdoc.c \
			parsing/handle_specials/ft_handle_quotes.c \
			parsing/2-parse_cmds.c \
			parsing/2_get_cmd_path.c \
			parsing/handle_specials/handle_syntax_errors.c \
#			execution/execute.c \
			execution/heredoc.c \
			execution/pipes.c \
			execution/utils.c \
			execution/builtins/builtin.c \
			execution/builtins/cd.c \
			execution/builtins/echo.c \
			execution/builtins/env.c \
			execution/builtins/exit.c \
			execution/builtins/export.c \
			execution/builtins/pwd.c \
			execution/builtins/unset.c \
			execution/redirections.c \

OBJ_FILES = $(SRC_FILES:%.c=%.o)

EXECUTABLE = minishell

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft all
	make -C libft bonus

clean:
	rm -f $(OBJ_FILES)
	make -C libft clean

fclean: clean
	rm -f $(EXECUTABLE)
	make -C libft fclean

re: fclean all


leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./minishell

.PHONY: all clean fclean re