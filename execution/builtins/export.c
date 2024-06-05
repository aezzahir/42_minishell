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


void export_env(char *var)
{
    if (var == NULL || strchr(var, '=') == NULL)
    {
        fprintf(stderr, "export: invalid format\n");
        return;
    }

    int i = 0;
    while (var[i] && var[i] != '=')
        i++;

    char *name = strndup(var, i);
    if (name == NULL)
    {
        perror("export");
        return;
    }

    if (check_name(name))
    {
        free(name);
        return;
    }

    char *value = strdup(var + i + 1);
    if (value == NULL)
    {
        perror("export");
        free(name);
        return;
    }

    char *var_copy = malloc(strlen(name) + strlen(value) + 2);
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