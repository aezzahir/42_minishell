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
// 0 - tokenazing strings
void ft_split_args(t_list **tokens_list, char *cmd_line);
char	*ft_substrdup(const char *str, int *start, int *end);
// 1 - parsing commandes
t_cmd   *ft_parse_cmds(t_list *token, char **envp);
t_list *get_cmds_list(t_list *token, char **envp);
//
void	free_split(char **str);
int ft_iswhitespace(char *str, int *start, int *end, char c);
int ft_isquote(char *str, int *start, int *end, char c);
int ft_isdquote(char *str, int *start, int *end, char c);
int ft_ispipe(char *str, int *start, int *end, char c);
int ft_isoutfile(char *str, int *start, int *end, char c);
int ft_isinfile(char *str, int *start, int *end, char c);
int ft_isoutfile_appendmode(char *str, int *start, int *end, char c);
int ft_isherdoc(char *str, int *start, int *end, char c);
int ft_isdollar(char *str, int *start, int *end, char c);

char *get_path(char *cmd, char **envp);
char	*find_path(char **arge);
void get_paths(t_list *list_cmds, char **envp);


/// Excution part :-)


int ft_exec(t_list *cmds, char **envp);

#endif