#include "../../minishell.h"


int check_name(const char *name)
{
    int j = 0;
    while (name[j])
    {
        if (!ft_isalnum((int)name[j]) && name[j] != '_')
        {
            fprintf(stderr, "Invalid variable name\n");
            return 1;
        }
        j++;
    }
    return 0;
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

void export_env(char *var)
{
    if (var == NULL || ft_strchr(var, '=') == NULL)
    {
        print_error("invalid format", var);
        return;
    }

    int i = 0;
    int append = 0;
    while (var[i] && var[i] != '=' && var[i] != '+')
        i++;

    if (var[i] == '+' && var[i + 1] == '=')
    {
        append = 1;
        var[i] = '\0';
        i++;
    }

    char *name = malloc(i + 1);
    if (name == NULL)
    {
        perror("export");
        return;
    }
    strncpy(name, var, i);
    name[i] = '\0'; // Null-terminate the substring

    if (check_name(name))
    {
        free(name);
        return;
    }

    char *value = ft_strdup(var + i + 1);
    if (value == NULL)
    {
        perror("export");
        free(name);
        return;
    }

    if (append)
    {
        char *old_value = getenv(name);
        if (old_value)
        {
            char *new_value = malloc(ft_strlen(old_value) + ft_strlen(value) + 1);
            if (new_value == NULL)
            {
                perror("export");
                free(name);
                free(value);
                return;
            }
            sprintf(new_value, "%s%s", old_value, value);
            free(value);
            value = new_value;
        }
    }

    char *var_copy = malloc(ft_strlen(name) + ft_strlen(value) + 2);
    if (var_copy == NULL)
    {
        perror("export");
        free(name);
        free(value);
        return;
    }

    sprintf(var_copy, "%s=%s", name, value);

    if (putenv(var_copy) != 0)
    {
        perror("export");
        free(var_copy);
    }
    free(name);
    free(value);
}