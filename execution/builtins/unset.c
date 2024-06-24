#include "../../minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void ft_free(void *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = NULL;
    }
}

void print_unset_error(const char *msg, const char *arg)
{
    ft_putstr_fd("unset: ", STDERR_FILENO);
    ft_putstr_fd((char *)msg, STDERR_FILENO);
    if (arg)
    {
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putendl_fd((char *)arg, STDERR_FILENO);
    }
}

void unset_env_var(char *var)
{
    if (var == NULL || *var == '\0' || strchr(var, '=') != NULL)
    {
        print_unset_error("invalid variable name", var);
        return;
    }

    if (unsetenv(var) != 0)
    {
        perror("unset");
    }
}

void unset_env(char **vars)
{
    int i = 1;
    while (vars[i])
    {
        unset_env_var(vars[i]);
        i++;
    }
}

void execute_command(const char *cmd)
{
    if (system(cmd) == -1)
    {
        perror("system");
    }
}

