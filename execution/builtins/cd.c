#include "../../minishell.h"
#include <unistd.h>
#include <limits.h>
void cd(char *path)
{
    if (path == NULL || path[0] == '\0')
    {
        fprintf(stderr, "cd: missing operand\n");
        return; 
    }

    if (chdir(path) != 0)
    {
        fprintf(stderr, "cd: %s: %s\n", path, strerror(errno));
    }
    else
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            setenv("PWD", cwd, 1);
        }
        else
        {
            fprintf(stderr, "cd: could not update PWD: %s\n", strerror(errno));
        }
    }
}