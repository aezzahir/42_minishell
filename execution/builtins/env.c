#include "../../minishell.h"

int env(void)
{
    extern char **environ;
    char **env;

    env = environ;
    if (env == NULL)
    {
        ft_putendl_fd("No environment variables found.", 2);
        return 1; // Non-zero indicates error
    }
    while (*env != NULL)
    {
        ft_putendl_fd(*env, 1);
        env++;
    }
    return 0; // Zero indicates success
}



// use it in main 
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