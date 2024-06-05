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