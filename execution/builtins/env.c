#include "../../minishell.h"

void env()
{
    extern char **environ;
    char **env = environ;
    while (*env != 0) {
        printf("%s\n", *env);
        env++;
    }
}

