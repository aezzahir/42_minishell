
#include "../../minishell.h"
#include <string.h>


bool is_builtin(char *cmd)
{
    return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 ||
            ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 ||
            ft_strcmp(cmd, "exit") == 0);
}

void execute_builtin(char *args[])
{
    if (ft_strcmp(args[0], "cd") == 0)
        g_status = cd(args[1]);
    else if (ft_strcmp(args[0], "echo") == 0)
        g_status = echo(args);
    else if (ft_strcmp(args[0], "pwd") == 0)
        g_status = pwd();
    else if (ft_strcmp(args[0], "export") == 0)
        g_status = export_env(args[1]);
    else if (ft_strcmp(args[0], "unset") == 0)
        g_status = unset_env(args);
    else if (ft_strcmp(args[0], "env") == 0)
        g_status = env();
    else if (ft_strcmp(args[0], "exit") == 0)
        exit_shell(args[1]);
}
