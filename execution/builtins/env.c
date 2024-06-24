#include "../../minishell.h"

void env(void)
{
    extern char **environ;
    char **env = environ;

    if (env == NULL)
    {
        ft_putendl_fd("No environment variables found.", 2);
        return;
    }

    while (*env != NULL)
    {
        ft_putendl_fd(*env, 1);
        env++;
    }
}


void setup_default_env(void)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        setenv("PWD", cwd, 1);
    }
    setenv("SHLVL", "1", 1);
setenv("_", "/usr/bin/env", 1);
}