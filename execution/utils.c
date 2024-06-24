#include "../minishell.h"

int is_number(const char *str)
{
    if (*str == '\0')
        return 0;

    while (*str)
    {
        if (!ft_isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}


void print_env_vars(void)
{
    extern char **environ;
    for (char **env = environ; *env; ++env)
    {
        printf("declare -x %s\n", *env);
    }
}

void print_error(const char *msg, const char *arg)
{
    ft_putstr_fd("export: ", STDERR_FILENO);
    ft_putstr_fd((char *)msg, STDERR_FILENO);
    if (arg)
    {
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putendl_fd((char *)arg, STDERR_FILENO);
    }
}