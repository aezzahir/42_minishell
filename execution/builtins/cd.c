#include "../../minishell.h"


void cd(char *path)
{
    // Check if the path is not NULL and not empty
    if (path == NULL || path[0] == '\0')
    {
        fprintf(stderr, "cd: missing operand\n");
        return;
    }

    // Try changing directory
    if (chdir(path) != 0)
    {
        fprintf(stderr, "cd: %s: %s\n", path, strerror(errno));
    }
}
