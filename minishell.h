#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define TRUE 1
#define FALSE 0

typedef struct s_cmd
{
    char	*cmd_path;
    char	*cmd;
    char	**cmd_args;
	char	*in_file;
	char	*out_file;
	char	*err_file;
}  cmd_t;



#endif