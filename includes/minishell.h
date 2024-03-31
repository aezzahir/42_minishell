#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

struct s_cmd
{
    char	*cmd_path;
    char	*cmd;
    char	**cmd_args;
	char	*in_file;
	char	*out_file;
	char	*err_file;
} typedef cmd_t;