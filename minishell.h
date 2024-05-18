#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

//
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
//
#define TRUE 1
#define FALSE 0


int	g_status;

typedef struct s_prompt
{
	t_list	*cmds; // linked list of cmds ... 
	char	**envp;
	pid_t	pid;
}		t_prompt;

typedef struct s_cmd
{
	char	**cmd_args;
	char	*cmd_path;
	int	    in_fd;
	int	    out_fd;
}		t_cmd;
// 1 - tokenazing strings
void ft_split_tokens(t_list **tokens_list, char *input, char **envp, int *last_exit_status);
void ft_add_token(t_list **tokens_list, char *token);

// 1.1 - handles herdoc quotes and enviremental variables
char	*ft_handle_envar(char *token, char **envp);
char *ft_handle_heredoc(char *input, int *end);
char	*ft_handle_quote(char *input, int *start, int *end, char quote);
char *ft_exit_status(char *token, int *g_status);

char	*ft_substrdup(const char *str, int *start, int *end);






// 1 - parsing commandes
t_cmd   *ft_parse_cmds(t_list *token, char **envp);
t_list *get_cmds_list(t_list *token, char **envp);
//
void	free_split(char **str);

char *get_path(char *cmd, char **envp);
char	*find_path(char **arge);
void get_paths(t_list *list_cmds, char **envp);


/// Excution part :-)


int ft_exec(t_list *cmds, char **envp);





// utility functions 
int ft_iswhitespace(char c);
#endif