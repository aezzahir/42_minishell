#include "../../minishell.h"

void exit_shell(char *arg)
{
    int status;

    if (arg == NULL)
        exit(0);
    if (!is_number(arg) && *arg)
    {
        print_error("numeric argument required", arg);
        exit(255);
    }
    status = atoi(arg);
    exit(status);
}
