#include "../../minishell.h"

void unset_env(char *var)
{
    if (var == NULL || *var == '\0' || strchr(var, '=') != NULL)
    {
        fprintf(stderr, "unset: invalid variable name\n");
        return;
    }

    if (unsetenv(var) != 0)
    {
        perror("unset");
    }
}
