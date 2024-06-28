#include "../../minishell.h"
#include <unistd.h>
#include <limits.h>

int cd(char *path)
{
    char cwd[1024];

    if (path == NULL || path[0] == '\0')
    {
        fprintf(stderr, "cd: missing operand\n");
        return 1; // Non-zero indicates error
    }
    if (chdir(path) != 0)
    {
        fprintf(stderr, "cd: %s: %s\n", path, strerror(errno));
        return 1;
    }
    else
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            setenv("PWD", cwd, 1);
        else
        {
            fprintf(stderr, "cd: could not update PWD: %s\n", strerror(errno));
            return 1;
        }
    }
    return 0; // Zero indicates success
}
