
#include "../../minishell.h"
#include <string.h>


void execute_builtin(char *args[])
{
    if (ft_strcmp(args[0], "cd") == 0)
        cd(args[1]);
    else if (ft_strcmp(args[0], "echo") == 0)
        echo(args);
    else if (ft_strcmp(args[0], "pwd") == 0)
        pwd();
    else if (ft_strcmp(args[0], "export") == 0)
        export_env(args[1]);
    else if (ft_strcmp(args[0], "unset") == 0)
        unset_env(args[1]);
    else if (ft_strcmp(args[0], "env") == 0)
        env();
    else if (ft_strcmp(args[0], "exit") == 0)
    {
        int status = args[1] ? ft_atoi(args[1]) : 0;
        exit_shell(status);
    }
}