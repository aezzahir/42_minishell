CC = gcc
CFLAGS = -Wall -Werror -Wextra
 
LIBFT = libft/libft.a

SRC_FILES = main.c \
			parsing/handle_specials/ft_handle_env_variables.c \
			execution/execute.c \
			execution/builtin.c \
			execution/redirections.c \
			parsing/handle_specials/ft_handle_herdoc.c \
			parsing/handle_specials/ft_handle_quotes.c \
			parsing/handle_specials/handle_syntax_errors.c \
			parsing/1-split_tokens.c \
			parsing/2-parse_cmds.c \
			parsing/2_get_cmd_path.c \
			parsing/free_split.c \
			parsing/ft_substrdup.c \
			parsing/utils.c

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

.PHONY: all clean fclean re