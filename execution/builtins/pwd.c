#include "../../minishell.h"

int pwd()
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        return 0; // Zero indicates success
    }
    else
    {
        perror("pwd");
        return 1; // Non-zero indicates error
    }
}
