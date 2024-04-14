#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

#define TRUE 1
#define FALSE 0


typedef struct s_cmd
{
    char	*cmd_path;
    char	*cmd;
    char	**cmd_args;
	char	*in_file;
	char	*out_file;
}  cmd_t;

void ft_split_args(t_list **tokens_list, char *cmd_line);
char	*ft_substrdup(const char *str, int *start, int *end);

//

int ft_iswhitespace(char *str, int *start, int *end, char c);
int ft_isquote(char *str, int *start, int *end, char c);
int ft_isdquote(char *str, int *start, int *end, char c);
int ft_ispipe(char *str, int *start, int *end, char c);
int ft_isoutfile(char *str, int *start, int *end, char c);
int ft_isinfile(char *str, int *start, int *end, char c);
int ft_isoutfile_appendmode(char *str, int *start, int *end, char c);
int ft_isherdoc(char *str, int *start, int *end, char c);
int ft_isdollar(char *str, int *start, int *end, char c);


#endif